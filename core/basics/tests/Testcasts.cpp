/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libfbasics - An core/basics/template for new NICE libraries
 * See file License for license information.
 */

#ifdef NICE_USELIB_CPPUNIT
#include "Testcasts.h"
#include <string>
#include <exception>
#include <core/basics/types.h>

using namespace NICE;

CPPUNIT_TEST_SUITE_REGISTRATION( Testcasts );

void Testcasts::setUp() {
}

void Testcasts::tearDown() {
}

void Testcasts::testConstructor() {
}

void Testcasts::testCasts() {
{
    float x=1.56;
    float y=1.34;
    CPPUNIT_ASSERT_EQUAL(2, round_to_nearest_cast<int>(x));
    CPPUNIT_ASSERT_EQUAL(1, round_to_nearest_cast<int>(y));
    CPPUNIT_ASSERT_EQUAL(-2, round_to_nearest_cast<int>(-x));
    CPPUNIT_ASSERT_EQUAL(-1, round_to_nearest_cast<int>(-y));
 }
{
    double x=1.56;
    double y=1.34;
    CPPUNIT_ASSERT_EQUAL(static_cast<unsigned char>(2), round_to_nearest_cast<unsigned char>(x));
    CPPUNIT_ASSERT_EQUAL(static_cast<char>(1), round_to_nearest_cast<char>(y));
    CPPUNIT_ASSERT_EQUAL(static_cast<char>(-2), round_to_nearest_cast<char>(-x));
    CPPUNIT_ASSERT_EQUAL(static_cast<char>(-1), round_to_nearest_cast<char>(-y));
 }
{
    float x=1.56;
    float y=1.34;
    CPPUNIT_ASSERT_EQUAL(2l, round_to_nearest_cast<long>(x));
    CPPUNIT_ASSERT_EQUAL(1ul, round_to_nearest_cast<ulong>(y));
    CPPUNIT_ASSERT_EQUAL(-2l, round_to_nearest_cast<long>(-x));
    CPPUNIT_ASSERT_EQUAL(-1l, round_to_nearest_cast<long>(-y));
 }
}
#endif
