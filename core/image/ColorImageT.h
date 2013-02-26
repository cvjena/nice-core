/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libimage - An image library
 * See file License for license information.
 */
#include <core/image/Convert.h>
#ifndef _LIMUN_COLORIMAGET_H
#define _LIMUN_COLORIMAGET_H

namespace NICE {
  template <class P> class GrayColorImageCommonImplementationT;
}

#ifdef NICE_USELIB_JPEG
    #include <jpeglib.h>
#endif


#include "core/image/ippwrapper.h"

#include "core/image/Drawable.h"
#include "core/image/CoordT.h"
#include "core/image/ColorT.h"
#include "core/image/GrayColorImageCommonImplementation.h"
#include "core/image/GrayColorImageCommonImplementationT.h"
#include "core/image/ColorImageAccess.h"
#include "core/image/RectT.h"

namespace NICE {

/**
 * A template class for color (three channel) images.
 * Use typedef ColorImage for a normal 8 bit color image.
 *
 * @author Ferid Bajramovic (ferid [dot] bajramovic [at] informatik [dot] uni-jena [dot] de)
 */
template <class P>
class ColorImageT : public GrayColorImageCommonImplementationT<P>, public ColorImageAccess {
public:

    /**
    * @name Constructors, factory methods and destructor
    * \{
    */

    /**
    * Default constructor
    */
    ColorImageT();

    /**
    * Create a ColorImageT of size (\c width, \c height)
    * @param width width
    * @param height height
    * @param _memoryLayout see \c MemoryLayout
    */
    ColorImageT(const int width, const int height,
                const GrayColorImageCommonImplementation::MemoryLayout _memoryLayout = GrayColorImageCommonImplementation::ippAlignment);

    /**
    * Create a copy of \c orig.
    * @param orig Original ColorImageT
    * @param copyMode \c MemoryLayout of the new \c ColorImageT
    *        See also \c MemoryLayout.
    */
    ColorImageT(const ColorImageT<P>& orig,
                const GrayColorImageCommonImplementation::MemoryLayout copyMode = GrayColorImageCommonImplementation::originalAlignment);

    /**
    * Create a shallow copy of \c orig directly using orig's pixel memory.
    * Pixels are not copied, onwership of pixel memory is not taken.
    * @param orig Original ColorImageT
    * @param shallow Set to GrayColorImageCommonImplementation::shallowCopy to use this constuctor
    */
    ColorImageT(ColorImageT<P>& orig, const GrayColorImageCommonImplementation::ShallowCopyMode shallow);

    /**
    * Create a ColorImageT from raw (interlaced) color image data
    * @param raw Raw image data
    * @param width Width of the image
    * @param height Height of the image
    * @param m_rowStepsize Number of bytes between the beginning of
    *        two consecutive lines (usually width * 3)
    * @param copyMode \c MemoryLayout of the new \c ColorImageT
    *        See also \c MemoryLayout.
    */
    ColorImageT(const P* raw, const int width,  const int height, const int m_rowStepsize,
                const GrayColorImageCommonImplementation::MemoryLayout copyMode = GrayColorImageCommonImplementation::originalAlignment);

    /**
    * Create a ColorImageT from raw (interlaced) color image data.
    * Assume stepwidth = width * 3
    * @see ColorImageT(P*,int,int,int,bool)
    * @param raw Raw image data
    * @param width Width of the image
    * @param height Height of the image
    * @param copyMode \c MemoryLayout of the new \c ColorImageT
    *        See also \c MemoryLayout.
    */
    ColorImageT(const P* raw, const int width, const int height,
                const GrayColorImageCommonImplementation::MemoryLayout copyMode = GrayColorImageCommonImplementation::originalAlignment);

    /**
    * Create a ColorImageT from raw (interlaced) color image data
    * directly using the pixel memory raw.
    * Pixels are not copied, onwership of pixel memory is not taken.
    * Assume stepwidth = width * 3
    * @see ColorImageT(P*,int,int,int,bool)
    * @param raw Raw image data
    * @param width Width of the image
    * @param height Height of the image
    * @param shallow Set to GrayColorImageCommonImplementation::shallowCopy to use this constuctor
    */
    ColorImageT(P* raw, const int width, const int height,
                const GrayColorImageCommonImplementation::ShallowCopyMode shallow);

