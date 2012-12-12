/** 
* @file CholeskyRobustAuto.h
* @author Erik Rodner
* @date 01/06/2010

*/
#ifndef _NICE_NICE_CHOLESKYROBUSTAUTOINCLUDE
#define _NICE_NICE_CHOLESKYROBUSTAUTOINCLUDE

#include <limits>
#include "core/vector/MatrixT.h"

#include "CholeskyRobust.h"

namespace NICE
{

/** @class CholeskyRobustAuto
 * robust cholesky decomposition by iteratively adding some noise 
 *
 * @author Erik Rodner
 */
class CholeskyRobustAuto : public CholeskyRobust
{

	protected:

    /** minimal log determinant */ 
	  double m_minMatrixLogDeterminant;

	public:
    /**
    * @brief copy constructor
    *
    * @param src input object
    */
		CholeskyRobustAuto (const CholeskyRobustAuto & src);

    /**
    * @brief constructor
    *
    * @param verbose whether to display a bunch of messages
    * @param noise constant added iteratively to the main diagonal
    * @param minMatrixLogDeterminant if the log determinant is greater than this threshold, we accept the decomposition
    * @param useCuda whether to use cuda with the cholesky-gpu sub-library
    */
		CholeskyRobustAuto (bool verbose = true, 
                        double noiseStep = 1e-8, 
                        double minMatrixLogDeterminant = -std::numeric_limits < double >::max (), 
                        bool useCuda = true);

	  virtual ~ CholeskyRobustAuto ();

    /**
    * @brief Compute the Cholesky decompisition with iterative regularization, i.e.
    * we add a constant value to the diagonal of the input matrix until we get a numerical stable
    * result determined by checking the log determinant.
    *
    * @param A input matrix
    * @param cholA Cholesky factor
    *
    * @return 
    */
		virtual double robustChol (const NICE::Matrix & A, NICE::Matrix & cholA);

    /** clone the object */
		virtual CholeskyRobustAuto *clone (void) const;

};

}

#endif
