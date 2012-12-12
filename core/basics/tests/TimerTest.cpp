#include "TimerTest.h"

#include <unistd.h>
#include <cmath>
#include <iomanip>

using namespace std;
using namespace NICE;

CPPUNIT_TEST_SUITE_REGISTRATION( TimerTest );


void TimerTest::setUp() {
}

void TimerTest::tearDown() {
}

void TimerTest::testTimer() {
  struct timeval t;
  t.tv_sec=123;
  t.tv_usec=456789;
  CPPUNIT_ASSERT_EQUAL(123.456789, Timer::convertTime(t));

  Timer timer;
  
  CPPUNIT_ASSERT_EQUAL(0, timer.getCounter());
  timer.start();
  CPPUNIT_ASSERT_EQUAL(0, timer.getCounter());
  usleep(40000);
  timer.stop();
  CPPUNIT_ASSERT_EQUAL(1, timer.getCounter());
  timer.start();
  CPPUNIT_ASSERT_EQUAL(1, timer.getCounter());
  usleep(40000);
  timer.stop();
  CPPUNIT_ASSERT_EQUAL(2, timer.getCounter());
  
  CPPUNIT_ASSERT_MESSAGE(

    "process time should be 0 during sleep",
    std::abs(0.0 - timer.getSum()) < 1E-20);
  CPPUNIT_ASSERT_MESSAGE(
    "process time should be 0 during sleep",
    std::abs(0.0 - timer.getMean()) < 1E-20);
  CPPUNIT_ASSERT_MESSAGE(
    "time measurement wrong (can depend on machine and current system load)",
    std::abs(0.082 - timer.getSumAbsolute()) < 0.01);
  CPPUNIT_ASSERT_MESSAGE(
    "time measurement wrong (can depend on machine and current system load)",
    std::abs(0.041 - timer.getMeanAbsolute()) < 0.005);
}