    /**
    * Create a ColorImageT from raw (interlaced) color image data
    * directly using the pixel memory raw.
    * Pixels are not copied, onwership of pixel memory is not taken.
    * @see ColorImageT(P*,int,int,int,bool)
    * @param raw Raw image data
    * @param width Width of the image
    * @param height Height of the image
    * @param m_rowStepsize Stepsize of the image
    * @param shallow Set to GrayColorImageCommonImplementation::shallowCopy to use this constuctor
    */
    ColorImageT(P* raw, const int width, const int height,
                const int m_rowStepsize, const GrayColorImageCommonImplementation::ShallowCopyMode shallow);

    /**
    * Create a ColorImageT from the file named \c filename.
    * @note If no file named \c filename exists, an ImageException is thrown.
    * @param filename Name of the input file
    * @param _memoryLayout see \c MemoryLayout
    */
    ColorImageT(const std::string& filename,
                const GrayColorImageCommonImplementation::MemoryLayout _memoryLayout = GrayColorImageCommonImplementation::ippAlignment);

    /**
    * Create a shallow copy of \c orig directly using orig's pixel memory.
    * Pixels are not copied, onwership of pixel memory is not taken.
    * @param orig Original ImageT
    * @param shallow Set to GrayColorImageCommonImplementation::shallowCopy to use this constuctor
    */
    static inline const ColorImageT<P>* createConst(const ColorImageT<P>& orig,
                                                    const GrayColorImageCommonImplementation::ShallowCopyMode shallow) {
        return new ColorImageT<P>(orig, shallow);
    }

    /**
    * Create a ColorImageT from raw (interlaced) color image data
    * directly using the pixel memory raw.
    * Pixels are not copied, onwership of pixel memory is not taken.
    * @param raw Raw ImageT data
    * @param width Width of the ImageT
    * @param height Height of the ImageT
    * @param m_rowStepsize Number of bytes between the beginning of
    *        two consecutive lines (usually width)
    * @param shallow Set to GrayColorImageCommonImplementation::shallowCopy to use this "constuctor"
    */
    static inline const ColorImageT<P>* createConst(
                const P* raw, const int width, const int height,
                const int m_rowStepsize, const GrayColorImageCommonImplementation::ShallowCopyMode shallow) {
        return new ColorImageT<P>(raw, width, height, m_rowStepsize, shallow);
    }

    /**
    * Create a ColorImageT from raw (interlaced) color image data
    * directly using the pixel memory raw.
    * Pixels are not copied, onwership of pixel memory is not taken.
    * Assume stepwidth = 3 * width.
    * @see ImageT(P*,int,int,int,bool)
    * @param raw Raw ImageT data
    * @param width Width of the ImageT
    * @param height Height of the ImageT
    * @param shallow Set to GrayColorImageCommonImplementation::shallowCopy to use this "constuctor"
    */
    static inline const ColorImageT<P>* createConst(
                const P* raw, const int width, const int height,
                const GrayColorImageCommonImplementation::ShallowCopyMode shallow) {
        return new ColorImageT<P>(raw, width, height, 3 * width, shallow);
    }

    /**
    * Create a ColorImageT from 3 given source channel images
    * @param src1 souce image for the first channel
    * @param src2 souce image for the second channel
    * @param src3 souce image for thethird channel
    * @throws ImageException if the size of the source images aren't equal
    */
    ColorImageT(const ImageT<P>& src1, const ImageT<P>& src2, const ImageT<P>& src3);

    /**
    * Destructor.
    */
    virtual ~ColorImageT();

    /**
    * \}
    * @name Access pixels and pixel memory
    * \{
    */

    virtual int width() const {
      return this->widthInline();
    }

    virtual int height() const {
      return this->heightInline();
    }

    virtual int channels() const {
      return 3;
    }

    virtual int getPixelInt(int x, int y, int channel) const {
      return (int)getPixel(x, y, channel);
    }

    virtual double getPixelFloat(int x, int y, int channel) const {
      return (double)getPixel(x, y, channel);
    }

    virtual void setPixelInt(int x, int y, int channel, int pixel) {
      setPixel(x, y, channel, (P)pixel);
    }

    virtual void setPixelFloat(int x, int y, int channel, double pixel) {
      setPixel(x, y, channel, (P)pixel);
    }

