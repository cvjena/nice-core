/** 
* @file GBCDSolver.h
* @author Erik Rodner
* @date 01/26/2012

*/
#ifndef _NICE_GBCDSOLVERINCLUDE
#define _NICE_GBCDSOLVERINCLUDE

#include "PartialGenericMatrix.h"

namespace NICE {
  
/** @class GBCDSolver
 * Greedy Block Coordinate Descent Algorithm 
 *
 * Details are included in the paper:
 * "Greedy Block Coordinate Descent for Large Scale Gaussian Process Regression"
 * by Liefeng Bo and Cristian Sminchisescu, 2008
 *
 * Their code can be found at: http://www.cs.washington.edu/homes/lfb/software/GBCD.htm
 * We re-implemented their approach using the description of the algorithm in the paper.
 *
 * @author Erik Rodner
 */
class GBCDSolver
{

  protected:
    bool verbose;

    uint maxIterations;

    //! known as kappa in the paper
    uint randomSetSize;

    //! known as M in the paper
    uint stepComponents;

    double minDelta;

    //! detailed time analysis
    bool timeAnalysis;

    void greedyApproximation ( const PartialGenericMatrix & gm, const Vector & b, const Vector & grad,
                               PartialGenericMatrix::SetType & B, Vector & deltaAlpha );

  public:

    /** simple constructor */
    GBCDSolver( uint randomSetSize = 60, uint stepComponents = 500, bool verbose = false, uint maxIterations = 10000, double minDelta = 1e-7 );
      
    /** simple destructor */
    virtual ~GBCDSolver();
    
    /**
    * @brief Solve a linear system given a PartialGenericMatrix interface
    *
    * @param gm PartialGenericMatrix interface providing sub-matrix multiplications
    * @param b right hand side of the system
    * @param x initial and final estimate
    *
    * @return method specific status information
    */
    virtual int solveLin ( const PartialGenericMatrix & gm, const Vector & b, Vector & x );

    
    /**
    * @brief set time analysis flag, this needs additional time and is only
    * important if you want to generate some time plots
    *
    * @param timeAnalysis
    */
    void setTimeAnalysis(bool timeAnalysis);
     
};

}

#endif
