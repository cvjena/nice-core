
#include "TestMorph.h"

#include "core/image/ImageT.h"
#include "core/image/ColorImageT.h"
#include "core/image/Morph.h"

using namespace std;
using namespace NICE;

CPPUNIT_TEST_SUITE_REGISTRATION( TestMorph );

void TestMorph::setUp() 
{
}

void TestMorph::tearDown()
{
}

void TestMorph::testRanking()
{
    Image* temp, *result;

    Image srcall(5,5);
    srcall.set(0);
    for(int j=1; j<=3; ++j)
        for(int i=1; i<=3; ++i)
            srcall.setPixelQuick(i,j, i+3*(j-1) );
    for(int i=1; i<=9; ++i) {
        result = rank(srcall, 1,i);
        CPPUNIT_ASSERT_EQUAL(i, static_cast<int>(result->getPixel(2,2)));
    }

    int width  = 10;
    int height = 10;
    Image src(width,height);
    for(int y=0; y<height; ++y)
        for(int x=0; x<width; ++x)
            src(x,y) = x+y;

    // test exceptions
    CPPUNIT_ASSERT_THROW(rank(src,1,0), ImageException);
    CPPUNIT_ASSERT_THROW(rank(src,1,10), ImageException);

    // test ranking operation
        // rank = min
        result = rank(src, 1,1);
        for(int j=1; j<height-1; ++j)
            for(int i=1; i<width-1; ++i)
                CPPUNIT_ASSERT_EQUAL((i-1)+(j-1), static_cast<int>(result->getPixel(i,j)));
        // rank = 2
        result = rank(src, 1,2,result);
        for(int j=1; j<height-1; ++j)
            for(int i=1; i<width-1; ++i)
                CPPUNIT_ASSERT_EQUAL(i+j-1      , static_cast<int>(result->getPixel(i,j)));
        // rank = median
        result = rank(src, 1,5,result);
        for(int j=1; j<height-1; ++j)
            for(int i=1; i<width-1; ++i)
                CPPUNIT_ASSERT_EQUAL(i+j        , static_cast<int>(result->getPixel(i,j)));
        // rank = 7
        result = rank(src, 1,7,result);
        for(int j=1; j<height-1; ++j)
            for(int i=1; i<width-1; ++i)
                CPPUNIT_ASSERT_EQUAL(i+j+1      , static_cast<int>(result->getPixel(i,j)));
        // rank = max
        result = rank(src, 1,9,result);
        for(int j=1; j<height-1; ++j)
            for(int i=1; i<width-1; ++i)
                CPPUNIT_ASSERT_EQUAL((i+1)+(j+1), static_cast<int>(result->getPixel(i,j)));

    // test IP ranking operation with the help of the testet ranking operation

        // rank = min
        result = rank(src, 1,1);
        temp   = new Image(src);
        rankingIP(*temp, 1);

        for(int y=1; y<height-1; ++y)
            for(int x=1; x<width-1; ++x)
                CPPUNIT_ASSERT_EQUAL( static_cast<int>((*result)(x,y)), static_cast<int>((*temp)(x,y)) );
        // rank = 2
        result = rank(src, 1,2,result);
        temp   = new Image(src);
        rankingIP(*temp, 2);
        for(int y=1; y<height-1; ++y)
            for(int x=1; x<width-1; ++x)
                CPPUNIT_ASSERT_EQUAL( static_cast<int>((*result)(x,y)), static_cast<int>((*temp)(x,y)) );

        // rank = median
        result = rank(src, 1,5,result);
        temp   = new Image(src);
        rankingIP(*temp, 5);
        for(int y=1; y<height-1; ++y)
            for(int x=1; x<width-1; ++x)
                CPPUNIT_ASSERT_EQUAL( static_cast<int>((*result)(x,y)), static_cast<int>((*temp)(x,y)) );

        // rank = 7
        result = rank(src, 1,7,result);
        temp   = new Image(src);
        rankingIP(*temp, 7);
        for(int y=1; y<height-1; ++y)
            for(int x=1; x<width-1; ++x)
                CPPUNIT_ASSERT_EQUAL( static_cast<int>((*result)(x,y)), static_cast<int>((*temp)(x,y)) );

        // rank = max
        result = rank(src, 1,9,result);
        temp   = new Image(src);
        rankingIP(*temp, 9);
        for(int y=1; y<height-1; ++y)
            for(int x=1; x<width-1; ++x)
                CPPUNIT_ASSERT_EQUAL( static_cast<int>((*result)(x,y)), static_cast<int>((*temp)(x,y)) );
}