    /**
    * Get a const pointer behind the end of line \c y.
    * Supposed for high performance pixel access. Use with care.
    * @param y Position (y-coordinate)
    * @return pointer to the beginning of line \c y
    */
    inline P const* getPixelPointerYEnd(const int y) const {
        return pointerToPixel3(this->getPixelPointer(), this->width(),
                            y, this->m_rowStepsize);
    }

    /**
    * Get a const pointer to the pixel data at point (x,y).
    * Supposed for high performance pixel access. Use with care.
    * @param x Position (x-coordinate)
    * @param y Position (y-coordinate)
    * @return pointer to the pixel at position (x,y)
    */
    inline P const* getPixelPointerXY(const int x, const int y) const {
        return pointerToPixel3(this->getPixelPointer(), x, y, this->m_rowStepsize);
    }

    /**
    * Get a non-const pointer to the pixel data at point (x,y).
    * @copydoc getPixelPointerXY()
    */
    inline P* getPixelPointerXY(const int x, const int y) {
        return pointerToPixel3(this->getPixelPointer(), x, y, this->m_rowStepsize);
    }

    /**
    * Get a pixel in one color channel WITHOUT boundary checking.
    * @param x X-coordinate
    * @param y Y-coordinate
    * @param channel color channel (beginninng with 0)
    * @return pixel at position (x,y) in color channel \c channel
    */
    inline P getPixelQuick(const int x, const int y,
                            const int channel) const {
        return *(getPixelPointerXY(x, y) + channel);
    }

    /**
    * Get a pixel in one color channel WITH boundary checking.
    * @param x X-coordinate
    * @param y Y-coordinate
    * @param channel color channel (beginninng with 0)
    * @return pixel at position (x,y) in color channel \c channel
    * @throws ImageException if (x,y) or channel is out of range
    */
    P getPixel(const int x, const int y, const int channel) const;

    /**
    * Get a const reference to the pixel data at point (x,y).
    * @copydoc getPixel()
    */
    inline const P& operator()(const int x, const int y, const int channel) const {
        return *(getPixelPointerXY(x, y) + channel);
    }
    /**
    * Get a non-const reference to the pixel data at point (x,y).
    * @copydoc getPixel()
    */
    inline P& operator()(const int x, const int y, const int channel) {
        return *(getPixelPointerXY(x, y) + channel);
    }

    /**
    * Set a pixel in one color channel WITHOUT boundary checking.
    * @param x X-coordinate
    * @param y Y-coordinate
    * @param channel color channel (beginninng with 0)
    * @param value New pixel value
    */
    inline void setPixelQuick(const int x, const int y, const int channel,
                                const P value) {
        *(getPixelPointerXY(x, y) + channel) = value;
    }

    /**
    * Set a pixel in one color channel WITH boundary checking.
    * @param x X-coordinate
    * @param y Y-coordinate
    * @param channel color channel (beginninng with 0)
    * @param value New pixel value
    * @throws ImageException if (x,y) or channel is out of range
    */
    void setPixel(const int x, const int y, const int channel, const P value);

    /**
    * Set a pixel in one color channel WITH boundary checking.
    * Do nothing if (x,y) or channel is out of range.
    * @param x X-coordinate
    * @param y Y-coordinate
    * @param channel color channel (beginninng with 0)
    * @param value New pixel value
    */
    void setPixelSave(const int x, const int y, const int channel, const P value);

    /**
    * Set a pixel WITHOUT boundary checking.
    * @param x X-coordinate
    * @param y Y-coordinate
    * @param value0 New pixel value in color channel 0
    * @param value1 New pixel value in color channel 1
    * @param value2 New pixel value in color channel 2
    */
    inline void setPixelQuick(const int x, const int y,
                              const P value0, const P value1, const P value2)
    {
        P* cursor = getPixelPointerXY(x, y);
        *cursor++ = value0;
        *cursor++ = value1;
        *cursor   = value2;
    }

    /**
     * Set a pixel WITHOUT boundary checking.
     * @param x X-coordinate
     * @param y Y-coordinate
     * @param color  new color of the pixel
     */
    inline void setPixelQuick(const int x, const int y, const ColorT<P> &color)
    {
      P* cursor = getPixelPointerXY(x, y);
      for(int i=0;i<3;i++)
        *cursor++ = color[i];
    }

    /**
    * Set a pixel WITH boundary checking.
    * @param x X-coordinate
    * @param y Y-coordinate
    * @param value0 New pixel value in color channel 0
    * @param value1 New pixel value in color channel 1
    * @param value2 New pixel value in color channel 2
    * @throws ImageException if (x,y) is out of range
    */
    void setPixel(const int x, const int y, const P value0, const P value1, const P value2);

