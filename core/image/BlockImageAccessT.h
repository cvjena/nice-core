/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libimage - An image library
 * See file License for license information.
 */

#ifndef _LIMUN_BLOCKIMAGET_H
#define _LIMUN_BLOCKIMAGET_H

#include <core/image/GrayColorImageCommonImplementationT.h>
#include <core/image/ImageAccessT.h>
#include <core/image/pointerArithmetic.h>

namespace NICE {

/**
 * An image with a defined memory layout, but no own memory management.
 * The class cannot be reasonable instantiated (use ImageT e.g.),
 * but provides an interface to access the pixels.
 * In addition to ImageAccessT, there are functions for high performance
 * pointer arithmetic access.
 *
 * The memory layout is defined as follows: there is a constant distance
 * of columnStepsize() bytes (NOT pixels!) between two columns
 * and a constant distance of rowStepsize() bytes between two rows of the image.
 *
 * @author Ferid Bajramovic
 */
template <class P>
class BlockImageAccessT : public GrayColorImageCommonImplementationT<P>, public ImageAccessT<P> {
public:
  virtual int width() const;
  virtual int height() const;

  virtual P getPixelT(int x, int y) const;
  virtual void setPixelT(int x, int y, P pixel);

  virtual int channels() const {
    return 1;
  }

  inline P getPixelQuick(int x, int y) const {
    return *this->getPixelPointerXY(x, y);
  }

  inline void setPixelQuick(int x, int y, P pixel) {
    *this->getPixelPointerXY(x, y) = pixel;
  }

  inline P* getPixelPointerXY(int x, int y) {
    return pointerToPixelEx(this->getPixelPointer(), x, y, this->rowStepsize(), this->columnStepsize());
  }

  inline const P* getPixelPointerXY(int x, int y) const {
    return pointerToPixelEx(this->getPixelPointer(), x, y, this->rowStepsize(), this->columnStepsize());
  }

  BlockImageAccessT(void) {};

  /**
  * Sets all pixel to the specified value
  * @param value pixel value
  */
  void set(const P& value);

};

} // namespace

//#ifdef __GNUC__
#include "core/image/BlockImageAccessT.tcc"
//#endif

#endif
