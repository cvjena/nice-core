/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libbasicvector - A simple vector library
 * See file License for license information.
 */

#ifdef NICE_USELIB_CPPUNIT
#include "TestEVector.h"
#include <string>
#include <iostream>
#include <core/basics/gzbinstream.h>
#include <stdexcept>
#include <core/basics/cppunitex.h>
#include "core/vector/VectorT.h"
#include "core/vector/CheckedVectorT.h"
#include "core/vector/Distance.h"
#include "core/vector/Algorithms.h"

CPPUNIT_TEST_SUITE_REGISTRATION( TestEVector );

using namespace NICE;
using namespace std;

void TestEVector::setUp() {
}

void TestEVector::tearDown() {
}

void TestEVector::testAccess() {
  VectorT<double> v(10, 5.4);
  CPPUNIT_ASSERT_EQUAL(5.4, v[0]);
  CPPUNIT_ASSERT_EQUAL(5.4, v[9]);
}

void TestEVector::testConst() {
  const char* data = "abcde";
  VectorT<char> v(data, 5u);
  CPPUNIT_ASSERT_EQUAL(5u, (uint)v.size());
  for (unsigned int i = 0; i < v.size(); i++) {
    CPPUNIT_ASSERT_EQUAL(data[i], v[i]);
  }
}

void TestEVector::testCopy() {
  const char data[] = "fkepw.xja8";
  unsigned int size = strlen(data);
  VectorT<char> v(data, size);
  VectorT<char> w(v);
  VectorT<char> x(w);
  CPPUNIT_ASSERT_EQUAL(size, (uint)v.size());
  CPPUNIT_ASSERT_EQUAL(size, (uint)w.size());
  CPPUNIT_ASSERT_EQUAL(size, (uint)x.size());
  for (unsigned int i = 0; i < size; i++) {
    CPPUNIT_ASSERT_EQUAL(data[i], v[i]);
    CPPUNIT_ASSERT_EQUAL(data[i], w[i]);
    CPPUNIT_ASSERT_EQUAL(data[i], x[i]);
  }
}

void TestEVector::testRangeAccess() {
    const char data[] = "Hello World";
    const char word1[] = "Hello";
    const char word2[] = "World";
    const char word1sub[] = "Hallo";
    const char word2sub[] = "Welt!";
    unsigned int size = strlen(data)+1;
    VectorT<char> v(data, size);
    VectorT<char> w = v.getRange ( 0, 4 );
    CPPUNIT_ASSERT_EQUAL ( w.size(), strlen(word1) );
    for ( unsigned int i = 0 ; i < w.size() ; i++ )
	CPPUNIT_ASSERT ( word1[i] == w[i] );
    VectorT<char> u = v.getRangeRef ( 6, 10 );
    for ( unsigned int i = 0 ; i < u.size() ; i++ )
	CPPUNIT_ASSERT ( word2[i] == u[i] );

    for ( unsigned int i = 0 ; i < w.size() ; i++ )
	w[i] = word1sub[i];
    
    CPPUNIT_ASSERT_EQUAL ( 0, strcmp( v.getDataPointer(), data ) );
    
    for ( unsigned int i = 0 ; i < u.size() ; i++ )
	u[i] = word2sub[i];
    
    CPPUNIT_ASSERT ( strcmp( v.getDataPointer(), data ) );
    CPPUNIT_ASSERT_EQUAL ( 0, strcmp( v.getDataPointer(), "Hello Welt!" ) );

    unsigned int oldsize = w.size();
    w.append ( u );
    CPPUNIT_ASSERT_EQUAL( oldsize + u.size(), w.size() );
}

