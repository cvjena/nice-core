/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libimage - An image library
 * See file License for license information.
 */
#ifndef _LIMUNIMAGE_IPPWRAPPER_H
#define _LIMUNIMAGE_IPPWRAPPER_H



#ifdef NICE_USELIB_IPP

  #include <ippdefs.h>
  #include "ippi.h"
  #include <ipps.h>
  #include <ippcv.h>
  #include <ippcore.h>
  #include <ippcc.h>

#else // NICE_USELIB_IPP

  #ifndef IPPWRAPPER_DEFS
  #define IPPWRAPPER_DEFS
        typedef unsigned char       Ipp8u;
        typedef char                Ipp8s;
        typedef signed short        Ipp16s;
        typedef unsigned short      Ipp16u;
        typedef signed int          Ipp32s;
        typedef unsigned int        Ipp32u;
        typedef float               Ipp32f;
        typedef double              Ipp64f;
        typedef long long           Ipp64s;
        typedef unsigned long long  Ipp64u;

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

  enum {
  IPPI_INTER_NN     = 1,
  IPPI_INTER_LINEAR = 2,
  IPPI_INTER_CUBIC  = 4,
  IPPI_INTER_SUPER  = 8,
  IPPI_SMOOTH_EDGE  = (1 << 31)
  };

  typedef struct {
  int x;
  int y;
  int width;
  int height;
  } IppiRect;

  typedef struct {
  int x;
  int y;
  } IppiPoint;

  typedef struct {
    int width;
    int height;
  } IppiSize;

  typedef enum {
  ippAxsHorizontal,
  ippAxsVertical,
  ippAxsBoth
  } IppiAxis;

  typedef enum _IppiBorderType {
  ippBorderConst     =  0,
      ippBorderRepl      =  1,
      ippBorderWrap      =  2,
      ippBorderMirror    =  3,
      ippBorderMirrorR   =  4,
      ippBorderMirror2   =  5,
      ippBorderInMem     =  6,
      ippBorderInMemTop     =  0x0010,
      ippBorderInMemBottom  =  0x0020
  } IppiBorderType;

  typedef enum {
  ippDitherNone,
  ippDitherFS,
  ippDitherJJN,
  ippDitherStucki,
      ippDitherBayer
  } IppiDitherType;

  typedef enum _IppiMaskSize {
  ippMskSize1x3 = 13,
  ippMskSize1x5 = 15,
  ippMskSize3x1 = 31,
  ippMskSize3x3 = 33,
  ippMskSize5x1 = 51,
  ippMskSize5x5 = 55
  } IppiMaskSize;

  typedef enum {
      ippAlphaOver,
      ippAlphaIn,
      ippAlphaOut,
      ippAlphaATop,
      ippAlphaXor,
      ippAlphaPlus,
      ippAlphaOverPremul,
      ippAlphaInPremul,
      ippAlphaOutPremul,
      ippAlphaATopPremul,
      ippAlphaXorPremul,
      ippAlphaPlusPremul
  } IppiAlphaType;

  typedef enum _IppiNorm {
    ippiNormInf = 0,
    ippiNormL1 = 1,
    ippiNormL2 = 2
  } IppiNorm;

  typedef enum _IppiKernelType {
    ippKernelSobel     =  0,
    ippKernelScharr    =  1
  } IppiKernelType;

  typedef struct _IppiConnectedComp {
    Ipp64f   area;  /*  area of the segmented component  */
    Ipp64f   value[3]; /*  gray scale value of the segmented component  */
    IppiRect rect;  /*  bounding rectangle of the segmented component  */
  } IppiConnectedComp;

  typedef struct _IppiPyramid {
    Ipp8u         **pImage;
    IppiSize      *pRoi;
    Ipp64f        *pRate;
    int           *pStep;
    Ipp8u         *pState;
    int            level;
//    int            channels;
//    int            depth;
  } IppiPyramid;

  typedef struct {
    Ipp32f x;
    Ipp32f y;
  } IppiPoint_32f;

  struct ipcvHaarClassifier_32f;
  typedef struct ipcvHaarClassifier_32f IppiHaarClassifier_32f;

  struct ipcvHaarClassifier_32s;
  typedef struct ipcvHaarClassifier_32s IppiHaarClassifier_32s;

  struct MomentState64f;
  struct MomentState64s;

  typedef struct MomentState64f IppiMomentState_64f;
  typedef struct MomentState64s IppiMomentState_64s;

  struct ipcvMorphState;
  typedef struct ipcvMorphState IppiMorphState;

  struct ipcvMorphAdvState;
  typedef struct ipcvMorphAdvState IppiMorphAdvState;

  struct ipcvMorphGrayState_8u;
  typedef struct ipcvMorphGrayState_8u IppiMorphGrayState_8u;

  struct ipcvMorphGrayState_32f;
  typedef struct ipcvMorphGrayState_32f IppiMorphGrayState_32f;

  struct OptFlowPyrLK;
  typedef struct OptFlowPyrLK IppiOptFlowPyrLK;
  typedef IppiOptFlowPyrLK IppiOptFlowPyrLK_8u_C1R;
  typedef IppiOptFlowPyrLK IppiOptFlowPyrLK_16u_C1R;
  typedef IppiOptFlowPyrLK IppiOptFlowPyrLK_32f_C1R;

  struct DeconvFFTState_32f_C1R;
  typedef struct DeconvFFTState_32f_C1R IppiDeconvFFTState_32f_C1R;

  struct DeconvFFTState_32f_C3R;
  typedef struct DeconvFFTState_32f_C3R IppiDeconvFFTState_32f_C3R;

  struct DeconvLR_32f_C1R;
  typedef struct DeconvLR_32f_C1R IppiDeconvLR_32f_C1R;

  struct DeconvLR_32f_C3R;
  typedef struct DeconvLR_32f_C3R IppiDeconvLR_32f_C3R;

  struct DFT2DSpec_C_32fc; 
  typedef struct DFT2DSpec_C_32fc IppiDFTSpec_C_32fc;

  struct DFT2DSpec_R_32f;
  typedef struct DFT2DSpec_R_32f IppiDFTSpec_R_32f;

  struct DFT2DSpec_R_32s;
  typedef struct DFT2DSpec_R_32s IppiDFTSpec_R_32s;

  struct FFT2DSpec_C_32fc;
  typedef struct FFT2DSpec_C_32fc IppiFFTSpec_C_32fc;

  struct FFT2DSpec_R_32f;
  typedef struct FFT2DSpec_R_32f IppiFFTSpec_R_32f;

  struct FFT2DSpec_R_32s;
  typedef struct FFT2DSpec_R_32s IppiFFTSpec_R_32s;

  struct DCT2DFwdSpec_32f;
  typedef struct DCT2DFwdSpec_32f IppiDCTFwdSpec_32f;

  struct DCT2DInvSpec_32f;
  typedef struct DCT2DInvSpec_32f IppiDCTInvSpec_32f;

  struct iWTFwdSpec_32f_C1R;
  typedef struct iWTFwdSpec_32f_C1R IppiWTFwdSpec_32f_C1R;

  struct iWTInvSpec_32f_C1R;
  typedef struct iWTInvSpec_32f_C1R IppiWTInvSpec_32f_C1R;

  struct iWTFwdSpec_32f_C3R;
  typedef struct iWTFwdSpec_32f_C3R IppiWTFwdSpec_32f_C3R;

  struct iWTInvSpec_32f_C3R;
  typedef struct iWTInvSpec_32f_C3R IppiWTInvSpec_32f_C3R;

#endif // !NICE_USELIB_IPP

//#ifdef __GNUC__
#include "core/image/ippwrapper.tcc"
//#endifö

#endif
