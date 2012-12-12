/** 
* @file testILSConjugateGradientsLanczos.cpp
* @author Paul Bodesheim
* @date  23/01/2012
* @brief test routine for Iterative Linear Solver: Conjugate Gradients Method (CGM) using Lanczos vectors
*/

#include "core/vector/MatrixT.h"
#include "core/vector/VectorT.h"
#include <stdio.h>
#include <ctime>
#include "iostream"
#include "core/basics/Exception.h"
#include "core/vector/Algorithms.h"
// #include "core/algebra/ILSConjugateGradients.h"
#include "core/algebra/GMStandard.h"
#include "core/algebra/ILSConjugateGradientsLanczos.h"


using namespace std;
using namespace NICE;

int main(int argc, char* argv[])
{
  
	int mySize = 20; // number of equations
	FILE * logfile;
	std::string logfilename;
	
	if ( argc < 2 )
	  logfilename = "/home/bodesheim/testILS-CGM-Lanczos.log";
	else
	  logfilename = argv[1];
	
	logfile = fopen(logfilename.c_str(), "w");
	
	// generate matrix A
	Matrix A(mySize,mySize,0.0);
	fprintf(logfile, "A:\n");
	for (uint i = 0; i < A.rows(); i++)
	{
		for (uint j = 0; j < A.cols(); j++)
		{
			if ( j == i ) A(i,j) = (i+1)+(j+1);
			else {
			  
			    A(i,j) = sqrt((i+1)*(j+1));
			}

			fprintf(logfile, "%f  ",A(i,j));
		}
		fprintf(logfile, "\n");
	}
	
	// generate vector b (RHS of LS)
	Vector b(mySize,0.0);
	fprintf(logfile, "b:\n");
	for (uint i = 0; i < b.size(); i++)
	{	
	    b(i) = (i+1)*sqrt(i+1);
	    fprintf(logfile, "%f  ",b(i));
	}
	fprintf(logfile, "\n");
	
	// solve Ax = b
	Vector x(mySize,0.0);
	ILSConjugateGradientsLanczos cgm(true,mySize);
	
	//tic
	time_t  start = clock();
	cgm.solveLin(GMStandard(A),b,x);
	//toc
	float duration = (float) (clock() - start);
	std::cerr << "Time for solveLin: " << duration/CLOCKS_PER_SEC << std::endl;	

	fprintf(logfile, "x:\n");
	for (uint i = 0; i < x.size(); i++)
	{	
	    fprintf(logfile, "%f  ",x(i));
	}
	fprintf(logfile, "\n");
	
  // check result
  Vector Ax(mySize,0.0);
  Ax = A*x;
  fprintf(logfile, "A*x:\n");
  for (uint i = 0; i < Ax.size(); i++)
  { 
      fprintf(logfile, "%f  ",Ax(i));
  }
  fprintf(logfile, "\n"); 	
	
	fclose(logfile);
	
	return 0;
}



// Algorithm without using class ILSConjugateGradientsLanczos works for 10x10 matrix A

