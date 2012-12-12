
#include "TestHistogram.h"
#include <string>

#include "core/image/ImageT.h"
#include "core/image/ColorImageT.h"
#include "core/image/Histogram.h"


#ifdef NICE_USELIB_LIMUN_IOCOMPRESSION
    #include <iocompression/md5.h>
#endif

using namespace std;
using namespace NICE;

CPPUNIT_TEST_SUITE_REGISTRATION( TestHistogram );

void TestHistogram::setUp() 
{
}

void TestHistogram::tearDown() 
{
}

void TestHistogram::testIterator()
{
    Histogram hist(10);
    for(Ipp32u i=0; i<hist.size(); ++i)
        hist[i] = i+1;

    CPPUNIT_ASSERT_EQUAL( 1, static_cast<int>(*hist.begin()));
    CPPUNIT_ASSERT_EQUAL(10, static_cast<int>(*(hist.end()-1)));
    CPPUNIT_ASSERT_EQUAL(static_cast<int>(*hist.getDataPointer()), static_cast<int>(*hist.begin()));

    Ipp32u j = 0;
    for(Histogram::iterator i=hist.begin(); i!=hist.end(); ++i,++j)
        CPPUNIT_ASSERT_EQUAL(static_cast<int>(hist[j]), static_cast<int>(*i));
}