    /**
     * Set a pixel WITH boundary checking.
     * @param x X-coordinate
     * @param y Y-coordinate
     * @param color  new color of the pixel
     * @throws ImageException if (x,y) is out of range
     */
    void setPixel(const int x, const int y, const ColorT<P> &color);

    /**
    * Set a pixel WITH boundary checking.
    * Do nothing if (x,y) or channel is out of range.
    * @param x X-coordinate
    * @param y Y-coordinate
    * @param value0 New pixel value in color channel 0
    * @param value1 New pixel value in color channel 1
    * @param value2 New pixel value in color channel 2
    */
    void setPixelSave(const int x, const int y, const P value0, const P value1, const P value2);

    /**
     * Set a pixel WITH boundary checking.
     * Do nothing if (x,y) or channel is out of range.
     * @param x X-coordinate
     * @param y Y-coordinate
     * @param color  new color for the pixel
     */
    void setPixelSave(const int x, const int y, const ColorT<P>& color);

    /**
    * Sets all pixel to the specified value
    * @param value0 value for the first  channel
    * @param value1 value for the second channel
    * @param value2 value for the thirs  channel
    */
    void set(const P& value0, const P& value1, const P& value2);

    /**
    * \}
    * @name Basic image operations
    * \{
    */

    /**
    * Assign constant to image values.
    */
    ColorImageT<P>& operator=(const P c[3]);

    /**
    * Assign constant to image values.
    */
    inline ColorImageT<P>& operator=(const ColorT<P> &color);

    /* --------------------------------- */
    /**
    * Get a const pointer to the pixel data at point (x,y).
    * Supposed for high performance pixel access. Use with care.
    * @param coord coordinates of the pixel
    * @return pointer to the pixel at position (x,y)
    */
    inline P const* getPixelPointerXY(const Coord &coord) const {
        return pointerToPixel3(this->getPixelPointer(), coord, this->m_rowStepsize);
    }

    /**
    * Get a non-const pointer to the pixel data at point (x,y).
    * @param coord coordinates of the pixel
    */
    inline P* getPixelPointerXY(const Coord &coord) {
        return pointerToPixel3(this->getPixelPointer(), coord, this->m_rowStepsize);
    }

    /**
    * Get a pixel in one color channel WITHOUT boundary checking.
    * @param coord   coordinates of the pixel
    * @param channel color channel (beginninng with 0)
    * @return pixel at position (x,y) in color channel \c channel
    */
    inline P getPixelQuick(const Coord &coord, const int channel) const {
        return *(getPixelPointerXY(coord) + channel);
    }

    /**
    * Get a pixel in one color channel WITH boundary checking.
    * @param coord   coordinates of the pixel
    * @param channel color channel (beginninng with 0)
    * @return pixel at position (x,y) in color channel \c channel
    * @throws ImageException if (x,y) or channel is out of range
    */
    P getPixel(const Coord &coord, const int channel) const;

    /**
    * Get a const reference to the pixel data at point (x,y).
    * @param coord   coordinates of the pixel
    * @param channel color channel (beginninng with 0)
    */
    inline const P& operator()(const Coord &coord, const int channel) const
    {
        return *(getPixelPointerXY(coord) + channel);
    }
    /**
    * Get a non-const reference to the pixel data at point (x,y).
    * @param coord   coordinates of the pixel
    * @param channel color channel (beginninng with 0)
    */
    inline P& operator()(const Coord &coord, const int channel) {
        return *(getPixelPointerXY(coord) + channel);
    }

    /**
    * Set a pixel in one color channel WITHOUT boundary checking.
    * @param coord   coordinates of the pixel
    * @param channel color channel (beginninng with 0)
    * @param value   new pixel value
    */
    inline void setPixelQuick(const Coord &coord, const int channel, const P value)
    {
        *(getPixelPointerXY(coord) + channel) = value;
    }

    /**
    * Set a pixel in one color channel WITH boundary checking.
    * @param coord   coordinates of the pixel
    * @param channel color channel (beginninng with 0)
    * @param value   new pixel value
    * @throws ImageException if (x,y) or channel is out of range
    */
    void setPixel(const Coord &coord, const int channel, const P value);

