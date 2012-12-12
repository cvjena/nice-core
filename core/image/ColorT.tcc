/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libimage - An image/template for new NICE libraries
 * See file License for license information.
 */
#include "core/image/ColorT.h"
#ifdef NICE_USELIB_FBASICS
#include "core/basics/Exception.h"
#else
#include <exception>
#endif

namespace NICE {

// Constructors:
// -------------
template<class T>
ColorT<T>::ColorT():VectorT<T>()
{
}

template<class T>
ColorT<T>::ColorT(T gray):VectorT<T>(1, gray)
{
}

template<class T>
ColorT<T>::ColorT(T *color,size_t nochannels, const VectorBase::Mode mode):VectorT<T>(color,nochannels, mode)
{
}

template<class T>
ColorT<T>::ColorT(T r, T g, T b):VectorT<T>(3)
{
    this->data[0] = r;
    this->data[1] = g;
    this->data[2] = b;
}

// template<class T>
// ColorT<T>::operator T() const
// {
//     if(this->size()==0)
//         return 0;
//     else
//         return this->constData[0];
// }

template<class T>
bool ColorT<T>::operator==(T value) const
{
  if(this->size()==1 && this->constData[0]==value)
        return true;
    else
        return false;
}

template<class T>
bool ColorT<T>::operator==(const ColorT<T> &value) const {
  if (this->size() != value.size()) {
    return false;
  }

  for (uint i = 0; i < this->size(); ++i) {
    if (this->constData[i] != value.constData[i]) {
      return false;
    }
  }
  return true;
}

template<class T>
bool ColorT<T>::operator!=(T value) const
{
    return !(operator==(value));
}

template<class T>
bool ColorT<T>::operator!=(const ColorT<T> &value) const
{
    return !(operator==(value));
}

template<class T>
T ColorT<T>::gray() const
{
  if(this->size()==1)
    return this->constData[0];
  else if(this->size()==0)
  {
    #ifdef NICE_USELIB_FBASICS
      fthrow(Exception,"invalid channel number");
    #else
      std::__throw_range_error("invalid channel number");
    #endif
  }
    // convert rgb to gray
  else if(this->size()==3)
        return static_cast<T>(this->constData[0]*0.299 + this->constData[0]*0.587 + this->constData[0]*0.114);
  else
  {
    #ifdef NICE_USELIB_FBASICS
      fthrow(Exception,"invalid channel number");
    #else
      std::__throw_range_error("invalid channel number");
    #endif
  }
}

template<class T>
const T* ColorT<T>::color() const
{
    return this->constData;
}

template<class T>
void ColorT<T>::getColorT(T *buffer) const
{
  ippsCopy(this->constData, buffer, this->size());
}

}; // namespace NICE
