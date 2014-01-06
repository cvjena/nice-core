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
  /////////////////////////////////////  
  ///////// check input arguments /////
  /////////////////////////////////////

  if ( data.rows () != data.cols () )
  {
    throw ( "EVArnoldi: matrix has to be quadratic" );
  }
  
  if ( k <= 0 )
  {
    throw ( "EVArnoldi: please use k>0." );
  }
  
  // did we specify more eigenvalues than the matrix can actually have?
  if ( k > data.rows() )
  {
    throw ( "EVArnoldi: specified k is larger then dimension of matrix! Aborting..." );
  }  
  
  //////////////////////////////////////
  ///////// initialize variables ///////
  //////////////////////////////////////

  if ( verbose )
    cerr << "Initialize Matrices" << std::endl;

  uint n = data.cols ();
  
  if ( verbose )
    std::cerr << "EVArnoldi: n: " << n << " k: " << k << std::endl;
  
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
      rmatrix ( j, i ) = drand48 ();
//       rmatrix ( j, i ) = 0.5;
      //TODO the random initialization might help, but it is bad for reproducibility :(

  ////////////////////////////////////
  ///////// start computation  ///////
  ////////////////////////////////////      
  if ( verbose )
    std::cerr << "EVArnoldi: start main computation" << std::endl;    
      
  //reduceddim
  double delta = 1.0;
  uint iteration = 0;
  while ( delta > mindelta && iteration < maxiterations )
  {
    //replace Vector rold by matrix rold to check for convergence of all eigenvectors
    //NICE::Vector rold ( rmatrix.getColumn ( k - 1 ) );
    NICE::Matrix rold(rmatrix);
    
    if ( verbose )
      std::cerr << "EVArnoldi: start for loop over reduced dims" << std::endl;
    
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
    
    if ( verbose )
      std::cerr << "EVArnoldi: ended for loop over reduced dims" << std::endl;
    
    //convergence stuff (replaced by checking all eigenvectors instead of a single one
    //NICE::Vector diff = rold - rmatrix.getColumn ( k - 1 );
    //delta = diff.normL2 ();
    NICE::Vector tmpDiff;
    double norm_tmpDiff;
    delta = 0.0;
    for ( uint j = 0; j < k; j++ )
    {
      tmpDiff = rold.getColumn(j) - rmatrix.getColumn(j);
      norm_tmpDiff = tmpDiff.normL2();
      if (norm_tmpDiff > delta)
        delta = norm_tmpDiff;
    }
    iteration++;

    if ( verbose )
      cerr << "EVArnoldi: [" << iteration << "] delta=" << delta << endl;
  }
  
  if ( verbose )
    std::cerr << "EVArnoldi: while-loop done" << std::endl;
  
  eigenvectors = rmatrix;
  
  for ( uint i = 0; i < k; i++ )
  {
    NICE::Vector tmp;
    eigenvectors.getColumnRef ( i ).normalizeL2 ();
    data.multiply ( tmp, eigenvectors.getColumn ( i ) );
    eigenvalues[i] = tmp.scalarProduct ( eigenvectors.getColumn ( i ) );
  }

  
  // post-processing: ensure that eigenvalues are in correct order!
  
  if ( this->b_verifyDecreasingOrder && (k > 1) )
  {
    NICE::VectorT< int > ewPermutation;
    eigenvalues.sortDescend ( ewPermutation );
    
    NICE::Vector tmpRow;
    int tmpIdx (-1);
    for ( uint i = 0; i < k; i++ )
    { 
      if ( i == ewPermutation[i] )
      {
        //identity - nothing to do here
      }
      else
      {
        if ( tmpIdx == -1 )
        {
          tmpIdx = i;
          tmpRow = eigenvectors.getColumn ( i );
          eigenvectors.getColumnRef ( i ) = eigenvectors.getColumn ( ewPermutation[i] );
        }
        else
        {
          if ( tmpIdx != ewPermutation[i] )
          {
            eigenvectors.getColumnRef ( i ) = eigenvectors.getColumn ( ewPermutation[i] );
          }
          else // tmpIdx == ewPermutation[i]
          {
            eigenvectors.getColumnRef ( i ) = tmpRow;
            tmpIdx = -1;
          }
        }
      }
    }
    
  }// sorting is only useful if we compute more then 1 ew  
}
