#include "core/image/Filter.h"
#include <math.h>
#include <limits>
#include <core/basics/numerictools.h>

#include <iostream>
using namespace std;

#ifdef NICE_BOOST_FOUND 
#include <boost/math/special_functions/round.hpp>
#endif

namespace NICE {

// // // // // general filter functions // // // // //

Image* filterX ( const Image& src, const IntVector& kernel, Image* dst, const int& anchor ) {
  Image* result = createResultBuffer ( src, dst );
  int kernelanch = ( anchor < 0 ) ? ( kernel.size() / 2 ) : anchor;

  int kernelsum = 0;
  int kerneloff = 0;
  for ( uint i = 0; i < kernel.size(); i++ ) {
    kernelsum += ( kernel[i] < 0 ) ? ( -kernel[i] ) : kernel[i];
    kerneloff += ( kernel[i] < 0 ) ? ( -kernel[i] ) : 0;
  }
  kerneloff = ( 256 * kerneloff ) / kernelsum;

#ifdef NICE_USELIB_IPP
  // there are negativ maskentries, so we need an floatfiltering because integerfiltering can't handle it
  if ( kerneloff > 0 ) {
    FloatVector fKernel ( kernel.size() );
    for ( size_t i = 0; i < kernel.size(); ++i )
      fKernel[i] = kernel[i] / static_cast<float> ( kernelsum );

    FloatImage* fresult = filterX ( *grayToFloat ( src ), fKernel );
    result = floatToGray ( *fresult + kerneloff, result );

    // clean up
    delete fresult;
  }
  // no negativ maskentries, we can do integer filtering
  else {
    IppStatus ret = ippiFilterRow_8u_C1R ( src.getPixelPointer(), src.getStepsize(), result->getPixelPointer(),
                                           result->getStepsize(), makeROIFullImage ( src ), kernel.getDataPointer(), kernel.size(), kernelanch, kernelsum );

    if ( ret != ippStsNoErr )
      fthrow ( ImageException, ippGetStatusString ( ret ) );
  }
#else // NICE_USELIB_IPP
  long long sum = 0;
  double dKernelSum = static_cast<double> ( kernelsum );
  int ka = kernelanch + 1;

  int xend = src.width() - ( kernel.size() - kernelanch - 1 );

  int i;

  const Ipp8u* pSrcStart = src.getPixelPointerXY ( kernelanch, 0 );
  Ipp8u* pDstStart = result->getPixelPointerXY ( kernelanch, 0 );

  const Image::Pixel* pSrc;
  Image::Pixel *pDst;
  for ( int y = 0; y < src.height(); ++y ) {
    pSrc = pSrcStart;
    pDst = pDstStart;

    for ( int x = kernelanch; x < xend; ++x, ++pSrc, ++pDst ) {
      sum = 0;

      i = kernel.size();
      do {
        sum += * ( pSrc - ka + i ) * kernel[kernel.size()-i];
        --i;
      } while ( i != 0 );
#ifdef NICE_BOOST_FOUND
      *pDst = static_cast<Ipp8u> ( boost::math::lround ( sum / dKernelSum ) + kerneloff );
#else
      *pDst = static_cast<Ipp8u> ( lround ( sum / dKernelSum ) + kerneloff );
#endif
    }

    pSrcStart += src.getStepsize();
    pDstStart += result->getStepsize();
  }
#endif // NICE_USELIB_IPP
  return result;
}

Image* filterY ( const Image& src, const VectorT<int>& kernel, Image* dst, const int& anchor ) {
  Image* result = createResultBuffer ( src, dst );
  int kernelanch = ( anchor < 0 ) ? ( kernel.size() / 2 ) : anchor;

  int kernelsum = 0;
  int kerneloff = 0;
  for ( uint i = 0; i < kernel.size(); i++ ) {
    kernelsum += ( kernel[i] < 0 ) ? ( -kernel[i] ) : kernel[i];
    kerneloff += ( kernel[i] < 0 ) ? ( -kernel[i] ) : 0;
  }
  kerneloff = ( 256 * kerneloff ) / kernelsum;

#ifdef NICE_USELIB_IPP
  // there are negativ maskentries, so we need an floatfiltering because integerfiltering can't handle it
  if ( kerneloff > 0 ) {
    FloatVector fKernel ( kernel.size() );
    for ( size_t i = 0; i < kernel.size(); ++i )
      fKernel[i] = kernel[i] / static_cast<float> ( kernelsum );

    FloatImage* fresult = filterY ( *grayToFloat ( src ), fKernel );
    result = floatToGray ( *fresult + kerneloff, result );

    // clean up
    delete fresult;
  }
  // no negativ entries, we can do integer filtering
  else {
    IppStatus ret = ippiFilterColumn_8u_C1R ( src.getPixelPointer(), src.getStepsize(), result->getPixelPointer(),
                    result->getStepsize(), makeROIFullImage ( src ), kernel.getDataPointer(), kernel.size(), kernelanch, kernelsum );

    if ( ret != ippStsNoErr )
      fthrow ( ImageException, ippGetStatusString ( ret ) );
  }
#else // NICE_USELIB_IPP
  long long sum = 0;
  double dKernelSum = static_cast<double> ( kernelsum );
  uint ks = kernel.size() - 1;
  int yend = src.height() - ( ks - kernelanch );

  int i;

  const Ipp8u* pSrcStart = src.getPixelPointerXY ( 0, kernelanch );
  Ipp8u* pDstStart = result->getPixelPointerXY ( 0, kernelanch );

  const Image::Pixel* pSrc;
  Image::Pixel *pDst;
  for ( int y = kernelanch; y < yend; ++y ) {
    pSrc = pSrcStart;
    pDst = pDstStart;

    for ( int x = 0; x < src.width(); ++x, ++pSrc, ++pDst ) {
      sum = 0;

      i = ks;
      do {
        sum += * ( pSrc - ( kernelanch - i ) * src.getStepsize() ) * kernel[ks-i];
        --i;
      } while ( i >= 0 );
#ifdef NICE_BOOST_FOUND
	  *pDst = static_cast<Ipp8u> ( boost::math::lround ( sum / dKernelSum ) + kerneloff );
#else
      *pDst = static_cast<Ipp8u> ( lround ( sum / dKernelSum ) + kerneloff );
#endif
    }

    pSrcStart += src.getStepsize();
    pDstStart += result->getStepsize();
  }
#endif // NICE_USELIB_IPP
  return ( result );
}

Image* filter ( const Image& src, const IntMatrix& mask, Image* dst, const int& anchorx, const int& anchory ) {
  Image *result = createResultBuffer ( src, dst );
  IppiPoint anchor = { ( anchorx < 0 ) ? ( mask.cols() / 2 ) : anchorx, ( anchory < 0 ) ? ( mask.rows() / 2 ) : anchory };

  int masksum = 0;
  int maskoff = 0;
  for ( uint j = 0; j < mask.rows(); ++j )
    for ( uint i = 0; i < mask.cols(); ++i ) {
      masksum += abs ( mask ( j, i ) );
      maskoff += ( mask ( j, i ) < 0 ) ? abs ( mask ( j, i ) ) : 0;
    }
  maskoff = ( 256 * maskoff ) / masksum;

#ifdef NICE_USELIB_IPP
  // there are negativ maskentries, so we need an floatfiltering because integerfiltering can't handle it
  if ( maskoff > 0 ) {
    FloatMatrix fMask ( mask.rows(), mask.cols() );
    for ( size_t j = 0; j < mask.rows(); ++j )
      for ( size_t i = 0; i < mask.cols(); ++i )
        fMask ( j, i ) = mask ( j, i ) / static_cast<float> ( masksum );

    FloatImage* fresult = filter ( *grayToFloat ( src ), fMask );
    result = floatToGray ( *fresult + maskoff, result );
  }
  // no negativ entries, we can do integer filtering
  else {
    IntMatrix imask ( mask.cols(), mask.rows() );
    for ( uint j = 0; j < mask.rows(); j++ )
      for ( uint i = 0; i < mask.cols(); ++i )
        imask ( i, j ) = mask ( j, i );

    IppiSize maskSize = { mask.cols(), mask.rows() };
    IppStatus ret = ippiFilter_8u_C1R ( src.getPixelPointer(), src.getStepsize(), result->getPixelPointer(),
                                        result->getStepsize(), makeROIFullImage ( src ), imask.getDataPointer(), maskSize, anchor, masksum );

    if ( ret != ippStsNoErr )
      fthrow ( ImageException, ippGetStatusString ( ret ) );
  }
#else // NICE_USELIB_IPP
  long long sum = 0;
  double dMaskSum = static_cast<double> ( masksum );

  uint mr = mask.rows() - 1;
  uint mc = mask.cols() - 1;

  const Ipp8u* pSrc;
  const Ipp8u* pMask;
  Ipp8u* pDst;

  int xend = static_cast<int> ( src.width() - ( mask.cols() - anchor.x - 1 ) );
  int jstart = -anchor.y;
  int jend = static_cast<int> ( mr - anchor.y );

  const Ipp8u* pSrcStart = src.getPixelPointerXY ( anchor.x, anchor.y );
  Ipp8u* pDstStart = result->getPixelPointerXY ( anchor.x, anchor.y );

  for ( int y = anchor.y; y < static_cast<int> ( src.height() - ( mask.rows() - anchor.y - 1 ) ); ++y ) {
    pSrc = pSrcStart;
    pDst = pDstStart;

    for ( int x = anchor.x; x < xend; ++x, ++pSrc, ++pDst ) {
      sum = 0;

      for ( int j = jstart; j <= jend; ++j ) {
        pMask = pSrc - anchor.x + j * src.getStepsize();
        for ( uint i = 0; i <= mc; ++i, ++pMask )
          sum += *pMask * mask ( mr - ( j + anchor.y ), mc - i );
      }
#ifdef NICE_BOOST_FOUND
      *pDst = static_cast<Image::Pixel> ( boost::math::lround ( sum / dMaskSum ) + maskoff );
#else
	  *pDst = static_cast<Image::Pixel> ( lround ( sum / dMaskSum ) + maskoff );
#endif
    }

    pSrcStart += src.getStepsize();
    pDstStart += result->getStepsize();
  }
#endif // NICE_USELIB_IPP
  return result;
}

// // // // // smoothing functions // // // // //

Image* meanX ( const Image& src, const uint& size, Image* dst ) {
  Image* result = createResultBuffer ( src, dst );

#ifdef NICE_USELIB_IPP
  IppiSize maskSize = { 2* size + 1, 1 };
  IppiPoint anchor = { size, 0 };

  IppStatus ret = ippiFilterBox_8u_C1R ( src.getPixelPointer(), src.getStepsize(), result->getPixelPointer(),
                                         result->getStepsize(), makeROIFullImage ( src ), maskSize, anchor );

  if ( ret != ippStsNoErr )
    fthrow ( ImageException, ippGetStatusString ( ret ) );

#else // NICE_USELIB_IPP
  int isize = size;
  int is = isize + 1;
  int ksize = 2 * isize + 1;
  long long sum = 0;

  int xstart = isize + 1;
  int xend = src.width() - isize;

  const Ipp8u* pSrc;
  Ipp8u* pDst;
  for ( int y = 0; y < src.height(); ++y ) {
    pSrc = src.getPixelPointerY ( y );
    sum = 0;
    for ( int i = 0; i < ksize; ++i, ++pSrc )
      sum += *pSrc;

    pSrc = src.getPixelPointerXY ( xstart, y );
    pDst = result->getPixelPointerXY ( isize, y );
    *pDst = sum / ksize;
    ++pDst;

    for ( int x = xstart; x < xend; ++x, ++pSrc, ++pDst ) {
      sum += * ( pSrc + size );
      sum -= * ( pSrc - is );
      *pDst = sum / ksize;
    }
  }
#endif // NICE_USELIB_IPP
  return ( result );
}

Image* meanY ( const Image& src, const uint& size, Image* dst ) {
  Image* result = createResultBuffer ( src, dst );

#ifdef NICE_USELIB_IPP
  IppiSize mask = { 1, 2* size + 1 };
  IppiPoint anchor = { 0, size };

  IppStatus ret = ippiFilterBox_8u_C1R ( src.getPixelPointer(), src.getStepsize(), result->getPixelPointer(),
                                         result->getStepsize(), makeROIFullImage ( src ), mask, anchor );

  if ( ret != ippStsNoErr )
    fthrow ( ImageException, ippGetStatusString ( ret ) );

#else // NICE_USELIB_IPP
  int isize = size;
  int is = isize + 1;
  int ksize = 2 * isize + 1;
  long long sum = 0;

  const Ipp8u* pSrc;
  Ipp8u* pDst;

  for ( int x = 0; x < src.width(); ++x ) {
    sum = 0;
    pSrc = src.getPixelPointerXY ( x, 0 );
    for ( int i = 0; i < ksize; ++i, pSrc += src.getStepsize() )
      sum += *pSrc;

    pDst = result->getPixelPointerXY ( x, size );
    *pDst = sum / ksize;
    pDst += src.getStepsize();

    for ( int y = isize + 1; y < src.height() - isize; ++y ) {
      sum -= src ( x, y - is );
      sum += src ( x, y + isize );

      *pDst = sum / ksize;
      pDst += result->getStepsize();
    }
  }
#endif // NICE_USELIB_IPP
  return ( result );
}

Image* filterMean ( const Image& src, const uint& size, Image* dst ) {
  Image* result = createResultBuffer ( src, dst );

#ifdef NICE_USELIB_IPP
  IppiSize maskSize = { 2* size + 1, 2* size + 1 };
  IppiPoint anchor = { size, size };
  IppStatus ret = ippiFilterBox_8u_C1R ( src.getPixelPointer(), src.getStepsize(), result->getPixelPointer(), result->getStepsize(), makeROIFullImage ( src ), maskSize, anchor );

  if ( ret != ippStsNoErr )
    fthrow ( ImageException, ippGetStatusString ( ret ) );

#else // NICE_USELIB_IPP
  filterMean<Ipp8u, long long int> ( src, size, result );
#endif // NICE_USELIB_IPP
  return result;
}
;

void filterMeanIP ( ColorImage& src, const uint& size ) {
#ifdef NICE_USELIB_IPP
  IppiSize maskSize = { 2* size + 1, 2* size + 1 };
  IppiPoint anchor = { size, size };
  IppiSize roiSize = { src.width() - 2* size , src.height() - 2* size };
  IppStatus ret = ippiFilterBox_8u_C3IR ( src.getPixelPointer() + src.getStepsize() * size + size, src.getStepsize(),
                                          roiSize, maskSize, anchor );

  if ( ret != ippStsNoErr )
    fthrow ( ImageException, ippGetStatusString ( ret ) );

#else // NICE_USELIB_IPP
  fthrow ( ImageException, "Not yet supportet without IPP." );
#endif // NICE_USELIB_IPP
}
;

Image* gaussX ( const Image& src, const uint& size, Image* dst ) {
  if ( size != 1 && size != 2 )
    fthrow ( ImageException, "Only gauss kernels with size 1x3 or 1x5 are supported." );

  Image* result = createResultBuffer ( src, dst );

#ifdef NICE_USELIB_IPP
  IppStatus ret;
  if ( size == 1 ) {
    IppiSize size = { src.width() - 2, src.height() };

    Ipp32s gaussKernel[] = { 1, 2, 1 };
    ret = ippiFilterRow_C1R ( src.getPixelPointer() + 1, src.getStepsize(), result->getPixelPointer() + 1,
                              result->getStepsize(), size, gaussKernel, 3, 1, 4 );
  } else {
    Ipp32s gaussKernel[] = { 1, 4, 6, 4, 1 };

    IppiSize size = { src.width() - 4, src.height() };

    ret = ippiFilterRow_C1R ( src.getPixelPointer() + 2, src.getStepsize(), result->getPixelPointer() + 2,
                              result->getStepsize(), size, gaussKernel, 5, 2, 16 );
  }

  if ( ret != ippStsNoErr )
    fthrow ( ImageException, ippGetStatusString ( ret ) );

#else // NICE_USELIB_IPP
  IntVector gk;

  if ( size == 1 ) {
    Ipp32s k[] = {1, 2, 1};
    gk = IntVector ( k, 3 );
  }
  else {
    Ipp32s k[] = {1, 4, 6, 4, 1};
    gk = IntVector ( k, 5 );
  }
  result = filterX ( src, gk, result );
#endif

  return result;
}

ImageT<float>* gaussX ( const ImageT<float>& src, const uint& size, ImageT<float>* dst ) {
  if ( size != 1 && size != 2 )
    fthrow ( ImageException, "Only gauss kernels with size 1x3 or 1x5 are supported." );

  ImageT<float>* result = createResultBuffer ( src, dst );

#ifdef NICE_USELIB_IPP
  IppStatus ret;
  if ( size == 1 ) {
    IppiSize size = { src.width() - 2, src.height() };

    Ipp32f gaussKernel[] = { 1.0, 2.0, 1.0 };
    ret = ippiFilterRow_32f_C1R ( src.getPixelPointer() + 1, src.getStepsize(), result->getPixelPointer() + 1,
                                  result->getStepsize(), size, gaussKernel, 3, 1 );
  } else {
    Ipp32f gaussKernel[] = { 1.0, 4.0, 6.0, 4.0, 1.0 };

    IppiSize size = { src.width() - 4, src.height() };

    ret = ippiFilterRow_32f_C1R ( src.getPixelPointer() + 2, src.getStepsize(), result->getPixelPointer() + 2,
                                  result->getStepsize(), size, gaussKernel, 5, 2 );
  }

  if ( ret != ippStsNoErr )
    fthrow ( ImageException, ippGetStatusString ( ret ) );

#else // NICE_USELIB_IPP
  //TODO implement this
  throw ( Exception ( "gaussX without IPP: not implemented" ) );
#endif
  return result;
}

Image* gaussY ( const Image& src, const uint& size, Image* dst ) {
  if ( size != 1 && size != 2 )
    fthrow ( ImageException, "Only gauss kernels with size 1x3 or 1x5 are supported." );

  Image* result = createResultBuffer ( src, dst );

#ifdef NICE_USELIB_IPP
  IppStatus ret;
  if ( size == 1 ) {
    Ipp32s gaussKernel[] = { 1, 2, 1 };

    IppiSize size = { src.width(), src.height() - 2 };

    ret = ippiFilterColumn_C1R ( src.getPixelPointer() + src.getStepsize(), src.getStepsize(), result->getPixelPointer()
                                 + result->getStepsize(), result->getStepsize(), size, gaussKernel, 3, 1, 4 );
  } else {
    Ipp32s gaussKernel[] = { 1, 4, 6, 4, 1 };

    IppiSize size = { src.width(), src.height() - 4 };

    ret = ippiFilterColumn_C1R ( src.getPixelPointer() + 2 * src.getStepsize(), src.getStepsize(),
                                 result->getPixelPointer() + 2 * result ->getStepsize(), result->getStepsize(), size, gaussKernel, 5, 2, 16 );
  }

  if ( ret != ippStsNoErr )
    fthrow ( ImageException, ippGetStatusString ( ret ) );

#else // NICE_USELIB_IPP
  IntVector gaussKernel;

  if ( size == 1 ) {
    Ipp32s k[] = {1, 2, 1};
    gaussKernel = IntVector ( k, 3 );
  }
  else {
    Ipp32s k[] = {1, 4, 6, 4, 1};
    gaussKernel = IntVector ( k, 5 );
  }

  result = filterY ( src, gaussKernel, result );
#endif

  return result;
}

ImageT<float>* gaussY ( const ImageT<float>& src, const uint& size, ImageT<float>* dst ) {
  if ( size != 1 && size != 2 )
    fthrow ( ImageException, "Only gauss kernels with size 1x3 or 1x5 are supported." );

  ImageT<float>* result = createResultBuffer ( src, dst );

#ifdef NICE_USELIB_IPP
  IppStatus ret;
  if ( size == 1 ) {
    Ipp32f gaussKernel[] = { 1.0, 2.0, 1.0 };

    IppiSize size = { src.width(), src.height() - 2 };

    //ret = ippiFilterColumn_C1R(src.getPixelPointer() + src.getStepsize(), src.getStepsize(), result->getPixelPointer()
    //  + result->getStepsize(), result->getStepsize(), size, gaussKernel, 3, 1);
    ret = ippiFilterColumn_32f_C1R ( src.getPixelPointerXY ( 0, 1 ), src.getStepsize(), result->getPixelPointerXY ( 0, 1 ), result->getStepsize(), size, gaussKernel, 3, 1 );
  } else {
    Ipp32f gaussKernel[] = { 1.0, 4.0, 6.0, 4.0, 1.0 };

    IppiSize size = { src.width(), src.height() - 4 };

    //ret = ippiFilterColumn_C1R(src.getPixelPointer() + 2* src .getStepsize(), src.getStepsize(),
    //  result->getPixelPointer() + 2* result ->getStepsize(), result->getStepsize(), size, gaussKernel, 5, 2);
    ret = ippiFilterColumn_32f_C1R ( src.getPixelPointerXY ( 0, 2 ) , src.getStepsize(),
                                     result->getPixelPointerXY ( 0, 2 ), result->getStepsize(), size, gaussKernel, 5, 2 );
  }

  if ( ret != ippStsNoErr )
    fthrow ( ImageException, ippGetStatusString ( ret ) );

#else // NICE_USELIB_IPP
  //TODO implement this
  throw ( Exception ( "gaussY without IPP: not implemented" ) );
#endif

  return result;
}

Image* filterGauss ( const Image& src, const uint& size, Image* dst ) {
  if ( size != 1 && size != 2 )
    fthrow ( ImageException, "Only gauss masks of size 3x3 and 5x5 are supportet." );

  Image* result = createResultBuffer ( src, dst );

//#ifdef NICE_USELIB_IPP
#if 0
  // This function is broken: http://origin-software.intel.com/en-us/forums/showthread.php?t=67082
  // and results in strange valgrind statements and random segfaults:
  //
  // Invalid read of size 8 by 0x1171E7CF: omp_get_thread_num (in /home/rodner/tmp/3rdparty64/ipp53/sharedlib/libguide.so)
  // ...
  // ==26073==    by 0x11999FFD: ???
  // ==26073==    by 0x136066FB: L_ownippiFilterLaplGaus5x5_8002__par_region0_2.0 (in /home/rodner/tmp/3rdparty64/ipp53/sharedlib/libippiu8.so.5.3)
  // ==26073==    by 0x11735AD2: __kmp_invoke_microtask (in /home/rodner/tmp/3rdparty64/ipp53/sharedlib/libguide.so)
  // ==26073==    by 0x11723A67: __kmpc_invoke_task_func (in /home/rodner/tmp/3rdparty64/ipp53/sharedlib/libguide.so)
  // ==26073==    by 0x117256EF: __kmp_fork_call (in /home/rodner/tmp/3rdparty64/ipp53/sharedlib/libguide.so)
  //
  //
  // It should be fixed in ipp 6.1 but I didn't test it.
  // The workaround presented in the above webpage does not work.
  // (erik)
  IppStatus ret = ippiFilterGauss_8u_C1R ( src.getPixelPointer(), src.getStepsize(), result->getPixelPointer(),
                  result->getStepsize(), makeROIFullImage ( src ), ( ( size == 1 ) ? ippMskSize3x3 : ippMskSize5x5 ) );

  if ( ret != ippStsNoErr )
    fthrow ( ImageException, ippGetStatusString ( ret ) );

#else // NICE_USELIB_IPP
  Image* temp = gaussX ( src, size );
  result = gaussY ( *temp, size, result );

  // clean up
  delete temp;
#endif // NICE_USELIB_IPP

  return result;
}

// // // // // gradient functions // // // // //

GrayImage16s* sobelX ( const Image& src, GrayImage16s* dst ) {
  GrayImage16s* result = createResultBuffer ( src, dst );

  /*               |-1 0 1|                    |1|
   / separize Sobel |-2 0 2| into a 1D gaussian |2| and a 1D difference operator |-1 0 1|
   /                |-1 0 1|                    |1|
   */
  Image* gaussImg = gaussY ( src, 1 );

#ifdef NICE_USELIB_IPP
  std::auto_ptr<GrayImage16s> temp ( new GrayImage16s ( src.width(), src.height() ) );

  IppStatus ret = ippiConvert_8u16s_C1R ( gaussImg->getPixelPointer(), gaussImg->getStepsize(), temp->getPixelPointer(),
                                          temp->getStepsize(), makeROIFullImage ( *gaussImg ) );

  if ( ret != ippStsNoErr )
    fthrow ( ImageException, ippGetStatusString ( ret ) );

  IppiSize ippiSize = { gaussImg->width() - 2, gaussImg->height() - 2 };
  Ipp32s diffKernel[] = { 1, 0, -1 };
  ret = ippiFilterRow_16s_C1R ( temp->getPixelPointerXY ( 1, 1 ), temp->getStepsize(), result->getPixelPointerXY ( 1, 1 ),
                                result->getStepsize(), ippiSize, diffKernel, 3, 1, 1 );

  if ( ret != ippStsNoErr )
    fthrow ( ImageException, ippGetStatusString ( ret ) );

#else // NICE_USELIB_IPP
  int ss = gaussImg->getStepsize();

  const Ipp8u* pSrc;
  Ipp16s* pDst;

  const Ipp8u* pSrcStart = gaussImg->getPixelPointerXY ( 1, 1 );
  Ipp16s* pDstStart = result->getPixelPointerXY ( 1, 1 );

  for ( int y = 1; y < src.height() - 1; ++y ) {
    pSrc = pSrcStart;
    pDst = pDstStart;

    for ( int x = 1; x < src.width() - 1; ++x, ++pSrc, ++pDst )
      *pDst = * ( pSrc + 1 ) - * ( pSrc - 1 );

    pSrcStart += ss;
    pDstStart += ss;
  }
#endif // NICE_USELIB_IPP
  // clean up
  delete gaussImg;

  return result;
}

ImageT<float>* sobelX ( const ImageT<float>& src, ImageT<float>* dst )
{
  ImageT<float>* result = createResultBuffer ( src, dst );

  /*               |-1 0 1|                    |1|
   / separize Sobel |-2 0 2| into a 1D gaussian |2| and a 1D difference operator |-1 0 1|
   /                |-1 0 1|                    |1|
   */
  ImageT<float>* gaussImg = gaussY ( src, 1 );

#ifdef NICE_USELIB_IPP
  IppiSize ippiSize = { gaussImg->width() - 2, gaussImg->height() - 2 };
  Ipp32f diffKernel[] = { 1.0, 0.0, -1.0 };
  IppStatus ret = ippiFilterRow_32f_C1R ( gaussImg->getPixelPointerXY ( 1, 1 ), gaussImg->getStepsize(),
                                          result->getPixelPointerXY ( 1, 1 ), result->getStepsize(), ippiSize, diffKernel, 3, 1 );

  if ( ret != ippStsNoErr )
    fthrow ( ImageException, ippGetStatusString ( ret ) );

#else // NICE_USELIB_IPP
  //TODO implement this
  throw ( Exception ( "sobelX not implemented without ipp" ) );
#endif // NICE_USELIB_IPP
  // clean up
  delete gaussImg;

  return result;
}

GrayImage16s* sobelY ( const Image& src, GrayImage16s* dst ) {
  GrayImage16s* result = createResultBuffer ( src, dst );

  /*               |-1 -2 -1|                                                         |-1|
   / separize Sobel | 0  0  0| into a 1D gaussian |1 2 1| and a 1D difference operator | 0|
   /                | 1  2  1|                                                         | 1|
   */

  Image* gaussImg = gaussX ( src, 1 );

#ifdef NICE_USELIB_IPP
  std::auto_ptr<GrayImage16s> temp ( new GrayImage16s ( src.width(), src.height() ) );
  IppStatus ret = ippiConvert_8u16s_C1R ( gaussImg->getPixelPointer(), gaussImg->getStepsize(), temp->getPixelPointer(),
                                          temp->getStepsize(), makeROIFullImage ( *gaussImg ) );

  if ( ret != ippStsNoErr )
    fthrow ( ImageException, ippGetStatusString ( ret ) );

  IppiSize ippiSize = { gaussImg->width() - 2, gaussImg->height() - 2 };

  Ipp32s diffKernel[] = { 1, 0, -1 };
  ret = ippiFilterColumn_C1R ( temp->getPixelPointerXY ( 1, 1 ), temp->getStepsize(), result->getPixelPointerXY ( 1, 1 ),
                               result->getStepsize(), ippiSize, diffKernel, 3, 1, 1 );

  if ( ret != ippStsNoErr )
    fthrow ( ImageException, ippGetStatusString ( ret ) );

#else // NICE_USELIB_IPP
  int ss = gaussImg->getStepsize();

  const Ipp8u* pSrc;
  Ipp16s* pDst;

  const Ipp8u* pSrcStart = gaussImg->getPixelPointerXY ( 1, 1 );
  Ipp16s* pDstStart = result->getPixelPointerXY ( 1, 1 );

  for ( int y = 1; y < src.height() - 1; ++y ) {
    pSrc = pSrcStart;
    pDst = pDstStart;

    for ( int x = 1; x < src.width() - 1; ++x, ++pSrc, ++pDst )
      *pDst = * ( pSrc + ss ) - * ( pSrc - ss );

    pSrcStart += ss;
    pDstStart += ss;
  }
#endif // NICE_USELIB_IPP
  // clean up
  delete gaussImg;

  return result;
}

ImageT<float>* sobelY ( const ImageT<float>& src, ImageT<float>* dst ) {
  ImageT<float>* result = createResultBuffer ( src, dst );

  /*               |-1 -2 -1|                                                         |-1|
   / separize Sobel | 0  0  0| into a 1D gaussian |1 2 1| and a 1D difference operator | 0|
   /                | 1  2  1|                                                         | 1|
   */

  ImageT<float>* gaussImg = gaussX ( src, 1 );

#ifdef NICE_USELIB_IPP
  IppiSize ippiSize = { gaussImg->width() - 2, gaussImg->height() - 2 };

  Ipp32f diffKernel[] = { 1.0, 0.0, -1.0 };
  IppStatus ret = ippiFilterColumn_32f_C1R ( gaussImg->getPixelPointerXY ( 1, 1 ), gaussImg->getStepsize(),
                  result->getPixelPointerXY ( 1, 1 ), result->getStepsize(), ippiSize, diffKernel, 3, 1 );

  if ( ret != ippStsNoErr )
    fthrow ( ImageException, ippGetStatusString ( ret ) );

#else // NICE_USELIB_IPP
  //TODO implement this
  throw ( Exception ( "sobelY not implemented without ipp" ) );
#endif // NICE_USELIB_IPP
  // clean up
  delete gaussImg;

  return result;
}

Image* createGradientStrengthLUT() {
  Image* result = new Image ( 256, 256 );
  double maxval = std::sqrt ( 255.0 * 255.0 + 255.0 * 255.0 );

  Ipp8u* p;
  for ( int y = 0; y < result->height(); ++y ) {
    p = result->getPixelPointerY ( y );
    for ( int x = 0; x < result->width(); ++x, ++p )
      *p = static_cast<Ipp8u> ( ( std::sqrt ( static_cast<double> ( x * x + y * y ) ) / maxval ) * 255 );
  }

  return result;
}

Image* gradientStrength ( const GrayImage16s& sobelX, const GrayImage16s& sobelY, Image* dst, const Image* strLUT ) {
  if ( sobelX.width() != sobelY.width() || sobelX.height() != sobelY.height() )
    fthrow ( ImageException, "Input images sobelX and sobelY must have same size." );

  if ( strLUT != NULL )
    if ( strLUT->width() != 256 || strLUT->height() != 256 )
      fthrow ( ImageException, "Invalid LUT: size does not match 256x256." );

  Image* result = createResultBuffer ( sobelX, dst );

  if ( strLUT != NULL && false ) { // FIXME inefficient temporary bug fix !!!
    for ( int y = 0; y < sobelX.height(); ++y ) {

      const Ipp16s* pX = sobelX.getPixelPointerY ( y );
      const Ipp16s* pY = sobelY.getPixelPointerY ( y );

      Ipp8u* pD = result->getPixelPointerY ( y );

      for ( int x = 0; x < sobelX.width(); ++x, ++pD, ++pX, ++pY )
        *pD = strLUT->getPixelQuick ( abs ( *pX ), abs ( *pY ) );
    }
  } else {
    double maxval = std::sqrt ( double ( 255 * 255 + 255 * 255 ) );

    for ( int y = 0; y < sobelX.height(); ++y ) {

      const Ipp16s* pX = sobelX.getPixelPointerY ( y );
      const Ipp16s* pY = sobelY.getPixelPointerY ( y );

      Ipp8u* pD = result->getPixelPointerY ( y );

      for ( int x = 0; x < sobelX.width(); ++x, ++pD, ++pX, ++pY )
        *pD = static_cast<Ipp8u> ( ( std::sqrt ( double ( *pX**pX + *pY**pY ) ) / maxval ) * 255 );
    }
  }

  return result;
};

Image* createGradientDirectionLUT()
{
  Image* LUT = new Image ( 256, 256 );

  float temp;
  Ipp8u *p;
  for ( int y = 0; y < 256; ++y ) {
    p = LUT->getPixelPointerY ( y );
    for ( int x = 0; x < 256; ++x, ++p ) {

      if ( x >= -1 && x <= 1 ) {
        if ( y >= -1 && y <= 1 )
          *p = 0;
        else
          *p = 90;
      }
      else {
        temp = y / x;

        if ( temp >= -0.4142135624 && temp < 0.4142135624 ) // [-22.5,22.5]
          *p = 0;
        else if ( temp >= + 0.4142135624 && temp < 2.414213562 ) // [22.5,67.5]
          *p = 45;
        else if ( temp >= 2.414213562 || temp < -2.414213562 ) // [67.5,\infty),[-67.5,-\infty)
          *p = 90;
        else if ( temp >= -2.414213562 && temp < -0.4142135624 ) // [-67.5,-22.5)
          *p = 135;
      }
    }
  }

  return LUT;
}

Image* gradientDirection ( const GrayImage16s& sobelX, const GrayImage16s& sobelY,
                           Image* dst, const Image* dirLUT )
{
  if ( sobelX.width() != sobelY.width() || sobelX.height() != sobelY.height() )
    fthrow ( ImageException, "Input images sobelX and sobelY must have same size." );

  Image* result = createResultBuffer ( sobelX, dst );

  double temp;
  GrayImage16s::Pixel dx, dy;
  Image::Pixel *p;

  if ( dirLUT != NULL && false ) { // FIXME inefficient temporary bug fix !!!
    for ( int y = 1; y < sobelX.height() - 1; ++y ) {
      p = result->getPixelPointerXY ( 1, y );
      for ( int x = 1; x < sobelX.width() - 1; ++x, ++p ) {
        dx = sobelX.getPixelQuick ( x, y );
        dy = sobelY.getPixelQuick ( x, y );
        *p = dirLUT->getPixelQuick ( dx, dy );
      }
    }
  }
  else {
    for ( int y = 1; y < sobelX.height() - 1; ++y ) {
      p = result->getPixelPointerXY ( 1, y );
      for ( int x = 1; x < sobelX.width() - 1; ++x, ++p ) {
        dx = sobelX.getPixelQuick ( x, y );
        dy = sobelY.getPixelQuick ( x, y );

        if ( dx >= -1 && dx <= 1 )
          if ( dy >= -1 && dy <= 1 )
            *p = 0;
          else
            *p = 90;
        else {
          temp = dy / dx;

          if ( temp >= -0.4142135624 && temp < 0.4142135624 ) // [-22.5,22.5]
            *p = 0;
          else if ( temp >= + 0.4142135624 && temp < 2.414213562 ) // [22.5,67.5]
            *p = 45;
          else if ( temp >= 2.414213562 || temp < -2.414213562 ) // [67.5,\infty),[-67.5,-\infty)
            *p = 90;
          else if ( temp >= -2.414213562 && temp < -0.4142135624 ) // [-67.5,-22.5)
            *p = 135;
        }
      }
    }
  }

  return result;
};

Image* canny ( const Image& src,
               const uint& lower_thresh, const uint& upper_thresh,
               Image* dst,
               const GrayImage16s* gradX, const GrayImage16s* gradY )
{
  if ( gradX != NULL )
    if ( gradX->width() != src.width() || gradX->height() != src.height() )
      fthrow ( ImageException, "Source and optional gradient images must have the same size." );
  if ( gradY != NULL )
    if ( gradY->width() != src.width() || gradY->height() != src.height() )
      fthrow ( ImageException, "Source and optional gradient images must have the same size." );

  GrayImage16s* gradientX = ( gradX == NULL ) ? sobelX ( src ) : const_cast<GrayImage16s*> ( gradX );
  GrayImage16s* gradientY = ( gradY == NULL ) ? sobelY ( src ) : const_cast<GrayImage16s*> ( gradY );

  Image* result = createResultBuffer ( src, dst );

#ifdef NICE_USELIB_IPP
  int BufSize;
  ippiCannyGetSize ( makeROIFullImage ( src ), &BufSize );
  Ipp8u* Buffer = new Ipp8u[BufSize];

  IppStatus ret = ippiCanny_16s8u_C1R ( gradientX->getPixelPointer(), gradientX->getStepsize(),
                                        gradientY->getPixelPointer(), gradientY->getStepsize(),
                                        result->getPixelPointer(), result->getStepsize(),
                                        makeROIFullImage ( src ), lower_thresh, upper_thresh, Buffer );

  if ( ret != ippStsNoErr )
    fthrow ( ImageException, ippGetStatusString ( ret ) );

  // clean up
  delete Buffer;

#else // NICE_USELIB_IPP
  result->set ( 0 );

  Image* strLUT = createGradientStrengthLUT();
  Image* imgStr = new Image ( src.width(), src.height() );
  imgStr = gradientStrength ( *gradientX, *gradientY, imgStr, strLUT );
  Image* imgDir = gradientDirection ( *gradientX, *gradientY );
  Image* nonMaxImg = new Image ( src.width(), src.height() );

  // Non-Maximum Suppression
  {
    short int dx, dy;
    const Image::Pixel *pStr, *pDir;
    Image::Pixel *pNonMax;
    for ( int y = 1; y < src.height() - 1; ++y ) {
      pStr = imgStr->getPixelPointerXY ( 1, y );
      pDir = imgDir->getPixelPointerXY ( 1, y );
      pNonMax = nonMaxImg->getPixelPointerXY ( 1, y );

      for ( int x = 1; x < src.width() - 1; ++x, ++pStr, ++pDir, ++pNonMax ) {
        dx = ( *pDir == 90 ) ? 0 : ( *pDir == 45 ) ? 1 : -1;
        dy = ( *pDir == 0 ) ? 0 : 1;

        *pNonMax = ( imgStr->getPixelQuick ( x + dx, y + dy ) > *pStr ||
                     imgStr->getPixelQuick ( x - dx, y - dy ) > *pStr ) ? 0 : *pStr;
      }
    }
  }

  // Hysterese-Threshold
  short int dx, dy, tx, ty;

  const Ipp8u *pDir, *pThin;
  Ipp8u* pdst;
  for ( int y = 1; y < nonMaxImg->height() - 1; ++y ) {
    pThin = nonMaxImg->getPixelPointerXY ( 1, y );
    pDir = imgDir->getPixelPointerXY ( 1, y );
    pdst = result->getPixelPointerXY ( 1, y );

    for ( int x = 1; x < nonMaxImg->width() - 1; ++x, ++pThin, ++pDir, ++pdst ) {
      if ( *pThin >= upper_thresh && *pdst == 0 ) {
        *pdst = *pThin;
        dx = ( abs ( *pDir ) == 90 ) ? 0 : 1;
        dy = ( *pDir == 135 ) ? -1 : ( ( *pDir == 0 || *pDir == 180 ) ? 0 : 1 );
        for ( int i = ( -1 ); i <= 1; i += 2 ) {
          tx = x + dx * i;
          ty = y + dy * i;

          while ( result->isWithinImage ( tx, ty ) && nonMaxImg->getPixelQuick ( tx, ty ) >= lower_thresh ) {
            result->setPixelQuick ( tx, ty, nonMaxImg->getPixelQuick ( tx, ty ) );
            tx += dx * i;
            ty += dy * i;
          }
        }
      }
    }
  }

  // clean up
  delete imgStr;
  delete imgDir;
  delete nonMaxImg;
  delete strLUT;
#endif // NICE_USELIB_IPP
  // clean up
  if ( gradX == NULL ) delete gradientX;
  if ( gradY == NULL ) delete gradientY;

  return result;
};

template<class P>
ImageT<float>* filter ( const ImageT<float>& src, const FloatMatrix& mask, ImageT<float>* dst,
                    const int& anchorx, const int& anchory )
{
  ImageT<float>* result = createResultBuffer ( src, dst );

  IppiPoint anchor;
  anchor.x = ( anchorx < 0 ) ? ( mask.cols() / 2 ) : anchorx;
  anchor.y = ( anchory < 0 ) ? ( mask.rows() / 2 ) : anchory;

#ifdef NICE_USELIB_IPP
  IppiSize ippiSize     = {src.width() - 2* ( mask.cols() - anchor.x - 1 ), src.height() - 2* ( mask.rows() - anchor.y - 1 ) };
  IppiSize ippiMaskSize = {mask.cols(), mask.rows() };

  FloatMatrix imask ( mask.cols(), mask.rows() );
  for ( uint j = 0; j < mask.rows(); j++ )
    for ( uint i = 0; i < mask.cols(); ++i )
      imask ( i, j ) = mask ( j, i );

  IppStatus ret = ippiFilter_C1R ( src.getPixelPointerXY ( anchor.x, anchor.y ),
                                   src.getStepsize(),
                                   result->getPixelPointerXY ( anchor.x, anchor.y ),
                                   result->getStepsize(),
                                   ippiSize, imask.getDataPointer(), ippiMaskSize, anchor );

  if ( ret != ippStsNoErr )
    fthrow ( ImageException, ippGetStatusString ( ret ) );

#else // NICE_USELIB_IPP
  double sum = 0.0;
  uint mr    = mask.rows() - 1;
  uint mc    = mask.cols() - 1;
  int ss     = src.getStepsize() / sizeof ( P );

  int xend   = src.width() - mask.cols() + 1;

  int jstart = -anchor.y;
  int jend   = static_cast<int> ( mr - anchor.y );

  const P *pSrc, *pMask;
  P* pDst;

  const P* pSrcStart = src.getPixelPointerXY ( anchor.x, anchor.y );
  P* pDstStart = result->getPixelPointerXY ( anchor.x, anchor.y );

  for ( uint y = anchor.y; y < src.height() - ( mr - anchor.y ); ++y ) {
    pSrc = pSrcStart;
    pDst = pDstStart;

    for ( int x = 0; x < xend; ++x, ++pSrc, ++pDst ) {
      sum = 0.0;

      for ( int j = jstart; j <= jend; ++j ) {
        pMask = pSrc - anchor.x + j * ss;
        for ( uint i = 0; i <= mc; ++i, ++pMask )
          sum += *pMask * mask ( mc - j - anchor.y, mr - i );
      }

      *pDst = static_cast<P> ( sum );
    }

    pSrcStart += ss;
    pDstStart += ss;
  }
#endif // NICE_USELIB_IPP

  return result;
}

} // namespace


