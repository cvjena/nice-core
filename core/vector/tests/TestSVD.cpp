/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libbasicvector - An core/vector/template for new NICE libraries
 * See file License for license information.
 */

#ifdef NICE_USELIB_CPPUNIT
#include "TestSVD.h"
#include "core/basics/cppunitex.h"
#include "core/vector/MatrixT.h"
#include "core/vector/SVD.h"

#include <string>
#include <exception>

using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION( TestSVD );

void TestSVD::setUp() {
}

void TestSVD::tearDown() {
}


#define sr(tr, tm, t0, t1, t2, t3) tm(tr,0)=t0; tm(tr,1)=t1; tm(tr,2)=t2; tm(tr,3)=t3;

#define ASSERT_MATRIX_EQUAL(m1, m2) for(int i=0; i<m1.rows(); i++) { \
	for(int j=0; j<m1.cols(); j++) { \
		CPPUNIT_ASSERT_DOUBLES_EQUAL(m1(i,j),m2(i,j),0.0002); \
	} \
}

void TestSVD::testSVD() {
	NICE::MatrixT<double> matrix(4,4);

	sr(0, matrix, 1, 2, 3, 4);
	sr(1, matrix, 4, 5, 6, 7);
	sr(2, matrix, 2, 3, 4, 5);
	sr(3, matrix, 2, 9, 8, 1);

	NICE::MatrixT<double> exu(4,4,0);
	sr(0, exu, -0.2852, -0.2948, -0.7390, -0.5345);
	sr(1, exu, -0.6079, -0.4409,  0.6038, -0.2673);
	sr(2, exu, -0.3927, -0.3435, -0.2914,  0.8018);
	sr(3, exu, -0.6284,  0.7750, -0.0667, -0.0000);

	NICE::MatrixT<double> exs(4,4,0);
	exs(0,0) = 17.8539;
	exs(1,1) = 6.3372;
	exs(2,2) = 1.0374;
	
	NICE::MatrixT<double> exv(4,4,0);
	sr(0, exv, -0.2666, -0.1866,  0.9256, -0.1913);
	sr(1, exv, -0.5849,  0.4971,  0.0646,  0.6376);
	sr(2, exv, -0.6218,  0.2046, -0.2823, -0.7013);
	sr(3, exv, -0.4474, -0.8218, -0.2436,  0.2550);

	NICE::MatrixT<double> fail(4,4,999.999);

#ifdef NICE_USELIB_LINAL
	NICE::SVD<double> test_svd(matrix);
	ASSERT_MATRIX_EQUAL(exu, test_svd.getU());
	ASSERT_MATRIX_EQUAL(exs, test_svd.getS());
	ASSERT_MATRIX_EQUAL(exv, test_svd.getV());
#else
	ASSERT_MATRIX_EQUAL(exu, fail);
#endif

}

#endif
