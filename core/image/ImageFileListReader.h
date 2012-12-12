#ifndef _IMAGE_IMAGEFILELISTREADER_H
#define _IMAGE_IMAGEFILELISTREADER_H

#include <string>
#include <vector>
#include "core/basics/FileName.h"
#include "core/image/ImageInputStream.h"

namespace NICE {

/**
 * An ImageInputStream reading a list of image files as defined by a textfile.
 *
 * The sequence is defined by a textfile which lists the filenames
 * of the sequence. The filenames are defined relative to the textfile
 * (absolute paths are also allowed). Filenames are separated by
 * a whitespace, usually one filename per line.
 *
 * If the filename given to a constructor is actually a directory 'something/foo',
 * it tries to read the file 'something/foo/foo.txt'.
 */
class ImageFileListReader : public ImageInputStream {
 public:
  /**
   * Constructor.
   * @param fileName Name of the textfile defining the sequence of image files.
   * @param _preload Preload the whole sequence into memory?
   */
  ImageFileListReader(const char* fileName, bool _preload = false);

  /**
   * Constructor.
   * @param fileName Name of the textfile defining the sequence of image files.
   * @param _preload Preload the whole sequence into memory?
   */
  ImageFileListReader(const std::string& fileName, bool _preload = false);

  virtual ~ImageFileListReader();

  virtual bool endOfStream();

  virtual void readColorImage(ColorImage& buffer);
  virtual void readGrayImage(Image& buffer);
  
  //! random access
  virtual void readColorImage(ColorImage& buffer, unsigned int index);
  //! random access
  virtual void readGrayImage(Image& buffer, unsigned int index);

  virtual int imageWidth();
  virtual int imageHeight();

  /**
   * Skip the next image, but do provide the image file name via
   * getPreviousImageFileName().
   */
  inline void skipNextImage() {
    ++currentFrame;
  }

  /**
   * Total number of frames (=images).
   * @return number of frames
   */
  virtual unsigned int numberOfFrames() const;

  /**
   * Start reading the sequence from the beginning.
   */
  virtual void reset();

  /**
   * Skip frames.
   * @param frames Number of frames to skip
   */
  virtual void ignoreFrames(int frames);

  /**
   * Get the file name of the image file list
   * (as given to the constructor).
   * @return file name
   */
  inline const FileName& getInputFileName() const {
    return inputFileName;
  }

  /**
   * Get the file name of the previously read image,
   * empty string if not available.
   */
  inline std::string getPreviousImageFileName() const {
    if (currentFrame == 0 || currentFrame > numberOfFrames()) {
      return "";
    } else {
      return *fileList.at(getPreviousImageIndex());
    }
  }
  
  /**
   * Get the file name of the image with index i
   */
  inline std::string getImageFileName(unsigned int i) const {
    if (i >= numberOfFrames()) {
      return "";
    } else {
      return *fileList.at(i);
    }
  }

  /**
   * The index of the previously read image.
   */
  inline uint getPreviousImageIndex() const {
    return currentFrame - 1;
  }

private:
  //! List of filenames read from the textfile.
  std::vector<std::string*> fileList;

  //! The file list definition file.
  FileName inputFileName;

  //! Current index into \c fileList.
  unsigned int currentFrame;

  //! Width of the images.
  int width;

  //! Height of the images.
  int height;

  //! Preload flag.
  bool preload;

  //! Preloaded images.
  std::vector<ColorImage*> images;

  /**
   * Initialize.
   * @param fileName Input file name
   * @param preload Preload?
   */
  void init(const std::string& fileName, bool preload);

  /**
   * Read the next image in the sequence.
   */
  ColorImage* doReadColorImage(ColorImage* buffer = NULL);
};

} // namespace

#endif // _IMAGE_IMAGEFILELISTREADER_H
