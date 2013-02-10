/** 
* @file DiagonalMatrixApprox.cpp
* @brief find a diagonal matrix to approximate bilinear products
* @author Erik Rodner
* @date 05/31/2012

*/
#include <iostream>

#include <core/optimization/gradientBased/FirstOrderRasmussen.h>
#include <core/vector/Eigen.h>

#include "DiagonalMatrixApprox.h"

#include "core/basics/numerictools.h"

using namespace NICE;
using namespace std;


DiagonalMatrixApprox::DiagonalMatrixApprox( bool verbose, int maxIterations )
{
  this->epsilonStart = 1.0;
  this->epsilonShrinkFactor = 0.8;
  this->minFDelta = 1e-8;
  this->minSolDelta = 1e-8;

  this->maxEpsilonIterations = 100;

  this->verbose = verbose;
  this->optimizer = new FirstOrderRasmussen( /*false*/ this->verbose );
  ( dynamic_cast< FirstOrderRasmussen * > (optimizer) )->setMaxIterations(maxIterations);

}

DiagonalMatrixApprox::~DiagonalMatrixApprox()
{
}

void DiagonalMatrixApprox::approx ( const Matrix & A, Vector & D ) const
{
  double f0 = std::numeric_limits<double>::max();

  // not so proper intialization with the diagonal matrix
  /*
  D.resize(A.rows());
  for ( uint i = 0; i < D.size(); i++ )
    D[i] = A(i,i);
  */

  Vector D0 ( D );

  double epsilon = epsilonStart;
  for ( uint i = 0; i < maxEpsilonIterations; i++ )
  {
    epsilon = epsilonShrinkFactor * epsilon;

    // perform minimization with some gradient based method (this is a convex optimization problem)
    DiagonalMatrixApproxOptimizationProblem opt ( &A, D0, epsilon, false /*verbose*/ );

    optimizer->optimizeFirst ( opt );

    D = opt.position();
    double f = opt.computeObjective ();

    if ( verbose )
    {
      cerr << "DiagonalMatrixApprox [" << i << " / " << maxEpsilonIterations << "]: " << f << " (epsilon=" << epsilon << ")" << endl;
      cerr << D << endl;
    }

	if ( !NICE::isFinite(f) )
    {
      f = f0;
      D = D0;
      if ( verbose )
        cerr << "DiagonalMatrixApprox ended in iteration " << i << " due to numerical problems when decreasing epsilon..." << endl;
      return;
    } 

    double eig_small = opt.getSmallestEigenvalue();
    if ( eig_small < 0.0 )
    {
      if ( verbose )
        cerr << "DiagonalMatrixApprox: resetting current value due to negative eigenvalue: " << eig_small << endl;
      D = f0;
      D = D0;
    } else {
      // otherwise check for convergence
      double solDelta = ( D - D0 ).normInf();
      double fDelta = f0 - f; // this value should be positive, otherwise convergence is likely

      if ( fDelta < minFDelta || solDelta < minSolDelta ) 
      {
        if ( verbose )
          cerr << "DiagonalMatrixApprox: convergence detected delta_f=" << fDelta << " x_delta=" << solDelta << endl;
        return;
      }
    }
      


    f0 = f;
    D0 = D;
  }

}
    
DiagonalMatrixApproxOptimizationProblem::DiagonalMatrixApproxOptimizationProblem ( const Matrix *A, const Vector & D0, double epsilon, bool verbose ) 
  : OptimizationProblemFirst( D0.size() )
{
  this->A = A;
  this->parameters() = D0;
  this->epsilon = epsilon;
  this->verbose = verbose;
}


double DiagonalMatrixApproxOptimizationProblem::computeObjective()
{
  // Theoretically, we have to compute lambda_max(A - diag(D)). However, we want to solve
  // the regularized and relaxed optimization problem, which involves all eigenvalues
  
  const Vector & D = parameters();
  Matrix M = (*A);
  M.addDiagonal ( (-1.0) * D );

  if ( verbose ) {
    cerr << "M = " << M << endl;
    cerr << "D = " << D << endl;
    cerr << "A = " << *A << endl;
  }

  //if ( verbose )
  //  cerr << "Computing the eigenvalue decomposition ..." << endl;
  
  try {
    eigenvectorvalues  ( M, eigenvectors, eigenvalues );
  } catch ( ... ) {
    // the matrix seems to be singular, maybe this is a good sign.
    // Does not have to be: only the smallest eigenvalue can be zero
    return 0.0;
  }

  //if ( verbose )
  //  cerr << "Computing the objective ..." << endl;
  double sumExp = 0.0;
  for ( uint i = 0 ; i < eigenvalues.size(); i++ )
    sumExp += exp( eigenvalues[i] / epsilon );

  double fval = epsilon * log( sumExp ) + 0.5 * D.scalarProduct(D); 

  //if ( verbose ) {
    cerr << "DiagonalMatrixApprox: maximum eigenvalue is " << eigenvalues.Max() << endl;
  //}

  if ( !NICE::isFinite(fval) )
  {
    // some numerical problems occured
    fval = numeric_limits<double>::infinity();
  }

  //if ( verbose )
  //  cerr << "Objective value of the sub-problem is: " << fval << endl;

  return fval;
}

void DiagonalMatrixApproxOptimizationProblem::computeGradient(Vector& newGradient)
{
  // inefficient but straightforward implementation with matrices P (denoted as A in the MATLAB code)
  const Vector & D = parameters();
  uint n = D.size();

  Matrix P ( n, n, 0.0 );
  Matrix W ( n, n, 0.0 );

  if ( verbose ) {
    cerr << "Eigenvectors are: " << eigenvectors << endl;
    cerr << "Eigenvalues are: " << eigenvalues << endl;
  }

  for ( uint i = 0 ; i < n ; i++ )
  {
    P(i,i) = 1.0;
    Matrix Ptilde = eigenvectors.transpose() * P * eigenvectors;
    for ( uint j = 0 ; j < n ; j++ )
      W(j,i) = Ptilde(j,j);
    P(i,i) = 0.0;
  }

  double eigmax = eigenvalues.Max();

  Vector mu (n);
  for ( uint i = 0 ; i < n ; i++ )
    mu[i] = exp( (eigenvalues[i] - eigmax)/epsilon );
  
  mu.normalizeL1();
  if ( verbose ) {
    cerr << "W = " << W << endl;
    cerr << "mu = " << mu << endl; 
  }

  newGradient = - 1.0 * W.transpose() * mu + D;

  if ( verbose ) {
    cerr << "gradient = " << newGradient << endl;
  }
}
