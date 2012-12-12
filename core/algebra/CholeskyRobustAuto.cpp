/** 
* @file CholeskyRobustAuto.cpp
* @brief robust cholesky decomposition by iteratively adding some noise
* @author Erik Rodner
* @date 01/06/2010

*/
#include <iostream>

#include "core/vector/Algorithms.h"

#include "CholeskyRobustAuto.h"

// include the optional cholesky sub-library, when available
#ifdef NICE_USELIB_CUDACHOLESKY
#include "cholesky-gpu/niceinterface/CudaCholeskyNICE.h"
#endif

using namespace std;
using namespace NICE;

/** number of maximum iterations used for regularization */
const int maxiterations = 30;
/** should we use exponential scaling for the regularization parameter */
const bool exponential_noise = true;
/** multiply in each iteration with this value (only if exponential noise is on) */
const double exp_multiplication_factor = 10.0;

CholeskyRobustAuto::CholeskyRobustAuto (const CholeskyRobustAuto & src):
CholeskyRobust (src)
{
  m_minMatrixLogDeterminant = src.m_minMatrixLogDeterminant;
}

double
CholeskyRobustAuto::robustChol (const Matrix & A, Matrix & cholA)
{
	// this additional memory requirement could be skipped
	// with a modified cholesky routine
	Matrix ARegularized (A);

	if (m_verbose)
		cerr << "CholeskyRobustAuto::robustChol: A " << A.rows () << " x " << A.cols () << endl;

	int i = 0;
	double noise = 0.0;
	double noiseStepExp = m_noise;
	bool robust = true;

  // iteration loop
	do
	{
    // first of all, we assume everything is fine
		robust = true;

		if (m_verbose)
			cerr << "CholeskyRobustAuto::robustChol: Cholesky decomposition" << endl;

		try
		{
#ifdef NICE_USELIB_CUDACHOLESKY
			if (m_useCuda)
				CudaCholeskyNICE::choleskyDecomp (ARegularized, cholA);
			else
#endif
				choleskyDecompLargeScale (ARegularized, cholA);
#ifdef NICE_USELIB_CUDACHOLESKY
		} // catch a nasty Cuda error
		catch (CudaError & e)
		{
			fthrow (CudaError, e.what ());
#endif
		}
		catch (Exception)
		{
			if (m_verbose)
				cerr << "CholeskyRobustAuto::robustChol: failed!" << endl;
      // Cholesky decomposition failed, therefore, we have to run again
			robust = false;
		}

    // check whether the Cholesky factor contains nasty NaN values
		if (robust && cholA.containsNaN ())
		{
			if (m_verbose)
				cerr <<
					"CholeskyRobustAuto::robustChol: cholesky matrix contains NaN values"
					<< endl;
      // if it contains NaNs it is surely not robust
			robust = false;
		}

    // set the log determinant to the minimum value
    // just in case we do not achieve a robust estimate
		m_logDetMatrix = m_minMatrixLogDeterminant;
		if (robust)
		{
      // compute the log determinant
			m_logDetMatrix = 2 * triangleMatrixLogDet (cholA);
			if (m_verbose)
				cerr << "CholeskyRobustAuto::robustChol: Cholesky condition: " <<
					m_logDetMatrix << endl;
		}


		if (isnan (m_logDetMatrix) || (m_logDetMatrix < m_minMatrixLogDeterminant))
		{
			robust = false;
		}

		if (!robust)
		{
			robust = false;
			if (m_verbose)
				cerr << "CholeskyRobustAuto::robustChol: Adding noise " << noiseStepExp
					<< endl;

      // in case the last estimate was not robust 
      // (1) add something to the diagonal
			ARegularized.addIdentity (noiseStepExp);
			noise += noiseStepExp;

      // increase the noise
			if (exponential_noise)
				noiseStepExp *= exp_multiplication_factor;
		}

		i++;
	}
  // while we did not achieve a robust value and the maximum number of iterations
  // is not reached
	while (!robust && (i < maxiterations));

	if (!robust)
		fthrow (Exception,
						"Inverse matrix is instable (please adjust the noise step term)");

	return noise;
}

CholeskyRobustAuto::~CholeskyRobustAuto ()
{
}

CholeskyRobustAuto::CholeskyRobustAuto (bool verbose, double noiseStep, double minMatrixLogDeterminant, bool useCuda):
    CholeskyRobust (verbose, noiseStep, useCuda)
{
  m_minMatrixLogDeterminant = minMatrixLogDeterminant;
}

CholeskyRobustAuto *CholeskyRobustAuto::clone (void) const 
{
	return new CholeskyRobustAuto (*this);
}
