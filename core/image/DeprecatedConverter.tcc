#include "core/image/DeprecatedConverter.h"
#include <iostream>

namespace NICE {

template<class P>
ImageT<P>* DeprecatedConverter::grayToDx(const ImageT<P>& src, ImageT<P>* dst)
{
  #ifdef NICE_USELIB_IPP
    ImageT<P>* result = createResultBuffer(src, dst);
    IppiSize ippiSize = { src.width()-2, src.height()-2 };
    IppStatus ret = ippiFilterSobelVert_C1R(src.getPixelPointerXY(1,1), src.getStepsize(),
                              result->getPixelPointerXY(1,1), result->getStepsize(),
                              ippiSize,ippMskSize3x3);
    if(ret!=ippStsNoErr)
                fthrow(ImageException, ippGetStatusString(ret));
    return result;
  #else // NICE_USELIB_IPP
    fthrow(ImageException,"Not yet supported without IPP.");
  #endif // NICE_USELIB_IPP
}

template<class P>
ImageT<P>* DeprecatedConverter::grayToDy(const ImageT<P>& src, ImageT<P>* dst)
{
  #ifdef NICE_USELIB_IPP
    ImageT<P>* result = createResultBuffer(src, dst);
    IppiSize ippiSize = { src.width()-2, src.height()-2 };
    IppStatus ret = ippiFilterSobelHoriz_C1R(src.getPixelPointerXY(1,1), src.getStepsize(),
                              result->getPixelPointerXY(1,1), result->getStepsize(),
                              ippiSize,ippMskSize3x3);
    if(ret!=ippStsNoErr)
                fthrow(ImageException, ippGetStatusString(ret));
    return result;
  #else // NICE_USELIB_IPP
    fthrow(ImageException,"Not yet supported without IPP.");
  #endif // NICE_USELIB_IPP
}

template<class P>
ImageT<P>* DeprecatedConverter::resize(const ImageT<P>& src, ImageT<P>* dst, double xFactor, double yFactor, int interpolation)
{
  #ifdef NICE_USELIB_IPP
   IppiRect rect;
   rect.x = 0;
   rect.y = 0;
   rect.width = src.width();
   rect.height = src.height();

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
ColorImageT<P>* DeprecatedConverter::resize(const ColorImageT<P>& src, ColorImageT<P>* dst, double xFactor, double yFactor, int interpolation)
{
  #ifdef NICE_USELIB_IPP
   IppiRect rect;
   rect.x = 0;
   rect.y = 0;
   rect.width = src.width();
   rect.height = src.height();

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
ImageT<P>* DeprecatedConverter::mirror(const ImageT<P>& src, IppiAxis axis, ImageT<P>* dst)
{
  #ifdef NICE_USELIB_IPP
    ImageT<P>* result = createResultBuffer(src, dst);
    IppStatus ret = ippiMirror_C1R(src.getPixelPointer(),
                                   src.getStepsize(),
                                   result->getPixelPointer(),
                                   result->getStepsize(),
                                   makeROIFullImage(src),
                                   axis);
    if(ret!=ippStsNoErr)
                fthrow(ImageException, ippGetStatusString(ret));
    return result;
  #else // NICE_USELIB_IPP
    fthrow(ImageException,"Not yet supported without IPP.");
  #endif // NICE_USELIB_IPP
}

template<class P>
ColorImageT<P>* DeprecatedConverter::mirror(const ColorImageT<P>& src, IppiAxis axis, ColorImageT<P>* dst)
{
  #ifdef NICE_USELIB_IPP
    ColorImageT<P>* result = createResultBuffer(src, dst);
    IppStatus ret = ippiMirror_C1R(src.getPixelPointer(),
                                   src.getStepsize(),
                                   result->getPixelPointer(),
                                   result->getStepsize(),
                                   makeROIFullImage(src),
                                   axis);
    if(ret!=ippStsNoErr)
                fthrow(ImageException, ippGetStatusString(ret));
    return result;
  #else // NICE_USELIB_IPP
    fthrow(ImageException,"Not yet supported without IPP.");
  #endif // NICE_USELIB_IPP
}


template<class P1, class P2>
ImageT<P2>* DeprecatedConverter::convertBitDepth(const ImageT<P1>& image,
                                   ImageT<P2>* buffer) {
  #ifdef NICE_USELIB_IPP
    ImageT<P2>* result = createResultBuffer(image, buffer);

    if(sizeof(P1)<sizeof(P2)) {
        IppStatus ret = ippiConvert_C1R(image.getPixelPointer(),
                          image.getStepsize(),
                          result->getPixelPointer(),
                          result->getStepsize(),
                          makeROIFullImage(image));
       if(ret!=ippStsNoErr)
            fthrow(ImageException, ippGetStatusString(ret));
    } else {
        IppStatus ret= ippiConvert_C1R(image.getPixelPointer(),
                          image.getStepsize(),
                          result->getPixelPointer(),
                          result->getStepsize(),
                          makeROIFullImage(image), ippRndNear);
        if(ret!=ippStsNoErr)
            fthrow(ImageException, ippGetStatusString(ret));
    }
    return result;
  #else // NICE_USELIB_IPP
    fthrow(ImageException,"Not yet supported without IPP.");
  #endif // NICE_USELIB_IPP
}

template<class P1, class P2>
ColorImageT<P2>* DeprecatedConverter::convertBitDepth(const ColorImageT<P1>& image,
                                   ColorImageT<P2>* buffer) {
  #ifdef NICE_USELIB_IPP
    ColorImageT<P2>* result = createResultBuffer(image, buffer);

    if(sizeof(P1)<sizeof(P2)) {
        IppStatus ret = ippiConvert_C3R(image.getPixelPointer(),
                          image.getStepsize(),
                          result->getPixelPointer(),
                          result->getStepsize(),
                          makeROIFullImage(image));
        if(ret!=ippStsNoErr)
            fthrow(ImageException, ippGetStatusString(ret));
    } else {
        IppStatus ret = ippiConvert_C3R(image.getPixelPointer(),
                          image.getStepsize(),
                          result->getPixelPointer(),
                          result->getStepsize(),
                          makeROIFullImage(image), ippRndNear);
        if(ret!=ippStsNoErr) {
            fthrow(ImageException, ippGetStatusString(ret));
        }
    }
    return result;
  #else // NICE_USELIB_IPP
    fthrow(ImageException,"Not yet supported without IPP.");
  #endif // NICE_USELIB_IPP
}

template<class P>
FloatImage* DeprecatedConverter::grayToFloat(const ImageT<P>& gray,
                                   FloatImage* fimage) {
  #ifdef NICE_USELIB_IPP
    FloatImage* result = createResultBuffer(gray, fimage);

    IppStatus ret = ippiConvert_C1R(gray.getPixelPointer(),
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

template<class P>
ImageT<P>* DeprecatedConverter::floatToGray(const FloatImage& fimage,
                                   ImageT<P>* gray) {
  #ifdef NICE_USELIB_IPP
    ImageT<P>* result = createResultBuffer(fimage, gray);

    IppStatus ret = ippiConvert_C1R(fimage.getPixelPointer(),
                          fimage.getStepsize(),
                          result->getPixelPointer(),
                          result->getStepsize(),
                          makeROIFullImage(fimage),ippRndNear);
    if(ret!=ippStsNoErr)
                fthrow(ImageException, ippGetStatusString(ret));
    return result;
  #else // NICE_USELIB_IPP
    fthrow(ImageException,"Not yet supported without IPP.");
  #endif // NICE_USELIB_IPP
}

template<class P>
ImageT<P>* DeprecatedConverter::floatToGrayScaled(const FloatImage& fimage, Ipp32f fmin, Ipp32f fmax,
                                   ImageT<P>* gray) {
  #ifdef NICE_USELIB_IPP
    ImageT<P>* result = createResultBuffer(fimage, gray);

    IppStatus ret = ippiScale_C1R(fimage.getPixelPointer(),
                          fimage.getStepsize(),
                          result->getPixelPointer(),
                          result->getStepsize(),
                          makeROIFullImage(fimage),
                          fmin,
                          fmax);
    if(ret!=ippStsNoErr)
                fthrow(ImageException, ippGetStatusString(ret));
    return result;
  #else // NICE_USELIB_IPP
    fthrow(ImageException,"Not yet supported without IPP.");
  #endif // NICE_USELIB_IPP
}

template<class P>
ImageT<P>* DeprecatedConverter::floatToGrayScaled(const FloatImage& fimage,
                                   ImageT<P>* gray) {
  Ipp32f fmin, fmax;
  #ifdef NICE_USELIB_IPP
  IppStatus ret = ippiMinMax_C1R(fimage.getPixelPointer(),
              fimage.getStepsize(),
              makeROIFullImage(fimage),
              &fmin,
              &fmax);
    if(ret!=ippStsNoErr)
                fthrow(ImageException, ippGetStatusString(ret));
  return DeprecatedConverter::floatToGrayScaled(fimage, fmin, fmax, gray);
  #else // NICE_USELIB_IPP
    fthrow(ImageException,"Not yet supported without IPP.");
  #endif // NICE_USELIB_IPP
}

template<class P>
ImageT<P>* DeprecatedConverter::rgbToGray(const ColorImageT<P>& rgb,
                                ImageT<P>* gray) {
    ImageT<P>* result = createResultBuffer(rgb, gray);
  #ifdef NICE_USELIB_IPP
	// XXX rgb->gray pixel value not rounded correctly
    IppStatus ret = ippiRGBToGray_C3C1R(rgb.getPixelPointer(),
                           rgb.getStepsize(),
                           result->getPixelPointer(),
                           result->getStepsize(),
                           makeROIFullImage(rgb));
    if(ret!=ippStsNoErr)
        fthrow(ImageException, ippGetStatusString(ret));
    return result;
  #else // NICE_USELIB_IPP
  // fill rgb -> gray  color transform lookup tables
    P *pdst;
    const P *psrc;
	if(sizeof(P)==1) {
		if(!pLut_initialized) {
			for (int i = 0; i < 256; ++i) {
				pLutRg[i] = static_cast<int>((0.299 *i+0.5)*(1<<12));
				pLutGg[i] = static_cast<int>(0.587 *i*(1<<12));
				pLutBg[i] = static_cast<int>(0.114 *i*(1<<12));
			}
			pLut_initialized=true;
		}
		for (int j=0; j < result->height(); ++j) {
		psrc=rgb.getPixelPointerY(j);
		pdst=result->getPixelPointerY(j);
		for (int i=0; i < result->width(); ++i, psrc+=3) {
		// using lookuptable is faster
			*(pdst++) = static_cast<P>((pLutRg[(int)(*psrc)]+pLutGg[(int)*(psrc+1)]+pLutBg[(int)*(psrc+2)])>>12);
		}
	}
  } else {
		for (int j=0; j < result->height(); ++j) {
		psrc=rgb.getPixelPointerY(j);
		pdst=result->getPixelPointerY(j);
			for (int i=0; i < result->width(); ++i, psrc+=3) {
				// without lookuptable (slow)
				*(pdst++) = static_cast<P>(*psrc*0.299+*(psrc+1)*0.587+*(psrc+2)*0.114);
			}
		}
  }
  return result;
  #endif // NICE_USELIB_IPP
}


template<class P>
ColorImageT<P>* DeprecatedConverter::grayToRGB(const ImageT<P>& gray,
                              ColorImageT<P>* rgb)
{
    ColorImageT<P>* result = createResultBuffer(gray, rgb);
  #ifdef NICE_USELIB_IPP
    const P *src[3];
	src[0] = gray.getPixelPointer();
	src[1] = gray.getPixelPointer();
	src[2] = gray.getPixelPointer();
    IppStatus ret = ippiCopy_P3C3R(src, gray.getStepsize(),
                      result->getPixelPointer(), result->getStepsize(),
					  makeROIFullImage(gray));
    if(ret!=ippStsNoErr)
        fthrow(ImageException, ippGetStatusString(ret));
    return result;
  #else // NICE_USELIB_IPP
    P *pdst;
    const P *psrc;
	for (int j=0; j < result->height(); ++j) {
        psrc=gray.getPixelPointerY(j);
        pdst=result->getPixelPointerY(j);
		for (int i=0; i < result->width(); ++i,++psrc) {
            *(pdst++) = *psrc;
            *(pdst++) = *psrc;
            *(pdst++) = *psrc;
		}
	}
    return result;
  #endif // NICE_USELIB_IPP
}

template<class P>
ImageT<P>* DeprecatedConverter::filterGauss3x3(const ImageT<P>& image, ImageT<P>* buffer)
{
  #ifdef NICE_USELIB_IPP
    ImageT<P>* result = createResultBuffer(image, buffer);
    IppiSize ippiSize = { image.width()-2, image.height()-2 };
    IppStatus ret = ippiFilterGauss_C1R(image.getPixelPointerXY(1,1), image.getStepsize(),
                              result->getPixelPointerXY(1,1), result->getStepsize(),
                              ippiSize,ippMskSize3x3);
    if(ret!=ippStsNoErr)
                fthrow(ImageException, ippGetStatusString(ret));
    return result;
  #else // NICE_USELIB_IPP
    fthrow(ImageException,"Not yet supported without IPP.");
  #endif // NICE_USELIB_IPP
}

template<class P>
ImageT<P>* DeprecatedConverter::filterGauss5x5(const ImageT<P>& image, ImageT<P>* buffer)
{
  #ifdef NICE_USELIB_IPP
    ImageT<P>* result = createResultBuffer(image, buffer);
    IppiSize ippiSize = { image.width()-4, image.height()-4 };
    IppStatus ret = ippiFilterGauss_C1R(image.getPixelPointerXY(2,2), image.getStepsize(),
                              result->getPixelPointerXY(2,2), result->getStepsize(),
                              ippiSize,ippMskSize5x5);
    if(ret!=ippStsNoErr)
                fthrow(ImageException, ippGetStatusString(ret));
    return result;
  #else // NICE_USELIB_IPP
    fthrow(ImageException,"Not yet supported without IPP.");
  #endif // NICE_USELIB_IPP
}

template<class P>
ImageT<P>* DeprecatedConverter::filterX(const ImageT<P>& src, const VectorT<float> &kernel, int anchor, ImageT<P>* dst)
{
    if(anchor==-1)
        anchor=kernel.size()/2;
  #ifdef NICE_USELIB_IPP
    ImageT<P>* result = createResultBuffer(src, dst);
    IppiSize ippiSize = { src.width()-kernel.size()+1, src.height() };
    IppStatus ret = ippiFilterRow_C1R(src.getPixelPointerXY(kernel.size()-1-anchor,0),
                   src.getStepsize(),
                   result->getPixelPointerXY(anchor,0),
                   result->getStepsize(),
                   ippiSize,
                   kernel.getDataPointer(),
                   kernel.size(),
                   anchor);
   if(ret!=ippStsNoErr)
       fthrow(ImageException, ippGetStatusString(ret));
    return result;
  #else // NICE_USELIB_IPP
	/*
#pragma message NICE_WARNING("untested")
    int yend=src.height();
    int xend=src.width()-kernel.size()+anchor;
    ImageT<P> &d=*result;
    for(int y=0;y<yend; ++y)
        for(int x=anchor;x<xend; ++x) {
            float t=0.0;
            ImageT<P> &s=src(-anchor,0);
            for (int i=0; i<kernel.size(); ++i)
                t +=  kernel[i] * s(x+i,y);
            d(x,y)=t;
        }
    return result;
	*/
    fthrow(ImageException,"Not yet supported without IPP.");
  #endif // NICE_USELIB_IPP
}

template<class P>
ImageT<P>* DeprecatedConverter::filterY(const ImageT<P>& src, const VectorT<float> &kernel, int anchor, ImageT<P>* dst)
{
    if(anchor==-1)
        anchor=kernel.size()/2;
    ImageT<P>* result = createResultBuffer(src, dst);

  #ifdef NICE_USELIB_IPP
    IppiSize ippiSize = { src.width(), src.height()-kernel.size()+1 };
    IppStatus ret = ippiFilterColumn_C1R(src.getPixelPointerXY(0,kernel.size()-1-anchor),
                   src.getStepsize(),
                   result->getPixelPointerXY(0,anchor),
                   result->getStepsize(),
                   ippiSize,
                   kernel.getDataPointer(),
                   kernel.size(),
                   anchor);
        if(ret!=ippStsNoErr)
            fthrow(ImageException, ippGetStatusString(ret));
    return result;
  #else // NICE_USELIB_IPP

    int yend=src.height()-anchor;
    int xend=src.width();
    ImageT<P> &d=*result;
    for(int y=anchor;y<yend; ++y)
        for(int x=0;x<xend; ++x) {
            float t=0.0;
            ImageT<P> &s=src(0,-anchor);
            for (int i=0; i<kernel.size(); ++i)
                t +=  kernel[i] * s(x,y+i);
            d(x,y)=t;
        }
    return result;

    fthrow(ImageException,"Not yet supported without IPP.");
  #endif // NICE_USELIB_IPP
}



template<class P>
ImageT<P>* DeprecatedConverter::filter(const ImageT<P>& src, const FloatImage &kernel, int anchorx, int anchory, ImageT<P>* dst)
{
    if(anchorx==-1)
        anchorx=kernel.width()/2;
    if(anchory==-1)
        anchory=kernel.height()/2;
    ImageT<P>* result = createResultBuffer(src, dst);
  #ifdef NICE_USELIB_IPP
    IppiPoint anchor={anchorx,anchory};
    IppiSize ippiSize = { src.width()-kernel.width()+1, src.height()-kernel.height()+1 };
    if(kernel.getMemoryLayout() != GrayColorImageCommonImplementation::noAlignment && (uint)kernel.getStepsize() != sizeof(float)*kernel.width()) {
        FloatImage k(kernel,GrayColorImageCommonImplementation::noAlignment);
        IppStatus ret = ippiFilter_C1R(src.getPixelPointerXY(kernel.width()-1-anchorx,kernel.height()-1-anchory),
                    src.getStepsize(),
                    result->getPixelPointerXY(anchorx,anchory),
                    result->getStepsize(),
                    ippiSize,
                    k.getPixelPointer(),
                    makeROIFullImage(k),
                    anchor);
        if(ret!=ippStsNoErr)
            fthrow(ImageException, ippGetStatusString(ret));
    } else {
        IppStatus ret = ippiFilter_C1R(src.getPixelPointerXY(kernel.width()-1-anchorx,kernel.height()-1-anchory),
                    src.getStepsize(),
                    result->getPixelPointerXY(anchorx,anchory),
                    result->getStepsize(),
                    ippiSize,
                    kernel.getPixelPointer(),
                    makeROIFullImage(kernel),
                    anchor);
        if(ret!=ippStsNoErr)
            fthrow(ImageException, ippGetStatusString(ret));
    }
  #else // NICE_USELIB_IPP
//     int yend=src.height()-anchory;
//     int xend=src.width()-anchorx;
//     ImageT<P> &d=*result;
//     for(int y=anchory;y<yend; ++y)
//         for(int x=anchorx;x<xend; ++x) {
//             float t=0.0;
//             ImageT<P> &s=src(-anchorx,-anchory);
//             for (int j=0; j<kernel.height(); ++j)
//                 for (int i=0; i<kernel.width(); ++i)
//                      t +=  kernel(i,j) * s(x+i,y+j);
//             d(x,y)=t;
//         }

    fthrow(ImageException,"Not yet supported without IPP.");
  #endif // NICE_USELIB_IPP
  return result;
}

template<class P>
ImageT<P>* DeprecatedConverter::And(const ImageT<P>& src0, const ImageT<P>& src1, ImageT<P>* dst)
{
  #ifdef NICE_USELIB_IPP
   ImageT<P> *result = createResultBuffer(src0.width(), src0.height(), dst);
   IppStatus ret = ippiAnd_C1R(src0.getPixelPointer(), src0.getStepsize(),
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

template<class P>
ColorImageT<P>* DeprecatedConverter::And(const ColorImageT<P>& src0, const ColorImageT<P>& src1, ColorImageT<P>* dst)
{
  #ifdef NICE_USELIB_IPP
   ColorImageT<P> *result = createResultBuffer(src0.width(), src0.height(), dst);
   IppStatus ret = ippiAnd_C3R(src0.getPixelPointer(), src0.getStepsize(),
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

template<class P>
ColorImageT<P>* DeprecatedConverter::mean(const ColorImageT<P>& src0, const ColorImageT<P>& src1, ColorImageT<P>* dst)
{
  #ifdef NICE_USELIB_IPP
   ColorImageT<P> *result = createResultBuffer(src0.width(), src0.height(), dst);
    IppStatus ret = ippiAlphaCompC_C3R(src0.getPixelPointer(), src0.getStepsize(), 127,
			src1.getPixelPointer(), src1.getStepsize(), 127,
			result->getPixelPointer(), result->getStepsize(),
			makeROIFullImage(src0),ippAlphaPlus);
    if(ret!=ippStsNoErr)
                fthrow(ImageException, ippGetStatusString(ret));
    return result;
  #else // NICE_USELIB_IPP
    fthrow(ImageException,"Not yet supported without IPP.");
  #endif // NICE_USELIB_IPP
}


template<class P>
ImageT<P>* DeprecatedConverter::mean(const ImageT<P>& src0, const ImageT<P>& src1, ImageT<P>* dst)
{
  #ifdef NICE_USELIB_IPP
    ImageT<P> * result = createResultBuffer(src0.width(), src0.height(), dst);
    IppStatus ret = ippiAlphaCompC_C1R(src0.getPixelPointer(), src0.getStepsize(), 127,
			src1.getPixelPointer(), src1.getStepsize(), 127,
			result->getPixelPointer(), result->getStepsize(),
			makeROIFullImage(src0),ippAlphaPlus);
    if(ret!=ippStsNoErr)
                fthrow(ImageException, ippGetStatusString(ret));
    return result;
  #else // NICE_USELIB_IPP
    fthrow(ImageException,"Not yet supported without IPP.");
  #endif // NICE_USELIB_IPP
}

template <class P>
VectorT<int>* DeprecatedConverter::histogramCumulative(const ImageT<P>& src, int min, int max, int levels)
{
	VectorT<int> *histo = new VectorT<int>(levels);
	return DeprecatedConverter::histogramCumulative(src,histo,min,max);
}

template <class P>
VectorT<int>* DeprecatedConverter::histogramCumulative(const ImageT<P>& src, VectorT<int> *histo, int  min, int max)
{
	DeprecatedConverter::histogram(src,histo,min,max);
    int *h=histo->getDataPointer();
    for(uint i=1;i<histo->size();i++,h++) {
        *(h+1) += *h;
    }
    return histo;
}

template <class P>
VectorT<float>* DeprecatedConverter::histogramNormalized(const ImageT<P>& src, int min, int max, int levels)
{
	VectorT<float> *histo = new VectorT<float>(levels);
	return DeprecatedConverter::histogramNormalized(src,histo,min,max);
}

template <class P>
VectorT<float>* DeprecatedConverter::histogramNormalized(const ImageT<P>& src, VectorT<float> *histo, int min, int max)
{
	VectorT<int> inthisto(histo->size());
	DeprecatedConverter::histogram(src,&inthisto,min,max);
    VectorT<int>::const_iterator it=inthisto.begin();
    VectorT<float>::iterator dst=histo->begin();
    float sum=0.0;
    for(;it!=inthisto.end();it++,dst++) {
        *dst=*it;
        sum+=*dst;
    }
    for(dst=histo->begin();dst!=histo->end();dst++) {
        *dst/=sum;
    }
    return histo;
}

template <class P>
VectorT<int>* DeprecatedConverter::histogram(const ImageT<P>& src, int min, int max, int levels)
{
	VectorT<int> *histo = new VectorT<int>(levels);
	return DeprecatedConverter::histogram(src,histo,min,max);
}

template <class P>
VectorT<int>* DeprecatedConverter::histogram(const ImageT<P>& src, VectorT<int> *histo, int min, int max)
{
  #ifdef NICE_USELIB_IPP
	int	nolevels=histo->size()+1;
	int levels[nolevels];
	ippiHistogramEven_C1R(src.getPixelPointer(), src.getStepsize(), makeROIFullImage(src), histo->getDataPointer(), levels, nolevels, min, max);
  #else // NICE_USELIB_IPP
    fthrow(ImageException,"Not yet supported without IPP.");
  #endif // NICE_USELIB_IPP
   return histo;
}

template <class P>
VectorT<int>* DeprecatedConverter::histogramCumulative(const ColorImageT<P>& src, int min, int max, int levels)
{
	VectorT<int> *histo = new VectorT<int>(levels*3);
	return DeprecatedConverter::histogramCumulative(src,histo,min,max);
}

template <class P>
VectorT<int>* DeprecatedConverter::histogramCumulative(const ColorImageT<P>& src, VectorT<int> *histo, int  min, int max)
{
	DeprecatedConverter::histogram(src,histo,min,max);
	int	nolevels=histo->size()/3;
    int *h=histo->getDataPointer();
    for(int c=0;c<3;c++) {
        for(int i=1;i<nolevels;i++,h++) {
            *(h+1) += *h;
        }
        h++;
    }
    return histo;
}

template <class P>
VectorT<float>* DeprecatedConverter::histogramNormalized(const ColorImageT<P>& src, int min, int max, int levels)
{
	VectorT<float> *histo = new VectorT<float>(levels*3);
	return DeprecatedConverter::histogramNormalized(src,histo,min,max);
}

template <class P>
VectorT<float>* DeprecatedConverter::histogramNormalized(const ColorImageT<P>& src, VectorT<float> *histo, int min, int max)
{
	VectorT<int> inthisto(histo->size());
	DeprecatedConverter::histogram(src,&inthisto,min,max);
	int	nolevels=histo->size()/3;
    int *it = inthisto.getDataPointer();
    float *dst = histo->getDataPointer();
    for(int c=0;c<3;c++) {
        float sum=0.0;
        for(int i=0;i<nolevels;i++,it++,dst++) {
            *dst = *it;
            sum += *dst;
        }
        dst=dst-nolevels;
        for(int i=0;i<nolevels;i++,dst++)
            *dst /= sum;
    }
    return histo;
}

template <class P>
VectorT<int>* DeprecatedConverter::histogram(const ColorImageT<P>& src, int min, int max, int levels)
{
	VectorT<int> *histo = new VectorT<int>(levels*3);
	return DeprecatedConverter::histogram(src,histo,min,max);
}

template <class P>
VectorT<int>* DeprecatedConverter::histogram(const ColorImageT<P>& src, VectorT<int> *histo, int  min, int max)
{
#ifdef NICE_USELIB_IPP
	int	nolevels=histo->size()/3;
	int levels[(nolevels+1)*3];
	int pnolevels[3];
	int *phisto[3], *plevels[3], pmin[3], pmax[3];
	int *h=histo->getDataPointer();
	for(int i=0;i<3;i++) {
		plevels[i]=&levels[i*(nolevels+1)];
		phisto[i]=&h[i*nolevels];
		pmin[i]=min;
		pmax[i]=max;
		pnolevels[i]=nolevels+1;
	}
 
	ippiHistogramEven_C3R(src.getPixelPointer(), src.getStepsize(), makeROIFullImage(src), phisto, plevels, pnolevels, pmin, pmax);
  #else // NICE_USELIB_IPP
    fthrow(ImageException,"Not yet supported without IPP.");
  #endif // NICE_USELIB_IPP
   return histo;
}

template<class BUFFER>
BUFFER* DeprecatedConverter::createResultBuffer(const int width,
                                      const int height,
                                      BUFFER* buffer) {
  BUFFER* result;
  if (buffer == NULL) {
    result = new BUFFER(width, height);
  } else if(buffer->width()==0 && buffer->height()==0) {
    result = buffer;
    result->resize(width,height);
  } else {
    result = buffer;
    if (result->width() != width || result->height() != height) {
      fthrow(ImageException,
        "DeprecatedConverter: size of image is not equal to (width, height).");
    }
  }
  return result;
}

template<class IMG, class BUFFER>
BUFFER* DeprecatedConverter::createResultBuffer(const IMG& image, BUFFER* buffer)
{
  BUFFER* result;
  if (buffer == NULL) {
    result = new BUFFER(image.width(), image.height());
  } else if(buffer->width()==0 && buffer->height()==0) {
    result = buffer;
    result->resize(image.width(),image.height());
  } else {
    result = buffer;
    if (result->width() != image.width()
        || result->height() != image.height()) {
      fthrow(ImageException,
        "DeprecatedConverter: size of image and buffer are not equal.");
    }
  }
  return result;
}

template<class P>
ColorImage* DeprecatedConverter::signedImageToRGB(const ImageT<P>& image,
                                        ColorImage* colored) {
  //fthrow(ImageException, "signedImageToRGB() not supported for this pixel type");
  ColorImage *result = createResultBuffer(image, colored);

  P vmin;
  P vmax;
  image.minmax(vmin, vmax);
  const P scale = std::max(+vmax, -vmin);
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

}
