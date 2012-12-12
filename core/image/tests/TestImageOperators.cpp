/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libimage - An image/template for new NICE libraries
 * See file License for license information.
 */


#ifdef NICE_USELIB_CPPUNIT
#include "TestImageOperators.h"
#include <string>
#include <exception>
#include <sstream>
#include <iostream>

#ifdef NICE_USELIB_LIMUN_IOCOMPRESSION
    #include <iocompression/md5.h>
#endif

using namespace NICE;
using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION( TestImageOperators );

void TestImageOperators::setUp() {
}

void TestImageOperators::tearDown() {
}

void TestImageOperators::testConstructor() {
}

void TestImageOperators::testOperators()
{
    // inline GrayImage16s operator-(const GrayImage16s& a)
    {
        GrayImage16s img(2,2);
        img(0,0) =  10;
        img(1,0) = -15;
        img(0,1) =   0;
        img(1,1) = -33;
        img = -img;
        CPPUNIT_ASSERT_EQUAL(-10, static_cast<int>(img(0,0)));
        CPPUNIT_ASSERT_EQUAL( 15, static_cast<int>(img(1,0)));
        CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(img(0,1)));
        CPPUNIT_ASSERT_EQUAL( 33, static_cast<int>(img(1,1)));
    }
    // inline FloatImage& operator-=(FloatImage& a, const FloatImage& b)
    {
        FloatImage fimg1(3,3);
        for(int y=0; y<fimg1.height(); ++y)
            for(int x=0; x<fimg1.width(); ++x)
                fimg1(x,y) = (x+1)+y*fimg1.height();

        FloatImage fsub(3,3);
        fsub.set(1.5);
        fimg1 -= fsub;

        for(int y=0; y<fimg1.height(); ++y)
            for(int x=0; x<fimg1.width(); ++x)
                CPPUNIT_ASSERT_DOUBLES_EQUAL((x+1)+y*fimg1.height()-1.5,
                                             static_cast<double>(fimg1.getPixel(x,y)), 0.0);
    }
    // inline const FloatImage operator-(const FloatImage& a, const FloatImage& b)
    {
        FloatImage fimg1(2,2);
        fimg1(0,0) = -15.5;
        fimg1(1,0) =  3.3;
        fimg1(0,1) =  0.25;
        fimg1(1,1) = -1.7;
        FloatImage fimg2(2,2);
        fimg2(0,0) = -1.3;
        fimg2(1,0) = -4.5;
        fimg2(0,1) =  1.1;
        fimg2(1,1) =  0.2;
        FloatImage fres(2,2);
        fres = fimg1-fimg2;
        CPPUNIT_ASSERT_DOUBLES_EQUAL(-14.2, static_cast<double>(fres.getPixel(0,0)), 0.000001);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(  7.8, static_cast<double>(fres.getPixel(1,0)), 0.000001);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(-0.85, static_cast<double>(fres.getPixel(0,1)), 0.000001);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(- 1.9, static_cast<double>(fres.getPixel(1,1)), 0.000001);
    }
    // inline FloatImage& operator-=(FloatImage& a, Ipp32f c)
    {
        FloatImage fimg(3,3);
        for(int y=0; y<fimg.height(); ++y)
            for(int x=0; x<fimg.width(); ++x)
                fimg(x,y) = (x+y+1.0)/2.0;
        fimg -= 0.45;
        for(int y=0; y<fimg.height(); ++y)
            for(int x=0; x<fimg.width(); ++x)
                CPPUNIT_ASSERT_DOUBLES_EQUAL((x+y+1.0)/2.0-0.45, static_cast<double>(fimg(x,y)), 0.000001);
    }
    // inline const FloatImage operator-(const FloatImage& a, Ipp32f c)
    {
        FloatImage fimg(3,3);
        for(int y=0; y<fimg.height(); ++y)
            for(int x=0; x<fimg.width(); ++x)
                fimg(x,y) = (x+y+1.0)/2.0;
        FloatImage fres(3,3);
        fres = fimg - 0.025;
        for(int y=0; y<fimg.height(); ++y)
            for(int x=0; x<fimg.width(); ++x)
                CPPUNIT_ASSERT_DOUBLES_EQUAL(fimg(x,y)-0.025, static_cast<double>(fres(x,y)), 0.000001);
    }
    // inline FloatImage& operator+=(FloatImage& a, const FloatImage& b)
    {
        FloatImage fimg1(3,3), fimg2(3,3);
        for(int y=0; y<fimg1.height(); ++y)
            for(int x=0; x<fimg1.width(); ++x)
            {
                fimg1(x,y) = (x+y+1.0)/2.0;
                fimg2(x,y) = (x+y+1.0)*2.0;
            }
        fimg1 += fimg2;
        for(int y=0; y<fimg1.height(); ++y)
            for(int x=0; x<fimg1.width(); ++x)
                CPPUNIT_ASSERT_DOUBLES_EQUAL((x+y+1)*(5.0/2.0), static_cast<double>(fimg1(x,y)), 0.000001);
    }
    // inline GrayImage16s& operator+=(GrayImage16s& a, const Ipp16s& c)
    {
        GrayImage16s src(3,3);
        src.set(1);

        src += 5;
        for(int y=0; y<src.height(); ++y)
            for(int x=0; x<src.width(); ++x)
                CPPUNIT_ASSERT_EQUAL(6, static_cast<int>(src(x,y)));

        src += (-11);
        for(int y=0; y<src.height(); ++y)
            for(int x=0; x<src.width(); ++x)
                CPPUNIT_ASSERT_EQUAL(-5, static_cast<int>(src(x,y)));

    }
    // inline const FloatImage operator+(const FloatImage& a, const FloatImage& b)
    {
        FloatImage fimg1(3,3), fimg2(3,3);
        for(int y=0; y<fimg1.height(); ++y)
            for(int x=0; x<fimg1.width(); ++x)
            {
                fimg1(x,y) = (x+y+1.0)/2.0;
                fimg2(x,y) = (x+y+1.0)*2.0;
            }
        FloatImage fres = fimg1 + fimg2;
        for(int y=0; y<fimg1.height(); ++y)
            for(int x=0; x<fimg1.width(); ++x)
                CPPUNIT_ASSERT_DOUBLES_EQUAL((x+y+1)*(5.0/2.0), static_cast<double>(fres(x,y)), 0.000001);
    }
    // inline FloatImage& operator+=(FloatImage& a, Ipp32f c)
    {
        FloatImage fimg(3,3);
        for(int y=0; y<fimg.height(); ++y)
            for(int x=0; x<fimg.width(); ++x)
                fimg(x,y) = (x+y+1.0)/2.0;
        fimg += 115.25;
        for(int y=0; y<fimg.height(); ++y)
            for(int x=0; x<fimg.width(); ++x)
                CPPUNIT_ASSERT_DOUBLES_EQUAL((x+y+1.0)/2.0+115.25, static_cast<double>(fimg(x,y)), 0.000001);
    }
    // inline const FloatImage operator+(const FloatImage& a, Ipp32f c)
    {
        FloatImage fimg(3,3);
        for(int y=0; y<fimg.height(); ++y)
            for(int x=0; x<fimg.width(); ++x)
                fimg(x,y) = (x+y+1.0)/2.0;
        FloatImage fres = fimg + 115.25;
        for(int y=0; y<fimg.height(); ++y)
            for(int x=0; x<fimg.width(); ++x)
                CPPUNIT_ASSERT_DOUBLES_EQUAL((x+y+1.0)/2.0+115.25, static_cast<double>(fres(x,y)), 0.000001);
    }
    // inline FloatImage& operator*=(FloatImage& a, const FloatImage& b)
    {
        FloatImage fimg1(5,5), fimg2(5,5);
        for(int y=0; y<fimg1.height(); ++y)
            for(int x=0; x<fimg1.width(); ++x)
            {
                fimg1(x,y) = (x+y+1.0)/2.0;
                fimg2(x,y) = (x+y+1.0)*1.25;
            }
        fimg1 *= fimg2;
        for(int y=0; y<fimg1.height(); ++y)
            for(int x=0; x<fimg1.width(); ++x)
                CPPUNIT_ASSERT_DOUBLES_EQUAL(((x+y+1.0)/2.0)*((x+y+1.0)*1.25),
                                             static_cast<double>(fimg1(x,y)), 0.000001);
    }
    // inline const FloatImage operator*(const FloatImage& a, const FloatImage& b)
    {
        FloatImage fimg1(5,5), fimg2(5,5);
        for(int y=0; y<fimg1.height(); ++y)
            for(int x=0; x<fimg1.width(); ++x)
            {
                fimg1(x,y) = (x+y+1.0)/2.0;
                fimg2(x,y) = (x+y+1.0)*1.25;
            }
        FloatImage fres = fimg1 * fimg2;
        for(int y=0; y<fimg1.height(); ++y)
            for(int x=0; x<fimg1.width(); ++x)
                CPPUNIT_ASSERT_DOUBLES_EQUAL(((x+y+1.0)/2.0)*((x+y+1.0)*1.25),
                                             static_cast<double>(fres(x,y)), 0.000001);
    }
    // inline FloatImage& operator*=(FloatImage& a, Ipp32f c)
    {
        FloatImage fimg(5,5);
        for(int y=0; y<fimg.height(); ++y)
            for(int x=0; x<fimg.width(); ++x)
                fimg(x,y) = (x+y+1.0)/2.0;
        fimg *= 2.0;
        for(int y=0; y<fimg.height(); ++y)
            for(int x=0; x<fimg.width(); ++x)
                CPPUNIT_ASSERT_DOUBLES_EQUAL(x+y+1.0, static_cast<double>(fimg(x,y)), 0.000001);
    }
    // inline Image operator*=(Image& a, Ipp8u c)
    {
        Image gimg(5,5);
        for(int y=0; y<gimg.height(); ++y)
            for(int x=0; x<gimg.width(); ++x)
                gimg(x,y) = x+y+1;
        gimg *= 2;
        for(int y=0; y<gimg.height(); ++y)
            for(int x=0; x<gimg.width(); ++x)
                CPPUNIT_ASSERT_EQUAL((x+y+1)*2, static_cast<int>(gimg(x,y)));
    }
    // inline const FloatImage operator*(const FloatImage& a, Ipp32f c)
     {
        FloatImage fimg(5,5);
        for(int y=0; y<fimg.height(); ++y)
            for(int x=0; x<fimg.width(); ++x)
                fimg(x,y) = (x+y+1.0)/2.0;
        FloatImage fres = fimg * 2.0;
        for(int y=0; y<fimg.height(); ++y)
            for(int x=0; x<fimg.width(); ++x)
                CPPUNIT_ASSERT_DOUBLES_EQUAL(x+y+1.0, static_cast<double>(fres(x,y)), 0.000001);
    }
    // inline const Image operator*(const Image& a, Ipp8u c)
    {
        Image gimg(5,5);
        for(int y=0; y<gimg.height(); ++y)
            for(int x=0; x<gimg.width(); ++x)
                gimg(x,y) = x+y+1;
        Image gres = gimg * 2;
        for(int y=0; y<gimg.height(); ++y)
            for(int x=0; x<gimg.width(); ++x)
                CPPUNIT_ASSERT_EQUAL((x+y+1)*2, static_cast<int>(gres(x,y)));
    }
    // inline FloatImage& operator/=(FloatImage& a, const FloatImage& b)
    {
        FloatImage fimg1(5,5), fimg2(5,5);
        for(int y=0; y<fimg1.height(); ++y)
            for(int x=0; x<fimg1.width(); ++x)
            {
                fimg1(x,y) = (x+y+1.0)*2.0;
                fimg2(x,y) = (x+y+1.0);
            }
        fimg1 /= fimg2;
        for(int y=0; y<fimg1.height(); ++y)
            for(int x=0; x<fimg1.width(); ++x)
                CPPUNIT_ASSERT_DOUBLES_EQUAL(2, static_cast<double>(fimg1(x,y)), 0.000001);
    }
    // inline const FloatImage operator/(const FloatImage& a, const FloatImage& b)
    {
        FloatImage fimg1(5,5), fimg2(5,5);
        for(int y=0; y<fimg1.height(); ++y)
            for(int x=0; x<fimg1.width(); ++x)
            {
                fimg1(x,y) = (x+y+1.0)*2.0;
                fimg2(x,y) = (x+y+1.0);
            }
        FloatImage fres = fimg1 / fimg2;
        for(int y=0; y<fimg1.height(); ++y)
            for(int x=0; x<fimg1.width(); ++x)
                CPPUNIT_ASSERT_DOUBLES_EQUAL(2, static_cast<double>(fres(x,y)), 0.000001);
    }
    // inline FloatImage& operator/=(FloatImage& a, Ipp32f c)
    {
        FloatImage fimg(5,5);
        for(int y=0; y<fimg.height(); ++y)
            for(int x=0; x<fimg.width(); ++x)
                fimg(x,y) = (x+y+1.0)*2.0;
        fimg /= 2.0;
        for(int y=0; y<fimg.height(); ++y)
            for(int x=0; x<fimg.width(); ++x)
                CPPUNIT_ASSERT_DOUBLES_EQUAL(x+y+1.0, static_cast<double>(fimg(x,y)), 0.000001);
    }
    // inline const FloatImage operator/(const FloatImage& a, Ipp32f c)
    {
        FloatImage fimg(5,5);
        for(int y=0; y<fimg.height(); ++y)
            for(int x=0; x<fimg.width(); ++x)
                fimg(x,y) = (x+y+1.0)*2.0;
        FloatImage fres = fimg / 2.0;
        for(int y=0; y<fimg.height(); ++y)
            for(int x=0; x<fimg.width(); ++x)
                CPPUNIT_ASSERT_DOUBLES_EQUAL(x+y+1.0, static_cast<double>(fres(x,y)), 0.000001);
    }
}


#endif
