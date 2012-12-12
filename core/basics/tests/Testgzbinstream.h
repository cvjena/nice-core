/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libiocompression - An iocompression/template for new NICE libraries
 * See file License for license information.
 */
#ifndef _TESTBINSTREAM_IOCOMPRESSION_H
#define _TESTBINSTREAM_IOCOMPRESSION_H

#include <cppunit/extensions/HelperMacros.h>
#include <core/basics/gzbinstream.h>

/**
 * CppUnit-Testcase. 
 * Test template...
 */
class Testgzbinstream : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE( Testgzbinstream );
  CPPUNIT_TEST( testOperators );
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
   * Operator testing 
   */  
  void testOperators();

};

#endif // _TESTBINSTREAM_IOCOMPRESSION_H
