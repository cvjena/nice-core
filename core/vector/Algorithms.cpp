#include "Algorithms.h"

#ifdef NICE_USELIB_LINAL
// direct access to lapack function (not forwarded in LinAl)
extern "C" {
	void dtrtrs_ ( char *uplo, char *trans, char *diag, int *n, int *nrhs, 
		const double *a, int *lda, double *b, int *ldb, int *info );
}
#endif

namespace NICE {

void choleskyDecompLargeScale ( const Matrix & A, Matrix & G, bool resetUpperTriangle )
{
	if ( A.rows() != A.cols() )
	  fthrow(Exception, "Matrix is not quadratic !");

	int size = A.rows();

	G.resize ( size, size );

	// IPP is faster for cholesky decomposition, but lapack
	// is faster for back substitution in combination with choleskyInvert
	// For a comparision: cf. testCholeskySpeed
#ifdef NICE_USELIB_IPP
	int stride = sizeof(double);
	int stride_m = size * sizeof(double);
	// the following function is undocumented in 5.3 but documented in 6.1
	IppStatus ippStatus = ippmCholeskyDecomp_m( A.getDataPointer(), stride_m, stride, 
			G.getDataPointer(), stride_m, stride, size);
	if ( ippStatus != ippStsOk ) 
			fthrow(Exception, ippGetStatusString(ippStatus));
	
	// we have now to correct this matrix -> transpose and invert diagonal elements
	// funny definition in IPP
	G.transposeInplace();
	for ( int i = 0 ; i < size ; i++ )
		G(i,i) = 1.0 / G(i,i);

	if ( resetUpperTriangle )
		for ( uint i = 0 ; i < (uint)size; i++ )
			for ( uint j = i+1 ; j < (uint)size ; j++ )
				G(i,j) = 0;
#else
#ifdef NICE_USELIB_LINAL
  // Lapack routines
	G = A;

	char uplo='L';
	int lda=size;
	int info;

	dpotrf_ ( &uplo, &size, G.getDataPointer(), &lda, &info );

	if ( info != 0 )
		fthrow(Exception, "Lapack cholesky decomposition failed: error=" << info << "." );

	if ( resetUpperTriangle )
		for ( uint i = 0 ; i < (uint)size; i++ )
			for ( uint j = i+1 ; j < (uint)size ; j++ )
				G(i,j) = 0;
#else
  #ifndef CHOLESKYLINAL_WARNING
	#warning "LinAl is not installed: choleskyDecompLargeScale will not be optimized."  
  #define CHOLESKYLINAL_WARNING
  #endif
	choleskyDecomp ( A, G, resetUpperTriangle );
#endif
#endif
}

void choleskyInvertLargeScale ( const Matrix & G, Matrix & Ainv )
{
	int size = G.rows();
	Ainv.resize ( size, size );
	Ainv.setIdentity();
	choleskySolveMatrixLargeScale ( G, Ainv ); 
}

void choleskySolveMatrixLargeScale ( const Matrix & G, Matrix & B )
{
#ifdef NICE_USELIB_LINAL
	if (G.rows() != G.cols())// || (B.rows() != B.cols()) )
	  fthrow(Exception, "Matrix is not quadratic !");
	if ( G.rows() != B.rows() )
	  fthrow(Exception, "Matrices sizes do not fit together.");

	int sizeG = G.rows();
        int sizeB = B.cols();
	int ldb = sizeG;
	char trans = 'N';
	char diag = 'N';
	char uplo='L';
	int lda=sizeG;
	int info;

	dtrtrs_ ( &uplo, &trans, &diag, &sizeG, &sizeB, G.getDataPointer(), &lda, 
			B.getDataPointer(), &ldb, &info );

	trans = 'T';
	dtrtrs_ ( &uplo, &trans, &diag, &sizeG, &sizeB, G.getDataPointer(), &lda, 
		B.getDataPointer(), &ldb, &info );
#else
  #ifndef CHOLESKYLINAL_WARNING
	#warning "LinAl is not installed: choleskyInvertLargeScale will not be optimized."
  #define CHOLESKYLINAL_WARNING
  #endif
	choleskyInvert ( G, B );
#endif
}

void triangleSolveMatrix ( const Matrix & G, Matrix & B, bool transposedMatrix )
{
#ifdef NICE_USELIB_LINAL
	if ( (G.rows() != G.cols()) || (B.rows() != B.cols()) )
	  fthrow(Exception, "Matrix is not quadratic !");
	if ( G.rows() != B.rows() )
	  fthrow(Exception, "Matrices sizes do not fit together.");

	int size = G.rows();
	int ldb = size;
	char trans = (transposedMatrix) ? 'T' : 'N';
	char diag = 'N';
	char uplo='L';
	int lda=size;
	int info;

	dtrtrs_ ( &uplo, &trans, &diag, &size, &size, G.getDataPointer(), &lda, 
			B.getDataPointer(), &ldb, &info );
#else
	fthrow(Exception, "LinAl is not installed: triangleSolveMatrix is not available.");
#endif
}

void triangleSolve ( const Matrix & G, const Vector & b, Vector & x, bool transposedMatrix )
{
#ifdef NICE_USELIB_LINAL
	if ( (G.rows() != G.cols()) )
	  fthrow(Exception, "Matrix is not quadratic !");
	if ( G.rows() != b.size() )
	  fthrow(Exception, "Matrix and vector sizes do not fit together.");

	int size = G.rows();
	int ldb = size;
	char trans = (transposedMatrix) ? 'T' : 'N';
	char diag = 'N';
	char uplo='L';
	int lda=size;
	int info;
	int sizeB = 1;
	x.resize ( b.size() );
	x = b;

	dtrtrs_ ( &uplo, &trans, &diag, &size, &sizeB, G.getDataPointer(), &lda, 
			x.getDataPointer(), &ldb, &info );
#else
	fthrow(Exception, "LinAl is not installed: triangleSolveMatrix is not available.");
#endif
}

void choleskySolveLargeScale ( const Matrix & G, const Vector & b, Vector & x )
{
	if ( G.rows() != G.cols() )
	  fthrow(Exception, "Matrix is not quadratic !");
	if ( b.size() != G.cols() )
		fthrow(Exception, "Matrix or right hand side of the linear system has wrong dimensions !");

	x.resize ( b.size() );
	x = b;

#ifdef NICE_USELIB_LINAL
	int size = G.rows();
	int ldb = size;
	char trans = 'N';
	char diag = 'N';
	char uplo='L';
	int lda=size;
	int info;
	int sizeSingle = 1;

	dtrtrs_ ( &uplo, &trans, &diag, &size, &sizeSingle, G.getDataPointer(), &lda, 
			x.getDataPointer(), &ldb, &info );

	if ( info != 0 )
		fthrow(Exception, "dtrtrs_ returned with error code (invalid cholesky matrix?)" << info );

	trans = 'T';
	dtrtrs_ ( &uplo, &trans, &diag, &size, &sizeSingle, G.getDataPointer(), &lda, 
		x.getDataPointer(), &ldb, &info );
	
	if ( info != 0 )
		fthrow(Exception, "dtrtrs_ returned with error code (invalid cholesky matrix?)" << info );

#else
#ifdef NICE_USELIB_IPP
	int stride = sizeof(double);
	int stride_m = G.rows() * sizeof(double);
	// this is nasty
	Matrix Gcorrected ( G );
	Gcorrected.transposeInplace();

	for ( uint i = 0 ; i < G.rows() ; i++ )
		Gcorrected(i,i) = 1.0 / Gcorrected(i,i);

	IppStatus ippStatus = ippmCholeskyBackSubst_mv( Gcorrected.getDataPointer(), stride_m,
					stride, b.getDataPointer(), stride, x.getDataPointer(), stride, G.rows() );
	if ( ippStatus != ippStsOk ) 
			fthrow(Exception, ippGetStatusString(ippStatus));

#else
  #ifndef CHOLESKYLINAL_WARNING
	#warning "LinAl is not installed: choleskyInvertLargeScale will not be optimized."
  #define CHOLESKYLINAL_WARNING
  #endif
	choleskySolve ( G, b, x );
#endif
#endif
}

}
