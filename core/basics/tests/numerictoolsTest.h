#ifndef NUMERICOTOOLSTEST_H
#define NUMERICOTOOLSTEST_H

#include <cppunit/extensions/HelperMacros.h>
#include "core/basics/numerictools.h"

/**
 * CppUnit-Testcase. 
 * Tests for FileName.
 */
class NumericToolsTest : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE( NumericToolsTest );
  CPPUNIT_TEST( testSign );
  CPPUNIT_TEST( testIsZeroAndEqual );
  CPPUNIT_TEST( testSquare );
  CPPUNIT_TEST( testCubeRoot );
  CPPUNIT_TEST( testIsNaN );
  CPPUNIT_TEST( testLimitValue );
  CPPUNIT_TEST( testStringToDouble );
  CPPUNIT_TEST( testStringToInt );
  CPPUNIT_TEST( testImposeSign );
  CPPUNIT_TEST( testAbsolute );
  CPPUNIT_TEST_SUITE_END();
  
 private:
 
 public:
  void setUp();
  void tearDown();

  void testSign();
  void testIsZeroAndEqual();
  void testSquare();
  void testCubeRoot();
  void testIsNaN();
  void testLimitValue();
  void testStringToDouble();
  void testStringToInt();
  void testImposeSign();
  void testAbsolute();
};

#endif // NUMERICOTOOLSTEST_H
