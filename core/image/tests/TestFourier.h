
#ifndef _TestFourier_H_
#define _TestFourier_H_

#include <cppunit/extensions/HelperMacros.h>

/**
 * CppUnit-Testcase. 
 * Tests for Fourier Operations
 */
class TestFourier : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE( TestFourier );

    
    CPPUNIT_TEST( testFourierTransform );

    CPPUNIT_TEST_SUITE_END();

    private:

    public:
        void setUp();
        void tearDown();
        void testFourierTransform();
       
};

#endif // _TestFourier_H_
