/*
 * LImUn - Library for ImageT Understanding
 *  - libimage - An ImageT library
 * See file License for license information.
 */
#include "core/image/BlockImageAccessT.h"

namespace NICE {

template<class P> int
BlockImageAccessT<P>::width() const {
  return this->widthInline();
}

template<class P> int
BlockImageAccessT<P>::height() const {
  return this->heightInline();
}

template<class P> P
BlockImageAccessT<P>::getPixelT(int x, int y) const {
  return getPixelQuick(x, y);
}

template<class P> void
BlockImageAccessT<P>::setPixelT(int x, int y, P pixel) {
  setPixelQuick(x, y, pixel);
}

template <class P>
void BlockImageAccessT<P>::set(const P& value) {
  for(int y=0; y<this->height(); ++y) {
    const P* end = this->getPixelPointerYEnd(y);
    const int inc = this->columnStepsize();
    for (P* p = this->getPixelPointerY(y); p != end; p = (void*)p + inc) {
      *p = value;
    }
  }
}

} // namespace
