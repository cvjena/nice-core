/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libbasicvector - A simple vector library
 * See file License for license information.
 */
#ifndef _EMATRIX_BASICVECTOR_H
#define _EMATRIX_BASICVECTOR_H


#include <cstdlib>
#include <string>
#include <sstream>
#include <stdexcept>
#include <core/basics/numerictools.h>
#include <core/basics/Exception.h>
//#include <core/basics/Streamable.h>
#ifdef NICE_USELIB_LINAL
#include <cstddef>
#include <LinAl/matrixCF.h>
#endif

#include "core/vector/MatrixBase.h"
#include "core/vector/VectorT.h"

namespace NICE {

/**
 * @class MatrixT
 * @brief  MatrixT is a simple matrix template class
 * @author Ferid Bajramovic (based on \c extarray from ckolumbus)
 *
 * \c MatrixT is a simple matrix class which provides the (optional) ability
 * to use externally allocated memory as storage.
 * The main features are:
 * - In concept an efficient implementation of a mathematical matrix
 * - An array-like storage class
 * - Support for externally allocated memory
 * - Ability to get pointer to internal memory
 * - Thus the ability to <b>directly</b> interface with other libraries such as
 *   LinAl without time consuming data copying
 *
 * @note MatrixT objects can only be copied and assigned to each other to
 *       a limited degree. This means that care has to be taken when putting
 *       VectorT objects into STL containers (such as std::vector).
 *       More information can be found in the documentation of VectorT.
 *
 * Todo: is the distinction between shallow and deep copy always clear?
 *
 * @example basicvector_matrix_overview.cpp
 */
template<class ElementType>
class MatrixT : public MatrixBase {
public:
  //! STL-like typedef for type of elements
  typedef ElementType value_type;

  //! STL-like typedef for const element reference
  typedef const ElementType& const_reference;

  //! STL-like typedef for iterator
  typedef ElementType* iterator;

  //! STL-like typedef for const iterator
  typedef const ElementType* const_iterator;

  //! STL-like typedef for element reference
  typedef ElementType& reference;

  /**
   * @brief Create an empty \c MatrixT with size zero.
   *
   * Such an object is actually useless, but sometimes you may need to have
   * such instances to initalize some data structure.
   * The only way to turn such an object into something useful is operator=().
   */
  MatrixT();

  /**
   * @brief Create an \c MatrixT with size \c size.
   *        Data will not be initialized.
   * @param rows  number of rows of the \c MatrixT
   * @param cols  number of rows of the \c MatrixT
   */
  explicit MatrixT(const size_t rows, const size_t cols);

  /**
   * @brief Create an \c MatrixT with size \c size.
   *        Data will be initialized to \c element.
   * @param rows  number of rows of the \c MatrixT
   * @param cols  number of rows of the \c MatrixT
   * @param element Initial value of all elements
   */
  MatrixT(const size_t rows, const size_t cols, const ElementType& element);

  /**
   * @brief Create an \c MatrixT of size \c size.
   *        It will be initialized with the data pointed to by \c _data.
   *
   * That is the first \c size elements of \c _data will be copied.
   * @param _data Data to be copied
   * @param rows  number of rows of the \c MatrixT
   * @param cols  number of rows of the \c MatrixT
   */
  MatrixT(const ElementType* _data, const size_t rows, const size_t cols);

  /**
   * @brief Create an \c MatrixT of size \c size
   *        with optionally external storage.
   *
   * It will be initialized with the data pointed to by \c _data.
   * The parameter _external control whether the data will be copied or
   * the pointer \c _data is directly kept as storage for the \c MatrixT.
   * In case of external storage the data will not be deleted in the destructor.
   * @param _data External data storage
   * @param rows  number of rows of the external storage
   * @param cols  number of cols of the external storage
   * @param mode Storage mode: keep external memory or copy data.
   */
  MatrixT(ElementType* _data, const size_t rows, const size_t cols,
          const MatrixBase::Mode mode = copy);

  // /**
  // * @brief Read from input stream.
  // * @param input Read from here
  // */
  //explicit MatrixT(std::istream& input);

  /**
   * @brief copy constructor
   * @param v MatrixT where to copy data from
   */
  MatrixT(const MatrixT<ElementType>& v);

  /**
   * @brief destructor
   */
  virtual ~MatrixT();

  void deleteRow ( const int & index);
  void deleteCol ( const int & index);
  
  //not const, because they get sorted internally
  void deleteRows ( std::vector<int> & indices);
  void deleteCols ( std::vector<int> & indices);
  