void TestMorph::testMorphological()
{
    int width  = 10;
    int height = 10;
    Image src(width,height);
    for(int y=0; y<height; ++y)
        for(int x=0; x<width; ++x)
            src(x,y) = x+y;

    Image* result;

    // test erode, median, dilate (3x3)

        // erode = minimum filter
        result = erode(src);
        for(int j=1; j<height-1; ++j)
            for(int i=1; i<width-1; ++i)
                CPPUNIT_ASSERT_EQUAL((i-1)+(j-1), static_cast<int>(result->getPixel(i,j)));

        // median
        result = median(src,result);
        for(int j=1; j<height-1; ++j)
            for(int i=1; i<width-1; ++i)
                CPPUNIT_ASSERT_EQUAL(i+j        , static_cast<int>(result->getPixel(i,j)));

            // test median with another image
            {
                Image t(5,5);
                t(0,0) =5; t(0,1) =1; t(0,2) =4; t(0,3) =7; t(0,4) =4;
                t(1,0) =1; t(1,1) =9; t(1,2) =8; t(1,3) =1; t(1,4) =3;
                t(2,0) =5; t(2,1) =2; t(2,2) =3; t(2,3) =3; t(2,4) =3;
                t(3,0) =8; t(3,1) =3; t(3,2) =7; t(3,3) =6; t(3,4) =7;
                t(4,0) =2; t(4,1) =5; t(4,2) =4; t(4,3) =8; t(4,4) =7;

                Image* r = median(t);

                CPPUNIT_ASSERT_EQUAL(4, static_cast<int>(r->getPixel(1,1)));
                CPPUNIT_ASSERT_EQUAL(5, static_cast<int>(r->getPixel(2,1)));
                CPPUNIT_ASSERT_EQUAL(4, static_cast<int>(r->getPixel(3,1)));
                CPPUNIT_ASSERT_EQUAL(3, static_cast<int>(r->getPixel(1,2)));
                CPPUNIT_ASSERT_EQUAL(3, static_cast<int>(r->getPixel(2,2)));
                CPPUNIT_ASSERT_EQUAL(4, static_cast<int>(r->getPixel(3,2)));
                CPPUNIT_ASSERT_EQUAL(3, static_cast<int>(r->getPixel(1,3)));
                CPPUNIT_ASSERT_EQUAL(3, static_cast<int>(r->getPixel(2,3)));
                CPPUNIT_ASSERT_EQUAL(6, static_cast<int>(r->getPixel(3,3)));

                // now check if ip median has the same results
                medianIP(t);
                for(int y=1; y<=3; ++y)
                    for(int x=1; x<=3; ++x)
                        CPPUNIT_ASSERT_EQUAL(static_cast<int>(t(x,y)),
                                             static_cast<int>(r->getPixel(x,y)));
            }

        // dilate = maximum filter
        result = dilate(src,result);
        for(int j=1; j<height-1; ++j)
            for(int i=1; i<width-1; ++i)
                CPPUNIT_ASSERT_EQUAL((i+1)+(j+1), static_cast<int>(result->getPixel(i,j)));

    // now test dilate, median, erode, opening and closing on binary images (0,255)
        src = Image(13,13);
        src = 0;
        src(3,3) = src(4,3) = src(5,3) = src(6,3) = src(7,3) = src(8,3) = 255;
        src(4,4) = src(5,4) = src(7,4)                                  = 255;
        src(4,5) = src(5,5) = src(6,5) = src(7,5) = src(8,5)            = 255;
        src(4,6) = src(5,6) = src(6,6) = src(7,6)                       = 255;
        src(3,7) = src(4,7) = src(5,7) = src(6,7) = src(7,7)            = 255;
        src(3,8) = src(4,8) = src(5,8) = src(6,8)                       = 255;
        src(3,9) = src(4,9) = src(5,9) = src(6,9) = src(9,9)            = 255;

        // erode
        result = erode(src);

            CPPUNIT_ASSERT_EQUAL(255, static_cast<int>(result->getPixel(5, 6)));
            CPPUNIT_ASSERT_EQUAL(255, static_cast<int>(result->getPixel(6, 6)));
            CPPUNIT_ASSERT_EQUAL(255, static_cast<int>(result->getPixel(5, 7)));
            CPPUNIT_ASSERT_EQUAL(255, static_cast<int>(result->getPixel(4, 8)));
            CPPUNIT_ASSERT_EQUAL(255, static_cast<int>(result->getPixel(5, 8)));
            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel(4, 6)));
            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel(4, 7)));
            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel(6, 7)));
            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel(6, 8)));
            for(int i=3; i<=7; ++i)
            {
                CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel(i, 5)));
                CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel(i, 9)));
            }
            for(int i=5; i<=9; ++i)
            {
                CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel(3,i)));
                CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel(7,i)));
            }

        // median
        result = median(src,result);

            for(int i=1; i<result->height()-1; ++i) {
                CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel( 1, i)));
                CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel( 2, i)));
                CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel( 9, i)));
                CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel(10, i)));
            }
            for(int i=1; i<result->width()-1; ++i) {
                CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel(i, 1)));
                CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel(i, 2)));
                CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel(i,10)));
                CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel(i,11)));
            }

            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel( 3, 3)));

            CPPUNIT_ASSERT_EQUAL(255, static_cast<int>(result->getPixel( 3, 7)));
            CPPUNIT_ASSERT_EQUAL(255, static_cast<int>(result->getPixel( 3, 8)));
            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel( 3, 9)));
            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel( 3,10)));

            CPPUNIT_ASSERT_EQUAL(255, static_cast<int>(result->getPixel( 4, 9)));
            CPPUNIT_ASSERT_EQUAL(255, static_cast<int>(result->getPixel( 5, 9)));
            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel( 6, 9)));

            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel( 7, 3)));
            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel( 8, 3)));
            CPPUNIT_ASSERT_EQUAL(255, static_cast<int>(result->getPixel( 8, 4)));
            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel( 8, 5)));

            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel( 9, 9)));

            Image med1(3,3);
            med1(0,0) = 1; med1(1,0) = 1; med1(2,0) = 1;
            med1(0,1) = 1; med1(1,1) = 1; med1(2,1) = 2;
            med1(0,2) = 2; med1(1,2) = 2; med1(2,2) = 2;
            result = median(med1);
            CPPUNIT_ASSERT_EQUAL(  1, static_cast<int>(result->getPixel(1,1)));

            med1(0,0) = 1; med1(1,0) = 1; med1(2,0) = 1;
            med1(0,1) = 1; med1(1,1) = 2; med1(2,1) = 2;
            med1(0,2) = 2; med1(1,2) = 2; med1(2,2) = 2;
            result = median(med1);
            CPPUNIT_ASSERT_EQUAL(  2, static_cast<int>(result->getPixel(1,1)));

      // dilate
        result = dilate(src);

            for(int y=2; y<result->height()-2; ++y)
                for(int x=2; x<result->width()-3; ++x)
                    if( (x==2&&y==5) || (x==9&&y==7) )
                        CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel(x,y)));
                    else
                        CPPUNIT_ASSERT_EQUAL(255, static_cast<int>(result->getPixel(x,y)));
            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel(10, 2)));
            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel(10, 3)));
            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel(10, 4)));
            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel(10, 5)));
            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel(10, 6)));
            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel(10, 7)));
            CPPUNIT_ASSERT_EQUAL(255, static_cast<int>(result->getPixel(10, 8)));
            CPPUNIT_ASSERT_EQUAL(255, static_cast<int>(result->getPixel(10, 9)));
            CPPUNIT_ASSERT_EQUAL(255, static_cast<int>(result->getPixel(10,10)));

        // opening
        result = opening(src,result);

            for(int i=2; i<result->width()-2; ++i) {
                CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel(i, 3)));
                CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel(i, 4)));
                CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel(i,10)));
                CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel(i,11)));
            }
            for(int i=2; i<result->height()-2; ++i) {
                CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel( 1,i)));
                CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel( 2,i)));
                CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel( 8,i)));
                CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel( 9,i)));
            }

            for(int i=3; i<=7; ++i)
                for(int j=5; j<=9; ++j)
                    if( (i==3&&j>=5&&j<=6) || (i==7&&j>=8&&j<=9) )
                        CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel(i,j)));
                    else
                        CPPUNIT_ASSERT_EQUAL(255, static_cast<int>(result->getPixel(i,j)));

        // closing
        result = closing(src,result);

            for(int i=1; i<result->width()-1; ++i) {
                CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel(i, 1)));
                CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel(i, 2)));
                CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel(i,10)));
                CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel(i,11)));
            }
            for(int i=1; i<result->height()-1; ++i) {
                CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel( 1,i)));
                CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel( 2,i)));
                CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel(10,i)));
                CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel(11,i)));
            }

            for(int i=3; i<=8; ++i)
                for(int j=3; j<=9; ++j)
                    if( (i==3&&j>=4&&j<=6) || (i==8&&j>=6&&j<=8) )
                        CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>(result->getPixel(i,j)));
                    else
                        CPPUNIT_ASSERT_EQUAL(255, static_cast<int>(result->getPixel(i,j)));

            CPPUNIT_ASSERT_EQUAL(255, static_cast<int>(result->getPixel( 9, 9)));
}

