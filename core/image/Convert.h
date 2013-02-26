/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libimage - An image library
 * See file License for license information.
 */
#ifndef LIMUN_CONVERT_H
#define LIMUN_CONVERT_H


#include "core/image/ippwrapper.h"

#include "core/vector/VectorT.h"
#include "core/image/Buffer.h"

#include "core/image/GrayColorImageCommonImplementation.h"
#include "core/image/RectT.h"
#include "core/image/ImageT.h"
#include "core/image/ColorImageT.h"


#include <math.h>
#include <limits>
#include <iostream>

namespace NICE {

template<class P> class ColorImageT;
template<class P> class ImageT;

    /**
    * @name Colorspace Conversion
    * \{
    */

  /**
  * Convert the HSV-ColorImage \c src into a RGB-ColorImage \c dst .
  * @param src source HSV image
  * @param dst optional buffer to be used as target.<br>
  *            Create a new ColorImage if \c dst == NULL.
  * @return Pointer to ColorImage
  * @throw ImageException will be thrown if \c dst != NULL and the size of \c src and \c dst is not equal.
  */
  ColorImage* hsvToRGB(const ColorImage& src, ColorImage* dst=NULL);

  /**
  * Convert the RGB-ColorImage \c src into a HSV-ColorImage \c dst .
  * @param src source RGB image
  * @param dst optional buffer to be used as target.<br>
    *            Create a new ColorImage if \c dst == NULL.
  * @return Pointer to ColorImage
  * @throw ImageException will be thrown if \c dst != NULL and the size of \c src and \c dst is not equal.
  */
  ColorImage* rgbToHSV(const ColorImage& src, ColorImage* dst=NULL);

  /**
  * Convert the YUV-ColorImage \c src into a RGB-ColorImage \c dst .
  * @param src source YUV image
  * @param dst optional buffer to be used as target.<br>
    *            Create a new ColorImage if \c dst == NULL.
  * @return Pointer to ColorImage
  * @throw  ImageException will be thrown if \c dst != NULL and the size of \c dst and \c src is not equal.
  */
  ColorImage* yuvToRGB(const ColorImage& src, ColorImage* dst=NULL);

    /**
    * Convert the RGB-ColorImage \c src into a YUV-ColorImage \c dst .
    * @param src source RGB image
    * @param dst optional buffer to be used as target.<br>
    *            Create a new ColorImage if \c dst == NULL.
    * @return Pointer to ColorImage
    * @throw ImageException will be thrown if \c dst != NULL and the size of \c dst and \c src is not equal.
    */
    ColorImage* rgbToYUV(const ColorImage& src, ColorImage* dst=NULL);

    /**
    * \}
    * @name Gray-RGB Conversion
    * \{
    */

    /**
    * Create a lookup table of size 256x3 for faster rgbToGray conversion.
    * @return Pointer to ImageT<int>
    *
    */
    ImageT<int>* rgbToGrayLUT();

  /**
  * Convert the RGB-ColorImage \c src into a Image \c dst .
  * @param src          source RGB image
  * @param dst          optional buffer to be used as target.<br>
    *                     Create a new ColorImage if \c dst == NULL.
    * @param rgbToGrayLUT optional lookup table (only if no Ipp is used and P = Ipp8u)
  * @return Pointer to Image
  * @throw ImageException will be thrown if \c dst != NULL and the size of \c src and \c dst is not equal.
  */
  template<class P>
    ImageT<P>* rgbToGray(const ColorImageT<P>& src, ImageT<P>* dst=NULL,
                             const ImageT<int>* rgbToGrayLUT=NULL);

    /**
    * Convert the Image \c src into a RGB-ColorImage \c dst .
    * @param src source gray image
    * @param dst optional buffer to be used as target.<br>
    *            Create a new gray image if \c dst == NULL.
    * @return Pointer to gray image
    * @throw ImageException will be thrown if \c dst != NULL and the size of \c src and \c dst is not equal.
    */
    template<class P>
    ColorImageT<P>* grayToRGB(const ImageT<P>& src, ColorImageT<P>* dst=NULL);

    /**
     * convert a gray value to RGB pseudo colors (gray value must be between 0 and 1)
     */
    void convertToPseudoColor ( double x, double & r, double & g, double & b );

    /**
    * Convert the Image \c src into a RGB-ColorImage \c dst using pseudo colors.
    * @param src source gray image
    * @param dst result image
    */
    template<class P>
    void imageToPseudoColor ( const NICE::ImageT<P> & src, NICE::ColorImage & dst );

    /**
    * Convert the matrix \c src into a RGB-ColorImage \c dst using pseudo colors.
    * @param src source gray image
    * @param dst result image
    */
    template<class P>
    void matrixToPseudoColor ( const NICE::MatrixT<P> & m, NICE::ColorImage & img );

    /**
    * Convert a signed image into a colored image
    * (white positiv values, red negativ values).
    * @note usefull to display float or signed images
    * @param src source gray image
    * @param dst optional buffer to be used as target.<br>
    *            Create a new ColorImage if \c dst == NULL.
    * @return Pointer to ColorImage
    */
    template<class P>
    ColorImage* signedImageToRGB(const ImageT<P>& src, ColorImageT<Ipp8u>* dst=NULL);

