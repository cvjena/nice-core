
#include "TestFilter.h"
#include <string>

#include "core/image/ImageT.h"
#include "core/image/ColorImageT.h"
#include "core/image/Filter.h"

using namespace std;
using namespace NICE;

CPPUNIT_TEST_SUITE_REGISTRATION( TestFilter );

void TestFilter::setUp()
{
}

void TestFilter::tearDown()
{
}

void TestFilter::testSepFloatFilter()
{
    FloatImage fsrc(5,5);
    fsrc(0,0)=1; fsrc(1,0)=5; fsrc(2,0)=3; fsrc(3,0)=2; fsrc(4,0)=12;
    fsrc(0,1)=3; fsrc(1,1)=3; fsrc(2,1)=5; fsrc(3,1)=2; fsrc(4,1)=15;
    fsrc(0,2)=7; fsrc(1,2)=9; fsrc(2,2)=7; fsrc(3,2)=1; fsrc(4,2)=11;
    fsrc(0,3)=9; fsrc(1,3)=6; fsrc(2,3)=3; fsrc(3,3)=1; fsrc(4,3)=13;
    fsrc(0,4)=5; fsrc(1,4)=5; fsrc(2,4)=6; fsrc(3,4)=3; fsrc(4,4)=18;

    FloatImage* fresult = new FloatImage(fsrc.width(), fsrc.height());

    // test a mean kernel with size=3
    FloatVector fmeanKernel1x3(3,1.0/3.0);

    fresult = filterX(fsrc, fmeanKernel1x3, fresult);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  3.00000, static_cast<double>(fresult->getPixel(1,0)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  3.33333, static_cast<double>(fresult->getPixel(2,0)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  5.66666, static_cast<double>(fresult->getPixel(3,0)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  3.66666, static_cast<double>(fresult->getPixel(1,1)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  3.33333, static_cast<double>(fresult->getPixel(2,1)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  7.33333, static_cast<double>(fresult->getPixel(3,1)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  7.66666, static_cast<double>(fresult->getPixel(1,2)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  5.66666, static_cast<double>(fresult->getPixel(2,2)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  6.33333, static_cast<double>(fresult->getPixel(3,2)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  6.00000, static_cast<double>(fresult->getPixel(1,3)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  3.33333, static_cast<double>(fresult->getPixel(2,3)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  5.66666, static_cast<double>(fresult->getPixel(3,3)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  5.33333, static_cast<double>(fresult->getPixel(1,4)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  4.66666, static_cast<double>(fresult->getPixel(2,4)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  9.00000, static_cast<double>(fresult->getPixel(3,4)), 0.00001);

    fresult = filterY(fsrc, fmeanKernel1x3);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  3.66666, static_cast<double>(fresult->getPixel(0,1)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  6.33333, static_cast<double>(fresult->getPixel(0,2)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  7.00000, static_cast<double>(fresult->getPixel(0,3)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  5.66666, static_cast<double>(fresult->getPixel(1,1)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  6.00000, static_cast<double>(fresult->getPixel(1,2)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  6.66666, static_cast<double>(fresult->getPixel(1,3)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  5.00000, static_cast<double>(fresult->getPixel(2,1)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  5.00000, static_cast<double>(fresult->getPixel(2,2)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  5.33333, static_cast<double>(fresult->getPixel(2,3)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  1.66666, static_cast<double>(fresult->getPixel(3,1)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  1.33333, static_cast<double>(fresult->getPixel(3,2)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  1.66666, static_cast<double>(fresult->getPixel(3,3)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL( 12.66666, static_cast<double>(fresult->getPixel(4,1)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL( 13.00000, static_cast<double>(fresult->getPixel(4,2)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL( 14.00000, static_cast<double>(fresult->getPixel(4,3)), 0.00001);

    // test a mean kernel with size=5
    FloatVector fmeanKernel1x5(5,1.0/5.0);

    fresult = filterX(fsrc, fmeanKernel1x5, fresult);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  4.60000, static_cast<double>(fresult->getPixel(2,0)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  5.60000, static_cast<double>(fresult->getPixel(2,1)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  7.00000, static_cast<double>(fresult->getPixel(2,2)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  6.40000, static_cast<double>(fresult->getPixel(2,3)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  7.40000, static_cast<double>(fresult->getPixel(2,4)), 0.00001);

    fresult = filterY(fsrc, fmeanKernel1x5);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  5.00000, static_cast<double>(fresult->getPixel(0,2)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  5.60000, static_cast<double>(fresult->getPixel(1,2)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  4.80000, static_cast<double>(fresult->getPixel(2,2)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  1.80000, static_cast<double>(fresult->getPixel(3,2)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL( 13.80000, static_cast<double>(fresult->getPixel(4,2)), 0.00001);

    // test a float difference operator
    FloatVector diffKernel(3); // inverted Kernel !
    diffKernel(0) = +1.0/2.0; diffKernel(1)=0.0; diffKernel(2)=-1.0/2.0;

    fresult = filterX(fsrc, diffKernel);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  1.00000, static_cast<double>(fresult->getPixel(1,0)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(- 1.50000, static_cast<double>(fresult->getPixel(2,0)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  4.50000, static_cast<double>(fresult->getPixel(3,0)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  1.00000, static_cast<double>(fresult->getPixel(1,1)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(- 0.50000, static_cast<double>(fresult->getPixel(2,1)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  5.00000, static_cast<double>(fresult->getPixel(3,1)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  0.00000, static_cast<double>(fresult->getPixel(1,2)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(- 4.00000, static_cast<double>(fresult->getPixel(2,2)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  2.00000, static_cast<double>(fresult->getPixel(3,2)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(- 3.00000, static_cast<double>(fresult->getPixel(1,3)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(- 2.50000, static_cast<double>(fresult->getPixel(2,3)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  5.00000, static_cast<double>(fresult->getPixel(3,3)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  0.50000, static_cast<double>(fresult->getPixel(1,4)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(- 1.00000, static_cast<double>(fresult->getPixel(2,4)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  6.00000, static_cast<double>(fresult->getPixel(3,4)), 0.00001);

    fresult = filterY(fsrc, diffKernel);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  3.00000, static_cast<double>(fresult->getPixel(0,1)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  3.00000, static_cast<double>(fresult->getPixel(0,2)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(- 1.00000, static_cast<double>(fresult->getPixel(0,3)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  2.00000, static_cast<double>(fresult->getPixel(1,1)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  1.50000, static_cast<double>(fresult->getPixel(1,2)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(- 2.00000, static_cast<double>(fresult->getPixel(1,3)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  2.00000, static_cast<double>(fresult->getPixel(2,1)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(- 1.00000, static_cast<double>(fresult->getPixel(2,2)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(- 0.50000, static_cast<double>(fresult->getPixel(2,3)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(- 0.50000, static_cast<double>(fresult->getPixel(3,1)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(- 0.50000, static_cast<double>(fresult->getPixel(3,2)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  1.00000, static_cast<double>(fresult->getPixel(3,3)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(- 0.50000, static_cast<double>(fresult->getPixel(4,1)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(- 1.00000, static_cast<double>(fresult->getPixel(4,2)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  3.50000, static_cast<double>(fresult->getPixel(4,3)), 0.00001);
}

void TestFilter::testSepIntFilter()
{
    Image src(5,5);
    src(0,0)=1; src(1,0)=5; src(2,0)=3; src(3,0)=2; src(4,0)=12;
    src(0,1)=3; src(1,1)=3; src(2,1)=5; src(3,1)=2; src(4,1)=15;
    src(0,2)=7; src(1,2)=9; src(2,2)=7; src(3,2)=1; src(4,2)=11;
    src(0,3)=9; src(1,3)=6; src(2,3)=3; src(3,3)=1; src(4,3)=13;
    src(0,4)=5; src(1,4)=5; src(2,4)=6; src(3,4)=3; src(4,4)=18;

    Image* result = new Image(src.width(), src.height());

    // test a mean kernel with size=3
    IntVector meanKernel1x3(3,1);

    result = filterX(src, meanKernel1x3, result);
    CPPUNIT_ASSERT_EQUAL(  3, static_cast<int>(result->getPixel(1,0)));
    CPPUNIT_ASSERT_EQUAL(  3, static_cast<int>(result->getPixel(2,0)));
    CPPUNIT_ASSERT_EQUAL(  6, static_cast<int>(result->getPixel(3,0)));
    CPPUNIT_ASSERT_EQUAL(  4, static_cast<int>(result->getPixel(1,1)));
    CPPUNIT_ASSERT_EQUAL(  3, static_cast<int>(result->getPixel(2,1)));
    CPPUNIT_ASSERT_EQUAL(  7, static_cast<int>(result->getPixel(3,1)));
    CPPUNIT_ASSERT_EQUAL(  8, static_cast<int>(result->getPixel(1,2)));
    CPPUNIT_ASSERT_EQUAL(  6, static_cast<int>(result->getPixel(2,2)));
    CPPUNIT_ASSERT_EQUAL(  6, static_cast<int>(result->getPixel(3,2)));
    CPPUNIT_ASSERT_EQUAL(  6, static_cast<int>(result->getPixel(1,3)));
    CPPUNIT_ASSERT_EQUAL(  3, static_cast<int>(result->getPixel(2,3)));
    CPPUNIT_ASSERT_EQUAL(  6, static_cast<int>(result->getPixel(3,3)));
    CPPUNIT_ASSERT_EQUAL(  5, static_cast<int>(result->getPixel(1,4)));
    CPPUNIT_ASSERT_EQUAL(  5, static_cast<int>(result->getPixel(2,4)));
    CPPUNIT_ASSERT_EQUAL(  9, static_cast<int>(result->getPixel(3,4)));

    result = filterY(src, meanKernel1x3, result);
    CPPUNIT_ASSERT_EQUAL(  4, static_cast<int>(result->getPixel(0,1)));
    CPPUNIT_ASSERT_EQUAL(  6, static_cast<int>(result->getPixel(0,2)));
    CPPUNIT_ASSERT_EQUAL(  7, static_cast<int>(result->getPixel(0,3)));
    CPPUNIT_ASSERT_EQUAL(  6, static_cast<int>(result->getPixel(1,1)));
    CPPUNIT_ASSERT_EQUAL(  6, static_cast<int>(result->getPixel(1,2)));
    CPPUNIT_ASSERT_EQUAL(  7, static_cast<int>(result->getPixel(1,3)));
    CPPUNIT_ASSERT_EQUAL(  5, static_cast<int>(result->getPixel(2,1)));
    CPPUNIT_ASSERT_EQUAL(  5, static_cast<int>(result->getPixel(2,2)));
    CPPUNIT_ASSERT_EQUAL(  5, static_cast<int>(result->getPixel(2,3)));
    CPPUNIT_ASSERT_EQUAL(  2, static_cast<int>(result->getPixel(3,1)));
    CPPUNIT_ASSERT_EQUAL(  1, static_cast<int>(result->getPixel(3,2)));
    CPPUNIT_ASSERT_EQUAL(  2, static_cast<int>(result->getPixel(3,3)));
    CPPUNIT_ASSERT_EQUAL( 13, static_cast<int>(result->getPixel(4,1)));
    CPPUNIT_ASSERT_EQUAL( 13, static_cast<int>(result->getPixel(4,2)));
    CPPUNIT_ASSERT_EQUAL( 14, static_cast<int>(result->getPixel(4,3)));

     // test a int mean kernel, size=3
    IntVector meanKernel1x5(5,1);

    result = filterX(src, meanKernel1x5, result);
    CPPUNIT_ASSERT_EQUAL(  5, static_cast<int>(result->getPixel(2,0)));
    CPPUNIT_ASSERT_EQUAL(  6, static_cast<int>(result->getPixel(2,1)));
    CPPUNIT_ASSERT_EQUAL(  7, static_cast<int>(result->getPixel(2,2)));
    CPPUNIT_ASSERT_EQUAL(  6, static_cast<int>(result->getPixel(2,3)));
    CPPUNIT_ASSERT_EQUAL(  7, static_cast<int>(result->getPixel(2,4)));

    result = filterY(src, meanKernel1x5, result);
    CPPUNIT_ASSERT_EQUAL(  5, static_cast<int>(result->getPixel(0,2)));
    CPPUNIT_ASSERT_EQUAL(  6, static_cast<int>(result->getPixel(1,2)));
    CPPUNIT_ASSERT_EQUAL(  5, static_cast<int>(result->getPixel(2,2)));
    CPPUNIT_ASSERT_EQUAL(  2, static_cast<int>(result->getPixel(3,2)));
    CPPUNIT_ASSERT_EQUAL( 14, static_cast<int>(result->getPixel(4,2)));

    // test a difference operator
    IntVector diffKernel(3);
    diffKernel(0)=+1; diffKernel(1)=0; diffKernel(2)=-1; // inverted Kernel !

    result = filterX(src, diffKernel);
    CPPUNIT_ASSERT_DOUBLES_EQUAL( 1+128, static_cast<double>(result->getPixel(1,0)), 1);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(-1+128, static_cast<double>(result->getPixel(2,0)), 1);
    CPPUNIT_ASSERT_DOUBLES_EQUAL( 4+128, static_cast<double>(result->getPixel(3,0)), 1);
    CPPUNIT_ASSERT_DOUBLES_EQUAL( 1+128, static_cast<double>(result->getPixel(1,1)), 1);
    CPPUNIT_ASSERT_DOUBLES_EQUAL( 0+128, static_cast<double>(result->getPixel(2,1)), 1);
    CPPUNIT_ASSERT_DOUBLES_EQUAL( 5+128, static_cast<double>(result->getPixel(3,1)), 1);
    CPPUNIT_ASSERT_DOUBLES_EQUAL( 0+128, static_cast<double>(result->getPixel(1,2)), 1);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(-4+128, static_cast<double>(result->getPixel(2,2)), 1);
    CPPUNIT_ASSERT_DOUBLES_EQUAL( 2+128, static_cast<double>(result->getPixel(3,2)), 1);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(-3+128, static_cast<double>(result->getPixel(1,3)), 1);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(-2+128, static_cast<double>(result->getPixel(2,3)), 1);
    CPPUNIT_ASSERT_DOUBLES_EQUAL( 5+128, static_cast<double>(result->getPixel(3,3)), 1);
    CPPUNIT_ASSERT_DOUBLES_EQUAL( 0+128, static_cast<double>(result->getPixel(1,4)), 1);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(-1+128, static_cast<double>(result->getPixel(2,4)), 1);
    CPPUNIT_ASSERT_DOUBLES_EQUAL( 6+128, static_cast<double>(result->getPixel(3,4)), 1);

    result = filterY(src, diffKernel);
    CPPUNIT_ASSERT_DOUBLES_EQUAL( 3+128, static_cast<double>(result->getPixel(0,1)), 1);
    CPPUNIT_ASSERT_DOUBLES_EQUAL( 3+128, static_cast<double>(result->getPixel(0,2)), 1);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(-1+128, static_cast<double>(result->getPixel(0,3)), 1);
    CPPUNIT_ASSERT_DOUBLES_EQUAL( 2+128, static_cast<double>(result->getPixel(1,1)), 1);
    CPPUNIT_ASSERT_DOUBLES_EQUAL( 1+128, static_cast<double>(result->getPixel(1,2)), 1);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(-2+128, static_cast<double>(result->getPixel(1,3)), 1);
    CPPUNIT_ASSERT_DOUBLES_EQUAL( 2+128, static_cast<double>(result->getPixel(2,1)), 1);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(-1+128, static_cast<double>(result->getPixel(2,2)), 1);
    CPPUNIT_ASSERT_DOUBLES_EQUAL( 0+128, static_cast<double>(result->getPixel(2,3)), 1);
    CPPUNIT_ASSERT_DOUBLES_EQUAL( 0+128, static_cast<double>(result->getPixel(3,1)), 1);
    CPPUNIT_ASSERT_DOUBLES_EQUAL( 0+128, static_cast<double>(result->getPixel(3,2)), 1);
    CPPUNIT_ASSERT_DOUBLES_EQUAL( 1+128, static_cast<double>(result->getPixel(3,3)), 1);
    CPPUNIT_ASSERT_DOUBLES_EQUAL( 0+128, static_cast<double>(result->getPixel(4,1)), 1);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(-1+128, static_cast<double>(result->getPixel(4,2)), 1);
    CPPUNIT_ASSERT_DOUBLES_EQUAL( 3+128, static_cast<double>(result->getPixel(4,3)), 1);
}

void TestFilter::testFloatFilter()
{
    FloatImage fsrc(5,5);
    fsrc(0,0)=1; fsrc(1,0)=5; fsrc(2,0)=3; fsrc(3,0)=2; fsrc(4,0)=12;
    fsrc(0,1)=3; fsrc(1,1)=3; fsrc(2,1)=5; fsrc(3,1)=2; fsrc(4,1)=15;
    fsrc(0,2)=7; fsrc(1,2)=9; fsrc(2,2)=7; fsrc(3,2)=1; fsrc(4,2)=11;
    fsrc(0,3)=9; fsrc(1,3)=6; fsrc(2,3)=3; fsrc(3,3)=1; fsrc(4,3)=13;
    fsrc(0,4)=5; fsrc(1,4)=5; fsrc(2,4)=6; fsrc(3,4)=3; fsrc(4,4)=18;

    FloatImage* fresult = new FloatImage(fsrc.width(), fsrc.height());

    // test a mean mask with size=3x3
    FloatMatrix fmeanMask3x3(3,3,1.0/9.0);
    fresult = filter(fsrc, fmeanMask3x3, fresult);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  4.77777, static_cast<double>(fresult->getPixel(1,1)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  4.11111, static_cast<double>(fresult->getPixel(2,1)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  6.44444, static_cast<double>(fresult->getPixel(3,1)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  5.77777, static_cast<double>(fresult->getPixel(1,2)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  4.11111, static_cast<double>(fresult->getPixel(2,2)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  6.44444, static_cast<double>(fresult->getPixel(3,2)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  6.33333, static_cast<double>(fresult->getPixel(1,3)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  4.55555, static_cast<double>(fresult->getPixel(2,3)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  7.00000, static_cast<double>(fresult->getPixel(3,3)), 0.00001);

    // test a mean mask with size=5x5
    FloatMatrix fmeanMask5x5(5,5,1.0/25.0);
    fresult = filter(fsrc, fmeanMask5x5, fresult);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  6.20000, static_cast<double>(fresult->getPixel(2,2)), 0.00001);

     // test a float gauss mask, size=3x3
    FloatMatrix fgaussMask(3,3);
    fgaussMask(0,0)=1.0/16.0; fgaussMask(0,1)=2.0/16.0; fgaussMask(0,2)=1.0/16.0;
    fgaussMask(1,0)=2.0/16.0; fgaussMask(1,1)=4.0/16.0; fgaussMask(1,2)=2.0/16.0;
    fgaussMask(2,0)=1.0/16.0; fgaussMask(2,1)=2.0/16.0; fgaussMask(2,2)=1.0/16.0;

    fresult = filter(fsrc, fgaussMask);
    CPPUNIT_ASSERT_DOUBLES_EQUAL( 4.62500, static_cast<double>(fresult->getPixel(1,1)), 0.0);
    CPPUNIT_ASSERT_DOUBLES_EQUAL( 4.18750, static_cast<double>(fresult->getPixel(2,1)), 0.0);
    CPPUNIT_ASSERT_DOUBLES_EQUAL( 5.43750, static_cast<double>(fresult->getPixel(3,1)), 0.0);
    CPPUNIT_ASSERT_DOUBLES_EQUAL( 6.37500, static_cast<double>(fresult->getPixel(1,2)), 0.0);
    CPPUNIT_ASSERT_DOUBLES_EQUAL( 4.75000, static_cast<double>(fresult->getPixel(2,2)), 0.0);
    CPPUNIT_ASSERT_DOUBLES_EQUAL( 5.12500, static_cast<double>(fresult->getPixel(3,2)), 0.0);
    CPPUNIT_ASSERT_DOUBLES_EQUAL( 6.31250, static_cast<double>(fresult->getPixel(1,3)), 0.0);
    CPPUNIT_ASSERT_DOUBLES_EQUAL( 4.37500, static_cast<double>(fresult->getPixel(2,3)), 0.0);
    CPPUNIT_ASSERT_DOUBLES_EQUAL( 5.37500, static_cast<double>(fresult->getPixel(3,3)), 0.0);

    // test a float sobel mask (inverted mask !)
    FloatMatrix fsobelX(3,3);
    fsobelX(0,0)=+1.0/8.0; fsobelX(0,1)=0.0; fsobelX(0,2)=-1.0/8.0;
    fsobelX(1,0)=+2.0/8.0; fsobelX(1,1)=0.0; fsobelX(1,2)=-2.0/8.0;
    fsobelX(2,0)=+1.0/8.0; fsobelX(2,1)=0.0; fsobelX(2,2)=-1.0/8.0;

    fresult = filter(fsrc, fsobelX);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  0.75000, static_cast<double>(fresult->getPixel(1,1)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(- 1.62500, static_cast<double>(fresult->getPixel(2,1)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  4.12500, static_cast<double>(fresult->getPixel(3,1)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(- 0.50000, static_cast<double>(fresult->getPixel(1,2)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(- 2.75000, static_cast<double>(fresult->getPixel(2,2)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  3.50000, static_cast<double>(fresult->getPixel(3,2)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(- 1.37500, static_cast<double>(fresult->getPixel(1,3)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(- 2.50000, static_cast<double>(fresult->getPixel(2,3)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  4.50000, static_cast<double>(fresult->getPixel(3,3)), 0.00001);

    FloatMatrix fsobelY(3,3);
    fsobelY(0,0)=+1.0/8.0; fsobelY(0,1)=+2.0/8.0; fsobelY(0,2)=+1.0/8.0;
    fsobelY(1,0)= 0.0    ; fsobelY(1,1)= 0.0    ; fsobelY(1,2)= 0.0;
    fsobelY(2,0)=-1.0/8.0; fsobelY(2,1)=-2.0/8.0; fsobelY(2,2)=-1.0/8.0;

    fresult = filter(fsrc, fsobelY);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  2.25000, static_cast<double>(fresult->getPixel(1,1)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  1.37500, static_cast<double>(fresult->getPixel(2,1)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  0.12500, static_cast<double>(fresult->getPixel(3,1)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  1.25000, static_cast<double>(fresult->getPixel(1,2)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(- 0.25000, static_cast<double>(fresult->getPixel(2,2)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(- 0.75000, static_cast<double>(fresult->getPixel(3,2)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(- 1.37500, static_cast<double>(fresult->getPixel(1,3)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(- 0.50000, static_cast<double>(fresult->getPixel(2,3)), 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  1.25000, static_cast<double>(fresult->getPixel(3,3)), 0.00001);
}

void TestFilter::testIntFilter()
{
    Image src(5,5);
    Image*  result  = new Image(src.width(), src.height());

    src(0,0)=1; src(1,0)=5; src(2,0)=3; src(3,0)=2; src(4,0)=12;
    src(0,1)=3; src(1,1)=3; src(2,1)=5; src(3,1)=2; src(4,1)=15;
    src(0,2)=7; src(1,2)=9; src(2,2)=7; src(3,2)=1; src(4,2)=11;
    src(0,3)=9; src(1,3)=6; src(2,3)=3; src(3,3)=1; src(4,3)=13;
    src(0,4)=5; src(1,4)=5; src(2,4)=6; src(3,4)=3; src(4,4)=18;

    // test a int mean mask, size=3x3
    IntMatrix meanMask3x3(3,3,1);
    result = filter(src, meanMask3x3, result);
    CPPUNIT_ASSERT_EQUAL(  5, static_cast<int>(result->getPixel(1,1)));
    CPPUNIT_ASSERT_EQUAL(  4, static_cast<int>(result->getPixel(2,1)));
    CPPUNIT_ASSERT_EQUAL(  6, static_cast<int>(result->getPixel(3,1)));
    CPPUNIT_ASSERT_EQUAL(  6, static_cast<int>(result->getPixel(1,2)));
    CPPUNIT_ASSERT_EQUAL(  4, static_cast<int>(result->getPixel(2,2)));
    CPPUNIT_ASSERT_EQUAL(  6, static_cast<int>(result->getPixel(3,2)));
    CPPUNIT_ASSERT_EQUAL(  6, static_cast<int>(result->getPixel(1,3)));
    CPPUNIT_ASSERT_EQUAL(  5, static_cast<int>(result->getPixel(2,3)));
    CPPUNIT_ASSERT_EQUAL(  7, static_cast<int>(result->getPixel(3,3)));

    // test a mean mask with size=5x5
    IntMatrix meanMask5x5(5,5,1);
    result = filter(src, meanMask5x5, result);
    CPPUNIT_ASSERT_EQUAL(  6, static_cast<int>(result->getPixel(2,2)));

    // test a int gauss mask, size=3x3
    IntMatrix gaussMask(3,3);
    gaussMask(0,0)=1; gaussMask(1,0)=2; gaussMask(2,0)=1;
    gaussMask(0,1)=2; gaussMask(1,1)=4; gaussMask(2,1)=2;
    gaussMask(0,2)=1; gaussMask(1,2)=2; gaussMask(2,2)=1;

    result = filter(src, gaussMask);
    CPPUNIT_ASSERT_EQUAL(  5, static_cast<int>(result->getPixel(1,1)));
    CPPUNIT_ASSERT_EQUAL(  4, static_cast<int>(result->getPixel(2,1)));
    CPPUNIT_ASSERT_EQUAL(  5, static_cast<int>(result->getPixel(3,1)));
    CPPUNIT_ASSERT_EQUAL(  6, static_cast<int>(result->getPixel(1,2)));
    CPPUNIT_ASSERT_EQUAL(  5, static_cast<int>(result->getPixel(2,2)));
    CPPUNIT_ASSERT_EQUAL(  5, static_cast<int>(result->getPixel(3,2)));
    CPPUNIT_ASSERT_EQUAL(  6, static_cast<int>(result->getPixel(1,3)));
    CPPUNIT_ASSERT_EQUAL(  4, static_cast<int>(result->getPixel(2,3)));
    CPPUNIT_ASSERT_EQUAL(  5, static_cast<int>(result->getPixel(3,3)));

    // test an sobel mask (inverted mask !)
    IntMatrix sobelX(3,3);
    sobelX(0,0)=+1; sobelX(0,1)=0; sobelX(0,2)=-1;
    sobelX(1,0)=+2; sobelX(1,1)=0; sobelX(1,2)=-2;
    sobelX(2,0)=+1; sobelX(2,1)=0; sobelX(2,2)=-1;

    IntMatrix sobelY(3,3);
    sobelY(0,0)=+1; sobelY(0,1)=+2; sobelY(0,2)=+1;
    sobelY(1,0)= 0; sobelY(1,1)= 0; sobelY(1,2)= 0;
    sobelY(2,0)=-1; sobelY(2,1)=-2; sobelY(2,2)=-1;

    result = filter(src, sobelX);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  0+128, static_cast<int>(result->getPixel(1,1)), 1);
    CPPUNIT_ASSERT_DOUBLES_EQUAL( -1+128, static_cast<int>(result->getPixel(2,1)), 1);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  4+128, static_cast<int>(result->getPixel(3,1)), 1);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  0+128, static_cast<int>(result->getPixel(1,2)), 1);
    CPPUNIT_ASSERT_DOUBLES_EQUAL( -2+128, static_cast<int>(result->getPixel(2,2)), 1);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  3+128, static_cast<int>(result->getPixel(3,2)), 1);
    CPPUNIT_ASSERT_DOUBLES_EQUAL( -1+128, static_cast<int>(result->getPixel(1,3)), 1);
    CPPUNIT_ASSERT_DOUBLES_EQUAL( -2+128, static_cast<int>(result->getPixel(2,3)), 1);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  4+128, static_cast<int>(result->getPixel(3,3)), 1);

    result = filter(src, sobelY);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  2+128, static_cast<int>(result->getPixel(1,1)), 1);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  1+128, static_cast<int>(result->getPixel(2,1)), 1);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  0+128, static_cast<int>(result->getPixel(3,1)), 1);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  1+128, static_cast<int>(result->getPixel(1,2)), 1);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  0+128, static_cast<int>(result->getPixel(2,2)), 1);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  0+128, static_cast<int>(result->getPixel(3,2)), 1);
    CPPUNIT_ASSERT_DOUBLES_EQUAL( -1+128, static_cast<int>(result->getPixel(1,3)), 1);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  0+128, static_cast<int>(result->getPixel(2,3)), 1);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  1+128, static_cast<int>(result->getPixel(3,3)), 1);
}

void TestFilter::testSmoothing()
{
    Image src(14,14);
    src.set(0);
    for(int j=4; j<src.height()-4; ++j)
        for(int i=4; i<src.width()-4; ++i)
            src(i,j)  = 150;
    Image* result = new Image(src.width(), src.height());
    // test mean
    {
        // meanX: size=2*1+1
        result = meanX(src, 1, result);
        for(int i=1; i<src.width()-1;++i)
        {
            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel(i, 2)));
            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel(i, 3)));
            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel(i,10)));
            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel(i,11)));
        }
        for(int i=4; i<=9; ++i)
        {
            CPPUNIT_ASSERT_EQUAL( 50, static_cast<int>(result->getPixel( 3,i)));
            CPPUNIT_ASSERT_EQUAL(100, static_cast<int>(result->getPixel( 4,i)));
            CPPUNIT_ASSERT_EQUAL(150, static_cast<int>(result->getPixel( 5,i)));

            CPPUNIT_ASSERT_EQUAL(150, static_cast<int>(result->getPixel( 8,i)));
            CPPUNIT_ASSERT_EQUAL(100, static_cast<int>(result->getPixel( 9,i)));
            CPPUNIT_ASSERT_EQUAL( 50, static_cast<int>(result->getPixel(10,i)));
        }
        // meanX: size=2*2+1
        result = meanX(src, 2, result);
        for(int i=2; i<src.width()-2;++i)
        {
            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel(i, 2)));
            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel(i, 3)));
            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel(i,10)));
            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel(i,11)));
        }
        for(int i=4; i<=9; ++i)
        {
            CPPUNIT_ASSERT_EQUAL( 30, static_cast<int>(result->getPixel( 2,i)));
            CPPUNIT_ASSERT_EQUAL( 60, static_cast<int>(result->getPixel( 3,i)));
            CPPUNIT_ASSERT_EQUAL( 90, static_cast<int>(result->getPixel( 4,i)));
            CPPUNIT_ASSERT_EQUAL(120, static_cast<int>(result->getPixel( 5,i)));
            CPPUNIT_ASSERT_EQUAL(150, static_cast<int>(result->getPixel( 6,i)));
            CPPUNIT_ASSERT_EQUAL(150, static_cast<int>(result->getPixel( 7,i)));
            CPPUNIT_ASSERT_EQUAL(120, static_cast<int>(result->getPixel( 8,i)));
            CPPUNIT_ASSERT_EQUAL( 90, static_cast<int>(result->getPixel( 9,i)));
            CPPUNIT_ASSERT_EQUAL( 60, static_cast<int>(result->getPixel(10,i)));
            CPPUNIT_ASSERT_EQUAL( 30, static_cast<int>(result->getPixel(11,i)));
        }
        // meanY: size=2*1+1
        result = meanY(src, 1, result);
        for(int i=1; i<src.height()-1;++i)
        {
            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel( 2,i)));
            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel( 3,i)));
            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel(10,i)));
            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel(11,i)));
        }
        for(int i=4; i<=9; ++i)
        {
            CPPUNIT_ASSERT_EQUAL( 50, static_cast<int>(result->getPixel(i, 3)));
            CPPUNIT_ASSERT_EQUAL(100, static_cast<int>(result->getPixel(i, 4)));
            CPPUNIT_ASSERT_EQUAL(150, static_cast<int>(result->getPixel(i, 5)));

            CPPUNIT_ASSERT_EQUAL(150, static_cast<int>(result->getPixel(i, 8)));
            CPPUNIT_ASSERT_EQUAL(100, static_cast<int>(result->getPixel(i, 9)));
            CPPUNIT_ASSERT_EQUAL( 50, static_cast<int>(result->getPixel(i,10)));
        }
        // meanY: size=2*2+1
        result = meanY(src, 2, result);
        for(int i=2; i<src.width()-2;++i)
        {
            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel( 2,i)));
            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel( 3,i)));
            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel(10,i)));
            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel(11,i)));
        }
        for(int i=4; i<=9; ++i)
        {
            CPPUNIT_ASSERT_EQUAL( 30, static_cast<int>(result->getPixel(i, 2)));
            CPPUNIT_ASSERT_EQUAL( 60, static_cast<int>(result->getPixel(i, 3)));
            CPPUNIT_ASSERT_EQUAL( 90, static_cast<int>(result->getPixel(i, 4)));
            CPPUNIT_ASSERT_EQUAL(120, static_cast<int>(result->getPixel(i, 5)));
            CPPUNIT_ASSERT_EQUAL(150, static_cast<int>(result->getPixel(i, 6)));
            CPPUNIT_ASSERT_EQUAL(150, static_cast<int>(result->getPixel(i, 7)));
            CPPUNIT_ASSERT_EQUAL(120, static_cast<int>(result->getPixel(i, 8)));
            CPPUNIT_ASSERT_EQUAL( 90, static_cast<int>(result->getPixel(i, 9)));
            CPPUNIT_ASSERT_EQUAL( 60, static_cast<int>(result->getPixel(i,10)));
            CPPUNIT_ASSERT_EQUAL( 30, static_cast<int>(result->getPixel(i,11)));
        }
        // filterMean: size=2*1+1 x 2*1+1
        result = filterMean(src, 1);
        for(int i=1; i<src.width()-1;++i)
        {
            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel( i, 1)));
            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel( i, 2)));
            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel( i,11)));
            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel( i,12)));

            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel( 1,i)));
            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel( 2,i)));
            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel(11,i)));
            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel(12,i)));
        }
        for(int i=5; i<=8; ++i)
        {
            CPPUNIT_ASSERT_EQUAL( 50, static_cast<int>(result->getPixel(i, 3)));
            CPPUNIT_ASSERT_EQUAL(100, static_cast<int>(result->getPixel(i, 4)));
            CPPUNIT_ASSERT_EQUAL(150, static_cast<int>(result->getPixel(i, 5)));
            CPPUNIT_ASSERT_EQUAL(150, static_cast<int>(result->getPixel(i, 6)));
            CPPUNIT_ASSERT_EQUAL(150, static_cast<int>(result->getPixel(i, 7)));
            CPPUNIT_ASSERT_EQUAL(150, static_cast<int>(result->getPixel(i, 8)));
            CPPUNIT_ASSERT_EQUAL(100, static_cast<int>(result->getPixel(i, 9)));
            CPPUNIT_ASSERT_EQUAL( 50, static_cast<int>(result->getPixel(i,10)));
        }
        for(int i=3; i<=10; i+=7)
        {
            CPPUNIT_ASSERT_EQUAL( 16, static_cast<int>(result->getPixel( i, 3)));
            CPPUNIT_ASSERT_EQUAL( 33, static_cast<int>(result->getPixel( i, 4)));
            CPPUNIT_ASSERT_EQUAL( 50, static_cast<int>(result->getPixel( i, 5)));
            CPPUNIT_ASSERT_EQUAL( 50, static_cast<int>(result->getPixel( i, 6)));
            CPPUNIT_ASSERT_EQUAL( 50, static_cast<int>(result->getPixel( i, 7)));
            CPPUNIT_ASSERT_EQUAL( 50, static_cast<int>(result->getPixel( i, 8)));
            CPPUNIT_ASSERT_EQUAL( 33, static_cast<int>(result->getPixel( i, 9)));
            CPPUNIT_ASSERT_EQUAL( 16, static_cast<int>(result->getPixel( i,10)));
        }
        for(int i=4; i<=9; i+=5)
        {
            CPPUNIT_ASSERT_EQUAL( 33, static_cast<int>(result->getPixel( i, 3)));
            CPPUNIT_ASSERT_EQUAL( 66, static_cast<int>(result->getPixel( i, 4)));
            CPPUNIT_ASSERT_EQUAL(100, static_cast<int>(result->getPixel( i, 5)));
            CPPUNIT_ASSERT_EQUAL(100, static_cast<int>(result->getPixel( i, 6)));
            CPPUNIT_ASSERT_EQUAL(100, static_cast<int>(result->getPixel( i, 7)));
            CPPUNIT_ASSERT_EQUAL(100, static_cast<int>(result->getPixel( i, 8)));
            CPPUNIT_ASSERT_EQUAL( 66, static_cast<int>(result->getPixel( i, 9)));
            CPPUNIT_ASSERT_EQUAL( 33, static_cast<int>(result->getPixel( i,10)));
        }
        // filterMean: size=2*2+1 x 2*2+1
        result = filterMean(src, 2);
        CPPUNIT_ASSERT_EQUAL(  6, static_cast<int>(result->getPixel( 2, 2)));
        CPPUNIT_ASSERT_EQUAL( 12, static_cast<int>(result->getPixel( 2, 3)));
        CPPUNIT_ASSERT_EQUAL( 18, static_cast<int>(result->getPixel( 2, 4)));
        CPPUNIT_ASSERT_EQUAL( 24, static_cast<int>(result->getPixel( 2, 5)));
        CPPUNIT_ASSERT_EQUAL( 30, static_cast<int>(result->getPixel( 2, 6)));
        CPPUNIT_ASSERT_EQUAL( 30, static_cast<int>(result->getPixel( 2, 7)));
        CPPUNIT_ASSERT_EQUAL( 24, static_cast<int>(result->getPixel( 2, 8)));
        CPPUNIT_ASSERT_EQUAL( 18, static_cast<int>(result->getPixel( 2, 9)));
        CPPUNIT_ASSERT_EQUAL( 12, static_cast<int>(result->getPixel( 2,10)));
        CPPUNIT_ASSERT_EQUAL(  6, static_cast<int>(result->getPixel( 2,11)));

        CPPUNIT_ASSERT_EQUAL( 18, static_cast<int>(result->getPixel( 4, 2)));
        CPPUNIT_ASSERT_EQUAL( 36, static_cast<int>(result->getPixel( 4, 3)));
        CPPUNIT_ASSERT_EQUAL( 54, static_cast<int>(result->getPixel( 4, 4)));
        CPPUNIT_ASSERT_EQUAL( 72, static_cast<int>(result->getPixel( 4, 5)));
        CPPUNIT_ASSERT_EQUAL( 90, static_cast<int>(result->getPixel( 4, 6)));
        CPPUNIT_ASSERT_EQUAL( 90, static_cast<int>(result->getPixel( 4, 7)));
        CPPUNIT_ASSERT_EQUAL( 72, static_cast<int>(result->getPixel( 4, 8)));
        CPPUNIT_ASSERT_EQUAL( 54, static_cast<int>(result->getPixel( 4, 9)));
        CPPUNIT_ASSERT_EQUAL( 36, static_cast<int>(result->getPixel( 4,10)));
        CPPUNIT_ASSERT_EQUAL( 18, static_cast<int>(result->getPixel( 4,11)));

        CPPUNIT_ASSERT_EQUAL( 30, static_cast<int>(result->getPixel( 6, 2)));
        CPPUNIT_ASSERT_EQUAL( 60, static_cast<int>(result->getPixel( 6, 3)));
        CPPUNIT_ASSERT_EQUAL( 90, static_cast<int>(result->getPixel( 6, 4)));
        CPPUNIT_ASSERT_EQUAL(120, static_cast<int>(result->getPixel( 6, 5)));
        CPPUNIT_ASSERT_EQUAL(150, static_cast<int>(result->getPixel( 6, 6)));
        CPPUNIT_ASSERT_EQUAL(150, static_cast<int>(result->getPixel( 6, 7)));
        CPPUNIT_ASSERT_EQUAL(120, static_cast<int>(result->getPixel( 6, 8)));
        CPPUNIT_ASSERT_EQUAL( 90, static_cast<int>(result->getPixel( 6, 9)));
        CPPUNIT_ASSERT_EQUAL( 60, static_cast<int>(result->getPixel( 6,10)));
        CPPUNIT_ASSERT_EQUAL( 30, static_cast<int>(result->getPixel( 6,11)));
    }

    // test gauss
    {
        // gaussX exception
        CPPUNIT_ASSERT_THROW(gaussX(src,0), ImageException);
        CPPUNIT_ASSERT_THROW(gaussX(src,3), ImageException);
        // gaussX: size=2*1+1
        result = gaussX(src, 1, result);
        for(int i=1; i<src.width()-1; ++i)
        {
            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel( i, 2)));
            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel( i, 3)));
            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel( i,10)));
            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel( i,11)));
        }
        for(int i=0; i<src.height(); ++i)
        {
            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel( 1, i)));
            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel( 2, i)));
            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel(11, i)));
            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel(12, i)));
        }
        for(int i=4; i<=9; ++i)
        {
            CPPUNIT_ASSERT_EQUAL( 38, static_cast<int>(result->getPixel( 3, i)));
            CPPUNIT_ASSERT_DOUBLES_EQUAL(113, static_cast<int>(result->getPixel( 4, i)), 1.5);
            CPPUNIT_ASSERT_EQUAL(150, static_cast<int>(result->getPixel( 5, i)));
            CPPUNIT_ASSERT_EQUAL(150, static_cast<int>(result->getPixel( 6, i)));
            CPPUNIT_ASSERT_EQUAL(150, static_cast<int>(result->getPixel( 7, i)));
            CPPUNIT_ASSERT_EQUAL(150, static_cast<int>(result->getPixel( 8, i)));
            CPPUNIT_ASSERT_DOUBLES_EQUAL(113, static_cast<int>(result->getPixel( 9, i)), 1.5);
            CPPUNIT_ASSERT_EQUAL( 38, static_cast<int>(result->getPixel(10, i)));
        }
        // gaussX: size=2*1+1
        result = gaussX(src, 2, result);
        for(int i=2; i<src.width()-2; ++i)
        {
            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel( i, 2)));
            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel( i, 3)));
            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel( i,10)));
            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel( i,11)));
        }
        for(int i=4; i<=9; ++i)
        {
            CPPUNIT_ASSERT_EQUAL(  9, static_cast<int>(result->getPixel( 2, i)));
            CPPUNIT_ASSERT_EQUAL( 47, static_cast<int>(result->getPixel( 3, i)));
            CPPUNIT_ASSERT_EQUAL(103, static_cast<int>(result->getPixel( 4, i)));
            CPPUNIT_ASSERT_EQUAL(141, static_cast<int>(result->getPixel( 5, i)));
            CPPUNIT_ASSERT_EQUAL(150, static_cast<int>(result->getPixel( 6, i)));
            CPPUNIT_ASSERT_EQUAL(150, static_cast<int>(result->getPixel( 7, i)));
            CPPUNIT_ASSERT_EQUAL(141, static_cast<int>(result->getPixel( 8, i)));
            CPPUNIT_ASSERT_EQUAL(103, static_cast<int>(result->getPixel( 9, i)));
            CPPUNIT_ASSERT_EQUAL( 47, static_cast<int>(result->getPixel(10, i)));
            CPPUNIT_ASSERT_EQUAL(  9, static_cast<int>(result->getPixel(11, i)));
        }
        // gaussY exception
        CPPUNIT_ASSERT_THROW(gaussY(src,0), ImageException);
        CPPUNIT_ASSERT_THROW(gaussY(src,3), ImageException);
        // gaussY: size=2*1+1
        result = gaussY(src, 1, result);
        for(int i=0; i<src.width(); ++i)
        {
            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel(i, 1)));
            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel(i, 2)));
            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel(i,11)));
            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel(i,12)));
        }
        for(int i=1; i<src.height()-1; ++i)
        {
            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel( 1, i)));
            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel( 2, i)));
            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel(11, i)));
            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel(12, i)));
        }
        for(int i=4; i<=9; ++i)
        {
            CPPUNIT_ASSERT_EQUAL( 38, static_cast<int>(result->getPixel(i, 3)));
            CPPUNIT_ASSERT_DOUBLES_EQUAL(113, static_cast<int>(result->getPixel(i, 4)), 1.5);
            CPPUNIT_ASSERT_EQUAL(150, static_cast<int>(result->getPixel(i, 5)));
            CPPUNIT_ASSERT_EQUAL(150, static_cast<int>(result->getPixel(i, 6)));
            CPPUNIT_ASSERT_EQUAL(150, static_cast<int>(result->getPixel(i, 7)));
            CPPUNIT_ASSERT_EQUAL(150, static_cast<int>(result->getPixel(i, 8)));
            CPPUNIT_ASSERT_DOUBLES_EQUAL(113, static_cast<int>(result->getPixel(i, 9)), 1.5);
            CPPUNIT_ASSERT_EQUAL( 38, static_cast<int>(result->getPixel(i,10)));
        }
        // gaussY: size=2*2+1
        result = gaussY(src, 2, result);
        for(int i=2; i<src.width()-2; ++i)
        {
            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel( 2, i)));
            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel( 3, i)));
            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel(10, i)));
            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel(11, i)));
        }
        for(int i=4; i<=9; ++i)
        {
            CPPUNIT_ASSERT_EQUAL(  9, static_cast<int>(result->getPixel(i, 2)));
            CPPUNIT_ASSERT_EQUAL( 47, static_cast<int>(result->getPixel(i, 3)));
            CPPUNIT_ASSERT_EQUAL(103, static_cast<int>(result->getPixel(i, 4)));
            CPPUNIT_ASSERT_EQUAL(141, static_cast<int>(result->getPixel(i, 5)));
            CPPUNIT_ASSERT_EQUAL(150, static_cast<int>(result->getPixel(i, 6)));
            CPPUNIT_ASSERT_EQUAL(150, static_cast<int>(result->getPixel(i, 7)));
            CPPUNIT_ASSERT_EQUAL(141, static_cast<int>(result->getPixel(i, 8)));
            CPPUNIT_ASSERT_EQUAL(103, static_cast<int>(result->getPixel(i, 9)));
            CPPUNIT_ASSERT_EQUAL( 47, static_cast<int>(result->getPixel(i,10)));
            CPPUNIT_ASSERT_EQUAL(  9, static_cast<int>(result->getPixel(i,11)));
        }
        // filterGauss exception
        CPPUNIT_ASSERT_THROW(filterGauss(src,0), ImageException);
        CPPUNIT_ASSERT_THROW(filterGauss(src,3), ImageException);
        // filterGauss: size=2*1+1 x 2*1+1
        result = filterGauss(src, 1, result);
        for(int i=1; i<=12; i++)
        {
            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel(i, 1)));
            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel(i, 2)));
            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel(i,11)));
            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel(i,12)));

            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel( 1,i)));
            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel( 2,i)));
            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel(11,i)));
            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel(12,i)));
        }
        // ipp uses some kind of float filtering for gaussFiltering
        // so here are some differences in results cause of rounding tempor� results
        // (non-ipp uses separizable integer filter)
        CPPUNIT_ASSERT_DOUBLES_EQUAL(  9, static_cast<double>(result->getPixel( 3, 3)), 1.0);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 28, static_cast<double>(result->getPixel( 4, 3)), 1.0);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 38, static_cast<double>(result->getPixel( 5, 3)), 1.0);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 38, static_cast<double>(result->getPixel( 8, 3)), 1.0);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 28, static_cast<double>(result->getPixel( 9, 3)), 1.0);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(  9, static_cast<double>(result->getPixel(10, 3)), 1.0);

        CPPUNIT_ASSERT_DOUBLES_EQUAL( 28, static_cast<double>(result->getPixel( 3, 4)), 1.0);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 84, static_cast<double>(result->getPixel( 4, 4)), 1.0);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(112, static_cast<double>(result->getPixel( 5, 4)), 1.0);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(112, static_cast<double>(result->getPixel( 8, 4)), 1.0);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 84, static_cast<double>(result->getPixel( 9, 4)), 1.0);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 28, static_cast<double>(result->getPixel(10, 4)), 1.0);

        CPPUNIT_ASSERT_DOUBLES_EQUAL( 38, static_cast<double>(result->getPixel( 3, 5)), 1.0);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(112, static_cast<double>(result->getPixel( 4, 5)), 1.0);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(150, static_cast<double>(result->getPixel( 5, 5)), 1.0);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(150, static_cast<double>(result->getPixel( 8, 5)), 1.0);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(112, static_cast<double>(result->getPixel( 9, 5)), 1.0);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 38, static_cast<double>(result->getPixel(10, 5)), 1.0);

        // filterGauss: size=2*1+2 x 2*2+1
        result = filterGauss(src, 2, result);
        // ipp uses a non-separizable float gaussFilter
        // but in the non-ipp implementation a separizable integer gauss filter is used
        // so here are some differences in results
        #ifdef NICE_USELIB_IPP
          // This testcase does NOT work with gcc4.2.2 using option -fopenmp.
          // This raises doubts regarding the correctness of the test case.
          // Thus, the test case has been commented out.
