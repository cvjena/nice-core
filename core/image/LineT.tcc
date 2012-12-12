/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libimage - An image/template for new NICE libraries
 * See file License for license information.
 */

#include "core/image/LineT.h"

namespace NICE {

// Constructors:
// -------------
template<class P>
LineT<P>::LineT(const Coord &_begin, const Coord &_end)
{
    begin=_begin;
    end=_end;
    steep = (::abs(end.y - begin.y) > ::abs(end.x - begin.x));
    if(steep) {
       std::swap(begin.x, begin.y);
       std::swap(end.x, end.y);
    }
    if(begin.x > end.x) {
         std::swap(begin, end);
    }
}

template<class P>
LineT<P>::LineT(const Coord &_begin, const Coord &_end,
                const ColorT<P>& _defaultColor)
    : Drawable<P>(_defaultColor)
{
    begin=_begin;
    end=_end;
    steep= (::abs(end.y - begin.y) > ::abs(end.x - begin.x));
    if(steep) {
       std::swap(begin.x, begin.y);
       std::swap(end.x, end.y);
    }
    if(begin.x > end.x) {
         std::swap(begin, end);
     }
}

template<class P>
LineT<P>::LineT(const LineT<P>& ex) : Drawable<P>(ex)
{
  *this=ex;
}

// Operators:
// ----------
template<class P>
LineT<P>& LineT<P>::operator=(const LineT<P>& ex)
{
  begin              = ex.begin;
  end                = ex.end;
  this->defaultColor = ex.defaultColor;
  return *this;
}

template<class P>
bool LineT<P>::operator==(const LineT<P>& ex) const
{
  if(begin==ex.begin &&  end==ex.end &&
       this->defaultColor==ex.defaultColor)
    return true;
  return false;
}

template<class P>
bool LineT<P>::operator!=(const LineT<P>& ex) const {
    return !(this->operator==(ex));
}

// Methods:
// --------
template<class P>
void LineT<P>::doDraw(ColorImageT<P> &image, const ColorT<P>& color) const
{
	int maxx = image.width();
	int maxy = image.height();
	if(steep)
	{
		maxx = image.height();
		maxy = image.width();
	}
	
     Coord start=begin;
     Coord stop=end;

     if(start.x<0) start.x=0;
     if(stop.x>maxx) stop.x= maxx;
     int deltax = stop.x - start.x;
     int deltay = ::abs(stop.y - start.y);
     int error = 0;
     int y = start.y;
     int ystep;
     if(start.y < stop.y) {
        if(stop.y > maxy)
            stop.y = maxy;
        if(start.y<0)
            start.y=0;
        ystep = 1;
     } else {
        if(stop.y<0)
            stop.y=0;
        if(start.y > maxy)
            start.y = maxy;
        ystep = -1;
     }

     for(int x=start.x;x<=stop.x;x++) {
         if(steep) {
            image.setPixelSave(y,x,color[0],color[1],color[2]);
         } else  {
            image.setPixelSave(x,y,color[0],color[1],color[2]);
         }
         error = error + deltay;
         if((error<<1) >= deltax) {
             y = y + ystep;
             error = error - deltax;
         }
    }
}

template<class P>
void LineT<P>::doDraw(ImageT<P> &image, const P& gray) const
{
	int maxx = image.width();
	int maxy = image.height();
	if(steep)
	{
		maxx = image.height();
		maxy = image.width();
	}
	
     Coord start=begin;
     Coord stop=end;

     if(start.x < 0) start.x = 0;
     if(stop.x > maxx) stop.x = maxx;
     int deltax = stop.x - start.x;
     int deltay = ::abs(stop.y - start.y);
     int error = 0;
     int y = start.y;
     int ystep;
     if(start.y < stop.y) {
        if(stop.y > maxy)
            stop.y = maxy;
        if(start.y<0)
            start.y=0;
        ystep = 1;
     } else {
        if(stop.y<0)
            stop.y=0;
        if(start.y > maxy)
            start.y = maxy;
        ystep = -1;
     }

    for(int x=start.x;x<=stop.x;x++) {
         if(steep) {
            image.setPixelSave(y,x,gray);
         } else  {
            image.setPixelSave(x,y,gray);
         }
         error = error + deltay;
         if((error<<1) >= deltax) {
             y = y + ystep;
             error = error - deltax;
         }
    }
}

// Destructor:
// -----------
template<class P>
LineT<P>::~LineT()
{
}

}; // namespace NICE