    /**
    * \}
    * @name Gray-Float Conversion
    * \{
    */

    /**
    * Convert the gray image \c src into a float image \c dst .
    * @param src source gray image.
    * @param dst optional buffer to be used as target.<br>
    *            Create a new FloatImage if \c dst == NULL.
    * @return Pointer to FloatImage
    * @throw ImageException will be thrown if \c dst != NULL and the size of \c src and \c dst is not equal.
    */
    template<class P>
    FloatImage* grayToFloat(const ImageT<P>& src, FloatImage* dst=NULL);

    /**
    * Convert the float image \c src into a gray image \c dst just rounded (not scaled).
    * @param src       source float image
    * @param dst       optional buffer to be used as target.<br>
    *                  Create a new ColorImage if \c dst == NULL.
    * @param roundMode rounding mode for floating point conversion
    * - ippRndZero : floating-point value will be truncated toward zero
    * - ippRndNear : floating-point value will be rounded to the nearest integer
    * @return Pointer to Image
    * @throw ImageException will be thrown if \c dst != NULL and the size of \c src and \c dst is not equal.
    */
    template<class P>
    ImageT<P>* floatToGray(const FloatImage& src, ImageT<P>* dst=NULL,
                               IppRoundMode roundMode=ippRndNear);

    /**
    * Convert the float image \c src into a gray image \c dst by scaling with p' = 255/(fmax-fmin)*(p-fmin).
    * @param src source float image
    * @param dst optional buffer to be used as target.<br>
    *            Create a new ColorImage if \c dst == NULL.
    * @return Pointer to Image
    * @throw ImageException will be thrown if \c dst != NULL and the size of \c src and \c dst is not equal.
    */
    Image* floatToGrayScaled(const FloatImage& src, Image* dst=NULL);

    /**
    * Convert the float image \c src into a gray image \c dst by scaling with p' = 255/(\c fmax-\c fmin)*(p-\c fmin) .
    * @param src  source float image
    * @param fmin minimum float value
    * @param fmax maximum float value
    * @param dst  optional buffer to be used as target.<br>
    *             Create a new ColorImage if \c dst == NULL.
    * @return Pointer to Image
    * @throw ImageException will be thrown if \c dst != NULL and the size of \c src and \c dst is not equal.
    */
    Image* floatToGrayScaled(const FloatImage& src, Ipp32f fmin, Ipp32f fmax, Image* dst=NULL);

    /**
    * \}
    * @name RGB-Float Conversion
    * \{
    */

    /**
    * Convert the RGB-ColorImage \c src into a FloatImage \c dst containing all rgb values.<br>
    * Result image is 3 times wider.
    * @param src source RGB image
    * @param dst optional buffer to be used as target.<br>
    *            Create a new FloatImage if \c dst == NULL.
    * @return Pointer to FloatImage
    * @throw ImageException will be thrown if \c dst != NULL and the size of \c src and \c dst is not equal.
    */
    FloatImage* rgbToFloat(const ColorImage& src, FloatImage* dst = NULL);

    /**
    * \}
    * @name BitDepth Conversion
    * \{
    */

    /**
     * @example image_convert.cpp
     */

    /**
    * Convert the gray image \c src  to a gray image \c dst with a different bitdepth.
    * @note Ipp only supports the following conversions:
    * - 8u16u, 8u16s, 8u32s,  8s32s, 16u32s
    * - 8u32f, 8s32f, 16u32f, 16s32f
    * - 16u8u, 16s8u, 32s8u,  32s8s
    * - 32f8u, 32f8s, 32f16u, 32f16s
    * @param src source gray image
    * @param dst optional buffer to be used as target.<br>
    *            Create a new Image if \c dst == NULL.
    * @return Pointer to Image
    * @throw ImageException will be thrown if \c dst != NULL and the size of \c src and \c dst is not equal.
    */
    template<class P1, class P2>
    ImageT<P2>* convertBitDepth(const ImageT<P1>& src, ImageT<P2>* dst);

    /**
    * Convert the color image \c src to a color image \c dst with a different bitdepth.
    * @note Ipp only supports the following conversions:
    * - 8u16u, 8u16s, 8u32s,  8s32s, 16u32s
    * - 8u32f, 8s32f, 16u32f, 16s32f
    * - 16u8u, 16s8u, 32s8u,  32s8s
    * - 32f8u, 32f8s, 32f16u, 32f16s
    * @param src source color image
    * @param dst optional buffer to be used as target.<br>
    *            Create a new ColorImage if \c dst == NULL.
    * @return Pointer to ColorImage
    * @throw ImageException will be thrown if \c dst != NULL and the size of \c src and \c dst is not equal.
    */
    template<class P1, class P2>
    ColorImageT<P2>* convertBitDepth(const ColorImageT<P1>& src, ColorImageT<P2>* dst);

