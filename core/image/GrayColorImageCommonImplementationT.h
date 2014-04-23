/*
 * LImUn - Library for ImageT Understanding
 *  - libimage - An ImageT library
 * See file License for license information.
 */
#ifndef _LIMUN_IMAGET_H
#define _LIMUN_IMAGET_H

namespace NICE {
  template <class P> class GrayColorImageCommonImplementationT;
  class ImageFile;
}

#include "core/image/ippwrapper.h"
#include "core/image/pointerArithmetic.h"
#include "core/image/ImageException.h"
#include "core/image/GrayColorImageCommonImplementation.h"
#include <core/image/RectT.h>

namespace NICE {

/**
 * A common implementation base class for images.
 *
 * @author Ferid Bajramovic
 */
template <class P>
class GrayColorImageCommonImplementationT : public GrayColorImageCommonImplementation {
public:
  //! Pixel type definition.
  typedef P Pixel;

  /**
   * Destructor.
   */
  virtual ~GrayColorImageCommonImplementationT();

  /**
   * @name Access to pixel memory
   * \{
   */

  /**
   * Get a const pointer to the pixel data.
   * Supposed for high performance pixel access. Use with care.
   * @return pixel
   * @example image_ippusage.cpp
   **/
  inline Pixel const* getPixelPointer() const { return m_pixelConst; }

  /**
   * Get a non-const pointer to the pixel data.
   * @copydoc getPixelPointer() const
   */
  inline Pixel* getPixelPointer() { return m_pixel; }

  /**
   * Get a const pointer to the beginning of line \c y.
   * Supposed for high performance pixel access. Use with care.
   * @param y Position (y-coordinate)
   * @return pointer to the beginning of line \c y
   */
  inline Pixel const* getPixelPointerY(const int y) const {
    return pointerToPixelY(getPixelPointer(), y, m_rowStepsize);
  }

  /**
   * Get a non-const pointer to the beginning of line \c y.
   * @copydoc getPixelPointerY()
   */
  inline Pixel* getPixelPointerY(const int y) {
    return pointerToPixelY(getPixelPointer(), y, m_rowStepsize);
  }

  /**
   * Get a const pointer beyond the end of line \c y.
   * Supposed for high performance pixel access. Use with care.
   * @param y Position (y-coordinate)
   * @return pointer to the beginning of line \c y
   */
  inline Pixel const* getPixelPointerYEnd(const int y) const {
    return pointerToPixelEx(getPixelPointer(), m_xsize, y, m_rowStepsize, m_columnStepsize);
  }

    /**
    * Get a const pointer to the pixel data at point (x,y).
    * Supposed for high performance pixel access. Use with care.
    * @param x Position (x-coordinate)
    * @param y Position (y-coordinate)
    * @return pointer to the pixel at position (x,y)
    */
    inline P const* getPixelPointerXY(const int x, const int y) const
    {
      return pointerToPixelEx(this->getPixelPointer(), x, y, this->rowStepsize(), this->columnStepsize());
    }

    /**
    * Get a non-const pointer to the pixel data at point (x,y).
    * @param x Position (x-coordinate)
    * @param y Position (y-coordinate)
    */
    inline P* getPixelPointerXY(const int x, const int y) {
        return pointerToPixelEx(this->getPixelPointer(), x, y, this->rowStepsize(), this->columnStepsize());
    }



  /**
   * \}
   * @name Basic image properties
   * \{
   */

  /**
   * get number of channels
   * @return number of (color) channels
   */
  virtual int channels() const = 0;

  /**
   * get bit depth of image per channel
   * @return number of bits per pixel and channel
   */
  inline int bitdepth() const { return sizeof(P)*8; }

  /**
   * get byte depth of image per channel
   * @return number of bytes per pixel and channel
   */
  inline int bytedepth() const { return sizeof(P); }

  /**
   * return if the image is aligned.
   * FIXME replace by isContinuousMemoryBlock()
   * @return is aligned?
   */
  inline bool isAligned() const;

  /**
   * \}
   * @name Change image size.
   * \{
   */

  /**
   * Resize image (external pointers to image become invalid).
   * @param width new image width
   * @param height ne image heigth
   * @param _memoryLayout see \c MemoryLayout
   * @note
   * This will invalidate all pointers to the pixel memory of this image
   * as well as all subimages of this image!
   * The image data will NOT be scaled!
   */
  void resize(const int width, const int height,
              const GrayColorImageCommonImplementation::MemoryLayout _memoryLayout = ippAlignment);

  /**
   * \}
   * @name File operations
   * \{
   */

  /**
  * Read this image from a file.
  * @note If no file named \c filename exists, an ImageException is thrown.
  * @param file an image filename
  * @param _memoryLayout see \c MemoryLayout
  * @example image_loadsave.cpp
  */
  void read(ImageFile file /*, const GrayColorImageCommonImplementation::MemoryLayout _memoryLayout = ippAlignment*/);

