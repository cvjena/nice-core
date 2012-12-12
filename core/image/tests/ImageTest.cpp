#include "ImageTest.h"
#include <string>


#include <core/image/ippwrapper.h>

#include <core/image/ImageT.h>
#include <core/image/ImageT.h>
#include <core/image/ColorImageT.h>

#include "core/basics/cppunitex.h"

using namespace std;
using namespace NICE;

CPPUNIT_TEST_SUITE_REGISTRATION( ImageTest );

void ImageTest::setUp() {
}

void ImageTest::tearDown() {
}

void ImageTest::testFloatImage() {
  int width=10;
  int height=10;
  FloatImage fimg(width,height);
  fimg=0;
  for(int w=0;w<width;w++) {
        fimg(w,height/2) = -25*w;
  }
  for(int h=0;h<height;h++) {
        fimg(width/2,h) = 25*h;
  }
//  fimg.writeColored(ImageFile("test.png",ImageFile::PNG));
}

void printGrayImage2(Image *result)
{
    printf("\n");
    for(int j=0; j<result->height(); ++j)
    {
        for(int i=0; i<result->width(); ++i)
        {
            if((*result)(i,j)<100) printf(" ");
            if((*result)(i,j)<10) printf(" ");
            printf("%i ",(*result)(i,j));
        }
        printf("\n");
    }
}