// int main(int argc, char* argv[])
// {
//   
// 	int mySize = 10; // number of equations
// 	FILE * logfile;
// 	std::string logfilename;
// 	
// 	if ( argc < 2 )
// 	  logfilename = "/home/bodesheim/testILS-CGM-Lanczos.log";
// 	else
// 	  logfilename = argv[1];
// 	
// 	logfile = fopen(logfilename.c_str(), "w");
// 	
// 	// generate matrix A
// 	Matrix A(mySize,mySize,0.0);
// 	fprintf(logfile, "A:\n");
// 	for (uint i = 0; i < A.rows(); i++)
// 	{
// 		for (uint j = 0; j < A.cols(); j++)
// 		{
// 			if ( j == i ) A(i,j) = (i+1)+(j+1);
// 			else {
// 			  
// 			    A(i,j) = sqrt((i+1)*(j+1));
// 			}
// 
// 			fprintf(logfile, "%f  ",A(i,j));
// 		}
// 		fprintf(logfile, "\n");
// 	}
// 	
// 	// generate vector b (RHS of LS)
// 	Vector b(mySize,0.0);
// 	fprintf(logfile, "b:\n");
// 	for (uint i = 0; i < b.size(); i++)
// 	{	
// 	    b(i) = (i+1)*sqrt(i+1);
// 	    fprintf(logfile, "%f  ",b(i));
// 	}
// 	fprintf(logfile, "\n");
// 	
// 	double beta1 = b.normL2();
// 	fprintf(logfile, "norm of b: %f\n\n",beta1);
// 	
// 	// init some helpers
// 	Matrix Tmatrix(mySize,mySize,0.0);
// 	Matrix Vmatrix(mySize,mySize,0.0);
// 	Matrix Cmatrix(mySize,mySize,0.0);
// 	Matrix Dmatrix(mySize,mySize,0.0);
// 	Matrix Lmatrix(mySize,mySize,0.0);
// 	Vector p(mySize,0.0);
// 	
// 	Vector Av(mySize,0.0);
// 	Vector v_new(mySize,0.0);
// 	Vector v_old(mySize,0.0);
// 	Vector v_older(mySize,0.0);
// 	Vector c_new(mySize,0.0);
// 	Vector c_old(mySize,0.0);
// 	
// 	Vector x(mySize,0.0);
// 	
// 	double d_new = 0;
// 	double d_old = 0;
// 	double l_new = 0;
// 	double p_new = 0;
// 	double p_old = 0;
// 	double alpha = 0;
// 	double beta = 0;
// 	
// 	for (uint iter = 0; iter < Tmatrix.rows(); iter++)
// 	{
// 	  
// 	      if ( iter == 0 ) {
// 		
// 		v_new = (1/beta1)*b; // init v1
// 		Av.multiply(A,v_new);
// 		alpha = v_new.scalarProduct(Av); 
// 		d_new=alpha;
// 		p_new = beta1/d_new;
// 
// 		Tmatrix(iter,iter)=alpha;
// 
// 	      } else {
// 		
// 		v_new = Av - (alpha*v_old) - (beta*v_older);
// 		
// 		beta = v_new.normL2();
// 		v_new.normalizeL2();
// 		
// 		Av.multiply(A,v_new);
// 		alpha = v_new.scalarProduct(Av);
// 		
// 		l_new = beta/sqrt(d_old);
// 		d_new = alpha-(l_new*l_new);
// 		
// 		l_new/=sqrt(d_old);
// 		
// 		p_new = -p_old*l_new*d_old/d_new;
// 		
// 		Tmatrix(iter,iter-1)=beta;
// 		Tmatrix(iter-1,iter)=beta;
// 		Tmatrix(iter,iter)=alpha;
// 		Lmatrix(iter,iter-1)=l_new;
// 	      }
// 	      
// 	      c_new = v_new - (l_new*c_old);
// 
// 	      x+=(p_new*c_new);
// 	      
// 	      fprintf(logfile, "\n x after iteration %d:\n",iter+1);
// 	      for (uint i = 0; i < x.size(); i++)
// 	      {
// 		      fprintf(logfile, "%f  ",x(i));
// 	      }
// 	
// 	      Dmatrix(iter,iter)=d_new;
// 	      Lmatrix(iter,iter)=1;
// 	      Vmatrix.getColumnRef(iter) = v_new;
// 	      Cmatrix.getColumnRef(iter) = c_new;
// 	      p(iter)=p_new;
// 	      
// 	      d_old = d_new;
// 	      p_old = p_new;
// 	      v_older = v_old;
// 	      v_old = v_new;
// 	      c_old = c_new;
// 	}
// 
// 	fprintf(logfile, "\n\n Result of CGM w/o Lanczos: \n");
// 	ILSConjugateGradients cgm(true,x.size());
// 	Vector xCGM (x.size(),0.0);
// 	cgm.solveLin(GMStandard(A),b,xCGM);
// 	for (uint i = 0; i < xCGM.size(); i++)
// 	{
// 	      fprintf(logfile, "%f  ",xCGM(i));
// 	}
// 	fprintf(logfile, "\n");
// 	
// 	fprintf(logfile, "\n\n Result using QR decomp: \n");
// 	solveLinearEquationQR(A, b, xCGM);
// 	for (uint i = 0; i < xCGM.size(); i++)
// 	{
// 	      fprintf(logfile, "%f  ",xCGM(i));
// 	}
// 	fprintf(logfile, "\n");	
// 
// 	fprintf(logfile, "\n\n Check Iterative Results: \n");
// 	Vector Cp(p.size(),0.0);
// 	Cp.multiply(Cmatrix,p);
// 	fprintf(logfile, "\nC*p:\n");
// 	for (uint i = 0; i < Cp.size(); i++)
// 	{
// 		fprintf(logfile, "%f  ",Cp(i));
// 	}
// 	fprintf(logfile, "\n");
// 	
// 	fprintf(logfile, "\ntransposed Vmatrix:\n");
// 	for (uint i = 0; i < Vmatrix.rows(); i++)
// 	{
// 		for (uint j = 0; j < Vmatrix.cols(); j++)
// 		{
// 			fprintf(logfile, "%f  ",Vmatrix(j,i));
// 		}
// 		fprintf(logfile, "\n");
// 	}	
// 	
// 	fprintf(logfile, "\nL times C^T:\n");
// 	Matrix LC (Lmatrix.rows(),Cmatrix.rows(),0.0);
// 	LC.multiply(Lmatrix,Cmatrix.transpose());
// 	for (uint i = 0; i < LC.rows(); i++)
// 	{
// 		for (uint j = 0; j < LC.cols(); j++)
// 		{
// 			fprintf(logfile, "%f  ",LC(i,j));
// 		}
// 		fprintf(logfile, "\n");
// 	}	
// 	
// 	fprintf(logfile, "\n\n Check Cholesky of T: \n");
// 	fprintf(logfile, "Tmatrix:\n");
// 	for (uint i = 0; i < Tmatrix.rows(); i++)
// 	{
// 		for (uint j = 0; j < Tmatrix.cols(); j++)
// 		{
// 			fprintf(logfile, "%f  ",Tmatrix(i,j));
// 		}
// 		fprintf(logfile, "\n");
// 	}	
// 	
// 	fprintf(logfile, "\nDmatrix:\n");
// 	for (uint i = 0; i < Dmatrix.rows(); i++)
// 	{
// 		for (uint j = 0; j < Dmatrix.cols(); j++)
// 		{
// 			fprintf(logfile, "%f  ",Dmatrix(i,j));
// 		}
// 		fprintf(logfile, "\n");
// 	}
// 	
// 	fprintf(logfile, "\nLmatrix:\n");
// 	for (uint i = 0; i < Lmatrix.rows(); i++)
// 	{
// 		for (uint j = 0; j < Lmatrix.cols(); j++)
// 		{
// 			fprintf(logfile, "%f  ",Lmatrix(i,j));
// 		}
// 		fprintf(logfile, "\n");
// 	}
// 	
// 	Matrix LD(mySize,mySize,0.0);
// 	Matrix LDL(mySize,mySize,0.0);
// 	LD.multiply(Lmatrix,Dmatrix);
// 	LDL.multiply(LD,Lmatrix.transpose());
// 	
// 	fprintf(logfile, "\nLDL:\n");
// 	for (uint i = 0; i < LDL.rows(); i++)
// 	{
// 		for (uint j = 0; j < LDL.cols(); j++)
// 		{
// 			fprintf(logfile, "%f  ",LDL(i,j));
// 		}
// 		fprintf(logfile, "\n");
// 	}
// 	
// 	Vector LDp;
// 	LDp.multiply(LD,p);
// 	
// 	fprintf(logfile, "\nL*D*p:\n");
// 	for (uint i = 0; i < LDp.size(); i++)
// 	{
// 		fprintf(logfile, "%f  ",LDp(i));
// 	}	
// 	
// 	
// 	fclose(logfile);
// 	
// 	return 0;
// }


