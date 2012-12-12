/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libimage - An image library
 * See file License for license information.
 */
#ifndef LIMUN_IMAGETOOLS_H
#define LIMUN_IMAGETOOLS_H


#include <core/image/ippwrapper.h>

#include <core/vector/VectorT.h>
#include <core/vector/MatrixT.h>

#include <core/image/ImageT.h>
#include <core/image/ColorImageT.h>

#include <core/image/Convert.h>
#include <core/image/Filter.h>

namespace NICE {

    /**
    * @name Arithmetic and Logical Operations
    * \{
    */

    /**
    * Calculates the absolute difference between Image \c src0 and Image \c src1 into the Image \c dst .
    * @param src0 source gray image
    * @param src1 source gray image
    * @param dst  optional buffer to be used as target.<br>
    *             Create a new Image if \c dst == NULL.<br>
    *             If \c dst != NULL then size must be equal to \c src 's size!
    * @throw ImageException will be thrown if \c dst != NULL and the size of \c src0 / \c scr1 and \c dst or
    *                       the size of \c src0 and \c src1 is not equal.
    * @return Image
    */
    Image* absDiff(const Image& src0, const Image& src1, Image* dst=NULL);

    /**
    * Calculates the absolute difference between ColorImage \c src0 and ColorImage \c src1 into the ColorImage \c dst .
    * @param src0 source color image
    * @param src1 source color image
    * @param dst  optional buffer to be used as target.<br>
    *             Create a new ColorImage if \c dst == NULL.<br>
    *             If \c dst != NULL then size must be equal to \c src' s size!
    * @throw ImageException will be thrown if \c dst != NULL and the size of \c src0 / \c scr1 and \c dst or
    *                       the size of \c src0 and \c src1 is not equal.
    * @return ColorImage
    */
    ColorImage* absDiff(const ColorImage& src0, const ColorImage& src1, ColorImage* dst=NULL);

    /**
    * Calculates bitwise and between the corresponding pixels of the Image \c src0 and Image
    * \c src1 into the Image \c dst.
    * @param src0 source gray image
    * @param src1 source gray image
    * @param dst  optional buffer to be used as target.<br>
    *             Create a new Image if \c dst == NULL.<br>
    *             If \c dst != NULL then size must be equal to \c src 's size!
    * @throw ImageException will be thrown if \c dst != NULL and the size of \c src0 / \c scr1 and \c dst or
    *                       the size of \c src0 and \c src1 is not equal.
    * @return Image
    */
    Image* And(const Image& src0, const Image& src1, Image* dst=NULL);

    /**
    * Calculates bitwise and between the corresponding pixels of the ColorImage \c src0 and
    * ColorImage \c src1 into the ColorImage \c dst.
    * @param src0 source color image
    * @param src1 source color image
    * @param dst  optional buffer to be used as target.<br>
    *             Create a new Image if \c dst == NULL.<br>
    *             If \c dst != NULL then size must be equal to \c src size!
    * @throw ImageException will be thrown if \c dst != NULL and the size of \c src0 / \c scr1 and \c dst or
    *                       the size of \c src0 and \c src1 is not equal.
    * @return ColorImage
    */
    ColorImage* And(const ColorImage& src0, const ColorImage& src1, ColorImage* dst=NULL);

    /**
    * \}
    * @name Border Functions
    * \{
    */

    /** Add Border with a constant value.
     * @param src    source gray image
     * @param width  width of the left and right border
     * @param height height of the top and bottom border
     * @param value  border color
     * @param dst    destination image
     */
    template<class P>
    ImageT<P>* addConstBorder(const ImageT<P> &src, uint width, uint height,
                                  P value=0, ImageT<P>* dst = NULL);


    /** Copy the border of an image.
     * @param src source gray image
     * @param width width of the left and right border
     * @param height height of the top and bottom border
     * @param dst destination image
    */
    template<class P>
    ImageT<P>* copyBorder(const ImageT<P> &src, uint width, uint height, ImageT<P>* dst);

    /**
    * \}
    * @name Threshold Functions
    * \{
    */

