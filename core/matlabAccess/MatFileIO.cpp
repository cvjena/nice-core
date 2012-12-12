/** 
* @file MatFileIO.cpp
* @brief Read and write mat-files
* @author Paul Bodesheim
* @date 06-01-2012 (dd-mm-yyyy)
*/

#include "MatFileIO.h"

namespace NICE {
  
      //------------------------------------------------------
      // several constructors and destructors
      //------------------------------------------------------

       
      // Default constructor
      MatFileIO::MatFileIO() { mat = 0; }
      
      // Recommended constructor
      MatFileIO::MatFileIO(std::string _filename, const mat_acc mode) { 
	
	mat = Mat_Open(_filename.c_str(),mode); 
	
	if (mat == NULL && mode == MAT_ACC_RDONLY) {
	 
	  fthrow(Exception, "MatFileIO::MatFileIO(const char * _filename, int mode): mat-file does not exist");
	  
	}
      } 
      
      // Default destructor
      MatFileIO::~MatFileIO() {}
      
      //------------------------------------------------------
      // count number of stored variables
      //------------------------------------------------------     
      
      int MatFileIO::getNumberOfVariables() {
	
	Mat_Rewind(mat); // get back to first variable
	int count = 0;
	matvar_t * matvar = Mat_VarReadNextInfo(mat);
	
	while (matvar != NULL) {
	  
	  count++;
	  matvar = Mat_VarReadNextInfo(mat);
	}
	
	Mat_VarFree(matvar);
	
	return count;
      }
      
      //------------------------------------------------------
      // several methods for reading data
      //------------------------------------------------------     
      
      matvar_t * MatFileIO::getVariableViaName(std::string _name) {
      
// 	std::cout << "MatFileIO::getVariableViaName: method entered" << std::endl;
	char * cString = new char[256];
// 	std::cout << "MatFileIO::getVariableViaName: cString init done" << std::endl;
	return Mat_VarRead(mat,strcpy(cString,_name.c_str()));
	
      }
      
