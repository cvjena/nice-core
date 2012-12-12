#include <string>
#include <sstream>
#include <stdexcept>
#include "core/basics/Exception.h"
#define _THROW_ERowMatrix(string) fthrow(Exception, string)
#include "core/vector/ippwrapper.h"
#include "core/vector/RowMatrixT.h"

namespace NICE {

template<typename ElementType>
inline RowMatrixT<ElementType>::RowMatrixT() {
  setDataPointer(NULL, 0, 0, false);
}

template<typename ElementType>
inline RowMatrixT<ElementType>::RowMatrixT(const size_t rows, const size_t cols) {
  setDataPointer(new ElementType[rows * cols], rows, cols, false);
}

#ifdef NICE_USELIB_LINAL
template<typename ElementType>
inline RowMatrixT<ElementType>::RowMatrixT(const LinAl::Matrix<ElementType>& m) {
  setDataPointer(new ElementType[m.rows() * m.cols()], 
                 m.rows(), m.cols(), false);
  for (unsigned int i = 0; i < rows(); i++) {
    for (unsigned int j = 0; j < cols(); j++) {
      (*this)(i, j) = m(i, j);
    }
  }
}
#endif // NICE_USELIB_LINAL

template<typename ElementType>
inline RowMatrixT<ElementType>::RowMatrixT(const size_t rows, const size_t cols,
                                     const ElementType& element) {
  setDataPointer(new ElementType[rows * cols], rows, cols, false);
  ippsSet(element, getDataPointer(), rows * cols);
}

template<typename ElementType>
inline RowMatrixT<ElementType>::RowMatrixT(const ElementType* _data, 
                                     const size_t rows, const size_t cols) {
  setDataPointer(new ElementType[rows * cols], rows, cols, false);
  ippsCopy(_data, getDataPointer(), rows * cols);
}

template<typename ElementType>
inline RowMatrixT<ElementType>::RowMatrixT(ElementType* _data,
                                     const size_t rows, const size_t cols,
                                     const MatrixBase::Mode mode) {
  switch (mode) {
  case external:
    setDataPointer(_data, rows, cols, true);
    break;
  case copy:
    setDataPointer(new ElementType[rows * cols], rows, cols, false);
    ippsCopy(_data, getDataPointer(), rows * cols);
    break;
   default:
     setDataPointer(NULL, 0, 0, false);
     _THROW_ERowMatrix("Unknown Mode-enum.");
  }
}

//template <class ElementType>
//inline RowMatrixT<ElementType>::RowMatrixT(std::istream& input) {
//  input >> dataSize;
//  setDataPointer(new ElementType[dataSize], dataSize, false);
//  
//  char c;
//  input >> c;
//  if (c != '<') {
//    _THROW_ERowMatrix("syntax error reading RowMatrixT");
//  }
//  
//  unsigned int i = -1;
//  while (true) {
//    std::string s;
//    input >> s;
//    if (s == ">") {
//      break;
//    }
//    i++;
//    if (i > dataSize) {
//      _THROW_ERowMatrix("syntax error reading RowMatrixT");
//    }
//    std::stringstream st(s);
//    ElementType x;
//    st >> x;
//    getDataPointer()[i] = x;
//  }
//}

template<typename ElementType>
RowMatrixT<ElementType>::RowMatrixT(const RowMatrixT<ElementType>& v) {
  setDataPointer(new ElementType[v.rows() * v.cols()],
                 v.rows(), v.cols(), false);
  ippsCopy(v.getDataPointer(), getDataPointer(), v.rows() * v.cols());
}

template<typename ElementType>
inline RowMatrixT<ElementType>::~RowMatrixT() {
  if (!externalStorage && data != NULL) {
    delete[] data;
    setDataPointer(NULL, 0, 0, false);
  }
}

template<typename ElementType>
void RowMatrixT<ElementType>::resize(size_t _rows, size_t _cols) {
  if (rows() * cols() == _rows * _cols) {
    m_rows = _rows;
    m_cols = _cols;
    return;
  }
  
  if (externalStorage) {
    if (_rows * _cols < rows() * cols()) {
      m_rows = _rows;
      m_cols = _cols;
      return;
    }
    _THROW_ERowMatrix("Cannot resize RowMatrixT (external storage used)");
  }
  
  if (getDataPointer() != NULL) {
    size_t oldRows = rows();
    size_t oldCols = cols();
    ElementType* tmp = getDataPointer();
    setDataPointer(new ElementType[_rows * _cols], _rows, _cols, false);
    ippsCopy(tmp, getDataPointer(), std::min(_rows * _cols, oldRows * oldCols));
    delete[] tmp;
  } else {
    setDataPointer(new ElementType[_rows * _cols], _rows, _cols, false);
  }
}

template<class ElementType>
inline const RowMatrixT<ElementType>*
RowMatrixT<ElementType>::createConst(const ElementType* _data, 
                                  const size_t rows, const size_t cols) {
  RowMatrixT<ElementType>* result = new RowMatrixT<ElementType>;
  result->setConstDataPointer(_data, rows, cols);
  return result;
}

template<class ElementType>
inline const VectorT<ElementType> RowMatrixT<ElementType>::getRowRef(uint i) const
{
    const VectorT<ElementType> row(constData[i * cols()],cols(),VectorBase::external);
    return row;
}

template<class ElementType>
inline VectorT<ElementType> RowMatrixT<ElementType>::getRowRef(uint i)
{
    VectorT<ElementType> row(data[i * cols()],cols(),VectorBase::external);
    return row;
}

template<class ElementType>
inline VectorT<ElementType> RowMatrixT<ElementType>::getRow(uint i) const
{
    VectorT<ElementType> row(constData[i * cols()],cols());
    return row;
}

template<class ElementType>
inline VectorT<ElementType> RowMatrixT<ElementType>::getColumn(uint i) const
{
    VectorT<ElementType> column(rows());
    for(int j=0;j<rows();j++) {
        column(j)=(*this)(j, i);
    }
    return column;
}

template<class ElementType>
inline bool 
RowMatrixT<ElementType>::operator==(const RowMatrixT<ElementType>& v) const {
  if (this->rows() != v.rows() || this->cols() != v.cols()) {
    throw std::invalid_argument(
      "RowMatrixT::operator==(): v.rows/cols() != rows/cols()");
  } else if (rows() == 0 || cols() == 0) {
    return true;
  } 
  for (unsigned int i = 0; i < rows(); i++) {
    for (unsigned int j = 0; j < cols(); j++) {
      if (!(operator()(i, j) == v(i, j))) {
        return false;
      }
    }
  }
  return true;
}

template<class ElementType>
inline bool 
RowMatrixT<ElementType>::operator!=(const RowMatrixT<ElementType>& v) const {
  if (this->rows() != v.rows() || this->cols() != v.cols()) {
    throw std::invalid_argument(
      "RowMatrixT::operator!=(): v.rows/cols() != rows/cols()");
  } else if (rows() == 0 || cols() == 0) {
    return false;
  } 
  for (unsigned int i = 0; i < rows(); i++) {
    for (unsigned int j = 0; j < cols(); j++) {
      if (!(operator()(i, j) == v(i, j))) {
        return true;
      }
    }
  }
  return false;
}


template<typename ElementType>
inline RowMatrixT<ElementType>&
RowMatrixT<ElementType>::operator=(const RowMatrixT<ElementType>& v) {
  if (rows() * cols() == 0 && !externalStorage && getDataPointer() == NULL) {
    setDataPointer(new ElementType[v.rows() * v.cols()],
                   v.rows(), v.cols(), false);
  } else if (this->rows() != v.rows() || this->cols() != v.cols()) {
    this->resize(v.rows(),v.cols());
  }
  ippsCopy(v.getDataPointer(), getDataPointer(), v.rows() * v.cols());
  return *this;
}

template<typename ElementType>
inline RowMatrixT<ElementType>&
RowMatrixT<ElementType>::operator=(const ElementType& element) {
  ippsSet(element, getDataPointer(), this->rows() * this->cols());
  return *this;
}

template<typename ElementType>
void RowMatrixT<ElementType>::transposeInplace() {
  if (rows() != cols()) {
    _THROW_ERowMatrix("transposeInplace(): matrix has to be quadratic");
  }
  
  for (unsigned int j = 1; j < cols(); j++) {
    for (unsigned int i = 0; i < j; i++) {
      std::swap((*this)(i, j), (*this)(j, i));
    }
  }
}

template<typename ElementType>
RowMatrixT<ElementType> RowMatrixT<ElementType>::transpose() {
  RowMatrixT<ElementType> result(cols(),rows());
// #ifdef NICE_USELIB_IPP
  size_t tsize = sizeof(ElementType);
  IppStatus ret = ippmTranspose_m(getDataPointer(), cols()*tsize, tsize,
                                  cols(), rows(), 
                                  result.getDataPointer(), rows()*tsize, tsize);
  if (ret!=ippStsNoErr) {
    _THROW_ERowMatrix(ippGetStatusString(ret));
  }
// #else
//   for (unsigned int i = 0; i < rows(); i++) {
//     for (unsigned int j = 0; j < cols(); j++) {
//       result(j, i) = (*this)(i, j);
//     }
//   }
// #endif
  return result;
}

#define _DEFINE_ERowMatrix_AUGMENTED_ASSIGNMENT(_Op, _Name)               \
template<class ElementType>                                            \
inline RowMatrixT<ElementType> &                                          \
RowMatrixT<ElementType>::operator _Op##= (const ElementType& v) {    \
  ipps##_Name##C_I(v, getDataPointer(), this->rows() * this->cols());    \
  return *this;                                                        \
}

