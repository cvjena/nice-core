
#ifndef _TESTMORPH_H_
#define _TESTMORPH_H_

#include <cppunit/extensions/HelperMacros.h>

/**
 * CppUnit-Testcase. 
 * Tests for Filter Operations
 */
class TestMorph : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE( TestMorph );

    CPPUNIT_TEST( testRanking );
    CPPUNIT_TEST( testMorphological );

    CPPUNIT_TEST( testMorphologicalIP );

    CPPUNIT_TEST( testRankingWithStructure );
    CPPUNIT_TEST( testMorphologicalWithStructure );

    CPPUNIT_TEST( testHitAndMiss );

    CPPUNIT_TEST_SUITE_END();

private:

public:
    void setUp();
    void tearDown();

    void testRanking();
    void testMorphological();
    void testMorphologicalIP();

    void testRankingWithStructure();
    void testMorphologicalWithStructure();

    void testHitAndMiss();
};

#endif // _TESTMORPH_H_
