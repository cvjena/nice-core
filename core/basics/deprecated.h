/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libfbasics - library of some basic tools
 * See file License for license information.
 */
#ifndef _FBASICS_DEPRECATED_H
#define _FBASICS_DEPRECATED_H

#if (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 1))
#define LIMUN_DEPRECATED  __attribute__((__deprecated__))
#else
#define LIMUN_DEPRECATED
#endif /* __GNUC__ */

namespace NICE {
};

#endif
