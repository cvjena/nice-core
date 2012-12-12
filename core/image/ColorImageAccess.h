/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libimage - An image library
 * See file License for license information.
 */

#ifndef _LIMUN_MULTICHANNELIMAGEACESS_H
#define _LIMUN_MULTICHANNELIMAGEACESS_H

#include <core/image/MultiChannelImageAccess.h>

namespace NICE {

/**
 * A MultiChannelImageAccess with guaranteed channels() == 3.
 *
 * @author Ferid Bajramovic
 */
class ColorImageAccess : public MultiChannelImageAccess {
public:
  virtual int channels() const; // FIXME is it a good idea to return constant 3 here?

  ColorImageAccess () {};
};

} // namespace

#endif
