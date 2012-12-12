/** 
* @file CholeskyRobust.h
* @author Erik Rodner
* @date 01/06/2010

*/
#ifndef _NICE_NICE_CHOLESKYROBUSTINCLUDE
#define _NICE_NICE_CHOLESKYROBUSTINCLUDE

#include <limits>
#include "core/vector/MatrixT.h"

namespace NICE
{

/** @class CholeskyRobust
 * robust cholesky decomposition by adding some noise 
 *
 * @author Erik Rodner
 */
class CholeskyRobust
{

	protected:
    /** output some messages */
		const bool m_verbose;

    /** noise added to the main diagonal */
		const double m_noise;

    /** should cuda be used */
		const bool m_useCuda;

    /** store the logarithm of the determinant */
		double m_logDetMatrix;


	public:

    
    /**
    * @brief constructor 
    *
    * @param verbose whether to display a bunch of messages
    * @param noise constant added to the main diagonal
    * @param useCuda whether to use cuda with the cholesky-gpu sub-library
    */
    CholeskyRobust (bool verbose = true, double noise = 1e-8, bool useCuda =	true);

    /**
    * @brief copy constructor
    *
    * @param src objrec to copy from (settings)
    */
    CholeskyRobust (const CholeskyRobust & src);

    /**
    * @brief destructor, currently empty
    */
    virtual ~CholeskyRobust ();

    /**
    * @brief Compute the Cholesky decomposition with additional regularization given to the
    * constructor of the object
    *
    * @param A input matrix
    * @param cholA Cholesky factor
    *
    * @return noise added to the diagonal of the matrix
    */
		virtual double robustChol (const NICE::Matrix & A, NICE::Matrix & cholA);

    /**
    * @brief Invert a positive definite matrix using its Cholesky decomposition and 
    * additional regularization. The function uses robustChol and is available for
    * every child class.
    *
    * @param A input matrix
    * @param invA inverse of the matrix (take care of the regularization)
    *
    * @return noise added to the diagonal of the matrix
    */
		virtual double robustCholInv (const NICE::Matrix & A, NICE::Matrix & invA);

    /**
    * @brief get the last log determinant computed
    *
    * @return log determinant of the last calculation
    */
		double getLastLogDet () const
		{
			return m_logDetMatrix;
		};

    /**
    * @brief clone the object
    */
		virtual CholeskyRobust *clone (void) const;

};

}

#endif
