/** 
* @file GBCDSolver.cpp
* @brief Greedy Block Coordinate Descent Algorithm
* @author Erik Rodner
* @date 01/26/2012

*/
#include <iostream>

#include <core/basics/Timer.h>
#include "GBCDSolver.h"

using namespace NICE;
using namespace std;


GBCDSolver::GBCDSolver( uint randomSetSize, uint stepComponents, bool verbose, uint maxIterations, double minDelta )
{
  this->verbose = verbose;
  this->maxIterations = maxIterations;
  this->minDelta = minDelta;
  this->stepComponents = stepComponents;
  this->randomSetSize = randomSetSize;
  this->timeAnalysis = false;
}

void GBCDSolver::setTimeAnalysis(bool timeAnalysis)
{
  this->timeAnalysis = timeAnalysis;
}

GBCDSolver::~GBCDSolver()
{
}

void GBCDSolver::greedyApproximation ( const PartialGenericMatrix & gm, const Vector & b, const Vector & grad,
                                       PartialGenericMatrix::SetType & B, Vector & deltaAlpha )
{
  uint t = 0;
  uint n = b.size();
  Vector e ( grad );

  // start with an empty set
  B.clear();

  //if ( verbose )
  //  cerr << "GBCDSolver::greedyApproximation: size of the problem is " << n << endl;

  PartialGenericMatrix::SetType O;
  uint elementsN = n;
  bool *N = new bool [ n ];
  for ( uint i = 0 ; i < n ; i++ )
  {
    O.push_back(i);
    N[i] = true; //N.insert(i);
  }

  Matrix R ( stepComponents, stepComponents, 0.0 );
  deltaAlpha.resize ( stepComponents );
  do {
    // step (3) of Algorithm 2 in the paper
    // determine the index s
    int s = *(O.begin());
    double min_expr = numeric_limits<double>::max();
    for ( PartialGenericMatrix::SetType::const_iterator i = O.begin(); i != O.end(); i++ )
    {
      double evalue = e(*i);
      double expr = - evalue*evalue / ( 2 * gm.getDiagonalElement(*i) );
      if ( expr < min_expr )
      {
        min_expr = expr;
        s = *i;
      }
    }
    //if ( verbose )
    //  cerr << "GBCDSolver: greedy selection of element " << s << endl;

    Vector deltaAlphaTmp ( t + 1 );
    // step (4) of Algorithm 2 in the paper
    if ( t == 0 ) {
      R(0,0) = 1 / ( gm.getDiagonalElement(s) );
      deltaAlpha[0] = - e(s) / ( gm.getDiagonalElement(s) );
      deltaAlphaTmp[0] = deltaAlpha[0];
    } else {
      Vector beta ( t );
      Vector rvector ( t );
      Vector tmpScalar ( 1 );
      PartialGenericMatrix::SetType sset;
      sset.push_back(s);
      // ---- calculation of beta
      // beta = R * A(B,s)
      // beta^T = A(s,B) * R^T
      // beta^T = A(B,s) * R^T (because we assume symmetry)
 
      for ( uint i = 0 ; i < beta.size() ; i++ )
      {
        for ( uint j = 0 ; j < rvector.size(); j++ )
          rvector[j] = R( i , j );

        gm.multiply ( sset, B, tmpScalar, rvector );
        beta[i] = tmpScalar[0];
      }

      // ---- calculation of nu
      gm.multiply ( sset, B, tmpScalar, beta );
      double nu = 1.0 / ( gm.getDiagonalElement ( s ) - tmpScalar[0] );

      // ---- update our R
      for ( uint i = 0 ; i < t ; i++ ) {
        for ( uint j = 0 ; j < t ; j++ ) {
          R(i,j) += nu * beta(i) * beta(j);
        }
        R(i,t) = nu * beta(i) * (-1);
        R(t,i) = nu * beta(i) * (-1);
      }
      R(t, t) = nu;

      // ---- compute our deltaAlpha update
      Vector gradSub ( t+1 );
      uint ii = 0;
      for ( PartialGenericMatrix::SetType::const_iterator i = B.begin(); i != B.end(); i++,ii++ )
        gradSub[ii] = grad[*i];
      gradSub[t] = grad[s];

      // this statement uses a copy of the R sub-matrix, which
      // might be not beneficial for performance!!!
      deltaAlphaTmp = (-1.0) * R(0,0,t,t) * gradSub;
      for ( uint i = 0 ; i < t+1; i++ )
        deltaAlpha[i] = deltaAlphaTmp[i];
    } 

    // step 5 of algorithm 2
    B.push_back(s);
    // N.erase ( s );
    N[s] = false;
    elementsN--;

    if ( elementsN == 0 ) {
      cerr << "Unable to select more elements! Adjust your parameters!" << endl;
      break;
    }

    // step 6 of algorithm 2
    // choose a subset O of size kappa = randomSetSize
    O.clear();
    set<int> selectedElements;
    for ( uint i = 0 ; i < randomSetSize ; i++ )
    {
      int selectedElement;
      
      do {
        selectedElement = rand() % n;
      } while ( // I have selected this element as the optimal element in a previous step
                !N[selectedElement] || 
                // I selected this element already for the set O
                (selectedElements.find(selectedElement) != selectedElements.end()) );

      //if ( verbose )
      //  cerr << "GBCDSolver: selecting " << selectedElement << " for the set O" << endl;
      selectedElements.insert( selectedElement );

      O.push_back ( selectedElement );
    }

    Vector eSub;
    gm.multiply ( O, B, eSub, deltaAlphaTmp );
    if ( eSub.size() != O.size() )
      fthrow(Exception, "The matrix interface did not return a vector of a proper size!");

    uint ii = 0;
    for ( PartialGenericMatrix::SetType::const_iterator i = O.begin(); i != O.end(); i++,ii++ )
      e[ *i ] = eSub[ ii ] + grad[ *i ];

    // increment our iteration counter
    t++;

  } while ( t < this->stepComponents );

  delete [] N;
}

