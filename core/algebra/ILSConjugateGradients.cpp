/** 
* @file ILSConjugateGradients.cpp
* @brief abstract interface for iterative linear solvers working with GenericMatrix
* @author Erik Rodner
* @date 12/21/2011

*/
#include <iostream>

#include <core/basics/Timer.h>
#include "ILSConjugateGradients.h"

using namespace NICE;
using namespace std;


ILSConjugateGradients::ILSConjugateGradients( bool verbose, uint maxIterations, double minDelta, double minResidual, bool useFlexibleVersion )
{
  this->minDelta = minDelta;
  this->maxIterations = maxIterations;
  this->verbose = verbose;
  this->minResidual = minResidual;
  this->useFlexibleVersion = useFlexibleVersion;
  this->timeAnalysis = false;
}

ILSConjugateGradients::~ILSConjugateGradients()
{
}

void ILSConjugateGradients::setTimeAnalysis( bool timeAnalysis )
{
  this->timeAnalysis = timeAnalysis;
}

void ILSConjugateGradients::setJacobiPreconditioner ( const Vector & jacobiPreconditioner )
{
  this->jacobiPreconditioner = jacobiPreconditioner;
}
    
int ILSConjugateGradients::solveLin ( const GenericMatrix & gm, const Vector & b, Vector & x )
{
  Timer t;

  if ( timeAnalysis )
    t.start();

  if ( b.size() != gm.rows() ) {
    fthrow(Exception, "Size of vector b (" << b.size() << ") mismatches with the size of the given GenericMatrix (" << gm.rows() << ").");
  }

  if ( x.size() != gm.cols() )
  {
    x.resize(gm.cols());
    x.set(0.0); // bad initial solution, but whatever
  }


  // CG-Method: http://www.netlib.org/templates/templates.pdf
  //

  Vector a;

  // compute r^0 = b - A*x^0
  gm.multiply( a, x ); 
  Vector r = b - a;
  
  if ( timeAnalysis ) {
    t.stop();
    cerr << "r = " << r << endl;
    cerr << "ILSConjugateGradients: TIME " << t.getSum() << " " << r.normL2() << " " << r.normInf() << endl;
    t.start();
  }

  Vector rold ( r.size(), 0.0 );

  // store optimal values 
  double res_min = r.scalarProduct(r);
  Vector current_x = x;
  
  double rhoold = 0.0;
  Vector z ( r.size() );
  Vector p ( z.size() );

  uint i = 1;
  while ( i <= maxIterations )
  {
    // pre-conditioned vector, currently M=I, i.e. no pre-condition
    // otherwise set z = M * r
    if ( jacobiPreconditioner.size() != r.size() )
      z = r;
    else {
      // use simple Jacobi pre-conditioning
      for ( uint jj = 0 ; jj < z.size() ; jj++ )
        z[jj] = r[jj] / jacobiPreconditioner[jj];
    }

    double rho = z.scalarProduct( r );

    if ( verbose ) {
      cerr << "ILSConjugateGradients: iteration " << i << " / " << maxIterations << endl;
      if ( current_x.size() <= 20 )
        cerr << "ILSConjugateGradients: current solution " << current_x << endl;
    }

    if ( i == 1 ) {
      p = z;
    } else {
      double beta;
      if ( useFlexibleVersion ) {
        beta = ( rho - z.scalarProduct(rold) ) / rhoold;
      } else {
        beta = rho / rhoold;
      }
      p = z + beta * p;
    }
    Vector q ( gm.rows() );
    // q = A*p
    gm.multiply ( q, p );

    // sp = p^T A p
    // if A is next to zero this gets nasty, because we divide by sp
    // later on
    double sp = p.scalarProduct(q);
    if ( fabs(sp) < 1e-20 ) {
      // we achieved some kind of convergence, at least this
      // is a termination condition used in the wiki article
      if ( verbose )
        cerr << "ILSConjugateGradients: p^T*q is quite small" << endl;
      break;
    }
    double alpha = rho / sp;
  
    current_x = current_x + alpha * p;

    rold = r;
    r = r - alpha * q;
    
    double res = r.scalarProduct(r);
    double resMax = r.normInf();

    // store optimal x that produces smallest residual
    if (res < res_min) {
      
      x = current_x;
      res_min = res;
    }
    
    // check convergence
    double delta = fabs(alpha) * p.normL2();
    if ( verbose ) {
      cerr << "ILSConjugateGradients: delta = " << delta << " lower bound = " << minDelta << endl;
      cerr << "ILSConjugateGradients: residual = " << res << endl;
      cerr << "ILSConjugateGradients: L_inf residual = " << resMax << " lower bound = " << minResidual << endl;      
      if (resMax < 0)
      {
        std::cerr << "WARNING: resMax is smaller than zero! " << std::endl;
        std::cerr << "ILSConjugateGradients: vector r: " << r << std::endl;
      }
    }
 
    if ( timeAnalysis ) {
      t.stop();
      cerr << "ILSConjugateGradients: TIME " << t.getSum() << " " << res << " " << resMax << endl;
      t.start();
    }

   
    if ( delta < minDelta ) {
      if ( verbose )
        cerr << "ILSConjugateGradients: small delta" << endl;
      break;
    }

    //fabs was necessary, since the IPP-implementation from normInf was not working correctly
//     if ( fabs(resMax) < minResidual ) {
    if ( resMax < minResidual ) {      
      if ( verbose )
      {
        cerr << "ILSConjugateGradients: small residual -- resMax: "<< resMax << " minRes: " << minResidual << endl;
      }
      break;
    }

    rhoold = rho;
    i++;
  }
  
  if (verbose)
  {
    cerr << "ILSConjugateGradients: iterations needed: " << std::min<uint>(i,maxIterations) << endl;
    cerr << "ILSConjugateGradients: minimal residual achieved: " << res_min << endl;
  }
  if (verbose)
  {    
    if ( x.size() <= 20 )
      cerr << "ILSConjugateGradients: optimal solution: " << x << endl;
  }
  
  return 0;
}

void ILSConjugateGradients::setVerbose(const bool& _verbose)
{
  this->verbose = _verbose;
}