void TestHistogram::testGrayHistogram()
{
    Image src(10,10);
    for(int y=0; y<src.height(); ++y)
        for(int x=0; x<src.width(); ++x)
            src.setPixelQuick(x,y, (x+1)+y);

    // test with 20bins, range 0-20
    {
        Histogram hist(src,0,20);

        CPPUNIT_ASSERT_EQUAL( 20, static_cast<int>(hist.size()));
        CPPUNIT_ASSERT_EQUAL(100, static_cast<int>(hist.sum()));
        CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(hist.min()));
        CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(hist.minIndex()));
        CPPUNIT_ASSERT_EQUAL( 10, static_cast<int>(hist.max()));
        CPPUNIT_ASSERT_EQUAL( 10, static_cast<int>(hist.maxIndex()));

        CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(hist.minBorder()));
        CPPUNIT_ASSERT_EQUAL( 20, static_cast<int>(hist.maxBorder()));

        CPPUNIT_ASSERT_EQUAL( 0, static_cast<int>(hist[0]));
        for(int i=1; i<=10; ++i) {
            CPPUNIT_ASSERT_EQUAL( i, static_cast<int>(hist[i]));
            CPPUNIT_ASSERT_EQUAL( i, static_cast<int>(hist[hist.size()-i]) );
        }
    }

    // test with 10bins, range 0-20
    {
        Histogram hist(src,0,20,10);

        CPPUNIT_ASSERT_EQUAL( 10, static_cast<int>(hist.size()));
        CPPUNIT_ASSERT_EQUAL( 10, static_cast<int>(hist.bins()));
        CPPUNIT_ASSERT_EQUAL(100, static_cast<int>(hist.sum()));
        CPPUNIT_ASSERT_EQUAL(  1, static_cast<int>(hist.min()));
        CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(hist.minIndex()));
        CPPUNIT_ASSERT_EQUAL( 19, static_cast<int>(hist.max()));
        CPPUNIT_ASSERT_EQUAL(  5, static_cast<int>(hist.maxIndex()));

        CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(hist.minBorder()));
        CPPUNIT_ASSERT_EQUAL( 20, static_cast<int>(hist.maxBorder()));

        CPPUNIT_ASSERT_EQUAL( 1, static_cast<int>(hist[ 0]));
        CPPUNIT_ASSERT_EQUAL( 5, static_cast<int>(hist[ 1]));
        CPPUNIT_ASSERT_EQUAL( 9, static_cast<int>(hist[ 2]));
        CPPUNIT_ASSERT_EQUAL(13, static_cast<int>(hist[ 3]));
        CPPUNIT_ASSERT_EQUAL(17, static_cast<int>(hist[ 4]));
        CPPUNIT_ASSERT_EQUAL(19, static_cast<int>(hist[ 5]));
        CPPUNIT_ASSERT_EQUAL(15, static_cast<int>(hist[ 6]));
        CPPUNIT_ASSERT_EQUAL(11, static_cast<int>(hist[ 7]));
        CPPUNIT_ASSERT_EQUAL( 7, static_cast<int>(hist[ 8]));
        CPPUNIT_ASSERT_EQUAL( 3, static_cast<int>(hist[ 9]));
    }

    // test with 5bins, range 0-20
    {
        Histogram hist(src,0,20,5);

        CPPUNIT_ASSERT_EQUAL(  5, static_cast<int>(hist.size()));
        CPPUNIT_ASSERT_EQUAL(100, static_cast<int>(hist.sum()));
        CPPUNIT_ASSERT_EQUAL(  6, static_cast<int>(hist.min()));
        CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(hist.minIndex()));
        CPPUNIT_ASSERT_EQUAL( 36, static_cast<int>(hist.max()));
        CPPUNIT_ASSERT_EQUAL(  2, static_cast<int>(hist.maxIndex()));

        CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(hist.minBorder()));
        CPPUNIT_ASSERT_EQUAL( 20, static_cast<int>(hist.maxBorder()));

        CPPUNIT_ASSERT_EQUAL( 6, static_cast<int>(hist[0]));
        CPPUNIT_ASSERT_EQUAL(22, static_cast<int>(hist[1]));
        CPPUNIT_ASSERT_EQUAL(36, static_cast<int>(hist[2]));
        CPPUNIT_ASSERT_EQUAL(26, static_cast<int>(hist[3]));
        CPPUNIT_ASSERT_EQUAL(10, static_cast<int>(hist[4]));
    }

    // test with 10bins, range 5-15
    {
        Histogram hist(src,5,15);

        CPPUNIT_ASSERT_EQUAL(10, static_cast<int>(hist.size()));
        CPPUNIT_ASSERT_EQUAL(75, static_cast<int>(hist.sum()));
        CPPUNIT_ASSERT_EQUAL( 5, static_cast<int>(hist.minBorder()));
        CPPUNIT_ASSERT_EQUAL(15, static_cast<int>(hist.maxBorder()));
        CPPUNIT_ASSERT_EQUAL(10, static_cast<int>(hist.bins()));

        CPPUNIT_ASSERT_EQUAL( 5, static_cast<int>(hist.min()));
        CPPUNIT_ASSERT_EQUAL( 0, static_cast<int>(hist.minIndex()));
        CPPUNIT_ASSERT_EQUAL(10, static_cast<int>(hist.max()));
        CPPUNIT_ASSERT_EQUAL( 5, static_cast<int>(hist.maxIndex()));

        CPPUNIT_ASSERT_EQUAL( 5, static_cast<int>(hist[ 0]));
        CPPUNIT_ASSERT_EQUAL( 6, static_cast<int>(hist[ 1]));
        CPPUNIT_ASSERT_EQUAL( 7, static_cast<int>(hist[ 2]));
        CPPUNIT_ASSERT_EQUAL( 8, static_cast<int>(hist[ 3]));
        CPPUNIT_ASSERT_EQUAL( 9, static_cast<int>(hist[ 4]));
        CPPUNIT_ASSERT_EQUAL(10, static_cast<int>(hist[ 5]));
        CPPUNIT_ASSERT_EQUAL( 9, static_cast<int>(hist[ 6]));
        CPPUNIT_ASSERT_EQUAL( 8, static_cast<int>(hist[ 7]));
        CPPUNIT_ASSERT_EQUAL( 7, static_cast<int>(hist[ 8]));
        CPPUNIT_ASSERT_EQUAL( 6, static_cast<int>(hist[ 9]));
    }

    // test with 5bins, range 5-15
    {
        Histogram hist(src,5,15,5);

        CPPUNIT_ASSERT_EQUAL( 5, static_cast<int>(hist.size()));
        CPPUNIT_ASSERT_EQUAL(75, static_cast<int>(hist.sum()));
        CPPUNIT_ASSERT_EQUAL( 5, static_cast<int>(hist.minBorder()));
        CPPUNIT_ASSERT_EQUAL(15, static_cast<int>(hist.maxBorder()));

        CPPUNIT_ASSERT_EQUAL(11, static_cast<int>(hist.min()));
        CPPUNIT_ASSERT_EQUAL( 0, static_cast<int>(hist.minIndex()));
        CPPUNIT_ASSERT_EQUAL(19, static_cast<int>(hist.max()));
        CPPUNIT_ASSERT_EQUAL( 2, static_cast<int>(hist.maxIndex()));

        CPPUNIT_ASSERT_EQUAL(11, static_cast<int>(hist[0]));
        CPPUNIT_ASSERT_EQUAL(15, static_cast<int>(hist[1]));
        CPPUNIT_ASSERT_EQUAL(19, static_cast<int>(hist[2]));
        CPPUNIT_ASSERT_EQUAL(17, static_cast<int>(hist[3]));
        CPPUNIT_ASSERT_EQUAL(13, static_cast<int>(hist[4]));
    }
}