int GBCDSolver::solveLin ( const PartialGenericMatrix & gm, const Vector & b, Vector & x )
{
  // FIXME: check for quadratic matrix

  uint iteration = 0;

  Vector grad;
  Vector Ax;

  if ( x.size() != gm.cols() ) {
    // use a simple initial solution, x = 0
    x.resize( gm.cols() );
    x.set(0.0);
    grad = (-1.0) * b;
  } else {
    gm.multiply ( Ax, x );
    grad = Ax - b;
  }

  PartialGenericMatrix::SetType wholeSet;
  for ( uint i = 0 ; i < b.size() ; i++ )
    wholeSet.push_back(i);

  Timer t;

  if ( timeAnalysis )
    t.start();

  // start with our iterations
  do {

    // Although the objective of the corresponding quadratic program decreases,
    // this is not necessarily true for the residual. We know that at the bottom we get a zero
    // gradient (and a residual) but we can not prove anything about the development of it during
    // optimization. 
    double residualNorm = grad.normInf();
    if ( verbose )
      cerr << "GBCDSolver: [ " << iteration << " / " << maxIterations << " ] " << residualNorm << endl;

    Vector deltaAlpha;
    PartialGenericMatrix::SetType B;

    // -------- the main part: solve the sub-problem of finding a good search direction 
    greedyApproximation ( gm, b, grad, B, deltaAlpha );

    // --------
    if ( verbose && b.size() <= 10 )
      cerr << "GBCDSolver: " << deltaAlpha << endl;

    uint ii = 0;
    for ( PartialGenericMatrix::SetType::const_iterator i = B.begin(); i != B.end(); i++, ii++)
    {
      // update our current estimate, but only at certain positions
      x[ *i ] += deltaAlpha[ ii ];
    }


    double deltaNorm = deltaAlpha.normL2();
    if ( verbose )
      cerr << "GBCDSolver: delta = " << deltaNorm << endl;

    if ( deltaNorm < minDelta ) {
      if ( verbose )
        cerr << "GBCDSolver: minimum delta reached" << endl;
      return iteration;
    }

    Vector A_deltaAlpha;
    gm.multiply ( wholeSet, B, A_deltaAlpha, deltaAlpha );

    grad += A_deltaAlpha;
 
    if ( timeAnalysis ) 
    {
      t.stop();
      cerr << "GBCDSolver: TIME " << t.getSum() << " " << grad.normL2() << " " << grad.normInf() << endl;
      t.start();
    }
   
    iteration++; 
  } while ( iteration < maxIterations );

  return iteration;
}
