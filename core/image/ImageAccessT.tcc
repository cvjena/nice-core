/*
 * LImUn - Library for ImageT Understanding
 *  - libimage - An ImageT library
 * See file License for license information.
 */
#include "core/image/ImageAccessT.h"

namespace NICE {

template<class P> int
ImageAccessT<P>::getPixelInt(int x, int y) const {
  throw( "this type is not implemented\n" );
  return -1;
}

template<class P> double
ImageAccessT<P>::getPixelFloat(int x, int y) const {
  throw( "this type is not implemented\n" );
  return -1.0;
}

template<class P> void
ImageAccessT<P>::setPixelInt(int x, int y, int pixel) {
  throw( "this type is not implemented\n" );
}

template<class P> void
ImageAccessT<P>::setPixelFloat(int x, int y, double pixel) {
  throw( "this type is not implemented\n" );
}

} // namespace
