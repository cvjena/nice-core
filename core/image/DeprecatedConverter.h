/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libimage - An image library
 * See file License for license information.
 */
/**
 * @file DeprecatedConverter.h
 * DEPRECATED
 * - Do NOT use this class in new code
 * - use the new functions in Convert.h, FilterT.h, etc.
 * @deprecated Use new functions in Convert.h, FilterT.h, ...
 */
#ifndef LIMUN_CONVERTER_H
#define LIMUN_CONVERTER_H

#include "core/basics/deprecated.h"

#include "core/image/ippwrapper.h"
#include "core/image/GrayColorImageCommonImplementation.h"
#include "core/image/RectT.h"
#include "core/vector/VectorT.h"
#include "core/image/Convert.h"

namespace NICE {
  class DeprecatedConverter;
  template<class P> class GrayColorImageCommonImplementationT;
  template<class P> class ColorImageT;
  template<class P> class ImageT;
  typedef ColorImageT<Ipp8u> ColorImage;
  typedef ColorImageT<Ipp8u> ThreeChannelImage;
  typedef ColorImageT<Ipp8u> HSVColorImage;
  typedef ImageT<Ipp8u>  Image;
  typedef ImageT<Ipp16s> GrayImage16s;
  typedef ImageT<Ipp32f> FloatImage;


/**
 * A DEPRECATED collection of image conversion functions, which has been
 * replaced by new functions in Convert.h, Filter.h, etc. Do NOT use this
 * class in new code!
 *
 * @deprecated Use new functions in Convert.h, Filter.h, ...
 *
 * @note Most functions are currently not supported without IPP
 *       and will throw an exception if compiled without IPP.
 *       Use new functions instead of this class if no IPP is available.
 *
 * @author Ferid Bajramovic (ferid [dot] bajramovic [at] informatik [dot] uni-jena [dot] de)
 */
class LIMUN_DEPRECATED DeprecatedConverter {
private:
#ifndef NICE_USELIB_IPP
  // lookup tables for rgb -> gray color transform
  static bool pLut_initialized;
  static int pLutRg[256];
  static int pLutGg[256];
  static int pLutBg[256];
#endif

 public:
  /**
   * Convert the HSV-ColorImage hsv into a RGB-ColorImage.
   * @param hsv Original HSV image
   * @param rgb optional buffer to be used as target.
   *            Create a new ColorImage if hsv == NULL.
   * @return ColorImage
   * @throw An ImageException will be thrown if
   *        rgb != NULL and the size of hsv and rgb are not equal.
   */
  static ColorImage* hsvToRGB(const HSVColorImage& hsv,
                                 ColorImage* rgb = NULL);

  /**
   * Convert the RGB-ColorImage rgb into a HSVColorImage.
   * @param rgb Original RGB image
   * @param hsv optional buffer to be used as target.
   *            Create a new HSVColorImage if hsv == NULL.
   * @return HSVColorImage
   * @throw An ImageException will be thrown if
   *        hsv != NULL and the size of rgb and hsv are not equal.
   */
  static HSVColorImage* rgbToHSV(const ColorImage& rgb,
                                 HSVColorImage* hsv = NULL);

  /**
   * Convert RGB to HSV inside a region of interest
   * (i.e. only a part of the image). The resulting image is
   * of the same (!) size as rgb.
   * @see rgbToHSV()
   * @param rgb input image
   * @param hsv optional buffer to be used as target.
   *            Create a new HSVColorImage if hsv == NULL.
   *            If hsv != NULL then size must be equal to rgb's size!
   * @param rect Region of interest
   */
  static HSVColorImage* rgbToHSVRegion(const ColorImage& rgb,
                                       HSVColorImage* hsv,
                                       const Rect rect);

  /**
   * Convert the RGB-ColorImage rgb into a Image.
   * @param rgb Original RGB image
   * @param gray optional buffer to be used as target.
   *             Create a new Image if gray == NULL.
   * @return Image
   * @throw An ImageException will be thrown if
   *        gray != NULL and the size of rgb and gray are not equal.
   */
  template<class P>
  static ImageT<P>* rgbToGray(const ColorImageT<P>& rgb,
                              ImageT<P>* gray = NULL);

