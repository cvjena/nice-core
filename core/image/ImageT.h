/*
 * NICE - New Image C++ extension
 *  - libimage - An ImageT library
 * See file License for license information.
 */
#include <core/image/Convert.h>
#ifndef _LIMUN_GRAYIMAGET_H
#define _LIMUN_GRAYIMAGET_H

#include <core/image/ippwrapper.h>

#include <core/image/CoordT.h>
#include <core/image/ColorT.h>
#include <core/image/Drawable.h>

#include <core/image/GrayColorImageCommonImplementation.h>
#include <core/image/BlockImageAccessT.h>

namespace NICE {

template<class P> class GrayColorImageCommonImplementationT;
class ImageFile;

/**
 * @class ImageT
 * The standard template class for gray images (single channel).
 * Use typdef Image for a normal 8 bit gray image.
 *
 * This class offers the same high performance pointer arithmetic pixel access
 * interface as BlockImageAccessT with the additional property that
 * rows are consecutive memory blocks, i.e. columnStepsize() == bytedepth().
 *
 * @author Ferid Bajramovic
 * @example image_overview.cpp
 */
template<class P>
class ImageT: public BlockImageAccessT<P> {
  public:
    /**
     * @name Constructors, factory methods and destructor
     * \{
     */

    /**
     * Default constructor
     */
    ImageT();

    /**
     * Create an ImageT of size (\c width, \c height)
     * @param width width
     * @param height height
     * @param _memoryLayout see \c MemoryLayout
     */
    ImageT ( const int width, const int height, const GrayColorImageCommonImplementation::MemoryLayout _memoryLayout =
               GrayColorImageCommonImplementation::ippAlignment );

    /**
     * Create a copy of \c orig.
     * @param orig Original ImageT
     * @param copyMode \c MemoryLayout of the new \c ImageT
     *        See also \c MemoryLayout.
     */
    ImageT ( const ImageT<P>& orig, const GrayColorImageCommonImplementation::MemoryLayout copyMode =
               GrayColorImageCommonImplementation::originalAlignment );

    /**
     * Create a shallow copy of \c orig directly using orig's pixel memory.
     * Pixels are not copied, onwership of pixel memory is not taken.
     * @param orig Original ImageT
     * @param shallow Set to GrayColorImageCommonImplementation::shallowCopy to use this constuctor
     */
    ImageT ( ImageT<P>& orig, const GrayColorImageCommonImplementation::ShallowCopyMode shallow );

    /**
     * Create an ImageT from raw ImageT data
     * @param raw Raw ImageT data
     * @param width Width of the ImageT
     * @param height Height of the ImageT
     * @param m_rowStepsize Number of bytes between the beginning of
     *        two consecutive lines (usually width)
     * @param copyMode \c MemoryLayout of the new \c ImageT
     *        See also \c MemoryLayout.
     * @example image_creation.cpp
     */
    ImageT ( const P* raw, const int width, const int height, const int m_rowStepsize,
             const GrayColorImageCommonImplementation::MemoryLayout copyMode =
               GrayColorImageCommonImplementation::originalAlignment );

    /**
     * Create a ImageT from raw data directly using the pixel memory raw.
     * Pixels are not copied, onwership of pixel memory is not taken.
     * @param raw Raw ImageT data
     * @param width Width of the ImageT
     * @param height Height of the ImageT
     * @param m_rowStepsize Number of bytes between the beginning of
     *        two consecutive lines (usually width)
     * @param shallow Set to GrayColorImageCommonImplementation::shallowCopy to use this constuctor
     */
    ImageT ( P* raw, const int width, const int height, const int m_rowStepsize,
             const GrayColorImageCommonImplementation::ShallowCopyMode shallow );