void TestHistogram::testGrayHistogramFromRect() {

    Image src(10,10);
    for(int y=0; y<src.height(); ++y) {
        for(int x=0; x<src.width(); ++x) {
            src.setPixelQuick(x,y, (x+1)+y);
        }
    }

    {
        Histogram hist(src, 0, 256, Rect(2,2,2,2));
    
        CPPUNIT_ASSERT_EQUAL(256, static_cast<Ipp32s>(hist.size()));
        CPPUNIT_ASSERT_EQUAL(  4, static_cast<Ipp32s>(hist.sum()));
    
        CPPUNIT_ASSERT_EQUAL(  1, static_cast<Ipp32s>(hist[5]));
        CPPUNIT_ASSERT_EQUAL(  2, static_cast<Ipp32s>(hist[6]));
        CPPUNIT_ASSERT_EQUAL(  1, static_cast<Ipp32s>(hist[7]));
    }

    {
        Histogram hist(src, 0, 256, Rect(2,2,5,5));

        CPPUNIT_ASSERT_EQUAL(256, static_cast<Ipp32s>(hist.size()));
        CPPUNIT_ASSERT_EQUAL( 25, static_cast<Ipp32s>(hist.sum()));

        CPPUNIT_ASSERT_EQUAL(  1, static_cast<Ipp32s>(hist[ 5]));
        CPPUNIT_ASSERT_EQUAL(  2, static_cast<Ipp32s>(hist[ 6]));
        CPPUNIT_ASSERT_EQUAL(  3, static_cast<Ipp32s>(hist[ 7]));
        CPPUNIT_ASSERT_EQUAL(  4, static_cast<Ipp32s>(hist[ 8]));
        CPPUNIT_ASSERT_EQUAL(  5, static_cast<Ipp32s>(hist[ 9]));
        CPPUNIT_ASSERT_EQUAL(  4, static_cast<Ipp32s>(hist[10]));
        CPPUNIT_ASSERT_EQUAL(  3, static_cast<Ipp32s>(hist[11]));
        CPPUNIT_ASSERT_EQUAL(  2, static_cast<Ipp32s>(hist[12]));
        CPPUNIT_ASSERT_EQUAL(  1, static_cast<Ipp32s>(hist[13]));
    }

    {
        Histogram hist(src, 0, 256, Rect(2,2,5,5), 30);

        CPPUNIT_ASSERT_EQUAL( 30, static_cast<Ipp32s>(hist.size()));
        CPPUNIT_ASSERT_EQUAL( 25, static_cast<Ipp32s>(hist.sum()));

        CPPUNIT_ASSERT_EQUAL( 10, static_cast<Ipp32s>(hist[0]));
        CPPUNIT_ASSERT_EQUAL( 15, static_cast<Ipp32s>(hist[1]));

        FloatVector* normHist = hist.normalized();

        CPPUNIT_ASSERT_DOUBLES_EQUAL( 10.0/25.0, (*normHist)[0], 1e-5);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 15.0/25.0, (*normHist)[1], 1e-5);
    }
}

