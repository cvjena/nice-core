/**
* @file MatrixDecomposition.h
* @brief: Abstract class for matrix decompositions (LU, SVD, cholesky, householder, ...)
* @author: Alexander Freytag
* @date: 22-10-2012
*/

#ifndef _NICE_MATRIXDECOMPOSITION_
#define _NICE_MATRIXDECOMPOSITION_

namespace NICE
{

  /*!
      Abstract class for matrix decompositions (LU, SVD, cholesky, householder, ...) 
  */

  class MatrixDecomposition  
  {
    public:


      /*!
        default constructor
      */
      MatrixDecomposition(){};

      /*!
          Destructor.
      */
      virtual ~MatrixDecomposition(){};


    protected:

  };
  
} //namespace

#endif
