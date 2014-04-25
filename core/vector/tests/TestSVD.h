/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libbasicvector - An core/vector/template for new NICE libraries
 * See file License for license information.
 */
#ifndef _TESTSVD_H
#define _TESTSVD_H

#include <cppunit/extensions/HelperMacros.h>
/**
 * CppUnit-Testcase. 
 * Test template...
 */
class TestSVD : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE( TestSVD );
  CPPUNIT_TEST( testSVD );
  CPPUNIT_TEST_SUITE_END();
  
 private:
 
 public:
  void setUp();
  void tearDown();

  void testSVD();
};

#endif // _TESTSVD_H