    /**
     * Create a ImageT from raw ImageT data
     * Assume stepwidth = width
     * @see ImageT(P*,int,int,int,bool)
     * @param raw Raw ImageT data
     * @param width Width of the ImageT
     * @param height Height of the ImageT
     * @param copyMode \c MemoryLayout of the new \c ImageT
     *        See also \c MemoryLayout.
     */
    ImageT ( const P* raw, const int width, const int height,
             const GrayColorImageCommonImplementation::MemoryLayout copyMode =
               GrayColorImageCommonImplementation::originalAlignment );

    /**
     * Create an ImageT from raw data directly using the pixel memory raw.
     * Pixels are not copied, onwership of pixel memory is not taken.
     * Assume stepwidth = width
     * @see ImageT(P*,int,int,int,bool)
     * @param raw Raw ImageT data
     * @param width Width of the ImageT
     * @param height Height of the ImageT
     * @param shallow Set to GrayColorImageCommonImplementation::shallowCopy to use this constuctor
     */
    ImageT ( P* raw, const int width, const int height, const GrayColorImageCommonImplementation::ShallowCopyMode shallow );

    /**
     * Create an ImageT from the file named pgmFilename.
     * @note If no file named \c Filename exists, an ImageException is thrown.
     * @param Filename Name of the input file
     * @param _memoryLayout see \c MemoryLayout
     */
    ImageT ( const std::string& Filename, const GrayColorImageCommonImplementation::MemoryLayout _memoryLayout =
               GrayColorImageCommonImplementation::ippAlignment );

    /**
     * Create a const shallow copy of \c orig directly using orig's pixel memory.
     * Pixels are not copied, onwership of pixel memory is not taken.
     * @param orig Original ImageT
     * @param shallow Set to GrayColorImageCommonImplementation::shallowCopy to use this constuctor
     */
    static inline const ImageT<P>* createConst ( const ImageT<P>& orig,
        const GrayColorImageCommonImplementation::ShallowCopyMode shallow ) {
      return new ImageT<P> ( orig, shallow );
    }

    /**
     * Create a const ImageT from raw data directly using the pixel memory
     * raw. Pixels are not copied, onwership of pixel memory is not taken.
     * @param raw Raw ImageT data
     * @param width Width of the ImageT
     * @param height Height of the ImageT
     * @param m_rowStepsize Number of bytes between the beginning of
     *        two consecutive lines (usually width)
     * @param shallow Set to GrayColorImageCommonImplementation::shallowCopy to use this "constuctor"
     */
    static inline const ImageT<P>* createConst ( const P* raw, const int width, const int height, const int m_rowStepsize,
        const GrayColorImageCommonImplementation::ShallowCopyMode shallow ) {
      return new ImageT<P> ( raw, width, height, m_rowStepsize, shallow );
    }

    /**
     * Create a const ImageT from raw data directly using the pixel memory
     * raw. Pixels are not copied, onwership of pixel memory is not taken.
     * Assume stepwidth = width
     * @see ImageT(P*,int,int,int,bool)
     * @param raw Raw ImageT data
     * @param width Width of the ImageT
     * @param height Height of the ImageT
     * @param shallow Set to GrayColorImageCommonImplementation::shallowCopy to use this "constuctor"
     */
    static inline const ImageT<P>* createConst ( const P* raw, const int width, const int height,
        const GrayColorImageCommonImplementation::ShallowCopyMode shallow ) {
      return new ImageT<P> ( raw, width, height, width, shallow );
    }

    /**
     * Destructor.
     */
    virtual ~ImageT();

    /**
     * \}
     * @name Access pixels and pixel memory
     * \{
     */

    /**
     * Get a const pointer to the pixel data at point (x,y).
     * Supposed for high performance pixel access. Use with care.
     * @param x Position (x-coordinate)
     * @param y Position (y-coordinate)
     * @return pointer to the pixel at position (x,y)
     */
    inline P const* getPixelPointerXY ( const int x, const int y ) const {
      return pointerToPixel1 ( this->getPixelPointer(), x, y, this->rowStepsize() );
    }

