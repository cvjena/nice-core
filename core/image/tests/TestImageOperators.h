/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libimage - An image/template for new NICE libraries
 * See file License for license information.
 */
#ifndef _TESTCONVERTER_IMAGE_H
#define _TESTCONVERTER_IMAGE_H

#include <cppunit/extensions/HelperMacros.h>
#include <core/image/ImageOperators.h>
#include <core/image/Convert.h>

/**
 * CppUnit-Testcase. 
 * Test template...
 */
class TestImageOperators : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE( TestImageOperators );
  CPPUNIT_TEST( testOperators );
  CPPUNIT_TEST_SUITE_END();
  
 private:
 
 public:
  void setUp();
  void tearDown();

  /**
   * Constructor / Destructor testing 
   */  
  void testConstructor();

  /**
   * Operator testing 
   */  
  void testOperators();

  
};

#endif // _TESTCONVERTER_IMAGE_H
