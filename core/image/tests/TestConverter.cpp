/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libimage - An image/template for new NICE libraries
 * See file License for license information.
 */

#ifdef NICE_USELIB_CPPUNIT
#include "TestConverter.h"
#include <string>
#include <exception>
#include <sstream>
#include <iomanip>
#include <iostream>

#ifdef NICE_USELIB_LIMUN_IOCOMPRESSION
#include <iocompression/md5.h>
#endif

using namespace NICE;
using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION( TestConverter );

void TestConverter::setUp() {
}

void TestConverter::tearDown() {
}

void TestConverter::testConstructor() {
}

void TestConverter::testOperators() {
}

void TestConverter::testGrayFilter() {
  int width=16, height=16;
  ImageT<short> gimg(width,height);
  ImageT<short> gbuffer(width,height);
  gbuffer = 0;
  gimg=100;
  for(int w=0;w<width;w++) {
        gimg(w,height/2) = abs(w*height/2-width);
  }
  for(int h=0;h<height;h++) {
        gimg(width/3,h) = abs(width/3-h);
  }
  gimg(0,0) = 0;
  gimg(width-1,height-1) = 0;
  {
    float karray[]={1.,0.,-1.};
    VectorT<float> kernel(karray,3);
    {
        std::stringstream inout;
        gbuffer=0;
        DeprecatedConverter::filterX(gimg,kernel,1,&gbuffer);
        inout << fixed << setw(3) << setprecision(0) << gbuffer << endl;
#ifdef NICE_USELIB_LIMUN_IOCOMPRESSION
      CPPUNIT_ASSERT_MD5_STRING("c6ea3197098b21bb8dab8fc849ce4e6c",inout.str());
#endif
    }
    {
        std::stringstream inout;
        gbuffer=0;
        DeprecatedConverter::filterX(gimg,kernel,2,&gbuffer);
        inout << fixed << setw(3) << setprecision(0) << gbuffer << endl;
#ifdef NICE_USELIB_LIMUN_IOCOMPRESSION
      CPPUNIT_ASSERT_MD5_STRING("34c67c6d452ae52e5d083b5bdd65a15f",inout.str());
#endif
    }
    {
        std::stringstream inout;
        gbuffer=0;
        DeprecatedConverter::filterX(gimg,kernel,0,&gbuffer);
        inout << fixed << setw(3) << setprecision(0) << gbuffer << endl;
#ifdef NICE_USELIB_LIMUN_IOCOMPRESSION
      CPPUNIT_ASSERT_MD5_STRING("b7dbf6cca3b44b476e71ac5c54b89882",inout.str());
#endif
    }
    {
/*
        std::stringstream inout;
        gbuffer=0;
        DeprecatedConverter::filterY(gimg,kernel,1,&gbuffer);
        inout << fixed << setw(3) << setprecision(0) << gbuffer << endl;
#ifdef NICE_USELIB_LIMUN_IOCOMPRESSION
      CPPUNIT_ASSERT_MD5_STRING("9ab894bd2c60eb9ab5270b68f5ff59b5",inout.str());
#endif
*/
    }
    {
/*	    
        std::stringstream inout;
        gbuffer=0;
        DeprecatedConverter::filterY(gimg,kernel,2,&gbuffer);
        inout << fixed << setw(3) << setprecision(0) << gbuffer << endl;
#ifdef NICE_USELIB_LIMUN_IOCOMPRESSION
      CPPUNIT_ASSERT_MD5_STRING("b575fdc2dc1d28aaf4ec84cf9d559000",inout.str());
#endif
*/
    }
    {
/*	    
        std::stringstream inout;
        gbuffer=0;
        DeprecatedConverter::filterY(gimg,kernel,0,&gbuffer);
        inout << fixed << setw(3) << setprecision(0) << gbuffer << endl;
#ifdef NICE_USELIB_LIMUN_IOCOMPRESSION
      CPPUNIT_ASSERT_MD5_STRING("5ed12d69541ec45a637547561f4bad18",inout.str());
#endif
*/
    }

    FloatImage gkern(3,3,GrayColorImageCommonImplementation::noAlignment);
    gkern(1,1)=gkern(1,0)=gkern(1,2)=0;
    gkern(0,1)=2.0;
    gkern(2,1)=-2.0;
    gkern(0,0)=gkern(0,2)=1.0;
    gkern(2,0)=gkern(2,2)=-1.0; 
    {
        std::stringstream inout;
        gbuffer=0;
        DeprecatedConverter::filter(gimg,gkern,1,1,&gbuffer);
        inout << fixed << setw(3) << setprecision(0) << gbuffer << endl;
#ifdef NICE_USELIB_LIMUN_IOCOMPRESSION
      CPPUNIT_ASSERT_MD5_STRING("796dd2b8c03ffaed06456c825ad89d6a",inout.str());
#endif
    }
    {
        std::stringstream inout;
        gbuffer=0;
        DeprecatedConverter::filter(gimg,gkern,0,0,&gbuffer);
        inout << fixed << setw(3) << setprecision(0) << gbuffer << endl;
#ifdef NICE_USELIB_LIMUN_IOCOMPRESSION
      CPPUNIT_ASSERT_MD5_STRING("81478bfeb4654208d61d9191bed7bde7",inout.str());
#endif
    }
    {
        std::stringstream inout;
        gbuffer=0;
        DeprecatedConverter::filter(gimg,gkern,2,2,&gbuffer);
        inout << fixed << setw(3) << setprecision(0) << gbuffer << endl;
#ifdef NICE_USELIB_LIMUN_IOCOMPRESSION
      CPPUNIT_ASSERT_MD5_STRING("5e3d5bdf3ea094f6cd7e8c5dca7aae4c",inout.str());
#endif
    }
  }
}

