/** 
* @file ILSPlainGradient.h
* @author Erik Rodner
* @date 12/21/2011

*/
#ifndef _NICE_ILSPlainGradient_INCLUDE
#define _NICE_ILSPlainGradient_INCLUDE

#include "core/vector/VectorT.h"
#include "core/optimization/gradientBased/OptimizationProblemFirst.h"
#include "core/optimization/gradientBased/OptimizationAlgorithmFirst.h"

#include "IterativeLinearSolver.h"


namespace NICE {
  
/** @class ILSPlainGradient
 * Iterative linear solver using our own non-linear optimization techniques
 * and assuming symmetric matrices
 *
 * @author Erik Rodner
 */
class ILSPlainGradient : public IterativeLinearSolver
{

  protected:

    bool verbose;
    bool minResidual;

    OptimizationAlgorithmFirst *optimizer;

  public:

		/** simple constructor */
		ILSPlainGradient( bool verbose = false, int maxIterations = 1000, bool minResidual = true );
	
		/** simple destructor */
		virtual ~ILSPlainGradient();

    /**
    * @brief Solve the linear System A*x = b, where A is indirectly presented
    * by the GenericMatrix gm and A is symmetric
    *
    * @param gm GenericMatrix providing matrix-vector multiplications (symmetry required!)
    * @param b Vector on the right hand side of the system
    * @param x solution
    *
    * @return method specific status information
    */
    virtual int solveLin ( const GenericMatrix & gm, const Vector & b, Vector & x );
     
};

/**
* @brief This class implements a quadratic optimization problem, trying to minimize $0.5 * \| A x - b \|^2$ (minimum residual)
*        or $0.5 * x^T A x - b^T x$ for symmetric A but without any additional constraints.
*/
class ILSPlainGradientOptimizationProblem : public OptimizationProblemFirst
{
  protected:
    const GenericMatrix *m_gm;
    Vector m_b;

    bool minResidual;

  public:

    /**
    * @brief Constructor
    *
    * @param gm input generic matrix object
    */
    ILSPlainGradientOptimizationProblem( const GenericMatrix *gm, const Vector & b, const Vector & x0, bool minResidual = true );

    /**
    * @brief Compute the objective
    *
    * @return 
    */
    virtual double computeObjective();

    /**
    * @brief Compute the gradient of the problem
    *
    * @param newGradient output gradient vector
    */
    virtual void computeGradient(Vector& newGradient);

};

}

#endif
