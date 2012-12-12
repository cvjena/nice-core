/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libimage - An image library
 * See file License for license information.
 */
#ifndef _IMAGEINPUTSTREAM_IMAGE_H
#define _IMAGEINPUTSTREAM_IMAGE_H


#include "core/image/ColorImageT.h"

namespace NICE {

/**
 * Abstract base class for an image input stream (like cameras and videos).
 * 
 * @author Ferid Bajramovic (ferid [dot] bajramovic [at] informatik [dot] uni-jena [dot] de)
 * 
 * @note
 * This class is HIGHLY experimental and might change in the future.
 */
class ImageInputStream {
public:
  //! destructor
	virtual ~ImageInputStream();
  
  /**
   * Has the end of the stream been reached or are more images available?
   * @return true if end of stream has been reached (cannot read images)
   */
  virtual bool endOfStream() = 0;

  /**
   * Read the next image from the stream (as RGB color image) .
   * @param buffer Will recieve the image data
   * @throw ImageException if no more images available
   */
  virtual void readColorImage(ColorImage& buffer) = 0;

  /**
   * Read the next image from the stream (as RGB color image)
   * and store the image data in a new ColorImage.
   * @return a new ColorImage conaining the image data.
   * @throw ImageException if no more images available
   */
  virtual ColorImage* readColorImageNew();

  /**
   * Read the next image from the stream (as gray image) .
   * @param buffer Will recieve the image data
   * @throw ImageException if no more images available
   */
  virtual void readGrayImage(Image& buffer) = 0;

  /**
   * Read the next image from the stream (as gray image)
   * and store the image data in a new Image.
   * @return a new Image conaining the image data.
   * @throw ImageException if no more images available
   */
  virtual Image* readGrayImageNew();

  /** 
   * Get the width of the images.
   * @return width
   */
  virtual int imageWidth() = 0;

  /** 
   * Get the height of the images.
   * @return height
   */
  virtual int imageHeight() = 0;

// the following methods only make sense for video sources, not for cameras
// they aren't needed in general anyway
  /** 
   * Get the number of frames which can be read.
   * @return number of frames
   */
  //virtual int getNumberOfFrames() = 0;

  /**
   * Reset the stream back to the first image.
   */
  //virtual void reset() = 0;
  
  /**
   * Leave out the next \c frames frames.
   * @param frames Number of frames to ignore
   */
  //virtual void ignoreFrames(int frames) = 0;
};

} // namespace
#endif // _IMAGEINPUTSTREAM_IMAGE_H
