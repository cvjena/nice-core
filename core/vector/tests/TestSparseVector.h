#ifndef _TESTSPARSEVECTOR_H
#define _TESTSPARSEVECTOR_H

#include <cppunit/extensions/HelperMacros.h>

/**
 * CppUnit-Testcase. 
 */
class TestSparseVector : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE( TestSparseVector );
  CPPUNIT_TEST( testProducts );
  CPPUNIT_TEST( testConversionToVectorT );
  CPPUNIT_TEST_SUITE_END();
  
private:
 
public:
  void setUp() {};
  void tearDown() {};

  void testProducts();
  void testConversionToVectorT();

};

#endif // _TESTEVECTOR_H