void TestHistogram::testColorHistogram()
{
    ColorImage src(2,2);
    for(int y=0; y<src.height(); ++y)
        for(int x=0; x<src.width(); ++x)
            src.setPixelQuick(x,y, (x+y), 2*(x+y), 3*(x+y));

    // create a histogram with 6 bins per channel [0,6) )
    {
        Histogram hist(src,0,6);

        CPPUNIT_ASSERT_EQUAL(18, static_cast<int>(hist.size()));
        CPPUNIT_ASSERT_EQUAL(11, static_cast<int>(hist.sum()));
        CPPUNIT_ASSERT_EQUAL( 6, static_cast<int>(hist.bins()));

        CPPUNIT_ASSERT_EQUAL( 0, static_cast<int>(hist.minBorder()));
        CPPUNIT_ASSERT_EQUAL( 6, static_cast<int>(hist.maxBorder()));

        CPPUNIT_ASSERT_EQUAL( 0, static_cast<int>(hist.min()));
        CPPUNIT_ASSERT_EQUAL( 3, static_cast<int>(hist.minIndex()));
        CPPUNIT_ASSERT_EQUAL( 2, static_cast<int>(hist.max()));
        CPPUNIT_ASSERT_EQUAL( 1, static_cast<int>(hist.maxIndex()));

        CPPUNIT_ASSERT_EQUAL( 1, static_cast<int>(hist[ 0]));
        CPPUNIT_ASSERT_EQUAL( 2, static_cast<int>(hist[ 1]));
        CPPUNIT_ASSERT_EQUAL( 1, static_cast<int>(hist[ 2]));
        CPPUNIT_ASSERT_EQUAL( 0, static_cast<int>(hist[ 3]));
        CPPUNIT_ASSERT_EQUAL( 0, static_cast<int>(hist[ 4]));
        CPPUNIT_ASSERT_EQUAL( 0, static_cast<int>(hist[ 5]));

        CPPUNIT_ASSERT_EQUAL( 1, static_cast<int>(hist[ 6]));
        CPPUNIT_ASSERT_EQUAL( 0, static_cast<int>(hist[ 7]));
        CPPUNIT_ASSERT_EQUAL( 2, static_cast<int>(hist[ 8]));
        CPPUNIT_ASSERT_EQUAL( 0, static_cast<int>(hist[ 9]));
        CPPUNIT_ASSERT_EQUAL( 1, static_cast<int>(hist[10]));
        CPPUNIT_ASSERT_EQUAL( 0, static_cast<int>(hist[11]));

        CPPUNIT_ASSERT_EQUAL( 1, static_cast<int>(hist[12]));
        CPPUNIT_ASSERT_EQUAL( 0, static_cast<int>(hist[13]));
        CPPUNIT_ASSERT_EQUAL( 0, static_cast<int>(hist[14]));
        CPPUNIT_ASSERT_EQUAL( 2, static_cast<int>(hist[15]));
        CPPUNIT_ASSERT_EQUAL( 0, static_cast<int>(hist[16]));
        CPPUNIT_ASSERT_EQUAL( 0, static_cast<int>(hist[17]));
    }

    // create a histogram with 7 bins per channel (values 0 to 6)
    {
        Histogram hist(src,0,6,3);

        CPPUNIT_ASSERT_EQUAL( 9, static_cast<int>(hist.size()));
        CPPUNIT_ASSERT_EQUAL(11, static_cast<int>(hist.sum()));
        CPPUNIT_ASSERT_EQUAL( 0, static_cast<int>(hist.minBorder()));
        CPPUNIT_ASSERT_EQUAL( 6, static_cast<int>(hist.maxBorder()));
        CPPUNIT_ASSERT_EQUAL( 3, static_cast<int>(hist.bins()));

        CPPUNIT_ASSERT_EQUAL( 0, static_cast<int>(hist.min()));
        CPPUNIT_ASSERT_EQUAL( 2, static_cast<int>(hist.minIndex()));
        CPPUNIT_ASSERT_EQUAL( 3, static_cast<int>(hist.max()));
        CPPUNIT_ASSERT_EQUAL( 0, static_cast<int>(hist.maxIndex()));

        CPPUNIT_ASSERT_EQUAL( 3, static_cast<int>(hist[ 0]));
        CPPUNIT_ASSERT_EQUAL( 1, static_cast<int>(hist[ 1]));
        CPPUNIT_ASSERT_EQUAL( 0, static_cast<int>(hist[ 2]));

        CPPUNIT_ASSERT_EQUAL( 1, static_cast<int>(hist[ 3]));
        CPPUNIT_ASSERT_EQUAL( 2, static_cast<int>(hist[ 4]));
        CPPUNIT_ASSERT_EQUAL( 1, static_cast<int>(hist[ 5]));

        CPPUNIT_ASSERT_EQUAL( 1, static_cast<int>(hist[ 6]));
        CPPUNIT_ASSERT_EQUAL( 2, static_cast<int>(hist[ 7]));
        CPPUNIT_ASSERT_EQUAL( 0, static_cast<int>(hist[ 8]));
    }

    // create a histogram with 2 bins per channel  [2,4)
    {
        Histogram hist(src,2,4);

        CPPUNIT_ASSERT_EQUAL( 6, static_cast<int>(hist.size()));
        CPPUNIT_ASSERT_EQUAL( 5, static_cast<int>(hist.sum()));
        CPPUNIT_ASSERT_EQUAL( 2, static_cast<int>(hist.minBorder()));
        CPPUNIT_ASSERT_EQUAL( 4, static_cast<int>(hist.maxBorder()));
        CPPUNIT_ASSERT_EQUAL( 2, static_cast<int>(hist.bins()));

        CPPUNIT_ASSERT_EQUAL( 0, static_cast<int>(hist.min()));
        CPPUNIT_ASSERT_EQUAL( 1, static_cast<int>(hist.minIndex()));
        CPPUNIT_ASSERT_EQUAL( 2, static_cast<int>(hist.max()));
        CPPUNIT_ASSERT_EQUAL( 2, static_cast<int>(hist.maxIndex()));

        CPPUNIT_ASSERT_EQUAL( 1, static_cast<int>(hist[ 0]));
        CPPUNIT_ASSERT_EQUAL( 0, static_cast<int>(hist[ 1]));

        CPPUNIT_ASSERT_EQUAL( 2, static_cast<int>(hist[ 2]));
        CPPUNIT_ASSERT_EQUAL( 0, static_cast<int>(hist[ 3]));

        CPPUNIT_ASSERT_EQUAL( 0, static_cast<int>(hist[ 4]));
        CPPUNIT_ASSERT_EQUAL( 2, static_cast<int>(hist[ 5]));
    }
}