void TestEVector::testExternal() {
  char data[] = "1234567890";
  unsigned int size = strlen(data);
  VectorT<char> v(data, size, VectorT<char>::external);
  data[5] = 'A';
  v[8] = 'B';
  CPPUNIT_ASSERT_EQUAL(size, (uint)v.size());
  for (unsigned int i = 0; i < size; i++) {
    CPPUNIT_ASSERT_EQUAL(data[i], v[i]);
  }
  CPPUNIT_ASSERT_EQUAL('A', v[5]);
  CPPUNIT_ASSERT_EQUAL('B', data[8]);
}

void TestEVector::testAssignment() {
  const char data[] = "fkepw.xja8";
  int size = strlen(data);
  VectorT<char> a(data, size);
  std::auto_ptr<const VectorT<char> >
    b(VectorT<char>::createConst(data, size));
  VectorT<char> t(a);
  VectorT<char> u;
  u = a;
  VectorT<char> v = a;
  VectorT<char> w(*b);
  VectorT<char> x;
  x = *b;
  VectorT<char> y = *b;
  for (int i = 0; i < size; i++) {
    CPPUNIT_ASSERT_EQUAL(data[i], t[i]);
    CPPUNIT_ASSERT_EQUAL(data[i], u[i]);
    CPPUNIT_ASSERT_EQUAL(data[i], v[i]);
    CPPUNIT_ASSERT_EQUAL(data[i], w[i]);
    CPPUNIT_ASSERT_EQUAL(data[i], x[i]);
    CPPUNIT_ASSERT_EQUAL(data[i], y[i]);
  }
  u = 'o';
  for (int i = 0; i < size; i++) {
    CPPUNIT_ASSERT_EQUAL('o', u[i]);
  }
  VectorT<int> ev[3];
  ev[0]=VectorT<int>(2);
  ev[1]=VectorT<int>(3);
  ev[2]=VectorT<int>(4);
  VectorT<VectorT<int> > eev(ev,3);
  VectorT<VectorT<int> > copy_eev = eev;
  for (unsigned int i = 0; i < 3; i++) {
    CPPUNIT_ASSERT_EQUAL(eev[i], copy_eev[i]);
  }
}

void TestEVector::testArithmetics() {
  VectorT<float> v(20);
  for (unsigned int i = 0; i < 20; i++) {
    v[i] = 100.0 - float(i);
  }

  VectorT<float> w(v);
  w *= 3.0;
  w -= v;
  for (unsigned int i = 0; i < v.size(); i++) {
    CPPUNIT_ASSERT_EQUAL(2.0f * v[i], w[i]);
  }

  VectorT<float> a(3);
  VectorT<float> b(3);
  VectorT<float> c(3);
  for (unsigned int i = 0; i < a.size(); i++) {
    a[i] = float(i);
    b[i] = float(i + 1);
    c[i] = float(i + 2);
  }
  VectorT<float> m(3);
  m = 0.0f;
  m += a;
  m += b;
  m += c;
  m /= 3.0f;

  for (unsigned int i = 0; i < m.size(); i++) {
    CPPUNIT_ASSERT_EQUAL(float(i + 1), m[i]);
  }
}

void TestEVector::testIO() {
  VectorT<float> v(20);
  for (unsigned int i = 0; i < 20; i++) {
    v[i] = 100.0 - float(i);
  }
  std::stringstream st;
  st << v;

  std::stringstream in2(st.str());
  while (!in2.eof()) {
    std::string s;
    in2 >> s;
  }

  std::stringstream in(st.str());
  VectorT<float> w(in);
  CPPUNIT_ASSERT_EQUAL(20u, (uint)w.size());
  for (unsigned int i = 0; i < 20; i++) {
    CPPUNIT_ASSERT_EQUAL(100.0f - float(i), w[i]);
  }

  { // scope block
    std::stringstream in(st.str());
    VectorT<float> w;
    in >> w;
    CPPUNIT_ASSERT_EQUAL(20u, (uint)w.size());
    for (unsigned int i = 0; i < 20; i++) {
      CPPUNIT_ASSERT_EQUAL(100.0f - float(i), w[i]);
    }
  }

  {
    char filename[] = "evectortest.bin.gz";

    NICE::ogzbinstream out(filename);
    out << v << v;
    out.close();

    NICE::igzbinstream in(filename);
    VectorT<float> w;
    in >> w;
    VectorT<float> w2;
    in >> w2;
    in.close();

    CPPUNIT_ASSERT_EQUAL(20u, (uint)w.size());
    CPPUNIT_ASSERT_EQUAL(20u, (uint)w2.size());
    for (unsigned int i = 0; i < 20; i++) {
      CPPUNIT_ASSERT_EQUAL(100.0f - float(i), w[i]);
      CPPUNIT_ASSERT_EQUAL(100.0f - float(i), w2[i]);
    }

    remove(filename);
  }
}

