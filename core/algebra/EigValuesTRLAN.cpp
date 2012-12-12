#include "EigValuesTRLAN.h"

#include <iostream>
#include <assert.h>


using namespace NICE;
using namespace std;


#ifdef NICE_USELIB_TRLAN
/** some hacks to use the C functions in the TRLAN library */
static const GenericMatrix* mat = NULL;

/** generic vector matrix multiplication */
static void op ( int* nrow, int* ncol, double* xin, int* ldx, double* xout, int* ldy )
{
  NICE::Vector xin_v ( xin, *ldy, NICE::VectorBase::external );
  NICE::Vector xout_v ( xout, *ldy, NICE::VectorBase::external );
  mat->multiply ( xout_v, xin_v );
}

/** imports from the TRLAN library */
typedef void ( *OpFunc ) ( int* nrow, int* ncol, double* xin, int* ldx, double* xout, int* ldy );
extern "C" void trlan77_ ( OpFunc op, int ipar[32], int* nrowl, int* mev, double* eval,
                             double* evec, int* nrow2, double* wrk, int* lwrk );
#endif


/** constructor, initialize some settings */
EigValuesTRLAN::EigValuesTRLAN ( int magnitude,
                                 int restarting_scheme,
                                 double tolerance,
                                 int max_mult,
                                 int mult_flops )
{
  this->magnitude = magnitude;
  this->restarting_scheme = restarting_scheme;
  this->tolerance = tolerance;
  this->max_mult = max_mult;
  this->mult_flops = mult_flops;
  this->verbose = false;
}


/** get some eigenvalues */
void EigValuesTRLAN::getEigenvalues ( const GenericMatrix &data, NICE::Vector & eigenvalues, NICE::Matrix & eigenvectors, uint k )
{
#ifndef NICE_USELIB_TRLAN
  fthrow ( Exception, "EigValuesTRLAN::getEigenvalues: this functions needs the TRLAN library" );
#else
  if ( verbose )
    fprintf ( stderr, "Starting eigenvalue computation with Lanczos Iteration ...\n" );
  assert ( data.rows() == data.cols() );
  if ( data.rows() != data.cols() ) {
    fthrow ( Exception, "EigValuesTRLAN::getEigenvalues: the input matrix is not quadratic\n" );
  }
  /** set the global matrix */
  mat = &data;
  int mat_size = ( int ) data.rows();

  if ( max_mult <= 0 ) max_mult = 10 * mat_size;
  if ( mult_flops <= 0 ) mult_flops = 10 * mat_size;

  /** intialize TRLAN stuff */
  int computed_eigenpairs = k;
  int ipar[32] = {0, magnitude, computed_eigenpairs, 0, 0, restarting_scheme, max_mult, 0, 1, 99, -1, 98, mult_flops};
  double* evalbuff = new double[k];
  memset ( evalbuff, 0, k*sizeof ( double ) );
  double* evecbuff = new double[k*mat_size];
  memset ( evecbuff, 1, k*mat_size*sizeof ( double ) );
  int ritz_size = ( computed_eigenpairs < 3 ? 2 * computed_eigenpairs : computed_eigenpairs + 6 );
  int workspace_size = ritz_size * ( ritz_size + 10 );
  double* workspace = new double[workspace_size];
  workspace[0] = tolerance;

  if ( verbose )
    cerr << "Initialization ready ... Starting TRLAN" << endl;
  // call lanczos iteration of trlan
  int kint = k;
  trlan77_ ( op, ipar, &mat_size, &kint, evalbuff, evecbuff, &mat_size, workspace, &workspace_size );

  if ( ipar[0] != 0 )
  {
    cerr << "EigValuesTRLAN: Error occured by calling TRLAN Eigenvalue Computation." << endl;
    cerr << "EigValuesTRLAN: " << ipar[3] << " converged eigenvectors" << endl;
  }
  if ( verbose )
    cerr << "TRLAN ready" << endl;

  // copy eigenvectors in evecbuff to vector
  eigenvectors.resize ( mat_size, k );
  eigenvalues.resize ( k );
  if ( verbose )
    cerr << "Store results" << endl;

  /** write back all eigenvalues and eigenvectors */
  if ( magnitude < 0 )
  {
    for ( uint i = 0;i < k;i++ )
      for ( uint j = 0;j < ( uint ) mat_size;j++ )
        eigenvectors ( j, i ) = evecbuff[i*mat_size+j];
    for ( uint i = 0;i < k;i++ )
      eigenvalues[i] = evalbuff[i];
  }
  else
  {
    for ( uint i = 0;i < k;i++ )
      for ( uint j = 0;j < ( uint ) mat_size;j++ )
        eigenvectors ( j, k - i - 1 ) = evecbuff[i*mat_size+j];
    for ( uint i = 0;i < k;i++ )
      eigenvalues[i] = evalbuff[k-i-1];
  }

  if ( verbose )
    cerr << "Clean up" << endl;

  /** clean up memory */
  delete[] workspace;
  delete[] evalbuff;
  delete[] evecbuff;

  if ( verbose )
    cerr << "Clean up done" << endl;
#endif
}
