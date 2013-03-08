/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libbasicvector - A simple vector library
 * See file License for license information.
 */
#ifndef _CHECKEDEVECTOR_H_
#define _CHECKEDEVECTOR_H_

#include "core/vector/VectorT.h"

namespace NICE {

/**
 * @brief This subclass of \c VectorT performs additional checks at runtime,
 *        especially range checks for element access.
 * 
 * Theses checks are implemented via "non-virtual overriding".
 * This means that checked versions of methods
 * (in this class as opposed to un-checked versions in \c VectorT)
 * are only called if the object is CheckedVectorT in the <b>static</b>
 * context. Example:<br>
 * @verbatim
 *   CheckedVectorT<float> v(10, 4.5);
 *   VectorT<float>& w = v;
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
class CheckedVectorT : public VectorT<ElementType> {
public:
  inline CheckedVectorT() : VectorT<ElementType>() {}

  explicit CheckedVectorT(const size_t size)  : VectorT<ElementType>(size) {}

  CheckedVectorT(const size_t size, const ElementType& element)
      : VectorT<ElementType>(size, element) {}

  CheckedVectorT(const ElementType* _data, const size_t size)
      : VectorT<ElementType>(_data, size) {}

  CheckedVectorT(ElementType* _data, const size_t size, 
                 const typename VectorT<ElementType>::Mode mode = VectorT<ElementType>::copy)
      : VectorT<ElementType>(_data, size, mode) {}

  explicit CheckedVectorT(std::istream& input)
      : VectorT<ElementType>(input) {}

  CheckedVectorT(const CheckedVectorT<ElementType>& v)
      : VectorT<ElementType>(v) {}

  CheckedVectorT(const VectorT<ElementType>& v)
      : VectorT<ElementType>(v) {}

  inline typename VectorT<ElementType>::reference
  operator[](const ptrdiff_t i) {
    if (i < 0 || static_cast<unsigned int>(i) >= this->size()) {
		std::out_of_range("VectorT () access out of range"); 
    }
    return this->data[i];
  }
  
  virtual ~CheckedVectorT();
};

template<class ElementType>
CheckedVectorT<ElementType>::~CheckedVectorT() {
}

}
#endif //_CHECKEDEVECTOR_H_
