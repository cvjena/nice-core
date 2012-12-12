#ifndef _NICE_CORE_COLORIMAGECHANNELACCESST_H
#define _NICE_CORE_COLORIMAGECHANNELACCESST_H

#include <core/image/ColorImageT.h>
#include <core/image/BlockImageT.h>

namespace NICE {

/**
 * This class provides access to a single channel in a ColorImageT
 * via a) the generic interface ImageAccessT and b) also via BlockImageAccessT,
 * which allows for fast pointer arithmetic access.
 */
template <class P>
class ColorImageChannelAccessT : public BlockImageAccessT<P> {
  inline ColorImageChannelAccessT(ColorImageT<P>& colorImage, int channel) {
    if (channel < 0 || channel >= 3) {
      fthrow(Exception, "channel must be 0, 1 or 2");
    }
    setForeignPointer(colorImage.getPixelPointer(),
                      colorImage.width(), colorImage.height(),
                      colorImage.rowStepsize(), 3 * sizeof(P));
  }
};

} // namespace

#endif
