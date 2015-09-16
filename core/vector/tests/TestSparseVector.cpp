/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libbasicvector - A simple vector library
 * See file License for license information.
 */

#ifdef NICE_USELIB_CPPUNIT
#include "TestSparseVector.h"
#include <string>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <core/basics/cppunitex.h>
#include "core/vector/VectorT.h"
#include "core/vector/SparseVectorT.h"

CPPUNIT_TEST_SUITE_REGISTRATION( TestSparseVector );

using namespace NICE;
using namespace std;

const bool b_verbose = false;

void TestSparseVector::testProducts()
{
  SparseVector v1;
  v1[0] = 0.5;
  v1[1] = 1.0;
  v1[3] = 0.1;
  v1[4] = 2.0;
  SparseVector v2;
  v2[2] = 8;
  v2[3] = 5;
  v2[4] = 1.1;
  
  CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN ( 2.7, v1.innerProduct(v2), 1e-12 );
  CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN ( 2.7, v2.innerProduct(v1), 1e-12 );
  CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN ( 1.2, v2.minimumKernel(v1), 1e-12 );
  CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN ( 1.2, v1.minimumKernel(v2), 1e-12 );

  string mystring = "SVECTOR 10 4 0 0.5 1 1.0 3 0.1 4 2.0 END ";
  istringstream iss ( mystring.c_str() );
  SparseVector v3;
  v3.restore ( iss );
  
  if ( b_verbose )
    std::cerr << "TestSparseVector::testProducts -- check1 v3 == v1 " << std::endl;
  
  CPPUNIT_ASSERT ( v3 == v1 );
  
  if ( b_verbose )
    std::cerr << "TestSparseVector::testProducts -- check1 v3 == v1 passed" << std::endl;

  //cerr << "Testing SparseVector::FORMAT_INDEX_LINE" << endl;
  stringstream ss;
  v1.store( ss, SparseVector::FORMAT_INDEX_LINE );
  ss.seekg( 0, ios::beg );
  v3.clear();
  v3.restore ( ss, SparseVector::FORMAT_INDEX_LINE );

  if ( b_verbose )
    std::cerr << "TestSparseVector::testProducts -- check2 v3 == v1 " << std::endl;
  
  CPPUNIT_ASSERT ( v3 == v1 );
  
  if ( b_verbose )
    std::cerr << "TestSparseVector::testProducts -- check2 v3 == v1 passed" << std::endl;
  
  //cerr << "Testing SparseVector::FORMAT_INDEX" << endl;
  stringstream ss2;
  v1.store( ss2, SparseVector::FORMAT_INDEX );
  ss2.seekg( 0, ios::beg );
  v3.clear();
  v3.restore ( ss2, SparseVector::FORMAT_INDEX );

  if ( b_verbose )
    std::cerr << "TestSparseVector::testProducts -- check3 v3 == v1" << std::endl;
  
  CPPUNIT_ASSERT ( v3 == v1 );
  
  if ( b_verbose )
    std::cerr << "TestSparseVector::testProducts -- check3 v3 == v1 passed" << std::endl;

}

void TestSparseVector::testConversionToVectorT()
{
  SparseVector sv;
  sv[0] = 0.5;
  sv[1] = 1.0;
  sv[3] = 0.1;
  sv[4] = 2.0;  
  
  NICE::Vector v;
  sv.convertToVectorT( v );
  
  NICE::Vector vGT(5);
  vGT[0] = 0.5;vGT[1] = 1.0;vGT[2] = 0.0;vGT[3] = 0.1;vGT[4] = 2.0;
   
  if ( b_verbose )
  {
    std::cerr << "TestSparseVector::testConversionToVectorT -- v == vGT" << std::endl;
  
    std::cerr << v << std::endl;
    std::cerr << vGT << std::endl;
  }
  
  CPPUNIT_ASSERT ( v == vGT );
  
  if ( b_verbose )
    std::cerr << "TestSparseVector::testConversionToVectorT -- v == vGT passed" << std::endl;
}

#endif