void ImageTest::testGrayImage()
{
    Image image(4,3);

    CPPUNIT_ASSERT_EQUAL(4, image.width());
    CPPUNIT_ASSERT_EQUAL(3, image.height());

    // setPixel
    CPPUNIT_ASSERT_THROW(image.setPixel(4, 2, 11), ImageException);
    CPPUNIT_ASSERT_THROW(image.setPixel(3, 3, 12), ImageException);
    CPPUNIT_ASSERT_NO_THROW(image.setPixelSave(4, 2, 11));
    CPPUNIT_ASSERT_NO_THROW(image.setPixelSave(3, 3, 12));
    CPPUNIT_ASSERT_THROW(image.getPixel(4, 2), ImageException);
    CPPUNIT_ASSERT_THROW(image.getPixel(3, 3), ImageException);

    image.setPixel(0, 0, 11);
    image.setPixel(3, 2, 12);

    CPPUNIT_ASSERT_EQUAL(11, (int)image.getPixel(0, 0));
    CPPUNIT_ASSERT_EQUAL(12, (int)image.getPixel(3, 2));

    CPPUNIT_ASSERT_EQUAL(12, (int)*image.getPixelPointerXY(3, 2));

    // operator ==, !=
    {
        Image img(2,2);
        img.set(133);

	// Image::set test
	CPPUNIT_ASSERT_EQUAL(133, static_cast<int>(img.getPixel(0,0)));
	CPPUNIT_ASSERT_EQUAL(133, static_cast<int>(img.getPixel(1,0)));
	CPPUNIT_ASSERT_EQUAL(133, static_cast<int>(img.getPixel(0,1)));
	CPPUNIT_ASSERT_EQUAL(133, static_cast<int>(img.getPixel(1,1)));

        Image timg(3,2);
        CPPUNIT_ASSERT_THROW(timg==img, ImageException);
        CPPUNIT_ASSERT_THROW(timg!=img, ImageException);

        timg = img;

        CPPUNIT_ASSERT_EQUAL(true, timg==img);
        CPPUNIT_ASSERT_EQUAL(false, timg!=img);

        timg.setPixelQuick(1,1,0);
        CPPUNIT_ASSERT_EQUAL(false, timg==img);
        CPPUNIT_ASSERT_EQUAL(true, timg!=img);
    }

    // invert
    Image image2(image, GrayColorImageCommonImplementation::noAlignment);
    CPPUNIT_ASSERT_EQUAL(11, (int)image.getPixel(0,0));
    CPPUNIT_ASSERT_EQUAL(12, (int)image.getPixel(3,2));
    CPPUNIT_ASSERT_EQUAL(11, (int)image2.getPixel(0,0));
    CPPUNIT_ASSERT_EQUAL(12, (int)image2.getPixel(3,2));

    CPPUNIT_ASSERT_EQUAL(12, (int) image2.getPixel(3, 2));
    CPPUNIT_ASSERT_EQUAL(12, (int) image.getPixel(3, 2));
    CPPUNIT_ASSERT_EQUAL(true,  image == image2);
    image2.invert();
    CPPUNIT_ASSERT_EQUAL(false,  image == image2);
    CPPUNIT_ASSERT_EQUAL(255-11, (int)image2.getPixel(0,0));
    CPPUNIT_ASSERT_EQUAL(255-12, (int)image2.getPixel(3,2));

    // mirror
    Image image3 = Image(3,4);
    for(int j=0; j<image3.height(); ++j)
        for(int i=0; i<image3.width(); ++i)
            image3.setPixel(i,j, (i+1)+j*(image3.width()));

    image3.mirror(ippAxsVertical);
    CPPUNIT_ASSERT_EQUAL(  3, static_cast<int>(image3.getPixel(0,0)));
    CPPUNIT_ASSERT_EQUAL(  2, static_cast<int>(image3.getPixel(1,0)));
    CPPUNIT_ASSERT_EQUAL(  1, static_cast<int>(image3.getPixel(2,0)));
    image3.mirror(ippAxsVertical);

    image3.mirror(ippAxsHorizontal);
    CPPUNIT_ASSERT_EQUAL( 10, static_cast<int>(image3.getPixel(0,0)));
    CPPUNIT_ASSERT_EQUAL(  7, static_cast<int>(image3.getPixel(0,1)));
    CPPUNIT_ASSERT_EQUAL(  4, static_cast<int>(image3.getPixel(0,2)));
    CPPUNIT_ASSERT_EQUAL(  1, static_cast<int>(image3.getPixel(0,3)));
    image3.mirror(ippAxsHorizontal);

    image3.mirror(ippAxsBoth);
    CPPUNIT_ASSERT_EQUAL( 12, static_cast<int>(image3.getPixel(0,0)));
    CPPUNIT_ASSERT_EQUAL(  9, static_cast<int>(image3.getPixel(0,1)));
    CPPUNIT_ASSERT_EQUAL(  4, static_cast<int>(image3.getPixel(2,2)));
    CPPUNIT_ASSERT_EQUAL(  1, static_cast<int>(image3.getPixel(2,3)));

    // transpose
    Image image4 = Image(3,4);
    CPPUNIT_ASSERT_THROW(image4.transpose(), ImageException);
    for(int s=1; s<=8; ++s)
    {
        image4 = Image(s,s);
        for(int j=0; j<image4.height(); ++j)
            for(int i=0; i<image4.width(); ++i)
                image4.setPixel(i,j, (i+1)+j*(image4.width()));
        image4.transpose();
        for(int j=0; j<image4.height(); ++j)
            for(int i=0; i<image4.width(); ++i)
                CPPUNIT_ASSERT_EQUAL(static_cast<int>((j+1)+i*(image4.width())),
                                     static_cast<int>(image4.getPixel(i,j)));
    }

    // set
    image4.set(133);
    CPPUNIT_ASSERT_EQUAL(133, static_cast<int>(image4.getPixel(1,1)));
    CPPUNIT_ASSERT_EQUAL(133, static_cast<int>(image4.getPixel(2,2)));
    image4.set(0);
    CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(image4.getPixel(0,1)));
    CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(image4.getPixel(1,0)));
    image4.set(255);
    CPPUNIT_ASSERT_EQUAL(255, static_cast<int>(image4.getPixel(2,3)));
    CPPUNIT_ASSERT_EQUAL(255, static_cast<int>(image4.getPixel(2,0)));

    // copyRect
    image4 = Image(10,10);
    for(int y=0; y<image4.width(); ++y)
        for(int x=0; x<image4.width(); ++x)
            image4(x,y) = x+1+y*image4.width();

    Image* imgRect = image4.copyRect(Rect(2,3,4,3));
    CPPUNIT_ASSERT_EQUAL(4, static_cast<int>(imgRect->width()));
    CPPUNIT_ASSERT_EQUAL(3, static_cast<int>(imgRect->height()));

    for(int y=0; y<imgRect->height(); ++y)
        for(int x=0; x<imgRect->width(); ++x)
            CPPUNIT_ASSERT_EQUAL((x+3)+(y+3)*image4.width(), static_cast<int>(imgRect->getPixel(x,y)));

    imgRect = image4.copyRect(Rect(7,6,10,10));
    CPPUNIT_ASSERT_EQUAL(  3, static_cast<int>(imgRect->width()));
    CPPUNIT_ASSERT_EQUAL(  4, static_cast<int>(imgRect->height()));
    CPPUNIT_ASSERT_EQUAL( 68, static_cast<int>(imgRect->getPixel(0,0)));
    CPPUNIT_ASSERT_EQUAL( 69, static_cast<int>(imgRect->getPixel(1,0)));
    CPPUNIT_ASSERT_EQUAL( 70, static_cast<int>(imgRect->getPixel(2,0)));
    CPPUNIT_ASSERT_EQUAL( 98, static_cast<int>(imgRect->getPixel(0,3)));
    CPPUNIT_ASSERT_EQUAL( 99, static_cast<int>(imgRect->getPixel(1,3)));
    CPPUNIT_ASSERT_EQUAL(100, static_cast<int>(imgRect->getPixel(2,3)));
}

