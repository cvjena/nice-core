/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libbasicvector - A simple vector library
 * See file License for license information.
 */

#ifdef NICE_USELIB_CPPUNIT
#include "TestEMatrix.h"
#include <string>
#include <iostream>
#include <stdexcept>
#include <core/basics/cppunitex.h>
#include "core/vector/MatrixT.h"
#include "core/vector/CheckedVectorT.h"
#include "core/vector/CheckedMatrixT.h"
#include "core/vector/Eigen.h"
#include "core/vector/Algorithms.h"
#ifdef NICE_USELIB_LINAL
#include "LinAl/eigen.h"
#endif

CPPUNIT_TEST_SUITE_REGISTRATION( TestEMatrix );

using namespace NICE;
using namespace std;

void TestEMatrix::setUp() {
}

void TestEMatrix::tearDown() {
}

void TestEMatrix::testAccess() {
  MatrixT<double> m(10, 7, 5.4);
  CPPUNIT_ASSERT_EQUAL(5.4, m(0, 3));
  CPPUNIT_ASSERT_EQUAL(5.4, m(9, 6));
}

void TestEMatrix::testConst() {
  const char* data = "abcdef";
  MatrixT<char> v(data, 2, 3);
  CPPUNIT_ASSERT_EQUAL(2u, (uint)v.rows());
  CPPUNIT_ASSERT_EQUAL(3u, (uint)v.cols());
  for (unsigned int i = 0; i < v.rows(); i++) {
    for (unsigned int j = 0; j < v.cols(); j++) {
      // column major
      CPPUNIT_ASSERT_EQUAL(data[j*2+i], v(i, j));
//      // row major
//      CPPUNIT_ASSERT_EQUAL(data[i*3+j], v(i, j));
    }
  }
}

void TestEMatrix::testCopy() {
  const char data[] = "fkepw.xja8";
  unsigned int size = strlen(data);
  unsigned int rows = size / 2;
  unsigned int cols = 2;
  MatrixT<char> v(data, rows, cols);
  MatrixT<char> w(v);
  MatrixT<char> x(w);
  CPPUNIT_ASSERT_EQUAL(rows, (uint)v.rows());
  CPPUNIT_ASSERT_EQUAL(cols, (uint)v.cols());
  CPPUNIT_ASSERT_EQUAL(rows, (uint)w.rows());
  CPPUNIT_ASSERT_EQUAL(cols, (uint)w.cols());
  CPPUNIT_ASSERT_EQUAL(rows, (uint)x.rows());
  CPPUNIT_ASSERT_EQUAL(cols, (uint)x.cols());
  for (unsigned int i = 0; i < v.rows(); i++) {
    for (unsigned int j = 0; j < v.cols(); j++) {
      // column major
      CPPUNIT_ASSERT_EQUAL(data[j*rows+i], v(i, j));
      CPPUNIT_ASSERT_EQUAL(data[j*rows+i], w(i, j));
      CPPUNIT_ASSERT_EQUAL(data[j*rows+i], x(i, j));
//      // row major
//      CPPUNIT_ASSERT_EQUAL(data[i*cols+j], v(i, j));
//      CPPUNIT_ASSERT_EQUAL(data[i*cols+j], w(i, j));
//      CPPUNIT_ASSERT_EQUAL(data[i*cols+j], x(i, j));
    }
  }
}

void TestEMatrix::testExternal() {
  char data[] = "1234567890";
  unsigned int size = strlen(data);
  unsigned int rows = size / 5;
  unsigned int cols = 5;
  MatrixT<char> v(data, rows, cols, MatrixBase::external);
  data[5] = 'A';
  v(0, 3) = 'B';
  CPPUNIT_ASSERT_EQUAL(rows, (uint)v.rows());
  CPPUNIT_ASSERT_EQUAL(cols, (uint)v.cols());
  for (unsigned int i = 0; i < v.rows(); i++) {
    for (unsigned int j = 0; j < v.cols(); j++) {
      // column major
      CPPUNIT_ASSERT_EQUAL(data[j*rows+i], v(i, j));
//      // row major
//      CPPUNIT_ASSERT_EQUAL(data[i*cols+j], v(i, j));
    }
  }
  // column major
  CPPUNIT_ASSERT_EQUAL('A', v(1, 2));
  CPPUNIT_ASSERT_EQUAL('B', data[6]);
//      // row major
//  CPPUNIT_ASSERT_EQUAL('A', v(1, 0));
//  CPPUNIT_ASSERT_EQUAL('B', data[3]);
}

