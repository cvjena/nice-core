#include "core/image/ImageTools.h"
#include <math.h>
#include <list>
#include <vector>
#include <queue>

using namespace std;
using namespace std;

namespace NICE
{

// // // // // arithmetic an logical operations // // // // /

Image* absDiff ( const Image& src0, const Image& src1, Image* dst )
{
  if ( src0.width() != src1.width() || src0.height() != src0.height() )
    fthrow ( ImageException, "Source Images must have the same size." );

  Image *result = createResultBuffer ( src0.width(), src0.height(), dst );

#ifdef NICE_USELIB_IPP
  IppStatus ret = ippiAbsDiff_8u_C1R ( src0.getPixelPointer(),
                                       src0.getStepsize(), src1.getPixelPointer(), src1.getStepsize(),
                                       result->getPixelPointer(), result->getStepsize(), makeROIFullImage (
                                         src0 ) );

  if ( ret != ippStsNoErr )
    fthrow ( ImageException, ippGetStatusString ( ret ) );

#else // NICE_USELIB_IPP
  const Ipp8u* pSrc0Start = src0.getPixelPointer();
  const Ipp8u* pSrc1Start = src1.getPixelPointer();
  Ipp8u* pDstStart = result->getPixelPointer();

  const Ipp8u *pSrc0, *pSrc1;
  Ipp8u *pDst;

  for ( int y = 0; y < src0.height(); ++y )
  {
    pSrc0 = pSrc0Start;
    pSrc1 = pSrc1Start;
    pDst = pDstStart;

    for ( int x = 0; x < src0.width(); ++x, ++pSrc0, ++pSrc1, ++pDst )
      *pDst = std::abs ( *pSrc0 - *pSrc1 );

    pSrc0Start += src0.getStepsize();
    pSrc1Start += src1.getStepsize();
    pDstStart += result->getStepsize();
  }
#endif // NICE_USELIB_IPP
  return ( result );
}

ColorImage* absDiff ( const ColorImage& src0, const ColorImage& src1,
                      ColorImage* dst )
{
  if ( src0.width() != src1.width() || src0.height() != src1.height() )
    fthrow ( ImageException, "Source Images must have the same size." );

  ColorImage *result = createResultBuffer ( src0.width(), src0.height(), dst );

#ifdef NICE_USELIB_IPP
  IppiSize ippiSize =
    { src0.width() * 3, src0.height() };

  IppStatus ret = ippiAbsDiff_8u_C1R ( src0.getPixelPointer(),
                                       src0.getStepsize(), src1.getPixelPointer(), src1.getStepsize(),
                                       result->getPixelPointer(), result->getStepsize(), ippiSize );

  if ( ret != ippStsNoErr )
    fthrow ( ImageException, ippGetStatusString ( ret ) );

#else // NICE_USELIB_IPP
  const Ipp8u* pSrc0Start = src0.getPixelPointer();
  const Ipp8u* pSrc1Start = src1.getPixelPointer();
  Ipp8u* pDstStart = result->getPixelPointer();

  const Ipp8u *pSrc0, *pSrc1;
  Ipp8u *pDst;

  for ( int y = 0; y < src0.height(); ++y )
  {
    pSrc0 = pSrc0Start;
    pSrc1 = pSrc1Start;
    pDst = pDstStart;

    for ( int x = 0; x < 3*src0.width(); ++x, ++pSrc0, ++pSrc1, ++pDst )
      *pDst = std::abs ( *pSrc0 - *pSrc1 );

    pSrc0Start += src0.getStepsize();
    pSrc1Start += src1.getStepsize();
    pDstStart += result->getStepsize();
  }
#endif // NICE_USELIB_IPP
  return ( result );
}

Image* And ( const Image& src0, const Image& src1, Image *dst )
{
  if ( src0.width() != src1.width() || src0.height() != src0.height() )
    fthrow ( ImageException, "Source Images must have the same size." );

  Image *result = createResultBuffer ( src0.width(), src0.height(), dst );

#ifdef NICE_USELIB_IPP
  IppStatus ret = ippiAnd_8u_C1R ( src0.getPixelPointer(), src0.getStepsize(),
                                   src1.getPixelPointer(), src1.getStepsize(),
                                   result->getPixelPointer(), result->getStepsize(), makeROIFullImage (
                                     src0 ) );

  if ( ret != ippStsNoErr )
    fthrow ( ImageException, ippGetStatusString ( ret ) );

#else // NICE_USELIB_IPP
  int bwidth = src0.width() / sizeof ( Ipp32u );
  int bwidth_remainder = src0.width() % sizeof ( Ipp32u );
  //int bwidthr = src0.width() - bwidth;

  for ( int y = 0; y < src0.height(); ++y )
  {
    const Ipp32u* s1 = ( const Ipp32u* ) ( src0.getPixelPointerY ( y ) );
    const Ipp32u* s2 = ( const Ipp32u* ) ( src1.getPixelPointerY ( y ) );
    Ipp32u* d = ( Ipp32u* ) ( result->getPixelPointerY ( y ) );

    for ( int x = 0; x < bwidth; ++x, ++s1, ++s2, ++d )
      *d = *s1 & *s2;

    const Ipp8u *ps1 = ( const Ipp8u* ) ( --s1 );
    const Ipp8u *ps2 = ( const Ipp8u* ) ( --s2 );
    Ipp8u *pd = ( Ipp8u* ) ( --d );

    for ( int x = 0; x < bwidth_remainder; ++x, ++ps1, ++ps2, ++pd )
      *pd = *ps1 & *ps2;
  }
#endif // NICE_USELIB_IPP
  return ( result );
}

ColorImage* And ( const ColorImage& src0, const ColorImage& src1, ColorImage* dst )
{
  if ( src0.width() != src1.width() || src0.height() != src0.height() )
    fthrow ( ImageException, "Source Images must have the same size." );

  ColorImage *result = createResultBuffer ( src0.width(), src0.height(), dst );

#ifdef NICE_USELIB_IPP
  IppStatus ret = ippiAnd_8u_C3R ( src0.getPixelPointer(), src0.getStepsize(),
                                   src1.getPixelPointer(), src1.getStepsize(),
                                   result->getPixelPointer(), result->getStepsize(), makeROIFullImage (
                                     src0 ) );

  if ( ret != ippStsNoErr )
    fthrow ( ImageException, ippGetStatusString ( ret ) );

#else // NICE_USELIB_IPP
  int bwidth = ( src0.width() * 3 ) / sizeof ( Ipp32u );
  int bwidth_remainder = ( src0.width() * 3 ) % sizeof ( Ipp32u );

  for ( int y = 0; y < src0.height(); ++y )
  {
    const Ipp32u* s1 = ( const Ipp32u* ) ( src0.getPixelPointerY ( y ) );
    const Ipp32u* s2 = ( const Ipp32u* ) ( src1.getPixelPointerY ( y ) );
    Ipp32u* d = ( Ipp32u* ) ( result->getPixelPointerY ( y ) );

    for ( int x = 0; x < bwidth; ++x, ++s1, ++s2, ++d )
      *d = *s1 & *s2;

    const Ipp8u *ps1 = ( const Ipp8u* ) ( --s1 );
    const Ipp8u *ps2 = ( const Ipp8u* ) ( --s2 );
    Ipp8u *pd = ( Ipp8u* ) ( --d );

    for ( int x = 0; x < bwidth_remainder; ++x, ++ps1, ++ps2, ++pd )
      *pd = *ps1 & *ps2;
  }
#endif // NICE_USELIB_IPP
  return ( result );
}

// // // // // threshold functions // // // // //

Image* threshold ( const Image& src, const int threshold, Image* dst )
{
  Image* result = createResultBuffer ( src, dst );

#ifdef NICE_USELIB_IPP
  IppiSize roiSize =
    { src.width(), src.height() };

  IppStatus ret = ippiThreshold_Val_8u_C1R ( src.getPixelPointer(),
                  src.getStepsize(), result->getPixelPointer(),
                  result->getStepsize(), makeROIFullImage ( src ), threshold + 1, 0,
                  ippCmpLess );

  if ( ret != ippStsNoErr )
    fthrow ( ImageException, ippGetStatusString ( ret ) );

  ret = ippiThreshold_Val_8u_C1R ( result->getPixelPointer(),
                                   result->getStepsize(), result->getPixelPointer(),
                                   result->getStepsize(), roiSize, threshold, 255, ippCmpGreater );

  if ( ret != ippStsNoErr )
    fthrow ( ImageException, ippGetStatusString ( ret ) );

#else // NICE_USELIB_IPP
  const Ipp8u* pSrcStart = src.getPixelPointer();
  Ipp8u* pDstStart = result->getPixelPointer();

  const Ipp8u* pSrc;
  Ipp8u* pDst;
  for ( int y = 0; y < src.height(); ++y )
  {
    pSrc = pSrcStart;
    pDst = pDstStart;

    for ( int x = 0; x < src.width(); ++x, ++pSrc, ++pDst )
      *pDst = ( *pSrc > threshold ) ? 255 : 0;

    pSrcStart += src.getStepsize();
    pDstStart += result->getStepsize();
  }
#endif

  return result;
}

Image* lowerThreshold ( const Image& src, const int threshold, Image* dst,
                        const int value )
{
  Image* result = createResultBuffer ( src, dst );

#ifdef NICE_USELIB_IPP
  IppStatus ret = ippiThreshold_Val_8u_C1R ( src.getPixelPointer(),
                  src.getStepsize(), result->getPixelPointer(),
                  result->getStepsize(), makeROIFullImage ( src ), threshold + 1, value,
                  ippCmpLess );

  if ( ret != ippStsNoErr )
    fthrow ( ImageException, ippGetStatusString ( ret ) );

#else // NICE_USELIB_IPP
  const Ipp8u* pSrcStart = src.getPixelPointer();
  Ipp8u* pDstStart = result->getPixelPointer();

  const Ipp8u* pSrc;
  Ipp8u* pDst;
  for ( int y = 0; y < src.height(); ++y )
  {
    pSrc = pSrcStart;
    pDst = pDstStart;

    for ( int x = 0; x < src.width(); ++x, ++pSrc, ++pDst )
      *pDst = ( *pSrc <= threshold ) ? value : *pSrc;

    pSrcStart += src.getStepsize();
    pDstStart += result->getStepsize();
  }
#endif

  return result;
}

Image* upperThreshold ( Image& src, const int threshold, Image* dst,
                        const int value )
{
  Image* result = createResultBuffer ( src, dst );

#ifdef NICE_USELIB_IPP
  IppStatus ret = ippiThreshold_Val_8u_C1R ( src.getPixelPointer(),
                  src.getStepsize(), result->getPixelPointer(),
                  result->getStepsize(), makeROIFullImage ( src ), threshold, value,
                  ippCmpGreater );

  if ( ret != ippStsNoErr )
    fthrow ( ImageException, ippGetStatusString ( ret ) );

#else // NICE_USELIB_IPP
  const Ipp8u* pSrcStart = src.getPixelPointer();
  Ipp8u* pDstStart = result->getPixelPointer();

  const Ipp8u* pSrc;
  Ipp8u* pDst;
  for ( int y = 0; y < src.height(); ++y )
  {
    pSrc = pSrcStart;
    pDst = pDstStart;

    for ( int x = 0; x < src.width(); ++x, ++pSrc, ++pDst )
      *pDst = ( *pSrc > threshold ) ? value : *pSrc;

    pSrcStart += src.getStepsize();
    pDstStart += result->getStepsize();
  }
#endif

  return result;
}

void thresholdIP ( Image& src, const int threshold )
{
#ifdef NICE_USELIB_IPP
  IppStatus ret = ippiThreshold_Val_8u_C1IR ( src.getPixelPointer(),
                  src.getStepsize(), makeROIFullImage ( src ), threshold + 1, 0,
                  ippCmpLess );

  if ( ret != ippStsNoErr )
    fthrow ( ImageException, ippGetStatusString ( ret ) );

  ret = ippiThreshold_Val_8u_C1IR ( src.getPixelPointer(), src.getStepsize(),
                                    makeROIFullImage ( src ), threshold, 255, ippCmpGreater );

  if ( ret != ippStsNoErr )
    fthrow ( ImageException, ippGetStatusString ( ret ) );

#else // NICE_USELIB_IPP
  Ipp8u* pSrcStart = src.getPixelPointer();
  Ipp8u* pSrc;
  for ( int y = 0; y < src.height(); ++y )
  {
    pSrc = pSrcStart;

    for ( int x = 0; x < src.width(); ++x, ++pSrc )
      *pSrc = ( *pSrc <= threshold ) ? 0 : 255;

    pSrcStart += src.getStepsize();
  }
#endif // NICE_USELIB_IPP
}

void lowerThresholdIP ( Image& src, const int threshold, const int value )
{
#ifdef NICE_USELIB_IPP
  IppStatus ret = ippiThreshold_Val_8u_C1IR ( src.getPixelPointer(),
                  src.getStepsize(), makeROIFullImage ( src ), threshold + 1, value,
                  ippCmpLess );

  if ( ret != ippStsNoErr )
    fthrow ( ImageException, ippGetStatusString ( ret ) );

#else // NICE_USELIB_IPP
  Ipp8u* pSrcStart = src.getPixelPointer();
  Ipp8u* pSrc;
  for ( int y = 0; y < src.height(); ++y )
  {
    pSrc = pSrcStart;

    for ( int x = 0; x < src.width(); ++x, ++pSrc )
      *pSrc = ( *pSrc <= threshold ) ? value : *pSrc;

    pSrcStart += src.getStepsize();
  }
#endif // NICE_USELIB_IPP
}

void upperThresholdIP ( Image& src, const int threshold, const int value )
{
#ifdef NICE_USELIB_IPP
  IppStatus ret = ippiThreshold_Val_8u_C1IR ( src.getPixelPointer(),
                  src.getStepsize(), makeROIFullImage ( src ), threshold, value,
                  ippCmpGreater );

  if ( ret != ippStsNoErr )
    fthrow ( ImageException, ippGetStatusString ( ret ) );

#else // NICE_USELIB_IPP
  Ipp8u* pSrcStart = src.getPixelPointer();
  Ipp8u* pSrc;
  for ( int y = 0; y < src.height(); ++y )
  {
    pSrc = pSrcStart;

    for ( int x = 0; x < src.width(); ++x, ++pSrc )
      *pSrc = ( *pSrc > threshold ) ? value : *pSrc;

    pSrcStart += src.getStepsize();
  }
#endif // NICE_USELIB_IPP
}

// // // // // Line Segmentation // // // // //

FloatImage* houghTransformLUT()
{
  FloatImage* lut = new FloatImage ( 256, 3 );

  for ( int phi = 0; phi < 180; ++phi )
  {
    lut->setPixelQuick ( phi, 0, std::cos ( ( phi * M_PI ) / 180.0 ) );
    lut->setPixelQuick ( phi, 1, std::sin ( ( phi * M_PI ) / 180.0 ) );
  }

  for ( int i = 0; i < 256; ++i )
    lut->setPixelQuick ( i, 2, 8 * std::log ( static_cast<float> ( i ) ) );

  return lut;
}

IntMatrix* houghTransform ( const Image& gradStr, const Image& gradDir,
                            const uint& noLines, const uint& gradThresh, const uint& soAreaDeg,
                            const uint& soAreaDist, const uint& soBorder, const FloatImage* lut,
                            const int diffAngle )
{
  if ( gradStr.width() != gradDir.width() || gradStr.height()
       != gradDir.height() )
    fthrow ( ImageException, "Source Images must have the same size." );

  int isoAreaDeg = soAreaDeg;
  int isoAreaDist = soAreaDist;
  int isoBorder = soBorder;
  int diag = static_cast<int> ( std::sqrt ( static_cast<double> ( gradStr.width()
                                * gradStr.width() + gradStr.height() * gradStr.height() ) ) );

  // building hough akku
  int tdist, tphi;
  ImageT<int> akku ( 2 * diag + 1, 180 );
  akku.set ( 0 );

  // use lut if specified
  if ( lut != NULL )
  {
    for ( int y = isoBorder; y < gradStr.height() - isoBorder; ++y )
      for ( int x = isoBorder; x < gradStr.width() - isoBorder; ++x )
        if ( gradStr.getPixelQuick ( x, y ) > gradThresh )
          for ( int phi = gradDir.getPixelQuick ( x, y ) - diffAngle; phi
                < gradDir.getPixelQuick ( x, y ) + diffAngle; ++phi )
          {
            if ( phi >= 180 )
              tphi = phi % 180;
            else if ( phi < 0 )
              tphi = 180 + phi;
            else
              tphi = phi;

            tdist = static_cast<int> ( x * lut->getPixelQuick ( tphi,
                                       0 ) + y * lut->getPixelQuick ( tphi, 1 ) );
            akku ( tdist + diag, tphi )
            += static_cast<int> ( lut->getPixelQuick (
                                    gradStr.getPixelQuick ( x, y ), 2 ) );
          }
  }
  else
  {
    for ( int y = isoBorder; y < gradStr.height() - isoBorder; ++y )
      for ( int x = isoBorder; x < gradStr.width() - isoBorder; ++x )
        if ( gradStr.getPixelQuick ( x, y ) > gradThresh )
          for ( int phi = gradDir.getPixelQuick ( x, y ) - diffAngle; phi
                < gradDir.getPixelQuick ( x, y ) + diffAngle; ++phi )
          {
            if ( phi >= 180 )
              tphi = phi % 180;
            else if ( phi < 0 )
              tphi = 180 + phi;
            else
              tphi = phi;

            tdist = static_cast<int> ( x
                                       * cos ( ( tphi * M_PI ) / 180.0 ) + y * sin ( ( tphi
                                           * M_PI ) / 180.0 ) );
            akku ( tdist + diag, tphi ) += static_cast<int> ( 8
                                           * std::log ( float ( gradStr.getPixelQuick ( x, y ) ) ) );
          }
  }

  //
  std::vector<IntVector> L;
  int max_dist, max_phi, max_val, _d, _p;
  while ( L.size() < noLines )
  {
    max_val = max_phi = max_dist = 0;
    for ( int phi = 0; phi < 180; ++phi )
      for ( int dist = -diag; dist <= diag; ++dist )
        if ( akku.getPixelQuick ( dist + diag, phi ) > max_val )
        {
          max_phi = phi;
          max_dist = dist;
          max_val = akku.getPixelQuick ( max_dist + diag, max_phi );
        }

    if ( max_val == 0 )
      break;

    for ( int deg = -isoAreaDeg; deg <= isoAreaDeg; ++deg )
      for ( int dist = -isoAreaDist; dist <= isoAreaDist; ++dist )
        if ( ( max_dist + dist ) >= -diag && ( max_dist + dist ) <= diag )
        {
          _p = max_phi + deg;
          _d = max_dist + dist;
          _d = ( _p >= 180 || _p < 0 ) ? -_d : _d;
          _p = ( _p >= 180 ) ? _p - 180 : ( _p < 0 ? _p + 180 : _p );
          akku ( _d + diag, _p ) = 0;
        }
    int buffer[3] =
      { max_dist, max_phi, max_val };
    L.push_back ( IntVector ( buffer, 3 ) );
  }

  IntMatrix* rMat = new IntMatrix ( L.size(), 3 );
  for ( uint j = 0; j < L.size(); ++j )
    for ( int i = 0; i < 3; ++i )
      ( *rMat ) ( j, i ) = L[j][i];

  return rMat;
}
;

IntMatrix* houghTransform ( const Image& gradStr, const uint& noLines,
                            const uint& gradThresh, const uint& soAreaDeg, const uint& soAreaDist,
                            const uint& soBorder, const FloatImage* lut )
{
  int isoAreaDeg = soAreaDeg;
  int isoAreaDist = soAreaDist;
  int isoBorder = soBorder;
  int width = gradStr.width();
  int height = gradStr.height();
  int diag = static_cast<int> ( std::sqrt ( static_cast<double> ( width * width
                                + height * height ) ) );

  // building hough akku
  int tdist;
  ImageT<int> akku ( 2 * diag + 1, 180 );
  akku.set ( 0 );

  if ( lut != NULL )
  {
    for ( int y = isoBorder; y < gradStr.height() - isoBorder; ++y )
      for ( int x = isoBorder; x < gradStr.width() - isoBorder; ++x )
        if ( gradStr.getPixelQuick ( x, y ) > gradThresh )
          for ( int tphi = 0; tphi < 180; ++tphi )
          {
            tdist = static_cast<int> ( x * lut->getPixelQuick ( tphi,
                                       0 ) + y * lut->getPixelQuick ( tphi, 1 ) );
            akku ( tdist + diag, tphi )
            += static_cast<int> ( lut->getPixelQuick (
                                    gradStr.getPixelQuick ( x, y ), 2 ) );
          }
  }
  else
  {
    for ( int y = isoBorder; y < gradStr.height() - isoBorder; ++y )
      for ( int x = isoBorder; x < gradStr.width() - isoBorder; ++x )
        if ( gradStr.getPixelQuick ( x, y ) > gradThresh )
          for ( int tphi = 0; tphi < 180; ++tphi )
          {
            tdist = static_cast<int> ( x
                                       * cos ( ( tphi * M_PI ) / 180.0 ) + y * sin ( ( tphi
                                           * M_PI ) / 180.0 ) );
            akku ( tdist + diag, tphi ) += static_cast<int> ( 8
                                           * std::log ( float ( gradStr.getPixelQuick ( x, y ) ) ) );
          }
  }

  //
  std::vector<IntVector> L;
  int max_dist, max_phi, max_val, _d, _p;
  while ( L.size() < noLines )
  {
    max_val = max_phi = max_dist = 0;
    for ( int phi = 0; phi < 180; ++phi )
      for ( int dist = -diag; dist <= diag; ++dist )
        if ( akku.getPixelQuick ( dist + diag, phi ) > max_val )
        {
          max_phi = phi;
          max_dist = dist;
          max_val = akku.getPixelQuick ( max_dist + diag, max_phi );
        }

    if ( max_val == 0 )
      break;

    for ( int deg = -isoAreaDeg; deg <= isoAreaDeg; ++deg )
      for ( int dist = -isoAreaDist; dist <= isoAreaDist; ++dist )
        if ( ( max_dist + dist ) >= -diag && ( max_dist + dist ) <= diag )
        {
          _p = max_phi + deg;
          _d = max_dist + dist;
          _d = ( _p >= 180 || _p < 0 ) ? -_d : _d;
          _p = ( _p >= 180 ) ? _p - 180 : ( _p < 0 ? _p + 180 : _p );
          akku ( _d + diag, _p ) = 0;
        }
    int buffer[3] =
      { max_dist, max_phi, max_val };
    L.push_back ( IntVector ( buffer, 3 ) );
  }

  IntMatrix* rMat = new IntMatrix ( L.size(), 3 );
  for ( uint j = 0; j < L.size(); ++j )
    for ( int i = 0; i < 3; ++i )
      ( *rMat ) ( j, i ) = L[j][i];

  return rMat;
}

// // // // // Corner Detection // // // // //

Matrix* KLTCornerDetector ( const Image& src, const uint& noCorners,
                            const double& EVThresh, const uint& soNeighborhood, const uint& soArea,
                            const GrayImage16s* gradX, const GrayImage16s* gradY )
{
  if ( gradX != NULL )
    if ( gradX->width() != src.width() || gradX->height() != src.height() )
      fthrow ( ImageException, "Optional gradient image gradY must have the same size like src." );

  if ( gradY != NULL )
    if ( gradY->width() != src.width() || gradY->height() != src.height() )
      fthrow ( ImageException, "Optional gradient image gradY must have the same size like src." );

  NICE::FilterT<unsigned char, unsigned char, unsigned char> filter;
  NICE::GrayImage16s* diffX = new NICE::GrayImage16s( src.width(), src.height() );
  NICE::GrayImage16s* diffY = new NICE::GrayImage16s( src.width(), src.height() );

  if ( gradX == NULL )
  {
    NICE::Image dstx( src.width(), src.height() );
    filter.sobelX( src, dstx );
    for (int y = 0; y < diffX->height(); y++)
      for (int x = 0; x < diffX->width(); x++)
        diffX->setPixelQuick( x, y, (short int)dstx.getPixelQuick(x,y) );
  }
  else
    diffX = (NICE::GrayImage16s*)gradX;

  if ( gradY == NULL )
  {
    NICE::Image dsty( src.width(), src.height() );
    filter.sobelY( src, dsty );
    for (int y = 0; y < diffY->height(); y++)
      for (int x = 0; x < diffY->width(); x++)
        diffY->setPixelQuick( x, y, (short int)dsty.getPixelQuick(x,y) );
  }
  else
    diffY = (NICE::GrayImage16s*)gradY;

  //
  uint EXQ, EYQ, EXY;
  double eigenV;
  int xval, yval;

  // std::vector is used because VectorT doesn't support something like push_back
  std::priority_queue<std::pair<double, std::pair<int, int> > > IP;
  for ( int y = soNeighborhood + 1; y < src.height() - 1
        - static_cast<int> ( soNeighborhood ); ++y )
    for ( int x = soNeighborhood + 1; x < src.width() - 1
          - static_cast<int> ( soNeighborhood ); ++x )
    {
      // build structure matrix for actuall pixel
      EXQ = EYQ = EXY = 0;
      for ( int tx = -static_cast<int> ( soNeighborhood ); tx
            <= static_cast<int> ( soNeighborhood ); ++tx )
        for ( int ty = -static_cast<int> ( soNeighborhood ); ty
              <= static_cast<int> ( soNeighborhood ); ++ty )
        {
          xval = ( *diffX ) ( x + tx, y + ty );
          yval = ( *diffY ) ( x + tx, y + ty );

          EXQ += xval * xval;
          EXY += xval * yval;
          EYQ += yval * yval;
        }

      // calc the smallest of the 2 eigenvalues of the char. matrix
      eigenV = ( EXQ + EYQ + sqrt ( static_cast<double> ( ( EXQ - EYQ ) * ( EXQ
                                    - EYQ ) + 4 * EXY * EXY ) ) );

      if ( eigenV > 0 && eigenV >= EVThresh )
      {
        IP.push ( pair<double, pair<int, int> > ( eigenV, pair<int, int> (
                    x, y ) ) );
      }
    }
  if ( gradX == NULL )
    delete diffX;
  if ( gradY == NULL )
    delete diffY;

  Matrix* ipMat;
  if ( noCorners == 0 )
  {
    ipMat = new Matrix ( IP.size(), 3, 0 );
  }
  else
  {
    ipMat = new Matrix ( IP.size() < noCorners ? IP.size() : noCorners, 3, 0 );
  }
  Image markImg ( src.width(), src.height() );
  markImg.set ( 0 );
  Rect rect;
  for ( size_t c = 0; c < ipMat->rows(); ++c )
  {
    int xp, yp;
    double ev = -1.0;
    bool validCornerFound = false;
    do
    {
      const std::pair<double, std::pair<int, int> > & topElement =
        IP.top();
      xp = topElement.second.first;
      yp = topElement.second.second;
      if ( markImg.getPixelQuick ( xp, yp ) == 0 )
      {
        ev = topElement.first;
        validCornerFound = true;
      }
      IP.pop();
    } while ( !validCornerFound && !IP.empty() );

    if ( !validCornerFound )
    {
      ipMat->resize ( c, 3 );
      break;
    }

    ( *ipMat ) ( c, 0 ) = xp; // x-pos
    ( *ipMat ) ( c, 1 ) = yp; // y-pos
    ( *ipMat ) ( c, 2 ) = ev; // EV

    // mark area around this corner
    rect = Rect ( xp - static_cast<int> ( soArea / 2 ), yp
                  - static_cast<int> ( soArea / 2 ), soArea, soArea );
    rect = clipRect ( markImg, rect );

    for ( int y = rect.top; y < rect.bottom(); ++y )
      for ( int x = rect.left; x < rect.right(); ++x )
        markImg.setPixelQuick ( x, y, 255 );
  }

  return ipMat;
}

}
; // namespace NICE
