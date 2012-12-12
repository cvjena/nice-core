/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libimage - An image library
 * See file License for license information.
 */
#ifndef _IMAGEOUTPUTSTREAM_IMAGE_H
#define _IMAGEOUTPUTSTREAM_IMAGE_H


#include "core/image/ColorImageT.h"

namespace NICE {

/**
 * Base class for writing sequences of ColorImages.
 * Usually the images will be written to disk.
 * 
 * @author Ferid Bajramovic (ferid [dot] bajramovic [at] informatik [dot] uni-jena [dot] de)
 * 
 * @note
 * This class is HIGHLY experimental and might change in the future.
 */
class ImageOutputStream {
public:
  //! Destructor
  virtual ~ImageOutputStream();

  /** 
   * Write the next ColorImage.
   * @param image Next ColorImage to write
   */
  virtual void writeColorImage(const ColorImage& image) = 0;

  /** 
   * Write the next Image.
   * @param image Next Image to write
   */
  virtual void writeGrayImage(const Image& image) = 0;

// the following methods probably aren't needed in general
  /**
   * Close the writer.
   * Usually no more writing will be possible after closing.
   */
  //virtual void close() = 0;
  
  /**
   * Insert \c frames missing/empty frames.
   * @param frames Number of empty/missing frames
   */
  //virtual void insertMissingFrames(int frames) = 0;
};

} // namespace
#endif // _IMAGEOUTPUTSTREAM_IMAGE_H
