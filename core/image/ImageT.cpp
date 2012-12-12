/*
 * LImUn - Library for ImageT Understanding
 *  - libimage - An ImageT library
 * See file License for license information.
 */
#include "core/image/Convert.h"
#include "core/image/ImageT.h"
#include "core/image/ColorImageT.h"

#include <fstream>
#include <sstream>

namespace NICE {

#ifdef NICE_USELIB_IPP
template <>
void ImageT<Ipp8u>::doAllocPixelIPP()
{
  setPixelPointer(ippiMalloc_8u_C1(m_xsize, m_ysize, &m_rowStepsize));
  m_columnStepsize = sizeof(Ipp8u);
}
template <>
void ImageT<Ipp16s>::doAllocPixelIPP() {
  setPixelPointer(ippiMalloc_16s_C1(m_xsize, m_ysize, &m_rowStepsize));
  m_columnStepsize = sizeof(Ipp16s);
}
template <>
void ImageT<Ipp32f>::doAllocPixelIPP() {
  setPixelPointer(ippiMalloc_32f_C1(m_xsize, m_ysize, &m_rowStepsize));
  m_columnStepsize = sizeof(Ipp32f);
}
#endif //NICE_USELIB_IPP

#ifdef NICE_USELIB_IPP
template <>
void ImageT<Ipp8u>::doFromRaw(const Pixel* raw, const int stepsize) {
  IppiSize roi = {width(), height()};
  ippiCopy_8u_C1R(raw, stepsize, getPixelPointer(), getStepsize(), roi);
}
template <>
void ImageT<Ipp16s>::doFromRaw(const Pixel* raw, const int stepsize) {
  IppiSize roi = {width(), height()};
  ippiCopy_16s_C1R(raw, stepsize, getPixelPointer(), getStepsize(), roi);
}
template <>
void ImageT<Ipp32f>::doFromRaw(const Pixel* raw, const int stepsize) {
  IppiSize roi = {width(), height()};
  ippiCopy_32f_C1R(raw, stepsize, getPixelPointer(), getStepsize(), roi);
}
#endif //NICE_USELIB_IPP

template <>
void ImageT<Ipp8u>::readPGM(const std::string& pgmFileName,
                           const GrayColorImageCommonImplementation::MemoryLayout _memoryLayout) {
  // open the file
  using namespace std;
  ifstream file(pgmFileName.c_str(), ios::binary);

  // error handling
  if(!file.good()) {
    fthrow(ImageException,
        string("ImageT<P>::readPGM: Cannot open ") + pgmFileName);
  }
  PXMImageHeaderInfo header=getPXMHeaderInfo(file);
  allocPixel(header.width, header.height, _memoryLayout);
  file.seekg(header.datapos);

  if(header.format==PGM_RAW) {
    for(int y = 0; y < header.height; y++) {
      file.read((char *)(getPixelPointerY(y)),header.width*header.channel);
    }
  } else if(header.format==PPM_RAW) {
#ifdef NICE_USELIB_IPP
    Pixel line[header.height*header.width*header.channel];
    file.read((char *)line,header.height*header.width*header.channel);
    Pixel *target = getPixelPointer();
    IppiSize region;
    region.width = header.width;
    region.height = header.height;
    ippiRGBToGray_8u_C3C1R(line, header.width*header.channel, target, header.width, region);
#else
    for (int y = 0; y < header.height; y++) {
      Pixel line[header.width*header.channel];
      file.read((char *)line,header.width*header.channel);
      Pixel *target = getPixelPointerY(y);
      Pixel *src = line;
      for (int x = 0; x < header.width; x++) {
        //  // with lookup table (see firewire ColorConvert)
        // *target = pLutRg[*src]+pLutGg[*(src+1)]+pLutBg[*(src+2)];
        // *target++ += (pLutRgr[*src]+pLutGgr[*(src+1)]+pLutBgr[*(src+2)])/64;
        // src=src+3;
        *target++ = static_cast<Pixel>(*src*0.299+*(src+1)*0.587+*(src+2)*0.114);
        src=src+3;
      }
    }
#endif
  } else {
    fthrow(ImageException,"Format not yet implemented.");
  }
}

template <>
void ImageT<Ipp8u>::writePGM(const char* pgmFileName) const {
  using namespace std;
  ofstream file(pgmFileName, ios::binary);
  file << "P5" << endl << m_xsize <<" "<< m_ysize << endl << 255 << endl;
  for(int y = 0; y < m_ysize; y++) {
    file.write((char *)getPixelPointerY(y),m_xsize);
  }
}


template<>
void ImageT<Ipp8u>::invert()
{
    #ifdef NICE_USELIB_IPP
        int values[]={255,0,0};
        int levels[]={0,255,256};
        IppiSize ippiSize = {this->width(), this->height() };
        IppStatus ret = ippiLUT_Linear_C1IR(this->getPixelPointer(),
                                            this->getStepsize(),
                                            ippiSize, values, levels, 3);

        if(ret!=ippStsNoErr)
                fthrow(ImageException, ippGetStatusString(ret));
    #else
        Ipp8u* p;
        for(int y=0; y<this->height(); ++y)
        {
            p = this->getPixelPointerY(y);
            for(int x=0; x<this->width(); ++x,++p)
                *p = 255-*p;
        }
    #endif
}

} // namespace
