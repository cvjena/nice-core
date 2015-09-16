/*
 *
 * NICE-Core - efficient algebra and computer vision methods
 *  - libimage - An image/template for new NICE libraries
 * See file License for license information.
 */

#ifdef NICE_USELIB_CPPUNIT
#include "TestImageFile.h"
#include <string>
#include <exception>

#include <core/image/ColorImageT.h>
#include <core/image/ImageOperators.h>
#include <sstream>

#ifdef NICE_USELIB_LIMUN_IOCOMPRESSION
#include <iocompression/md5.h>
#endif

using namespace NICE;
using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION( TestImageFile );

void TestImageFile::setUp() {
}

void TestImageFile::tearDown() {
}

void TestImageFile::testConstructor() {
}

void TestImageFile::testFloatPXM() 
{
/*
    int width=32;
    int height=8;
    ColorImage c(width,height);
    for(int j=0;j<height;j++)
        for(int i=0;i<width;i++) 
        {
            c.setPixel(i,j,0,i*j);
            c.setPixel(i,j,1,i*j+i);
            c.setPixel(i,j,2,i*j+j*3);
        }

    Image g(width,height);
    rgbToGray(c,&g);
    c.write(ImageFile("test-float.ppm"));
    ColorImageT<Ipp32f> newc;
    newc.read(ImageFile("test-float.ppm"));


    FloatImage newf(width,height);
    newf.read(ImageFile("test-float.ppm"));
    Image newg(width,height);
    convertBitDepth(newf,&newg);
    newg.write(ImageFile("test-floatcmp.ppm"));

    #ifdef NICE_USELIB_LIMUN_IOCOMPRESSION
    {
        std::stringstream inout; inout << g;
        std::stringstream inout1; inout1 << newg;
        CPPUNIT_ASSERT_EQUAL(inout.str(),inout1.str());
    }

    {
        std::stringstream inout; inout << c;
        std::stringstream inout1; inout1 << newc;
        CPPUNIT_ASSERT_EQUAL(inout.str(),inout1.str());
    }
    #endif
    system("rm test-float.ppm");
*/
}

void TestImageFile::testFloatImage()
{
/*
  int width=32;
  int height=8;
  ColorImage c(width,height);
  for(int j=0;j<height;j++) {
  	for(int i=0;i<width;i++) {
		c.setPixel(i,j,0,i*j);
		c.setPixel(i,j,1,i*j+i);
		c.setPixel(i,j,2,i*j+j*3);
	}
  }
  Image g(width,height);
  rgbToGray(c,&g);
  c.write(ImageFile("test-float.png"));
  ColorImageT<Ipp32f> newc;
  newc.read(ImageFile("test-float.png"));

  ColorImage newc2(width,height);
  convertBitDepth(newc,&newc2);
  FloatImage newf(width,height);
  newf.read(ImageFile("test-float.png"));
  Image newg(width,height);
  convertBitDepth(newf,&newg);

    #ifdef NICE_USELIB_LIMUN_IOCOMPRESSION
    {
	   std::stringstream inout; inout << g;
	   std::stringstream inout1; inout1 << newg;
        CPPUNIT_ASSERT_EQUAL(inout.str(),inout1.str());
    }
    {
        std::stringstream inout; inout << c;
        std::stringstream inout1; inout1 << newc2;
        CPPUNIT_ASSERT_EQUAL(inout.str(),inout1.str());
    }
    #endif
    system("rm test-float.png");
*/
}

void TestImageFile::testColorImage() {
  int width=31;
  int height=8;
  ColorImage c(width,height);
  for(int i=0;i<width;i++) {
  	for(int j=0;j<height;j++) {
		c.setPixel(i,j,0,i*j);
		c.setPixel(i,j,1,i*j+i);
		c.setPixel(i,j,2,i*j+j*3);
	}
  }
  c.write(ImageFile("test-color.png"));
  ColorImage newc;
  newc.read(ImageFile("test-color.png"));
  newc.write(ImageFile("test-color.ppm"));
  ColorImage newc2(width,height);
  newc2.read(ImageFile("test-color.ppm"));

  std::stringstream inout;
  for(int w=0;w<width;w++) {
        for(int h=0;h<height;h++) {
			for(int channel=0;channel<3;channel++) {
         	  int g_c = static_cast<int>(c.getPixel(w,h,channel));
			  int g_newc = static_cast<int>(newc.getPixel(w,h,channel));
			  int g_newc2 = static_cast<int>(newc2.getPixel(w,h,channel));
			  CPPUNIT_ASSERT_EQUAL( g_c, g_newc );
			  CPPUNIT_ASSERT_EQUAL( g_c, g_newc2 );
			}
        }
  }
	
	system("rm test-color.png test-color.ppm");
}
void TestImageFile::testGrayImage() {
  int width=9;
  int height=32;
  Image orig(width,height);
  for(int i=0;i<width;i++) {
  	for(int j=0;j<height;j++) {
		orig.setPixel(i,j,i*j);
	}
  }
  orig.write(ImageFile("test.png"));

  ImageFile imgf ("test.png");
  CPPUNIT_ASSERT_EQUAL( width, (int)imgf.width() );
  CPPUNIT_ASSERT_EQUAL( height, (int)imgf.height() );

  // getHeader() for ImageMagick formats is not yet defined.
  // Therefore, we need the PNG library here to issue getHeader().
  ImageFile::Header imgfheader = imgf.getHeader();
  CPPUNIT_ASSERT_EQUAL( height, imgfheader.height );
  CPPUNIT_ASSERT_EQUAL( width, imgfheader.width );

  vector<Image> gray(4);
  gray[0].read(ImageFile("test.png"));
  gray[0].write(ImageFile("test.pgm"));
  gray[1].read(ImageFile("test.pgm"));
  gray[1].write(ImageFile("test.ppm"));
  gray[2].read(ImageFile("test.ppm"));
  ColorImage c(width,height);
  c.read(ImageFile("test.pgm"));
  c.write(ImageFile("testc.pgm"));
  gray[3].read(ImageFile("testc.pgm"));

    for(int i=0;i<4;i++) 
    {
	   for(int w=0;w<width;w++) {
			 for(int h=0;h<height;h++) {
				    int g_w = static_cast<int>(gray[i].getPixel(w,h));
					int g_orig = static_cast<int>(orig.getPixel(w,h));
					CPPUNIT_ASSERT_EQUAL( g_orig, g_w );
			 }
	   }
    }
	system("rm test.png test.pgm test.ppm testc.pgm");
}


