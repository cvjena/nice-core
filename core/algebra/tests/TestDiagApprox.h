/** 
 * @file TestDiagApprox.h
 * @brief TestDiagApprox
 * @author Michael Koch
 * @date Di Aug 4 2009
 */
 

#ifndef OBJREC_TestDiagApprox_H
#define OBJREC_TestDiagApprox_H


#include <cppunit/extensions/HelperMacros.h>

/**
 * CppUnit-Testcase. 
 * Tests for EigenValue Operations
 */
class TestDiagApprox : public CppUnit::TestFixture
{
     CPPUNIT_TEST_SUITE( TestDiagApprox );

    
     CPPUNIT_TEST( TestDiagApproxComputation );

     CPPUNIT_TEST_SUITE_END();

     private:

     public:
          void setUp();
          void tearDown();
          void TestDiagApproxComputation();
       
};

#endif // _TestDiagApprox_H_

