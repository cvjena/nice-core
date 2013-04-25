#include <iostream>
#include "ImageT.h"
#include <core/image/FilterT.h>

namespace NICE {
 
template<class SrcType, class CalcType, class DstType>
void FilterT<SrcType, CalcType, DstType>::filterX ( const ImageT<SrcType>& src, const VectorT<CalcType>& kernel, ImageT<DstType> &result, const int& anchor )
{
  if(result.width() != src.width() || result.height() != src.height())
  {
    result.resize(src.width(), src.height());
  }

  uint kernelanch       = ( anchor < 0 ) ? ( kernel.size() / 2 ) : anchor;

  CalcType sum = 0.0;
  int ka     = kernelanch + 1;

  uint xstart = kernelanch;
  uint xend   = src.width() - ( kernel.size() - 1 - kernelanch );

  int  i;

  const SrcType* pSrc;
  DstType*       pDst;
  for ( int y = 0; y < src.height(); ++y ) {

    pSrc = src.getPixelPointerXY ( kernelanch, y );
    pDst = result.getPixelPointerXY ( kernelanch, y );

    for ( uint x = xstart; x < xend; ++x, ++pSrc, ++pDst ) {
      sum = (CalcType)0;

      i   = kernel.size();
      do {
        sum += * ( pSrc - ka + i ) * kernel[kernel.size()-i];
        --i;
      } while ( i != 0 );

      *pDst = static_cast<DstType> ( sum );
    }
  }
}

template<class SrcType, class CalcType, class DstType>
void FilterT<SrcType, CalcType, DstType>::filterY ( const ImageT<SrcType>& src, const VectorT<CalcType>& kernel, ImageT<DstType>& result, const int& anchor )
{
  if(result.width() != src.width() || result.height() != src.height())
  {
    result.resize(src.width(), src.height());
  }
  uint kernelanch = ( anchor < 0 ) ? ( kernel.size() / 2 ) : anchor;

  CalcType sum         = 0.0;
  int ks             = kernel.size() - 1;
  int i;
  for ( uint y = kernelanch; y < src.height() - ( kernel.size() - 1 - kernelanch ); ++y ) 
  {
    for ( int x = 0; x < src.width(); ++x ) {
      sum = 0.0;

      i = ks;
      do {
        //TODO: optimizable similar to filterX, old version was buggy
        sum += src(x,y+kernelanch-ks+i) * kernel[ks-i];
        --i;
      } while ( i >= 0 );
      
      result(x,y) = static_cast<DstType> ( sum );
    }
  }
}

template<class SrcType, class CalcType, class DstType>
void FilterT<SrcType, CalcType, DstType>::sobelX ( const NICE::ImageT<SrcType> &src, NICE::ImageT<DstType> &dst)
{
  if(dst.width() != src.width() || dst.height() != src.height() )
  {
    dst.resize(src.width(), src.height());
  }

  /*                |-1 0 1|                    |1|
   * separize Sobel |-2 0 2| into a 1D gaussian |2| and a 1D difference operator |-1 0 1|
   *                |-1 0 1|                    |1|
   */
  
  VectorT<CalcType> kernel(3);
  kernel[0] = static_cast<CalcType> ( -1.0 );
  kernel[1] = static_cast<CalcType> ( 0.0 );
  kernel[2] = static_cast<CalcType> ( 1.0 );
  
  FilterT<SrcType, CalcType, DstType>::filterX(src, kernel, dst);

  return;
}

template<class SrcType, class CalcType, class DstType>
void FilterT<SrcType, CalcType, DstType>::sobelY ( const NICE::ImageT<SrcType> &src, NICE::ImageT<DstType> &dst)
{
  if(dst.width() != src.width() || dst.height() != src.height() )
  {
    dst.resize (src.width(), src.height());
  }

  /*                |-1 -2 -1|                                                         |-1|
   / separize Sobel | 0  0  0| into a 1D gaussian |1 2 1| and a 1D difference operator | 0|
   /                | 1  2  1|                                                         | 1|
   */
  
  VectorT<CalcType> kernel(3);
  kernel[0] = static_cast<CalcType> ( -1 );
  kernel[1] = static_cast<CalcType> ( 0 );
  kernel[2] = static_cast<CalcType> ( 1 );
  
  FilterT<SrcType, CalcType, DstType>::filterY(src, kernel, dst);

  return;
}

template<class SrcType, class CalcType, class DstType>
void FilterT<SrcType, CalcType, DstType>::gradientStrength ( const NICE::ImageT<SrcType> &src, NICE::ImageT<DstType> &dst)
{
  
  if(dst.width() != src.width() || dst.height() != src.height() )
  {
    dst.resize (src.width(), src.height());
  }

  ImageT<DstType> dstx;
  ImageT<DstType> dsty;
  FilterT<SrcType, CalcType, DstType>::sobelX(src,dstx);
  FilterT<SrcType, CalcType, DstType>::sobelY(src,dsty);
  
  int width = src.width();
  int height = src.height();
 
  for(int y = 0; y < height; y++)
  {
    for(int x = 0; x < width; x++)
    {
      dst(x,y) = sqrt(dstx(x,y)*dstx(x,y)+dsty(x,y)*dsty(x,y));
    }
  }
  
  return;
}

template<class SrcType, class CalcType, class DstType>
ImageT<DstType> * FilterT<SrcType, CalcType, DstType>::filterMean ( const NICE::ImageT<SrcType>& src, const uint& size, ImageT<DstType>* dst )
{
  ImageT<DstType>* result = createResultBuffer ( src, dst );

  int isize = size;
  int is = isize + 1;
  int msize = ( 2 * isize + 1 ) * ( 2 * isize + 1 );
  CalcType sum = 0;

  int xend = src.width() - isize;

  const SrcType* pSrc;
  DstType* pDst;
  for ( int y = isize; y < src.height() - isize; ++y ) {
    sum = 0;

    for ( int j = y - isize; j <= y + isize; ++j ) {
      pSrc = src.getPixelPointerY ( j );
      for ( uint i = 0; i <= 2*size; ++i, ++pSrc )
        sum += *pSrc;
    }

    pSrc = src.getPixelPointerXY ( is, y );
    pDst = result->getPixelPointerXY ( isize, y );
    *pDst = sum / msize;
    ++pDst;

    for ( int x = is; x < xend; ++x, ++pSrc, ++pDst ) {
      for ( int i = -isize; i <= isize; ++i ) {
        sum += * ( pSrc + size + i * src.getStepsize() );
        sum -= * ( pSrc - is + i * src.getStepsize() );
      }
      *pDst = sum / msize;
    }
  }

  return result;
}

template<class SrcType, class CalcType, class DstType>
ImageT<DstType> * FilterT<SrcType, CalcType, DstType>::filterMeanLargeFS ( const ImageT<SrcType>& src, const uint& size, ImageT<DstType>* dst )
{
  ImageT<DstType>* result = createResultBuffer ( src, dst );
  ImageT<CalcType> tmp ( src.width(), src.height() );

  unsigned int isize = size;
  unsigned int n = 2 * isize + 1;
  CalcType sum = 0;

  unsigned int xend = src.width();
  unsigned int yend = src.height();

  // legend of the following comments
  // current pixel in dst = x
  // end of filter mask and current pixel in src = e
  // the examples use a size=2 filter, is=3, n=5
  for ( int y = 0; y < src.height(); ++y ) {
    sum = 0;

    const SrcType* pSrc = src.getPixelPointerY ( y );
    DstType *pDst = tmp.getPixelPointerY ( y );

    // first position: [eoooooooooooooooooo]
    // last position:  [-eooooooooooooooooo]
    for ( unsigned int e = 0; e < size; ++e ) {
      sum += * ( pSrc );
      pSrc++;
    }
    // first position: [x-eoooooooooooooooo]
    // last position:  [s-x-eoooooooooooooo]
    for ( unsigned int e = size; e < n; ++e ) {
      sum += * ( pSrc );
      pSrc++;
      *pDst = sum / ( e + 1 );
      pDst++;
    }
    // first position: [os-x-eooooooooooooo]
    // last position:  [oooooooooooooos-x-e]
    for ( unsigned int e = n;e < xend; ++e ) {
      sum -= * ( pSrc - n );
      sum += * ( pSrc );
      pSrc++;
      *pDst = sum / n;
      pDst++;
    }
    // first position: [ooooooooooooooos-x-]
    // last position:  [oooooooooooooooos-x]
    for ( unsigned int x = xend - size; x < xend; ++x ) {
      sum -= * ( pSrc - ( xend - x + 1 ) );
      *pDst = sum / ( size + xend - x );
      pDst++;
    }
  }

  // now let us filter along the columns
  long long linestep = src.rowStepsize() / src.bytedepth();

  for ( unsigned int x = 0; x < xend; ++x ) {
    sum = 0;

    const CalcType* pSrc = tmp.getPixelPointerXY ( x, 0 );
    SrcType *pDst = result->getPixelPointerXY ( x, 0 );

    for ( unsigned int e = 0; e < size; ++e ) {
      sum += * ( pSrc );
      pSrc += linestep;
    }
    for ( unsigned int e = size; e < n; ++e ) {
      sum += * ( pSrc );
      pSrc += linestep;
      *pDst = sum / ( e + 1 );
      pDst += linestep;
    }
    for ( unsigned int e = n;e < yend; ++e ) {
      sum -= * ( pSrc - n * linestep );
      sum += * ( pSrc );
      pSrc += linestep;
      *pDst = sum / n;
      pDst += linestep;
    }
    for ( unsigned int y = yend - size; y < yend; ++y ) {
      sum -= * ( pSrc - ( yend - y + 1 ) * linestep );
      *pDst = sum / ( size + yend - y );
      pDst += linestep;
    }
  }

  return result;
}    

template<class SrcType, class CalcType, class DstType>
ImageT<DstType> * FilterT<SrcType, CalcType, DstType>::filterGaussSigmaApproximate ( const NICE::ImageT<SrcType> &src, double sigma, NICE::ImageT<DstType> *dst,
    bool use_filtersize_independent_implementation )
{
  // We use the idea of Wells 1986
  // Efficient Synthesis of Gaussian Filters by Cascaded Uniform Filters
  // http://ieeexplore.ieee.org/stamp/stamp.jsp?arnumber=04767776
  // However, the idea is mainly from the lecture script of Prof. Schukat-Talamazzini.
  //
  // 4x mean filter of size (2M+1) x (2M+1) is nearly the same as a
  // gauss filter with sigma = sqrt(4/3(M^2+M))
  // stddev of a mean filter of size 2M+1 is 1/3 M (M+1)
  // after applying it 4 times (convolution) the stddev is 4/3 M (M+1)
  // After some school math stuff (solving quadratic equations),
  // we can derive the formula used below.
  // copy-n-paste for gnuplot: plot [0:10] (sqrt(1+3*x*x)-1)/2
  ImageT<DstType>* result = createResultBuffer ( src, dst );
  NICE::ImageT<CalcType> tmp ( src.width(), src.height() );

  int M = ( int ) ( ( sqrt ( 1 + 3 * sigma * sigma ) - 1 ) / 2.0 + 0.5 );
  if ( M < 1 ) {
    fthrow ( Exception, "Unable to approximate an Gaussian filter of this small scale (sigma=" << sigma << ")" );
  }

  if ( use_filtersize_independent_implementation )
  {
    this->filterMeanLargeFS ( src, M, &tmp );
    this->filterMeanLargeFS ( tmp, M, result );
    this->filterMeanLargeFS ( *result, M, &tmp );
    this->filterMeanLargeFS ( tmp, M, result );
  } else {
    this->filterMean ( src, M, &tmp );
    this->filterMean ( tmp, M, result );
    this->filterMean ( *result, M, &tmp );
    this->filterMean ( tmp, M, result );
  }

  return result;
}

} //namespace
