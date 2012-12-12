/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libimage - An image/template for new NICE libraries
 * See file License for license information.
 */
/*****************************************************************************/
/*! \file Drawable.h 
    \brief Drawable class declaration
 */
/*****************************************************************************/
/*
 *  $Author: bajramov $
 *  $Date: 2009/05/28 11:36:30 $
 *  $Revision: 1.2 $
*/
/*****************************************************************************/

#ifndef _DRAWABLE_IMAGE_H
#define _DRAWABLE_IMAGE_H


#include <core/image/ippwrapper.h>
#include <core/image/ColorT.h>

namespace NICE {

template<class P> class ColorImageT;
template<class P> class ImageT;

//! Base class for drawable geometric primitives.
template<class P>
class Drawable
{
protected:
    ColorT<P> defaultColor;
public:
  //! Default constructor
  Drawable() : defaultColor(ColorT<P>(0,0,0)) {}

  //! Constructor with default color
  Drawable(const ColorT<P>& _defaultColor) : defaultColor(_defaultColor) {}

  //! Destructor of Drawable
  virtual ~Drawable() {}

  //! Draw the object using the default color.
  inline void draw(ColorImageT<P> &image) const {
    draw(image, defaultColor);
  }
  
  //! Draw the object using the default color.
  inline void draw(ImageT<P> &image) const {
    draw(image, defaultColor.gray());
  }

  //! Draw the object using the default color.
  inline void draw(ImageT<P> &image, const ColorT<P>& color) const {
    draw(image, color.gray());
  }

  inline void draw(ColorImageT<P> &image, const ColorT<P>& color) const {
    if(color.size()==1)
        draw(image, ColorT<P>(color.gray(), color.gray(), color.gray()));
    else if (color.size() < (unsigned int)image.channels())
      #ifdef NICE_USELIB_FBASICS
        fthrow(Exception,"color has to few channels");
      #else
        std::__throw_range_error("color has to few channels"); 
      #endif
    else
        doDraw(image, color);
  }

  inline void draw(ImageT<P> &image, const P& gray) const {
    doDraw(image, gray);
  }
  
protected:
  //! Draw Object on image
  /*! \param image image
   *  \param color The color. Needs to have at least as many channels as image!
   */
  virtual void doDraw(ColorImageT<P> &image, const ColorT<P>& color) const = 0;

  //! Draw Object on image
  /*! \param image image
   *  \param gray the gray value
   */
  virtual void doDraw(ImageT<P> &image, const P& gray) const = 0;
};

} // namespace NICE 

#include "core/image/ColorImageT.h"
#include "core/image/ImageT.h"

#endif /* _DRAWABLE_IMAGE_H */


/*****************************************************************************/
/*
 *  $Log: Drawable.h,v $
 *  Revision 1.2  2009/05/28 11:36:30  bajramov
 *  renamed a few things for consistency
 *
 *  Revision 1.1.1.1  2007/05/22 19:26:35  bajramov
 *  limun2
 *
 *  Revision 1.6  2007/02/04 15:32:50  zimmermann
 *  * added operator !=
 *  * bugfix operator == : circle, color
 *  * bugfix operator =  : point, circle
 *  * expended gray() in ColorT for size()==3
 *  * expended draw for ColorImage, to draw gray Drawables
 *  * added new constructor PointT(Coord)
 *
 *  Revision 1.5  2006/11/02 14:25:25  zimmermann
 *  * fixed wrong function call
 *
 *  Revision 1.4  2006/11/01 16:05:24  bajramov
 *  Further changes to Drawable and subclasses.
 *  Methods draw() of ImageT/ColorImageT with iterator parameter renamed to drawIter().
 *  New Drawable CrossT.
 *
 *  Revision 1.3  2006/11/01 15:18:14  bajramov
 *  added drawing methods with color/gray value parameter
 *
 *  Revision 1.2  2006/07/13 11:53:51  mattern
 *  - large bug fixes
 *
 *  Revision 1.1  2006/06/29 10:16:03  bajramov
 *  classes and functions for drawing points, lines, ellipses, ...
 *
 */