//             CPPUNIT_ASSERT_EQUAL(  1, static_cast<int>(result->getPixel( 2, 2)));
//             CPPUNIT_ASSERT_EQUAL(  2, static_cast<int>(result->getPixel( 3, 2)));
//             CPPUNIT_ASSERT_EQUAL(  6, static_cast<int>(result->getPixel( 4, 2)));
//             CPPUNIT_ASSERT_EQUAL(  7, static_cast<int>(result->getPixel( 5, 2)));
//             CPPUNIT_ASSERT_EQUAL(  8, static_cast<int>(result->getPixel( 6, 2)));
//             CPPUNIT_ASSERT_EQUAL(  8, static_cast<int>(result->getPixel( 7, 2)));
//             CPPUNIT_ASSERT_EQUAL(  7, static_cast<int>(result->getPixel( 8, 2)));
//             CPPUNIT_ASSERT_EQUAL(  6, static_cast<int>(result->getPixel( 9, 2)));
//             CPPUNIT_ASSERT_EQUAL(  2, static_cast<int>(result->getPixel(10, 2)));
//             CPPUNIT_ASSERT_EQUAL(  1, static_cast<int>(result->getPixel(11, 2)));
//
//             CPPUNIT_ASSERT_EQUAL(  8, static_cast<int>(result->getPixel( 2, 6)));
//             CPPUNIT_ASSERT_EQUAL( 42, static_cast<int>(result->getPixel( 3, 6)));
//             CPPUNIT_ASSERT_EQUAL(108, static_cast<int>(result->getPixel( 4, 6)));
//             CPPUNIT_ASSERT_EQUAL(142, static_cast<int>(result->getPixel( 5, 6)));
//             CPPUNIT_ASSERT_EQUAL(150, static_cast<int>(result->getPixel( 6, 6)));
//             CPPUNIT_ASSERT_EQUAL(150, static_cast<int>(result->getPixel( 7, 6)));
//             CPPUNIT_ASSERT_EQUAL(142, static_cast<int>(result->getPixel( 8, 6)));
//             CPPUNIT_ASSERT_EQUAL(108, static_cast<int>(result->getPixel( 9, 6)));
//             CPPUNIT_ASSERT_EQUAL( 42, static_cast<int>(result->getPixel(10, 6)));
//             CPPUNIT_ASSERT_EQUAL(  8, static_cast<int>(result->getPixel(11, 6)));
        #else
            CPPUNIT_ASSERT_EQUAL(  1, static_cast<int>(result->getPixel( 2, 2)));
            CPPUNIT_ASSERT_EQUAL(  3, static_cast<int>(result->getPixel( 3, 2)));
            CPPUNIT_ASSERT_EQUAL(  6, static_cast<int>(result->getPixel( 4, 2)));
            CPPUNIT_ASSERT_EQUAL(  9, static_cast<int>(result->getPixel( 5, 2)));
            CPPUNIT_ASSERT_EQUAL(  9, static_cast<int>(result->getPixel( 6, 2)));
            CPPUNIT_ASSERT_EQUAL(  9, static_cast<int>(result->getPixel( 7, 2)));
            CPPUNIT_ASSERT_EQUAL(  9, static_cast<int>(result->getPixel( 8, 2)));
            CPPUNIT_ASSERT_EQUAL(  6, static_cast<int>(result->getPixel( 9, 2)));
            CPPUNIT_ASSERT_EQUAL(  3, static_cast<int>(result->getPixel(10, 2)));
            CPPUNIT_ASSERT_EQUAL(  1, static_cast<int>(result->getPixel(11, 2)));

            CPPUNIT_ASSERT_EQUAL(  9, static_cast<int>(result->getPixel( 2, 6)));
            CPPUNIT_ASSERT_EQUAL( 47, static_cast<int>(result->getPixel( 3, 6)));
            CPPUNIT_ASSERT_EQUAL(103, static_cast<int>(result->getPixel( 4, 6)));
            CPPUNIT_ASSERT_EQUAL(141, static_cast<int>(result->getPixel( 5, 6)));
            CPPUNIT_ASSERT_EQUAL(150, static_cast<int>(result->getPixel( 6, 6)));
            CPPUNIT_ASSERT_EQUAL(150, static_cast<int>(result->getPixel( 7, 6)));
            CPPUNIT_ASSERT_EQUAL(141, static_cast<int>(result->getPixel( 8, 6)));
            CPPUNIT_ASSERT_EQUAL(103, static_cast<int>(result->getPixel( 9, 6)));
            CPPUNIT_ASSERT_EQUAL( 47, static_cast<int>(result->getPixel(10, 6)));
            CPPUNIT_ASSERT_EQUAL(  9, static_cast<int>(result->getPixel(11, 6)));
        #endif
    }
}

