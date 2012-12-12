/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libfbasics - An core/basics/template for new NICE libraries
 * See file License for license information.
 */
#ifndef _TESTCASTS_FBASICS_H
#define _TESTCASTS_FBASICS_H

#include <cppunit/extensions/HelperMacros.h>
#include <core/basics/RoundToNearest.h>

/**
 * CppUnit-Testcase. 
 * Test template...
 */
class Testcasts : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE( Testcasts );
  CPPUNIT_TEST( testCasts );
  CPPUNIT_TEST_SUITE_END();
  
 private:
 
 public:
  void setUp();
  void tearDown();

  /**
   * Constructor / Destructor testing 
   */  
  void testConstructor();

  /**
   * Test something...
   */  
  void testCasts();
};

#endif // _TESTCASTS_FBASICS_H
