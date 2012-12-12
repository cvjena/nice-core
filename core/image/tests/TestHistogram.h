
#ifndef _TESTHISTOGRAM_H_
#define _TESTHISTOGRAM_H_

#include <cppunit/extensions/HelperMacros.h>

/**
 * CppUnit-Testcase.
 * Tests for Histogram Operations
 */
class TestHistogram : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE( TestHistogram );

  CPPUNIT_TEST( testGrayHistogram );
  CPPUNIT_TEST( testGrayHistogramFromRect );

  CPPUNIT_TEST( testColorHistogram );
  CPPUNIT_TEST( testCombined );

  CPPUNIT_TEST( testIterator );

  CPPUNIT_TEST( testProp );
  CPPUNIT_TEST( testOp );

  CPPUNIT_TEST( testCumulative_Normalized );

  CPPUNIT_TEST_SUITE_END();

 private:
 public:
  void setUp();
  void tearDown();

  void testIterator();

  void testGrayHistogram();
  void testGrayHistogramFromRect();

  void testColorHistogram();
  void testCombined();

  void testProp();
  void testOp();

  void testCumulative_Normalized();
};

#endif // _TESTHISTOGRAM_H_
