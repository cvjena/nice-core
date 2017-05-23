/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libimage - An image/template for new NICE libraries
 * See file License for license information.
 */

#ifdef NICE_USELIB_CPPUNIT

#include "TestImageTools.h"
#include <string>

#include "core/image/ImageTools.h"
//#include "core/image/Filter.h"
#include "core/image/LineT.h"

#ifdef NICE_USELIB_LIMUN_IOCOMPRESSION
    #include <iocompression/md5.h>
#endif

using namespace std;
using namespace NICE;

CPPUNIT_TEST_SUITE_REGISTRATION( TestImageTools );

void TestImageTools::setUp()
{
}

void TestImageTools::tearDown()
{
}

void TestImageTools::testaddConstBorder()
{
    #ifdef NICE_USELIB_IPP
        Image test(3,5);
        test(2,4)=128;
        test(1,3)=128;
        test(0,0)=128;
        Image testwithborder;
        addConstBorder(test,4,2,(Ipp8u)(255),&testwithborder);
        std::string fileName("whiteborder.png");
        testwithborder.write(ImageFile(fileName));
        #ifdef NICE_USELIB_LIMUN_IOCOMPRESSION
            CPPUNIT_ASSERT_MD5_FILE("d41d8cd98f00b204e9800998ecf8427e","whiteborder.pgm");
        #endif
        remove(fileName.c_str());
    #endif //NICE_USELIB_IPP
}

void TestImageTools::testautoCropRect()
{
    Image test(41,37);
    test=0;
    Rect rect;
    Ipp8u value=2;
    autoCropRect(test,value,rect);
    CPPUNIT_ASSERT_EQUAL(Rect(0,0,0,0),rect);
    test(10,7)=3;
    autoCropRect(test,value,rect);
    CPPUNIT_ASSERT_EQUAL(Rect(10,7,1,1),rect);
    test(10,15)=3;
    autoCropRect(test,value,rect);
    CPPUNIT_ASSERT_EQUAL(Rect(10,7,1,9),rect);
    test(15,5)=3;
    autoCropRect(test,value,rect);
    CPPUNIT_ASSERT_EQUAL(Rect(10,5,6,11),rect);
}

void TestImageTools::testfindLocalMinima()
{
    Image test(64,64);
    for(int y=0;y<64;y++) {
        for(int x=0;x<64;x++) {
            test(x,y)=4*(x%16+y%16);
        }
    }
    {
        Ipp8u thresh=40;
        std::vector<Coord> minima;
        findLocalMinima(test, thresh, 10, minima);
        Image test2(test);
        for(uint i=0;i<minima.size();i++) {
            test2(minima[i])=255;
        }
        test2.write(ImageFile("testfindLocalMinima.pgm"));

        #ifdef NICE_USELIB_LIMUN_IOCOMPRESSION
            CPPUNIT_ASSERT_MD5_FILE("ae5d33b62395a8c4db8e4c8780d854d8","testfindLocalMinima.pgm");
        #endif

        system("rm -f testfindLocalMinima.pgm");
    }
    {
        Ipp8u thresh=100;
        std::vector<Coord> minima;
        findLocalMinima(test, thresh, 30, minima);
        Image test2(test);
        for(uint i=0;i<minima.size();i++) {
            test2(minima[i])=255;
        }
        test2.write(ImageFile("testfindLocalMinima2.pgm"));

        #ifdef NICE_USELIB_LIMUN_IOCOMPRESSION
            CPPUNIT_ASSERT_MD5_FILE("a8ff018660e40252b6794f4e03128b42","testfindLocalMinima2.pgm");
        #endif

        system("rm -f testfindLocalMinima2.pgm");
    }
}