void TestEVector::testRangeChecks() {
  CheckedVectorT<double> v(10, 4.5);
  CPPUNIT_ASSERT_EQUAL(4.5, v[0]);
  CPPUNIT_ASSERT_EQUAL(4.5, v[9]);
  CPPUNIT_ASSERT_THROW(v[-1], std::out_of_range);
  CPPUNIT_ASSERT_THROW(v[10], std::out_of_range);
  VectorT<double> z(10, 4.5);
  CPPUNIT_ASSERT_EQUAL(4.5, z(0));
  CPPUNIT_ASSERT_EQUAL(4.5, z(9));
  CPPUNIT_ASSERT_THROW(z(-1), std::out_of_range);
  CPPUNIT_ASSERT_THROW(z(10), std::out_of_range);

  v[9] = 5.1;
  CheckedVectorT<double> w(v.getDataPointer(), v.size());
  CPPUNIT_ASSERT_EQUAL(4.5, w[0]);
  CPPUNIT_ASSERT_EQUAL(5.1, w[9]);
  CPPUNIT_ASSERT_THROW(w[-1], std::out_of_range);
  CPPUNIT_ASSERT_THROW(w[10], std::out_of_range);
}

void TestEVector::testScalarProduct() {
  VectorT<double> v(10, 4.5);
  VectorT<double> w(10, 7.3);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(4.5 * 7.3 * 10.0, v.scalarProduct(w), 1e-6);
}

void TestEVector::testEqual() {
  VectorT<double> v(10, 4.5);
  VectorT<double> w(10, 4.5);
  VectorT<double> x(10, 4.5);
  VectorT<double> y(9, 4.5);
  VectorT<double> z;
  x[9]=4.7;
  CPPUNIT_ASSERT(z==z);
  CPPUNIT_ASSERT(!(z!=z));
  CPPUNIT_ASSERT(v==w);
  CPPUNIT_ASSERT(!(v!=w));
  CPPUNIT_ASSERT(v!=x);
  CPPUNIT_ASSERT(!(v==x));
  CPPUNIT_ASSERT_THROW(x==y, std::invalid_argument);
  CPPUNIT_ASSERT_THROW(x!=y, std::invalid_argument);
}

