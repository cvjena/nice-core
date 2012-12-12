/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libiocompression - An iocompression/template for new NICE libraries
 * See file License for license information.
 */
#ifndef _TESTSTREAMABLE_BASICVECTOR_H
#define _TESTSTREAMABLE_BASICVECTOR_H


#ifdef NICE_USELIB_LINAL 
#include <LinAl/vectorC.h>
#include <LinAl/matrixCF.h>
#include <LinAl/matio.h>
#include <LinAl/operatorsT.h>
#endif
#include <cppunit/extensions/HelperMacros.h>
#include <core/basics/Streamable.h>
#include <core/basics/BinStreamable.h>
#include <core/vector/VectorT.h>

class StreamableClass;
/**
 * CppUnit-Testcase. 
 * Test template...
 */
class TestStreamable : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE( TestStreamable );
  CPPUNIT_TEST( testASCII );
  CPPUNIT_TEST( testBIN );
  CPPUNIT_TEST( testGZ );
  CPPUNIT_TEST( testGZBIN );
  CPPUNIT_TEST( testBZ );
  CPPUNIT_TEST_SUITE_END();
 private:
  StreamableClass *s;
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

  /**
   * Test ascii read and write 
   */  
  void testASCII();
  /**
   * Test binary read and write 
   */  
  void testBIN();
  /**
   * Test ascii gzip read and write 
   */  
  void testGZ();
  /**
   * Test binary gzip read and write 
   */  
  void testGZBIN();
  /**
   * Test bzip read and write 
   */  
  void testBZ();
};

#endif // _TESTSTREAMABLE_BASICVECTOR_H
