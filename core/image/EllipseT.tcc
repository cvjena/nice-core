/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libimage - An image/template for new NICE libraries
 * See file License for license information.
 */
/*****************************************************************************/

#include "core/image/EllipseT.h"

namespace NICE {

// Constructors:
// -------------
template<class P>
EllipseT<P>::EllipseT(const Coord &center, const Coord &axis, float angle)
{
  this->center=center;
  this->axis=axis;
  this->angle=angle;
}

template<class P>
EllipseT<P>::EllipseT(const Coord &center, const Coord &axis, float angle,
                      const ColorT<P>& _defaultColor)
    : Drawable<P>(_defaultColor)
{
  this->center=center;
  this->axis=axis;
  this->angle=angle;
}

template<class P>
EllipseT<P>::EllipseT()
{
}

template<class P>
EllipseT<P>::EllipseT(const EllipseT<P>& ex) : Drawable<P>(ex)
{
  *this=ex;
}

// Operators:
// ----------
template<class P>
EllipseT<P>& EllipseT<P>::operator=(const EllipseT<P>& ex)
{
  center=ex.center;
  axis=ex.axis;
  angle=ex.angle;
  this->defaultColor=ex.defaultColor;
  return *this;
}

template<class P>
bool EllipseT<P>::operator==(const EllipseT<P>& ex) const
{
  if(center==ex.center &&
       axis==ex.axis&&
       angle==ex.angle&&
       this->defaultColor==ex.defaultColor)
      return true;
  return false;
}

template<class P>
bool EllipseT<P>::operator!=(const EllipseT<P>& ex) const {
    return !(this->operator==(ex));
}

// Methods:
// --------
template<class P>
void EllipseT<P>::doDraw(ColorImageT<P> &image, const ColorT<P>& color) const
{
  const int rx2 =(axis.x*axis.x);
  const int ry2 =(axis.y*axis.y);
  int F = (int)(ry2-rx2*axis.y+0.25*rx2+0.5);
  int ddF_x =0;
  int ddF_y =(2*rx2*axis.y);
  int x =0;
  int y =axis.y;

  float cosinus=cos(angle);
  float sinus=sin(angle);
  image.setPixelSave(center.x+int(cosinus*x-sinus*y), center.y+int(sinus*x+cosinus*y),color[0],color[1],color[2]);
  image.setPixelSave(center.x+int(cosinus*-x-sinus*y), center.y+int(sinus*-x+cosinus*y),color[0],color[1],color[2]);
  image.setPixelSave(center.x+int(cosinus*x+sinus*y), center.y+int(sinus*x-cosinus*y),color[0],color[1],color[2]);
  image.setPixelSave(center.x+int(cosinus*-x+sinus*y), center.y+int(sinus*-x-cosinus*y),color[0],color[1],color[2]);
  while( ddF_x < ddF_y ) {
    if(F >= 0) {
      y     -= 1;        // south
      ddF_y -= 2*rx2;
      F     -= ddF_y;
    }
    x     += 1;          // east
    ddF_x += 2*ry2;
    F     += ddF_x + ry2;
    image.setPixelSave(center.x+int(cosinus*x-sinus*y), center.y+int(sinus*x+cosinus*y),color[0],color[1],color[2]);
    image.setPixelSave(center.x+int(cosinus*-x-sinus*y), center.y+int(sinus*-x+cosinus*y),color[0],color[1],color[2]);
    image.setPixelSave(center.x+int(cosinus*x+sinus*y), center.y+int(sinus*x-cosinus*y),color[0],color[1],color[2]);
    image.setPixelSave(center.x+int(cosinus*-x+sinus*y), center.y+int(sinus*-x-cosinus*y),color[0],color[1],color[2]);
  }

  F = int(ry2*(x+0.5)*(x+0.5) + rx2*(y-1)*(y-1) - rx2*ry2+0.5);
  while( y > 0 ) {
    if(F <= 0) {
      x     += 1;        // east
      ddF_x += 2*ry2;
      F     += ddF_x;
    }
    y     -=1;           // south
    ddF_y -= 2*rx2;
    F     += rx2 - ddF_y;
    image.setPixelSave(center.x+int(cosinus*x-sinus*y), center.y+int(sinus*x+cosinus*y),color[0],color[1],color[2]);
    image.setPixelSave(center.x+int(cosinus*-x-sinus*y), center.y+int(sinus*-x+cosinus*y),color[0],color[1],color[2]);
    image.setPixelSave(center.x+int(cosinus*x+sinus*y), center.y+int(sinus*x-cosinus*y),color[0],color[1],color[2]);
    image.setPixelSave(center.x+int(cosinus*-x+sinus*y), center.y+int(sinus*-x-cosinus*y),color[0],color[1],color[2]);
  }
}

template<class P>
void EllipseT<P>::doDraw(ImageT<P> &image, const P& gray) const
{
  const int rx2 =(axis.x*axis.x);
  const int ry2 =(axis.y*axis.y);
  int F = (int)(ry2-rx2*axis.y+0.25*rx2+0.5);
  int ddF_x =0;
  int ddF_y =(2*rx2*axis.y);
  int x =0;
  int y =axis.y;

  float cosinus=cos(angle);
  float sinus=sin(angle);
  image.setPixelSave(center.x+int(cosinus*x-sinus*y), center.y+int(sinus*x+cosinus*y),gray);
  image.setPixelSave(center.x+int(cosinus*-x-sinus*y), center.y+int(sinus*-x+cosinus*y),gray);
  image.setPixelSave(center.x+int(cosinus*x+sinus*y), center.y+int(sinus*x-cosinus*y),gray);
  image.setPixelSave(center.x+int(cosinus*-x+sinus*y), center.y+int(sinus*-x-cosinus*y),gray);
  while( ddF_x < ddF_y ) {
    if(F >= 0) {
      y     -= 1;        // south
      ddF_y -= 2*rx2;
      F     -= ddF_y;
    }
    x     += 1;          // east
    ddF_x += 2*ry2;
    F     += ddF_x + ry2;
    image.setPixelSave(center.x+int(cosinus*x-sinus*y), center.y+int(sinus*x+cosinus*y),gray);
    image.setPixelSave(center.x+int(cosinus*-x-sinus*y), center.y+int(sinus*-x+cosinus*y),gray);
    image.setPixelSave(center.x+int(cosinus*x+sinus*y), center.y+int(sinus*x-cosinus*y),gray);
    image.setPixelSave(center.x+int(cosinus*-x+sinus*y), center.y+int(sinus*-x-cosinus*y),gray);
  }

  F = int(ry2*(x+0.5)*(x+0.5) + rx2*(y-1)*(y-1) - rx2*ry2+0.5);
  while( y > 0 ) {
    if(F <= 0) {
      x     += 1;        // east
      ddF_x += 2*ry2;
      F     += ddF_x;
    }
    y     -=1;           // south
    ddF_y -= 2*rx2;
    F     += rx2 - ddF_y;
    image.setPixelSave(center.x+int(cosinus*x-sinus*y), center.y+int(sinus*x+cosinus*y),gray);
    image.setPixelSave(center.x+int(cosinus*-x-sinus*y), center.y+int(sinus*-x+cosinus*y),gray);
    image.setPixelSave(center.x+int(cosinus*x+sinus*y), center.y+int(sinus*x-cosinus*y),gray);
    image.setPixelSave(center.x+int(cosinus*-x+sinus*y), center.y+int(sinus*-x-cosinus*y),gray);
  }
}

// Destructor:
// -----------
template<class P>
EllipseT<P>::~EllipseT()
{
}


}; // namespace NICE