      void MatFileIO::getSparseVariableViaName(sparse_t & sparseVariable, std::string _name) {
	
	matvar_t * matvar = getVariableViaName(_name);
	
	if (matvar == NULL) {
	  
	  fthrow(Exception, "MatFileIO::getSparseVariableViaName(sparse_t & sparseVariable, std::string _name): variable with specified name does not exist");
	  return;
	}

	if (matvar->class_type != MAT_C_SPARSE) {
	  
	  fthrow(Exception, "MatFileIO::getSparseVariableViaName(sparse_t & sparseVariable, std::string _name): format of variable is not sparse");
	  return;
	}
	
	sparseVariable = *((sparse_t*)matvar->data);
	sparseVariable.data = (double*) sparseVariable.data;
      }

      
      void MatFileIO::getFeatureMatrixViaName(std::vector<std::vector<double> > & features, std::string _name, const feature_matrix_order order) {
	
	matvar_t * matvar = getVariableViaName(_name);
	
	if (matvar == NULL) {
	  
	  fthrow(Exception, "MatFileIO::getFeatureMatrixViaName(char * _name, feature_matrix_order order): variable with specified name does not exist");
	  return;
	}
	
	if (matvar->rank != 2) {
	  
	  fthrow(Exception, "MatFileIO::getFeatureMatrixViaName(char * _name, feature_matrix_order order): dimension of variable != 2");
	  return;
	}
	
	features.clear();
	std::vector<double> currentFeature;
	currentFeature.clear();
	
	// case 1: feature vectors in the rows of matrix
	if (order == NxD) {
	  
	  // depending on the class type of data elements, we have to treat several cases and cast the data elements correctly
          switch (matvar->data_type) {
	    
            case MAT_T_DOUBLE:
	      
  
	      for ( int i = 0; i < matvar->dims[0]; i++ ) {
		for ( int j = 0; j < matvar->dims[1]; j++ ) {
		  
		  currentFeature.push_back( ((double*)matvar->data)[matvar->dims[0]*j+i] );	      
		}
		  
		  features.push_back(currentFeature);
		  currentFeature.clear();
	      }
	      
	      break;
	      
            case MAT_T_SINGLE:
	  
	      for ( int i = 0; i < matvar->dims[0]; i++ ) {
		for ( int j = 0; j < matvar->dims[1]; j++ ) {
		  
		  currentFeature.push_back( ((float*)matvar->data)[matvar->dims[0]*j+i] );	      
		}
		  
		  features.push_back(currentFeature);
		  currentFeature.clear();
	      }
	      
	      break;
	      
#ifdef HAVE_MAT_INT64_T
            case MAT_T_INT64:
	      
	      for ( int i = 0; i < matvar->dims[0]; i++ ) {
		for ( int j = 0; j < matvar->dims[1]; j++ ) {
		  
		  currentFeature.push_back( ((signed long long*)matvar->data)[matvar->dims[0]*j+i] );	      
		}
		  
		  features.push_back(currentFeature);
		  currentFeature.clear();
	      }	            

	      break;
#endif
#ifdef HAVE_MAT_UINT64_T	      
            case MAT_T_UINT64:

	      for ( int i = 0; i < matvar->dims[0]; i++ ) {
		for ( int j = 0; j < matvar->dims[1]; j++ ) {
		  
		  currentFeature.push_back( ((unsigned long long*)matvar->data)[matvar->dims[0]*j+i] );	      
		}
		  
		  features.push_back(currentFeature);
		  currentFeature.clear();
	      }	

	      break; 
#endif
            case MAT_T_INT32:
	      
	      for ( int i = 0; i < matvar->dims[0]; i++ ) {
		for ( int j = 0; j < matvar->dims[1]; j++ ) {
		  
		  currentFeature.push_back( ((signed long*)matvar->data)[matvar->dims[0]*j+i] );	      
		}
		  
		  features.push_back(currentFeature);
		  currentFeature.clear();
	      }
	      
	      break;	      

            case MAT_T_UINT32:
	      
	      for ( int i = 0; i < matvar->dims[0]; i++ ) {
		for ( int j = 0; j < matvar->dims[1]; j++ ) {
		  
		  currentFeature.push_back( ((unsigned long*)matvar->data)[matvar->dims[0]*j+i] );	      
		}
		  
		  features.push_back(currentFeature);
		  currentFeature.clear();
	      }
	      
	      break;	      
	      
            case MAT_T_INT16:

	      for ( int i = 0; i < matvar->dims[0]; i++ ) {
		for ( int j = 0; j < matvar->dims[1]; j++ ) {
		  
		  currentFeature.push_back( ((signed short*)matvar->data)[matvar->dims[0]*j+i] );	      
		}
		  
		  features.push_back(currentFeature);
		  currentFeature.clear();
	      }
	      
	      break;
	      
            case MAT_T_UINT16:
	      
	      for ( int i = 0; i < matvar->dims[0]; i++ ) {
		for ( int j = 0; j < matvar->dims[1]; j++ ) {
		  
		  currentFeature.push_back( ((unsigned short*)matvar->data)[matvar->dims[0]*j+i] );	      
		}
		  
		  features.push_back(currentFeature);
		  currentFeature.clear();
	      }
	      
	      break;	      
	      
            case MAT_T_INT8:
	      
	      for ( int i = 0; i < matvar->dims[0]; i++ ) {
		for ( int j = 0; j < matvar->dims[1]; j++ ) {
		  
		  currentFeature.push_back( ((signed char*)matvar->data)[matvar->dims[0]*j+i] );
		}
		  
		  features.push_back(currentFeature);
		  currentFeature.clear();
	      }
	      
	      break;	      

            case MAT_T_UINT8:
	      
	      for ( int i = 0; i < matvar->dims[0]; i++ ) {
		for ( int j = 0; j < matvar->dims[1]; j++ ) {
		  
		  currentFeature.push_back( ((unsigned char*)matvar->data)[matvar->dims[0]*j+i] );	      
		}
		  
		  features.push_back(currentFeature);
		  currentFeature.clear();
	      }
	      
	      break;
	  }   

	// case 2: feature vectors in the columns of matrix
	} else if (order == DxN) {
	  
	  // depending on the class type of data elements, we have to treat several cases and cast the data elements correctly
          switch (matvar->data_type) {
	    
            case MAT_T_DOUBLE:
	  
	      for ( int j = 0; j < matvar->dims[1]; j++ ) {
		for ( int i = 0; i < matvar->dims[0]; i++ ) {
		  
		  currentFeature.push_back( ((double*)matvar->data)[matvar->dims[0]*j+i] );	      
		}
		  
		  features.push_back(currentFeature);
		  currentFeature.clear();
	      }
	      
	      break;
	      
            case MAT_T_SINGLE:
	  
	      for ( int j = 0; j < matvar->dims[1]; j++ ) {
		for ( int i = 0; i < matvar->dims[0]; i++ ) {
		  
		  currentFeature.push_back( ((float*)matvar->data)[matvar->dims[0]*j+i] );	      
		}
		  
		  features.push_back(currentFeature);
		  currentFeature.clear();
	      }
	      
	      break;
	      
#ifdef HAVE_MAT_INT64_T
            case MAT_T_INT64:
	      
	      for ( int j = 0; j < matvar->dims[1]; j++ ) {
		for ( int i = 0; i < matvar->dims[0]; i++ ) {
		  
		  currentFeature.push_back( ((signed long long*)matvar->data)[matvar->dims[0]*j+i] );	      
		}
		  
		  features.push_back(currentFeature);
		  currentFeature.clear();
	      }	            

	      break;
#endif
#ifdef HAVE_MAT_UINT64_T	      
            case MAT_T_UINT64:

	      for ( int j = 0; j < matvar->dims[1]; j++ ) {
		for ( int i = 0; i < matvar->dims[0]; i++ ) {
		  
		  currentFeature.push_back( ((unsigned long long*)matvar->data)[matvar->dims[0]*j+i] );	      
		}
		  
		  features.push_back(currentFeature);
		  currentFeature.clear();
	      }	

	      break;
#endif
            case MAT_T_INT32:
	      
	      for ( int j = 0; j < matvar->dims[1]; j++ ) {
		for ( int i = 0; i < matvar->dims[0]; i++ ) {
		  
		  currentFeature.push_back( ((signed long*)matvar->data)[matvar->dims[0]*j+i] );	      
		}
		  
		  features.push_back(currentFeature);
		  currentFeature.clear();
	      }
	      
	      break;	      

            case MAT_T_UINT32:
	      
	      for ( int j = 0; j < matvar->dims[1]; j++ ) {
		for ( int i = 0; i < matvar->dims[0]; i++ ) {
		  
		  currentFeature.push_back( ((unsigned long*)matvar->data)[matvar->dims[0]*j+i] );	      
		}
		  
		  features.push_back(currentFeature);
		  currentFeature.clear();
	      }
	      
	      break;	      
	      
            case MAT_T_INT16:

	      for ( int j = 0; j < matvar->dims[1]; j++ ) {
		for ( int i = 0; i < matvar->dims[0]; i++ ) {
		  
		  currentFeature.push_back( ((signed short*)matvar->data)[matvar->dims[0]*j+i] );	      
		}
		  
		  features.push_back(currentFeature);
		  currentFeature.clear();
	      }
	      
	      break;
	      
            case MAT_T_UINT16:
	      
	      for ( int j = 0; j < matvar->dims[1]; j++ ) {
		for ( int i = 0; i < matvar->dims[0]; i++ ) {
		  
		  currentFeature.push_back( ((unsigned short*)matvar->data)[matvar->dims[0]*j+i] );	      
		}
		  
		  features.push_back(currentFeature);
		  currentFeature.clear();
	      }
	      
	      break;	      
	      
            case MAT_T_INT8:
	      
	      for ( int j = 0; j < matvar->dims[1]; j++ ) {
		for ( int i = 0; i < matvar->dims[0]; i++ ) {
		  
		  currentFeature.push_back( ((signed char*)matvar->data)[matvar->dims[0]*j+i] );	      
		}
		  
		  features.push_back(currentFeature);
		  currentFeature.clear();
	      }
	      
	      break;	      

            case MAT_T_UINT8:
	      
	      for ( int j = 0; j < matvar->dims[1]; j++ ) {
		for ( int i = 0; i < matvar->dims[0]; i++ ) {
		  
		  currentFeature.push_back( ((unsigned char*)matvar->data)[matvar->dims[0]*j+i] );	      
		}
		  
		  features.push_back(currentFeature);
		  currentFeature.clear();
	      }
	      
	      break;
	  }            
          
	} else {
	  
	  fthrow(Exception, "MatFileIO::getFeatureMatrixViaName(char * _name, feature_matrix_order order): wrong feature_matrix_order specified");
	  return;
	}	
	
      }
      
