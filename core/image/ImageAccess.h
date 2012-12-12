/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libimage - An image library
 * See file License for license information.
 */

#ifndef _LIMUN_BASEIMAGE_H
#define _LIMUN_BASEIMAGE_H

#include <core/image/MultiChannelImageAccess.h>

namespace NICE {

/**
 * A generic, but not very efficient single channel image access interface.
 * Also provides MultiChannelImageAccess with channels() == 1.
 *
 * @author Ferid Bajramovic
 */
class ImageAccess : public MultiChannelImageAccess {
public:
  virtual int getPixelInt(int x, int y) const = 0;
  virtual double getPixelFloat(int x, int y) const = 0;

  virtual void setPixelInt(int x, int y, int pixel) = 0;
  virtual void setPixelFloat(int x, int y, double pixel) = 0;

  virtual int channels() const;

  virtual int getPixelInt(int x, int y, int channel) const;
  virtual double getPixelFloat(int x, int y, int channel) const;

  virtual void setPixelInt(int x, int y, int channel, int pixel);
  virtual void setPixelFloat(int x, int y, int channel, double pixel);

};

} // namespace

#endif