void TestEMatrix::testAssignment() {
  const char data[] = "fkepw.xja8";
  int size = strlen(data);
  unsigned int rows = size / 5;
  unsigned int cols = 5;
  MatrixT<char> a(data, rows, cols);
  std::auto_ptr<const MatrixT<char> >
    b(MatrixT<char>::createConst(data, rows, cols));
  MatrixT<char> t(a);
  MatrixT<char> u;
  u = a;
  MatrixT<char> v = a;
  MatrixT<char> w(*b);
  MatrixT<char> x;
  x = *b;
  MatrixT<char> y = *b;
  for (unsigned int i = 0; i < v.rows(); i++) {
    for (unsigned int j = 0; j < v.cols(); j++) {
      // column major
      CPPUNIT_ASSERT_EQUAL(data[j*rows+i], t(i, j));
      CPPUNIT_ASSERT_EQUAL(data[j*rows+i], u(i, j));
      CPPUNIT_ASSERT_EQUAL(data[j*rows+i], v(i, j));
      CPPUNIT_ASSERT_EQUAL(data[j*rows+i], w(i, j));
      CPPUNIT_ASSERT_EQUAL(data[j*rows+i], x(i, j));
      CPPUNIT_ASSERT_EQUAL(data[j*rows+i], y(i, j));
//      // row major
//      CPPUNIT_ASSERT_EQUAL(data[i*cols+j], t(i, j));
//      CPPUNIT_ASSERT_EQUAL(data[i*cols+j], u(i, j));
//      CPPUNIT_ASSERT_EQUAL(data[i*cols+j], v(i, j));
//      CPPUNIT_ASSERT_EQUAL(data[i*cols+j], w(i, j));
//      CPPUNIT_ASSERT_EQUAL(data[i*cols+j], x(i, j));
//      CPPUNIT_ASSERT_EQUAL(data[i*cols+j], y(i, j));
    }
  }
  u = 'o';
  for (unsigned int i = 0; i < v.rows(); i++) {
    for (unsigned int j = 0; j < v.cols(); j++) {
      CPPUNIT_ASSERT_EQUAL('o', u(i, j));
    }
  }
  MatrixT<int> ev[3];
  ev[0]=MatrixT<int>(2, 2);
  ev[1]=MatrixT<int>(3, 3);
  ev[2]=MatrixT<int>(4, 4);
  MatrixT<MatrixT<int> > eev(ev,3,1);
  MatrixT<MatrixT<int> > copy_eev = eev;
  for (unsigned int i = 0; i < eev.rows(); i++) {
    for (unsigned int j = 0; j < eev.cols(); j++) {
      CPPUNIT_ASSERT_EQUAL(eev(i, j), copy_eev(i, j));
    }
  }
}

void TestEMatrix::testArithmetics() {
  MatrixT<float> v(2, 10);
  for (unsigned int i = 0; i < v.rows(); i++) {
    for (unsigned int j = 0; j < v.cols(); j++) {
      v(i, j) = 100.0 - float(i+j);
    }
  }

  MatrixT<float> w(v);
  w *= 3.0;
  w -= v;
  for (unsigned int i = 0; i < v.rows(); i++) {
    for (unsigned int j = 0; j < v.cols(); j++) {
      CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(2.0f * v(i, j), w(i, j), 1E-20);
    }
  }

  MatrixT<float> a(3, 1);
  MatrixT<float> b(3, 1);
  MatrixT<float> c(3, 1);
  for (unsigned int i = 0; i < a.rows(); i++) {
    a(i, 0) = float(i);
    b(i, 0) = float(i + 1);
    c(i, 0) = float(i + 2);
  }
  MatrixT<float> m(3, 1);
  m = 0.0f;
  m += a;
  m += b;
  m += c;
  m /= 3.0f;

  for (unsigned int i = 0; i < m.rows(); i++) {
    CPPUNIT_ASSERT_EQUAL(float(i + 1), m(i, 0));
  }
}

void TestEMatrix::testRangeChecks() {
  CheckedMatrixT<double> v(10, 10, 4.5);
  CPPUNIT_ASSERT_EQUAL(4.5, v(0, 0));
  CPPUNIT_ASSERT_EQUAL(4.5, v(9, 9));
  CPPUNIT_ASSERT_THROW(v(-1, 0), std::out_of_range);
  CPPUNIT_ASSERT_THROW(v(0, -1), std::out_of_range);
  CPPUNIT_ASSERT_THROW(v(10, 0), std::out_of_range);
  CPPUNIT_ASSERT_THROW(v(0, 10), std::out_of_range);

  v(9, 9) = 5.1;
  CheckedMatrixT<double> w(v.getDataPointer(), v.rows(), v.cols());
  CPPUNIT_ASSERT_EQUAL(4.5, w(0, 0));
  CPPUNIT_ASSERT_EQUAL(5.1, w(9, 9));
  CPPUNIT_ASSERT_THROW(w(-1, 0), std::out_of_range);
  CPPUNIT_ASSERT_THROW(w(0, -1), std::out_of_range);
  CPPUNIT_ASSERT_THROW(w(10, 0), std::out_of_range);
  CPPUNIT_ASSERT_THROW(w(0, 10), std::out_of_range);
}

