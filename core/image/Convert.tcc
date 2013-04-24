
#include "core/image/Convert.h"
#include <iostream>
#include <limits>
#include "core/image/ColorImageT.h"
#include <core/basics/tools.h>

namespace NICE {

template<class P>
ImageT<P>* rgbToGray(const ColorImageT<P>& src, ImageT<P>* dst,
                         const ImageT<int>* rgbToGrayLUT)
{
    ImageT<P>* result = createResultBuffer(src.width(), src.height(), dst);

    #ifdef NICE_USELIB_IPP
        UNUSED_PARAMETER(rgbToGrayLUT);
        IppStatus ret = ippiRGBToGray_C3C1R(src.getPixelPointer(), src.getStepsize(),
                                            result->getPixelPointer(), result->getStepsize(),
                                            makeROIFullImage(src));

        if(ret!=ippStsNoErr)
            fthrow(ImageException, ippGetStatusString(ret));

    #else // NICE_USELIB_IPP
        const P *pSrc;
              P *pDst;
        // use lut if given
        if(sizeof(P)==1 && rgbToGrayLUT!=NULL)
            for(int y=0; y<result->height(); ++y) {
                pSrc = src.getPixelPointerY(y);
                pDst = result->getPixelPointerY(y);
                for (int x=0; x<result->width(); ++x,pSrc+=3,++pDst)
                    *pDst = static_cast<P>( rgbToGrayLUT->getPixelQuick(static_cast<int>(*pSrc),0) +
                                            rgbToGrayLUT->getPixelQuick(static_cast<int>(*(pSrc+1)),1) +
                                            rgbToGrayLUT->getPixelQuick(static_cast<int>(*(pSrc+2)),2) );
            }
        // else calculate values
        else
            for(int y=0; y<result->height(); ++y) {
                pSrc = src.getPixelPointerY(y);
                pDst = result->getPixelPointerY(y);
                for(int i=0; i<result->width(); ++i,pSrc+=3,++pDst)
                    *pDst = static_cast<P>(*pSrc*0.299+*(pSrc+1)*0.587+*(pSrc+2)*0.114);
            }
    #endif // NICE_USELIB_IPP

    return result;
}

template<class P>
ColorImageT<P>* grayToRGB(const ImageT<P>& src, ColorImageT<P>* dst)
{
    ColorImageT<P>* result = createResultBuffer(src.width(), src.height(), dst);

    #ifdef NICE_USELIB_IPP
        const P* buf[3];
        for(int i=0; i<=2; ++i)
            buf[i] = src.getPixelPointer();

        IppStatus ret = ippiCopy_P3C3R(buf, src.getStepsize(),
                                       result->getPixelPointer(), result->getStepsize(),
                                       makeROIFullImage(src));

        if(ret!=ippStsNoErr)
            fthrow(ImageException, ippGetStatusString(ret));

    #else // NICE_USELIB_IPP
        int i;

        const P* pSrcStart = src.getPixelPointer();
        P*  pDstStart      = result->getPixelPointer();

        // FIXME only works if getStepsize() is a multiple of sizeof(P)
        //       (same problem probably in many other functions)
        //       however, without IPP, this is usually ok (no guarantees, however)
        int sStep = src.getStepsize()/sizeof(P);
        int dStep = result->getStepsize()/sizeof(Ipp32f);

        const P* pSrc;
              P* pDst;
        for (int y=0; y<result->height(); ++y) {
            pSrc = pSrcStart;
            pDst = pDstStart;

            for (int x=0; x<result->width(); ++x,++pSrc) {
                i=3;
                do {
                    *pDst = *pSrc;
                    ++pDst;
                    --i;
                } while(i!=0);
            }

            pSrcStart += sStep;
            pDstStart += dStep;
        }
    #endif // NICE_USELIB_IPP

    return(result);
}


template<class P>
void matrixToPseudoColor ( const NICE::MatrixT<P> & m, NICE::ColorImage & img )
{
  img.resize ( m.cols(), m.rows() );
  double max = - std::numeric_limits<double>::max();
  double min = std::numeric_limits<double>::max();
  for ( size_t x = 0 ; x < ( size_t ) m.cols(); x++ )
    for ( size_t y = 0 ; y < ( size_t ) m.rows() ; y++ )
    {
      if ( m ( y, x ) > max ) max = m ( y, x );
      if ( m ( y, x ) < min ) min = m ( y, x );
    }
  for ( size_t y = 0 ; y < ( size_t ) m.rows() ; y++ )
    for ( size_t x = 0 ; x < ( size_t ) m.cols(); x++ )
    {
      double val = ( m ( y, x ) - min ) / ( max - min );
      double r, g, b;
      convertToPseudoColor ( val, r, g, b );
      img.setPixel ( x, y, 0, ( int ) ( r*255 ) );
      img.setPixel ( x, y, 1, ( int ) ( g*255 ) );
      img.setPixel ( x, y, 2, ( int ) ( b*255 ) );
    }
}

template<class P>
void imageToPseudoColor ( const NICE::ImageT<P> & src, NICE::ColorImage & img )
{
  img.resize ( src.width(), src.height() );

  // determine maximum and minimum value in the source image
  // for appropiate scaling
  double max = - std::numeric_limits<double>::max();
  double min = std::numeric_limits<double>::max();
  for ( size_t x = 0 ; x < ( size_t ) src.width(); x++ )
    for ( size_t y = 0 ; y < ( size_t ) src.height() ; y++ )
    {
      double v = src.getPixel ( x, y );
      if ( v > max ) max = v;
      if ( v < min ) min = v;
    }

  for ( size_t y = 0 ; y < ( size_t ) src.height() ; y++ )
    for ( size_t x = 0 ; x < ( size_t ) src.width(); x++ )
    {
      // scale the grayvalue
      double val = ( src.getPixel ( x, y ) - min ) / ( max - min );
      double r, g, b;
      // determine the RGB values
      convertToPseudoColor ( val, r, g, b );
      img.setPixel ( x, y, 0, ( int ) ( r*255 ) );
      img.setPixel ( x, y, 1, ( int ) ( g*255 ) );
      img.setPixel ( x, y, 2, ( int ) ( b*255 ) );
    }
}

template<class P>
void imageToPseudoColorWithRangeSpecification ( const NICE::ImageT<P> & src, NICE::ColorImage & img, const double & _min, const double & _max )
{
  img.resize ( src.width(), src.height() );

  double max ( _max );
  double min ( _min );

  //consistency check
  if (max < min )
  {
    min = max;
    max = _min;
  }
  
  //to avoid division by numerical zero
  double rangeSpecified ( fabs(max - min) );
  if ( rangeSpecified < 10e-10 )
  { 
    max = min + 10e-10;
    rangeSpecified = fabs(max - min);
  }

  for ( size_t y = 0 ; y < ( size_t ) src.height() ; y++ )
    for ( size_t x = 0 ; x < ( size_t ) src.width(); x++ )
    {
      // scale the grayvalue
      double val = ( src.getPixel ( x, y ) - min );
      val = std::max( val , min ); // check for lower bound
      val = std::min( val , max ); //check for upper bound
      val /= rangeSpecified; //appropriate scaling
      double r, g, b;
      // determine the RGB values
      convertToPseudoColor ( val, r, g, b );
      img.setPixel ( x, y, 0, ( int ) ( r*255 ) );
      img.setPixel ( x, y, 1, ( int ) ( g*255 ) );
      img.setPixel ( x, y, 2, ( int ) ( b*255 ) );
    }
}


template<class P>
FloatImage* grayToFloat(const ImageT<P>& src, FloatImage* dst)
{
    FloatImage* result = createResultBuffer(src.width(), src.height(), dst);

    #ifdef NICE_USELIB_IPP
        IppStatus ret = ippiConvert_C1R(src.getPixelPointer(), src.getStepsize(),
                                        result->getPixelPointer(), result->getStepsize(),
                                        makeROIFullImage(src));

        if(ret!=ippStsNoErr)
                    fthrow(ImageException, ippGetStatusString(ret));

    #else
        const P* pSrcStart = src.getPixelPointer();
        Ipp32f*  pDstStart = result->getPixelPointer();

        int sStep = src.getStepsize()/sizeof(P);
        int dStep = result->getStepsize()/sizeof(Ipp32f);

        const P           *pSrc;
        FloatImage::Pixel *pDst;
        for(int y=0; y<src.height(); ++y) {
            pSrc = pSrcStart;
            pDst = pDstStart;

            for(int x=0; x<src.width(); ++x,++pSrc,++pDst)
                *pDst = *pSrc;

            pSrcStart += sStep;
            pDstStart += dStep;
        }
    #endif // NICE_USELIB_IPP

    return result;
}

template<class P>
ImageT<P>* floatToGray(const FloatImage& src, ImageT<P>* dst, IppRoundMode roundMode)
{
    ImageT<P>* result = createResultBuffer(src, dst);

    #ifdef NICE_USELIB_IPP
        IppStatus ret = ippiConvert_C1R(src.getPixelPointer(), src.getStepsize(),
                                        result->getPixelPointer(), result->getStepsize(),
                                        makeROIFullImage(src), roundMode);

        if(ret!=ippStsNoErr)
                    fthrow(ImageException, ippGetStatusString(ret));

    #else
        const Ipp32f* pSrcStart = src.getPixelPointer();
        P*  pDstStart           = result->getPixelPointer();

        int sStep = src.getStepsize()/sizeof(Ipp32f);
        int dStep = result->getStepsize()/sizeof(P);

        const Ipp32f* pSrc;
        P*            pDst;
        for(int y=0; y<src.height(); ++y) {
            pSrc = pSrcStart;
            pDst = pDstStart;

            for(int x=0; x<src.width(); ++x,++pSrc,++pDst)
                if(*pSrc < std::numeric_limits<P>::min())
                    *pDst = std::numeric_limits<P>::min();
                else if(*pSrc > std::numeric_limits<P>::max())
                    *pDst = std::numeric_limits<P>::max();
                else
                    if(roundMode == ippRndZero)
                        *pDst = static_cast<P>(*pSrc);
                    else
                        *pDst = static_cast<P>(round(*pSrc));

            pSrcStart += sStep;
            pDstStart += dStep;
        }
    #endif // NICE_USELIB_IPP

    return result;
}





// bitdepth conversion without scaling
template<class P1, class P2>
ImageT<P2>* convertBitDepth(const ImageT<P1>& src, ImageT<P2>* dst)
{
    ImageT<P2>* result = createResultBuffer(src.width(), src.height(), dst);

    #ifdef NICE_USELIB_IPP
        IppStatus ret = ippiConvert_C1R(src.getPixelPointer(), src.getStepsize(),
                                        result->getPixelPointer(), result->getStepsize(),
                                        makeROIFullImage(src));

        if(ret!=ippStsNoErr)
            fthrow(ImageException, ippGetStatusString(ret));

    #else // NICE_USELIB_IPP
        const P1* pSrc;
              P2* pDst;

        if(sizeof(P1)<sizeof(P2))
            for(int y=0; y<src.height(); ++y) {
                pSrc = src.getPixelPointerY(y);
                pDst = result->getPixelPointerY(y);
                for(int x=0; x<src.width(); ++x,++pSrc,++pDst)
                    *pDst = static_cast<P2>(*pSrc);
            }
        else
            for(int y=0; y<src.height(); ++y) {
                pSrc = src.getPixelPointerY(y);
                pDst = result->getPixelPointerY(y);
                for(int x=0; x<src.width(); ++x,++pSrc,++pDst)
                    if(*pSrc < std::numeric_limits<P2>::min())
                        *pDst = std::numeric_limits<P2>::min();
                    else if(*pSrc > std::numeric_limits<P2>::max())
                        *pDst = std::numeric_limits<P2>::max();
                    else
                        *pDst = static_cast<P2>(round(*pSrc));
            }
    #endif // NICE_USELIB_IPP

    return result;
}

// specialication for convertBitDepth to decrease bitdepth from 32f to 8u/8s/16u/16s
template<class P>
ImageT<P>* convertBitDepth(const ImageT<Ipp32f>& src, ImageT<P>* dst)
{
    ImageT<P>* result = createResultBuffer(src.width(), src.height(), dst);

    #ifdef NICE_USELIB_IPP
        if(sizeof(Ipp32f)<sizeof(P))
            fthrow(ImageException,"Conversion not supported by IPP.");

        IppStatus ret = ippiConvert_C1R(src.getPixelPointer(), src.getStepsize(),
                                        result->getPixelPointer(), result->getStepsize(),
                                        makeROIFullImage(src), ippRndNear);

        if(ret!=ippStsNoErr)
            fthrow(ImageException, ippGetStatusString(ret));

    #else // NICE_USELIB_IPP
        const FloatImage::Pixel* pSrc;
        P*                       pDst;

        if(sizeof(Ipp32f)<sizeof(P))
            for(int y=0; y<src.height(); ++y) {
                pSrc = src.getPixelPointerY(y);
                pDst = result->getPixelPointerY(y);
                for(int x=0; x<src.width(); ++x,++pSrc,++pDst)
                    *pDst = static_cast<P>(*pSrc);
            }
        else
            for(int y=0; y<src.height(); ++y) {
                pSrc = src.getPixelPointerY(y);
                pDst = result->getPixelPointerY(y);
                for(int x=0; x<src.width(); ++x,++pSrc,++pDst)
                    if(*pSrc < std::numeric_limits<P>::min())
                        *pDst = std::numeric_limits<P>::min();
                    else if(*pSrc > std::numeric_limits<P>::max())
                        *pDst = std::numeric_limits<P>::max();
                    else
                        *pDst = static_cast<P>(round(*pSrc));
            }
    #endif // NICE_USELIB_IPP

    return result;
}

// bitdepth conversion without scaling

template<class P1, class P2>
ColorImageT<P2>* convertBitDepth(const ColorImageT<P1>& src, ColorImageT<P2>* dst)
{
    ColorImageT<P2>* result = createResultBuffer(src.width(), src.height(), dst);

    #ifdef NICE_USELIB_IPP
        IppStatus ret = ippiConvert_C3R(src.getPixelPointer(), src.getStepsize(),
                                        result->getPixelPointer(), result->getStepsize(),
                                        makeROIFullImage(src));

        if(ret!=ippStsNoErr)
            fthrow(ImageException, ippGetStatusString(ret));

  #else // NICE_USELIB_IPP
        const P1* pSrc;
              P2* pDst;
        if(sizeof(P1)<sizeof(P2))
            for(int y=0; y<src.height(); ++y) {
                pSrc = src.getPixelPointerY(y);
                pDst = result->getPixelPointerY(y);
                for(int x=0; x<3*src.width(); ++x,++pSrc,++pDst)
                    *pDst = static_cast<P2>(*pSrc);
            }
        else
            for(int y=0; y<src.height(); ++y) {
                pSrc = src.getPixelPointerY(y);
                pDst = result->getPixelPointerY(y);
                for(int x=0; x<3*src.width(); ++x,++pSrc,++pDst)
                    if(*pSrc < std::numeric_limits<P2>::min())
                        *pDst = std::numeric_limits<P2>::min();
                    else if(*pSrc > std::numeric_limits<P2>::max())
                        *pDst = std::numeric_limits<P2>::max();
                    else
                        *pDst = static_cast<P2>(round(*pSrc));
            }
    #endif // NICE_USELIB_IPP

    return result;
}

// specialication for convertBitDepth to decrease bitdepth from 32f to 8u/8s/16u/16s
template<class P>
ColorImageT<P>* convertBitDepth(const ColorImageT<Ipp32f> &src, ColorImageT<P>* dst)
{
   ColorImageT<P>* result = createResultBuffer(src.width(), src.height(), dst);

    #ifdef NICE_USELIB_IPP
        if(sizeof(Ipp32f)<sizeof(P))
            fthrow(ImageException,"Conversion not supported by IPP.");

        IppStatus ret = ippiConvert_C3R(src.getPixelPointer(), src.getStepsize(),
                                        result->getPixelPointer(), result->getStepsize(),
                                        makeROIFullImage(src), ippRndNear);

        if(ret!=ippStsNoErr)
            fthrow(ImageException, ippGetStatusString(ret));

  #else // NICE_USELIB_IPP
        const Ipp32f* pSrc;
        P*            pDst;

        if(sizeof(Ipp32f)<sizeof(P))
            for(int y=0; y<src.height(); ++y) {
                pSrc = src.getPixelPointerY(y);
                pDst = result->getPixelPointerY(y);
                for(int x=0; x<3*src.width(); ++x,++pSrc,++pDst)
                    *pDst = static_cast<P>(*pSrc);
            }
        else
            for(int y=0; y<src.height(); ++y) {
                pSrc = src.getPixelPointerY(y);
                pDst = result->getPixelPointerY(y);
                for(int x=0; x<3*src.width(); ++x,++pSrc,++pDst)
                    if(*pSrc < std::numeric_limits<P>::min())
                        *pDst = std::numeric_limits<P>::min();
                    else if(*pSrc > std::numeric_limits<P>::max())
                        *pDst = std::numeric_limits<P>::max();
                    else
                        *pDst = static_cast<P>(round(*pSrc));
            }
    #endif // NICE_USELIB_IPP

    return result;
}





template<class P>
ImageT<P>* scale(const ImageT<P>& src, ImageT<P>* dst, double xFactor, double yFactor, int interpolation)
{
    #ifdef NICE_USELIB_IPP
        IppiRect rect = makeRectFullImage(src);

        IppiSize dstSize;
        if(isZero(xFactor) && dst!=NULL) {
                dstSize.width = dst->width();
                xFactor=dst->width()/(double)src.width();
        } else
                dstSize.width = (int) ceil ((double) src.width () * xFactor);

        if(isZero(yFactor) && dst!=NULL) {
                dstSize.height = dst->height();
                yFactor=dst->height()/(double)src.height();
        } else
                dstSize.height = (int) ceil ((double)src.height () * yFactor);

        ImageT<P> * result = createResultBuffer(dstSize.width, dstSize.height, dst);

        IppStatus ret = ippiResize_C1R(src.getPixelPointer(), makeROIFullImage(src),  src.getStepsize(), rect,
                                       result->getPixelPointer(), result->getStepsize(),
                                       dstSize, xFactor, yFactor, interpolation);

        if(ret!=ippStsNoErr)
            fthrow(ImageException, ippGetStatusString(ret));

        return result;
    #else // NICE_USELIB_IPP
        fthrow(ImageException,"Not yet supported without IPP.");
    #endif // NICE_USELIB_IPP
}

template<class P>
ColorImageT<P>* scale(const ColorImageT<P>& src, ColorImageT<P>* dst, double xFactor, double yFactor, int interpolation)
{
    #ifdef NICE_USELIB_IPP
        IppiRect rect = makeRectFullImage(src);

        IppiSize dstSize;
        if(isZero(xFactor) && dst!=NULL) {
                dstSize.width = dst->width();
                xFactor=dst->width()/(double)src.width();
        } else
                dstSize.width = (int) ceil ((double) src.width () * xFactor);
        if(isZero(yFactor) && dst!=NULL) {
                dstSize.height = dst->height();
                yFactor=dst->height()/(double)src.height();
        } else
                dstSize.height = (int) ceil ((double)src.height () * yFactor);

        ColorImageT<P> * result = createResultBuffer(dstSize.width, dstSize.height, dst);

        IppStatus ret = ippiResize_C3R(src.getPixelPointer(), makeROIFullImage(src),  src.getStepsize(), rect,
                                       result->getPixelPointer(), result->getStepsize(), dstSize,
                                       xFactor, yFactor, interpolation);

        if(ret!=ippStsNoErr)
            fthrow(ImageException, ippGetStatusString(ret));

        return result;
    #else // NICE_USELIB_IPP
        fthrow(ImageException,"Not yet supported without IPP.");
    #endif // NICE_USELIB_IPP
}


template<class P>
ColorImageT<Ipp8u>* signedImageToRGB(const ImageT<P>& image,
                                        ColorImageT<Ipp8u>* colored) {
  //fthrow(ImageException, "signedImageToRGB() not supported for this pixel type");
  ColorImageT<Ipp8u> *result = createResultBuffer(image, colored);

  P vmin;
  P vmax;
  image.minmax(vmin, vmax);
  const P scale = std::max(vmax, static_cast<P>(-vmin));
  const Ipp8u black[3] = {0,0,0};
  *result = black;
  if (vmax == 0) {
    return result;
  }

  // FIXME not efficient
  for (int y = 0; y < image.height(); y++) {
    for (int x = 0; x < image.width(); x++) {
      const P pixel = image.getPixel(x, y);
      if (pixel < P(0)) {
        const Ipp8u newPixel = static_cast<Ipp8u>(-pixel * P(255) / scale);
        (*result)(x,y,0) = newPixel;
      } else {
        const Ipp8u newPixel = static_cast<Ipp8u>(pixel * P(255) / scale);
        (*result)(x,y,0) = newPixel;
        (*result)(x,y,1) = newPixel;
        (*result)(x,y,2) = newPixel;
      }
    }
  }

  return result;
}

} // namespace