  /**
   * @brief Create a const MatrixT of size \c size
   *        with <b>external</b> storage.
   *
   * It will be initialized with the data pointed to by %_data.
   * The data will not be deleted in the destructor.
   * @param _data External data storage
   * @param rows  number of rows of the external storage
   * @param cols  number of cols of the external storage
   */
  inline static const MatrixT<ElementType>* createConst(
                                              const ElementType* _data,
                                              const size_t rows,
                                              const size_t cols);

  /**
   * @brief Read access to elements.
   * @param row row to access
   * @param col col to access
   * @return Element (as const reference)
   * @example basicvector_matrix_access_operator1.cpp
   */
  inline const_reference operator()(const ptrdiff_t row,
                                    const ptrdiff_t col) const {
    return constData[col * rows() + row];
  }

  /**
   * @brief Read access to elements.
   * @param row row to access
   * @param col col to access
   * @return Element (as const reference)
   */
  inline reference operator()(const ptrdiff_t row,
                              const ptrdiff_t col) {
    return data[col * rows() + row];
  }

  /**
   * @brief Get a sub-matrix of the current matrix
   * @param row_tl row of the top left element
   * @param col_tl column of the top left element
   * @param row_br row of the bottom right element
   * @param col_br column of the bottom right element
   * @return sub-matrix as a copy
   */
  MatrixT<ElementType> operator()(const uint row_tl,
                    const uint col_tl,
                    const uint row_br,
                    const uint col_br) const;


  /**
   * @brief Get a const pointer to the internal memory.
   */
//   operator ElementType const* () const { return constData; }

  /**
   * @brief Get a const_iterator pointing to the first element.
   *
   * (Actually the same as \c getDataPointer())
   */
  inline const_iterator begin() const { return constData; }

  /**
   * @brief Get an iterator pointing beyond the last element.
   */
  inline const_iterator end() const { return constData + rows() * cols(); }

  /**
   * @brief Return the number of rows of this MatrixT.
   * @return Size of this MatrixT.
   */
  inline size_t rows() const { return m_rows; }

  /**
   * @brief Return the number of columns of this MatrixT.
   * @return Size of this MatrixT.
   */
  inline size_t cols() const { return m_cols; }

  /**
    * Maximum of elements
    * @return Max of elements
    */
  inline ElementType Max() const;

  /**
    * Minimum of elements
    * @return Min of elements
    */
  inline ElementType Min() const;

  /**
   * @brief Compare \c v with \c this.
   * @pre Size of \c v and \c this must be equal
   * @param v data to compare with
   * @return true if \c v and \c this are equal
   */
  inline bool operator== (const MatrixT<ElementType>& v) const;

  /**
   * @brief Compare \c v with \c this.
   * @pre Size of \c v and \c this must be equal
   * @param v data to compare with
   * @return \c *this
   * @return true if \c v and \c this are not equal
   */
  inline bool operator!= (const MatrixT<ElementType>& v) const;

  /**
   * @brief Change the number of MatrixT elements
   * @param rows  new number of rows
   * @param cols  new number of cols
   * @throw std::runtime_error if using external storage and \c size > \c size()
   * @note Changing the size of the vector invalidates all iterators
   *       and pointers held to the data.
   */
   inline void resize(size_t rows, size_t cols);

  /**
   * @brief Transpose a quadratic MatrixT.
   * @throw Exception if matrix is not square.
   */
   inline void transposeInplace();

  /**
   * @brief return a transposed MatrixT.
   * @return transposed matrix
   */
   MatrixT<ElementType> transpose() const;

   /*! @copydoc MatrixT::transpose() **/
   MatrixT<ElementType> operator !()
   { return transpose(); };

  /**
   * @brief Copy data from \c v to \c this.
   * @pre Size of \c v and \c this must be equal
   * @param v New data
   * @return \c *this
   */
  inline MatrixT<ElementType>& operator=(const MatrixT<ElementType>& v);

  /**
   * @brief Set all elements to value \c element
   * @param element New value of all elements
   */
  inline MatrixT<ElementType>& operator=(const ElementType& element);

  /**
   * @brief Set all elements to value \c element
   * @param element New value of all elements
   */
  inline void set(const ElementType& element) {
    *this = element;
  }

  /**
   * Set a subblock of the matrix.
   * @param top row of top left position of block
   * @param left column of top left position of block
   * @param m data to be copied into the block
   */
  void setBlock(uint top, uint left, MatrixT<ElementType> m);
 

