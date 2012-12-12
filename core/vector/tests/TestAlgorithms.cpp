/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libbasicvector - An core/vector/template for new NICE libraries
 * See file License for license information.
 */

#ifdef NICE_USELIB_CPPUNIT
#include "TestAlgorithms.h"
#include "core/basics/cppunitex.h"

    #ifdef NICE_USELIB_LINAL
        #include "LinAl/algorithms.h"
        #include "LinAl/operatorsT.h"
    #endif

#include <string>
#include <exception>

using namespace NICE;
using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION( TestAlgorithms );

void TestAlgorithms::setUp() {
}

void TestAlgorithms::tearDown() {
}

void TestAlgorithms::testSomething() {
  float Abuffer[]={2, 8, 6, 5, -3, 0, 1, 9, -7, 0, -1, 4};
  float bbuffer[] = { 16, -13, -7, 7};
  float ybuffer[] = { -2, 1, 2}; // Result from solvelineQR (LinAl)
  VectorT<float> y(ybuffer,3);
  MatrixT<float> A(Abuffer,3,4);
  VectorT<float> b(bbuffer, 4);

    #ifdef NICE_USELIB_IPP
        VectorT<float> x(3);
        solveLinearEquationQR(A,b,x);
        y-=x;
        CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(0, y.normInf(), 5e-6);
        //CPPUNIT_ASSERT_EQUAL(x,y);
    #endif
}

void TestAlgorithms::testInvert3x3() {
  Matrix id(3, 3);
  id.setIdentity();

  {
    Matrix a(3, 3);
    a.setIdentity();
    invert3x3UpperTriangle(a);

    Matrix b(3, 3);
    b.setIdentity();
    invert3x3LowerTriangle(b);

    for (uint i = 0; i < 3; ++i) {
      for (uint j = 0; j < 3; ++j) {
        CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(id(i,j), a(i,j), 1E-16);
        CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(id(i,j), b(i,j), 1E-16);
      }
    }
  }

  {
    Matrix a(3, 3);
    a.setIdentity();
    a(0,0) = 2.0;
    a(1,1) = 3.0;
    a(2,2) = 4.0;
    Matrix b(a);

    invert3x3LowerTriangle(a);
    invert3x3UpperTriangle(b);

    for (uint i = 0; i < 3; ++i) {
      for (uint j = 0; j < 3; ++j) {
        double exp = (i==j) ? (1.0/(double(i)+2.0)) : 0.0;
        CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(exp, a(i,j), 1E-16);
        CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(exp, b(i,j), 1E-16);
      }
    }
  }


  Matrix aa(3, 3);
  aa.setIdentity();
  aa(0,0) = 2.0;
  aa(1,1) = 4.0;
  aa(2,2) = 8.0;
  aa(0,1) = 10.0;
  aa(0,2) = 20.0;
  aa(1,2) = 40.0;

  Matrix aaInv(3, 3);
  aaInv.setIdentity();
  aaInv(0,0) = 0.5;
  aaInv(1,1) = 0.25;
  aaInv(2,2) = 0.125;
  aaInv(0,1) = -1.25;
  aaInv(0,2) = 5.0;
  aaInv(1,2) = -1.25;

  {
    Matrix a(aa);
    Matrix b(a);

    invert3x3UpperTriangle(b);

    Matrix c(3,3);
    c.multiply(a, b);

    for (uint i = 0; i < 3; ++i) {
      for (uint j = 0; j < 3; ++j) {
        CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(id(i,j), c(i,j), 1E-16);
        CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(aaInv(i,j), b(i,j), 1E-16);
      }
    }
  }

  {
    Matrix a(aa);
    a.transposeInplace();
    Matrix b(a);

    invert3x3LowerTriangle(b);

    Matrix c(3,3);
    c.multiply(a, b);

    for (uint i = 0; i < 3; ++i) {
      for (uint j = 0; j < 3; ++j) {
        CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(id(i,j), c(i,j), 1E-16);
        CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(aaInv(j,i), b(i,j), 1E-16);
      }
    }
  }

}