  /**
   * Convert the Image gray into a RGB-ColorImage.
   * @param gray Original gray image
   * @param rgb optional buffer to be used as target.
   *             Create a new ColorImage if rgb == NULL.
   * @return ColorImage
   * @throw An ImageException will be thrown if
   *        rgb != NULL and the size of rgb and gray are not equal.
   */
  template<class P>
  static ColorImageT<P>* grayToRGB(const ImageT<P>& gray,
                                   ColorImageT<P>* rgb = NULL);

  /**
   * Convert the graylevel image to a graylevel image with a different bitdepth.
   * @param image Original graylevel image
   * @param buffer optional buffer to be used as target.
   *             Create a new Image if buffer == NULL.
   * @return graylevel image
   * @throw An ImageException will be thrown if
   *        buffer != NULL and the size of buffer and image are not equal.
   */
  template<class P1, class P2>
  static ImageT<P2>* convertBitDepth(const ImageT<P1>& image,
                                               ImageT<P2>* buffer=NULL);

  /**
   * Convert the color image to a color image with a different bitdepth.
   * @param image Original color image
   * @param buffer optional buffer to be used as target.
   *             Create a new ColorImage if buffer == NULL.
   * @return color image pointer
   * @throw An ImageException will be thrown if
   *        buffer != NULL and the size of buffer and image are not equal.
   */
  template<class P1, class P2>
  static ColorImageT<P2>* convertBitDepth(const ColorImageT<P1>& image,
                                               ColorImageT<P2>* buffer=NULL);

  /**
   * Convert the graylevel image gray into a FloatImage.
   * @param gray Original graylevel image
   * @param fimage optional buffer to be used as target.
   *             Create a new FloatImage if fimage == NULL.
   * @return FloatImage
   * @throw An ImageException will be thrown if
   *        fimage != NULL and the size of fimage and gray are not equal.
   */
  template<class P>
  static FloatImage* grayToFloat(const ImageT<P>& gray,
                              FloatImage* fimage = NULL);

  /**
   * Convert the FloatImage into a Image just rounded (not scaled)
   * @param fimage Original float image
   * @param gray optional buffer to be used as target.
   *            Create a new Image if gray == NULL.
   * @return Image*
   * @throw An ImageException will be thrown if
   *        gray != NULL and the size of fimage and gray are not equal.
   */
  template<class P>
  static ImageT<P>* floatToGray(const FloatImage& fimage,
                              ImageT<P>* gray = NULL);

  /**
   * Convert the FloatImage into a Image by scaling with p' = 255/(max-min)*(p-min)
   * @param fimage Original float image
   * @param gray optional buffer to be used as target.
   *            Create a new Image if gray == NULL.
   * @return Image*
   * @throw An ImageException will be thrown if
   *        gray != NULL and the size of fimage and gray are not equal.
   */
  template<class P>
  static ImageT<P>* floatToGrayScaled(const FloatImage& fimage,
                              ImageT<P>* gray = NULL);

  /**
   * Convert the FloatImage into a Image by scaling with p' = 255/(fmax-fmin)*(p-fmin)
   * @param fimage Original float image
   * @param fmin minimum float value
   * @param fmax maximum float value
   * @param gray optional buffer to be used as target.
   *            Create a new Image if gray == NULL.
   * @return Image*
   * @throw An ImageException will be thrown if
   *        gray != NULL and the size of fimage and gray are not equal.
   */
  template<class P>
  static ImageT<P>* floatToGrayScaled(const FloatImage& fimage, Ipp32f fmin, Ipp32f fmax,
                              ImageT<P>* gray = NULL);

  /**
   * Convert the 16bit graylevel image gray into a FloatImage.
   * @param gray Original 16 bit graylevel image
   * @param fimage optional buffer to be used as target.
   *             Create a new FloatImage if fimage == NULL.
   * @return FloatImage
   * @throw An ImageException will be thrown if
   *        fimage != NULL and the size of rgb and gray are not equal.
   */
  static FloatImage* gray16sToFloat(const GrayImage16s& gray,
                              FloatImage* fimage = NULL);


