#ifndef CPPUNITEXTEST_H
#define CPPUNITEXTEST_H

#include <cppunit/extensions/HelperMacros.h>

/**
 * CppUnit-Testcase. 
 * Tests for FileName.
 */
class CppUnitExTest : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE( CppUnitExTest );
  CPPUNIT_TEST( testNotNaN );
  CPPUNIT_TEST_SUITE_END();
  
 private:
 
 public:
  void setUp();
  void tearDown();

  void testNotNaN();

};

#endif // CPPUNITEXTEST_H
