#ifndef TIMERTEST_H
#define TIMERTEST_H

#include <cppunit/extensions/HelperMacros.h>
#include "core/basics/Timer.h"

/**
 * CppUnit-Testcase. 
 * Tests for Timer.
 */
class TimerTest : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE( TimerTest );
  CPPUNIT_TEST( testTimer );
  CPPUNIT_TEST_SUITE_END();
  
 private:
 
 public:
  void setUp();
  void tearDown();

  void testTimer();

};

#endif // TIMERTEST_H