_DEFINE_ERowMatrix_AUGMENTED_ASSIGNMENT(+, Add)
_DEFINE_ERowMatrix_AUGMENTED_ASSIGNMENT(-, Sub)
_DEFINE_ERowMatrix_AUGMENTED_ASSIGNMENT(*, Mul)
_DEFINE_ERowMatrix_AUGMENTED_ASSIGNMENT(/, Div)

#define _DEFINE_ERowMatrix_ASSIGNMENT(_Op, _Name)               \
template<class ElementType>                                            \
inline RowMatrixT<ElementType> &                                          \
RowMatrixT<ElementType>::operator _Op##= (const RowMatrixT<ElementType>& v) {    \
  if(this->rows() != v.rows() || this->cols() != v. cols())               \
     _THROW_ERowMatrix("RowMatrixT: different data size");             \
  ipps##_Name##_I(v.getDataPointer(), getDataPointer(),           \
                  this->rows() * this->cols());  \
  return *this;                                                        \
}

_DEFINE_ERowMatrix_ASSIGNMENT(+, Add)
_DEFINE_ERowMatrix_ASSIGNMENT(-, Sub)
//_DEFINE_ERowMatrix_ASSIGNMENT(*, Mul)
//_DEFINE_ERowMatrix_ASSIGNMENT(/, Div)

