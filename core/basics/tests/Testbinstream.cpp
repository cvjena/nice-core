/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libiocompression - An iocompression/template for new NICE libraries
 * See file License for license information.
 */

#ifdef NICE_USELIB_CPPUNIT
#include "Testbinstream.h"
#include <string>
#include <vector>
#include <exception>
#include <core/basics/binstream.h>
#include <core/basics/gzbinstream.h>

using namespace NICE;

CPPUNIT_TEST_SUITE_REGISTRATION( Testbinstream );

void Testbinstream::setUp() {
}

void Testbinstream::tearDown() {
  remove("tmp.bin");
}

void Testbinstream::testOperators() {
  int i= rand();
  char c= rand();
  short s = rand();
  long l = rand();
  unsigned int ui = rand();
  unsigned short us = rand();
  unsigned char uc = rand();
  unsigned long ul = rand();
  float f = rand();
  double d = rand();
  long long ll = rand();
  unsigned long long ull = rand();
  long double ld = rand();
  std::string str="string";
  ofbinstream file("tmp.bin");
  char array[]="array";
  std::vector<int> v(3);
  v[0] = 10;
  v[1] = 20;
  v[2] = 30;
  (NICE::obinstream&)file
      << 'x' << i << 'x' << c << 'x' << s << 'x' << l << 'x' << ll 
      << 'x' << f << 'x' << d << 'x' << ld
      << 'x' << ui << 'x' << uc << 'x' << us << 'x' << ul << 'x' << ull
      << "array" << 'x' << str << v;
  file.close();
  int i_new= 0;
  char c_new= 0;
  short s_new= 0;
  long l_new= 0;
  unsigned int ui_new= 0;
  unsigned short us_new= 0;
  unsigned char uc_new= 0;
  unsigned long ul_new= 0;
  float f_new= 0;
  double d_new= 0;
  long long ll_new= 0;
  unsigned long long ull_new= 0;
  long double ld_new= 0;
  std::string str_new;
  std::vector<int> v_new;
  char t[14];
  char buf[10];
  ifbinstream in("tmp.bin");
  (ibinstream&)in
    >> t[0] >> i_new >> t[1] >> c_new >> t[2] >> s_new >> t[3] >> l_new >> t[4] >> ll_new
    >> t[5] >> f_new >> t[6] >> d_new >> t[7] >> ld_new 
    >> t[8] >> ui_new >> t[9] >> uc_new >> t[10] >> us_new >> t[11] >> ul_new >> t[12] >> ull_new
    >> buf >> t[13] >> str_new >> v_new;
  in.close();
    CPPUNIT_ASSERT_EQUAL(i, i_new);
    CPPUNIT_ASSERT_EQUAL(c, c_new);
    CPPUNIT_ASSERT_EQUAL(s, s_new);
    CPPUNIT_ASSERT_EQUAL(l, l_new);
    CPPUNIT_ASSERT_EQUAL(ll, ll_new);
    CPPUNIT_ASSERT_EQUAL(ui, ui_new);
    CPPUNIT_ASSERT_EQUAL(uc, uc_new);
    CPPUNIT_ASSERT_EQUAL(us, us_new);
    CPPUNIT_ASSERT_EQUAL(ul, ul_new);
    CPPUNIT_ASSERT_EQUAL(ull, ull_new);
    CPPUNIT_ASSERT_EQUAL(f, f_new);
    CPPUNIT_ASSERT_EQUAL(d, d_new);
    CPPUNIT_ASSERT_EQUAL(ld, ld_new);
    CPPUNIT_ASSERT_EQUAL(str, str_new);
  for(uint i=0;i<strlen(array);i++) {
      CPPUNIT_ASSERT_EQUAL(buf[i], array[i]);
  }
  for(uint i=0;i<v.size();i++) {
    CPPUNIT_ASSERT_EQUAL(v[i], v_new[i]);
  }
  for(int i=0;i<14;i++) {
      CPPUNIT_ASSERT_EQUAL(t[i], 'x');
  }
}

void Testbinstream::testOperatorsGz() {
  int i= rand();
  char c= rand();
  short s = rand();
  long l = rand();
  unsigned int ui = rand();
  unsigned short us = rand();
  unsigned char uc = rand();
  unsigned long ul = rand();
  float f = rand();
  double d = rand();
  long long ll = rand();
  unsigned long long ull = rand();
  long double ld = rand();
  std::string str="string";
  ogzbinstream file("tmp.bin");
  char array[]="array";
  std::vector<int> v(3);
  v[0] = 10;
  v[1] = 20;
  v[2] = 30;
  (NICE::obinstream&)file
      << 'x' << i << 'x' << c << 'x' << s << 'x' << l << 'x' << ll 
      << 'x' << f << 'x' << d << 'x' << ld
      << 'x' << ui << 'x' << uc << 'x' << us << 'x' << ul << 'x' << ull
      << "array" << 'x' << str << v;
  file.close();
  int i_new= 0;
  char c_new= 0;
  short s_new= 0;
  long l_new= 0;
  unsigned int ui_new= 0;
  unsigned short us_new= 0;
  unsigned char uc_new= 0;
  unsigned long ul_new= 0;
  float f_new= 0;
  double d_new= 0;
  long long ll_new= 0;
  unsigned long long ull_new= 0;
  long double ld_new= 0;
  std::string str_new;
  std::vector<int> v_new;
  char t[14];
  char buf[10];
  igzbinstream in("tmp.bin");
  (ibinstream&)in
    >> t[0] >> i_new >> t[1] >> c_new >> t[2] >> s_new >> t[3] >> l_new >> t[4] >> ll_new
    >> t[5] >> f_new >> t[6] >> d_new >> t[7] >> ld_new 
    >> t[8] >> ui_new >> t[9] >> uc_new >> t[10] >> us_new >> t[11] >> ul_new >> t[12] >> ull_new
    >> buf >> t[13] >> str_new >> v_new;
  in.close();
    CPPUNIT_ASSERT_EQUAL(i, i_new);
    CPPUNIT_ASSERT_EQUAL(c, c_new);
    CPPUNIT_ASSERT_EQUAL(s, s_new);
    CPPUNIT_ASSERT_EQUAL(l, l_new);
    CPPUNIT_ASSERT_EQUAL(ll, ll_new);
    CPPUNIT_ASSERT_EQUAL(ui, ui_new);
    CPPUNIT_ASSERT_EQUAL(uc, uc_new);
    CPPUNIT_ASSERT_EQUAL(us, us_new);
    CPPUNIT_ASSERT_EQUAL(ul, ul_new);
    CPPUNIT_ASSERT_EQUAL(ull, ull_new);
    CPPUNIT_ASSERT_EQUAL(f, f_new);
    CPPUNIT_ASSERT_EQUAL(d, d_new);
    CPPUNIT_ASSERT_EQUAL(ld, ld_new);
    CPPUNIT_ASSERT_EQUAL(str, str_new);
  for(uint i=0;i<strlen(array);i++) {
      CPPUNIT_ASSERT_EQUAL(buf[i], array[i]);
  }
  for(uint i=0;i<v.size();i++) {
    CPPUNIT_ASSERT_EQUAL(v[i], v_new[i]);
  }
  for(int i=0;i<14;i++) {
      CPPUNIT_ASSERT_EQUAL(t[i], 'x');
  }
}

#endif
