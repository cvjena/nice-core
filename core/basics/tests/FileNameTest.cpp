#include "FileNameTest.h"

using namespace std;
using namespace NICE;

CPPUNIT_TEST_SUITE_REGISTRATION( FileNameTest );


void FileNameTest::setUp() {
}

void FileNameTest::tearDown() {
}

void FileNameTest::testFileName() {
  string path("/home/bajramov/VAMPIRE/");
  string basename("filename");
  string ext(".test");
  string name = basename + ext;
  string fileNameString = path + name;
  FileName fileName(fileNameString);
  CPPUNIT_ASSERT_EQUAL(fileNameString, fileName.str());
  CPPUNIT_ASSERT_EQUAL(path, fileName.extractPath().str());
  CPPUNIT_ASSERT_EQUAL(name, fileName.extractFileName().str());
  CPPUNIT_ASSERT_EQUAL(ext, fileName.extractExtension().str());

  CPPUNIT_ASSERT_EQUAL(false, fileName.isRelative() );
  FileName fileNameRelative(name);
  CPPUNIT_ASSERT_EQUAL(true, fileNameRelative.isRelative() );
}

void FileNameTest::testFileNameSlash() {
  string path("/home/bajramov/VAMPIRE");
  string pathSlash = path + "/";
  FileName fileName(path);
  fileName.addSlash();
  FileName fileNameSlash(pathSlash);
  fileNameSlash.removeSlash();
  CPPUNIT_ASSERT_EQUAL(path, fileNameSlash.str());
  CPPUNIT_ASSERT_EQUAL(pathSlash, fileName.str());

  CPPUNIT_ASSERT_EQUAL(false, fileName.isRelative() );
  CPPUNIT_ASSERT_EQUAL(false, fileNameSlash.isRelative() );
}

void FileNameTest::testPathRelative() {
  FileName fileName;

  // absolute pathes
  fileName.set("");
  CPPUNIT_ASSERT_EQUAL(false, fileName.isRelative() );
  fileName.set("/home/user/temporary.ext");
  CPPUNIT_ASSERT_EQUAL(false, fileName.isRelative() );
  fileName.set("/home/user/");
  CPPUNIT_ASSERT_EQUAL(false, fileName.isRelative() );
  fileName.set("/tmp/tmp.ect");
  CPPUNIT_ASSERT_EQUAL(false, fileName.isRelative() );

  // relative pathes and files
  fileName.set("temporary.ext");
  CPPUNIT_ASSERT_EQUAL(true, fileName.isRelative() );
  fileName.set("./");
  CPPUNIT_ASSERT_EQUAL(true, fileName.isRelative() );
  fileName.set("./temporary.ext");
  CPPUNIT_ASSERT_EQUAL(true, fileName.isRelative() );
  fileName.set("../temporary.ext");
  CPPUNIT_ASSERT_EQUAL(true, fileName.isRelative() );
  fileName.set("../../temporary.ext");
  CPPUNIT_ASSERT_EQUAL(true, fileName.isRelative() );
  fileName.set("../../temporary.ext");
  CPPUNIT_ASSERT_EQUAL(true, fileName.isRelative() );


}