  /**
   * Read this image from a file. See also documentation of \c ImageFile.
   * @param filename name of the file to read an image
   *        (file format defined by extension)
   * @param _memoryLayout target memory layout
   * @note   If you want to explicitly select a file format,
   *         use read(ImageFile, const GrayColorImageCommonImplementation::MemoryLayout)
   */
  void read(const std::string &filename); 

  /**
  * Write this image to a file. See also documentation of \c ImageFile.
  * @param file an image file to be written
  */
  void write(const ImageFile &file) const;

  /**
   * Write this image to a file. See also documentation of \c ImageFile.
   * \param filename name of the file to write an image
   *        (file format defined by extension)
   * @note If you want to explicitly select a file format,
   *       use write(ImageFile)
   */
  inline void write(const std::string &filename) const; 

  /**
  * Read this image from a PPM or PGM file.
  * @note If no file named \c pxmFilename exists, an ImageException is thrown.
  * @param pxmFileName Name of the input file
  * @param _memoryLayout see \c MemoryLayout
  */
  void readPXM(const std::string& pxmFileName, const GrayColorImageCommonImplementation::MemoryLayout _memoryLayout);

  /**
  * Write this image as a PPM or PGM file.
  * @note If an file named \c pxmFilename exists, it will be overwritten.
  * @param pxmFileName Name of the file to be written
  */
  void writePXM(const char* pxmFileName) const;

  /**
   * \}
   * @name Subimages
   * \{
   */

  /**
   * Create a subimage using the same pixel memory.
   * @param area The area of the new subimage (must be within the image!)
   * @return A new ColorImageT<P> using the same pixel memory,
   *         but representing only a part of the image.
   */
  virtual GrayColorImageCommonImplementationT<P>* createSubImage(const Rect& area) = 0;

  /**
   * Create a const subimage using the same pixel memory.
   * @param area The area of the new subimage (must be within the image!)
   * @return A new ImageT<P> using the same pixel memory,
   *         but representing only a part of the image.
   */
  virtual const GrayColorImageCommonImplementationT<P>* createSubImage(const Rect& area) const = 0;

  /* \} */

protected:
  /**
   * Create an uninitialized GrayColorImageCommonImplementationT
   */
  GrayColorImageCommonImplementationT();

  /**
   * @name Memory management
   * \{
   */

  /**
   * deallocate the memory which was allocated by the GrayColorImageCommonImplementationT
   */
  void deallocPixel();

  /**
   * Allocate memory for pixel data.
   * Deallocate existing data before allocating.
   * @param width width
   * @param height height
   * @param _memoryLayout see \c MemoryLayout
   */
  void allocPixel(const int width, const int height,
                  const GrayColorImageCommonImplementation::MemoryLayout _memoryLayout = ippAlignment);

  //! helper function for \c allocPixel(), separated for template specialization
  virtual void doAllocPixelNoAlignment() = 0;

  //! helper function for \c allocPixel(), separated for template specialization
  virtual void doAllocPixelIPP() = 0;

  /**
   * Initialize from raw data (foreign pointer mode, no ownership taken)
   * @param raw Raw GrayColorImageCommonImplementationT data
   * @param width Width of the GrayColorImageCommonImplementationT
   * @param height Height of the GrayColorImageCommonImplementationT
   * @param rowStepsize Step size between rows
   * @param columnStepsize Step size between columns
   */
  void setForeignPointer(Pixel* raw,
                         const int width,
                         const int height,
                         const int rowStepsize,
                         const int columnStepsize);

  /**
   * Initialize from raw data (foreign pointer mode, no ownership taken)
   * @param raw Raw GrayColorImageCommonImplementationT data
   * @param width Width of the GrayColorImageCommonImplementationT
   * @param height Height of the GrayColorImageCommonImplementationT
   * @param rowStepsize Step size between rows
   * @param columnStepsize Step size between columns
   */
  void setForeignPointerConst(const Pixel* raw,
                              const int width,
                              const int height,
                              const int rowStepsize,
                              const int columnStepsize);

  //! set pixel and pixelConst to newPixelPointer
  inline void setPixelPointer(Pixel* newPixelPointer) {
    this->m_pixel = newPixelPointer;
    this->m_pixelConst = newPixelPointer;
  }

  //! set pixelConst to newPixelPointer and pixel to NULL
  inline void setPixelPointerConst(const Pixel* newPixelPointer) {
    this->m_pixel = NULL;
    this->m_pixelConst = newPixelPointer;
  }

  /* \} */


protected:
  //! Pixel data (can be NULL for image created from a const image!)
  Pixel* m_pixel;

  //! Const pixel data
  const Pixel* m_pixelConst;

};

// typedef GrayColorImageCommonImplementationT<Ipp8u>  Image8u;
// typedef GrayColorImageCommonImplementationT<Ipp16s> Image16s;
// typedef GrayColorImageCommonImplementationT<Ipp32f> Image32f;

} // namespace

//#ifdef __GNUC__
#include "core/image/GrayColorImageCommonImplementationT.tcc"
//#endif

#endif
