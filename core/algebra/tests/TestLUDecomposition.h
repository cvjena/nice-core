/** 
 * @file TestLUDecomposition.h
 * @brief TestLUDecomposition 
 * @author Alexander Freytag
 * @date 22-10-2012
 */
 

#ifndef NICE_TESTLINEARSOLVE
#define NICE_TESTLINEARSOLVE


#include <cppunit/extensions/HelperMacros.h>

/**
 * CppUnit-Testcase. 
 * Tests for LU Decomposition
 */
class TestLUDecomposition : public CppUnit::TestFixture
{
     CPPUNIT_TEST_SUITE( TestLUDecomposition );

    
     CPPUNIT_TEST( testLUDecomposition );

     CPPUNIT_TEST_SUITE_END();

     private:

     public:
          void setUp();
          void tearDown();
          void testLUDecomposition();
       
};

#endif // NICE_TESTLINEARSOLVE