void TestConverter::testConvolution() {
  int width=16, height=16;
  FloatImage fimg(width,height);
  FloatImage fbuffer(width-2,height-2);
  fbuffer = 0;
  fimg=100;
  for(int w=0;w<width;w++) {
        fimg(w,height/2) = abs(w*height/2-width);
  }
  for(int h=0;h<height;h++) {
        fimg(width/3,h) = abs(width/3-h);
  }
  fimg(0,0) = 0;
  fimg(width-1,height-1) = 0;

    FloatImage fkern(3,3,GrayColorImageCommonImplementation::noAlignment);
    fkern(1,1)=fkern(1,0)=fkern(1,2)=0;
    fkern(0,1)=2.0;
    fkern(2,1)=-2.0;
    fkern(0,0)=fkern(0,2)=1.0;
    fkern(2,0)=fkern(2,2)=-1.0; 
    {
        std::stringstream inout;
        fbuffer=0;
        DeprecatedConverter::convolution(fimg,fkern,&fbuffer);
        inout << fixed << setw(3) << setprecision(0) << fbuffer << endl;
#ifdef NICE_USELIB_LIMUN_IOCOMPRESSION
      CPPUNIT_ASSERT_MD5_STRING("ca4f8fde956b49957f4f8ca013bd16d9",inout.str());
#endif
    }
}

