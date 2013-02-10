/** 
* @file CholeskyRobust.cpp
* @brief robust cholesky decomposition by adding some noise
* @author Erik Rodner
* @date 01/06/2010

*/
#include <iostream>

#include "CholeskyRobust.h"
#include "core/vector/Algorithms.h"

#ifdef NICE_USELIB_CUDACHOLESKY
#include "cholesky-gpu/niceinterface/CudaCholeskyNICE.h"
#endif

using namespace std;
using namespace NICE;
using namespace NICE;


CholeskyRobust::CholeskyRobust (const CholeskyRobust & src):m_verbose (src.m_verbose), m_noise (src.m_noise),
        m_useCuda (src.m_useCuda), m_logDetMatrix (src.m_logDetMatrix)
{
}

double
CholeskyRobust::robustChol (const Matrix & A, Matrix & cholA)
{
	// this additional memory requirement could be skipped
	// with a modified cholesky routine
	Matrix ARegularized (A);

	if (m_verbose)
		cerr << "CholeskyRobust::robustChol: Adding noise " << m_noise << endl;

  // add a constant value to the diagonal
	ARegularized.addIdentity (m_noise);

  // check whether the cholesky-gpu sub-library is installed
#ifdef NICE_USELIB_CUDACHOLESKY
	if (m_useCuda)
    try {
  		CudaCholeskyNICE::choleskyDecomp (ARegularized, cholA);
    } catch (CudaError & e)
		{
			fthrow (CudaError, e.what ());
    }
	else
#endif
    // use the cholesky decomposition available in core/vector/
    // we use the large scale version here, because we expect that if you use
    // CholeskyRobust, you do not have input matrices with a few elements
		choleskyDecompLargeScale (ARegularized, cholA);

  // compute the logarithm of the log determinant by
  // summing up logarithms of all diagonal elements
  // multiplication by 2 is necessary, because ARegularized = cholA'*cholA
	m_logDetMatrix = 2 * triangleMatrixLogDet (cholA);
	if (m_verbose)
		cerr << "CholeskyRobust::robustChol: Cholesky condition (logdet): " << m_logDetMatrix << endl;

  // if the log determinant is NaN or Inf, then we should warn!
	if (!NICE::isFinite (m_logDetMatrix))
	{
		fthrow (Exception,
						"The matrix has infinite or not defined log determinant !");
	}

	return m_noise;
}

double
CholeskyRobust::robustCholInv (const Matrix & A, Matrix & invA)
{
	Matrix G;
	double noise = robustChol (A, G);
	if (m_verbose)
		cerr << "CholeskyRobust::robustChol: Cholesky inversion" << endl;

	choleskyInvertLargeScale (G, invA);

	return noise;
}


CholeskyRobust::~CholeskyRobust ()
{
}

CholeskyRobust::CholeskyRobust (bool verbose, double noise, bool useCuda):
    m_verbose (verbose), m_noise(noise),  m_useCuda (useCuda)
{
	m_logDetMatrix = - std::numeric_limits<double>::max();
}

CholeskyRobust *
CholeskyRobust::clone (void) const
{
	CholeskyRobust *dst = new CholeskyRobust (*this);
	return dst;
}
