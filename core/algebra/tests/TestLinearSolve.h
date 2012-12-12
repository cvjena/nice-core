/** 
 * @file TestLinearSolve.h
 * @brief TestLinearSolve
 * @author Erik Rodner
 * @date 21.12.2011
 */
 

#ifndef OBJREC_TestLinearSolve_H
#define OBJREC_TestLinearSolve_H


#include <cppunit/extensions/HelperMacros.h>

/**
 * CppUnit-Testcase. 
 * Tests for Iterative Linear Solvers
 */
class TestLinearSolve : public CppUnit::TestFixture
{
     CPPUNIT_TEST_SUITE( TestLinearSolve );

    
     CPPUNIT_TEST( TestLinearSolveComputation );

     CPPUNIT_TEST_SUITE_END();

     private:

     public:
          void setUp();
          void tearDown();
          void TestLinearSolveComputation();
       
};

#endif // _TestLinearSolve_H_

