#ifdef NICE_USELIB_CPPUNIT

#include <string>
#include <exception>
#include <map>

#include "TestDownhillSimplex.h"

using namespace std;
using namespace OPTIMIZATION;

const bool verboseStartEnd = true;
// const bool verbose = true;
const bool verbose = false;

CPPUNIT_TEST_SUITE_REGISTRATION( TestDownhillSimplex );

void TestDownhillSimplex::setUp() {
}

void TestDownhillSimplex::tearDown() {
}

//define a simple cost function for one-dimensional or two-dimensional data
class MyCostFunction : public CostFunction
{
  public: 
  
   MyCostFunction(const int & dim) : CostFunction(dim)
   {
   }

   virtual double evaluate(const OPTIMIZATION::matrix_type & x)
   {
     double f;
     
     if (verbose)
      std::cerr << x.rows() << " x " << x.cols() << std::endl;
     if ( x.rows() == 1 )
     {
       if (verbose)
        std::cerr << "current position: " << x(0,0) << std::endl;
       
       //our cost function is f(x) = (x-5)^2
       f = pow(x(0,0) - 4.2, 2.0);
    
       if (verbose)
        std::cerr << "function value: " << f << std::endl;

     } 
     //two-dimensional data
     else {
       if (verbose)
         std::cerr << "current position: " << x(0,0) << " " << x(1,0) << std::endl;
       
       //our cost function is f(x,y) = (x-4.7)^2 + (y-1.1)^2
       f = pow(x(0,0) - 4.7, 2.0) + pow( x(1,0) - 1.1, 2.0 );
       
       if (verbose)
         std::cerr << "function value: " << f << std::endl;
     }
     return f;
   }


};

void TestDownhillSimplex::testDHS_1Dim ()
{
  
  if (verboseStartEnd)
    std::cerr << "================== TestDownhillSimplex::testDHS_1Dim ===================== " << std::endl;
  
  int dim (1);
  
  CostFunction *func = new MyCostFunction(dim); 
   
  //initial guess: 2.0
  OPTIMIZATION::matrix_type initialParams (dim, 1, 2.0);

  //we search with step-width of 1.0
  OPTIMIZATION::matrix_type scales (dim, 1, 1.0);

  //setup the OPTIMIZATION:: problem
  SimpleOptProblem optProblem ( func, initialParams, scales );
  
  DownhillSimplexOptimizer optimizer;
  //actually, this has no effect at all
  optimizer.setMaxNumIter(true, 100);
  optimizer.optimizeProb ( optProblem );  
  
  OPTIMIZATION::matrix_type optimizedParams (optProblem.getAllCurrentParams());
  
  double goal(4.2);  
  
  if (verbose)
    std::cerr << "1d OPTIMIZATION:: -- result " << optimizedParams(0,0) << " -- goal: " << goal << std::endl;

  CPPUNIT_ASSERT_DOUBLES_EQUAL( optimizedParams(0,0), goal, 1e-7 /* tolerance */);

  if (verboseStartEnd)
    std::cerr << "================== TestDownhillSimplex::testDHS_1Dim done ===================== " << std::endl;  

}

void TestDownhillSimplex::testDHS_2Dim() 
{
  
  if (verboseStartEnd)
    std::cerr << "================== TestDownhillSimplex::testDHS_2Dim ===================== " << std::endl;
  
  int dim (2);  
  
  CostFunction *func = new MyCostFunction(dim); 
   
  //initial guess: 2.0
  OPTIMIZATION::matrix_type initialParams (dim, 1, 2.0);

  //we search with step-width of 1.0
  OPTIMIZATION::matrix_type scales (dim, 1, 1.0);

  //setup the OPTIMIZATION:: problem
  SimpleOptProblem optProblem ( func, initialParams, scales );
  
  DownhillSimplexOptimizer optimizer;
  //actually, this has no effect at all
  optimizer.setMaxNumIter(true, 100);
  optimizer.optimizeProb ( optProblem );  
  
  OPTIMIZATION::matrix_type optimizedParams (optProblem.getAllCurrentParams());

  double goalFirstDim(4.7);
  double goalSecondDim(1.1);
  
  if (verbose)
  {
    std::cerr << "2d OPTIMIZATION::  1st dim-- result " << optimizedParams(0,0) << " -- goal: " << goalFirstDim << std::endl;
    std::cerr << "2d OPTIMIZATION::  1st dim-- result " << optimizedParams(1,0) << " -- goal: " << goalSecondDim << std::endl;
  }

  CPPUNIT_ASSERT_DOUBLES_EQUAL( optimizedParams(0,0), goalFirstDim, 1e-7 /* tolerance */);
  CPPUNIT_ASSERT_DOUBLES_EQUAL( optimizedParams(1,0), goalSecondDim, 1e-7 /* tolerance */);
  
  
  if (verboseStartEnd)
    std::cerr << "================== TestDownhillSimplex::testDHS_2Dim done ===================== " << std::endl;  
}

#endif