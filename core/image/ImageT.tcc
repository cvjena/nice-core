/*
 * LImUn - Library for ImageT Understanding
 *  - libimage - An ImageT library
 * See file License for license information.
 */
#include "core/image/ImageT.h"
#include <core/basics/tools.h>
#include <memory>

namespace NICE {

template<class P>
ImageT<P>& ImageT<P>::operator= ( const P c ) {
#ifdef NICE_USELIB_IPP
  IppiSize ippiSize = { this->width(), this->height() };
  ippiSet_C1R ( static_cast<P> ( c ), this->getPixelPointer(), this->rowStepsize(), ippiSize );
#else
  Ipp8u* pos = reinterpret_cast<Ipp8u*> ( this->getPixelPointer() );
  P **row = new P*[this->height() ];
  for ( int y = 0;y < this->height(); ++y ) {
    row[y] = reinterpret_cast<P*> ( pos );
    pos += this->rowStepsize();
  }
  P *p;
  for ( int y = 0;y < this->height(); ++y ) {
    p = row[y];
    for ( int x = 0;x < this->width(); ++x, p++ ) {
      *p = c;
    }
  }
  delete [] row;
#endif
  return *this;
}

template<class P>
ImageT<P>::ImageT ( const int width, const int height,
                    const GrayColorImageCommonImplementation::MemoryLayout _memoryLayout ) {
  this->allocPixel ( width, height, _memoryLayout );
}

template<class P>
ImageT<P>::ImageT ( const ImageT<P>& orig, const GrayColorImageCommonImplementation::MemoryLayout copyMode ) :
    BlockImageAccessT<P> () {
  this->fromRaw ( orig.getPixelPointer(), orig.width(), orig.height(), orig.rowStepsize(), this->toCopyLayout ( copyMode, orig ) );
}

template<class P>
ImageT<P>& ImageT<P>::operator= ( const ImageT<P>& orig ) {
  if ( this->width() == orig.width() && this->height() == orig.height() ) {
    doFromRaw ( orig.getPixelPointer(), orig.rowStepsize() );
  } else {
    fromRaw ( orig.getPixelPointer(), orig.width(), orig.height(), orig.rowStepsize(), this->toCopyLayout (
                GrayColorImageCommonImplementation::originalAlignment, orig ) );
  }
  return *this;
}

template<class P>
ImageT<P>::ImageT ( ImageT<P>& orig, const GrayColorImageCommonImplementation::ShallowCopyMode shallow ) {
  UNUSED_PARAMETER ( shallow );
  setForeignPointer ( orig.getPixelPointer(), orig.width(), orig.height(), orig.getStepsize(), sizeof ( P ) );
}

template<class P>
ImageT<P>::ImageT ( const P* raw, const int width, const int height, const int stepsize,
                    const GrayColorImageCommonImplementation::MemoryLayout copyMode ) {
  fromRaw ( raw, width, height, stepsize, copyMode );
}

template<class P>
ImageT<P>::ImageT ( P* raw, const int width, const int height, const int stepsize,
                    const GrayColorImageCommonImplementation::ShallowCopyMode shallow ) {
  UNUSED_PARAMETER ( shallow );
  this->setForeignPointer ( raw, width, height, stepsize, sizeof ( P ) );
}

template<class P>
ImageT<P>::ImageT ( const P* raw, const int width, const int height,
                    const GrayColorImageCommonImplementation::MemoryLayout copyMode ) {
  fromRaw ( raw, width, height, sizeof ( P ) * width, copyMode );
}

template<class P>
ImageT<P>::ImageT ( P* raw, const int width, const int height,
                    const GrayColorImageCommonImplementation::ShallowCopyMode shallow ) {
  UNUSED_PARAMETER ( shallow );
  this->setForeignPointer ( raw, width, height, sizeof ( P ) * width, sizeof ( P ) );
}

template<class P>
ImageT<P>::ImageT ( const ImageT<P>& orig, const GrayColorImageCommonImplementation::ShallowCopyMode shallow ) {
  UNUSED_PARAMETER ( shallow );
  this->setForeignPointerConst ( orig.getPixelPointer(), orig.width(), orig.height(), orig.rowStepsize(), orig.columnStepsize() );
}

template<class P>
ImageT<P>::ImageT ( const P* raw, const int width, const int height, const int stepsize,
                    const GrayColorImageCommonImplementation::ShallowCopyMode shallow ) {
  UNUSED_PARAMETER ( shallow );
  this->setForeignPointerConst ( raw, width, height, stepsize, sizeof ( P ) );
}

template<class P>
ImageT<P>::ImageT() {
  this->allocPixel ( 0, 0, GrayColorImageCommonImplementation::ippAlignment );
}

template<class P>
ImageT<P>::ImageT ( const std::string& FileName, const GrayColorImageCommonImplementation::MemoryLayout _memoryLayout ) {
  this->allocPixel ( 0, 0, _memoryLayout );
  this->read ( ImageFile ( FileName ) /*, _memoryLayout*/ );
}

template<class P>
void ImageT<P>::doAllocPixelNoAlignment() {
  this->setPixelPointer ( new P[this->m_xsize * this->m_ysize] );
  this->m_rowStepsize = sizeof ( P ) * this->m_xsize;
}

template<class P>
void ImageT<P>::doAllocPixelIPP() {
  // no IPP in generic implementation (-> specialization in ImageT.cpp)
  doAllocPixelNoAlignment();
  this->m_memoryLayout = GrayColorImageCommonImplementation::noAlignment;
}

#ifdef NICE_USELIB_IPP
template<>
void ImageT<Ipp8u>::doAllocPixelIPP();
template<>
void ImageT<Ipp16s>::doAllocPixelIPP();
template<>
void ImageT<Ipp32f>::doAllocPixelIPP();
#endif //NICE_USELIB_IPP
template<class P>
ImageT<P>::~ImageT() {
}

template<class P>
void ImageT<P>::fromRaw ( const P* raw, const int width, const int height, const int rowStepsize,
                          const GrayColorImageCommonImplementation::MemoryLayout copyMode ) {
  if ( copyMode == GrayColorImageCommonImplementation::internal__foreignPointer || copyMode
       == GrayColorImageCommonImplementation::originalAlignment ) {
    fthrow ( ImageException,
             "internal__foreignPointer and originalAlignment not supported here" );
  } else if ( copyMode == GrayColorImageCommonImplementation::keepAlignment && this->width() >= width && this->height()
              >= height ) {
    fthrow ( ImageException, "not enough image space for copying data without reallocation" );
  } else {
    this->allocPixel ( width, height, copyMode );
    doFromRaw ( raw, rowStepsize );
  }
}

template<class P>
void ImageT<P>::doFromRaw ( const P* raw, const int rowStepsize ) {
  // no IPP in generic implementation (-> specialization in ImageT.cpp)
  for ( int y = 0; y < this->height(); y++ ) {
    const P* line = pointerToPixel1 ( raw, 0, y, rowStepsize );
    const P* lineTargetEnd = this->getPixelPointerYEnd ( y );
    for ( P* lineTarget = this->getPixelPointerY ( y ); lineTarget < lineTargetEnd; lineTarget++ ) {
      *lineTarget = *line;
      line++;
    }
  }
}

#ifdef NICE_USELIB_IPP
template<>
void ImageT<Ipp8u>::doFromRaw ( const Pixel* raw, const int stepsize );
template<>
void ImageT<Ipp16s>::doFromRaw ( const Pixel* raw, const int stepsize );
template<>
void ImageT<Ipp32f>::doFromRaw ( const Pixel* raw, const int stepsize );
#endif //NICE_USELIB_IPP
template<class P>
P ImageT<P>::getPixel ( const int x, const int y ) const {
  if ( this->isWithinImage ( x, y ) ) {
    return getPixelQuick ( x, y );
  } else {
    fthrow ( ImageException,
             "ImageT<P>::getPixel: (x,y) out of range." );
  }
}

template<class P>
P ImageT<P>::getPixel ( const Coord &coord ) const {
  if ( this->isWithinImage ( coord.x, coord.y ) ) {
    return getPixelQuick ( coord.x, coord.y );
  } else {
    fthrow ( ImageException,
             "ImageT<P>::getPixel: (coord) out of range." );
  }
}

// used by ImageT<P>::getPixelBilinear()
template<class P>
inline P getPixel0 ( const ImageT<P>& img, int x, int y ) {
  if ( x < 0 ) {
    x = 0;
  } else if ( x >= img.width() ) {
    x = img.width() - 1;
  }
  if ( y < 0 ) {
    y = 0;
  } else if ( y >= img.height() ) {
    y = img.height() - 1;
  }
  return img.getPixelQuick ( x, y );
}

template<class P>
float ImageT<P>::getPixelBilinear ( const float x, const float y ) const {
  if ( int ( x ) < this->width() && int ( ceil ( x ) ) >= 0 && int ( y ) < this->height() && int ( ceil ( y ) ) >= 0 ) {
    int xi = ( int ) x;
    int yi = ( int ) y;

    float dx1 = float ( x ) - xi;
    float dy1 = float ( y ) - yi;
    float dx2 = 1.0 - dx1;
    float dy2 = 1.0 - dy1;
    float g1 = getPixel0 ( *this, xi, yi );
    float g2 = getPixel0 ( *this, xi + 1, yi );
    float g3 = getPixel0 ( *this, xi, yi + 1 );
    float g4 = getPixel0 ( *this, xi + 1, yi + 1 );
    return dx2 * ( dy2 * g1 + dy1 * g3 ) + dx1 * ( dy2 * g2 + dy1 * g4 );
  } else {
    std::stringstream s;
    s << "ImageT<P>::getPixelBilinear: (x,y) out of range: " << x << ", " << y << ".";
    fthrow ( ImageException, s.str() );
  }
}

template<class P>
void ImageT<P>::setPixel ( const int x, const int y, const P value ) {
  if ( this->isWithinImage ( x, y ) ) {
    setPixelQuick ( x, y, value );
  } else {
    fthrow ( ImageException,
             "ImageT<P>::setPixel: (x,y) out of range." );
  }
}

template<class P>
void ImageT<P>::setPixelSave ( const int x, const int y, const P value ) {
  if ( this->isWithinImage ( x, y ) ) {
    setPixelQuick ( x, y, value );
  }
}

template<class P>
void ImageT<P>::set ( const P& value ) {
#ifdef NICE_USELIB_IPP
  // FIXME: does not work for double. Does it work for other types than unsigned char?
  if ( sizeof ( P ) == 1 ) {
    IppStatus ret = ippiSet_C1R ( value, this->getPixelPointer(), this->getStepsize(), makeROIFullImage ( *this ) );

    if ( ret != ippStsNoErr )
      fthrow ( ImageException, ippGetStatusString ( ret ) );

    return;
  }
#endif // NICE_USELIB_IPP
  P *p;
  for ( int y = 0; y < this->height(); ++y )
  {
    p = this->getPixelPointerY ( y );
    for ( int x = 0; x < this->width(); ++x, ++p )
      *p = value;
  }
}

template<class P>
void ImageT<P>::mirror ( IppiAxis axis ) {
#ifdef NICE_USELIB_IPP
  IppStatus ret = ippiMirror_C1IR ( this->getPixelPointer(), this->getStepsize(), makeROIFullImage ( *this ), axis );

  if ( ret != ippStsNoErr )
    fthrow ( ImageException, ippGetStatusString ( ret ) );

#else
  bool mirrorX = ( axis == ippAxsVertical || axis == ippAxsBoth ) ? true : false;
  bool mirrorY = ( axis == ippAxsHorizontal || axis == ippAxsBoth ) ? true : false;

  for ( int y = 0; y <= ( mirrorY ? this->height() / 2 - 1 : this->height() - 1 ); ++y )
    for ( int x = 0; x <= ( mirrorX ? this->width() / 2 - 1 : this->width() - 1 ); ++x )
      std::swap ( ( *this ) ( Coord ( x, y ) ),
                  ( *this ) ( Coord ( ( mirrorX ? this->width() - 1 - x : x ), ( mirrorY ? this->height() - 1 - y : y ) ) ) );
#endif
}

template<class P>
void ImageT<P>::transpose() {
  if ( this->width() != this->height() )
    fthrow ( ImageException, "Image size must be symetric." );

#ifdef NICE_USELIB_IPP
  IppStatus ret = ippiTranspose_C1IR ( this->getPixelPointer(), this->getStepsize(), makeROIFullImage ( *this ) );

  if ( ret != ippStsNoErr )
    fthrow ( ImageException, ippGetStatusString ( ret ) );

#else
  for ( int y = 0; y < this->height(); ++y )
    for ( int x = 0; x < y; ++x )
      std::swap ( ( *this ) ( Coord ( x, y ) ), ( *this ) ( Coord ( y, x ) ) );
#endif
}

template<class P>
void ImageT<P>::invert() {
  fthrow ( ImageException, "Datatype not yet supported." );
}
template<>
void ImageT<Ipp8u>::invert();

template<class P>
void ImageT<P>::abs()
{
#ifdef NICE_USELIB_IPP
  IppStatus ret = ippiAbs_C1IR ( this->getPixelPointer(),
                                 this->getStepsize(),
                                 makeROIFullImage ( *this ) );

  if ( ret != ippStsNoErr )
    fthrow ( ImageException, ippGetStatusString ( ret ) );

#else
  P* p;
  for ( int y = 0; y < this->height(); ++y )
  {
    p = this->getPixelPointerY ( y );
    for ( int x = 0; x < this->width(); ++x, ++p )
      *p = ( *p < 0 ) ? -*p : *p;
  }
#endif
}

template<class P>
P ImageT<P>::min() const
{
  P min = std::numeric_limits<P>::max();

#ifdef NICE_USELIB_IPP
  IppStatus ret = ippiMin_C1R ( this->getPixelPointer(),
                                this->getStepsize(),
                                makeROIFullImage ( *this ), &min );

  if ( ret != ippStsNoErr )
    fthrow ( ImageException, ippGetStatusString ( ret ) );

#else
  const P* p;
  for ( int y = 0; y < this->height(); ++y )
  {
    p = this->getPixelPointerY ( y );
    for ( int x = 0; x < this->width(); ++x, ++p )
      min = ( *p < min ) ? *p : min;
  }
#endif
  return min;
}

template<class P>
P ImageT<P>::max() const
{
  P max = std::numeric_limits<P>::min();

#ifdef NICE_USELIB_IPP
  IppStatus ret = ippiMax_C1R ( this->getPixelPointer(),
                                this->getStepsize(),
                                makeROIFullImage ( *this ), &max );

  if ( ret != ippStsNoErr )
    fthrow ( ImageException, ippGetStatusString ( ret ) );

#else
  const P* p;
  for ( int y = 0; y < this->height(); ++y )
  {
    p = this->getPixelPointerY ( y );
    for ( int x = 0; x < this->width(); ++x, ++p )
      max = ( *p > max ) ? *p : max;
  }
#endif

  return max;
}

template<class P>
void ImageT<P>::minmax ( P& min, P& max ) const
{
#ifdef NICE_USELIB_IPP
  IppStatus ret = ippiMinMax_C1R ( this->getPixelPointer(),
                                   this->getStepsize(),
                                   makeROIFullImage ( *this ), &min, &max );

  if ( ret != ippStsNoErr )
    fthrow ( ImageException, ippGetStatusString ( ret ) );
#else
  min = std::numeric_limits<P>::max();
  max = - std::numeric_limits<P>::max();

  const P* p;
  for ( int y = 0; y < this->height(); ++y )
  {
    p = this->getPixelPointerY ( y );
    for ( int x = 0; x < this->width(); ++x, ++p )
    {
      min = ( *p < min ) ? *p : min;
      max = ( *p > max ) ? *p : max;
    }
  }
#endif
}

template<class P>
Coord ImageT<P>::minIndex() const
{
  P min = std::numeric_limits<P>::max();
  Coord index;

#ifdef NICE_USELIB_IPP
  IppStatus ret = ippiMinIndx_C1R ( this->getPixelPointer(),
                                    this->getStepsize(),
                                    makeROIFullImage ( *this ), &min, &index.x, &index.y );

  if ( ret != ippStsNoErr )
    fthrow ( ImageException, ippGetStatusString ( ret ) );

#else
  const P* p;
  for ( int y = 0; y < this->height(); ++y )
  {
    p = this->getPixelPointerY ( y );
    for ( int x = 0; x < this->width(); ++x, ++p )
      if ( *p < min ) {
        min = *p;
        index.x = x;
        index.y = y;
      }
  }
#endif
  return index;
}

template<class P>
Coord ImageT<P>::maxIndex() const
{
  P max = std::numeric_limits<P>::min();
  Coord index;

#ifdef NICE_USELIB_IPP
  IppStatus ret = ippiMaxIndx_C1R ( this->getPixelPointer(),
                                    this->getStepsize(),
                                    makeROIFullImage ( *this ), &max, &index.x, &index.y );

  if ( ret != ippStsNoErr )
    fthrow ( ImageException, ippGetStatusString ( ret ) );

#else
  const P* p;
  for ( int y = 0; y < this->height(); ++y )
  {
    p = this->getPixelPointerY ( y );
    for ( int x = 0; x < this->width(); ++x, ++p )
      if ( *p > max ) {
        max = static_cast<P> ( *p );
        index.x = x;
        index.y = y;
      }
  }
#endif

  return index;
}

template<class P>
void ImageT<P>::minmaxIndex ( Coord& minidx, Coord& maxidx ) const
{
  Ipp32f min, max;
#ifdef NICE_USELIB_IPP
  IppiPoint minindex, maxindex;
  IppStatus ret = ippiMinMaxIndx_C1R ( this->getPixelPointer(), this->getStepsize(),
                                       makeROIFullImage ( *this ),
                                       &min, &max, &minindex, &maxindex );

  if ( ret != ippStsNoErr )
    fthrow ( ImageException, ippGetStatusString ( ret ) );

  minidx = Coord ( minindex.x, minindex.y );
  maxidx = Coord ( maxindex.x, maxindex.y );
#else
  min = std::numeric_limits<Ipp32f>::max();
  max = std::numeric_limits<Ipp32f>::min();

  const P* p;
  for ( int y = 0; y < this->height(); ++y )
  {
    p = this->getPixelPointerY ( y );
    for ( int x = 0; x < this->width(); ++x, ++p )
    {
      if ( *p < min ) {
        min = *p;
        minidx.x = x;
        minidx.y = y;
      }
      if ( *p > max ) {
        max = *p;
        maxidx.x = x;
        maxidx.y = y;
      }
    }
  }
#endif
}

template<class P>
double ImageT<P>::sum() const
{
  double sum = 0;

#ifdef NICE_USELIB_IPP
  IppStatus ret = ippiSum_C1R ( this->getPixelPointer(),
                                this->getStepsize(),
                                makeROIFullImage ( *this ), &sum );

  if ( ret != ippStsNoErr )
    fthrow ( ImageException, ippGetStatusString ( ret ) );
#else
  const P* p;
  for ( int y = 0; y < this->height(); ++y )
  {
    p = this->getPixelPointerY ( y );
    for ( int x = 0; x < this->width(); ++x, ++p )
      sum += *p;
  }
#endif

  return sum;
}

template<class P>
double ImageT<P>::mean() const
{
  P mean = 0;

#ifdef NICE_USELIB_IPP
  Ipp64f fmean;
  IppStatus ret = ippiMean_C1R ( this->getPixelPointer(), this->getStepsize(),
                                 makeROIFullImage ( *this ), &fmean );

  mean = static_cast<P> ( fmean );

  if ( ret != ippStsNoErr )
    fthrow ( ImageException, ippGetStatusString ( ret ) );

#else
  mean = static_cast<P> ( this->sum() / ( this->width() * this->height() ) );
#endif

  return mean;
}

template<class P>
void ImageT<P>::meanStdDev ( double& mean, double& stddev ) const
{
#ifdef NICE_USELIB_IPP
  IppStatus ret     = ippiMean_StdDev_C1R ( this->getPixelPointer(),
                      this->getStepsize(),
                      makeROIFullImage ( *this ), &mean, &stddev );

  if ( ret != ippStsNoErr )
    fthrow ( ImageException, ippGetStatusString ( ret ) );

#else
  mean        = this->mean();
  stddev      = 0.0;
  double temp = 0;

  const P* p;
  for ( int y = 0; y < this->height(); ++y )
  {
    p = this->getPixelPointerY ( y );
    for ( int x = 0; x < this->width(); ++x, ++p )
    {
      temp    = *p - mean;
      stddev += temp * temp;
    }
  }
  // ipp divide it by (this->width()*this->height()) not by (this->width()*this->height())-1) !
  stddev = sqrt ( static_cast<double> ( stddev / ( this->width() * this->height() ) ) );
#endif
}

template<class P>
ImageT<P>* ImageT<P>::copyRect ( const Rect& rect, ImageT<P>* dst )
{
  Rect roi              = clipRect ( *this, rect );
  ImageT<P>* result = createResultBuffer ( roi.width, roi.height, dst );

#ifdef NICE_USELIB_IPP
  Ipp8u const *src_rect = this->getPixelPointerXY ( roi.left, roi.top );
  IppStatus ret         = ippiCopy_C1R ( src_rect, this->getStepsize(),
                                         result->getPixelPointer(),
                                         result->getStepsize(), makeROIRect ( *this, roi ) );

  if ( ret != ippStsNoErr )
    fthrow ( ImageException, ippGetStatusString ( ret ) );

#else // NICE_USELIB_IPP
  P *pS, *pD;
  for ( int y = 0; y < roi.height; ++y )
  {
    pS = this->getPixelPointerXY ( roi.left, roi.top + y );
    pD = result->getPixelPointerY ( y );
    for ( int x = 0; x < roi.width; ++x, ++pS, ++pD )
      *pD = *pS;
  }
#endif // NICE_USELIB_IPP
  return ( result );
}

// PGM

template<class P>
void ImageT<P>::readPGM ( const char *pgmFileName, const GrayColorImageCommonImplementation::MemoryLayout _memoryLayout ) {
  readPGM ( std::string ( pgmFileName ), _memoryLayout );
}

template<class P>
void ImageT<P>::readPGM ( const std::string& pgmFileName,
                          const GrayColorImageCommonImplementation::MemoryLayout _memoryLayout ) {
  // not in generic implementation (-> specialization in ImageT.cpp)
  fthrow ( ImageException,
           "ImageT<P> readPGM currently supported for ImageT<Ipp8u> only." );
}
template<>
void ImageT<Ipp8u>::readPGM ( const std::string& pgmFileName,
                              const GrayColorImageCommonImplementation::MemoryLayout _memoryLayout );

template<class P>
void ImageT<P>::readRaw ( const char* rawFilename, const GrayColorImageCommonImplementation::MemoryLayout _memoryLayout ) {
  unsigned int width = 0;
  unsigned int height = 0;

  std::ifstream in ( rawFilename );
  in >> width >> height;
  this->allocPixel ( width, height, _memoryLayout );

  for ( unsigned int x = 0; x < width; ++x ) {
    for ( unsigned int y = 0; y < height; ++y ) {
      P value;
      in >> value;
      this->operator() ( x,y ) = value;
    }
  }
  in.close();
}

template<class P>
void ImageT<P>::readRaw ( const std::string& rawFilename,
                          const GrayColorImageCommonImplementation::MemoryLayout _memoryLayout ) {
  readRaw ( rawFilename.c_str(), _memoryLayout );
}

template<class P>
void ImageT<P>::writePGM ( const char* pgmFileName ) const {
  // not in generic implementation (-> specialization in ImageT.cpp)
  fthrow ( ImageException,
           "ImageT<P> writePGM currently supported for ImageT<Ipp8u> only." );
}
template<>
void ImageT<Ipp8u>::writePGM ( const char* pgmFileName ) const;

template<class P>
void ImageT<P>::writePGM ( const std::string& pgmFilename ) const {
  writePGM ( pgmFilename.c_str() );
}

template<class P>
void ImageT<P>::writeRaw ( const char* rawFilename ) const {
  std::ofstream out ( rawFilename );
  unsigned int width = this->width();
  unsigned int height = this->height();
  out << width << " " << height << std::endl;
  for ( unsigned int x = 0; x < width; ++x ) {
    for ( unsigned int y = 0; y < height; ++y ) {
      out << this->operator() ( x, y ) << " ";
    }
    out << std::endl;
  }
  out.close();
}

template<class P>
void ImageT<P>::writeRaw ( const std::string& rawFilename ) const {
  writeRaw ( rawFilename.c_str() );
}

template<class P>
void ImageT<P>::writeColored ( const ImageFile &file ) const {
  std::auto_ptr<ColorImageT<Ipp8u> > colored ( signedImageToRGB ( *this, NULL ) );
  file.writer ( dynamic_cast<GrayColorImageCommonImplementationT<Ipp8u> *> ( colored.get() ) );
}

//template<class P>
//void ImageT<P>::writeColored(const ImageFile &file) const
//{
//    file.writer(this);
//}
//template <>
//void ImageT<Ipp32f>::writeColored(const ImageFile &file) const;
//template <>
//void ImageT<Ipp16s>::writeColored(const ImageFile &file) const;

// Drawable

template<class P>
void ImageT<P>::draw ( Drawable<P> &drawable ) {
  drawable.draw ( *this );
}

template<class P>
template<typename DrawableIterator>
void ImageT<P>::drawIter ( const DrawableIterator begin, const DrawableIterator end ) {
  DrawableIterator it = begin;
  for ( ; it != end; it++ )
    it->draw ( *this );
}

template<class P>
template<typename DrawableIterator>
void ImageT<P>::drawIter ( const DrawableIterator begin, size_t number ) {
  DrawableIterator it = begin;
  for ( size_t i = 0; i < number; i++, it++ )
    it->draw ( *this );
}

template<class P>
void ImageT<P>::draw ( Drawable<P> &drawable, const P& gray ) {
  drawable.draw ( *this, gray );
}

template<class P>
template<typename DrawableIterator>
void ImageT<P>::drawIter ( const DrawableIterator begin, const DrawableIterator end, const P& gray ) {
  DrawableIterator it = begin;
  for ( ; it != end; it++ )
    it->draw ( *this, gray );
}

template<class P>
template<typename DrawableIterator>
void ImageT<P>::drawIter ( const DrawableIterator begin, size_t number, const P& gray ) {
  DrawableIterator it = begin;
  for ( size_t i = 0; i < number; i++, it++ )
    it->draw ( *this, gray );
}

template<class P> inline bool ImageT<P>::operator== ( const ImageT<P>& g ) const {
  if ( this->height() != g.height() || this->width() != g.width() ) {
    fthrow ( ImageException, "ImageT<P> width and height does not match" );
  } else if ( this->width() == 0 || this->height() == 0 ) {
    return true;
  }

  const P* pSrc1, *pSrc2;
  for ( int i = 0; i < this->height(); ++i ) {
    pSrc1 = this->getPixelPointerY ( i );
    pSrc2 = g.getPixelPointerY ( i );

    for ( int j = 0; j < this->width(); ++j, ++pSrc1, ++pSrc2 )
      if ( *pSrc1 != *pSrc2 )
        return false;
  }

  return true;
}

template<class P> inline bool ImageT<P>::operator!= ( const ImageT<P>& g ) const {
  return ! ( this->operator== ( g ) );
}

template<class P> inline bool ImageT<P>::operator== ( const ColorT<P> &color ) const {
  P* pSrc;
  for ( int i = 0; i < this->height(); ++i ) {
    pSrc = this->getPixelPointerY ( i );
    for ( int j = 0; j < this->width(); ++j, ++pSrc )
      if ( color != *pSrc )
        return false;
  }

  return true;
}

template<class P> inline bool ImageT<P>::operator!= ( const ColorT<P> &color ) const {
  return ! ( this->operator== ( color ) );
}

template<class P> inline bool ImageT<P>::operator== ( P color ) const {
  for ( int i = 0; i < this->height(); i++ )
    for ( int j = 0; j < this->width(); j++ )
      if ( this->getPixelQuick ( j, i ) != color )
        return false;

  return true;
}

template<class P> inline bool ImageT<P>::operator!= ( P color ) const {
  return ! ( this->operator== ( color ) );
}

} // namespace