void TestImageTools::testabsDiff()
{
    // Image: absDiff
    {
        // exception
        CPPUNIT_ASSERT_THROW(absDiff(Image(1,1), Image(3,4)), ImageException);

        //
        Image src1(3,3), src2(3,3);
        src1(0,0) =  3; src1(1,0) = 81; src1(2,0) =  0;
        src1(0,1) = 12; src1(1,1) =  8; src1(2,1) =  1;
        src1(0,2) =  9; src1(1,2) = 18; src1(2,2) = 38;

        src2(0,0) = 18; src2(1,0) = 39; src2(2,0) =  0;
        src2(0,1) = 37; src2(1,1) =  5; src2(2,1) =  2;
        src2(0,2) =  3; src2(1,2) =  1; src2(2,2) =  1;

        Image* result = absDiff(src1, src2);

        CPPUNIT_ASSERT_EQUAL( 15, static_cast<int>(result->getPixel(0,0)));
        CPPUNIT_ASSERT_EQUAL( 25, static_cast<int>(result->getPixel(0,1)));
        CPPUNIT_ASSERT_EQUAL(  6, static_cast<int>(result->getPixel(0,2)));
        CPPUNIT_ASSERT_EQUAL( 42, static_cast<int>(result->getPixel(1,0)));
        CPPUNIT_ASSERT_EQUAL(  3, static_cast<int>(result->getPixel(1,1)));
        CPPUNIT_ASSERT_EQUAL( 17, static_cast<int>(result->getPixel(1,2)));
        CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel(2,0)));
        CPPUNIT_ASSERT_EQUAL(  1, static_cast<int>(result->getPixel(2,1)));
        CPPUNIT_ASSERT_EQUAL( 37, static_cast<int>(result->getPixel(2,2)));
    }
    // ColorImage: absDiff
    {
        // exception
        CPPUNIT_ASSERT_THROW(absDiff(ColorImage(1,1), ColorImage(3,4)), ImageException);

        //
        ColorImage src1(3,3), src2(3,3);

        for(int i=0; i<3; ++i)
        {
            src1(0,0,i) =  3; src1(1,0,i) = 81; src1(2,0,i) =  0;
            src1(0,1,i) = 12; src1(1,1,i) =  8; src1(2,1,i) =  1;
            src1(0,2,i) =  9; src1(1,2,i) = 18; src1(2,2,i) = 38;

            src2(0,0,i) = 18; src2(1,0,i) = 39; src2(2,0,i) =  0;
            src2(0,1,i) = 37; src2(1,1,i) =  5; src2(2,1,i) =  2;
            src2(0,2,i) =  3; src2(1,2,i) =  1; src2(2,2,i) =  1;
        }

        ColorImage* result = absDiff(src1, src2);

        for(int i=0; i<3; ++i)
        {
            CPPUNIT_ASSERT_EQUAL( 15, static_cast<int>(result->getPixel(0,0,i)));
            CPPUNIT_ASSERT_EQUAL( 25, static_cast<int>(result->getPixel(0,1,i)));
            CPPUNIT_ASSERT_EQUAL(  6, static_cast<int>(result->getPixel(0,2,i)));
            CPPUNIT_ASSERT_EQUAL( 42, static_cast<int>(result->getPixel(1,0,i)));
            CPPUNIT_ASSERT_EQUAL(  3, static_cast<int>(result->getPixel(1,1,i)));
            CPPUNIT_ASSERT_EQUAL( 17, static_cast<int>(result->getPixel(1,2,i)));
            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel(2,0,i)));
            CPPUNIT_ASSERT_EQUAL(  1, static_cast<int>(result->getPixel(2,1,i)));
            CPPUNIT_ASSERT_EQUAL( 37, static_cast<int>(result->getPixel(2,2,i)));
        }
    }
}

