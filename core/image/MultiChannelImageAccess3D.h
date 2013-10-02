/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libimage - An image library
 * See file License for license information.
 */

#ifndef _LIMUN_BASEMULTICHANNELIMAGE3D_H
#define _LIMUN_BASEMULTICHANNELIMAGE3D_H

namespace NICE {

/**
 * A generic, but not very efficient multi channel image access interface.
 *
 * @author Sven Sickert
 */
class MultiChannelImageAccess3D {
public:
  virtual int width() const = 0;
  virtual int height() const = 0;
	virtual int depth() const = 0;
  virtual int channels() const = 0;

  virtual int getPixelInt(int x, int y, int z, int channel) const = 0;
  virtual double getPixelFloat(int x, int y, int z, int channel) const = 0;

  virtual void setPixelInt(int x, int y, int z, int channel, int pixel) = 0;
  virtual void setPixelFloat(int x, int y, int z, int channel, double pixel) = 0;

  virtual ~MultiChannelImageAccess3D () {};
};

} // namespace

#endif
