
#ifndef _TESTCONVERT_H_
#define _TESTCONVERT_H_

#include <cppunit/extensions/HelperMacros.h>

#include "core/image/ImageT.h"
#include "core/image/ColorImageT.h"

/**
 * CppUnit-Testcase. 
 * Tests for Filter Operations
 */
class TestConvert : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE( TestConvert );

  CPPUNIT_TEST( testColorspaceConversion );
  CPPUNIT_TEST( testImageConversion );
  CPPUNIT_TEST( testGrayFloat );
  CPPUNIT_TEST( testRGBFloat );
  CPPUNIT_TEST( testfloatToGrayScaled );
  CPPUNIT_TEST( testconvertBitDepth );

  CPPUNIT_TEST_SUITE_END();

 private:

 public:
    void setUp();
    void tearDown();

    void testColorspaceConversion();
    void testImageConversion();

    void testGrayFloat();

    void testfloatToGrayScaled();

    void testRGBFloat();

    void testconvertBitDepth();
};

#endif // _TESTCONVERT_H_