  /**
   * Convert the RGB-ColorImage rgb into a FloatImage containing all rgb values,
   * so that the resulting image is 3 times wider.
   * @param rgb Original RGB image
   * @param fimage optional buffer to be used as target.
   *             Create a new FloatImage if fimage == NULL.
   * @return FloatImage
   * @throw An ImageException will be thrown if
   *        fimage != NULL and the size of rgb and gray are not equal.
   */
  static FloatImage* rgbToFloat(const ColorImage& rgb,
                              FloatImage* fimage = NULL);

  /**
   * Set Image dst to grayvalue value.
   * @param dst destination gray image
   * @param value destination grayvalue
   */
  static void set(const unsigned char& value, Image* dst);

  /**
   * Mirror Image on horizontal, vertical or both axis.
   * @param src source gray image
   * @param dst destination gray image
   * @param axis mirror type (horizontal:ippAxsHorizontal, vertical:ippAxsVertical, both:ippAxsBoth)
   * @return Image
   */
  template<class P>
  static ImageT<P>* mirror(const ImageT<P>& src, IppiAxis axis, ImageT<P>* dst = NULL);

  /**
   * Mirror Image on horizontal, vertical or both axis.
   * @param src source gray image
   * @param dst destination gray image
   * @param axis mirror type (horizontal:ippAxsHorizontal, vertical:ippAxsVertical, both:ippAxsBoth)
   * @return Image
   */
  template<class P>
  static ColorImageT<P>* mirror(const ColorImageT<P>& src, IppiAxis axis, ColorImageT<P>* dst = NULL);

  /**
   * Remap Image src into the Image dst using lookup tables.
   * @param src source gray image
   * @param dst destination gray image
   * @param px 2D float image containing new x coordinate
   * @param py 2D float image containing new y coordinate
   * @param interpolation interpolation type (IPPI_INTER_NN|IPPI_INTER_LINEAR|IPPI_INTER_CUBIC) nearest neighbor interpolation, linear interpolation or cubic interpolation
   * @return Image
   */
  static Image* remap(const Image& src, const FloatImage &px, const FloatImage &py, Image* dst = NULL, int interpolation=IPPI_INTER_LINEAR);

  /**
   * Remap ColorImage src into the ColorImage dst using lookup tables.
   * @param src source RGB image
   * @param dst destination RGB image
   * @param px 2D float image containing new x coordinate
   * @param py 2D float image containing new y coordinate
   * @param interpolation interpolation type (IPPI_INTER_NN|IPPI_INTER_LINEAR|IPPI_INTER_CUBIC) nearest neighbor interpolation, linear interpolation or cubic interpolation
   * @return ColorImage
   */
  static ColorImage* remap(const ColorImage& src, const FloatImage &px, const FloatImage &py, ColorImage* dst = NULL, int interpolation=IPPI_INTER_LINEAR);

  /**
   * Resizes ImageT src into the ImageT dst using scale factors xFactor and yFactor.
   * @param src source ImageT
   * @param dst destination ImageT
   * @param xFactor factor for scaling the x-axis if 0 it is caculated by src vs. dst
   * @param yFactor factor for scaling the y-axis if 0 it is caculated by src vs. dst
   * @param interpolation interpolation type (IPPI_INTER_NN|IPPI_INTER_LINEAR|IPPI_INTER_CUBIC) nearest neighbor interpolation, linear interpolation or cubic interpolation
   * @return ImageT<P>
   */
   template<class P>
   static ImageT<P>* resize(const ImageT<P>& src, ImageT<P>* dst, double xFactor=0.0, double yFactor=0.0, int interpolation=IPPI_INTER_LINEAR);

  /**
   * Resizes ColorImageT src into the ColorImageT dst using scale factors xFactor and yFactor.
   * @param src source ColorImageT
   * @param dst destination ColorImageT
   * @param xFactor factor for scaling the x-axis if 0 it is caculated by src width vs. dst width
   * @param yFactor factor for scaling the y-axis if 0 it is caculated by src height vs. dst height
   * @param interpolation interpolation type (IPPI_INTER_NN|IPPI_INTER_LINEAR|IPPI_INTER_CUBIC) nearest neighbor interpolation, linear interpolation or cubic interpolation
   * @return ColorImageT
   */
   template<class P>
   static ColorImageT<P>* resize(const ColorImageT<P>& src, ColorImageT<P>* dst, double xFactor=0.0, double yFactor=0.0, int interpolation=IPPI_INTER_LINEAR);