    /**
     * Get a non-const pointer to the pixel data at point (x,y).
     * @param x Position (x-coordinate)
     * @param y Position (y-coordinate)
     */
    inline P* getPixelPointerXY ( const int x, const int y ) {
      return pointerToPixel1 ( this->getPixelPointer(), x, y, this->rowStepsize() );
    }

    /**
     * Get a const reference to the pixel data at point (x,y).
     * @param x Position (x-coordinate)
     * @param y Position (y-coordinate)
     * @example image_access_operator1.cpp
     */
    inline const P& operator() ( const int x, const int y ) const {
      return *pointerToPixel1 ( this->m_pixel, x, y, this->m_rowStepsize );
      // see getPixelQuick for changes
      // return *pointerToPixel1(this->getPixelPointer(), x, y, this->m_rowStepsize);
    }

    /**
     * Get a non-const reference to the pixel data at point (x,y).
     * @param x Position (x-coordinate)
     * @param y Position (y-coordinate)
     */
    inline P& operator() ( const int x, const int y ) {
      return *pointerToPixel1 ( this->m_pixel, x, y, this->m_rowStepsize );
      // see getPixelQuick for changes
      // return *pointerToPixel1(this->getPixelPointer(), x, y, this->m_rowStepsize);
    }

    /**
     * Get a pixel value WITHOUT boundary checking.
     * @param x Position (x-coordinate)
     * @param y Position (y-coordinate)
     * @return pixel at position (x,y)
     * @example image_access_function.cpp
     */
    inline P getPixelQuick ( const int x, const int y ) const {
      return * ( ( P* ) ( ( ( Ipp8u* ) this->m_pixel ) + y * this->m_rowStepsize + x * sizeof ( P ) ) );
      // version 3 was:
      // return *pointerToPixel1(this->m_pixel, x, y, this->m_rowStepsize);
      //
      // version 2 was:
      // return *pointerToPixel1(this->getPixelPointer(), x, y, this->m_rowStepsize);
      // getPixelPointer() requires some additional operations :(
      //
      // version 1 was:
      //return *getPixelPointerXY(x, y);
      // which used to many inline functions that were not optimized
      // by the compiler, tested with the program imageAccessTime (erik, Feb/2012)
    }

    /**
     * Get a pixel value WITH boundary checking.
     * @param x Position (x-coordinate)
     * @param y Position (y-coordinate)
     * @return pixel at position (x,y)
     * @throws ImageException if (x,y) is out of range
     */
    P getPixel ( const int x, const int y ) const;

    /**
     * Set a pixel value WITHOUT boundary checking.
     * @param x Position (x-coordinate)
     * @param y Position (y-coordinate)
     * @param value New pixel value
     */
    inline void setPixelQuick ( const int x, const int y, const P value ) {
      *getPixelPointerXY ( x, y ) = value;
    }

    /**
     * Set a pixel value WITH boundary checking.
     * @param x Position (x-coordinate)
     * @param y Position (y-coordinate)
     * @param value New pixel value
     * @throws ImageException if (x,y) is out of range
     */
    void setPixel ( const int x, const int y, const P value );

    /**
     * Set a pixel value WITH boundary checking.
     * Do nothing if (x,y) is out of range.
     * @param x Position (x-coordinate)
     * @param y Position (y-coordinate)
     * @param value New pixel value
     */
    void setPixelSave ( const int x, const int y, const P value );

    /**
     * Sets all pixel to the specified value
     * @param value pixel value
     */
    void set ( const P& value );

    /**
     * \}
     * @name Basic image operations
     * \{
     */

    /**
     * Assign constant to image values.
     */
    inline ImageT<P>& operator= ( const P c );