    /**
    * Set a pixel in one color channel WITH boundary checking.
    * Do nothing if (x,y) or channel is out of range.
    * @param coord   coordinates of the pixel
    * @param channel color channel (beginninng with 0)
    * @param value   new pixel value
    */
    void setPixelSave(const Coord &coord, const int channel, const P value);

    /**
    * Set a pixel WITHOUT boundary checking.
    * @param coord   coordinates of the pixel
    * @param value0 New pixel value in color channel 0
    * @param value1 New pixel value in color channel 1
    * @param value2 New pixel value in color channel 2
    */
    inline void setPixelQuick(const Coord &coord, const P value0, const P value1, const P value2)
    {
        P* cursor = getPixelPointerXY(coord);
        *cursor++ = value0;
        *cursor++ = value1;
        *cursor = value2;
    }

    /**
    * Set a pixel WITHOUT boundary checking.
    * @param coord  coordinates of the pixel
    * @param color  new color of the pixel
    */
    inline void setPixelQuick(const Coord &coord,const ColorT<P> &color)
    {
        P* cursor = getPixelPointerXY(coord);
        for(int i=0;i<3;i++)
        *cursor++ = color[i];
    }

    /**
    * Set a pixel WITH boundary checking.
    * @param coord  coordinates of the pixel
    * @param value0 new pixel value in color channel 0
    * @param value1 new pixel value in color channel 1
    * @param value2 new pixel value in color channel 2
    * @throws ImageException if (x,y) is out of range
    */
    void setPixel(const Coord &coord, const P value0, const P value1, const P value2);

    /**
    * Set a pixel WITH boundary checking.
    * Do nothing if \c coord is out of range.
    * @param coord  coordinates of the pixel
    * @param value0 new pixel value in color channel 0
    * @param value1 new pixel value in color channel 1
    * @param value2 new pixel value in color channel 2
    */
    void setPixelSave(const Coord &coord, const P value0, const P value1, const P value2);

    /**
    * Set a pixel WITH boundary checking.
    * Do nothing if \c coord is out of range.
    * @param coord  coordinates of the pixel
    * @param color  new color for the pixel
    */
    void setPixelSave(const Coord& coord, const ColorT<P>& color);

    /**
    * \}
    * @name Drawing Functions
    * \{
    */

    /**
    * Draw drawable object using the default color of the object.
    * @param drawable object to draw
    */
    void draw(Drawable<P> &drawable);

    /**
    * Draw drawable objects using the default color of the objects.
    * @param begin iterator to first Drawable object
    * @param end   iterator to last Drawable object
    */
    template <typename DrawableIterator>
    void drawIter(const DrawableIterator begin, const DrawableIterator end);

    /**
    * Draw drawable objects using the default color of the objects.
    * @param begin  iterator to first Drawable object
    * @param number number of objects to draw
    */
    template <typename DrawableIterator>
    void drawIter(const DrawableIterator begin, size_t number);

    /**
    * Draw drawable object
    * @param drawable object to draw
    * @param color    color to draw with
    */
    void draw(Drawable<P> &drawable, const ColorT<P>& color);

    /**
    * Draw drawable objects
    * @param begin iterator to first Drawable object
    * @param end   iterator to last Drawable object
    * @param color color to draw with
    */
    template <typename DrawableIterator>
    void drawIter(const DrawableIterator begin, const DrawableIterator end,
                  const ColorT<P>& color);

    /**
    * Draw drawable objects
    * @param begin  iterator to first Drawable object
    * @param number number of objects to draw
    * @param color  color to draw with
    */
    template <typename DrawableIterator>
    void drawIter(const DrawableIterator begin, size_t number,
                  const ColorT<P>& color);

    /**
    * \}
    * @name Compare Functions
    * \{
    */

    /**
    * @brief Compare \c g with \c this.
    * @pre    size of \c g and \c this must be equal
    * @param  g image to compare with
    * @return true if \c g and \c this are equal
    */
    inline bool operator==(const ColorImageT<P>& g) const;

    /**
    * @brief Compare \c g with \c this.
    * @pre    size of \c g and \c this must be equal
    * @param  g image to compare with
    * @return true if \c g and \c this are not equal
    */
    inline bool operator!=(const ColorImageT<P>& g) const;

    /**
    * @brief Compare \c this with color.
    * @param color color to compare with
    * @return true if each pixel of \c this has the value \c color
    */
    inline bool operator==(const ColorT<P> &color) const;