  /**
   * Blurs Image src into the Image dst.
   * @param src source gray image
   * @param dst destination gray image
   * @param size length and width of the square used for mean filter
   * @return Image
   */
  static Image* blur(const Image& src, const int& size, Image* dst);

  /**
   * Filters Image src into the Image dst using a median filter.
   * @param src source gray image
   * @param dst destination gray image
   * @param size length and width of the square used for median filter
   * @return Image
   */
  static Image* median(const Image& src, const int& size, Image* dst);

  /**
   * Generate a binarized image from Image img
   * @param img gray image
   * @param threshold threshold
   */
  static void thresholdIP(Image& img, int threshold);

  /**
   * Generate a threshold image from Image img
   * @param img gray image
   * @param threshold threshold
   * @param value set pixel less than threshold to this value
   */
  static void lowerThresholdIP(Image& img, int threshold, int value=0);

  /**
   * Generate a threshold image from Image img
   * @param img gray image
   * @param threshold threshold
   * @param value set pixel greater than threshold to this value
   */
  static void upperThresholdIP(Image& img, int threshold, int value=255);

  /**
   * Filters Image src into the Image dst using a 3x3 erosion.
   * @param src source gray image
   * @param dst destination gray image
   * @return Image
   */
  static Image* erode(const Image& src, Image* dst=NULL);

  /**
   * Filters Image img using a 3x3 erosion (in place).
   * @param img gray image
   */
  static void erodeIP(Image& img);

  /**
   * Filters Image src into the Image dst using a 3x3 dilation.
   * @param src source gray image
   * @param dst destination gray image
   * @return Image
   */
  static Image* dilate(const Image& src, Image* dst=NULL);

  /**
   * Filters Image img using a 3x3 dilation (in place).
   * @param img gray image
   */
  static void dilateIP(Image& img);

  /**
   * Calculate a histogram.
   * @param src source image
   * @param min lower boundary (included)
   * @param max upper boundary (not included)
   * @param nlevels number of histogram bins
   * @return gray value histogram
   */
  template<class P>
  static VectorT<int>* histogram(const ImageT<P>& src, int min=0, int max=256, int nlevels=256);
  /**
   * Calculate a histogram.
   * @param src source image
   * @param histo outputvector for the histogram (number of element is the number of histogram bins)
   * @param min lower boundary (included)
   * @param max upper boundary (not included)
   * @return gray value histogram
   */
  template<class P>
  static VectorT<int>* histogram(const ImageT<P>& src, VectorT<int> *histo, int min=0, int max=256);
  /**
   * Calculate a histogram.
   * @param src source image
   * @param min lower boundary (included)
   * @param max upper boundary (not included)
   * @param nlevels number of histogram bins
   * @return histogram (histogram bins for red, histogram bins for green and histogram bins for blue)
   */
  template<class P>
  static VectorT<int>* histogram(const ColorImageT<P>& src, int min=0, int max=256, int nlevels=256);
  /**
   * Calculate a histogram.
   * @param src source image
   * @param histo outputvector for the histogram (number of element / 3 is the number of histogram bins per color)
   * @param min lower boundary (included)
   * @param max upper boundary (not included)
   * @return histogram (histogram bins for red, histogram bins for green and histogram bins for blue)
   */
  template<class P>
  static VectorT<int>* histogram(const ColorImageT<P>& src, VectorT<int> *histo, int min=0, int max=256);

