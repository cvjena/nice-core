/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libimage - An image/template for new NICE libraries
 * See file License for license information.
 */
/*****************************************************************************/
/*! \file RectangleT.C
    \brief RectangleT class definitions
 */

#include "core/image/RectangleT.h"

namespace NICE {

// Constructors:
// -------------
template<class P>
RectangleT<P>::RectangleT(const Coord& _begin, const Coord& _end)
    : begin(_begin), end(_end) {
}

template<class P>
RectangleT<P>::RectangleT(const Coord &_begin, const Coord &_end,
                          const ColorT<P>& _defaultColor)
    : Drawable<P>(_defaultColor) {

    RectangleT<P>(begin, end);
}

template<class P>
RectangleT<P>::RectangleT(const int x, const int y, const int width, const int height)
    : begin(Coord(x,y)), end(Coord(x+width,y+height)) {
}

template<class P>
RectangleT<P>::RectangleT(const int x, const int y, const int width, const int height,
                          const ColorT<P>& _defaultColor) 
    : begin(Coord(x,y)), end(Coord(x+width,y+height)), Drawable<P>(_defaultColor) {
}

template<class P>
RectangleT<P>::RectangleT(const Rect& rect)
    : begin(Coord(rect.left, rect.top)), end(Coord(rect.left+rect.width, rect.top+rect.height)) {
}

template<class P>
RectangleT<P>::RectangleT(const Rect& rect, const ColorT<P>& _defaultColor)
    : begin(Coord(rect.left, rect.top)), end(Coord(rect.left+rect.width, rect.top+rect.height)),
      Drawable<P>(_defaultColor) {
}

template<class P>
RectangleT<P>::RectangleT(const RectangleT<P>& ex) {

    *this=ex;
}

// Operators:
// ----------
template<class P>
RectangleT<P>& RectangleT<P>::operator=(const RectangleT<P>& ex) {

  begin              = ex.begin;
  end                = ex.end;
  this->defaultColor = ex.defaultColor;

  return *this;
}

template<class P>
bool RectangleT<P>::operator==(const RectangleT<P>& ex) const {

    if(begin==ex.begin &&  
       end==ex.end     && this->defaultColor==ex.defaultColor)
        return true;

    return false;
}

template<class P>
bool RectangleT<P>::operator!=(const RectangleT<P>& ex) const {
    return !(this->operator==(ex));
}

// Methods:
// --------
template<class P>
void RectangleT<P>::doDraw(ColorImageT<P> &image, const ColorT<P>& color) const {

    // clip rect coords to image boundaries
    Coord b(begin);
    Coord e(end);

    Ipp32s width  = image.width();  
    Ipp32s height = image.height();
  
    b.x = b.x<0?0:b.x;
    b.x = b.x>=width?width-1:b.x;
    b.y = b.y<0?0:b.y;
    b.y = b.y>=height?height-1:b.y;

    e.x = e.x<0?0:e.x;
    e.x = e.x>=width?width-1:e.x;
    e.y = e.y<0?0:e.y;
    e.y = e.y>=height?height-1:e.y;

    // draw horizontal lines
    Ipp8u* pL1 = image.getPixelPointerXY(b.x, b.y);
    Ipp8u* pL2 = image.getPixelPointerXY(b.x, e.y);
    for(Ipp32s x=b.x; x<=e.x; ++x,pL1+=3,pL2+=3) {
        *pL2     = *pL1     = color[0];
        *(pL2+1) = *(pL1+1) = color[1];
        *(pL2+2) = *(pL1+2) = color[2];
    }

    // draw vertical lines
    pL1 = image.getPixelPointerXY(b.x, b.y);
    pL2 = image.getPixelPointerXY(e.x, b.y);
    for(Ipp32s y=b.y; y<=e.y; ++y,pL1+=image.getStepsize(),pL2+=image.getStepsize()) {
        *pL2     = *pL1     = color[0];
        *(pL2+1) = *(pL1+1) = color[1];
        *(pL2+2) = *(pL1+2) = color[2];
    }
}

template<class P>
void RectangleT<P>::doDraw(ImageT<P> &image, const P& gray) const {

    // clip rect coords to image boundaries
    Coord b(begin);
    Coord e(end);

    Ipp32s width  = image.width();  
    Ipp32s height = image.height();
  
    b.x = b.x<0?0:b.x;
    b.x = b.x>=width?width-1:b.x;
    b.y = b.y<0?0:b.y;
    b.y = b.y>=height?height-1:b.y;

    e.x = e.x<0?0:e.x;
    e.x = e.x>=width?width-1:e.x;
    e.y = e.y<0?0:e.y;
    e.y = e.y>=height?height-1:e.y;

    // draw horizontal lines
    Ipp8u* pL1 = image.getPixelPointerXY(b.x, b.y);
    Ipp8u* pL2 = image.getPixelPointerXY(b.x, e.y);
    for(Ipp32s x=b.x; x<=e.x; ++x,++pL1,++pL2)
        *pL2 = *pL1 = gray;

    // draw vertical lines
    pL1 = image.getPixelPointerXY(b.x, b.y);
    pL2 = image.getPixelPointerXY(e.x, b.y);
    for(Ipp32s y=b.y; y<=e.y; ++y,pL1+=image.getStepsize(),pL2+=image.getStepsize())
        *pL2 = *pL1 = gray;
}

// Destructor:
// -----------
template<class P>
RectangleT<P>::~RectangleT() {
}


}; // namespace NICE 
