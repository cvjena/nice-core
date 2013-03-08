/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libiocompression - An iocompression/template for new NICE libraries
 * See file License for license information.
 */

#ifdef NICE_USELIB_CPPUNIT
#include <stdlib.h>
#include <string>
#include <exception>
#include <cstddef>

#include "TestStreamable.h"

using namespace NICE;

CPPUNIT_TEST_SUITE_REGISTRATION( TestStreamable );

class StreamableClass : public NICE::Streamable, public NICE::BinStreamable {
 public:
   NICE::VectorT<double> evdouble;
   NICE::VectorT<long> evlong;
#ifdef NICE_USELIB_LINAL 
   LinAl::VectorCC<float> vcfloat;
   LinAl::MatrixCF<float> mcfloat;
#endif
   
  StreamableClass(){}
  StreamableClass(NICE::VectorT<double> &ed, NICE::VectorT<long> &el
#ifdef NICE_USELIB_LINAL 
   ,const LinAl::VectorCC<float> &vf, const LinAl::MatrixCF<float> &mf
#endif
      );
  virtual void read(std::istream& strm);
  virtual void write(std::ostream& strm) const;

  virtual void read(NICE::ibinstream& strm);
  virtual void write(NICE::obinstream& strm) const;
};

void TestStreamable::setUp() {
  s=NULL;
  static const int k=10;
  double darray[k];
  long larray[2*k];
  float farray[2*k];
  for(int i=0;i<k;i++) {
    larray[2*i] = i;
    larray[2*i+1] = rand();
    farray[2*i] = i;
    farray[2*i+1] = rand();
    darray[i] = rand(); 
  }
  VectorT<double> ed(darray,k);
  VectorT<long> el(larray,2*k);
  
#ifdef NICE_USELIB_LINAL 
  LinAl::VectorCC<float> vf(farray,2*k);
  LinAl::MatrixCF<float> mf=vf*vf.transpose();
#endif
  s = new StreamableClass(ed,el
#ifdef NICE_USELIB_LINAL 
      ,vf,mf
#endif
      );
}

void TestStreamable::tearDown() {
  if(s!=NULL)
    delete s;
  //system("rm StreamableClass.*");
}

void TestStreamable::testConstructor() {
}

void TestStreamable::testOperators() {
  // Test Assignment Operator
  //CPPUNIT_ASSERT_EQUAL(x, y);
}

void TestStreamable::testASCII() {
  s->writeToFile("StreamableClass.txt");
  StreamableClass s_new;
  s_new.readFromFile("StreamableClass.txt");
  VectorT<double> evdiff=s->evdouble;
  evdiff-=s_new.evdouble;
  CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, evdiff.scalarProduct(evdiff), 1E-10);
#ifdef NICE_USELIB_LINAL 
  CPPUNIT_ASSERT_EQUAL(s->vcfloat, s_new.vcfloat);
  CPPUNIT_ASSERT_EQUAL(s->mcfloat, s_new.mcfloat);
#endif
  CPPUNIT_ASSERT_EQUAL(s->evlong, s_new.evlong);
  remove("StreamableClass.txt");
}

void TestStreamable::testGZ() {
#ifdef NICE_USELIB_ZLIB
  s->writeToFile("StreamableClass.txt.gz",Streamable::ASCII_GZ);
  StreamableClass s_new;
  s_new.readFromFile("StreamableClass.txt.gz",Streamable::ASCII_GZ);
  VectorT<double> evdiff=s->evdouble;
  evdiff-=s_new.evdouble;
  CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, evdiff.scalarProduct(evdiff), 1E-10);
#ifdef NICE_USELIB_LINAL 
  CPPUNIT_ASSERT_EQUAL(s->vcfloat, s_new.vcfloat);
  CPPUNIT_ASSERT_EQUAL(s->mcfloat, s_new.mcfloat);
#endif
  CPPUNIT_ASSERT_EQUAL(s->evlong, s_new.evlong);
  remove("StreamableClass.txt.gz");
#endif
}