    /**
    * @brief Compare \c this with color.
    * @param color color to compare with
    * @return true if each pixel of \c this has not the value \c color
    */
    inline bool operator!=(const ColorT<P> &color) const;

    /**
    * \}
    * @name Image Tools
    * \{
    */

    /**
    * Creates a single channel image as a copy of the specified channel.
    * @param channel number of channel to retrieve
    * @param dst     optional buffer to be used as target. Create a new Image if dst == NULL.
    *                If dst != NULL then size must be equal to this's size!
    * @throws ImageException if channel is out of range
    * @return Image
    * @note
    * You can alternatively use ColorImageChannelAccessT to access a channel
    * of a color image <b>without</b> copying the image data.
    * However, that will not provide you with a ImageT object.
    */
    ImageT<P>* getChannel(const int channel, ImageT<P>* dst=NULL) const;

    /**
    * Mirror on horizontal, vertical or both axis.
    * @param axis type
    * - ippAxsHorizontal = horizontal
    * - ippAxsVertical = vertical
    * - ippAxsBoth = both
    */
    void mirror(IppiAxis axis);

    /**
    * transpose image (must be symmetric)
    */
    void transpose();

    /**
    * \}
    * @name File operations
    * \{
    */

    /**
    * Write this image as a PPM file.
    * @note If an file named \c ppmFilename exists, it will be overwritten.
    * @param ppmFilename Name of the file to be written
    */
    void writePPM(const char* ppmFilename) const;

    /**
    * Write this image as a PPM file.
    * @note If an file named \c ppmFilename exists, it will be overwritten.
    * @param ppmFilename Name of the file to be written
    */
    void writePPM(const std::string& ppmFilename) const;

    /**
    * Read this image from a PPM file.
    * @note If no file named \c ppmFilename exists, an ImageException is thrown.
    * @param ppmFilename Name of the input file
    * @param _memoryLayout see \c MemoryLayout
    */
    void readPPM(const char* ppmFilename,
                const GrayColorImageCommonImplementation::MemoryLayout _memoryLayout = GrayColorImageCommonImplementation::ippAlignment);

    /**
    * Read this image from a PPM file.
    * @note If no file named \c ppmFilename exists, an ImageException is thrown.
    * @param ppmFilename Name of the input file
    * @param _memoryLayout see \c MemoryLayout
    */
    void readPPM(const std::string& ppmFilename,
                const GrayColorImageCommonImplementation::MemoryLayout _memoryLayout = GrayColorImageCommonImplementation::ippAlignment);

    /**
    * \}
    * @name Copying
    * \{
    */

    /**
    * Copy \c orig to this (external pointers to image become invalid)
    * @param orig Original ColorImageT
    * @note
    * This will (in many cases) invalidate all pointers to the pixel memory
    * of this image as well as all subimages of this image!
    * MemoryLayout is set to GrayColorImageCommonImplementation::originalAlignment
    * if memory has to be reallocated.
    */
    ColorImageT<P>& operator=(const ColorImageT<P>& orig);

    /**
    * Copy \c image to this (external pointers to image become invalid)
    * @param image Original ColorImageT
    * @param copyMode New \c MemoryLayout of this \c ColorImageT
    *        if memory has to be reallocated.
    *        See also \c MemoryLayout.
    * @note
    * This will (in many cases) invalidate all pointers to the pixel memory
    * of this image as well as all subimages of this image!
    */
    inline void copyFrom(const GrayColorImageCommonImplementationT<P>& image,
                         const GrayColorImageCommonImplementation::MemoryLayout copyMode = GrayColorImageCommonImplementation::ippAlignment) {
        fromRaw(image.getPixelPointer(), image.width(), image.height(), image.rowStepsize(), copyMode);
    }

    /**
    * \}
    * @name Subimages
    * \{
    */

    /**
    * Create a subimage using the same pixel memory.
    * @param area The area of the new subimage (must be within the image!)
    * @return A new ColorImageT<P> using the same pixel memory,
    *         but representing a only a part of the image.
    */
    inline ColorImageT<P>* createSubImage(const Rect& area) {
        return new ColorImageT<P>(getPixelPointerXY(area.left, area.top),
                                  area.width, area.height, this->getStepsize(), GrayColorImageCommonImplementation::shallowCopy);
    }

