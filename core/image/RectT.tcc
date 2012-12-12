
#include "core/image/RectT.h"

namespace NICE {

template <class T>
bool RectT<T>::intersect(const RectT<T>& rect, RectT<T>& intersectRect) {
        
    Ipp32s xdata[4] = {left, right(), rect.left, rect.right()};
    Ipp32s ydata[4] = {top, bottom(), rect.top, rect.bottom()};

    VectorT<Ipp32s> xCoords(xdata, 4); xCoords.sortAscend();
    VectorT<Ipp32s> yCoords(ydata, 4); yCoords.sortAscend();

    // check if there is no intersection
    if( (xCoords[1]==right()       && xCoords[2]==rect.left) ||
        (xCoords[1]==rect.right()  && xCoords[2]==left     ) ||
        (yCoords[1]==bottom()      && yCoords[2]==rect.top ) ||
        (yCoords[1]==rect.bottom() && yCoords[2]==top      )  ) {

        intersectRect = RectT<T>();
        return false;
    }
    // rectangles are equal
    else if( xCoords[0]==xCoords[1] && xCoords[2]==xCoords[3] &&
             yCoords[0]==yCoords[1] && yCoords[2]==yCoords[3] ) {

        intersectRect = RectT<T>(xCoords[1], yCoords[1], xCoords[2]-xCoords[1], yCoords[2]-yCoords[1]);
        return true;
    }
    // vertical adjacent rectangles
    else if( xCoords[1]==xCoords[2] ) {
        
        intersectRect = RectT<T>(xCoords[1], yCoords[1], 1, yCoords[2]-yCoords[1]);
        return true;
    }
    // horizontal adjacend rectangles
    else if( yCoords[1]==yCoords[2] ) {

        intersectRect = RectT<T>(xCoords[1], yCoords[1], xCoords[2]-xCoords[1], 1);
        return true;
    }
    // there is an intersection, so we calc the intersected rectangle
    else {

        intersectRect = RectT<T>(xCoords[1], yCoords[1], xCoords[2]-xCoords[1], yCoords[2]-yCoords[1]);
        return true;
    }

    intersectRect = RectT<T>();
    return false;
}   

} // namespace NICE
