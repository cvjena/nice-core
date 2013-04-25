/**
 * @class FilterT
 * A generic filter class
 * based on old LImUn implementation by Ferid Bajramovic
 * @author Erik Rodner and Björn Fröhlich
 * @example notyet
 */

#include <core/image/ippwrapper.h>
#include <core/image/ImageOperators.h>

#include <core/vector/VectorT.h>
#include <core/vector/MatrixT.h>

#include <core/basics/RoundToNearest.h>

#include <core/image/ImageT.h>
#include <core/image/ColorImageT.h>
#include <core/image/Buffer.h>

#ifndef NICE_FILTERT_H
#define NICE_FILTERT_H

namespace NICE {

//FIXME: there should be a second generic class for lossless processing (or should it be always double?!

/** class for filter operations on images of generic type */
template<class SrcType, class CalcType, class DstType >
class FilterT
{
  public:
    /**
    * Filters (=convolves) Image \c src by column into the
    * Image \c dst using filter (=convolution) kernel \c kernel.
    * @param src    source gray image
    * @param kernel filter kernel (coefficients are used in inverse order,
    *               i.e. as mathematical convolution kernel)
    * @param dst  destination image, if it has not the same size as input, it will be resized
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
    static void filterX ( const ImageT<SrcType>& src, const VectorT<CalcType>& kernel, ImageT<DstType> &result, const int& anchor = -1 );

    /**
    * Filters (=convolves) Image \c src by rows into the
    * Image \c dst using filter (=convolution) kernel \c kernel.
    * @param src    source gray image
    * @param kernel filter kernel (coefficients are used in inverse order,
    *               i.e. as mathematical convolution kernel)
    * @param dst  destination image, if it has not the same size as input, it will be resized
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
    static void filterY ( const ImageT<SrcType>& src, const VectorT<CalcType>& kernel, ImageT<DstType> &result, const int& anchor = -1 );

    /**
    * Compute horizontal part of the gradient of a Image \c src via Sobel into Image \c dst.
    * The resulting image \c dst is of the same size as \c src.
    * @param src  source gray image
    * @param dst  destination image, if it has not the same size as input, it will be resized
    * @return Pointer to GrayImage16s
    * @throw ImageException will be thrown if \c dst != NULL and the size of \c src and \c dst is not equal.
    */
    static void sobelX ( const NICE::ImageT<SrcType> &src, NICE::ImageT<DstType> &dst );

    /**
    * Compute vertical part of the gradient of a Image \c src via Sobel into Image \c dst.
    * The resulting image \c dst is of the same size as \c src.
    * @param src  source gray image
    * @param dst  destination image, if it has not the same size as input, it will be resized
    * @return Pointer to GrayImage16s
    * @throw ImageException will be thrown if \c dst != NULL and the size of \c src and \c dst is not equal.
    */
    static void sobelY ( const NICE::ImageT<SrcType> &src, NICE::ImageT<DstType> &dst );

    /**
    * @brief compute the norm of the image gradient g = sqrt(g_x^2+g_y^2)
    *
    * @param src source gray image
    * @param dst destination
    * @return void
    **/
    static void gradientStrength ( const NICE::ImageT<SrcType> &src, NICE::ImageT<DstType> &dst );
    
    
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
    ImageT<DstType> * filterMean ( const ImageT<SrcType>& src, const uint& size, ImageT<DstType>* dst = NULL );     
    
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
    ImageT<DstType> * filterMeanLargeFS ( const ImageT<SrcType>& src, const uint& size, ImageT<DstType>* dst = NULL );    
      
    /**
    * @brief Blurs Image \c src into the Image \c dst by approximating a gauss filter with a specific standard deviation through multiple mean filters
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
    NICE::ImageT<DstType> * filterGaussSigmaApproximate ( const NICE::ImageT<SrcType> &src, double sigma, NICE::ImageT<DstType> *dst = NULL,
        bool use_filtersize_independent_implementation = true );  
  
 
};

// float specializations using IPP
template<>
void FilterT<float,float,float>::filterX ( const ImageT<float>& src, const VectorT<float>& kernel, ImageT<float> &result, const int& anchor );

template<>
void FilterT<float,float,float>::filterY ( const ImageT<float>& src, const VectorT<float>& kernel, ImageT<float> &result, const int& anchor );

// typedef for standard images
typedef FilterT<unsigned char,double,unsigned char> Filter;
// typedef for double images
typedef FilterT<double,double,double> FilterDouble;

} //namespace

#ifdef __GNUC__
#include <core/image/FilterT.tcc>
#endif

#endif
