/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libimage - An image/template for new NICE libraries
 * See file License for license information.
 */
/*****************************************************************************/
#ifndef _RECTANGLET_IMAGE_H
#define _RECTANGLET_IMAGE_H

#include <iostream>

#include <core/image/Drawable.h>
#include <core/image/CoordT.h>
#include <core/image/ColorT.h>

namespace NICE {

/**
 * A Drawable rectangle.
 */
template<class P>
class RectangleT : public Drawable<P>
{
private:
    Coord begin;
    Coord end;
protected:
  void doDraw(ColorImageT<P> &image, const ColorT<P>& color) const;
  void doDraw(ImageT<P> &image, const P& gray) const;
public:
  //! Default constructor
  inline RectangleT() {}

  //! Constructor
  /** \param begin begin of the rectangle
   *  \param end   end of the rectangle
   */
  RectangleT(const Coord &begin, const Coord &end);

  //! Constructor
  /** \param begin          begin of the rectangle
   *  \param end            end of the rectangle
   *  \param _defaultColor  color of the rectangle
   */
  RectangleT(const Coord &begin, const Coord &end, const ColorT<P>& _defaultColor);

  //! Constructor
  /** \param x      x coord of the begin of the rectangle
   *  \param y      y coord of the begin of the rectangle
   *  \param width  width of the rectangle
   *  \param height height of the rectangle
   */
  RectangleT(const int x, const int y, const int width, const int height);

  //! Constructor
  /** \param x              x coord of the begin of the rectangle
   *  \param y              y coord of the begin of the rectangle
   *  \param width          width of the rectangle
   *  \param height         height of the rectangle
   *  \param _defaultColor  color of the rectangle
   */
  RectangleT(const int x, const int y, const int width, const int height,
             const ColorT<P>& _defaultColor);

  //! Constructor
  /** \param rect           rect to draw
  */
  RectangleT(const Rect& rect);

  //! Constructor
  /** \param rect           rect to draw
  *   \param _defaultColor  color of the rectangle
  */
  RectangleT(const Rect& rect, const ColorT<P>& _defaultColor);

  //! Copy-Constructor
  /*! \param arg class to copy
    */
  RectangleT(const RectangleT<P>& arg);

  //! Destructor of LineT
  virtual ~RectangleT();

  //! Assignment operator
  /*! \param ex class to copy
   *  \return a reference to this class
   */
  RectangleT<P>& operator=(const RectangleT<P>& ex);

  //! Compare operator
  /*! \param ex class to compare
   *  \return true if class content is equal
   */
  bool operator==(const RectangleT<P>& ex) const;

  //! Compare operator
  /*! \param ex class to compare
   *  \return true if class content is not equal
   */
  bool operator!=(const RectangleT<P>& ex) const;

};

typedef RectangleT<Ipp8u> Rectangle;

} // namespace NICE

//#ifdef __GNUC__
#include "core/image/RectangleT.tcc"
//#endif

#endif /* _RectangleT_IMAGE_H */