    /**
     * Get a const pointer to the pixel data at point (x,y).
     * Supposed for high performance pixel access. Use with care.
     * @param coord coordinates of the pixel
     * @return pointer to the pixel at position (x,y)
     * @example image_access_pointer.cpp
     */
    inline P const* getPixelPointerXY ( const Coord &coord ) const {
      return pointerToPixel1 ( this->getPixelPointer(), coord, this->m_rowStepsize );
    }

    /**
     * Get a non-const pointer to the pixel data at point (x,y).
     * @param coord coordinates of the pixel
     */
    inline P* getPixelPointerXY ( const Coord &coord ) {
      return pointerToPixel1 ( this->getPixelPointer(), coord, this->m_rowStepsize );
    }

    /**
     * Get a const reference to the pixel data at point (x,y).
     * @param coord coordinates of the pixel
     */
    inline const P& operator() ( const Coord &coord ) const {
      return *pointerToPixel1 ( this->getPixelPointer(), coord, this->m_rowStepsize );
    }

    /**
     * Get a non-const reference to the pixel data at point (x,y).
     * @param coord coordinates of the pixel
     */
    inline P& operator() ( const Coord &coord ) {
      return *pointerToPixel1 ( this->getPixelPointer(), coord, this->m_rowStepsize );
    }

    /**
     * Get a pixel value WITHOUT boundary checking.
     * @param coord coordinates of the pixel
     * @return pixel at position (x,y)
     */
    inline P getPixelQuick ( const Coord &coord ) const {
      return *getPixelPointerXY ( coord );
    }

    /**
     * Get a pixel value WITH boundary checking.
     * @param coord coordinates
     * @return pixel at position (x,y)
     * @throws ImageException if (x,y) is out of range
     */
    P getPixel ( const Coord &coord ) const;

    /**
     * Get a pixel value at arbitrary position using bilinear interpolation.
     * @param x coordinate
     * @param y coordinate
     * @return pixel at position (x,y)
     */
    float getPixelBilinear ( const float x, const float y ) const;

    /**
     * Set a pixel value WITHOUT boundary checking.
     * @param coord coordinates
     * @param value New pixel value
     */
    inline void setPixelQuick ( const Coord &coord, const P value ) {
      *getPixelPointerXY ( coord ) = value;
    }

    /**
     * Set a pixel value WITH boundary checking.
     * @param coord coordinates
     * @param value New pixel value
     * @throws ImageException if (x,y) is out of range
     */
    void setPixel ( const Coord &coord, const P value );

    /**
     * Set a pixel value WITH boundary checking.
     * Do nothing if (x,y) is out of range.
     * @param coord coordinates
     * @param value New pixel value
     */
    void setPixelSave ( const Coord &coord, const P value );

    /**
     * \}
     * @name Drawing Functions
     * \{
     */

    /**
     * Draw drawable object using the default gray value of the object.
     * @param drawable object to draw
     * @example image_draw.cpp
     */
    void draw ( Drawable<P> &drawable );

    /**
     * Draw drawable objects using the default gray value of the objects.
     * @param begin Iterator to first object to draw
     * @param end   Iterator to last object to draw
     */
    template<typename DrawableIterator>
    void drawIter ( const DrawableIterator begin, const DrawableIterator end );

    /**
     * Draw drawable objects using the default gray value of the objects.
     * @param begin  iterator to the first object to draw
     * @param number number of objects to draw
     */
    template<typename DrawableIterator>
    void drawIter ( const DrawableIterator begin, size_t number );

    /**
     * Draw drawable object
     * @param drawable object to draw
     * @param gray the gray value used for drawing
     */
    void draw ( Drawable<P> &drawable, const P& gray );

    /**
     * Draw drawable object
     * @param begin Iterator to first object to draw
     * @param end   Iterator to last object to draw
     * @param gray the gray value used for drawing
     */
    template<typename DrawableIterator>
    void drawIter ( const DrawableIterator begin, const DrawableIterator end, const P& gray );

