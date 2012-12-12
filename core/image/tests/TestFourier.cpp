
#include "TestFourier.h"
#include <string>

#include "core/basics/cppunitex.h"
#include "core/image/ImageT.h"
#include "core/image/ColorImageT.h"
#include "core/image/Fourier.h"
#include "core/image/ImageOperators.h"



using namespace std;
using namespace NICE;

CPPUNIT_TEST_SUITE_REGISTRATION(TestFourier);

void TestFourier::setUp()
{
}

void TestFourier::tearDown()
{
}

void TestFourier::testFourierTransform()
{
#ifdef NICE_USELIB_ICE 
    const int testsizex = 99;
    const int testsizey = 89;
    const float testvalue = 100.0;
    FloatImage space_real(testsizex, testsizey), space_imag(testsizex, testsizey), freq_real, freq_imag, space_real_compare, space_imag_compare;
    space_real.set(testvalue);
    space_imag.set(0.0);

    Fourier::FourierTransform(space_real, space_imag, freq_real, freq_imag);
    Fourier::FourierTransformInverse(freq_real, freq_imag, space_real_compare, space_imag_compare);

    CPPUNIT_ASSERT_EQUAL(testsizex, space_real_compare.width());
    CPPUNIT_ASSERT_EQUAL(testsizey, space_real_compare.height());
    CPPUNIT_ASSERT_EQUAL(testsizex, space_imag_compare.width());
    CPPUNIT_ASSERT_EQUAL(testsizey, space_imag_compare.height());
    FloatImage diff;
    diff = space_real - space_real_compare;
    CPPUNIT_ASSERT_EQUAL(testsizex, diff.width());
    CPPUNIT_ASSERT_EQUAL(testsizey, diff.height());
    CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(0.0, diff.max(), 1e-10);
    CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(0.0, diff.min(), 1e-10);
    CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(0.0, freq_imag.max(), 1e-10);
    CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(0.0, freq_imag.min(), 1e-10);
    CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(sqrt(testsizex*testsizey)*testvalue, freq_real.getPixel(testsizex / 2, testsizey / 2), 1e-3);
    freq_real.setPixel(testsizex / 2, testsizey / 2,0);
    CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(0.0, freq_real.max(), 1e-10);
    CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(0.0, freq_real.min(), 1e-10);
#endif
}
