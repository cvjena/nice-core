/** 
* @file testILSmethods.cpp
* @author Paul Bodesheim
* @date  23/01/2012
* @brief test routine for Iterative Linear Solvers
*/

#include "core/vector/MatrixT.h"
#include "core/vector/VectorT.h"
#include <stdio.h>
#include <ctime>
#include "core/basics/Exception.h"
#include "core/vector/Algorithms.h"
#include "core/algebra/GMStandard.h"
#include "core/algebra/ILSConjugateGradients.h"
#include "core/algebra/ILSConjugateGradientsLanczos.h"
#include "core/algebra/ILSSymmLqLanczos.h"
#include "core/algebra/ILSMinResLanczos.h"

using namespace std;
using namespace NICE;

int main(int argc, char* argv[])
{
  
	int mySize = 10000; // number of equations
	
	srand ( time(NULL) );
  
	// generate matrix A
	Matrix A(mySize,mySize,0.0);
	for (uint i = 0; i < A.rows(); i++)
	{
		for (uint j = i; j < A.cols(); j++)
		{
			if ( j == i ) A(i,j) = (i+1)+(j+1);
			else {
			  
          double r = ( (double) rand() ) / (RAND_MAX);
			    A(i,j) = r;
          A(j,i) = r;
			}

		}
	}
	
	// generate vector b (RHS of LS)
	Vector b(mySize,0.0);
	for (uint i = 0; i < b.size(); i++)
	{	
	    b(i) = ( (double) rand() ) / (RAND_MAX);
	}
	
	// solve Ax = b with cgm method
	ILSConjugateGradients cgm(false,mySize);
  ILSConjugateGradientsLanczos cgm_L(false,mySize);
  ILSSymmLqLanczos symmlq(false,mySize);
  ILSMinResLanczos minres(false,mySize);
	
  Vector x(mySize,0.0);
	//tic
	time_t  start = clock();
	cgm.solveLin(GMStandard(A),b,x);
	//toc
	float duration = (float) (clock() - start);
	std::cerr << "Time for solveLin (ILSConjugateGradients): " << duration/CLOCKS_PER_SEC << std::endl;	

  x.set(0.0);
  //tic
  start = clock();
  cgm_L.solveLin(GMStandard(A),b,x);
  //toc
  duration = (float) (clock() - start);
  std::cerr << "Time for solveLin (ILSConjugateGradientsLanczos): " << duration/CLOCKS_PER_SEC << std::endl;   

  x.set(0.0);
  //tic
  start = clock();
  symmlq.solveLin(GMStandard(A),b,x);
  //toc
  duration = (float) (clock() - start);
  std::cerr << "Time for solveLin (ILSSymmLqLanczos): " << duration/CLOCKS_PER_SEC << std::endl; 

  x.set(0.0);
  //tic
  start = clock();
  minres.solveLin(GMStandard(A),b,x);
  //toc
  duration = (float) (clock() - start);
  std::cerr << "Time for solveLin (ILSMinResLanczos): " << duration/CLOCKS_PER_SEC << std::endl;   
  
	return 0;
}
