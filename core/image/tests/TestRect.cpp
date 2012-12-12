
#include "TestRect.h"

#include "core/image/RectT.h"

using namespace std;
using namespace NICE;

CPPUNIT_TEST_SUITE_REGISTRATION( TestRect );

void TestRect::setUp() {
}

void TestRect::tearDown() {
}

void TestRect::testRect () {
    

    // test rect from 2 coordinates
    {

        Rect r(Coord(10,15) , Coord(35,30));

        CPPUNIT_ASSERT_EQUAL(10, r.left);    
        CPPUNIT_ASSERT_EQUAL(15, r.top);
        CPPUNIT_ASSERT_EQUAL(35, r.right());    
        CPPUNIT_ASSERT_EQUAL(30, r.bottom());

        CPPUNIT_ASSERT_EQUAL(25, r.width);
        CPPUNIT_ASSERT_EQUAL(15, r.height);

        Rect r2(Coord(35,30), Coord(10,15));
        CPPUNIT_ASSERT_EQUAL(true, r==r2);
    }

}

void TestRect::testCenter () {

    Rect rect(5,10, 30,20);
    Coord center = rect.center();

    CPPUNIT_ASSERT_EQUAL(20, center.x);
    CPPUNIT_ASSERT_EQUAL(20, center.y);
}

void TestRect::testArea() {
    
    Rect rect(4,4, 10,15);

    CPPUNIT_ASSERT_EQUAL(150, static_cast<Ipp32s>(rect.area()));
}

void TestRect::testIntersect() {

    Rect r1,r2,ir;

    // horizontal missmatch
    r1 = Rect(10, 10, 10,10);
    r2 = Rect(50, 10, 10,10);
    
    CPPUNIT_ASSERT_EQUAL(false, r1.intersect(r2,ir));

    // vertical missmatch
    r1 = Rect(10, 10, 10,10);
    r2 = Rect(10, 50, 10,10);
    
    CPPUNIT_ASSERT_EQUAL(false, r1.intersect(r2,ir));

    // horizontal and vertical missmatch
    r1 = Rect(10, 10, 10,10);
    r2 = Rect(50, 50, 10,10);
    
    CPPUNIT_ASSERT_EQUAL(false, r1.intersect(r2,ir));

    // identical rectangles
    r1 = Rect(10, 10, 10,10);
    r2 = Rect(10, 10, 10,10);
    
    CPPUNIT_ASSERT_EQUAL(true, r1.intersect(r2,ir));
    CPPUNIT_ASSERT_EQUAL(10, ir.left);
    CPPUNIT_ASSERT_EQUAL(10, ir.top);
    CPPUNIT_ASSERT_EQUAL(10, ir.width);
    CPPUNIT_ASSERT_EQUAL(10, ir.height);

    // horizontal adjacent rectangles
    r1 = Rect(10, 10, 10,10);
    r2 = Rect(12,  1, 10,10);
    
    CPPUNIT_ASSERT_EQUAL(true, r1.intersect(r2,ir));
    CPPUNIT_ASSERT_EQUAL(12, ir.left);
    CPPUNIT_ASSERT_EQUAL(10, ir.top);
    CPPUNIT_ASSERT_EQUAL( 8, ir.width);
    CPPUNIT_ASSERT_EQUAL( 1, ir.height);

    // vertical adjacent rectangles
    r1 = Rect( 1, 10, 10,10);
    r2 = Rect(10, 12, 10,10);
    
    CPPUNIT_ASSERT_EQUAL(true, r1.intersect(r2,ir));
    CPPUNIT_ASSERT_EQUAL(10, ir.left);
    CPPUNIT_ASSERT_EQUAL(12, ir.top);
    CPPUNIT_ASSERT_EQUAL( 1,  ir.width);
    CPPUNIT_ASSERT_EQUAL( 8,  ir.height);

    // general intersection
    r1 = Rect(10, 10, 10,10);
    r2 = Rect(15, 15, 10,10);
    
    CPPUNIT_ASSERT_EQUAL(true, r1.intersect(r2,ir));
    CPPUNIT_ASSERT_EQUAL(15, ir.left);
    CPPUNIT_ASSERT_EQUAL(15, ir.top);
    CPPUNIT_ASSERT_EQUAL( 5,  ir.width);
    CPPUNIT_ASSERT_EQUAL( 5,  ir.height);
}