    /**
     * Draw drawable objects
     * @param begin  iterator to the first object to draw
     * @param number number of objects to draw
     * @param gray the gray value used for drawing
     */
    template<typename DrawableIterator>
    void drawIter ( const DrawableIterator begin, size_t number, const P& gray );

    /**
     * \}
     * @name Compare Functions
     * \{
     */

    /**
     * @brief Compare \c g with \c this.
     * @pre Size of \c g and \c this must be equal
     * @param g image to compare with
     * @return true if \c g and \c this are equal
     */
    inline bool operator== ( const ImageT<P> &g ) const;

    /**
     * @brief Compare \c g with \c this.
     * @pre Size of \c g and \c this must be equal
     * @param g image to compare with
     * @return true if \c g and \c this are not equal
     */
    inline bool operator!= ( const ImageT<P> &g ) const;

    /**
     * @brief Compare \c this with color.
     * @param color color to compare with
     * @return true if each pixel of \c this has the value color
     */
    inline bool operator== ( const ColorT<P> &color ) const;

    /**
     * @brief Compare \c this with color.
     * @param color color to compare with
     * @return true if each pixel of \c this has not the value color
     */
    inline bool operator!= ( const ColorT<P> &color ) const;

    /**
     * @brief Compare \c this with color.
     * @param color color to compare with
     * @return true if each pixel of \c this has the value color
     */
    inline bool operator== ( P color ) const;

    /**
     * @brief Compare \c this with color.
     * @param color color to compare with
     * @return true if each pixel of \c this has not the value color
     */
    inline bool operator!= ( P color ) const;

    /**
     * \}
     * @name Image Tools
     * \{
     */

    /**
     * Mirror on horizontal, vertical or both axis.
     * @param axis mirror type
     * - ippAxsHorizontal = horizontal
     * - ippAxsVertical = vertical
     * - ippAxsBoth = both
     */
    void mirror ( IppiAxis axis );

    /**
     * transpose image (must be quadratic)
     */
    void transpose();

    /**
     * invert image (works only with an 8 bit image)
     */
    void invert();

    /**
     * Replace each value by the absolute value
     */
    void abs();

    /**
     * Get minimum value of the image.
     * @return minimun value of the image
     */
    P min() const;

    /**
     * Get maximum value of the image.
     * @return maximum value of the image
     */
    P max() const;

    /**
     * Get minimum and maximum value of the image.
     * @param min minimun value of the image
     * @param max maximum value of the image
     */
    void minmax ( P &min, P &max ) const;

    /**
     * Get x and y coordinate of the minimum value of the image.
     * @return x and y coordinate of the minimun value of the image
     */
    Coord minIndex() const;

    /**
     * Get the x and y coordinates of the maximum value of the image.
     * @return x and y coordinate of the maximum value of the image
     */
    Coord maxIndex() const;

    /**
     * Get the x and y coordinates of the minimum and maximum value of the image.
     * @param min x and y coordinate of the minimun value of the image
     * @param max x and y coordinate of the maximum value of the image
     */
    void minmaxIndex ( Coord& min, Coord& max ) const;

    /**
     * Get the sum of all pixel values of the image.
     * @return sum of all pixel values
     */
    double sum() const;

    /**
     * Get the mean of all pixel values of the image.
     * @return mean of all pixel values
     */
    double mean() const;

    /**
     * Get the mean and standard derivation of all pixel values of the image.
     * @param mean mean value of all pixel values
     * @param stddev standard derivation of all pixel values
     */
    void meanStdDev ( double &mean, double &stddev ) const;

    /**
     * \}
     * @name File operations
     * \{
     */

    /**
     * Write a colored image (white positiv values, red negativ values).
     *   @note usefull to display float or signed images
     * @param file should contain a colorimage  ImageFile
     */
    void writeColored ( const ImageFile &file ) const;