void TestMorph::testMorphologicalIP()
{
    Image src(13,13);
    src.set(0);
    src(3,3) = src(4,3) = src(5,3) = src(6,3) = src(7,3) = src(8,3) = 255;
    src(4,4) = src(5,4) = src(7,4)                                  = 255;
    src(4,5) = src(5,5) = src(6,5) = src(7,5) = src(8,5)            = 255;
    src(4,6) = src(5,6) = src(6,6) = src(7,6)                       = 255;
    src(3,7) = src(4,7) = src(5,7) = src(6,7) = src(7,7)            = 255;
    src(3,8) = src(4,8) = src(5,8) = src(6,8)                       = 255;
    src(3,9) = src(4,9) = src(5,9) = src(6,9) = src(9,9)            = 255;
    Image* result, *temp;

    // test IP operations with the help of the testet non IP operations
        // erodeIP
        result = erode(src);
        temp   = new Image(src);
        erodeIP(*temp);

        for(int y=1; y<result->height()-1; ++y)
            for(int x=1; x<result->width()-1; ++x)
                CPPUNIT_ASSERT_EQUAL( static_cast<int>((*result)(x,y)), static_cast<int>((*temp)(x,y)) );

        // medianIP
        result = median(src);
        temp   = new Image(src);
        medianIP(*temp);

        for(int y=1; y<result->height()-1; ++y)
            for(int x=1; x<result->width()-1; ++x)
                CPPUNIT_ASSERT_EQUAL( static_cast<int>((*result)(x,y)), static_cast<int>((*temp)(x,y)) );

        // dilateIP
        result = dilate(src);
        temp   = new Image(src);
        dilateIP(*temp);

        for(int y=1; y<result->height()-1; ++y)
            for(int x=1; x<result->width()-1; ++x)
                CPPUNIT_ASSERT_EQUAL( static_cast<int>((*result)(x,y)), static_cast<int>((*temp)(x,y)) );


        // openingIP
        result = opening(src,result);
        temp   = new Image(src);
        openingIP(*temp);
        for(int y=2; y<result->height()-2; ++y)
            for(int x=2; x<result->width()-2; ++x)
                CPPUNIT_ASSERT_EQUAL( static_cast<int>((*result)(x,y)), static_cast<int>((*temp)(x,y)) );

        // closingIP
        result = closing(src,result);
        temp   = new Image(src);
        closingIP(*temp);
        for(int y=2; y<result->height()-2; ++y)
            for(int x=2; x<result->width()-2; ++x)
                CPPUNIT_ASSERT_EQUAL( static_cast<int>((*result)(x,y)), static_cast<int>((*temp)(x,y)) );
}