    /**
    * Generate a binarized image from Image \c src .
    * @param src       source gray image
    * @param threshold threshold
    * @param dst       optional buffer to be used as target.<br>
    *                  Create a new Image if \c dst == NULL.<br>
    *                  If \c dst != NULL then size must be equal to \c src 's size!
    * @return Image
    * @throw ImageException will be thrown if \c dst != NULL and the size of \c src and \c dst is not equal.
    */
    Image* threshold(const Image& src, const int threshold, Image* dst=NULL);

    /**
    * Generate a threshold image from Image \c src .
    * @param src       source Image
    * @param threshold threshold
    * @param dst       optional buffer to be used as target.<br>
    *                  Create a new Image if \c dst == NULL.<br>
    *                  If \c dst != NULL then size must be equal to \c src 's size!
    * @param value     set pixel less or equal to \c threshold to this value
    * @return Image
    * @throw ImageException will be thrown if \c dst != NULL and the size of \c src and \c dst is not equal.
    */
    Image* lowerThreshold(const Image& src, const int threshold,
                              Image* dst=NULL, const int value=0);

    /**
    * Generate a threshold image from Image \c src .
    * @param src       source Image
    * @param threshold threshold
    * @param dst       optional buffer to be used as target.<br>
    *                  Create a new Image if \c dst == NULL.<br>
    *                  If \c dst != NULL then size must be equal to \c src 's size!
    * @param value     set pixel greater than threshold to this value
    * @return Image
    * @throw ImageException will be thrown if \c dst != NULL and the size of \c src and \c dst is not equal.
    */
    Image* upperThreshold(Image& src, const int threshold,
                              Image* dst=NULL, const int value=255);

	/**
	* Generate a binarized image from Image \c src .
	* @param src       source gray image
	* @param threshold threshold
	*/
	void thresholdIP(Image& src, const int threshold);
	
	/**
	* Generate a threshold image from Image \c src .
	* @param src       source gray image
	* @param threshold threshold
	* @param value     set pixel less or equal to \c threshold to this value
	*/
	void lowerThresholdIP(Image& src, const int threshold, const int value=0);
	
	/**
	* Generate a threshold image from Image \c src .
	* @param src       source gray image
	* @param threshold threshold
	* @param value     set pixel greater than \c threshold to this value
	*/
    void upperThresholdIP(Image& src, const int threshold, const int value=255);

    /**
    * \}
    * @name Minimum / Maximum Functions
    * \{
    */

    /**
     * autoCropRect determine the rectangular area \c Rect within the pixels have larger values than a given value.
     * @param src source image
     * @param color color value
     * @param rect returned \c Rect of the area which has larger values than the color value
     **/
    template<class P>
    void autoCropRect(const ImageT<P> &src, P color, Rect &rect);
    
    
     /**
     * scale and shift image values as a new image with a destined range [min,max] 
     * @param src input image
     * @param dst output image
     * @param min target range minimum
     * @param max target range maximum
      */
    template<class P>
    void normalizeToRange(const ImageT<P> &src, ImageT<P> &dst , P min, P max);
    
    /**
     * scale and shift image values to destined range [min,max] (inplace)
     * @param src image to modify
     * @param min target range minimum
     * @param max target range maximum
     */
    template<class P>
    void normalizeToRange(ImageT<P> &src, P min, P max);
    
    
    /**
     * findLocalMinima find minima in images.
     * @param src source image
     * @param thresh minima must be below this threshold
     * @param dist  local minima have a displacement of rectangular distance to other minima
     * @param minima vector of coordiantes of minima
     **/
    template<class P>
    void findLocalMinima(const ImageT<P> &src, P thresh, int dist, std::vector<Coord> &minima);

    /**
     * findLocalMaxima find maxima in images.
     * @param src    source image
     * @param thresh maxima must be below this threshold
     * @param dist   local maxima have a displacement of rectangular distance to other minima
     * @param maxima vector of coordiantes of maxima
     **/
    template<class P>
    void findLocalMaxima(const ImageT<P> &src, P thresh, int dist, std::vector<Coord> &maxima);