void TestImageFile::testJPG_IO()
{
    // Image
    {
        Image src(4,1);
        src(0,0) =   0;
        src(1,0) = 100;
        src(2,0) = 160;
        src(3,0) = 255;

        src.write(ImageFile("gray-out.jpg"));

	ImageFile imgf ("gray-out.jpg");
        CPPUNIT_ASSERT_EQUAL( src.width(), (int)imgf.width() );
        CPPUNIT_ASSERT_EQUAL( src.height(), (int)imgf.height() );

        Image in;
        in.read(ImageFile("gray-out.jpg"));

        for(int i=0; i<src.width(); ++i)
            CPPUNIT_ASSERT_EQUAL(static_cast<int>(src(i,0)),static_cast<int>(in(i,0)));

        system("rm gray-out.jpg");
    }

    // ImageT<Ipp32f>
    {
        ImageT<Ipp32f> src(5,1);
        src(0,0) =  -10.5;
        src(1,0) =    0.0;
        src(2,0) = 199.75;
        src(3,0) =  255.0;
        src(4,0) =  300.5;

        src.write(ImageFile("gray-float-out.jpg"));

        ImageT<Ipp32f> in;
        in.read(ImageFile("gray-float-out.jpg"));

        CPPUNIT_ASSERT_DOUBLES_EQUAL(  0.0,static_cast<int>(in(0,0)), 0.0001);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(  0.0,static_cast<int>(in(1,0)), 0.0001);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(199.0,static_cast<int>(in(2,0)), 0.0001);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(255.0,static_cast<int>(in(3,0)), 0.0001);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(255.0,static_cast<int>(in(4,0)), 0.0001);

        system("rm gray-float-out.jpg");
    }

    // ColorImage
    {
        ColorImage src(4,1);
        src.setPixelQuick(0,0,   0,  0,  0);
        src.setPixelQuick(1,0, 100,100,100);
        src.setPixelQuick(2,0, 160,160,160);
        src.setPixelQuick(3,0, 255,255,255);

        src.write(ImageFile("color-out.jpg"));
	ImageFile imgf ("color-out.jpg");
        CPPUNIT_ASSERT_EQUAL( src.width(), (int)imgf.width() );
        CPPUNIT_ASSERT_EQUAL( src.height(), (int)imgf.height() );
        CPPUNIT_ASSERT_EQUAL( imgf.getHeader().channel, 3 );

        ColorImage in;
        in.read(ImageFile("color-out.jpg"));

        for(int i=0; i<src.width(); ++i)
            for(int c=0; c<3; ++c)
            CPPUNIT_ASSERT_EQUAL(static_cast<int>(src(i,0,c)),static_cast<int>(in(i,0,c)));

        system("rm color-out.jpg");
    }

    // ColorImageT<Ipp32f>
    {
        ColorImageT<Ipp32f> src(5,1);
        src.setPixelQuick(0,0,  -10.5,  -10.5,  -10.5);
        src.setPixelQuick(1,0,    0.0,    0.0,    0.0);
        src.setPixelQuick(2,0, 199.75, 199.75, 199.75);
        src.setPixelQuick(3,0,  255.0,  255.0,  255.0);
        src.setPixelQuick(4,0,  300.5,  300.5,  300.5);

        src.write(ImageFile("color-float-out.jpg"));

        ColorImageT<Ipp32f> in;
        in.read(ImageFile("color-float-out.jpg"));

        for(int i=0; i<3; ++i) {
            CPPUNIT_ASSERT_DOUBLES_EQUAL(  0.0,static_cast<int>(in(0,0,i)), 0.0001);
            CPPUNIT_ASSERT_DOUBLES_EQUAL(  0.0,static_cast<int>(in(1,0,i)), 0.0001);
            CPPUNIT_ASSERT_DOUBLES_EQUAL(199.0,static_cast<int>(in(2,0,i)), 0.0001);
            CPPUNIT_ASSERT_DOUBLES_EQUAL(255.0,static_cast<int>(in(3,0,i)), 0.0001);
            CPPUNIT_ASSERT_DOUBLES_EQUAL(255.0,static_cast<int>(in(4,0,i)), 0.0001);
        }

        system("rm color-float-out.jpg");
    }
}

void TestImageFile::testInvalidFileName() {
	ImageFile image_file;
	ImageFile::Format fileformat = image_file.name2Format("nodothere");
	CPPUNIT_ASSERT_EQUAL(fileformat,ImageFile::FormatUnknown);
}

#endif