void TestMorph::testRankingWithStructure()
{
    Image* result, *rresult;

    Image src = Image(10,11);
    src.set(0);
    src(2,2) = src(3,2) = src(4,2) = src(5,2) =src(6,2) = src(7,2) = 255;
    src(3,3) = src(5,3) = src(6,3)                                 = 255;
    src(3,4) = src(4,4) = src(5,4) = src(6,4) = src(7,4)           = 255;
    src(3,5) = src(4,5) = src(5,5) = src(6,5)                      = 255;
    src(2,6) = src(3,6) = src(4,6) = src(5,6) = src(6,6)           = 255;
    src(2,7) = src(3,7) = src(4,7) = src(5,7)                      = 255;
    src(2,8) = src(3,8) = src(4,8) = src(5,8) = src(8,8)           = 255;

    // test ranking operation
    CharMatrix structure(3,3);

    // 3x3 quadratic structure Element
    {
        structure = 1;

        // rank = 1
        rresult   = erode(src);
        result    = rank(src, structure, 1);
        for(int y=1; y<src.height()-1; ++y)
            for(int x=1; x<src.width()-1; ++x)
                CPPUNIT_ASSERT_EQUAL( static_cast<int>((*rresult)(x,y)), static_cast<int>((*result)(x,y)) );

        // rank = 2
        rresult   = rank(src, 1, 2, rresult);
        result    = rank(src, structure, 2, result);
        for(int y=1; y<src.height()-1; ++y)
            for(int x=1; x<src.width()-1; ++x)
                CPPUNIT_ASSERT_EQUAL( static_cast<int>((*rresult)(x,y)), static_cast<int>((*result)(x,y)) );

        // rank = median
        rresult   = median(src, rresult);
        result    = rank(src, structure, 5, result);
        for(int y=1; y<src.height()-1; ++y)
            for(int x=1; x<src.width()-1; ++x)
                CPPUNIT_ASSERT_EQUAL( static_cast<int>((*rresult)(x,y)), static_cast<int>((*result)(x,y)) );

        // rank = 7
        rresult   = rank(src, 1, 7, rresult);
        result    = rank(src, structure, 7, result);
        for(int y=1; y<src.height()-1; ++y)
            for(int x=1; x<src.width()-1; ++x)
                CPPUNIT_ASSERT_EQUAL( static_cast<int>((*rresult)(x,y)), static_cast<int>((*result)(x,y)) );

        // rank = 9
        rresult   = dilate(src, rresult);
        result    = rank(src, structure, 9, result);
        for(int y=1; y<src.height()-1; ++y)
            for(int x=1; x<src.width()-1; ++x)
                CPPUNIT_ASSERT_EQUAL( static_cast<int>((*rresult)(x,y)), static_cast<int>((*result)(x,y)) );
    }
}