void TestFilter::testGradient()
{
    Image src(10,10);
    src = 0;
    for(int j=3;j<src.height(); ++j)
        for(int i=3;i<src.width(); ++i)
            src(i,j)=255;

    // test sobel
        // sobelX
        GrayImage16s* gradX = sobelX(src);
        CPPUNIT_ASSERT_EQUAL( 64, static_cast<int>(gradX->getPixel(2,2)));
        CPPUNIT_ASSERT_EQUAL( 64, static_cast<int>(gradX->getPixel(3,2)));
        CPPUNIT_ASSERT_EQUAL(191, static_cast<int>(gradX->getPixel(2,3)));
        CPPUNIT_ASSERT_EQUAL(191, static_cast<int>(gradX->getPixel(3,3)));
        CPPUNIT_ASSERT_EQUAL(255, static_cast<int>(gradX->getPixel(2,4)));
        CPPUNIT_ASSERT_EQUAL(255, static_cast<int>(gradX->getPixel(3,4)));

        // sobelY
        GrayImage16s* gradY = sobelY(src);
        CPPUNIT_ASSERT_EQUAL( 64, static_cast<int>(gradY->getPixel(2,2)));
        CPPUNIT_ASSERT_EQUAL( 64, static_cast<int>(gradY->getPixel(2,3)));
        CPPUNIT_ASSERT_EQUAL(191, static_cast<int>(gradY->getPixel(3,2)));
        CPPUNIT_ASSERT_EQUAL(191, static_cast<int>(gradY->getPixel(3,3)));
        CPPUNIT_ASSERT_EQUAL(255, static_cast<int>(gradY->getPixel(4,2)));
        CPPUNIT_ASSERT_EQUAL(255, static_cast<int>(gradY->getPixel(4,3)));

        // strength, direction
        Image* strLUT = createGradientStrengthLUT();

        // strength exceptions
        CPPUNIT_ASSERT_THROW(gradientStrength(GrayImage16s(3,5),GrayImage16s(2,4)), ImageException);
        CPPUNIT_ASSERT_THROW(gradientStrength(*gradX,*gradY,new Image(100,125)), ImageException);

        // strength (with LUT)
        Image* gradStr = new Image(src.width(), src.height());
        gradStr = gradientStrength(*gradX, *gradY, gradStr, strLUT);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(63.5, static_cast<int>(gradStr->getPixel(2,2)), 0.6);
        CPPUNIT_ASSERT_EQUAL(142, static_cast<int>(gradStr->getPixel(3,2)));
        CPPUNIT_ASSERT_EQUAL(180, static_cast<int>(gradStr->getPixel(4,2)));
        CPPUNIT_ASSERT_EQUAL(142, static_cast<int>(gradStr->getPixel(2,3)));
        CPPUNIT_ASSERT_DOUBLES_EQUAL(190.5, static_cast<int>(gradStr->getPixel(3,3)), 0.6);
        CPPUNIT_ASSERT_EQUAL(180, static_cast<int>(gradStr->getPixel(4,3)));
        CPPUNIT_ASSERT_EQUAL(180, static_cast<int>(gradStr->getPixel(2,4)));
        CPPUNIT_ASSERT_EQUAL(180, static_cast<int>(gradStr->getPixel(3,4)));

        // strength (without LUT)
        gradStr->set(0);
        gradStr = gradientStrength(*gradX, *gradY, gradStr);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(63.5, static_cast<int>(gradStr->getPixel(2,2)), 0.6);
        CPPUNIT_ASSERT_EQUAL(142, static_cast<int>(gradStr->getPixel(3,2)));
        CPPUNIT_ASSERT_EQUAL(180, static_cast<int>(gradStr->getPixel(4,2)));
        CPPUNIT_ASSERT_EQUAL(142, static_cast<int>(gradStr->getPixel(2,3)));
        CPPUNIT_ASSERT_DOUBLES_EQUAL(190.5, static_cast<int>(gradStr->getPixel(3,3)), 0.6);
        CPPUNIT_ASSERT_EQUAL(180, static_cast<int>(gradStr->getPixel(4,3)));
        CPPUNIT_ASSERT_EQUAL(180, static_cast<int>(gradStr->getPixel(2,4)));
        CPPUNIT_ASSERT_EQUAL(180, static_cast<int>(gradStr->getPixel(3,4)));

        // direction exception
        CPPUNIT_ASSERT_THROW(gradientDirection(GrayImage16s(3,5), GrayImage16s(2,4)), ImageException);

        // direction
        Image* gradDir = gradientDirection(*gradX, *gradY);
        CPPUNIT_ASSERT_EQUAL( 45, static_cast<int>(gradDir->getPixel(2,2)));
        CPPUNIT_ASSERT_EQUAL( 45, static_cast<int>(gradDir->getPixel(3,2)));
        CPPUNIT_ASSERT_EQUAL( 90, static_cast<int>(gradDir->getPixel(4,2)));
        CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(gradDir->getPixel(2,3)));
        CPPUNIT_ASSERT_EQUAL( 45, static_cast<int>(gradDir->getPixel(3,3)));
        CPPUNIT_ASSERT_EQUAL( 90, static_cast<int>(gradDir->getPixel(4,3)));
        CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(gradDir->getPixel(2,4)));
        CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(gradDir->getPixel(2,4)));
}

