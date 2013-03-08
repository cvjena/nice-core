/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libbasicvector - A simple vector library
 * See file License for license information.
 */
#ifndef _CHECKEDEMATRIX_BASICMATRIX_H
#define _CHECKEDEMATRIX_BASICMATRIX_H

#include "core/vector/RowMatrixT.h"

namespace NICE {

/**
 * @brief This subclass of \c RowMatrixT performs additional checks at runtime,
 *        especially range checks for element access.
 * 
 * Theses checks are implemented via "non-virtual overriding".
 * This means that checked versions of methods
 * (in this class as opposed to un-checked versions in \c RowMatrixT)
 * are only called if the object is CheckedRowMatrixT in the <b>static</b>
 * context. Example:<br>
 * @verbatim
 *   CheckedRowMatrixT<float> v(10, 4.5);
 *   RowMatrixT<float>& w = v;
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
class CheckedRowMatrixT : public RowMatrixT<ElementType> {
public:
  inline CheckedRowMatrixT() : RowMatrixT<ElementType>() {}

  explicit CheckedRowMatrixT(const size_t rows, const size_t cols)
      : RowMatrixT<ElementType>(rows, cols) {}

  CheckedRowMatrixT(const size_t rows, const size_t cols,
                 const ElementType& element)
      : RowMatrixT<ElementType>(rows, cols, element) {}

  CheckedRowMatrixT(const ElementType* _data, const size_t rows, const size_t cols)
      : RowMatrixT<ElementType>(_data, rows, cols) {}

  CheckedRowMatrixT(ElementType* _data, const size_t rows, const size_t cols, 
                 const typename RowMatrixT<ElementType>::Mode mode
                   = MatrixBase::copy)
      : RowMatrixT<ElementType>(_data, rows, cols, mode) {}

  explicit CheckedRowMatrixT(std::istream& input)
      : RowMatrixT<ElementType>(input) {}

  CheckedRowMatrixT(const CheckedRowMatrixT<ElementType>& v)
      : RowMatrixT<ElementType>(v) {}

  CheckedRowMatrixT(const RowMatrixT<ElementType>& v)
      : RowMatrixT<ElementType>(v) {}

  /**
   * Retrieve a reference to Element (i,j)
   * @param i row
   * @param j col
   */
  inline typename RowMatrixT<ElementType>::reference
  operator()(const ptrdiff_t i, const ptrdiff_t j) {
    if (i < 0 || static_cast<unsigned int>(i) >= this->rows()
        || j < 0 || static_cast<unsigned int>(j) >= this->cols()) {
        std::out_of_range("RowMatrixT () access out of range"); 
    }
    return RowMatrixT<ElementType>::operator()(i, j);
  }
  
  virtual ~CheckedRowMatrixT();
};

template<class ElementType> CheckedRowMatrixT<ElementType>::~CheckedRowMatrixT() {
}

}
#endif // _CHECKEDEMATRIX_BASICMATRIX_H
