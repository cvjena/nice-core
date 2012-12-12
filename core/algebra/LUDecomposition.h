/**
* @file LUDecomposition.h
* @brief: LU-Decomposition of a matrix
* @author: Alexander Freytag, Wolfgang Ortmann
* @date: 22-10-2012
*/

// Note: for further matrix operations, you might use the ICE library available at http://www.inf-cv.uni-jena.de/ice.html

#ifndef _NICE_LUDECOMPOSITION_
#define _NICE_LUDECOMPOSITION_

#include "core/vector/MatrixT.h"
#include "core/vector/VectorT.h"
#include "MatrixDecomposition.h"

namespace NICE
{

  /*!
      LU-Decomposition of a matrix
  */

  class LUDecomposition : MatrixDecomposition  
  {
    public:


      /*!
        default constructor
      */
      LUDecomposition();

      /*!
          Destructor.
      */
      virtual ~LUDecomposition();
      
      /**
       * @brief decompose a square matrix m into lower and upper triangular matrices L and U
       * @date 22-10-2012
       * @author Alexander Freytag
       * @param m a square matrix
       * @param L the resulting lower triangular matrix
       * @param U the resulting upper triangular matrix
       */      
      void decompose( const NICE::Matrix & m, NICE::Matrix & L, NICE::Matrix & U);
      
      /**
       * @brief solve a linear equation system, using the LU-decomposition of a square matrix m
       * @date 22-10-2012
       * @author Alexander Freytag
       * @param LU the given LU-decomposition of a square matrix m
       * @param indx vector containing information about the exchange of rows during the decomposition (when pivotization is done)
       * @param b the right-hand-side of the linear equation system
       */
      NICE::Vector solve( const NICE::Matrix &LU,const NICE::VectorT<int> &indx, const NICE::Vector &b);

      /**
       * @brief decompose a square matrix m into lower and upper triangular matrices L and U, which are packed into a single matrix 
       * @date 22-10-2012
       * @author Alexander Freytag
       * @param m a square matrix
       * @param LU the decomposition of m in a single matrix (LU_ij: i<=j -> LU_ij=U_ij, i>j -> LU_ij=L_ij, L_ii = 1.0)
       * @param indx vector containing information about the exchange of rows during the decomposition (when pivotization is done)
       * @param pivot use pivotization? (default true)
       */         
      void decomposePacked(const NICE::Matrix & m, NICE::Matrix & LU, NICE::VectorT<int> & indx, bool pivot=true); 
      
      /**
       * @brief decompose a square matrix m into lower and upper triangular matrices L and U, which are packed into a single matrix, NO pivotization
       * @date 22-10-2012
       * @author Alexander Freytag
       * @param m a square matrix
       * @param LU the decomposition of m in a single matrix (LU_ij: i<=j -> LU_ij=U_ij, i>j -> LU_ij=L_ij, L_ii = 1.0)
       */          
      void decomposePacked(const NICE::Matrix & m, NICE::Matrix & LU);      
      
    protected:

  };
  
} //namespace

#endif
