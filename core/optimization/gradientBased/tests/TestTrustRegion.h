/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - liboptimization - An optimization/template for new NICE libraries
 * See file License for license information.
 */
#ifndef _TESTTRUSTREGION_OPTIMIZATION_H
#define _TESTTRUSTREGION_OPTIMIZATION_H

#include <cppunit/extensions/HelperMacros.h>

/**
 * CppUnit-Testcase. 
 * Test template...
 */
class TestTrustRegion : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE( TestTrustRegion );
  CPPUNIT_TEST( testOptimization1 );
  CPPUNIT_TEST( testOptimization1Ras );
  CPPUNIT_TEST( testOptimization2 );
  CPPUNIT_TEST_SUITE_END();
  
 private:
 
 public:
  void setUp();
  void tearDown();

  /**
   * Test optimization...
   */  
  void testOptimization1();
  void testOptimization1Ras();
  void testOptimization2();
};

#endif // _TESTTRUSTREGION_OPTIMIZATION_H