    /**
    * \}
    * @name Line Segmentation
    * \{
    */

    /**
    * Create a lookup table to speed up the Hough Transformation
    * @return Pointer to gray image
    */
    FloatImage* houghTransformLUT();

    /**
    * Hough Transformation for a given gradient strength and degree image
    * @param gradStr    gradient strength image
    * @param gradDir    gradient direction image
    * @param noLines    return the \c noLines strongest Lines as result
    * @param gradThresh pixels with gradient strenth lower \c gradThresh will be ignored 
    * @param soAreaDeg  degree area which will be cleared while getting best \c nolines lines
    * @param soAreaDist distance area which will be cleared while getting best \c nolines lines
    * @param soBorder   ignore a border of size \c soBorder
    * @param lut        optional lookup table, create with \b houghTransformLUT() to speed up the ht
    * @param diffAngle  only angles from \c -diffAngle to \c +diffAngle will be accumulated
    * @throw ImageException will be thrown if the size of \c gradStr and \c gradDir is not equal.
    * @return IntMatrix of size (\c noLines x 3) or
    *         (lines found x 3) if lesser lines than \c noLines can be found.
    *   - 1.col: distance
    *   - 2.col: angle in degree
    *   - 3.col: accumulator value
    */
    IntMatrix* houghTransform(const Image& gradStr,
                              const Image& gradDir,
                              const uint& noLines,
                              const uint& gradThresh,
                              const uint& soAreaDeg,
                              const uint& soAreaDist,
                              const uint& soBorder = 0,
                              const FloatImage* lut=NULL,
                              const int diffAngle = 22);

    /**
    * Hough Transformation for a given gradient strength image
    * @param gradStr    gradient strength image
    * @param noLines    return the \c noLines strongest Lines as result
    * @param gradThresh pixels with gradient strenth lower \c gradThresh will be ignored
    * @param soAreaDeg  degree area which will be cleared while getting the stronges \c nolines lines
    * @param soAreaDist distance area which will be cleared while getting the strongest \c nolines lines
    * @param soBorder   ignore a border of size \c soBorder
    * @param lut        optional lookup table, create with \b houghTransformLUT() to speed up the ht
    * @throw ImageException will be thrown if the size of \c gradStr and \c gradDir is not equal.
    * @return IntMatrix of size (\c noLines x 3) or
    *         (lines found x 3) if lesser lines than \c noLines can be found.
    *   - 1.col: distance
    *   - 2.col: angle in degree
    *   - 3.col: accumulator value
    */
    IntMatrix* houghTransform(const Image& gradStr,
                              const uint& noLines,
                              const uint& gradThresh,
                              const uint& soAreaDeg,
                              const uint& soAreaDist,
                              const uint& soBorder = 0,
                              const FloatImage* lut=NULL);

    /**
    * \}
    * @name Corner Detection
    * \{
    */

    /**
    * Kanade-Lucas-Tomasi corner detection
    * @param src            source gray image
    * @param noCorner       return the \c noCorner strongest corners as result
    * @param EVThresh       only corners where the smaller eigenvalue is bigger than \c EVThresh will be processed
    * @param soNeighborhood only neighbors of a pixel with distance lower or equal to
                            \c soNeighborhood are taken into account during the calculation of the structure matrix
    * @param soArea         all pixels around a detected corner with distance smaller or equal to
    *                       \c soArea will be deleted
    * @param gradX          optional horizontal gradient image
    * @param gradY          optional vertical gradient image
    * @throw ImageException will be thrown, if \c gradX != NULL or \c GradY != NULL and the
    *                       size of \c gradX and \c gradY or \c gradX / \c gradY and \c src is not equal.
    * @return Matrix
    */
    Matrix* KLTCornerDetector(const Image& src,
                                 const uint& noCorner,
                                 const double& EVThresh,
                                 const uint& soNeighborhood,
                                 const uint& soArea,
                                 const GrayImage16s* gradX=NULL,
                                 const GrayImage16s* gradY=NULL);

    /**
    * \}
    * @name Floodfill Functions
    * \{
    */

