/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libiocompression - An iocompression/template for new NICE libraries
 * See file License for license information.
 */
#include "Testgzbinstream.h"
#include <string>
#include <vector>
#include <exception>

using namespace NICE;

enum ENUM { ONE=1, TWO=2, FIVE=5 };

CPPUNIT_TEST_SUITE_REGISTRATION( Testgzbinstream );

void Testgzbinstream::setUp() {
}

void Testgzbinstream::tearDown() {
  remove("tmp.bgz");
}

void Testgzbinstream::testConstructor() {
}

void Testgzbinstream::testOperators() {
#ifdef NICE_USELIB_ZLIB
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
    ENUM enu=FIVE;
    std::vector<double> vd(10);
    for(uint i=0;i<vd.size();i++)
        vd[i]=i;
    std::vector<std::vector<std::string> > vvs(3);
  for(uint i=0;i<vvs.size();i++) {
        vvs[i].resize(3);
      for(int j=0;j<3;j++) {
            std::string x="test-";
          vvs[i][j]= x + (char)(i+'0')+(char)(j+'0');
        }
  }
  std::string str="string";
  ogzbinstream file("tmp.bgz");
  char array[]="array";
  file << 'x' << i << 'x' << c << 'x' << s << 'x' << l << 'x' << ll 
       << 'x' << f << 'x' << d << 'x' << ld
       << 'x' << ui << 'x' << uc << 'x' << us << 'x' << ul << 'x' << ull
     << "array" << 'x' << str << 'x' << vd << 'x' << vvs << 'x'
         << (char)enu << 'x';
     ;
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
  char t[18];
  char buf[10];
    std::vector<double> vd_new;
    std::vector<std::vector<std::string> > vvs_new;
    ENUM enu_new;
    unsigned char enu_char;
  igzbinstream in("tmp.bgz");
  in  >> t[0] >> i_new >> t[1] >> c_new >> t[2] >> s_new >> t[3] >> l_new >> t[4] >> ll_new
      >> t[5] >> f_new >> t[6] >> d_new >> t[7] >> ld_new 
      >> t[8] >> ui_new >> t[9] >> uc_new >> t[10] >> us_new >> t[11] >> ul_new >> t[12] >> ull_new
    >> buf >> t[13] >> str_new >> t[14] >> vd_new >> t[15] >> vvs_new >>t[16] >> enu_char >> t[17];
     ;
    enu_new=(ENUM)enu_char;
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
  for(uint i=0;i<vd.size();i++) {
      CPPUNIT_ASSERT_EQUAL(vd[i], vd_new[i]);
  }
  for(uint i=0;i<vvs.size();i++) {
      for(uint j=0;j<vvs[i].size();j++) {
          CPPUNIT_ASSERT_EQUAL(vvs[i][j], vvs_new[i][j]);
        }
  }
    CPPUNIT_ASSERT_EQUAL(enu, enu_new);
  for(int i=0;i<18;i++) {
      CPPUNIT_ASSERT_EQUAL(t[i], 'x');
  }
#endif
}
