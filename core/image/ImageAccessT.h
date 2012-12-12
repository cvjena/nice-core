/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libimage - An image library
 * See file License for license information.
 */

#ifndef _LIMUN_BASEIMAGET_H
#define _LIMUN_BASEIMAGET_H

#include <core/image/ImageAccess.h>

namespace NICE {

/**
 * @class ImageAccessT
 * A generic, but not very efficient single channel image access interface.
 * In addition to ImageAccess, this classes provides getPixel() and
 * setPixel() using the template parameter as pixel type (instead of int/double).
 *
 * @author Ferid Bajramovic
 */
template <class P>
class ImageAccessT : public ImageAccess {
public:
  virtual P getPixelT(int x, int y) const = 0;
  virtual void setPixelT(int x, int y, P pixel) = 0;

  virtual int getPixelInt(int x, int y) const;
  virtual double getPixelFloat(int x, int y) const;

  virtual void setPixelInt(int x, int y, int pixel);
  virtual void setPixelFloat(int x, int y, double pixel);
};

} // namespace

#ifdef __GNUC__
#include "core/image/ImageAccessT.tcc"
#endif

#endif