void TestEVector::testDistance() {
  {
    VectorT<float> v(9, 3);
    VectorT<float> w(9, 4);
    EuclidianDistance<float> edist;
    float dist=edist(v,w);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(3.0, dist,1e-6);
  }
  {
    VectorT<float> v(9, 3);
    VectorT<float> w(9, 4);
    ManhattanDistance<float> edist;
    float dist=edist(v,w);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(9.0, dist,1e-6);
  }
  {
    VectorT<float> v(9, 3);
    VectorT<float> w(9, 4);
    MaximumDistance<float> edist;
    float dist=edist(v,w);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, dist,1e-6);
  }
  {
    VectorT<float> v(2, 0.);
    VectorT<float> w(2, 0.);
    v[0]=(-90.)*(M_PI/180.);
    v[1]=(0.)*(M_PI/180.);
    w[0]=(90.)*(M_PI/180.);
    w[1]=(0.)*(M_PI/180.);
    float z=(180.)*(M_PI/180.);
    SphericalDistance<float> edist;
    float dist=edist(v,w);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(z, dist,1e-3);
  }
  {
    // Bronstein example
    VectorT<float> v(2, 0.);
    VectorT<float> w(2, 0.);
    v[0]=(13+46./60.)*(M_PI/180.);
    v[1]=(51+16./60.)*(M_PI/180.);
    w[0]=(76+55./60.)*(M_PI/180.);
    w[1]=(43+18./60.)*(M_PI/180.);
    float z=(42+12.8/60.)*(M_PI/180.);
    SphericalDistance<float> edist;
    float dist=edist(v,w);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(z, dist,1e-3);
  }
  {
    VectorT<float> v(9, 3);
    VectorT<float> w(9, 4);
    SinDistance<float> edist;
    float dist=edist(v,w);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, dist,1e-6);
  }
  {
    VectorT<float> v(4, 3);
    VectorT<float> w(4, 3);
    w(1)=-w(1);
    w(2)=-w(2);
    SinDistance<float> edist;
    float dist=edist(v,w);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, dist,1e-6);
  }
//   {
//     VectorT<float> v(9, 3);
//     VectorT<float> w(9, 4);
//     Chi2Distance<float> edist;
//     float dist=edist(v,w);
//     CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, dist,1e-6);
//   }
  {
    VectorT<float> v(9, 3);
    VectorT<float> w(9, 4);
    KLDistance<float> edist;
    float dist=edist(v,w);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(-7.76742, dist,1e-5);
  }
  {
    VectorT<double> v(9, 3);
    VectorT<double> w(9, 4);
    EuclidianDistance<double> edist;
    double dist=edist(v,w);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(3.0, dist,1e-6);
  }
}

void TestEVector::testRandUni()
{
  {
    VectorT<int> unirand = VectorT<int>::UniformRandom(10,0,10,0);
    int m=mean(unirand);
      CPPUNIT_ASSERT_EQUAL(5, m);
  }
  {
    VectorT<float> unirand = VectorT<float>::UniformRandom(1000,0,10,0);
    float m=mean(unirand);
      CPPUNIT_ASSERT_DOUBLES_EQUAL(5.0, m,1e-1);

  }
}

void TestEVector::testStatistics() {
        int array[]= {0,2,3,4,6};
        VectorT<int> v(array,5);
      CPPUNIT_ASSERT_EQUAL(3, v.Mean());
      CPPUNIT_ASSERT_EQUAL(2, v.StdDev());
}

void TestEVector::testRandGauss()
{
  {
    VectorT<float> gaussrand = VectorT<float>::GaussRandom(100000,0,10,0);
    float m=mean(gaussrand);
        float v=gaussrand.StdDev();
      CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, m,1e-1);
      CPPUNIT_ASSERT_DOUBLES_EQUAL(10.0, v,1e-1);
  }
  {
    VectorT<int> gaussrand = VectorT<int>::GaussRandom(10000,0,10,0);
    int m=gaussrand.Mean();
        int v=gaussrand.StdDev();
      CPPUNIT_ASSERT_EQUAL(0, m);
      CPPUNIT_ASSERT_EQUAL(10, v);
  }
}
void TestEVector::testFlip()
{
  {
        int array[]= {1,2,3,4,5};
        int rarray[]= {5,4,3,2,1};
        VectorT<int> v(array,4);
        v.flip();
      CPPUNIT_ASSERT_EQUAL(3,v[1]);
        VectorT<int> v2(array,5);
        VectorT<int> v3(rarray,5);
        v2.flip();
      CPPUNIT_ASSERT_EQUAL(v3,v2);
  }
  {
        float array[]= {1.,2.,3.,4.,5.};
        float rarray[]= {5.,4.,3.,2.,1.};
        VectorT<float> v(array,4);
        v.flip();
      CPPUNIT_ASSERT_DOUBLES_EQUAL(3.,v[1],1e-6);
        VectorT<float> v2(array,5);
        VectorT<float> v3(rarray,5);
        v2.flip();
      CPPUNIT_ASSERT_EQUAL(v3,v2);
  }
}