void TestEMatrix::testEqual() {
  MatrixT<double> v(10, 10, 4.5);
  MatrixT<double> w(10, 10, 4.5);
  MatrixT<double> x(10, 10, 4.5);
  MatrixT<double> y(9, 10, 4.5);
  MatrixT<double> z;
  x(9,9)=4.7;
  CPPUNIT_ASSERT(z==z);
  CPPUNIT_ASSERT(!(z!=z));
  CPPUNIT_ASSERT(v==w);
  CPPUNIT_ASSERT(!(v!=w));
  CPPUNIT_ASSERT(v!=x);
  CPPUNIT_ASSERT(!(v==x));
  CPPUNIT_ASSERT_THROW(x==y, std::invalid_argument);
  CPPUNIT_ASSERT_THROW(x!=y, std::invalid_argument);
}

void TestEMatrix::testTranspose() {
  {
    const char data[] = "fkepw.xja";
    unsigned int rows = 3;
    unsigned int cols = 3;
    MatrixT<char> a(data, rows, cols);
    MatrixT<char> b(data, rows, cols);

    a.transposeInplace();
    for (unsigned int i = 0; i < a.rows(); i++) {
      for (unsigned int j = 0; j < a.cols(); j++) {
        CPPUNIT_ASSERT_EQUAL(a(i, j), b(j, i));
      }
    }

    MatrixT<char> c = a.transpose();
    CPPUNIT_ASSERT_EQUAL(a.rows(), c.cols());
    CPPUNIT_ASSERT_EQUAL(a.cols(), c.rows());
    for (unsigned int i = 0; i < a.rows(); i++) {
      for (unsigned int j = 0; j < a.cols(); j++) {
        CPPUNIT_ASSERT_EQUAL(a(i, j), c(j, i));
      }
    }

    //std::stringstream inout; inout << c << "!=" << a.transpose();
    //CPPUNIT_COND_STREAM(!(a==c), inout.str());

    MatrixT<char> d(data, 2, 3);
    MatrixT<char> e = d.transpose();
    CPPUNIT_ASSERT_EQUAL(d.rows(), e.cols());
    CPPUNIT_ASSERT_EQUAL(d.cols(), e.rows());
    for (unsigned int i = 0; i < d.rows(); i++) {
      for (unsigned int j = 0; j < d.cols(); j++) {
        CPPUNIT_ASSERT_EQUAL(d(i, j), e(j, i));
      }
    }

    // test operator, time inefficient :)
    for (unsigned int i = 0; i < a.rows(); i++) {
      for (unsigned int j = 0; j < a.cols(); j++) {
	CPPUNIT_ASSERT_EQUAL(a(i,j), (!a)(j,i));
      }
    }

  }
  {
    const float data[] = {13.0f,15.0f,17.0f,18.0f,1.0f,2.0f,3.0f,4.0f,5.0f};
    unsigned int rows = 3;
    unsigned int cols = 3;
    MatrixT<float> a(data, rows, cols);
    MatrixT<float> b(data, rows, cols);

    a.transposeInplace();
    for (unsigned int i = 0; i < a.rows(); i++) {
      for (unsigned int j = 0; j < a.cols(); j++) {
        CPPUNIT_ASSERT_EQUAL(a(i, j), b(j, i));
      }
    }

    MatrixT<float> c = a.transpose();
    CPPUNIT_ASSERT_EQUAL(a.rows(), c.cols());
    CPPUNIT_ASSERT_EQUAL(a.cols(), c.rows());
    for (unsigned int i = 0; i < a.rows(); i++) {
      for (unsigned int j = 0; j < a.cols(); j++) {
        CPPUNIT_ASSERT_EQUAL(a(i, j), c(j, i));
      }
    }

    //std::stringstream inout; inout << c << "!=" << a.transpose();
    //CPPUNIT_COND_STREAM(!(a==c), inout.str());

    MatrixT<float> d(data, 2, 3);
    MatrixT<float> e = d.transpose();
    CPPUNIT_ASSERT_EQUAL(d.rows(), e.cols());
    CPPUNIT_ASSERT_EQUAL(d.cols(), e.rows());
    for (unsigned int i = 0; i < d.rows(); i++) {
      for (unsigned int j = 0; j < d.cols(); j++) {
        CPPUNIT_ASSERT_EQUAL(d(i, j), e(j, i));
      }
    }
  }
}

