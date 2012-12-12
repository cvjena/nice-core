/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libbasicvector - A simple vector library
 * See file License for license information.
 */
#ifndef _TESTEMATRIX_H
#define _TESTEMATRIX_H

#include <cppunit/extensions/HelperMacros.h>

/**
 * CppUnit-Testcase. 
 * Tests for Image and ColorImage
 */
class TestERowMatrix : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE( TestERowMatrix );
  CPPUNIT_TEST( testAssignment );
  CPPUNIT_TEST( testAccess );
  CPPUNIT_TEST( testConst );
  CPPUNIT_TEST( testCopy );
  CPPUNIT_TEST( testExternal );
  CPPUNIT_TEST( testArithmetics );
  CPPUNIT_TEST( testRangeChecks );
  CPPUNIT_TEST( testEqual );
  CPPUNIT_TEST( testTranspose );
  CPPUNIT_TEST( testMultiply );
  CPPUNIT_TEST( testDet );
  CPPUNIT_TEST( testEigenValues );
  CPPUNIT_TEST_SUITE_END();
  
private:
 
public:
  void setUp();
  void tearDown();

  /**
   * Test VectorT::operator[]()
   */  
  void testAccess();

  /**
   * Test VectorT::operator[]()
   */  
  void testConst();

  /**
   * Test copying.
   */  
  void testCopy();

  /**
   * Test external storage.
   */  
  void testExternal();

  /**
   * Test operator=.
   */  
  void testAssignment();

  /**
   * Test operator+= etc.
   */  
  void testArithmetics();

  /**
   * Test ranged checked subclasses.
   */  
  void testRangeChecks();

  /**
   * Test == and != operators 
   */  
  void testEqual();

  void testTranspose();
  void testMultiply();
  void testDet();
  void testEigenValues();
};

#endif // _TESTEMATRIX_H
