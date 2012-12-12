#include "core/image/MultiChannelImageT.h"

using namespace NICE;

#define SET_FUNCS_MACRO(MYTYPE) \
  template <> \
  int MultiChannelImageT<MYTYPE>::getPixelInt(int x, int y, int channel) const \
  { \
    return (int)get(x,y,channel); \
  } \
  \
  template<>\
  double MultiChannelImageT<MYTYPE>::getPixelFloat(int x, int y, int channel) const\
  {\
    return (double)get(x,y,channel);\
  }\
  template<>\
  void MultiChannelImageT<MYTYPE>::setPixelInt(int x, int y, int channel, int pixel)\
  {\
    set(x,y,(MYTYPE)pixel,channel);\
  }\
  \
  template<>\
  void MultiChannelImageT<MYTYPE>::setPixelFloat(int x, int y, int channel, double pixel)\
  {\
    set(x,y,(MYTYPE)pixel,channel);\
  }

SET_FUNCS_MACRO ( int )
SET_FUNCS_MACRO ( long int )
SET_FUNCS_MACRO ( double )
SET_FUNCS_MACRO ( float )
SET_FUNCS_MACRO ( unsigned int )