void TestHistogram::testProp()
{
    Image src(5,5);
    for(int y=0; y<src.height(); ++y)
        for(int x=0; x<src.width(); ++x)
            src(x,y) = x+y;

    Histogram hist(src,0,9);

    CPPUNIT_ASSERT_EQUAL(  1, static_cast<int>(hist.min()));
    CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(hist.minIndex()));
    CPPUNIT_ASSERT_EQUAL(  5, static_cast<int>(hist.max()));
    CPPUNIT_ASSERT_EQUAL(  4, static_cast<int>(hist.maxIndex()));

    CPPUNIT_ASSERT_EQUAL( 9, static_cast<int>(hist.bins()));
    CPPUNIT_ASSERT_EQUAL( 0, static_cast<int>(hist.minBorder()));
    CPPUNIT_ASSERT_EQUAL( 9, static_cast<int>(hist.maxBorder()));

    CPPUNIT_ASSERT_EQUAL(25, static_cast<int>(hist.sum()));

    CPPUNIT_ASSERT_EQUAL( false, hist.isWithin(-1));
    CPPUNIT_ASSERT_EQUAL( false, hist.isWithin( 9));
    CPPUNIT_ASSERT_EQUAL(  true, hist.isWithin( 0));
    CPPUNIT_ASSERT_EQUAL(  true, hist.isWithin( 8));

    // write, read and compare
    {
        Histogram hist2;
        CPPUNIT_ASSERT_EQUAL(true, hist.write("test1.color.hist"));
        CPPUNIT_ASSERT_EQUAL(true, hist2.read("test1.color.hist"));
        CPPUNIT_ASSERT_EQUAL(true, hist2.write("test2.color.hist"));

        #ifdef NICE_USELIB_LIMUN_IOCOMPRESSION
        {
            std::ifstream hf1("test1.color.hist");
            std::ifstream hf2("test2.color.hist");

            MD5::MD5 md5hf1(hf1);
            MD5::MD5 md5hf2(hf2);

            hf1.close();
            hf2.close();

            string m1 = md5hf1.hex_digest();
            string m2 = md5hf2.hex_digest();

            CPPUNIT_ASSERT_EQUAL(m1,m2);
        }
        #endif

        system("rm test1.color.hist test2.color.hist");
    }
}