void TestEVector::testSort()
{
  {
        int array[]= {1,3,2,5,1};
        int rarray[]= {1,1,2,3,5};
        int r2array[]= {5,3,2,1,1};
        VectorT<int> v(array,5);
        v.sortAscend();
        VectorT<int> vr(rarray,5);
      CPPUNIT_ASSERT_EQUAL(vr,v);
        VectorT<int> vr2(r2array,5);
        v.sortDescend();
      CPPUNIT_ASSERT_EQUAL(vr2,v);
  }
  {
        float array[]= {1.,3.,2.,5.,1.};
        float rarray[]= {1.,1.,2.,3.,5.};
        VectorT<float> v(array,5);
        VectorT<float> vr(rarray,5);
        v.sortAscend();
      CPPUNIT_ASSERT_EQUAL(vr,v);
        v.sortDescend();
        vr.sortDescend();
      CPPUNIT_ASSERT_EQUAL(vr,v);
      CPPUNIT_ASSERT_DOUBLES_EQUAL(5.,v[0],1e-6);
  }
}

void TestEVector::testGauss()
{
/*    VectorT<float> *x=createGaussFunc<float>(1.0f);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, x->Sum(),1e-6);
    x=createGaussFunc(1.0,x);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, x->Sum(),1e-1);
    x=createGaussFunc(0.0,x);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, x->Sum(),1e-1);
 */
}
void TestEVector::testNorm() {
    {
        float array[]= {0,2,3,4,6};
        VectorT<float> v(array,5);
      CPPUNIT_ASSERT_DOUBLES_EQUAL(6, v.normInf(),1e-6);
      CPPUNIT_ASSERT_DOUBLES_EQUAL(15, v.normL1(),1e-6);
      CPPUNIT_ASSERT_DOUBLES_EQUAL(8.06225774829854965236, v.normL2(),1e-6);
    }
    {
        unsigned char array[]= {0,2,3,4,6};
        VectorT<unsigned char> v(array,5);
      CPPUNIT_ASSERT_EQUAL(static_cast<unsigned char>(6), v.normInf());
      CPPUNIT_ASSERT_EQUAL(static_cast<unsigned char>(15), v.normL1());
      CPPUNIT_ASSERT_EQUAL(static_cast<unsigned char>(8), v.normL2());
    }
    
    //new test to verify the correctness of the infinity norm (which is not computed properly using IPP)
    {
      float array[]= {0,-2,3,4,-6};
      VectorT<float> v(array,5);
      CPPUNIT_ASSERT_DOUBLES_EQUAL( 6, v.normInf(), 1e-6 );
    }
    {
      float array[]= {0,-2,-3,-4,-6};
       VectorT<float> v(array,5);
      CPPUNIT_ASSERT_DOUBLES_EQUAL( 6, v.normInf(), 1e-6 );
    }
    {
      float array[]= {0,-2,-3,-4,6};
       VectorT<float> v(array,5);
      CPPUNIT_ASSERT_DOUBLES_EQUAL( 6, v.normInf(), 1e-6 );
    }
    {
      uint array[]= {0,2,3,4,6};
       VectorT<uint> v(array,5);
      CPPUNIT_ASSERT_DOUBLES_EQUAL( 6, v.normInf(), 1e-6 );
    }    
    

}

