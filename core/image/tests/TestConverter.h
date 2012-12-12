/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libimage - An image/template for new NICE libraries
 * See file License for license information.
 */
#ifndef _TESTCONVERTER_IMAGE_H
#define _TESTCONVERTER_IMAGE_H

#include <cppunit/extensions/HelperMacros.h>
#include <core/image/DeprecatedConverter.h>
#include <core/image/ImageOperators.h>

/**
 * CppUnit-Testcase. 
 * Test template...
 */
class TestConverter : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE( TestConverter );
  CPPUNIT_TEST( testGrayFilter );
  CPPUNIT_TEST( testFloatFilter );
  CPPUNIT_TEST( testConvolution );
  CPPUNIT_TEST( testSomething );
  CPPUNIT_TEST( testHistogram );
//  CPPUNIT_TEST( testMean );
  CPPUNIT_TEST( testGaussFilter );
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
   * Test histogram 
   */  
  void testHistogram();
  /**
   * Test something...
   */  
  void testSomething();
  /**
   * Test filters 
   */  
  void testConvolution();
  void testFloatFilter();
  void testGrayFilter();
//  void testMean();
  void testGaussFilter();
};

#endif // _TESTCONVERTER_IMAGE_H
