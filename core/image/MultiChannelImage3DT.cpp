#include "core/image/MultiChannelImage3DT.h"

using namespace NICE;

#define SET_FUNCS_MACRO(MYTYPE) \
  template <> \
  int MultiChannelImage3DT<MYTYPE>::getPixelInt(int x, int y, int z, int channel) const \
  { \
    return (int)get(x,y,z,channel); \
  } \
  \
  template<>\
  double MultiChannelImage3DT<MYTYPE>::getPixelFloat(int x, int y, int z, int channel) const\
  {\
    return (double)get(x,y,z,channel);\
  }\
  template<>\
  void MultiChannelImage3DT<MYTYPE>::setPixelInt(int x, int y, int z, int channel, int pixel)\
  {\
    set(x,y,z,(MYTYPE)pixel,channel);\
  }\
  \
  template<>\
  void MultiChannelImage3DT<MYTYPE>::setPixelFloat(int x, int y, int z, int channel, double pixel)\
  {\
    set(x,y,z,(MYTYPE)pixel,channel);\
  }

SET_FUNCS_MACRO ( int )
SET_FUNCS_MACRO ( long int )
SET_FUNCS_MACRO ( double )
SET_FUNCS_MACRO ( float )
SET_FUNCS_MACRO ( unsigned int )