void TestEVector::testAbs() {
    {
        float array[]= {0,-2,3,-4,-6};
        VectorT<float> v(array,5);
        {
            VectorT<float> z(v.abs());
          CPPUNIT_ASSERT_DOUBLES_EQUAL(0.f,z(0),1e-6);
          CPPUNIT_ASSERT_DOUBLES_EQUAL(2.f,z(1),1e-6);
          CPPUNIT_ASSERT_DOUBLES_EQUAL(3.f,z(2),1e-6);
          CPPUNIT_ASSERT_DOUBLES_EQUAL(4.f,z(3),1e-6);
          CPPUNIT_ASSERT_DOUBLES_EQUAL(6.f,z(4),1e-6);
        }
        v.absInplace();
      CPPUNIT_ASSERT_DOUBLES_EQUAL(0.f,v(0),1e-6);
      CPPUNIT_ASSERT_DOUBLES_EQUAL(2.f,v(1),1e-6);
      CPPUNIT_ASSERT_DOUBLES_EQUAL(3.f,v(2),1e-6);
      CPPUNIT_ASSERT_DOUBLES_EQUAL(4.f,v(3),1e-6);
      CPPUNIT_ASSERT_DOUBLES_EQUAL(6.f,v(4),1e-6);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(3.f,v.Median(),1e-6);
    }
}

void TestEVector::testRowMultiply() {
  RowMatrixT<double> a(2,3);
  RowMatrixT<double> b(3,2);
  double buffer[]={3.0,10.0,.5};
  VectorT<double> d(buffer,3);
  for (unsigned int i = 0; i < a.rows(); i++) {
    for (unsigned int j = 0; j < a.cols(); j++) {
      a(i, j) = 3*i+j;
    }
  }
  for (unsigned int i = 0; i < b.rows(); i++) {
    for (unsigned int j = 0; j < b.cols(); j++) {
      b(i, j) = (int)i - (int)j + 0.5;
    }
  }
  {
   VectorT<double> m;
   CPPUNIT_ASSERT_THROW(m.multiply(d, a), Exception);
  }
  {
   VectorT<double> m;
   CPPUNIT_ASSERT_THROW(m.multiply(a, d, true), Exception);
  }
  {
   VectorT<double> m;
   CPPUNIT_ASSERT_THROW(m.multiply(b, d), Exception);
  }
  {
   VectorT<double> m(2);
   CPPUNIT_ASSERT_NO_THROW(m.multiply(a, d));
  }
  {
   VectorT<double> m;
   CPPUNIT_ASSERT_NO_THROW(m.multiply(d, b));
  }
  {
   VectorT<double> m(2);
   CPPUNIT_ASSERT_NO_THROW(m.multiply(d, a, true));
  }
  {
   VectorT<double> m(2);
   CPPUNIT_ASSERT_NO_THROW(m.multiply(d, b));
  }
  VectorT<double> m;
  m.multiply(a, d);
  CPPUNIT_ASSERT_EQUAL(2u, (uint)m.size());
  CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(11.0, m(0), 1E-20);
  CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(51.5, m(1), 1E-20);

    float array[]= {0.4302,0.1556,0.4608,0.2974,0.4001,0.4199,
                  0.8903,0.1911,0.4574,0.0492,0.1988,0.7537,
                  0.7349,0.4225,0.4507,0.6932,0.6252,0.7939,
                  0.6873,0.8560,0.4122,0.6501,0.7334,0.9200,
                  0.3461,0.4902,0.9016,0.9830,0.3759,0.8447,
                  0.1660,0.8159,0.0056,0.5527,0.0099,0.3678};
   float buffer2[]= {0.6208,0.7313,0.1939,0.9048,0.5692,0.6318};
   VectorT<float> e(buffer2,6);
   RowMatrixT<float> c(array,6,6);
  {
      VectorT<float> m;
      m.multiply(c, e);
      double checksum=0;
      for(int i=0;i<6;i++) {
            checksum += m(i);
            checksum*=3.0;
      }
      std::stringstream inout; inout << checksum << endl << c << "*" << e << "=" << m;
      CPPUNIT_COND_STREAM(abs(checksum-2104.77)/2104.77>1e-6, inout.str());

  }
}

