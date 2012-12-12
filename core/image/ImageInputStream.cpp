/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libimage - An image library
 * See file License for license information.
 */
#include "core/image/ImageInputStream.h"
#include "core/image/ImageException.h"

namespace NICE {

ImageInputStream::~ImageInputStream() {
}

ColorImage* ImageInputStream::readColorImageNew() {
  if (endOfStream()) {
    fthrow(ImageException, "End of stream.");
  }
  
  ColorImage* buffer = new ColorImage(imageWidth(), imageHeight());
  readColorImage(*buffer);
  return buffer;
}

Image* ImageInputStream::readGrayImageNew() {
  if (endOfStream()) {
    fthrow(ImageException, "End of stream.");
  }
  
  Image* buffer = new Image(imageWidth(), imageHeight());
  readGrayImage(*buffer);
  return buffer;
}

} // namespace
