/**
 * @file TestDiagApprox.cpp
 * @brief TestDiagApprox
 * @author Michael Koch
 * @date Di Aug 4 2009
 */

#include "TestDiagApprox.h"
#include <string>

#include "core/basics/cppunitex.h"
#include "core/basics/numerictools.h"
#include "core/vector/Distance.h"

#include "core/algebra/DiagonalMatrixApprox.h"

using namespace std;
using namespace NICE;

CPPUNIT_TEST_SUITE_REGISTRATION(TestDiagApprox);

void TestDiagApprox::setUp()
{
}

void TestDiagApprox::tearDown()
{
}

void TestDiagApprox::TestDiagApproxComputation()
{
    // size of the matrix
    uint rows = 2;
    uint cols = rows;
  
    // number of eigenvalues used
    uint maxiterations =  20;
   
   // use a fixed seed, its a test case
#ifdef WIN32
	srand(0);
#else
    srand48(0);
#endif
 
    DiagonalMatrixApprox diagApprox ( true /*verbose*/ );
    
    Vector D ( rows, 0.0 );

    Matrix Tdiag ( rows, rows, 0.0 );
   
    for (uint j = 0 ; j < rows ; j++)
    {
#ifdef WIN32
		 Tdiag(j, j) = double( rand() ) / RAND_MAX;
#else
      Tdiag(j, j) = drand48();
#endif
    }
 
    diagApprox.approx ( Tdiag, D );
    cerr << Tdiag << endl;
    cerr << D << endl;

    double error = 0.0;
    for ( uint i = 0 ; i < rows; i++ )
      error += fabs(Tdiag(i,i) - D[i]);

    CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN( 0.0, error, 0.1 );

    
    D.set(0.0); 
    
    NICE::Matrix T(rows, cols, 0.0);

   
    // generate random symmetric matrix
    for (uint i = 0 ; i < rows ; i++)
        for (uint j = i ; j < cols ; j++)
        {
#ifdef WIN32
		 T(i, j) = double( rand() ) / RAND_MAX;
#else
            T(i, j) = drand48();
#endif
            T(j, i) = T(i, j);
        }

    // create a positive definite matrix
    T = T*T;
    
    diagApprox.approx ( T, D );
    cerr << T << endl;
    cerr << D << endl;


}