void TestAlgorithms::testCholesky() {
	Matrix testM(3,3);
	testM.setIdentity();

	Matrix G;
	CPPUNIT_ASSERT_NO_THROW ( choleskyDecomp ( testM, G ) );

	CPPUNIT_ASSERT ( G.isEqual(testM, 1E-16) );

	testM(1,1) = -1.0;
	
	CPPUNIT_ASSERT_THROW ( choleskyDecomp ( testM, G ), Exception );

	{ 
		string text = string("3 x 3\n") +
			  + "0.9012    1.0575    0.6621\n"
			  + "1.0575    1.5656    1.0545\n"
			  + "0.6621    1.0545    0.8456\n";
		std::istringstream is ( text );
		is >> testM;
	}

	CPPUNIT_ASSERT_NO_THROW ( choleskyDecomp ( testM, G ) );

	Matrix G_groundtruth;

	{
		string text = string("3 x 3\n") +
					  + "0.9493    1.1139    0.6974\n" 
					  + "0    0.5699    0.4871\n"
					  + "0         0    0.3491\n";
		std::istringstream is ( text );
		is >> G_groundtruth;
		G_groundtruth.transposeInplace();
	}
	

	CPPUNIT_ASSERT ( G.isEqual(G_groundtruth, 1E-4) );
	CPPUNIT_ASSERT ( testM.isEqual(G*G.transpose(), 1E-4) );

    Matrix Minv;
	CPPUNIT_ASSERT_NO_THROW ( choleskyInvert ( G, Minv ) );

	Matrix id(3,3);
	id.setIdentity();
	CPPUNIT_ASSERT ( id.isEqual ( Minv * testM, 1E-14 ) );

	Matrix MinvFoo (3,3);
	MinvFoo.setIdentity();
	CPPUNIT_ASSERT_NO_THROW ( choleskySolveMatrixLargeScale ( G, MinvFoo ) );
	CPPUNIT_ASSERT ( id.isEqual ( MinvFoo * testM, 1E-14 ) );

	Matrix MinvBar (3,3);
	MinvBar.setIdentity();
	CPPUNIT_ASSERT_NO_THROW ( triangleSolveMatrix ( G, MinvBar, false ) );
	CPPUNIT_ASSERT ( id.isEqual ( G * MinvBar, 1E-4 ) );
	CPPUNIT_ASSERT_NO_THROW ( triangleSolveMatrix ( G, MinvBar, true ) );
	CPPUNIT_ASSERT ( id.isEqual ( MinvBar * testM, 1E-14 ) );

	Vector b (3);
	b(0) = -12.312;
	b(1) = -1.2141;
	b(2) = 31.23;

	Vector Mb;
	CPPUNIT_ASSERT_NO_THROW ( choleskySolve ( G, b, Mb ) );
	// 1E-14 might be to small
	CPPUNIT_ASSERT ( Mb.isEqual ( Minv*b, 1E-10 ) );

	Vector Mb1;
	CPPUNIT_ASSERT_NO_THROW ( triangleSolve ( G, b, Mb1, false ) );
	Vector Mb2;
	CPPUNIT_ASSERT_NO_THROW ( triangleSolve ( G, Mb1, Mb2, true ) );

	CPPUNIT_ASSERT ( Mb2.isEqual ( Minv*b, 1E-10 ) );

}

