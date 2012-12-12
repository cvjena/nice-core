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
class TestDrawable : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE( TestDrawable );
  CPPUNIT_TEST( testSomething );

  CPPUNIT_TEST( testCrossT );
  CPPUNIT_TEST( testCircleT );
  CPPUNIT_TEST( testEllipseT );
  CPPUNIT_TEST( testLineT );
  CPPUNIT_TEST( testPointT );

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

  /**
   * Test something...
   */  
  void testSomething();

  /**
   * Test CrossT
  */
  void testCrossT();

  /**
   * Test CircleT
  */
  void testCircleT();

  /**
   * Test EllipseT
  */
  void testEllipseT();

  /**
   * Test LineT
  */
  void testLineT();

  /**
   * Test CircleT
  */
  void testPointT();
};

#endif // _TESTDRAWABLE_IMAGE_H
