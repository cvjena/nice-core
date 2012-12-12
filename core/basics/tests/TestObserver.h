#ifndef TestObserver_H
#define TestObserver_H

#include <cppunit/extensions/HelperMacros.h>
#include "core/basics/Observer.h"
#include "core/basics/Observable.h"

/**
 * CppUnit-Testcase. 
 */
class TestObserver : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE( TestObserver );
  CPPUNIT_TEST( testObserver );
  CPPUNIT_TEST_SUITE_END();
  
 private:
 
 public:
  void setUp();
  void tearDown();

  void testObserver();

};

#endif // TestObserver_H
