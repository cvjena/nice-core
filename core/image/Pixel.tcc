/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libimage - An image/template for new NICE libraries
 * See file License for license information.
 */
#include "core/image/Pixel.h"
#ifdef NICE_USELIB_FBASICS
#include "core/basics/Exception.h"
#else
#include <exception>
#endif

namespace NICE {

// Constructors:
// -------------
template<class T>
Pixel<T>::Pixel():VectorT<T>() 
{
}

template<class T>
Pixel<T>::Pixel(T gray):VectorT<T>(1, gray)
{
}

template<class T>
Pixel<T>::Pixel(T *color,size_t nochannels, const VectorBase::Mode mode):VectorT<T>(color,nochannels, mode)
{
}

template<class T>
Pixel<T>::Pixel(T r, T g, T b):VectorT<T>(3)
{
    this->data[0] = r;
    this->data[1] = g;
    this->data[2] = b;
}

template<class T>
Pixel<T>::operator T() const
{
    if(this->size()==0)
      return 0;
    else
      return this->constData[0];
}

template<class T>
T Pixel<T>::gray() const
{
    if(this->size()==1) {
      return  this->constData[0]; 
    } else if(this->size()==0) {
      this->__throw_range_error("invalid channel number"); 
    } else if(this->size()==3) {
      this->__throw_range_error("not implemented yet"); 
    } else {
      this->__throw_range_error("invalid channel number"); 
    }
}

template<class T>
const T* Pixel<T>::color() const
{
  return this->constData;
}

template<class T>
void Pixel<T>::getColor(T *buffer) const
{
  ippsCopy(this->constData, buffer, this->size());
}

}; // namespace NICE 