void TestEVector::testMultiply() {
  MatrixT<double> a(2,3);
  MatrixT<double> b(3,2);
  double buffer[]={3.0,10.0,.5};
  VectorT<double> d(buffer,3);
  for (unsigned int i = 0; i < a.rows(); i++) {
    for (unsigned int j = 0; j < a.cols(); j++) {
      a(i, j) = 3*i+j;
    }
  }
  for (unsigned int i = 0; i < b.rows(); i++) {
    for (unsigned int j = 0; j < b.cols(); j++) {
      b(i, j) = (int)i - (int)j + 0.5;
    }
  }
  {
   VectorT<double> m;
   CPPUNIT_ASSERT_THROW(m.multiply(d, a), Exception);
  }
  {
   VectorT<double> m;
   CPPUNIT_ASSERT_THROW(m.multiply(a, d, true), Exception);
  }
  {
   VectorT<double> m;
   CPPUNIT_ASSERT_THROW(m.multiply(b, d), Exception);
  }
  {
   VectorT<double> m(2);
   CPPUNIT_ASSERT_NO_THROW(m.multiply(a, d));
  }
  {
   VectorT<double> m;
   CPPUNIT_ASSERT_NO_THROW(m.multiply(d, b));
  }
  {
   VectorT<double> m(2);
   CPPUNIT_ASSERT_NO_THROW(m.multiply(d, a, true));
  }
  {
   VectorT<double> m(2);
   CPPUNIT_ASSERT_NO_THROW(m.multiply(d, b));
  }
  VectorT<double> m;
  m.multiply(a, d);
  CPPUNIT_ASSERT_EQUAL(2u, (uint)m.size());
  CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(11.0, m(0), 1E-20);
  CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(51.5, m(1), 1E-20);

    float array[]= {0.4302,0.1556,0.4608,0.2974,0.4001,0.4199,
                  0.8903,0.1911,0.4574,0.0492,0.1988,0.7537,
                  0.7349,0.4225,0.4507,0.6932,0.6252,0.7939,
                  0.6873,0.8560,0.4122,0.6501,0.7334,0.9200,
                  0.3461,0.4902,0.9016,0.9830,0.3759,0.8447,
                  0.1660,0.8159,0.0056,0.5527,0.0099,0.3678};
   float buffer2[]= {0.6208,0.7313,0.1939,0.9048,0.5692,0.6318};
   VectorT<float> e(buffer2,6);
   MatrixT<float> c(array,6,6);
  {
      VectorT<float> m;
      m.multiply(c, e);
      double checksum=0;
      for(int i=0;i<6;i++) {
            checksum += m(i);
            checksum*=3.0;
      }
      std::stringstream inout; inout << checksum << endl << c << "*" << e << "=" << m;
      CPPUNIT_COND_STREAM(abs(checksum-2104.77)/2104.77>1e-6, inout.str());

  }
}