    /**
     * Write this ImageT as a PGM file.
     * @note If an file named \c pgmFilename exists, it will be overwritten.
     * @param pgmFilename Name of the file to be written
     */
    void writePGM ( const char* pgmFilename ) const;

    /**
     * Write this ImageT as a PGM file.
     * @note If an file named \c pgmFilename exists, it will be overwritten.
     * @param pgmFilename Name of the file to be written
     */
    void writePGM ( const std::string& pgmFilename ) const;

    /**
     * Write this ImageT as a rawfile.
     * @note If an file named \c rawFilename exists, it will be overwritten.
     * @param rawFilename Name of the file to be written
     */
    void writeRaw ( const char* rawFilename ) const;

    /**
     * Write this ImageT as a rawfile.
     * @note If an file named \c rawFilename exists, it will be overwritten.
     * @param rawFilename Name of the file to be written
     */
    void writeRaw ( const std::string& rawFilename ) const;

    /**
     * Read this ImageT from a PGM file.
     * @note If no file named \c pgmFilename exists, an ImageException is thrown.
     * @param pgmFilename Name of the input file
     * @param _memoryLayout see \c MemoryLayout
     */
    void readPGM ( const char* pgmFilename, const GrayColorImageCommonImplementation::MemoryLayout _memoryLayout =
                     GrayColorImageCommonImplementation::ippAlignment );

    /**
     * Read this ImageT from a PPM file.
     * @note If no file named \c pgmFilename exists, an ImageException is thrown.
     * @param pgmFilename Name of the input file
     * @param _memoryLayout see \c MemoryLayout
     */
    void readPGM ( const std::string& pgmFilename, const GrayColorImageCommonImplementation::MemoryLayout _memoryLayout =
                     GrayColorImageCommonImplementation::ippAlignment );

    /**
     * Read this ImageT from a raw file.
     * @note If no file named \c rawFilename exists, an ImageException is thrown.
     * @param rawFilename Name of the input file
     * @param _memoryLayout see \c MemoryLayout
     */
    void readRaw ( const char* rawFilename, const GrayColorImageCommonImplementation::MemoryLayout _memoryLayout =
                     GrayColorImageCommonImplementation::ippAlignment );

    /**
     * Read this ImageT from a raw file.
     * @note If no file named \c rawFilename exists, an ImageException is thrown.
     * @param rawFilename Name of the input file
     * @param _memoryLayout see \c MemoryLayout
     */
    void readRaw ( const std::string& rawFilename, const GrayColorImageCommonImplementation::MemoryLayout _memoryLayout =
                     GrayColorImageCommonImplementation::ippAlignment );

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
    ImageT<P>& operator= ( const ImageT<P>& orig );

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
    inline void copyFrom ( const GrayColorImageCommonImplementationT<P>& image, const GrayColorImageCommonImplementation::MemoryLayout copyMode =
                             GrayColorImageCommonImplementation::ippAlignment ) {
      fromRaw ( image.getPixelPointer(), image.width(), image.height(), image.rowStepsize(), copyMode );
    }

    /**
     * \}
     * @name Subimages
     * \{
     */

    /**
     * Create a subimage using the same pixel memory.
     * @param area The area of the new subimage (must be within the image!)
     * @return A new ImageT<P> using the same pixel memory,
     *         but representing a only a part of the image.
     */
    inline ImageT<P>* createSubImage ( const Rect& area ) {
      return new ImageT<P> ( getPixelPointerXY ( area.left, area.top ), area.width, area.height, this->getStepsize(),
                             GrayColorImageCommonImplementation::shallowCopy );
    }

    /**
     * Create a const subimage using the same pixel memory.
     * @param area The area of the new subimage (must be within the image!)
     * @return A new ImageT<P> using the same pixel memory,
     *         but representing a only a part of the image.
     */
    inline const ImageT<P>* createSubImage ( const Rect& area ) const {
      return new ImageT<P> ( getPixelPointerXY ( area.left, area.top ), area.width, area.height, this->getStepsize(),
                             GrayColorImageCommonImplementation::shallowCopy );
    }

