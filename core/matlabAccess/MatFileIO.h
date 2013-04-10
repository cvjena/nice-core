/** 
* @file MatFileIO.h
* @brief Read and write mat-files
* @author Paul Bodesheim
* @date 06-01-2012 (dd-mm-yyyy)
*/
#ifndef MATFILEIOH_INCLUDE
#define MATFILEIOH_INCLUDE

#include <cstdlib>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <vector>

#include <core/basics/Exception.h>
#include <core/vector/VectorT.h>

#ifndef NICE_USELIB_MATIO

#warning "We need the MATIO Library for accessing MATLAB structures. Otherwise this is not compiling."

#else //#ifdef NICE_USELIB_MATIO

#include <matio/matio.h>

#ifndef sparse_t
#define sparse_t mat_sparse_t
#endif

namespace NICE {
  
  class MatFileIO {
       
    protected:
      
      mat_t *mat; // struct for the mat-file, defined in matio.h
      
    public:

      //------------------------------------------------------
      // several constructors and destructors
      //----------------------------------------------------

      /** 
      * @brief Default constructor
      * @author Paul Bodesheim
      * @date 06-01-2012 (dd-mm-yyyy)
      */
      MatFileIO(); 
      
      /** 
      * @brief Recommended constructor
      * @author Paul Bodesheim
      * @date 06-01-2012 (dd-mm-yyyy)
      * @param _filename name of the mat-file, if mode = MAT_ACC_RDWR and _filename does not exist, a new file will be created
      * @param mode file access mode: MAT_ACC_RDONLY (read only) or MAT_ACC_RDWR (read + write)
      */
      MatFileIO(std::string _filename, const mat_acc mode);  
      
      /** 
      * @brief Default destructor
      * @author Paul Bodesheim
      * @date 06-01-2012 (dd-mm-yyyy)
      */
      ~MatFileIO();
             
      //------------------------------------------------------
      // enumeration
      //------------------------------------------------------           
      
      /** 
      * @brief feature matrix order
      * @author Paul Bodesheim
      * @date 09-01-2012 (dd-mm-yyyy)
      */
      enum feature_matrix_order {
	NxD = 1,  /**< @brief Read only file access                */
	DxN   = 2   /**< @brief Read/Write file access               */
      };
            
      //------------------------------------------------------
      // count number of stored variables
      //------------------------------------------------------     
      
      /** 
      * @brief get the number of variables stored in the mat-file referenced by mat
      * @author Paul Bodesheim
      * @date 06-01-2012 (dd-mm-yyyy)
      * @return number of variables
      */
      int getNumberOfVariables();
      
      //------------------------------------------------------
      // several methods for reading data
      //------------------------------------------------------     
 
      /** 
      * @brief get the variable with name _name stored in the mat-file referenced by mat
      * @author Paul Bodesheim
      * @date 06-01-2012 (dd-mm-yyyy)
      * @param _name name of the variable
      * @return variable with name _name in the matvar_t format
      */  
      matvar_t * getVariableViaName(std::string _name);
      
      
      /**
       * @brief get the sparsely stored variable with name _name stored in the mat-file referenced by mat
       * @author Paul Bodesheim
       * @date 10-01-2012 (dd-mm-yyyy)
       * @param sparseVariable result: sparse variable with name _name in sparse matio-format sparse_t (see matio/src/matio.h)
       * @param _name name of the variable
       **/
      void getSparseVariableViaName(sparse_t & sparseVariable, std::string _name);
      
      /** 
      * @brief get the feature matrix with name _name stored in the mat-file referenced by mat
      * @author Paul Bodesheim
      * @date 09-01-2012 (dd-mm-yyyy)
      * @param _name name of the variable
      * @param order organization of the feature matrix: NxD (each feature in a row and each feature dimension in a coliumn)or DxN (vice versa)
      * @param features result: feature matrix with name _name in the fast-HIK format: std::vector<std::vector<double> >
      */  
      void getFeatureMatrixViaName(std::vector<std::vector<double> > & features, std::string _name, const feature_matrix_order order = NxD);
 
      /** 
      * @brief get vector with name _name stored in the mat-file referenced by mat
      * @author Paul Bodesheim
      * @date 09-01-2012 (dd-mm-yyyy)
      * @param _name name of the variable
      * @param vec result: vector with name _name in format NICE::Vector 
      */ 
      void getVectorViaName(NICE::Vector & vec, std::string _name);  
            
  }; // class
  
} // namespace

#endif
#endif
