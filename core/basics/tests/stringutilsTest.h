#ifndef TIMERTEST_H
#define TIMERTEST_H

#include <cppunit/extensions/HelperMacros.h>
#include "core/basics/stringutils.h"

/**
 * CppUnit-Testcase. 
 * Tests for stringutils.
 */
class stringutilsTest : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE( stringutilsTest );
  CPPUNIT_TEST( teststringutils );
  CPPUNIT_TEST_SUITE_END();
  
 private:
 
 public:
  void setUp();
  void tearDown();

  void teststringutils();

};

#endif // TIMERTEST_H
