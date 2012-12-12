#ifndef IMAGETEST_H
#define IMAGETEST_H

#include <cppunit/extensions/HelperMacros.h>

/**
 * CppUnit-Testcase. 
 * Tests for Image and ColorImage
 */
class ImageTest : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE( ImageTest );
    CPPUNIT_TEST( testGrayImage );
    CPPUNIT_TEST( testGrayImageBilinear );
    CPPUNIT_TEST( testGrayImage16s );
    CPPUNIT_TEST( testColorImage );
    CPPUNIT_TEST( testFloatImage );
    CPPUNIT_TEST( testImageTools );
    CPPUNIT_TEST_SUITE_END();

 private:

 public:
    void setUp();
    void tearDown();

    void testGrayImage();
    void testGrayImageBilinear();
    void testGrayImage16s();
    void testFloatImage();
    void testColorImage();

    void testImageTools();
};

#endif // IMAGETEST_H
