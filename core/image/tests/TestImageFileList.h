#ifndef IMAGE_TESTIMAGEFILELIST_H
#define IMAGE_TESTIMAGEFILELIST_H

#include <cppunit/extensions/HelperMacros.h>

/**
 * CppUnit-Testcase. 
 * Tests for ImageFileList and PpmListOutput.
 */
class TestImageFileList : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE( TestImageFileList );
  CPPUNIT_TEST( testIO );
  CPPUNIT_TEST_SUITE_END();
  
 private:
 
 public:
  void setUp();
  void tearDown();

  /**
   * Test PpmImageSequence
   */  
  void testIO();
};

#endif // IMAGE_TESTIMAGEFILELIST_H