    /**
    * \}
    * @name Interpolation
    * @note This functions are only available with ipp support.
    * \{
    */

  /**
  * Remap Image src into the Image dst using lookup tables.
  * @param src source gray image
  * @param dst destination gray image
  * @param px 2D float image containing new x coordinate
  * @param py 2D float image containing new y coordinate
  * @param interpolation interpolation type (IPPI_INTER_NN|IPPI_INTER_LINEAR|IPPI_INTER_CUBIC)
  *                  nearest neighbor interpolation, linear interpolation or cubic interpolation
  * @return Pointer to Image
  */
  Image* remap(const Image& src, const FloatImage &px, const FloatImage &py,
               Image* dst = NULL, int interpolation=IPPI_INTER_LINEAR);

  /**
  * Remap ColorImage src into the ColorImage dst using lookup tables.
  * @param src source RGB image
  * @param dst destination RGB image
  * @param px 2D float image containing new x coordinate
  * @param py 2D float image containing new y coordinate
  * @param interpolation interpolation type (IPPI_INTER_NN|IPPI_INTER_LINEAR|IPPI_INTER_CUBIC)
  *          nearest neighbor interpolation, linear interpolation or cubic interpolation
  * @return Pointer to ColorImage
  */
  ColorImage* remap(const ColorImage& src, const FloatImage &px, const FloatImage &py,
                ColorImage* dst = NULL, int interpolation=IPPI_INTER_LINEAR);

  /**
  * Scale ImageT src into the ImageT dst using scale factors xFactor and yFactor.
  * @param src source ImageT
  * @param dst destination ImageT
  * @param xFactor factor for scaling the x-axis if 0 it is caculated by src vs. dst
  * @param yFactor factor for scaling the y-axis if 0 it is caculated by src vs. dst
  * @param interpolation interpolation type
  *       (IPPI_INTER_NN|IPPI_INTER_LINEAR|IPPI_INTER_CUBIC)
  *         nearest neighbor interpolation, linear interpolation
  *        or cubic interpolation
  * @return Pointer to ImageT<P>
  */
  template<class P>
  ImageT<P>* scale(const ImageT<P>& src, ImageT<P>* dst,
                       double xFactor=0.0, double yFactor=0.0,
                       int interpolation=IPPI_INTER_LINEAR);

  //! see scale()
  template<class P>
  inline ImageT<P>* resize(const ImageT<P>& src, ImageT<P>* dst,
                        double xFactor=0.0, double yFactor=0.0,
                        int interpolation=IPPI_INTER_LINEAR) {
    return scale(src, dst, xFactor, yFactor, interpolation);
  }

  /**
  * Scale ColorImageT src into the ColorImageT dst using scale factors xFactor and yFactor.
  * @param src source ColorImageT
  * @param dst destination ColorImageT
  * @param xFactor factor for scaling the x-axis if 0 it is caculated by src vs. dst
  * @param yFactor factor for scaling the y-axis if 0 it is caculated by src vs. dst
  * @param interpolation interpolation type (IPPI_INTER_NN|IPPI_INTER_LINEAR|IPPI_INTER_CUBIC)
  *                      nearest neighbor interpolation, linear interpolation or cubic interpolation
  * @return Pointer to ColorImageT<P>
  */
  template<class P>
  ColorImageT<P>* scale(const ColorImageT<P>& src, ColorImageT<P>* dst,
                        double xFactor=0.0, double yFactor=0.0,
                        int interpolation=IPPI_INTER_LINEAR);

  //! see scale()
  template<class P>
  inline ColorImageT<P>* resize(const ColorImageT<P>& src, ColorImageT<P>* dst,
                         double xFactor=0.0, double yFactor=0.0,
                         int interpolation=IPPI_INTER_LINEAR) {
    return scale(src, dst, xFactor, yFactor, interpolation);
  }

    /**
    * @name Some Helper Functions
    * \{
    */

    /**
    * Clip a \c rect within \c image.
    * @param image The image
    * @param rect  The rectangle
    * @return \c Rect
    */
    Rect clipRect(const MultiChannelImageAccess& image, const Rect& rect);

  /**
  * Make an \c IppiRect for the full image.
  * @param image The image
  * @return \c IppiRect
  */
  IppiRect makeRectFullImage(const MultiChannelImageAccess& image);

  /**
  * Make an \c IppiSize for the full image.
  * @param image The image
  * @return \c IppiSize
  */
  IppiSize makeROIFullImage(const MultiChannelImageAccess& image);

  /**
  * Get an \c IppiSize for \c rect clipped within \c image.
  * @param image The image
  * @param rect The rectangle
  * @return \c IppiSize
  */
  IppiSize makeROIRect(const MultiChannelImageAccess& image, const Rect& rect);

    /**
    * Work around a certain IPP bug (?).
    * @param ippiSize input and output
    * @param clippedROI input and output
    */
    void preventIppBug(IppiSize& ippiSize, Rect& clippedROI);
} // namespace

//#ifdef __GNUC__
#include <core/image/Convert.tcc>
//#endif

#endif // LIMUN_CONVERT_H
