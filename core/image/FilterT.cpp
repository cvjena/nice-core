#include <core/image/FilterT.h>

using namespace NICE;

template<>
void FilterT<float,float,float>::filterX ( const ImageT<float>& src, const VectorT<float>& kernel, ImageT<float> &result, const int& anchor )
{
  if ( result.width() != src.width() || result.height() != src.height() )
  {
    result = ImageT<float> ( src.width(), src.height() );
  }

  uint kernelanch       = ( anchor < 0 ) ? ( kernel.size() / 2 ) : anchor;

#ifdef NICE_USELIB_IPP
  IppiSize ippiSize = {(int)(src.width() - ( kernel.size() - 1 )), (int)(src.height()) };
  IppStatus ret     = ippiFilterRow_C1R ( src.getPixelPointerXY ( kernel.size() - 1 - kernelanch, 0 ),
                                          src.getStepsize(),
                                          result.getPixelPointerXY ( kernelanch, 0 ),
                                          result.getStepsize(),
                                          ippiSize, kernel.getDataPointer(), kernel.size(), kernelanch );

  if ( ret != ippStsNoErr )
    fthrow ( ImageException, ippGetStatusString ( ret ) );

#else // NICE_USELIB_IPP
  double sum = 0.0;
  int ka     = kernelanch + 1;

  uint xstart = kernelanch;
  uint xend   = src.width() - ( kernel.size() - 1 - kernelanch );

  int  i;

  const float* pSrc;
  float*       pDst;
  for ( int y = 0; y < src.height(); ++y ) 
  {
    pSrc = src.getPixelPointerXY ( kernelanch, y );
    pDst = result.getPixelPointerXY ( kernelanch, y );

    for ( uint x = xstart; x < xend; ++x, ++pSrc, ++pDst ) {
      sum = 0.0;

      i = kernel.size();
      do {
        sum += * ( pSrc - ka + i ) * kernel[kernel.size()-i];
        --i;
      } while ( i != 0 );

      *pDst = static_cast<float> ( sum );
    }
  }
#endif // NICE_USELIB_IPP
}

template<>
void FilterT<float,float,float>::filterY ( const ImageT<float>& src, const VectorT<float>& kernel, ImageT<float> &result, const int& anchor )
{
  if(result.width() != src.width() || result.height() != src.height())
  {
    result = ImageT<float>(src.width(), src.height());
  }
  uint kernelanch = ( anchor < 0 ) ? ( kernel.size() / 2 ) : anchor;

#ifdef NICE_USELIB_IPP
  IppiSize ippiSize = {(int)(src.width()), (int)(src.height() - ( kernel.size() - 1 )) };
  IppStatus ret     = ippiFilterColumn_C1R ( src.getPixelPointerXY ( 0, kernel.size() - 1 - kernelanch ),
                      src.getStepsize(),
                      result.getPixelPointerXY ( 0, kernelanch ),
                      result.getStepsize(),
                      ippiSize, kernel.getDataPointer(), kernel.size(), kernelanch );

  if ( ret != ippStsNoErr )
    fthrow ( ImageException, ippGetStatusString ( ret ) );

#else // NICE_USELIB_IPP*/
  double sum         = 0.0;
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
      
      result(x,y) = static_cast<float> ( sum );
    }
  }
#endif // NICE_USELIB_IPP
}


