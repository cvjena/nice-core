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

} //namespace
