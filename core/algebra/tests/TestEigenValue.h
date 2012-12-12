/** 
 * @file TestEigenValue.h
 * @brief TestEigenValue
 * @author Michael Koch
 * @date Di Aug 4 2009
 */
 

#ifndef OBJREC_TestEigenValue_H
#define OBJREC_TestEigenValue_H


#include <cppunit/extensions/HelperMacros.h>

/**
 * CppUnit-Testcase. 
 * Tests for EigenValue Operations
 */
class TestEigenValue : public CppUnit::TestFixture
{
     CPPUNIT_TEST_SUITE( TestEigenValue );

    
     CPPUNIT_TEST( TestEigenValueComputation );

     CPPUNIT_TEST_SUITE_END();

     private:

     public:
          void setUp();
          void tearDown();
          void TestEigenValueComputation();
       
};

#endif // _TestEigenValue_H_