void TestHistogram::testOp()
{
    // test exceptions
    {
        Histogram h1(5), h2(3);

        CPPUNIT_ASSERT_THROW(h1 +h2, ImageException);
        CPPUNIT_ASSERT_THROW(h1+=h2, ImageException);
    }

    Histogram h1(3), h2(3);
    h1[0] = 4; h1[1] = 2; h1[2] = 6;
    h2[0] = 4; h2[1] = 2; h2[2] = 6;

    // test boolean operators
    CPPUNIT_ASSERT_EQUAL(true,  h1==h2);
    CPPUNIT_ASSERT_EQUAL(false, h1!=h2);

    // test add
    Histogram h3 = h1+h2;

    CPPUNIT_ASSERT_EQUAL( 8, static_cast<int>(h3[0]));
    CPPUNIT_ASSERT_EQUAL( 4, static_cast<int>(h3[1]));
    CPPUNIT_ASSERT_EQUAL(12, static_cast<int>(h3[2]));

    h1 += h2;
    CPPUNIT_ASSERT_EQUAL(true, h1==h3);

    // = element
    {
        h3 = 128;
        for(Histogram::iterator i=h3.begin(); i!=h3.end(); ++i)
            CPPUNIT_ASSERT_EQUAL(128, static_cast<int>(*i));

        h3 = 33;
        for(Histogram::iterator i=h3.begin(); i!=h3.end(); ++i)
            CPPUNIT_ASSERT_EQUAL( 33, static_cast<int>(*i));
    }
    // = Histogram
    {
        Histogram t1(100);
        t1 = 128;
        CPPUNIT_ASSERT_EQUAL(100, static_cast<int>(t1.size()));
        for(Histogram::iterator i=t1.begin(); i!=t1.end(); ++i)
            CPPUNIT_ASSERT_EQUAL(128, static_cast<int>(*i));

        Histogram t2(50);
        t2 = 64;
        CPPUNIT_ASSERT_EQUAL( 50, static_cast<int>(t2.size()));
        for(Histogram::iterator i=t2.begin(); i!=t2.end(); ++i)
            CPPUNIT_ASSERT_EQUAL( 64, static_cast<int>(*i));

        CPPUNIT_ASSERT_EQUAL( true, t1!=t2);
        CPPUNIT_ASSERT_EQUAL(false, t1==t2);

        t2 = t1;
        CPPUNIT_ASSERT_EQUAL(static_cast<int>(t1.size()), static_cast<int>(t2.size()));
        for(uint i=0; i<t2.size(); ++i)
            CPPUNIT_ASSERT_EQUAL(static_cast<int>(t1[i]), static_cast<int>(t2[i]));

        CPPUNIT_ASSERT_EQUAL(false, t1!=t2);
        CPPUNIT_ASSERT_EQUAL( true, t1==t2);
    }
}

