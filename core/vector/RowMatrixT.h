/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libbasicvector - A simple vector library
 * See file License for license information.
 */
#ifndef _EROWMATRIX_BASICVECTOR_H
#define _EROWMATRIX_BASICVECTOR_H


#include <cstdlib>
#include <string>
#include <sstream>
#include <stdexcept>
#include <core/basics/numerictools.h>
#ifdef NICE_USELIB_LINAL
#include <LinAl/matrixCF.h>
#endif

#include "core/vector/MatrixBase.h"
#include "core/vector/VectorT.h"

namespace NICE {

/**
 * @brief  RowMatrixT is a simple row matrix template class
 * @author Frank Mattern (based on \c MatrixT)
 *
 * This is a row major variant of MatrixT. If you don't know whether to choose
 * MatrixT or RowMatrixT, you should take MatrixT.
 *
 * \c RowMatrixT is a simple matrix class which provides the (optional) ability
 * to use externally allocated memory as storage.
 * The main features are:
 * - In concept an efficient implementation of a mathematical matrix
 * - An array-like storage class
 * - Support for externally allocated memory
 * - Ability to get pointer to internal memory
 * - Thus the ability to <b>directly</b> interface with other libraries such as
 *   LinAl without time consuming data copying. HOWEVER: LinAl in column major.
 *   MatrixT is better for interfacing with LinAl.
 *
 * @note
 * This class is in a preliminary state!
 * Todo: is the distinction between shallow and deep copy always clear?
 */
template<class ElementType>
class RowMatrixT : public MatrixBase {
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
   * @brief Create an empty \c RowMatrixT with size zero.
   *
   * Such an object is actually useless, but sometimes you may need to have
   * such instances to initalize some data structure.
   * The only way to turn such an object into something useful is operator=().
   */
  RowMatrixT();

  /**
   * @brief Create an \c RowMatrixT with size \c size.
   *        Data will not be initialized.
   * @param rows  number of rows
   * @param cols  number of cols
   */
  explicit RowMatrixT(const size_t rows, const size_t cols);

  /**
   * @brief Create an \c RowMatrixT with size \c size.
   *        Data will be initialized to \c element.
   * @param rows    number of rows
   * @param cols    number of cols
   * @param element initial value of all elements
   */
  RowMatrixT(const size_t rows, const size_t cols, const ElementType& element);

  /**
   * @brief Create an \c RowMatrixT of size \c size.
   *        It will be initialized with the data pointed to by \c _data.
   *
   * That is the first \c size elements of \c _data will be copied.
   * @param _data data to be copied
   * @param rows  number of rows
   * @param cols  number of cols
   */
  RowMatrixT(const ElementType* _data, const size_t rows, const size_t cols);

  /**
   * @brief Create an \c RowMatrixT of size \c size
   *        with optionally external storage.
   *
   * It will be initialized with the data pointed to by \c _data.
   * The parameter _external control whether the data will be copied or
   * the pointer \c _data is directly kept as storage for the \c RowMatrixT.
   * In case of external storage the data will not be deleted in the destructor.
   * @param _data External data storage
   * @param rows  number of rows of the external storage
   * @param cols  number of cols of the external storage
   * @param mode Storage mode: keep external memory or copy data.
   */
  RowMatrixT(ElementType* _data, const size_t rows, const size_t cols,
          const MatrixBase::Mode mode = copy);

  // /**
  // * @brief Read from input stream.
  // * @param input Read from here
  // */
  //explicit RowMatrixT(std::istream& input);

  /**
   * @brief copy constructor
   * @param v RowMatrixT where to copy data from
   */
  RowMatrixT(const RowMatrixT<ElementType>& v);

  virtual ~RowMatrixT();

  /**
   * @brief Create a const RowMatrixT of size \c size
   *        with <b>external</b> storage.
   *
   * It will be initialized with the data pointed to by %_data.
   * The data will not be deleted in the destructor.
   * @param _data External data storage
   * @param rows  number of rows of the external storage
   * @param cols  number of cols of the external storage
   */
  inline static const RowMatrixT<ElementType>* createConst(
                                              const ElementType* _data,
                                              const size_t rows,
                                              const size_t cols);

  /**
   * @brief Read access to elements.
   * @param row row to access
   * @param col col to access
   * @return Element (as const reference)
   */
  inline const_reference operator()(const ptrdiff_t row,
                                    const ptrdiff_t col) const {
    return constData[col + row * cols()];
  }

  /**
   * @brief Read access to elements.
   * @param row row to access
   * @param col col to access
   * @return Element (as const reference)
   */
  inline reference operator()(const ptrdiff_t row,
                              const ptrdiff_t col) {
    return data[col + row * cols()];
  }

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
   * @brief Return the number of rows of this RowMatrixT.
   * @return Size of this RowMatrixT.
   */
  inline size_t rows() const { return m_rows; }

  /**
   * @brief Return the number of columns of this RowMatrixT.
   * @return Size of this RowMatrixT.
   */
  inline size_t cols() const { return m_cols; }

  /**
   * @brief Compare \c v with \c this.
   * @pre Size of \c v and \c this must be equal
   * @param v data to compare with
   * @return true if \c v and \c this are equal
   */
  inline bool operator== (const RowMatrixT<ElementType>& v) const;

  /**
   * @brief Compare \c v with \c this.
   * @pre Size of \c v and \c this must be equal
   * @param v data to compare with
   * @return \c *this
   * @return true if \c v and \c this are not equal
   */
  inline bool operator!= (const RowMatrixT<ElementType>& v) const;