    /**
    * Floodfill algorithm for GrayImages
    * fill area with the color \c newVal beginning with the starting point \c seed
    * using a 4-neighborhood
    * @param src        source gray image
    * @param seed       start point
    * @param newVal     value to fill component with
    * @param compBuffer optional buffer to be used as target.<br>
    *                   create a new IppiConnectedComp if \c compBuffer == NULL.<br>
    * @return pointer to IppiConnectedComp
    */
    template<class P>
    IppiConnectedComp* floodFill4Connected(ImageT<P>&  src,
                                           const IppiPoint&      seed,
                                           const P&              newVal,
                                           IppiConnectedComp*    compBuffer = NULL);

    /**
    * Floodfill algorithm for GrayImages
    * fill area with the color \c newVal beginning with the starting point \c seed
    * using a 4-neighborhood 
    * @param src        source gray image
    * @param seed       start point
    * @param newVal     value to fill component with
    * @param compBuffer optional buffer to be used as target.<br>
    *                   create a new IppiConnectedComp if \c compBuffer == NULL.<br>
    * @return pointer to IppiConnectedComp
    */
    template<class P>
    IppiConnectedComp* floodFill8Connected(ImageT<P>&  src,
                                           const IppiPoint&      seed,
                                           const P&              newVal,
                                           IppiConnectedComp*    compBuffer = NULL);

    /**
     * Floodfill algorithm for GrayImages
     * @param src       source image
     * @param startx    start x coordinate for floodfill
     * @param starty    start y coordinate for floodfill
     * @param newVal    new value in filled area
     * @param minDelta  minimum Delta for neighbourpixel from actual pixelvalue
     * @param maxDelta  maximum Delta for neighbourpixel from actual pixelvalue
     */
    template<class P>
    void Floodfill(ImageT<P>& src, int startx=0, int starty=0,
                   uint newVal=0, uint minDelta=50, uint maxDelta=50);

    /**
     * Floodfill algorithm for ColorImages treating all channels the same
     * @param src       source image
     * @param startx    start x coordinate for floodfill
     * @param starty    start y coordinate for floodfill
     * @param newVal    new value in filled area
     * @param minDelta      minimum Delta for neighbourpixel from actual pixelvalue
     * @param maxDelta      maximum Delta for neighbourpixel from actual pixelvalue
     */
    template<class P>
    void Floodfill(ColorImageT<P>& src, int startx=0, int starty=0,
                   uint newVal=0, uint minDelta=50, uint maxDelta=50);

    /**
     * Floodfill algorithm for ColorImages
     * @param src       source image
     * @param startx    start x coordinate for floodfill
     * @param starty    start y coordinate for floodfill
     * @param newValR   new value in filled area for R channel
     * @param newValG   new value in filled area for G channel
     * @param newValB   new value in filled area for B channel
     * @param minDeltaR     minimum Delta for neighbourpixel from actual pixelvalue for R channel
     * @param minDeltaG     minimum Delta for neighbourpixel from actual pixelvalue for G channel
     * @param minDeltaB     minimum Delta for neighbourpixel from actual pixelvalue for B channel
     * @param maxDeltaR     maximum Delta for neighbourpixel from actual pixelvalue for R channel
     * @param maxDeltaG     maximum Delta for neighbourpixel from actual pixelvalue for G channel
     * @param maxDeltaB     maximum Delta for neighbourpixel from actual pixelvalue for B channel
     */
    template<class P>
    void FloodfillRGB(ColorImageT<P>& src, int startx=0, int starty=0,
                      uint newValR=0,    uint newValG=0,    uint newValB=0,
                      uint minDeltaR=50, uint minDeltaG=50, uint minDeltaB=50,
                      uint maxDeltaR=50, uint maxDeltaG=50, uint maxDeltaB=50);
	
} // namespace

#include "core/image/ImageT.h"
#include "core/image/ImageT.h"
#include "core/image/ColorImageT.h"
#include "core/image/Buffer.h"

#ifdef __GNUC__
	#include <core/image/ImageTools.tcc>
#endif

#endif //LIMUN_IMAGETOOLS_H