void TestHistogram::testCumulative_Normalized()
{
    Histogram hist(9);

    hist[0] = 1; hist[1] = 2; hist[2] = 3; hist[3] = 4;
    hist[4] = 5;
    hist[5] = 4; hist[6] = 3; hist[7] = 2; hist[8] = 1;

    CPPUNIT_ASSERT_EQUAL( 9, static_cast<int>(hist.size()));
    CPPUNIT_ASSERT_EQUAL(25, static_cast<int>(hist.sum()));

    // cumulative
    {
        IntVector cum = *hist.cumulative();

        CPPUNIT_ASSERT_EQUAL(  9, static_cast<int>(cum.size()));
        CPPUNIT_ASSERT_EQUAL(125, static_cast<int>(cum.Sum()));

        CPPUNIT_ASSERT_EQUAL( 1, static_cast<int>(cum[0]));
        CPPUNIT_ASSERT_EQUAL( 3, static_cast<int>(cum[1]));
        CPPUNIT_ASSERT_EQUAL( 6, static_cast<int>(cum[2]));
        CPPUNIT_ASSERT_EQUAL(10, static_cast<int>(cum[3]));
        CPPUNIT_ASSERT_EQUAL(15, static_cast<int>(cum[4]));
        CPPUNIT_ASSERT_EQUAL(19, static_cast<int>(cum[5]));
        CPPUNIT_ASSERT_EQUAL(22, static_cast<int>(cum[6]));
        CPPUNIT_ASSERT_EQUAL(24, static_cast<int>(cum[7]));
        CPPUNIT_ASSERT_EQUAL(25, static_cast<int>(cum[8]));
    }

    // normalized
    {
        FloatVector norm = *hist.normalized();

        CPPUNIT_ASSERT_EQUAL(   9, static_cast<int>(norm.size()));
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 1.0, static_cast<double>(norm.Sum()), 0.00001);

        CPPUNIT_ASSERT_DOUBLES_EQUAL( 1.0/25.0, static_cast<double>(norm[0]), 0.00001);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 2.0/25.0, static_cast<double>(norm[1]), 0.00001);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 3.0/25.0, static_cast<double>(norm[2]), 0.00001);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 4.0/25.0, static_cast<double>(norm[3]), 0.00001);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 5.0/25.0, static_cast<double>(norm[4]), 0.00001);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 4.0/25.0, static_cast<double>(norm[5]), 0.00001);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 3.0/25.0, static_cast<double>(norm[6]), 0.00001);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 2.0/25.0, static_cast<double>(norm[7]), 0.00001);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 1.0/25.0, static_cast<double>(norm[8]), 0.00001);
    }
}

