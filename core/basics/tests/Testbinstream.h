/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libiocompression - An iocompression/template for new NICE libraries
 * See file License for license information.
 */
#ifndef _TESTBINSTREAM_IOCOMPRESSION_H
#define _TESTBINSTREAM_IOCOMPRESSION_H

#include <cppunit/extensions/HelperMacros.h>

/**
 * CppUnit-Testcase. 
 * Test template...
 */
class Testbinstream : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE( Testbinstream );
  CPPUNIT_TEST( testOperators );
  CPPUNIT_TEST( testOperatorsGz );
  CPPUNIT_TEST_SUITE_END();
  
 private:
 
 public:
  void setUp();
  void tearDown();

  void testOperators();
  void testOperatorsGz();

  void testSomething();
};

#endif // _TESTBINSTREAM_IOCOMPRESSION_H
