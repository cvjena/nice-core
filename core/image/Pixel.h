/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libimage - An image/template for new NICE libraries
 * See file License for license information.
 */
#ifndef _IMAGE_PIXEL_H
#define _IMAGE_PIXEL_H

//
#include <vector>
#include <numeric>
#include <core/vector/VectorBase.h>
#include <core/vector/VectorT.h>

namespace NICE {

//! Class for a color pixel
template<class T>
class Pixel : public VectorT<T> 
{

public:
  //! Default constructor.
  Pixel();

  //! Constructor with gray value.
  /*! 
   * \param gray gray value 
   */
  Pixel(T gray);

  //! Constructor with r,g,b values.
  /*! 
   * \param r red channel 
   * \param g green channel 
   * \param b blue channel 
   */
  Pixel(T r, T g, T b);

  //! Constructor with array of values.
  /*!
   * \param color    color value array
   * \param channels number of channels (default 3) 
   * \param mode     copy mode of the color spezified by \c color
   */
  Pixel(T *color, size_t channels=3,
        const VectorBase::Mode mode = VectorBase::copy);

  //! Destructor of Pixel.
  virtual ~Pixel(){}

  //! Access the first channel. 
  /*! 
   *  \return the value of the first color channel
   */
  inline operator T() const;

  //! Return number of channels of this pixel.
  inline size_t channels() const { return this->size(); }
  
  //! Return gray value.
  inline T gray() const;
  
  // Return color array.
  inline const T *color() const;

  // Copy color array to \c buffer. 
  inline void getColor(T *buffer) const;

  //! Create a black pixel
  static Pixel Black() { return Pixel(std::numeric_limits<T>::min()); }

  //! Create a white pixel
  static Pixel White() { return Pixel(std::numeric_limits<T>::max()); }
  
  //! Create a gray pixel
  static Pixel Gray() { return Pixel((std::numeric_limits<T>::max()+std::numeric_limits<T>::min()/static_cast<T>(2))); }

  //! Create a black RGB color pixel
  static Pixel RGB_Black() { return Pixel(std::numeric_limits<T>::min(),std::numeric_limits<T>::min(),std::numeric_limits<T>::min()); }

  //! Create a red RGB color pixel
  static Pixel RGB_Red() { return Pixel(std::numeric_limits<T>::max(),std::numeric_limits<T>::min(),std::numeric_limits<T>::min()); }
  
  //! Create a green RGB color pixel
  static Pixel RGB_Green() { return Pixel(std::numeric_limits<T>::min(),std::numeric_limits<T>::max(),std::numeric_limits<T>::min()); }
  
  //! Create a blue RGB color pixel
  static Pixel RGB_Blue() { return Pixel(std::numeric_limits<T>::min(),std::numeric_limits<T>::min(),std::numeric_limits<T>::max()); }
  
  //! Create a white RGB color pixel
  static Pixel RGB_White() { return Pixel(std::numeric_limits<T>::max(),std::numeric_limits<T>::max(),std::numeric_limits<T>::max()); }
   
};


}; // namespace NICE 

#ifdef __GNUC__
#include "core/image/Pixel.tcc"
#endif

#endif // PIXEL_H