void TestEVector::testShift() {

    IntVector vec(6);
    for(Ipp32u i=0; i<vec.size(); ++i)
        vec[i] = i;

    IntVector lShift0 = vec.LShiftCircular(0);
    CPPUNIT_ASSERT_EQUAL(lShift0[0], 0);
    CPPUNIT_ASSERT_EQUAL(lShift0[1], 1);
    CPPUNIT_ASSERT_EQUAL(lShift0[2], 2);
    CPPUNIT_ASSERT_EQUAL(lShift0[3], 3);
    CPPUNIT_ASSERT_EQUAL(lShift0[4], 4);
    CPPUNIT_ASSERT_EQUAL(lShift0[5], 5);

    IntVector lShift2 = vec.LShiftCircular(2);
    CPPUNIT_ASSERT_EQUAL(lShift2[0], 2);
    CPPUNIT_ASSERT_EQUAL(lShift2[1], 3);
    CPPUNIT_ASSERT_EQUAL(lShift2[2], 4);
    CPPUNIT_ASSERT_EQUAL(lShift2[3], 5);
    CPPUNIT_ASSERT_EQUAL(lShift2[4], 0);
    CPPUNIT_ASSERT_EQUAL(lShift2[5], 1);

    IntVector lShift6 = vec.LShiftCircular(6);
    CPPUNIT_ASSERT_EQUAL(lShift6[0], 0);
    CPPUNIT_ASSERT_EQUAL(lShift6[1], 1);
    CPPUNIT_ASSERT_EQUAL(lShift6[2], 2);
    CPPUNIT_ASSERT_EQUAL(lShift6[3], 3);
    CPPUNIT_ASSERT_EQUAL(lShift6[4], 4);
    CPPUNIT_ASSERT_EQUAL(lShift6[5], 5);

    IntVector rShift0 = vec.RShiftCircular(0);
    CPPUNIT_ASSERT_EQUAL(rShift0[0], 0);
    CPPUNIT_ASSERT_EQUAL(rShift0[1], 1);
    CPPUNIT_ASSERT_EQUAL(rShift0[2], 2);
    CPPUNIT_ASSERT_EQUAL(rShift0[3], 3);
    CPPUNIT_ASSERT_EQUAL(rShift0[4], 4);
    CPPUNIT_ASSERT_EQUAL(rShift0[5], 5);

    IntVector rShift2 = vec.RShiftCircular(2);
    CPPUNIT_ASSERT_EQUAL(rShift2[0], 4);
    CPPUNIT_ASSERT_EQUAL(rShift2[1], 5);
    CPPUNIT_ASSERT_EQUAL(rShift2[2], 0);
    CPPUNIT_ASSERT_EQUAL(rShift2[3], 1);
    CPPUNIT_ASSERT_EQUAL(rShift2[4], 2);
    CPPUNIT_ASSERT_EQUAL(rShift2[5], 3);

    IntVector rShift6 = vec.RShiftCircular(6);
    CPPUNIT_ASSERT_EQUAL(rShift6[0], 0);
    CPPUNIT_ASSERT_EQUAL(rShift6[1], 1);
    CPPUNIT_ASSERT_EQUAL(rShift6[2], 2);
    CPPUNIT_ASSERT_EQUAL(rShift6[3], 3);
    CPPUNIT_ASSERT_EQUAL(rShift6[4], 4);
    CPPUNIT_ASSERT_EQUAL(rShift6[5], 5);

    IntVector lShift0IP(vec);
    lShift0IP.LShiftCircularInplace(0);
    for(Ipp32u i=0; i<vec.size(); ++i)
        CPPUNIT_ASSERT_EQUAL(lShift0[i], lShift0IP[i]);

    IntVector lShift2IP(vec);
    lShift2IP.LShiftCircularInplace(2);
    for(Ipp32u i=0; i<vec.size(); ++i)
        CPPUNIT_ASSERT_EQUAL(lShift2[i], lShift2IP[i]);

    IntVector lShift6IP(vec);
    lShift6IP.LShiftCircularInplace(6);
    for(Ipp32u i=0; i<vec.size(); ++i)
        CPPUNIT_ASSERT_EQUAL(lShift6[i], lShift6IP[i]);

    IntVector rShift0IP(vec);
    rShift0IP.RShiftCircularInplace(0);
    for(Ipp32u i=0; i<vec.size(); ++i)
        CPPUNIT_ASSERT_EQUAL(rShift0[i], rShift0IP[i]);

    IntVector rShift2IP(vec);
    rShift2IP.RShiftCircularInplace(2);
    for(Ipp32u i=0; i<vec.size(); ++i)
        CPPUNIT_ASSERT_EQUAL(rShift2[i], rShift2IP[i]);

    IntVector rShift6IP(vec);
    rShift6IP.RShiftCircularInplace(6);
    for(Ipp32u i=0; i<vec.size(); ++i)
        CPPUNIT_ASSERT_EQUAL(rShift6[i], rShift6IP[i]);

}

#endif