void TestEMatrix::testMultiply() {
  MatrixT<double> a(2,3);
  MatrixT<double> b(3,2);
  MatrixT<double> d(3,1);
  for (unsigned int i = 0; i < a.rows(); i++) {
    for (unsigned int j = 0; j < a.cols(); j++) {
      a(i, j) = i+j;
    }
  }
  for (unsigned int i = 0; i < b.rows(); i++) {
    for (unsigned int j = 0; j < b.cols(); j++) {
      b(i, j) = (int)i - (int)j;
    }
  }
  {
   MatrixT<double> m;
   CPPUNIT_ASSERT_THROW(m.multiply(d, a), Exception);
   CPPUNIT_ASSERT_THROW(m=d*a, Exception);
  }
  {
   MatrixT<double> m;
   CPPUNIT_ASSERT_THROW(m.multiply(a, d, true), Exception);
  }
  {
   MatrixT<double> m;
   CPPUNIT_ASSERT_THROW(m.multiply(b, d), Exception);
   CPPUNIT_ASSERT_THROW(m=b*d, Exception);
  }
  {
   MatrixT<double> m;
   CPPUNIT_ASSERT_THROW(m.multiply(d, b), Exception);
   CPPUNIT_ASSERT_THROW(m=d*b, Exception);
  }
  {
   MatrixT<double> m(2,1);
   CPPUNIT_ASSERT_NO_THROW(m.multiply(a, d));
   CPPUNIT_ASSERT_NO_THROW(m=a*d);
  }
  {
   MatrixT<double> m(1,2);
   CPPUNIT_ASSERT_NO_THROW(m.multiply(d, a, true, true));
  }
  {
   MatrixT<double> m(1,2);
   CPPUNIT_ASSERT_NO_THROW(m.multiply(d, b, true, false));
  }
  {
   MatrixT<double> m(2,2);
   CPPUNIT_ASSERT_NO_THROW(m.multiply(a, a, false, true));
  }
  MatrixT<double> m;
  m.multiply(a, b);
  // assumes that the operator== is working correctly
  CPPUNIT_ASSERT( m == a*b );
  CPPUNIT_ASSERT_EQUAL(2u, (uint)m.cols());
  CPPUNIT_ASSERT_EQUAL(2u, (uint)m.rows());
  CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(5.0, m(0, 0), 1E-20);
  CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(2.0, m(0, 1), 1E-20);
  CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(8.0, m(1, 0), 1E-20);
  CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(2.0, m(1, 1), 1E-20);
   float array[]= {0.8385,0.6946,0.1730,0.1365,0.2844,0.5155
                  ,0.5681,0.6213,0.9797,0.0118,0.4692,0.3340
                  ,0.3704,0.7948,0.2714,0.8939,0.0648,0.4329
                  ,0.7027,0.9568,0.2523,0.1991,0.9883,0.2259
                  ,0.5466,0.5226,0.8757,0.2987,0.5828,0.5798
                  ,0.4449,0.8801,0.7373,0.6614,0.4235,0.7604};
   MatrixT<float> c(array,6,6);
  {
      MatrixT<float> m;
      m.multiply(c, c);
      double checksum=0;
      for(int i=0;i<6;i++)
        for(int j=0;j<6;j++) {
            checksum += m(i,j);
            checksum*=3.0;
        }
      std::stringstream inout; inout << checksum << endl << c << "*" << c << "=" << m;
      CPPUNIT_COND_STREAM(abs(checksum-3.72091e+17)/3.72091e+17<1e-6, inout.str());


  }
  {
      MatrixT<float> m;
      m.multiply(c, c, false, true);
      double checksum=0;
      for(int i=0;i<6;i++)
        for(int j=0;j<6;j++) {
            checksum += m(i,j);
            checksum*=3.0;
        }
      std::stringstream inout; inout << checksum << endl << c << "*" << c.transpose() << "=" << m;
      CPPUNIT_COND_STREAM(abs(checksum-4.92936e+17)/4.92936e+17<1e-6, inout.str());
  }
  {
      MatrixT<float> m;
      m.multiply(c, c, true, true);
      double checksum=0;
      for(int i=0;i<6;i++)
        for(int j=0;j<6;j++) {
            checksum += m(i,j);
            checksum*=3.0;
        }
      std::stringstream inout; inout << checksum << endl << c.transpose() << "*" << c.transpose() << "=" << m;
      CPPUNIT_COND_STREAM(abs(checksum-3.7386e+17)/3.7386e+17<1e-6, inout.str());
  }
  {
      MatrixT<float> m;
      m.multiply(c, c, true, false);
      double checksum=0;
      for(int i=0;i<6;i++)
        for(int j=0;j<6;j++) {
            checksum += m(i,j);
            checksum*=3.0;
        }
      std::stringstream inout; inout << checksum << endl << c.transpose() << "*" << c << " =" << m;
      CPPUNIT_COND_STREAM(abs(checksum-3.4161e+17)/3.4161e+17<1e-6, inout.str());

  }

}
void TestEMatrix::testDet() {
#ifdef NICE_USELIB_IPP
    MatrixT<float> a(20,20);
    a.setIdentity();
    CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(1.0,det(a), 1E-6);
    MatrixT<float> b(20,20,0.0);
    CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(0.0,det(b), 1E-6);

    float array[]= {0.8385,0.6946,0.1730,0.1365,0.2844,0.5155
                   ,0.5681,0.6213,0.9797,0.0118,0.4692,0.3340
                   ,0.3704,0.7948,0.2714,0.8939,0.0648,0.4329
                   ,0.7027,0.9568,0.2523,0.1991,0.9883,0.2259
                   ,0.5466,0.5226,0.8757,0.2987,0.5828,0.5798
                   ,0.4449,0.8801,0.7373,0.6614,0.4235,0.7604};
    MatrixT<float> c(array,6,6);
    CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(0.0498667,det(c), 1E-6);
#endif
}

