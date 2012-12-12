/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libimage - An image/template for new NICE libraries
 * See file License for license information.
 */
/*****************************************************************************/
#ifndef _POINT_IMAGE_H
#define _POINT_IMAGE_H

#include <iostream>

#include <core/image/Drawable.h>
#include <core/image/CoordT.h>
#include <core/image/ColorT.h>

namespace NICE {

/**
 * A Drawable point.
 */
template<class P>
class PointT  : public Drawable<P>
{
private:
    Coord coord;
protected:
  void doDraw(ColorImageT<P> &image, const ColorT<P>& color) const;
  void doDraw(ImageT<P> &image, const P& gray) const;
public:
  //! Default constructor
  PointT() {}

  //! Constructor of optional argument with default-value
  /*! \param x
   *  \param y
   */
  PointT(int x, int y) : coord(x,y) {}
  PointT(int x, int y, const ColorT<P>& _defaultColor)
      : Drawable<P>(_defaultColor), coord(x,y) {}

  //! Constructor with given coordinatens \c coords
  /*! \param coords coordinates of the point
   */
  PointT(Coord coords) : coord(coords) {};

  //! Copy-Constructor
  /*! \param arg class to copy
	*/
  PointT(const PointT<P>& arg);

  //! Destructor of PointT
  virtual ~PointT();

  //! Assignment operator
  /*! \param ex class to copy
   *  \return a reference to this class
   */
  PointT<P>& operator=(const PointT<P>& ex);

  //! Compare operator
  /*! \param ex class to compare
   *  \return true if class content is equal
   */
  bool operator==(const PointT<P>& ex) const;

  //! Compare operator
  /*! \param ex class to compare
   *  \return true if class content is not equal
   */
  bool operator!=(const PointT<P>& ex) const;
};

typedef PointT<Ipp8u> Point;

} // namespace NICE

#ifdef __GNUC__
#include "core/image/PointT.tcc"
#endif

#endif /* _POINT_IMAGE_H */
