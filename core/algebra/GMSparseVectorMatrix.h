/** 
 * @file GMSparseVectorMatrix.h
 * @brief Sparse Matrix depends on SparseVectors
 * @author Björn Fröhlich
 * @date 05/14/2009

 */
#ifndef GMSPARSE2INCLUDE
#define GMSPARSE2INCLUDE

#include "GenericMatrix.h"

namespace NICE
{

  /** implementation of GenericMatrix using a sparse representation of a matrix as a collection of sparse vectors 
   * @remark the functions in this class do not really exploit the sparseness of the involved vectors */
	class GMSparseVectorMatrix : public GenericMatrix
	{
	protected:
		//! the sparse matrix
		std::vector < NICE::SparseVector * >A;

		//! count of rows
		uint m_rows;

		//! count of columns
		uint m_cols;

		//! are the vectors new ones or come they from somewhere else
		bool newvectors;

	public:
		/**
		 * simple constructor -> does nothing
		 */
    GMSparseVectorMatrix ()
		{
			resize (0, 0);
		};

		/**
		 * constructor which set the rows and cols of the SparseMatrix
		 * @param _rows number of rows of the matrix
		 * @param _cols number of cols of the matrix
		 */
    GMSparseVectorMatrix (uint _rows, uint _cols);

		/**
		 * converts a dense matrix to a sparse matrix
		 * @param A input ICE::Matrix
		 * @param epsilon tolerance value
		 */
    GMSparseVectorMatrix (const NICE::Matrix & iceA, double epsilon = 1e-9);

		/**
		 * simple destructor
		 */
   ~GMSparseVectorMatrix ();

		/**
		 * resize the matrix
		 * @param _rows new count of rows
		 * @param _cols new count of cols
		 */
		void resize (int _rows, int _cols);

		/**
		 * clean up
		 */
		void clear ();

		/** get the number of rows in A */
		uint rows () const
		{
			return m_rows;
		};

		/** get the number of columns in A */
		uint cols () const
		{
			return m_cols;
		};

		/** multiply with a vector: A*x = y */
		void multiply (NICE::Vector & y, const NICE::Vector & x) const;

		/**
		 * return the i-th row
		 * @param i 
		 * @return SparseVector at row i
		 */
    NICE::SparseVector & operator[] (int i) const;

		/**
		 * restore the information of the sparse matrix
		 * @param is inputstream
		 * @param format 
		 */
		void restore (std::istream & is, int format = 0);

		/**
		 * store the information of the sparse matrix
		 * @param os outputstream
		 * @param format 
		 */
		void store (std::ostream & os, int format = 0) const;

		/**
		 * Should the data be deleted when the destructor is called
		 * @param del 
		 */
		void setDel (bool del = true);

		/**
		 * add a new row 
		 * @param x ICE::Vector
		 */
		void addRow (const NICE::Vector & x);

		/**
		 * add a new row
		 * @param x SparseVector
		 */
		void addRow (NICE::SparseVector * x);

		/**
		 * matrixmultiplication x*y = out
		 * @param y input
		 * @param out output
		 * @param transpx use the transpose of x 
		 * @param transpy use the transpose of y
		 * @return z
		 */
		void mult (GMSparseVectorMatrix & y, GMSparseVectorMatrix & out, bool transpx =
							 false, bool transpy = false);

		/**
		 * matrixmultiplication x*y = out
		 * @param y input Sparse Vector
		 * @param out output
		 * @param transpx use the transpose of x 
		 * @param transpy use the transpose of y
		 * @return z
		 */
		void mult (NICE::SparseVector & y, GMSparseVectorMatrix & out, bool transpx =
							 false, bool transpy = false);

		/**
		 * same like mult, but faster when y ist very sparse and slower if not
		 * @param y input
		 * @param out output
		 * @param transpx use the transpose of x 
		 * @param transpy use the transpose of y
		 * @return z
		 */
		void mult2 (GMSparseVectorMatrix & y, GMSparseVectorMatrix & out, bool transpx =
								false, bool transpy = false);
	};

}	// namespace

#endif
