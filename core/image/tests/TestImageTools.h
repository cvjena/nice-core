
#ifndef _TESTIMAGETOOLS_H_
#define _TESTIMAGETOOLS_H_

#include <cppunit/extensions/HelperMacros.h>

/**
 * CppUnit-Testcase. 
 * Tests for ImageTools
 */
class TestImageTools : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE( TestImageTools );

    CPPUNIT_TEST( testabsDiff );
    CPPUNIT_TEST( testBoolean );

    CPPUNIT_TEST( testTreshold );

    CPPUNIT_TEST( testHough );
    CPPUNIT_TEST( testKLT );

    CPPUNIT_TEST( testautoCropRect );
    CPPUNIT_TEST( testaddConstBorder );
    CPPUNIT_TEST( testfindLocalMinima );

    CPPUNIT_TEST_SUITE_END();

    private:

    public:
    void setUp();
    void tearDown();

    /**
    * addConstBorder 
    */
    void testaddConstBorder();
    /**
    * autocrop 
    */
    void testautoCropRect();

    /**
    * findLocalMinima 
    */
    void testfindLocalMinima();

    /**
    * Split&Merge ColorImage testing
    */
    void testSplitMergeColorImage();


        /**
        * absDiff
        */
        void testabsDiff();

        /**
        * boolean (and) 
        */
        void testBoolean();

        /**
        * Treshold
        */
        void testTreshold();

        /**
        * Hough Transformation
        */
        void testHough();

        /**
        * KLTCornerDetector 
        */
        void testKLT();

};

#endif // _TESTIMAGETOOLS_H_
