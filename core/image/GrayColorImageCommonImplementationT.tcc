/*
 * LImUn - Library for ImageT Understanding
 *  - libimage - An ImageT library
 * See file License for license information.
 */
#include <fstream>
#include <cmath>
#include "core/image/GrayColorImageCommonImplementationT.h"
#include "core/image/ImageFile.h"

namespace NICE {

template <class P>
GrayColorImageCommonImplementationT<P>::GrayColorImageCommonImplementationT() {
  setPixelPointer(NULL);
  m_xsize = 0;
  m_ysize = 0;
  // the step size are measured in bytes!!
  m_rowStepsize = 1;
  m_columnStepsize = sizeof(P);
}

template <class P>
bool GrayColorImageCommonImplementationT<P>::isAligned() const {
  if (m_memoryLayout == GrayColorImageCommonImplementation::noAlignment)
    return false;
  if (bytedepth() * m_xsize * channels() == m_rowStepsize)
    return false;
  return true;
}


template <class P>
void GrayColorImageCommonImplementationT<P>::resize(const int width,
                       const int height,
                       const GrayColorImageCommonImplementation::MemoryLayout _memoryLayout) {
  if(m_pixelConst != NULL && m_memoryLayout==internal__foreignPointer)
      fthrow(ImageException, "resize of image with foreignPointer requested.");
  deallocPixel();
  allocPixel(width, height, _memoryLayout);
}

template <class P>
void GrayColorImageCommonImplementationT<P>::allocPixel(const int width, const int height,
                           const GrayColorImageCommonImplementation::MemoryLayout _memoryLayout) {
  if (getPixelPointer() != NULL) {
    if (width == m_xsize && height == m_ysize && m_memoryLayout == _memoryLayout) {
      return;
    } else {
      deallocPixel();
    }
  }

  m_xsize = width;
  m_ysize = height;

  m_memoryLayout = toAllocationLayout(_memoryLayout);
  switch (m_memoryLayout) {
  case ippAlignment:
    doAllocPixelIPP();
    break;
  case noAlignment:
    doAllocPixelNoAlignment();
    break;
  default:
    fthrow(ImageException, "Invalid or unknown MemoryLayout.");
  }
}

template <class P>
void GrayColorImageCommonImplementationT<P>::deallocPixel() {
  if (getPixelPointer() != NULL) {
    switch (m_memoryLayout) {
    case ippAlignment:
#ifdef NICE_USELIB_IPP
      ippiFree(getPixelPointer());
      // break inside #ifdef uses next case if NICE_USELIB_IPP is not set
      break;
#endif
    case noAlignment:
      delete[] getPixelPointer();
      break;
    case internal__foreignPointer:
      // nothing to do
      break;
    default:
      fthrow(ImageException, "Invalid or unknown MemoryLayout.");
    }
    setPixelPointer(NULL);
  }
}

template <class P>
GrayColorImageCommonImplementationT<P>::~GrayColorImageCommonImplementationT<P>() {
  deallocPixel();
}

template <class P>
void GrayColorImageCommonImplementationT<P>::setForeignPointer(Pixel* raw,
                                  const int width,
                                  const int height,
                                  const int rowStepsize,
                                  const int columnStepsize) {
  m_memoryLayout = internal__foreignPointer;
  m_xsize = width;
  m_ysize = height;
  this->m_rowStepsize = rowStepsize;
  this->m_columnStepsize = columnStepsize;
  setPixelPointer(raw);
}

template <class P>
void GrayColorImageCommonImplementationT<P>::setForeignPointerConst(const Pixel* raw,
                                       const int width,
                                       const int height,
                                       const int rowStepsize,
                                       const int columnStepsize) {
  m_memoryLayout = internal__foreignPointer;
  m_xsize = width;
  m_ysize = height;
  this->m_rowStepsize = rowStepsize;
  this->m_columnStepsize = columnStepsize;
  setPixelPointerConst(raw);
}


template <class P>
void GrayColorImageCommonImplementationT<P>::write(const ImageFile &file) const {
    file.writer(this);
}

template <class P>
void GrayColorImageCommonImplementationT<P>::read(ImageFile file/*,
                     const GrayColorImageCommonImplementation::MemoryLayout _memoryLayout*/) {
    file.reader(this);
}


template <class P>
void GrayColorImageCommonImplementationT<P>::readPXM(const std::string& pxmFileName,
                        const GrayColorImageCommonImplementation::MemoryLayout _memoryLayout) {
  using namespace std;
  // open the file
  ifstream file(pxmFileName.c_str(), ios::binary);

  // error handling
  if(!file.good()) {
    fthrow(ImageException,
        string("ColorImage::readPXM: Cannot open ") + pxmFileName);
  }
  PXMImageHeaderInfo header=getPXMHeaderInfo(file);

  if(header.width != m_xsize || header.height != m_ysize) {
    deallocPixel();
    allocPixel(header.width, header.height, _memoryLayout);
  }
  file.seekg(header.datapos);

  int srcbytedepth=0;
  if(header.maxval<256)
    srcbytedepth=1;
  else if (header.maxval<65536)
    srcbytedepth=2;
  else
    fthrow(ImageException,"Format not yet implemented.");

  if(srcbytedepth != bytedepth())
    fthrow(ImageException,"Cannot read Image: Different bit depths.");
  if(header.channel==channels())
    fthrow(ImageException,"Cannot read Image: Different number of channels().");

  if(header.format==PPM_RAW || header.format==PGM_RAW) {
  for(int y = 0; y < header.height; y++) {
      file.read(reinterpret_cast<char *>(getPixelPointerY(y)),header.width*header.channel*srcbytedepth);
  }
  } else
    fthrow(ImageException,"Cannot read this Format. This is not yet implemented.");
}


template <class P>
void GrayColorImageCommonImplementationT<P>::writePXM(const char* pxmFileName) const {
  using namespace std;
  ofstream file(pxmFileName, ios::binary);
  if(channels()==1)
    file << "P5" << endl;
  else if(channels()==3)
    file << "P6" << endl;
  else
  fthrow(ImageException,"Cannot write this Format. This is not yet implemented.");
  file << m_xsize <<" "<< m_ysize << endl;
  file << static_cast<int>(std::pow(2.0,bitdepth())-1) << endl;
  for(int y = 0; y < m_ysize; y++) {
      file.write(reinterpret_cast<char *>(getPixelPointerY(y)),m_xsize*channels()*bytedepth());
  }
}

} // namespace