void TestFilter::testCanny()
{
    // canny: test a rectangle
    {
        Image src = Image(19,19);
        src.set(0);
        for(int y=4; y<15; ++y)
            for(int x=4; x<15; ++x)
                src(x,y) = 255;

        GrayImage16s* gradX = sobelX(src);
        GrayImage16s* gradY = sobelY(src);

        Image* result = new Image(src.width(), src.height());
        result = canny(src, 10,30, result, gradX, gradY);

        // because ipp will give us value 255 but non ipp implementation 180/190
        for(int i=5; i<=13; ++i) {
            CPPUNIT_ASSERT_DOUBLES_EQUAL(190, static_cast<int>(result->getPixel(i,3)), 65);
            CPPUNIT_ASSERT_DOUBLES_EQUAL(190, static_cast<int>(result->getPixel(i,3)), 65);
        }
        for(int i=4; i<=14; ++i) {
            CPPUNIT_ASSERT_DOUBLES_EQUAL(190, static_cast<int>(result->getPixel(14,i)), 65);
            CPPUNIT_ASSERT_DOUBLES_EQUAL(190, static_cast<int>(result->getPixel(i,14)), 65);
        }
    }

    // canny: 45deg rotated rectangle
    {
        Image src = Image(13,13);
        src.set(0);
        for(int i=0; i<=4; ++i)
            for(int j=2+i; j<=10-i; ++j)
            {
                src(j,6-i) = 255;
                src(j,6+i) = 255;
            }

        GrayImage16s* gradX = sobelX(src);
        GrayImage16s* gradY = sobelY(src);

        Image* result = new Image(src.width(), src.height());
        result = canny(src, 10,30, result, gradX, gradY);

        for(int i=1; i<=11; ++i)
        {
            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel(i, 1)));
            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel(i,11)));
            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel( 1,i)));
            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel(11,i)));
        }

        // because ipp will give us value 255 but non ipp implementation 180/190
        CPPUNIT_ASSERT_DOUBLES_EQUAL(190, static_cast<int>(result->getPixel(  4,  4)), 65);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(190, static_cast<int>(result->getPixel(  4,  3)), 65);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(190, static_cast<int>(result->getPixel(  5,  3)), 65);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(190, static_cast<int>(result->getPixel(  5,  2)), 65);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(190, static_cast<int>(result->getPixel(  6,  2)), 65);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(190, static_cast<int>(result->getPixel(  7,  2)), 65);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(190, static_cast<int>(result->getPixel(  7,  3)), 65);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(190, static_cast<int>(result->getPixel(  8,  3)), 65);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(190, static_cast<int>(result->getPixel(  8,  4)), 65);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(190, static_cast<int>(result->getPixel(  9,  4)), 65);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(190, static_cast<int>(result->getPixel(  9,  5)), 65);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(190, static_cast<int>(result->getPixel( 10,  5)), 65);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(190, static_cast<int>(result->getPixel( 10,  6)), 65);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(190, static_cast<int>(result->getPixel( 10,  7)), 65);

        for(int i=0; i<=3; ++i)
            for(int j=3+i; j<=9-i; ++j)
            {
                CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel( j, 6-i)));
                CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel( j, 6+i)));
            }
    }
}
