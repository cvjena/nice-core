#include "cppunitexTest.h"

#include "core/basics/cppunitex.h"

using namespace std;
using namespace NICE;

CPPUNIT_TEST_SUITE_REGISTRATION( CppUnitExTest );


void CppUnitExTest::setUp() {
}

void CppUnitExTest::tearDown() {
}

void CppUnitExTest::testNotNaN() {
  double zero = 1.0;
  zero -= zero;
  double nd = zero / zero;
  double nf = (float)zero / (float)zero;
  
  CPPUNIT_ASSERT_IS_NAN(nd);
  CPPUNIT_ASSERT_IS_NAN(nf);
  CPPUNIT_ASSERT_NOT_NAN(1.0);
  CPPUNIT_ASSERT_NOT_NAN(1.0f);
  CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(1.0, 2.0 * 0.5, 1E-20);
  CPPUNIT_ASSERT_THROW(CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(1.0, nd, 1E-20),
                       CppUnit::Exception);
}

