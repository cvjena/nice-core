/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libimage - An image/template for new NICE libraries
 * See file License for license information.
 */

#ifdef NICE_USELIB_CPPUNIT
#include "TestDrawable.h"
#include <string>
#include <vector>
#include <exception>

#include "core/image/PointT.h"
#include "core/image/LineT.h"
#include "core/image/EllipseT.h"
#include "core/image/CircleT.h"
#include "core/image/CrossT.h"

using namespace std;
using namespace NICE;

CPPUNIT_TEST_SUITE_REGISTRATION( TestDrawable );

void TestDrawable::setUp() {
}

void TestDrawable::tearDown() {
}

void TestDrawable::testConstructor() {
}

void TestDrawable::testOperators() {
  // Test Assignment Operator
}

void TestDrawable::testSomething() {
    // define some colors
    Color black(0,0,0);
    Color blue(0,0,255);
    Color red(255,0,0);
    Color white(255,255,255);

    ColorImage x(40,40);
    x=black;

    Coord midpoint(10,10);
    Point y(5,5,red);
    Coord b(0,0);
    Coord c(19,19);
    Coord d(2,19);
    Coord e(19,2);
    std::vector<Line> l(5);
    l[0]= Line(b,c,white);
    l[1]= Line(c,b,white);
    l[2]= Line(c,d,white);
    l[3]= Line(d,e,white);
    l[4]= Line(e,c,white);

    Circle circle(midpoint,7,blue);
    Coord axis(4,9);
    Ellipse ellipse(midpoint,axis,M_PI/4,red);
    Cross cross(Coord(24, 30), 7, true);

    x.draw(ellipse);
    x.draw(circle);
    x.draw(y);
    x.draw(cross);
    x.drawIter(l.begin(),l.end());

    x.draw(ellipse, red);
    x.draw(circle, blue);
    x.draw(y, black);
    x.draw(cross, white);
    x.drawIter(l.begin(),l.end(), white);
}

void TestDrawable::testCrossT() {

    Image  tgImg(300,300);
    ColorImage tcImg(300,300);

    CrossT<Ipp8u> cross1(Coord(100,100),5);
    CrossT<Ipp8u> cross2 = cross1;

    CrossT<Ipp8u> cross3(Coord(200,200),5);
    CrossT<Ipp8u> cross4(Coord(100,100), 10, false,
                         ColorT<Ipp8u>(static_cast<Ipp8u>(255)));

    CPPUNIT_ASSERT_EQUAL(true,  cross1==cross2);
    CPPUNIT_ASSERT_EQUAL(false, cross1==cross3);
    CPPUNIT_ASSERT_EQUAL(false, cross1==cross4);

    CPPUNIT_ASSERT_EQUAL(false, cross1!=cross2);
    CPPUNIT_ASSERT_EQUAL(true,  cross1!=cross3);

    CPPUNIT_ASSERT_EQUAL(true,  cross1!=cross4);
    CPPUNIT_ASSERT_NO_THROW(cross1=cross3);

    CPPUNIT_ASSERT_EQUAL(false, cross1==cross2);
    CPPUNIT_ASSERT_EQUAL(true,  cross1!=cross2);

    tgImg.draw(cross1);
    tcImg.draw(cross1);

    tgImg.draw(cross4);
    tcImg.draw(cross4);
}

void TestDrawable::testCircleT() {

    Image  tgImg(300,300);
    ColorImage tcImg(300,300);

    CircleT<Ipp8u> circ1(Coord(100,100),5);
    CircleT<Ipp8u> circ2 = circ1;

    CircleT<Ipp8u> circ3(Coord(200,200),5);
    CircleT<Ipp8u> circ4(Coord(100,100),10, ColorT<Ipp8u>(static_cast<Ipp8u>(255)));

    CPPUNIT_ASSERT_EQUAL(true,  circ1==circ2);
    CPPUNIT_ASSERT_EQUAL(false, circ1==circ3);
    CPPUNIT_ASSERT_EQUAL(false, circ1==circ4);

    CPPUNIT_ASSERT_EQUAL(false, circ1!=circ2);
    CPPUNIT_ASSERT_EQUAL(true,  circ1!=circ3);

    CPPUNIT_ASSERT_EQUAL(true,  circ1!=circ4);
    CPPUNIT_ASSERT_NO_THROW(circ1=circ3);

    CPPUNIT_ASSERT_EQUAL(false, circ1==circ2);
    CPPUNIT_ASSERT_EQUAL(true,  circ1!=circ2);

    tgImg.draw(circ1);
    tcImg.draw(circ1);

    tgImg.draw(circ4);
    tcImg.draw(circ4);
}

