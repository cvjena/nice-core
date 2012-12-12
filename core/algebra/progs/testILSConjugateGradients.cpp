/** 
* @file testILSConjugateGradients.cpp
* @author Paul Bodesheim
* @date  23/01/2012
* @brief test routine for Iterative Linear Solver: Conjugate Gradients Method (CGM)
*/

#include "core/vector/MatrixT.h"
#include "core/vector/VectorT.h"
#include <stdio.h>
#include <ctime>
#include "iostream"
#include "core/basics/Exception.h"
#include "core/vector/Algorithms.h"
#include "core/algebra/ILSConjugateGradients.h"
#include "core/algebra/GMStandard.h"

using namespace std;
using namespace NICE;

int main(int argc, char* argv[])
{
  
	int mySize = 20; // number of equations
	FILE * logfile;
	std::string logfilename;
	
	if ( argc < 2 )
	  logfilename = "/home/bodesheim/testILS-CGM.log";
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
	ILSConjugateGradients cgm(true,mySize);
	
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
