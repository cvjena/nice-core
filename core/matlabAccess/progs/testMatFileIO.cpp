/** 
* @file testMatFileIO.cpp
* @brief 
* @author Paul Bodesheim
* @date 06/01/2012 (dd-mm-yyyy)
*/

#include <vector>
#include <iostream>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#ifdef NICE_USELIB_MATIO
#include "core/matlabAccess/MatFileIO.h"
using namespace NICE;
#endif

using namespace std;

int main (int argc, char* argv[]) 
{
#ifdef NICE_USELIB_MATIO	
  std::string filenameA = "/home/bodesheim/data/2012-01-09-testMatFileIO/sparse3x3matrixA.mat";

  // A
  MatFileIO matfileIOA = MatFileIO(filenameA,MAT_ACC_RDONLY);
  printf("\n%d \n", matfileIOA.getNumberOfVariables());
  
  sparse_t sparseA;
  matfileIOA.getSparseVariableViaName(sparseA,"A");
  for (uint i = 0; i < sparseA.nzmax; i++) std::cout << ((double*)sparseA.data)[i]<< "  "; 
  std::cerr << std::endl;
  std::cerr << "now start reading imagenet-data" << std::endl;
  
  std::string filename = "/home/dbv/bilder/imagenet/devkit-1.0/demo/demo.train.mat";
  std::string variable1 = "training_instance_matrix";
  std::string variable2 = "training_label_vector";

  //
  // test matvar functions
  //
  
  mat_t * mat;
  matvar_t * matvar;
  
  mat = Mat_Open(filename.c_str(),MAT_ACC_RDONLY);
  matvar = Mat_VarReadNext(mat);

  while (matvar != NULL) {

    printf("dimension of variable: %i : ",matvar->rank);
    printf("%i ",*(matvar->dims));
    for (int i = 2; i<=matvar->rank; i++) {
		  
      matvar->dims++;	  
      printf("x %i ",*(matvar->dims));
      
    }
    printf("\n");
    matvar = Mat_VarReadNext(mat);

  };
  
  //
  // test class MatFileIO
  //
  
  MatFileIO matfileIO = MatFileIO(filename,MAT_ACC_RDONLY);
  printf("\nnumber of variables: %d \n", matfileIO.getNumberOfVariables()); 
  
  sparse_t *sparse;
  matfileIO.getSparseVariableViaName(*sparse,variable1);
  
  printf("\nSparse Matrix \n"); 

  for ( int i = 0; i < 5; i++ ) {
    for ( int j = sparse->jc[i]; j < sparse->jc[i+1] && j < sparse->ndata && j < sparse->jc[i]+5; j++ ) {
                              
	printf("\t\t(%d,%d)\t%f", sparse->ir[j]+1,i+1,((double*)sparse->data)[j]);
    }
    printf("\n");
  }
  
//   int count = 0;
//   
//   for ( int i = 0; i < sparse->njc-1; i++ ) {
//     for ( int j = sparse->jc[i]; j < sparse->jc[i+1] && j < sparse->ndata; j++ )
//                          
//       if (count < 15) {
//       
// 	printf("    (%d,%d)  %f\n", sparse->ir[j]+1,i+1, data[j]);
// 	count++;
//       }     
//   }

  NICE::Vector vec;
  matfileIO.getVectorViaName(vec,variable2);
  
  std::cout << std::endl << "Vector" << std::endl << std::endl; 
  
  for (size_t k = 0; k < 15; k++) {
    
    std::cout << vec[k] << "  ";
  }
  
  std::cout << "..." <<std::endl;
#else
  std::cout << "The MATIO Library has to be installed to run this program." << endl;
#endif

  return 0;
}