void TestConverter::testFloatFilter() {
  int width=16, height=16;
  FloatImage fimg(width,height);
  FloatImage fbuffer(width,height);
  fbuffer = 0;
  fimg=100;
  for(int w=0;w<width;w++) {
        fimg(w,height/2) = abs(w*height/2-width);
  }
  for(int h=0;h<height;h++) {
        fimg(width/3,h) = abs(width/3-h);
  }
  fimg(0,0) = 0;
  fimg(width-1,height-1) = 0;
  {
    VectorT<float> kernel(3);
    for(int i=0;i<(int)kernel.size();i++) {
        kernel[i] = (1-i);
    }
    {
        std::stringstream inout;
        fbuffer=0;
        DeprecatedConverter::filterX(fimg,kernel,1,&fbuffer);
        inout << fixed << setw(3) << setprecision(0) << fbuffer << endl;
#ifdef NICE_USELIB_LIMUN_IOCOMPRESSION
      CPPUNIT_ASSERT_MD5_STRING("c6ea3197098b21bb8dab8fc849ce4e6c",inout.str());
#endif
    }
    {
        std::stringstream inout;
        fbuffer=0;
        DeprecatedConverter::filterX(fimg,kernel,2,&fbuffer);
        inout << fixed << setw(3) << setprecision(0) << fbuffer << endl;
#ifdef NICE_USELIB_LIMUN_IOCOMPRESSION
      CPPUNIT_ASSERT_MD5_STRING("34c67c6d452ae52e5d083b5bdd65a15f",inout.str());
#endif
    }
    {
        std::stringstream inout;
        fbuffer=0;
        DeprecatedConverter::filterX(fimg,kernel,0,&fbuffer);
        inout << fixed << setw(3) << setprecision(0) << fbuffer << endl;
#ifdef NICE_USELIB_LIMUN_IOCOMPRESSION
      CPPUNIT_ASSERT_MD5_STRING("b7dbf6cca3b44b476e71ac5c54b89882",inout.str());
#endif
    }
    {
/*	    
        std::stringstream inout;
        fbuffer=0;
        DeprecatedConverter::filterY(fimg,kernel,1,&fbuffer);
        inout << fixed << setw(3) << setprecision(0) << fbuffer << endl;
#ifdef NICE_USELIB_LIMUN_IOCOMPRESSION
      CPPUNIT_ASSERT_MD5_STRING("9ab894bd2c60eb9ab5270b68f5ff59b5",inout.str());
#endif
*/
    }
    {
/*   
        std::stringstream inout;
        fbuffer=0;
        DeprecatedConverter::filterY(fimg,kernel,2,&fbuffer);
        inout << fixed << setw(3) << setprecision(0) << fbuffer << endl;
#ifdef NICE_USELIB_LIMUN_IOCOMPRESSION
      CPPUNIT_ASSERT_MD5_STRING("b575fdc2dc1d28aaf4ec84cf9d559000",inout.str());
#endif
*/
    }
    {
/*	    
        std::stringstream inout;
        fbuffer=0;
        DeprecatedConverter::filterY(fimg,kernel,0,&fbuffer);
        inout << fixed << setw(3) << setprecision(0) << fbuffer << endl;
#ifdef NICE_USELIB_LIMUN_IOCOMPRESSION
      CPPUNIT_ASSERT_MD5_STRING("5ed12d69541ec45a637547561f4bad18",inout.str());
#endif
*/
    }

    FloatImage fkern(3,3,GrayColorImageCommonImplementation::noAlignment);
    fkern(1,1)=fkern(1,0)=fkern(1,2)=0;
    fkern(0,1)=2.0;
    fkern(2,1)=-2.0;
    fkern(0,0)=fkern(0,2)=1.0;
    fkern(2,0)=fkern(2,2)=-1.0; 
    fkern.mirror(ippAxsBoth);
    {
        std::stringstream inout;
        fbuffer=0;
        DeprecatedConverter::filter(fimg,fkern,1,1,&fbuffer);
        inout << fixed << setw(3) << setprecision(0) << fbuffer << endl;
#ifdef NICE_USELIB_LIMUN_IOCOMPRESSION
      CPPUNIT_ASSERT_MD5_STRING("796dd2b8c03ffaed06456c825ad89d6a",inout.str());
#endif
    }
    {
        std::stringstream inout;
        fbuffer=0;
        DeprecatedConverter::filter(fimg,fkern,0,0,&fbuffer);
        inout << fixed << setw(3) << setprecision(0) << fbuffer << endl;
#ifdef NICE_USELIB_LIMUN_IOCOMPRESSION
      CPPUNIT_ASSERT_MD5_STRING("81478bfeb4654208d61d9191bed7bde7",inout.str());
#endif
    }
    {
        std::stringstream inout;
        fbuffer=0;
        DeprecatedConverter::filter(fimg,fkern,2,2,&fbuffer);
        inout << fixed << setw(3) << setprecision(0) << fbuffer << endl;
#ifdef NICE_USELIB_LIMUN_IOCOMPRESSION
      CPPUNIT_ASSERT_MD5_STRING("5e3d5bdf3ea094f6cd7e8c5dca7aae4c",inout.str());
#endif
    }
  }
}

