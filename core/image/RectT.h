#ifndef _IMAGE_RECT_H
#define _IMAGE_RECT_H


#include "core/image/ippwrapper.h"

#include "core/image/CoordT.h"

#include "core/vector/VectorT.h"

#include <ostream>

namespace NICE {
  
/**
 * A simple discrete rectangle (oriented along coordinate axes).
 * 
 * @author Ferid Bajramovic
 **/
template<class T>
class RectT {

public:
    //! left border
    T left;
    
    //! top border
    T top;
    
    //! width
    T width;
    
    //! height
    T height;
  
public:
  
    /**
    * Create an empty Rect.
    **/
    inline RectT()
        : left(0), top(0), width(0), height(0) {
    }
    
    /**
    * Create a Rect with given parameters.
    * @param _left left border
    * @param _top top border
    * @param _width width
    * @param _height height
    **/
    inline RectT(const T _left, const T _top, const T _width, const T _height)
        : left(_left), top(_top), width(_width), height(_height) {
    }

    /**
    * Create a Rect with given coordinates
    * @param c1 first coordinate
    * @param c2 second coordinate
    **/
    template <class Tp>
    inline RectT(const CoordT<Tp>& c1, const CoordT<Tp>& c2) {

        left   = std::min(c1.x, c2.x);
        top    = std::min(c1.y, c2.y);
        width  = std::max(c1.x, c2.x) - left;
        height = std::max(c1.y, c2.y) - top;
    }
    
    /**
    * Copy-constructor.
    * @param other Original Rect.
    **/
    inline RectT(const RectT<T>& other) {
        left   = other.left;
        top    = other.top;
        width  = other.width;
        height = other.height;
    }
    
    ~RectT() {
    }
    
    /**
    * Compute the right border (which is NOT part of the rect's area).
    * @return right border
    **/
    inline T right() const {
        return left + width;
    }
    
    /**
    * Compute the bottom border (which is NOT part of the rect's area).
    * @return bottom border
    **/
    inline T bottom() const {
        return top + height;
    }
    
    /**
    * Compute the area of \c this .
    * @return center
    **/    
    inline T area() const {

        return width*height;
    }

    /**
    * Compute the center of \c this .
    * @return center
    **/
    inline CoordT<T> center() const {

        return CoordT<T>(left+width/2, top+height/2);
    }

    /**
    * Are \c this and \c rect equal ?
    **/    
    inline bool operator==(const RectT<T> &rect) const {
        return (left==rect.left && top==rect.top &&
                width==rect.width && height==rect.height);
    }
    
    /**
    * Are \c this and \c rect not equal ?
    **/
    inline bool operator!=(const RectT<T> &rect) const {

        return !(operator==(rect));
    }

    /**
    * Assign \c rect to \c this
    **/
    inline void operator=(const RectT<T> &rect) {
        left   = rect.left;
        top    = rect.top;
        width  = rect.width;
        height = rect.height;
    }
    
    /**
    * Is (\c x , \c y ) inside \c this ?
    */
    template <class Tp>
    inline bool isWithin(Tp x, Tp y) const {

        return x >= left && x < right() && y >= top && y < bottom();
    }
    
    /**
    * Is \c pt inside \c this ?
    */
    template <class Tp>
    inline bool isWithin(const CoordT<Tp>& pt) const {

        return isWithin(pt.x, pt.y);
    }

    /**
    * Calculate the intersection of \c this with \c rect
    * @param rect           rect to calculate the intersection with
    * @param intersectRect  resulting rect
    * @return true if there's an intersection of \c this with \c rect
    * @remark current implementation works only for T=int
    */
    bool intersect(const RectT<T>& rect, RectT<T>& intersectRect);

};

    template <class T>
    inline std::ostream& operator<< (std::ostream& out, const RectT<T>& rect) {
    out << rect.left << ", " << rect.top
        << ", " << rect.width << ", " << rect.height;
    return out;
    }

    typedef RectT<int> Rect;

} // namespace

//#ifdef __GNUC__
#include "core/image/RectT.tcc"
//#endif


#endif // _IMAGE_RECT_H
