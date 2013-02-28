/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libimage - An image library
 * See file License for license information.
 */
#include "core/image/GrayColorImageCommonImplementation.h"


#include <fstream>
#include <sstream>

namespace NICE {
//Note: You must define the static instance, not just declare it. The definition creates the actual object you refer to. Without this line
//Visual Studio returns an undefined reference error
const GrayColorImageCommonImplementation::ShallowCopyMode GrayColorImageCommonImplementation::shallowCopy;

GrayColorImageCommonImplementation::GrayColorImageCommonImplementation() {
  m_memoryLayout = internal__foreignPointer;
}

GrayColorImageCommonImplementation::~GrayColorImageCommonImplementation() {
}

GrayColorImageCommonImplementation::MemoryLayout GrayColorImageCommonImplementation::toAllocationLayout(
                              GrayColorImageCommonImplementation::MemoryLayout _memoryLayout) {
  switch (_memoryLayout) {
  case ippAlignment:
    #ifdef NICE_USELIB_IPP
      return ippAlignment;
    #else
      return noAlignment;
    #endif
    break;
  case noAlignment:
    return noAlignment;
  default:
    fthrow(ImageException,"MemoryLayout not supported.");
    //return noAlignment;
  }
}

GrayColorImageCommonImplementation::MemoryLayout GrayColorImageCommonImplementation::toCopyLayout(
                              GrayColorImageCommonImplementation::MemoryLayout copyMode,
                              const GrayColorImageCommonImplementation& source) {
  if (copyMode == internal__foreignPointer) {
    fthrow(ImageException,
      "internal__foreignPointer is for internal purpose only.!");
  } else if (copyMode == originalAlignment) {
    if (source.m_memoryLayout != internal__foreignPointer) {
      return source.m_memoryLayout;
    } else {
      return ippAlignment;
    }
  } else {
    return copyMode;
  }
}

PXMImageHeaderInfo GrayColorImageCommonImplementation::getPXMHeaderInfo(std::ifstream &file) {
    char val;
    file.get(val);
    PXMImageHeaderInfo header;
    if(val!='P') {
        file.putback(val);
        header.format=PXM_INVALID;
        return header;
    }
    file.get(val);
    if(val>'0' && val<'8') {
        header.format=static_cast<PXMImageFormat>(val-'0');
    }
    if(header.format==PPM_IMAGE_TEXT || header.format==PPM_RAW)
      header.channel=3;
    else
      header.channel=1;

    int values=3; // header values
    if(header.format==PBM_IMAGE_TEXT || header.format==PBM_RAW) {
      values=2;
      header.maxval=1;
    }

    int status=0;
    int i=0, num=0;
    const int bsize = 1024;
    char buffer[bsize];
    while (file.good()&&num<values) {
        file.get(val);
        if(val=='#') { // omit comment
            while (file.good() && val!='\n') {
                file.get(val);
            }
            continue;
        }
        if(val>='0'&& val<='9') {
            status=1;
            buffer[i++]=val;
        } else if(status==1) {
            num++;
            buffer[i++]=' ';
            status=0;
        }
     }
    header.datapos = file.tellg();
    buffer[i]=0;
    std::stringstream stream;
    stream << buffer;
    if(values==3)
      stream >> header.width >> header.height >> header.maxval;
    else
      stream >> header.width >> header.height;
    return header;
}


} // namespace
