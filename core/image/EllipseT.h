/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libimage - An image/template for new NICE libraries
 * See file License for license information.
 */
#ifndef _ELLIPSE_IMAGE_H
#define _ELLIPSE_IMAGE_H

#include <iostream>

#include <core/image/Drawable.h>
#include <core/image/CoordT.h>
#include <core/image/ColorT.h>

namespace NICE {

/**
 * A Drawable ellipse.
 */
template<class P>
class EllipseT  : public Drawable<P>
{
private:
    Coord center;
    Coord axis;
    float angle;
protected:
  void doDraw(ColorImageT<P> &image, const ColorT<P>& color) const;
  void doDraw(ImageT<P> &image, const P& gray) const;
public:
  //! Default constructor
  EllipseT();

  /** Constructor
   * \param center center of the ellipse
   * \param axis   axis of the ellipse
   * \param angle  angle of the ellipse
   */
  EllipseT(const Coord &center, const Coord &axis, float angle=0.0);

  /** Constructor
   * \param center          center of the ellipse
   * \param axis            axis of the ellipse
   * \param angle           angle of the ellipse
   * \param _defaultColor   color of the ellipse
   */
  EllipseT(const Coord &center, const Coord &axis, float angle,
           const ColorT<P>& _defaultColor);

  //! Copy-Constructor
  /*! \param arg class to copy
  */
  EllipseT(const EllipseT<P>& arg);

  //! Destructor of EllipseT
  virtual ~EllipseT();

  //! Assignment operator
  /*! \param ex class to copy
   *  \return a reference to this class
   */
  EllipseT<P>& operator=(const EllipseT<P>& ex);

  //! Compare operator
  /*! \param ex class to compare
   *  \return true if class content is equal
   */
  bool operator==(const EllipseT<P>& ex) const;

  //! Compare operator
  /*! \param ex class to compare
   *  \return true if class content is not equal
   */
  bool operator!=(const EllipseT<P>& ex) const;

};

typedef EllipseT<Ipp8u> Ellipse;

} // namespace NICE

//#ifdef __GNUC__
#include "core/image/EllipseT.tcc"
//#endif

#endif /* _ELLIPSE_IMAGE_H */