void TestDrawable::testEllipseT() {

    Image  tgImg(300,300);
    ColorImage tcImg(300,300);

    EllipseT<Ipp8u> ell1(Coord(100,100), Coord(10,10), 45.0);
    EllipseT<Ipp8u> ell2 = ell1;

    EllipseT<Ipp8u> ell3(Coord(200,200), Coord(45,45), 0.0);
    EllipseT<Ipp8u> ell4(Coord(100,100), Coord(10,10), 90.0, ColorT<Ipp8u>(static_cast<Ipp8u>(255)));

    CPPUNIT_ASSERT_EQUAL(true,  ell1==ell2);
    CPPUNIT_ASSERT_EQUAL(false, ell1==ell3);
    CPPUNIT_ASSERT_EQUAL(false, ell1==ell4);

    CPPUNIT_ASSERT_EQUAL(false, ell1!=ell2);
    CPPUNIT_ASSERT_EQUAL(true,  ell1!=ell3);

    CPPUNIT_ASSERT_EQUAL(true,  ell1!=ell4);
    CPPUNIT_ASSERT_NO_THROW(ell1=ell3);

    CPPUNIT_ASSERT_EQUAL(false, ell1==ell2);
    CPPUNIT_ASSERT_EQUAL(true,  ell1!=ell2);

    tgImg.draw(ell1);
    tcImg.draw(ell1);

    tgImg.draw(ell4);
    tcImg.draw(ell4);
}

void TestDrawable::testLineT() {

    Image  tgImg(300,300);
    ColorImage tcImg(300,300);

    LineT<Ipp8u> line1(Coord(100,100), Coord(200,200));
    LineT<Ipp8u> line2 = line1;

    LineT<Ipp8u> line3(Coord(101,101), Coord(200,200));
    LineT<Ipp8u> line4(Coord(1,1),     Coord(2,2), ColorT<Ipp8u>(static_cast<Ipp8u>(255)));

    CPPUNIT_ASSERT_EQUAL(true,  line1==line2);
    CPPUNIT_ASSERT_EQUAL(false, line1==line3);
    CPPUNIT_ASSERT_EQUAL(false, line1==line4);

    CPPUNIT_ASSERT_EQUAL(false, line1!=line2);
    CPPUNIT_ASSERT_EQUAL(true,  line1!=line3);

    CPPUNIT_ASSERT_EQUAL(true,  line1!=line4);
    CPPUNIT_ASSERT_NO_THROW(line1=line3);

    CPPUNIT_ASSERT_EQUAL(false, line1==line2);
    CPPUNIT_ASSERT_EQUAL(true,  line1!=line2);

    tgImg.draw(line1);
    tcImg.draw(line1);

    tgImg.draw(line4);
    tcImg.draw(line4);
}

void TestDrawable::testPointT() {
    Image  tgImg(300,300);
    ColorImage tcImg(300,300);

    PointT<Ipp8u> point1(100,100);
    PointT<Ipp8u> point2 = point1;

    PointT<Ipp8u> point3(200,200), point4(1,1,ColorT<Ipp8u>(static_cast<Ipp8u>(255)));

    CPPUNIT_ASSERT_EQUAL(true,  point1==point2);
    CPPUNIT_ASSERT_EQUAL(false, point1==point3);
    CPPUNIT_ASSERT_EQUAL(false, point1==point4);

    CPPUNIT_ASSERT_EQUAL(false, point1!=point2);
    CPPUNIT_ASSERT_EQUAL(true,  point1!=point3);

    CPPUNIT_ASSERT_EQUAL(true,  point1!=point4);
    CPPUNIT_ASSERT_NO_THROW(point1=point3);

    CPPUNIT_ASSERT_EQUAL(false, point1==point2);
    CPPUNIT_ASSERT_EQUAL(true,  point1!=point2);

    tgImg.draw(point1);
    tcImg.draw(point1);

    tgImg.draw(point4);
    tcImg.draw(point4);
}
#endif