  /**
   * Calculate a normalized histogram.
   * @param src source image
   * @param min lower boundary (included)
   * @param max upper boundary (not included)
   * @param nlevels number of histogram bins
   * @return gray value normalized histogram
   */
  template<class P>
  static VectorT<float>* histogramNormalized(const ImageT<P>& src, int min=0, int max=256, int nlevels=256);
  /**
   * Calculate a normalized histogram.
   * @param src source image
   * @param histo outputvector for the histogram (number of element is the number of histogram bins)
   * @param min lower boundary (included)
   * @param max upper boundary (not included)
   * @return gray value normalized histogram
   */
  template<class P>
  static VectorT<float>* histogramNormalized(const ImageT<P>& src, VectorT<float> *histo, int min=0, int max=256);
  /**
   * Calculate a normalized histogram.
   * @param src source image
   * @param min lower boundary (included)
   * @param max upper boundary (not included)
   * @param nlevels number of histogram bins
   * @return normalized histogram (histogram bins for red, histogram bins for green and histogram bins for blue)
   */
  template<class P>
  static VectorT<float>* histogramNormalized(const ColorImageT<P>& src, int min=0, int max=256, int nlevels=256);
  /**
   * Calculate a normalized histogram.
   * @param src source image
   * @param histo outputvector for the histogram (number of element / 3 is the number of histogram bins per color)
   * @param min lower boundary (included)
   * @param max upper boundary (not included)
   * @return normalized histogram (histogram bins for red, histogram bins for green and histogram bins for blue)
   */
  template<class P>
  static VectorT<float>* histogramNormalized(const ColorImageT<P>& src, VectorT<float> *histo, int min=0, int max=256);

  /**
   * Calculate a cumulative histogram.
   * @param src source image
   * @param min lower boundary (included)
   * @param max upper boundary (not included)
   * @param nlevels number of histogram bins
   * @return gray value cumulative histogram
   */
  template<class P>
  static VectorT<int>* histogramCumulative(const ImageT<P>& src, int min=0, int max=256, int nlevels=256);
  /**
   * Calculate a cumulative histogram.
   * @param src source image
   * @param histo outputvector for the histogram (number of element is the number of histogram bins)
   * @param min lower boundary (included)
   * @param max upper boundary (not included)
   * @return gray value cumulative histogram
   */
  template<class P>
  static VectorT<int>* histogramCumulative(const ImageT<P>& src, VectorT<int> *histo, int min=0, int max=256);
  /**
   * Calculate a cumulative histogram.
   * @param src source image
   * @param min lower boundary (included)
   * @param max upper boundary (not included)
   * @param nlevels number of histogram bins
   * @return cumulative histogram (histogram bins for red, histogram bins for green and histogram bins for blue)
   */
  template<class P>
  static VectorT<int>* histogramCumulative(const ColorImageT<P>& src, int min=0, int max=256, int nlevels=256);
  /**
   * Calculate a cumulative histogram.
   * @param src source image
   * @param histo outputvector for the histogram (number of element / 3 is the number of histogram bins per color)
   * @param min lower boundary (included)
   * @param max upper boundary (not included)
   * @return cumulative histogram (histogram bins for red, histogram bins for green and histogram bins for blue)
   */
  template<class P>
  static VectorT<int>* histogramCumulative(const ColorImageT<P>& src, VectorT<int> *histo, int min=0, int max=256);

    /**
    * Compute gradient streng image for a given vertical and horizontal gradient image
    * @param  dx vertical gradient of a Image
    * @param  dy horizontal gradient of a Image
    * @param  buffer target buffer
    * @return FloatImage
    * @throw  An ImageException will be thrown if the size of dx and dy are not equal.
    */
    static FloatImage* gradientStrength(const GrayImage16s& dx, const GrayImage16s& dy, FloatImage *buffer=NULL);
  /**
  * nonMaximumSuppression
  * @return FloatImage
  */
    static Image* nonMaximumSuppression(const GrayImage16s& dx, const GrayImage16s& dy, const FloatImage &mag, Image *buffer=NULL);

  /**
   * Calculates bitwise AND between the corresponding pixels of the ColorImage src0 and ColorImage src1 into the ColorImage dst.
   * @param src0 source color image
   * @param src1 source color image
   * @param dst destination color image
   * @return ColorImage
   */
  template<class P>
  static ColorImageT<P>* And(const ColorImageT<P>& src0, const ColorImageT<P>& src1, ColorImageT<P>* dst=NULL);

  /**
   * Calculates bitwise AND between the corresponding pixels of the Image src0 and Image src1 into the Image dst.
   * @param src0 source gray image
   * @param src1 source gray image
   * @param dst destination gray image
   * @return Image
   */
  template<class P>
  static ImageT<P>* And(const ImageT<P>& src0, const ImageT<P>& src1, ImageT<P>* dst=NULL);

  /**
   * Calculates the MEAN of the corresponding pixels of the ColorImage src0 and ColorImage src1 into the ColorImage dst.
   * @param src0 source color image
   * @param src1 source color image
   * @param dst destination color image
   * @return ColorImage
   */
  template<class P>
  static ColorImageT<P>* mean(const ColorImageT<P>& src0, const ColorImageT<P>& src1, ColorImageT<P>* dst=NULL);