  /**
   * Set a specific row of the matrix.
   * @param row index of the row to be set
   * @param v new data for the specified row
   */  
  void setRow(const uint & row, const NICE::VectorT<ElementType> & v);
  
  /**
   * Exchange two rows of the matrix
   * @param r1 first row to exchange
   * @param r2 second row to exchange
   */  
  void exchangeRows(const uint & r1, const uint & r2);

  /**
   * Add m to Set a subblock of the matrix.
   * @param top row of top left position of block
   * @param left column of top left position of block
   * @param m data to be added to the block
   */
  void addToBlock(uint top, uint left, MatrixT<ElementType> m);

  /**
   * @brief Get a pointer to the internal memory.
   */
//   inline operator ElementType* () { return data; }

  /**
   * @brief Get a pointer to the internal memory.
   */
  inline ElementType* getDataPointer() { return data; }

  /**
   * @brief Get the ith column of the matrix and return an VectorT with is a reference to the internal memory.
   * @param i number of column
   */
  inline const VectorT<ElementType> getColumnRef(uint i) const;

  /**
   * @brief Get the ith column of the matrix and return an VectorT with is a reference to the internal memory.
   * @param i number of column
   */
  inline VectorT<ElementType> getColumnRef(uint i);

  /**
   * @brief Get the ith column of the matrix and return it as VectorT.
   * @param i number of column
   */
  inline VectorT<ElementType> getColumn(uint i) const;

  /**
   * @brief Get the ith row of the matrix and return it as VectorT.
   * @param i number of row
   */
  inline VectorT<ElementType> getRow(uint i) const;

  /**
   * @brief Get a const pointer to the internal memory.
   */
  inline const ElementType* getDataPointer() const { return constData; }

  /**
   * @brief Get an iterator pointing to the first element.
   *
   * (Actually the same as \c getDataPointer())
   * @example basicvector_matrix_access_iterator.cpp
   */
  inline iterator begin() { return data; }

  /**
   * @brief Get an iterator pointing beyond the last element.
   */
  inline iterator end() { return data + rows() * cols(); }

  /**
   * @brief Add \c e to each element of \c this.
   * @param e value
   * @return \c *this
   * @example basicvector_matrix_operator.cpp
   */
  inline MatrixT<ElementType>& operator+= (const ElementType& e);

  /**
   * @brief Subtract \c e from each element of \c this.
   * @param e value
   * @return \c *this
   */
  inline MatrixT<ElementType>& operator-= (const ElementType& e);

  /**
   * @brief Multiply each element of \c this with \c e.
   * @param e value
   * @return \c *this
   */
  inline MatrixT<ElementType>& operator*= (const ElementType& e);

  /**
   * @brief Divide each element of \c this through \c e.
   * @param e value
   * @return \c *this
   */
  inline MatrixT<ElementType>& operator/= (const ElementType& e);

  /**
   * @brief Add \c v to \c this.
   * @pre Size of \c v and \c this must be equal
   * @param v New data
   * @return \c *this
   */
  inline MatrixT<ElementType>& operator+= (const MatrixT<ElementType>& v);

  /**
   * @brief Subtract \c v from \c this.
   * @pre Size of \c v and \c this must be equal
   * @param v New data
   * @return \c *this
   */
  inline MatrixT<ElementType>& operator-= (const MatrixT<ElementType>& v);

//  /**
//   * @brief Multiplicate elementwise \c v to \c this.
//   * @pre Size of \c v and \c this must be equal
//   * @param v New data
//   * @return \c *this
//   */
//  inline MatrixT<ElementType>& operator*= (const MatrixT<ElementType>& v);

//  /**
//   * @brief Divide elementwise \c v from \c this.
//   * @pre Size of \c v and \c this must be equal
//   * @param v New data
//   * @return \c *this
//   */
//  inline MatrixT<ElementType>& operator/= (const MatrixT<ElementType>& v);

  /**
   * @brief Set this matrix to be the identity matrix
   */
  inline void setIdentity() {
    *this = ElementType(0);
    unsigned int m = std::min(rows(), cols());
    for (unsigned int i = 0; i < m; i++) {
      (*this)(i, i) = ElementType(1);
    }
  }

  /** add \c scale to each element of the main diagonal */
  void addIdentity( double scale );
  
  /** add \c scale * \c m to this */
  void addScaledMatrix( const ElementType & scale , const MatrixT<ElementType>& m);  

