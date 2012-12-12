/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libimage - An image library
 * See file License for license information.
 */

#ifndef _LIMUN_IMAGEBASE_H
#define _LIMUN_IMAGEBASE_H

namespace NICE {
class GrayColorImageCommonImplementation;
}


#include "core/image/ImageException.h"

namespace NICE {

enum PXMImageFormat { PXM_INVALID, PBM_IMAGE_TEXT, PGM_IMAGE_TEXT,
                      PPM_IMAGE_TEXT, PBM_RAW, PGM_RAW, PPM_RAW, PAM_RAW };

typedef struct {
    PXMImageFormat format;
    int width;
    int height;
    int maxval;
    int channel;
    int datapos;
} PXMImageHeaderInfo;

/**
 * A common implementation base class for images.
 *
 * @author Ferid Bajramovic (ferid [dot] bajramovic [at] informatik [dot] uni-jena [dot] de)
 */
class GrayColorImageCommonImplementation {
public:
  /**
   * Specifies the alignment of the beginning of each new row (line).
   * This will influence the memory layout and the value of \c rowStepsize.
   * \c ippAlignment Use IPP alignment
   *    (if IPP is not available, this is currently the same as \c noAlignment)
   * \c noAlignment There must not be any alignment
   *    (may cost performance when using IPP)
   * \c originalAlignment Only valid when copying: use the same alignment
   * \c internal__foreignPointer internal usage only (do not free such memory)
   */
  enum MemoryLayout {
    /**
     * use IPP alignment if available
     **/
    ippAlignment,
    /**
     * do not use any alignment
     **/
    noAlignment,
    /**
     * use the same alignment (only valid when copiing)
     **/
    originalAlignment,
    /**
     *  do not reallocate memory and keep the alignment (only valid when copiing)
     **/
    keepAlignment,
    /**
     * internal usage only (memory not deallocated)
     **/
    internal__foreignPointer};

  /**
   * A pseudo-enum class (C++ allows implicitly casting enums to int,
   * which is bad for the multiple constructors in ImageT and ColorImageT).
   */
  class ShallowCopyMode {};

  /**
   * Pseudo-enum value:
   * Use the same pixel memory as the original image/raw pointer
   * (do not copy data and also do not take ownership of the memory).
   **/
  static const ShallowCopyMode shallowCopy;

  /**
   * @name Basic image properties
   * \{
   */

  /**
   * Get the width of the image in pixels (not including any alignment bytes).
   * @return Width (aka xsize) of the image
   */
  inline int widthInline() const { return m_xsize; }

  /**
   * Get the height of the image in pixels.
   * @return Height (aka ysize) of the image
   */
  inline int heightInline() const { return m_ysize; }

  /**
   * Get the width of the image in pixels (not including any alignment bytes).
   * @return Width (aka xsize) of the image
   */
  virtual int width() const { return widthInline(); }

  /**
   * Get the height of the image in pixels.
   * @return Height (aka ysize) of the image
   */
  virtual int height() const { return heightInline(); }

  /**
   * Get the total size of the image in pixels.
   * @return Size (\c width() \c * \c height())
   * @note
   * Neither \c size() nor (\c size() * "bytes per pixel") is guaranteed
   * to equal the amount of memory consumed by the image data.
   */
  inline int sizeInline() const { return m_xsize * m_ysize; }

  /**
   * Get the step size.
   * FIXME remove
   * @return step size
   */
  inline int getStepsize() const { return m_rowStepsize; }

  /**
   * Get the step size.
   * @return step size
   */
  inline int rowStepsize() const { return m_rowStepsize; }

  /**
   * Get the step size.
   * @return step size
   */
  inline int columnStepsize() const { return m_columnStepsize; }

  /**
   * Get the memory layout.
   * @return memory layout
   */
  inline MemoryLayout getMemoryLayout() const { return m_memoryLayout; }

  /**
   * \}
   * @name Simple utility functions
   * \{
   */

  /**
   * Check if the point (x,y) is within this image.
   * @param x x-coordinate
   * @param y y-coordinate
   * @return true if within bounds, false otherwise
   */
  inline bool isWithinImage(const int x, const int y) const;

  /* \} */

protected:
  /**
   * Constructor.
   */
  GrayColorImageCommonImplementation();

  //! Destructor
  virtual ~GrayColorImageCommonImplementation();

  /**
   * Return the best available layout given the "wish" \c _memoryLayout
   */
  MemoryLayout toAllocationLayout(MemoryLayout _memoryLayout);

  /**
   * If copyMode == originalAlignment return source.memoryLayout,
   * else return copyMode.
   */
  MemoryLayout toCopyLayout(MemoryLayout copyMode,
                            const GrayColorImageCommonImplementation& source);

  /**
   * Read PXM header and return PXM header information
   * @param file image filestream
   * @return header information of the image
   */
  PXMImageHeaderInfo getPXMHeaderInfo(std::ifstream &file);

  //! width of the image
  int m_xsize;

  //! height of the image
  int m_ysize;

  /**
   * Number of bytes between the beginning of two consecutive rows
   * (see IPP documentation).
   */
  int m_rowStepsize;

  /**
   * Number of bytes between the beginning of two consecutive columns.
   */
  int m_columnStepsize;

  //! The type of memory layout.
  MemoryLayout m_memoryLayout;
};

inline bool GrayColorImageCommonImplementation::isWithinImage(const int x, const int y) const {
  return (x >= 0 && x < widthInline() && y >= 0 && y < heightInline());
}

} // namespace
#endif