void ImageTest::testGrayImage16s() 
{
  GrayImage16s image(4,3);

  CPPUNIT_ASSERT_EQUAL(4, image.width());
  CPPUNIT_ASSERT_EQUAL(3, image.height());

  CPPUNIT_ASSERT_THROW(image.setPixel(4, 2, 11), ImageException);
  CPPUNIT_ASSERT_THROW(image.setPixel(3, 3, 12), ImageException);
  CPPUNIT_ASSERT_NO_THROW(image.setPixelSave(4, 2, 11));
  CPPUNIT_ASSERT_NO_THROW(image.setPixelSave(3, 3, 12));
  CPPUNIT_ASSERT_THROW(image.getPixel(4, 2), ImageException);
  CPPUNIT_ASSERT_THROW(image.getPixel(3, 3), ImageException);

  image.setPixel(0, 0, 11);
  image.setPixel(3, 2, 12);

  CPPUNIT_ASSERT_EQUAL(11, (int) image.getPixel(0, 0));
  CPPUNIT_ASSERT_EQUAL(12, (int) image.getPixel(3, 2));

  CPPUNIT_ASSERT_EQUAL(12, (int) *image.getPixelPointerXY(3, 2));

  GrayImage16s image2(image, GrayColorImageCommonImplementation::noAlignment);
  CPPUNIT_ASSERT_EQUAL(12, (int) image.getPixel(3, 2));
  CPPUNIT_ASSERT_EQUAL(12, (int) image2.getPixel(3, 2));
}

