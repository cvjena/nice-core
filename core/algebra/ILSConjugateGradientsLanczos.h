/** 
* @file ILSConjugateGradientsLanczos.h
* @author Paul Bodesheim
* @date 20/01/2012 (dd/mm/yyyy)

*/
#ifndef _NICE_ILSConjugateGradientsLanczos_INCLUDE
#define _NICE_ILSConjugateGradientsLanczos_INCLUDE

#include "core/vector/VectorT.h"
#include "GenericMatrix.h"
#include "IterativeLinearSolver.h"
#include "EigValues.h"
#include "ILSConjugateGradients.h"

namespace NICE {
  
/** @class ILSConjugateGradientsLanczos
 * Iteratively solving linear equation systems with the conjugate gradients method using Lanczos process
 *
 * @author Paul Bodesheim
 */
class ILSConjugateGradientsLanczos : public IterativeLinearSolver
{

    protected:
      bool verbose;
      uint maxIterations;
      double minDelta;
//       bool useFlexibleVersion;

//       Vector jacobiPreconditioner;

    public:

    /**
    * @brief constructor 
    *
    * @param verbose output the residual and some debug information for each iteration
    * @param maxIterations maximum number of iterations
    * @param minDelta minimum difference between two solutions x_t and x_{t+1}
    */
    ILSConjugateGradientsLanczos( bool verbose = false, uint maxIterations = 10000, double minDelta = 1e-7);//, bool useFlexibleVersion = false);
		  
    /** simple destructor */
    virtual ~ILSConjugateGradientsLanczos();

//     /**
//     * @brief set a vector of diagonal elements for the jacobi preconditioner
//     *
//     * @param jacobiPreconditioner
//     */
//     void setJacobiPreconditioner ( const Vector & jacobiPreconditioner );

    /**
    * @brief Solve the linear System A*x = b, where A is indirectly presented
    * by the GenericMatrix gm
    *
    * @param gm GenericMatrix providing matrix-vector multiplications
    * @param b Vector on the right hand side of the system
    * @param x initial and final estimate
    *
    * @return method specific status information
    */
    int solveLin ( const GenericMatrix & gm, const Vector & b, Vector & x );
};

}

#endif