  /**
   * Calculates the MEAN of the corresponding pixels of the Image src0 and Image src1 into the Image dst.
   * @param src0 source gray image
   * @param src1 source gray image
   * @param dst destination gray image
   * @return Image
   */
  template<class P>
  static ImageT<P>* mean(const ImageT<P>& src0, const ImageT<P>& src1, ImageT<P>* dst=NULL);

  /**
   * Calculates the absolute difference between Image src0 and Image src1 into the Image dst.
   * @param src0 source gray image
   * @param src1 source gray image
   * @param dst destination gray image
   * @return Image
   */
  static Image* absDiff(const Image& src0, const Image& src1, Image* dst=NULL);

  /**
   * Calculates the absolute difference between ColorImage src0 and ColorImage src1 into the ColorImage dst.
   * @param src0 source color image
   * @param src1 source color image
   * @param dst destination color image
   * @return ColorImage
   */
  static ColorImage* absDiff(const ColorImage& src0, const ColorImage& src1, ColorImage* dst=NULL);

  /**
   * Copies pixels from inside a rectangle in src to dst top left.
   * @param src source gray image
   * @param x0 left border of the rectangle in src
   * @param y0 top border of the rectangle in src
   * @param x1 right border of the rectangle in src
   * @param y1 lower border of the rectangle in src
   * @param dst destination gray image
   * @return Image
   */
  static Image* copyRect(const Image& src, const int& x0, const int& y0, const int& x1, const int& y1, Image* dst);

  /**
   * Copies pixels from inside a rectangle in src to dst top left.
   * @param src source color image
   * @param x0 left border of the rectangle in src
   * @param y0 top border of the rectangle in src
   * @param x1 right border of the rectangle in src
   * @param y1 lower border of the rectangle in src
   * @param dst destination color image
   * @return ColorImage
   */
  static ColorImage* copyRect(const ColorImage& src, const int& x0, const int& y0, const int& x1, const int& y1, ColorImage* dst);

  /**
   * Convert RGB to HSV inside a region of interest
   * (i.e. only a part of the image). The resulting image is
   * of the same (!) size as rgb.
   * @see rgbToGray()
   * @param rgb input image
   * @param gray optional buffer to be used as target.
   *             Create a new Image if hsv == NULL.
   *             If gray != NULL then size must be equal to rgb's size!
   * @param rect Region of interest
   */
  static Image* rgbToGrayRegion(const ColorImage& rgb,
                                    Image* gray,
                                    const Rect rect);

  /**
   * Compute horizontal part of the gradient of a Image via Sobel
   * inside a region of interest (i.e. only a part of the image).
   * The resulting image is of the same (!) size as gray.
   * @param gray Original gray image
   * @param dx optional buffer to be used as target.
   *           Create a new GrayImage16s if dx == NULL.
   *           If dx != NULL then size must be equal to gray's size!
   * @param rect Region of interest
   * @return GrayImage16s
   * @throw An ImageException will be thrown if
   *        dx != NULL and the size of gray and dx are not equal.
   */
  static GrayImage16s* grayToDxRegion(const Image& gray,
                                      GrayImage16s* dx,
                                      Rect rect);

  /**
   * Canny algorithm for edge detection.
   * @param srcdx x-derivate of Image
   * @param srcdy y-derivate of Image
   * @param low lower edge threshold
   * @param high upper edge threshold
   * @param dst destination Image
   * @return ImageT<Ipp16s>
   */
  static Image* canny(GrayImage16s& srcdx, GrayImage16s &srcdy,
                          float low, float high, Image* dst=NULL);

  /**
   * Filters Image \c src by columns into the Image \c dst using Sobel 3x3.
   * @param src source gray image
   * @param dst destination gray image
   * @return ImageT<Ipp16s>
   */
  template<class P>
  static ImageT<P>* grayToDx(const ImageT<P>& src, ImageT<P>* dst=NULL);
  static GrayImage16s* grayToDx(const Image& src, GrayImage16s* dst=NULL);


