/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libimage - An image/template for new NICE libraries
 * See file License for license information.
 */

#ifdef NICE_USELIB_CPPUNIT
#include "TestColor.h"
#include <string>
#include <vector>
#include <exception>

#include "core/image/ColorT.h"

using namespace std;
using namespace NICE;

CPPUNIT_TEST_SUITE_REGISTRATION( TestColor );

void TestColor::setUp() {
}

void TestColor::tearDown() {
}

void TestColor::testColorT() {
    Color c1(static_cast<Ipp8u>(0));
    Color c2 = c1;

    CPPUNIT_ASSERT_EQUAL(true,  c1==c2);
    CPPUNIT_ASSERT_EQUAL(false, c1!=c2);

    Color c3(0,0,0);
    Color c4 = c3;

    CPPUNIT_ASSERT_EQUAL(true,  c1==c2);
    CPPUNIT_ASSERT_EQUAL(false, c1!=c2);

    CPPUNIT_ASSERT_EQUAL(false, c1==c3);

    CPPUNIT_ASSERT_NO_THROW(c1=c3);
    CPPUNIT_ASSERT_EQUAL(true, c1==c3);
}
#endif
