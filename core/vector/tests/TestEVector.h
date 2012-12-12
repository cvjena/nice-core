/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libbasicvector - A simple vector library
 * See file License for license information.
 */
#ifndef _TESTEVECTOR_H
#define _TESTEVECTOR_H

#include <cppunit/extensions/HelperMacros.h>

/**
 * CppUnit-Testcase. 
 * Tests for Image and ColorImage
 */
class TestEVector : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE( TestEVector );
  CPPUNIT_TEST( testAssignment );
  CPPUNIT_TEST( testAccess );
  CPPUNIT_TEST( testConst );
  CPPUNIT_TEST( testCopy );
  CPPUNIT_TEST( testRangeAccess );
  CPPUNIT_TEST( testExternal );
  CPPUNIT_TEST( testArithmetics );
  CPPUNIT_TEST( testIO );
  CPPUNIT_TEST( testRangeChecks );
  CPPUNIT_TEST( testScalarProduct );
  CPPUNIT_TEST( testEqual );
  CPPUNIT_TEST( testStatistics );
  CPPUNIT_TEST( testDistance );
  CPPUNIT_TEST( testRandUni );
  CPPUNIT_TEST( testRandGauss );
  CPPUNIT_TEST( testFlip );
  CPPUNIT_TEST( testSort );
  CPPUNIT_TEST( testGauss );
  CPPUNIT_TEST( testNorm );
  CPPUNIT_TEST( testAbs );
  CPPUNIT_TEST( testRowMultiply );
  CPPUNIT_TEST( testMultiply );
  CPPUNIT_TEST( testShift );
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
   * Test range access with getRange, getRangeRef and append functions.
   */  
  void testRangeAccess();

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
   * Test IO funtionalify (<< and >>)
   */
  void testIO();

  /**
   * Test ranged checked subclasses.
   */  
  void testRangeChecks();
  
  /**
   * Test scalar product 
   */  
  void testScalarProduct();

  /**
   * Test == and != operators 
   */  
  void testEqual();
  
  /**
   * Test vector distance
   */  
  void testDistance();
  
  /**
   * Test uniform random
   */  
  void testRandUni();
  /**
   * Test gauss random
   */  
  void testRandGauss();
  /**
   * Test reverse ordering
   */  
  void testFlip();
  /**
   * Test sorting 
   */  
  void testSort();
  /**
   * Test statistics function 
   */  
  void testStatistics();
  /**
   * Test gauss function 
   */  
  void testGauss();
  /**
   * Test Norm 
   */  
  void testNorm();
  /**
   * Test Abs 
   */  
  void testAbs();
  /**
   * Test Multiply 
   */  
  void testMultiply();
  /**
   * Test Multiply 
   */  
  void testRowMultiply();

    /**
    * Test Shift
    */  
    void testShift();
    
    /**
    * Test CircularMean
    */  
    void testCircularMean();
};

#endif // _TESTEVECTOR_H
