/** 
* @file ILSPlainGradient.cpp
* @brief abstract interface for iterative linear solvers working with GenericMatrix
* @author Erik Rodner
* @date 12/21/2011

*/
#include <iostream>

#include "core/optimization/gradientBased/FirstOrderRasmussen.h"
#include "core/optimization/gradientBased/FirstOrderTrustRegion.h"
#include "ILSPlainGradient.h"

using namespace NICE;
using namespace std;



ILSPlainGradient::ILSPlainGradient(bool verbose, int maxIterations, bool minResidual)
{
  this->verbose = verbose;
  optimizer = new FirstOrderRasmussen(this->verbose);
  ( dynamic_cast< FirstOrderRasmussen * > (optimizer) )->setMaxIterations(maxIterations);
  
  // another optimization method
  //optimizer = new FirstOrderTrustRegion(0.1, false);
  //( dynamic_cast< FirstOrderTrustRegion * > (optimizer) )->setMaxIterations(maxIterations);
  
  this->minResidual = minResidual;
}

ILSPlainGradient::~ILSPlainGradient()
{
  delete optimizer;
}


int ILSPlainGradient::solveLin ( const GenericMatrix & gm, const Vector & b, Vector & x )
{
  if ( b.size() != gm.rows() ) {
    fthrow(Exception, "Size of vector b mismatches with the size of the given GenericMatrix.");
  }

  if ( x.size() != gm.cols() )
  {
    x.resize(gm.cols());
    x.set(0.0); // bad initial solution, but whatever
  }

  // use x as an initial solution
  ILSPlainGradientOptimizationProblem op ( &gm, b, x, this->minResidual );

  optimizer->optimizeFirst(op);

  x = op.position();
  return 0;
}
    
ILSPlainGradientOptimizationProblem::ILSPlainGradientOptimizationProblem( const GenericMatrix *gm, const Vector & b, const Vector & x0, bool minResidual ) : OptimizationProblemFirst(gm->cols())
{
  this->m_gm = gm;
  this->m_b = b;
  this->parameters() = x0;
  this->minResidual = minResidual;
}

double ILSPlainGradientOptimizationProblem::computeObjective()
{
  // we need to compute A*x
  Vector v_Ax;
  m_gm->multiply ( v_Ax, position() );

  if ( minResidual ) 
  {
    // we need to compute A*x-b
    Vector diff ( v_Ax - m_b );

    // ... and the quadratic norm
    return 0.5 * diff.scalarProduct(diff);
  } else {
    // x^T A x - b^T x = (A x - b)^T x (A is symmetric!)
    return (0.5 * v_Ax - m_b).scalarProduct ( position() );
  }
}

void ILSPlainGradientOptimizationProblem::computeGradient(Vector& newGradient)
{
  // the gradient is A*(A*x - b) (note that we exploited the symmetry of A)
  Vector v_Ax;

  // we need to compute A*x
  m_gm->multiply ( v_Ax, position() );

  // we need to compute A*x-b
  Vector diff ( v_Ax - m_b );

  newGradient.resize ( m_gm->cols() );
  if ( minResidual ) 
  {
    // computing A*(Ax - b)
    m_gm->multiply ( newGradient, diff );
  } else {
    newGradient = diff;
  }
}


