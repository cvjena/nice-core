#ifndef FILENAMETEST_H
#define FILENAMETEST_H

#include <cppunit/extensions/HelperMacros.h>
#include "core/basics/FileName.h"

/**
 * CppUnit-Testcase. 
 * Tests for FileName.
 */
class FileNameTest : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE( FileNameTest );
  CPPUNIT_TEST( testFileName );
  CPPUNIT_TEST( testFileNameSlash );
  CPPUNIT_TEST_SUITE_END();
  
 private:
 
 public:
  void setUp();
  void tearDown();

  /**
   * Test FileName
   */  
  void testFileName();

  /**
   * Test FileName addSlash/removeSlash
   */
  void testFileNameSlash();

};

#endif // FILENAMETEST_H
