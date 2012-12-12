
#include "core/image/Convert.h"

using namespace std;

namespace NICE {

ColorImage* rgbToHSV(const ColorImage& src, ColorImage* dst)
{
    ColorImage* result = createResultBuffer(src, dst);

    #ifdef NICE_USELIB_IPP
        IppStatus ret = ippiRGBToHSV_8u_C3R(src.getPixelPointer(), src.getStepsize(),
                                            result->getPixelPointer(), result->getStepsize(),
                                            makeROIFullImage(src));

        if(ret!=ippStsNoErr)
            fthrow(ImageException, ippGetStatusString(ret));

    #else // NICE_USELIB_IPP
        double min,max,diff,  r,g,b,  h;

        const Ipp8u* pSrcStart = src.getPixelPointer();
        Ipp8u* pDstStart       = result->getPixelPointer();

        const Ipp8u* pSrc;
              Ipp8u* pDst;
        for(int y=0; y<src.height(); ++y) {
            pSrc = pSrcStart;
            pDst = pDstStart;

            for(int x=0; x<src.width(); ++x) {
                r   = *pSrc/255.0; ++pSrc;
                g   = *pSrc/255.0; ++pSrc;
                b   = *pSrc/255.0; ++pSrc;

                min  = std::min(g,b);
                min  = std::min(r, min);

                max  = std::max(g,b);
                max  = std::max(r, max);

                diff = max-min;

                // H
                h = 0;
                if(diff!=0) {
                    if(max==r)      { h = ((g-b)/diff    )*60; }
                    else if(max==g) { h = ((b-r)/diff + 2)*60; }
                    else if(max==b) { h = ((r-g)/diff + 4)*60; }
				}
                h += (h<0)?360:0;

                *pDst = static_cast<unsigned char>(h*17/24);                   ++pDst; // *255/360
                *pDst = static_cast<unsigned char>((max==0)?0:(diff*255)/max); ++pDst;
                *pDst = static_cast<unsigned char>(max*255);                   ++pDst; // v = max;
            }

            pSrcStart += src.getStepsize();
            pDstStart += result->getStepsize();
        }
    #endif // NICE_USELIB_IPP

    return result;
}

ColorImage* hsvToRGB(const ColorImage& src, ColorImage* dst)
{
    ColorImage* result = createResultBuffer(src.width(), src.height(), dst);

    #ifdef NICE_USELIB_IPP
        IppStatus ret = ippiHSVToRGB_8u_C3R(src.getPixelPointer(), src.getStepsize(),
                                            result->getPixelPointer(), result->getStepsize(),
                                            makeROIFullImage(src));

        if(ret!=ippStsNoErr)
            fthrow(ImageException, ippGetStatusString(ret));

    #else // NICE_USELIB_IPP
        double h,s,v, r,g,b, k,m,n, f;
        int    i;

        const Ipp8u* pSrcStart = src.getPixelPointer();
        Ipp8u* pDstStart       = result->getPixelPointer();

        const ColorImage::Pixel* pSrc;
              ColorImage::Pixel* pDst;
        for(int y=0; y<src.height(); ++y) {
            pSrc = pSrcStart;
            pDst = pDstStart;

            for(int x=0; x<src.width(); ++x) {
                h   =(*pSrc/255.0)*360; ++pSrc;
                s   = *pSrc/255.0;      ++pSrc;
                v   = *pSrc/255.0;      ++pSrc;

                r = g = b = v; // default case if s==0

                if(s!=0) {
                    h = (h==360)?0:h/60;

                    i = static_cast<int>(h);
                    f = h-i;
                    m = v*(1-s);
                    n = v*(1-s*f);
                    k = v*(1-s*(1-f));

                    switch(i) {
                        case 0: r = v; g = k; b = m; break;
                        case 1: r = n; g = v; b = m; break;
                        case 2: r = m; g = v; b = k; break;
                        case 3: r = m; g = n; b = v; break;
                        case 4: r = k; g = m; b = v; break;
                        case 5: r = v; g = m; b = n; break;
                    }
                }

                *pDst = static_cast<Ipp8u>(r*255); ++pDst;
                *pDst = static_cast<Ipp8u>(g*255); ++pDst;
                *pDst = static_cast<Ipp8u>(b*255); ++pDst;
            }

            pSrcStart += src.getStepsize();
            pDstStart += result->getStepsize();
       }
    #endif // NICE_USELIB_IPP

    return(result);
}

ColorImage* rgbToYUV(const ColorImage& src, ColorImage* dst)
{
    ColorImage* result = createResultBuffer(src.width(), src.height(), dst);

    #ifdef NICE_USELIB_IPP
        IppStatus ret = ippiRGBToYUV_8u_C3R(src.getPixelPointer(), src.getStepsize(),
                                            result->getPixelPointer(), result->getStepsize(),
                                            makeROIFullImage(src));

        if(ret!=ippStsNoErr)
            fthrow(ImageException, ippGetStatusString(ret));

    #else // NICE_USELIB_IPP
        double r,g,b, y,u,v;

        const Ipp8u* pSrcStart = src.getPixelPointer();
        Ipp8u* pDstStart       = result->getPixelPointer();

        const ColorImage::Pixel* pSrc;
              ColorImage::Pixel* pDst;
        for(int ty=0; ty<src.height(); ++ty) {
            pSrc = pSrcStart;
            pDst = pDstStart;

            for(int tx=0; tx<src.width(); ++tx) {
                r = *pSrc/255.0; ++pSrc;
                g = *pSrc/255.0; ++pSrc;
                b = *pSrc/255.0; ++pSrc;

                y = 0.299*r + 0.587*g + 0.114*b;
                u = 0.492*(b-y);
                v = 0.877*(r-y);

                v+= 0.5;
                v = std::max(0.0, v);
                v = std::min(1.0, v);

                *pDst = static_cast<Ipp8u>(y*255);       ++pDst;
                *pDst = static_cast<Ipp8u>((u+0.5)*255); ++pDst;
                *pDst = static_cast<Ipp8u>(v*255);       ++pDst;
            }

            pSrcStart += src.getStepsize();
            pDstStart += result->getStepsize();
        }
    #endif // NICE_USELIB_IPP

    return result;
}

ColorImage* yuvToRGB(const ColorImage& src, ColorImage* dst)
{
    ColorImage* result = createResultBuffer(src.width(), src.height(), dst);

    #ifdef NICE_USELIB_IPP
        IppStatus ret = ippiYUVToRGB_8u_C3R(src.getPixelPointer(), src.getStepsize(),
                                            result->getPixelPointer(), result->getStepsize(),
                                            makeROIFullImage(src));

        if(ret!=ippStsNoErr)
                fthrow(ImageException, ippGetStatusString(ret));

    #else // NICE_USELIB_IPP
        double y,u,v, r,g,b;

        const Ipp8u* pSrcStart = src.getPixelPointer();
        Ipp8u* pDstStart       = result->getPixelPointer();

        const ColorImage::Pixel* pSrc;
              ColorImage::Pixel* pDst;
        for(int ty=0; ty<src.height(); ++ty) {
            pSrc = pSrcStart;
            pDst = pDstStart;

            for(int tx=0; tx<src.width(); ++tx) {
                y = *pSrc/255.0;     ++pSrc;
                u = *pSrc/255.0-0.5; ++pSrc;
                v = *pSrc/255.0-0.5; ++pSrc;

                r = y + 1.140*v;
                g = y - 0.394*u - 0.581*v;
                b = y + 2.032*u;

                r = std::min(1.0, r);
                r = std::max(0.0, r);

                g = std::min(1.0, g);
                g = std::max(0.0, g);

                b = std::min(1.0, b);
                b = std::max(0.0, b);

                *pDst = static_cast<Ipp8u>(r*255); ++pDst;
                *pDst = static_cast<Ipp8u>(g*255); ++pDst;
                *pDst = static_cast<Ipp8u>(b*255); ++pDst;
            }

            pSrcStart += src.getStepsize();
            pDstStart += result->getStepsize();
        }
    #endif // NICE_USELIB_IPP

    return result;
}





// create a LUT for rgbToGray conversion
ImageT<int>* rgbToGrayLUT()
{
    ImageT<int>* result = new ImageT<int>(256,3);

    for(int i=0; i<256; ++i) {
        result->setPixelQuick(i,0, static_cast<int>(0.299*i));
        result->setPixelQuick(i,1, static_cast<int>(0.587*i));
        result->setPixelQuick(i,2, static_cast<int>(0.114*i));
    }

    return result;
}





// float-rgb conversion
FloatImage* rgbToFloat(const ColorImage& src, FloatImage* dst)
{
    FloatImage* result = createResultBuffer(src.width()*3, src.height(), dst);

    #ifdef NICE_USELIB_IPP
        IppStatus ret = ippiConvert_8u32f_C3R(src.getPixelPointer(), src.getStepsize(),
                                              result->getPixelPointer(), result->getStepsize(),
                                              makeROIFullImage(src));

        if(ret!=ippStsNoErr)
            fthrow(ImageException, ippGetStatusString(ret));

    #else
        const ColorImage::Pixel* pSrc;
              FloatImage::Pixel* pDst;
        for(int y=0; y<src.height(); ++y) {
            pSrc = src.getPixelPointerY(y);
            pDst = result->getPixelPointerY(y);
            for(int x=0; x<3*src.width(); ++x,++pSrc,++pDst)
                *pDst = static_cast<Ipp32f>(*pSrc);
        }
    #endif

    return result;
}





Image* floatToGrayScaled(const FloatImage& src, Ipp32f fmin, Ipp32f fmax, Image* dst)
{
    Image* result = createResultBuffer(src.width(), src.height(), dst);

    #ifdef NICE_USELIB_IPP
        IppStatus ret = ippiScale_C1R(src.getPixelPointer(), src.getStepsize(),
                                      result->getPixelPointer(), result->getStepsize(),
                                      makeROIFullImage(src), fmin, fmax);

        if(ret!=ippStsNoErr)
            fthrow(ImageException, ippGetStatusString(ret));

    #else // NICE_USELIB_IPP
        double k = 255/(fmax-fmin);

        const Ipp32f* pSrc;
              Ipp8u*  pDst;
        for(int y=0; y<src.height(); ++y) {
            pSrc = src.getPixelPointerY(y);
            pDst = result->getPixelPointerY(y);
            for(int x=0; x<src.width(); ++x,++pSrc,++pDst)
                *pDst = static_cast<Ipp8u>(k*(*pSrc-fmin));
        }
    #endif // NICE_USELIB_IPP

    return result;
}

Image* floatToGrayScaled(const FloatImage& src, Image* dst)
{
    Ipp32f fmin, fmax;
    src.minmax(fmin, fmax);

    // make sure fmin is not equal to fmax
    if (isEqual(fmin, fmax, 1e-6f)) {
      fmax = fmin + 1.0f;
    }

    return floatToGrayScaled(src, fmin, fmax, dst);
}





Image* remap(const Image& src, const FloatImage &px, const FloatImage &py, Image* dst, int interpolation)
{
  #ifdef NICE_USELIB_IPP
        Image * result = createResultBuffer(src.width(), src.height(), dst);

        Image gi(src);
        *(gi.getPixelPointerY(0)) = 0;

    IppStatus ret = ippiRemap_8u_C1R(gi.getPixelPointer(), makeROIFullImage(src), gi.getStepsize(),
             makeRectFullImage(gi), px.getPixelPointer(), px.getStepsize(),
             py.getPixelPointer(), py.getStepsize(),
             result->getPixelPointer(), result->getStepsize(),
             makeROIFullImage(gi), interpolation);

        if(ret!=ippStsNoErr)
            fthrow(ImageException, ippGetStatusString(ret));

    return result;
  #else // NICE_USELIB_IPP
    fthrow(ImageException,"Not yet supported without IPP.");
  #endif // NICE_USELIB_IPP
}

ColorImage* remap(const ColorImage& src, const FloatImage &px, const FloatImage &py, ColorImage* dst, int interpolation)
{
  #ifdef NICE_USELIB_IPP
        ColorImage ci(src);
        ColorImage::Pixel* cursor = ci.getPixelPointerY(0);
    *cursor++ = 0;
    *cursor++ = 0;
    *cursor = 0;

        ColorImage * result = createResultBuffer(ci.width(), ci.height(), dst);

        IppStatus ret = ippiRemap_8u_C3R(ci.getPixelPointer(), makeROIFullImage(ci), ci.getStepsize(),
                                        makeRectFullImage(ci),
                                        px.getPixelPointer(), px.getStepsize(),
                                        py.getPixelPointer(), py.getStepsize(),
                                        result->getPixelPointer(), result->getStepsize(),
                                        makeROIFullImage(ci), interpolation);

        if(ret!=ippStsNoErr)
            fthrow(ImageException, ippGetStatusString(ret));

        return result;
    #else // NICE_USELIB_IPP
        fthrow(ImageException,"Not yet supported without IPP.");
    #endif // NICE_USELIB_IPP
}





Rect clipRect(const MultiChannelImageAccess& image, const Rect& rect)
{
  Rect result(rect);
  if (result.left < 0) {
    result.width += result.left;
    result.left = 0;
  }
  if (result.top < 0) {
    result.height += result.top;
    result.top = 0;
  }
  if (result.left >= image.width()) {
    result.left = image.width() - 1;
    result.width = 0;
  }
  if (result.top >= image.height()) {
    result.top = image.height() - 1;
    result.height = 0;
  }

  int maxWidth  = image.width() - result.left;
  int maxHeight = image.height() - result.top;

  if (result.width >= maxWidth) {
    result.width = maxWidth;
  }
  if (result.height >= maxHeight) {
    result.height = maxHeight;
  }

  return result;
}

IppiRect makeRectFullImage(const MultiChannelImageAccess& image)
{
   IppiRect ippiRect = {0, 0, image.width(), image.height()};
   return ippiRect;
}

IppiSize makeROIFullImage(const MultiChannelImageAccess& image)
{
    IppiSize ippiSize = {image.width(), image.height()};
    return ippiSize;
}

IppiSize makeROIRect(const MultiChannelImageAccess& image, const Rect& rect)
{
    Rect roi = clipRect(image, rect);
    IppiSize ippiSize = {roi.width, roi.height};
    return ippiSize;
}

void preventIppBug(IppiSize& ippiSize, Rect& clippedROI)
{
    // there is a bug in IPP: if ippiSize.height == 1 the function won't return
    if(ippiSize.height==1)
    {
        ippiSize.height = 2;
        if (clippedROI.top > 0)
            clippedROI.top--;
    }
    // maybe there is the same problem when ippiSize.width == 1
    if(ippiSize.width==1)
    {
        ippiSize.width = 2;
        if (clippedROI.left > 0)
            clippedROI.left--;
    }
}

void convertToPseudoColor ( double x, double & r, double & g, double & b )
{
  if ( x < 0 || x > 1 )
  {
    fthrow(Exception, "Unable to convert a value outside of [0,1] to a pseudo color.");
  }

  size_t seg = ( size_t ) ( x * 6.0 );
  double y   = ( 6 * x - seg );

  switch ( seg ) {
    case 0:
      r = 0.0;
      g = 0.0;
      b = y;
      break;
    case 1:
      r = 0.0;
      g =  y;
      b = 1.0;
      break;
    case 2:
      r = 0.0;
      g = 1.0;
      b = 1.0 - y;
      break;
    case 3:
      r =  y;
      g = 1.0;
      b = 0.0;
      break;
    case 4:
      r = 1.0;
      g = 1.0 - y;
      b = 0.0;
      break;
    case 5:
      r = 1.0;
      g = y;
      b = y;
      break;
    default:
      r = 1.0;
      g = 1.0;
      b = 1.0;
      break;
  }
}

} // namespace
