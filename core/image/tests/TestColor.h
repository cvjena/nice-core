/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libimage - An image/template for new NICE libraries
 * See file License for license information.
 */
#ifndef _TESTDRAWABLE_IMAGE_H
#define _TESTDRAWABLE_IMAGE_H

#include <cppunit/extensions/HelperMacros.h>

/**
 * CppUnit-Testcase. 
 * Test template...
 */
class TestColor : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE( TestColor );
  CPPUNIT_TEST( testColorT );
  CPPUNIT_TEST_SUITE_END();
  
 private:
 
 public:
  void setUp();
  void tearDown();

  /**
   * Test ColorT
   */  
  void testColorT();
};

#endif // _TESTDRAWABLE_IMAGE_H
