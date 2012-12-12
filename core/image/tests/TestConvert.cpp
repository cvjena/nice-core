
#include "TestConvert.h"
#include <string>

using namespace std;
using namespace NICE;

CPPUNIT_TEST_SUITE_REGISTRATION( TestConvert );

void TestConvert::setUp()
{
}

void TestConvert::tearDown()
{
}

void TestConvert::testColorspaceConversion()
{
    ColorImage src(9,1);
    src.setPixelQuick( 0, 0,   0,   0,   0);
    src.setPixelQuick( 1, 0, 255, 255, 255);
    src.setPixelQuick( 2, 0, 255,   0,   0);
    src.setPixelQuick( 3, 0, 255, 255,   0);
    src.setPixelQuick( 4, 0,   0, 255,   0);
    src.setPixelQuick( 5, 0,   0, 255, 255);
    src.setPixelQuick( 6, 0,   0,   0, 255);
    src.setPixelQuick( 7, 0, 255,   0, 255);
    src.setPixelQuick( 8, 0, 255,   0,   0);

    // rgbToHSV, HSVToRGB
    {
        // rgbToHSV
        ColorImage* result = rgbToHSV(src);

        // H
        CPPUNIT_ASSERT_DOUBLES_EQUAL(   0, static_cast<double>(result->getPixelQuick(0,0,0)), 1); // R=G=B -> H undef.
        CPPUNIT_ASSERT_DOUBLES_EQUAL(   0, static_cast<double>(result->getPixelQuick(1,0,0)), 1); // R=G=B -> H undef.
        CPPUNIT_ASSERT_DOUBLES_EQUAL(   0, static_cast<double>(result->getPixelQuick(2,0,0)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(  42, static_cast<double>(result->getPixelQuick(3,0,0)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(  85, static_cast<double>(result->getPixelQuick(4,0,0)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 127, static_cast<double>(result->getPixelQuick(5,0,0)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 170, static_cast<double>(result->getPixelQuick(6,0,0)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 212, static_cast<double>(result->getPixelQuick(7,0,0)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(   0, static_cast<double>(result->getPixelQuick(8,0,0)), 1);
        // S
        CPPUNIT_ASSERT_DOUBLES_EQUAL(   0, static_cast<double>(result->getPixelQuick(0,0,1)), 1); // R=G=B=0 -> S undef.
        CPPUNIT_ASSERT_DOUBLES_EQUAL(   0, static_cast<double>(result->getPixelQuick(1,0,1)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 254, static_cast<double>(result->getPixelQuick(2,0,1)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 254, static_cast<double>(result->getPixelQuick(3,0,1)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 254, static_cast<double>(result->getPixelQuick(4,0,1)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 254, static_cast<double>(result->getPixelQuick(5,0,1)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 254, static_cast<double>(result->getPixelQuick(6,0,1)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 254, static_cast<double>(result->getPixelQuick(7,0,1)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 255, static_cast<double>(result->getPixelQuick(8,0,1)), 1);
        // V
        CPPUNIT_ASSERT_DOUBLES_EQUAL(   0, static_cast<double>(result->getPixelQuick(0,0,2)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 255, static_cast<double>(result->getPixelQuick(1,0,2)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 255, static_cast<double>(result->getPixelQuick(2,0,2)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 255, static_cast<double>(result->getPixelQuick(3,0,2)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 255, static_cast<double>(result->getPixelQuick(4,0,2)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 255, static_cast<double>(result->getPixelQuick(5,0,2)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 255, static_cast<double>(result->getPixelQuick(6,0,2)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 255, static_cast<double>(result->getPixelQuick(7,0,2)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 255, static_cast<double>(result->getPixelQuick(8,0,2)), 1);

        // hsvToRGB
        ColorImage* result2 = hsvToRGB(*result);

        // R
        CPPUNIT_ASSERT_DOUBLES_EQUAL(   0, static_cast<double>(result2->getPixelQuick(0,0,0)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 255, static_cast<double>(result2->getPixelQuick(1,0,0)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 255, static_cast<double>(result2->getPixelQuick(2,0,0)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 255, static_cast<double>(result2->getPixelQuick(3,0,0)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(   0, static_cast<double>(result2->getPixelQuick(4,0,0)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(   0, static_cast<double>(result2->getPixelQuick(5,0,0)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(   1, static_cast<double>(result2->getPixelQuick(6,0,0)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 252, static_cast<double>(result2->getPixelQuick(7,0,0)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 255, static_cast<double>(result2->getPixelQuick(8,0,0)), 1);
        // G
        CPPUNIT_ASSERT_DOUBLES_EQUAL(   0, static_cast<double>(result2->getPixelQuick(0,0,1)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 255, static_cast<double>(result2->getPixelQuick(1,0,1)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(   0, static_cast<double>(result2->getPixelQuick(2,0,1)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 252, static_cast<double>(result2->getPixelQuick(3,0,1)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 255, static_cast<double>(result2->getPixelQuick(4,0,1)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 255, static_cast<double>(result2->getPixelQuick(5,0,1)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(   0, static_cast<double>(result2->getPixelQuick(6,0,1)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(   0, static_cast<double>(result2->getPixelQuick(7,0,1)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(   0, static_cast<double>(result2->getPixelQuick(8,0,1)), 1);
        // B
        CPPUNIT_ASSERT_DOUBLES_EQUAL(   0, static_cast<double>(result2->getPixelQuick(0,0,2)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 255, static_cast<double>(result2->getPixelQuick(1,0,2)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(   0, static_cast<double>(result2->getPixelQuick(2,0,2)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(   0, static_cast<double>(result2->getPixelQuick(3,0,2)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(   1, static_cast<double>(result2->getPixelQuick(4,0,2)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 252, static_cast<double>(result2->getPixelQuick(5,0,2)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 255, static_cast<double>(result2->getPixelQuick(6,0,2)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 255, static_cast<double>(result2->getPixelQuick(7,0,2)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(   0, static_cast<double>(result2->getPixelQuick(8,0,2)), 1);
    }

    // rgbToYUV, yuvToRGB
    {
        // rgbToYUV
        ColorImage* result  = rgbToYUV(src);

        // Y
        CPPUNIT_ASSERT_DOUBLES_EQUAL(   0, static_cast<double>(result->getPixelQuick(0,0,0)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 254, static_cast<double>(result->getPixelQuick(1,0,0)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(  76, static_cast<double>(result->getPixelQuick(2,0,0)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 225, static_cast<double>(result->getPixelQuick(3,0,0)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 149, static_cast<double>(result->getPixelQuick(4,0,0)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 178, static_cast<double>(result->getPixelQuick(5,0,0)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(  29, static_cast<double>(result->getPixelQuick(6,0,0)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 105, static_cast<double>(result->getPixelQuick(7,0,0)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(  76, static_cast<double>(result->getPixelQuick(8,0,0)), 1);

        // U
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 128, static_cast<double>(result->getPixelQuick(0,0,1)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 128, static_cast<double>(result->getPixelQuick(1,0,1)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(  90, static_cast<double>(result->getPixelQuick(2,0,1)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(  17, static_cast<double>(result->getPixelQuick(3,0,1)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(  54, static_cast<double>(result->getPixelQuick(4,0,1)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 165, static_cast<double>(result->getPixelQuick(5,0,1)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 239, static_cast<double>(result->getPixelQuick(6,0,1)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 201, static_cast<double>(result->getPixelQuick(7,0,1)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(  90, static_cast<double>(result->getPixelQuick(8,0,1)), 1);

        // V
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 128, static_cast<double>(result->getPixelQuick(0,0,2)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 128, static_cast<double>(result->getPixelQuick(1,0,2)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 255, static_cast<double>(result->getPixelQuick(2,0,2)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 153, static_cast<double>(result->getPixelQuick(3,0,2)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(   0, static_cast<double>(result->getPixelQuick(4,0,2)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(   0, static_cast<double>(result->getPixelQuick(5,0,2)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 102, static_cast<double>(result->getPixelQuick(6,0,2)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 255, static_cast<double>(result->getPixelQuick(7,0,2)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 255, static_cast<double>(result->getPixelQuick(8,0,2)), 1);

        // yuvToRGB
        ColorImage* result2 = yuvToRGB(*result);

        // R
        CPPUNIT_ASSERT_DOUBLES_EQUAL(   0, static_cast<double>(result2->getPixelQuick(0,0,0)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 254, static_cast<double>(result2->getPixelQuick(1,0,0)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 220, static_cast<double>(result2->getPixelQuick(2,0,0)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 253, static_cast<double>(result2->getPixelQuick(3,0,0)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(   3, static_cast<double>(result2->getPixelQuick(4,0,0)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(  32, static_cast<double>(result2->getPixelQuick(5,0,0)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(   0, static_cast<double>(result2->getPixelQuick(6,0,0)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 249, static_cast<double>(result2->getPixelQuick(7,0,0)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 220, static_cast<double>(result2->getPixelQuick(8,0,0)), 1);

        // G
        CPPUNIT_ASSERT_DOUBLES_EQUAL(   0, static_cast<double>(result2->getPixelQuick(0,0,1)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 254, static_cast<double>(result2->getPixelQuick(1,0,1)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(  16, static_cast<double>(result2->getPixelQuick(2,0,1)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 253, static_cast<double>(result2->getPixelQuick(3,0,1)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 252, static_cast<double>(result2->getPixelQuick(4,0,1)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 237, static_cast<double>(result2->getPixelQuick(5,0,1)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(   0, static_cast<double>(result2->getPixelQuick(6,0,1)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(   2, static_cast<double>(result2->getPixelQuick(7,0,1)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(  16, static_cast<double>(result2->getPixelQuick(8,0,1)), 1);

        // B
        CPPUNIT_ASSERT_DOUBLES_EQUAL(   0, static_cast<double>(result2->getPixelQuick(0,0,2)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 253, static_cast<double>(result2->getPixelQuick(1,0,2)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(   0, static_cast<double>(result2->getPixelQuick(2,0,2)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(   0, static_cast<double>(result2->getPixelQuick(3,0,2)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(   0, static_cast<double>(result2->getPixelQuick(4,0,2)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 253, static_cast<double>(result2->getPixelQuick(5,0,2)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 254, static_cast<double>(result2->getPixelQuick(6,0,2)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 253, static_cast<double>(result2->getPixelQuick(7,0,2)), 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(   0, static_cast<double>(result2->getPixelQuick(8,0,2)), 1);
    }
}

void TestConvert::testImageConversion()
{
    // rgbToGray
    {
        // Ipp8u
        {
            ColorImage src(13,1);
            src.setPixelQuick( 0,0,   0,  0,  0);
            src.setPixelQuick( 1,0, 255,  0,  0);
            src.setPixelQuick( 2,0,   0,255,  0);
            src.setPixelQuick( 3,0,   0,  0,255);
            src.setPixelQuick( 4,0, 255,255,  0);
            src.setPixelQuick( 5,0,   0,255,255);
            src.setPixelQuick( 6,0, 255,  0,255);
            src.setPixelQuick( 7,0, 255,255,255);
            src.setPixelQuick( 8,0, 100,100,100);
            src.setPixelQuick( 9,0, 150,150,150);
            src.setPixelQuick(10,0, 128,  0,  0);
            src.setPixelQuick(11,0,   0,128,  0);
            src.setPixelQuick(12,0,   0,  0,128);

            Image* result = rgbToGray(src);

            CPPUNIT_ASSERT_DOUBLES_EQUAL(   0, static_cast<double>(result->getPixelQuick( 0,0)), 1);
            CPPUNIT_ASSERT_DOUBLES_EQUAL(  76, static_cast<double>(result->getPixelQuick( 1,0)), 1);
            CPPUNIT_ASSERT_DOUBLES_EQUAL( 149, static_cast<double>(result->getPixelQuick( 2,0)), 1);
            CPPUNIT_ASSERT_DOUBLES_EQUAL(  29, static_cast<double>(result->getPixelQuick( 3,0)), 1);
            CPPUNIT_ASSERT_DOUBLES_EQUAL( 225, static_cast<double>(result->getPixelQuick( 4,0)), 1);
            CPPUNIT_ASSERT_DOUBLES_EQUAL( 178, static_cast<double>(result->getPixelQuick( 5,0)), 1);
            CPPUNIT_ASSERT_DOUBLES_EQUAL( 105, static_cast<double>(result->getPixelQuick( 6,0)), 1);
            CPPUNIT_ASSERT_DOUBLES_EQUAL( 254, static_cast<double>(result->getPixelQuick( 7,0)), 1);
            CPPUNIT_ASSERT_DOUBLES_EQUAL(  99, static_cast<double>(result->getPixelQuick( 8,0)), 1);
            CPPUNIT_ASSERT_DOUBLES_EQUAL( 149, static_cast<double>(result->getPixelQuick( 9,0)), 1);
            CPPUNIT_ASSERT_DOUBLES_EQUAL(  38, static_cast<double>(result->getPixelQuick(10,0)), 1);
            CPPUNIT_ASSERT_DOUBLES_EQUAL(  75, static_cast<double>(result->getPixelQuick(11,0)), 1);
            CPPUNIT_ASSERT_DOUBLES_EQUAL(  14, static_cast<double>(result->getPixelQuick(12,0)), 1);

            // test again with optional lut
            ImageT<int>* lut = rgbToGrayLUT();

            CPPUNIT_ASSERT_EQUAL(256, static_cast<int>(lut->width()));
            CPPUNIT_ASSERT_EQUAL(  3, static_cast<int>(lut->height()));

            Image* result2 = new Image(src.width(), src.height());
            CPPUNIT_ASSERT_EQUAL(src.width() , static_cast<int>(result2->width()));
            CPPUNIT_ASSERT_EQUAL(src.height(), static_cast<int>(result2->height()));

            result2            = rgbToGray(src, result2, lut);
            for(int i=0; i<=12; ++i)
                CPPUNIT_ASSERT_DOUBLES_EQUAL( static_cast<int>(result->getPixelQuick(i,0)),
                                              static_cast<int>(result2->getPixelQuick(i,0)), 1);
        }

        // Ipp32f
        {
            ColorImageT<Ipp32f> src(13,1);
            src.setPixelQuick( 0,0,   0,  0,  0);
            src.setPixelQuick( 1,0, 255,  0,  0);
            src.setPixelQuick( 2,0,   0,255,  0);
            src.setPixelQuick( 3,0,   0,  0,255);
            src.setPixelQuick( 4,0, 255,255,  0);
            src.setPixelQuick( 5,0,   0,255,255);
            src.setPixelQuick( 6,0, 255,  0,255);
            src.setPixelQuick( 7,0, 255,255,255);
            src.setPixelQuick( 8,0, 100,100,100);
            src.setPixelQuick( 9,0, 150,150,150);
            src.setPixelQuick(10,0, 128,  0,  0);
            src.setPixelQuick(11,0,   0,128,  0);
            src.setPixelQuick(12,0,   0,  0,128);

            FloatImage* result = rgbToGray(src);
            CPPUNIT_ASSERT_DOUBLES_EQUAL(   0.0000, static_cast<double>(result->getPixelQuick( 0,0)),0.0001);
            CPPUNIT_ASSERT_DOUBLES_EQUAL(  76.2450, static_cast<double>(result->getPixelQuick( 1,0)),0.0001);
            CPPUNIT_ASSERT_DOUBLES_EQUAL( 149.6850, static_cast<double>(result->getPixelQuick( 2,0)),0.0001);
            CPPUNIT_ASSERT_DOUBLES_EQUAL(  29.0700, static_cast<double>(result->getPixelQuick( 3,0)),0.0001);
            CPPUNIT_ASSERT_DOUBLES_EQUAL( 225.9300, static_cast<double>(result->getPixelQuick( 4,0)),0.0001);
            CPPUNIT_ASSERT_DOUBLES_EQUAL( 178.7550, static_cast<double>(result->getPixelQuick( 5,0)),0.0001);
            CPPUNIT_ASSERT_DOUBLES_EQUAL( 105.3150, static_cast<double>(result->getPixelQuick( 6,0)),0.0001);
            CPPUNIT_ASSERT_DOUBLES_EQUAL( 255.0000, static_cast<double>(result->getPixelQuick( 7,0)),0.0001);
            CPPUNIT_ASSERT_DOUBLES_EQUAL( 100.0000, static_cast<double>(result->getPixelQuick( 8,0)),0.0001);
            CPPUNIT_ASSERT_DOUBLES_EQUAL( 150.0000, static_cast<double>(result->getPixelQuick( 9,0)),0.0001);
            CPPUNIT_ASSERT_DOUBLES_EQUAL(  38.2720, static_cast<double>(result->getPixelQuick(10,0)),0.0001);
            CPPUNIT_ASSERT_DOUBLES_EQUAL(  75.1360, static_cast<double>(result->getPixelQuick(11,0)),0.0001);
            CPPUNIT_ASSERT_DOUBLES_EQUAL(  14.5920, static_cast<double>(result->getPixelQuick(12,0)),0.0001);
        }

    }

    // grayToRGB
    {
        // Ipp8u
        {
            Image src(256,1);
            for(int i=0; i<src.width(); ++i)
                src(i,0) = i;

            ColorImage* result = grayToRGB(src);

            for(int i=0; i<src.width(); ++i)
                for(int c=0; c<3; ++c)
                    CPPUNIT_ASSERT_EQUAL(i, static_cast<int>(result->getPixelQuick(i,0,c)));
        }
        // Ipp32f
        {
            FloatImage src(255*3,1);
            for(int i=0; i<src.width(); ++i)
                src.setPixelQuick(i,0,i/3.0);

            ColorImageT<Ipp32f>* result = grayToRGB(src);

            for(int i=0; i<result->width(); ++i)
                for(int c=0; c<3; ++c)
                    CPPUNIT_ASSERT_DOUBLES_EQUAL(static_cast<double>(i/3.0),
                                                 static_cast<double>(result->getPixelQuick(i,0,c)), 0.0001);
        }
    }
}

void TestConvert::testGrayFloat()
{
    // grayToFloat
    {
        // Ipp8u
        {
            Image src(256,1);
            for(int i=0; i<src.width(); ++i)
                src.setPixelQuick(i,0,i);

            FloatImage* result = grayToFloat(src);

            for(int i=0; i<src.width(); ++i)
                CPPUNIT_ASSERT_DOUBLES_EQUAL(static_cast<double>(i),
                                             static_cast<double>(result->getPixelQuick(i,0)), 0.0001);
        }

        // Ipp8s
        {
            ImageT<Ipp8s> src(256,1);
            for(int i=0; i<src.width(); ++i)
                src.setPixelQuick(i,0,std::numeric_limits<Ipp8s>::min()+i);

            FloatImage* result = grayToFloat(src);

            for(int i=0; i<src.width(); ++i)
                CPPUNIT_ASSERT_EQUAL(std::numeric_limits<Ipp8s>::min()+i,
                                     static_cast<int>(result->getPixelQuick(i,0)));
        }

        // Ipp16s
        {
            ImageT<Ipp16s> src(2,1);
            src.setPixelQuick(0,0, std::numeric_limits<Ipp16s>::min());
            src.setPixelQuick(1,0, std::numeric_limits<Ipp16s>::max());

            FloatImage* result = grayToFloat(src);

            CPPUNIT_ASSERT_EQUAL(static_cast<int>(std::numeric_limits<Ipp16s>::min()),
                                 static_cast<int>(result->getPixelQuick(0,0)));
            CPPUNIT_ASSERT_EQUAL(static_cast<int>(std::numeric_limits<Ipp16s>::max()),
                                 static_cast<int>(result->getPixelQuick(1,0)));
        }
    }

    // floatToGray
    {
        FloatImage src(200,1);

        src(100,0) = 1.652312;

        for(int i=1; i<100; ++i) {
            src(100-i,0) = src(100,0)*src(100-i+1,0)*(src(100-i+1,0)<0?1:-1);
            src(100+i,0) = src(100,0)*src(100+i-1,0);
        }

         // Ipp8u
        {
            Image* result = new Image(src.width(), src.height());
            result            = floatToGray(src, result);

            for(int i=1; i<=99; ++i)
                CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixelQuick(i,0)));

            CPPUNIT_ASSERT_EQUAL(  2, static_cast<int>(result->getPixelQuick(100,0)));
            CPPUNIT_ASSERT_EQUAL(  3, static_cast<int>(result->getPixelQuick(101,0)));
            CPPUNIT_ASSERT_EQUAL(  5, static_cast<int>(result->getPixelQuick(102,0)));
            CPPUNIT_ASSERT_EQUAL(  7, static_cast<int>(result->getPixelQuick(103,0)));
            CPPUNIT_ASSERT_EQUAL( 12, static_cast<int>(result->getPixelQuick(104,0)));
            CPPUNIT_ASSERT_EQUAL( 20, static_cast<int>(result->getPixelQuick(105,0)));
            CPPUNIT_ASSERT_EQUAL( 34, static_cast<int>(result->getPixelQuick(106,0)));
            CPPUNIT_ASSERT_EQUAL( 56, static_cast<int>(result->getPixelQuick(107,0)));
            CPPUNIT_ASSERT_EQUAL( 92, static_cast<int>(result->getPixelQuick(108,0)));
            CPPUNIT_ASSERT_EQUAL(152, static_cast<int>(result->getPixelQuick(109,0)));
            CPPUNIT_ASSERT_EQUAL(251, static_cast<int>(result->getPixelQuick(110,0)));

            for(int i=111; i<src.width(); ++i)
                CPPUNIT_ASSERT_EQUAL(255, static_cast<int>(result->getPixelQuick(i,0)));
        }

        // Ipp8s
        {
            ImageT<Ipp8s>* result = new ImageT<Ipp8s>(src.width(), src.height());
            result                    = floatToGray(src, result);

            for(int i=1; i<=91; ++i)
                CPPUNIT_ASSERT_EQUAL(-128, static_cast<int>(result->getPixelQuick(i,0)));

            CPPUNIT_ASSERT_EQUAL(-92, static_cast<int>(result->getPixelQuick( 92,0)));
            CPPUNIT_ASSERT_EQUAL(-34, static_cast<int>(result->getPixelQuick( 94,0)));
            CPPUNIT_ASSERT_EQUAL(-12, static_cast<int>(result->getPixelQuick( 96,0)));
            CPPUNIT_ASSERT_EQUAL(- 5, static_cast<int>(result->getPixelQuick( 98,0)));
            CPPUNIT_ASSERT_EQUAL(  2, static_cast<int>(result->getPixelQuick(100,0)));
            CPPUNIT_ASSERT_EQUAL(  5, static_cast<int>(result->getPixelQuick(102,0)));
            CPPUNIT_ASSERT_EQUAL( 12, static_cast<int>(result->getPixelQuick(104,0)));
            CPPUNIT_ASSERT_EQUAL( 34, static_cast<int>(result->getPixelQuick(106,0)));
            CPPUNIT_ASSERT_EQUAL( 92, static_cast<int>(result->getPixelQuick(108,0)));

            for(int i=109; i<src.width(); ++i)
                CPPUNIT_ASSERT_EQUAL( 127, static_cast<int>(result->getPixelQuick(i,0)));
        }

        // Ipp16s
        {
            ImageT<Ipp16s>* result = new ImageT<Ipp16s>(src.width(), src.height());
            result                     = floatToGray(src, result);

            for(int i=1; i<=80; ++i)
                CPPUNIT_ASSERT_EQUAL(-32768, static_cast<int>(result->getPixelQuick(i,0)));

            CPPUNIT_ASSERT_EQUAL(-13924, static_cast<int>(result->getPixelQuick( 82,0)));
            CPPUNIT_ASSERT_EQUAL(- 5100, static_cast<int>(result->getPixelQuick( 84,0)));
            CPPUNIT_ASSERT_EQUAL(- 1868, static_cast<int>(result->getPixelQuick( 86,0)));
            CPPUNIT_ASSERT_EQUAL(-  684, static_cast<int>(result->getPixelQuick( 88,0)));
            CPPUNIT_ASSERT_EQUAL(-  251, static_cast<int>(result->getPixelQuick( 90,0)));
            CPPUNIT_ASSERT_EQUAL(   414, static_cast<int>(result->getPixelQuick(111,0)));
            CPPUNIT_ASSERT_EQUAL(  1131, static_cast<int>(result->getPixelQuick(113,0)));
            CPPUNIT_ASSERT_EQUAL(  3087, static_cast<int>(result->getPixelQuick(115,0)));
            CPPUNIT_ASSERT_EQUAL(  8427, static_cast<int>(result->getPixelQuick(117,0)));
            CPPUNIT_ASSERT_EQUAL( 23006, static_cast<int>(result->getPixelQuick(119,0)));

            for(int i=120; i<src.width(); ++i)
                CPPUNIT_ASSERT_EQUAL(+32767, static_cast<int>(result->getPixelQuick(i,0)));
        }
    }
}

void TestConvert::testRGBFloat()
{
    ColorImage src(3,2);
    src.setPixelQuick(0,0,  1,  2,  3);
    src.setPixelQuick(1,0,  5, 10, 15);
    src.setPixelQuick(2,0,100,150,200);
    src.setPixelQuick(0,1,111,112,113);
    src.setPixelQuick(1,1,  0,  0,  0);
    src.setPixelQuick(2,1,255,  0,255);

    FloatImage* result = rgbToFloat(src);

    CPPUNIT_ASSERT_EQUAL(  1, static_cast<int>(result->getPixelQuick(0,0)));
    CPPUNIT_ASSERT_EQUAL(  2, static_cast<int>(result->getPixelQuick(1,0)));
    CPPUNIT_ASSERT_EQUAL(  3, static_cast<int>(result->getPixelQuick(2,0)));
    CPPUNIT_ASSERT_EQUAL(  5, static_cast<int>(result->getPixelQuick(3,0)));
    CPPUNIT_ASSERT_EQUAL( 10, static_cast<int>(result->getPixelQuick(4,0)));
    CPPUNIT_ASSERT_EQUAL( 15, static_cast<int>(result->getPixelQuick(5,0)));
    CPPUNIT_ASSERT_EQUAL(100, static_cast<int>(result->getPixelQuick(6,0)));
    CPPUNIT_ASSERT_EQUAL(150, static_cast<int>(result->getPixelQuick(7,0)));
    CPPUNIT_ASSERT_EQUAL(200, static_cast<int>(result->getPixelQuick(8,0)));
    CPPUNIT_ASSERT_EQUAL(111, static_cast<int>(result->getPixelQuick(0,1)));
    CPPUNIT_ASSERT_EQUAL(112, static_cast<int>(result->getPixelQuick(1,1)));
    CPPUNIT_ASSERT_EQUAL(113, static_cast<int>(result->getPixelQuick(2,1)));
    CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixelQuick(3,1)));
    CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixelQuick(4,1)));
    CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixelQuick(5,1)));
    CPPUNIT_ASSERT_EQUAL(255, static_cast<int>(result->getPixelQuick(6,1)));
    CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixelQuick(7,1)));
    CPPUNIT_ASSERT_EQUAL(255, static_cast<int>(result->getPixelQuick(8,1)));
}

void TestConvert::testconvertBitDepth()
{
    // gray images
    {
        // Ipp8u -> Ipp16u/Ipp16s/Ipp32s//32f
        {
            ImageT<Ipp8u> src(3,2);
            src(0,0) =   5; src(1,0) =  10; src(2,0) =  15;
            src(0,1) = 100; src(1,1) =   0; src(2,1) = 255;

            ImageT<Ipp16u>* result = new ImageT<Ipp16u>(src.width(), src.height());
            result                     = convertBitDepth(src, result);

            CPPUNIT_ASSERT_EQUAL(  5, static_cast<int>(result->getPixelQuick(0,0)));
            CPPUNIT_ASSERT_EQUAL( 10, static_cast<int>(result->getPixelQuick(1,0)));
            CPPUNIT_ASSERT_EQUAL( 15, static_cast<int>(result->getPixelQuick(2,0)));
            CPPUNIT_ASSERT_EQUAL(100, static_cast<int>(result->getPixelQuick(0,1)));
            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixelQuick(1,1)));
            CPPUNIT_ASSERT_EQUAL(255, static_cast<int>(result->getPixelQuick(2,1)));

            ImageT<Ipp16s>* result2 = new ImageT<Ipp16s>(src.width(), src.height());
            result2                     = convertBitDepth(src, result2);

            CPPUNIT_ASSERT_EQUAL(  5, static_cast<int>(result2->getPixelQuick(0,0)));
            CPPUNIT_ASSERT_EQUAL( 10, static_cast<int>(result2->getPixelQuick(1,0)));
            CPPUNIT_ASSERT_EQUAL( 15, static_cast<int>(result2->getPixelQuick(2,0)));
            CPPUNIT_ASSERT_EQUAL(100, static_cast<int>(result2->getPixelQuick(0,1)));
            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result2->getPixelQuick(1,1)));
            CPPUNIT_ASSERT_EQUAL(255, static_cast<int>(result2->getPixelQuick(2,1)));

            ImageT<Ipp32s>* result3 = new ImageT<Ipp32s>(src.width(), src.height());
            result3                     = convertBitDepth(src, result3);

            CPPUNIT_ASSERT_EQUAL(  5, static_cast<int>(result3->getPixelQuick(0,0)));
            CPPUNIT_ASSERT_EQUAL( 10, static_cast<int>(result3->getPixelQuick(1,0)));
            CPPUNIT_ASSERT_EQUAL( 15, static_cast<int>(result3->getPixelQuick(2,0)));
            CPPUNIT_ASSERT_EQUAL(100, static_cast<int>(result3->getPixelQuick(0,1)));
            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result3->getPixelQuick(1,1)));
            CPPUNIT_ASSERT_EQUAL(255, static_cast<int>(result3->getPixelQuick(2,1)));

            ImageT<Ipp32f>* result4 = new ImageT<Ipp32f>(src.width(), src.height());
            result4                     = convertBitDepth(src, result4);

            CPPUNIT_ASSERT_EQUAL(  5, static_cast<int>(result4->getPixelQuick(0,0)));
            CPPUNIT_ASSERT_EQUAL( 10, static_cast<int>(result4->getPixelQuick(1,0)));
            CPPUNIT_ASSERT_EQUAL( 15, static_cast<int>(result4->getPixelQuick(2,0)));
            CPPUNIT_ASSERT_EQUAL(100, static_cast<int>(result4->getPixelQuick(0,1)));
            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result4->getPixelQuick(1,1)));
            CPPUNIT_ASSERT_EQUAL(255, static_cast<int>(result4->getPixelQuick(2,1)));
        }

        //8s to 32s//32f
        {
            ImageT<Ipp8s> src(3,1);
            src(0,0) = 0;
            src(1,0) = std::numeric_limits<Ipp8s>::min();
            src(2,0) = std::numeric_limits<Ipp8s>::max();

            ImageT<Ipp32s>* result = new ImageT<Ipp32s>(src.width(), src.height());
            result                     = convertBitDepth(src, result);

            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixelQuick(0,0)));
            CPPUNIT_ASSERT_EQUAL(static_cast<int>(std::numeric_limits<Ipp8s>::min()),
                                 static_cast<int>(result->getPixelQuick(1,0)));
            CPPUNIT_ASSERT_EQUAL(static_cast<int>(std::numeric_limits<Ipp8s>::max()),
                                 static_cast<int>(result->getPixelQuick(2,0)));

            ImageT<Ipp32f>* result2 = new ImageT<Ipp32f>(src.width(), src.height());
            result2                     = convertBitDepth(src, result2);

            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result2->getPixelQuick(0,0)));
            CPPUNIT_ASSERT_EQUAL(static_cast<int>(std::numeric_limits<Ipp8s>::min()),
                                 static_cast<int>(result2->getPixelQuick(1,0)));
            CPPUNIT_ASSERT_EQUAL(static_cast<int>(std::numeric_limits<Ipp8s>::max()),
                                 static_cast<int>(result2->getPixelQuick(2,0)));
        }

        // Ipp16u -> Ipp32s//32f
        {
            ImageT<Ipp16u> src(3,2);
            src(0,0) =   500; src(1,0) = 1000; src(2,0) = 10000;
            src(0,1) = 15000; src(1,1) = std::numeric_limits<Ipp16u>::min(); src(2,1) = std::numeric_limits<Ipp16u>::max();

            ImageT<Ipp32s>* result = new ImageT<Ipp32s>(src.width(), src.height());
            result                     = convertBitDepth(src, result);

            CPPUNIT_ASSERT_EQUAL(  500, static_cast<int>(result->getPixelQuick(0,0)));
            CPPUNIT_ASSERT_EQUAL( 1000, static_cast<int>(result->getPixelQuick(1,0)));
            CPPUNIT_ASSERT_EQUAL(10000, static_cast<int>(result->getPixelQuick(2,0)));
            CPPUNIT_ASSERT_EQUAL(15000, static_cast<int>(result->getPixelQuick(0,1)));
            CPPUNIT_ASSERT_EQUAL(static_cast<int>(std::numeric_limits<Ipp16u>::min()),
                                 static_cast<int>(result->getPixelQuick(1,1)));
            CPPUNIT_ASSERT_EQUAL(static_cast<int>(std::numeric_limits<Ipp16u>::max()),
                                 static_cast<int>(result->getPixelQuick(2,1)));

            ImageT<Ipp32f>* result2 = new ImageT<Ipp32f>(src.width(), src.height());
            result2                     = convertBitDepth(src, result2);

            CPPUNIT_ASSERT_EQUAL(  500, static_cast<int>(result2->getPixelQuick(0,0)));
            CPPUNIT_ASSERT_EQUAL( 1000, static_cast<int>(result2->getPixelQuick(1,0)));
            CPPUNIT_ASSERT_EQUAL(10000, static_cast<int>(result2->getPixelQuick(2,0)));
            CPPUNIT_ASSERT_EQUAL(15000, static_cast<int>(result2->getPixelQuick(0,1)));
            CPPUNIT_ASSERT_EQUAL(static_cast<int>(std::numeric_limits<Ipp16u>::min()),
                                 static_cast<int>(result2->getPixelQuick(1,1)));
            CPPUNIT_ASSERT_EQUAL(static_cast<int>(std::numeric_limits<Ipp16u>::max()),
                                 static_cast<int>(result2->getPixelQuick(2,1)));

            // decrease bitdepth to 8u
            ImageT<Ipp8u>* result3 = new ImageT<Ipp8u>(src.width(), src.height());
            result3                    = convertBitDepth(src, result3);

            CPPUNIT_ASSERT_EQUAL(255, static_cast<int>(result3->getPixelQuick(0,0)));
            CPPUNIT_ASSERT_EQUAL(255, static_cast<int>(result3->getPixelQuick(1,0)));
            CPPUNIT_ASSERT_EQUAL(255, static_cast<int>(result3->getPixelQuick(2,0)));
            CPPUNIT_ASSERT_EQUAL(255, static_cast<int>(result3->getPixelQuick(0,1)));
            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result3->getPixelQuick(1,1)));
            CPPUNIT_ASSERT_EQUAL(255, static_cast<int>(result3->getPixelQuick(2,1)));

        }

        // Ipp16s -> Ipp32f
        {
            ImageT<Ipp16s> src(3,2);

            src(0,0) =   0; src(1,0) = std::numeric_limits<Ipp16s>::min();  src(2,0) = std::numeric_limits<Ipp16s>::max();
            src(0,1) =  std::numeric_limits<Ipp16s>::max()/2;
            src(1,1) = -std::numeric_limits<Ipp16s>::max()/2;
            src(2,1) =  std::numeric_limits<Ipp16s>::max()/8;

            ImageT<Ipp32f>* result = new ImageT<Ipp32f>(src.width(), src.height());
            result                     = convertBitDepth(src, result);

            CPPUNIT_ASSERT_EQUAL(     0, static_cast<int>(result->getPixelQuick(0,0)));
            CPPUNIT_ASSERT_EQUAL(static_cast<int>(std::numeric_limits<Ipp16s>::min()),
                                static_cast<int>(result->getPixelQuick(1,0)));
            CPPUNIT_ASSERT_EQUAL(static_cast<int>(std::numeric_limits<Ipp16s>::max()),
                                static_cast<int>(result->getPixelQuick(2,0)));
            CPPUNIT_ASSERT_EQUAL(static_cast<int>(std::numeric_limits<Ipp16s>::max()/2),
                                static_cast<int>(result->getPixelQuick(0,1)));
            CPPUNIT_ASSERT_EQUAL(static_cast<int>(-std::numeric_limits<Ipp16s>::max()/2),
                                static_cast<int>(result->getPixelQuick(1,1)));
            CPPUNIT_ASSERT_EQUAL(static_cast<int>(std::numeric_limits<Ipp16s>::max()/8),
                                static_cast<int>(result->getPixelQuick(2,1)));

            // decrease bitdepth to 8u
            ImageT<Ipp8u>* result2 = new ImageT<Ipp8u>(src.width(), src.height());
            result2                    = convertBitDepth(src, result2);

            CPPUNIT_ASSERT_EQUAL(     0, static_cast<int>(result2->getPixelQuick(0,0)));
            CPPUNIT_ASSERT_EQUAL(     0, static_cast<int>(result2->getPixelQuick(1,0)));
            CPPUNIT_ASSERT_EQUAL(   255, static_cast<int>(result2->getPixelQuick(2,0)));
            CPPUNIT_ASSERT_EQUAL(   255, static_cast<int>(result2->getPixelQuick(0,1)));
            CPPUNIT_ASSERT_EQUAL(     0, static_cast<int>(result2->getPixelQuick(1,1)));
            CPPUNIT_ASSERT_EQUAL(   255, static_cast<int>(result2->getPixelQuick(2,1)));
        }

        // test specialization to decrease bitdepth from 32f to 8u/8s/16u/16s with ImageT
        {
            ImageT<Ipp32f> src(1,10);
            src(0,0) = -std::numeric_limits<float>::max();
            src(0,1) =  std::numeric_limits<Ipp16s>::min();
            src(0,2) =  std::numeric_limits<Ipp8s>::min();
            src(0,3) =  std::numeric_limits<Ipp8u>::min();
            src(0,4) =  std::numeric_limits<Ipp16u>::min();
            src(0,5) =  std::numeric_limits<Ipp8s>::max();
            src(0,6) =  std::numeric_limits<Ipp8u>::max();
            src(0,7) =  std::numeric_limits<Ipp16s>::max();
            src(0,8) =  std::numeric_limits<Ipp16u>::max();
            src(0,9) =  std::numeric_limits<float>::max();

            // to Ipp16u
            {
                ImageT<Ipp16u>* result = new ImageT<Ipp16u>(src.width(), src.height());
                result                     = convertBitDepth(src, result);

                CPPUNIT_ASSERT_EQUAL(    0, static_cast<int>(result->getPixelQuick(0,0)));
                CPPUNIT_ASSERT_EQUAL(    0, static_cast<int>(result->getPixelQuick(0,1)));
                CPPUNIT_ASSERT_EQUAL(    0, static_cast<int>(result->getPixelQuick(0,2)));
                CPPUNIT_ASSERT_EQUAL(    0, static_cast<int>(result->getPixelQuick(0,3)));
                CPPUNIT_ASSERT_EQUAL(    0, static_cast<int>(result->getPixelQuick(0,4)));
                CPPUNIT_ASSERT_EQUAL(  127, static_cast<int>(result->getPixelQuick(0,5)));
                CPPUNIT_ASSERT_EQUAL(  255, static_cast<int>(result->getPixelQuick(0,6)));
                CPPUNIT_ASSERT_EQUAL(32767, static_cast<int>(result->getPixelQuick(0,7)));
                CPPUNIT_ASSERT_EQUAL(65535, static_cast<int>(result->getPixelQuick(0,8)));
                CPPUNIT_ASSERT_EQUAL(65535, static_cast<int>(result->getPixelQuick(0,9)));
            }
            // to Ipp16s
            {
                ImageT<Ipp16s>* result = new ImageT<Ipp16s>(src.width(), src.height());
                result                     = convertBitDepth(src, result);

                CPPUNIT_ASSERT_EQUAL(-32768, static_cast<int>(result->getPixelQuick(0,0)));
                CPPUNIT_ASSERT_EQUAL(-32768, static_cast<int>(result->getPixelQuick(0,1)));
                CPPUNIT_ASSERT_EQUAL(  -128, static_cast<int>(result->getPixelQuick(0,2)));
                CPPUNIT_ASSERT_EQUAL(     0, static_cast<int>(result->getPixelQuick(0,3)));
                CPPUNIT_ASSERT_EQUAL(     0, static_cast<int>(result->getPixelQuick(0,4)));
                CPPUNIT_ASSERT_EQUAL(   127, static_cast<int>(result->getPixelQuick(0,5)));
                CPPUNIT_ASSERT_EQUAL(   255, static_cast<int>(result->getPixelQuick(0,6)));
                CPPUNIT_ASSERT_EQUAL( 32767, static_cast<int>(result->getPixelQuick(0,7)));
                CPPUNIT_ASSERT_EQUAL( 32767, static_cast<int>(result->getPixelQuick(0,8)));
                CPPUNIT_ASSERT_EQUAL( 32767, static_cast<int>(result->getPixelQuick(0,9)));
            }
            // to Ipp8u
            {
                ImageT<Ipp8u>* result = new ImageT<Ipp8u>(src.width(), src.height());
                result                    = convertBitDepth(src, result);

                CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixelQuick(0,0)));
                CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixelQuick(0,1)));
                CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixelQuick(0,2)));
                CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixelQuick(0,3)));
                CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixelQuick(0,4)));
                CPPUNIT_ASSERT_EQUAL(127, static_cast<int>(result->getPixelQuick(0,5)));
                CPPUNIT_ASSERT_EQUAL(255, static_cast<int>(result->getPixelQuick(0,6)));
                CPPUNIT_ASSERT_EQUAL(255, static_cast<int>(result->getPixelQuick(0,7)));
                CPPUNIT_ASSERT_EQUAL(255, static_cast<int>(result->getPixelQuick(0,8)));
                CPPUNIT_ASSERT_EQUAL(255, static_cast<int>(result->getPixelQuick(0,9)));
            }
            // to Ipp8s
            {
                ImageT<Ipp8s>* result = new ImageT<Ipp8s>(src.width(), src.height());
                result                    = convertBitDepth(src, result);

                CPPUNIT_ASSERT_EQUAL(-128, static_cast<int>(result->getPixelQuick(0,0)));
                CPPUNIT_ASSERT_EQUAL(-128, static_cast<int>(result->getPixelQuick(0,1)));
                CPPUNIT_ASSERT_EQUAL(-128, static_cast<int>(result->getPixelQuick(0,2)));
                CPPUNIT_ASSERT_EQUAL(   0, static_cast<int>(result->getPixelQuick(0,3)));
                CPPUNIT_ASSERT_EQUAL(   0, static_cast<int>(result->getPixelQuick(0,4)));
                CPPUNIT_ASSERT_EQUAL(127, static_cast<int>(result->getPixelQuick(0,5)));
                CPPUNIT_ASSERT_EQUAL(127, static_cast<int>(result->getPixelQuick(0,6)));
                CPPUNIT_ASSERT_EQUAL(127, static_cast<int>(result->getPixelQuick(0,7)));
                CPPUNIT_ASSERT_EQUAL(127, static_cast<int>(result->getPixelQuick(0,8)));
                CPPUNIT_ASSERT_EQUAL(127, static_cast<int>(result->getPixelQuick(0,9)));
            }
        }

    }

    // color images
    {
        // Ipp8u -> Ipp16u/Ipp16s/Ipp32s//Ipp32f
        {
            ColorImageT<Ipp8u> src(3,2);
            src.setPixelQuick(0,0,  5,  5,  5);
            src.setPixelQuick(1,0, 10, 10, 10);
            src.setPixelQuick(2,0, 15, 15, 15);
            src.setPixelQuick(0,1,100,100,100);
            src.setPixelQuick(1,1,  0,  0,  0);
            src.setPixelQuick(2,1,255,255,255);

            ColorImageT<Ipp16u>* result = new ColorImageT<Ipp16u>(src.width(), src.height());
            result                      = convertBitDepth(src, result);

            for(int i=0; i<3; ++i) {
                CPPUNIT_ASSERT_EQUAL(  5, static_cast<int>(result->getPixelQuick(0,0,i)));
                CPPUNIT_ASSERT_EQUAL( 10, static_cast<int>(result->getPixelQuick(1,0,i)));
                CPPUNIT_ASSERT_EQUAL( 15, static_cast<int>(result->getPixelQuick(2,0,i)));
                CPPUNIT_ASSERT_EQUAL(100, static_cast<int>(result->getPixelQuick(0,1,i)));
                CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixelQuick(1,1,i)));
                CPPUNIT_ASSERT_EQUAL(255, static_cast<int>(result->getPixelQuick(2,1,i)));
            }

            ColorImageT<Ipp16s>* result2 = new ColorImageT<Ipp16s>(src.width(), src.height());
            result2                      = convertBitDepth(src, result2);

            for(int i=0; i<3; ++i) {
                CPPUNIT_ASSERT_EQUAL(  5, static_cast<int>(result2->getPixelQuick(0,0,i)));
                CPPUNIT_ASSERT_EQUAL( 10, static_cast<int>(result2->getPixelQuick(1,0,i)));
                CPPUNIT_ASSERT_EQUAL( 15, static_cast<int>(result2->getPixelQuick(2,0,i)));
                CPPUNIT_ASSERT_EQUAL(100, static_cast<int>(result2->getPixelQuick(0,1,i)));
                CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result2->getPixelQuick(1,1,i)));
                CPPUNIT_ASSERT_EQUAL(255, static_cast<int>(result2->getPixelQuick(2,1,i)));
            }

            ColorImageT<Ipp32s>* result3 = new ColorImageT<Ipp32s>(src.width(), src.height());
            result3                      = convertBitDepth(src, result3);

            for(int i=0; i<3; ++i) {
                CPPUNIT_ASSERT_EQUAL(  5, static_cast<int>(result3->getPixelQuick(0,0,i)));
                CPPUNIT_ASSERT_EQUAL( 10, static_cast<int>(result3->getPixelQuick(1,0,i)));
                CPPUNIT_ASSERT_EQUAL( 15, static_cast<int>(result3->getPixelQuick(2,0,i)));
                CPPUNIT_ASSERT_EQUAL(100, static_cast<int>(result3->getPixelQuick(0,1,i)));
                CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result3->getPixelQuick(1,1,i)));
                CPPUNIT_ASSERT_EQUAL(255, static_cast<int>(result3->getPixelQuick(2,1,i)));
            }

            ColorImageT<Ipp32f>* result4 = new ColorImageT<Ipp32f>(src.width(), src.height());
            result4                      = convertBitDepth(src, result4);

            for(int i=0; i<3; ++i) {
                CPPUNIT_ASSERT_EQUAL(  5, static_cast<int>(result4->getPixelQuick(0,0,i)));
                CPPUNIT_ASSERT_EQUAL( 10, static_cast<int>(result4->getPixelQuick(1,0,i)));
                CPPUNIT_ASSERT_EQUAL( 15, static_cast<int>(result4->getPixelQuick(2,0,i)));
                CPPUNIT_ASSERT_EQUAL(100, static_cast<int>(result4->getPixelQuick(0,1,i)));
                CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result4->getPixelQuick(1,1,i)));
                CPPUNIT_ASSERT_EQUAL(255, static_cast<int>(result4->getPixelQuick(2,1,i)));
            }
        }

        //8s to 32s//32f
        {
            ColorImageT<Ipp8s> src(3,1);
            src.setPixelQuick(0,0, 0,0,0);
            src.setPixelQuick(1,0, std::numeric_limits<Ipp8s>::min(),
                                   std::numeric_limits<Ipp8s>::min(),
                                   std::numeric_limits<Ipp8s>::min());
            src.setPixelQuick(2,0, std::numeric_limits<Ipp8s>::max(),
                                   std::numeric_limits<Ipp8s>::max(),
                                   std::numeric_limits<Ipp8s>::max());

            ColorImageT<Ipp32s>* result = new ColorImageT<Ipp32s>(src.width(), src.height());
            result                      = convertBitDepth(src, result);

            for(int i=0; i<3; ++i) {
                CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixelQuick(0,0,i)));
                CPPUNIT_ASSERT_EQUAL(static_cast<int>(std::numeric_limits<Ipp8s>::min()),
                                    static_cast<int>(result->getPixelQuick(1,0,i)));
                CPPUNIT_ASSERT_EQUAL(static_cast<int>(std::numeric_limits<Ipp8s>::max()),
                                    static_cast<int>(result->getPixelQuick(2,0,i)));
            }


            ColorImageT<Ipp32f>* result2 = new ColorImageT<Ipp32f>(src.width(), src.height());
            result2                      = convertBitDepth(src, result2);

            for(int i=0; i<3; ++i) {
                CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result2->getPixelQuick(0,0,i)));
                CPPUNIT_ASSERT_EQUAL(static_cast<int>(std::numeric_limits<Ipp8s>::min()),
                                    static_cast<int>(result2->getPixelQuick(1,0,i)));
                CPPUNIT_ASSERT_EQUAL(static_cast<int>(std::numeric_limits<Ipp8s>::max()),
                                    static_cast<int>(result2->getPixelQuick(2,0,i)));
            }
        }

        // Ipp16u -> Ipp32s//32f
        {
            ColorImageT<Ipp16u> src(2,1);
            src.setPixelQuick(0,0, 500,500,500);
            src.setPixelQuick(1,0, std::numeric_limits<Ipp16u>::max(),
                                   std::numeric_limits<Ipp16u>::max(),
                                   std::numeric_limits<Ipp16u>::max());

            ColorImageT<Ipp32s>* result = new ColorImageT<Ipp32s>(src.width(), src.height());
            result                      = convertBitDepth(src, result);

            for(int i=0; i<3; ++i) {
                CPPUNIT_ASSERT_EQUAL(500, static_cast<int>(result->getPixelQuick(0,0,i)));
                CPPUNIT_ASSERT_EQUAL(static_cast<int>(std::numeric_limits<Ipp16u>::max()),
                                     static_cast<int>(result->getPixelQuick(1,0,i)));
            }

            ColorImageT<Ipp32f>* result2 = new ColorImageT<Ipp32f>(src.width(), src.height());
            result2                      = convertBitDepth(src, result2);

            for(int i=0; i<3; ++i) {
                CPPUNIT_ASSERT_EQUAL(  500, static_cast<int>(result2->getPixelQuick(0,0,i)));
                CPPUNIT_ASSERT_EQUAL(static_cast<int>(std::numeric_limits<Ipp16u>::max()),
                                     static_cast<int>(result2->getPixelQuick(1,0,i)));
            }
        }

        // Ipp16s -> Ipp32f
        {
            ColorImageT<Ipp16s> src(3,2);
            src.setPixelQuick(0,0, 0,0,0);
            src.setPixelQuick(1,0, std::numeric_limits<Ipp16s>::min(),
                                   std::numeric_limits<Ipp16s>::min(),
                                   std::numeric_limits<Ipp16s>::min());
            src.setPixelQuick(2,0, std::numeric_limits<Ipp16s>::max(),
                                   std::numeric_limits<Ipp16s>::max(),
                                   std::numeric_limits<Ipp16s>::max());
            src.setPixelQuick(0,1, std::numeric_limits<Ipp16s>::max()/2,
                                   std::numeric_limits<Ipp16s>::max()/2,
                                   std::numeric_limits<Ipp16s>::max()/2);
            src.setPixelQuick(1,1,-std::numeric_limits<Ipp16s>::max()/2,
                                  -std::numeric_limits<Ipp16s>::max()/2,
                                  -std::numeric_limits<Ipp16s>::max()/2);
            src.setPixelQuick(2,1, std::numeric_limits<Ipp16s>::max()/8,
                                   std::numeric_limits<Ipp16s>::max()/8,
                                   std::numeric_limits<Ipp16s>::max()/8);

            ColorImageT<Ipp32f>* result = new ColorImageT<Ipp32f>(src.width(), src.height());
            result                      = convertBitDepth(src, result);

            for(int i=0; i<3; ++i) {
                CPPUNIT_ASSERT_EQUAL(     0, static_cast<int>(result->getPixelQuick(0,0,i)));
                CPPUNIT_ASSERT_EQUAL(static_cast<int>(std::numeric_limits<Ipp16s>::min()),
                                     static_cast<int>(result->getPixelQuick(1,0,i)));
                CPPUNIT_ASSERT_EQUAL(static_cast<int>(std::numeric_limits<Ipp16s>::max()),
                                     static_cast<int>(result->getPixelQuick(2,0,i)));
                CPPUNIT_ASSERT_EQUAL(static_cast<int>(std::numeric_limits<Ipp16s>::max()/2),
                                     static_cast<int>(result->getPixelQuick(0,1,i)));
                CPPUNIT_ASSERT_EQUAL(static_cast<int>(-std::numeric_limits<Ipp16s>::max()/2),
                                     static_cast<int>(result->getPixelQuick(1,1,i)));
                CPPUNIT_ASSERT_EQUAL(static_cast<int>(std::numeric_limits<Ipp16s>::max()/8),
                                     static_cast<int>(result->getPixelQuick(2,1,i)));
            }
        }

        // 32s to 8u/8s
        {
            ColorImageT<Ipp32s> src(1,10);
            for(int i=0; i<3; ++i) {
                src(0,0,i) =  std::numeric_limits<Ipp32s>::min();
                src(0,1,i) =  std::numeric_limits<Ipp16s>::min();
                src(0,2,i) =  std::numeric_limits<Ipp8s>::min();
                src(0,3,i) =  std::numeric_limits<Ipp8u>::min();
                src(0,4,i) =  std::numeric_limits<Ipp16u>::min();
                src(0,5,i) =  std::numeric_limits<Ipp8s>::max();
                src(0,6,i) =  std::numeric_limits<Ipp8u>::max();
                src(0,7,i) =  std::numeric_limits<Ipp16s>::max();
                src(0,8,i) =  std::numeric_limits<Ipp16u>::max();
                src(0,9,i) =  std::numeric_limits<Ipp32s>::max();
            }

            // to 8u
            {
                ColorImageT<Ipp8u>* result = new ColorImageT<Ipp8u>(src.width(), src.height());
                result                      = convertBitDepth(src, result);

                for(int i=0; i<3; ++i) {
                    CPPUNIT_ASSERT_EQUAL(    0, static_cast<int>(result->getPixelQuick(0,0,i)));
                    CPPUNIT_ASSERT_EQUAL(    0, static_cast<int>(result->getPixelQuick(0,1,i)));
                    CPPUNIT_ASSERT_EQUAL(    0, static_cast<int>(result->getPixelQuick(0,2,i)));
                    CPPUNIT_ASSERT_EQUAL(    0, static_cast<int>(result->getPixelQuick(0,3,i)));
                    CPPUNIT_ASSERT_EQUAL(    0, static_cast<int>(result->getPixelQuick(0,4,i)));
                    CPPUNIT_ASSERT_EQUAL(  127, static_cast<int>(result->getPixelQuick(0,5,i)));
                    CPPUNIT_ASSERT_EQUAL(  255, static_cast<int>(result->getPixelQuick(0,6,i)));
                    CPPUNIT_ASSERT_EQUAL(  255, static_cast<int>(result->getPixelQuick(0,7,i)));
                    CPPUNIT_ASSERT_EQUAL(  255, static_cast<int>(result->getPixelQuick(0,8,i)));
                    CPPUNIT_ASSERT_EQUAL(  255, static_cast<int>(result->getPixelQuick(0,9,i)));
                }
            }

            // to 8s
            {
                ColorImageT<Ipp8s>* result = new ColorImageT<Ipp8s>(src.width(), src.height());
                result                      = convertBitDepth(src, result);

                for(int i=0; i<3; ++i) {
                    CPPUNIT_ASSERT_EQUAL( -128, static_cast<int>(result->getPixelQuick(0,0,i)));
                    CPPUNIT_ASSERT_EQUAL( -128, static_cast<int>(result->getPixelQuick(0,1,i)));
                    CPPUNIT_ASSERT_EQUAL( -128, static_cast<int>(result->getPixelQuick(0,2,i)));
                    CPPUNIT_ASSERT_EQUAL(    0, static_cast<int>(result->getPixelQuick(0,3,i)));
                    CPPUNIT_ASSERT_EQUAL(    0, static_cast<int>(result->getPixelQuick(0,4,i)));
                    CPPUNIT_ASSERT_EQUAL(  127, static_cast<int>(result->getPixelQuick(0,5,i)));
                    CPPUNIT_ASSERT_EQUAL(  127, static_cast<int>(result->getPixelQuick(0,6,i)));
                    CPPUNIT_ASSERT_EQUAL(  127, static_cast<int>(result->getPixelQuick(0,7,i)));
                    CPPUNIT_ASSERT_EQUAL(  127, static_cast<int>(result->getPixelQuick(0,8,i)));
                    CPPUNIT_ASSERT_EQUAL(  127, static_cast<int>(result->getPixelQuick(0,9,i)));
                }
            }
        }

        // test specialization to decrease bitdepth from 32f to 16u/16s/8u/8s ColorImageT
        {
            ColorImageT<Ipp32f> src(1,10);
            for(int i=0; i<3; ++i) {
                src(0,0,i) = -std::numeric_limits<float>::max();
                src(0,1,i) =  std::numeric_limits<Ipp16s>::min();
                src(0,2,i) =  std::numeric_limits<Ipp8s>::min();
                src(0,3,i) =  std::numeric_limits<Ipp8u>::min();
                src(0,4,i) =  std::numeric_limits<Ipp16u>::min();
                src(0,5,i) =  std::numeric_limits<Ipp8s>::max();
                src(0,6,i) =  std::numeric_limits<Ipp8u>::max();
                src(0,7,i) =  std::numeric_limits<Ipp16s>::max();
                src(0,8,i) =  std::numeric_limits<Ipp16u>::max();
                src(0,9,i) =  std::numeric_limits<float>::max();
            }

            // to 16u
            {
                ColorImageT<Ipp16u>* result = new ColorImageT<Ipp16u>(src.width(), src.height());
                result                      = convertBitDepth(src, result);

                for(int i=0; i<3; ++i) {
                    CPPUNIT_ASSERT_EQUAL(    0, static_cast<int>(result->getPixelQuick(0,0,i)));
                    CPPUNIT_ASSERT_EQUAL(    0, static_cast<int>(result->getPixelQuick(0,1,i)));
                    CPPUNIT_ASSERT_EQUAL(    0, static_cast<int>(result->getPixelQuick(0,2,i)));
                    CPPUNIT_ASSERT_EQUAL(    0, static_cast<int>(result->getPixelQuick(0,3,i)));
                    CPPUNIT_ASSERT_EQUAL(    0, static_cast<int>(result->getPixelQuick(0,4,i)));
                    CPPUNIT_ASSERT_EQUAL(  127, static_cast<int>(result->getPixelQuick(0,5,i)));
                    CPPUNIT_ASSERT_EQUAL(  255, static_cast<int>(result->getPixelQuick(0,6,i)));
                    CPPUNIT_ASSERT_EQUAL(32767, static_cast<int>(result->getPixelQuick(0,7,i)));
                    CPPUNIT_ASSERT_EQUAL(65535, static_cast<int>(result->getPixelQuick(0,8,i)));
                    CPPUNIT_ASSERT_EQUAL(65535, static_cast<int>(result->getPixelQuick(0,9,i)));
                }
            }

            // to 16s
            {
                ColorImageT<Ipp16s>* result = new ColorImageT<Ipp16s>(src.width(), src.height());
                result                      = convertBitDepth(src, result);

                for(int i=0; i<3; ++i) {
                    CPPUNIT_ASSERT_EQUAL(-32768, static_cast<int>(result->getPixelQuick(0,0,i)));
                    CPPUNIT_ASSERT_EQUAL(-32768, static_cast<int>(result->getPixelQuick(0,1,i)));
                    CPPUNIT_ASSERT_EQUAL(  -128, static_cast<int>(result->getPixelQuick(0,2,i)));
                    CPPUNIT_ASSERT_EQUAL(     0, static_cast<int>(result->getPixelQuick(0,3,i)));
                    CPPUNIT_ASSERT_EQUAL(     0, static_cast<int>(result->getPixelQuick(0,4,i)));
                    CPPUNIT_ASSERT_EQUAL(   127, static_cast<int>(result->getPixelQuick(0,5,i)));
                    CPPUNIT_ASSERT_EQUAL(   255, static_cast<int>(result->getPixelQuick(0,6,i)));
                    CPPUNIT_ASSERT_EQUAL( 32767, static_cast<int>(result->getPixelQuick(0,7,i)));
                    CPPUNIT_ASSERT_EQUAL( 32767, static_cast<int>(result->getPixelQuick(0,8,i)));
                    CPPUNIT_ASSERT_EQUAL( 32767, static_cast<int>(result->getPixelQuick(0,9,i)));
                }
            }
            // to 8u
            {
                ColorImageT<Ipp8u>* result = new ColorImageT<Ipp8u>(src.width(), src.height());
                result                     = convertBitDepth(src, result);

                for(int i=0; i<3; ++i) {
                    CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixelQuick(0,0,i)));
                    CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixelQuick(0,1,i)));
                    CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixelQuick(0,2,i)));
                    CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixelQuick(0,3,i)));
                    CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixelQuick(0,4,i)));
                    CPPUNIT_ASSERT_EQUAL(127, static_cast<int>(result->getPixelQuick(0,5,i)));
                    CPPUNIT_ASSERT_EQUAL(255, static_cast<int>(result->getPixelQuick(0,6,i)));
                    CPPUNIT_ASSERT_EQUAL(255, static_cast<int>(result->getPixelQuick(0,7,i)));
                    CPPUNIT_ASSERT_EQUAL(255, static_cast<int>(result->getPixelQuick(0,8,i)));
                    CPPUNIT_ASSERT_EQUAL(255, static_cast<int>(result->getPixelQuick(0,9,i)));
                }
            }
            // to 8s
            {
                ColorImageT<Ipp8s>* result = new ColorImageT<Ipp8s>(src.width(), src.height());
                result                     = convertBitDepth(src, result);

                for(int i=0; i<3; ++i) {
                    CPPUNIT_ASSERT_EQUAL(-128, static_cast<int>(result->getPixelQuick(0,0,i)));
                    CPPUNIT_ASSERT_EQUAL(-128, static_cast<int>(result->getPixelQuick(0,1,i)));
                    CPPUNIT_ASSERT_EQUAL(-128, static_cast<int>(result->getPixelQuick(0,2,i)));
                    CPPUNIT_ASSERT_EQUAL(   0, static_cast<int>(result->getPixelQuick(0,3,i)));
                    CPPUNIT_ASSERT_EQUAL(   0, static_cast<int>(result->getPixelQuick(0,4,i)));
                    CPPUNIT_ASSERT_EQUAL(127, static_cast<int>(result->getPixelQuick(0,5,i)));
                    CPPUNIT_ASSERT_EQUAL(127, static_cast<int>(result->getPixelQuick(0,6,i)));
                    CPPUNIT_ASSERT_EQUAL(127, static_cast<int>(result->getPixelQuick(0,7,i)));
                    CPPUNIT_ASSERT_EQUAL(127, static_cast<int>(result->getPixelQuick(0,8,i)));
                    CPPUNIT_ASSERT_EQUAL(127, static_cast<int>(result->getPixelQuick(0,9,i)));
                }
            }
        }
    }
}

void TestConvert::testfloatToGrayScaled()
{
    FloatImage src(7,1);
    src(0,0) = -255; src(1,0) = -128; src(2,0) = - 51;
    src(3,0) =    0;
    src(4,0) =   51; src(5,0) =  128; src(6,0) =  255;

    Image*  result = new Image(src.width(), src.height());
    result             = floatToGrayScaled(src, result);

    CPPUNIT_ASSERT_DOUBLES_EQUAL(   0, static_cast<int>(result->getPixelQuick(0,0)), 1);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  64, static_cast<int>(result->getPixelQuick(1,0)), 1);
    CPPUNIT_ASSERT_DOUBLES_EQUAL( 102, static_cast<int>(result->getPixelQuick(2,0)), 1);
    CPPUNIT_ASSERT_DOUBLES_EQUAL( 128, static_cast<int>(result->getPixelQuick(3,0)), 1);
    CPPUNIT_ASSERT_DOUBLES_EQUAL( 153, static_cast<int>(result->getPixelQuick(4,0)), 1);
    CPPUNIT_ASSERT_DOUBLES_EQUAL( 192, static_cast<int>(result->getPixelQuick(5,0)), 1);
    CPPUNIT_ASSERT_DOUBLES_EQUAL( 255, static_cast<int>(result->getPixelQuick(6,0)), 1);
}