  /**
   * @brief Change the number of RowMatrixT elements
   * @param rows number of rows of the \c RowMatrixT
   * @param cols number of cols of the \c RowMatrixT
   * @throw std::runtime_error if using external storage and \c size > \c size()
   * @note Changing the size of the vector invalidates all iterators
   *       and pointers held to the data.
   */
   inline void resize(size_t rows, size_t cols);

  /**
   * @brief Transpose a quadratic RowMatrixT.
   * @throw Exception if matrix is not square.
   */
   inline void transposeInplace();

  /**
   * @brief return a transposed RowMatrixT.
   * @return transposed matrix
   */
   RowMatrixT<ElementType> transpose();

  /**
   * @brief Copy data from \c v to \c this.
   * @param v New data
   * @return \c *this
   */
  inline RowMatrixT<ElementType>& operator=(const RowMatrixT<ElementType>& v);

  /**
   * @brief Set all elements to value \c element
   * @param element New value of all elements
   */
  inline RowMatrixT<ElementType>& operator=(const ElementType& element);

  /**
   * @brief Set all elements to value \c element
   * @param element New value of all elements
   */
  inline void set(const ElementType& element) {
    *this = element;
  }

  /**
   * @brief Get a pointer to the internal memory.
   */
//   inline operator ElementType* () { return data; }

  /**
   * @brief Get a pointer to the internal memory.
   */
  inline ElementType* getDataPointer() { return data; }

  /**
   * @brief Get the ith row of the matrix and return an VectorT with is a reference to the internal memory.
   * @param i number of row
   */
  inline const VectorT<ElementType> getRowRef(uint i) const;

  /**
   * @brief Get the ith row of the matrix and return an VectorT with is a reference to the internal memory.
   * @param i number of row
   */
  inline VectorT<ElementType> getRowRef(uint i);

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
   */
  inline RowMatrixT<ElementType>& operator+= (const ElementType& e);

  /**
   * @brief Subtract \c e from each element of \c this.
   * @param e value
   * @return \c *this
   */
  inline RowMatrixT<ElementType>& operator-= (const ElementType& e);

  /**
   * @brief Multiply each element of \c this with \c e.
   * @param e value
   * @return \c *this
   */
  inline RowMatrixT<ElementType>& operator*= (const ElementType& e);

  /**
   * @brief Divide each element of \c this through \c e.
   * @param e value
   * @return \c *this
   */
  inline RowMatrixT<ElementType>& operator/= (const ElementType& e);

  /**
   * @brief Add \c v to \c this.
   * @pre Size of \c v and \c this must be equal
   * @param v New data
   * @return \c *this
   */
  inline RowMatrixT<ElementType>& operator+= (const RowMatrixT<ElementType>& v);

  /**
   * @brief Subtract \c v from \c this.
   * @pre Size of \c v and \c this must be equal
   * @param v New data
   * @return \c *this
   */
  inline RowMatrixT<ElementType>& operator-= (const RowMatrixT<ElementType>& v);

//  /**
//   * @brief Multiplicate elementwise \c v to \c this.
//   * @pre Size of \c v and \c this must be equal
//   * @param v New data
//   * @return \c *this
//   */
//  inline RowMatrixT<ElementType>& operator*= (const RowMatrixT<ElementType>& v);

//  /**
//   * @brief Divide elementwise \c v from \c this.
//   * @pre Size of \c v and \c this must be equal
//   * @param v New data
//   * @return \c *this
//   */
//  inline RowMatrixT<ElementType>& operator/= (const RowMatrixT<ElementType>& v);

  /**
   * Set this matrix to be the identity matrix
   */
  inline void setIdentity() {
    *this = ElementType(0);
    unsigned int m = std::min(rows(), cols());
    for (unsigned int i = 0; i < m; i++) {
      (*this)(i, i) = ElementType(1);
    }
  }

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
  void multiply(const RowMatrixT<ElementType>& a, const RowMatrixT<ElementType>& b, bool atranspose=false, bool btranspose=false);

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
  inline bool isEqual(const RowMatrixT<ElementType> &a, ElementType threshold=static_cast<ElementType>(0)) const;

  /**
   * Square of the frobenius norm of this matrix.
   * Only defined for numerical ElementType.
   */
  ElementType squaredFrobeniusNorm() const;

  /**
   * Frobenius norm of this matrix. Only defined for numerical ElementType.
   */
  inline ElementType frobeniusNorm() const {
    return sqrt(squaredFrobeniusNorm());
  }

#ifdef NICE_USELIB_LINAL
  RowMatrixT(const LinAl::Matrix<ElementType>& m);

  inline LinAl::MatrixCF<ElementType> linal() {
    return LinAl::MatrixCF<ElementType>(data, rows(), cols(), true);
  }

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
};

template <class ElementType>
inline std::istream&
operator >> (std::istream& input, RowMatrixT<ElementType>& v) {
  size_t w, h;
  char c;
  input >> w >> c >> h;
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
operator << (std::ostream& output, const RowMatrixT<ElementType>& v) {
  output << v.rows() << " x " << v.cols() << std::endl;
  for (size_t r = 0; r < v.rows(); r++) {
    for (size_t c = 0; c < v.cols(); c++) {
      output << v(r, c) << " ";
    }
    output << std::endl;
  }
  return output;
}

typedef RowMatrixT<int>   IntRowMatrix;
typedef RowMatrixT<float> FloatRowMatrix;
typedef RowMatrixT<double> DoubleRowMatrix;
typedef RowMatrixT<char>  CharRowMatrix;
}

//#ifdef __GNUC__
#include "core/vector/RowMatrixT.tcc"
//#endif

#endif // _EROWMATRIX_BASICVECTOR_H

