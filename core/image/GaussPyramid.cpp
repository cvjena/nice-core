
#include "core/image/GaussPyramid.h"
#include <iostream>
#include <vector>

namespace NICE {

GaussPyramid::GaussPyramid(const Image& src, uint levelin, float rate)
{
    this->rate=rate;
    gaussimage.resize(levelin+1);
  convertBitDepth(src, &gaussimage[0]);
  uint level=0;
  uint x=(uint)src.width();
  uint y=(uint)src.height();
  while (level<levelin && x/rate>=2 && y/rate>=2) {
    x=uint(x/rate);
    y=uint(y/rate);
    level++;

  }
  buildGaussPyramid(level,rate);
}

GaussPyramid::GaussPyramid(const FloatImage& src, uint levelin, float rate)
{
    this->rate=rate;
    gaussimage.resize(levelin+1);
    gaussimage[0]=src;
  uint level=0;
  uint x=(uint)src.width();
  uint y=(uint)src.height();
  while (level<levelin && x/rate>=2 && y/rate>=2) {
    x=uint(x/rate);
    y=uint(y/rate);
    level++;
  }
  buildGaussPyramid(level,rate);
}

GaussPyramid::GaussPyramid(const Image& src, uint sizeMinX, uint sizeMinY, float rate)
{
    this->rate=rate;
  uint x=(uint)src.width();
  uint y=(uint)src.height();
  uint level=0;
  while (x/rate>=sizeMinX && y/rate>=sizeMinY) {
    x=uint(x/rate);
    y=uint(y/rate);
    level++;
  }
    gaussimage.resize(level+1);
  convertBitDepth(src, &gaussimage[0]);
  buildGaussPyramid(level,rate);
}

GaussPyramid::GaussPyramid(const FloatImage& src, uint sizeMinX, uint sizeMinY, float rate)
{
    this->rate=rate;
  uint x=(uint)src.width();
  uint y=(uint)src.height();
  uint level=0;
  while (x/rate>=sizeMinX && y/rate>=sizeMinY) {
    x=uint(x/rate);
    y=uint(y/rate);
    level++;
  }
    gaussimage.resize(level+1);
    gaussimage[0]=src;
  buildGaussPyramid(level,rate);
}

void GaussPyramid::buildGaussPyramid(uint levelin, float rate)
{
    laplaceimage.resize(levelin+1);
#ifdef NICE_USELIB_IPP
  int maskSize;
  Ipp32f *pKernel=NULL;
  Ipp32f Kernel5x5[]={1.0,  4.0,  6.0,  4.0, 1.0,
              4.0, 16.0, 24.0, 16.0, 4.0,
              6.0, 24.0, 36.0, 24.0, 6.0,
              4.0, 16.0, 24.0, 16.0, 4.0,
              1.0,  4.0,  6.0,  4.0, 1.0};
  Ipp32f Kernel7x7[]={0.000900, 0.0031500, 0.006660, 0.008580, 0.006660, 0.0031500, 0.000900,
            0.003150, 0.0110250, 0.023310, 0.030030, 0.023310, 0.0110250, 0.003150,
            0.006660, 0.0233100, 0.049284, 0.063492, 0.049284, 0.0233100, 0.006660,
            0.008580, 0.0300300, 0.063492, 0.081796, 0.063492, 0.0300300, 0.008580,
            0.006660, 0.0233100, 0.049284, 0.063492, 0.049284, 0.0233100, 0.006660,
            0.003150, 0.0110250, 0.023310, 0.030030, 0.023310, 0.0110250, 0.003150,
            0.000900, 0.0031500, 0.006660, 0.008580, 0.006660, 0.0031500, 0.000900};
  if(isEqual(rate, 1.5f, 1E-6f)) {
    maskSize=7;
    pKernel=Kernel7x7;
  } else {
    maskSize=5;
    pKernel=Kernel5x5;
  }
  IppiSize ippiSize = {gaussimage[0].width(), gaussimage[0].height()};
  IppStatus ret = ippiPyramidInitAlloc(
        &gPyramid,
        levelin,
        ippiSize,
        rate);
  if(ret!=ippStsNoErr)
    fthrow(ImageException, ippGetStatusString(ret));

  ret = ippiPyramidInitAlloc(
      &lPyramid,
      levelin,
      ippiSize,
      rate);
  if(ret!=ippStsNoErr)
    fthrow(ImageException, ippGetStatusString(ret));

  IppiPyramidDownState_32f_C1R **gState =(IppiPyramidDownState_32f_C1R**) &(gPyramid->pState);
  IppiPyramidUpState_32f_C1R **lState =(IppiPyramidUpState_32f_C1R**) &(lPyramid->pState);

  Ipp32f **gImage = (Ipp32f**)(gPyramid->pImage);
  Ipp32f **lImage = (Ipp32f**)(lPyramid->pImage);
  IppiSize *pRoi = gPyramid->pRoi;
  int *gStep = gPyramid->pStep;
  int *lStep = lPyramid->pStep;
  int level = gPyramid->level;
  Ipp32f *ptr;
  int step;

  ret = ippiPyramidLayerDownInitAlloc_32f_C1R(
      gState,
      ippiSize,
      rate,
      pKernel,
      maskSize,
      IPPI_INTER_LINEAR);
  if(ret!=ippStsNoErr)
    fthrow(ImageException, ippGetStatusString(ret));

  ret = ippiPyramidLayerUpInitAlloc_32f_C1R (
      lState,
      ippiSize,
      rate,
      pKernel,
      maskSize,
      IPPI_INTER_LINEAR);
  if(ret!=ippStsNoErr)
    fthrow(ImageException, ippGetStatusString(ret));

  gImage[0] = gaussimage[0].getPixelPointer();
  gStep[0] = gaussimage[0].getStepsize();
  for (int i=1; i<=level; i++)
  {
        gaussimage[i] = FloatImage(pRoi[i].width,pRoi[i].height);
    gImage[i] = gaussimage[i].getPixelPointer();
        gStep[i] = gaussimage[i].getStepsize();
    ret = ippiPyramidLayerDown_32f_C1R(
        gImage[i-1],
        gStep[i-1],
        pRoi[i-1],
        gImage[i],
        gStep[i],
        pRoi[i],
        *gState);
    if(ret!=ippStsNoErr)
      fthrow(ImageException, ippGetStatusString(ret));
  }

  ptr = ippiMalloc_32f_C1(ippiSize.width,ippiSize.height,&step);
  for (int i=level-1; i>=0; i--)
  {
        laplaceimage[i] = FloatImage(pRoi[i].width,pRoi[i].height);
    lImage[i] = laplaceimage[i].getPixelPointer();
        lStep[i] = laplaceimage[i].getStepsize();
    ret = ippiPyramidLayerUp_32f_C1R(
        gImage[i+1],
        gStep[i+1],
        pRoi[i+1],
        ptr,
        step,
        pRoi[i],
        *lState);
    if(ret!=ippStsNoErr)
      fthrow(ImageException, ippGetStatusString(ret));

    ret = ippiSub_32f_C1R(
        gImage[i],
        gStep[i],
        ptr,
        step,
        lImage[i],
        lStep[i],
        pRoi[i]);
    if(ret!=ippStsNoErr)
      fthrow(ImageException, ippGetStatusString(ret));
  }
  ippiFree(ptr);
  ippiPyramidLayerDownFree_32f_C1R(*gState);
  ippiPyramidLayerUpFree_32f_C1R (*lState);
#endif
}

GaussPyramid::~GaussPyramid()
{
    #ifdef NICE_USELIB_IPP
     IppStatus ret =  ippiPyramidFree(gPyramid);
     if(ret!=ippStsNoErr)
      fthrow(ImageException, ippGetStatusString(ret));

     ret =  ippiPyramidFree(lPyramid);
     if(ret!=ippStsNoErr)
      fthrow(ImageException, ippGetStatusString(ret));
    #endif
}

const FloatImage &GaussPyramid::getGauss(uint nr) const
{
    if(nr>gaussimage.size())
        fthrow(ImageException,"Invalid Gauss image! Largest Gauss image is nr==level!");
    return gaussimage[nr];
}

Image GaussPyramid::getGaussGray(uint nr) const
{
  FloatImage out(
      (Ipp32f*)gPyramid->pImage[nr],
      gPyramid->pRoi[nr].width,
      gPyramid->pRoi[nr].height,
      gPyramid->pStep[nr],
      GrayColorImageCommonImplementation::shallowCopy);
  Image grayOut;
  convertBitDepth(out, &grayOut);

  return grayOut;
}

const FloatImage &GaussPyramid::getLaplace(uint nr) const
{
    if(nr<1)
        fthrow(ImageException,"Invalid Laplace image! Smallest Laplace image is nr==1!");
    if(nr>laplaceimage.size())
        fthrow(ImageException,"Invalid Laplace image! Largest Laplace image is nr==level!");
    return laplaceimage[nr];
}

Coord GaussPyramid::CoordOrig(int level, const Coord &coord)
{
    Coord result;
    float fac=1;
    for(int i=0;i<level;i++)
        fac*=level;
    result.x=int(coord.x*fac+0.5);
    result.y=int(coord.y*fac+0.5);
    return result;
}

Coord GaussPyramid::CoordLevel(int level, const Coord &coord)
{
    Coord result;
    float fac=1;
    for(int i=0;i<level;i++)
        fac*=level;
    result.x=int(coord.x/fac+0.5);
    result.y=int(coord.y/fac+0.5);
    return result;
}

Coord GaussPyramid::CoordUp(int level, const Coord &coord)
{
    UNUSED_PARAMETER(level);
    Coord result;
    result.x=int(coord.x*rate+0.5);
    result.y=int(coord.y*rate+0.5);

    return result;
}

Coord GaussPyramid::CoordDown(int level, const Coord &coord)
{
    UNUSED_PARAMETER(level);
    Coord result;
    result.x=int(coord.x/rate+0.5);
    result.y=int(coord.y/rate+0.5);
    return result;
}

}//namespace NICE