void ImageTest::testColorImage()
{
    ColorImage image(4,3);

    CPPUNIT_ASSERT_EQUAL(4, image.width());
    CPPUNIT_ASSERT_EQUAL(3, image.height());

    CPPUNIT_ASSERT_THROW(image.setPixel(4, 2, 1, 11), ImageException);
    CPPUNIT_ASSERT_THROW(image.setPixel(3, 3, 2, 12), ImageException);
    CPPUNIT_ASSERT_NO_THROW(image.setPixelSave(4, 2, 11, 12, 13));
    CPPUNIT_ASSERT_NO_THROW(image.setPixelSave(3, 3, 11, 12, 13));
    CPPUNIT_ASSERT_THROW(image.getPixel(4, 2, 1), ImageException);
    CPPUNIT_ASSERT_THROW(image.getPixel(3, 3, 2), ImageException);

    image.setPixel(0, 0, 11, 12, 13);
    image.setPixel(3, 2, 25, 26, 27);

    CPPUNIT_ASSERT_EQUAL(11, (int) image.getPixel(0, 0, 0));
    CPPUNIT_ASSERT_EQUAL(12, (int) image.getPixel(0, 0, 1));
    CPPUNIT_ASSERT_EQUAL(13, (int) image.getPixel(0, 0, 2));
    CPPUNIT_ASSERT_EQUAL(25, (int) image.getPixel(3, 2, 0));
    CPPUNIT_ASSERT_EQUAL(26, (int) image.getPixel(3, 2, 1));
    CPPUNIT_ASSERT_EQUAL(27, (int) image.getPixel(3, 2, 2));

    CPPUNIT_ASSERT_EQUAL(25, (int) *image.getPixelPointerXY(3, 2));

    ColorImage image2(image, GrayColorImageCommonImplementation::noAlignment);
    CPPUNIT_ASSERT_EQUAL(26, (int) image.getPixel(3, 2, 1));
    CPPUNIT_ASSERT_EQUAL(26, (int) image2.getPixel(3, 2, 1));

    // set
    ColorImage image3(10,10);
    image3.set(15,64,253);
    for(int y=0; y<image3.height(); ++y)
        for(int x=0; x<image3.width(); ++x)
        {
            CPPUNIT_ASSERT_EQUAL( 15, static_cast<int>(image3.getPixelQuick(x,y,0)));
            CPPUNIT_ASSERT_EQUAL( 64, static_cast<int>(image3.getPixelQuick(x,y,1)));
            CPPUNIT_ASSERT_EQUAL(253, static_cast<int>(image3.getPixelQuick(x,y,2)));
        }

    // operator =, ==, !=
    {
        ColorImage img(2,2);
        img.set(0,0,0);
        img.setPixelQuick(1,1,0,133);

        ColorImage fimg(3,2);

        CPPUNIT_ASSERT_THROW(fimg==img, ImageException);
        CPPUNIT_ASSERT_THROW(fimg!=img, ImageException);

        ColorImage timg;
        timg = img;
        CPPUNIT_ASSERT_NO_THROW(img==timg);
        CPPUNIT_ASSERT_EQUAL(true, img==timg);
        CPPUNIT_ASSERT_EQUAL(false, img!=timg);

        timg.setPixelQuick(0,0,3,99);
        CPPUNIT_ASSERT_NO_THROW(img!=timg);
        CPPUNIT_ASSERT_EQUAL(true, img!=timg);
        CPPUNIT_ASSERT_EQUAL(false, img==timg);
    }

    // Kontruktor: create a ColorImageT from 3 Channel Images ImageT
    {
        // exception
        {
            Image chan1, chan2, chan3;
            chan1 = Image(5,6);
            chan2 = Image(6,7);
            chan3 = Image(7,8);
            CPPUNIT_ASSERT_THROW(ColorImage c(chan1,chan2,chan3), ImageException);
        }

        // <Ipp8u>
        {
            Image chan1(5,5), chan2(5,5), chan3(5,5);
            chan1.set(100);
            chan2.set(150);
            chan3.set(200);

            for(int y=0; y<chan1.height(); ++y)
                for(int x=0; x<chan1.width(); ++x)
                {
                    CPPUNIT_ASSERT_EQUAL(100, static_cast<int>(chan1.getPixelQuick(x,y)));
                    CPPUNIT_ASSERT_EQUAL(150, static_cast<int>(chan2.getPixelQuick(x,y)));
                    CPPUNIT_ASSERT_EQUAL(200, static_cast<int>(chan3.getPixelQuick(x,y)));
                }

            ColorImage c(chan1,chan2,chan3);
            CPPUNIT_ASSERT_EQUAL(static_cast<int>(c.width()), static_cast<int>(chan1.width()));
            CPPUNIT_ASSERT_EQUAL(static_cast<int>(c.height()), static_cast<int>(chan1.height()));

            for(int y=0; y<c.height(); ++y)
                for(int x=0; x<c.width(); ++x)
                {
                    CPPUNIT_ASSERT_EQUAL(100, static_cast<int>(c.getPixelQuick(x,y,0)));
                    CPPUNIT_ASSERT_EQUAL(150, static_cast<int>(c.getPixelQuick(x,y,1)));
                    CPPUNIT_ASSERT_EQUAL(200, static_cast<int>(c.getPixelQuick(x,y,2)));
                }
        }
        // FloatImage
        {
            FloatImage chan1(5,5), chan2(5,5), chan3(5,5);
            chan1.set( -50.0);
            chan2.set(1000.0);
            chan3.set(   1.0);

            for(int y=0; y<chan1.height(); ++y)
                for(int x=0; x<chan1.width(); ++x)
                {
                    CPPUNIT_ASSERT_EQUAL( -50.0, static_cast<double>(chan1.getPixelQuick(x,y)));
                    CPPUNIT_ASSERT_EQUAL(1000.0, static_cast<double>(chan2.getPixelQuick(x,y)));
                    CPPUNIT_ASSERT_EQUAL(   1.0, static_cast<double>(chan3.getPixelQuick(x,y)));
                }

            ColorImageT<float> c(chan1,chan2,chan3);

            for(int y=0; y<c.height(); ++y)
                for(int x=0; x<c.width(); ++x)
                {
                    CPPUNIT_ASSERT_DOUBLES_EQUAL( -50.0, static_cast<double>(c.getPixelQuick(x,y,0)), 0.0);
                    CPPUNIT_ASSERT_DOUBLES_EQUAL(1000.0, static_cast<double>(c.getPixelQuick(x,y,1)), 0.0);
                    CPPUNIT_ASSERT_DOUBLES_EQUAL(   1.0, static_cast<double>(c.getPixelQuick(x,y,2)), 0.0);
                }
        }
        // Ipp16s
        {
            ImageT<Ipp16s> chan1(5,5), chan2(5,5), chan3(5,5);
            chan1.set(-255);
            chan2.set(+255);
            chan3.set(   0);

            for(int y=0; y<chan1.height(); ++y)
                for(int x=0; x<chan1.width(); ++x)
                {
                    CPPUNIT_ASSERT_EQUAL(-255, static_cast<int>(chan1.getPixelQuick(x,y)));
                    CPPUNIT_ASSERT_EQUAL(+255, static_cast<int>(chan2.getPixelQuick(x,y)));
                    CPPUNIT_ASSERT_EQUAL(   0, static_cast<int>(chan3.getPixelQuick(x,y)));
                }

            ColorImageT<Ipp16s> c(chan1,chan2,chan3);

            for(int y=0; y<c.height(); ++y)
                for(int x=0; x<c.width(); ++x)
                {
                    CPPUNIT_ASSERT_EQUAL(-255, static_cast<int>(c.getPixelQuick(x,y,0)));
                    CPPUNIT_ASSERT_EQUAL(+255, static_cast<int>(c.getPixelQuick(x,y,1)));
                    CPPUNIT_ASSERT_EQUAL(   0, static_cast<int>(c.getPixelQuick(x,y,2)));
                }
        }
    }

    // getChannel
    {
        // exception
        {
            ColorImage c(5,5);
            CPPUNIT_ASSERT_NO_THROW(c.getChannel(0));
            CPPUNIT_ASSERT_NO_THROW(c.getChannel(1));
            CPPUNIT_ASSERT_NO_THROW(c.getChannel(2));
            CPPUNIT_ASSERT_THROW(c.getChannel( 3), ImageException);
            CPPUNIT_ASSERT_THROW(c.getChannel( 4), ImageException);
        }
        // <Ipp8u>
        {
            ColorImage c(5,5);
            for(int y=0; y<c.height(); ++y)
                for(int x=0; x<c.width(); ++x)
                    c.setPixelQuick(x,y, 100,150,200);

            Image* g0 = c.getChannel(0);
            Image* g1 = c.getChannel(1);
            Image* g2 = c.getChannel(2);
            for(int y=0; y<c.height(); ++y)
                for(int x=0; x<c.width(); ++x)
                {
                    CPPUNIT_ASSERT_EQUAL(100, static_cast<int>(g0->getPixelQuick(x,y)));
                    CPPUNIT_ASSERT_EQUAL(150, static_cast<int>(g1->getPixelQuick(x,y)));
                    CPPUNIT_ASSERT_EQUAL(200, static_cast<int>(g2->getPixelQuick(x,y)));
                }
        }
        // FloatImage
        {
            ColorImageT<float> c(5,5);
            for(int y=0; y<c.height(); ++y)
                for(int x=0; x<c.width(); ++x)
                    c.setPixelQuick(x,y, -1000.125, 1.32678, +999.999);

            FloatImage* g0 = c.getChannel(0);
            FloatImage* g1 = c.getChannel(1);
            FloatImage* g2 = c.getChannel(2);

            for(int y=0; y<c.height(); ++y)
                for(int x=0; x<c.width(); ++x)
                {
                    CPPUNIT_ASSERT_DOUBLES_EQUAL(-1000.125, static_cast<double>(g0->getPixelQuick(x,y)), 0.001);
                    CPPUNIT_ASSERT_DOUBLES_EQUAL(1.32678  , static_cast<double>(g1->getPixelQuick(x,y)), 0.00001);
                    CPPUNIT_ASSERT_DOUBLES_EQUAL(999.999  , static_cast<double>(g2->getPixelQuick(x,y)), 0.001);
                }
        }
        // <Ipp16s>
        {
            ColorImageT<Ipp16s> c(5,5);
            for(int y=0; y<c.height(); ++y)
                for(int x=0; x<c.width(); ++x)
                    c.setPixelQuick(x,y, -255, 0, +255);

            GrayImage16s* g0 = c.getChannel(0);
            GrayImage16s* g1 = c.getChannel(1);
            GrayImage16s* g2 = c.getChannel(2);
            for(int y=0; y<c.height(); ++y)
                for(int x=0; x<c.width(); ++x)
                {
                    CPPUNIT_ASSERT_EQUAL(-255, static_cast<int>(g0->getPixelQuick(x,y)));
                    CPPUNIT_ASSERT_EQUAL(   0, static_cast<int>(g1->getPixelQuick(x,y)));
                    CPPUNIT_ASSERT_EQUAL(+255, static_cast<int>(g2->getPixelQuick(x,y)));
                }
        }
    }

    // mirror
    ColorImage image4(5,5);
    for(int y=0; y<image4.height(); ++y)
        for(int x=0; x<image4.width(); ++x)
            image4.setPixelQuick(x,y,1*(x+1+y*5),3*(x+1+y*5),6*(x+1+y*5));

    image4.mirror(ippAxsHorizontal);
    CPPUNIT_ASSERT_EQUAL( 21, static_cast<int>(image4.getPixelQuick(0,0,0)));
    CPPUNIT_ASSERT_EQUAL( 16, static_cast<int>(image4.getPixelQuick(0,1,0)));
    CPPUNIT_ASSERT_EQUAL( 11, static_cast<int>(image4.getPixelQuick(0,2,0)));
    CPPUNIT_ASSERT_EQUAL(  6, static_cast<int>(image4.getPixelQuick(0,3,0)));
    CPPUNIT_ASSERT_EQUAL(  1, static_cast<int>(image4.getPixelQuick(0,4,0)));
    CPPUNIT_ASSERT_EQUAL( 22, static_cast<int>(image4.getPixelQuick(1,0,0)));
    CPPUNIT_ASSERT_EQUAL( 17, static_cast<int>(image4.getPixelQuick(1,1,0)));
    CPPUNIT_ASSERT_EQUAL( 12, static_cast<int>(image4.getPixelQuick(1,2,0)));
    CPPUNIT_ASSERT_EQUAL(  7, static_cast<int>(image4.getPixelQuick(1,3,0)));
    CPPUNIT_ASSERT_EQUAL(  2, static_cast<int>(image4.getPixelQuick(1,4,0)));
    image4.mirror(ippAxsHorizontal);

    image4.mirror(ippAxsVertical);
    CPPUNIT_ASSERT_EQUAL(  5, static_cast<int>(image4.getPixelQuick(0,0,0)));
    CPPUNIT_ASSERT_EQUAL( 10, static_cast<int>(image4.getPixelQuick(0,1,0)));
    CPPUNIT_ASSERT_EQUAL( 15, static_cast<int>(image4.getPixelQuick(0,2,0)));
    CPPUNIT_ASSERT_EQUAL( 20, static_cast<int>(image4.getPixelQuick(0,3,0)));
    CPPUNIT_ASSERT_EQUAL( 25, static_cast<int>(image4.getPixelQuick(0,4,0)));
    CPPUNIT_ASSERT_EQUAL(  4, static_cast<int>(image4.getPixelQuick(1,0,0)));
    CPPUNIT_ASSERT_EQUAL(  9, static_cast<int>(image4.getPixelQuick(1,1,0)));
    CPPUNIT_ASSERT_EQUAL( 14, static_cast<int>(image4.getPixelQuick(1,2,0)));
    CPPUNIT_ASSERT_EQUAL( 19, static_cast<int>(image4.getPixelQuick(1,3,0)));
    CPPUNIT_ASSERT_EQUAL( 24, static_cast<int>(image4.getPixelQuick(1,4,0)));
    image4.mirror(ippAxsVertical);

    image4.mirror(ippAxsBoth);
    CPPUNIT_ASSERT_EQUAL( 25, static_cast<int>(image4.getPixelQuick(0,0,0)));
    CPPUNIT_ASSERT_EQUAL( 19, static_cast<int>(image4.getPixelQuick(1,1,0)));
    CPPUNIT_ASSERT_EQUAL( 13, static_cast<int>(image4.getPixelQuick(2,2,0)));
    CPPUNIT_ASSERT_EQUAL(  7, static_cast<int>(image4.getPixelQuick(3,3,0)));
    CPPUNIT_ASSERT_EQUAL(  1, static_cast<int>(image4.getPixelQuick(4,4,0)));
    CPPUNIT_ASSERT_EQUAL( 21, static_cast<int>(image4.getPixelQuick(4,0,0)));
    CPPUNIT_ASSERT_EQUAL( 17, static_cast<int>(image4.getPixelQuick(3,1,0)));
    CPPUNIT_ASSERT_EQUAL( 13, static_cast<int>(image4.getPixelQuick(2,2,0)));
    CPPUNIT_ASSERT_EQUAL(  9, static_cast<int>(image4.getPixelQuick(1,3,0)));
    CPPUNIT_ASSERT_EQUAL(  5, static_cast<int>(image4.getPixelQuick(0,4,0)));
    image4.mirror(ippAxsBoth);

    // transpose
    image4.transpose();
    for(int y=0; y<image4.height(); ++y)
        for(int x=0; x<image4.width(); ++x)
        {
            CPPUNIT_ASSERT_EQUAL( 1*(y+1+x*5), static_cast<int>(image4.getPixelQuick(x,y,0)));
            CPPUNIT_ASSERT_EQUAL( 3*(y+1+x*5), static_cast<int>(image4.getPixelQuick(x,y,1)));
            CPPUNIT_ASSERT_EQUAL( 6*(y+1+x*5), static_cast<int>(image4.getPixelQuick(x,y,2)));
        }

    // copyRect
    image4 = ColorImage(10,10);
    for(int y=0; y<image4.width(); ++y)
        for(int x=0; x<image4.width(); ++x)
            image4.setPixelQuick(x,y,x+1+y*image4.width(),(x+1+y*image4.width())/2,(x+1+y*image4.width())/3);

    ColorImage* imgRect = image4.copyRect(Rect(2,3,4,3));
    CPPUNIT_ASSERT_EQUAL(4, static_cast<int>(imgRect->width()));
    CPPUNIT_ASSERT_EQUAL(3, static_cast<int>(imgRect->height()));

    for(int y=0; y<imgRect->height(); ++y)
        for(int x=0; x<imgRect->width(); ++x)
        {
            CPPUNIT_ASSERT_EQUAL(((x+3)+(y+3)*image4.width())/1, static_cast<int>(imgRect->getPixelQuick(x,y,0)));
            CPPUNIT_ASSERT_EQUAL(((x+3)+(y+3)*image4.width())/2, static_cast<int>(imgRect->getPixelQuick(x,y,1)));
            CPPUNIT_ASSERT_EQUAL(((x+3)+(y+3)*image4.width())/3, static_cast<int>(imgRect->getPixelQuick(x,y,2)));
        }

    imgRect = image4.copyRect(Rect(7,6,10,10));
    CPPUNIT_ASSERT_EQUAL(    3, static_cast<int>(imgRect->width()));
    CPPUNIT_ASSERT_EQUAL(    4, static_cast<int>(imgRect->height()));
    CPPUNIT_ASSERT_EQUAL( 68/1, static_cast<int>(imgRect->getPixelQuick(0,0,0)));
    CPPUNIT_ASSERT_EQUAL( 68/2, static_cast<int>(imgRect->getPixelQuick(0,0,1)));
    CPPUNIT_ASSERT_EQUAL( 68/3, static_cast<int>(imgRect->getPixelQuick(0,0,2)));
    CPPUNIT_ASSERT_EQUAL( 69/1, static_cast<int>(imgRect->getPixelQuick(1,0,0)));
    CPPUNIT_ASSERT_EQUAL( 69/2, static_cast<int>(imgRect->getPixelQuick(1,0,1)));
    CPPUNIT_ASSERT_EQUAL( 69/3, static_cast<int>(imgRect->getPixelQuick(1,0,2)));
    CPPUNIT_ASSERT_EQUAL( 70/1, static_cast<int>(imgRect->getPixelQuick(2,0,0)));
    CPPUNIT_ASSERT_EQUAL( 70/2, static_cast<int>(imgRect->getPixelQuick(2,0,1)));
    CPPUNIT_ASSERT_EQUAL( 70/3, static_cast<int>(imgRect->getPixelQuick(2,0,2)));
    CPPUNIT_ASSERT_EQUAL( 98/1, static_cast<int>(imgRect->getPixelQuick(0,3,0)));
    CPPUNIT_ASSERT_EQUAL( 98/2, static_cast<int>(imgRect->getPixelQuick(0,3,1)));
    CPPUNIT_ASSERT_EQUAL( 98/3, static_cast<int>(imgRect->getPixelQuick(0,3,2)));
    CPPUNIT_ASSERT_EQUAL( 99/1, static_cast<int>(imgRect->getPixelQuick(1,3,0)));
    CPPUNIT_ASSERT_EQUAL( 99/2, static_cast<int>(imgRect->getPixelQuick(1,3,1)));
    CPPUNIT_ASSERT_EQUAL( 99/3, static_cast<int>(imgRect->getPixelQuick(1,3,2)));
    CPPUNIT_ASSERT_EQUAL(100/1, static_cast<int>(imgRect->getPixelQuick(2,3,0)));
    CPPUNIT_ASSERT_EQUAL(100/2, static_cast<int>(imgRect->getPixelQuick(2,3,1)));
    CPPUNIT_ASSERT_EQUAL(100/3, static_cast<int>(imgRect->getPixelQuick(2,3,2)));
}