void TestImageTools::testBoolean()
{
    // Image: and
    {
        // exception
        CPPUNIT_ASSERT_THROW(And(Image(1,1), Image(3,4)), ImageException);

        //
        Image srcAnd(8,8);
        for(int y=0; y<srcAnd.height(); ++y)
            for(int x=0; x<srcAnd.width(); ++x)
                srcAnd.setPixelQuick(x,y, (x+1)+y*srcAnd.width());

        Image src(srcAnd.width(), srcAnd.height());
        Image* result;

        src.set(1);
        result = And(srcAnd, src);
        for(int y=0; y<srcAnd.height(); ++y)
            for(int x=0; x<srcAnd.width(); ++x)
                if(x%2==0)
                    CPPUNIT_ASSERT_EQUAL(  1, static_cast<int>(result->getPixel(x,y)));
                else
                    CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel(x,y)));

        src.set(2);
        result = And(srcAnd, src);
        for(int y=0; y<srcAnd.height(); ++y)
            for(int x=0; x<srcAnd.width(); ++x)
                if(x==1 || x==2 || x==5 || x==6)
                    CPPUNIT_ASSERT_EQUAL(  2, static_cast<int>(result->getPixel(x,y)));
                else
                    CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel(x,y)));

        src.set(4);
        result = And(srcAnd, src);
        for(int y=0; y<srcAnd.height(); ++y)
            for(int x=0; x<srcAnd.width(); ++x)
                if(x>=3 && x<=6)
                    CPPUNIT_ASSERT_EQUAL(  4, static_cast<int>(result->getPixel(x,y)));
                else
                    CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel(x,y)));

        src.set(8);
        result = And(srcAnd, src);
        for(int y=0; y<srcAnd.height(); ++y)
            for(int x=0; x<srcAnd.width(); ++x)
                if( (y%2==1&&x!=7) || (y%2==0&&x==7) )
                    CPPUNIT_ASSERT_EQUAL(  8, static_cast<int>(result->getPixel(x,y)));
                else
                    CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel(x,y)));
    }
    // ColorImage: absDiff
    {
        // exception
        CPPUNIT_ASSERT_THROW(And(ColorImage(1,1), ColorImage(3,4)), ImageException);

        //
        ColorImage srcAnd(8,8);
        for(int y=0; y<srcAnd.height(); ++y)
            for(int x=0; x<srcAnd.width(); ++x)
                for(int i=0; i<3; ++i)
                    srcAnd.setPixelQuick(x,y,i, (x+1)+y*srcAnd.width());

        ColorImage src(8,8);
        ColorImage* result;

        src.set(1,1,1);
        result = And(srcAnd, src);
        for(int y=0; y<srcAnd.height(); ++y)
            for(int x=0; x<srcAnd.width(); ++x)
                for(int i=0; i<3; ++i)
                    if(x%2==0)
                        CPPUNIT_ASSERT_EQUAL(  1, static_cast<int>(result->getPixel(x,y,i)));
                    else
                        CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel(x,y,i)));

        src.set(2,2,2);
        result = And(srcAnd, src);
        for(int y=0; y<srcAnd.height(); ++y)
            for(int x=0; x<srcAnd.width(); ++x)
                for(int i=0; i<3; ++i)
                    if(x==1 || x==2 || x==5 || x==6)
                        CPPUNIT_ASSERT_EQUAL(  2, static_cast<int>(result->getPixel(x,y,i)));
                    else
                        CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel(x,y,i)));

        src.set(4,4,4);
        result = And(srcAnd, src);
        for(int y=0; y<srcAnd.height(); ++y)
            for(int x=0; x<srcAnd.width(); ++x)
                for(int i=0; i<3; ++i)
                    if(x>=3 && x<=6)
                        CPPUNIT_ASSERT_EQUAL(  4, static_cast<int>(result->getPixel(x,y,i)));
                    else
                        CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel(x,y,i)));

        src.set(8,8,8);
        result = And(srcAnd, src);
        for(int y=0; y<srcAnd.height(); ++y)
            for(int x=0; x<srcAnd.width(); ++x)
                for(int i=0; i<3; ++i)
                    if( (y%2==1&&x!=7) || (y%2==0&&x==7) )
                        CPPUNIT_ASSERT_EQUAL(  8, static_cast<int>(result->getPixel(x,y,i)));
                    else
                        CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel(x,y,i)));
    }
}