  /**
   * Filters Image \c src by rows into the Image \c dst using Sobel 3x3.
   * @param src source gray image
   * @param dst destination gray image
   * @return ImageT<Ipp16s>
   */
  template<class P>
  static ImageT<P>* grayToDy(const ImageT<P>& src, ImageT<P>* dst=NULL);
  static GrayImage16s* grayToDy(const Image& src, GrayImage16s* dst=NULL);

  /**
   * Filters Image \c src by columns into the Image \c dst using filter kernel \c kernel.
   * @param src source gray image
   * @param kernel filter kernel
   * @param anchor vertical offset to the kernelposition if negativ use center position
   * @param dst destination gray image
   * @return Image
   */
  template<class P>
  static ImageT<P>* filterX(const ImageT<P>& src, const VectorT<float> &kernel, int anchor=-1, ImageT<P>* dst=NULL);
  static Image* filterX(const Image& src, const VectorT<int> &kernel, int anchor=-1, int divisor=1, Image* dst=NULL);

  /**
   * Filters Image \c src by rows into the Image \c dst using filter kernel \c kernel.
   * @param src source gray image
   * @param kernel filter kernel
   * @param anchor horizontal offset to the kernelposition if negativ use center position
   * @param dst destination gray image
   * @return Image
   */
  template<class P>
  static ImageT<P>* filterY(const ImageT<P>& src, const VectorT<float> &kernel, int anchor=-1, ImageT<P>* dst=NULL);
  static Image* filterY(const Image& src, const VectorT<int> &kernel, int anchor=-1, int divisor=1, Image* dst=NULL);

  /**
   * Filters Image \c src by rows into the Image \c dst using filter kernel \c kernel.
   * @param src source gray image
   * @param kernel filter kernel (kernel cooefficient in inverse order!, use noAlignment for kernel image!)
   * @param anchorx horizontal offset to the kernelposition if negativ use center position
   * @param anchory vertical offset to the kernelposition if negativ use center position
   * @param dst destination gray image
   * @return Image
   */
  template<class P>
  static ImageT<P>* filter(const ImageT<P>& src, const FloatImage &kernel, int anchorx=-1, int anchory=-1, ImageT<P>* dst=NULL);
  static Image* filter(const Image& src, const ImageT<int> &kernel, int anchorx=-1, int anchory=-1, int divisor=1, Image* dst=NULL);

  /**
   * Performs a 2d valid convolution between src and kernel.
   * @param src source floatimage
   * @param kernel convolution floatimage (kernel cooefficient in inverse order!)
   * @param dst destination floatimage
   * @return Image
   */
  static FloatImage* convolution(const FloatImage& src, const FloatImage &kernel, FloatImage* dst=NULL);

  /**
   * Apply a 3x3 averaging filter to image
   * @param image Original image
   * @param buffer optional buffer to be used as target.
   *               Create a new ColorImage if buffer == NULL.
   *               If buffer != NULL then size must be equal to image's size!
   * @param rect Region of interest
   * @return ColorImage
   * @throw An ImageException will be thrown if
   *        buffer != NULL and the size of image and buffer are not equal.
   */
  static ColorImage* filterLowpassRegion(const ColorImage& image,
                                         ColorImage* buffer,
                                         Rect rect);

  /**
   * Apply a 3x3 gauss filter to image
   * @param image Original image
   * @param buffer optional buffer to be used as target.
   *               Create a new ColorImage if buffer == NULL.
   *               If buffer != NULL then size must be equal to image's size!
   * @param rect Region of interest
   * @return ColorImage
   * @throw An ImageException will be thrown if
   *        buffer != NULL and the size of image and buffer are not equal.
   */
  static ColorImage* filterGaussRegion(const ColorImage& image,
                                       ColorImage* buffer,
                                       Rect rect);
  /**
   * Apply a 3x3 gauss filter to image
   * @param image Original image
   * @param buffer optional buffer to be used as target.
   *               Create a new Image if buffer == NULL.
   * @return Image
   */
  template<class P>
  static ImageT<P>* filterGauss3x3(const ImageT<P>& image, ImageT<P>* buffer=NULL);

  /**
   * Apply a 3x3 gauss filter to image
   * @param image Original image
   * @param buffer optional buffer to be used as target.
   *               Create a new Image if buffer == NULL.
   * @return Image
   */
  template<class P>
  static ImageT<P>* filterGauss5x5(const ImageT<P>& image, ImageT<P>* buffer=NULL);

