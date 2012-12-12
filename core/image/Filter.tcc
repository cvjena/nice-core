#include <iostream>
#include "ImageT.h"

namespace NICE {

template<class P>
ImageT<P>* filterX ( const ImageT<P>& src, const FloatVector& kernel,
                     ImageT<P>* dst, const int& anchor )
{
  ImageT<P>* result = createResultBuffer ( src, dst );
  uint kernelanch       = ( anchor < 0 ) ? ( kernel.size() / 2 ) : anchor;

#ifdef NICE_USELIB_IPP
  IppiSize ippiSize = {src.width() - ( kernel.size() - 1 ), src.height() };
  IppStatus ret     = ippiFilterRow_C1R ( src.getPixelPointerXY ( kernel.size() - 1 - kernelanch, 0 ),
                                          src.getStepsize(),
                                          result->getPixelPointerXY ( kernelanch, 0 ),
                                          result->getStepsize(),
                                          ippiSize, kernel.getDataPointer(), kernel.size(), kernelanch );

  if ( ret != ippStsNoErr )
    fthrow ( ImageException, ippGetStatusString ( ret ) );

#else // NICE_USELIB_IPP
  double sum = 0.0;
  int ka     = kernelanch + 1;

  uint xstart = kernelanch;
  uint xend   = src.width() - ( kernel.size() - 1 - kernelanch );

  int  i;

  const P* pSrc;
  P*       pDst;
  for ( int y = 0; y < src.height(); ++y ) {

    pSrc = src.getPixelPointerXY ( kernelanch, y );
    pDst = result->getPixelPointerXY ( kernelanch, y );

    for ( uint x = xstart; x < xend; ++x, ++pSrc, ++pDst ) {
      sum = 0.0;

      i   = kernel.size();
      do {
        sum += * ( pSrc - ka + i ) * kernel[kernel.size()-i];
        --i;
      } while ( i != 0 );

      *pDst = static_cast<P> ( sum );
    }
  }
#endif // NICE_USELIB_IPP

  return result;
}

template<class P>
ImageT<P>* filterY ( const ImageT<P>& src, const FloatVector& kernel,
                     ImageT<P>* dst, const int& anchor )
{
  ImageT<P>* result = createResultBuffer ( src, dst );
  uint kernelanch       = ( anchor < 0 ) ? ( kernel.size() / 2 ) : anchor;

#ifdef NICE_USELIB_IPP
  IppiSize ippiSize = {src.width(), src.height() - ( kernel.size() - 1 ) };
  IppStatus ret     = ippiFilterColumn_C1R ( src.getPixelPointerXY ( 0, kernel.size() - 1 - kernelanch ),
                      src.getStepsize(),
                      result->getPixelPointerXY ( 0, kernelanch ),
                      result->getStepsize(),
                      ippiSize, kernel.getDataPointer(), kernel.size(), kernelanch );

  if ( ret != ippStsNoErr )
    fthrow ( ImageException, ippGetStatusString ( ret ) );

#else // NICE_USELIB_IPP*/
  double sum         = 0;
  int ks             = kernel.size() - 1;
  int ss             = src.getStepsize() / sizeof ( P );
  const P* pSrcStart = src.getPixelPointerXY ( 0, kernelanch );
  P*       pDstStart = result->getPixelPointerXY ( 0, kernelanch );

  int i;

  const P* pSrc;
  P*       pDst;
  for ( uint y = kernelanch; y < src.height() - ( kernel.size() - 1 - kernelanch ); ++y ) {
    pSrc = pSrcStart;
    pDst = pDstStart;

    for ( int x = 0; x < src.width(); ++x, ++pSrc, ++pDst ) {
      sum = 0;

      i = kernel.size() - 1;
      do {
        sum += * ( pSrc - ( kernelanch - i ) * ss ) * kernel[ks-i];
        --i;
      } while ( i >= 0 );

      *pDst = static_cast<P> ( sum );
    }

    pSrcStart += ss;
    pDstStart += ss;
  }
#endif // NICE_USELIB_IPP

  return result;
}

template<class P>
ImageT<P>* filter ( const ImageT<P>& src, const FloatMatrix& mask, ImageT<P>* dst,
                    const int& anchorx, const int& anchory )
{
  ImageT<P>* result = createResultBuffer ( src, dst );

  IppiPoint anchor;
  anchor.x = ( anchorx < 0 ) ? ( mask.cols() / 2 ) : anchorx;
  anchor.y = ( anchory < 0 ) ? ( mask.rows() / 2 ) : anchory;

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

  return result;
}

template<class P, class PCalc>
ImageT<P> *filterGaussSigma ( const NICE::ImageT<P> &src, double sigma, NICE::ImageT<P> *dst )
{
  ImageT<P>* result = createResultBuffer ( src, dst );

  //create odd filter size out of sigma
  int filtersize = ( int ) round ( fabs ( sigma ) * 5.0 );
  int masksize = filtersize / 2;
  filtersize = 2 * masksize + 1; //take next best odd filtersize

  if ( masksize > 0 )
  {
    result->set ( 0.0 );

    /* initialize 1D Gauss filter mask */
    PCalc filt[filtersize];

    double filt_dbl[masksize+1];
    for ( int x = 0; x <= masksize; x++ )
      filt_dbl[x] = exp ( - ( x * x ) / ( 2 * sigma * sigma ) );

    P sum = 0;
    for ( int i = 0; i < masksize; i++ )
    {
      filt[i] = ( filt_dbl[masksize-i] / filt_dbl[masksize] );
      sum += filt[i];
    }
    for ( int i = 0; i <= masksize; i++ )
    {
      filt[i+masksize] = ( filt_dbl[i] / filt_dbl[masksize] );
      sum += filt[i];
    }

    /* temporary image */
    NICE::ImageT<P> temp ( src.width(), src.height() );

    /* 1D separation y-direction */
    for ( int y = 0;y < src.height();y++ )
      for ( int x = 0;x < src.width();x++ )
      {
        PCalc filterweight = 0;
        PCalc filtersum = 0;
        for ( int ym = -masksize;ym <= masksize;ym++ )
        {
          int ypos = y + ym;
          int xpos = x;
          if ( ypos >= 0 && ypos < src.height() )
          {
            PCalc value = src.getPixelQuick ( xpos, ypos ) * filt[ym+masksize];
            filtersum += value;
            filterweight += filt[ym+masksize];
          }
        }
        if ( filterweight > 0 )
          temp.setPixelQuick ( x, y, ( P ) ( filtersum / filterweight ) );
      }

    /* 1D separation x-direction */
    for ( int y = 0;y < src.height();y++ )
      for ( int x = 0;x < src.width();x++ )
      {
        PCalc filterweight = 0;
        PCalc filtersum = 0;
        for ( int xm = -masksize;xm <= masksize;xm++ )
        {
          int ypos = y;
          int xpos = x + xm;
          if ( xpos >= 0 && xpos < src.width() )
          {
            PCalc value = temp.getPixelQuick ( xpos, ypos ) * filt[xm+masksize];//take from already filtered image
            filtersum += value;
            filterweight += filt[xm+masksize];
          }
        }
        if ( filterweight > 0 )
          result->setPixelQuick ( x, y, ( P ) ( filtersum / filterweight ) );
      }
  } else {
    *result = src;
  }

  return result;
}

template<class P>
void sobelX ( const NICE::ImageT<P> &src, NICE::ImageT<P> &dst)
{
  if(dst.width() != src.width() || dst.height() != src.height() )
  {
    dst = ImageT<P>(src.width(), src.height());
  }

  /*                |-1 0 1|                    |1|
   / separize Sobel |-2 0 2| into a 1D gaussian |2| and a 1D difference operator |-1 0 1|
   /                |-1 0 1|                    |1|
   */
  
  
  FloatVector kernel(3);
  kernel[0] = -1;
  kernel[1] = 0;
  kernel[2] = 1;
  
  filterX<P>(src, kernel, &dst);

  return;
}

template<class P>
void sobelY ( const NICE::ImageT<P> &src, NICE::ImageT<P> &dst)
{
  if(dst.width() != src.width() || dst.height() != src.height() )
  {
    dst = ImageT<P>(src.width(), src.height());
  }

  /*                |-1 -2 -1|                                                         |-1|
   / separize Sobel | 0  0  0| into a 1D gaussian |1 2 1| and a 1D difference operator | 0|
   /                | 1  2  1|                                                         | 1|
   */
  
  FloatVector kernel(3);
  kernel[0] = -1;
  kernel[1] = 0;
  kernel[2] = 1;
  
  filterY<P>(src, kernel, &dst);

  return;
}

template<class P>
void sobel ( const NICE::ImageT<P> &src, NICE::ImageT<P> &dst)
{
  ImageT<P> dst2;
  sobelX<P>(src,dst);
  sobelY<P>(src,dst2);
  
  int width = src.width();
  int height = src.height();
  
  for(int y = 0; y < height; y++)
  {
    for(int x = 0; x < width; x++)
    {
      dst(x,y) = sqrt(dst(x,y)*dst(x,y)+dst2(x,y)*dst2(x,y));
    }
  }
  
  return;
}

template<class P, class PCalc, class PTemp>
ImageT<P> *filterGaussSigmaApproximate ( const NICE::ImageT<P> &src, double sigma, NICE::ImageT<P> *dst,
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
  ImageT<P>* result = createResultBuffer ( src, dst );
  NICE::ImageT<P> tmp ( src.width(), src.height() );

  int M = ( int ) ( ( sqrt ( 1 + 3 * sigma * sigma ) - 1 ) / 2.0 + 0.5 );
  if ( M < 1 ) {
    fthrow ( Exception, "Unable to approximate an Gaussian filter of this small scale (sigma=" << sigma << ")" );
  }

  if ( use_filtersize_independent_implementation )
  {
    filterMeanLargeFS<P, PCalc, PTemp> ( src, M, &tmp );
    filterMeanLargeFS<P, PCalc, PTemp> ( tmp, M, result );
    filterMeanLargeFS<P, PCalc, PTemp> ( *result, M, &tmp );
    filterMeanLargeFS<P, PCalc, PTemp> ( tmp, M, result );
  } else {
    filterMean<P, PCalc> ( src, M, &tmp );
    filterMean<P, PCalc> ( tmp, M, result );
    filterMean<P, PCalc> ( *result, M, &tmp );
    filterMean<P, PCalc> ( tmp, M, result );
  }

  return result;
}

template<class P, class PCalc, class PTemp>
NICE::ImageT<P>* filterMeanLargeFS ( const NICE::ImageT<P>& src, const uint& size, ImageT<P>* dst )
{
  ImageT<P>* result = createResultBuffer ( src, dst );
  ImageT<PTemp> tmp ( src.width(), src.height() );

  unsigned int isize = size;
  unsigned int n = 2 * isize + 1;
  PCalc sum = 0;

  unsigned int xend = src.width();
  unsigned int yend = src.height();

  // legend of the following comments
  // current pixel in dst = x
  // end of filter mask and current pixel in src = e
  // the examples use a size=2 filter, is=3, n=5
  for ( int y = 0; y < src.height(); ++y ) {
    sum = 0;

    const P* pSrc = src.getPixelPointerY ( y );
    PTemp *pDst = tmp.getPixelPointerY ( y );

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

    const PTemp* pSrc = tmp.getPixelPointerXY ( x, 0 );
    P *pDst = result->getPixelPointerXY ( x, 0 );

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


template<class P, class PCalc>
NICE::ImageT<P>* filterMean ( const NICE::ImageT<P>& src, const uint& size, ImageT<P>* dst )
{
  ImageT<P>* result = createResultBuffer ( src, dst );

  int isize = size;
  int is = isize + 1;
  int msize = ( 2 * isize + 1 ) * ( 2 * isize + 1 );
  PCalc sum = 0;

  int xend = src.width() - isize;

  const P* pSrc;
  P* pDst;
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

template<class P>
ImageT<P>* wiener ( const ImageT<P>& src, int anchorx, int anchory,
                    uint maskx, uint masky, float noiserate, ImageT<P>* dst )
{
  if ( anchorx == -1 )
    anchorx = maskx / 2;
  if ( anchory == -1 )
    anchory = masky / 2;

  ImageT<P> *result = createResultBuffer ( src, dst );

  if ( src.width() != result->width() || src.height() != result->height() )
    fthrow ( ImageException, "src and dst must have the same size." );

#ifdef NICE_USELIB_IPP
  IppiPoint anchor = {anchorx, anchory};
  IppiSize ippiSize = { src.width() - maskx + 1, src.height() - masky + 1 };
  IppiSize mask = {maskx, masky};
  Ipp32f noise[1];
  noise[0] = noiserate;

  int pBufferSize;
  IppStatus ret = ippiFilterWienerGetBufferSize ( ippiSize, mask, 1, &pBufferSize );
  if ( ret != ippStsNoErr )
    fthrow ( ImageException, ippGetStatusString ( ret ) );
  Ipp8u pBuffer[pBufferSize];

  ret = ippiFilterWiener_C1R ( src.getPixelPointerXY ( maskx - 1 - anchorx, masky - 1 - anchory ),
                               src.getStepsize(),
                               result->getPixelPointerXY ( anchorx, anchory ),
                               result->getStepsize(),
                               ippiSize, mask, anchor, noise, pBuffer );

  if ( ret != ippStsNoErr )
    fthrow ( ImageException, ippGetStatusString ( ret ) );
#else // NICE_USELIB_IPP
  fthrow ( ImageException, "Not yet supportet without IPP." );
#endif // NICE_USELIB_IPP

  return result;
}





template<class P>
ColorImageT<P>* wiener ( const ColorImageT<P>& src, int anchorx, int anchory,
                         uint maskx, uint masky, float noiserate, ColorImageT<P>* dst )
{
  return wiener ( src, anchorx, anchory, maskx, masky, noiserate,
                  noiserate, noiserate, dst );
}

template<class P>
ColorImageT<P>* wiener ( const ColorImageT<P>& src, int anchorx, int anchory,
                         uint maskx, uint masky, float noiserateR,
                         float noiserateG, float noiserateB, ColorImageT<P>* dst )
{
  if ( anchorx == -1 )
    anchorx = maskx / 2;
  if ( anchory == -1 )
    anchory = masky / 2;

  ColorImageT<P> *result = createResultBuffer ( src, dst );

  if ( src.width() != result->width() || src.height() != result->height() )
    fthrow ( ImageException, "src and dst must have the same size." );

#ifdef NICE_USELIB_IPP
  IppiPoint anchor = {anchorx, anchory};
  IppiSize ippiSize = { src.width() - maskx + 1, src.height() - masky + 1 };
  IppiSize mask = {maskx, masky};
  Ipp32f noise[3] = {noiserateR, noiserateG, noiserateB};

  int pBufferSize;
  IppStatus ret = ippiFilterWienerGetBufferSize ( ippiSize, mask, 3, &pBufferSize );
  if ( ret != ippStsNoErr )
    fthrow ( ImageException, ippGetStatusString ( ret ) );
  Ipp8u pBuffer[pBufferSize];

  ret = ippiFilterWiener_C3R ( src.getPixelPointerXY ( maskx - 1 - anchorx, masky - 1 - anchory ),
                               src.getStepsize(),
                               result->getPixelPointerXY ( anchorx, anchory ),
                               result->getStepsize(),
                               ippiSize,
                               mask,
                               anchor,
                               noise,
                               pBuffer );
  if ( ret != ippStsNoErr )
    fthrow ( ImageException, ippGetStatusString ( ret ) );
#else // NICE_USELIB_IPP
  fthrow ( ImageException, "Not yet supportet without IPP." );
#endif // NICE_USELIB_IPP

  return result;
}
} // namespace

