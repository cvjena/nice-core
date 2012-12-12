/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libimage - An image/template for new NICE libraries
 * See file License for license information.
 */

#include "core/image/CircleT.h"
#include "core/image/EllipseT.h"

namespace NICE {

// Constructors:
// -------------
template<class P>
CircleT<P>::CircleT(const Coord &center, const int radius)
{
  this->center=center;
  this->radius=radius;
}

template<class P>
CircleT<P>::CircleT(const Coord &center, const int radius,
                    const ColorT<P>& _defaultColor)
    : Drawable<P>(_defaultColor)
{
  this->center=center;
  this->radius=radius;
}

template<class P>
CircleT<P>::CircleT()
{
}

template<class P>
CircleT<P>::CircleT(const CircleT<P>& ex) : Drawable<P>(ex)
{
  *this=ex;
}

// Operators:
// ----------
template<class P>
CircleT<P>& CircleT<P>::operator=(const CircleT<P>& ex)
{
  center=ex.center;
  radius=ex.radius;
  this->defaultColor=ex.defaultColor;
  return *this;
}

template<class P>
bool CircleT<P>::operator==(const CircleT<P>& ex) const
{
  if(center==ex.center &&
       radius==ex.radius&&
       this->defaultColor==ex.defaultColor)
      return true;
  return false;
}

template<class P>
bool CircleT<P>::operator!=(const CircleT<P>& ex) const {
    return !(this->operator==(ex));
}

// Methods:
// --------
template<class P>
void CircleT<P>::doDraw(ColorImageT<P> &image, const ColorT<P>& color) const
{
    Coord axis(radius,radius);
    EllipseT<P> e(center,axis,0);
    e.draw(image, color);
}

template<class P>
void CircleT<P>::doDraw(ImageT<P> &image, const P& gray) const
{
    Coord axis(radius,radius);
    EllipseT<P> e(center,axis,0);
    e.draw(image, gray);
}

// Destructor:
// -----------
template<class P>
CircleT<P>::~CircleT()
{
}


}; // namespace NICE
