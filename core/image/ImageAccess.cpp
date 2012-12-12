#include <core/image/ImageAccess.h>
#include <core/basics/Exception.h>

namespace NICE {

int ImageAccess::getPixelInt(int x, int y, int channel) const {
  if (channel != 1) {
    fthrow(Exception, "channel must be 1 for single channel images.");
  }
  return getPixelInt(x, y);
}

double ImageAccess::getPixelFloat(int x, int y, int channel) const {
  if (channel != 1) {
    fthrow(Exception, "channel must be 1 for single channel images.");
  }
  return getPixelFloat(x, y);
}

int ImageAccess::channels() const {
  return 1;
}

void ImageAccess::setPixelInt(int x, int y, int channel, int pixel) {
  if (channel != 1) {
    fthrow(Exception, "channel must be 1 for single channel images.");
  }
  setPixelInt(x, y, pixel);
}

void ImageAccess::setPixelFloat(int x, int y, int channel, double pixel) {
  if (channel != 1) {
    fthrow(Exception, "channel must be 1 for single channel images.");
  }
  setPixelFloat(x, y, pixel);
}


} // namespace