// CHOLESKY FACTORIZATION OF TRIDIAGONAL MATRIX T WORKS:

// int main(int argc, char* argv[])
// {
//   
// 	FILE * logfile;
// 	std::string logfilename;
// 	
// 	if ( argc < 2 )
// 	  logfilename = "/home/bodesheim/testILS-CGM-Lanczos.log";
// 	else
// 	  logfilename = argv[1];
// 	
// 	logfile = fopen(logfilename.c_str(), "w");
// 	
// 	Matrix Tmatrix(5,5,0.0);
// 	fprintf(logfile, "Tmatrix:\n");
// 	for (uint i = 0; i < Tmatrix.rows(); i++)
// 	{
// 		for (uint j = 0; j < Tmatrix.cols(); j++)
// 		{
// 			if ( j == i ) Tmatrix(i,j) = (i+1)+(j+1);
// 			else if ( j == (i+1) ) {
// 			  
// 			    Tmatrix(i,j) = sqrt((i+1)*(j+1));
// 			    Tmatrix(j,i) = Tmatrix(i,j);
// 			}
// 
// 			fprintf(logfile, "%f  ",Tmatrix(i,j));
// 		}
// 		fprintf(logfile, "\n");
// 	}
// 	
// 	Matrix Dmatrix(5,5,0.0);
// 	Matrix Lmatrix(5,5,0.0);
// 	Vector p(5,0.0);
// 	
// 	double beta = 2.4;
// 	double d_new = 0;
// 	double d_old = 0;
// 	double l_new = 0;
// 	double p_new = 0;
// 	double p_old = 0;
// 	
// 	for (uint iter = 0; iter < Tmatrix.rows(); iter++)
// 	{
// 	  
// 	      if ( iter == 0 ) {
// 		
// 		d_new = Tmatrix(iter,iter);
// 		l_new = 1;
// 		p_new = beta/d_new;
// 		
// 	      } else {
// 		
// 		l_new = Tmatrix(iter,iter-1)/sqrt(d_old);
// 		d_new = Tmatrix(iter,iter)-(l_new*l_new);
// 		
// 		l_new/=sqrt(d_old);
// 		Lmatrix(iter,iter-1)=l_new;
// 		
// 		p_new = -p_old*l_new*d_old/d_new;
// 
// 	      }
// 	      
// 	      Dmatrix(iter,iter)=d_new;
// 	      Lmatrix(iter,iter)=1;
// 	      p(iter)=p_new;
// 	      
// 	      d_old = d_new;
// 	      p_old = p_new;
// 	}
// 	
// 	fprintf(logfile, "Dmatrix:\n");
// 	for (uint i = 0; i < Dmatrix.rows(); i++)
// 	{
// 		for (uint j = 0; j < Dmatrix.cols(); j++)
// 		{
// 			fprintf(logfile, "%f  ",Dmatrix(i,j));
// 		}
// 		fprintf(logfile, "\n");
// 	}
// 	
// 	fprintf(logfile, "Lmatrix:\n");
// 	for (uint i = 0; i < Lmatrix.rows(); i++)
// 	{
// 		for (uint j = 0; j < Lmatrix.cols(); j++)
// 		{
// 			fprintf(logfile, "%f  ",Lmatrix(i,j));
// 		}
// 		fprintf(logfile, "\n");
// 	}
// 	
// 	Matrix LD(5,5,0.0);
// 	Matrix LDL(5,5,0.0);
// 	LD.multiply(Lmatrix,Dmatrix);
// 	LDL.multiply(LD,Lmatrix.transpose());
// 	
// 	fprintf(logfile, "LDL:\n");
// 	for (uint i = 0; i < LDL.rows(); i++)
// 	{
// 		for (uint j = 0; j < LDL.cols(); j++)
// 		{
// 			fprintf(logfile, "%f  ",LDL(i,j));
// 		}
// 		fprintf(logfile, "\n");
// 	}
// 	
// 	Vector result;
// 	result.multiply(LD,p);
// 	
// 	fprintf(logfile, "result:\n");
// 	for (uint i = 0; i < result.size(); i++)
// 	{
// 		fprintf(logfile, "%f  ",result(i));
// 	}	
// 	
// 	
// 	fclose(logfile);
// 	
// 	return 0;
// }