void TestAlgorithms::testCholeskyLargeScale() {
	Matrix testM(3,3);
	testM.setIdentity();

	Matrix G;
	CPPUNIT_ASSERT_NO_THROW ( choleskyDecompLargeScale ( testM, G ) );

	CPPUNIT_ASSERT ( G.isEqual(testM, 1E-16) );

	testM(1,1) = -1.0;
	
	CPPUNIT_ASSERT_THROW ( choleskyDecompLargeScale ( testM, G ), Exception );

	{ 
		string text = string("3 x 3\n") +
			  + "0.9012    1.0575    0.6621\n"
			  + "1.0575    1.5656    1.0545\n"
			  + "0.6621    1.0545    0.8456\n";
		std::istringstream is ( text );
		is >> testM;
	}

	CPPUNIT_ASSERT_NO_THROW ( choleskyDecompLargeScale ( testM, G ) );

	Matrix G_groundtruth;

	{
		string text = string("3 x 3\n") +
					  + "0.9493    1.1139    0.6974\n" 
					  + "0    0.5699    0.4871\n"
					  + "0         0    0.3491\n";
		std::istringstream is ( text );
		is >> G_groundtruth;
		G_groundtruth.transposeInplace();
	}
	

	CPPUNIT_ASSERT ( G.isEqual(G_groundtruth, 1E-4) );
	CPPUNIT_ASSERT ( testM.isEqual(G*G.transpose(), 1E-4) );

    Matrix Minv;
	CPPUNIT_ASSERT_NO_THROW ( choleskyInvertLargeScale ( G, Minv ) );

	Matrix id(3,3);
	id.setIdentity();
	CPPUNIT_ASSERT ( id.isEqual ( Minv * testM, 1E-14 ) );

	Vector b (3);
	b(0) = -12.312;
	b(1) = -1.2141;
	b(2) = 31.23;

	Vector Mb;
	CPPUNIT_ASSERT_NO_THROW ( choleskySolveLargeScale ( G, b, Mb ) );

	CPPUNIT_ASSERT ( Mb.isEqual ( Minv*b, 1E-10 ) );

}


void TestAlgorithms::testInvert() {
#if defined(NICE_USELIB_IPP) || defined(NICE_USELIB_LINAL)
  Matrix id(3, 3);
  id.setIdentity();

  {
    Matrix a(3, 3);
    a.setIdentity();
    Matrix aInv = invert(a);

    for (uint i = 0; i < 3; ++i) {
      for (uint j = 0; j < 3; ++j) {
        CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(id(i,j), aInv(i,j), 1E-16);
      }
    }
  }

  {
    Matrix a(3, 3);
    a.setIdentity();
    a(0,0) = 2.0;
    a(1,1) = 3.0;
    a(2,2) = 4.0;

    Matrix aInv = invert(a);

    for (uint i = 0; i < 3; ++i) {
      for (uint j = 0; j < 3; ++j) {
        double exp = (i==j) ? (1.0/(double(i)+2.0)) : 0.0;
        CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(exp, aInv(i,j), 1E-16);
      }
    }
  }


  Matrix aa(3, 3);
  aa.setIdentity();
  aa(0,0) = 2.0;
  aa(1,1) = 4.0;
  aa(2,2) = 8.0;
  aa(0,1) = 10.0;
  aa(0,2) = 20.0;
  aa(1,2) = 40.0;

  Matrix aaInv(3, 3);
  aaInv.setIdentity();
  aaInv(0,0) = 0.5;
  aaInv(1,1) = 0.25;
  aaInv(2,2) = 0.125;
  aaInv(0,1) = -1.25;
  aaInv(0,2) = 5.0;
  aaInv(1,2) = -1.25;

  {
    Matrix a(aa);
    Matrix b = invert(a);

    Matrix c(3,3);
    c.multiply(a, b);

    for (uint i = 0; i < 3; ++i) {
      for (uint j = 0; j < 3; ++j) {
        CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(id(i,j), c(i,j), 1E-14);
        CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(aaInv(i,j), b(i,j), 1E-14);
      }
    }
  }

  {
    Matrix a(aa);
    a.transposeInplace();
    Matrix b = invert(a);

    Matrix c(3,3);
    c.multiply(a, b);

    for (uint i = 0; i < 3; ++i) {
      for (uint j = 0; j < 3; ++j) {
        CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(id(i,j), c(i,j), 1E-14);
        CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(aaInv(j,i), b(i,j), 1E-14);
      }
    }
  }

  {
    Matrix bla(2,2);
    bla.setIdentity();
    bla(1,1) = 0.0;
    CPPUNIT_ASSERT_THROW(invert(bla), Exception);
  }
#endif
}

#endif