void TestHistogram::testCombined()
{
    // test exception
    {
        Image f1(3,3);
        Histogram f1h(f1,0,256);
        CPPUNIT_ASSERT_THROW(f1h.reproject(0,0,0), ImageException);

        ColorImage f2(3,3);
        Histogram f2h(f2,0,256);
        CPPUNIT_ASSERT_THROW(f2h.reproject(0,0,0), ImageException);
    }

    ColorImage src(1,17);
    src.setPixelQuick(0, 0, 255,  0,  0);
    src.setPixelQuick(0, 1,   0,255,  0);
    src.setPixelQuick(0, 2,   0,  0,255);
    src.setPixelQuick(0, 3, 255,255,  0);
    src.setPixelQuick(0, 4,   0,255,255);
    src.setPixelQuick(0, 5, 255,  0,255);
    src.setPixelQuick(0, 6, 255,255,255);
    src.setPixelQuick(0, 7, 128,  0,  0);
    src.setPixelQuick(0, 8,   0,128,  0);
    src.setPixelQuick(0, 9,   0,  0,128);
    src.setPixelQuick(0,10, 128,128,  0);
    src.setPixelQuick(0,11,   0,128,128);
    src.setPixelQuick(0,12, 128,  0,128);
    src.setPixelQuick(0,13, 128,128,128);
    src.setPixelQuick(0,14,   0,192,132);
    src.setPixelQuick(0,15,   0,  0,  0);
    src.setPixelQuick(0,16,   0,  0, 26);

    // [0,256) with 10 bins per channel, first channel is ignored
    {
        Ipp32u bins = 10;
        Histogram hist(src, 0,256, bins, true);

        CPPUNIT_ASSERT_EQUAL(static_cast<int>(bins*bins+bins), static_cast<int>(hist.size()));
        CPPUNIT_ASSERT_EQUAL(static_cast<int>(src.height())  , static_cast<int>(hist.sum()));
        CPPUNIT_ASSERT_EQUAL(static_cast<int>(bins)          , static_cast<int>(hist.bins()));

        CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(hist.min()));
        CPPUNIT_ASSERT_EQUAL(  2, static_cast<int>(hist.minIndex()));
        CPPUNIT_ASSERT_EQUAL(  3, static_cast<int>(hist.max()));
        CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(hist.maxIndex()));

        CPPUNIT_ASSERT_EQUAL(   0, static_cast<int>(hist.minBorder()));
        CPPUNIT_ASSERT_EQUAL( 256, static_cast<int>(hist.maxBorder()));
        CPPUNIT_ASSERT_EQUAL(  17, static_cast<int>(hist.sum()));

        // now check the reprojection
        CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(hist.reproject(  0,  0,  0)));
        CPPUNIT_ASSERT_EQUAL(  1, static_cast<int>(hist.reproject(  0,  0, 26)));
        CPPUNIT_ASSERT_EQUAL(109, static_cast<int>(hist.reproject(255,255,255)));
        CPPUNIT_ASSERT_EQUAL( 50, static_cast<int>(hist.reproject(  0,128,  0)));
        CPPUNIT_ASSERT_EQUAL(  9, static_cast<int>(hist.reproject(  0,  0,255)));

        // because noLum==true
        CPPUNIT_ASSERT_EQUAL(static_cast<int>(hist.reproject(  0,255,255)),
                            static_cast<int>(hist.reproject(255,255,255)));
        CPPUNIT_ASSERT_EQUAL(static_cast<int>(hist.reproject(  0,128,128)),
                            static_cast<int>(hist.reproject(128,128,128)));
        CPPUNIT_ASSERT_EQUAL(static_cast<int>(hist.reproject(255,255,  0)),
                            static_cast<int>(hist.reproject(  0,255,  0)));
    }

    // [100,200) mit 10 bins
    {
        int bins = 10;
        Histogram hist(src, 100,200, bins, true);

        CPPUNIT_ASSERT_EQUAL(static_cast<int>(bins*bins+bins), static_cast<int>(hist.size()));
        CPPUNIT_ASSERT_EQUAL(    3, static_cast<int>(hist.sum()));
        CPPUNIT_ASSERT_EQUAL( bins, static_cast<int>(hist.bins()));

        CPPUNIT_ASSERT_EQUAL( 30, static_cast<int>(hist.reproject(0,128,128)));
        CPPUNIT_ASSERT_EQUAL( 95, static_cast<int>(hist.reproject(0,192,132)));

        CPPUNIT_ASSERT_EQUAL( 55, static_cast<int>(hist.reproject(0,150,150)));
        CPPUNIT_ASSERT_EQUAL( 39, static_cast<int>(hist.reproject(0,133,166)));
    }
}




