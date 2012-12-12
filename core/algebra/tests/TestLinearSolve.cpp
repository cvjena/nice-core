/**
 * @file TestLinearSolve.cpp
 * @brief TestLinearSolve
 * @author Erik Rodner
 * @date 21.12.2011
 */

#include "TestLinearSolve.h"
#include <string>
#include <vector>

#include "core/basics/cppunitex.h"
#include "core/basics/numerictools.h"
#include "core/vector/Distance.h"
#include "core/vector/Algorithms.h"

#include "core/algebra/ILSPlainGradient.h"
#include "core/algebra/ILSConjugateGradients.h"
#include "core/algebra/ILSConjugateGradientsLanczos.h"
#include "core/algebra/ILSSymmLqLanczos.h"
#include "core/algebra/ILSMinResLanczos.h"
#include "core/algebra/GMStandard.h"

#include "core/algebra/GBCDSolver.h"

using namespace std;
using namespace NICE;

CPPUNIT_TEST_SUITE_REGISTRATION(TestLinearSolve);

void TestLinearSolve::setUp()
{
}

void TestLinearSolve::tearDown()
{
}

void TestLinearSolve::TestLinearSolveComputation()
{
    // verbose flag for additional output for each iteration
    bool verbose = false;

    // size of the matrix
    uint rows = 15;
    uint cols = rows;
 
    // probability of zero entries
    double sparse_prob = 0.0;

    NICE::Matrix T(rows, cols, 0.0);

    // use a fixed seed, its a test case
    srand48(0);

    // generate random symmetric matrix
    for (uint i = 0 ; i < rows ; i++)
        for (uint j = i ; j < cols ; j++)
        {
            if (sparse_prob != 0.0)
                if (drand48() < sparse_prob)
                    continue;
            T(i, j) = drand48();
            T(j, i) = T(i, j);
        }
    // use positive definite matrices
    T = T*T;

    T.addIdentity(1.0);
    NICE::Vector b = Vector::UniformRandom( rows, 0.0, 1.0, 0 ); 

    GMStandard Tg(T);
    GMSparse Ts(T, 0.0);

    CPPUNIT_ASSERT_EQUAL((int)T.rows(),(int)Ts.rows());
    CPPUNIT_ASSERT_EQUAL((int)T.cols(),(int)Ts.cols());

    // first of all test the generic matrix interface
    for ( uint i = 0 ; i < rows ; i++ )
    {
      NICE::Vector x ( rows );
      for ( uint j = 0 ; j < x.size(); j++ )
        x[j] = drand48();
      Vector yg;
      Vector ys;
      Tg.multiply ( yg, x );
      Ts.multiply ( ys, x );
      CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(0.0,(yg-ys).normL2(),1e-10);
    }

    vector< IterativeLinearSolver * > methods;
    int max_iterations = 100;
    methods.push_back ( new ILSPlainGradient(verbose, max_iterations*10) );
    methods.push_back ( new ILSConjugateGradients(verbose, max_iterations) );
    methods.push_back ( new ILSConjugateGradientsLanczos(verbose, max_iterations) );
    methods.push_back ( new ILSSymmLqLanczos(verbose, max_iterations) );
    methods.push_back ( new ILSMinResLanczos(verbose, max_iterations) );
    // the following method is pretty instable!! and needs to much time
    //methods.push_back ( new ILSPlainGradient(verbose, max_iterations, false /* minResidual */) );
    //methods.push_back ( new ILSPlainGradient(verbose, max_iterations, true /* minResidual */) );

    //Vector solstd;
    //solveLinearEquationQR( T, b, solstd );

    for ( vector< IterativeLinearSolver * >::const_iterator i = methods.begin();
        i != methods.end(); i++ ) 
    {
      IterativeLinearSolver *method = *i;
      Vector solg (Tg.cols(), 0.0);
      Vector sols (Ts.cols(), 0.0);
      
      if ( verbose )
        cerr << "solving the sparse system ..." << endl;
      method->solveLin ( Ts, b, sols );
      if ( verbose )
        cerr << "solving the dense system ..." << endl;
      method->solveLin ( Tg, b, solg );

      Vector bg;
      Tg.multiply ( bg, solg );
      Vector bs;
      Ts.multiply ( bs, sols );
     
      // compute residuals
      if ( verbose ) 
      {
        cerr << "solg = " << solg << endl;
        cerr << "sols = " << sols << endl;
        cerr << "bg = " << bg << endl;
        cerr << "bs = " << bs << endl;
        cerr << "b = " << b << endl;
      }
      double err_dense = ( b - bg ).normL2();
      double err_sparse = ( b - bs ).normL2();
   
   
      CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(0.0,err_dense,1e-1);
      CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(0.0,err_sparse,1e-1);
    }
    
    // ---------- check the greedy block coordinate descent method
    Vector solg (0.0);
    
    GBCDSolver gbcd ( 5, 10, verbose, 100 /*maximum iterations*/ );
    gbcd.solveLin ( Tg, b, solg );

    Vector bg;
    Tg.multiply ( bg, solg );
      
    double err_dense = ( b - bg ).normL2();
    CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(0.0,err_dense,1e-4);
}
