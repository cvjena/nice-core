#include "numerictoolsTest.h"
#include <core/basics/cppunitex.h>

#include <core/basics/numerictools.h>
#include <core/basics/tools.h>
//#include <core/basics/stringutils.h>
#include <core/basics/Exception.h>
#include <core/basics/Streamable.h>
#include <core/basics/BinStreamable.h>
#include <core/basics/Timer.h>
#include <core/basics/FrameRateCounter.h>
#include <core/basics/FileName.h>
#include <core/basics/NonCopyable.h>
#include <core/basics/Log.h>
#include <core/basics/Observable.h>
#include <core/basics/Observer.h>
//#include <core/basics/vectorio.h>
//#include <core/basics/assert.h>
#include <assert.h>
// #include <core/basics/ransac.h>
#include <core/basics/deprecated.h>
#include <core/basics/types.h>

using namespace std;
using namespace NICE;

CPPUNIT_TEST_SUITE_REGISTRATION( NumericToolsTest );


void NumericToolsTest::setUp() {
}

void NumericToolsTest::tearDown() {
}

void NumericToolsTest::testSign() {
  CPPUNIT_ASSERT_EQUAL(1, sign(10));
  CPPUNIT_ASSERT_EQUAL(-1, sign(-10));
  CPPUNIT_ASSERT_EQUAL(0, sign(0));
  CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0f, sign(5.0f), 1E-6);
  CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(-1.0f, sign(-5.0f), 1E-6);
  CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(0.0f, sign(0.0f), 1E-6);
  CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(1.0, sign(5.0), 1E-20);
  CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(-1.0, sign(-5.0), 1E-20);
  CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(0.0, sign(0.0), 1E-20);
  CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(0.0, sign(1E-17), 1E-20);
  CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(0.0, sign(-1E-40), 1E-20);
  CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(
      1.0, sign(std::numeric_limits<double>::epsilon()), 1E-20);
  CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(
      0.0, sign(std::numeric_limits<double>::epsilon() / 2.0), 1E-20);
  CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(
      1.0f, sign(std::numeric_limits<float>::epsilon()), 1E-20);
  CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(
      0.0f, sign(std::numeric_limits<float>::epsilon() / 2.0f), 1E-20);
}

void NumericToolsTest::testIsZeroAndEqual() {
  CPPUNIT_ASSERT(isZero(1E-10f));
  CPPUNIT_ASSERT(!isZero(1E-10));
  CPPUNIT_ASSERT(isZero(1E-50));

  CPPUNIT_ASSERT(isZero(1E-10f, 1E-9f));
  CPPUNIT_ASSERT(!isZero(1E-10, 1E-10));
  CPPUNIT_ASSERT(isZero(1E-10, 1E-9));
  CPPUNIT_ASSERT(isZero(1E-50, 1E-49));

  CPPUNIT_ASSERT(isEqual(1E-10f, 2E-10f, 1E-9f));
  CPPUNIT_ASSERT(isEqual(1E-10, 2E-10, 1E-9));
  CPPUNIT_ASSERT(!isEqual(1E-10, 2E-10, 1E-10));
}

void NumericToolsTest::testImposeSign() {
  CPPUNIT_ASSERT_EQUAL(-25, imposeSign(25, -17));
  CPPUNIT_ASSERT_EQUAL(0, imposeSign(25, 0));
  CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(-25.0f, imposeSign(-25.0f, -17.0f), 1E-6);
  CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(-25.0, imposeSign(-25.0, -17.0), 1E-20);
  CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(-25.0f, imposeSign(25.0f, -17.0f), 1E-6);
  CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(-25.0, imposeSign(25.0, -17.0), 1E-20);
}

void NumericToolsTest::testAbsolute() {
  CPPUNIT_ASSERT_EQUAL(25, absolute((int)-25));
  CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(25.0f, absolute(-25.0f), 1E-6);
  CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(25.0, absolute(-25.0), 1E-20);
  CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(1E-10, absolute(-1E-10), 1E-20);
  CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(1E-10, absolute(1E-10), 1E-20);
}

void NumericToolsTest::testSquare() {
  CPPUNIT_ASSERT_EQUAL(25, square(5));
  CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(25.0f, square(5.0f), 1E-6);
  CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(25.0, square(5.0), 1E-20);
}

void NumericToolsTest::testCubeRoot() {
  CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(2.0, cubeRoot(8.0), 1E-20);
  CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(-2.0, cubeRoot(-8.0), 1E-20);
}

void NumericToolsTest::testIsNaN() {
  double zero = 1.0;
  zero -= zero;
  CPPUNIT_ASSERT(isNaN(0.0 / zero));
  CPPUNIT_ASSERT(isNaN(0.0f / (float)zero));
  CPPUNIT_ASSERT(isNaN(doubleNaN()));
  CPPUNIT_ASSERT(isNaN(floatNaN()));
}

void NumericToolsTest::testLimitValue() {
  CPPUNIT_ASSERT_EQUAL(11, limitValue(11, 10, 30));
  CPPUNIT_ASSERT_EQUAL(29, limitValue(29, 10, 30));
  CPPUNIT_ASSERT_EQUAL(10, limitValue(10, 10, 30));
  CPPUNIT_ASSERT_EQUAL(10, limitValue(9, 10, 30));
  CPPUNIT_ASSERT_EQUAL(30, limitValue(30, 10, 30));
  CPPUNIT_ASSERT_EQUAL(30, limitValue(31, 10, 30));
}

void NumericToolsTest::testStringToDouble() {
  CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(-15E3, stringToDouble("-15E3"), 1E-20);
  CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(-15E3, stringToDouble("  -15E3  "), 1E-20);
  CPPUNIT_ASSERT_THROW(stringToDouble("-15E3  x"), Exception);
  CPPUNIT_ASSERT_THROW(stringToDouble("-15E"), Exception);
}

void NumericToolsTest::testStringToInt() {
  CPPUNIT_ASSERT_EQUAL(-15, (int)stringToInt("-15"));
  CPPUNIT_ASSERT_EQUAL(-15, (int)stringToInt("  -15  "));
  CPPUNIT_ASSERT_THROW(stringToInt("-15  x"), Exception);
  CPPUNIT_ASSERT_THROW(stringToInt("-15E"), Exception);
}