  /** add diagonal matrix (represented as a vector) */
  void addDiagonal( const VectorT<ElementType> & D );

  /**
   * Tensor product v * w^T, result goes to this matrix.
   * @param v First input vector
   * @param w Second input vector
   * @throw Exception if formats are inconsistent
   */
  void tensorProduct(const VectorT<ElementType>& v,
                     const VectorT<ElementType>& w);

  /**
   * Tensor product lambda * v * w^T, result goes to this matrix.
   * @param v First input vector
   * @param w Second input vector
   * @param lambda scale parameter
   * @throw Exception if formats are inconsistent
   */
  void addTensorProduct(double lambda, const VectorT<ElementType>& v,
                     const VectorT<ElementType>& w);

  /**
   * Matrix multiplication: this = a^{T if atranspose} * b^{T if btranspose}.
   * The formats of this, a and b must be consistent.
   * If this is empty (size 0x0), it will be resize.
   * @param a matrix to multiply (must NOT be the same object as \c this !)
   * @param b matrix to multiply (must NOT be the same object as \c this !)
   * @param atranspose use a.transpose() instead of a
   * @param btranspose use b.transpose() instead of b
   * @throw Exception if formats are inconsistent
   */
  void multiply(const MatrixT<ElementType>& a, const MatrixT<ElementType>& b,
                bool atranspose=false, bool btranspose=false);

  /**
   * Is an entry NaN?
   * @note This method is defined on floating point matrices only!
   */
  bool containsNaN() const;

  /**
   * @brief Returns 'true' if the memory is allocated externally
   * @return true if external storage
   */
  inline bool isExternal() const { return externalStorage; }

  /**
   * @brief Compare \c v with \c this.
   * @pre Size of \c v and \c this must be equal
   * @param a data to compare with
   * @param threshold difference of each entry which can be neglected
   * @return true if \c v and \c this are equal
   */
  inline bool isEqual(const MatrixT<ElementType> &a, ElementType threshold=static_cast<ElementType>(0)) const;

  /**
   * Square of the frobenius norm of this matrix.
   * Only defined for numerical ElementType.
   * @example basicvector_matrix_norm.cpp
   */
  ElementType squaredFrobeniusNorm() const;

  /**
   * Trace of the matrix.
   * Only defined for numeric ElementType, but also defined
   * for non-quadratic matrices!
   */
  ElementType trace() const;

  /**
   * Bilinear form: v^T Matrix v
   * Only defined for numerical ElementType and quadratic matrizes.
   */
  ElementType bilinear( const VectorT<ElementType> & v ) const;

  /**
   * Divide each row with its sum of all absolute values (L1-norm). 
   * The L1-norm of each row is 1 after this operation,
   * except for rows with a prior L1-norm near zero.
   */
  void normalizeRowsL1();

  /**
   * Divide each column with its sum of all absolute values (L1-norm).
   * The L1-norm of each column is 1 after this operation,
   * except for columns with a prior L1-norm near zero.
   */
  void normalizeColumnsL1();

  /**
   * Frobenius norm of this matrix. Only defined for numerical ElementType.
   */
  inline ElementType frobeniusNorm() const {
    return static_cast<ElementType>(sqrt(squaredFrobeniusNorm()));
  }

#ifdef NICE_USELIB_LINAL
  /**
   * Copy data from linal matrix
   */
  explicit MatrixT(const LinAl::Matrix<ElementType>& m);

  /**
   * @brief Copy data from \c v to \c this.
   * @pre Size of \c v and \c this must be equal or this must have size 0x0
   * @param v New data
   * @return \c *this
   */
  inline MatrixT<ElementType>& operator=(const LinAl::Matrix<ElementType>& v);

  /**
   * Shallow copy data to LinAl matrix
   */
  inline LinAl::MatrixCF<ElementType> linal() {
    return LinAl::MatrixCF<ElementType>(data, rows(), cols(), true);
  }

  /**
   * Copy data to LinAl matrix
   */
  inline LinAl::MatrixCF<ElementType> linal() const {
    return LinAl::MatrixCF<ElementType>(data, rows(), cols());
  }
#endif // NICE_USELIB_LINAL

protected:
  /**
   * Are we using external storage?
   */
  bool externalStorage;

  /**
   * Const pointer to the data.
   */
  const ElementType* constData;

  /**
   * Pointer to the data.
   * @note This has to point to the same adress as constData!
   *       (NULL is only const data is available)
   */
  ElementType* data;

