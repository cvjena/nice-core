/** 
* @file testCholeskySpeed.cpp
* @brief test LinAl cholesky decomposition
* @author Erik Rodner
* @date 01/06/2010

*/

#include "core/basics/numerictools.h"
#include "core/vector/Algorithms.h"
#include "core/basics/Timer.h"

extern "C" {
	  IppStatus ippmCholeskyDecomp_m_64f(const Ipp64f* pSrc, int srcStride1, int
	  			srcStride2, Ipp64f* pDst, int dstStride1, int dstStride2, int widthHeight);


}

using namespace std;
using namespace NICE;

double getInvError ( const Matrix & A, const Matrix & Ainv )
{
	Matrix idapprox = Ainv*A;
	idapprox.addIdentity(-1.0);
	double error = idapprox.frobeniusNorm();
	cerr << "error = " << error << endl;

	return error;
}

/** 
    
    test LinAl cholesky decomposition 
    
*/
int main (int argc, char **argv)
{   
    std::set_terminate(__gnu_cxx::__verbose_terminate_handler);

    int size = 500;
	if ( argc > 1 )
		size = atoi(argv[1]);

	cerr << "creating positive-definite random matrix with size " << size << endl;
	Matrix B ( size, size );
	initRand();
	for ( int i = 0 ; i < size; i++ )
		for ( int j = 0 ; j < size; j++ )
			B(i,j) = randDouble();
    
	Matrix A = B * B.transpose();

	Timer timer;

	/************* LinAl Cholesky (broken !!) ****/

#ifdef NICE_USELIB_LINAL
	/*********** lapack direct ************/
	{
		timer.start();
		cerr << "cholesky decomposition (core/large scale/lapack)" << endl;
		Matrix G;
		choleskyDecompLargeScale ( A, G );
		timer.stop();

		if ( size < 11 )
			cerr << G << endl;

		cerr << "--- IPP or LAPACK/core(large-scale) chol: " << timer.getLast() << endl;
		cerr << "cholesky inversion" << endl;
		timer.start();
		Matrix Ainv;
		choleskyInvertLargeScale ( G, Ainv ); 
		timer.stop();
		cerr << "cholesky inversion finished." << endl;
		
		cerr << "--- LAPACK/core(large-scale) cholinv: " << timer.getLast() << endl;

		getInvError ( A, Ainv );

	}
#endif


	{
		/************ NICE Cholesky *********/
		timer.start();
		cerr << "cholesky decomposition (core)" << endl;
		Matrix G;
		Matrix Ainv;
		choleskyDecomp ( A, G );
		timer.stop();
		
		cerr << "--- core chol: " << timer.getLast() << endl;

		if ( size < 11 )
			cerr << G << endl;

		cerr << "cholesky inversion" << endl;
		timer.start();
		choleskyInvert ( G, Ainv ); 
		timer.stop();
		cerr << "cholesky inversion finished." << endl;
		
		cerr << "--- core cholinv: " << timer.getLast() << endl;

		getInvError ( A, Ainv );
	}

	{
#ifdef NICE_USELIB_IPP
		/********** IPP cholesky *********/
		cerr << "cholesky decomposition (IPP)" << endl;
		timer.start();
		Matrix G (A.rows(), A.cols());

		int stride = sizeof(double);
		int stride_m = A.rows() * sizeof(double);
		IppStatus ippStatus = ippmCholeskyDecomp_m_64f( (Ipp64f *)A.getDataPointer(), stride_m, stride, 
			(Ipp64f *)G.getDataPointer(), stride_m, stride, A.rows());
		timer.stop();
		cerr << "--- IPP chol: " << timer.getLast() << endl;

		if ( ippStatus != ippStsOk ) 
			fthrow(Exception, ippGetStatusString(ippStatus));

		{
			timer.start();
			Matrix Gcorrected ( G.transpose() );
			for ( int i = 0 ; i < size ; i++ )
				Gcorrected(i,i) = 1.0 / Gcorrected(i,i);

			if ( size < 11 )
			{
				cerr << Gcorrected << endl;
			}
			
			Matrix Ainv (A.rows(), A.cols());
			choleskyInvertLargeScale ( Gcorrected, Ainv );
			timer.stop();
			
			cerr << "--- IPP->LargeScale(cholinv): " << timer.getLast() << endl;

			getInvError ( A, Ainv );
		}
		
		{ 
			timer.start();
			Matrix Ainv (A.rows(), A.cols());
			Matrix id ( A.rows(), A.cols() );
			id.setIdentity();

			ippStatus = ippmCholeskyBackSubst_mva_64f( (Ipp64f *)G.getDataPointer(), stride_m,
					stride, (Ipp64f *)id.getDataPointer(), stride_m, stride, Ainv.getDataPointer(), stride_m, stride,
					A.rows(), A.rows() );

			if ( ippStatus != ippStsOk )
				fthrow(Exception, ippGetStatusString(ippStatus));

			timer.stop();

			cerr << "--- IPP cholinv: " << timer.getLast() << endl;

			getInvError (A, Ainv);
		}
#endif
	}

	// to slow :)
#if 0
    {
		/*********** NICE invert () *******/

		timer.start();
		cerr << "matrix inversion (core/IPP)" << endl;
		Matrix Ainv;
		Ainv = invert ( A );
		timer.stop();
		cerr << "--- IPP/core invert: " << timer.getLast() << endl;

		getInvError (A, Ainv);
	}
#endif

#ifdef NICE_USELIB_LINAL
	/************* LinAl LU **************/
	{
		timer.start();

		Matrix inplaceLinAl ( A );
		LinAl::MatrixCF<double> Glinal ( inplaceLinAl.linal() );
		cerr << "LU decomposition and inversion (LinAl)" << endl;
		Glinal.LUinvert();
		timer.stop ();
		
		cerr << "--- LinAL/LUinvert cholinv: " << timer.getLast() << endl;

		getInvError ( A, inplaceLinAl );
	}
#endif



    return 0;
}
