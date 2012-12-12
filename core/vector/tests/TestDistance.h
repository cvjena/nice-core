/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libbasicvector - An core/vector/template for new NICE libraries
 * See file License for license information.
 */
#ifndef _TESTDISTANCE_BASICVECTOR_H
#define _TESTDISTANCE_BASICVECTOR_H

#include <cppunit/extensions/HelperMacros.h>
#include <core/vector/Distance.h>

/**
 * CppUnit-Testcase. 
 * Test template...
 */
class TestDistance : public CppUnit::TestFixture {

    CPPUNIT_TEST_SUITE( TestDistance );
    
    CPPUNIT_TEST(testDistance);

    CPPUNIT_TEST(testEuclidianDistance);
    CPPUNIT_TEST(testCosinusDistance);
    CPPUNIT_TEST(testScalarProductDistance);
    CPPUNIT_TEST(testBhattacharyyaDistance);
    CPPUNIT_TEST(testKLDistance);

    CPPUNIT_TEST_SUITE_END();
  
 private:
 
 public:
    void setUp();
    void tearDown();

    /**
    * Constructor / Destructor testing 
    */  
    void testConstructor();

    void testDistance();

    void testEuclidianDistance();

    void testCosinusDistance();

    void testScalarProductDistance();

    void testBhattacharyyaDistance();

    void testKLDistance();
};

#endif // _TESTDISTANCE_BASICVECTOR_H