      void MatFileIO::getVectorViaName(NICE::Vector & vec, std::string _name) {
	
	matvar_t * matvar = getVariableViaName(_name);
	
	if (matvar == NULL) {
	  
	  fthrow(Exception, "MatFileIO::getFeatureMatrixViaName(char * _name, feature_matrix_order order): variable with specified name does not exist");
	  return;
	}
	
	// it can happen that a vector is treated as (N x 1) or (1 x N) matrix with two dimensions
	if (matvar->rank > 2 || ( (matvar->rank == 2) && (matvar->dims[0] != 1) && (matvar->dims[1] != 1) ) ) {
	  
	  fthrow(Exception, "MatFileIO::getFeatureMatrixViaName(char * _name, feature_matrix_order order): dimension of variable > 1");
	  return;
	}  
	
	std::vector<double> v;
	v.clear();
	
	// vector is stored as a variable with one dimensional 
	if (matvar->rank == 1) {
	  
          switch( matvar->data_type ) {
	    
            case MAT_T_DOUBLE:
	  
	      for ( int i = 0; i < matvar->nbytes/matvar->data_size; i++ ) {
		  
		  v.push_back( ((double*)matvar->data)[i] );	      
	      }
	      
	      break;
	      
            case MAT_T_SINGLE:
	  
	      for ( int i = 0; i < matvar->nbytes/matvar->data_size; i++ ) {
		  
		  v.push_back( ((float*)matvar->data)[i] );	      
	      }
	      
	      break;
	      
#ifdef HAVE_MAT_INT64_T
            case MAT_T_INT64:
	      
	      for ( int i = 0; i < matvar->nbytes/matvar->data_size; i++ ) {
		  
		  v.push_back( ((signed long long*)matvar->data)[i] );	      
	      }            

	      break;
#endif
#ifdef HAVE_MAT_UINT64_T	      
            case MAT_T_UINT64:

	      for ( int i = 0; i < matvar->nbytes/matvar->data_size; i++ ) {
		  
		  v.push_back( ((unsigned long long*)matvar->data)[i] );	      
	      }

	      break;
#endif
            case MAT_T_INT32:
	      
	      for ( int i = 0; i < matvar->nbytes/matvar->data_size; i++ ) {
		  
		  v.push_back( ((signed long*)matvar->data)[i] );	      
	      }
	      
	      break;	      

            case MAT_T_UINT32:
	      
	      for ( int i = 0; i < matvar->nbytes/matvar->data_size; i++ ) {
		  
		  v.push_back( ((unsigned long*)matvar->data)[i] );	      
	      }
	      
	      break;	      
	      
            case MAT_T_INT16:

	      for ( int i = 0; i < matvar->nbytes/matvar->data_size; i++ ) {
		  
		  v.push_back( ((signed short*)matvar->data)[i] );	      
	      }
	      
	      break;
	      
            case MAT_T_UINT16:
	      
	      for ( int i = 0; i < matvar->nbytes/matvar->data_size; i++ ) {
		  
		  v.push_back( ((unsigned short*)matvar->data)[i] );	      
	      }
	      
	      break;	      
	      
            case MAT_T_INT8:
	      
	      for ( int i = 0; i < matvar->nbytes/matvar->data_size; i++ ) {
		  
		  v.push_back( ((signed char*)matvar->data)[i] );	      
	      }
	      
	      break;	      

            case MAT_T_UINT8:
	      
	      for ( int i = 0; i < matvar->nbytes/matvar->data_size; i++ ) {
		  
		  v.push_back( ((unsigned char*)matvar->data)[i] );	      
	      }
	      
	      break;
	  } 	  
	  
	// it can happen that a vector is treated as (N x 1) or (1 x N) matrix with two dimensions, here we handle this case
	} else {
	  
          switch( matvar->data_type ) {
	    
            case MAT_T_DOUBLE:
	  
	      for ( int i = 0; i < matvar->dims[0]; i++ ) {
		for ( int j = 0; j < matvar->dims[1]; j++ ) {
		  
		  v.push_back( ((double*)matvar->data)[matvar->dims[0]*j+i] );	      
		}
	      }
	      
	      break;
	      
            case MAT_T_SINGLE:
	  
	      for ( int i = 0; i < matvar->dims[0]; i++ ) {
		for ( int j = 0; j < matvar->dims[1]; j++ ) {
		  
		  v.push_back( ((float*)matvar->data)[matvar->dims[0]*j+i] );	      
		}
	      }
	      
	      break;
	      
#ifdef HAVE_MAT_INT64_T
            case MAT_T_INT64:
	      
	      for ( int i = 0; i < matvar->dims[0]; i++ ) {
		for ( int j = 0; j < matvar->dims[1]; j++ ) {
		  
		  v.push_back( ((signed long long*)matvar->data)[matvar->dims[0]*j+i] );	      
		}
	      }	            

	      break;
#endif
#ifdef HAVE_MAT_UINT64_T	      
            case MAT_T_UINT64:

	      for ( int i = 0; i < matvar->dims[0]; i++ ) {
		for ( int j = 0; j < matvar->dims[1]; j++ ) {
		  
		  v.push_back( ((unsigned long long*)matvar->data)[matvar->dims[0]*j+i] );	      
		}
	      }	

	      break;
#endif
            case MAT_T_INT32:
	      
	      for ( int i = 0; i < matvar->dims[0]; i++ ) {
		for ( int j = 0; j < matvar->dims[1]; j++ ) {
		  
		  v.push_back( ((signed long*)matvar->data)[matvar->dims[0]*j+i] );	      
		}
	      }
	      
	      break;	      

            case MAT_T_UINT32:
	      
	      for ( int i = 0; i < matvar->dims[0]; i++ ) {
		for ( int j = 0; j < matvar->dims[1]; j++ ) {
		  
		  v.push_back( ((unsigned long*)matvar->data)[matvar->dims[0]*j+i] );	      
		}
	      }
	      
	      break;	      
	      
            case MAT_T_INT16:

	      for ( int i = 0; i < matvar->dims[0]; i++ ) {
		for ( int j = 0; j < matvar->dims[1]; j++ ) {
		  
		  v.push_back( ((signed short*)matvar->data)[matvar->dims[0]*j+i] );	      
		}
	      }
	      
	      break;
	      
            case MAT_T_UINT16:
	      
	      for ( int i = 0; i < matvar->dims[0]; i++ ) {
		for ( int j = 0; j < matvar->dims[1]; j++ ) {
		  
		  v.push_back( ((unsigned short*)matvar->data)[matvar->dims[0]*j+i] );	      
		}
	      }
	      
	      break;	      
	      
            case MAT_T_INT8:
	      
	      for ( int i = 0; i < matvar->dims[0]; i++ ) {
		for ( int j = 0; j < matvar->dims[1]; j++ ) {
		  
		  v.push_back( ((signed char*)matvar->data)[matvar->dims[0]*j+i] );	      
		}
	      }
	      
	      break;	      

            case MAT_T_UINT8:
	      
	      for ( int i = 0; i < matvar->dims[0]; i++ ) {
		for ( int j = 0; j < matvar->dims[1]; j++ ) {
		  
		  v.push_back( ((unsigned char*)matvar->data)[matvar->dims[0]*j+i] );	      
		}
	      }
	      
	      break;
	  } 	  
	  
	}
	
	vec = NICE::Vector(v);	
      }
}

