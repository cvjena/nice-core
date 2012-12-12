/**
 * @file TestLUDecomposition.cpp
 * @brief TestLUDecomposition
 * @author Alexander Freytag
 * @date 22-10-2012
 */

#include <string>
#include <vector>

#include <core/vector/MatrixT.h>
#include "core/algebra/LUDecomposition.h"

#include "TestLUDecomposition.h"

using namespace std;
using namespace NICE;

CPPUNIT_TEST_SUITE_REGISTRATION(TestLUDecomposition);

void TestLUDecomposition::setUp()
{
}

void TestLUDecomposition::tearDown()
{
}

void TestLUDecomposition::testLUDecomposition()
{
    // verbose flag for additional output for each iteration
    bool verbose (false);
    
    NICE::Matrix m (4, 4, 0.0);
    
    for (int j = 0; j < 4; j++)
      for (int i = 0; i < 4; i++)
        m(i,j) = i*4+(j+1);
      
    //ensure the non-singularity :)
    m.addIdentity(1.0);
    
    LUDecomposition luDecomp;
    
    NICE::Matrix L;
    NICE::Matrix U;

    //perform the actual decomposition - with pivotization if needed
    luDecomp.decompose(m, L, U);
   
    
    NICE::Matrix mult;
    mult.multiply(L,U);
    
    double diff(0.0);
    
    for (int j = 0; j < 4; j++)
      for (int i = 0; i < 4; i++)
        diff += pow( mult(i,j) - m(i,j) , 2);
      
    diff = sqrt(diff);

    if (verbose)
    {
      std::cerr << "LUDecomposition test: " << std::endl;    
      std::cerr << "m: " << m << std::endl;    
      std::cerr << "L: " << L << std::endl;
      std::cerr << "U: " << U << std::endl;
      std::cerr << "LU: " << mult << std::endl;
      std::cerr << "LUDecomposition test done " << std::endl;
    }

    double tol(10e-6);    
    if (verbose)
      std::cerr << "tol: " << tol << " diff: " << diff << std::endl;   
    CPPUNIT_ASSERT( diff < tol);
    
}
