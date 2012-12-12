/** 
* @file testILSMinResLanczos.cpp
* @author Paul Bodesheim
* @date  23/01/2012
* @brief test routine for Iterative Linear Solver: minimum residual method (MINRES) using Lanczos vectors
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
#include "core/algebra/ILSMinResLanczos.h"


using namespace std;
using namespace NICE;

int main(int argc, char* argv[])
{
  
	int mySize = 20; // number of equations
	FILE * logfile;
	std::string logfilename;
	
	if ( argc < 2 )
	  logfilename = "/home/bodesheim/testILS-MinRes-Lanczos.log";
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
	ILSMinResLanczos ils(true,mySize);
	
	//tic
	time_t  start = clock();
	ils.solveLin(GMStandard(A),b,x);
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
//   int mySize = 10; // number of equations
//   FILE * logfile;
//   std::string logfilename;
//   
//   if ( argc < 2 )
//     logfilename = "/home/bodesheim/testILS-MinRes-Lanczos.log";
//   else
//     logfilename = argv[1];
//   
//   logfile = fopen(logfilename.c_str(), "w");
//   
//   // generate matrix A
//   Matrix A(mySize,mySize,0.0);
//   fprintf(logfile, "A:\n");
//   for (uint i = 0; i < A.rows(); i++)
//   {
//     for (uint j = 0; j < A.cols(); j++)
//     {
//       if ( j == i ) A(i,j) = (i+1)+(j+1);
//       else {
//         
//           A(i,j) = sqrt((i+1)*(j+1));
//       }
// 
//       fprintf(logfile, "%f  ",A(i,j));
//     }
//     fprintf(logfile, "\n");
//   }
//   
//   // generate vector b (RHS of LS)
//   Vector b(mySize,0.0);
//   fprintf(logfile, "b:\n");
//   for (uint i = 0; i < b.size(); i++)
//   { 
//       b(i) = (i+1)*sqrt(i+1);
//       fprintf(logfile, "%f  ",b(i));
//   }
//   fprintf(logfile, "\n");
//   
//   // solve Ax = b
//   Vector x(mySize,0.0);
//   ILSMinResLanczos ils(true,mySize);
//   
//   //tic
//   time_t  start = clock();
// //  ils.solveLin(GMStandard(A),b,x);
//   
//               uint maxIterations = (uint) mySize;
//               double minDelta = 1e-7;
//               bool verbose = true;
//               GMStandard gm(A);
//   
//               Matrix T(mySize,mySize,0.0);
//               Matrix L(mySize,mySize,0.0);
//               Matrix Q(mySize,mySize,0.0);
//               Matrix Q_tmp(mySize,mySize,0.0);
//               
//               for (int kk = 0; kk < mySize; kk++)
//                 Q(kk,kk) = 1.0;
//   
//               if ( b.size() != gm.rows() ) {
//                 fthrow(Exception, "Size of vector b (" << b.size() << ") mismatches with the size of the given GenericMatrix (" << gm.rows() << ").");
//               }
// 
//               if ( x.size() != gm.cols() )
//               {
//                 x.resize(gm.cols());
//                 x.set(0.0); // bad initial solution, but whatever
//               }
// 
//             //   if ( verbose ) cerr << "initial solution: " << x << endl;
// 
//               // SYMMLQ-Method based on Lanczos vectors: implementation based on the following:
//               //
//               // C.C. Paige and M.A. Saunders: "Solution of sparse indefinite systems of linear equations". SIAM Journal on Numerical Analysis, p. 617--629, vol. 12, no. 4, 1975
//               // 
//               // http://www.netlib.org/templates/templates.pdf
//               //
//               
//               // declare some helpers
//               double gamma = 0;
//               double gamma_bar = 0;
//               double alpha = 0; // alpha_j = v_j^T * A * v_j for new Lanczos vector v_j
//               double beta = b.normL2(); // beta_1 = norm(b), in general beta_j = norm(v_j) for new Lanczos vector v_j
//               double beta_next = 0; // beta_{j+1}
//               double c_new = 0;
//               double c_old = -1;
//               double s_new = 0;
//               double s_old = 0;
//               double z_new = 0;
//               double z_old = 0;
//               double z_older = 0;
//               double delta_new = 0;
//               double epsilon_new = 0;
//               double epsilon_next = 0;
// 
//               // init some helping vectors
//               Vector Av(b.size(),0.0); // Av = A * v_j
//               Vector Ac(b.size(),0.0); // Ac = A * c_j
//             //   Vector r(b.size(),0.0); // current residual
//               Vector *v_new = new Vector(b.size(),0.0); // new Lanczos vector v_j
//               Vector *v_old = 0; // Lanczos vector of the iteration before: v_{j-1}
//               Vector *v_next = new Vector(b.size(),0.0); // Lanczos vector of the next iteration: v_{j+1}
//               Vector *w_new = new Vector(b.size(),0.0); 
//               Vector *w_bar = new Vector(b.size(),0.0); 
//               Vector x_L (b.size(),0.0); 
//               Vector x_C (b.size(),0.0); 
//               
//               // first iteration + initialization, where b will be used as the first Lanczos vector
//               *v_new = (1/beta)*b; // init v_1, v_1 = b / norm(b)
//               gm.multiply(Av,*v_new); // Av = A * v_1
//               alpha = v_new->scalarProduct(Av); // alpha_1 = v_1^T * A * v_1  
//               gamma_bar = alpha; // (gamma_bar_1 is equal to alpha_1 in ILSConjugateGradientsLanczos)
//               *v_next = Av - (alpha*(*v_new));
//               beta_next = v_next->normL2();
//               v_next->normalizeL2();
//               
//               gamma = sqrt( (gamma_bar*gamma_bar) + (beta_next*beta_next) );
//               c_new = gamma_bar/gamma;
//               s_new = beta_next/gamma;
//               
//               z_new = beta/gamma;
//               
//               *w_bar = *v_new;
//               
//               *w_new = c_new*(*w_bar) + s_new*(*v_next);
//               *w_bar = s_new*(*w_bar) - c_new*(*v_next);
//               
//               x_L = z_new*(*w_new); // first approximation of x
//               
//               double delta = fabs(z_new) * w_new->normL2();
//               if ( verbose ) {
//                 cerr << "ILSMinResLanczos: iteration 1 / " << maxIterations << endl;
//                 if ( x.size() <= 20 )
//                   cerr << "ILSMinResLanczos: current solution x_L: " << x_L << endl;
//                 cerr << "ILSMinResLanczos: delta = " << delta << endl;
//             //     cerr << "ILSMinResLanczos: residual = " << r.scalarProduct(r) << endl;
//               }
//               
//               T(0,0) = alpha;
//               L(0,0) = gamma;
//               
//               // start with second iteration
//               uint j = 2;
//               while (j <= maxIterations )
//               {
//               
//                 // prepare next iteration
//                 if ( v_old == 0 ) v_old = v_new;
//                 else {
//                   
//                   delete v_old;
//                   v_old = v_new;
//                 }
//                 v_new = v_next;
//                 v_next = new Vector(b.size(),0.0);
//                 beta = beta_next;
//                 z_older = z_old;
//                 z_old = z_new;
//                 s_old = s_new;
//                 epsilon_new = epsilon_next;
//                 
//                 gm.multiply(Av,*v_new);
//                 alpha = v_new->scalarProduct(Av);
//                 *v_next = Av - (alpha*(*v_new)) - (beta*(*v_old));
//                 beta_next = v_next->normL2();
//                 v_next->normalizeL2();
//                 
//                 gamma_bar = -c_old*s_new*beta - c_new*alpha;
//                 delta_new = -c_old*c_new*beta + s_new*alpha;
// /*                epsilon_new = s_old*beta;*/
//                 c_old = c_new;
//                 
//                 gamma = sqrt( (gamma_bar*gamma_bar) + (beta_next*beta_next) );
//                 c_new = gamma_bar/gamma;
//                 s_new = beta_next/gamma;  
//                 
//                 z_new = - (delta_new*z_old + epsilon_new*z_older)/gamma;
//                 epsilon_next = s_old*beta_next;
// 
//                 // NOTE this update step is necessary before computing the new w_bar !!
//                 x_C = x_L + (z_new/c_new)*(*w_bar); // update x
// 
//                 *w_new = c_new*(*w_bar) + s_new*(*v_next);
//                 *w_bar = s_new*(*w_bar) - c_new*(*v_next);
//               
//                 x_L += z_new*(*w_new); // update x
//                 
//                 Vector tmp;
//                 gm.multiply(tmp,x_C);
//                 Vector res ( b - tmp );
//                 double res_x_C = res.scalarProduct(res);
//                 
//                 gm.multiply(tmp,x_L);
//                 res = b - tmp;
//                 double res_x_L = res.scalarProduct(res);
//                 
//                 if ( res_x_L < res_x_C )
//                 {
//                   x = x_L;
//                   if ( verbose )
//                     cerr << "ILSMinResLanczos: x_L used with residual " << res_x_L << " < " << res_x_C << endl;
//                   
//                 } else 
//                 {
//                   
//                   x = x_C;
//                   if ( verbose )
//                     cerr << "ILSMinResLanczos: x_C used with residual " << res_x_C << " < " << res_x_L << endl;    
//                   
//                 }    
//                 
//                 
//                 if ( verbose ) {
//                   cerr << "ILSMinResLanczos: iteration " << j << " / " << maxIterations << endl;
//                   if ( x.size() <= 20 )
//                   {
//                     cerr << "ILSMinResLanczos: current solution x_L: " << x_L << endl;
//                     cerr << "ILSMinResLanczos: current solution x_C: " << x_C << endl;
//                   }
//                 }
//                 
//                 // store optimal x that produces smallest residual
//             //     if (res < res_min) {
//             //       
//             //       x_opt = x;
//             //       res_min = res;
//             //     }
// 
//                 // check convergence
//                 delta = fabs(z_new) * w_new->normL2();
//                 if ( verbose ) {
//                   cerr << "ILSMinResLanczos: delta = " << delta << endl;
//             //       cerr << "ILSMinResLanczos: residual = " << r.scalarProduct(r) << endl;
//                 }  
// 
//                 if ( delta < minDelta ) {
//                   if ( verbose )
//                     cerr << "ILSMinResLanczos: small delta" << endl;
//                   break;
//                 } 
//                 
//                 T(j-1,j-1) = alpha;
//                 T(j-2,j-1) = beta;
//                 T(j-1,j-2) = beta;
//                 
//                 L(j-1,j-1) = gamma;
//                 L(j-1,j-2) = delta_new;
//                 if (j >= 3) 
//                   L(j-1,j-3) = epsilon_new;
// 
//                 Q_tmp = 0.0;
//                 for (uint kk = 0; kk < mySize; kk++)
//                 {
//                   Q_tmp(kk,kk) = 1.0;                
//                   if (kk == j-2)
//                   {
//                     Q_tmp(kk,kk) = c_old;
//              
//                   } else if (kk == j-1)
//                   {
//                     Q_tmp(kk,kk) = -c_old;
//                     Q_tmp(kk-1,kk) = s_old;
//                     Q_tmp(kk,kk-1) = s_old;
//                   } 
//                   
//                 }
//                 
//                 Matrix tmpQ(Q);
//                 Q.multiply(tmpQ,Q_tmp);
//                 
//                 tmpQ.multiply(T,Q);
//                 
//                 fprintf(logfile, "\n iteration %i\n",j);
//                 fprintf(logfile, "T:\n");
//                 for (uint i = 0; i < T.rows(); i++)
//                 {
//                   for (uint j = 0; j < T.cols(); j++)
//                   {
//                     fprintf(logfile, "%f  ",T(i,j));
//                   }
//                   fprintf(logfile, "\n");
//                 }
//                 
//                 fprintf(logfile, "Q:\n");
//                 for (uint i = 0; i < Q.rows(); i++)
//                 {
//                   for (uint j = 0; j < Q.cols(); j++)
//                   {
//                     fprintf(logfile, "%f  ",Q(i,j));
//                   }
//                   fprintf(logfile, "\n");
//                 } 
//                 
//                 fprintf(logfile, "Q_tmp:\n");
//                 for (uint i = 0; i < Q_tmp.rows(); i++)
//                 {
//                   for (uint j = 0; j < Q_tmp.cols(); j++)
//                   {
//                     fprintf(logfile, "%f  ",Q_tmp(i,j));
//                   }
//                   fprintf(logfile, "\n");
//                 }  
//                 
//                 fprintf(logfile, "L:\n");
//                 for (uint i = 0; i < L.rows(); i++)
//                 {
//                   for (uint j = 0; j < L.cols(); j++)
//                   {
//                     fprintf(logfile, "%f  ",L(i,j));
//                   }
//                   fprintf(logfile, "\n");
//                 }
//                 
//                 fprintf(logfile, "T*Q:\n");
//                 for (uint i = 0; i < tmpQ.rows(); i++)
//                 {
//                   for (uint j = 0; j < tmpQ.cols(); j++)
//                   {
//                     fprintf(logfile, "%f  ",tmpQ(i,j));
//                   }
//                   fprintf(logfile, "\n");
//                 }                
//                 fprintf(logfile, "gamma_bar: %f\n",gamma_bar);
//                 
//                 j++;
//               }
//               
//               Vector tmp;
//               gm.multiply(tmp,x_C);
//               Vector res ( b - tmp );
//               double res_x_C = res.scalarProduct(res);
//               
//               gm.multiply(tmp,x_L);
//               res = b - tmp;
//               double res_x_L = res.scalarProduct(res);
//               
//               if ( res_x_L < res_x_C )
//               {
//                 x = x_L;
//                 if ( verbose )
//                   cerr << "ILSMinResLanczos: x_L used with residual " << res_x_L << " < " << res_x_C << endl;
//                 
//               } else 
//               {
//                 
//                 x = x_C;
//                 if ( verbose )
//                   cerr << "ILSMinResLanczos: x_C used with residual " << res_x_C << " < " << res_x_L << endl;    
//                 
//               }
//               
//               delete v_new;
//               delete v_old;
//               delete v_next;
//               delete w_new;
//               delete w_bar;
//   
//   
//   //toc
//   float duration = (float) (clock() - start);
//   std::cerr << "Time for solveLin: " << duration/CLOCKS_PER_SEC << std::endl; 
// 
//   fprintf(logfile, "x:\n");
//   for (uint i = 0; i < x.size(); i++)
//   { 
//       fprintf(logfile, "%f  ",x(i));
//   }
//   fprintf(logfile, "\n");
//   
//   // check result
//   Vector Ax(mySize,0.0);
//   Ax = A*x;
//   fprintf(logfile, "A*x:\n");
//   for (uint i = 0; i < Ax.size(); i++)
//   { 
//       fprintf(logfile, "%f  ",Ax(i));
//   }
//   fprintf(logfile, "\n"); 
//   
//   fclose(logfile);
//   
//   return 0;
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

