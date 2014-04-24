    /*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libimage - An image library
 * See file License for license information.
 */
#include "core/image/ColorImageT.h"


#include <fstream>
#include <sstream>

extern "C" {
 #ifdef PPM_BIGFLOATS // make sure that we read chars (see ppm.h)
    #undef PPM_BIGFLOATS
  #endif
 #ifdef NICE_USELIB_PPM
 #include <ppm.h>
 #endif
}

namespace NICE {

#ifdef NICE_USELIB_IPP
template <>
void ColorImageT<Ipp8u>::doAllocPixelIPP() {
  setPixelPointer(ippiMalloc_8u_C3(m_xsize, m_ysize, &m_rowStepsize));
  m_columnStepsize = this->channels() * sizeof(Ipp8u);
}
template <>
void ColorImageT<Ipp16s>::doAllocPixelIPP() {
  setPixelPointer(ippiMalloc_16s_C3(m_xsize, m_ysize, &m_rowStepsize));
  m_columnStepsize = this->channels() * sizeof(Ipp16s);
}
template <>
void ColorImageT<Ipp32f>::doAllocPixelIPP() {
  setPixelPointer(ippiMalloc_32f_C3(m_xsize, m_ysize, &m_rowStepsize));
  m_columnStepsize = this->channels() * sizeof(Ipp32f);
}
#endif //NICE_USELIB_IPP

#ifdef NICE_USELIB_IPP
template <>
void ColorImageT<Ipp8u>::doFromRaw(const Pixel* raw, const int stepsize) {
  IppiSize roi = {width(), height()};
  ippiCopy_8u_C3R(raw, stepsize, getPixelPointer(), getStepsize(), roi);
}
template <>
void ColorImageT<Ipp16s>::doFromRaw(const Pixel* raw, const int stepsize) {
  IppiSize roi = {width(), height()};
  ippiCopy_16s_C3R(raw, stepsize, getPixelPointer(), getStepsize(), roi);
}
template <>
void ColorImageT<Ipp32f>::doFromRaw(const Pixel* raw, const int stepsize) {
  IppiSize roi = {width(), height()};
  ippiCopy_32f_C3R(raw, stepsize, getPixelPointer(), getStepsize(), roi);
}
#endif //NICE_USELIB_IPP

template <>
void ColorImageT<Ipp8u>::readPPM(const std::string& ppmFileName,
                            const GrayColorImageCommonImplementation::MemoryLayout _memoryLayout) {
  using namespace std;
  // open the file
  ifstream file(ppmFileName.c_str(), ios::binary);

  // error handling
  if(!file.good()) {
    fthrow(ImageException,
        string("ColorImage::readPPM: Cannot open ") + ppmFileName);
  }
  PXMImageHeaderInfo header=getPXMHeaderInfo(file);

  if(header.width != m_xsize || header.height != m_ysize) {
    deallocPixel();
    allocPixel(header.width, header.height, _memoryLayout);
  }
  file.seekg(header.datapos);

  if(header.format==PPM_RAW) {
    for(int y = 0; y < header.height; y++) {
      file.read((char *)(getPixelPointerY(y)),header.width*header.channel);
    }
  } else if(header.format==PGM_RAW) {
    for (int y = 0; y < header.height; y++) {
#ifdef WIN32
		Pixel *line = new Pixel[header.width];
      file.read((char *)line,header.width);
      Pixel *target = getPixelPointerY(y);
      Pixel *src = line;
      for (int x = 0; x < header.width; x++) {
        *target++ = *src;
        *target++ = *src;
        *target++ = *src++;
      }
		delete [] line;
#else
	  Pixel line[header.width];
      file.read((char *)line,header.width);
      Pixel *target = getPixelPointerY(y);
      Pixel *src = line;
      for (int x = 0; x < header.width; x++) {
        *target++ = *src;
        *target++ = *src;
        *target++ = *src++;
      }
#endif
    }
  } else {
    fthrow(ImageException,"Format not yet implemented.");
  }
}

template <>
void ColorImageT<Ipp8u>::writePPM(const char* ppmFileName) const {
  using namespace std;
  ofstream file(ppmFileName, ios::binary);
  file << "P6" << endl << m_xsize <<" "<< m_ysize << endl << 255 << endl;
  for(int y = 0; y < m_ysize; y++) {
      file.write((char *)getPixelPointerY(y),m_xsize*3);
  }
}

} // namespace