 /**
   * Apply a gauss filter with standard derivation sigma to image
   * @param image Original image
   * @param buffer optional buffer to be used as target.
   *               Create a new ColorImage if buffer == NULL.
   *               If buffer != NULL then size must be equal to image's size!
   * @param sigma standard derivation of the gauss distribution
   * @return ColorImage
   * @throw An ImageException will be thrown if
   *        buffer != NULL and the size of image and buffer are not equal.
   */
  static Image* filterGauss(const Image& image,
                                      float sigma,
                                      Image* buffer=NULL);
/*  static ColorImage* filterGauss(const ColorImage& image,
                                       float sigma,
                                       ColorImage* buffer=NULL);
*/
  /**
   * Compute vertical part of the gradient of a Image via Sobel
   * inside a region of interest (i.e. only a part of the image).
   * The resulting image is of the same (!) size as gray.
   * @param gray Original gray image
   * @param dy optional buffer to be used as target.
   *           Create a new GrayImage16s if dy == NULL.
   *           If dy != NULL then size must be equal to gray's size!
   * @param rect Region of interest
   * @return GrayImage16s
   * @throw An ImageException will be thrown if
   *        dy != NULL and the size of gray and dy are not equal.
   */
  static GrayImage16s* grayToDyRegion(const Image& gray,
                                      GrayImage16s* dy,
                                      const Rect rect);

  /**
   * Convert a floating point image into a gray image (in RGB format)
   */
  static ColorImage* floatImageToGrayRGB(const FloatImage& floatImage,
                                         ColorImage* image);

  /**
   * Convert a signed image into a colored image
   * (white positiv values, red negativ values).
   *  @note usefull to display float or signed images
   */
  template<class P>
  static ColorImage* signedImageToRGB(const ImageT<P>& image,
                                      ColorImage* colored);

  /**
   * Clip a \c rect within \c image.
   * @param image The image
   * @param rect The rectangle
   * @return \c Rect
   */
  static inline Rect clipRect(const MultiChannelImageAccess& image, const Rect rect) {
    return NICE::clipRect(image, rect);
  }

    /**
     * Make an \c IppiRect for the full image.
     * @param image The image
     * @return \c IppiRect
     */
  static inline IppiRect makeRectFullImage(const MultiChannelImageAccess& image) {
    return NICE::makeRectFullImage(image);
  }

    /**
     * Make an \c IppiSize for the full image.
     * @param image The image
     * @return \c IppiSize
     */
  static inline IppiSize makeROIFullImage(const MultiChannelImageAccess& image) {
    return NICE::makeROIFullImage(image);
  }

    /**
     * Get an \c IppiSize for \c rect clipped within \c image.
     * @param image The image
     * @param rect The rectangle
     * @return \c IppiSize
     */
  static inline IppiSize makeROIRect(const MultiChannelImageAccess& image, const Rect rect) {
    return NICE::makeROIRect(image, rect);
  }

  #ifdef NICE_USELIB_IPP
    /**
     * Work around a certain IPP bug (?).
     * @param ippiSize input and output
     * @param clippedROI input and output
     */
     static void preventIppBug(IppiSize& ippiSize, Rect& clippedROI) {
       return NICE::preventIppBug(ippiSize, clippedROI);
     }
  #endif // NICE_USELIB_IPP

 private:
  /**
   * Create result buffer.
   * @param image input
   * @param buffer image buffer for result
   * @return image buffer
   */
  template<class IMG, class BUFFER>
  static BUFFER* createResultBuffer(const IMG& image,
                                       BUFFER* buffer);

  /**
   * Create result buffer.
   * @param width width of the input image
   * @param height height of the input image
   * @param buffer image buffer for result
   * @return image buffer
   */
  template<class BUFFER>
  static BUFFER* createResultBuffer(const int width,
                                    const int height,
                                    BUFFER* buffer);

};

} // namespace

#include "core/image/ImageT.h"
#include "core/image/ImageT.h"
#include "core/image/ColorImageT.h"

//#ifdef __GNUC__
#include <core/image/DeprecatedConverter.tcc>
//#endif

#endif
