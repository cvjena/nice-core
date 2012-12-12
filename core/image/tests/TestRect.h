
#ifndef _TESTRECT_H_
#define _TESTRECT_H_

#include <cppunit/extensions/HelperMacros.h>

/**
 * CppUnit-Testcase. 
 * Tests for Filter Operations
 */
class TestRect : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE( TestRect );

    CPPUNIT_TEST( testRect );

    CPPUNIT_TEST( testCenter );
    CPPUNIT_TEST( testArea );

    CPPUNIT_TEST( testIntersect );

    CPPUNIT_TEST_SUITE_END();

private:

public:
    void setUp();
    void tearDown();

    void testRect();

    void testCenter();
    void testArea();

    void testIntersect();
};

#endif // _TESTRECT_H_
