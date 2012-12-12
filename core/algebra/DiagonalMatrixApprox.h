/** 
* @file DiagonalMatrixApprox.h
* @author Erik Rodner
* @date 05/31/2012

*/
#ifndef _NICE_DIAGONALMATRIXAPPROXINCLUDE
#define _NICE_DIAGONALMATRIXAPPROXINCLUDE

#include <core/vector/MatrixT.h>
#include <core/vector/VectorT.h>
#include <core/optimization/gradientBased/OptimizationProblemFirst.h>
#include <core/optimization/gradientBased/OptimizationAlgorithmFirst.h>

namespace NICE {
  
/** @class DiagonalMatrixApprox
 * find a diagonal matrix to approximate bilinear products 
 * (Method according to Chen et al., "Smooth convex approximation to the maximum eigenvalue function", 2004, J. of Global Optimization)
 *
 * @author Erik Rodner
 */
class DiagonalMatrixApprox
{

  protected:
    bool verbose;

    double epsilonStart;
    double epsilonShrinkFactor;
    double minFDelta;
    double minSolDelta;

    uint maxEpsilonIterations;


    OptimizationAlgorithmFirst *optimizer;

  public:

    /** simple constructor */
    DiagonalMatrixApprox( bool verbose = false, int maxIterations = -50 );
      
    /** simple destructor */
    virtual ~DiagonalMatrixApprox();

    /**
    * @brief Approximate a (positive-definite) matrix A with a diagonal matrix, such that bilinear products are approximated.
    * This is done by minimizing the largest eigenvalue of (A-D)
    *
    * @param A input matrix
    * @param D resulting diagonal matrix given as a vector
    */
    void approx ( const Matrix & A, Vector & D ) const;
     
};

/** corresponding optimization problem of DiagonalMatrixApprox (do not use directly) */
class DiagonalMatrixApproxOptimizationProblem : public OptimizationProblemFirst
{
  protected:
    bool verbose;
    const Matrix *A;
    double epsilon;

    /** cached eigen-decomposition */
    Matrix eigenvectors; 
    Vector eigenvalues;

  public:

    /**
    * @brief Constructor
    *
    * @param gm input generic matrix object
    */
    DiagonalMatrixApproxOptimizationProblem ( const Matrix *A, const Vector & D0, double epsilon, bool verbose = false );

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
    virtual void computeGradient( NICE::Vector& newGradient);


    /**
    * @brief get smallest eigenvalue
    * @return smallest eigenvalue
    */
    double getSmallestEigenvalue () const
    {
      return (eigenvalues.size()>0) ? eigenvalues[eigenvalues.size() - 1] : 0.0;
    }

};


}

#endif