void TestEMatrix::testEigenValues() {
  VectorT<float> buffer(3);
  MatrixT<float> b(3,3,0.0f);
  float data[][3]= {{1.00861, 2.17143, 2.90536},
                    {9.01223, 2.17129, 1.90898},
                    {8.01585, 2.17114, 9.9126},
                    {7.01947, 2.171, 8.91622},
                    {6.02309, 2.17086, 7.91984},
                    {5.02671, 2.17071, 6.92346},
                    {4.03033, 2.17057, 5.92708},
                    {3.03396, 2.17042, 4.93071},
                    {2.03758, 2.17028, 3.93433},
                    {1.0412, 2.17013, 2.93795}};
  for(int i=0;i<10;i++) {
      //buffer = VectorT<float>::UniformRandom(3,1.0,10.0,i);
      buffer = VectorT<float>(data[i], 3, VectorBase::external);
      //std::cerr << buffer << std::endl;
      MatrixT<float> x(buffer.getDataPointer(),3,1,MatrixBase::external);
      MatrixT<float> a(3,3);
      a.multiply(x,x,false,true);
      b+=a;
  }
  MatrixT<double> evecs;
  VectorT<double> evals;
  MatrixT<double> I;
#ifdef NICE_USELIB_IPP
  {
      float array[]= {11,4,14,4,-1,10,14,10,8};
      MatrixT<float> c(array,3,3);
      eigenvalues(c,&buffer);
      CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(0.0,27-buffer(0), 2E-6);
      CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(0.0,buffer(1), 2E-6);
      CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(0.0,-9-buffer(2), 1E-6);
  }
  {
    eigenvalues(b,&buffer);
    CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(677.0, buffer(0), 5);
    CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(40.07, buffer(1), 3);
//     CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(674.32794189453, buffer(0), 1E-4);
//     CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(37.728626251220, buffer(1), 1E-4);
    double array[]= {292,101,295,104,48,122,295,122,384};
    MatrixT<double> c(array,3,3);
    eigenvectorvalues(c,evecs,evals);
    I.multiply(evecs,evecs.transpose());
    CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(0.0, 1.0-det(I), 2E-15);
  }
#endif
#ifdef NICE_USELIB_LINAL
  {
    double array[]= {292,101,295,101,48,122,295,122,384};
    MatrixT<double> c(array,3,3);
    evals= VectorT<double>(3,0.0);
    evecs= MatrixT<double>(3,3,0.0);
    LinAl::MatrixCF<double> lc = c.linal();
    LinAl::VectorCC<double> levals = evals.linalCol();
    LinAl::MatrixCF<double> levecs = evecs.linal();
    eigensym(lc, levals, levecs, 3);
    CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(677.0, levals(0,0), 5);
    CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(40.07, levals(1,0), 1.1);
    I.multiply(evecs,evecs.transpose());
    double d = LinAl::det(I.linal());
    CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(0.0, 1.0-d, 2E-15);
  }
#endif
}


#endif