    /**
    * Create a const subimage using the same pixel memory.
    * @param area The area of the new subimage (must be within the image!)
    * @return A new ImageT<P> using the same pixel memory,
    *         but representing a only a part of the image.
    */
    inline const ColorImageT<P>* createSubImage(const Rect& area) const {
        return new ColorImageT<P>(getPixelPointerXY(area.left, area.top),
                                  area.width, area.height, this->getStepsize(), GrayColorImageCommonImplementation::shallowCopy);
    }

    /**
    * A subimage using the same pixel memory.
    * @param area The area of the new subimage (must be within the image!)
    * @return A ColorImageT<P> using the same pixel memory,
    *         but representing a only a part of the image.
    */
    inline ColorImageT<P> subImage(const Rect& area) {
        return ColorImageT<P>(getPixelPointerXY(area.left, area.top),
                              area.width, area.height, this->getStepsize(), GrayColorImageCommonImplementation::shallowCopy);
    }

    /**
    * A const subimage using the same pixel memory.
    * @param area The area of the new subimage (must be within the image!)
    * @return A ImageT<P> using the same pixel memory,
    *         but representing a only a part of the image.
    */
    inline const ColorImageT<P> subImage(const Rect& area) const {
        return ColorImageT<P>(getPixelPointerXY(area.left, area.top),
                              area.width, area.height, this->getStepsize(), GrayColorImageCommonImplementation::shallowCopy);
        }

    /**
    * Copies pixels from inside a rectangle to dst top left.
    * @param rect rectangle where to copy pixel from
    * @param dst  optional buffer to be used as target.
    *             Create a new Image if dst == NULL.
    *             If dst != NULL then size must be equal to rect's size!
    * @return ColorImage
    */
    ColorImageT<P>* copyRect(const Rect& rect, ColorImageT<P>* dst=NULL);

    /**
    * \}
    */

private:

    /**
    * Create a const shallow copy of \c orig directly using orig's pixel memory.
    * Pixels are not copied, onwership of pixel memory is not taken.
    * @param orig Original ColorImageT
    * @param shallow Set to GrayColorImageCommonImplementation::shallowCopy to use this constuctor
    * @note This constructor is private, use createConst() instead.
    */
    ColorImageT(const ColorImageT<P>& orig,
                const GrayColorImageCommonImplementation::ShallowCopyMode shallow);

    /**
    * Create a const ColorImageT from raw (interlaced) color image data
    * directly using the pixel memory raw.
    * Pixels are not copied, onwership of pixel memory is not taken.
    * @param raw Raw image data
    * @param width Width of the image
    * @param height Height of the image
    * @param m_rowStepsize Number of bytes between the beginning of
    *        two consecutive lines (usually width * 3)
    * @param shallow Set to GrayColorImageCommonImplementation::shallowCopy to use this constuctor
    * @note This constructor is private, use createConst() instead.
    */
    ColorImageT(const P* raw, const int width, const int height,
                const int m_rowStepsize, const GrayColorImageCommonImplementation::ShallowCopyMode shallow);

    //! helper function for \c allocPixel(), separated for template specialization
    virtual void doAllocPixelNoAlignment();

    //! helper function for \c allocPixel(), separated for template specialization
    virtual void doAllocPixelIPP();

    /**
    * Initialize from raw pixel data.
    * @param raw Raw image data
    * @param width Width of the image
    * @param height Height of the image
    * @param m_rowStepsize Stepsize
    * @param copyMode \c MemoryLayout of the new \c ColorImageT
    *        See also \c MemoryLayout.
    */
    void fromRaw(const P* raw, const int width, const int height,
                 const int m_rowStepsize,
                 const GrayColorImageCommonImplementation::MemoryLayout copyMode = GrayColorImageCommonImplementation::originalAlignment);

    //! helper function for \c allocPixel(), separated for template specialization
    void doFromRaw(const P* raw, const int m_rowStepsize);

    //! is \c channel a legal channel index? (0, 1, 2 are legal)
    inline bool isChannelLegal(const int channel) const {
        return (channel >= 0) && (channel <= 2);
    }

};

typedef ColorImageT<Ipp8u> ColorImage;
typedef ColorImageT<Ipp8u> ThreeChannelImage;
typedef ColorImageT<Ipp8u> HSVColorImage;
typedef ColorImageT<Ipp8u> YUVColorImage;

} // namespace

//#ifdef __GNUC__
#include "core/image/ColorImageT.tcc"
//#endif

#endif