void TestMorph::testMorphologicalWithStructure()
{
    Image* result = NULL;

    Image src (10,11);
    src = 0;
    src(2,2) = src(3,2) = src(4,2) = src(5,2) =src(6,2) = src(7,2) = 255;
    src(3,3) = src(5,3) = src(6,3)                                 = 255;
    src(3,4) = src(4,4) = src(5,4) = src(6,4) = src(7,4)           = 255;
    src(3,5) = src(4,5) = src(5,5) = src(6,5)                      = 255;
    src(2,6) = src(3,6) = src(4,6) = src(5,6) = src(6,6)           = 255;
    src(2,7) = src(3,7) = src(4,7) = src(5,7)                      = 255;
    src(2,8) = src(3,8) = src(4,8) = src(5,8) = src(8,8)           = 255;

    // test some specific corner and line structure elements with the erode operator
    {
        src = Image(12,12);
        src = 0;
        src(4,4) = src(5,4) = src(6,4) = src(7,4) = src(7,5) = src(7,6) = src(7,7) = 255;
        src(6,7) = src(5,7) = src(4,7) = src(4,6) = src(4,5) = 255;

        // test lines
            CharMatrix hl(5,5,0), vl(5,5,0);
            hl(2,1) = hl(2,2) = hl(2,3) = 1;
            vl(1,2) = vl(2,2) = vl(3,2) = 1;

            // horizontal line
            CPPUNIT_ASSERT_NO_THROW(result = erode(src, hl));
            CPPUNIT_ASSERT_EQUAL(255, static_cast<int>((*result)(5,4)));
            CPPUNIT_ASSERT_EQUAL(255, static_cast<int>((*result)(6,4)));
            CPPUNIT_ASSERT_EQUAL(255, static_cast<int>((*result)(5,7)));
            CPPUNIT_ASSERT_EQUAL(255, static_cast<int>((*result)(6,7)));

            // vertical line
            CPPUNIT_ASSERT_NO_THROW(result = erode(src, vl));
            CPPUNIT_ASSERT_EQUAL(255, static_cast<int>((*result)(4,5)));
            CPPUNIT_ASSERT_EQUAL(255, static_cast<int>((*result)(4,6)));
            CPPUNIT_ASSERT_EQUAL(255, static_cast<int>((*result)(7,5)));
            CPPUNIT_ASSERT_EQUAL(255, static_cast<int>((*result)(7,6)));

        // test edges
            CharMatrix tl(5,5,0), tr(5,5,0), bl(5,5,0), br(5,5,0);
            tl(2,2) = tl(3,2) = tl(4,2) = tl(2,3) = tl(2,4) = 1;
            tr(2,2) = tr(3,2) = tr(4,2) = tr(2,1) = tr(2,0) = 1;
            bl(2,2) = bl(2,3) = bl(2,4) = bl(1,2) = bl(0,2) = 1;
            br(2,2) = br(2,1) = br(2,0) = br(1,2) = br(0,2) = 1;

            CPPUNIT_ASSERT_NO_THROW(result = erode(src, tl));
            CPPUNIT_ASSERT_EQUAL(255, static_cast<int>((*result)(4,4)));
            CPPUNIT_ASSERT_NO_THROW(result = erode(src, tr));
            CPPUNIT_ASSERT_EQUAL(255, static_cast<int>((*result)(7,4)));
            CPPUNIT_ASSERT_NO_THROW(result = erode(src, bl));
            CPPUNIT_ASSERT_EQUAL(255, static_cast<int>((*result)(4,7)));
            CPPUNIT_ASSERT_NO_THROW(result = erode(src, br));
            CPPUNIT_ASSERT_EQUAL(255, static_cast<int>((*result)(7,7)));
    }

    // test erode and dilate with a cross structure element
    {
        src = 0;
        for(int y=4; y<=7; ++y)
            for(int x=4; x<=7; ++x)
                src(x,y) = 255;

        CharMatrix cross(3,3,0);
        cross(0,1) = cross(1,0) = cross(1,1) = cross(1,2) = cross(2,1) = 1;

        // erode
        CPPUNIT_ASSERT_NO_THROW(result = erode(src, cross));
        for(int y=1; y<result->height()-1; ++y)
            for(int x=1; x<result->width()-1; ++x)
                if( y>=5 && y<=6 && x>=5 && x<=6 )
                    CPPUNIT_ASSERT_EQUAL(255, static_cast<int>((*result)(x,y)));
                else
                    CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>((*result)(x,y)));

        // dialte
        CPPUNIT_ASSERT_NO_THROW(result = dilate(src, cross));
		for(int i=1; i<=10; ++i)
        {
            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>((*result)(i, 1)));
            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>((*result)(i, 2)));
            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>((*result)(i, 9)));
            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>((*result)(i,10)));

            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>((*result)( 1,i)));
            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>((*result)( 2,i)));
            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>((*result)( 9,i)));
            CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>((*result)(10,i)));
        }
        for(int y=3; y<=8; ++y)
            for(int x=8; x<=8; ++x)
                if( (x==3)&&(y==3) || (x==8)&&(y==3) || (x==3)&&(y==8) || (x==8)&&(y==8) )
                    CPPUNIT_ASSERT_EQUAL(  0, static_cast<int>((*result)(x,y)));
                else
                    CPPUNIT_ASSERT_EQUAL(255, static_cast<int>((*result)(x,y)));
    }
}