void TestConverter::testHistogram() {
  int width=16, height=16;
  Image gimg(width,height,GrayColorImageCommonImplementation::noAlignment);
  int p=0;
  for(int w=0;w<width;w++)
        for(int h=0;h<height;h++,p++) {
          gimg.setPixel(w,h, p);
        }
  VectorT<int> *histo = DeprecatedConverter::histogram(gimg);
  VectorT<int> *cumuhisto = DeprecatedConverter::histogramCumulative(gimg);
  VectorT<float> *normhisto = DeprecatedConverter::histogramNormalized(gimg);
  {
	std::stringstream inout;
	for(uint i=0;i<histo->size();i++) {
		inout << (*histo)[i] << " ";
	}
#ifdef NICE_USELIB_LIMUN_IOCOMPRESSION
      CPPUNIT_ASSERT_MD5_STRING("e1424600e005af0c45dd405d3e71e6b5",inout.str());
#endif
  }
  {
	std::stringstream inout;
	for(uint i=0;i<cumuhisto->size();i++) {
		inout << (*cumuhisto)[i] << " ";
	}
#ifdef NICE_USELIB_LIMUN_IOCOMPRESSION
      CPPUNIT_ASSERT_MD5_STRING("9261e264e6848d33f223c726d54cbdd6",inout.str());
#endif
  }
  {
	std::stringstream inout;
	for(uint i=0;i<normhisto->size();i++) {
		inout << (*normhisto)[i] << " ";
	}
#ifdef NICE_USELIB_LIMUN_IOCOMPRESSION
      CPPUNIT_ASSERT_MD5_STRING("73e2f2a300d678a44eda8cc08a9ce502",inout.str());
#endif
  }
  ColorImage cimg(width,height,GrayColorImageCommonImplementation::noAlignment);
  p=0;
  for(int w=0;w<width;w++)
        for(int h=0;h<height;h++,p++) {
          cimg.setPixel(w,h, p, p, p);
        }
  VectorT<int> *color_histo = DeprecatedConverter::histogram(cimg);
  VectorT<int> *color_cumuhisto = DeprecatedConverter::histogramCumulative(cimg);
  VectorT<float> *color_normhisto = DeprecatedConverter::histogramNormalized(cimg);
  {
	std::stringstream inout;
	for(uint i=0;i<color_histo->size();i++) {
		inout << (*color_histo)[i] << " ";
	}
#ifdef NICE_USELIB_LIMUN_IOCOMPRESSION
      CPPUNIT_ASSERT_MD5_STRING("da9470d8c8079238380a20695973d03b",inout.str());
#endif
  }
  {
	std::stringstream inout;
	for(uint i=0;i<color_cumuhisto->size();i++) {
		inout << (*color_cumuhisto)[i] << " ";
	}
#ifdef NICE_USELIB_LIMUN_IOCOMPRESSION
      CPPUNIT_ASSERT_MD5_STRING("4eb56a726ee138c35cd8a69179e34ccc",inout.str());
#endif
  }
  {
	std::stringstream inout;
	for(uint i=0;i<color_normhisto->size();i++) {
		inout << (*color_normhisto)[i] << " ";
	}
#ifdef NICE_USELIB_LIMUN_IOCOMPRESSION
      CPPUNIT_ASSERT_MD5_STRING("f0187401062bec17c699456ea4907bdb",inout.str());
#endif
  }
}


void TestConverter::testSomething() {
  int width=8, height=8;
  ColorImage cimg(width,height,GrayColorImageCommonImplementation::noAlignment);
  for(int w=0;w<width;w++)
        for(int h=0;h<height;h++) {
          cimg.setPixel(w,h, (w*h)*7,(w*h)*12,(w*h)*9);
        }
  cimg.setPixel(0,0,255,255,255);
  Image gimg(width,height, GrayColorImageCommonImplementation::noAlignment);
  CPPUNIT_ASSERT_NO_THROW(DeprecatedConverter::rgbToGray(cimg, &gimg));
  std::stringstream inout;
  for(int w=0;w<width;w++) {
        for(int h=0;h<height;h++) {
         	 inout << (int)gimg.getPixel(w,h) << " ";
        }
		inout << endl;
  }
#ifdef NICE_USELIB_LIMUN_IOCOMPRESSION
  	  // allow both conversions
	  try {
		// correct conversion
	  	CPPUNIT_ASSERT_MD5_STRING("aa9e7d699518e0e33c97ae673decbeeb", inout.str());
	  } catch(exception e) {
		// conversion with ipp bug (not rounded) 255,255,255 -> 254
	  	CPPUNIT_ASSERT_MD5_STRING("3c693fccf4abc0095a0a9fe991d8c3ee", inout.str());
	  }
#endif
}
#endif

void TestConverter::testGaussFilter() {
  int width=16, height=16;
  Image gimg(width,height);
  Image gbuffer(width,height);
  gbuffer = 0;
  gimg=100;
  for(int w=0;w<width;w++) {
        gimg(w,height/2) = abs(w*height/2-width);
  }
  for(int h=0;h<height;h++) {
        gimg(width/3,h) = abs(width/3-h);
  }
  gimg(0,0) = 0;
  gimg(width-1,height-1) = 0;
    {
        std::stringstream inout;
        gbuffer=0;
        std::string fileName("testGaussfilter-orig.png");
        std::string fileNameTest("testGaussfilter-gauss-1.png");
        gimg.write(ImageFile(fileName));
        DeprecatedConverter::filterGauss(gimg,0.85,&gbuffer);
        gbuffer.write(ImageFile(fileNameTest));
        inout << fixed << setw(3) << setprecision(0) << gbuffer << endl;
        remove(fileName.c_str());
        remove(fileNameTest.c_str());
#ifdef NICE_USELIB_LIMUN_IOCOMPRESSION
  //    CPPUNIT_ASSERT_MD5_STRING("b7dbf6cca3b44b476e71ac5c54b89882",inout.str());
#endif
    }
}

