/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libimage - An image library
 * See file License for license information.
 */
#ifndef LIMUN_FILTER_H
#define LIMUN_FILTER_H


#include <core/image/ippwrapper.h>
#include <core/image/ImageOperators.h>

#include <core/vector/VectorT.h>
#include <core/vector/MatrixT.h>

#include <core/basics/RoundToNearest.h>

#include <core/image/ImageT.h>
#include <core/image/ColorImageT.h>
#include <core/image/Buffer.h>

#warning "Filter.h is obsolete. Please use FilterT.h instead and adapt your calls and implement the filter if necessary :)"

namespace NICE {
/**
* @name General Filter Functions
* \{
*/

/**
* Filters (=convolves) Image \c src by column into the
* Image \c dst using filter (=convolution) kernel \c kernel.
* Result will be scaled to fit the graylevel domain [0,255].
* @param src    source gray image
* @param kernel filter kernel (coefficients are used in inverse order,
*               i.e. as mathematical convolution kernel)
* @param dst    Optional buffer to be used as target.<br>
*               Create a new Image if \c dst == NULL.<br>
*               If \c dst != NULL then size must be equal to \c src 's size!
* @param anchor vertical offset to the kernelposition if negativ use center position
* @return Pointer to Image
* @throw ImageException will be thrown if \c dst != NULL and the size of \c src and \c dst is not equal.
* @note This function performs a mathematical convolution.
*       In image processing, linear filters are often defined
*       by "filter masks", which are NOT the same as convolution kernels.
*       The difference is a coordinate transformation on the filter mask:
*       index \c i becomes \c (kernel.size() \c - \c i),
*       i.e. the mask is flipped.
*/
Image* filterX ( const Image& src, const IntVector& kernel,
                 Image* dst = NULL, const int& anchor = -1 );

/**
* Filters (=convolves) Image \c src by column into the
* Image \c dst using filter (=convolution) kernel \c kernel.
* @copydoc filterX()
*/
template<class P>
ImageT<P>* filterX ( const ImageT<P>& src, const FloatVector& kernel,
                     ImageT<P>* dst = NULL, const int& anchor = -1 );

/**
* Filters (=convolves) Image \c src by rows into the
* Image \c dst using filter (=convolution) kernel \c kernel.
* Result will be scaled to fit the graylevel domain [0,255].
* @param src    source gray image
* @param kernel filter kernel (coefficients are used in inverse order,
*               i.e. as mathematical convolution kernel)
* @param dst    Optional buffer to be used as target.<br>
*               Create a new Image if \c dst == NULL.<br>
*               If \c dst != NULL then size must be equal to \c src 's size!
* @param anchor horizontal offset to the kernelposition, if negativ use center position
* @return Pointer to Image
* @throw  ImageException will be thrown if \c dst != NULL and the size of \c src and \c dst is not equal.
* @note This function performs a mathematical convolution.
*       In image processing, linear filters are often defined
*       by "filter masks", which are NOT the same as convolution kernels.
*       The difference is a coordinate transformation on the filter mask:
*       index \c i becomes \c (kernel.size() \c - \c i),
*       i.e. the mask is flipped.
*/
Image* filterY ( const Image& src, const IntVector& kernel,
                 Image* dst = NULL, const int& anchor = -1 );

/**
* Filters (=convolves) Image \c src by rows into the
* Image \c dst using filter (=convolution) kernel \c kernel.
* @copydoc filterY()
*/
template<class P>
ImageT<P>* filterY ( const ImageT<P>& src, const FloatVector& kernel,
                     ImageT<P>* dst = NULL, const int& anchor = -1 );

/**
* @example image_imageprocessing.cpp
*/

/**
* Filters (=convolves) Image \c src into the
* Image \c dst using filter (=convolution) kernel \c kernel.
* Result will be scaled to fit the graylevel domain [0,255].
* @param src  source gray image
* @param kernel filter kernel (coefficients are used in inverse order,
*               i.e. as mathematical convolution kernel)
* @param dst  Optional buffer to be used as target.<br>
*             Create a new Image if \c dst == NULL.<br>
*             If \c dst != NULL then size must be equal to \c src 's size!
* @param anchorx horizontal offset to the kernel position, if negativ use center position
* @param anchory vertical offset to the kernel position, if negativ use center position
* @throw ImageException will be thrown if \c dst != NULL and the size of \c src and \c dst is not equal.
* @return Pointer to Image
* @note This function performs a mathematical convolution.
*       In image processing, linear filters are often defined
*       by "filter masks", which are NOT the same as convolution kernels.
*       The difference is a coordinate transformation on the filter mask:
*       index \c i becomes \c (kernel.height() \c - \c i),
*       index \c j becomes \c (kernel.width() \c - \c j),
*       i.e. the mask is flipped at its center (in both dimensions).
*/
Image* filter ( const Image& src, const IntMatrix& kernel, Image* dst = NULL,
                const int& anchorx = -1, const int& anchory = -1 );

/**
* Filters (=convolves) Image \c src into the
* Image \c dst using filter (=convolution) kernel \c kernel.
* @copydoc filter()
*/
template<class P>
ImageT<P>* filter ( const ImageT<P>& src, const FloatMatrix& kernel, ImageT<P>* dst = NULL,
                    const int& anchorx = -1, const int& anchory = -1 );


/**
* \}
* @name Smoothing Functions
* \{
*/

/**
* Blurs Image \c src by rows into the Image \c dst using a mean kernel.
* @param src  source gray image
* @param size mean kernel of size 2*\c size + 1
* @param dst  Optional buffer to be used as target.<br>
*             Create a new Image if \c dst == NULL.<br>
*             If \c dst != NULL then size must be equal to \c src 's size!
* @throw ImageException will be thrown if \c dst != NULL and the size of \c src and \c dst is not equal.
* @return Pointer to Image
*/
Image* meanX ( const Image& src, const uint& size, Image* dst = NULL );

/**
* Blurs Image \c src by column into the Image \c dst using a mean kernel.
* @param src  source gray image
* @param size mean kernel of size 2*\c size + 1
* @param dst  Optional buffer to be used as target.<br>
*             Create a new Image if \c dst == NULL.<br>
*             If \c dst != NULL then size must be equal to \c src 's size!
* @throw ImageException will be thrown if \c dst != NULL and the size of \c src and \c dst is not equal.
* @return Pointer to Image
*/
Image* meanY ( const Image& src, const uint& size, Image* dst = NULL );

/**
* Blurs Image \c src by rows into the Image \c dst using a gaussian kernel.
* @param src  source gray image
* @param size gauss kernel of size:
*    - 1: 1x3 gauss kernel
*    - 2: 1x5 gauss kernel
* @param dst  Optional buffer to be used as target.<br>
*             Create a new Image if \c dst == NULL.<br>
* @throw ImageException will be thrown if \c dst != NULL and the size of \c src and \c dst is not equal.
* @return Pointer to Image
*/
Image* gaussX ( const Image& src, const uint& size, Image* dst = NULL );

ImageT<float>* gaussX ( const ImageT<float>& src, const uint& size, ImageT<float>* dst = NULL );

/**
* Blurs Image \c src by column into the Image \c dst using a gaussian kernel.
* @param src  source gray image
* @param size gauss kernel of size:
*    - 1: 3x1 gauss kernel
*    - 2: 5x1 gauss kernel
* @param dst  Optional buffer to be used as target.<br>
*             Create a new Image if \c dst == NULL.<br>
*             If \c dst != NULL then size must be equal to \c src 's size!
* @throw ImageException will be thrown if \c dst != NULL and the size of \c src and \c dst is not equal.
* @return Pointer to Image
*/
Image* gaussY ( const Image& src, const uint& size, Image* dst = NULL );
ImageT<float>* gaussY ( const ImageT<float>& src, const uint& size, ImageT<float>* dst = NULL );

/**
* Blurs Image \c src into the Image \c dst using a gauss filter with a specific standard deviation.
* The filter size is calculated using the standard deviation multiplied with 5.
* Boundary handling is done with a cropped filter.
* @param src  source gray image
* @param sigma standard deviation of the gauss filter
* @param dst  Optional buffer to be used as target.<br>
*             Create a new Image if \c dst == NULL.<br>
*             If \c dst != NULL then size must be equal to \c src 's size!
* @throw ImageException will be thrown if \c dst != NULL and the size of \c src and \c dst is not equal
*                       or an invalid size \c size is specified.
* @return Pointer to Image
*/
template<class P, class PCalc>
NICE::ImageT<P> *filterGaussSigma ( const NICE::ImageT<P> &src, double sigma, NICE::ImageT<P> *dst = NULL );

/**
   * Blurs Image \c src into the Image \c dst by approximating a gauss filter with a specific standard deviation through multiple mean filters
* The size of the mean filters is automatically calculated
* The second template parameter gives the type used to store sums of gray-values. The third template parameter,
* which is only necessary if use_filtersize_independent_implementation
* is set to true, specifies the data type of the temporary image used to handle the seperability of the mean filter.
* Boundary handling is done with a cropped filter if use_filtersize_independent_implementation is set to true, otherwise the borders of the image
* are ignored.
   * @param src  source gray image
   * @param sigma standard deviation of the gauss filter
   * @param dst  Optional buffer to be used as target.<br>
   *             Create a new Image if \c dst == NULL.<br>
   *             If \c dst != NULL then size must be equal to \c src 's size!
* @param use_filtersize_independent_implementation  if this flag is set to true, we use the implementation of the mean filter with a runtime
*  independent of the filter size. This is beneficial for large filter sizes. However, for small filter sizes (<10) the standard implementation is faster.
*  An analysis can be done with the program testApproxGaussFilter.
   * @throw ImageException will be thrown if \c dst != NULL and the size of \c src and \c dst is not equal
   *                       or an invalid size \c size is specified.
   * @return Pointer to Image
   */
template<class P, class PCalc, class PTemp>
NICE::ImageT<P> *filterGaussSigmaApproximate ( const NICE::ImageT<P> &src, double sigma, NICE::ImageT<P> *dst = NULL,
    bool use_filtersize_independent_implementation = true );

/**
* Blurs Image \c src into the Image \c dst using a mean filter.
* @param src  source gray image
* @param size mean mask of size (2*\c size + 1) x (2*\c size + 1)
* @param dst  Optional buffer to be used as target.<br>
*             Create a new Image if \c dst == NULL.<br>
*             If \c dst != NULL then size must be equal to \c src 's size!
* @throw ImageException will be thrown if \c dst != NULL and the size of \c src and \c dst is not equal.
* @return Pointer to Image
*/
Image* filterMean ( const Image& src, const uint& size, Image* dst = NULL );
template<class P, class PCalc>
ImageT<P>* filterMean ( const ImageT<P>& src, const uint& size, ImageT<P>* dst = NULL );

/**
   * Blurs Image \c src into the Image \c dst using a mean filter. This is the
* implementation of the filter with a runtime independent of the filter size.
* It is significantly faster for large filter sizes. An analysis can be done with the program
* testApproxGaussFilter.
* The second template parameter gives the type used to store sums of gray-values. The third template
* parameter specifies the data type of the temporary image used to handle the seperability of the mean filter.
* Boundary handling is done with a cropped filter if use_filtersize_independent_implementation is set to true, otherwise the borders of the image
* are ignored.
   * @param src  source gray image
   * @param size mean mask of size (2*\c size + 1) x (2*\c size + 1)
   * @param dst  Optional buffer to be used as target.<br>
   *             Create a new Image if \c dst == NULL.<br>
   *             If \c dst != NULL then size must be equal to \c src 's size!
   * @throw ImageException will be thrown if \c dst != NULL and the size of \c src and \c dst is not equal.
   * @return Pointer to Image
   */
template<class P, class PCalc, class PTemp>
ImageT<P>* filterMeanLargeFS ( const ImageT<P>& src, const uint& size, ImageT<P>* dst = NULL );

/**
* Blurs ColorImage \c src inplace using a mean filter.
* @param src  source color image
* @param size mean mask of size (2*\c size + 1) x (2*\c size + 1)
*/
void filterMeanIP ( const ColorImage& src, const uint& size );

/**
* Blurs Image \c src into the Image \c dst using a gauss filter.
* @param src  source gray image
* @param size masksize of the gauss filter
*    - 1: 3x3 gauss mask
*    - 2: 5x5 gauss mask
* @param dst  Optional buffer to be used as target.<br>
*             Create a new Image if \c dst == NULL.<br>
*             If \c dst != NULL then size must be equal to \c src 's size!
* @throw ImageException will be thrown if \c dst != NULL and the size of \c src and \c dst is not equal
*                       or an invalid size \c size is specified.
* @return Pointer to Image
*/
Image* filterGauss ( const Image& src, const uint& size, Image* dst = NULL );

/**
* \}
* @name Gradient Functions
* \{
*/

/**
* Compute horizontal part of the gradient of a Image \c src via Sobel into Image \c dst.
* The resulting image \c dst is of the same size as \c src.
* @param src  source gray image
* @param dst  optional buffer to be used as target.<br>
*             Create a new GrayImage16s if \c dst == NULL.<br>
*             If \c dst != NULL then size must be equal to \c src 's size!
* @return Pointer to GrayImage16s
* @throw ImageException will be thrown if \c dst != NULL and the size of \c src and \c dst is not equal.
*/
GrayImage16s* sobelX ( const Image& src, GrayImage16s* dst = NULL );

ImageT<float>* sobelX ( const ImageT<float>& src, ImageT<float>* dst = NULL );

template<class P>
void sobelX ( const NICE::ImageT<P> &src, NICE::ImageT<P> &dst);

/**
* Compute vertical part of the gradient of a Image \c src via Sobel into Image \c dst.
* The resulting image \c dst is of the same size as \c src.
* @param src  source gray image
* @param dst  optional buffer to be used as target.<br>
*             Create a new GrayImage16s if \c dst == NULL.<br>
*             If \c dst != NULL then size must be equal to \c src 's size!
* @return Pointer to GrayImage16s
* @throw ImageException will be thrown if \c dst != NULL and the size of \c src and \c dst is not equal.
*/
GrayImage16s* sobelY ( const Image& src, GrayImage16s* dst = NULL );

ImageT<float>* sobelY ( const ImageT<float>& src, ImageT<float>* dst = NULL );

template<class P>
void sobelY ( const NICE::ImageT<P> &src, NICE::ImageT<P> &dst);

/**
 * @brief combined sobel filter g = sqrt(g_x^2+g_y^2)
 *
 * @param src source gray image
 * @param dst destination
 * @return void
 **/
template<class P>
void sobel ( const NICE::ImageT<P> &src, NICE::ImageT<P> &dst);

/**
* Compute a gradient strength LUT of size 256x256.<br>
* Result is scaled to the graylevel domain [0,255].
* @return Pointer to Image
*/
Image* createGradientStrengthLUT();

/**
* Compute gradientstrength Image for a given vertical gradient Image \c sobelX and
* and a given horizontal gradient Image \c sobelY.
* The resulting image \c dst is of the same size as \c sobelX and \c sobelY.
* @param sobelX vertical gradient of a Image
* @param sobelY horizontal gradient of a Image
* @param dst    Optional buffer to be used as target.<br>
*               Create a new Image if \c dst == NULL.<br>
*               If \c dst != NULL then size must be equal to \c src 's size!
* @param strLUT Optional lookup table, if \c strLUT != NULL lookup table is used
*               instead of calculating the gradientstrength values
* @return Pointer to Image
* @throw  ImageException will be thrown if \c dst != NULL and the size of \c dst and \c sobelX / \c sobelY
*                        is not equal or if \c strLUT != NULL and the size of \c strLUT doesnt match 256x256.
*/
Image* gradientStrength ( const GrayImage16s& sobelX,
                          const GrayImage16s& sobelY,
                          Image* dst = NULL,
                          const Image* strLUT = NULL );

/**
* Compute a gradientdirection look-up table of size 256x256.<br>
* Possible discrete results are: 0, 45, 90, 135.
* @return Pointer to Image
*/
Image* createGradientDirectionLUT();

/**
* Computes the discrete gradient directions for a given vertical gradient Image \c sobelX and
* and a given horizontal gradient Image \c sobelY .<br>
* Possible discrete directions are 0,45,90 and 135.
* @param sobelX vertical gradient of a gray image
* @param sobelY horizontal gradient of a gray image
* @param dst    Optional buffer to be used as target.<br>
*               Create a new Image if \c dst == NULL.<br>
*               If \c dst != NULL then size must be equal to \c sobelX 's and \c sobelY 's size!
*               If dst != NULL then size must be equal to sobelX's and sobelY's size!
* @param dirLUT Optional lookup table, if \c strLUT != NULL lookup table is used
*               instead of calculating the gradient direction values
* @return Pointer to Image
* @throw  ImageException will be thrown if \c dst != NULL and the size of \c dst and \c sobelX / \c sobelY
*                        is not equal or if \c dirLUT != NULL and the size doesn't match 256x256.
*/
Image* gradientDirection ( const GrayImage16s& sobelX,
                           const GrayImage16s& sobelY,
                           Image* dst = NULL,
                           const Image* dirLUT = NULL );

/**
* Filters Image \c src into \c dst using a canny filter
* @param src   source gray image
* @param lower lower threshold for edge tracing
* @param upper upper treshold for edge tracing
* @param dst   Optional buffer to be used as target.<br>
*              Create a new Image if \c dst == NULL.<br>
*              If \c dst != NULL then size must be equal to \c src 's size!
* @param gradX Optional vertical gradient image.<br>
*              If \c gradX != NULL, \c gradX is used instead of calculating horizontal gradient values.
* @param gradY Optional horizontal gradient image.<br>
*              If \c gradY != NULL, \c gradY is used instead of calculating vertical gradient values.
* @return Pointer to Image
* @throw  ImageException will be thrown \c dst != NULL and the size of \c dst and \c src is not equal.
*/
Image* canny ( const Image& src, const uint& lower, const uint& upper,
               Image* dst = NULL, const GrayImage16s* gradX = NULL, const GrayImage16s* gradY = NULL );

/**
* \}
* @name Image Restoration Functions
* \{
*/

/**
 * Filters Image \c src by rows into the Image \c dst using a wiener filter.
 * @param src source gray image
 * @param anchorx horizontal offset to the kernelposition if negativ use center position
 * @param anchory vertical offset to the kernelposition if negativ use center position
 * @param maskx horizontal size of the median mask
 * @param masky vertical size of the median mask
 * @param noiserate noise ratio [0,1]
 * @param dst       Optional buffer to be used as target.<br>
 *                  Create a new Image if \c dst == NULL.<br>
 *                  If \c dst != NULL then size must be equal to \c src 's size!
 * @return Pointer to Image
 */
template<class P>
ImageT<P>* wiener ( const ImageT<P>& src, int anchorx = -1, int anchory = -1,
                    uint maskx = 3, uint masky = 3, float noiserate = 0.5, ImageT<P>* dst = NULL );

/**
 * Filters ColorImage \c src by rows into the ColorImage \c dst using wienerfilter.
 * @param src source gray image
 * @param anchorx horizontal offset to the kernelposition if negativ use center position
 * @param anchory vertical offset to the kernelposition if negativ use center position
 * @param maskx horizontal size of the median mask
 * @param masky vertical size of the median mask
 * @param noiserate noise ratio [0,1] of  all channels
 * @param dst       Optional buffer to be used as target.<br>
 *                  Create a new Image if \c dst == NULL.<br>
 *                  If \c dst != NULL then size must be equal to \c src 's size!
 * @return Pointer to ColorImage
 */
template<class P>
ColorImageT<P>* wiener ( const ColorImageT<P>& src, int anchorx = -1, int anchory = -1,
                         uint maskx = 3, uint masky = 3, float noiserate = 0.5, ColorImageT<P>* dst = NULL );

/**
* Filters ColorImage \c src by rows into the ColorImage \c dst using wienerfilter.
* @param src source gray image
* @param anchorx horizontal offset to the kernelposition if negativ use center position
* @param anchory vertical offset to the kernelposition if negativ use center position
* @param maskx horizontal size of the median mask
* @param masky vertical size of the median mask
* @param noiserateR noise ratio [0,1] of R-channel
* @param noiserateG noise ratio [0,1] of G-channel
* @param noiserateB noise ratio [0,1] of B-channel
* @param dst        Optional buffer to be used as target.<br>
*                   Create a new Image if \c dst == NULL.<br>
*                   If \c dst != NULL then size must be equal to \c src 's size!
* @return Pointer to ColorImage
*/
template<class P>
ColorImageT<P>* wiener ( const ColorImageT<P>& src, int anchorx = -1, int anchory = -1,
                         uint maskx = 3, uint masky = 3, float noiserateR = 0.5, float noiserateG = 0.5,
                         float noiserateB = 0.5, ColorImageT<P>* dst = NULL );
} // namespace

#ifdef __GNUC__
#include <core/image/Filter.tcc>
#endif

#endif //LIMUN_FILTER_H

