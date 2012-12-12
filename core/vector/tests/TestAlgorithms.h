/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libbasicvector - An core/vector/template for new NICE libraries
 * See file License for license information.
 */
#ifndef _TESTALGORITHMS_BASICVECTOR_H
#define _TESTALGORITHMS_BASICVECTOR_H

#include <cppunit/extensions/HelperMacros.h>
#include <core/vector/Algorithms.h>

/**
 * CppUnit-Testcase. 
 * Test template...
 */
class TestAlgorithms : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE( TestAlgorithms );
  CPPUNIT_TEST( testSomething );
  CPPUNIT_TEST( testInvert3x3 );
  CPPUNIT_TEST( testCholesky );
  CPPUNIT_TEST( testCholeskyLargeScale );
  CPPUNIT_TEST( testInvert );
  CPPUNIT_TEST_SUITE_END();
  
 private:
 
 public:
  void setUp();
  void tearDown();

  void testSomething();
  
  void testInvert3x3();
  void testInvert();
  
  void testCholesky();
  void testCholeskyLargeScale();
};

#endif // _TESTALGORITHMS_BASICVECTOR_H
