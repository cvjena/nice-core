/** 
* @file ILSConjugateGradients.h
* @author Erik Rodner
* @date 12/21/2011

*/
#ifndef _NICE_ILSConjugateGradients_INCLUDE
#define _NICE_ILSConjugateGradients_INCLUDE

#include "core/vector/VectorT.h"
#include "GenericMatrix.h"
#include "IterativeLinearSolver.h"

namespace NICE {
  
/** @class ILSConjugateGradients
 * Iteratively solving linear equation systems with the conjugate gradients method 
 *
 * @author Erik Rodner
 */
class ILSConjugateGradients : public IterativeLinearSolver
{

    protected:
      bool verbose;
      uint maxIterations;
      double minDelta;
      double minResidual;
      bool useFlexibleVersion;
      bool timeAnalysis;

      Vector jacobiPreconditioner;

    public:

    /**
    * @brief constructor 
    *
    * @param verbose output the residual and some debug information for each iteration
    * @param maxIterations maximum number of iterations
    * @param minDelta minimum difference between two solutions x_t and x_{t+1}
    * @param useFlexibleVersion use the Polak-Ribiere formula instead of the Fletcher–Reeves formula (we did not see any benefit from it)
    */
    ILSConjugateGradients( bool verbose = false, uint maxIterations = 10000, double minDelta = 1e-7, double minResidual = 1e-20, bool useFlexibleVersion = false);
		  
		/** simple destructor */
		virtual ~ILSConjugateGradients();

    /**
    * @brief set a vector of diagonal elements for the jacobi preconditioner
    *
    * @param jacobiPreconditioner
    */
    void setJacobiPreconditioner ( const Vector & jacobiPreconditioner );

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


    /**
    * @brief switch to detailed time analysis
    *
    * @param timeAnalysis
    */
    void setTimeAnalysis( bool timeAnalysis = true );

    /**
    * @brief Enable or disable output
    *
    * @param _verbose
    */    
    void setVerbose( const bool & _verbose );
};

}

#endif
