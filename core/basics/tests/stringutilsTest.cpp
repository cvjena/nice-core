#include "stringutilsTest.h"

#include <cmath>

using namespace std;
using namespace NICE;

CPPUNIT_TEST_SUITE_REGISTRATION( stringutilsTest );


void stringutilsTest::setUp() {
}

void stringutilsTest::tearDown() {
}

void stringutilsTest::teststringutils() {
  int x=-1234;
  string sx="-1234";
  CPPUNIT_ASSERT_EQUAL(sx, itostr(x));
  vector<string> test;
  string data="data-";
  for(int i=0;i<10;i++)
    test.push_back(data + itostr(i) + "\t" + itostr(i));
  vector<vector<string> > list=splitStringVector(test,'\t');
  for(int i=0;i<10;i++) {
    CPPUNIT_ASSERT_EQUAL(data+itostr(i),list[i][0]);
    CPPUNIT_ASSERT_EQUAL(itostr(i),list[i][1]);

  }

}