void TestMorph::testHitAndMiss()
{
    // test some corner structure Elements with the hitAndMiss operator
    {
        Image src(12,12);
        src.set(0);

        for(int y=4; y<=7; ++y)
            for(int x=4; x<=7; ++x)
                src(x,y) = 255;

        CharMatrix tl(5,5,0), tr(5,5,0), bl(5,5,0), br(5,5,0);

        tl(2,2) = tl(3,2) = tl(4,2) = tl(2,3) = tl(3,3) = tl(4,3) = tl(2,4) = tl(3,4) = tl(4,4) = 1;
        tr(2,0) = tr(2,1) = tr(2,2) = tr(3,0) = tr(3,1) = tr(3,2) = tr(4,0) = tr(4,1) = tr(4,2) = 1;
        bl(0,2) = bl(0,3) = bl(0,4) = bl(1,2) = bl(1,3) = bl(1,4) = bl(2,2) = bl(2,3) = bl(2,4) = 1;
        br(0,0) = br(0,1) = br(0,2) = br(1,0) = br(1,1) = br(1,2) = br(2,0) = br(2,1) = br(2,2) = 1;

        Image* result = new Image(src.width(), src.height());
        Image exp(src.width()-2*2, src.height()-2*2);

        result = hitAndMiss(src, tl, result);
        exp.set(0);
        exp.setPixelQuick(2,2,255);
        CPPUNIT_ASSERT_EQUAL(true, *result->createSubImage(Rect(2,2,result->width()-4,result->height()-4))==exp);

        result = hitAndMiss(src, tr, result);
        exp.set(0);
        exp.setPixelQuick(5,2,255);
        CPPUNIT_ASSERT_EQUAL(true, *result->createSubImage(Rect(2,2,result->width()-4,result->height()-4))==exp);

        result = hitAndMiss(src, bl, result);
        exp.set(0);
        exp.setPixelQuick(2,5,255);
        CPPUNIT_ASSERT_EQUAL(true, *result->createSubImage(Rect(2,2,result->width()-4,result->height()-4))==exp);

        result = hitAndMiss(src, br, result);
        exp.set(0);
        exp.setPixelQuick(5,5,255);
        CPPUNIT_ASSERT_EQUAL(true, *result->createSubImage(Rect(2,2,result->width()-4,result->height()-4))==exp);

        // clean up
        delete result;
    }

    // now we try to find the letter A out of A and B with the hitAndMiss operator
    {
        Image src(19,11);
        src.set(0);
        src(4,3) = src(5,3) = src(6,3) = src(4,4) = src(6,4) = src(5,5) = 255;
        src(4,5) = src(6,5) = src(4,6) = src(6,6) = src(4,7) = src(6,7) = 255;
        src(12,3) = src(13,3) = src(14,3) = src(12,4) = src(14,4) = 255;
        src(12,5) = src(13,5) = src(14,5) = src(12,6) = src(14,6) = 255;
        src(12,7) = src(13,7) = src(14,7)                         = 255;

        CharMatrix CharTest(7,5);
        CharTest = 0;
        CharTest(1,1) = CharTest(1,2) = CharTest(1,3) = CharTest(2,1) = CharTest(2,3) = CharTest(3,1) = 1;
        CharTest(3,2) = CharTest(3,3) = CharTest(4,1) = CharTest(4,3) = CharTest(5,1) = CharTest(5,3) = 1;

        Image* result = new Image(src.width(), src.height());
        result            = hitAndMiss(src, CharTest, result);

        Image exp(src.width()-4, src.height()-4);
        exp.set(0);
        exp.setPixelQuick(3,3, 255);

        CPPUNIT_ASSERT_EQUAL(true, *result->createSubImage(Rect(2,2,result->width()-4,result->height()-4))==exp);

        // clean up
        delete result;
    }
}
