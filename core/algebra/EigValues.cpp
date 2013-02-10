/**
 * @file EigValues.cpp
 * @brief EigValues Class
 * @author Michael Koch
 * @date 08/19/2008
*/

#include <iostream>

#include "EigValues.h"

#define DEBUG_ARNOLDI

using namespace NICE;
using namespace std;

void
EVArnoldi::getEigenvalues ( const GenericMatrix & data, Vector & eigenvalues,
                            Matrix & eigenvectors, uint k )
{

  if ( data.rows () != data.cols () )
  {
    throw ( "EVArnoldi: matrix has to be quadratic" );
  }
  if ( k <= 0 )
  {
    throw ( "EVArnoldi: please use k>0." );
  }

  if ( verbose )
    cerr << "Initialize Matrices";

  uint n = data.cols ();
  NICE::Matrix rmatrix ( n, k, 0 ); //=eigenvectors
  NICE::Matrix qmatrix ( n, k, 0 ); //saves data =eigenvectors
  eigenvalues.resize ( k );
  NICE::Vector q ( n );
  NICE::Vector r ( n );

  if ( verbose )
    cerr << "Random Initialization" << endl;

  //random initialisation
  for ( uint i = 0; i < k; i++ )
    for ( uint j = 0; j < n; j++ )
#ifdef WIN32
		rmatrix (j, i) = double(rand())/RAND_MAX;
#else
		rmatrix (j, i) = drand48 ();
#endif
//       rmatrix ( j, i ) = 0.5;
      //TODO the random initialization might help, but it is bad for reproducibility :(

  //reduceddim
  double delta = 1.0;
  uint iteration = 0;
  while ( delta > mindelta && iteration < maxiterations )
  {
    NICE::Vector rold ( rmatrix.getColumn ( k - 1 ) );
    // meta-comment: i is an index for the iteration, j is an index for the basis
    // element (1 <= j <= k)
    for ( uint reduceddim = 0; reduceddim < k; reduceddim++ )
    {
      // -> get r^i_j from R matrix
      q = rmatrix.getColumn ( reduceddim );
      // q^i_j = r^i_j / ||r^i_j||
      q.normalizeL2 ();
      // -> store in Q matrix
      qmatrix.getColumnRef ( reduceddim ) = q;

      // this line copies a vector with external memory!
      // changing currentcol leads to a change in the R matrix!!
      Vector currentCol = rmatrix.getColumnRef ( reduceddim );
      // r^{i+1}_j = A * q^i_j      ( r^i_j is overwritten by r^{i+1}_j )
      data.multiply ( currentCol, q );

      // for all j: r^{i+1}_j -= q^i_j * < q^i_j, r^{i+1}_j >
      for ( uint j = 0; j < reduceddim; j++ )
        rmatrix.getColumnRef ( reduceddim ) -=
          qmatrix.getColumn ( j ) *
          ( qmatrix.getColumn ( j ).
            scalarProduct ( rmatrix.getColumn ( reduceddim ) ) );
    }
    //convergence stuff
    NICE::Vector diff = rold - rmatrix.getColumn ( k - 1 );
    delta = diff.normL2 ();
    iteration++;

    if ( verbose )
      cerr << "EVArnoldi: [" << iteration << "] delta=" << delta << endl;
  }
  eigenvectors = rmatrix;

  for ( uint i = 0; i < k; i++ )
  {
    NICE::Vector tmp;
    eigenvectors.getColumnRef ( i ).normalizeL2 ();
    data.multiply ( tmp, eigenvectors.getColumn ( i ) );
    eigenvalues[i] = tmp.scalarProduct ( eigenvectors.getColumn ( i ) );
  }
}
