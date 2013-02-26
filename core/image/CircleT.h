/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libimage - An image/template for new NICE libraries
 * See file License for license information.
 */
#ifndef _CIRCLE_IMAGE_H
#define _CIRCLE_IMAGE_H

#include <iostream>

#include <core/image/Drawable.h>
#include <core/image/CoordT.h>
#include <core/image/ColorT.h>

namespace NICE {

/**
 * A Drawable circle.
 */
template<class P>
class CircleT  : public Drawable<P>
{
private:
    Coord center;
    int radius;
protected:
  void doDraw(ColorImageT<P> &image, const ColorT<P>& color) const;
  void doDraw(ImageT<P> &image, const P& gray) const;
public:
  //! Default constructor
  CircleT();

  CircleT(const Coord &center, const int radius);
  CircleT(const Coord &center, const int radius, const ColorT<P>& _defaultColor);

  //! Copy-Constructor
  /*! \param arg class to copy
  */
  CircleT(const CircleT<P>& arg);

  //! Destructor of CircleT
  virtual ~CircleT();

  //! Assignment operator
  /*! \param ex class to copy
   *  \return a reference to this class
   */
  CircleT<P>& operator=(const CircleT<P>& ex);

  //! Compare operator
  /*! \param ex class to compare
   *  \return true if class content is equal
   */
  bool operator==(const CircleT<P>& ex) const;

  //! Compare operator
  /*! \param ex class to compare
   *  \return true if class content is not equal
   */
  bool operator!=(const CircleT<P>& ex) const;

};

typedef CircleT<Ipp8u> Circle;
} // namespace NICE

//#ifdef __GNUC__
#include "core/image/CircleT.tcc"
//#endif

#endif /* _CIRCLE_IMAGE_H */
