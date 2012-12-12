#ifndef MultiChannelImageTTest_H
#define MultiChannelImageTTest_H

#include <cppunit/extensions/HelperMacros.h>

/**
 * CppUnit-Testcase. 
 * Tests for Image and ColorImage
 */
class MultiChannelImageTTest : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE( MultiChannelImageTTest );
    CPPUNIT_TEST( test );
    CPPUNIT_TEST_SUITE_END();

 private:

 public:
    void setUp();
    void tearDown();

    void test();
};

#endif // MultiChannelImageTTest_H
