/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libbasicvector - A simple vector library
 * See file License for license information.
 */
#ifndef _CHECKEDEMATRIX_BASICMATRIX_H
#define _CHECKEDEMATRIX_BASICMATRIX_H

#include "core/vector/MatrixT.h"

namespace NICE {

/**
 * @brief This subclass of \c MatrixT performs additional checks at runtime,
 *        especially range checks for element access.
 * 
 * Theses checks are implemented via "non-virtual overriding".
 * This means that checked versions of methods
 * (in this class as opposed to un-checked versions in \c MatrixT)
 * are only called if the object is CheckedMatrixT in the <b>static</b>
 * context. Example:<br>
 * @verbatim
 *   CheckedMatrixT<float> v(10, 4.5);
 *   MatrixT<float>& w = v;
 *   try {
 *     v[10]; // will throw range_exception
 *   } catch (std::range_exception) {
 *   }
 *   w[10]; // will NOT throw an exception
 *          // and (probably) cause a segmentation fault
 * @endverbatim
 * 
 * See base class for further documentation.
 */
template<class ElementType>
class CheckedMatrixT : public MatrixT<ElementType> {
public:
  inline CheckedMatrixT() : MatrixT<ElementType>() {}

  explicit CheckedMatrixT(const size_t rows, const size_t cols)
      : MatrixT<ElementType>(rows, cols) {}

  /**
   * Create a \c CheckedMatrixT
   * @param rows    number of rows
   * @param cols    number of cols
   * @param element initialize the elements of \c CheckedMatrixT with the value \c element
   */
  CheckedMatrixT(const size_t rows, const size_t cols,
                 const ElementType& element)
      : MatrixT<ElementType>(rows, cols, element) {}

  /**
   * Create a \c CheckedMatrixT
   * @param _data   pointer to the data of the \c CheckedMatrixT
   * @param rows    number of rows of the data
   * @param cols    number of cols of the data
   */
  CheckedMatrixT(const ElementType* _data, const size_t rows, const size_t cols)
      : MatrixT<ElementType>(_data, rows, cols) {}

  /**
   * Create a \c CheckedMatrixT
   * @param _data   pointer to the data of the \c CheckedMatrixT
   * @param rows    number of rows of the data
   * @param cols    number of cols of the data
   * @param mode    copy mode
   */
  CheckedMatrixT(ElementType* _data, const size_t rows, const size_t cols, 
                 const typename MatrixT<ElementType>::Mode mode
                   = MatrixBase::copy)
      : MatrixT<ElementType>(_data, rows, cols, mode) {}

  explicit CheckedMatrixT(std::istream& input)
      : MatrixT<ElementType>(input) {}

  CheckedMatrixT(const CheckedMatrixT<ElementType>& v)
      : MatrixT<ElementType>(v) {}

  CheckedMatrixT(const MatrixT<ElementType>& v)
      : MatrixT<ElementType>(v) {}

  /**
   * Retrieve a reference to Element (i,j)
   * @param i row
   * @param j col
   */
  inline typename MatrixT<ElementType>::reference
  operator()(const ptrdiff_t i, const ptrdiff_t j) {
    if (i < 0 || static_cast<unsigned int>(i) >= this->rows()
        || j < 0 || static_cast<unsigned int>(j) >= this->cols()) {
        throw std::out_of_range("MatrixT () access out of range"); 
    }
    return MatrixT<ElementType>::operator()(i, j);
  }
  
  virtual ~CheckedMatrixT();
};

template<class ElementType>
CheckedMatrixT<ElementType>::~CheckedMatrixT() {
}

}
#endif // _CHECKEDEMATRIX_BASICMATRIX_H