void TestImageTools::testTreshold()
{
    int size = 21;
    Image src(size,size);
    for(int y=0; y<src.height(); ++y)
        for(int x=0; x<src.width(); ++x)
            src.setPixelQuick(x,y, x+y);

    Image* result = new Image(src.width(), src.height());

    // lowerThreshold
    {
        // with default value
        for(int t=0; t<=40; ++t) {
            result = lowerThreshold(src, t, result);
            for(int y=0; y<src.height(); ++y)
                for(int x=0; x<src.width(); ++x)
                    if(x+y<=t)
                        CPPUNIT_ASSERT_EQUAL(0, static_cast<int>(result->getPixelQuick(x,y)));
                    else
                        CPPUNIT_ASSERT_EQUAL(static_cast<int>(src.getPixelQuick(x,y)),
                                             static_cast<int>(result->getPixelQuick(x,y)));
        }
        // with another value as the default
        for(int t=0; t<=40; ++t) {
            result = lowerThreshold(src, t, result, 33);
            for(int y=0; y<src.height(); ++y)
                for(int x=0; x<src.width(); ++x)
                    if(x+y<=t)
                        CPPUNIT_ASSERT_EQUAL(33, static_cast<int>(result->getPixelQuick(x,y)));
                    else
                        CPPUNIT_ASSERT_EQUAL(static_cast<int>(src.getPixelQuick(x,y)),
                                             static_cast<int>(result->getPixelQuick(x,y)));
        }
    }
    // upperThreshold
    {
        for(int t=0; t<=40; ++t) {
            result = upperThreshold(src, t, result);
            for(int y=0; y<src.height(); ++y)
                for(int x=0; x<src.width(); ++x)
                    if(x+y>t)
                        CPPUNIT_ASSERT_EQUAL(255, static_cast<int>(result->getPixelQuick(x,y)));
                    else
                        CPPUNIT_ASSERT_EQUAL(static_cast<int>(src.getPixelQuick(x,y)),
                                             static_cast<int>(result->getPixelQuick(x,y)));
        }
        // with another value as the default
        for(int t=0; t<=40; ++t) {
            result = upperThreshold(src, t, result, 33);
            for(int y=0; y<src.height(); ++y)
                for(int x=0; x<src.width(); ++x)
                    if(x+y>t)
                        CPPUNIT_ASSERT_EQUAL(33, static_cast<int>(result->getPixelQuick(x,y)));
                    else
                        CPPUNIT_ASSERT_EQUAL(static_cast<int>(src.getPixelQuick(x,y)),
                                             static_cast<int>(result->getPixelQuick(x,y)));
        }
    }
    // threshold
    {
        for(int t=0; t<=40; ++t) {
            result = threshold(src, t, result);
            for(int y=0; y<src.height(); ++y)
                for(int x=0; x<src.width(); ++x)
                    if(x+y<=t)
                        CPPUNIT_ASSERT_EQUAL(0  , static_cast<int>(result->getPixelQuick(x,y)));
                    else
                        CPPUNIT_ASSERT_EQUAL(255, static_cast<int>(result->getPixelQuick(x,y)));
        }
    }
    // lowerThresholdIP
    {
        Image r(src.width(), src.height());
        for(int t=0; t<=40; ++t) {
            result = lowerThreshold(src, t, result);
            r      = Image(src);
            lowerThresholdIP(r, t);
            for(int y=0; y<src.height(); ++y)
                for(int x=0; x<src.width(); ++x)
                    CPPUNIT_ASSERT_EQUAL(static_cast<int>(result->getPixelQuick(x,y)),
                                         static_cast<int>(r.getPixelQuick(x,y)));
        }
        // with another value as the default
        for(int t=0; t<=40; ++t) {
            result = lowerThreshold(src, t, result, 33);
            r      = Image(src);
            lowerThresholdIP(r, t, 33);
            for(int y=0; y<src.height(); ++y)
                for(int x=0; x<src.width(); ++x)
                    CPPUNIT_ASSERT_EQUAL(static_cast<int>(result->getPixelQuick(x,y)),
                                         static_cast<int>(r.getPixelQuick(x,y)));
        }
    }
    // upperThresholdIP
    {
        Image r(src.width(), src.height());
        for(int t=0; t<=40; ++t) {
            result = upperThreshold(src, t, result);
            r      = Image(src);
            upperThresholdIP(r, t);
            for(int y=0; y<src.height(); ++y)
                for(int x=0; x<src.width(); ++x)
                    CPPUNIT_ASSERT_EQUAL(static_cast<int>(result->getPixelQuick(x,y)),
                                         static_cast<int>(r.getPixelQuick(x,y)));
        }
        // with another value as the default
        for(int t=0; t<=40; ++t) {
            result = upperThreshold(src, t, result, 33);
            r      = Image(src);
            upperThresholdIP(r, t, 33);
            for(int y=0; y<src.height(); ++y)
                for(int x=0; x<src.width(); ++x)
                    CPPUNIT_ASSERT_EQUAL(static_cast<int>(result->getPixelQuick(x,y)),
                                         static_cast<int>(r.getPixelQuick(x,y)));
        }
    }
    // thresholdIP
    {
        Image r(src.width(), src.height());
        for(int t=0; t<=40; ++t) {
            result = threshold(src, t, result);
            r      = Image(src);
            thresholdIP(r, t);
            for(int y=0; y<src.height(); ++y)
                for(int x=0; x<src.width(); ++x)
                    CPPUNIT_ASSERT_EQUAL(static_cast<int>(result->getPixelQuick(x,y)),
                                         static_cast<int>(r.getPixelQuick(x,y)));
        }
    }
}

