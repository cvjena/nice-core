
#ifndef _TESTFILTER_H_
#define _TESTFILTER_H_

#include <cppunit/extensions/HelperMacros.h>

/**
 * CppUnit-Testcase. 
 * Tests for Filter Operations
 */
class TestFilter : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE( TestFilter );

    CPPUNIT_TEST( testSepFloatFilter );
    CPPUNIT_TEST( testSepIntFilter );

    CPPUNIT_TEST( testFloatFilter );
    CPPUNIT_TEST( testIntFilter );

    CPPUNIT_TEST( testSmoothing );
    CPPUNIT_TEST( testGradient );

    CPPUNIT_TEST( testCanny );

    CPPUNIT_TEST_SUITE_END();

    private:

    public:
        void setUp();
        void tearDown();

        void testSepFloatFilter();
        void testSepIntFilter();

        void testFloatFilter();
        void testIntFilter();

        void testSmoothing();
        void testGradient();

        void testCanny();
};

#endif // _TESTFILTER_H_