template<typename ElementType>
void RowMatrixT<ElementType>::multiply(const RowMatrixT<ElementType>& a,
                                    const RowMatrixT<ElementType>& b,
                                    bool atranspose,
                                    bool btranspose) {
  if (this == &a || this == &b) {
    _THROW_ERowMatrix(
      "Matrix multiplication: a and b must not be the same object as this.");
  }
                                      
  size_t arows, acols;
  if(atranspose) {
    arows=a.cols();
    acols=a.rows();
  } else {
    arows=a.rows();
    acols=a.cols();
  }
  
  size_t brows, bcols;
  if(btranspose) {
    brows=b.cols();
    bcols=b.rows();
  } else {
    brows=b.rows();
    bcols=b.cols();
  }

  if (acols != brows) {
    _THROW_ERowMatrix("Matrix multiplication: inconsistent sizes of factors.");
  }
  if (rows() == 0 && cols() == 0) {
    resize(arows, bcols);
  }
  if (rows() != arows || cols() != bcols) {
    _THROW_ERowMatrix("Matrix multiplication: inconsistent size of result matriq.");
  }

#ifdef NICE_USELIB_IPP 
  size_t tsize=sizeof(ElementType);
  IppStatus ret;
  if(atranspose) {
    if(btranspose) {
        ret = ippmMul_tt(a.getDataPointer(), a.cols()*tsize, tsize, a.cols(), a.rows(), 
                         b.getDataPointer(), b.cols()*tsize, tsize, b.cols(), b.rows(),
                         this->getDataPointer(), cols()*tsize, tsize);
    } else {
        ret = ippmMul_tm(a.getDataPointer(), a.cols()*tsize, tsize, a.cols(), a.rows(), 
                         b.getDataPointer(), b.cols()*tsize, tsize, b.cols(), b.rows(),
                         this->getDataPointer(), cols()*tsize, tsize);
    }
  } else {
    if(btranspose) {
        ret = ippmMul_mt(a.getDataPointer(), a.cols()*tsize, tsize, a.cols(), a.rows(), 
                         b.getDataPointer(), b.cols()*tsize, tsize, b.cols(), b.rows(),
                         this->getDataPointer(), cols()*tsize, tsize);
    } else {
        ret = ippmMul_mm(a.getDataPointer(), a.cols()*tsize, tsize, a.cols(), a.rows(), 
                         b.getDataPointer(), b.cols()*tsize, tsize, b.cols(), b.rows(),
                         this->getDataPointer(), cols()*tsize, tsize);
    }
  }
  if(ret!=ippStsNoErr)
     _THROW_ERowMatrix(ippGetStatusString(ret));
#else
  // FIXME not very efficient
  ElementType ela, elb;
  for (unsigned int i = 0; i < rows(); i++) {
    for (unsigned int j = 0; j < cols(); j++) {
      ElementType sum = ElementType(0);
      for (unsigned int k = 0; k < acols; k++) {
        ela = atranspose ? a(k, i) : a(i, k);
        elb = btranspose ? b(j, k) : b(k, j);
        sum += ela * elb;
      }
      (*this)(i, j) = sum;
    }
  }
#endif
}

template<typename ElementType>
bool RowMatrixT<ElementType>::containsNaN() const {
  for (unsigned int r = 0; r < rows(); r++) {
    for (unsigned int c = 0; c < cols(); c++) {
      if (isNaN((*this)(r, c))) {
        return true;
      }
    }
  }
  return false;
}

template<typename ElementType>
inline bool RowMatrixT<ElementType>::isEqual(const RowMatrixT<ElementType> &a, ElementType threshold) const
{
  if(this->rows() != a.rows() || this->cols() != a.cols())
     _THROW_ERowMatrix("RowMatrixT: different data size");
  for (unsigned int i = 0; i < rows(); i++) {
    for (unsigned int j = 0; j < cols(); j++) {
       if(abs((*this)(i, j)-a(i,j))>threshold)
           return false;
    }
  }
  return true;
}

template<typename ElementType>
ElementType RowMatrixT<ElementType>::squaredFrobeniusNorm() const {
  double sum = ElementType(0);
  for (unsigned int i = 0; i < rows(); i++) {
    for (unsigned int j = 0; j < cols(); j++) {
      sum += square((*this)(i, j));
    }
  }
  return sum;
}

}
