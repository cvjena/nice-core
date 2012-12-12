/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libimage - An image library
 * See file License for license information.
 */
#ifndef _LIMUNBASICVECTOR_IPPWRAPPER_H
#define _LIMUNBASICVECTOR_IPPWRAPPER_H



#ifdef NICE_USELIB_IPP
    #include <ipps.h>
    #include <ippcv.h>

  #if NICE_USELIB_IPP >= 4
    #include <ippcore.h>
    #include <ipps.h>
    #include <ippm.h>
  #else
    #warning "Not fully supported with IPP < 4"
  #endif

#else // NICE_USELIB_IPP

  #ifndef IPPWRAPPER_DEFS
  #define IPPWRAPPER_DEFS
    typedef unsigned char Ipp8u;
    typedef signed short Ipp16s;
    typedef unsigned short Ipp16u;
    typedef signed int Ipp32s;
    typedef unsigned int Ipp32u;
    typedef float Ipp32f;
    typedef double Ipp64f;

    typedef enum {
            ippStsSingularErr           = -195,
      ippStsDataTypeErr           = -12, 
      ippStsOutOfRangeErr         = -11,
      ippStsDivByZeroErr          = -10, 
      ippStsMemAllocErr           = -9, 
      ippStsNullPtrErr            = -8,
      ippStsRangeErr              = -7, 
      ippStsSizeErr               = -6,  
      ippStsBadArgErr             = -5,  
      ippStsNoMemErr              = -4, 
      ippStsErr                   = -2, 
      ippStsNoErr                 =  0, 
      ippStsDivByZero             =  6
    } IppStatus;

        #define ippStsOk ippStsNoErr

    typedef enum {
      ippCmpLess,
      ippCmpLessEq,
      ippCmpEq,
      ippCmpGreaterEq,
      ippCmpGreater
    } IppCmpOp;

    typedef enum {
      ippAlgHintNone,
      ippAlgHintFast,
      ippAlgHintAccurate
    } IppHintAlgorithm;

    typedef enum {
      ippRndZero,
      ippRndNear
    } IppRoundMode;
  #endif // IPPWRAPPER_DEFS

typedef char Ipp8s;
typedef long long Ipp64s;
typedef unsigned long long Ipp64u;  

    struct RandUniState_8u;
    struct RandUniState_16s;
    struct RandUniState_32f;
                                                                                                                                                                        
    struct RandGaussState_8u;
    struct RandGaussState_16s;
    struct RandGaussState_32f;
                                                                                                                                                                        
    typedef struct RandGaussState_8u IppsRandGaussState_8u;
    typedef struct RandGaussState_16s IppsRandGaussState_16s;
    typedef struct RandGaussState_32f IppsRandGaussState_32f;
    typedef struct RandUniState_8u IppsRandUniState_8u;
    typedef struct RandUniState_16s IppsRandUniState_16s;
    typedef struct RandUniState_32f IppsRandUniState_32f;

typedef struct {
    Ipp8s  re;
    Ipp8s  im;
} Ipp8sc;
                                                                                                                                                                     
typedef struct {
    Ipp16s  re;
    Ipp16s  im;
} Ipp16sc;
                                                                                                                                                                     
typedef struct {
    Ipp32s  re;
    Ipp32s  im;
} Ipp32sc;
                                                                                                                                                                     
typedef struct {
    Ipp32f  re;
    Ipp32f  im;
} Ipp32fc;
                                                                                                                                                                     
typedef struct {
    Ipp64s  re;
    Ipp64s  im;
} Ipp64sc;
                                                                                                                                                                     
typedef struct {
    Ipp64f  re;
    Ipp64f  im;
} Ipp64fc;

const char *ippGetStatusString(IppStatus status);

#endif // !NICE_USELIB_IPP

//#ifdef __GNUC__
  #include <core/vector/ippwrapper.tcc>
//#endif

#endif