void ImageTest::testImageTools()
{
    Image image(2,3);
    image.setPixel(0,0, 50);
    image.setPixel(1,0, 66);
    image.setPixel(0,1,100);
    image.setPixel(1,1,111);
    image.setPixel(0,2,200);
    image.setPixel(1,2,211);

    // min, max, minmax
    CPPUNIT_ASSERT_EQUAL(50 , static_cast<int>(image.min()));
    CPPUNIT_ASSERT_EQUAL(211, static_cast<int>(image.max()));
    Ipp8u min = 0;
    Ipp8u max = 0;
    image.minmax(min,max);
    CPPUNIT_ASSERT_EQUAL(50 , static_cast<int>(min));
    CPPUNIT_ASSERT_EQUAL(211, static_cast<int>(max));

    // minIndex, maxIndex, minmaxIndex
    Coord IMin = image.minIndex();
    Coord IMax = image.maxIndex();
    CPPUNIT_ASSERT_EQUAL(0, static_cast<int>(IMin.x));
    CPPUNIT_ASSERT_EQUAL(0, static_cast<int>(IMin.y));
    CPPUNIT_ASSERT_EQUAL(1, static_cast<int>(IMax.x));
    CPPUNIT_ASSERT_EQUAL(2, static_cast<int>(IMax.y));
    image.minmaxIndex(IMin,IMax);
    CPPUNIT_ASSERT_EQUAL(0, static_cast<int>(IMin.x));
    CPPUNIT_ASSERT_EQUAL(0, static_cast<int>(IMin.y));
    CPPUNIT_ASSERT_EQUAL(1, static_cast<int>(IMax.x));
    CPPUNIT_ASSERT_EQUAL(2, static_cast<int>(IMax.y));

    // sum,mean,meanStdDev
    CPPUNIT_ASSERT_EQUAL(738, static_cast<int>(image.sum()));
    CPPUNIT_ASSERT_EQUAL(123, static_cast<int>(image.mean()));
    double mean, stddev;
    image.meanStdDev(mean, stddev);
    CPPUNIT_ASSERT_EQUAL(123, static_cast<int>(mean));
    CPPUNIT_ASSERT_DOUBLES_EQUAL(61.811542, stddev, 0.01);

    // transpose
    image = Image(3,4);
    CPPUNIT_ASSERT_THROW(image.transpose(), ImageException);

    for(int s=1; s<=8; ++s)
    {
        image = Image(s,s);
        for(int j=0; j<image.height(); ++j)
            for(int i=0; i<image.width(); ++i)
                image.setPixel(i,j, (i+1)+j*(image.width()));
        image.transpose();
        for(int j=0; j<image.height(); ++j)
            for(int i=0; i<image.width(); ++i)
                CPPUNIT_ASSERT_EQUAL(static_cast<int>((j+1)+i*(image.width())), static_cast<int>(image.getPixel(i,j)));
    }

    // abs
    GrayImage16s* img16s = new GrayImage16s(2,3);
    img16s->setPixel(0,0, -50);
    img16s->setPixel(1,0,  33);
    img16s->setPixel(0,1,   0);
    img16s->setPixel(1,1,  -0);
    img16s->setPixel(0,2, 255);
    img16s->setPixel(1,2,-255);
    img16s->abs();
    CPPUNIT_ASSERT_EQUAL( 50, static_cast<int>(img16s->getPixel(0,0)));
    CPPUNIT_ASSERT_EQUAL( 33, static_cast<int>(img16s->getPixel(1,0)));
    CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(img16s->getPixel(0,1)));
    CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(img16s->getPixel(1,1)));
    CPPUNIT_ASSERT_EQUAL(255, static_cast<int>(img16s->getPixel(0,2)));
    CPPUNIT_ASSERT_EQUAL(255, static_cast<int>(img16s->getPixel(1,2)));
}

void ImageTest::testGrayImageBilinear() 
{
  Image image(4,3);
  for (int y = 0; y < image.height(); y++) {
    for (int x = 0; x < image.width(); x++) {
      image.setPixel(x, y, y * image.width() + x);
    }
  }
  
  for (int y = 0; y < image.height(); y++) {
    for (int x = 0; x < image.width(); x++) {
      CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(double(y * image.width() + x),
                                           image.getPixelBilinear(x, y), 1E-20);
    }
  }
  for (int y = 0; y < image.height()-1; y++) {
    for (int x = 0; x < image.width()-1; x++) {
      CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(
        double(y * image.width() + x) + 0.5, 
        image.getPixelBilinear(float(x)+0.5, y), 1E-20);
      CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(
        double(y * image.width() + x) + double(image.width()) / 2.0,
        image.getPixelBilinear(x, float(y) + 0.5), 1E-20);
    }
  }
}