void TestStreamable::testBIN() {
#ifdef NICE_USELIB_ZLIB
  s->writeToBinFile("StreamableClass.bin");
  StreamableClass s_new;
  s_new.readFromBinFile("StreamableClass.bin");
  VectorT<double> evdiff=s->evdouble;
  evdiff-=s_new.evdouble;
  CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, evdiff.scalarProduct(evdiff), 1E-10);
#ifdef NICE_USELIB_LINAL 
  CPPUNIT_ASSERT_EQUAL(s->vcfloat, s_new.vcfloat);
  CPPUNIT_ASSERT_EQUAL(s->mcfloat, s_new.mcfloat);
#endif
  CPPUNIT_ASSERT_EQUAL(s->evlong, s_new.evlong);
  remove("StreamableClass.bin");
#endif
}

void TestStreamable::testGZBIN() {
#ifdef NICE_USELIB_ZLIB
  s->writeToBinFile("StreamableClass.bin.gz",BinStreamable::BIN_GZ);
  StreamableClass s_new;
  s_new.readFromBinFile("StreamableClass.bin.gz",BinStreamable::BIN_GZ);
  VectorT<double> evdiff=s->evdouble;
  evdiff-=s_new.evdouble;
  CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, evdiff.scalarProduct(evdiff), 1E-10);
#ifdef NICE_USELIB_LINAL 
  CPPUNIT_ASSERT_EQUAL(s->vcfloat, s_new.vcfloat);
  CPPUNIT_ASSERT_EQUAL(s->mcfloat, s_new.mcfloat);
#endif
  CPPUNIT_ASSERT_EQUAL(s->evlong, s_new.evlong);
  remove("StreamableClass.bin.gz");
#endif
}

void TestStreamable::testBZ() {
#ifdef NICE_USELIB_BZLIB
  s->writeToFile("StreamableClass.txt.bz2",Streamable::ASCII_BZ);
  StreamableClass s_new;
  s_new.readFromFile("StreamableClass.txt.bz2",Streamable::ASCII_BZ);
  VectorT<double> evdiff=s->evdouble;
  evdiff-=s_new.evdouble;
  CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, evdiff.scalarProduct(evdiff), 1E-10);
#ifdef NICE_USELIB_LINAL 
  CPPUNIT_ASSERT_EQUAL(s->vcfloat, s_new.vcfloat);
  CPPUNIT_ASSERT_EQUAL(s->mcfloat, s_new.mcfloat);
#endif
  CPPUNIT_ASSERT_EQUAL(s->evlong, s_new.evlong);
  remove("StreamableClass.txt.bz2");
#endif
}

StreamableClass::StreamableClass(VectorT<double> &ed, VectorT<long> &el
#ifdef NICE_USELIB_LINAL 
   ,const LinAl::VectorCC<float> &vf, const LinAl::MatrixCF<float> &mf
#endif
      ) 
{
  evdouble=ed;
  evlong=el;
#ifdef NICE_USELIB_LINAL 
  vcfloat=vf;
  mcfloat=mf;
#endif
}

void StreamableClass::read(std::istream& strm)
{
  strm>>evdouble>>evlong;
#ifdef NICE_USELIB_LINAL 
  ReadASCII(vcfloat,strm);
  ReadASCII(mcfloat,strm);
#endif
}

void StreamableClass::write(std::ostream& strm) const
{
  strm.precision(20);
  strm<<evdouble<<std::endl
    <<evlong<<std::endl;
#ifdef NICE_USELIB_LINAL 
  WriteASCII(vcfloat,strm);
  WriteASCII(mcfloat,strm);
#endif
}

void StreamableClass::read(ibinstream& strm)
{
  strm >>evdouble >>evlong 
#ifdef NICE_USELIB_LINAL 
    >>vcfloat >>mcfloat 
#endif
    ;
}

void StreamableClass::write(obinstream& strm) const
{
  strm <<evdouble <<evlong 
#ifdef NICE_USELIB_LINAL 
    <<vcfloat <<mcfloat 
#endif
    ;
}

#endif