    /**
     * A subimage using the same pixel memory.
     * @param area The area of the new subimage (must be within the image!)
     * @return A ImageT<P> using the same pixel memory,
     *         but representing a only a part of the image.
     */
    inline ImageT<P> subImage ( const Rect& area ) {
      return ImageT<P> ( getPixelPointerXY ( area.left, area.top ), area.width, area.height, this->getStepsize(),
                         GrayColorImageCommonImplementation::shallowCopy );
    }

    /**
     * A const subimage using the same pixel memory.
     * @param area The area of the new subimage (must be within the image!)
     * @return A ImageT<P> using the same pixel memory,
     *         but representing a only a part of the image.
     */
    inline const ImageT<P> subImage ( const Rect& area ) const {
      return ImageT<P> ( getPixelPointerXY ( area.left, area.top ), area.width, area.height, this->getStepsize(),
                         GrayColorImageCommonImplementation::shallowCopy );
    }

    /**
     * Copies pixels from inside a rectangle to dst top left.
     * @param rect rectangle where to copy pixel from
     * @param dst  optional buffer to be used as target.
     *             Create a new Image if dst == NULL.
     *             If dst != NULL then size must be equal to rect's size!
     * @return Image
     * @example image_copyrectsubimage.cpp
     */
    ImageT<P>* copyRect ( const Rect& rect, ImageT<P>* dst = NULL );

    /**
     * \}
     */

  private:
    /**
     * Create a const shallow copy of \c orig directly using orig's pixel memory.
     * Pixels are not copied, onwership of pixel memory is not taken.
     * @param orig Original ImageT
     * @param shallow Set to GrayColorImageCommonImplementation::shallowCopy to use this constuctor
     * @note This constructor is private, use createConst() instead.
     */
    ImageT ( const ImageT<P>& orig, const GrayColorImageCommonImplementation::ShallowCopyMode shallow );

    /**
     * Create a const ImageT from raw data directly using the pixel memory
     * raw. Pixels are not copied, onwership of pixel memory is not taken.
     * @param raw Raw ImageT data
     * @param width Width of the ImageT
     * @param height Height of the ImageT
     * @param m_rowStepsize Number of bytes between the beginning of
     *        two consecutive lines (usually width)
     * @param shallow Set to GrayColorImageCommonImplementation::shallowCopy to use this constuctor
     * @note This constructor is private, use createConst() instead.
     */
    ImageT ( const P* raw, const int width, const int height, const int m_rowStepsize,
             const GrayColorImageCommonImplementation::ShallowCopyMode shallow );

    //! helper function for \c allocPixel(), separated for template specialization
    virtual void doAllocPixelNoAlignment();

    //! helper function for \c allocPixel(), separated for template specialization
    virtual void doAllocPixelIPP();

    /**
     * Initialize from raw pixel data.
     * @param raw Raw ImageT data
     * @param width Width of the ImageT
     * @param height Height of the ImageT
     * @param m_rowStepsize Stepsize
     * @param copyMode \c MemoryLayout of the new \c ImageT
     *        See also \c MemoryLayout.
     */
    void fromRaw ( const P* raw, const int width, const int height, const int m_rowStepsize,
                   const GrayColorImageCommonImplementation::MemoryLayout copyMode =
                     GrayColorImageCommonImplementation::originalAlignment );

    //! helper function for \c allocPixel(), separated for template specialization
    void doFromRaw ( const P* raw, const int m_rowStepsize );
};

typedef ImageT<Ipp8u> Image;
typedef ImageT<Ipp16s> GrayImage16s;
typedef ImageT<Ipp32f> FloatImage;

} // namespace

#include "core/image/GrayColorImageCommonImplementationT.h"

//#ifdef __GNUC__
#include "core/image/ImageT.tcc"
//#endif

#endif
