/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libimage - An image/template for new NICE libraries
 * See file License for license information.
 */
/*****************************************************************************/
/*! \file ColorT.h
    \brief ColorT class declaration
 */
#ifndef _IMAGE_COLOR_H
#define _IMAGE_COLOR_H

//
#include <vector>
#include <numeric>
#include <core/vector/VectorBase.h>
#include <core/vector/VectorT.h>

namespace NICE {

//! Class for a color pixel
template<class T>
class ColorT : public VectorT<T> {
public:
  /**
   * @name Constructors
   * \{
   */
  //! Default constructor.
  ColorT();

  //! Constructor with gray value.
  /*!
   * \param gray gray value
   */
  explicit ColorT(T gray);

  //! Constructor with r,g,b values.
  /*!
   * \param r red channel
   * \param g green channel
   * \param b blue channel
   */
  ColorT(T r, T g, T b);

  //! Constructor with array of values.
  /*!
   * \param color    color value array
   * \param channels number of channels (default 3)
   * \param mode     copy mode
   */
  ColorT(T *color, size_t channels=3, const VectorBase::Mode mode = VectorBase::copy);

  /**
   * \}
   */

  //! Destructor of ColorT.
  virtual ~ColorT(){}

  //! operator=
  inline ColorT<T>& operator=(const ColorT<T>& x) {
    this->resize(x.size());
    VectorT<T>::operator=(x);
    return *this;
  }

//  //! Access the first channel.
//  /*!
//   *  \return the value of the first color channel
//   */
//  inline operator T() const;

  //! Return true if \c this has color value \c value.
  inline bool operator==(T value) const;

  //! Return true if \c this has color value \c value.
  inline bool operator==(const ColorT<T> &value) const;

  //! Return true if \c this has not color value \c value.
  inline bool operator!=(T value) const;

  //! Return true if \c this has not color value \c value.
  inline bool operator!=(const ColorT<T> &value) const;

  //! Return number of channels of this pixel.
  inline size_t channels() const { return this->size(); }

  //! Return gray value.
  inline T gray() const;

  // Return color array.
  inline const T *color() const;

  // Copy color array to \c buffer.
  inline void getColorT(T *buffer) const;

  //! Create a black pixel
  static ColorT Black() { return ColorT(std::numeric_limits<T>::min()); }

  //! Create a white pixel
  static ColorT White() { return ColorT(std::numeric_limits<T>::max()); }

  //! Create a gray pixel
  static ColorT Gray() { return ColorT((std::numeric_limits<T>::max()+std::numeric_limits<T>::min()/static_cast<T>(2))); }

  //! Create a black RGB color pixel
  static ColorT RGB_Black() { return ColorT(std::numeric_limits<T>::min(),std::numeric_limits<T>::min(),std::numeric_limits<T>::min()); }

  //! Create a red RGB color pixel
  static ColorT RGB_Red() { return ColorT(std::numeric_limits<T>::max(),std::numeric_limits<T>::min(),std::numeric_limits<T>::min()); }

  //! Create a green RGB color pixel
  static ColorT RGB_Green() { return ColorT(std::numeric_limits<T>::min(),std::numeric_limits<T>::max(),std::numeric_limits<T>::min()); }

  //! Create a blue RGB color pixel
  static ColorT RGB_Blue() { return ColorT(std::numeric_limits<T>::min(),std::numeric_limits<T>::min(),std::numeric_limits<T>::max()); }

  //! Create a white RGB color pixel
  static ColorT RGB_White() { return ColorT(std::numeric_limits<T>::max(),std::numeric_limits<T>::max(),std::numeric_limits<T>::max()); }

};

typedef ColorT<Ipp8u> Color;

}; // namespace NICE

#ifdef __GNUC__
#include "core/image/ColorT.tcc"
#endif

#endif // COLOR_H