  /**
   * Size of the vector
   */
  size_t m_rows;
  size_t m_cols;

  inline void setDataPointer(ElementType* _data, size_t rows, size_t cols,
                             bool _externalStorage) {
    data = _data;
    constData = _data;
    m_rows = rows;
    m_cols = cols;
    externalStorage = _externalStorage;
  }

  inline void setConstDataPointer(const ElementType* _data,
                                  size_t rows, size_t cols) {
    data = NULL;
    constData = _data;
    m_rows = rows;
    m_cols = cols;
    externalStorage = true;
  }

//   virtual void read(std::istream& stream);
//
//   virtual void write(std::ostream& stream) const;

};

template <class ElementType>
inline std::istream&
operator >> (std::istream& input, MatrixT<ElementType>& v) {
  size_t w, h;
  char c;
  input >> w >> c >> h;
  if (c != 'x') {
    fthrow(Exception, "Error reading MatrixT from stream: expected x, got " << c);
  }
  v.resize(w, h);
  for (size_t r = 0; r < v.rows(); r++) {
    for (size_t c = 0; c < v.cols(); c++) {
      input >> v(r, c);
    }
  }
  return input;
}

template <class ElementType>
inline std::ostream&
operator << (std::ostream& output, const MatrixT<ElementType>& v) {
  output << v.rows() << " x " << v.cols() << std::endl;
  for (size_t r = 0; r < v.rows(); r++) {
    for (size_t c = 0; c < v.cols(); c++) {
      output << v(r, c) << " ";
    }
    output << std::endl;
  }
  return output;
}


template <class Tp>
inline NICE::ibinstream& operator>>(NICE::ibinstream& s, MatrixT<Tp> &r)
{
  unsigned int rows;
  unsigned int cols;
  s >> rows;
  s >> cols;
  r.resize(rows,cols);
  typename MatrixT<Tp>::iterator it=r.begin();
  for(;it!=r.end();it++)
    s>>*it;
  return s;
}

template <class Tp>
inline NICE::obinstream& operator<<(NICE::obinstream& s, const MatrixT<Tp>& r)
{
  unsigned int rows=r.rows();
  unsigned int cols=r.cols();
  s<<rows;
  s<<cols;
  typename MatrixT<Tp>::const_iterator it=r.begin();
  for(;it!=r.end();it++)
    s << *it;
  return s;
}

typedef MatrixT<bool>   BoolMatrix;
typedef MatrixT<char>   CharMatrix;
typedef MatrixT<int>    IntMatrix;
typedef MatrixT<float>  FloatMatrix;
typedef MatrixT<double> Matrix;

/** Matrix addition */
template<class ElementType>
MatrixT<ElementType> operator+(const MatrixT<ElementType> &, const MatrixT<ElementType>&);

/** Matrix substraction */
template<class ElementType>
MatrixT<ElementType> operator-(const MatrixT<ElementType>&, const MatrixT<ElementType>&);

/** Matrix (right) multiplication with a scalar */
template<class ElementType>
MatrixT<ElementType> operator*(const MatrixT<ElementType>&, const double);

/** Matrix (left) multiplication with a scalar */
template<class ElementType>
MatrixT<ElementType> operator*(const double, const MatrixT<ElementType>&);

/** Matrix multiplication with a vector */
template<class ElementType>
VectorT<ElementType> operator*(const MatrixT<ElementType>&, const VectorT<ElementType>& );

/** Matrix multiplication with a matrix */
template<class ElementType>
MatrixT<ElementType> operator*(const MatrixT<ElementType>&, const MatrixT<ElementType>& );

/** Kronecker product of two matrices */
template<class ElementType>
void kroneckerProduct (const MatrixT<ElementType>& A, const MatrixT<ElementType>& B, MatrixT<ElementType>& dst);

/** Multiply the kronecker product of two matrices with a vector */
template <typename T>
void kroneckerProductMultiplication ( const MatrixT<T> & A, const MatrixT<T> & B, const Vector & x, Vector & y );

/** The vector x is divided in parts of size blockSize, these parts are multiplied with A and concatenated
 * to the results. The operation is equivalent to kroneckerProductMultiplication with B being a identity matrix. */
template <typename T>
void blockwiseMultiplication ( const MatrixT<T> & A, uint blockSize, const Vector & x, Vector & y );


}

//#ifdef __GNUC__
#include "core/vector/MatrixT.tcc"
//#endif

#endif // _EMATRIX_BASICVECTOR_H

