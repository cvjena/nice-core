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

//#ifdef __GNUC__
#include <core/image/FilterT.tcc>
//#endif

#endif
