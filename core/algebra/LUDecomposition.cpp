/**
* @file LUDecomposition.cpp
* @brief: LU-Decomposition of a matrix
* @author: Alexander Freytag, Wolfgang Ortmann
* @date: 22-10-2012
*/

// Note: for further matrix operations, you might use the ICE library available at http://www.inf-cv.uni-jena.de/ice.html

#include "LUDecomposition.h"

using namespace std;
using namespace NICE;  

LUDecomposition::LUDecomposition()
{
}


LUDecomposition::~LUDecomposition()
{
}

void LUDecomposition::decompose( const NICE::Matrix & m, NICE::Matrix & L, NICE::Matrix  &U )
{
  NICE::Matrix LU;

  this->decomposePacked( m, LU );

  int i,j;
  L = LU; 
  U = LU;
  
  // get the actual matrices
  // U is an upper triangular matrix
  for (i = 0; i < (int)U.cols(); i++)
  {
    for (j = i + 1; j < (int)U.rows(); j++)
      U(j,i) = 0;
  }  
   
  // L is a lower triangular matrix
  for (i = 0; i < (int)L.cols(); i++)
  {
    for (j = 0; j < i; j++)
      L(j,i) = 0;

    L(i,i) = 1.0;
  }  
}


Vector LUSolve(const NICE::Matrix & LU, const NICE::VectorT<int> & indx, const NICE::Vector & b)
{
  NICE::Vector res(b);
  double sum;

  int dim = LU.cols();
  
  //is the given matrix square?
  if (dim!=(int)LU.rows()) 
  {
    fthrow(Exception, "Matrix is not square");    
    return res;
  }

  //do the matrix LU and the given index vector have same sizes?
  if ((int)indx.size()!=dim) 
  {
    fthrow(Exception, "Wrong dimensions of matrix and index-vector");
    return res;
  }
  
  //do the matrix LU and the given b-vector have same sizes?
  if ((int)b.size()!=dim) 
  {
    fthrow(Exception, "Wrong dimensions of matrix and b-vector");      
    return res;
  }
  
  int i, ii, ip, j;
  ii = -1;
  
  for (i = 0; i < dim; i++)
  {
    ip = indx[i];
    sum = res[ip];
    res[ip] = res[i];    
    
    if (ii >= 0)
    {
      for (j = ii; j < i; j++)
        sum -= LU(i, j) * res[j];
    }
    else
    {
      if (sum) 
        ii = i;
    }

    res[i] = sum;    
  }

  for (i = dim - 1; i >= 0; i--)
  {
    sum = res[i];

    for (j = i + 1; j < dim; j++)
      sum -= LU(i, j) * res[j];

    res[i] = sum / LU(i, i);
  }

  return res;
}

void LUDecomposition::decomposePacked(const NICE::Matrix & m, NICE::Matrix & LU, NICE::VectorT<int> &indx, bool pivot)
{
  int dim = m.cols();
  
  // check, whether the matrix is square
  if (dim != (int)m.rows())
  {
    fthrow(Exception, "Matrix is not square");
  }
  
  LU = m;
  
  NICE::Vector vv(dim);
  indx.resize(dim);

  int i, j, k, imax;
  double sum, big, dum;
  int dsign = 1;

  for (i = 0; i < dim; i++)
  {
    big = 0.0;

    for (j = 0; j < dim; j++)
    {
      double temp = fabs(LU(i, j));

      if (temp > big)
        big = temp;
    }    
    //check for singularity, i.e., the largest absolute singular value is zero
    if (big == 0) 
    {
      fthrow(Exception, "Matrix is singular");
    }
    
    vv[i] = 1.0 / big;
  }

  // loop over all columns
  for (j = 0; j < dim; j++)
  {
    //and over all rows
    for (i = 0; i < j; i++)
    {
      sum = LU(i,j);
      
      for (k = 0; k < i; k++)
        sum -= LU(i, k) * LU(k, j);
      
      LU(i,j)=sum;
    }
    
    big = 0.0;
    imax = 0; // avoid warning
        
    for (i = j; i < dim; i++)
    {
      sum = LU(i, j);
      
      for (k = 0; k < j; k++)
        sum -= LU(i, k) * LU(k, j);

      LU(i, j) = sum;
      dum = vv[i] * fabs(sum);

      if (dum >= big)
      {
        big = dum;
        imax = i;
      }
    }

    //pivotization?
    if (pivot)
    {
      if (j != imax)
      {
        LU.exchangeRows(j, imax);
        dsign = -dsign;
        vv[imax] = vv[j];
      }
      
      indx[j] = imax;     
    }
    else indx[j] = j;

    if (LU(j, j) == 0) 
    {
      fthrow(Exception, "Matrix is singular");
    }

    if (j < dim - 1)
    {
      dum = 1.0 / LU(j, j);

      for (i = j + 1; i < dim; i++)
        LU(i, j) *= dum;
    }
  } // all columns
}

void LUDecomposition::decomposePacked(const NICE::Matrix & m, NICE::Matrix & LU)
{
  NICE::VectorT<int> ndx; // dummy, not used (without pivotization)
  this->decomposePacked(m, LU, ndx, false);
}

