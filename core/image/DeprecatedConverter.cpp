#include "core/image/DeprecatedConverter.h"
#include <math.h>
#include <limits>
#include <core/basics/numerictools.h>

#include <sstream>
#include <iostream>
#include <core/basics/Log.h>
using namespace std;

namespace NICE {

#ifndef NICE_USELIB_IPP
  // lookup tables for rgb -> gray colour transform
  bool DeprecatedConverter::pLut_initialized=false;
  int DeprecatedConverter::pLutRg[256];
  int DeprecatedConverter::pLutGg[256];
  int DeprecatedConverter::pLutBg[256];
#endif


ColorImage* DeprecatedConverter::hsvToRGB(
  const HSVColorImage& hsv, ColorImage* rgb)
{
  #ifdef NICE_USELIB_IPP
    ColorImage* result = createResultBuffer(hsv, rgb);
    IppStatus ret = ippiHSVToRGB_8u_C3R(hsv.getPixelPointer(),
                        hsv.getStepsize(),
                        result->getPixelPointer(),
                        result->getStepsize(),
                        makeROIFullImage(hsv));
    if(ret!=ippStsNoErr)
                fthrow(ImageException, ippGetStatusString(ret));
    return result;
  #else // NICE_USELIB_IPP
    fthrow(ImageException,"Not yet supported without IPP.");
  #endif // NICE_USELIB_IPP
}

HSVColorImage* DeprecatedConverter::rgbToHSV(
  const ColorImage& rgb, HSVColorImage* hsv)
{
  #ifdef NICE_USELIB_IPP
    HSVColorImage* result = createResultBuffer(rgb, hsv);
    IppStatus ret = ippiRGBToHSV_8u_C3R(rgb.getPixelPointer(),
                        rgb.getStepsize(),
                        result->getPixelPointer(),
                        result->getStepsize(),
                        makeROIFullImage(rgb));
    if(ret!=ippStsNoErr)
                fthrow(ImageException, ippGetStatusString(ret));
    return result;
  #else // NICE_USELIB_IPP
    fthrow(ImageException,"Not yet supported without IPP.");
  #endif // NICE_USELIB_IPP
}

HSVColorImage* DeprecatedConverter::rgbToHSVRegion(const ColorImage& rgb,
                                         HSVColorImage* hsv,
                                         const Rect rect) {
  #ifdef NICE_USELIB_IPP
    Rect roi = clipRect(rgb, rect);
    IppiSize ippiSize = makeROIRect(rgb, rect);
    preventIppBug(ippiSize, roi);

    HSVColorImage* result = createResultBuffer(rgb, hsv);

    if (ippiSize.width == 0 || ippiSize.height == 0) {
      return result;
    }

    Ipp8u const* src = rgb.getPixelPointerXY(roi.left, roi.top);
    Ipp8u* dest = result->getPixelPointerXY(roi.left, roi.top);
    IppStatus ret = ippiRGBToHSV_8u_C3R(src, rgb.getStepsize(),
                        dest, result->getStepsize(),
                        ippiSize);
    if(ret!=ippStsNoErr)
                fthrow(ImageException, ippGetStatusString(ret));
    return result;
  #else // NICE_USELIB_IPP
    fthrow(ImageException,"Not yet supported without IPP.");
  #endif // NICE_USELIB_IPP
}

FloatImage* DeprecatedConverter::gray16sToFloat(const GrayImage16s& gray,
                     FloatImage* fimage)
{
  #ifdef NICE_USELIB_IPP
    FloatImage* result = createResultBuffer(gray, fimage);
    IppStatus ret = ippiConvert_16s32f_C1R(gray.getPixelPointer(),
                           gray.getStepsize(),
                           result->getPixelPointer(),
                           result->getStepsize(),
                           makeROIFullImage(gray));
    if(ret!=ippStsNoErr)
                fthrow(ImageException, ippGetStatusString(ret));
    return result;
  #else // NICE_USELIB_IPP
    fthrow(ImageException,"Not yet supported without IPP.");
  #endif // NICE_USELIB_IPP
}
FloatImage* DeprecatedConverter::rgbToFloat(const ColorImage& rgb,
                              FloatImage* fimage)
{
  #ifdef NICE_USELIB_IPP
    FloatImage* result = createResultBuffer(rgb.width()*3,rgb.height(), fimage);
    IppStatus ret = ippiConvert_8u32f_C3R(rgb.getPixelPointer(),
                          rgb.getStepsize(),
                          result->getPixelPointer(),
                          result->getStepsize(),
                          makeROIFullImage(rgb));
    if(ret!=ippStsNoErr)
                fthrow(ImageException, ippGetStatusString(ret));
    return result;
  #else // NICE_USELIB_IPP
    fthrow(ImageException,"Not yet supported without IPP.");
  #endif // NICE_USELIB_IPP
}

void DeprecatedConverter::set(const unsigned char& value, Image* dst)
{
  #ifdef NICE_USELIB_IPP
    IppStatus ret = ippiSet_8u_C1R(value, dst->getPixelPointer(), dst->getStepsize(), makeROIFullImage(*dst));
    if(ret!=ippStsNoErr)
                fthrow(ImageException, ippGetStatusString(ret));
  #else // NICE_USELIB_IPP
    fthrow(ImageException,"Not yet supported without IPP.");
  #endif // NICE_USELIB_IPP
}

Image* DeprecatedConverter::remap(const Image& src, const FloatImage &px, const FloatImage &py, Image* dst, int interpolation)
{
  #ifdef NICE_USELIB_IPP
   Image gi (src);
   *(gi.getPixelPointerY(0)) = 0;
   Image * result = createResultBuffer(src.width(), src.height(), dst);
   IppStatus ret = ippiRemap_8u_C1R(gi.getPixelPointer(), makeROIFullImage(src), gi.getStepsize(), makeRectFullImage(gi),
       px.getPixelPointer(), px.getStepsize(), py.getPixelPointer(), py.getStepsize(),
       result->getPixelPointer(), result->getStepsize(), makeROIFullImage(gi), interpolation);
    if(ret!=ippStsNoErr)
                fthrow(ImageException, ippGetStatusString(ret));
    return result;
  #else // NICE_USELIB_IPP
    fthrow(ImageException,"Not yet supported without IPP.");
  #endif // NICE_USELIB_IPP
}

FloatImage* DeprecatedConverter::gradientStrength(const GrayImage16s& dx, const GrayImage16s& dy, FloatImage *buffer)
{
  #ifdef NICE_USELIB_IPP
    if( dx.width()!=dy.width() || dx.height()!=dy.height() )
        fthrow(ImageException,"DeprecatedConverter::gradientStrength input images must have same size.");
    FloatImage *result = createResultBuffer(dx.width(), dx.height(), buffer);
    FloatImage tmp(dx.width(),dx.height());
    IppiSize roi=makeROIFullImage(*result);
    IppStatus ret = ippiConvert_16s32f_C1R(dx.getPixelPointer(),
                                           dx.getStepsize(),
                                           result->getPixelPointer(),
                                           result->getStepsize(),
                                           roi);
    if(ret!=ippStsNoErr)
                fthrow(ImageException, ippGetStatusString(ret));
    ret = ippiConvert_16s32f_C1R(dy.getPixelPointer(),
                                 dy.getStepsize(),
                                 tmp.getPixelPointer(),
                                 tmp.getStepsize(),
                                 roi);
    if(ret!=ippStsNoErr)
                fthrow(ImageException, ippGetStatusString(ret));
    ret = ippiSqr_32f_C1IR(result->getPixelPointer(),
                           result->getStepsize(),
                           roi);
    if(ret!=ippStsNoErr)
                fthrow(ImageException, ippGetStatusString(ret));
    ret = ippiAddSquare_32f_C1IR(tmp.getPixelPointer(),
                                 tmp.getStepsize(),
                                 result->getPixelPointer(),
                                 result->getStepsize(),
                                 roi);
    if(ret!=ippStsNoErr)
                fthrow(ImageException, ippGetStatusString(ret));
    ret = ippiSqrt_32f_C1IR(result->getPixelPointer(),
                            result->getStepsize(),
                            roi);
    if(ret!=ippStsNoErr)
                fthrow(ImageException, ippGetStatusString(ret));
    return result;
  #else // NICE_USELIB_IPP
    fthrow(ImageException,"Not yet supported without IPP.");
  #endif // NICE_USELIB_IPP
}

Image* DeprecatedConverter::nonMaximumSuppression(const GrayImage16s& dx, const GrayImage16s& dy, const FloatImage &mag, Image *buffer)
{
//  #ifdef NICE_USELIB_IPP
    if( dx.width()!=dy.width() || dy.width() != mag.width() || dx.height()!=dy.height() || dy.height() != mag.height() )
        fthrow(ImageException,"DeprecatedConverter::nonMaximumSuppression input images must have same size.");
    int height=dx.height();
    int width=dx.width();
    Image *result = createResultBuffer(width, height, buffer);
    *result=0;
    for(int y=1;y<height-1;y++)
        for(int x=1;x<width-1;x++)

#if 0
        {

            float m=mag.getPixelQuick(x,y);
            if(m==0) {
                result->setPixelSave(x,y,0);
            }  else {
                Ipp16s gx=dx.getPixelQuick(x,y);
                Ipp16s gy=dy.getPixelQuick(x,y);
                float l1,l2,r1,r2;
                float mag1,mag2;
                float xperp = -gx/m;
                float yperp = gy/m;
                if(gx>=0) {
                    l1 = mag.getPixelQuick(x-1,y);
                    r1 = mag.getPixelQuick(x+1,y);
                    if(gy>=0) {
                        l2 = mag.getPixelQuick(x-1,y-1);
                        r2 = mag.getPixelQuick(x+1,y+1);
                        if (gx >= gy) {  // 111
                            // Left point
                            mag1 = (m - l1)*xperp + (l2 - l1)*yperp;
                            // Right point
                            mag2 = (m - r1)*xperp + (r2 - r1)*yperp;
                        } else {    // 110
                            // Left point
                            mag1 = (l1 - l2)*xperp + (l1 - m)*yperp;
                            // Right point
                            mag2 = (r1 - r2)*xperp + (r1 - m)*yperp;
                        }
                    } else {
                        l2 = mag.getPixelQuick(x-1,y+1);
                        r2 = mag.getPixelQuick(x+1,y-1);
                        if (gx >= -gy) { // 101
                            // Left point
                            mag1 = (m - l1)*xperp + (l1 - l2)*yperp;
                            // Right point
                            mag2 = (m - r1)*xperp + (r1 - r2)*yperp;
                        } else {    // 100
                            // Left point
                            mag1 = (r1 - r2)*xperp + (m - r1)*yperp;
                            // Right point
                            mag2 = (l1 - l2)*xperp + (m - l1)*yperp;
                        }
                    }
                } else {
                    if (gy >= 0) {
                        r2 = mag.getPixelQuick(x+1,y-1);
                        l2 = mag.getPixelQuick(x-1,y+1);
                        if (-gx >= gy) { // 011
                            // Left point
                            r1 = mag.getPixelQuick(x+1,y);
                            mag1 = (r1 - m)*xperp + (r2 - r1)*yperp;
                            // Right point
                            l1 = mag.getPixelQuick(x-1,y);
                            mag2 = (l1 - m)*xperp + (l2 - l1)*yperp;
                        } else { // 010
                            // Left point
                            r1 = mag.getPixelQuick(x,y-1);
                            mag1 = (r2 - r1)*xperp + (r1 - m)*yperp;
                            // Right point
                            l1 = mag.getPixelQuick(x,y+1);
                            mag2 = (l2 - l1)*xperp + (l1 - m)*yperp;
                        }
                    } else {
                        r2 = mag.getPixelQuick(x+1,y+1);
                        l2 = mag.getPixelQuick(x-1,y-1);
                        if (-gx > -gy) { // 001
                            // Left point
                            r1 = mag.getPixelQuick(x+1,y);
                            mag1 = (r1 - m)*xperp + (r1 - r2)*yperp;
                            // Right point
                            l1 = mag.getPixelQuick(x-1,y);
                            mag2 = (l1 - m)*xperp + (l1 - l2)*yperp;
                        } else { // 000
                            // Left point
                            r1 = mag.getPixelQuick(x,y+1);
                            mag1 = (r2 - r1)*xperp + (m - r1)*yperp;
                            // Right point
                            l1 = mag.getPixelQuick(x,y-1);
                            mag2 = (l2 - l1)*xperp + (m - l1)*yperp;
                        }
                    }
                }
                if ((mag1 >= 0.0) || (mag2 > 0.0))
                    result->setPixelQuick(x,y,0);
                else
                    result->setPixelQuick(x,y,255);
            }
        }
#else
    {
            if(x==17 && y==17) {
                cout << mag.getPixelQuick(x,y) << " " << dx.getPixelQuick(x,y) << " " << dy.getPixelQuick(x,y) << endl;
                cout << mag.getPixelQuick(x-1,y-1) << " " << mag.getPixelQuick(x,y-1) << " " << mag.getPixelQuick(x+1,y-1) << endl;
                cout << mag.getPixelQuick(x-1,y) << " " << mag.getPixelQuick(x,y) << " " << mag.getPixelQuick(x+1,y) << endl;
                cout << mag.getPixelQuick(x-1,y+1) << " " << mag.getPixelQuick(x,y+1) << " " << mag.getPixelQuick(x+1,y+1) << endl;
             }
            float m=mag.getPixelQuick(x,y);
            if(isZero(m)) {
                result->setPixelSave(x,y,0);
            }  else {
                Ipp16s gx=dx.getPixelQuick(x,y);
                Ipp16s gy=dy.getPixelQuick(x,y);
                float mag1,mag2, d;
                if((gy<=0 && gx>-gy) || (gy>=0 && gx<-gy)) {
                    d = abs(gy/gx);
                    mag1 = mag.getPixelQuick(x,y+1)*(1-d) + mag.getPixelQuick(x-1,y+1)*d;
                    mag2 = mag.getPixelQuick(x,y-1)*(1-d) + mag.getPixelQuick(x+1,y-1)*d;
                } else if((gx>0 && -gy>=gx) || (gx<0 && -gy<=gx)) {
                    d = abs(gx/gy);
                    mag1 = mag.getPixelQuick(x-1,y)*(1-d) + mag.getPixelQuick(x-1,y+1)*d;
                    mag2 = mag.getPixelQuick(x+1,y)*(1-d) + mag.getPixelQuick(x+1,y-1)*d;
                } else if((gx<=0 && gx>gy) || (gx>=0 && gx<gy)) {
                    d = abs(gx/gy);
                    mag1 = mag.getPixelQuick(x-1,y)*(1-d) + mag.getPixelQuick(x-1,y-1)*d;
                    mag2 = mag.getPixelQuick(x+1,y)*(1-d) + mag.getPixelQuick(x+1,y+1)*d;
                } else if((gy<0 && gx<=gy) || (gy>0 && gx>=gy)) {
                    d = abs(gy/gx);
                    mag1 = mag.getPixelQuick(x,y-1)*(1-d) + mag.getPixelQuick(x-1,y-1)*d;
                    mag2 = mag.getPixelQuick(x,y+1)*(1-d) + mag.getPixelQuick(x+1,y+1)*d;
                } else {
                    result->setPixelQuick(x,y,0);
                    continue;
                }
                if(m>=mag1 && m>=mag2) {
                    result->setPixelQuick(x,y,255);
                } else {
                    result->setPixelQuick(x,y,0);
                }
            }
    }
#endif
    return result;
/*
  #else // NICE_USELIB_IPP
    fthrow(ImageException,"Not yet supported without IPP.");
  #endif // NICE_USELIB_IPP
*/
}

FloatImage* DeprecatedConverter::convolution(const FloatImage& src, const FloatImage &kernel, FloatImage* dst)
{
  #ifdef NICE_USELIB_IPP
    FloatImage* result = createResultBuffer(abs(src.width()-kernel.width())+1,
                                            abs(src.height()-kernel.height())+1,
                                            dst);
    IppStatus ret = ippiConvValid_32f_C1R(src.getPixelPointer(),
                                          src.getStepsize(),
                                          makeROIFullImage(src),
                                          kernel.getPixelPointer(),
                                          kernel.getStepsize(),
                                          makeROIFullImage(kernel),
                                          result->getPixelPointer(),
                                          result->getStepsize());
    if(ret!=ippStsNoErr)
                fthrow(ImageException, ippGetStatusString(ret));
    return result;
  #else // NICE_USELIB_IPP
    fthrow(ImageException,"Not yet supported without IPP.");
  #endif // NICE_USELIB_IPP
}

ColorImage* DeprecatedConverter::remap(const ColorImage& src, const FloatImage &px, const FloatImage &py, ColorImage* dst, int interpolation)
{
  #ifdef NICE_USELIB_IPP
   ColorImage::Pixel *cursor;
   ColorImage ci (src);
   cursor = ci.getPixelPointerY(0);
   *cursor = 0; cursor++;
   *cursor = 0; cursor++;
   *cursor = 0;
   ColorImage * result = createResultBuffer(ci.width(), ci.height(), dst);
   IppStatus ret = ippiRemap_8u_C3R(ci.getPixelPointer(), makeROIFullImage(ci), ci.getStepsize(), makeRectFullImage(ci),
       px.getPixelPointer(), px.getStepsize(), py.getPixelPointer(), py.getStepsize(),
       result->getPixelPointer(), result->getStepsize(), makeROIFullImage(*result), interpolation);
    if(ret!=ippStsNoErr)
                fthrow(ImageException, ippGetStatusString(ret));
    return result;
  #else // NICE_USELIB_IPP
    fthrow(ImageException,"Not yet supported without IPP.");
  #endif // NICE_USELIB_IPP
}


Image* DeprecatedConverter::blur(const Image& src, const int& size, Image* dst)
{
  #ifdef NICE_USELIB_IPP
   Image * result = createResultBuffer(src.width(), src.height(), dst);
   IppiSize maskSize;
   maskSize.width = size;
   maskSize.height = size;
   IppiPoint anchor;
   anchor.x = (int)(size/2);
   anchor.y = (int)(size/2);
   IppiSize imageSize;
   imageSize.width = dst->width()-size;
   imageSize.height = dst->height()-size;
   IppStatus ret = ippiFilterBox_8u_C1R(src.getPixelPointerXY(anchor.x,anchor.y), src.getStepsize(),
      result->getPixelPointerXY(anchor.x,anchor.y), result->getStepsize(),
      imageSize, maskSize, anchor);
   if(ret!=ippStsNoErr)
                fthrow(ImageException, ippGetStatusString(ret));
   return result;
  #else // NICE_USELIB_IPP
    fthrow(ImageException,"Not yet supported without IPP.");
  #endif // NICE_USELIB_IPP
}

Image* DeprecatedConverter::median(const Image& src, const int& size, Image* dst)
{
  #ifdef NICE_USELIB_IPP
   Image * result = createResultBuffer(src.width(), src.height(), dst);
   IppiSize maskSize;
   maskSize.width = size;
   maskSize.height = size;
   IppiPoint anchor;
   anchor.x = (int)(size/2);
   anchor.y = (int)(size/2);
   IppiSize imageSize;
   imageSize.width = dst->width()-size;
   imageSize.height = dst->height()-size;
   IppStatus ret = ippiFilterMedian_8u_C1R(src.getPixelPointerXY(anchor.x,anchor.y), src.getStepsize(),
      result->getPixelPointerXY(anchor.x,anchor.y), result->getStepsize(),
      imageSize, maskSize, anchor);
   if(ret!=ippStsNoErr)
                fthrow(ImageException, ippGetStatusString(ret));
   return result;
  #else // NICE_USELIB_IPP
    fthrow(ImageException,"Not yet supported without IPP.");
  #endif // NICE_USELIB_IPP
}

void DeprecatedConverter::thresholdIP(Image& img, int threshold)
{
  #ifdef NICE_USELIB_IPP
    IppStatus ret = ippiThreshold_Val_8u_C1IR(img.getPixelPointer(), img.getStepsize(), makeROIFullImage(img), threshold, 0, ippCmpLess);
    if(ret!=ippStsNoErr)
                fthrow(ImageException, ippGetStatusString(ret));
    ret = ippiThreshold_Val_8u_C1IR(img.getPixelPointer(), img.getStepsize(), makeROIFullImage(img), threshold, 255, ippCmpGreater);
    if(ret!=ippStsNoErr)
                fthrow(ImageException, ippGetStatusString(ret));
  #else // NICE_USELIB_IPP
    fthrow(ImageException,"Not yet supported without IPP.");
  #endif // NICE_USELIB_IPP
}

void DeprecatedConverter::lowerThresholdIP(Image& img, int threshold, int value)
{
  #ifdef NICE_USELIB_IPP
    IppStatus ret = ippiThreshold_Val_8u_C1IR(img.getPixelPointer(), img.getStepsize(), makeROIFullImage(img), threshold, value, ippCmpLess);
    if(ret!=ippStsNoErr)
                fthrow(ImageException, ippGetStatusString(ret));
  #else // NICE_USELIB_IPP
    fthrow(ImageException,"Not yet supported without IPP.");
  #endif // NICE_USELIB_IPP
}

void DeprecatedConverter::upperThresholdIP(Image& img, int threshold, int value)
{
  #ifdef NICE_USELIB_IPP
    IppStatus ret = ippiThreshold_Val_8u_C1IR(img.getPixelPointer(), img.getStepsize(), makeROIFullImage(img), threshold, value, ippCmpGreater);
    if(ret!=ippStsNoErr)
                fthrow(ImageException, ippGetStatusString(ret));
  #else // NICE_USELIB_IPP
    fthrow(ImageException,"Not yet supported without IPP.");
  #endif // NICE_USELIB_IPP
}

Image* DeprecatedConverter::erode(const Image& src, Image* dst)
{
  #ifdef NICE_USELIB_IPP
   IppiSize maskSize;
   maskSize.width = src.width()-2;
   maskSize.height = src.height()-2;
   Image * result = createResultBuffer(src.width(), src.height(), dst);
   IppStatus ret = ippiErode3x3_8u_C1R(src.getPixelPointerY(1)+1, src.getStepsize(),
      result->getPixelPointerY(1)+1, result->getStepsize(),
      maskSize);
    if(ret!=ippStsNoErr)
                fthrow(ImageException, ippGetStatusString(ret));
    return result;
  #else // NICE_USELIB_IPP
    fthrow(ImageException,"Not yet supported without IPP.");
  #endif // NICE_USELIB_IPP
}

void DeprecatedConverter::erodeIP(Image& img)
{
  #ifdef NICE_USELIB_IPP
   IppiSize roiSize;
   roiSize.width = img.width()-2;
   roiSize.height = img.height()-2;
   IppStatus ret = ippiErode3x3_8u_C1IR(img.getPixelPointer()+img.getStepsize()+1, img.getStepsize(), roiSize);
    if(ret!=ippStsNoErr)
                fthrow(ImageException, ippGetStatusString(ret));
  #else // NICE_USELIB_IPP
    fthrow(ImageException,"Not yet supported without IPP.");
  #endif // NICE_USELIB_IPP
}

Image* DeprecatedConverter::dilate(const Image& src, Image* dst)
{
  #ifdef NICE_USELIB_IPP
   IppiSize maskSize;
   maskSize.width = src.width()-2;
   maskSize.height = src.height()-2;
   Image * result = createResultBuffer(src.width(), src.height(), dst);
   IppStatus ret = ippiDilate3x3_8u_C1R(src.getPixelPointerY(1)+1, src.getStepsize(),
      result->getPixelPointerY(1)+1, result->getStepsize(),
      maskSize);
    if(ret!=ippStsNoErr)
                fthrow(ImageException, ippGetStatusString(ret));
   return result;
  #else // NICE_USELIB_IPP
    fthrow(ImageException,"Not yet supported without IPP.");
  #endif // NICE_USELIB_IPP
}

void DeprecatedConverter::dilateIP(Image& img)
{
  #ifdef NICE_USELIB_IPP
   IppiSize roiSize;
   roiSize.width = img.width()-2;
   roiSize.height = img.height()-2;
   IppStatus ret = ippiDilate3x3_8u_C1IR(img.getPixelPointer()+img.getStepsize()+1, img.getStepsize(), roiSize);
    if(ret!=ippStsNoErr)
                fthrow(ImageException, ippGetStatusString(ret));
  #else // NICE_USELIB_IPP
    fthrow(ImageException,"Not yet supported without IPP.");
  #endif // NICE_USELIB_IPP
}

Image* DeprecatedConverter::absDiff(const Image& src0, const Image& src1, Image* dst)
{
  #ifdef NICE_USELIB_IPP
   Image * result = createResultBuffer(src0.width(), src0.height(), dst);
   IppStatus ret = ippiAbsDiff_8u_C1R(src0.getPixelPointer(), src0.getStepsize(),
      src1.getPixelPointer(), src1.getStepsize(),
      result->getPixelPointer(), result->getStepsize(),
      makeROIFullImage(src0));
    if(ret!=ippStsNoErr)
                fthrow(ImageException, ippGetStatusString(ret));
    return result;
  #else // NICE_USELIB_IPP
    fthrow(ImageException,"Not yet supported without IPP.");
  #endif // NICE_USELIB_IPP
}

ColorImage* DeprecatedConverter::absDiff(const ColorImage& src0, const ColorImage& src1, ColorImage* dst)
{
  #ifdef NICE_USELIB_IPP
   IppiSize ippiSize;
   ippiSize.width = src0.width()*3;
   ippiSize.height = src0.height();
   ColorImage * result = createResultBuffer(src0.width(), src0.height(), dst);
   IppStatus ret = ippiAbsDiff_8u_C1R(src0.getPixelPointer(), src0.getStepsize(),
      src1.getPixelPointer(), src1.getStepsize(),
      result->getPixelPointer(), result->getStepsize(),
      ippiSize);
    if(ret!=ippStsNoErr)
                fthrow(ImageException, ippGetStatusString(ret));
    return result;
  #else // NICE_USELIB_IPP
    fthrow(ImageException,"Not yet supported without IPP.");
  #endif // NICE_USELIB_IPP
}

Image* DeprecatedConverter::copyRect(const Image& src, const int& x0, const int& y0, const int& x1, const int& y1, Image* dst) {
  #ifdef NICE_USELIB_IPP
    int copyRectWidth = x1-x0+1;
    int copyRectHeight = y1-y0+1;
    Rect rect (x0, y0, copyRectWidth, copyRectHeight);
    Rect roi = clipRect(src, rect);
    IppiSize ippiSize = makeROIRect(src, rect);
    preventIppBug(ippiSize, roi);

    Image * result = createResultBuffer(copyRectWidth, copyRectHeight, dst);
    Ipp8u const* src_rect = src.getPixelPointerXY(roi.left, roi.top);
    IppStatus ret = ippiCopy_8u_C1R(src_rect, src.getStepsize(),
     result->getPixelPointer(), result->getStepsize(),
     ippiSize);
    if(ret!=ippStsNoErr)
                fthrow(ImageException, ippGetStatusString(ret));
    return result;
  #else // NICE_USELIB_IPP
    fthrow(ImageException,"Not yet supported without IPP.");
  #endif // NICE_USELIB_IPP
}

ColorImage* DeprecatedConverter::copyRect(const ColorImage& src, const int& x0, const int& y0, const int& x1, const int& y1, ColorImage* dst) {
  #ifdef NICE_USELIB_IPP
    int copyRectWidth = x1-x0+1;
    int copyRectHeight = y1-y0+1;
    Rect rect (x0, y0, copyRectWidth, copyRectHeight);
    Rect roi = clipRect(src, rect);
    IppiSize ippiSize = makeROIRect(src, rect);
    preventIppBug(ippiSize, roi);

    ColorImage * result = createResultBuffer(copyRectWidth, copyRectHeight, dst);
    Ipp8u const* src_rect = src.getPixelPointerXY(roi.left, roi.top);
    ippiCopy_8u_C3R(src_rect, src.getStepsize(),
     result->getPixelPointer(), result->getStepsize(),
     ippiSize);
    return result;
  #else // NICE_USELIB_IPP
    throw ImageException("Not yet supported without IPP.");
  #endif // NICE_USELIB_IPP
}

Image* DeprecatedConverter::rgbToGrayRegion(const ColorImage& rgb,
                                      Image* gray,
                                      const Rect rect) {
  #ifdef NICE_USELIB_IPP
    Rect roi = clipRect(rgb, rect);
    IppiSize ippiSize = makeROIRect(rgb, rect);
    preventIppBug(ippiSize, roi);


    Image* result = createResultBuffer(rgb, gray);
    Ipp8u const* src = rgb.getPixelPointerXY(roi.left, roi.top);
    Ipp8u* dest = result->getPixelPointerXY(roi.left, roi.top);
    if (ippiSize.width <= 0 || ippiSize.height <= 0) {
      return result;
    }
    IppStatus ret = ippiRGBToGray_8u_C3C1R(src, rgb.getStepsize(),
                           dest, result->getStepsize(),
                           ippiSize);
    if(ret!=ippStsNoErr) {
      std::stringstream s;
      s << ippGetStatusString(ret)
        << " (ippiSize: " << ippiSize.width << "x" << ippiSize.height;
      fthrow(ImageException, s.str());
    }
    return result;
  #else // NICE_USELIB_IPP
    fthrow(ImageException,"Not yet supported without IPP.");
  #endif // NICE_USELIB_IPP
}

ColorImage* DeprecatedConverter::floatImageToGrayRGB(const FloatImage& floatImage,
                                           ColorImage* image) {
//  #ifdef NICE_USELIB_IPP
    ColorImage* result
      = createResultBuffer(floatImage.width(), floatImage.height(), image);
    float minValue = numeric_limits<float>::infinity();
    float maxValue = -numeric_limits<float>::infinity();
    for (int y = 0; y < floatImage.height(); y++) {
      FloatImage::Pixel const* cursor = floatImage.getPixelPointerXY(0, y);
      for (int x = 0; x < floatImage.width(); x++) {
        float value = *cursor++;
        minValue = min(minValue, value);
        maxValue = max(maxValue, value);
      }
    }

    const float range = maxValue - minValue;
    for (int y = 0; y < floatImage.height(); y++) {
      FloatImage::Pixel const* cursor = floatImage.getPixelPointerXY(0, y);
      ColorImage::Pixel* target = result->getPixelPointerXY(0, y);
      for (int x = 0; x < floatImage.width(); x++) {
        float value = *cursor++;
        ColorImage::Pixel pixel
          = ColorImage::Pixel(round(value * 255.0 / range));
        *target++ = pixel;
        *target++ = pixel;
        *target++ = pixel;
      }
    }
    return result;
//  #else // NICE_USELIB_IPP
//    fthrow(ImageException,"Not yet supported without IPP.");
//  #endif // NICE_USELIB_IPP
}

GrayImage16s* DeprecatedConverter::grayToDxRegion(const Image& gray,
                                        GrayImage16s* dx,
                                        const Rect rect) {
  #ifdef NICE_USELIB_IPP
    Rect roi = clipRect(gray, rect);
    IppiSize ippiSize = makeROIRect(gray, rect);
    preventIppBug(ippiSize, roi);

    GrayImage16s* result = createResultBuffer(gray, dx);
    Ipp8u const* src = gray.getPixelPointerXY(roi.left, roi.top);
    Ipp16s* dest = result->getPixelPointerXY(roi.left, roi.top);
    if (ippiSize.width <= 0 || ippiSize.height <= 0) {
      return result;
    }
    IppStatus ret = ippiFilterSobelHoriz_8u16s_C1R(src, gray.getStepsize(),
                              dest, result->getStepsize(),
                              ippiSize,ippMskSize3x3);
    if(ret!=ippStsNoErr)
                fthrow(ImageException, ippGetStatusString(ret));
    return result;
  #else // NICE_USELIB_IPP
    fthrow(ImageException,"Not yet supported without IPP.");
  #endif // NICE_USELIB_IPP
}

GrayImage16s* DeprecatedConverter::grayToDyRegion(const Image& gray,
                                        GrayImage16s* dy,
                                        const Rect rect) {
  #ifdef NICE_USELIB_IPP
    Rect roi = clipRect(gray, rect);
    IppiSize ippiSize = makeROIRect(gray, rect);
    preventIppBug(ippiSize, roi);

    GrayImage16s* result = createResultBuffer(gray, dy);
    Ipp8u const* src = gray.getPixelPointerXY(roi.left, roi.top);
    Ipp16s* dest = result->getPixelPointerXY(roi.left, roi.top);
    if (ippiSize.width <= 0 || ippiSize.height <= 0) {
      return result;
    }
    IppStatus ret = ippiFilterSobelVert_8u16s_C1R(src, gray.getStepsize(),
                              dest, result->getStepsize(),
                              ippiSize,ippMskSize3x3);
    if(ret!=ippStsNoErr)
                fthrow(ImageException, ippGetStatusString(ret));
    return result;
  #else // NICE_USELIB_IPP
    fthrow(ImageException,"Not yet supported without IPP.");
  #endif // NICE_USELIB_IPP
}

Image* DeprecatedConverter::canny(GrayImage16s& srcdx, GrayImage16s &srcdy,
                                   float low, float high, Image* dst)
{
  #ifdef NICE_USELIB_IPP
    Image* result = createResultBuffer(srcdx, dst);
    IppiSize ippiSize = { srcdx.width()-2, srcdx.height()-2 };
    int buffersize=0;
    IppStatus ret = ippiCannyGetSize(ippiSize, &buffersize);
    if(ret!=ippStsNoErr)
                fthrow(ImageException, ippGetStatusString(ret));
    Ipp8u buffer[buffersize];
    ret = ippiCanny_16s8u_C1R(srcdx.getPixelPointerXY(1,1), srcdx.getStepsize(),
                              srcdy.getPixelPointerXY(1,1), srcdy.getStepsize(),
                              result->getPixelPointerXY(1,1), result->getStepsize(),
                              ippiSize,low,high,buffer);
    if(ret!=ippStsNoErr)
                fthrow(ImageException, ippGetStatusString(ret));
    return result;
  #else // NICE_USELIB_IPP
    fthrow(ImageException,"Not yet supported without IPP.");
  #endif // NICE_USELIB_IPP
}

GrayImage16s* DeprecatedConverter::grayToDx(const Image& src, GrayImage16s* dst)
{
  #ifdef NICE_USELIB_IPP
    GrayImage16s* result = createResultBuffer(src, dst);
    IppiSize ippiSize = { src.width()-2, src.height()-2 };
    IppStatus ret = ippiFilterSobelVert_8u16s_C1R(src.getPixelPointerXY(1,1), src.getStepsize(),
                              result->getPixelPointerXY(1,1), result->getStepsize(),
                              ippiSize,ippMskSize3x3);
    if(ret!=ippStsNoErr)
                fthrow(ImageException, ippGetStatusString(ret));
    return result;
  #else // NICE_USELIB_IPP
    fthrow(ImageException,"Not yet supported without IPP.");
  #endif // NICE_USELIB_IPP
}

GrayImage16s* DeprecatedConverter::grayToDy(const Image& src, GrayImage16s* dst)
{
  #ifdef NICE_USELIB_IPP
    GrayImage16s* result = createResultBuffer(src, dst);
    IppiSize ippiSize = { src.width()-2, src.height()-2 };
    IppStatus ret = ippiFilterSobelHoriz_8u16s_C1R(src.getPixelPointerXY(1,1), src.getStepsize(),
                              result->getPixelPointerXY(1,1), result->getStepsize(),
                              ippiSize,ippMskSize3x3);
    if(ret!=ippStsNoErr)
                fthrow(ImageException, ippGetStatusString(ret));
    return result;
  #else // NICE_USELIB_IPP
    fthrow(ImageException,"Not yet supported without IPP.");
  #endif // NICE_USELIB_IPP
}

Image* DeprecatedConverter::filterX(const Image& src, const VectorT<int> &kernel, int anchor, int divisor, Image* dst)
{
    if(anchor==-1)
        anchor=kernel.size()/2;
  #ifdef NICE_USELIB_IPP
    Image* result = createResultBuffer(src, dst);
    IppiSize ippiSize = { (int)(src.width()-kernel.size()+1), (int)(src.height()) };
    IppStatus ret = ippiFilterRow_8u_C1R(src.getPixelPointerXY(kernel.size()-1-anchor,0),
                   src.getStepsize(),
                   result->getPixelPointerXY(anchor,0),
                   result->getStepsize(),
                   ippiSize,
                   kernel.getDataPointer(),
                   kernel.size(),
                   anchor,
                   divisor);
    if(ret!=ippStsNoErr)
                fthrow(ImageException, ippGetStatusString(ret));
    return result;
  #else // NICE_USELIB_IPP
  /*
    int yend=src.height();
    int xend=src.width()-anchor;
    Image &d=*result;
    VectorT<float> k(kernel.size());
    for (int i=0; i<kernel.size(); ++i)
        k[i]=static_cast<float>(kernel[i]);
    for(int y=0;y<yend; ++y)
        for(int x=anchor;x<xend; ++x) {
            float t=0.0;
            Image &s=src(-anchor,0);
            for (int i=0; i<kernel.size(); ++i)
                t +=  k[i] * s(x+i,y);
            d(x,y)=static_cast<Ipp8u>(t/divisor+0.5);
        }
    return result;
  */
    fthrow(ImageException,"Not yet supported without IPP.");
  #endif // NICE_USELIB_IPP
}

Image* DeprecatedConverter::filterY(const Image& src, const VectorT<int> &kernel, int anchor, int divisor, Image* dst)
{
    if(anchor==-1)
        anchor=kernel.size()/2;
  #ifdef NICE_USELIB_IPP
    Image* result = createResultBuffer(src, dst);
    IppiSize ippiSize = { (int)(src.width()), (int)(src.height()-kernel.size()+1) };
    IppStatus ret = ippiFilterColumn_8u_C1R(src.getPixelPointerXY(0,kernel.size()-1-anchor),
                   src.getStepsize(),
                   result->getPixelPointerXY(0,anchor),
                   result->getStepsize(),
                   ippiSize,
                   kernel.getDataPointer(),
                   kernel.size(),
                   anchor,
                   divisor);
    if(ret!=ippStsNoErr)
                fthrow(ImageException, ippGetStatusString(ret));
    return result;
  #else // NICE_USELIB_IPP
  /*
#pragma message NICE_WARNING("untested")
    int yend=src.height()-anchor;
    int xend=src.width();
    Image &d=*result;
    VectorT<float> k(kernel.size());
    for (int i=0; i<kernel.size(); ++i)
        k[i]=static_cast<float>(kernel[i]);
    for(int y=anchor;y<yend; ++y)
        for(int x=0;x<xend; ++x) {
            float t=0.0;
            Image &s=src(0,-anchor);
            for (int i=0; i<kernel.size(); ++i)
                t +=  k[i] * s(x,y+i);
            d(x,y)=static_cast<Ipp8u>(t/divisor+0.5);
        }
    return result;
  */
    fthrow(ImageException,"Not yet supported without IPP.");
  #endif // NICE_USELIB_IPP
}

Image* DeprecatedConverter::filter(const Image& src, const ImageT<int> &kernel, int anchorx, int anchory, int divisor, Image* dst)
{
    if(anchorx==-1)
        anchorx=kernel.width()/2;
    if(anchory==-1)
        anchory=kernel.height()/2;
    Image* result = createResultBuffer(src, dst);
  #ifdef NICE_USELIB_IPP
    IppiPoint anchor={anchorx,anchory};
    IppiSize ippiSize = { src.width()-kernel.width()+1, src.height()-kernel.height()+1 };
    if(kernel.getStepsize() != kernel.width()) {
        ImageT<int> k(kernel,GrayColorImageCommonImplementation::noAlignment);
        IppStatus ret = ippiFilter_8u_C1R(src.getPixelPointerXY(kernel.width()-1-anchorx,kernel.height()-1-anchory),
                   src.getStepsize(),
                   result->getPixelPointerXY(anchorx,anchory),
                   result->getStepsize(),
                   ippiSize,
                   k.getPixelPointer(),
                   makeROIFullImage(k),
                   anchor,
                   divisor);
    if(ret!=ippStsNoErr)
                fthrow(ImageException, ippGetStatusString(ret));
    } else {
        IppStatus ret = ippiFilter_8u_C1R(src.getPixelPointerXY(kernel.width()-1-anchorx,kernel.height()-1-anchory),
                   src.getStepsize(),
                   result->getPixelPointerXY(anchorx,anchory),
                   result->getStepsize(),
                   ippiSize,
                   kernel.getPixelPointer(),
                   makeROIFullImage(kernel),
                   anchor,
                   divisor);
    if(ret!=ippStsNoErr)
                fthrow(ImageException, ippGetStatusString(ret));
    }
  #else // NICE_USELIB_IPP
  /*
#pragma message NICE_WARNING("untested")
    int yend=src.height()-anchory;
    int xend=src.width()-anchorx;
    Image &d=*result;
    FloatImage k(kernel.width(),kernel.height());
    DeprecatedConverter::grayToFloat(kernel,&k);
    for(int y=anchory;y<yend; ++y)
        for(int x=anchorx;x<xend; ++x) {
            float t=0.0;
            Image &s=src(-anchorx,-anchory);
            for (int j=0; j<kernel.height(); ++j)
                for (int i=0; i<kernel.width(); ++i)
                     t +=  k(i,j) * s(x+i,y+j);
            d(x,y)=static_cast<P>(t/divisor);
        }
    */
    fthrow(ImageException,"Not yet supported without IPP.");
  #endif // NICE_USELIB_IPP
  return result;
}

ColorImage* DeprecatedConverter::filterLowpassRegion(const ColorImage& image,
                                           ColorImage* buffer,
                                           Rect rect) {
  #ifdef NICE_USELIB_IPP
    Rect roi = clipRect(image, rect);
    IppiSize ippiSize = makeROIRect(image, rect);
    preventIppBug(ippiSize, roi);

    ColorImage* result
      = createResultBuffer(image.width(), image.height(), buffer);
    ColorImage::Pixel const* src = image.getPixelPointerXY(roi.left, roi.top);
    ColorImage::Pixel* dest = result->getPixelPointerXY(roi.left, roi.top);
    IppStatus ret = ippiFilterLowpass_8u_C3R(src, image.getStepsize(),
                             dest, result->getStepsize(),
                             ippiSize,
                             ippMskSize3x3);
    if(ret!=ippStsNoErr)
                fthrow(ImageException, ippGetStatusString(ret));
    return result;
  #else // NICE_USELIB_IPP
    fthrow(ImageException,"Not yet supported without IPP.");
  #endif // NICE_USELIB_IPP
}


ColorImage* DeprecatedConverter::filterGaussRegion(const ColorImage& image,
                                         ColorImage* buffer,
                                         Rect rect) {
  #ifdef NICE_USELIB_IPP
    Rect roi = clipRect(image, rect);
    IppiSize ippiSize = makeROIRect(image, rect);
    preventIppBug(ippiSize, roi);

    ColorImage* result
      = createResultBuffer(image.width(), image.height(), buffer);
    ColorImage::Pixel const* src = image.getPixelPointerXY(roi.left, roi.top);
    ColorImage::Pixel* dest
      = result->getPixelPointerXY(roi.left, roi.top);
    IppStatus ret = ippiFilterGauss_8u_C3R(src, image.getStepsize(),
                           dest, result->getStepsize(),
                           ippiSize,
                           ippMskSize3x3);
    if(ret!=ippStsNoErr)
                fthrow(ImageException, ippGetStatusString(ret));
    return result;
  #else // NICE_USELIB_IPP
    fthrow(ImageException,"Not yet supported without IPP.");
  #endif // NICE_USELIB_IPP
}

Image* DeprecatedConverter::filterGauss(const Image& image,
                                        float sigma,
                                        Image* buffer) {
  #ifdef NICE_USELIB_IPP
    int length=static_cast<int>(2.0*sigma*sigma-0.5);
    if(length<1)
       length=0;
    int resultlength=3+length*2;
    float kernel[resultlength];
    const float konst1=1.0/(sigma*sqrt(2.*M_PI));
    const float konst2=-.5/(sigma*sigma);
    float sum=konst1;
    int half=length+1;
    kernel[half]=konst1;
    for(int i=0;i<half;i++) {
        kernel[i]=kernel[resultlength-1-i]=konst1* exp(konst2*(half-i));
        sum+=2*kernel[i];
    }
    for(int i=0;i<resultlength;i++) {
        kernel[i]/=sum;
    }

    IppiSize ippiCSize = { image.width()-resultlength+1, image.height()};
    Image tmpimg(image.width(),image.height());
    tmpimg=image;
    IppStatus ret = ippiFilterRow_C1R(image.getPixelPointerXY(resultlength/2,0),
                                             image.getStepsize(),
                                             tmpimg.getPixelPointerXY(resultlength/2,0),
                                             tmpimg.getStepsize(),
                                             ippiCSize,
                                             kernel,
                                             resultlength,
                                             half);
    if(ret!=ippStsNoErr) {
            fthrow(ImageException, ippGetStatusString(ret));
    }
    IppiSize ippiRSize = { image.width(), image.height()-resultlength+1};
    Image* result = createResultBuffer(image, buffer);
    *result=tmpimg;
    ret = ippiFilterColumn_C1R(tmpimg.getPixelPointerXY(0,resultlength/2),
                                tmpimg.getStepsize(),
                                result->getPixelPointerXY(0,resultlength/2),
                                result->getStepsize(),
                                ippiRSize,
                                kernel,
                                resultlength,
                                half);
    if(ret!=ippStsNoErr)
            fthrow(ImageException, ippGetStatusString(ret));
  return result;

  #else // NICE_USELIB_IPP
    fthrow(ImageException,"Not yet supported without IPP.");
  #endif // NICE_USELIB_IPP
}

/*
ColorImage* DeprecatedConverter::filterGaussRegion(const ColorImage& image,
                                         ColorImage* buffer,
                                         Rect rect, float sigma) {
  #ifdef NICE_USELIB_IPP
    Rect roi = clipRect(image, rect);
    IppiSize ippiSize = makeROIRect(image, rect);
    preventIppBug(ippiSize, roi);

    ColorImage* result = createResultBuffer(image.width(), image.height(), buffer);
    ColorImage::Pixel const* src = image.getPixelPointerXY(roi.left, roi.top);
    ColorImage::Pixel* dest = result->getPixelPointerXY(roi.left, roi.top);

    int length=static_cast<int>(2.0*sigma*sigma-0.5);
    if(length<1)
       length=0;
    float base[] = {0.25, 0.5, 0.25};
    int resultlength=3+length*2;
    float *tmpv = ippsMalloc_32f(resultlength);
    float *kernel = ippsMalloc_32f(resultlength);
    copy(base, base+3, kernel);
    for(int i=0;i<length;i++) {
        ippsConv_32f(base,3,kernel,3+i*2,tmpv);
        copy(tmpv, tmpv+3+(i+1)*2, kernel);
    }
    ippsFree(tmpv);
    ippiFilterColumn_32f_C3R(src, image.getStepsize(),
                 dest, result->getStepsize(),
                             ippiSize, kernel,  resultlength, resultlength/2);
  region.width=xsize-2*windowcenter;
  IppStatus ret = ippiFilterRow_32f_C3R(tmp_image+windowcenter+(windowcenter*stepsize)/4, tmpstepsize,
               ret_image+windowcenter+(windowcenter*stepsize)/4, retstepsize, region,
               pkernel, windowsize, windowcenter);
    if(ret!=ippStsNoErr)
            fthrow(ImageException, ippGetStatusString(ret));
  return result;

  #else // NICE_USELIB_IPP
    fthrow(ImageException,"Not yet supported.");
//  #endif // NICE_USELIB_IPP
}
*/

// Rect DeprecatedConverter::clipRect(const MultiChannelImageAccess& image, const Rect rect) {
//   Rect result(rect);
//   if (result.left < 0) {
//     result.width += result.left;
//     result.left = 0;
//   }
//   if (result.top < 0) {
//     result.height += result.top;
//     result.top = 0;
//   }
//   if (result.left >= image.width()) {
//     result.left = image.width() - 1;
//     result.width = 0;
//   }
//   if (result.top >= image.height()) {
//     result.top = image.height() - 1;
//     result.height = 0;
//   }
//   int maxWidth = image.width() - result.left;
//   int maxHeight = image.height() - result.top;
//   if (result.width >= maxWidth) {
//     result.width = maxWidth;
//   }
//   if (result.height >= maxHeight) {
//     result.height = maxHeight;
//   }
//   return result;
// }
//
// #ifdef NICE_USELIB_IPP
//   IppiRect DeprecatedConverter::makeRectFullImage(const MultiChannelImageAccess& image) {
//     IppiRect ippiRect;
//     ippiRect.x = 0;
//     ippiRect.y = 0;
//     ippiRect.width = image.width();
//     ippiRect.height = image.height();
//     return ippiRect;
//   }
//
//   IppiSize DeprecatedConverter::makeROIFullImage(const MultiChannelImageAccess& image) {
//     IppiSize ippiSize;
//     ippiSize.width = image.width();
//     ippiSize.height = image.height();
//     return ippiSize;
//   }
//
//   IppiSize DeprecatedConverter::makeROIRect(const MultiChannelImageAccess& image, const Rect rect) {
//     Rect roi = clipRect(image, rect);
//     IppiSize ippiSize;
//     ippiSize.width = roi.width;
//     ippiSize.height = roi.height;
//     return ippiSize;
//   }
//
//   void DeprecatedConverter::preventIppBug(IppiSize& ippiSize, Rect& clippedROI) {
//     // there is a bug in IPP: if ippiSize.height == 1 the function won't return
//     if (ippiSize.height == 1) {
//       ippiSize.height = 2;
//       if (clippedROI.top > 0) {
//         clippedROI.top--;
//       }
//     }
//     // maybe there is the same problem when ippiSize.width == 1
//     if (ippiSize.width == 1) {
//       ippiSize.width = 2;
//       if (clippedROI.left > 0) {
//         clippedROI.left--;
//       }
//     }
//   }
// #endif // NICE_USELIB_IPP


} // namespace
