/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libimage - An image/template for new NICE libraries
 * See file License for license information.
 */

#include "core/image/CrossT.h"
#include "core/image/LineT.h"

namespace NICE {

// Constructors:
// -------------
template<class P>
CrossT<P>::CrossT(const Coord &_center, const unsigned int _halfWidth,
                  bool _diagonal)
    : center(_center), halfWidth(_halfWidth), diagonal(_diagonal)
{
}

template<class P>
CrossT<P>::CrossT(const Coord &_center, const unsigned int _halfWidth,
                  bool _diagonal, const ColorT<P>& _defaultColor)
    : Drawable<P>(_defaultColor), center(_center), halfWidth(_halfWidth),
      diagonal(_diagonal)
{
}

template<class P>
CrossT<P>::CrossT(const CrossT<P>& ex) : Drawable<P>(ex)
{
  *this = ex;
}

// Operators:
// ----------
template<class P>
CrossT<P>& CrossT<P>::operator=(const CrossT<P>& ex)
{
  center             = ex.center;
  this->halfWidth    = ex.halfWidth;
  this->defaultColor = ex.defaultColor;

  return *this;
}

template<class P>
bool CrossT<P>::operator==(const CrossT<P>& ex) const
{
    if(center             == ex.center    &&
       this->halfWidth    == ex.halfWidth &&
       this->defaultColor == ex.defaultColor)
        return true;
    else
        return false;
}

template<class P>
bool CrossT<P>::operator!=(const CrossT<P>& ex) const {
    return !(this->operator==(ex));
}

// Methods:
// --------
template<class P>
void CrossT<P>::doDraw(ColorImageT<P> &image, const ColorT<P>& color) const
{
  const int x = center.x;
  const int y = center.y;
  const int left = center.x - halfWidth;
  const int right = center.x + halfWidth;
  const int top = center.y - halfWidth;
  const int bottom = center.y + halfWidth;

  if (diagonal) {
    LineT<P> line1(Coord(left, top), Coord(right, bottom));
    LineT<P> line2(Coord(left, bottom), Coord(right, top));
    line1.draw(image, color);
    line2.draw(image, color);
  } else {
    LineT<P> line1(Coord(left, y), Coord(right, y));
    LineT<P> line2(Coord(x, top), Coord(x, bottom));
    line1.draw(image, color);
    line2.draw(image, color);
  }
}

template<class P>
void CrossT<P>::doDraw(ImageT<P> &image, const P& gray) const
{
  const int x = center.x;
  const int y = center.y;
  const int left = center.x - halfWidth;
  const int right = center.x + halfWidth;
  const int top = center.y - halfWidth;
  const int bottom = center.y + halfWidth;

  if (diagonal) {
    LineT<P> line1(Coord(left, top), Coord(right, bottom));
    LineT<P> line2(Coord(left, bottom), Coord(right, top));
    line1.draw(image, gray);
    line2.draw(image, gray);
  } else {
    LineT<P> line1(Coord(left, y), Coord(right, y));
    LineT<P> line2(Coord(x, top), Coord(x, bottom));
    line1.draw(image, gray);
    line2.draw(image, gray);
  }
}

// Destructor:
// -----------
template<class P>
CrossT<P>::~CrossT()
{
}

}; // namespace NICE
