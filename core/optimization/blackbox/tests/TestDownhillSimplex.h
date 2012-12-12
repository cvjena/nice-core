#ifndef _TESTDOWNHILLSIMPLEX_H
#define _TESTDOWNHILLSIMPLEX_H

#include <cppunit/extensions/HelperMacros.h>
#include "core/optimization/blackbox/DownhillSimplexOptimizer.h"

/**
 * @brief CppUnit-Testcase for Downhill-Simplex Optimization
 * @author Alexander Freytag
 * @date 27-09-2012
 */
class TestDownhillSimplex : public CppUnit::TestFixture {

    CPPUNIT_TEST_SUITE( TestDownhillSimplex );
    
    CPPUNIT_TEST(testDHS_1Dim);
    CPPUNIT_TEST(testDHS_2Dim);
    
    CPPUNIT_TEST_SUITE_END();
  
 private:
 
 public:
    void setUp();
    void tearDown();

    /**
    * @brief Test of 1D optimziation with a simple convex cost function
    * @date 27-09-2012
    * @author Alexander Freytag
    */      
    void testDHS_1Dim();

    /**
    * @brief Test of 2D optimziation with a simple convex cost function
    * @date 27-09-2012
    * @author Alexander Freytag
    */    
    void testDHS_2Dim();

};

#endif // _TESTFASTHIK_H
