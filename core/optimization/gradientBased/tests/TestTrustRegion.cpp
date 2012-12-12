/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - liboptimization - An optimization/template for new NICE libraries
 * See file License for license information.
 */

#ifdef NICE_USELIB_CPPUNIT
#include "TestTrustRegion.h"
#include <string>
#include <exception>
#include <core/basics/cppunitex.h>
#include <core/optimization/gradientBased/FirstOrderTrustRegion.h>
#include <core/optimization/gradientBased/FirstOrderRasmussen.h>
#include <core/optimization/gradientBased/SecondOrderTrustRegion.h>

using namespace NICE;

CPPUNIT_TEST_SUITE_REGISTRATION( TestTrustRegion );

void TestTrustRegion::setUp() {
}

void TestTrustRegion::tearDown() {
}

/** a simple quadratic optimization problem */
class MyProblem : public OptimizationProblemFirst {
public:
  inline MyProblem() : OptimizationProblemFirst(2) {
    parameters()[0] = 1.0;
  }

protected:
  virtual void computeGradient(Vector& newGradient);
  virtual double computeObjective();
};

double MyProblem::computeObjective() {
  return 0.7 * square(parameters()[0] + 0.6)
         + 0.4 * square(parameters()[1] - 0.3);
}
    
void MyProblem::computeGradient(Vector& newGradient) {
  newGradient[0] = 1.4 * (parameters()[0] + 0.6);
  newGradient[1] = 0.8 * (parameters()[1] - 0.3);
}

/** a simple quadratic optimization problem with hessian */
class MyProblem2 : public OptimizationProblemSecond {
public:
  inline MyProblem2() : OptimizationProblemSecond(2) {
    parameters()[0] = 1.0;
    parameters()[1] = 1.0;
  }

protected:
  virtual void computeGradientAndHessian(Vector& newGradient,
                                         Matrix& newHessian);
  virtual double computeObjective();
};

double MyProblem2::computeObjective() {
  return 0.7 * square(parameters()[0] + 0.6)
         + 0.4 * square(parameters()[1] - 0.3);
}
    
void MyProblem2::computeGradientAndHessian(Vector& newGradient,
                                           Matrix& newHessian) {
  newGradient[0] = 1.4 * (parameters()[0] + 0.6);
  newGradient[1] = 0.8 * (parameters()[1] - 0.3);
  newHessian(0,0) = 1.4;
  newHessian(0,1) = 0.0;
  newHessian(1,0) = 0.0;
  newHessian(1,1) = 0.8;
}

/** a large scale optimization problem */
class MyProblem3 : public OptimizationProblemFirst
{
    public:
        MyProblem3 (uint n) : OptimizationProblemFirst(n) {}
        double computeObjective()
        {
            double sum = 0.0;
            for ( uint i = 0 ; i < parameters().size() ; i++ )
                sum += pow(parameters()[i] - 1,2);
            for ( uint i = 1; i < parameters().size(); i++ )
                sum -= parameters()[i] * parameters()[i-1];
            return sum;
        }

        void computeGradient ( NICE::Vector &newGradient )
        {
            newGradient.resize(parameters().size());
            for ( uint i = 0 ; i < parameters().size() ; i++ )
            {
                newGradient[i] = 2*(parameters()[i]-1);
                if ( i > 0 )
                    newGradient[i] -= parameters()[i-1];
                if ( i < parameters().size()-1 )
                    newGradient[i] -= parameters()[i+1];
            }
        }

		Vector groundtruth () {
			Vector gt ( parameters().size() );
			for ( uint i = 0 ; i < gt.size() ; i++ )
		         gt[i] = (i+1)*(gt.size()-i);
			return gt;
		}
};


void TestTrustRegion::testOptimization1() {
  {
    MyProblem problem;
    FirstOrderTrustRegion optimizer;
    optimizer.setEpsilonG(1E-4);
    optimizer.optimizeFirst(problem);
    CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(0.0, problem.objective(), 1E-8);
    CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(-0.6, problem.position()[0], 2E-5);
    CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(0.3, problem.position()[1], 5E-5);
  }

  {
    MyProblem2 problem2;
    FirstOrderTrustRegion optimizer;
    optimizer.setEpsilonG(1E-4);
    optimizer.optimizeFirst(problem2);
    CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(0.0, problem2.objective(), 1E-8);
    CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(-0.6, problem2.position()[0], 5E-5);
    CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(0.3, problem2.position()[1], 2E-6);
  }
}

void TestTrustRegion::testOptimization1Ras () {
  {
    MyProblem problem;
    FirstOrderRasmussen optimizer ( false /*verbose*/ );
    optimizer.setEpsilonG(1E-4);
    optimizer.optimizeFirst(problem);
    CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(0.0, problem.objective(), 1E-8);
    CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(-0.6, problem.position()[0], 2E-5);
    CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(0.3, problem.position()[1], 5E-5);
  }

  {
    MyProblem2 problem2;
    FirstOrderRasmussen optimizer (false);
    optimizer.setEpsilonG(1E-4);
    optimizer.optimizeFirst(problem2);
    CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(0.0, problem2.objective(), 1E-8);
    CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(-0.6, problem2.position()[0], 5E-5);
    CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(0.3, problem2.position()[1], 2E-6);
  }

  {
	uint size = 100;
    MyProblem3 problem3 (size);
    FirstOrderRasmussen optimizer (false);
    optimizer.setEpsilonG(1E-9);
    optimizer.setMaxIterations ( -1000 );
    optimizer.optimizeFirst(problem3);
    CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(0.0, (problem3.position() - problem3.groundtruth()).normL2() / size, 4E-3);
  }

}

void TestTrustRegion::testOptimization2() {
  MyProblem2 problem2;
  SecondOrderTrustRegion optimizer;
  optimizer.setEpsilonG(1E-4);
  optimizer.optimize(problem2);
  CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(0.0, problem2.objective(), 1E-30);
  CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(-0.6, problem2.position()[0], 1E-14);
  CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(0.3, problem2.position()[1], 1E-16);
}

#endif