void TestImageTools::testHough()
{

}

void TestImageTools::testKLT()
{
/*
    // test exceptions
    {
        Image src(13,13);

        GrayImage16s* gradX = new GrayImage16s(5,6);
        GrayImage16s* gradY = NULL;

        CPPUNIT_ASSERT_THROW(KLTCornerDetector(src, 4, 10000, 1, 2, gradX, gradY), ImageException);
        gradX = NULL;
        gradY = new GrayImage16s(5,2);
        CPPUNIT_ASSERT_THROW(KLTCornerDetector(src, 4, 10000, 1, 2, gradX, gradY), ImageException);
        gradX = NULL;
        gradY = NULL;
        CPPUNIT_ASSERT_NO_THROW(KLTCornerDetector(src, 4, 10000, 1, 2, gradX, gradY));
        gradX = new GrayImage16s(13,13);
        gradY = new GrayImage16s(13,13);
        CPPUNIT_ASSERT_NO_THROW(KLTCornerDetector(src, 4, 10000, 1, 2, gradX, gradY));
    }

    // test a simple rectangle
    {
        Image src(13,13);
        src.set(0);
        for(int y=4; y<9; ++y)
            for(int x=4; x<9; ++x)
                src.setPixelQuick(x,y,255);

        GrayImage16s* gradX = sobelX(src);
        GrayImage16s* gradY = sobelY(src);

        Matrix* corners = KLTCornerDetector(src, 4, 1000, 1, 1, gradX, gradY);
        CPPUNIT_ASSERT_EQUAL(4, static_cast<int>(corners->rows()));

        Image result(src.width(), src.height());
        result.set(0);
        for(uint i=0; i<corners->rows(); ++i) {
            result.setPixelQuick((*corners)(i,0), (*corners)(i,1), 255);
		}

        for(int y=0; y<result.height(); ++y)
            for(int x=0; x<result.width(); ++x)
                if(x==4&&(y==4||y==8) || x==8&&(y==4||y==8))
                    CPPUNIT_ASSERT_EQUAL(255, static_cast<int>(result.getPixelQuick(x,y)));
                else
                    CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result.getPixelQuick(x,y)));
    }

    // test a star structure
    {
        Image src(23,23);
        src.set(0);

        for(int y=4; y<=18; ++y)
            for(int x=9; x<=13; ++x)
                src.setPixelQuick(x,y, 255);
        for(int y=9; y<=13; ++y)
            for(int x=4; x<=18; ++x)
                src.setPixelQuick(x,y, 255);

        // soNeighborhood = 1
        Matrix* corners = KLTCornerDetector(src, 12, 10000, 1, 1);
        CPPUNIT_ASSERT_EQUAL(12, static_cast<int>(corners->rows()));

        Image result(src.width(), src.height());
        result.set(0);

        for(uint i=0; i<corners->rows(); ++i)
            result.setPixelQuick((*corners)(i,0), (*corners)(i,1), 255);

        for(int y=1; y<result.height()-1; ++y)
            for(int x=1; x<result.width()-1; ++x)
                if( y==4&&(x==9||x==13) || y==8&&(x==8||x==14) || y==9&&(x==4||x==18) ||
                    y==13&&(x==4||x==18) || y==14&&(x==8||x==14) || y==18&&(x==9||x==13) )
                    CPPUNIT_ASSERT_EQUAL(255, static_cast<int>(result.getPixelQuick(x,y)));
                else
                    CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result.getPixelQuick(x,y)));

        // soNeighborhood = 2
        corners = KLTCornerDetector(src, 4, 10000, 2, 2);
        CPPUNIT_ASSERT_EQUAL(4, static_cast<int>(corners->rows()));
        Image result2(src.width(), src.height());
        result2.set(0);
        for(uint i=0; i<corners->rows(); ++i)
            result2.setPixelQuick((*corners)(i,0), (*corners)(i,1), 255);

        for(int y=1; y<result2.height()-1; ++y)
            for(int x=1; x<result2.width()-1; ++x)
                if( x==11&&y==5 || x==17&&y==11 || x==11&&y==17 || x==5&&y==11 )
                    CPPUNIT_ASSERT_EQUAL(255, static_cast<int>(result2.getPixelQuick(x,y)));
                else
                    CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result2.getPixelQuick(x,y)));
    }
*/
}

#endif // NICE_USELIB_CPPUNIT
