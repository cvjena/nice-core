/**
* @file GenericMatrix.cpp
* @brief matrix interface for indirect matrix multiplications
* @author Erik Rodner
* @date 05/14/2009

*/

#include "GenericMatrix.h"

using namespace NICE;
using namespace std;

GMSparse::GMSparse ( const NICE::Matrix & A, double epsilon )
{
  // derive a sparse matrix from a dense one
  m_rows = A.rows ();
  m_cols = A.cols ();
  for ( uint i = 0; i < m_rows; i++ )
    for ( uint j = 0; j < m_cols; j++ )
      if ( fabs ( A ( i, j ) ) > epsilon )
        this->A.insert ( this->A.begin (), NICE::triplet < int, int,
                         double > ( i, j, A ( i, j ) ) );
}

void
GMSparse::multiply ( NICE::Vector & y, const NICE::Vector & x ) const
{
  if ( x.size() != m_cols )
    fthrow ( Exception, "GMSparse::multiply: vector and matrix size do not match!" );

  y.resize ( m_rows );
  y.set ( 0.0 );

  // perform sparse multiplication
  for ( vector < NICE::triplet < int, int, double > >::const_iterator k =
          this->A.begin (); k != this->A.end (); k++ )
  {
    int i = k->first;
    int j = k->second;
    double value = k->third;  // = a_ij
    y[i] += value * x[j];
  }
}

GMCovariance::GMCovariance ( const NICE::Matrix *data )
{
  this->data = data;
}

void
GMCovariance::multiply ( NICE::Vector & y, const NICE::Vector & x ) const
{
  if ( x.size() != data->rows() )
    fthrow ( Exception, "GMCovariance::multiply: vector and matrix size do not match!" );

  /*******************************************************************
   * d_k = data(:,k) vector k in the data set
   * f_k = d_k^T x
   * fSum = \sum_k f_k
   * In the following we use the following relationship
   * S = \sum_i d_i ( d_i - \mu )^T = \sum_i (d_i - \mu) (d_i - \mu)^T
   * Sx = \sum_i d_i ( f_i - fSum/N )
   * which seems to be very efficient
   * *****************************************************************/

  NICE::Vector f ( data->cols () );
  f.set ( 0.0 );
  double fSum = 0.0;

  for ( uint k = 0; k < data->cols (); k++ )
  {
    for ( uint d = 0; d < data->rows (); d++ )
      f[k] += ( *data ) ( d, k ) * x[d];
    fSum += f[k];
  }

  y.resize ( x.size () );
  y.set ( 0.0 );
  int N = data->cols ();
  for ( uint k = 0; k < data->cols (); k++ )
    for ( int l = 0; l < ( int ) y.size (); l++ )
      y[l] += ( f[k] - fSum / N ) * ( ( *data ) ( l, k ) );

  for ( int i = 0; i < ( int ) y.size (); i++ )
    y[i] /= N;
}
