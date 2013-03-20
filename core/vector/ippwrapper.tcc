#include <core/vector/ippwrapper.h>
#include <core/basics/RoundToNearest.h>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <functional>

template<class P>
inline IppStatus ippsCopy( const P* pSrc, P* pDst, int len ) {
 std::copy(pSrc,pSrc+len,pDst);
 return ippStsNoErr;
}
template<class P>
inline IppStatus ippsMove( const P* pSrc, P* pDst, int len ) {
 P buffer[len];
 std::copy(pSrc,pSrc+len,buffer);
 std::copy(buffer,buffer+len,pDst);
 return ippStsNoErr;
}
template<class P>
inline IppStatus ippsZero( P* pDst, int len ) {
 std::fill(pDst, pDst+len, 0);
 return ippStsNoErr;
}
template<class P>
inline IppStatus ippsSet( P val, P* pDst, int len ) {
 std::fill(pDst, pDst+len, val);
 return ippStsNoErr;
}

template<class P>
inline IppStatus ippsRandUniform_Direct(P* pDst, int len, P low, P high,
                                               unsigned int* pSeed) 
{
  srand(*pSeed);
  for(int i=0;i<len;i++)
    pDst[i] = low+static_cast<P>((high-low)*(rand()/static_cast<float>(RAND_MAX))+0.5)-static_cast<P>(0.5);

  return(ippStsNoErr);
}

/*
The polar form of the Box-Muller transformation is both faster and more robust numerically.

         float x1, x2, w, y1, y2;
 
         do {
                 x1 = 2.0 * ranf() - 1.0;
                 x2 = 2.0 * ranf() - 1.0;
                 w = x1 * x1 + x2 * x2;
         } while ( w >= 1.0 );

         w = sqrt( (-2.0 * ln( w ) ) / w );
         y1 = x1 * w;
         y2 = x2 * w;
*/

template<class P>
inline IppStatus ippsRandGauss_Direct(P* pDst, int len, P mean, P stdev,
                                            unsigned int* pSeed) {
    srand(*pSeed);
  double s,v1,v2;
  for(int i=0;i<len/2;i++) {
    do {
      v1=2.0*rand()/(RAND_MAX+1.0)-1.0;
      v2=2.0*rand()/(RAND_MAX+1.0)-1.0;
      s = v1*v1+v2*v2;  
    } while(s >= 1.0);
    pDst[i] = static_cast<P>(v1 * stdev * sqrt(-2.0*log(s)/s)+mean);
    pDst[i+len/2] = static_cast<P>(v2 * stdev * sqrt(-2.0*log(s)/s)+mean);
  }
  if(len&1) {
    do {
      v1=2.0*rand()/(RAND_MAX+1.0)-1.0;
      v2=2.0*rand()/(RAND_MAX+1.0)-1.0;
      s = v1*v1+v2*v2;  
    } while(s >= 1);
    pDst[len-1] = static_cast<P>(v1 * stdev * sqrt(-2*log(s)/s)+mean);
  } 
    return ippStsNoErr;
}

template<class P>
inline IppStatus ippsRandUniformInitAlloc(IppsRandUniState_8u** pRandUniState,
                                   P low, P high, unsigned int seed) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsRandUniformInitAlloc(IppsRandUniState_16s** pRandUniState,
                                   P low, P high, unsigned int seed) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsRandUniformInitAlloc(IppsRandUniState_32f** pRandUniState,
                                   P low, P high, unsigned int seed) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsRandUniform(P* pDst,  int len, IppsRandUniState_8u* pRandUniState) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsRandUniform(P* pDst, int len, IppsRandUniState_16s* pRandUniState) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsRandUniform(P* pDst, int len, IppsRandUniState_32f* pRandUniState) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsRandGaussInitAlloc(IppsRandGaussState_8u** pRandGaussState,
                                   P mean, P stdDev, unsigned int seed) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsRandGaussInitAlloc(IppsRandGaussState_16s** pRandGaussState,
                                   P mean, P stdDev, unsigned int seed) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsRandGaussInitAlloc(IppsRandGaussState_32f** pRandGaussState,
                                   P mean, P stdDev, unsigned int seed) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsRandGauss(P* pDst,  int len, IppsRandGaussState_8u*  pRandGaussState) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsRandGauss(P* pDst, int len, IppsRandGaussState_16s* pRandGaussState) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsRandGauss(P* pDst, int len, IppsRandGaussState_32f* pRandGaussState) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsRandGaussInit(IppsRandGaussState_16s* pRandGaussState,
                                   P mean, P stdDev, unsigned int seed) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsRandUniformInit(IppsRandUniState_16s* pRandUniState,
                                   P low, P high, unsigned int seed) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsVectorJaehne(P*  pDst, int len, P magn) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsVectorRamp(P*  pDst, int len, float offset, float slope) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsReal(const P* pSrc, Ipp64f* pDstRe, int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsReal(const P* pSrc, Ipp32f* pDstRe, int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsReal(const P* pSrc, Ipp16s* pDstRe, int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsImag(const P* pSrc, Ipp64f* pDstIm, int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsImag(const P* pSrc, Ipp32f* pDstIm, int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsImag(const P* pSrc, Ipp16s* pDstIm, int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsCplxToReal( const P* pSrc, Ipp64f* pDstRe,
       Ipp64f* pDstIm, int len ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsCplxToReal( const P* pSrc, Ipp32f* pDstRe,
       Ipp32f* pDstIm, int len ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsCplxToReal( const P* pSrc, Ipp16s* pDstRe,
       Ipp16s* pDstIm, int len ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsRealToCplx( const P* pSrcRe,
       const P* pSrcIm, Ipp64fc* pDst, int len ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsRealToCplx( const P* pSrcRe,
       const P* pSrcIm, Ipp32fc* pDst, int len ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsRealToCplx( const P* pSrcRe,
       const P* pSrcIm, Ipp16sc* pDst, int len ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsConj_I( P* pSrcDst, int len ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsConj( const P* pSrc, P* pDst, int len ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsConjFlip( const P* pSrc, P* pDst, int len ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsConjCcs_I( P* pSrcDst, int lenDst ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsConjCcs( const Ipp64f* pSrc, P* pDst, int lenDst ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsConjCcs( const Ipp32f* pSrc, P* pDst, int lenDst ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsConjCcs( const Ipp16s* pSrc, P* pDst, int lenDst ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsConjPack_I( P* pSrcDst, int lenDst ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsConjPack( const Ipp64f* pSrc, P* pDst, int lenDst ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsConjPack( const Ipp32f* pSrc, P* pDst, int lenDst ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsConjPack( const Ipp16s* pSrc, P* pDst, int lenDst ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsConjPerm_I( P* pSrcDst, int lenDst ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsConjPerm( const Ipp64f* pSrc, P* pDst, int lenDst ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsConjPerm( const Ipp32f* pSrc, P* pDst, int lenDst ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsConjPerm( const Ipp16s* pSrc, P* pDst, int lenDst ) {
 return ippStsDataTypeErr;
}
template<class P1, class P2>
inline IppStatus ippsConvert(const P1* pSrc,P2* pDst,int len) {
 return ippStsDataTypeErr;
}
template<class P1, class P2>
inline IppStatus ippsConvert_Sfs(const P1* pSrc, P2* pDst,
       int len, IppRoundMode rndmode, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P1, class P2>
inline IppStatus ippsConvert_Sfs( const P1* pSrc, P2* pDst, int len, int scaleFactor ) {
 return ippStsDataTypeErr;
}
template<class P1, class P2>
inline IppStatus ippsConvert(const P1* pSrc,P2* pDst,int len,IppRoundMode rndmode) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsThreshold_I( P* pSrcDst, int len,
       P level, IppCmpOp relOp ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsThreshold_I( P* pSrcDst, int len,
       Ipp32f level, IppCmpOp relOp ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsThreshold_I( P* pSrcDst, int len,
       Ipp64f level, IppCmpOp relOp ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsThreshold_I( P* pSrcDst, int len,
       Ipp16s level,  IppCmpOp relOp ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsThreshold( const P* pSrc, P* pDst,
       int len, P level, IppCmpOp relOp ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsThreshold( const P* pSrc, P* pDst,
       int len, Ipp32f level, IppCmpOp relOp ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsThreshold( const P* pSrc, P* pDst,
       int len, Ipp64f level, IppCmpOp relOp ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsThreshold( const P* pSrc, P* pDst,
       int len, Ipp16s level, IppCmpOp relOp) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsThreshold_LT_I( P* pSrcDst, int len,
       P level ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsThreshold_LT_I( P* pSrcDst, int len,
       Ipp32f level ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsThreshold_LT_I( P* pSrcDst, int len,
       Ipp64f level ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsThreshold_LT_I( P* pSrcDst, int len,
       Ipp16s level ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsThreshold_LT( const P* pSrc, P* pDst,
       int len, P level ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsThreshold_LT( const P* pSrc, P* pDst,
       int len, Ipp32f level ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsThreshold_LT( const P* pSrc, P* pDst,
       int len, Ipp64f level ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsThreshold_LT( const P* pSrc, P* pDst,
       int len, Ipp16s level ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsThreshold_GT_I( P* pSrcDst, int len,
       P level ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsThreshold_GT_I( P* pSrcDst, int len,
       Ipp32f level ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsThreshold_GT_I( P* pSrcDst, int len,
       Ipp64f level ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsThreshold_GT_I( P* pSrcDst, int len,
       Ipp16s level ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsThreshold_GT( const P* pSrc, P* pDst,
       int len, P level ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsThreshold_GT( const P* pSrc, P* pDst,
       int len, Ipp32f level ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsThreshold_GT( const P* pSrc, P* pDst,
       int len, Ipp64f level ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsThreshold_GT( const P* pSrc, P* pDst,
       int len, Ipp16s level ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsThreshold_LTAbs(const P* pSrc, P *pDst,
       int len, P level) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsThreshold_LTAbs_I(P *pSrcDst,
       int len, P level) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsThreshold_GTAbs(const P* pSrc, P *pDst,
       int len, P level) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsThreshold_GTAbs_I(P *pSrcDst,
       int len, P level) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsThreshold_LTVal_I( P* pSrcDst, int len,
       P level, P value ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsThreshold_LTVal_I( P* pSrcDst, int len,
       Ipp32f level, P value ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsThreshold_LTVal_I( P* pSrcDst, int len,
       Ipp64f level, P value ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsThreshold_LTVal_I( P* pSrcDst, int len,
       Ipp16s level, P value ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsThreshold_LTVal( const P* pSrc, P* pDst,
       int len, P level, P value ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsThreshold_LTVal( const P* pSrc, P* pDst,
       int len, Ipp32f level, P value ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsThreshold_LTVal( const P* pSrc, P* pDst,
       int len, Ipp64f level, P value ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsThreshold_LTVal( const P* pSrc, P* pDst,
       int len, Ipp16s level, P value ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsThreshold_GTVal_I( P* pSrcDst, int len,
       P level, P value ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsThreshold_GTVal_I( P* pSrcDst, int len,
       Ipp32f level, P value ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsThreshold_GTVal_I( P* pSrcDst, int len,
       Ipp64f level, P value ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsThreshold_GTVal_I( P* pSrcDst, int len,
       Ipp16s level, P value ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsThreshold_GTVal( const P* pSrc, P* pDst,
       int len, P level, P value ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsThreshold_GTVal( const P* pSrc, P* pDst,
       int len, Ipp32f level, P value ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsThreshold_GTVal( const P* pSrc, P* pDst,
       int len, Ipp64f level, P value ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsThreshold_GTVal( const P* pSrc, P* pDst,
       int len, Ipp16s level, P value ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsThreshold_LTInv_I(P* pSrcDst,int len,P level) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsThreshold_LTInv_I(P* pSrcDst,int len,Ipp32f level) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsThreshold_LTInv_I(P* pSrcDst,int len,Ipp64f level) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsThreshold_LTInv(const P* pSrc,P* pDst,int len,P level) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsThreshold_LTInv(const P* pSrc,P* pDst,int len,Ipp32f level) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsThreshold_LTInv(const P* pSrc,P* pDst,int len,Ipp64f level) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsCartToPolar(const P* pSrc, Ipp32f* pDstMagn,
                                                   Ipp32f* pDstPhase, int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsCartToPolar(const P* pSrc, Ipp64f* pDstMagn,
                                                   Ipp64f* pDstPhase, int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsCartToPolar(const P* pSrcRe, const P*
                        pSrcIm, P* pDstMagn, P* pDstPhase, int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsPolarToCart(const Ipp32f* pSrcMagn,
                  const Ipp32f* pSrcPhase, P* pDst, int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsPolarToCart(const Ipp64f* pSrcMagn,
                  const Ipp64f* pSrcPhase, P* pDst, int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsPolarToCart(const P* pSrcMagn,
                  const P* pSrcPhase, P* pDstRe, P* pDstIm, int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsCartToPolar_Sfs(const P* pSrc, Ipp16s* pDstMagn, Ipp16s* pDstPhase, int len, int magnScaleFactor, int phaseScaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsPolarToCart_Sfs(const Ipp16s* pSrcMagn, const Ipp16s* pSrcPhase, P* pDst, int len, int magnScaleFactor, int phaseScaleFactor) {
 return ippStsDataTypeErr;
}
template<class P1, class P2>
inline IppStatus ippsALawToLin(const P1* pSrc, P2* pDst, int len) {
 return ippStsDataTypeErr;
}
template<class P1, class P2>
inline IppStatus ippsMuLawToLin(const P1* pSrc, P2* pDst, int len) {
 return ippStsDataTypeErr;
}
template<class P1, class P2>
inline IppStatus ippsLinToALaw(const P1* pSrc, P2* pDst, int len) {
 return ippStsDataTypeErr;
}
template<class P1, class P2>
inline IppStatus ippsLinToMuLaw(const P1* pSrc, P2* pDst, int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsALawToMuLaw(const P* pSrc, P* pDst, int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsMuLawToALaw(const P* pSrc, P* pDst, int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsPreemphasize(P* pSrcDst, int len, P val) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsPreemphasize(P* pSrcDst, int len, Ipp32f val) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFlip( const P* pSrc, P* pDst, int len ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFlip_I( P* pSrcDst, int len ) {
 P *src=pSrcDst;
 P *dst=pSrcDst+len-1;
 for(int i=0;i<len/2;i++)
    std::swap(*src++,*dst--);
 return ippStsNoErr;
}
template<class P1, class P2>
inline IppStatus ippsUpdateLinear_I(const P1* pSrc,int len,
       P2* pSrcDst, int srcShiftRight,P1 alpha, IppHintAlgorithm hint=ippAlgHintNone) {
 return ippStsDataTypeErr;
}
template<class P1, class P2>
inline IppStatus ippsUpdatePower_I(const P1* pSrc,int len,
       P2* pSrcDst, int srcShiftRight,P1 alpha, IppHintAlgorithm hint=ippAlgHintNone) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsSwapBytes_I( P* pSrcDst, int len ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsSwapBytes( const P* pSrc, P* pDst, int len ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsAddC_I(P  val, P*  pSrcDst, int len) {
  P *dst=pSrcDst;
  for (int i=0;i<len;i++) {
      *(dst++) += val; 
  }
  return ippStsNoErr;
}
template<class P>
inline IppStatus ippsSubC_I(P  val, P*  pSrcDst, int len) {
  P *dst=pSrcDst;
  for (int i=0;i<len;i++) {
      *(dst++) -= val; 
  }
  return ippStsNoErr;
}
template<class P>
inline IppStatus ippsMulC_I(P  val, P*  pSrcDst, int len) {
  P *dst=pSrcDst;
  for (int i=0;i<len;i++) {
      *(dst++) *= val;
  }
  return ippStsNoErr;
}
template<class P>
inline IppStatus ippsSubCRev_I(P  val, P*  pSrcDst, int len) {
 return ippStsDataTypeErr;
}
template<class P1, class P2>
inline IppStatus ippsMulC_Sfs(const P1*  pSrc, P1  val,
       P2*  pDst, int len, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P1, class P2>
inline IppStatus ippsMulC_Low(const P1*  pSrc, P1  val,
       P2*  pDst, int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsAddC_ISfs(P   val, P*   pSrcDst,
       int len, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsSubC_ISfs(P   val, P*   pSrcDst,
       int len, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsSubCRev_ISfs(P   val, P*   pSrcDst,
       int len, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsMulC_ISfs(P   val, P*   pSrcDst,
       int len, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsAddC(const P*  pSrc, P  val,
       P*  pDst, int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsSubC(const P*  pSrc, P  val,
       P*  pDst, int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsSubCRev(const P*  pSrc, P  val,
       P*  pDst, int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsMulC(const P*  pSrc, P  val,
       P*  pDst, int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsAddC_Sfs(const P*   pSrc, P   val,
       P*   pDst, int len, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsSubC_Sfs(const P*   pSrc, P   val,
       P*   pDst, int len, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsSubCRev_Sfs(const P*   pSrc, P   val,
       P*   pDst, int len, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsMulC_Sfs(const P*   pSrc, P   val,
       P*   pDst, int len, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsAdd_I(const P*  pSrc, P*  pSrcDst, int len) {  
  const P *src=pSrc;
  P *dst=pSrcDst;
  for (int i=0;i<len;i++) {
      *(dst++) += *(src++);
  }
  return ippStsNoErr;
}

template<class P>
inline IppStatus ippsSub_I(const P*  pSrc, P*  pSrcDst, int len) {
  const P *src=pSrc;
  P *dst=pSrcDst;
  for (int i=0;i<len;i++) {
      *(dst++) -= *(src++);
  }
  return ippStsNoErr;
}
template<class P>
inline IppStatus ippsMul_I(const P*  pSrc, P*  pSrcDst, int len) {
  const P *src=pSrc;
  P *dst=pSrcDst;
  for (int i=0;i<len;i++) {
      *(dst++) *= *(src++);
  }
  return ippStsNoErr;
}
template<class P>
inline IppStatus ippsAdd_ISfs(const P*   pSrc, P*   pSrcDst,
       int len, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsSub_ISfs(const P*   pSrc, P*   pSrcDst,
       int len, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsMul_ISfs(const P*   pSrc, P*   pSrcDst,
       int len, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P1, class P2>
inline IppStatus ippsAdd(const P1*   pSrc1, const P1*   pSrc2,
       P2*  pDst, int len) {
 return ippStsDataTypeErr;
}
template<class P1, class P2>
inline IppStatus ippsMul(const P1*   pSrc1, const P1*   pSrc2,
       P2*  pDst, int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsAdd(const P*  pSrc1, const P*  pSrc2,
       P*  pDst, int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsSub(const P*  pSrc1, const P*  pSrc2,
       P*  pDst, int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsMul(const P*  pSrc1, const P*  pSrc2,
       P*  pDst, int len) {
 return ippStsDataTypeErr;
}
template<class P1, class P2>
inline IppStatus ippsSub(const P1*  pSrc1, const P1*  pSrc2,
       P2*  pDst, int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsAdd_Sfs(const P*   pSrc1, const P*   pSrc2,
       P*   pDst, int len, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsSub_Sfs(const P*   pSrc1, const P*   pSrc2,
       P*   pDst, int len, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsMul_Sfs(const P*   pSrc1, const P*   pSrc2,
       P*   pDst, int len, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P1, class P2>
inline IppStatus ippsMul_Sfs(const P1*  pSrc1, const P1*  pSrc2,
       P2*  pDst, int len, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P1, class P2>
inline IppStatus ippsMul_Sfs(const P1* pSrc1, const P2* pSrc2,
       P2* pDst, int len, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P1, class P2>
inline IppStatus ippsMul_ISfs(const P1* pSrc, P2* pSrcDst,
       int len, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P1, class P2>
inline IppStatus ippsMul_I(const P1* pSrc, P2* pSrcDst, int len) 
{
  return ippStsDataTypeErr;
}
template<class P1, class P2>
inline IppStatus ippsMul(const P1* pSrc1, const P2* pSrc2,
       P2* pDst, int len) {
 return ippStsDataTypeErr;
}
template<class P1, class P2>
inline IppStatus ippsAdd_I(const P1* pSrc, P2* pSrcDst, int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsAddProduct_Sfs( const P* pSrc1, const P* pSrc2,
                                               P* pSrcDst, int len, int scaleFactor ) {
 return ippStsDataTypeErr;
}
template<class P1, class P2>
inline IppStatus ippsAddProduct_Sfs( const P1* pSrc1, const P1* pSrc2,
                                               P2* pSrcDst, int len, int scaleFactor ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsAddProduct( const P* pSrc1, const P* pSrc2,
                                               P* pSrcDst, int len ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsSqr_I(P* pSrcDst, int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsSqr(const P* pSrc, P* pDst, int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsSqr_ISfs(P* pSrcDst, int len, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsSqr_Sfs(const P* pSrc, P* pDst, int len,
                                  int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsDiv(const P* pSrc1, const P* pSrc2,
       P* pDst, int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsDiv_Sfs(const P* pSrc1, const P* pSrc2,
       P* pDst, int len, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsDivC(const P* pSrc, P val,
       P* pDst, int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsDivC_Sfs(const P* pSrc, P val,
       P* pDst, int len, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsDiv_I(const P* pSrc, P* pSrcDst, int len) {
  const P *src=pSrc;
  P *dst=pSrcDst;
  for (int i=0;i<len;i++) {
      *(dst++) /= *(src++);
  }
  return ippStsNoErr;
}
template<class P>
inline IppStatus ippsDiv_ISfs(const P* pSrc, P* pSrcDst,
       int len, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P1, class P2>
inline IppStatus ippsDiv_Sfs(const P2* pSrc1, const P1* pSrc2,
       P2* pDst, int len, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsDivC_I(P val, P* pSrcDst, int len) {
  P *dst=pSrcDst;
  if(val==0)
    return ippStsDivByZeroErr; 
  for (int i=0;i<len;i++) {
      *(dst++) /= val;
  }
  return ippStsNoErr;
}
template<class P>
inline IppStatus ippsDivC_ISfs(P val, P* pSrcDst,
       int len, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsDivCRev(const P* pSrc, P val,
       P* pDst, int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsDivCRev_I(P val, P* pSrcDst, int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsSqrt_I(P* pSrcDst,int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsSqrt(const P* pSrc,P* pDst,int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsSqrt_ISfs(P* pSrcDst,int len,int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsSqrt_Sfs(const P* pSrc,P* pDst,int len,
                                   int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P1, class P2>
inline IppStatus ippsSqrt_Sfs(const P1* pSrc,P2* pDst,
        int len, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P1, class P2>
inline IppStatus ippsCubrt_Sfs( const P1* pSrc, P2* pDst, int Len, int sFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsCubrt( const P* pSrc, P* pDst, int Len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsAbs_I(P* pSrcDst,int len) {
  for (P* cursor = pSrcDst; cursor < pSrcDst + len; cursor++) {
    if (*cursor < P(0)) {
      *cursor = -(*cursor);
    }
  }
  return ippStsNoErr;
}
template<class P>
inline IppStatus ippsAbs(const P* pSrc, P* pDst,int len) {
  P* destCursor = pDst;
  for (const P* cursor = pSrc; cursor < pSrc + len; cursor++) {
    P element = *cursor;
    if (element < P(0)) {
      element = -element;
    }
    *destCursor++ = element;
  }
  return ippStsNoErr;
}
template<class P>
inline IppStatus ippsMagnitude(const P* pSrc,Ipp32f* pDst,int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsMagnitude(const P* pSrc,Ipp64f* pDst,int len) {
 return ippStsDataTypeErr;
}
template<class P1, class P2>
inline IppStatus ippsMagnitude(const P1* pSrc,P2* pDst,int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsMagnitude_Sfs(const P* pSrc,Ipp16s* pDst,
                                    int len,int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsMagnitude(const P* pSrcRe,const P* pSrcIm,
                               P* pDst,int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsMagnitude_Sfs(const P* pSrcRe,const P* pSrcIm,
                               P* pDst,int len,int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsMagnitude_Sfs(const P* pSrc,Ipp32s* pDst,
                                    int len,int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P1, class P2>
inline IppStatus ippsMagnitude(const P1* pSrcRe, const P1* pSrcIm,
                                                             P2* pDst, int len) {
 return ippStsDataTypeErr;
}
template<class P1, class P2>
inline IppStatus ippsMagSquared_Sfs(const P1* pSrc,P2* pDst, int len, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsExp_I(P* pSrcDst, int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsExp_ISfs(P* pSrcDst, int len, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsExp(const P* pSrc, P* pDst, int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsExp_Sfs(const P* pSrc, P* pDst, int len,
   int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P1, class P2>
inline IppStatus ippsExp(const P1* pSrc, P2* pDst, int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsLn_I(P* pSrcDst, int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsLn(const P* pSrc, P* pDst, int len) {
 return ippStsDataTypeErr;
}
template<class P1, class P2>
inline IppStatus ippsLn(const P1* pSrc, P2* pDst, int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsLn_ISfs(P* pSrcDst, int len, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsLn_Sfs(const P* pSrc, P* pDst, int len, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P1, class P2>
inline IppStatus ippsLn_Sfs( const P1* pSrc, P2* pDst, int Len, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ipps10Log10_ISfs( P* pSrcDst, int Len, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ipps10Log10_Sfs( const P* pSrc, P* pDst, int Len, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsSumLn(const P* pSrc, int len, P* pSum) {
 return ippStsDataTypeErr;
}
template<class P1, class P2>
inline IppStatus ippsSumLn(const P1* pSrc, int len, P2* pSum) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsSortAscend_I(P*  pSrcDst, int len) {
 std::sort(pSrcDst,pSrcDst+len);
 return ippStsNoErr;
}
template<class P>
inline IppStatus ippsSortDescend_I(P*  pSrcDst, int len) {
 std::sort(pSrcDst,pSrcDst+len,std::greater<P>());
 return ippStsNoErr;
}
template<class P>
inline IppStatus ippsSum(const P*  pSrc,int len, P* pSum,
       IppHintAlgorithm hint/*=ippAlgHintNone*/) {
 *pSum = std::accumulate(pSrc,pSrc+len,static_cast<P>(0));
 return ippStsNoErr;
}
template<class P>
inline IppStatus ippsSum(const P*  pSrc,int len, P* pSum) {
 *pSum = std::accumulate(pSrc,pSrc+len,static_cast<P>(0));
 return ippStsNoErr;
}
template<class P1, class P2>
inline IppStatus ippsSum_Sfs(const P1*  pSrc, int len,
                                       P2*  pSum, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsSum_Sfs(const P*  pSrc, int len,
                                       P*  pSum, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsMean(const P*  pSrc,int len,P*  pMean,
       IppHintAlgorithm hint) {
 if(len==0)
     return ippStsSizeErr;
 *pMean = std::accumulate(pSrc, pSrc + len, static_cast<P>(0));
 *pMean /= len;
 return ippStsNoErr;
}
template<class P>
inline IppStatus ippsMean(const P*  pSrc,int len,P*  pMean) {
 if(len==0)
     return ippStsSizeErr;
 *pMean = std::accumulate(pSrc, pSrc + len, static_cast<P>(0));
 *pMean /= len;
 return ippStsNoErr;
}
template<class P>
inline IppStatus ippsMean_Sfs(const P*  pSrc,int len,
                                    P*  pMean,int scaleFactor) {
 if(len==0)
     return ippStsSizeErr;
 double sum=std::accumulate(pSrc, pSrc + len, static_cast<P>(0));
 *pMean = static_cast<P>(sum/len*std::pow(2.0,scaleFactor));
 return ippStsNoErr;
}
template<class P>
inline IppStatus ippsStdDev(const P* pSrc,int len,P* pStdDev,
       IppHintAlgorithm hint) {
 if(len==0)
     return ippStsSizeErr;
 P mean = std::accumulate(pSrc, pSrc + len, static_cast<P>(0));
 mean /= len;
 double std=0.0;
 P* src=pSrc;
 for (int i=0;i<len;i++) {
        double tmp = *(src++)-mean;
      std += tmp*tmp;
 }
 *pStdDev=static_cast<P>(std::sqrt(std/len)+0.5)-static_cast<P>(0.5);
 return ippStsNoErr;
}

template<class P>
inline IppStatus ippsStdDev(const P* pSrc,int len,P* pStdDev) {
 if(len==0)
     return ippStsSizeErr;
 double mean = std::accumulate(pSrc, pSrc + len, static_cast<P>(0));
 mean /= len;
 double std=0.0;
 const P* src=pSrc;
 for (int i=0;i<len;i++) {
        double tmp = *(src++)-mean;
      std += tmp*tmp;
 }
 *pStdDev=static_cast<P>(std::sqrt(std/len)+0.5)-static_cast<P>(0.5);
 return ippStsNoErr;
}

template<class P1, class P2>
inline IppStatus ippsStdDev_Sfs(const P1* pSrc,int len,
                                        P2* pStdDev,int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsStdDev_Sfs(const P* pSrc,int len,
                                     P* pStdDev,int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsMax(const P* pSrc,int len,P* pMax) {
 *pMax = *std::max_element(pSrc, pSrc+len);
 return ippStsNoErr;
}
template<class P>
inline IppStatus ippsMaxIndx( const P* pSrc, int len, P* pMax, int* pIndx ) {
 const P* maxref = std::max_element(pSrc, pSrc+len);
 *pIndx = maxref-pSrc;
 *pMax = *maxref;
 return ippStsNoErr;
}
template<class P>
inline IppStatus ippsMin(const P* pSrc,int len,P* pMin) {
 *pMin = *std::min_element(pSrc, pSrc+len);
 return ippStsNoErr;
}
template<class P>
inline IppStatus ippsMinIndx( const P* pSrc, int len, P* pMin, int* pIndx ) {
 const P* minref = std::min_element(pSrc, pSrc+len);
 *pIndx = minref-pSrc;
 *pMin = *minref;
 return ippStsNoErr;
}
template<class P>
inline IppStatus ippsMinEvery_I(const P* pSrc, P* pSrcDst, int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsMaxEvery_I(const P* pSrc, P* pSrcDst, int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsMinMax(const P* pSrc, int len, P* pMin, P* pMax) {
 *pMax = *std::max_element(pSrc, pSrc+len);
 *pMin = *std::min_element(pSrc, pSrc+len);
 return ippStsNoErr;
}
template<class P>
inline IppStatus ippsMinMaxIndx(const P* pSrc, int len, P* pMin, int* pMinIndx,
                                                                   P* pMax, int* pMaxIndx) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsMinAbs(const P* pSrc, int len, P* pMinAbs) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsMaxAbs(const P* pSrc, int len, P* pMaxAbs) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsMinAbsIndx(const P* pSrc, int len, P* pMinAbs, int* pIndx) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsMaxAbsIndx(const P* pSrc, int len, P* pMaxAbs, int* pIndx) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsPhase(const P* pSrc, Ipp64f* pDst, int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsPhase(const P* pSrc, Ipp32f* pDst, int len) {
 return ippStsDataTypeErr;
}
template<class P1, class P2>
inline IppStatus ippsPhase(const P1* pSrc, P2* pDst, int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsPhase_Sfs(const P* pSrc, Ipp16s* pDst, int len,
                                                                int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsPhase(const P* pSrcRe, const P* pSrcIm,
                                                            P* pDst, int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsPhase_Sfs(const P* pSrcRe, const P* pSrcIm,
                                           P* pDst, int len, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P1, class P2>
inline IppStatus ippsPhase(const P1* pSrcRe, const P1* pSrcIm,
                                                            P2* pDst, int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsPhase_Sfs(const P* pSrc, Ipp32s* pDst, int len,
                                                                int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsMaxOrder(const P* pSrc, int len, int* pOrder) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsArctan_I(      P* pSrcDst, int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsArctan(const P* pSrc, P* pDst, int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFindNearestOne(P inpVal, P* pOutVal, int* pOutIndex, const P *pTable, int tblLen) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFindNearest(const P* pVals, P* pOutVals, int* pOutIndexes, int len, const P *pTable, int tblLen) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsAndC_I(P val, P* pSrcDst, int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsAndC(const P* pSrc, P val, P* pDst, int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsAnd_I(const P* pSrc, P* pSrcDst, int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsAnd(const P* pSrc1, const P* pSrc2, P* pDst, int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsOrC_I(P val, P* pSrcDst, int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsOrC(const P* pSrc, P val, P* pDst, int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsOr_I(const P* pSrc, P* pSrcDst, int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsOr(const P* pSrc1, const P* pSrc2, P* pDst, int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsXorC_I(P val, P* pSrcDst, int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsXorC(const P* pSrc, P val, P* pDst, int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsXor_I(const P* pSrc, P* pSrcDst, int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsXor(const P* pSrc1, const P* pSrc2, P* pDst, int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsNot_I(P* pSrcDst, int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsNot(const P* pSrc, P* pDst, int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsLShiftC_I(int val, P* pSrcDst, int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsLShiftC(const P* pSrc, int val, P* pDst, int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsRShiftC_I(int val, P* pSrcDst, int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsRShiftC(const P* pSrc, int val, P* pDst, int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsDotProd(const P* pSrc1,
       const P* pSrc2, int len, P* pDp) {
  *pDp = pSrc1[0] * pSrc2[0];
  for (int i = 1; i < len; i++) {
    *pDp += pSrc1[i] * pSrc2[i]; 
  }
  return ippStsNoErr;
}
template<class P1, class P2>
inline IppStatus ippsDotProd(const P1* pSrc1,
       const P2* pSrc2, int len, P2* pDp) {
  *pDp = static_cast<P2>(pSrc1[0]) * pSrc2[0];
  for (int i = 1; i < len; i++) {
    *pDp += static_cast<P2>(pSrc1[i]) * pSrc2[i]; 
  }
  return ippStsNoErr;
}
template<class P>
inline IppStatus ippsDotProd_Sfs(const P* pSrc1,
       const P* pSrc2, int len, P* pDp, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P1, class P2>
inline IppStatus ippsDotProd_Sfs(const P1* pSrc1,
       const P2* pSrc2, int len, P2* pDp, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P1, class P2>
inline IppStatus ippsDotProd(const P1*  pSrc1,
       const P1*  pSrc2, int len, P2*  pDp) {
  *pDp = static_cast<P2>(pSrc1[0] * pSrc2[0]);
  for (int i = 1; i < len; i++) {
    *pDp += static_cast<P2>(pSrc1[i] * pSrc2[i]); 
  }
  return ippStsNoErr;
}
template<class P1, class P2, class P3>
inline IppStatus ippsDotProd(const P1*  pSrc1,
       const P2* pSrc2, int len, P3* pDp) {
  *pDp = static_cast<P3>(pSrc1[0] * pSrc2[0]);
  for (int i = 1; i < len; i++) {
    *pDp += static_cast<P3>(pSrc1[i] * pSrc2[i]); 
  }
  return ippStsNoErr;
}
template<class P1, class P2>
inline IppStatus ippsDotProd_Sfs( const P1* pSrc1, const P1* pSrc2,
          int len, P2* pDp, int scaleFactor ) {
 return ippStsDataTypeErr;
}
template<class P1, class P2, class P3>
inline IppStatus ippsDotProd_Sfs( const P1* pSrc1, const P2* pSrc2,
          int len, P3* pDp, int scaleFactor ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsPowerSpectr(const P* pSrc, Ipp64f* pDst, int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsPowerSpectr(const P* pSrc, Ipp32f* pDst, int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsPowerSpectr_Sfs(const P* pSrc, Ipp16s* pDst,
                                                              int len, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P1, class P2>
inline IppStatus ippsPowerSpectr(const P1* pSrc, P2* pDst,
                                                                           int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsPowerSpectr(const P* pSrcRe, const P* pSrcIm,
                                                          P* pDst, int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsPowerSpectr_Sfs(const P* pSrcRe, const P* pSrcIm,
                                                P* pDst, int len, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P1, class P2>
inline IppStatus ippsPowerSpectr(const P1* pSrcRe, const P1* pSrcIm,
                                                             P2* pDst, int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsNormalize(const P* pSrc, P* pDst,
       int len, P vsub, Ipp64f vdiv) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsNormalize(const P* pSrc, P* pDst,
       int len, P vsub, Ipp32f vdiv) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsNormalize_Sfs(const P* pSrc, P* pDst,
       int len, P vsub, int vdiv, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsNormalize(const P* pSrc, P* pDst, int len,
       P vsub, P vdiv) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsMulPack_ISfs(const P* pSrc, P* pSrcDst, int length, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsMulPerm_ISfs(const P* pSrc, P* pSrcDst, int length, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsMulPack_I(const P* pSrc, P* pSrcDst, int length) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsMulPerm_I(const P* pSrc, P* pSrcDst, int length) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsMulPack_Sfs(const P* pSrc1, const P* pSrc2, P* pDst, int length, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsMulPerm_Sfs(const P* pSrc1, const P* pSrc2, P* pDst, int length, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsMulPack(const P* pSrc1, const P* pSrc2, P* pDst, int length) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsMulPerm(const P* pSrc1, const P* pSrc2, P* pDst, int length) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsMulPackConj_I(const P* pSrc, P* pSrcDst, int length) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsGoertz(const P* pSrc, int len, P* pVal, Ipp32f freq) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsGoertz(const P* pSrc, int len, P* pVal, Ipp64f freq) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsGoertz_Sfs(const P* pSrc, int len, P* pVal, Ipp32f freq, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsGoertz(const P* pSrc, int len, Ipp32fc* pVal, P freq) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsGoertz_Sfs(const P* pSrc, int len, Ipp16sc* pVal, Ipp32f freq, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsGoertzTwo(const P* pSrc, int len,
       P pVal[2], const Ipp32f freq[2] ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsGoertzTwo(const P* pSrc, int len,
       P pVal[2], const Ipp64f freq[2] ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsGoertzTwo_Sfs(const P* pSrc, int len,
       P pVal[2], const Ipp32f freq[2], int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsGoertzQ15_Sfs(const P* pSrc, int len, P* pVal, Ipp16s rFreqQ15, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsGoertzTwoQ15_Sfs(const P* pSrc, int len, P pVal[2], const Ipp16s rFreqQ15[2], int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsConv( const P* pSrc1, int lenSrc1,
       const P* pSrc2, int lenSrc2, P* pDst) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsConv_Sfs( const P* pSrc1, int lenSrc1,
       const P* pSrc2, int lenSrc2, P* pDst, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsConvBiased( const P *pSrc1, int len1,
                      const P *pSrc2, int len2,
                            P *pDst, int lenDst, int bias ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsConvCyclic8x8( const P* x,
       const P* h, P* y ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsConvCyclic8x8_Sfs( const P* x,
       const P* h, P* y, int scaleFactor ) {
 return ippStsDataTypeErr;
}
template<class P1, class P2>
inline IppStatus ippsConvCyclic4x4( const P1* x,
       const P2* h, P2* y ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFilterMedian_I(P* pSrcDst,int len,int maskSize) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFilterMedian(const P* pSrc, P *pDst,
                                       int len, int maskSize ) {
 return ippStsDataTypeErr;
}
template<class P1, class P2>
inline IppStatus ippsNorm_Inf(const P1* pSrc, int len, P2* pNorm) {
 *pNorm = static_cast<P2>(*std::max_element(pSrc, pSrc+len));
 return ippStsNoErr;
}
template<class P1, class P2>
inline IppStatus ippsNorm_Inf_Sfs(const P1* pSrc, int len, P2* pNorm, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsNorm_Inf(const P* pSrc, int len, P* pNorm) {
 *pNorm = *std::max_element(pSrc, pSrc+len);
 return ippStsNoErr;
}
template<class P1, class P2>
inline IppStatus ippsNorm_L1(const P1* pSrc, int len, P2* pNorm) {
 if(len==0)
     return ippStsSizeErr;
 *pNorm = std::accumulate(pSrc, pSrc + len, static_cast<P2>(0));
 return ippStsNoErr;
}
template<class P1, class P2>
inline IppStatus ippsNorm_L1_Sfs(const P1* pSrc, int len, P2* pNorm, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsNorm_L1(const P* pSrc, int len, P* pNorm) {
 if(len==0)
     return ippStsSizeErr;
 *pNorm = std::accumulate(pSrc, pSrc + len, static_cast<P>(0));
 return ippStsNoErr;
}
template<class P1, class P2>
inline IppStatus ippsNorm_L2(const P1* pSrc, int len, P2* pNorm) {
 if(len==0)
     return ippStsSizeErr;
 *pNorm = static_cast<P2>(::sqrt(static_cast<P2>(std::inner_product(pSrc, pSrc + len, pSrc, static_cast<P2>(0)))));
 return ippStsNoErr;
}
template<class P1, class P2>
inline IppStatus ippsNorm_L2_Sfs(const P1* pSrc, int len, P2* pNorm, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsNorm_L2(const P* pSrc, int len, P* pNorm) {
 if(len==0)
     return ippStsSizeErr;
 *pNorm = static_cast<P>(::sqrt((double)std::inner_product(pSrc, pSrc + len, pSrc, static_cast<P>(0))));
 return ippStsNoErr;
}
template<class P1, class P2>
inline IppStatus ippsNorm_L2Sqr_Sfs(const P1* pSrc, int len, P2* pNorm, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P1, class P2>
inline IppStatus ippsNormDiff_Inf(const P1* pSrc1, const P1* pSrc2, int len, P2* pNorm) {
 const P1 *pi1=pSrc1, *pi2=pSrc2;
 const P1 *pE=pSrc1+len;
 *pNorm=0; 
 for(; pi1!=pE; pi1++, pi2++) {
     P2 tmp=static_cast<P2>(std::abs(*pi1 - *pi2));
     if(tmp>*pNorm)
        *pNorm=tmp;
 }
 return ippStsNoErr;
}
template<class P1, class P2>
inline IppStatus ippsNormDiff_Inf_Sfs(const P1* pSrc1, const P1* pSrc2, int len, P2* pNorm, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsNormDiff_Inf(const P* pSrc1, const P* pSrc2, int len, P* pNorm) {
 const P *pi1=pSrc1, *pi2=pSrc2;
 const P *pE=pSrc1+len;
 *pNorm=0; 
 for(; pi1!=pE; pi1++, pi2++) {
     P tmp=std::abs(*pi1 - *pi2);
     if(tmp>*pNorm)
        *pNorm=tmp;
 }
 return ippStsNoErr;
}
template<class P1, class P2>
inline IppStatus ippsNormDiff_L1(const P1* pSrc1, const P1* pSrc2, int len, P2* pNorm) {
 const P1 *pi1=pSrc1, *pi2=pSrc2;
 const P1 *pE=pSrc1+len;
 *pNorm=0; 
 for(; pi1!=pE; pi1++, pi2++) {
     *pNorm += static_cast<P2>(std::abs(*pi1 - *pi2));
 }
 return ippStsNoErr;
}
template<class P1, class P2>
inline IppStatus ippsNormDiff_L1_Sfs(const P1* pSrc1, const P1* pSrc2, int len, P2* pNorm, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsNormDiff_L1(const P* pSrc1, const P* pSrc2, int len, P* pNorm) {
 const P *pi1=pSrc1, *pi2=pSrc2;
 const P *pE=pSrc1+len;
 *pNorm=0; 
 for(; pi1!=pE; pi1++, pi2++) {
     *pNorm += std::abs(*pi1 - *pi2);
 }
 return ippStsNoErr;
}
template<class P1, class P2>
inline IppStatus ippsNormDiff_L2(const P1* pSrc1, const P1* pSrc2, int len, P2* pNorm) {
 const P1 *pi1=pSrc1, *pi2=pSrc2;
 const P1 *pE=pSrc1+len;
 *pNorm=0; 
 for(; pi1!=pE; pi1++, pi2++) {
     *pNorm += static_cast<P2>((*pi1 - *pi2)*(*pi1 - *pi2));
 }
 *pNorm=sqrt(*pNorm);
 return ippStsNoErr;
}
template<class P1, class P2>
inline IppStatus ippsNormDiff_L2_Sfs(const P1* pSrc1, const P1* pSrc2, int len, P2* pNorm, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsNormDiff_L2(const P* pSrc1, const P* pSrc2, int len, P* pNorm) {
 const P *pi1=pSrc1, *pi2=pSrc2;
 const P *pE=pSrc1+len;
 *pNorm=0; 
 for(; pi1!=pE; pi1++, pi2++) {
     *pNorm += (*pi1 - *pi2)*(*pi1 - *pi2);
 }
 *pNorm=sqrt(*pNorm);
 return ippStsNoErr;
}
template<class P1, class P2>
inline IppStatus ippsNormDiff_L2Sqr_Sfs(const P1* pSrc1, const P1* pSrc2, int len, P2* pNorm, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsCrossCorr(const P* pSrc1, int len1, const P* pSrc2, int len2, P* pDst,  int dstLen, int lowLag) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsCrossCorr_Sfs(const P* pSrc1, int len1, const P* pSrc2, int len2, P* pDst, int dstLen, int lowLag, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsAutoCorr( const P* pSrc, int srcLen, P* pDst, int dstLen ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsAutoCorr_NormA( const P* pSrc, int srcLen, P* pDst, int dstLen ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsAutoCorr_NormB( const P* pSrc, int srcLen, P* pDst, int dstLen ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsAutoCorr_Sfs( const P* pSrc, int srcLen, P* pDst,
                                                        int dstLen, int scaleFactor ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsAutoCorr_NormA_Sfs( const P* pSrc, int srcLen, P* pDst,
                                                        int dstLen, int scaleFactor ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsAutoCorr_NormB_Sfs( const P* pSrc, int srcLen, P* pDst,
                                                        int dstLen, int scaleFactor ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsSampleUp(const P* pSrc, int  srcLen,
                                             P* pDst, int* dstLen,
                                             int factor,   int* phase) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsSampleDown(const P* pSrc, int  srcLen,
                                               P* pDst, int* dstLen,
                                               int factor,   int* phase) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsGetVarPointDV(const P *pSrc,P *pDst,
       P *pVariantPoint,const Ipp8u *pLabel,int state) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsBuildSymblTableDV4D(const P *pVariantPoint,
       P *pCurrentSubsetPoint,int state,int bitInversion ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsUpdatePathMetricsDV(P *pBranchError,
       P *pMinPathError,Ipp8u *pMinSost,P *pPathError,int state) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsAddProductC( const P* pSrc, const P val,
                                               P* pSrcDst, int len ) {
 return ippStsDataTypeErr;
}
template<class P1, class P2>
inline IppStatus ippsSumWindow(const P1*  pSrc,P2* pDst,int len, int maskSize ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmExtract_v(const P*  pSrc,  int srcStride2,
                                              P*  pDst,  int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmExtract_v_P(const P** ppSrc, int srcRoiShift,
                                              P*  pDst,  int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmExtract_va(const P*  pSrc,  int srcStride0, int srcStride2,
                                              P*  pDst,  int len, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmExtract_va_P(const P** ppSrc, int srcRoiShift, int srcStride0,
                                              P*  pDst,  int len, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmExtract_va_L(const P** ppSrc, int srcRoiShift, int srcStride2,
                                              P*  pDst,  int len, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmExtract_m(const P*  pSrc,  int srcStride1, int srcStride2,
                                              P*  pDst,  int width, int height) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmExtract_m_P(const P** ppSrc, int srcRoiShift,
                                              P*  pDst,  int width, int height) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmExtract_t(const P*  pSrc,  int srcStride1, int srcStride2,
                                              P*  pDst,  int width, int height) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmExtract_t_P(const P** ppSrc, int srcRoiShift,
                                              P*  pDst,  int width, int height) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmExtract_ma(const P*  pSrc,  int srcStride0, int srcStride1, int srcStride2,
                                              P*  pDst,  int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmExtract_ma_P(const P** ppSrc, int srcRoiShift, int srcStride0,
                                              P*  pDst,  int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmExtract_ma_L(const P** ppSrc, int srcRoiShift, int srcStride1, int srcStride2,
                                              P*  pDst,  int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmExtract_ta(const P*  pSrc, int srcStride0, int srcStride1, int srcStride2,
                                              P*  pDst, int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmExtract_ta_P(const P** ppSrc, int srcRoiShift, int srcStride0,
                                              P*  pDst,  int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmExtract_ta_L(const P** ppSrc, int srcRoiShift, int srcStride1, int srcStride2,
                                              P*  pDst,  int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmCopy_va_SS(const P*  pSrc,  int srcStride0,  int srcStride2,
                                            P*  pDst,  int dstStride0,  int dstStride2,
                                            int len, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmCopy_va_SP(const P*  pSrc,  int srcStride0,  int srcStride2,
                                            P** ppDst, int dstRoiShift, int dstStride0,
                                            int len, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmCopy_va_SL(const P*  pSrc,  int srcStride0,  int srcStride2,
                                            P** ppDst, int dstRoiShift, int dstStride2,
                                            int len, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmCopy_va_LS(const P** ppSrc, int srcRoiShift, int srcStride2,
                                            P*  pDst,  int dstStride0,  int dstStride2,
                                            int len, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmCopy_va_PS(const P** ppSrc, int srcRoiShift, int srcStride0,
                                            P*  pDst,  int dstStride0,  int dstStride2,
                                            int len, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmCopy_va_LP(const P** ppSrc, int srcRoiShift, int srcStride2,
                                            P** ppDst, int dstRoiShift, int dstStride0,
                                            int len, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmCopy_va_LL(const P** ppSrc, int srcRoiShift, int srcStride2,
                                            P** ppDst, int dstRoiShift, int dstStride2,
                                            int len, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmCopy_va_PP(const P** ppSrc, int srcRoiShift, int srcStride0,
                                            P** ppDst, int dstRoiShift, int dstStride0,
                                            int len, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmCopy_va_PL(const P** ppSrc, int srcRoiShift, int srcStride0,
                                            P** ppDst, int dstRoiShift, int dstStride2,
                                            int len, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmCopy_ma_SS(const P*  pSrc,  int srcStride0, int srcStride1, int srcStride2,
                                            P*  pDst,  int dstStride0, int dstStride1, int dstStride2,
                                            int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmCopy_ma_SP(const P*  pSrc,  int srcStride0, int srcStride1, int srcStride2,
                                            P** ppDst, int dstRoiShift, int dstStride0,
                                            int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmCopy_ma_SL(const P*  pSrc,  int srcStride0, int srcStride1, int srcStride2,
                                            P** ppDst, int dstRoiShift, int dstStride1, int dstStride2,
                                            int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmCopy_ma_LS(const P** ppSrc, int srcRoiShift, int srcStride1, int srcStride2,
                                            P*  pDst,  int dstStride0, int dstStride1, int dstStride2,
                                            int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmCopy_ma_PS(const P** ppSrc, int srcRoiShift, int srcStride0,
                                            P*  pDst,  int dstStride0, int dstStride1, int dstStride2,
                                            int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmCopy_ma_LP(const P** ppSrc, int srcRoiShift, int srcStride1, int srcStride2,
                                            P** ppDst, int dstRoiShift, int dstStride0,
                                            int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmCopy_ma_LL(const P** ppSrc, int srcRoiShift, int srcStride1, int srcStride2,
                                            P** ppDst, int dstRoiShift, int dstStride1, int dstStride2,
                                            int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmCopy_ma_PP(const P** ppSrc, int srcRoiShift, int srcStride0,
                                            P** ppDst, int dstRoiShift, int dstStride0,
                                            int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmCopy_ma_PL(const P** ppSrc, int srcRoiShift, int srcStride0,
                                            P** ppDst, int dstRoiShift, int dstStride1, int dstStride2,
                                            int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmLoadIdentity_ma(P*  pDst,  int dstStride0, int dstStride1, int dstStride2,
                                             int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmLoadIdentity_ma_P(P** ppDst, int dstRoiShift, int dstStride0,
                                             int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmLoadIdentity_ma_L(P** ppDst, int dstRoiShift, int dstStride1, int dstStride2,
                                             int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmSaxpy_vv(const P* pSrc1, int src1Stride2, P scale,
                                       const P* pSrc2, int src2Stride2,
                                             P* pDst,  int dstStride2,
                                             int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmSaxpy_vv_P(const P** ppSrc1, int src1RoiShift, P scale,
                                       const P** ppSrc2, int src2RoiShift,
                                             P** ppDst,  int dstRoiShift,
                                             int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmSaxpy_vva(const P* pSrc1, int src1Stride2, P scale,
                                       const P* pSrc2, int src2Stride0, int src2Stride2,
                                             P* pDst,  int dstStride0,  int dstStride2,
                                             int len, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmSaxpy_vva_P(const P** ppSrc1, int src1RoiShift, P scale,
                                       const P** ppSrc2, int src2RoiShift, int src2Stride0,
                                             P** ppDst,  int dstRoiShift,  int dstStride0,
                                             int len, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmSaxpy_vva_L(const P*  pSrc1,  int src1Stride2, P scale,
                                       const P** ppSrc2, int src2RoiShift, int src2Stride2,
                                             P** ppDst,  int dstRoiShift,  int dstStride2,
                                             int len, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmSaxpy_vav(const P*  pSrc1,  int src1Stride0, int src1Stride2, P scale,
                                       const P*  pSrc2,  int src2Stride2,
                                             P*  pDst,   int dstStride0,  int dstStride2,
                                             int len, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmSaxpy_vav_P(const P** ppSrc1, int src1RoiShift, int src1Stride0, P scale,
                                        const P** ppSrc2, int src2RoiShift,
                                              P** ppDst,  int dstRoiShift,  int dstStride0,
                                              int len, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmSaxpy_vav_L(const P** ppSrc1, int src1RoiShift, int src1Stride2, P scale,
                                        const P*  pSrc2,  int src2Stride2,
                                              P** ppDst,  int dstRoiShift,  int dstStride2,
                                              int len, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmSaxpy_vava(const P*  pSrc1,  int src1Stride0,  int src1Stride2, P scale,
                                        const P*  pSrc2,  int src2Stride0,  int src2Stride2,
                                              P*  pDst,   int dstStride0,   int dstStride2,
                                              int len, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmSaxpy_vava_P(const P** ppSrc1, int src1RoiShift, int src1Stride0, P scale,
                                        const P** ppSrc2, int src2RoiShift, int src2Stride0,
                                              P** ppDst,  int dstRoiShift,  int dstStride0,
                                              int len, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmSaxpy_vava_L(const P** ppSrc1, int src1RoiShift, int src1Stride2, P scale,
                                        const P** ppSrc2, int src2RoiShift, int src2Stride2,
                                              P** ppDst,  int dstRoiShift,  int dstStride2,
                                              int len, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmAdd_vc(const P*  pSrc,  int srcStride2, P val,
                                           P*  pDst,  int dstStride2,
                                           int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmAdd_vc_P(const P** ppSrc, int srcRoiShift, P val,
                                           P** ppDst, int dstRoiShift,
                                           int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmAdd_vac(const P*  pSrc,  int srcStride0, int srcStride2, P val,
                                           P*  pDst,  int dstStride0, int dstStride2,
                                           int len, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmAdd_vac_P(const P** ppSrc, int srcRoiShift, int srcStride0, P val,
                                           P** ppDst, int dstRoiShift, int dstStride0,
                                           int len, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmAdd_vac_L(const P** ppSrc, int srcRoiShift, int srcStride2, P val,
                                           P** ppDst, int dstRoiShift, int dstStride2,
                                           int len, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmAdd_vv(const P*  pSrc1, int src1Stride2,
                                     const P*  pSrc2, int src2Stride2,
                                           P*  pDst,  int dstStride2,
                                           int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmAdd_vv_P(const P** ppSrc1, int src1RoiShift,
                                     const P** ppSrc2, int src2RoiShift,
                                           P** ppDst,  int dstRoiShift,
                                           int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmAdd_vav(const P*  pSrc1,  int src1Stride0, int src1Stride2,
                                     const P*  pSrc2,  int src2Stride2,
                                           P*  pDst,   int dstStride0,  int dstStride2,
                                           int len, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmAdd_vav_P(const P** ppSrc1, int src1RoiShift, int src1Stride0,
                                     const P** ppSrc2, int src2RoiShift,
                                           P** ppDst,  int dstRoiShift,  int dstStride0,
                                           int len, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmAdd_vav_L(const P** ppSrc1, int src1RoiShift, int src1Stride2,
                                     const P*  pSrc2,  int src2Stride2,
                                           P** ppDst,  int dstRoiShift,  int dstStride2,
                                           int len, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmAdd_vava(const P*  pSrc1,  int src1Stride0, int src1Stride2,
                                     const P*  pSrc2,  int src2Stride0, int src2Stride2,
                                           P*  pDst,   int dstStride0,  int dstStride2,
                                           int len, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmAdd_vava_P(const P** ppSrc1, int src1RoiShift, int src1Stride0,
                                      const P** ppSrc2, int src2RoiShift, int src2Stride0,
                                            P** ppDst,  int dstRoiShift,  int dstStride0,
                                            int len, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmAdd_vava_L(const P** ppSrc1, int src1RoiShift, int src1Stride2,
                                      const P** ppSrc2, int src2RoiShift, int src2Stride2,
                                            P** ppDst,  int dstRoiShift,  int dstStride2,
                                            int len, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmSub_vc(const P*  pSrc,  int srcStride2, P val,
                                           P*  pDst,  int dstStride2,
                                           int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmSub_vc_P(const P** ppSrc, int srcRoiShift, P val,
                                           P** ppDst, int dstRoiShift,
                                           int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmSub_cv(const P*  pSrc,  int srcStride2, P val,
                                           P*  pDst,  int dstStride2,
                                           int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmSub_cv_P(const P** ppSrc, int srcRoiShift, P val,
                                           P** ppDst, int dstRoiShift,
                                           int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmSub_vac(const P*  pSrc,  int srcStride0, int srcStride2, P val,
                                           P*  pDst,  int dstStride0, int dstStride2,
                                           int len, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmSub_vac_P(const P** ppSrc, int srcRoiShift, int srcStride0, P val,
                                           P** ppDst, int dstRoiShift, int dstStride0,
                                           int len, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmSub_vac_L(const P** ppSrc, int srcRoiShift, int srcStride2, P val,
                                           P** ppDst, int dstRoiShift, int dstStride2,
                                           int len, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmSub_cva(const P*  pSrc,  int srcStride0, int srcStride2, P val,
                                           P*  pDst,  int dstStride0, int dstStride2,
                                           int len, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmSub_cva_P(const P** ppSrc, int srcRoiShift, int srcStride0, P val,
                                           P** ppDst, int dstRoiShift, int dstStride0,
                                           int len, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmSub_cva_L(const P** ppSrc, int srcRoiShift, int srcStride2, P val,
                                           P** ppDst, int dstRoiShift, int dstStride2,
                                           int len, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmSub_vv(const P*  pSrc1, int src1Stride2,
                                     const P*  pSrc2, int src2Stride2,
                                           P*  pDst,  int dstStride2,
                                           int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmSub_vv_P(const P** ppSrc1, int src1RoiShift,
                                     const P** ppSrc2, int src2RoiShift,
                                           P** ppDst,  int dstRoiShift,
                                           int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmSub_vav(const P*  pSrc1,  int src1Stride0, int src1Stride2,
                                     const P*  pSrc2,  int src2Stride2,
                                           P*  pDst,   int dstStride0,  int dstStride2,
                                           int len, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmSub_vav_P(const P** ppSrc1, int src1RoiShift, int src1Stride0,
                                     const P** ppSrc2, int src2RoiShift,
                                           P** ppDst,  int dstRoiShift,  int dstStride0,
                                           int len, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmSub_vav_L(const P** ppSrc1, int src1RoiShift, int src1Stride2,
                                     const P*  pSrc2,  int src2Stride2,
                                           P** ppDst,  int dstRoiShift,  int dstStride2,
                                           int len, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmSub_vva(const P*  pSrc1,  int src1Stride2,
                                     const P*  pSrc2,  int src2Stride0, int src2Stride2,
                                           P*  pDst,   int dstStride0,  int dstStride2,
                                           int len, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmSub_vva_P(const P** ppSrc1, int src1RoiShift,
                                     const P** ppSrc2, int src2RoiShift, int src2Stride0,
                                           P** ppDst,  int dstRoiShift,  int dstStride0,
                                           int len, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmSub_vva_L(const P*  pSrc1,  int src1Stride2,
                                     const P** ppSrc2, int src2RoiShift, int src2Stride2,
                                           P** ppDst,  int dstRoiShift,  int dstStride2,
                                           int len, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmSub_vava(const P*  pSrc1,  int src1Stride0, int src1Stride2,
                                     const P*  pSrc2,  int src2Stride0, int src2Stride2,
                                           P*  pDst,   int dstStride0,  int dstStride2,
                                           int len, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmSub_vava_P(const P** ppSrc1, int src1RoiShift, int src1Stride0,
                                      const P** ppSrc2, int src2RoiShift, int src2Stride0,
                                            P** ppDst,  int dstRoiShift,  int dstStride0,
                                            int len, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmSub_vava_L(const P** ppSrc1, int src1RoiShift, int src1Stride2,
                                      const P** ppSrc2, int src2RoiShift, int src2Stride2,
                                            P** ppDst,  int dstRoiShift,  int dstStride2,
                                            int len, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmMul_vc(const P*  pSrc,  int srcStride2, P val,
                                           P*  pDst,  int dstStride2,
                                           int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmMul_vc_P(const P** ppSrc, int srcRoiShift, P val,
                                           P** ppDst, int dstRoiShift,
                                           int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmMul_vac(const P*  pSrc,  int srcStride0, int srcStride2, P val,
                                           P*  pDst,  int dstStride0, int dstStride2,
                                           int len, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmMul_vac_P(const P** ppSrc, int srcRoiShift, int srcStride0, P val,
                                           P** ppDst, int dstRoiShift, int dstStride0,
                                           int len, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmMul_vac_L(const P** ppSrc, int srcRoiShift, int srcStride2, P val,
                                           P** ppDst, int dstRoiShift, int dstStride2,
                                           int len, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmCrossProduct_vv(const P*  pSrc1,  int src1Stride2,
                                               const P*  pSrc2,  int src2Stride2,
                                                     P*  pDst,   int dstStride2) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmCrossProduct_vv_P(const P** ppSrc1, int src1RoiShift,
                                               const P** ppSrc2, int src2RoiShift,
                                                     P** ppDst,  int dstRoiShift) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmCrossProduct_vva(const P*  pSrc1,  int src1Stride2,
                                               const P*  pSrc2,  int src2Stride0, int src2Stride2,
                                                     P*  pDst,   int dstStride0,  int dstStride2,
                                                     int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmCrossProduct_vva_P(const P** ppSrc1, int src1RoiShift,
                                               const P** ppSrc2, int src2RoiShift, int src2Stride0,
                                                     P** ppDst,  int dstRoiShift,  int dstStride0,
                                                     int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmCrossProduct_vva_L(const P*  pSrc1,  int src1Stride2,
                                               const P** ppSrc2, int src2RoiShift, int src2Stride2,
                                                     P** ppDst,  int dstRoiShift,  int dstStride2,
                                                     int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmCrossProduct_vav(const P*  pSrc1,  int src1Stride0, int src1Stride2,
                                               const P*  pSrc2,  int src2Stride2,
                                                     P*  pDst,   int dstStride0, int dstStride2,
                                                     int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmCrossProduct_vav_P(const P** ppSrc1, int src1RoiShift, int src1Stride0,
                                               const P** ppSrc2, int src2RoiShift,
                                                     P** ppDst,  int dstRoiShift, int dstStride0,
                                                     int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmCrossProduct_vav_L(const P** ppSrc1, int src1RoiShift, int src1Stride2,
                                               const P*  pSrc2,  int src2Stride2,
                                                     P** ppDst,  int dstRoiShift, int dstStride2,
                                                     int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmCrossProduct_vava(const P* pSrc1, int src1Stride0, int src1Stride2,
                                               const P* pSrc2, int src2Stride0, int src2Stride2,
                                                     P* pDst,  int dstStride0,  int dstStride2,
                                                     int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmCrossProduct_vava_P(const P** ppSrc1, int src1RoiShift, int src1Stride0,
                                               const P** ppSrc2, int src2RoiShift, int src2Stride0,
                                                     P** ppDst,  int dstRoiShift,  int dstStride0,
                                                     int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmCrossProduct_vava_L(const P** ppSrc1, int src1RoiShift, int src1Stride2,
                                               const P** ppSrc2, int src2RoiShift, int src2Stride2,
                                                     P** ppDst,  int dstRoiShift,  int dstStride2,
                                                     int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmDotProduct_vv(const P*  pSrc1,  int src1Stride2,
                                             const P*  pSrc2,  int src2Stride2,
                                                   P*  pDst,   int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmDotProduct_vv_P(const P** ppSrc1, int src1RoiShift,
                                             const P** ppSrc2, int src2RoiShift,
                                                   P*  pDst,   int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmDotProduct_vav(const P*  pSrc1,  int src1Stride0, int src1Stride2,
                                             const P*  pSrc2,  int src2Stride2,
                                                   P*  pDst,   int len, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmDotProduct_vav_P(const P** ppSrc1, int src1RoiShift, int src1Stride0,
                                             const P** ppSrc2, int src2RoiShift,
                                                   P*  pDst,   int len, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmDotProduct_vav_L(const P** ppSrc1, int src1RoiShift, int src1Stride2,
                                             const P*  pSrc2,  int src2Stride2,
                                                   P*  pDst,   int len, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmDotProduct_vava(const P* pSrc1, int src1Stride0, int src1Stride2,
                                             const P* pSrc2, int src2Stride0, int src2Stride2,
                                                   P* pDst,  int len, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmDotProduct_vava_P(const P** ppSrc1, int src1RoiShift, int src1Stride0,
                                             const P** ppSrc2, int src2RoiShift, int src2Stride0,
                                                   P*  pDst,   int len, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmDotProduct_vava_L(const P** ppSrc1, int src1RoiShift, int src1Stride2,
                                             const P** ppSrc2, int src2RoiShift, int src2Stride2,
                                                   P*  pDst,   int len, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmL2Norm_v(const P*  pSrc, int srcStride2,
                                             P*  pDst, int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmL2Norm_v_P(const P** ppSrc, int srcRoiShift,
                                             P*  pDst,  int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmL2Norm_va(const P*  pSrc,  int srcStride0, int srcStride2,
                                             P*  pDst,  int len, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmL2Norm_va_P(const P** ppSrc, int srcRoiShift, int srcStride0,
                                             P*  pDst,  int len, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmL2Norm_va_L(const P** ppSrc, int srcRoiShift, int srcStride2,
                                             P*  pDst,  int len, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmLComb_vv(const P*  pSrc1,  int src1Stride2, P scale1,
                                        const P*  pSrc2,  int src2Stride2, P scale2,
                                              P*  pDst,   int dstStride2,
                                              int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmLComb_vv_P(const P** ppSrc1, int src1RoiShift, P scale1,
                                        const P** ppSrc2, int src2RoiShift, P scale2,
                                              P** ppDst,  int dstRoiShift,
                                              int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmLComb_vav(const P*  pSrc1,  int src1Stride0, int src1Stride2, P scale1,
                                        const P*  pSrc2,  int src2Stride2, P scale2,
                                              P*  pDst,   int dstStride0,  int dstStride2,
                                              int len, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmLComb_vav_P(const P** ppSrc1, int src1RoiShift, int src1Stride0, P scale1,
                                        const P** ppSrc2, int src2RoiShift, P scale2,
                                              P** ppDst,  int dstRoiShift,  int dstStride0,
                                              int len, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmLComb_vav_L(const P** ppSrc1, int src1RoiShift, int src1Stride2, P scale1,
                                        const P*  pSrc2,  int src2Stride2,  P scale2,
                                              P** ppDst,  int dstRoiShift,  int dstStride2,
                                              int len, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmLComb_vava(const P*  pSrc1,  int src1Stride0, int src1Stride2, P scale1,
                                        const P*  pSrc2,  int src2Stride0, int src2Stride2, P scale2,
                                              P*  pDst,   int dstStride0,  int dstStride2,
                                              int len, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmLComb_vava_P(const P** ppSrc1, int src1RoiShift, int src1Stride0, P scale1,
                                        const P** ppSrc2, int src2RoiShift, int src2Stride0, P scale2,
                                              P** ppDst,  int dstRoiShift,  int dstStride0,
                                              int len, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmLComb_vava_L(const P** ppSrc1, int src1RoiShift, int src1Stride2, P scale1,
                                        const P** ppSrc2, int src2RoiShift, int src2Stride2, P scale2,
                                              P** ppDst,  int dstRoiShift,  int dstStride2,
                                              int len, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmTranspose_m(const P* pSrc, int srcStride1, int srcStride2,
                                                int width, int height,
                                                P* pDst, int dstStride1, int dstStride2) {
  const P *src=pSrc;
  const P *srccol=src;
  P *dst=pDst;
  P *dstcol=dst;
  for(int h=0;h<height;h++) {
    for(int w=0;w<width;w++) {
        *dst=*src;
        src=reinterpret_cast<const P*>(reinterpret_cast<const char *>(src)+srcStride2);
        dst=reinterpret_cast<P*>(reinterpret_cast<char *>(dst)+dstStride1);
    }
    srccol=reinterpret_cast<const P*>(reinterpret_cast<const char *>(srccol)+srcStride1);
    dstcol=reinterpret_cast<P*>(reinterpret_cast<char *>(dstcol)+dstStride2);
    src=srccol;
    dst=dstcol;
  }
  return ippStsNoErr;
}
template<class P>
inline IppStatus ippmTranspose_m_P(const P** ppSrc, int srcRoiShift,
                                                int width, int height,
                                                P** ppDst, int dstRoiShift) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmTranspose_ma(const P* pSrc, int srcStride0, int srcStride1, int srcStride2,
                                                int width, int height,
                                                P* pDst, int dstStride0, int dstStride1, int dstStride2,
                                                int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmTranspose_ma_P(const P** ppSrc, int srcRoiShift, int srcStride0,
                                                int width, int height,
                                                P** ppDst, int dstRoiShift, int dstStride0,
                                                int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmTranspose_ma_L(const P** ppSrc, int srcRoiShift, int srcStride1, int srcStride2,
                                                int width, int height,
                                                P** ppDst, int dstRoiShift, int dstStride1, int dstStride2,
                                                int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmInvert_m(const P* pSrc, int srcStride1, int srcStride2,
                                             P* pBuffer,
                                             P* pDst, int dstStride1, int dstStride2,
                                             int widthHeight) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmInvert_m_P(const P** ppSrc, int srcRoiShift,
                                             P*  pBuffer,
                                             P** ppDst, int dstRoiShift,
                                             int widthHeight ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmInvert_ma(const P* pSrc, int srcStride0, int srcStride1, int srcStride2,
                                             P* pBuffer,
                                             P* pDst, int dstStride0, int dstStride1, int dstStride2,
                                             int widthHeight, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmInvert_ma_P(const P** ppSrc, int srcRoiShift, int srcStride0,
                                             P* pBuffer,
                                             P** ppDst, int dstRoiShift, int dstStride0,
                                             int widthHeight, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmInvert_ma_L(const P** ppSrc, int srcRoiShift, int srcStride1, int srcStride2,
                                             P*  pBuffer,
                                             P** ppDst, int dstRoiShift, int dstStride1, int dstStride2,
                                             int widthHeight, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmFrobNorm_m(const P* pSrc, int srcStride1, int srcStride2,
                                               int width, int height,
                                               P* pDst) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmFrobNorm_m_P(const P** ppSrc, int srcRoiShift,
                                               int width, int height,
                                               P* pDst) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmFrobNorm_ma(const P* pSrc, int srcStride0, int srcStride1, int srcStride2,
                                               int width, int height,
                                               P* pDst,
                                               int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmFrobNorm_ma_P(const P** ppSrc, int srcRoiShift, int srcStride0,
                                               int width, int height,
                                               P* pDst,
                                               int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmFrobNorm_ma_L(const P** ppSrc, int srcRoiShift, int srcStride1, int srcStride2,
                                               int width, int height,
                                               P* pDst,
                                               int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmDet_m(const P*  pSrc, int srcStride1, int srcStride2,
                                          int widthHeight, P* pBuffer,
                                          P*  pDst) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmDet_m_P(const P** ppSrc, int srcRoiShift,
                                          int widthHeight, P* pBuffer,
                                          P*  pDst) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmDet_ma(const P*   pSrc, int srcStride0, int srcStride1, int srcStride2,
                                          int widthHeight, P* pBuffer,
                                          P*  pDst, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmDet_ma_P(const P** ppSrc, int srcRoiShift, int srcStride0,
                                          int widthHeight, P* pBuffer,
                                          P*  pDst,  int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmDet_ma_L(const P** ppSrc, int srcRoiShift, int srcStride1, int srcStride2,
                                          int widthHeight, P* pBuffer,
                                          P*  pDst,  int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmTrace_m(const P*  pSrc,   int srcStride1, int srcStride2,
                                            int widthHeight, P* pDst) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmTrace_m_P(const P** ppSrc,  int srcRoiShift,
                                            int widthHeight, P* pDst) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmTrace_ma(const P*   pSrc,   int srcStride0, int srcStride1, int srcStride2,
                                           int widthHeight,  P* pDst,   int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmTrace_ma_P(const P** ppSrc,  int srcRoiShift, int srcStride0,
                                            int widthHeight, P* pDst,    int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmTrace_ma_L(const P** ppSrc,  int srcRoiShift, int srcStride1, int srcStride2,
                                            int widthHeight, P* pDst,    int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmMul_mc(const P*  pSrc, int srcStride1, int srcStride2,
                                           P   val,
                                           P*  pDst, int dstStride1, int dstStride2,
                                           int width, int height) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmMul_mc_P(const P** ppSrc, int srcRoiShift,
                                           P   val,
                                           P** ppDst, int dstRoiShift,
                                           int width, int height) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmMul_tc(const P*  pSrc, int srcStride1, int srcStride2,
                                           P   val,
                                           P*  pDst, int dstStride1, int dstStride2,
                                           int width, int height) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmMul_tc_P(const P** ppSrc, int srcRoiShift,
                                           P   val,
                                           P** ppDst, int dstRoiShift,
                                           int width, int height) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmMul_mac(const P*  pSrc, int srcStride0, int srcStride1, int srcStride2,
                                           P   val,
                                           P*  pDst, int dstStride0, int dstStride1, int dstStride2,
                                           int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmMul_mac_P(const P** ppSrc, int srcRoiShift, int srcStride0,
                                           P   val,
                                           P** ppDst, int dstRoiShift, int dstStride0,
                                           int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmMul_mac_L(const P** ppSrc, int srcRoiShift, int srcStride1, int srcStride2,
                                           P   val,
                                           P** ppDst, int dstRoiShift, int dstStride1, int dstStride2,
                                           int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmMul_tac(const P*  pSrc, int srcStride0, int srcStride1, int srcStride2,
                                           P   val,
                                           P*  pDst, int dstStride0, int dstStride1, int dstStride2,
                                           int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmMul_tac_P(const P** ppSrc, int srcRoiShift, int srcStride0,
                                           P   val,
                                           P** ppDst, int dstRoiShift, int dstStride0,
                                           int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmMul_tac_L(const P** ppSrc, int srcRoiShift, int srcStride1, int srcStride2,
                                           P   val,
                                           P** ppDst, int dstRoiShift, int dstStride1, int dstStride2,
                                           int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmMul_mv(const P*  pSrc1, int src1Stride1, int src1Stride2,
                                            int src1Width,  int src1Height,
                                      const P*  pSrc2, int src2Stride2, int src2Len,
                                            P*  pDst,  int dstStride2) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmMul_mv_P(const P** ppSrc1, int src1RoiShift,
                                            int src1Width,   int src1Height,
                                      const P** ppSrc2, int src2RoiShift, int src2Len,
                                            P** ppDst,  int dstRoiShift) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmMul_tv(const P*  pSrc1, int src1Stride1, int src1Stride2,
                                            int src1Width,  int src1Height,
                                      const P*  pSrc2, int src2Stride2, int src2Len,
                                            P*  pDst,  int dstStride2) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmMul_tv_P(const P** ppSrc1, int src1RoiShift,
                                            int src1Width,   int src1Height,
                                      const P** ppSrc2, int src2RoiShift, int src2Len,
                                            P** ppDst,  int dstRoiShift) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmMul_mva(const P*  pSrc1, int src1Stride1, int src1Stride2,
                                            int src1Width,  int src1Height,
                                      const P*  pSrc2, int src2Stride0, int src2Stride2, int src2Len,
                                            P*  pDst,  int dstStride0,  int dstStride2, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmMul_mva_P(const P** ppSrc1, int src1RoiShift,
                                            int src1Width,   int src1Height,
                                      const P** ppSrc2, int src2RoiShift, int src2Stride0, int src2Len,
                                            P** ppDst,  int dstRoiShift,  int dstStride0,  int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmMul_mva_L(const P*  pSrc1,  int src1Stride1,  int src1Stride2,
                                            int src1Width,   int src1Height,
                                      const P** ppSrc2, int src2RoiShift, int src2Stride2, int src2Len,
                                            P** ppDst,  int dstRoiShift,  int dstStride2,  int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmMul_tva(const P*  pSrc1, int src1Stride1, int src1Stride2,
                                            int src1Width,  int src1Height,
                                      const P*  pSrc2, int src2Stride0, int src2Stride2, int src2Len,
                                            P*  pDst,  int dstStride0,  int dstStride2,  int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmMul_tva_P(const P** ppSrc1, int src1RoiShift,
                                            int src1Width,   int src1Height,
                                      const P** ppSrc2, int src2RoiShift, int src2Stride0, int src2Len,
                                            P** ppDst,  int dstRoiShift,  int dstStride0,  int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmMul_tva_L(const P*  pSrc1,  int src1Stride1,  int src1Stride2,
                                            int src1Width,   int src1Height,
                                      const P** ppSrc2, int src2RoiShift, int src2Stride2, int src2Len,
                                            P** ppDst,  int dstRoiShift,  int dstStride2,  int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmMul_mav(const P*  pSrc1, int src1Stride0, int src1Stride1, int src1Stride2,
                                            int src1Width,  int src1Height,
                                      const P*  pSrc2, int src2Stride2, int src2Len,
                                            P*  pDst,  int dstStride0,  int dstStride2, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmMul_mav_P(const P** ppSrc1, int src1RoiShift, int src1Stride0,
                                            int src1Width,   int src1Height,
                                      const P** ppSrc2, int src2RoiShift, int src2Len,
                                            P** ppDst,  int dstRoiShift,  int dstStride0, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmMul_mav_L(const P** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                            int src1Width,   int src1Height,
                                      const P*  pSrc2,  int src2Stride2,  int src2Len,
                                            P** ppDst,  int dstRoiShift,  int dstStride2, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmMul_tav(const P*  pSrc1, int src1Stride0, int src1Stride1, int src1Stride2,
                                            int src1Width,  int src1Height,
                                      const P*  pSrc2, int src2Stride2, int src2Len,
                                            P*  pDst,  int dstStride0,  int dstStride2, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmMul_tav_P(const P** ppSrc1, int src1RoiShift, int src1Stride0,
                                            int src1Width,   int src1Height,
                                      const P** ppSrc2, int src2RoiShift, int src2Len,
                                            P** ppDst,  int dstRoiShift,  int dstStride0, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmMul_tav_L(const P** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                            int src1Width,   int src1Height,
                                      const P*  pSrc2,  int src2Stride2,  int src2Len,
                                            P** ppDst,  int dstRoiShift,  int dstStride2, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmMul_mava(const P*  pSrc1, int src1Stride0, int src1Stride1, int src1Stride2,
                                            int src1Width,  int src1Height,
                                      const P*  pSrc2, int src2Stride0, int src2Stride2, int src2Len,
                                            P*  pDst,  int dstStride0,  int dstStride2,  int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmMul_mava_P(const P** ppSrc1, int src1RoiShift, int src1Stride0,
                                            int src1Width,   int src1Height,
                                      const P** ppSrc2, int src2RoiShift, int src2Stride0, int src2Len,
                                            P** ppDst,  int dstRoiShift,  int dstStride0, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmMul_mava_L(const P** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                            int src1Width,   int src1Height,
                                      const P** ppSrc2, int src2RoiShift, int src2Stride2, int src2Len,
                                            P** ppDst,  int dstRoiShift,  int dstStride2,  int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmMul_tava(const P*  pSrc1, int src1Stride0, int src1Stride1, int src1Stride2,
                                            int src1Width,  int src1Height,
                                      const P*  pSrc2, int src2Stride0, int src2Stride2, int src2Len,
                                            P*  pDst,  int dstStride0,  int dstStride2,  int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmMul_tava_P(const P** ppSrc1, int src1RoiShift, int src1Stride0,
                                            int src1Width,   int src1Height,
                                      const P** ppSrc2, int src2RoiShift, int src2Stride0, int src2Len,
                                            P** ppDst,  int dstRoiShift,  int dstStride0,  int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmMul_tava_L(const P** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                            int src1Width,   int src1Height,
                                      const P** ppSrc2, int src2RoiShift, int src2Stride2, int src2Len,
                                            P** ppDst,  int dstRoiShift,  int dstStride2,  int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmMul_mm(const P*  pSrc1, int src1Stride1, int src1Stride2,
                                            int src1Width,  int src1Height,
                                      const P*  pSrc2, int src2Stride1, int src2Stride2,
                                            int src2Width,  int src2Height,
                                            P*  pDst,  int dstStride1,  int dstStride2) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmMul_mm_P(const P** ppSrc1, int src1RoiShift,
                                            int src1Width,   int src1Height,
                                      const P** ppSrc2, int src2RoiShift,
                                            int src2Width,   int src2Height,
                                            P** ppDst,  int dstRoiShift) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmMul_tm(const P*  pSrc1, int src1Stride1, int src1Stride2,
                                            int src1Width,  int src1Height,
                                      const P*  pSrc2, int src2Stride1, int src2Stride2,
                                            int src2Width,  int src2Height,
                                            P*  pDst,  int dstStride1,  int dstStride2) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmMul_tm_P(const P** ppSrc1, int src1RoiShift,
                                            int src1Width,   int src1Height,
                                      const P** ppSrc2, int src2RoiShift,
                                            int src2Width,   int src2Height,
                                            P** ppDst,  int dstRoiShift) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmMul_mt(const P*  pSrc1, int src1Stride1, int src1Stride2,
                                            int src1Width,  int src1Height,
                                      const P*  pSrc2, int src2Stride1, int src2Stride2,
                                            int src2Width,  int src2Height,
                                            P*  pDst,  int dstStride1,  int dstStride2) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmMul_mt_P(const P** ppSrc1, int src1RoiShift,
                                            int src1Width,   int src1Height,
                                      const P** ppSrc2, int src2RoiShift,
                                            int src2Width,   int src2Height,
                                            P** ppDst,  int dstRoiShift) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmMul_tt(const P*  pSrc1, int src1Stride1, int src1Stride2,
                                            int src1Width,  int src1Height,
                                      const P*  pSrc2, int src2Stride1, int src2Stride2,
                                            int src2Width,  int src2Height,
                                            P*  pDst,  int dstStride1,  int dstStride2) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmMul_tt_P(const P** ppSrc1, int src1RoiShift,
                                            int src1Width,   int src1Height,
                                      const P** ppSrc2, int src2RoiShift,
                                            int src2Width,   int src2Height,
                                            P** ppDst,  int dstRoiShift) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmMul_mma(const P*  pSrc1, int src1Stride1, int src1Stride2,
                                            int src1Width,  int src1Height,
                                      const P*  pSrc2, int src2Stride0, int src2Stride1, int src2Stride2,
                                            int src2Width,  int src2Height,
                                            P*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmMul_mma_P(const P** ppSrc1, int src1RoiShift,
                                            int src1Width,   int src1Height,
                                      const P** ppSrc2, int src2RoiShift, int src2Stride0,
                                            int src2Width,   int src2Height,
                                            P** ppDst,  int dstRoiShift,  int dstStride0,
                                            int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmMul_mma_L(const P*  pSrc1,  int src1Stride1,  int src1Stride2,
                                            int src1Width,   int src1Height,
                                      const P** ppSrc2, int src2RoiShift, int src2Stride1, int src2Stride2,
                                            int src2Width,   int src2Height,
                                            P** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmMul_tma(const P*  pSrc1, int src1Stride1, int src1Stride2,
                                            int src1Width,  int src1Height,
                                      const P*  pSrc2, int src2Stride0, int src2Stride1, int src2Stride2,
                                            int src2Width,  int src2Height,
                                            P*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmMul_tma_P(const P** ppSrc1, int src1RoiShift,
                                            int src1Width,   int src1Height,
                                      const P** ppSrc2, int src2RoiShift, int src2Stride0,
                                            int src2Width,   int src2Height,
                                            P** ppDst,  int dstRoiShift,  int dstStride0,
                                            int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmMul_tma_L(const P*  pSrc1,  int src1Stride1,  int src1Stride2,
                                            int src1Width,   int src1Height,
                                      const P** ppSrc2, int src2RoiShift, int src2Stride1, int src2Stride2,
                                            int src2Width,   int src2Height,
                                            P** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmMul_mta(const P*  pSrc1, int src1Stride1, int src1Stride2,
                                            int src1Width,  int src1Height,
                                      const P*  pSrc2, int src2Stride0, int src2Stride1, int src2Stride2,
                                            int src2Width,  int src2Height,
                                            P*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmMul_mta_P(const P** ppSrc1, int src1RoiShift,
                                            int src1Width,   int src1Height,
                                      const P** ppSrc2, int src2RoiShift, int src2Stride0,
                                            int src2Width,   int src2Height,
                                            P** ppDst,  int dstRoiShift,  int dstStride0,
                                            int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmMul_mta_L(const P*  pSrc1,  int src1Stride1,  int src1Stride2,
                                            int src1Width,   int src1Height,
                                      const P** ppSrc2, int src2RoiShift, int src2Stride1, int src2Stride2,
                                            int src2Width,   int src2Height,
                                            P** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmMul_tta(const P*  pSrc1, int src1Stride1, int src1Stride2,
                                            int src1Width,  int src1Height,
                                      const P*  pSrc2, int src2Stride0, int src2Stride1, int src2Stride2,
                                            int src2Width,  int src2Height,
                                            P*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmMul_tta_P(const P** ppSrc1, int src1RoiShift,
                                            int src1Width,   int src1Height,
                                      const P** ppSrc2, int src2RoiShift, int src2Stride0,
                                            int src2Width,   int src2Height,
                                            P** ppDst,  int dstRoiShift,  int dstStride0,
                                            int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmMul_tta_L(const P*  pSrc1,  int src1Stride1,  int src1Stride2,
                                            int src1Width,   int src1Height,
                                      const P** ppSrc2, int src2RoiShift, int src2Stride1, int src2Stride2,
                                            int src2Width,   int src2Height,
                                            P** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmMul_mam(const P*  pSrc1, int src1Stride0, int src1Stride1, int src1Stride2,
                                            int src1Width,  int src1Height,
                                      const P*  pSrc2, int src2Stride1, int src2Stride2,
                                            int src2Width,  int src2Height,
                                            P*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmMul_mam_P(const P** ppSrc1, int src1RoiShift, int src1Stride0,
                                            int src1Width,   int src1Height,
                                      const P** ppSrc2, int src2RoiShift,
                                            int src2Width,   int src2Height,
                                            P** ppDst,  int dstRoiShift,  int dstStride0,
                                            int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmMul_mam_L(const P** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                            int src1Width,   int src1Height,
                                      const P*  pSrc2,  int src2Stride1, int src2Stride2,
                                            int src2Width,   int src2Height,
                                            P** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmMul_tam(const P*  pSrc1, int src1Stride0, int src1Stride1, int src1Stride2,
                                            int src1Width,  int src1Height,
                                      const P*  pSrc2, int src2Stride1, int src2Stride2,
                                            int src2Width,  int src2Height,
                                            P*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmMul_tam_P(const P** ppSrc1, int src1RoiShift, int src1Stride0,
                                            int src1Width,   int src1Height,
                                      const P** ppSrc2, int src2RoiShift,
                                            int src2Width,   int src2Height,
                                            P** ppDst,  int dstRoiShift,  int dstStride0,
                                            int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmMul_tam_L(const P** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                            int src1Width,   int src1Height,
                                      const P*  pSrc2,  int src2Stride1, int src2Stride2,
                                            int src2Width,   int src2Height,
                                            P** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmMul_mat(const P*  pSrc1, int src1Stride0, int src1Stride1, int src1Stride2,
                                            int src1Width,  int src1Height,
                                      const P*  pSrc2, int src2Stride1, int src2Stride2,
                                            int src2Width,  int src2Height,
                                            P*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmMul_mat_P(const P** ppSrc1, int src1RoiShift, int src1Stride0,
                                            int src1Width,   int src1Height,
                                      const P** ppSrc2, int src2RoiShift,
                                            int src2Width,   int src2Height,
                                            P** ppDst,  int dstRoiShift,  int dstStride0,
                                            int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmMul_mat_L(const P** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                            int src1Width,   int src1Height,
                                      const P*  pSrc2,  int src2Stride1, int src2Stride2,
                                            int src2Width,   int src2Height,
                                            P** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmMul_tat(const P*  pSrc1, int src1Stride0, int src1Stride1, int src1Stride2,
                                            int src1Width,  int src1Height,
                                      const P*  pSrc2, int src2Stride1, int src2Stride2,
                                            int src2Width,  int src2Height,
                                            P*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmMul_tat_P(const P** ppSrc1, int src1RoiShift, int src1Stride0,
                                            int src1Width,   int src1Height,
                                      const P** ppSrc2, int src2RoiShift,
                                            int src2Width,   int src2Height,
                                            P** ppDst,  int dstRoiShift,  int dstStride0,
                                            int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmMul_tat_L(const P** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                            int src1Width,   int src1Height,
                                      const P*  pSrc2,  int src2Stride1, int src2Stride2,
                                            int src2Width,   int src2Height,
                                            P** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmMul_mama(const P*  pSrc1, int src1Stride0, int src1Stride1, int src1Stride2,
                                            int src1Width,  int src1Height,
                                      const P*  pSrc2, int src2Stride0, int src2Stride1, int src2Stride2,
                                            int src2Width,  int src2Height,
                                            P*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmMul_mama_P(const P** ppSrc1, int src1RoiShift, int src1Stride0,
                                            int src1Width,   int src1Height,
                                      const P** ppSrc2, int src2RoiShift, int src2Stride0,
                                            int src2Width,   int src2Height,
                                            P** ppDst,  int dstRoiShift,  int dstStride0,
                                            int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmMul_mama_L(const P** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                            int src1Width,   int src1Height,
                                      const P** ppSrc2, int src2RoiShift, int src2Stride1, int src2Stride2,
                                            int src2Width,   int src2Height,
                                            P** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmMul_tama(const P*  pSrc1, int src1Stride0, int src1Stride1, int src1Stride2,
                                            int src1Width,  int src1Height,
                                      const P*  pSrc2, int src2Stride0, int src2Stride1, int src2Stride2,
                                            int src2Width,  int src2Height,
                                            P*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmMul_tama_P(const P** ppSrc1, int src1RoiShift, int src1Stride0,
                                            int src1Width,   int src1Height,
                                      const P** ppSrc2, int src2RoiShift, int src2Stride0,
                                            int src2Width,   int src2Height,
                                            P** ppDst,  int dstRoiShift,  int dstStride0,
                                            int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmMul_tama_L(const P** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                            int src1Width,   int src1Height,
                                      const P** ppSrc2, int src2RoiShift, int src2Stride1, int src2Stride2,
                                            int src2Width,   int src2Height,
                                            P** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmMul_mata(const P*  pSrc1, int src1Stride0, int src1Stride1, int src1Stride2,
                                            int src1Width,  int src1Height,
                                      const P*  pSrc2, int src2Stride0, int src2Stride1, int src2Stride2,
                                            int src2Width,  int src2Height,
                                            P*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmMul_mata_P(const P** ppSrc1, int src1RoiShift, int src1Stride0,
                                            int src1Width,   int src1Height,
                                      const P** ppSrc2, int src2RoiShift, int src2Stride0,
                                            int src2Width,   int src2Height,
                                            P** ppDst,  int dstRoiShift,  int dstStride0,
                                            int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmMul_mata_L(const P** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                            int src1Width,   int src1Height,
                                      const P** ppSrc2, int src2RoiShift, int src2Stride1, int src2Stride2,
                                            int src2Width,   int src2Height,
                                            P** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmMul_tata(const P*  pSrc1, int src1Stride0, int src1Stride1, int src1Stride2,
                                            int src1Width,  int src1Height,
                                      const P*  pSrc2, int src2Stride0, int src2Stride1, int src2Stride2,
                                            int src2Width,  int src2Height,
                                            P*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmMul_tata_P(const P** ppSrc1, int src1RoiShift, int src1Stride0,
                                            int src1Width,   int src1Height,
                                      const P** ppSrc2, int src2RoiShift, int src2Stride0,
                                            int src2Width,   int src2Height,
                                            P** ppDst,  int dstRoiShift,  int dstStride0,
                                            int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmMul_tata_L(const P** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                            int src1Width,   int src1Height,
                                      const P** ppSrc2, int src2RoiShift, int src2Stride1, int src2Stride2,
                                            int src2Width,   int src2Height,
                                            P** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmAdd_mm(const P*  pSrc1, int src1Stride1, int src1Stride2,
                                      const P*  pSrc2, int src2Stride1, int src2Stride2,
                                            P*  pDst,  int dstStride1,  int dstStride2,
                                            int width, int height) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmAdd_mm_P(const P** ppSrc1, int src1RoiShift,
                                      const P** ppSrc2, int src2RoiShift,
                                            P** ppDst,  int dstRoiShift,
                                            int width, int height) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmAdd_tm(const P*  pSrc1, int src1Stride1, int src1Stride2,
                                      const P*  pSrc2, int src2Stride1, int src2Stride2,
                                            P*  pDst,  int dstStride1,  int dstStride2,
                                            int width, int height) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmAdd_tm_P(const P** ppSrc1, int src1RoiShift,
                                      const P** ppSrc2, int src2RoiShift,
                                            P** ppDst,  int dstRoiShift,
                                            int width, int height) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmAdd_tt(const P*  pSrc1, int src1Stride1, int src1Stride2,
                                      const P*  pSrc2, int src2Stride1, int src2Stride2,
                                            P*  pDst,  int dstStride1,  int dstStride2,
                                            int width, int height) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmAdd_tt_P(const P** ppSrc1, int src1RoiShift,
                                      const P** ppSrc2, int src2RoiShift,
                                            P** ppDst,  int dstRoiShift,
                                            int width, int height) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmAdd_mam(const P*  pSrc1, int src1Stride0, int src1Stride1, int src1Stride2,
                                      const P*  pSrc2, int src2Stride1, int src2Stride2,
                                            P*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmAdd_mam_P(const P** ppSrc1, int src1RoiShift, int src1Stride0,
                                      const P** ppSrc2, int src2RoiShift,
                                            P** ppDst,  int dstRoiShift,  int dstStride0,
                                            int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmAdd_mam_L(const P** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                      const P*  pSrc2,  int src2Stride1,  int src2Stride2,
                                            P** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmAdd_tam(const P*  pSrc1, int src1Stride0, int src1Stride1, int src1Stride2,
                                      const P*  pSrc2, int src2Stride1, int src2Stride2,
                                            P*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmAdd_tam_P(const P** ppSrc1, int src1RoiShift, int src1Stride0,
                                      const P** ppSrc2, int src2RoiShift,
                                            P** ppDst,  int dstRoiShift,  int dstStride0,
                                            int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmAdd_tam_L(const P** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                      const P*  pSrc2,  int src2Stride1,  int src2Stride2,
                                            P** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmAdd_mat(const P*  pSrc1, int src1Stride0, int src1Stride1, int src1Stride2,
                                      const P*  pSrc2, int src2Stride1, int src2Stride2,
                                            P*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmAdd_mat_P(const P** ppSrc1, int src1RoiShift, int src1Stride0,
                                      const P** ppSrc2, int src2RoiShift,
                                            P** ppDst,  int dstRoiShift,  int dstStride0,
                                            int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmAdd_mat_L(const P** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                      const P*  pSrc2,  int src2Stride1,  int src2Stride2,
                                            P** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmAdd_tat(const P*  pSrc1, int src1Stride0, int src1Stride1, int src1Stride2,
                                      const P*  pSrc2, int src2Stride1, int src2Stride2,
                                            P*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmAdd_tat_P(const P** ppSrc1, int src1RoiShift, int src1Stride0,
                                      const P** ppSrc2, int src2RoiShift,
                                            P** ppDst,  int dstRoiShift,  int dstStride0,
                                            int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmAdd_tat_L(const P** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                      const P*  pSrc2,  int src2Stride1,  int src2Stride2,
                                            P** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmAdd_mama(const P*  pSrc1, int src1Stride0, int src1Stride1, int src1Stride2,
                                      const P*  pSrc2, int src2Stride0, int src2Stride1, int src2Stride2,
                                            P*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmAdd_mama_P(const P** ppSrc1, int src1RoiShift, int src1Stride0,
                                      const P** ppSrc2, int src2RoiShift, int src2Stride0,
                                            P** ppDst,  int dstRoiShift,  int dstStride0,
                                            int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmAdd_mama_L(const P** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                      const P** ppSrc2, int src2RoiShift, int src2Stride1, int src2Stride2,
                                            P** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmAdd_tama(const P*  pSrc1, int src1Stride0, int src1Stride1, int src1Stride2,
                                      const P*  pSrc2, int src2Stride0, int src2Stride1, int src2Stride2,
                                            P*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmAdd_tama_P(const P** ppSrc1, int src1RoiShift, int src1Stride0,
                                      const P** ppSrc2, int src2RoiShift, int src2Stride0,
                                            P** ppDst,  int dstRoiShift,  int dstStride0,
                                            int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmAdd_tama_L(const P** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                      const P** ppSrc2, int src2RoiShift, int src2Stride1, int src2Stride2,
                                            P** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmAdd_tata(const P*  pSrc1, int src1Stride0, int src1Stride1, int src1Stride2,
                                      const P*  pSrc2, int src2Stride0, int src2Stride1, int src2Stride2,
                                            P*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmAdd_tata_P(const P** ppSrc1, int src1RoiShift, int src1Stride0,
                                      const P** ppSrc2, int src2RoiShift, int src2Stride0,
                                            P** ppDst,  int dstRoiShift,  int dstStride0,
                                            int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmAdd_tata_L(const P** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                      const P** ppSrc2, int src2RoiShift, int src2Stride1, int src2Stride2,
                                            P** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmSub_mm(const P*  pSrc1, int src1Stride1, int src1Stride2,
                                      const P*  pSrc2, int src2Stride1, int src2Stride2,
                                            P*  pDst,  int dstStride1,  int dstStride2,
                                            int width, int height) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmSub_mm_P(const P** ppSrc1, int src1RoiShift,
                                      const P** ppSrc2, int src2RoiShift,
                                            P** ppDst,  int dstRoiShift,
                                            int width, int height) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmSub_tm(const P*  pSrc1, int src1Stride1, int src1Stride2,
                                      const P*  pSrc2, int src2Stride1, int src2Stride2,
                                            P*  pDst,  int dstStride1,  int dstStride2,
                                            int width, int height) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmSub_tm_P(const P** ppSrc1, int src1RoiShift,
                                      const P** ppSrc2, int src2RoiShift,
                                            P** ppDst,  int dstRoiShift,
                                            int width, int height) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmSub_mt(const P*  pSrc1, int src1Stride1, int src1Stride2,
                                      const P*  pSrc2, int src2Stride1, int src2Stride2,
                                            P*  pDst,  int dstStride1,  int dstStride2,
                                            int width, int height) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmSub_mt_P(const P** ppSrc1, int src1RoiShift,
                                      const P** ppSrc2, int src2RoiShift,
                                            P** ppDst,  int dstRoiShift,
                                            int width, int height) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmSub_tt(const P*  pSrc1, int src1Stride1, int src1Stride2,
                                      const P*  pSrc2, int src2Stride1, int src2Stride2,
                                            P*  pDst,  int dstStride1,  int dstStride2,
                                            int width, int height) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmSub_tt_P(const P** ppSrc1, int src1RoiShift,
                                      const P** ppSrc2, int src2RoiShift,
                                            P** ppDst,  int dstRoiShift,
                                            int width, int height) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmSub_mma(const P*  pSrc1, int src1Stride1, int src1Stride2,
                                      const P*  pSrc2, int src2Stride0, int src2Stride1, int src2Stride2,
                                            P*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmSub_mma_P(const P** ppSrc1, int src1RoiShift,
                                      const P** ppSrc2, int src2RoiShift, int src2Stride0,
                                            P** ppDst,  int dstRoiShift,  int dstStride0,
                                            int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmSub_mma_L(const P*  pSrc1,  int src1Stride1,  int src1Stride2,
                                      const P** ppSrc2, int src2RoiShift, int src2Stride1, int src2Stride2,
                                            P** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmSub_tma(const P*  pSrc1, int src1Stride1, int src1Stride2,
                                      const P*  pSrc2, int src2Stride0, int src2Stride1, int src2Stride2,
                                            P*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmSub_tma_P(const P** ppSrc1, int src1RoiShift,
                                      const P** ppSrc2, int src2RoiShift, int src2Stride0,
                                            P** ppDst,  int dstRoiShift,  int dstStride0,
                                            int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmSub_tma_L(const P*  pSrc1,  int src1Stride1,  int src1Stride2,
                                      const P** ppSrc2, int src2RoiShift, int src2Stride1, int src2Stride2,
                                            P** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmSub_mta(const P*  pSrc1, int src1Stride1, int src1Stride2,
                                      const P*  pSrc2, int src2Stride0, int src2Stride1, int src2Stride2,
                                            P*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmSub_mta_P(const P** ppSrc1, int src1RoiShift,
                                      const P** ppSrc2, int src2RoiShift, int src2Stride0,
                                            P** ppDst,  int dstRoiShift,  int dstStride0,
                                            int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmSub_mta_L(const P*  pSrc1,  int src1Stride1,  int src1Stride2,
                                      const P** ppSrc2, int src2RoiShift, int src2Stride1, int src2Stride2,
                                            P** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmSub_tta(const P*  pSrc1, int src1Stride1, int src1Stride2,
                                      const P*  pSrc2, int src2Stride0, int src2Stride1, int src2Stride2,
                                            P*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmSub_tta_P(const P** ppSrc1, int src1RoiShift,
                                      const P** ppSrc2, int src2RoiShift, int src2Stride0,
                                            P** ppDst,  int dstRoiShift,  int dstStride0,
                                            int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmSub_tta_L(const P*  pSrc1,  int src1Stride1,  int src1Stride2,
                                      const P** ppSrc2, int src2RoiShift, int src2Stride1, int src2Stride2,
                                            P** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmSub_mam(const P*  pSrc1, int src1Stride0, int src1Stride1, int src1Stride2,
                                      const P*  pSrc2, int src2Stride1, int src2Stride2,
                                            P*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmSub_mam_P(const P** ppSrc1, int src1RoiShift, int src1Stride0,
                                      const P** ppSrc2, int src2RoiShift,
                                            P** ppDst,  int dstRoiShift,  int dstStride0,
                                            int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmSub_mam_L(const P** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                      const P*  pSrc2,  int src2Stride1,  int src2Stride2,
                                            P** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmSub_tam(const P*  pSrc1, int src1Stride0, int src1Stride1, int src1Stride2,
                                      const P*  pSrc2, int src2Stride1, int src2Stride2,
                                            P*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmSub_tam_P(const P** ppSrc1, int src1RoiShift, int src1Stride0,
                                      const P** ppSrc2, int src2RoiShift,
                                            P** ppDst,  int dstRoiShift,  int dstStride0,
                                            int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmSub_tam_L(const P** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                      const P*  pSrc2,  int src2Stride1,  int src2Stride2,
                                            P** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmSub_mat(const P*  pSrc1, int src1Stride0, int src1Stride1, int src1Stride2,
                                      const P*  pSrc2, int src2Stride1, int src2Stride2,
                                            P*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmSub_mat_P(const P** ppSrc1, int src1RoiShift, int src1Stride0,
                                      const P** ppSrc2, int src2RoiShift,
                                            P** ppDst,  int dstRoiShift,  int dstStride0,
                                            int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmSub_mat_L(const P** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                      const P*  pSrc2,  int src2Stride1,  int src2Stride2,
                                            P** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmSub_tat(const P*  pSrc1, int src1Stride0, int src1Stride1, int src1Stride2,
                                      const P*  pSrc2, int src2Stride1, int src2Stride2,
                                            P*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmSub_tat_P(const P** ppSrc1, int src1RoiShift, int src1Stride0,
                                      const P** ppSrc2, int src2RoiShift,
                                            P** ppDst,  int dstRoiShift,  int dstStride0,
                                            int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmSub_tat_L(const P** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                      const P*  pSrc2,  int src2Stride1,  int src2Stride2,
                                            P** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmSub_mama(const P*  pSrc1, int src1Stride0, int src1Stride1, int src1Stride2,
                                      const P*  pSrc2, int src2Stride0, int src2Stride1, int src2Stride2,
                                            P*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmSub_mama_P(const P** ppSrc1, int src1RoiShift, int src1Stride0,
                                      const P** ppSrc2, int src2RoiShift, int src2Stride0,
                                            P** ppDst,  int dstRoiShift,  int dstStride0,
                                            int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmSub_mama_L(const P** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                      const P** ppSrc2, int src2RoiShift, int src2Stride1, int src2Stride2,
                                            P** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmSub_tama(const P*  pSrc1, int src1Stride0, int src1Stride1, int src1Stride2,
                                      const P*  pSrc2, int src2Stride0, int src2Stride1, int src2Stride2,
                                            P*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmSub_tama_P(const P** ppSrc1, int src1RoiShift, int src1Stride0,
                                      const P** ppSrc2, int src2RoiShift, int src2Stride0,
                                            P** ppDst,  int dstRoiShift,  int dstStride0,
                                            int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmSub_tama_L(const P** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                      const P** ppSrc2, int src2RoiShift, int src2Stride1, int src2Stride2,
                                            P** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmSub_mata(const P*  pSrc1, int src1Stride0, int src1Stride1, int src1Stride2,
                                      const P*  pSrc2, int src2Stride0, int src2Stride1, int src2Stride2,
                                            P*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmSub_mata_P(const P** ppSrc1, int src1RoiShift, int src1Stride0,
                                      const P** ppSrc2, int src2RoiShift, int src2Stride0,
                                            P** ppDst,  int dstRoiShift,  int dstStride0,
                                            int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmSub_mata_L(const P** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                      const P** ppSrc2, int src2RoiShift, int src2Stride1, int src2Stride2,
                                            P** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmSub_tata(const P*  pSrc1, int src1Stride0, int src1Stride1, int src1Stride2,
                                      const P*  pSrc2, int src2Stride0, int src2Stride1, int src2Stride2,
                                            P*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmSub_tata_P(const P** ppSrc1, int src1RoiShift, int src1Stride0,
                                      const P** ppSrc2, int src2RoiShift, int src2Stride0,
                                            P** ppDst,  int dstRoiShift,  int dstStride0,
                                            int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmSub_tata_L(const P** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                      const P** ppSrc2, int src2RoiShift, int src2Stride1, int src2Stride2,
                                            P** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmGaxpy_mv(const P*  pSrc1, int src1Stride1, int src1Stride2,
                                             int src1Width,  int src1Height,
                                       const P*  pSrc2, int src2Stride2, int src2Len,
                                       const P*  pSrc3, int src2Stride3, int src3Len,
                                             P*  pDst,  int dstStride2) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmGaxpy_mv_P(const P** ppSrc1, int src1RoiShift,
                                             int src1Width,   int src1Height,
                                       const P** ppSrc2, int src2RoiShift, int src2Len,
                                       const P** ppSrc3, int src3RoiShift, int src3Len,
                                             P** ppDst,  int dstRoiShift) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmGaxpy_mva(const P*  pSrc1, int src1Stride1, int src1Stride2,
                                             int src1Width,  int src1Height,
                                       const P*  pSrc2, int src2Stride0, int src2Stride2, int src2Len,
                                       const P*  pSrc3, int src3Stride0, int src3Stride2, int src3Len,
                                             P*  pDst,  int dstStride0,  int dstStride2, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmGaxpy_mva_P(const P** ppSrc1, int src1RoiShift,
                                             int src1Width,   int src1Height,
                                       const P** ppSrc2, int src2RoiShift, int src2Stride0, int src2Len,
                                       const P** ppSrc3, int src3RoiShift, int src3Stride0, int src3Len,
                                             P** ppDst,  int dstRoiShift,  int dstStride0,  int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmGaxpy_mva_L(const P*  pSrc1,  int src1Stride1,  int src1Stride2,
                                             int src1Width,   int src1Height,
                                       const P** ppSrc2, int src2RoiShift, int src2Stride2, int src2Len,
                                       const P** ppSrc3, int src3RoiShift, int src3Stride2, int src3Len,
                                             P** ppDst,  int dstRoiShift,  int dstStride2,  int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmLUDecomp_m(const P*  pSrc,  int srcStride1, int srcStride2,
                                               int*     pDstIndex,
                                               P*  pDst,  int dstStride1, int dstStride2,
                                               int widthHeight) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmLUDecomp_m_P(const P** ppSrc, int srcRoiShift,
                                               int*     pDstIndex,
                                               P** ppDst, int dstRoiShift,
                                               int widthHeight) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmLUDecomp_ma(const P*  pSrc,   int srcStride0, int srcStride1, int srcStride2,
                                               int*     pDstIndex,
                                               P*  pDst,   int dstStride0, int dstStride1, int dstStride2,
                                               int widthHeight, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmLUDecomp_ma_P(const P** ppSrc,  int srcRoiShift, int srcStride0,
                                               int*     pDstIndex,
                                               P** ppDst,  int dstRoiShift, int dstStride0,
                                               int widthHeight, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmLUDecomp_ma_L(const P** ppSrc,  int srcRoiShift, int srcStride1, int srcStride2,
                                               int*     pDstIndex,
                                               P** ppDst,  int dstRoiShift, int dstStride1, int dstStride2,
                                               int widthHeight, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmLUBackSubst_mv(const P*  pSrc1,  int src1Stride1, int src1Stride2,
                                                    int* pSrcIndex,
                                              const P*  pSrc2,  int src2Stride2,
                                                    P*  pDst,   int dstStride2,
                                                    int widthHeight) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmLUBackSubst_mv_P(const P** ppSrc1, int src1RoiShift,
                                                    int* pSrcIndex,
                                              const P** ppSrc2, int src2RoiShift,
                                                    P** ppDst,  int dstRoiShift,
                                                    int widthHeight) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmLUBackSubst_mva(const P*  pSrc1,  int src1Stride1, int src1Stride2,
                                                    int* pSrcIndex,
                                              const P*  pSrc2,  int src2Stride0, int src2Stride2,
                                                    P*  pDst,   int dstStride0,  int dstStride2,
                                                    int widthHeight, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmLUBackSubst_mva_P(const P** ppSrc1, int src1RoiShift,
                                                    int* pSrcIndex,
                                              const P** ppSrc2, int src2RoiShift, int src2Stride0,
                                                    P** ppDst,  int dstRoiShift,  int dstStride0,
                                                    int widthHeight, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmLUBackSubst_mva_L(const P*  pSrc1,  int src1Stride1,  int src1Stride2,
                                                    int* pSrcIndex,
                                              const P** ppSrc2, int src2RoiShift, int src2Stride2,
                                                    P** ppDst,  int dstRoiShift,  int dstStride2,
                                                    int widthHeight, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmLUBackSubst_mava(const P*  pSrc1,  int src1Stride0, int src1Stride1, int src1Stride2,
                                                    int* pSrcIndex,
                                              const P*  pSrc2,  int src2Stride0, int src2Stride2,
                                                    P*  pDst,   int dstStride0,  int dstStride2,
                                                    int widthHeight, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmLUBackSubst_mava_P(const P** ppSrc1, int src1RoiShift, int src1Stride0,
                                                    int* pSrcIndex,
                                              const P** ppSrc2, int src2RoiShift, int src2Stride0,
                                                    P** ppDst,  int dstRoiShift,  int dstStride0,
                                                    int widthHeight, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmLUBackSubst_mava_L(const P** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                                    int* pSrcIndex,
                                              const P** ppSrc2, int src2RoiShift, int src2Stride2,
                                                    P** ppDst,  int dstRoiShift,  int dstStride2,
                                                    int widthHeight, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmCholeskyDecomp_m(const P*  pSrc,  int srcStride1, int srcStride2,
                                                     P*  pDst,  int dstStride1, int dstStride2,
                                                     int widthHeight) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmCholeskyDecomp_m_P(const P** ppSrc, int srcRoiShift,
                                                     P** ppDst, int dstRoiShift,
                                                     int widthHeight) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmCholeskyDecomp_ma(const P*  pSrc,   int srcStride0, int srcStride1, int srcStride2,
                                                     P*  pDst,   int dstStride0, int dstStride1, int dstStride2,
                                                     int widthHeight, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmCholeskyDecomp_ma_P(const P** ppSrc,  int srcRoiShift, int srcStride0,
                                                     P** ppDst,  int dstRoiShift, int dstStride0,
                                                     int widthHeight, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmCholeskyDecomp_ma_L(const P** ppSrc,  int srcRoiShift, int srcStride1, int srcStride2,
                                                     P** ppDst,  int dstRoiShift, int dstStride1, int dstStride2,
                                                     int widthHeight, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmCholeskyBackSubst_mv(const P*  pSrc1,  int src1Stride1, int src1Stride2,
                                                    const P*  pSrc2,  int src2Stride2,
                                                          P*  pDst,   int dstStride2,
                                                          int widthHeight) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmCholeskyBackSubst_mv_P(const P** ppSrc1, int src1RoiShift,
                                                    const P** ppSrc2, int src2RoiShift,
                                                          P** ppDst,  int dstRoiShift,
                                                          int widthHeight) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmCholeskyBackSubst_mva(const P*  pSrc1,  int src1Stride1, int src1Stride2,
                                                    const P*  pSrc2,  int src2Stride0, int src2Stride2,
                                                          P*  pDst,   int dstStride0,  int dstStride2,
                                                          int widthHeight, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmCholeskyBackSubst_mva_P(const P** ppSrc1, int src1RoiShift,
                                                    const P** ppSrc2, int src2RoiShift, int src2Stride0,
                                                          P** ppDst,  int dstRoiShift,  int dstStride0,
                                                          int widthHeight, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmCholeskyBackSubst_mva_L(const P*  pSrc1,  int src1Stride1,  int src1Stride2,
                                                    const P** ppSrc2, int src2RoiShift, int src2Stride2,
                                                          P** ppDst,  int dstRoiShift,  int dstStride2,
                                                          int widthHeight, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmCholeskyBackSubst_mava(const P*  pSrc1,  int src1Stride0, int src1Stride1, int src1Stride2,
                                                    const P*  pSrc2,  int src2Stride0, int src2Stride2,
                                                          P*  pDst,   int dstStride0,  int dstStride2,
                                                          int widthHeight, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmCholeskyBackSubst_mava_P(const P** ppSrc1, int src1RoiShift, int src1Stride0,
                                                    const P** ppSrc2, int src2RoiShift, int src2Stride0,
                                                          P** ppDst,  int dstRoiShift,  int dstStride0,
                                                          int widthHeight, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmCholeskyBackSubst_mava_L(const P** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                                    const P** ppSrc2, int src2RoiShift, int src2Stride2,
                                                          P** ppDst,  int dstRoiShift,  int dstStride2,
                                                          int widthHeight, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmQRDecomp_m(const P*  pSrc,  int srcStride1, int srcStride2,
                                               P*  pBuffer,
                                               P*  pDst,  int dstStride1, int dstStride2,
                                               int width, int height) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmQRDecomp_m_P(const P** ppSrc, int srcRoiShift,
                                               P*  pBuffer,
                                               P** ppDst, int dstRoiShift,
                                               int width, int height) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmQRDecomp_ma(const P*  pSrc,   int srcStride0, int srcStride1, int srcStride2,
                                               P*  pBuffer,
                                               P*  pDst,   int dstStride0, int dstStride1, int dstStride2,
                                               int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmQRDecomp_ma_P(const P** ppSrc,  int srcRoiShift, int srcStride0,
                                               P*  pBuffer,
                                               P** ppDst,  int dstRoiShift, int dstStride0,
                                               int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmQRDecomp_ma_L(const P** ppSrc,  int srcRoiShift, int srcStride1, int srcStride2,
                                               P*  pBuffer,
                                               P** ppDst,  int dstRoiShift, int dstStride1, int dstStride2,
                                               int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmQRBackSubst_mv(const P*  pSrc1,  int src1Stride1, int src1Stride2,
                                                    P*  pBuffer,
                                              const P*  pSrc2,  int src2Stride2,
                                                    P*  pDst,   int dstStride2,
                                                    int width, int height) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmQRBackSubst_mv_P(const P** ppSrc1, int src1RoiShift,
                                                    P*  pBuffer,
                                              const P** ppSrc2, int src2RoiShift,
                                                    P** ppDst,  int dstRoiShift,
                                                    int width, int height) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmQRBackSubst_mva(const P*  pSrc1,  int src1Stride1, int src1Stride2,
                                                    P*  pBuffer,
                                              const P*  pSrc2,  int src2Stride0, int src2Stride2,
                                                    P*  pDst,   int dstStride0,  int dstStride2,
                                                    int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmQRBackSubst_mva_P(const P** ppSrc1, int src1RoiShift,
                                                    P*  pBuffer,
                                              const P** ppSrc2, int src2RoiShift, int src2Stride0,
                                                    P** ppDst,  int dstRoiShift,  int dstStride0,
                                                    int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmQRBackSubst_mva_L(const P*  pSrc1,  int src1Stride1,  int src1Stride2,
                                                    P*  pBuffer,
                                              const P** ppSrc2, int src2RoiShift, int src2Stride2,
                                                    P** ppDst,  int dstRoiShift,  int dstStride2,
                                                    int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmQRBackSubst_mava(const P*  pSrc1,  int src1Stride0, int src1Stride1, int src1Stride2,
                                                    P*  pBuffer,
                                              const P*  pSrc2,  int src2Stride0, int src2Stride2,
                                                    P*  pDst,   int dstStride0,  int dstStride2,
                                                    int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmQRBackSubst_mava_P(const P** ppSrc1, int src1RoiShift, int src1Stride0,
                                                    P*  pBuffer,
                                              const P** ppSrc2, int src2RoiShift, int src2Stride0,
                                                    P** ppDst,  int dstRoiShift,  int dstStride0,
                                                    int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmQRBackSubst_mava_L(const P** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                                    P*  pBuffer,
                                              const P** ppSrc2, int src2RoiShift, int src2Stride2,
                                                    P** ppDst,  int dstRoiShift,  int dstStride2,
                                                    int width, int height, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmEigenValuesVectorsSym_m(const P* pSrc, int srcStride1, int srcStride2,
                                                           P* pBuffer,
                                                           P* pDstVectors, int dstStride1, int dstStride2,
                                                           P* pDstValues,  int widthHeight) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmEigenValuesVectorsSym_m_P(const P** ppSrc, int srcRoiShift,
                                                           P*  pBuffer,
                                                           P** ppDstVectors, int dstRoiShift,
                                                           P*  pDstValues,   int widthHeight) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmEigenValuesVectorsSym_ma(const P* pSrc, int srcStride0, int srcStride1, int srcStride2,
                                                            P* pBuffer,
                                                            P* pDstVectors, int dstStride0, int dstStride1, int dstStride2,
                                                            P* pDstValues,  int widthHeight, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmEigenValuesVectorsSym_ma_P(const P** ppSrc, int srcRoiShift, int srcStride0,
                                                            P*  pBuffer,
                                                            P** ppDstVectors, int dstRoiShift, int dstStride0,
                                                            P*  pDstValues,   int widthHeight, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmEigenValuesVectorsSym_ma_L(const P** ppSrc, int srcRoiShift, int srcStride1, int srcStride2,
                                                            P*  pBuffer,
                                                            P** ppDstVectors, int dstRoiShift, int dstStride1, int dstStride2,
                                                            P*  pDstValues,   int widthHeight, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmEigenValuesSym_m(const P* pSrc, int srcStride1, int srcStride2,
                                                    P* pBuffer,
                                                    P* pDstValues, int widthHeight) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmEigenValuesSym_m_P(const P** ppSrc, int srcRoiShift,
                                                    P*  pBuffer,
                                                    P*  pDstValues, int widthHeight) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmEigenValuesSym_ma(const P* pSrc, int srcStride0, int srcStride1, int srcStride2,
                                                     P* pBuffer,
                                                     P* pDstValues, int widthHeight, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmEigenValuesSym_ma_P(const P** ppSrc, int srcRoiShift, int srcStride0,
                                                     P*  pBuffer,
                                                     P*  pDstValues, int widthHeight, int count) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippmEigenValuesSym_ma_L(const P** ppSrc, int srcRoiShift, int srcStride1, int srcStride2,
                                                     P*  pBuffer,
                                                     P*  pDstValues, int widthHeight, int count) {
 return ippStsDataTypeErr;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef NICE_USELIB_IPP
template<class P1, class P2>
inline IppStatus ippsHilbert(const P1 *pSrc, P2 *pDst,
                                        IppsHilbertSpec_32f32fc *pSpec) {
 return ippStsDataTypeErr;
}
template<class P1, class P2>
inline IppStatus ippsHilbert(const P1 *pSrc, P2 *pDst,
                                        IppsHilbertSpec_16s32fc *pSpec) {
 return ippStsDataTypeErr;
}
template<class P1, class P2>
inline IppStatus ippsHilbert_Sfs(const P1 *pSrc, P2 *pDst,
                                        IppsHilbertSpec_16s16sc *pSpec, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRSparseInit( IppsFIRSparseState_32f** pState,
    const P *pNZTaps, const Ipp32s* pNZTapPos, int nzTapsLen,
    const P *pDlyLine, Ipp8u *pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsIIRSparseInit( IppsIIRSparseState_32f** pState,
        const P* pNZTaps, const Ipp32s* pNZTapPos, int nzTapsLen1,
        int nzTapsLen2, const P* pDlyLine, Ipp8u* pBuf ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRSparse(const P* pSrc, P* pDst, int len,
        IppsFIRSparseState_32f* pState) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsIIRSparse(const P* pSrc, P* pDst, int len,
       IppsIIRSparseState_32f* pState) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsIIRInitAlloc(IppsIIRState_32f** pState,
       const P* pTaps, int order, const P* pDlyLine) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsIIRInitAlloc(IppsIIRState_32fc** pState,
       const P* pTaps, int order, const P* pDlyLine) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsIIRInitAlloc(IppsIIRState_64f** pState,
       const P* pTaps, int order, const P* pDlyLine) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsIIRInitAlloc(IppsIIRState_64fc** pState,
       const P* pTaps, int order, const P* pDlyLine) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsIIRInitAlloc_BiQuad(IppsIIRState_32f** pState,
       const P* pTaps, int numBq, const P* pDlyLine) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsIIRInitAlloc_BiQuad(IppsIIRState_32fc** pState,
       const P* pTaps, int numBq, const P* pDlyLine) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsIIRInitAlloc_BiQuad(IppsIIRState_64f** pState,
       const P* pTaps, int numBq, const P* pDlyLine) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsIIRInitAlloc_BiQuad(IppsIIRState_64fc** pState,
       const P* pTaps, int numBq, const P* pDlyLine) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsIIRGetDlyLine(const IppsIIRState_32f* pState, P* pDlyLine) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsIIRSetDlyLine(IppsIIRState_32f* pState, const P* pDlyLine) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsIIRGetDlyLine(const IppsIIRState_32fc* pState, P* pDlyLine) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsIIRSetDlyLine(IppsIIRState_32fc* pState, const P* pDlyLine) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsIIRGetDlyLine(const IppsIIRState_64f* pState, P* pDlyLine) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsIIRSetDlyLine(IppsIIRState_64f* pState, const P* pDlyLine) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsIIRGetDlyLine(const IppsIIRState_64fc* pState, P* pDlyLine) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsIIRSetDlyLine(IppsIIRState_64fc* pState, const P* pDlyLine) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsIIROne(P src, P* pDstVal, IppsIIRState_32f* pState) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsIIROne(P src, P* pDstVal, IppsIIRState_32fc* pState) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsIIROne32f_Sfs(P src, P* pDstVal, IppsIIRState32f_16s* pState, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsIIROne32fc_Sfs(P src, P* pDstVal, IppsIIRState32fc_16sc* pState, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsIIROne(P src, P* pDstVal, IppsIIRState_64f* pState) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsIIROne(P src, P* pDstVal, IppsIIRState_64fc* pState) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsIIROne64f(P src, P* pDstVal, IppsIIRState64f_32f* pState) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsIIROne64fc(P src, P* pDstVal, IppsIIRState64fc_32fc* pState) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsIIROne64f_Sfs(P src, P* pDstVal, IppsIIRState64f_32s* pState, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsIIROne64fc_Sfs(P src, P* pDstVal, IppsIIRState64fc_32sc* pState, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsIIROne64f_Sfs(P src, P* pDstVal, IppsIIRState64f_16s* pState, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsIIROne64fc_Sfs(P src, P* pDstVal, IppsIIRState64fc_16sc* pState, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsIIR(const P* pSrc, P* pDst, int len,
       IppsIIRState_32f* pState) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsIIR_I(P* pSrcDst, int len, IppsIIRState_32f* pState) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsIIR(const P* pSrc, P* pDst, int len,
       IppsIIRState_32fc* pState) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsIIR_I(P* pSrcDst, int len, IppsIIRState_32fc* pState) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsIIR32f_Sfs(const P* pSrc, P* pDst, int len,
       IppsIIRState32f_16s* pState, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsIIR32f_ISfs(P* pSrcDst, int len,
       IppsIIRState32f_16s* pState, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsIIR32fc_Sfs(const P* pSrc, P* pDst, int len,
       IppsIIRState32fc_16sc* pState, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsIIR32fc_ISfs(P* pSrcDst, int len,
       IppsIIRState32fc_16sc* pState, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsIIR(const P* pSrc, P* pDst, int len,
       IppsIIRState_64f* pState) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsIIR_I(P* pSrcDst, int len, IppsIIRState_64f* pState) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsIIR(const P* pSrc, P* pDst, int len,
       IppsIIRState_64fc* pState) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsIIR_I(P* pSrcDst, int len, IppsIIRState_64fc* pState) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsIIR64f(const P* pSrc, P* pDst, int len,
       IppsIIRState64f_32f* pState) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsIIR64f_I(P* pSrcDst, int len, IppsIIRState64f_32f* pState) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsIIR64fc(const P* pSrc, P* pDst, int len,
       IppsIIRState64fc_32fc* pState) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsIIR64fc_I(P* pSrcDst, int len, IppsIIRState64fc_32fc* pState) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsIIR64f_Sfs(const P* pSrc, P* pDst, int len,
       IppsIIRState64f_32s* pState, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsIIR64f_ISfs(P* pSrcDst, int len,
       IppsIIRState64f_32s* pState, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsIIR64fc_Sfs(const P* pSrc, P* pDst, int len,
       IppsIIRState64fc_32sc* pState, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsIIR64fc_ISfs(P* pSrcDst, int len,
       IppsIIRState64fc_32sc* pState, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsIIR64f_Sfs(const P* pSrc, P* pDst, int len,
       IppsIIRState64f_16s* pState, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsIIR64f_ISfs(P* pSrcDst, int len,
       IppsIIRState64f_16s* pState, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsIIR64fc_Sfs(const P* pSrc, P* pDst, int len,
       IppsIIRState64fc_16sc* pState, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsIIR64fc_ISfs(P* pSrcDst, int len,
       IppsIIRState64fc_16sc* pState, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsIIROne32s_Sfs(P src, P* pDstVal, IppsIIRState32s_16s* pState, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsIIROne32sc_Sfs(P src, P* pDstVal, IppsIIRState32sc_16sc* pState, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsIIR32s_Sfs(const P* pSrc, P* pDst, int len,
       IppsIIRState32s_16s* pState, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsIIR32sc_Sfs(const P* pSrc, P* pDst, int len,
       IppsIIRState32sc_16sc* pState, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsIIR32s_ISfs(P* pSrcDst, int len, IppsIIRState32s_16s* pState,
       int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsIIR32sc_ISfs(P* pSrcDst, int len, IppsIIRState32sc_16sc* pState,
       int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsIIR_Direct( const P* pSrc, P* pDst,
                 int len, const P* pTaps, int order, Ipp32s* pDlyLine ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsIIR_Direct_I( P* pSrcDst, int len,
                          const P* pTaps, int order, Ipp32s* pDlyLine ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsIIROne_Direct( P src, P* pDstVal,
                          const P* pTaps, int order, Ipp32s* pDlyLine ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsIIROne_Direct_I( P* pSrcDst,
                          const P* pTaps, int order, Ipp32s* pDlyLine ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsIIR_BiQuadDirect( const P* pSrc, P* pDst,
             int len, const P* pTaps, int numBq, Ipp32s* pDlyLine ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsIIR_BiQuadDirect_I( P* pSrcDst, int len,
                     const P * pTaps, int numBq, Ipp32s* pDlyLine ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsIIROne_BiQuadDirect( P src, P* pDstVal,
                      const P* pTaps, int numBq, Ipp32s* pDlyLine ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsIIROne_BiQuadDirect_I( P* pSrcDstVal,
                      const P* pTaps, int numBq, Ipp32s* pDlyLine ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsIIRInit( IppsIIRState_32f** pState,
         const P* pTaps, int order, const P* pDlyLine, Ipp8u* pBuf ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsIIRInit( IppsIIRState_32fc** pState,
       const P* pTaps, int order, const P* pDlyLine, Ipp8u* pBuf ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsIIRInit_BiQuad( IppsIIRState_32f** pState,
         const P* pTaps, int numBq, const P* pDlyLine, Ipp8u* pBuf ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsIIRInit_BiQuad( IppsIIRState_32fc** pState,
       const P* pTaps, int numBq, const P* pDlyLine, Ipp8u* pBuf ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsIIRInit( IppsIIRState_64f** pState,
         const P* pTaps, int order, const P* pDlyLine, Ipp8u* pBuf ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsIIRInit( IppsIIRState_64fc** pState,
       const P* pTaps, int order, const P* pDlyLine, Ipp8u* pBuf ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsIIRInit_BiQuad( IppsIIRState_64f** pState,
         const P* pTaps, int numBq, const P* pDlyLine, Ipp8u* pBuf ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsIIRInit_BiQuad( IppsIIRState_64fc** pState,
       const P* pTaps, int numBq, const P* pDlyLine, Ipp8u* pBuf ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsIIRSetTaps( const P *pTaps,
                                                    IppsIIRState_32f* pState ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsIIRSetTaps( const P *pTaps,
                                                   IppsIIRState_32fc* pState ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsIIRSetTaps( const P *pTaps,
                                                    IppsIIRState_64f* pState ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsIIRSetTaps( const P *pTaps,
                                                   IppsIIRState_64fc* pState ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRInitAlloc(IppsFIRState_32f** pState,
        const P* pTaps, int tapsLen, const P* pDlyLine) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRMRInitAlloc(IppsFIRState_32f** pState,
        const P* pTaps, int tapsLen, int upFactor, int upPhase,
        int downFactor, int downPhase, const P* pDlyLine) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRInitAlloc(IppsFIRState_32fc** pState,
        const P* pTaps, int tapsLen, const P* pDlyLine) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRMRInitAlloc(IppsFIRState_32fc** pState,
        const P* pTaps, int tapsLen, int upFactor, int upPhase,
        int downFactor, int downPhase, const P* pDlyLine) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRInitAlloc32f(IppsFIRState32f_16s** pState,
        const Ipp32f* pTaps, int tapsLen, const P* pDlyLine) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRMRInitAlloc32f(IppsFIRState32f_16s** pState,
        const Ipp32f* pTaps, int tapsLen, int upFactor, int upPhase,
        int downFactor, int downPhase, const P* pDlyLine) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRInitAlloc32fc(IppsFIRState32fc_16sc** pState,
        const Ipp32fc* pTaps, int tapsLen, const P* pDlyLine) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRMRInitAlloc32fc(IppsFIRState32fc_16sc** pState,
        const Ipp32fc* pTaps, int tapsLen, int upFactor, int upPhase,
        int downFactor, int downPhase, const P* pDlyLine) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRInitAlloc(IppsFIRState_64f** pState,
        const P* pTaps, int tapsLen, const P* pDlyLine) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRMRInitAlloc(IppsFIRState_64f** pState,
        const P* pTaps, int tapsLen, int upFactor, int upPhase,
        int downFactor, int downPhase, const P* pDlyLine) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRInitAlloc(IppsFIRState_64fc** pState,
        const P* pTaps, int tapsLen, const P* pDlyLine) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRMRInitAlloc(IppsFIRState_64fc** pState,
        const P* pTaps, int tapsLen, int upFactor, int upPhase,
        int downFactor, int downPhase, const P* pDlyLine) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRInitAlloc64f(IppsFIRState64f_32f** pState,
        const Ipp64f* pTaps, int tapsLen, const P* pDlyLine) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRMRInitAlloc64f(IppsFIRState64f_32f** pState,
        const Ipp64f* pTaps, int tapsLen, int upFactor, int upPhase,
        int downFactor, int downPhase, const P* pDlyLine) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRInitAlloc64fc(IppsFIRState64fc_32fc** pState,
        const Ipp64fc* pTaps, int tapsLen, const P* pDlyLine) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRMRInitAlloc64fc(IppsFIRState64fc_32fc** pState,
        const Ipp64fc* pTaps, int tapsLen, int upFactor, int upPhase,
        int downFactor, int downPhase, const P* pDlyLine) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRInitAlloc64f(IppsFIRState64f_32s** pState,
        const Ipp64f* pTaps, int tapsLen, const P* pDlyLine) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRMRInitAlloc64f(IppsFIRState64f_32s** pState,
        const Ipp64f* pTaps, int tapsLen, int upFactor, int upPhase,
        int downFactor, int downPhase, const P* pDlyLine) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRInitAlloc64fc(IppsFIRState64fc_32sc** pState,
        const Ipp64fc* pTaps, int tapsLen, const P* pDlyLine) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRMRInitAlloc64fc(IppsFIRState64fc_32sc** pState,
        const Ipp64fc* pTaps, int tapsLen, int upFactor, int upPhase,
        int downFactor, int downPhase, const P* pDlyLine) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRInitAlloc64f(IppsFIRState64f_16s** pState,
        const Ipp64f* pTaps, int tapsLen, const P* pDlyLine) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRMRInitAlloc64f(IppsFIRState64f_16s** pState,
        const Ipp64f* pTaps, int tapsLen, int upFactor, int upPhase,
        int downFactor, int downPhase, const P* pDlyLine) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRInitAlloc64fc(IppsFIRState64fc_16sc** pState,
        const Ipp64fc* pTaps, int tapsLen, const P* pDlyLine) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRMRInitAlloc64fc(IppsFIRState64fc_16sc** pState,
        const Ipp64fc* pTaps, int tapsLen, int upFactor, int upPhase,
        int downFactor, int downPhase, const P* pDlyLine) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRInit32s( IppsFIRState32s_16s** pState,
      const Ipp32s *pTaps, int tapsLen, int tapsFactor, const P *pDlyLine,
                                                             Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRMRInit32s( IppsFIRState32s_16s** pState,
   const Ipp32s *pTaps, int tapsLen, int tapsFactor, int upFactor, int upPhase,
         int downFactor, int downPhase, const P *pDlyLine, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRInit32sc( IppsFIRState32sc_16sc** pState,
                             const Ipp32sc *pTaps, int tapsLen, int tapsFactor,
                                       const P *pDlyLine, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRMRInit32sc( IppsFIRState32sc_16sc** pState,
  const Ipp32sc *pTaps, int tapsLen, int tapsFactor, int upFactor, int upPhase,
        int downFactor, int downPhase, const P *pDlyLine, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P1, class P2>
inline IppStatus ippsFIRInit32s( IppsFIRState32s_16s** pState,
      const P2 *pTaps, int tapsLen, const P1 *pDlyLine, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P1, class P2>
inline IppStatus ippsFIRMRInit32s( IppsFIRState32s_16s** pState,
                   const P2 *pTaps, int tapsLen, int upFactor, int upPhase,
         int downFactor, int downPhase, const P1 *pDlyLine, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P1, class P2>
inline IppStatus ippsFIRInit32sc( IppsFIRState32sc_16sc** pState,
    const P2 *pTaps, int tapsLen, const P1 *pDlyLine, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P1, class P2>
inline IppStatus ippsFIRMRInit32sc( IppsFIRState32sc_16sc** pState,
                  const P2 *pTaps, int tapsLen, int upFactor, int upPhase,
        int downFactor, int downPhase, const P1 *pDlyLine, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRInit( IppsFIRState_32f** pState,
   const P *pTaps, int tapsLen, const P *pDlyLine, Ipp8u *pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRInit( IppsFIRState_32fc** pState,
 const P *pTaps, int tapsLen, const P *pDlyLine, Ipp8u *pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRMRInit( IppsFIRState_32f** pState,
                   const P* pTaps, int tapsLen, int upFactor, int upPhase,
      int downFactor, int downPhase, const P* pDlyLine, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRMRInit( IppsFIRState_32fc** pState,
                  const P *pTaps, int tapsLen, int upFactor, int upPhase,
     int downFactor, int downPhase, const P *pDlyLine, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRInit32f( IppsFIRState32f_16s** pState,
   const Ipp32f *pTaps, int tapsLen, const P *pDlyLine, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRInit32fc(IppsFIRState32fc_16sc** pState,
 const Ipp32fc *pTaps, int tapsLen, const P *pDlyLine, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRMRInit32f( IppsFIRState32f_16s** pState,
                   const Ipp32f* pTaps, int tapsLen, int upFactor, int upPhase,
      int downFactor, int downPhase, const P* pDlyLine, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRMRInit32fc( IppsFIRState32fc_16sc** pState,
                  const Ipp32fc *pTaps, int tapsLen, int upFactor, int upPhase,
     int downFactor, int downPhase, const P *pDlyLine, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRInit( IppsFIRState_64f** pState,
   const P *pTaps, int tapsLen, const P *pDlyLine, Ipp8u *pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRInit( IppsFIRState_64fc** pState,
 const P *pTaps, int tapsLen, const P *pDlyLine, Ipp8u *pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRMRInit( IppsFIRState_64f** pState,
                   const P* pTaps, int tapsLen, int upFactor, int upPhase,
      int downFactor, int downPhase, const P* pDlyLine, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRMRInit( IppsFIRState_64fc** pState,
                  const P *pTaps, int tapsLen, int upFactor, int upPhase,
     int downFactor, int downPhase, const P *pDlyLine, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRInit64f( IppsFIRState64f_16s** pState,
   const Ipp64f *pTaps, int tapsLen, const P *pDlyLine, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRInit64fc(IppsFIRState64fc_16sc** pState,
 const Ipp64fc *pTaps, int tapsLen, const P *pDlyLine, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRMRInit64f( IppsFIRState64f_16s** pState,
                   const Ipp64f* pTaps, int tapsLen, int upFactor, int upPhase,
      int downFactor, int downPhase, const P* pDlyLine, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRMRInit64fc( IppsFIRState64fc_16sc** pState,
                  const Ipp64fc *pTaps, int tapsLen, int upFactor, int upPhase,
     int downFactor, int downPhase, const P *pDlyLine, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRInit64f( IppsFIRState64f_32s** pState,
   const Ipp64f *pTaps, int tapsLen, const P *pDlyLine, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRInit64fc(IppsFIRState64fc_32sc** pState,
 const Ipp64fc *pTaps, int tapsLen, const P *pDlyLine, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRMRInit64f( IppsFIRState64f_32s** pState,
                   const Ipp64f* pTaps, int tapsLen, int upFactor, int upPhase,
      int downFactor, int downPhase, const P* pDlyLine, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRMRInit64fc( IppsFIRState64fc_32sc** pState,
                  const Ipp64fc *pTaps, int tapsLen, int upFactor, int upPhase,
     int downFactor, int downPhase, const P *pDlyLine, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRInit64f( IppsFIRState64f_32f** pState,
   const Ipp64f *pTaps, int tapsLen, const P *pDlyLine, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRInit64fc(IppsFIRState64fc_32fc** pState,
 const Ipp64fc *pTaps, int tapsLen, const P *pDlyLine, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRMRInit64f( IppsFIRState64f_32f** pState,
                   const Ipp64f* pTaps, int tapsLen, int upFactor, int upPhase,
      int downFactor, int downPhase, const P* pDlyLine, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRMRInit64fc( IppsFIRState64fc_32fc** pState,
                  const Ipp64fc *pTaps, int tapsLen, int upFactor, int upPhase,
     int downFactor, int downPhase, const P *pDlyLine, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRGetTaps(const IppsFIRState_32f* pState, P* pTaps) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRGetTaps(const IppsFIRState_32fc* pState, P* pTaps) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRGetTaps(const IppsFIRState_64f* pState, P* pTaps) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRGetTaps(const IppsFIRState_64fc* pState, P* pTaps) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRSetTaps( const P *pTaps,
                                                    IppsFIRState_32f* pState ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRSetTaps( const P *pTaps,
                                                   IppsFIRState_32fc* pState ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRSetTaps( const P *pTaps,
                                                    IppsFIRState_64f* pState ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRSetTaps( const P *pTaps,
                                                   IppsFIRState_64fc* pState ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRGetDlyLine(const IppsFIRState_32f* pState, P* pDlyLine) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRSetDlyLine(IppsFIRState_32f* pState, const P* pDlyLine) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRGetDlyLine(const IppsFIRState_32fc* pState, P* pDlyLine) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRSetDlyLine(IppsFIRState_32fc* pState, const P* pDlyLine) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRGetDlyLine32f(const IppsFIRState32f_16s* pState, P* pDlyLine) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRSetDlyLine32f(IppsFIRState32f_16s* pState, const P* pDlyLine) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRGetDlyLine32fc(const IppsFIRState32fc_16sc* pState, P* pDlyLine) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRSetDlyLine32fc(IppsFIRState32fc_16sc* pState, const P* pDlyLine) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRGetDlyLine(const IppsFIRState_64f* pState, P* pDlyLine) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRSetDlyLine(IppsFIRState_64f* pState, const P* pDlyLine) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRGetDlyLine(const IppsFIRState_64fc* pState, P* pDlyLine) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRSetDlyLine(IppsFIRState_64fc* pState, const P* pDlyLine) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRGetDlyLine64f(const IppsFIRState64f_32f* pState, P* pDlyLine) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRSetDlyLine64f(IppsFIRState64f_32f* pState, const P* pDlyLine) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRGetDlyLine64fc(const IppsFIRState64fc_32fc* pState, P* pDlyLine) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRSetDlyLine64fc(IppsFIRState64fc_32fc* pState, const P* pDlyLine) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRGetDlyLine64f(const IppsFIRState64f_32s* pState, P* pDlyLine) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRSetDlyLine64f(IppsFIRState64f_32s* pState, const P* pDlyLine) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRGetDlyLine64fc(const IppsFIRState64fc_32sc* pState, P* pDlyLine) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRSetDlyLine64fc(IppsFIRState64fc_32sc* pState, const P* pDlyLine) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRGetDlyLine64f(const IppsFIRState64f_16s* pState, P* pDlyLine) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRSetDlyLine64f(IppsFIRState64f_16s* pState, const P* pDlyLine) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRGetDlyLine64fc(const IppsFIRState64fc_16sc* pState, P* pDlyLine) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRSetDlyLine64fc(IppsFIRState64fc_16sc* pState, const P* pDlyLine) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIROne(P src, P* pDstVal, IppsFIRState_32f* pState) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIROne(P src, P* pDstVal, IppsFIRState_32fc* pState) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIROne32f_Sfs(P src, P* pDstVal,
        IppsFIRState32f_16s* pState, int scaleFactor ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIROne32fc_Sfs(P src, P* pDstVal,
        IppsFIRState32fc_16sc* pState,  int scaleFactor ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIROne(P src, P* pDstVal, IppsFIRState_64f* pState) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIROne(P src, P* pDstVal, IppsFIRState_64fc* pState) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIROne64f(P src, P* pDstVal, IppsFIRState64f_32f* pState) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIROne64fc(P src, P* pDstVal, IppsFIRState64fc_32fc* pState) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIROne64f_Sfs(P src, P* pDstVal,
        IppsFIRState64f_32s* pState, int scaleFactor ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIROne64fc_Sfs(P src, P* pDstVal,
        IppsFIRState64fc_32sc* pState,  int scaleFactor ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIROne64f_Sfs(P src, P* pDstVal,
        IppsFIRState64f_16s* pState,  int scaleFactor ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIROne64fc_Sfs(P src, P* pDstVal,
         IppsFIRState64fc_16sc* pState, int scaleFactor ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIR(const P* pSrc, P* pDst, int numIters,
        IppsFIRState_32f* pState) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIR(const P* pSrc, P* pDst, int numIters,
        IppsFIRState_32fc* pState) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIR32f_Sfs(const P* pSrc, P* pDst, int numIters,
        IppsFIRState32f_16s* pState, int scaleFactor ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIR32fc_Sfs(const P* pSrc, P* pDst, int numIters,
        IppsFIRState32fc_16sc* pState, int scaleFactor ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIR_I(P* pSrcDst, int numIters,
        IppsFIRState_32f* pState) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIR_I(P* pSrcDst, int numIters,
        IppsFIRState_32fc* pState) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIR32f_ISfs(P* pSrcDst, int numIters,
        IppsFIRState32f_16s* pState, int scaleFactor ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIR32fc_ISfs(P* pSrcDst, int numIters,
        IppsFIRState32fc_16sc* pState, int scaleFactor ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIR(const P* pSrc, P* pDst, int numIters,
        IppsFIRState_64f* pState) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIR(const P* pSrc, P* pDst, int numIters,
        IppsFIRState_64fc* pState) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIR_I(P* pSrcDst, int numIters,
        IppsFIRState_64f* pState) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIR_I(P* pSrcDst, int numIters,
        IppsFIRState_64fc* pState) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIR64f(const P* pSrc, P* pDst, int numIters,
        IppsFIRState64f_32f* pState) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIR64fc(const P* pSrc, P* pDst, int numIters,
        IppsFIRState64fc_32fc* pState) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIR64f_I(P* pSrcDst, int numIters,
        IppsFIRState64f_32f* pState) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIR64fc_I(P* pSrcDst, int numIters,
        IppsFIRState64fc_32fc* pState) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIR64f_Sfs(const P* pSrc, P* pDst, int numIters,
        IppsFIRState64f_32s* pState, int scaleFactor ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIR64fc_Sfs(const P* pSrc, P* pDst, int numIters,
        IppsFIRState64fc_32sc* pState, int scaleFactor ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIR64f_ISfs(P* pSrcDst, int numIters,
        IppsFIRState64f_32s* pState,  int scaleFactor ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIR64fc_ISfs(P* pSrcDst, int numIters,
        IppsFIRState64fc_32sc* pState,  int scaleFactor ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIR64f_Sfs(const P* pSrc, P* pDst, int numIters,
        IppsFIRState64f_16s* pState,  int scaleFactor ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIR64fc_Sfs(const P* pSrc, P* pDst, int numIters,
        IppsFIRState64fc_16sc* pState, int scaleFactor ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIR64f_ISfs(P* pSrcDst, int numIters,
        IppsFIRState64f_16s* pState, int scaleFactor ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIR64fc_ISfs(P* pSrcDst, int numIters,
        IppsFIRState64fc_16sc* pState, int scaleFactor ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRInitAlloc32s(IppsFIRState32s_16s** pState,
        const Ipp32s *pTaps, int tapsLen, int tapsFactor, const P *pDlyLine) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRMRInitAlloc32s(IppsFIRState32s_16s** pState,
        const Ipp32s *pTaps, int tapsLen, int tapsFactor, int upFactor,
        int upPhase, int downFactor, int downPhase, const P *pDlyLine) {
 return ippStsDataTypeErr;
}
template<class P1, class P2>
inline IppStatus ippsFIRInitAlloc32s(IppsFIRState32s_16s** pState,
        const P2 *pTaps, int tapsLen, const P1 *pDlyLine) {
 return ippStsDataTypeErr;
}
template<class P1, class P2>
inline IppStatus ippsFIRMRInitAlloc32s(IppsFIRState32s_16s **pState,
        const P2 *pTaps, int tapsLen, int upFactor, int upPhase,
        int downFactor, int downPhase, const P1 *pDlyLine) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRInitAlloc32sc(IppsFIRState32sc_16sc** pState,
        const Ipp32sc *pTaps, int tapsLen, int tapsFactor, const P *pDlyLine) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRMRInitAlloc32sc(IppsFIRState32sc_16sc** pState,
        const Ipp32sc *pTaps, int tapsLen, int tapsFactor, int upFactor,
        int upPhase, int downFactor, int downPhase, const P *pDlyLine) {
 return ippStsDataTypeErr;
}
template<class P1, class P2>
inline IppStatus ippsFIRInitAlloc32sc(IppsFIRState32sc_16sc** pState,
        const P2 *pTaps, int tapsLen, const P1 *pDlyLine) {
 return ippStsDataTypeErr;
}
template<class P1, class P2>
inline IppStatus ippsFIRMRInitAlloc32sc(IppsFIRState32sc_16sc** pState,
        const P2 *pTaps, int tapsLen, int upFactor, int upPhase,
        int downFactor, int downPhase, const P1 *pDlyLine) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRGetDlyLine32s(const IppsFIRState32s_16s* pState,
        P* pDlyLine) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRSetDlyLine32s(IppsFIRState32s_16s* pState,
        const P* pDlyLine) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRGetDlyLine32sc(const IppsFIRState32sc_16sc* pState,
        P* pDlyLine) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRSetDlyLine32sc(IppsFIRState32sc_16sc* pState,
        const P* pDlyLine) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIROne32s_Sfs(P src, P *pDstVal,
        IppsFIRState32s_16s *pState, int scaleFactor ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIROne32sc_Sfs(P src, P *pDstVal,
        IppsFIRState32sc_16sc *pState, int scaleFactor ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIR32s_Sfs(const P *pSrc, P *pDst,
        int numIters, IppsFIRState32s_16s *pState, int scaleFactor ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIR32sc_Sfs(const P *pSrc, P *pDst,
        int numIters, IppsFIRState32sc_16sc *pState, int scaleFactor ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIR32s_ISfs(P *pSrcDst, int numIters,
        IppsFIRState32s_16s *pState, int scaleFactor ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIR32sc_ISfs(P *pSrcDst, int numIters,
        IppsFIRState32sc_16sc *pState, int scaleFactor ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRInitAlloc( IppsFIRState_32s** pState,
                   const P *pTaps, int tapsLen, const P *pDlyLine ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRInit( IppsFIRState_32s** pState,
      const P *pTaps, int tapsLen, const P *pDlyLine, Ipp8u* pBuf ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRSetTaps( const P *pTaps,
                                                   IppsFIRState_32s* pState ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRGetTaps( const IppsFIRState_32s* pState,
                                                              P* pTaps ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIROne_Sfs( P src, P *pDstVal,
                                  IppsFIRState_32s *pState, int scaleFactor ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIR_Sfs( const P *pSrc, P *pDst,
                    int numIters, IppsFIRState_32s *pState, int scaleFactor ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIR_ISfs( P *pSrcDst, int numIters,
                                  IppsFIRState_32s *pState, int scaleFactor ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRLMSOne_Direct( P src, P refval,
       P* pDstVal, P* pTapsInv, int tapsLen, float mu, P* pDlyLine,
       int* pDlyIndex ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRLMSOne_Direct32f( P src, P refval,
       P* pDstVal, Ipp32f* pTapsInv, int tapsLen, float mu, P* pDlyLine,
       int* pDlyIndex ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRLMSOne_DirectQ15( P src, P refval,
       P* pDstVal, Ipp32s* pTapsInv, int tapsLen, int muQ15, P* pDlyLine,
       int* pDlyIndex ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRLMS( const P* pSrc, const P* pRef,
       P* pDst, int len, float mu, IppsFIRLMSState_32f* pState ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRLMS32f( const P* pSrc, const P* pRef,
       P* pDst, int len, float mu, IppsFIRLMSState32f_16s* pStatel ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRLMSInitAlloc( IppsFIRLMSState_32f** pState,
   const P* pTaps, int tapsLen, const P* pDlyLine, int dlyLineIndex ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRLMSInitAlloc32f( IppsFIRLMSState32f_16s** pState,
   const Ipp32f* pTaps, int tapsLen, const P* pDlyLine, int dlyLineIndex ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRLMSGetTaps( const IppsFIRLMSState_32f* pState,
       P* pOutTaps ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRLMSGetDlyLine( const IppsFIRLMSState_32f* pState,
   P* pDlyLine, int* pDlyLineIndex ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRLMSGetDlyLine32f( const IppsFIRLMSState32f_16s* pState,
   P* pDlyLine, int* pDlyLineIndex ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRLMSSetDlyLine( IppsFIRLMSState_32f* pState,
   const P* pDlyLine, int dlyLineIndex ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRLMSSetDlyLine32f( IppsFIRLMSState32f_16s* pState,
   const P* pDlyLine, int dlyLineIndex ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRLMSMROneVal32s( P val, Ipp32s* pDstVal,
                                            IppsFIRLMSMRState32s_16s* pState ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRLMSMROneVal32sc( P val, Ipp32sc* pDstVal,
                                            IppsFIRLMSMRState32sc_16sc* pState ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRLMSMRInitAlloc32s( IppsFIRLMSMRState32s_16s** pState,
   const Ipp32s* pTaps, int tapsLen, const P* pDlyLine, int dlyLineIndex,
   int dlyStep, int updateDly, int mu ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRLMSMRInitAlloc32sc( IppsFIRLMSMRState32sc_16sc** pState,
   const Ipp32sc* pTaps, int tapsLen, const P* pDlyLine, int dlyLineIndex,
   int dlyStep, int updateDly, int mu ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRLMSMRSetDlyLine32s( IppsFIRLMSMRState32s_16s* pState,
                                        const P* pInDlyLine, int dlyLineIndex ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRLMSMRGetDlyLine32s( IppsFIRLMSMRState32s_16s* pState,
                                        P* pOutDlyLine, int* pOutDlyIndex ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRLMSMRGetDlyVal32s( IppsFIRLMSMRState32s_16s* pState,
                                        P* pOutVal, int index ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRLMSMRSetDlyLine32sc( IppsFIRLMSMRState32sc_16sc* pState,
                                        const P* pInDlyLine, int dlyLineIndex ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRLMSMRGetDlyLine32sc( IppsFIRLMSMRState32sc_16sc* pState,
                                        P* pOutDlyLine, int* pOutDlyLineIndex ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRLMSMRGetDlyVal32sc( IppsFIRLMSMRState32sc_16sc* pState,
                                        P* pOutVal, int index ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRLMSMRPutVal32s( P val,
                                            IppsFIRLMSMRState32s_16s* pState ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRLMSMRPutVal32sc( P val,
                                            IppsFIRLMSMRState32sc_16sc* pState ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIROne_Direct(P src, P* pDstVal, const P* pTaps, int tapsLen,
        P* pDlyLine, int* pDlyLineIndex) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIROne_Direct_I(P* pSrcDstVal, const P* pTaps, int tapsLen,
        P* pDlyLine, int* pDlyLineIndex) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIROne32f_Direct_Sfs(P src, P* pDstVal, const Ipp32f* pTaps, int tapsLen,
        P* pDlyLine, int* pDlyLineIndex, int scaleFactor ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIROne32fc_Direct_Sfs(P src, P* pDstVal, const Ipp32fc* pTaps, int tapsLen,
        P* pDlyLine, int* pDlyLineIndex, int scaleFactor ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIROne32f_Direct_ISfs(P* pSrcDstVal, const Ipp32f* pTaps, int tapsLen,
        P* pDlyLine, int* pDlyLineIndex, int scaleFactor ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIROne32fc_Direct_ISfs(P* pSrcDstVal, const Ipp32fc* pTaps, int tapsLen,
        P* pDlyLine, int* pDlyLineIndex, int scaleFactor ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIROne64f_Direct(P src, P* pDstVal, const Ipp64f* pTaps, int tapsLen,
        P* pDlyLine, int* pDlyLineIndex) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIROne64fc_Direct(P src, P* pDstVal, const Ipp64fc* pTaps, int tapsLen,
        P* pDlyLine, int* pDlyLineIndex) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIROne64f_Direct_I(P* pSrcDstVal, const Ipp64f* pTaps, int tapsLen,
        P* pDlyLine, int* pDlyLineIndex) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIROne64fc_Direct_I(P* pSrcDstVal, const Ipp64fc* pTaps, int tapsLen,
        P* pDlyLine, int* pDlyLineIndex) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIROne64f_Direct_Sfs(P src, P* pDstVal, const Ipp64f* pTaps, int tapsLen,
        P* pDlyLine, int* pDlyLineIndex, int scaleFactor ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIROne64fc_Direct_Sfs(P src, P* pDstVal, const Ipp64fc* pTaps, int tapsLen,
        P* pDlyLine, int* pDlyLineIndex, int scaleFactor ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIROne64f_Direct_ISfs(P* pSrcDstVal, const Ipp64f* pTaps, int tapsLen,
        P* pDlyLine, int* pDlyLineIndex, int scaleFactor ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIROne64fc_Direct_ISfs(P* pSrcDstVal, const Ipp64fc* pTaps, int tapsLen,
        P* pDlyLine, int* pDlyLineIndex, int scaleFactor ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIROne32s_Direct_Sfs(P src, P* pDstVal,
        const Ipp32s* pTaps, int tapsLen, int tapsFactor,
        P* pDlyLine, int* pDlyLineIndex, int scaleFactor ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIROne32sc_Direct_Sfs(P src, P* pDstVal,
        const Ipp32sc* pTaps, int tapsLen, int tapsFactor,
        P* pDlyLine, int* pDlyLineIndex, int scaleFactor ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIROne32s_Direct_ISfs(P* pSrcDstVal,
        const Ipp32s* pTaps, int tapsLen, int tapsFactor,
        P* pDlyLine, int* pDlyLineIndex, int scaleFactor ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIROne32sc_Direct_ISfs(P* pSrcDstVal,
        const Ipp32sc* pTaps, int tapsLen, int tapsFactor,
        P* pDlyLine, int* pDlyLineIndex, int scaleFactor ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIR_Direct(const P* pSrc, P* pDst, int numIters, const P* pTaps, int tapsLen,
        P* pDlyLine, int* pDlyLineIndex) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIR_Direct_I(P* pSrcDst, int numIters, const P* pTaps, int tapsLen,
        P* pDlyLine, int* pDlyLineIndex) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIR32f_Direct_Sfs(const P* pSrc, P* pDst, int numIters, const Ipp32f* pTaps, int tapsLen,
        P* pDlyLine, int* pDlyLineIndex, int scaleFactor ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIR32fc_Direct_Sfs(const P* pSrc, P* pDst, int numIters, const Ipp32fc* pTaps, int tapsLen,
        P* pDlyLine, int* pDlyLineIndex, int scaleFactor ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIR32f_Direct_ISfs(P* pSrcDst, int numIters, const Ipp32f* pTaps, int tapsLen,
        P* pDlyLine, int* pDlyLineIndex, int scaleFactor ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIR32fc_Direct_ISfs(P* pSrcDst, int numIters, const Ipp32fc* pTaps, int tapsLen,
        P* pDlyLine, int* pDlyLineIndex, int scaleFactor ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIR64f_Direct(const P* pSrc, P* pDst, int numIters, const Ipp64f* pTaps, int tapsLen,
        P* pDlyLine, int* pDlyLineIndex) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIR64fc_Direct(const P* pSrc, P* pDst, int numIters, const Ipp64fc* pTaps, int tapsLen,
        P* pDlyLine, int* pDlyLineIndex) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIR64f_Direct_I(P* pSrcDst, int numIters, const Ipp64f* pTaps, int tapsLen,
        P* pDlyLine, int* pDlyLineIndex) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIR64fc_Direct_I(P* pSrcDst, int numIters, const Ipp64fc* pTaps, int tapsLen,
        P* pDlyLine, int* pDlyLineIndex) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIR64f_Direct_Sfs(const P* pSrc, P* pDst, int numIters, const Ipp64f* pTaps, int tapsLen,
        P* pDlyLine, int* pDlyLineIndex, int scaleFactor ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIR64fc_Direct_Sfs(const P* pSrc, P* pDst, int numIters, const Ipp64fc* pTaps, int tapsLen,
        P* pDlyLine, int* pDlyLineIndex, int scaleFactor ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIR64f_Direct_ISfs(P* pSrcDst, int numIters, const Ipp64f* pTaps, int tapsLen,
        P* pDlyLine, int* pDlyLineIndex, int scaleFactor ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIR64fc_Direct_ISfs(P* pSrcDst, int numIters, const Ipp64fc* pTaps, int tapsLen,
        P* pDlyLine, int* pDlyLineIndex, int scaleFactor ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIR32s_Direct_Sfs(const P* pSrc, P* pDst, int numIters,
        const Ipp32s* pTaps, int tapsLen, int tapsFactor,
        P* pDlyLine, int* pDlyLineIndex, int scaleFactor ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIR32sc_Direct_Sfs(const P* pSrc, P* pDst, int numIters,
        const Ipp32sc* pTaps, int tapsLen, int tapsFactor,
        P* pDlyLine, int* pDlyLineIndex, int scaleFactor ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIR32s_Direct_ISfs(P* pSrcDst, int numIters,
        const Ipp32s* pTaps, int tapsLen, int tapsFactor,
        P* pDlyLine, int* pDlyLineIndex, int scaleFactor ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIR32sc_Direct_ISfs(P* pSrcDst, int numIters,
        const Ipp32sc* pTaps, int tapsLen, int tapsFactor,
        P* pDlyLine, int* pDlyLineIndex, int scaleFactor ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRMR_Direct(const P* pSrc, P* pDst, int numIters,
        const P* pTaps, int tapsLen, int upFactor,int upPhase, int downFactor, int downPhase,
        P* pDlyLine) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRMR_Direct_I(P* pSrcDst, int numIters,
        const P* pTaps, int tapsLen, int upFactor,int upPhase, int downFactor, int downPhase,
        P* pDlyLine) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRMR32f_Direct_Sfs(const P* pSrc, P* pDst, int numIters,
        const Ipp32f* pTaps, int tapsLen, int upFactor,int upPhase, int downFactor, int downPhase,
        P* pDlyLine, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRMR32fc_Direct_Sfs(const P* pSrc, P* pDst, int numIters,
        const Ipp32fc* pTaps, int tapsLen, int upFactor,int upPhase, int downFactor, int downPhase,
        P* pDlyLine, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRMR32f_Direct_ISfs(P* pSrcDst, int numIters,
        const Ipp32f* pTaps, int tapsLen, int upFactor,int upPhase, int downFactor, int downPhase,
        P* pDlyLine, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRMR32fc_Direct_ISfs(P* pSrcDst, int numIters,
        const Ipp32fc* pTaps, int tapsLen, int upFactor,int upPhase, int downFactor, int downPhase,
        P* pDlyLine, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRMR64f_Direct(const P* pSrc, P* pDst, int numIters,
        const Ipp64f* pTaps, int tapsLen, int upFactor,int upPhase, int downFactor, int downPhase,
        P* pDlyLine) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRMR64fc_Direct(const P* pSrc, P* pDst, int numIters,
        const Ipp64fc* pTaps, int tapsLen, int upFactor,int upPhase, int downFactor, int downPhase,
        P* pDlyLine) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRMR64f_Direct_I(P* pSrcDst, int numIters,
        const Ipp64f* pTaps, int tapsLen, int upFactor,int upPhase, int downFactor, int downPhase,
        P* pDlyLine) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRMR64fc_Direct_I(P* pSrcDst, int numIters,
        const Ipp64fc* pTaps, int tapsLen, int upFactor,int upPhase, int downFactor, int downPhase,
        P* pDlyLine) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRMR64f_Direct_Sfs(const P* pSrc, P* pDst, int numIters,
        const Ipp64f* pTaps, int tapsLen, int upFactor,int upPhase, int downFactor, int downPhase,
        P* pDlyLine, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRMR64fc_Direct_Sfs(const P* pSrc, P* pDst, int numIters,
        const Ipp64fc* pTaps, int tapsLen, int upFactor,int upPhase, int downFactor, int downPhase,
        P* pDlyLine, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRMR64f_Direct_ISfs(P* pSrcDst, int numIters,
        const Ipp64f* pTaps, int tapsLen, int upFactor,int upPhase, int downFactor, int downPhase,
        P* pDlyLine, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRMR64fc_Direct_ISfs(P* pSrcDst, int numIters,
        const Ipp64fc* pTaps, int tapsLen, int upFactor,int upPhase, int downFactor, int downPhase,
        P* pDlyLine, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRMR32s_Direct_Sfs(const P* pSrc, P* pDst, int numIters,
        const Ipp32s* pTaps, int tapsLen, int tapsFactor,
        int upFactor,int upPhase, int downFactor, int downPhase,
        P* pDlyLine, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRMR32sc_Direct_Sfs(const P* pSrc, P* pDst, int numIters,
        const Ipp32sc* pTaps, int tapsLen, int tapsFactor,
        int upFactor,int upPhase, int downFactor, int downPhase,
        P* pDlyLine, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRMR32s_Direct_ISfs(P* pSrcDst, int numIters,
        const Ipp32s* pTaps, int tapsLen, int tapsFactor,
        int upFactor,int upPhase, int downFactor, int downPhase,
        P* pDlyLine, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRMR32sc_Direct_ISfs(P* pSrcDst, int numIters,
        const Ipp32sc* pTaps, int tapsLen, int tapsFactor,
        int upFactor,int upPhase, int downFactor, int downPhase,
        P* pDlyLine, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIR_Direct_Sfs( const P* pSrc, P* pDst,
          int numIters, const P* pTapsQ15, int tapsLen, P* pDlyLine,
                                      int* pDlyLineIndex, int scaleFactor ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIR_Direct_ISfs( P* pSrcDst, int numIters,
                       const P* pTapsQ15, int tapsLen, P* pDlyLine,
                                      int* pDlyLineIndex, int scaleFactor ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIROne_Direct_Sfs( P src, P* pDstVal,
                       const P* pTapsQ15, int tapsLen, P* pDlyLine,
                                      int* pDlyLineIndex, int scaleFactor ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIROne_Direct_ISfs( P* pSrcDstVal,
                      const P* pTapsQ15, int tapsLen, P * pDlyLine,
                                      int* pDlyLineIndex, int scaleFactor ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRGenLowpass(P rfreq, P* taps, int tapsLen,
                                            IppWinType winType, IppBool doNormal) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRGenHighpass(P rfreq, P* taps, int tapsLen,
                                             IppWinType winType, IppBool doNormal) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRGenBandpass(P rLowFreq, P rHighFreq, P* taps,
                                     int tapsLen, IppWinType winType, IppBool doNormal) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFIRGenBandstop(P rLowFreq, P rHighFreq, P* taps,
                                     int tapsLen, IppWinType winType, IppBool doNormal) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsWinBartlett_I(P* pSrcDst, int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsWinBartlett(const P* pSrc, P* pDst, int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsWinHann_I(P* pSrcDst, int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsWinHann(const P* pSrc, P* pDst, int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsWinHamming_I(P* pSrcDst, int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsWinHamming(const P* pSrc, P* pDst, int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsWinBlackmanQ15_ISfs(P* pSrcDst, int len,
                                             int alphaQ15, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsWinBlackmanQ15_I(P* pSrcDst, int len, int alphaQ15) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsWinBlackman_I(P* pSrcDst, int len, float alpha) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsWinBlackmanQ15(const P* pSrc, P* pDst, int len, int alphaQ15) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsWinBlackman(const P* pSrc, P* pDst, int len, float alpha) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsWinBlackmanStd_I(P* pSrcDst, int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsWinBlackmanOpt_I(P* pSrcDst, int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsWinBlackmanStd(const P* pSrc, P* pDst, int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsWinBlackmanOpt(const P* pSrc, P* pDst, int len) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsWinBlackman_I(P*  pSrcDst, int len, double alpha) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsWinBlackman(const P*  pSrc, P*  pDst, int len, double alpha) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsWinKaiser(const P* pSrc, P* pDst, int len, float alpha) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsWinKaiser_I(P* pSrcDst, int len, float alpha) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsWinKaiserQ15(const P* pSrc, P* pDst, int len, int alphaQ15) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsWinKaiserQ15_I(P* pSrcDst, int len, int alphaQ15) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsDCTFwd_Sfs( const P* pSrc, P* pDst,
                     const IppsDCTFwdSpec_16s* pDCTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsDCTInv_Sfs( const P* pSrc, P* pDst,
                     const IppsDCTInvSpec_16s* pDCTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsDCTFwd( const P* pSrc, P* pDst,
                     const IppsDCTFwdSpec_32f* pDCTSpec, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsDCTInv( const P* pSrc, P* pDst,
                     const IppsDCTInvSpec_32f* pDCTSpec, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsDCTFwd( const P* pSrc, P* pDst,
                     const IppsDCTFwdSpec_64f* pDCTSpec, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsDCTInv( const P* pSrc, P* pDst,
                     const IppsDCTInvSpec_64f* pDCTSpec, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsWTHaarFwd( const P* pSrc, int len,
                        P* pDstLow, P* pDstHigh ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsWTHaarFwd_Sfs( const P* pSrc, int len,
                        P* pDstLow, P* pDstHigh, int scaleFactor) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsWTHaarInv( const P* pSrcLow, const P* pSrcHigh,
                                P* pDst, int len ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsWTHaarInv_Sfs( const P* pSrcLow, const P* pSrcHigh,
                                P* pDst, int len, int scaleFactor ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsWTFwdInitAlloc(IppsWTFwdState_32f** pState,
        const P* pTapsLow,  int lenLow,  int offsLow,
        const P* pTapsHigh, int lenHigh, int offsHigh) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsWTFwdSetDlyLine(IppsWTFwdState_32f* pState,
        const P* pDlyLow, const P* pDlyHigh) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsWTFwdGetDlyLine(IppsWTFwdState_32f* pState,
        P* pDlyLow, P* pDlyHigh) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsWTFwd(const P* pSrc,
        P* pDstLow, P* pDstHigh, int dstLen,
        IppsWTFwdState_32f* pState) {
 return ippStsDataTypeErr;
}
template<class P1, class P2>
inline IppStatus ippsWTFwd(const P1* pSrc,
        P2* pDstLow, P2* pDstHigh, int dstLen,
        IppsWTFwdState_8s32f* pState) {
 return ippStsDataTypeErr;
}
template<class P1, class P2>
inline IppStatus ippsWTFwd(const P1* pSrc,
        P2* pDstLow, P2* pDstHigh, int dstLen,
        IppsWTFwdState_8u32f* pState) {
 return ippStsDataTypeErr;
}
template<class P1, class P2>
inline IppStatus ippsWTFwd(const P1* pSrc,
        P2* pDstLow, P2* pDstHigh, int dstLen,
        IppsWTFwdState_16s32f* pState) {
 return ippStsDataTypeErr;
}
template<class P1, class P2>
inline IppStatus ippsWTFwd(
        const P1* pSrc, P2* pDstLow, P2* pDstHigh, int dstLen,
        IppsWTFwdState_16u32f* pState) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsWTInvInitAlloc(IppsWTInvState_32f** pState,
        const P* pTapsLow,  int lenLow,  int offsLow,
        const P* pTapsHigh, int lenHigh, int offsHigh) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsWTInvSetDlyLine(IppsWTInvState_32f* pState,
        const P* pDlyLow, const P* pDlyHigh) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsWTInvGetDlyLine(IppsWTInvState_32f* pState,
        P* pDlyLow, P* pDlyHigh) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsWTInv(
        const P* pSrcLow, const P* pSrcHigh, int srcLen, P* pDst,
        IppsWTInvState_32f* pState) {
 return ippStsDataTypeErr;
}
template<class P1, class P2>
inline IppStatus ippsWTInv(
        const P1* pSrcLow, const P1* pSrcHigh, int srcLen, P2* pDst,
        IppsWTInvState_32f8s* pState) {
 return ippStsDataTypeErr;
}
template<class P1, class P2>
inline IppStatus ippsWTInv(
        const P1* pSrcLow, const P1* pSrcHigh, int srcLen, P2* pDst,
        IppsWTInvState_32f8u* pState) {
 return ippStsDataTypeErr;
}
template<class P1, class P2>
inline IppStatus ippsWTInv(
        const P1* pSrcLow, const P1* pSrcHigh, int srcLen, P2* pDst,
        IppsWTInvState_32f16s* pState) {
 return ippStsDataTypeErr;
}
template<class P1, class P2>
inline IppStatus ippsWTInv(
        const P1* pSrcLow, const P1* pSrcHigh, int srcLen, P2* pDst,
        IppsWTInvState_32f16u* pState) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFFTFwd_CToC( const P* pSrc, P* pDst,
                     const IppsFFTSpec_C_32fc* pFFTSpec, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFFTInv_CToC( const P* pSrc, P* pDst,
                     const IppsFFTSpec_C_32fc* pFFTSpec, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFFTFwd_CToC( const P* pSrcRe, const P* pSrcIm,
                     P* pDstRe, P* pDstIm,
                     const IppsFFTSpec_C_32f* pFFTSpec, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFFTInv_CToC( const P* pSrcRe, const P* pSrcIm,
                     P* pDstRe, P* pDstIm,
                     const IppsFFTSpec_C_32f* pFFTSpec, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFFTFwd_CToC_I( P* pSrcDst,
                     const IppsFFTSpec_C_32fc* pFFTSpec, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFFTInv_CToC_I( P* pSrcDst,
                     const IppsFFTSpec_C_32fc* pFFTSpec, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFFTFwd_CToC_I( P* pSrcDstRe, P* pSrcDstIm,
                     const IppsFFTSpec_C_32f* pFFTSpec, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFFTInv_CToC_I( P* pSrcDstRe, P* pSrcDstIm,
                     const IppsFFTSpec_C_32f* pFFTSpec, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFFTFwd_CToC( const P* pSrc, P* pDst,
                     const IppsFFTSpec_C_64fc* pFFTSpec, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFFTInv_CToC( const P* pSrc, P* pDst,
                     const IppsFFTSpec_C_64fc* pFFTSpec, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFFTFwd_CToC( const P* pSrcRe, const P* pSrcIm,
                     P* pDstRe, P* pDstIm,
                     const IppsFFTSpec_C_64f* pFFTSpec, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFFTInv_CToC( const P* pSrcRe, const P* pSrcIm,
                     P* pDstRe, P* pDstIm,
                     const IppsFFTSpec_C_64f* pFFTSpec, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFFTFwd_CToC_I( P* pSrcDst,
                     const IppsFFTSpec_C_64fc* pFFTSpec, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFFTInv_CToC_I( P* pSrcDst,
                     const IppsFFTSpec_C_64fc* pFFTSpec, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFFTFwd_CToC_I( P* pSrcDstRe, P* pSrcDstIm,
                     const IppsFFTSpec_C_64f* pFFTSpec, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFFTInv_CToC_I( P* pSrcDstRe, P* pSrcDstIm,
                     const IppsFFTSpec_C_64f* pFFTSpec, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFFTFwd_CToC_Sfs( const P* pSrc, P* pDst,
                     const IppsFFTSpec_C_16sc* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFFTInv_CToC_Sfs( const P* pSrc, P* pDst,
                     const IppsFFTSpec_C_16sc* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFFTFwd_CToC_Sfs( const P* pSrcRe, const P* pSrcIm,
                     P* pDstRe, P* pDstIm,
                     const IppsFFTSpec_C_16s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFFTInv_CToC_Sfs( const P* pSrcRe, const P* pSrcIm,
                     P* pDstRe, P* pDstIm,
                     const IppsFFTSpec_C_16s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFFTFwd_CToC_ISfs( P* pSrcDst,
                     const IppsFFTSpec_C_16sc* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFFTInv_CToC_ISfs( P* pSrcDst,
                     const IppsFFTSpec_C_16sc* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFFTFwd_CToC_ISfs( P* pSrcDstRe, P* pSrcDstIm,
                     const IppsFFTSpec_C_16s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFFTInv_CToC_ISfs( P* pSrcDstRe, P* pSrcDstIm,
                     const IppsFFTSpec_C_16s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFFTFwd_CToC_Sfs( const P* pSrc, P* pDst,
                     const IppsFFTSpec_C_32sc* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFFTInv_CToC_Sfs( const P* pSrc, P* pDst,
                     const IppsFFTSpec_C_32sc* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFFTFwd_CToC_Sfs( const P* pSrcRe, const P* pSrcIm,
                     P* pDstRe, P* pDstIm,
                     const IppsFFTSpec_C_32s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFFTInv_CToC_Sfs( const P* pSrcRe, const P* pSrcIm,
                     P* pDstRe, P* pDstIm,
                     const IppsFFTSpec_C_32s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFFTFwd_CToC_ISfs( P* pSrcDst,
                     const IppsFFTSpec_C_32sc* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFFTInv_CToC_ISfs( P* pSrcDst,
                     const IppsFFTSpec_C_32sc* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFFTFwd_CToC_ISfs( P* pSrcDstRe, P* pSrcDstIm,
                     const IppsFFTSpec_C_32s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFFTInv_CToC_ISfs( P* pSrcDstRe, P* pSrcDstIm,
                     const IppsFFTSpec_C_32s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFFTFwd_RToPerm( const P* pSrc, P* pDst,
                     const IppsFFTSpec_R_32f* pFFTSpec, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFFTFwd_RToPack( const P* pSrc, P* pDst,
                     const IppsFFTSpec_R_32f* pFFTSpec, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFFTFwd_RToCCS( const P* pSrc, P* pDst,
                     const IppsFFTSpec_R_32f* pFFTSpec, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFFTInv_PermToR( const P* pSrc, P* pDst,
                     const IppsFFTSpec_R_32f* pFFTSpec, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFFTInv_PackToR( const P* pSrc, P* pDst,
                     const IppsFFTSpec_R_32f* pFFTSpec, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFFTInv_CCSToR( const P* pSrc, P* pDst,
                     const IppsFFTSpec_R_32f* pFFTSpec, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFFTFwd_RToPerm_I( P* pSrcDst,
                     const IppsFFTSpec_R_32f* pFFTSpec, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFFTFwd_RToPack_I( P* pSrcDst,
                     const IppsFFTSpec_R_32f* pFFTSpec, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFFTFwd_RToCCS_I( P* pSrcDst,
                     const IppsFFTSpec_R_32f* pFFTSpec, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFFTInv_PermToR_I( P* pSrcDst,
                     const IppsFFTSpec_R_32f* pFFTSpec, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFFTInv_PackToR_I( P* pSrcDst,
                     const IppsFFTSpec_R_32f* pFFTSpec, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFFTInv_CCSToR_I( P* pSrcDst,
                     const IppsFFTSpec_R_32f* pFFTSpec, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFFTFwd_RToPerm( const P* pSrc, P* pDst,
                     const IppsFFTSpec_R_64f* pFFTSpec, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFFTFwd_RToPack( const P* pSrc, P* pDst,
                     const IppsFFTSpec_R_64f* pFFTSpec, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFFTFwd_RToCCS( const P* pSrc, P* pDst,
                     const IppsFFTSpec_R_64f* pFFTSpec, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFFTInv_PermToR( const P* pSrc, P* pDst,
                     const IppsFFTSpec_R_64f* pFFTSpec, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFFTInv_PackToR( const P* pSrc, P* pDst,
                     const IppsFFTSpec_R_64f* pFFTSpec, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFFTInv_CCSToR( const P* pSrc, P* pDst,
                     const IppsFFTSpec_R_64f* pFFTSpec, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFFTFwd_RToPerm_I( P* pSrcDst,
                     const IppsFFTSpec_R_64f* pFFTSpec, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFFTFwd_RToPack_I( P* pSrcDst,
                     const IppsFFTSpec_R_64f* pFFTSpec, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFFTFwd_RToCCS_I( P* pSrcDst,
                     const IppsFFTSpec_R_64f* pFFTSpec, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFFTInv_PermToR_I( P* pSrcDst,
                     const IppsFFTSpec_R_64f* pFFTSpec, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFFTInv_PackToR_I( P* pSrcDst,
                     const IppsFFTSpec_R_64f* pFFTSpec, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFFTInv_CCSToR_I( P* pSrcDst,
                     const IppsFFTSpec_R_64f* pFFTSpec, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFFTFwd_RToPerm_Sfs( const P* pSrc, P* pDst,
                     const IppsFFTSpec_R_16s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFFTFwd_RToPack_Sfs( const P* pSrc, P* pDst,
                     const IppsFFTSpec_R_16s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFFTFwd_RToCCS_Sfs( const P* pSrc, P* pDst,
                     const IppsFFTSpec_R_16s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFFTInv_PermToR_Sfs( const P* pSrc, P* pDst,
                     const IppsFFTSpec_R_16s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFFTInv_PackToR_Sfs( const P* pSrc, P* pDst,
                     const IppsFFTSpec_R_16s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFFTInv_CCSToR_Sfs( const P* pSrc, P* pDst,
                     const IppsFFTSpec_R_16s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFFTFwd_RToPerm_ISfs( P* pSrcDst,
                     const IppsFFTSpec_R_16s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFFTFwd_RToPack_ISfs( P* pSrcDst,
                     const IppsFFTSpec_R_16s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFFTFwd_RToCCS_ISfs( P* pSrcDst,
                     const IppsFFTSpec_R_16s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFFTInv_PermToR_ISfs( P* pSrcDst,
                     const IppsFFTSpec_R_16s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFFTInv_PackToR_ISfs( P* pSrcDst,
                     const IppsFFTSpec_R_16s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFFTInv_CCSToR_ISfs( P* pSrcDst,
                     const IppsFFTSpec_R_16s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFFTFwd_RToPerm_Sfs( const P* pSrc, P* pDst,
                     const IppsFFTSpec_R_32s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFFTFwd_RToPack_Sfs( const P* pSrc, P* pDst,
                     const IppsFFTSpec_R_32s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFFTFwd_RToCCS_Sfs( const P* pSrc, P* pDst,
                     const IppsFFTSpec_R_32s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFFTInv_PermToR_Sfs( const P* pSrc, P* pDst,
                     const IppsFFTSpec_R_32s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFFTInv_PackToR_Sfs( const P* pSrc, P* pDst,
                     const IppsFFTSpec_R_32s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFFTInv_CCSToR_Sfs( const P* pSrc, P* pDst,
                     const IppsFFTSpec_R_32s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFFTFwd_RToPerm_ISfs( P* pSrcDst,
                     const IppsFFTSpec_R_32s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFFTFwd_RToPack_ISfs( P* pSrcDst,
                     const IppsFFTSpec_R_32s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFFTFwd_RToCCS_ISfs( P* pSrcDst,
                     const IppsFFTSpec_R_32s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFFTInv_PermToR_ISfs( P* pSrcDst,
                     const IppsFFTSpec_R_32s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFFTInv_PackToR_ISfs( P* pSrcDst,
                     const IppsFFTSpec_R_32s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsFFTInv_CCSToR_ISfs( P* pSrcDst,
                     const IppsFFTSpec_R_32s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P1, class P2>
inline IppStatus ippsFFTFwd_RToCCS_Sfs( const P1* pSrc, P2* pDst,
                     const IppsFFTSpec_R_16s32s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P1, class P2>
inline IppStatus ippsFFTInv_CCSToR_Sfs( const P1* pSrc, P2* pDst,
                     const IppsFFTSpec_R_16s32s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsDFTFwd_CToC_Sfs( const P* pSrc, P* pDst,
                     const IppsDFTSpec_C_16sc* pDFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsDFTInv_CToC_Sfs( const P* pSrc, P* pDst,
                     const IppsDFTSpec_C_16sc* pDFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsDFTFwd_CToC_Sfs( const P* pSrcRe, const P* pSrcIm,
                     P* pDstRe, P* pDstIm,
                     const IppsDFTSpec_C_16s* pDFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsDFTInv_CToC_Sfs( const P* pSrcRe, const P* pSrcIm,
                     P* pDstRe, P* pDstIm,
                     const IppsDFTSpec_C_16s* pDFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsDFTFwd_CToC( const P* pSrc, P* pDst,
                     const IppsDFTSpec_C_32fc* pDFTSpec, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsDFTInv_CToC( const P* pSrc, P* pDst,
                     const IppsDFTSpec_C_32fc* pDFTSpec, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsDFTFwd_CToC( const P* pSrcRe, const P* pSrcIm,
                     P* pDstRe, P* pDstIm,
                     const IppsDFTSpec_C_32f* pDFTSpec, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsDFTInv_CToC( const P* pSrcRe, const P* pSrcIm,
                     P* pDstRe, P* pDstIm,
                     const IppsDFTSpec_C_32f* pDFTSpec, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsDFTFwd_CToC( const P* pSrc, P* pDst,
                     const IppsDFTSpec_C_64fc* pDFTSpec, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsDFTInv_CToC( const P* pSrc, P* pDst,
                     const IppsDFTSpec_C_64fc* pDFTSpec, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsDFTFwd_CToC( const P* pSrcRe, const P* pSrcIm,
                     P* pDstRe, P* pDstIm,
                     const IppsDFTSpec_C_64f* pDFTSpec, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsDFTInv_CToC( const P* pSrcRe, const P* pSrcIm,
                     P* pDstRe, P* pDstIm,
                     const IppsDFTSpec_C_64f* pDFTSpec, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsDFTOutOrdFwd_CToC( const P* pSrc, P* pDst,
                     const IppsDFTOutOrdSpec_C_32fc* pDFTSpec, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsDFTOutOrdInv_CToC( const P* pSrc, P* pDst,
                     const IppsDFTOutOrdSpec_C_32fc* pDFTSpec, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsDFTOutOrdFwd_CToC( const P* pSrc, P* pDst,
                     const IppsDFTOutOrdSpec_C_64fc* pDFTSpec, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsDFTOutOrdInv_CToC( const P* pSrc, P* pDst,
                     const IppsDFTOutOrdSpec_C_64fc* pDFTSpec, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsDFTFwd_RToPerm_Sfs( const P* pSrc, P* pDst,
                     const IppsDFTSpec_R_16s* pDFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsDFTFwd_RToPack_Sfs( const P* pSrc, P* pDst,
                     const IppsDFTSpec_R_16s* pDFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsDFTFwd_RToCCS_Sfs( const P* pSrc, P* pDst,
                     const IppsDFTSpec_R_16s* pDFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsDFTInv_PermToR_Sfs( const P* pSrc, P* pDst,
                     const IppsDFTSpec_R_16s* pDFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsDFTInv_PackToR_Sfs( const P* pSrc, P* pDst,
                     const IppsDFTSpec_R_16s* pDFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsDFTInv_CCSToR_Sfs( const P* pSrc, P* pDst,
                     const IppsDFTSpec_R_16s* pDFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsDFTFwd_RToPerm( const P* pSrc, P* pDst,
                     const IppsDFTSpec_R_32f* pDFTSpec, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsDFTFwd_RToPack( const P* pSrc, P* pDst,
                     const IppsDFTSpec_R_32f* pDFTSpec, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsDFTFwd_RToCCS( const P* pSrc, P* pDst,
                     const IppsDFTSpec_R_32f* pDFTSpec, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsDFTInv_PermToR( const P* pSrc, P* pDst,
                     const IppsDFTSpec_R_32f* pDFTSpec, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsDFTInv_PackToR( const P* pSrc, P* pDst,
                     const IppsDFTSpec_R_32f* pDFTSpec, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsDFTInv_CCSToR( const P* pSrc, P* pDst,
                     const IppsDFTSpec_R_32f* pDFTSpec, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsDFTFwd_RToPerm( const P* pSrc, P* pDst,
                     const IppsDFTSpec_R_64f* pDFTSpec, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsDFTFwd_RToPack( const P* pSrc, P* pDst,
                     const IppsDFTSpec_R_64f* pDFTSpec, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsDFTFwd_RToCCS( const P* pSrc, P* pDst,
                     const IppsDFTSpec_R_64f* pDFTSpec, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsDFTInv_PermToR( const P* pSrc, P* pDst,
                     const IppsDFTSpec_R_64f* pDFTSpec, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsDFTInv_PackToR( const P* pSrc, P* pDst,
                     const IppsDFTSpec_R_64f* pDFTSpec, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}
template<class P>
inline IppStatus ippsDFTInv_CCSToR( const P* pSrc, P* pDst,
                     const IppsDFTSpec_R_64f* pDFTSpec, Ipp8u* pBuffer ) {
 return ippStsDataTypeErr;
}

inline IppStatus ippsCopy( const Ipp8u* pSrc, Ipp8u* pDst, int len ) {
  return ippsCopy_8u(pSrc,pDst,len);
}
inline IppStatus ippsCopy( const Ipp16s* pSrc, Ipp16s* pDst, int len ) {
  return ippsCopy_16s(pSrc,pDst,len);
}
inline IppStatus ippsCopy( const Ipp16sc* pSrc, Ipp16sc* pDst, int len ) {
  return ippsCopy_16sc(pSrc,pDst,len);
}
inline IppStatus ippsCopy( const Ipp32f* pSrc, Ipp32f* pDst, int len ) {
  return ippsCopy_32f(pSrc,pDst,len);
}
inline IppStatus ippsCopy( const Ipp32fc* pSrc, Ipp32fc* pDst, int len ) {
  return ippsCopy_32fc(pSrc,pDst,len);
}
inline IppStatus ippsCopy( const Ipp64f* pSrc, Ipp64f* pDst, int len ) {
  return ippsCopy_64f(pSrc,pDst,len);
}
inline IppStatus ippsCopy( const Ipp64fc* pSrc, Ipp64fc* pDst, int len ) {
  return ippsCopy_64fc(pSrc,pDst,len);
}
inline IppStatus ippsCopy( const Ipp32s* pSrc, Ipp32s* pDst, int len ) {
  return ippsCopy_32s(pSrc,pDst,len);
}
inline IppStatus ippsCopy( const Ipp32sc* pSrc, Ipp32sc* pDst, int len ) {
  return ippsCopy_32sc(pSrc,pDst,len);
}
inline IppStatus ippsCopy( const Ipp64s* pSrc, Ipp64s* pDst, int len ) {
  return ippsCopy_64s(pSrc,pDst,len);
}
inline IppStatus ippsCopy( const Ipp64sc* pSrc, Ipp64sc* pDst, int len ) {
  return ippsCopy_64sc(pSrc,pDst,len);
}
inline IppStatus ippsMove( const Ipp8u* pSrc, Ipp8u* pDst, int len ) {
  return ippsMove_8u(pSrc,pDst,len);
}
inline IppStatus ippsMove( const Ipp16s* pSrc, Ipp16s* pDst, int len ) {
  return ippsMove_16s(pSrc,pDst,len);
}
inline IppStatus ippsMove( const Ipp16sc* pSrc, Ipp16sc* pDst, int len ) {
  return ippsMove_16sc(pSrc,pDst,len);
}
inline IppStatus ippsMove( const Ipp32f* pSrc, Ipp32f* pDst, int len ) {
  return ippsMove_32f(pSrc,pDst,len);
}
inline IppStatus ippsMove( const Ipp32fc* pSrc, Ipp32fc* pDst, int len ) {
  return ippsMove_32fc(pSrc,pDst,len);
}
inline IppStatus ippsMove( const Ipp64f* pSrc, Ipp64f* pDst, int len ) {
  return ippsMove_64f(pSrc,pDst,len);
}
inline IppStatus ippsMove( const Ipp64fc* pSrc, Ipp64fc* pDst, int len ) {
  return ippsMove_64fc(pSrc,pDst,len);
}
inline IppStatus ippsMove( const Ipp32s* pSrc, Ipp32s* pDst, int len ) {
  return ippsMove_32s(pSrc,pDst,len);
}
inline IppStatus ippsMove( const Ipp32sc* pSrc, Ipp32sc* pDst, int len ) {
  return ippsMove_32sc(pSrc,pDst,len);
}
inline IppStatus ippsMove( const Ipp64s* pSrc, Ipp64s* pDst, int len ) {
  return ippsMove_64s(pSrc,pDst,len);
}
inline IppStatus ippsMove( const Ipp64sc* pSrc, Ipp64sc* pDst, int len ) {
  return ippsMove_64sc(pSrc,pDst,len);
}
inline IppStatus ippsZero( Ipp8u* pDst, int len ) {
  return ippsZero_8u(pDst,len);
}
inline IppStatus ippsZero( Ipp16s* pDst, int len ) {
  return ippsZero_16s(pDst,len);
}
inline IppStatus ippsZero( Ipp16sc* pDst, int len ) {
  return ippsZero_16sc(pDst,len);
}
inline IppStatus ippsZero( Ipp32f* pDst, int len ) {
  return ippsZero_32f(pDst,len);
}
inline IppStatus ippsZero( Ipp32fc* pDst, int len ) {
  return ippsZero_32fc(pDst,len);
}
inline IppStatus ippsZero( Ipp64f* pDst, int len ) {
  return ippsZero_64f(pDst,len);
}
inline IppStatus ippsZero( Ipp64fc* pDst, int len ) {
  return ippsZero_64fc(pDst,len);
}
inline IppStatus ippsZero( Ipp32s* pDst, int len ) {
  return ippsZero_32s(pDst,len);
}
inline IppStatus ippsZero( Ipp32sc* pDst, int len ) {
  return ippsZero_32sc(pDst,len);
}
inline IppStatus ippsZero( Ipp64s* pDst, int len ) {
  return ippsZero_64s(pDst,len);
}
inline IppStatus ippsZero( Ipp64sc* pDst, int len ) {
  return ippsZero_64sc(pDst,len);
}
inline IppStatus ippsSet( Ipp8u val, Ipp8u* pDst, int len ) {
  return ippsSet_8u(val,pDst,len);
}
inline IppStatus ippsSet( Ipp16s val, Ipp16s* pDst, int len ) {
  return ippsSet_16s(val,pDst,len);
}
inline IppStatus ippsSet( Ipp16sc val, Ipp16sc* pDst, int len ) {
  return ippsSet_16sc(val,pDst,len);
}
inline IppStatus ippsSet( Ipp32s val, Ipp32s* pDst, int len ) {
  return ippsSet_32s(val,pDst,len);
}
inline IppStatus ippsSet( Ipp32sc val, Ipp32sc* pDst, int len ) {
  return ippsSet_32sc(val,pDst,len);
}
inline IppStatus ippsSet( Ipp32f val, Ipp32f* pDst, int len ) {
  return ippsSet_32f(val,pDst,len);
}
inline IppStatus ippsSet( Ipp32fc val, Ipp32fc* pDst, int len ) {
  return ippsSet_32fc(val,pDst,len);
}
inline IppStatus ippsSet( Ipp64s val, Ipp64s* pDst, int len ) {
  return ippsSet_64s(val,pDst,len);
}
inline IppStatus ippsSet( Ipp64sc val, Ipp64sc* pDst, int len ) {
  return ippsSet_64sc(val,pDst,len);
}
inline IppStatus ippsSet( Ipp64f val, Ipp64f* pDst, int len ) {
  return ippsSet_64f(val,pDst,len);
}
inline IppStatus ippsSet( Ipp64fc val, Ipp64fc* pDst, int len ) {
  return ippsSet_64fc(val,pDst,len);
}
inline IppStatus ippsRandUniform_Direct(Ipp16s* pDst, int len, Ipp16s low, Ipp16s high,
                                               unsigned int* pSeed) {
  return ippsRandUniform_Direct_16s(pDst,len,low,high,pSeed);
}
inline IppStatus ippsRandUniform_Direct(Ipp32f* pDst, int len, Ipp32f low, Ipp32f high,
                                               unsigned int* pSeed) {
  return ippsRandUniform_Direct_32f(pDst,len,low,high,pSeed);
}
inline IppStatus ippsRandUniform_Direct(Ipp64f* pDst, int len, Ipp64f low, Ipp64f high,
                                               unsigned int* pSeed) {
  return ippsRandUniform_Direct_64f(pDst,len,low,high,pSeed);
}
inline IppStatus ippsRandGauss_Direct(Ipp16s* pDst, int len, Ipp16s mean, Ipp16s stdev,
                                            unsigned int* pSeed) {
  return ippsRandGauss_Direct_16s(pDst,len,mean,stdev,pSeed);
}
inline IppStatus ippsRandGauss_Direct(Ipp32f* pDst, int len, Ipp32f mean, Ipp32f stdev,
                                            unsigned int* pSeed) {
  return ippsRandGauss_Direct_32f(pDst,len,mean,stdev,pSeed);
}
inline IppStatus ippsRandGauss_Direct(Ipp64f* pDst, int len, Ipp64f mean, Ipp64f stdev,
                                            unsigned int* pSeed) {
  return ippsRandGauss_Direct_64f(pDst,len,mean,stdev,pSeed);
}
inline IppStatus ippsRandUniformInitAlloc(IppsRandUniState_8u** pRandUniState,
                                   Ipp8u low, Ipp8u high, unsigned int seed) {
  return ippsRandUniformInitAlloc_8u(pRandUniState,low,high,seed);
}
inline IppStatus ippsRandUniformInitAlloc(IppsRandUniState_16s** pRandUniState,
                                   Ipp16s low, Ipp16s high, unsigned int seed) {
  return ippsRandUniformInitAlloc_16s(pRandUniState,low,high,seed);
}
inline IppStatus ippsRandUniformInitAlloc(IppsRandUniState_32f** pRandUniState,
                                   Ipp32f low, Ipp32f high, unsigned int seed) {
  return ippsRandUniformInitAlloc_32f(pRandUniState,low,high,seed);
}
inline IppStatus ippsRandUniform(Ipp8u* pDst,  int len, IppsRandUniState_8u* pRandUniState) {
  return ippsRandUniform_8u(pDst,len,pRandUniState);
}
inline IppStatus ippsRandUniform(Ipp16s* pDst, int len, IppsRandUniState_16s* pRandUniState) {
  return ippsRandUniform_16s(pDst,len,pRandUniState);
}
inline IppStatus ippsRandUniform(Ipp32f* pDst, int len, IppsRandUniState_32f* pRandUniState) {
  return ippsRandUniform_32f(pDst,len,pRandUniState);
}
inline IppStatus ippsRandGaussInitAlloc(IppsRandGaussState_8u** pRandGaussState,
                                   Ipp8u mean, Ipp8u stdDev, unsigned int seed) {
  return ippsRandGaussInitAlloc_8u(pRandGaussState,mean,stdDev,seed);
}
inline IppStatus ippsRandGaussInitAlloc(IppsRandGaussState_16s** pRandGaussState,
                                   Ipp16s mean, Ipp16s stdDev, unsigned int seed) {
  return ippsRandGaussInitAlloc_16s(pRandGaussState,mean,stdDev,seed);
}
inline IppStatus ippsRandGaussInitAlloc(IppsRandGaussState_32f** pRandGaussState,
                                   Ipp32f mean, Ipp32f stdDev, unsigned int seed) {
  return ippsRandGaussInitAlloc_32f(pRandGaussState,mean,stdDev,seed);
}
inline IppStatus ippsRandGauss(Ipp8u* pDst,  int len, IppsRandGaussState_8u*  pRandGaussState) {
  return ippsRandGauss_8u(pDst,len,pRandGaussState);
}
inline IppStatus ippsRandGauss(Ipp16s* pDst, int len, IppsRandGaussState_16s* pRandGaussState) {
  return ippsRandGauss_16s(pDst,len,pRandGaussState);
}
inline IppStatus ippsRandGauss(Ipp32f* pDst, int len, IppsRandGaussState_32f* pRandGaussState) {
  return ippsRandGauss_32f(pDst,len,pRandGaussState);
}
inline IppStatus ippsRandGaussInit(IppsRandGaussState_16s* pRandGaussState,
                                   Ipp16s mean, Ipp16s stdDev, unsigned int seed) {
  return ippsRandGaussInit_16s(pRandGaussState,mean,stdDev,seed);
}
inline IppStatus ippsRandUniformInit(IppsRandUniState_16s* pRandUniState,
                                   Ipp16s low, Ipp16s high, unsigned int seed) {
  return ippsRandUniformInit_16s(pRandUniState,low,high,seed);
}
inline IppStatus ippsVectorJaehne(Ipp8u*  pDst, int len, Ipp8u magn) {
  return ippsVectorJaehne_8u(pDst,len,magn);
}
inline IppStatus ippsVectorJaehne(Ipp8s*  pDst, int len, Ipp8s magn) {
  return ippsVectorJaehne_8s(pDst,len,magn);
}
inline IppStatus ippsVectorJaehne(Ipp16u* pDst, int len, Ipp16u magn) {
  return ippsVectorJaehne_16u(pDst,len,magn);
}
inline IppStatus ippsVectorJaehne(Ipp16s* pDst, int len, Ipp16s magn) {
  return ippsVectorJaehne_16s(pDst,len,magn);
}
inline IppStatus ippsVectorJaehne(Ipp32u* pDst, int len, Ipp32u magn) {
  return ippsVectorJaehne_32u(pDst,len,magn);
}
inline IppStatus ippsVectorJaehne(Ipp32s* pDst, int len, Ipp32s magn) {
  return ippsVectorJaehne_32s(pDst,len,magn);
}
inline IppStatus ippsVectorJaehne(Ipp32f* pDst, int len, Ipp32f magn) {
  return ippsVectorJaehne_32f(pDst,len,magn);
}
inline IppStatus ippsVectorJaehne(Ipp64f* pDst, int len, Ipp64f magn) {
  return ippsVectorJaehne_64f(pDst,len,magn);
}
inline IppStatus ippsVectorRamp(Ipp8u*  pDst, int len, float offset, float slope) {
  return ippsVectorRamp_8u(pDst,len,offset,slope);
}
inline IppStatus ippsVectorRamp(Ipp8s*  pDst, int len, float offset, float slope) {
  return ippsVectorRamp_8s(pDst,len,offset,slope);
}
inline IppStatus ippsVectorRamp(Ipp16u* pDst, int len, float offset, float slope) {
  return ippsVectorRamp_16u(pDst,len,offset,slope);
}
inline IppStatus ippsVectorRamp(Ipp16s* pDst, int len, float offset, float slope) {
  return ippsVectorRamp_16s(pDst,len,offset,slope);
}
inline IppStatus ippsVectorRamp(Ipp32u* pDst, int len, float offset, float slope) {
  return ippsVectorRamp_32u(pDst,len,offset,slope);
}
inline IppStatus ippsVectorRamp(Ipp32s* pDst, int len, float offset, float slope) {
  return ippsVectorRamp_32s(pDst,len,offset,slope);
}
inline IppStatus ippsVectorRamp(Ipp32f* pDst, int len, float offset, float slope) {
  return ippsVectorRamp_32f(pDst,len,offset,slope);
}
inline IppStatus ippsVectorRamp(Ipp64f* pDst, int len, float offset, float slope) {
  return ippsVectorRamp_64f(pDst,len,offset,slope);
}
inline IppStatus ippsReal(const Ipp64fc* pSrc, Ipp64f* pDstRe, int len) {
  return ippsReal_64fc(pSrc,pDstRe,len);
}
inline IppStatus ippsReal(const Ipp32fc* pSrc, Ipp32f* pDstRe, int len) {
  return ippsReal_32fc(pSrc,pDstRe,len);
}
inline IppStatus ippsReal(const Ipp16sc* pSrc, Ipp16s* pDstRe, int len) {
  return ippsReal_16sc(pSrc,pDstRe,len);
}
inline IppStatus ippsImag(const Ipp64fc* pSrc, Ipp64f* pDstIm, int len) {
  return ippsImag_64fc(pSrc,pDstIm,len);
}
inline IppStatus ippsImag(const Ipp32fc* pSrc, Ipp32f* pDstIm, int len) {
  return ippsImag_32fc(pSrc,pDstIm,len);
}
inline IppStatus ippsImag(const Ipp16sc* pSrc, Ipp16s* pDstIm, int len) {
  return ippsImag_16sc(pSrc,pDstIm,len);
}
inline IppStatus ippsCplxToReal( const Ipp64fc* pSrc, Ipp64f* pDstRe,
       Ipp64f* pDstIm, int len ) {
  return ippsCplxToReal_64fc(pSrc,pDstRe,pDstIm,len);
}
inline IppStatus ippsCplxToReal( const Ipp32fc* pSrc, Ipp32f* pDstRe,
       Ipp32f* pDstIm, int len ) {
  return ippsCplxToReal_32fc(pSrc,pDstRe,pDstIm,len);
}
inline IppStatus ippsCplxToReal( const Ipp16sc* pSrc, Ipp16s* pDstRe,
       Ipp16s* pDstIm, int len ) {
  return ippsCplxToReal_16sc(pSrc,pDstRe,pDstIm,len);
}
inline IppStatus ippsRealToCplx( const Ipp64f* pSrcRe,
       const Ipp64f* pSrcIm, Ipp64fc* pDst, int len ) {
  return ippsRealToCplx_64f(pSrcRe,pSrcIm,pDst,len);
}
inline IppStatus ippsRealToCplx( const Ipp32f* pSrcRe,
       const Ipp32f* pSrcIm, Ipp32fc* pDst, int len ) {
  return ippsRealToCplx_32f(pSrcRe,pSrcIm,pDst,len);
}
inline IppStatus ippsRealToCplx( const Ipp16s* pSrcRe,
       const Ipp16s* pSrcIm, Ipp16sc* pDst, int len ) {
  return ippsRealToCplx_16s(pSrcRe,pSrcIm,pDst,len);
}
inline IppStatus ippsConj_I( Ipp64fc* pSrcDst, int len ) {
  return ippsConj_64fc_I(pSrcDst,len);
}
inline IppStatus ippsConj_I( Ipp32fc* pSrcDst, int len ) {
  return ippsConj_32fc_I(pSrcDst,len);
}
inline IppStatus ippsConj_I( Ipp16sc* pSrcDst, int len ) {
  return ippsConj_16sc_I(pSrcDst,len);
}
inline IppStatus ippsConj( const Ipp64fc* pSrc, Ipp64fc* pDst, int len ) {
  return ippsConj_64fc(pSrc,pDst,len);
}
inline IppStatus ippsConj( const Ipp32fc* pSrc, Ipp32fc* pDst, int len ) {
  return ippsConj_32fc(pSrc,pDst,len);
}
inline IppStatus ippsConj( const Ipp16sc* pSrc, Ipp16sc* pDst, int len ) {
  return ippsConj_16sc(pSrc,pDst,len);
}
inline IppStatus ippsConjFlip( const Ipp64fc* pSrc, Ipp64fc* pDst, int len ) {
  return ippsConjFlip_64fc(pSrc,pDst,len);
}
inline IppStatus ippsConjFlip( const Ipp32fc* pSrc, Ipp32fc* pDst, int len ) {
  return ippsConjFlip_32fc(pSrc,pDst,len);
}
inline IppStatus ippsConjFlip( const Ipp16sc* pSrc, Ipp16sc* pDst, int len ) {
  return ippsConjFlip_16sc(pSrc,pDst,len);
}
inline IppStatus ippsConjCcs_I( Ipp64fc* pSrcDst, int lenDst ) {
  return ippsConjCcs_64fc_I(pSrcDst,lenDst);
}
inline IppStatus ippsConjCcs_I( Ipp32fc* pSrcDst, int lenDst ) {
  return ippsConjCcs_32fc_I(pSrcDst,lenDst);
}
inline IppStatus ippsConjCcs_I( Ipp16sc* pSrcDst, int lenDst ) {
  return ippsConjCcs_16sc_I(pSrcDst,lenDst);
}
inline IppStatus ippsConjCcs( const Ipp64f* pSrc, Ipp64fc* pDst, int lenDst ) {
  return ippsConjCcs_64fc(pSrc,pDst,lenDst);
}
inline IppStatus ippsConjCcs( const Ipp32f* pSrc, Ipp32fc* pDst, int lenDst ) {
  return ippsConjCcs_32fc(pSrc,pDst,lenDst);
}
inline IppStatus ippsConjCcs( const Ipp16s* pSrc, Ipp16sc* pDst, int lenDst ) {
  return ippsConjCcs_16sc(pSrc,pDst,lenDst);
}
inline IppStatus ippsConjPack_I( Ipp64fc* pSrcDst, int lenDst ) {
  return ippsConjPack_64fc_I(pSrcDst,lenDst);
}
inline IppStatus ippsConjPack_I( Ipp32fc* pSrcDst, int lenDst ) {
  return ippsConjPack_32fc_I(pSrcDst,lenDst);
}
inline IppStatus ippsConjPack_I( Ipp16sc* pSrcDst, int lenDst ) {
  return ippsConjPack_16sc_I(pSrcDst,lenDst);
}
inline IppStatus ippsConjPack( const Ipp64f* pSrc, Ipp64fc* pDst, int lenDst ) {
  return ippsConjPack_64fc(pSrc,pDst,lenDst);
}
inline IppStatus ippsConjPack( const Ipp32f* pSrc, Ipp32fc* pDst, int lenDst ) {
  return ippsConjPack_32fc(pSrc,pDst,lenDst);
}
inline IppStatus ippsConjPack( const Ipp16s* pSrc, Ipp16sc* pDst, int lenDst ) {
  return ippsConjPack_16sc(pSrc,pDst,lenDst);
}
inline IppStatus ippsConjPerm_I( Ipp64fc* pSrcDst, int lenDst ) {
  return ippsConjPerm_64fc_I(pSrcDst,lenDst);
}
inline IppStatus ippsConjPerm_I( Ipp32fc* pSrcDst, int lenDst ) {
  return ippsConjPerm_32fc_I(pSrcDst,lenDst);
}
inline IppStatus ippsConjPerm_I( Ipp16sc* pSrcDst, int lenDst ) {
  return ippsConjPerm_16sc_I(pSrcDst,lenDst);
}
inline IppStatus ippsConjPerm( const Ipp64f* pSrc, Ipp64fc* pDst, int lenDst ) {
  return ippsConjPerm_64fc(pSrc,pDst,lenDst);
}
inline IppStatus ippsConjPerm( const Ipp32f* pSrc, Ipp32fc* pDst, int lenDst ) {
  return ippsConjPerm_32fc(pSrc,pDst,lenDst);
}
inline IppStatus ippsConjPerm( const Ipp16s* pSrc, Ipp16sc* pDst, int lenDst ) {
  return ippsConjPerm_16sc(pSrc,pDst,lenDst);
}
inline IppStatus ippsConvert(const Ipp8s* pSrc,Ipp16s* pDst,int len) {
  return ippsConvert_8s16s(pSrc,pDst,len);
}
inline IppStatus ippsConvert(const Ipp16s* pSrc, Ipp32s* pDst, int len) {
  return ippsConvert_16s32s(pSrc,pDst,len);
}
inline IppStatus ippsConvert(const Ipp32s* pSrc, Ipp16s* pDst, int len) {
  return ippsConvert_32s16s(pSrc,pDst,len);
}
inline IppStatus ippsConvert(const Ipp8s* pSrc,Ipp32f* pDst,int len) {
  return ippsConvert_8s32f(pSrc,pDst,len);
}
inline IppStatus ippsConvert(const Ipp8u* pSrc,Ipp32f* pDst,int len) {
  return ippsConvert_8u32f(pSrc,pDst,len);
}
inline IppStatus ippsConvert(const Ipp16s* pSrc,Ipp32f* pDst,int len) {
  return ippsConvert_16s32f(pSrc,pDst,len);
}
inline IppStatus ippsConvert(const Ipp16u* pSrc,Ipp32f* pDst,int len) {
  return ippsConvert_16u32f(pSrc,pDst,len);
}
inline IppStatus ippsConvert(const Ipp32s* pSrc,Ipp64f* pDst,int len) {
  return ippsConvert_32s64f(pSrc,pDst,len);
}
inline IppStatus ippsConvert(const Ipp32s* pSrc,Ipp32f* pDst,int len) {
  return ippsConvert_32s32f(pSrc,pDst,len);
}
inline IppStatus ippsConvert_Sfs(const Ipp32f* pSrc, Ipp8s* pDst,
       int len, IppRoundMode rndmode, int scaleFactor) {
  return ippsConvert_32f8s_Sfs(pSrc,pDst,len,rndmode,scaleFactor);
}
inline IppStatus ippsConvert_Sfs(const Ipp32f* pSrc, Ipp8u* pDst,
       int len, IppRoundMode rndmode, int scaleFactor) {
  return ippsConvert_32f8u_Sfs(pSrc,pDst,len,rndmode,scaleFactor);
}
inline IppStatus ippsConvert_Sfs(const Ipp32f* pSrc, Ipp16s* pDst,
       int len, IppRoundMode rndmode, int scaleFactor) {
  return ippsConvert_32f16s_Sfs(pSrc,pDst,len,rndmode,scaleFactor);
}
inline IppStatus ippsConvert_Sfs(const Ipp32f* pSrc, Ipp16u* pDst,
       int len, IppRoundMode rndmode, int scaleFactor) {
  return ippsConvert_32f16u_Sfs(pSrc,pDst,len,rndmode,scaleFactor);
}
inline IppStatus ippsConvert_Sfs(const Ipp64f* pSrc, Ipp32s* pDst,
       int len, IppRoundMode rndmode, int scaleFactor) {
  return ippsConvert_64f32s_Sfs(pSrc,pDst,len,rndmode,scaleFactor);
}
inline IppStatus ippsConvert_Sfs(const Ipp32f* pSrc, Ipp32s* pDst,
       int len, IppRoundMode rndmode, int scaleFactor) {
  return ippsConvert_32f32s_Sfs(pSrc,pDst,len,rndmode,scaleFactor);
}
inline IppStatus ippsConvert( const Ipp32f* pSrc, Ipp64f* pDst, int len ) {
  return ippsConvert_32f64f(pSrc,pDst,len);
}
inline IppStatus ippsConvert( const Ipp64f* pSrc, Ipp32f* pDst, int len ) {
  return ippsConvert_64f32f(pSrc,pDst,len);
}
inline IppStatus ippsConvert_Sfs( const Ipp16s* pSrc, Ipp32f* pDst, int len, int scaleFactor ) {
  return ippsConvert_16s32f_Sfs(pSrc,pDst,len,scaleFactor);
}
inline IppStatus ippsConvert_Sfs( const Ipp16s* pSrc, Ipp64f* pDst, int len, int scaleFactor ) {
  return ippsConvert_16s64f_Sfs(pSrc,pDst,len,scaleFactor);
}
inline IppStatus ippsConvert_Sfs( const Ipp32s* pSrc, Ipp32f* pDst, int len, int scaleFactor ) {
  return ippsConvert_32s32f_Sfs(pSrc,pDst,len,scaleFactor);
}
inline IppStatus ippsConvert_Sfs( const Ipp32s* pSrc, Ipp64f* pDst, int len, int scaleFactor ) {
  return ippsConvert_32s64f_Sfs(pSrc,pDst,len,scaleFactor);
}
inline IppStatus ippsConvert_Sfs( const Ipp32s* pSrc, Ipp16s* pDst, int len,
                       int scaleFactor ) {
  return ippsConvert_32s16s_Sfs(pSrc,pDst,len,scaleFactor);
}
inline IppStatus ippsConvert(const Ipp16s* pSrc,Ipp16f* pDst,int len,IppRoundMode rndmode) {
  return ippsConvert_16s16f(pSrc,pDst,len,rndmode);
}
inline IppStatus ippsConvert_Sfs(const Ipp16f* pSrc,Ipp16s* pDst,int len,IppRoundMode rndmode,int scaleFactor) {
  return ippsConvert_16f16s_Sfs(pSrc,pDst,len,rndmode,scaleFactor);
}
inline IppStatus ippsConvert(const Ipp32f* pSrc,Ipp16f* pDst,int len,IppRoundMode rndmode) {
  return ippsConvert_32f16f(pSrc,pDst,len,rndmode);
}
inline IppStatus ippsConvert_Sfs(const Ipp64s* pSrc, Ipp32s* pDst,
       int len, IppRoundMode rndmode, int scaleFactor) {
  return ippsConvert_64s32s_Sfs(pSrc,pDst,len,rndmode,scaleFactor);
}
inline IppStatus ippsThreshold_I( Ipp32f* pSrcDst, int len,
       Ipp32f level, IppCmpOp relOp ) {
  return ippsThreshold_32f_I(pSrcDst,len,level,relOp);
}
inline IppStatus ippsThreshold_I( Ipp32fc* pSrcDst, int len,
       Ipp32f level, IppCmpOp relOp ) {
  return ippsThreshold_32fc_I(pSrcDst,len,level,relOp);
}
inline IppStatus ippsThreshold_I( Ipp64f* pSrcDst, int len,
       Ipp64f level, IppCmpOp relOp ) {
  return ippsThreshold_64f_I(pSrcDst,len,level,relOp);
}
inline IppStatus ippsThreshold_I( Ipp64fc* pSrcDst, int len,
       Ipp64f level, IppCmpOp relOp ) {
  return ippsThreshold_64fc_I(pSrcDst,len,level,relOp);
}
inline IppStatus ippsThreshold_I( Ipp16s* pSrcDst, int len,
       Ipp16s level, IppCmpOp relOp ) {
  return ippsThreshold_16s_I(pSrcDst,len,level,relOp);
}
inline IppStatus ippsThreshold_I( Ipp16sc* pSrcDst, int len,
       Ipp16s level,  IppCmpOp relOp ) {
  return ippsThreshold_16sc_I(pSrcDst,len,level,relOp);
}
inline IppStatus ippsThreshold( const Ipp32f* pSrc, Ipp32f* pDst,
       int len, Ipp32f level, IppCmpOp relOp ) {
  return ippsThreshold_32f(pSrc,pDst,len,level,relOp);
}
inline IppStatus ippsThreshold( const Ipp32fc* pSrc, Ipp32fc* pDst,
       int len, Ipp32f level, IppCmpOp relOp ) {
  return ippsThreshold_32fc(pSrc,pDst,len,level,relOp);
}
inline IppStatus ippsThreshold( const Ipp64f* pSrc, Ipp64f* pDst,
       int len, Ipp64f level, IppCmpOp relOp ) {
  return ippsThreshold_64f(pSrc,pDst,len,level,relOp);
}
inline IppStatus ippsThreshold( const Ipp64fc* pSrc, Ipp64fc* pDst,
       int len, Ipp64f level, IppCmpOp relOp ) {
  return ippsThreshold_64fc(pSrc,pDst,len,level,relOp);
}
inline IppStatus ippsThreshold( const Ipp16s* pSrc, Ipp16s* pDst,
       int len, Ipp16s level, IppCmpOp relOp ) {
  return ippsThreshold_16s(pSrc,pDst,len,level,relOp);
}
inline IppStatus ippsThreshold( const Ipp16sc* pSrc, Ipp16sc* pDst,
       int len, Ipp16s level, IppCmpOp relOp) {
  return ippsThreshold_16sc(pSrc,pDst,len,level,relOp);
}
inline IppStatus ippsThreshold_LT_I( Ipp32f* pSrcDst, int len,
       Ipp32f level ) {
  return ippsThreshold_LT_32f_I(pSrcDst,len,level);
}
inline IppStatus ippsThreshold_LT_I( Ipp32fc* pSrcDst, int len,
       Ipp32f level ) {
  return ippsThreshold_LT_32fc_I(pSrcDst,len,level);
}
inline IppStatus ippsThreshold_LT_I( Ipp64f* pSrcDst, int len,
       Ipp64f level ) {
  return ippsThreshold_LT_64f_I(pSrcDst,len,level);
}
inline IppStatus ippsThreshold_LT_I( Ipp64fc* pSrcDst, int len,
       Ipp64f level ) {
  return ippsThreshold_LT_64fc_I(pSrcDst,len,level);
}
inline IppStatus ippsThreshold_LT_I( Ipp16s* pSrcDst, int len,
       Ipp16s level ) {
  return ippsThreshold_LT_16s_I(pSrcDst,len,level);
}
inline IppStatus ippsThreshold_LT_I( Ipp16sc* pSrcDst, int len,
       Ipp16s level ) {
  return ippsThreshold_LT_16sc_I(pSrcDst,len,level);
}
inline IppStatus ippsThreshold_LT( const Ipp32f* pSrc, Ipp32f* pDst,
       int len, Ipp32f level ) {
  return ippsThreshold_LT_32f(pSrc,pDst,len,level);
}
inline IppStatus ippsThreshold_LT( const Ipp32fc* pSrc, Ipp32fc* pDst,
       int len, Ipp32f level ) {
  return ippsThreshold_LT_32fc(pSrc,pDst,len,level);
}
inline IppStatus ippsThreshold_LT( const Ipp64f* pSrc, Ipp64f* pDst,
       int len, Ipp64f level ) {
  return ippsThreshold_LT_64f(pSrc,pDst,len,level);
}
inline IppStatus ippsThreshold_LT( const Ipp64fc* pSrc, Ipp64fc* pDst,
       int len, Ipp64f level ) {
  return ippsThreshold_LT_64fc(pSrc,pDst,len,level);
}
inline IppStatus ippsThreshold_LT( const Ipp16s* pSrc, Ipp16s* pDst,
       int len, Ipp16s level ) {
  return ippsThreshold_LT_16s(pSrc,pDst,len,level);
}
inline IppStatus ippsThreshold_LT( const Ipp16sc* pSrc, Ipp16sc* pDst,
       int len, Ipp16s level ) {
  return ippsThreshold_LT_16sc(pSrc,pDst,len,level);
}
inline IppStatus ippsThreshold_LT_I(Ipp32s* pSrcDst,int len,Ipp32s level) {
  return ippsThreshold_LT_32s_I(pSrcDst,len,level);
}
inline IppStatus ippsThreshold_LT(const Ipp32s* pSrc,Ipp32s* pDst,int len,Ipp32s level) {
  return ippsThreshold_LT_32s(pSrc,pDst,len,level);
}
inline IppStatus ippsThreshold_GT_I( Ipp32f* pSrcDst, int len,
       Ipp32f level ) {
  return ippsThreshold_GT_32f_I(pSrcDst,len,level);
}
inline IppStatus ippsThreshold_GT_I( Ipp32fc* pSrcDst, int len,
       Ipp32f level ) {
  return ippsThreshold_GT_32fc_I(pSrcDst,len,level);
}
inline IppStatus ippsThreshold_GT_I( Ipp64f* pSrcDst, int len,
       Ipp64f level ) {
  return ippsThreshold_GT_64f_I(pSrcDst,len,level);
}
inline IppStatus ippsThreshold_GT_I( Ipp64fc* pSrcDst, int len,
       Ipp64f level ) {
  return ippsThreshold_GT_64fc_I(pSrcDst,len,level);
}
inline IppStatus ippsThreshold_GT_I( Ipp16s* pSrcDst, int len,
       Ipp16s level ) {
  return ippsThreshold_GT_16s_I(pSrcDst,len,level);
}
inline IppStatus ippsThreshold_GT_I( Ipp16sc* pSrcDst, int len,
       Ipp16s level ) {
  return ippsThreshold_GT_16sc_I(pSrcDst,len,level);
}
inline IppStatus ippsThreshold_GT( const Ipp32f* pSrc, Ipp32f* pDst,
       int len, Ipp32f level ) {
  return ippsThreshold_GT_32f(pSrc,pDst,len,level);
}
inline IppStatus ippsThreshold_GT( const Ipp32fc* pSrc, Ipp32fc* pDst,
       int len, Ipp32f level ) {
  return ippsThreshold_GT_32fc(pSrc,pDst,len,level);
}
inline IppStatus ippsThreshold_GT( const Ipp64f* pSrc, Ipp64f* pDst,
       int len, Ipp64f level ) {
  return ippsThreshold_GT_64f(pSrc,pDst,len,level);
}
inline IppStatus ippsThreshold_GT( const Ipp64fc* pSrc, Ipp64fc* pDst,
       int len, Ipp64f level ) {
  return ippsThreshold_GT_64fc(pSrc,pDst,len,level);
}
inline IppStatus ippsThreshold_GT( const Ipp16s* pSrc, Ipp16s* pDst,
       int len, Ipp16s level ) {
  return ippsThreshold_GT_16s(pSrc,pDst,len,level);
}
inline IppStatus ippsThreshold_GT( const Ipp16sc* pSrc, Ipp16sc* pDst,
       int len, Ipp16s level ) {
  return ippsThreshold_GT_16sc(pSrc,pDst,len,level);
}
inline IppStatus ippsThreshold_LTAbs(const Ipp32f* pSrc, Ipp32f *pDst,
       int len, Ipp32f level) {
  return ippsThreshold_LTAbs_32f(pSrc,pDst,len,level);
}
inline IppStatus ippsThreshold_LTAbs(const Ipp64f* pSrc, Ipp64f *pDst,
       int len, Ipp64f level) {
  return ippsThreshold_LTAbs_64f(pSrc,pDst,len,level);
}
inline IppStatus ippsThreshold_LTAbs(const Ipp16s* pSrc, Ipp16s *pDst,
       int len, Ipp16s level) {
  return ippsThreshold_LTAbs_16s(pSrc,pDst,len,level);
}
inline IppStatus ippsThreshold_LTAbs(const Ipp32s* pSrc, Ipp32s *pDst,
       int len, Ipp32s level) {
  return ippsThreshold_LTAbs_32s(pSrc,pDst,len,level);
}
inline IppStatus ippsThreshold_LTAbs_I(Ipp32f *pSrcDst,
       int len, Ipp32f level) {
  return ippsThreshold_LTAbs_32f_I(pSrcDst,len,level);
}
inline IppStatus ippsThreshold_LTAbs_I(Ipp64f *pSrcDst,
       int len, Ipp64f level) {
  return ippsThreshold_LTAbs_64f_I(pSrcDst,len,level);
}
inline IppStatus ippsThreshold_LTAbs_I(Ipp16s *pSrcDst,
       int len, Ipp16s level) {
  return ippsThreshold_LTAbs_16s_I(pSrcDst,len,level);
}
inline IppStatus ippsThreshold_LTAbs_I(Ipp32s *pSrcDst,
       int len, Ipp32s level) {
  return ippsThreshold_LTAbs_32s_I(pSrcDst,len,level);
}
inline IppStatus ippsThreshold_GTAbs(const Ipp32f* pSrc, Ipp32f *pDst,
       int len, Ipp32f level) {
  return ippsThreshold_GTAbs_32f(pSrc,pDst,len,level);
}
inline IppStatus ippsThreshold_GTAbs(const Ipp64f* pSrc, Ipp64f *pDst,
       int len, Ipp64f level) {
  return ippsThreshold_GTAbs_64f(pSrc,pDst,len,level);
}
inline IppStatus ippsThreshold_GTAbs(const Ipp16s* pSrc, Ipp16s *pDst,
       int len, Ipp16s level) {
  return ippsThreshold_GTAbs_16s(pSrc,pDst,len,level);
}
inline IppStatus ippsThreshold_GTAbs(const Ipp32s* pSrc, Ipp32s *pDst,
       int len, Ipp32s level) {
  return ippsThreshold_GTAbs_32s(pSrc,pDst,len,level);
}
inline IppStatus ippsThreshold_GTAbs_I(Ipp32f *pSrcDst,
       int len, Ipp32f level) {
  return ippsThreshold_GTAbs_32f_I(pSrcDst,len,level);
}
inline IppStatus ippsThreshold_GTAbs_I(Ipp64f *pSrcDst,
       int len, Ipp64f level) {
  return ippsThreshold_GTAbs_64f_I(pSrcDst,len,level);
}
inline IppStatus ippsThreshold_GTAbs_I(Ipp16s *pSrcDst,
       int len, Ipp16s level) {
  return ippsThreshold_GTAbs_16s_I(pSrcDst,len,level);
}
inline IppStatus ippsThreshold_GTAbs_I(Ipp32s *pSrcDst,
       int len, Ipp32s level) {
  return ippsThreshold_GTAbs_32s_I(pSrcDst,len,level);
}
inline IppStatus ippsThreshold_LTVal_I( Ipp32f* pSrcDst, int len,
       Ipp32f level, Ipp32f value ) {
  return ippsThreshold_LTVal_32f_I(pSrcDst,len,level,value);
}
inline IppStatus ippsThreshold_LTVal_I( Ipp32fc* pSrcDst, int len,
       Ipp32f level, Ipp32fc value ) {
  return ippsThreshold_LTVal_32fc_I(pSrcDst,len,level,value);
}
inline IppStatus ippsThreshold_LTVal_I( Ipp64f* pSrcDst, int len,
       Ipp64f level, Ipp64f value ) {
  return ippsThreshold_LTVal_64f_I(pSrcDst,len,level,value);
}
inline IppStatus ippsThreshold_LTVal_I( Ipp64fc* pSrcDst, int len,
       Ipp64f level, Ipp64fc value ) {
  return ippsThreshold_LTVal_64fc_I(pSrcDst,len,level,value);
}
inline IppStatus ippsThreshold_LTVal_I( Ipp16s* pSrcDst, int len,
       Ipp16s level, Ipp16s value ) {
  return ippsThreshold_LTVal_16s_I(pSrcDst,len,level,value);
}
inline IppStatus ippsThreshold_LTVal_I( Ipp16sc* pSrcDst, int len,
       Ipp16s level, Ipp16sc value ) {
  return ippsThreshold_LTVal_16sc_I(pSrcDst,len,level,value);
}
inline IppStatus ippsThreshold_LTVal( const Ipp32f* pSrc, Ipp32f* pDst,
       int len, Ipp32f level, Ipp32f value ) {
  return ippsThreshold_LTVal_32f(pSrc,pDst,len,level,value);
}
inline IppStatus ippsThreshold_LTVal( const Ipp32fc* pSrc, Ipp32fc* pDst,
       int len, Ipp32f level, Ipp32fc value ) {
  return ippsThreshold_LTVal_32fc(pSrc,pDst,len,level,value);
}
inline IppStatus ippsThreshold_LTVal( const Ipp64f* pSrc, Ipp64f* pDst,
       int len, Ipp64f level, Ipp64f value ) {
  return ippsThreshold_LTVal_64f(pSrc,pDst,len,level,value);
}
inline IppStatus ippsThreshold_LTVal( const Ipp64fc* pSrc, Ipp64fc* pDst,
       int len, Ipp64f level, Ipp64fc value ) {
  return ippsThreshold_LTVal_64fc(pSrc,pDst,len,level,value);
}
inline IppStatus ippsThreshold_LTVal( const Ipp16s* pSrc, Ipp16s* pDst,
       int len, Ipp16s level, Ipp16s value ) {
  return ippsThreshold_LTVal_16s(pSrc,pDst,len,level,value);
}
inline IppStatus ippsThreshold_LTVal( const Ipp16sc* pSrc, Ipp16sc* pDst,
       int len, Ipp16s level, Ipp16sc value ) {
  return ippsThreshold_LTVal_16sc(pSrc,pDst,len,level,value);
}
inline IppStatus ippsThreshold_GTVal_I( Ipp32f* pSrcDst, int len,
       Ipp32f level, Ipp32f value ) {
  return ippsThreshold_GTVal_32f_I(pSrcDst,len,level,value);
}
inline IppStatus ippsThreshold_GTVal_I( Ipp32fc* pSrcDst, int len,
       Ipp32f level, Ipp32fc value ) {
  return ippsThreshold_GTVal_32fc_I(pSrcDst,len,level,value);
}
inline IppStatus ippsThreshold_GTVal_I( Ipp64f* pSrcDst, int len,
       Ipp64f level, Ipp64f value ) {
  return ippsThreshold_GTVal_64f_I(pSrcDst,len,level,value);
}
inline IppStatus ippsThreshold_GTVal_I( Ipp64fc* pSrcDst, int len,
       Ipp64f level, Ipp64fc value ) {
  return ippsThreshold_GTVal_64fc_I(pSrcDst,len,level,value);
}
inline IppStatus ippsThreshold_GTVal_I( Ipp16s* pSrcDst, int len,
       Ipp16s level, Ipp16s value ) {
  return ippsThreshold_GTVal_16s_I(pSrcDst,len,level,value);
}
inline IppStatus ippsThreshold_GTVal_I( Ipp16sc* pSrcDst, int len,
       Ipp16s level, Ipp16sc value ) {
  return ippsThreshold_GTVal_16sc_I(pSrcDst,len,level,value);
}
inline IppStatus ippsThreshold_GTVal( const Ipp32f* pSrc, Ipp32f* pDst,
       int len, Ipp32f level, Ipp32f value ) {
  return ippsThreshold_GTVal_32f(pSrc,pDst,len,level,value);
}
inline IppStatus ippsThreshold_GTVal( const Ipp32fc* pSrc, Ipp32fc* pDst,
       int len, Ipp32f level, Ipp32fc value ) {
  return ippsThreshold_GTVal_32fc(pSrc,pDst,len,level,value);
}
inline IppStatus ippsThreshold_GTVal( const Ipp64f* pSrc, Ipp64f* pDst,
       int len, Ipp64f level, Ipp64f value ) {
  return ippsThreshold_GTVal_64f(pSrc,pDst,len,level,value);
}
inline IppStatus ippsThreshold_GTVal( const Ipp64fc* pSrc, Ipp64fc* pDst,
       int len, Ipp64f level, Ipp64fc value ) {
  return ippsThreshold_GTVal_64fc(pSrc,pDst,len,level,value);
}
inline IppStatus ippsThreshold_GTVal( const Ipp16s* pSrc, Ipp16s* pDst,
       int len, Ipp16s level, Ipp16s value ) {
  return ippsThreshold_GTVal_16s(pSrc,pDst,len,level,value);
}
inline IppStatus ippsThreshold_GTVal( const Ipp16sc* pSrc, Ipp16sc* pDst,
       int len, Ipp16s level, Ipp16sc value ) {
  return ippsThreshold_GTVal_16sc(pSrc,pDst,len,level,value);
}
inline IppStatus ippsThreshold_LTInv_I(Ipp32f* pSrcDst,int len,Ipp32f level) {
  return ippsThreshold_LTInv_32f_I(pSrcDst,len,level);
}
inline IppStatus ippsThreshold_LTInv_I(Ipp32fc* pSrcDst,int len,Ipp32f level) {
  return ippsThreshold_LTInv_32fc_I(pSrcDst,len,level);
}
inline IppStatus ippsThreshold_LTInv_I(Ipp64f* pSrcDst,int len,Ipp64f level) {
  return ippsThreshold_LTInv_64f_I(pSrcDst,len,level);
}
inline IppStatus ippsThreshold_LTInv_I(Ipp64fc* pSrcDst,int len,Ipp64f level) {
  return ippsThreshold_LTInv_64fc_I(pSrcDst,len,level);
}
inline IppStatus ippsThreshold_LTInv(const Ipp32f* pSrc,Ipp32f* pDst,int len,Ipp32f level) {
  return ippsThreshold_LTInv_32f(pSrc,pDst,len,level);
}
inline IppStatus ippsThreshold_LTInv(const Ipp32fc* pSrc,Ipp32fc* pDst,int len,Ipp32f level) {
  return ippsThreshold_LTInv_32fc(pSrc,pDst,len,level);
}
inline IppStatus ippsThreshold_LTInv(const Ipp64f* pSrc,Ipp64f* pDst,int len,Ipp64f level) {
  return ippsThreshold_LTInv_64f(pSrc,pDst,len,level);
}
inline IppStatus ippsThreshold_LTInv(const Ipp64fc* pSrc,Ipp64fc* pDst,int len,Ipp64f level) {
  return ippsThreshold_LTInv_64fc(pSrc,pDst,len,level);
}
inline IppStatus ippsCartToPolar(const Ipp32fc* pSrc, Ipp32f* pDstMagn,
                                                   Ipp32f* pDstPhase, int len) {
  return ippsCartToPolar_32fc(pSrc,pDstMagn,pDstPhase,len);
}
inline IppStatus ippsCartToPolar(const Ipp64fc* pSrc, Ipp64f* pDstMagn,
                                                   Ipp64f* pDstPhase, int len) {
  return ippsCartToPolar_64fc(pSrc,pDstMagn,pDstPhase,len);
}
inline IppStatus ippsCartToPolar(const Ipp32f* pSrcRe, const Ipp32f*
                        pSrcIm, Ipp32f* pDstMagn, Ipp32f* pDstPhase, int len) {
  return ippsCartToPolar_32f(pSrcRe,pSrcIm,pDstMagn,pDstPhase,len);
}
inline IppStatus ippsCartToPolar(const Ipp64f* pSrcRe, const Ipp64f*
                        pSrcIm, Ipp64f* pDstMagn, Ipp64f* pDstPhase, int len) {
  return ippsCartToPolar_64f(pSrcRe,pSrcIm,pDstMagn,pDstPhase,len);
}
inline IppStatus ippsPolarToCart(const Ipp32f* pSrcMagn,
                  const Ipp32f* pSrcPhase, Ipp32fc* pDst, int len) {
  return ippsPolarToCart_32fc(pSrcMagn,pSrcPhase,pDst,len);
}
inline IppStatus ippsPolarToCart(const Ipp64f* pSrcMagn,
                  const Ipp64f* pSrcPhase, Ipp64fc* pDst, int len) {
  return ippsPolarToCart_64fc(pSrcMagn,pSrcPhase,pDst,len);
}
inline IppStatus ippsPolarToCart(const Ipp32f* pSrcMagn,
                  const Ipp32f* pSrcPhase, Ipp32f* pDstRe, Ipp32f* pDstIm, int len) {
  return ippsPolarToCart_32f(pSrcMagn,pSrcPhase,pDstRe,pDstIm,len);
}
inline IppStatus ippsPolarToCart(const Ipp64f* pSrcMagn,
                  const Ipp64f* pSrcPhase, Ipp64f* pDstRe, Ipp64f* pDstIm, int len) {
  return ippsPolarToCart_64f(pSrcMagn,pSrcPhase,pDstRe,pDstIm,len);
}
inline IppStatus ippsCartToPolar_Sfs(const Ipp16sc* pSrc, Ipp16s* pDstMagn, Ipp16s* pDstPhase, int len, int magnScaleFactor, int phaseScaleFactor) {
  return ippsCartToPolar_16sc_Sfs(pSrc,pDstMagn,pDstPhase,len,magnScaleFactor,phaseScaleFactor);
}
inline IppStatus ippsPolarToCart_Sfs(const Ipp16s* pSrcMagn, const Ipp16s* pSrcPhase, Ipp16sc* pDst, int len, int magnScaleFactor, int phaseScaleFactor) {
  return ippsPolarToCart_16sc_Sfs(pSrcMagn,pSrcPhase,pDst,len,magnScaleFactor,phaseScaleFactor);
}
inline IppStatus ippsALawToLin(const Ipp8u* pSrc, Ipp32f* pDst, int len) {
  return ippsALawToLin_8u32f(pSrc,pDst,len);
}
inline IppStatus ippsALawToLin(const Ipp8u* pSrc, Ipp16s* pDst, int len) {
  return ippsALawToLin_8u16s(pSrc,pDst,len);
}
inline IppStatus ippsMuLawToLin(const Ipp8u* pSrc, Ipp32f* pDst, int len) {
  return ippsMuLawToLin_8u32f(pSrc,pDst,len);
}
inline IppStatus ippsMuLawToLin(const Ipp8u* pSrc, Ipp16s* pDst, int len) {
  return ippsMuLawToLin_8u16s(pSrc,pDst,len);
}
inline IppStatus ippsLinToALaw(const Ipp32f* pSrc, Ipp8u* pDst, int len) {
  return ippsLinToALaw_32f8u(pSrc,pDst,len);
}
inline IppStatus ippsLinToALaw(const Ipp16s* pSrc, Ipp8u* pDst, int len) {
  return ippsLinToALaw_16s8u(pSrc,pDst,len);
}
inline IppStatus ippsLinToMuLaw(const Ipp32f* pSrc, Ipp8u* pDst, int len) {
  return ippsLinToMuLaw_32f8u(pSrc,pDst,len);
}
inline IppStatus ippsLinToMuLaw(const Ipp16s* pSrc, Ipp8u* pDst, int len) {
  return ippsLinToMuLaw_16s8u(pSrc,pDst,len);
}
inline IppStatus ippsALawToMuLaw(const Ipp8u* pSrc, Ipp8u* pDst, int len) {
  return ippsALawToMuLaw_8u(pSrc,pDst,len);
}
inline IppStatus ippsMuLawToALaw(const Ipp8u* pSrc, Ipp8u* pDst, int len) {
  return ippsMuLawToALaw_8u(pSrc,pDst,len);
}
inline IppStatus ippsPreemphasize(Ipp32f* pSrcDst, int len, Ipp32f val) {
  return ippsPreemphasize_32f(pSrcDst,len,val);
}
inline IppStatus ippsPreemphasize(Ipp16s* pSrcDst, int len, Ipp32f val) {
  return ippsPreemphasize_16s(pSrcDst,len,val);
}
inline IppStatus ippsFlip( const Ipp8u* pSrc, Ipp8u* pDst, int len ) {
  return ippsFlip_8u(pSrc,pDst,len);
}
inline IppStatus ippsFlip_I( Ipp8u* pSrcDst, int len ) {
  return ippsFlip_8u_I(pSrcDst,len);
}
inline IppStatus ippsFlip( const Ipp16u* pSrc, Ipp16u* pDst, int len ) {
  return ippsFlip_16u(pSrc,pDst,len);
}
inline IppStatus ippsFlip_I( Ipp16u* pSrcDst, int len ) {
  return ippsFlip_16u_I(pSrcDst,len);
}
inline IppStatus ippsFlip( const Ipp32f* pSrc, Ipp32f* pDst, int len ) {
  return ippsFlip_32f(pSrc,pDst,len);
}
inline IppStatus ippsFlip_I( Ipp32f* pSrcDst, int len ) {
  return ippsFlip_32f_I(pSrcDst,len);
}
inline IppStatus ippsFlip( const Ipp64f* pSrc, Ipp64f* pDst, int len ) {
  return ippsFlip_64f(pSrc,pDst,len);
}
inline IppStatus ippsFlip_I( Ipp64f* pSrcDst, int len ) {
  return ippsFlip_64f_I(pSrcDst,len);
}
inline IppStatus ippsUpdateLinear_I(const Ipp16s* pSrc,int len,
       Ipp32s* pSrcDst, int srcShiftRight,Ipp16s alpha, IppHintAlgorithm hint=ippAlgHintNone) {
  return ippsUpdateLinear_16s32s_I(pSrc,len,pSrcDst,srcShiftRight,alpha,hint);
}
inline IppStatus ippsUpdatePower_I(const Ipp16s* pSrc,int len,
       Ipp32s* pSrcDst, int srcShiftRight,Ipp16s alpha, IppHintAlgorithm hint=ippAlgHintNone) {
  return ippsUpdatePower_16s32s_I(pSrc,len,pSrcDst,srcShiftRight,alpha,hint);
}
inline IppStatus ippsSwapBytes_I( Ipp16u* pSrcDst, int len ) {
  return ippsSwapBytes_16u_I(pSrcDst,len);
}
inline IppStatus ippsSwapBytes_I( Ipp32u* pSrcDst, int len ) {
  return ippsSwapBytes_32u_I(pSrcDst,len);
}
inline IppStatus ippsSwapBytes( const Ipp16u* pSrc, Ipp16u* pDst, int len ) {
  return ippsSwapBytes_16u(pSrc,pDst,len);
}
inline IppStatus ippsSwapBytes( const Ipp32u* pSrc, Ipp32u* pDst, int len ) {
  return ippsSwapBytes_32u(pSrc,pDst,len);
}
inline IppStatus ippsAddC_I(Ipp16s  val, Ipp16s*  pSrcDst, int len) {
  return ippsAddC_16s_I(val,pSrcDst,len);
}
inline IppStatus ippsSubC_I(Ipp16s  val, Ipp16s*  pSrcDst, int len) {
  return ippsSubC_16s_I(val,pSrcDst,len);
}
inline IppStatus ippsMulC_I(Ipp16s  val, Ipp16s*  pSrcDst, int len) {
  return ippsMulC_16s_I(val,pSrcDst,len);
}
inline IppStatus ippsAddC_I(Ipp32f  val, Ipp32f*  pSrcDst, int len) {
  return ippsAddC_32f_I(val,pSrcDst,len);
}
inline IppStatus ippsAddC_I(Ipp32fc val, Ipp32fc* pSrcDst, int len) {
  return ippsAddC_32fc_I(val,pSrcDst,len);
}
inline IppStatus ippsSubC_I(Ipp32f  val, Ipp32f*  pSrcDst, int len) {
  return ippsSubC_32f_I(val,pSrcDst,len);
}
inline IppStatus ippsSubC_I(Ipp32fc val, Ipp32fc* pSrcDst, int len) {
  return ippsSubC_32fc_I(val,pSrcDst,len);
}
inline IppStatus ippsSubCRev_I(Ipp32f  val, Ipp32f*  pSrcDst, int len) {
  return ippsSubCRev_32f_I(val,pSrcDst,len);
}
inline IppStatus ippsSubCRev_I(Ipp32fc val, Ipp32fc* pSrcDst, int len) {
  return ippsSubCRev_32fc_I(val,pSrcDst,len);
}
inline IppStatus ippsMulC_I(Ipp32f  val, Ipp32f*  pSrcDst, int len) {
  return ippsMulC_32f_I(val,pSrcDst,len);
}
inline IppStatus ippsMulC_I(Ipp32fc val, Ipp32fc* pSrcDst, int len) {
  return ippsMulC_32fc_I(val,pSrcDst,len);
}
inline IppStatus ippsAddC_I(Ipp64f  val, Ipp64f*  pSrcDst, int len) {
  return ippsAddC_64f_I(val,pSrcDst,len);
}
inline IppStatus ippsAddC_I(Ipp64fc val, Ipp64fc* pSrcDst, int len) {
  return ippsAddC_64fc_I(val,pSrcDst,len);
}
inline IppStatus ippsSubC_I(Ipp64f  val, Ipp64f*  pSrcDst, int len) {
  return ippsSubC_64f_I(val,pSrcDst,len);
}
inline IppStatus ippsSubC_I(Ipp64fc val, Ipp64fc* pSrcDst, int len) {
  return ippsSubC_64fc_I(val,pSrcDst,len);
}
inline IppStatus ippsSubCRev_I(Ipp64f  val, Ipp64f*  pSrcDst, int len) {
  return ippsSubCRev_64f_I(val,pSrcDst,len);
}
inline IppStatus ippsSubCRev_I(Ipp64fc val, Ipp64fc* pSrcDst, int len) {
  return ippsSubCRev_64fc_I(val,pSrcDst,len);
}
inline IppStatus ippsMulC_I(Ipp64f  val, Ipp64f*  pSrcDst, int len) {
  return ippsMulC_64f_I(val,pSrcDst,len);
}
inline IppStatus ippsMulC_I(Ipp64fc val, Ipp64fc* pSrcDst, int len) {
  return ippsMulC_64fc_I(val,pSrcDst,len);
}
inline IppStatus ippsMulC_Sfs(const Ipp32f*  pSrc, Ipp32f  val,
       Ipp16s*  pDst, int len, int scaleFactor) {
  return ippsMulC_32f16s_Sfs(pSrc,val,pDst,len,scaleFactor);
}
inline IppStatus ippsMulC_Low(const Ipp32f*  pSrc, Ipp32f  val,
       Ipp16s*  pDst, int len) {
  return ippsMulC_Low_32f16s(pSrc,val,pDst,len);
}
inline IppStatus ippsAddC_ISfs(Ipp8u   val, Ipp8u*   pSrcDst,
       int len, int scaleFactor) {
  return ippsAddC_8u_ISfs(val,pSrcDst,len,scaleFactor);
}
inline IppStatus ippsSubC_ISfs(Ipp8u   val, Ipp8u*   pSrcDst,
       int len, int scaleFactor) {
  return ippsSubC_8u_ISfs(val,pSrcDst,len,scaleFactor);
}
inline IppStatus ippsSubCRev_ISfs(Ipp8u   val, Ipp8u*   pSrcDst,
       int len, int scaleFactor) {
  return ippsSubCRev_8u_ISfs(val,pSrcDst,len,scaleFactor);
}
inline IppStatus ippsMulC_ISfs(Ipp8u   val, Ipp8u*   pSrcDst,
       int len, int scaleFactor) {
  return ippsMulC_8u_ISfs(val,pSrcDst,len,scaleFactor);
}
inline IppStatus ippsAddC_ISfs(Ipp16s  val, Ipp16s*  pSrcDst,
       int len, int scaleFactor) {
  return ippsAddC_16s_ISfs(val,pSrcDst,len,scaleFactor);
}
inline IppStatus ippsSubC_ISfs(Ipp16s  val, Ipp16s*  pSrcDst,
       int len, int scaleFactor) {
  return ippsSubC_16s_ISfs(val,pSrcDst,len,scaleFactor);
}
inline IppStatus ippsMulC_ISfs(Ipp16s  val, Ipp16s*  pSrcDst,
       int len, int scaleFactor) {
  return ippsMulC_16s_ISfs(val,pSrcDst,len,scaleFactor);
}
inline IppStatus ippsAddC_ISfs(Ipp16sc val, Ipp16sc* pSrcDst,
       int len, int scaleFactor) {
  return ippsAddC_16sc_ISfs(val,pSrcDst,len,scaleFactor);
}
inline IppStatus ippsSubC_ISfs(Ipp16sc val, Ipp16sc* pSrcDst,
       int len, int scaleFactor) {
  return ippsSubC_16sc_ISfs(val,pSrcDst,len,scaleFactor);
}
inline IppStatus ippsMulC_ISfs(Ipp16sc val, Ipp16sc* pSrcDst,
       int len, int scaleFactor) {
  return ippsMulC_16sc_ISfs(val,pSrcDst,len,scaleFactor);
}
inline IppStatus ippsSubCRev_ISfs(Ipp16s  val, Ipp16s*  pSrcDst,
       int len, int scaleFactor) {
  return ippsSubCRev_16s_ISfs(val,pSrcDst,len,scaleFactor);
}
inline IppStatus ippsSubCRev_ISfs(Ipp16sc val, Ipp16sc* pSrcDst,
       int len, int scaleFactor) {
  return ippsSubCRev_16sc_ISfs(val,pSrcDst,len,scaleFactor);
}
inline IppStatus ippsAddC_ISfs(Ipp32s  val, Ipp32s*  pSrcDst,
       int len, int scaleFactor) {
  return ippsAddC_32s_ISfs(val,pSrcDst,len,scaleFactor);
}
inline IppStatus ippsAddC_ISfs(Ipp32sc val, Ipp32sc* pSrcDst,
       int len, int scaleFactor) {
  return ippsAddC_32sc_ISfs(val,pSrcDst,len,scaleFactor);
}
inline IppStatus ippsSubC_ISfs(Ipp32s  val, Ipp32s*  pSrcDst,
       int len, int scaleFactor) {
  return ippsSubC_32s_ISfs(val,pSrcDst,len,scaleFactor);
}
inline IppStatus ippsSubC_ISfs(Ipp32sc val, Ipp32sc* pSrcDst,
       int len, int scaleFactor) {
  return ippsSubC_32sc_ISfs(val,pSrcDst,len,scaleFactor);
}
inline IppStatus ippsSubCRev_ISfs(Ipp32s  val, Ipp32s*  pSrcDst,
       int len, int scaleFactor) {
  return ippsSubCRev_32s_ISfs(val,pSrcDst,len,scaleFactor);
}
inline IppStatus ippsSubCRev_ISfs(Ipp32sc val, Ipp32sc* pSrcDst,
       int len, int scaleFactor) {
  return ippsSubCRev_32sc_ISfs(val,pSrcDst,len,scaleFactor);
}
inline IppStatus ippsMulC_ISfs(Ipp32s  val, Ipp32s*  pSrcDst,
       int len, int scaleFactor) {
  return ippsMulC_32s_ISfs(val,pSrcDst,len,scaleFactor);
}
inline IppStatus ippsMulC_ISfs(Ipp32sc val, Ipp32sc* pSrcDst,
       int len, int scaleFactor) {
  return ippsMulC_32sc_ISfs(val,pSrcDst,len,scaleFactor);
}
inline IppStatus ippsAddC(const Ipp32f*  pSrc, Ipp32f  val,
       Ipp32f*  pDst, int len) {
  return ippsAddC_32f(pSrc,val,pDst,len);
}
inline IppStatus ippsAddC(const Ipp32fc* pSrc, Ipp32fc val,
       Ipp32fc* pDst, int len) {
  return ippsAddC_32fc(pSrc,val,pDst,len);
}
inline IppStatus ippsSubC(const Ipp32f*  pSrc, Ipp32f  val,
       Ipp32f*  pDst, int len) {
  return ippsSubC_32f(pSrc,val,pDst,len);
}
inline IppStatus ippsSubC(const Ipp32fc* pSrc, Ipp32fc val,
       Ipp32fc* pDst, int len) {
  return ippsSubC_32fc(pSrc,val,pDst,len);
}
inline IppStatus ippsSubCRev(const Ipp32f*  pSrc, Ipp32f  val,
       Ipp32f*  pDst, int len) {
  return ippsSubCRev_32f(pSrc,val,pDst,len);
}
inline IppStatus ippsSubCRev(const Ipp32fc* pSrc, Ipp32fc val,
       Ipp32fc* pDst, int len) {
  return ippsSubCRev_32fc(pSrc,val,pDst,len);
}
inline IppStatus ippsMulC(const Ipp32f*  pSrc, Ipp32f  val,
       Ipp32f*  pDst, int len) {
  return ippsMulC_32f(pSrc,val,pDst,len);
}
inline IppStatus ippsMulC(const Ipp32fc* pSrc, Ipp32fc val,
       Ipp32fc* pDst, int len) {
  return ippsMulC_32fc(pSrc,val,pDst,len);
}
inline IppStatus ippsAddC(const Ipp64f*  pSrc, Ipp64f  val,
       Ipp64f*  pDst, int len) {
  return ippsAddC_64f(pSrc,val,pDst,len);
}
inline IppStatus ippsAddC(const Ipp64fc* pSrc, Ipp64fc val,
       Ipp64fc* pDst, int len) {
  return ippsAddC_64fc(pSrc,val,pDst,len);
}
inline IppStatus ippsSubC(const Ipp64f*  pSrc, Ipp64f  val,
       Ipp64f*  pDst, int len) {
  return ippsSubC_64f(pSrc,val,pDst,len);
}
inline IppStatus ippsSubC(const Ipp64fc* pSrc, Ipp64fc val,
       Ipp64fc* pDst, int len) {
  return ippsSubC_64fc(pSrc,val,pDst,len);
}
inline IppStatus ippsSubCRev(const Ipp64f*  pSrc, Ipp64f  val,
       Ipp64f*  pDst, int len) {
  return ippsSubCRev_64f(pSrc,val,pDst,len);
}
inline IppStatus ippsSubCRev(const Ipp64fc* pSrc, Ipp64fc val,
       Ipp64fc* pDst, int len) {
  return ippsSubCRev_64fc(pSrc,val,pDst,len);
}
inline IppStatus ippsMulC(const Ipp64f*  pSrc, Ipp64f  val,
       Ipp64f*  pDst, int len) {
  return ippsMulC_64f(pSrc,val,pDst,len);
}
inline IppStatus ippsMulC(const Ipp64fc* pSrc, Ipp64fc val,
       Ipp64fc* pDst, int len) {
  return ippsMulC_64fc(pSrc,val,pDst,len);
}
inline IppStatus ippsAddC_Sfs(const Ipp8u*   pSrc, Ipp8u   val,
       Ipp8u*   pDst, int len, int scaleFactor) {
  return ippsAddC_8u_Sfs(pSrc,val,pDst,len,scaleFactor);
}
inline IppStatus ippsSubC_Sfs(const Ipp8u*   pSrc, Ipp8u   val,
       Ipp8u*   pDst, int len, int scaleFactor) {
  return ippsSubC_8u_Sfs(pSrc,val,pDst,len,scaleFactor);
}
inline IppStatus ippsSubCRev_Sfs(const Ipp8u*   pSrc, Ipp8u   val,
       Ipp8u*   pDst, int len, int scaleFactor) {
  return ippsSubCRev_8u_Sfs(pSrc,val,pDst,len,scaleFactor);
}
inline IppStatus ippsMulC_Sfs(const Ipp8u*   pSrc, Ipp8u   val,
       Ipp8u*   pDst, int len, int scaleFactor) {
  return ippsMulC_8u_Sfs(pSrc,val,pDst,len,scaleFactor);
}
inline IppStatus ippsAddC_Sfs(const Ipp16s*  pSrc, Ipp16s  val,
       Ipp16s*  pDst, int len, int scaleFactor) {
  return ippsAddC_16s_Sfs(pSrc,val,pDst,len,scaleFactor);
}
inline IppStatus ippsAddC_Sfs(const Ipp16sc* pSrc, Ipp16sc val,
       Ipp16sc* pDst, int len, int scaleFactor) {
  return ippsAddC_16sc_Sfs(pSrc,val,pDst,len,scaleFactor);
}
inline IppStatus ippsSubC_Sfs(const Ipp16s*  pSrc, Ipp16s  val,
       Ipp16s*  pDst, int len, int scaleFactor) {
  return ippsSubC_16s_Sfs(pSrc,val,pDst,len,scaleFactor);
}
inline IppStatus ippsSubC_Sfs(const Ipp16sc* pSrc, Ipp16sc val,
       Ipp16sc* pDst, int len, int scaleFactor) {
  return ippsSubC_16sc_Sfs(pSrc,val,pDst,len,scaleFactor);
}
inline IppStatus ippsSubCRev_Sfs(const Ipp16s*  pSrc, Ipp16s  val,
       Ipp16s*  pDst, int len, int scaleFactor) {
  return ippsSubCRev_16s_Sfs(pSrc,val,pDst,len,scaleFactor);
}
inline IppStatus ippsSubCRev_Sfs(const Ipp16sc* pSrc, Ipp16sc val,
       Ipp16sc* pDst, int len, int scaleFactor) {
  return ippsSubCRev_16sc_Sfs(pSrc,val,pDst,len,scaleFactor);
}
inline IppStatus ippsMulC_Sfs(const Ipp16s*  pSrc, Ipp16s  val,
       Ipp16s*  pDst, int len, int scaleFactor) {
  return ippsMulC_16s_Sfs(pSrc,val,pDst,len,scaleFactor);
}
inline IppStatus ippsMulC_Sfs(const Ipp16sc* pSrc, Ipp16sc val,
       Ipp16sc* pDst, int len, int scaleFactor) {
  return ippsMulC_16sc_Sfs(pSrc,val,pDst,len,scaleFactor);
}
inline IppStatus ippsAddC_Sfs(const Ipp32s*  pSrc, Ipp32s  val,
       Ipp32s*  pDst, int len, int scaleFactor) {
  return ippsAddC_32s_Sfs(pSrc,val,pDst,len,scaleFactor);
}
inline IppStatus ippsAddC_Sfs(const Ipp32sc* pSrc, Ipp32sc val,
       Ipp32sc* pDst, int len, int scaleFactor) {
  return ippsAddC_32sc_Sfs(pSrc,val,pDst,len,scaleFactor);
}
inline IppStatus ippsSubC_Sfs(const Ipp32s*  pSrc, Ipp32s  val,
       Ipp32s*  pDst, int len, int scaleFactor) {
  return ippsSubC_32s_Sfs(pSrc,val,pDst,len,scaleFactor);
}
inline IppStatus ippsSubC_Sfs(const Ipp32sc* pSrc, Ipp32sc val,
       Ipp32sc* pDst, int len, int scaleFactor) {
  return ippsSubC_32sc_Sfs(pSrc,val,pDst,len,scaleFactor);
}
inline IppStatus ippsSubCRev_Sfs(const Ipp32s*  pSrc, Ipp32s  val,
       Ipp32s*  pDst, int len, int scaleFactor) {
  return ippsSubCRev_32s_Sfs(pSrc,val,pDst,len,scaleFactor);
}
inline IppStatus ippsSubCRev_Sfs(const Ipp32sc* pSrc, Ipp32sc val,
       Ipp32sc* pDst, int len, int scaleFactor) {
  return ippsSubCRev_32sc_Sfs(pSrc,val,pDst,len,scaleFactor);
}
inline IppStatus ippsMulC_Sfs(const Ipp32s*  pSrc, Ipp32s  val,
       Ipp32s*  pDst, int len, int scaleFactor) {
  return ippsMulC_32s_Sfs(pSrc,val,pDst,len,scaleFactor);
}
inline IppStatus ippsMulC_Sfs(const Ipp32sc* pSrc, Ipp32sc val,
       Ipp32sc* pDst, int len, int scaleFactor) {
  return ippsMulC_32sc_Sfs(pSrc,val,pDst,len,scaleFactor);
}
inline IppStatus ippsAdd_I(const Ipp16s*  pSrc,
       Ipp16s*  pSrcDst, int len) {
  return ippsAdd_16s_I(pSrc,pSrcDst,len);
}
inline IppStatus ippsSub_I(const Ipp16s*  pSrc,
       Ipp16s*  pSrcDst, int len) {
  return ippsSub_16s_I(pSrc,pSrcDst,len);
}
inline IppStatus ippsMul_I(const Ipp16s*  pSrc,
       Ipp16s*  pSrcDst, int len) {
  return ippsMul_16s_I(pSrc,pSrcDst,len);
}
inline IppStatus ippsAdd_I(const Ipp32f*  pSrc,
       Ipp32f*  pSrcDst, int len) {
  return ippsAdd_32f_I(pSrc,pSrcDst,len);
}
inline IppStatus ippsAdd_I(const Ipp32fc* pSrc,
       Ipp32fc* pSrcDst, int len) {
  return ippsAdd_32fc_I(pSrc,pSrcDst,len);
}
inline IppStatus ippsSub_I(const Ipp32f*  pSrc,
       Ipp32f*  pSrcDst, int len) {
  return ippsSub_32f_I(pSrc,pSrcDst,len);
}
inline IppStatus ippsSub_I(const Ipp32fc* pSrc,
       Ipp32fc* pSrcDst, int len) {
  return ippsSub_32fc_I(pSrc,pSrcDst,len);
}
inline IppStatus ippsMul_I(const Ipp32f*  pSrc,
       Ipp32f*  pSrcDst, int len) {
  return ippsMul_32f_I(pSrc,pSrcDst,len);
}
inline IppStatus ippsMul_I(const Ipp32fc* pSrc,
       Ipp32fc* pSrcDst, int len) {
  return ippsMul_32fc_I(pSrc,pSrcDst,len);
}
inline IppStatus ippsAdd_I(const Ipp64f*  pSrc,
       Ipp64f*  pSrcDst, int len) {
  return ippsAdd_64f_I(pSrc,pSrcDst,len);
}
inline IppStatus ippsAdd_I(const Ipp64fc* pSrc,
       Ipp64fc* pSrcDst, int len) {
  return ippsAdd_64fc_I(pSrc,pSrcDst,len);
}
inline IppStatus ippsSub_I(const Ipp64f*  pSrc,
       Ipp64f*  pSrcDst, int len) {
  return ippsSub_64f_I(pSrc,pSrcDst,len);
}
inline IppStatus ippsSub_I(const Ipp64fc* pSrc,
       Ipp64fc* pSrcDst, int len) {
  return ippsSub_64fc_I(pSrc,pSrcDst,len);
}
inline IppStatus ippsMul_I(const Ipp64f*  pSrc,
       Ipp64f*  pSrcDst, int len) {
  return ippsMul_64f_I(pSrc,pSrcDst,len);
}
inline IppStatus ippsMul_I(const Ipp64fc* pSrc,
       Ipp64fc* pSrcDst, int len) {
  return ippsMul_64fc_I(pSrc,pSrcDst,len);
}
inline IppStatus ippsAdd_ISfs(const Ipp8u*   pSrc, Ipp8u*   pSrcDst,
       int len, int scaleFactor) {
  return ippsAdd_8u_ISfs(pSrc,pSrcDst,len,scaleFactor);
}
inline IppStatus ippsSub_ISfs(const Ipp8u*   pSrc, Ipp8u*   pSrcDst,
       int len, int scaleFactor) {
  return ippsSub_8u_ISfs(pSrc,pSrcDst,len,scaleFactor);
}
inline IppStatus ippsMul_ISfs(const Ipp8u*   pSrc, Ipp8u*   pSrcDst,
       int len, int scaleFactor) {
  return ippsMul_8u_ISfs(pSrc,pSrcDst,len,scaleFactor);
}
inline IppStatus ippsAdd_ISfs(const Ipp16s*  pSrc, Ipp16s*  pSrcDst,
       int len, int scaleFactor) {
  return ippsAdd_16s_ISfs(pSrc,pSrcDst,len,scaleFactor);
}
inline IppStatus ippsAdd_ISfs(const Ipp16sc* pSrc, Ipp16sc* pSrcDst,
       int len, int scaleFactor) {
  return ippsAdd_16sc_ISfs(pSrc,pSrcDst,len,scaleFactor);
}
inline IppStatus ippsSub_ISfs(const Ipp16s*  pSrc, Ipp16s*  pSrcDst,
       int len, int scaleFactor) {
  return ippsSub_16s_ISfs(pSrc,pSrcDst,len,scaleFactor);
}
inline IppStatus ippsSub_ISfs(const Ipp16sc* pSrc, Ipp16sc* pSrcDst,
       int len, int scaleFactor) {
  return ippsSub_16sc_ISfs(pSrc,pSrcDst,len,scaleFactor);
}
inline IppStatus ippsMul_ISfs(const Ipp16s*  pSrc, Ipp16s*  pSrcDst,
       int len, int scaleFactor) {
  return ippsMul_16s_ISfs(pSrc,pSrcDst,len,scaleFactor);
}
inline IppStatus ippsMul_ISfs(const Ipp16sc* pSrc, Ipp16sc* pSrcDst,
       int len, int scaleFactor) {
  return ippsMul_16sc_ISfs(pSrc,pSrcDst,len,scaleFactor);
}
inline IppStatus ippsAdd_ISfs(const Ipp32s*  pSrc, Ipp32s*  pSrcDst,
       int len, int scaleFactor) {
  return ippsAdd_32s_ISfs(pSrc,pSrcDst,len,scaleFactor);
}
inline IppStatus ippsAdd_ISfs(const Ipp32sc* pSrc, Ipp32sc* pSrcDst,
       int len, int scaleFactor) {
  return ippsAdd_32sc_ISfs(pSrc,pSrcDst,len,scaleFactor);
}
inline IppStatus ippsSub_ISfs(const Ipp32s*  pSrc, Ipp32s*  pSrcDst,
       int len, int scaleFactor) {
  return ippsSub_32s_ISfs(pSrc,pSrcDst,len,scaleFactor);
}
inline IppStatus ippsSub_ISfs(const Ipp32sc* pSrc, Ipp32sc* pSrcDst,
       int len, int scaleFactor) {
  return ippsSub_32sc_ISfs(pSrc,pSrcDst,len,scaleFactor);
}
inline IppStatus ippsMul_ISfs(const Ipp32s*  pSrc, Ipp32s*  pSrcDst,
       int len, int scaleFactor) {
  return ippsMul_32s_ISfs(pSrc,pSrcDst,len,scaleFactor);
}
inline IppStatus ippsMul_ISfs(const Ipp32sc* pSrc, Ipp32sc* pSrcDst,
       int len, int scaleFactor) {
  return ippsMul_32sc_ISfs(pSrc,pSrcDst,len,scaleFactor);
}
inline IppStatus ippsAdd(const Ipp8u*   pSrc1, const Ipp8u*   pSrc2,
       Ipp16u*  pDst, int len) {
  return ippsAdd_8u16u(pSrc1,pSrc2,pDst,len);
}
inline IppStatus ippsMul(const Ipp8u*   pSrc1, const Ipp8u*   pSrc2,
       Ipp16u*  pDst, int len) {
  return ippsMul_8u16u(pSrc1,pSrc2,pDst,len);
}
inline IppStatus ippsAdd(const Ipp16s*  pSrc1, const Ipp16s*  pSrc2,
       Ipp16s*  pDst, int len) {
  return ippsAdd_16s(pSrc1,pSrc2,pDst,len);
}
inline IppStatus ippsSub(const Ipp16s*  pSrc1, const Ipp16s*  pSrc2,
       Ipp16s*  pDst, int len) {
  return ippsSub_16s(pSrc1,pSrc2,pDst,len);
}
inline IppStatus ippsMul(const Ipp16s*  pSrc1, const Ipp16s*  pSrc2,
       Ipp16s*  pDst, int len) {
  return ippsMul_16s(pSrc1,pSrc2,pDst,len);
}
inline IppStatus ippsAdd(const Ipp16u*  pSrc1, const Ipp16u*  pSrc2,
       Ipp16u*  pDst, int len) {
  return ippsAdd_16u(pSrc1,pSrc2,pDst,len);
}
inline IppStatus ippsAdd(const Ipp32u*  pSrc1, const Ipp32u*  pSrc2,
       Ipp32u*  pDst, int len) {
  return ippsAdd_32u(pSrc1,pSrc2,pDst,len);
}
inline IppStatus ippsAdd(const Ipp16s*  pSrc1, const Ipp16s*  pSrc2,
       Ipp32f*  pDst, int len) {
  return ippsAdd_16s32f(pSrc1,pSrc2,pDst,len);
}
inline IppStatus ippsSub(const Ipp16s*  pSrc1, const Ipp16s*  pSrc2,
       Ipp32f*  pDst, int len) {
  return ippsSub_16s32f(pSrc1,pSrc2,pDst,len);
}
inline IppStatus ippsMul(const Ipp16s*  pSrc1, const Ipp16s*  pSrc2,
       Ipp32f*  pDst, int len) {
  return ippsMul_16s32f(pSrc1,pSrc2,pDst,len);
}
inline IppStatus ippsAdd(const Ipp32f*  pSrc1, const Ipp32f*  pSrc2,
       Ipp32f*  pDst, int len) {
  return ippsAdd_32f(pSrc1,pSrc2,pDst,len);
}
inline IppStatus ippsAdd(const Ipp32fc* pSrc1, const Ipp32fc* pSrc2,
       Ipp32fc* pDst, int len) {
  return ippsAdd_32fc(pSrc1,pSrc2,pDst,len);
}
inline IppStatus ippsSub(const Ipp32f*  pSrc1, const Ipp32f*  pSrc2,
       Ipp32f*  pDst, int len) {
  return ippsSub_32f(pSrc1,pSrc2,pDst,len);
}
inline IppStatus ippsSub(const Ipp32fc* pSrc1, const Ipp32fc* pSrc2,
       Ipp32fc* pDst, int len) {
  return ippsSub_32fc(pSrc1,pSrc2,pDst,len);
}
inline IppStatus ippsMul(const Ipp32f*  pSrc1, const Ipp32f*  pSrc2,
       Ipp32f*  pDst, int len) {
  return ippsMul_32f(pSrc1,pSrc2,pDst,len);
}
inline IppStatus ippsMul(const Ipp32fc* pSrc1, const Ipp32fc* pSrc2,
       Ipp32fc* pDst, int len) {
  return ippsMul_32fc(pSrc1,pSrc2,pDst,len);
}
inline IppStatus ippsAdd(const Ipp64f*  pSrc1, const Ipp64f*  pSrc2,
       Ipp64f*  pDst, int len) {
  return ippsAdd_64f(pSrc1,pSrc2,pDst,len);
}
inline IppStatus ippsAdd(const Ipp64fc* pSrc1, const Ipp64fc* pSrc2,
       Ipp64fc* pDst, int len) {
  return ippsAdd_64fc(pSrc1,pSrc2,pDst,len);
}
inline IppStatus ippsSub(const Ipp64f*  pSrc1, const Ipp64f*  pSrc2,
       Ipp64f*  pDst, int len) {
  return ippsSub_64f(pSrc1,pSrc2,pDst,len);
}
inline IppStatus ippsSub(const Ipp64fc* pSrc1, const Ipp64fc* pSrc2,
       Ipp64fc* pDst, int len) {
  return ippsSub_64fc(pSrc1,pSrc2,pDst,len);
}
inline IppStatus ippsMul(const Ipp64f*  pSrc1, const Ipp64f*  pSrc2,
       Ipp64f*  pDst, int len) {
  return ippsMul_64f(pSrc1,pSrc2,pDst,len);
}
inline IppStatus ippsMul(const Ipp64fc* pSrc1, const Ipp64fc* pSrc2,
       Ipp64fc* pDst, int len) {
  return ippsMul_64fc(pSrc1,pSrc2,pDst,len);
}
inline IppStatus ippsAdd_Sfs(const Ipp8u*   pSrc1, const Ipp8u*   pSrc2,
       Ipp8u*   pDst, int len, int scaleFactor) {
  return ippsAdd_8u_Sfs(pSrc1,pSrc2,pDst,len,scaleFactor);
}
inline IppStatus ippsSub_Sfs(const Ipp8u*   pSrc1, const Ipp8u*   pSrc2,
       Ipp8u*   pDst, int len, int scaleFactor) {
  return ippsSub_8u_Sfs(pSrc1,pSrc2,pDst,len,scaleFactor);
}
inline IppStatus ippsMul_Sfs(const Ipp8u*   pSrc1, const Ipp8u*   pSrc2,
       Ipp8u*   pDst, int len, int scaleFactor) {
  return ippsMul_8u_Sfs(pSrc1,pSrc2,pDst,len,scaleFactor);
}
inline IppStatus ippsAdd_Sfs(const Ipp16s*  pSrc1, const Ipp16s*  pSrc2,
       Ipp16s*  pDst, int len, int scaleFactor) {
  return ippsAdd_16s_Sfs(pSrc1,pSrc2,pDst,len,scaleFactor);
}
inline IppStatus ippsAdd_Sfs(const Ipp16sc* pSrc1, const Ipp16sc* pSrc2,
       Ipp16sc* pDst, int len, int scaleFactor) {
  return ippsAdd_16sc_Sfs(pSrc1,pSrc2,pDst,len,scaleFactor);
}
inline IppStatus ippsSub_Sfs(const Ipp16s*  pSrc1, const Ipp16s*  pSrc2,
       Ipp16s*  pDst, int len, int scaleFactor) {
  return ippsSub_16s_Sfs(pSrc1,pSrc2,pDst,len,scaleFactor);
}
inline IppStatus ippsSub_Sfs(const Ipp16sc* pSrc1, const Ipp16sc* pSrc2,
       Ipp16sc* pDst, int len, int scaleFactor) {
  return ippsSub_16sc_Sfs(pSrc1,pSrc2,pDst,len,scaleFactor);
}
inline IppStatus ippsMul_Sfs(const Ipp16s*  pSrc1, const Ipp16s*  pSrc2,
       Ipp16s*  pDst, int len, int scaleFactor) {
  return ippsMul_16s_Sfs(pSrc1,pSrc2,pDst,len,scaleFactor);
}
inline IppStatus ippsMul_Sfs(const Ipp16sc* pSrc1, const Ipp16sc* pSrc2,
       Ipp16sc* pDst, int len, int scaleFactor) {
  return ippsMul_16sc_Sfs(pSrc1,pSrc2,pDst,len,scaleFactor);
}
inline IppStatus ippsMul_Sfs(const Ipp16s*  pSrc1, const Ipp16s*  pSrc2,
       Ipp32s*  pDst, int len, int scaleFactor) {
  return ippsMul_16s32s_Sfs(pSrc1,pSrc2,pDst,len,scaleFactor);
}
inline IppStatus ippsAdd_Sfs(const Ipp32s*  pSrc1, const Ipp32s*  pSrc2,
       Ipp32s*  pDst, int len, int scaleFactor) {
  return ippsAdd_32s_Sfs(pSrc1,pSrc2,pDst,len,scaleFactor);
}
inline IppStatus ippsAdd_Sfs(const Ipp32sc* pSrc1, const Ipp32sc* pSrc2,
       Ipp32sc* pDst, int len, int scaleFactor) {
  return ippsAdd_32sc_Sfs(pSrc1,pSrc2,pDst,len,scaleFactor);
}
inline IppStatus ippsSub_Sfs(const Ipp32s*  pSrc1, const Ipp32s*  pSrc2,
       Ipp32s*  pDst, int len, int scaleFactor) {
  return ippsSub_32s_Sfs(pSrc1,pSrc2,pDst,len,scaleFactor);
}
inline IppStatus ippsSub_Sfs(const Ipp32sc* pSrc1, const Ipp32sc* pSrc2,
       Ipp32sc* pDst, int len, int scaleFactor) {
  return ippsSub_32sc_Sfs(pSrc1,pSrc2,pDst,len,scaleFactor);
}
inline IppStatus ippsMul_Sfs(const Ipp32s*  pSrc1, const Ipp32s*  pSrc2,
       Ipp32s*  pDst, int len, int scaleFactor) {
  return ippsMul_32s_Sfs(pSrc1,pSrc2,pDst,len,scaleFactor);
}
inline IppStatus ippsMul_Sfs(const Ipp32sc* pSrc1, const Ipp32sc* pSrc2,
       Ipp32sc* pDst, int len, int scaleFactor) {
  return ippsMul_32sc_Sfs(pSrc1,pSrc2,pDst,len,scaleFactor);
}
inline IppStatus ippsMul_Sfs(const Ipp16u* pSrc1, const Ipp16s* pSrc2,
       Ipp16s* pDst, int len, int scaleFactor) {
  return ippsMul_16u16s_Sfs(pSrc1,pSrc2,pDst,len,scaleFactor);
}
inline IppStatus ippsMul_ISfs(const Ipp32s* pSrc, Ipp32sc* pSrcDst,
       int len, int scaleFactor) {
  return ippsMul_32s32sc_ISfs(pSrc,pSrcDst,len,scaleFactor);
}
inline IppStatus ippsMul_Sfs(const Ipp32s* pSrc1, const Ipp32sc* pSrc2,
       Ipp32sc* pDst, int len, int scaleFactor) {
  return ippsMul_32s32sc_Sfs(pSrc1,pSrc2,pDst,len,scaleFactor);
}
inline IppStatus ippsMul_I(const Ipp32f* pSrc, Ipp32fc* pSrcDst,
       int len) {
  return ippsMul_32f32fc_I(pSrc,pSrcDst,len);
}
inline IppStatus ippsMul(const Ipp32f* pSrc1, const Ipp32fc* pSrc2,
       Ipp32fc* pDst, int len) {
  return ippsMul_32f32fc(pSrc1,pSrc2,pDst,len);
}
inline IppStatus ippsAdd_I(const Ipp16s* pSrc, Ipp32s* pSrcDst, int len) {
  return ippsAdd_16s32s_I(pSrc,pSrcDst,len);
}
inline IppStatus ippsAddProduct_Sfs( const Ipp16s* pSrc1, const Ipp16s* pSrc2,
                                               Ipp16s* pSrcDst, int len, int scaleFactor ) {
  return ippsAddProduct_16s_Sfs(pSrc1,pSrc2,pSrcDst,len,scaleFactor);
}
inline IppStatus ippsAddProduct_Sfs( const Ipp16s* pSrc1, const Ipp16s* pSrc2,
                                               Ipp32s* pSrcDst, int len, int scaleFactor ) {
  return ippsAddProduct_16s32s_Sfs(pSrc1,pSrc2,pSrcDst,len,scaleFactor);
}
inline IppStatus ippsAddProduct_Sfs( const Ipp32s* pSrc1, const Ipp32s* pSrc2,
                                               Ipp32s* pSrcDst, int len, int scaleFactor ) {
  return ippsAddProduct_32s_Sfs(pSrc1,pSrc2,pSrcDst,len,scaleFactor);
}
inline IppStatus ippsAddProduct( const Ipp32f* pSrc1, const Ipp32f* pSrc2,
                                               Ipp32f* pSrcDst, int len ) {
  return ippsAddProduct_32f(pSrc1,pSrc2,pSrcDst,len);
}
inline IppStatus ippsAddProduct( const Ipp64f* pSrc1, const Ipp64f* pSrc2,
                                               Ipp64f* pSrcDst, int len ) {
  return ippsAddProduct_64f(pSrc1,pSrc2,pSrcDst,len);
}
inline IppStatus ippsAddProduct( const Ipp32fc* pSrc1, const Ipp32fc* pSrc2,
                                               Ipp32fc* pSrcDst, int len ) {
  return ippsAddProduct_32fc(pSrc1,pSrc2,pSrcDst,len);
}
inline IppStatus ippsAddProduct( const Ipp64fc* pSrc1, const Ipp64fc* pSrc2,
                                               Ipp64fc* pSrcDst, int len ) {
  return ippsAddProduct_64fc(pSrc1,pSrc2,pSrcDst,len);
}
inline IppStatus ippsSqr_I(Ipp32f* pSrcDst, int len) {
  return ippsSqr_32f_I(pSrcDst,len);
}
inline IppStatus ippsSqr_I(Ipp32fc* pSrcDst, int len) {
  return ippsSqr_32fc_I(pSrcDst,len);
}
inline IppStatus ippsSqr_I(Ipp64f* pSrcDst, int len) {
  return ippsSqr_64f_I(pSrcDst,len);
}
inline IppStatus ippsSqr_I(Ipp64fc* pSrcDst, int len) {
  return ippsSqr_64fc_I(pSrcDst,len);
}
inline IppStatus ippsSqr(const Ipp32f* pSrc, Ipp32f* pDst, int len) {
  return ippsSqr_32f(pSrc,pDst,len);
}
inline IppStatus ippsSqr(const Ipp32fc* pSrc, Ipp32fc* pDst, int len) {
  return ippsSqr_32fc(pSrc,pDst,len);
}
inline IppStatus ippsSqr(const Ipp64f* pSrc, Ipp64f* pDst, int len) {
  return ippsSqr_64f(pSrc,pDst,len);
}
inline IppStatus ippsSqr(const Ipp64fc* pSrc, Ipp64fc* pDst, int len) {
  return ippsSqr_64fc(pSrc,pDst,len);
}
inline IppStatus ippsSqr_ISfs(Ipp16s* pSrcDst, int len, int scaleFactor) {
  return ippsSqr_16s_ISfs(pSrcDst,len,scaleFactor);
}
inline IppStatus ippsSqr_ISfs(Ipp16sc* pSrcDst, int len, int scaleFactor) {
  return ippsSqr_16sc_ISfs(pSrcDst,len,scaleFactor);
}
inline IppStatus ippsSqr_Sfs(const Ipp16s* pSrc, Ipp16s* pDst, int len,
                                  int scaleFactor) {
  return ippsSqr_16s_Sfs(pSrc,pDst,len,scaleFactor);
}
inline IppStatus ippsSqr_Sfs(const Ipp16sc* pSrc, Ipp16sc* pDst, int len,
                                   int scaleFactor) {
  return ippsSqr_16sc_Sfs(pSrc,pDst,len,scaleFactor);
}
inline IppStatus ippsSqr_ISfs(Ipp8u* pSrcDst, int len, int scaleFactor) {
  return ippsSqr_8u_ISfs(pSrcDst,len,scaleFactor);
}
inline IppStatus ippsSqr_Sfs(const Ipp8u* pSrc, Ipp8u* pDst, int len,
                                 int scaleFactor) {
  return ippsSqr_8u_Sfs(pSrc,pDst,len,scaleFactor);
}
inline IppStatus ippsSqr_ISfs(Ipp16u* pSrcDst, int len, int scaleFactor) {
  return ippsSqr_16u_ISfs(pSrcDst,len,scaleFactor);
}
inline IppStatus ippsSqr_Sfs(const Ipp16u* pSrc, Ipp16u* pDst, int len,
                                  int scaleFactor) {
  return ippsSqr_16u_Sfs(pSrc,pDst,len,scaleFactor);
}
inline IppStatus ippsDiv(const Ipp32f* pSrc1, const Ipp32f* pSrc2,
       Ipp32f* pDst, int len) {
  return ippsDiv_32f(pSrc1,pSrc2,pDst,len);
}
inline IppStatus ippsDiv(const Ipp32fc* pSrc1, const Ipp32fc* pSrc2,
       Ipp32fc* pDst, int len) {
  return ippsDiv_32fc(pSrc1,pSrc2,pDst,len);
}
inline IppStatus ippsDiv(const Ipp64f* pSrc1, const Ipp64f* pSrc2,
       Ipp64f* pDst, int len) {
  return ippsDiv_64f(pSrc1,pSrc2,pDst,len);
}
inline IppStatus ippsDiv(const Ipp64fc* pSrc1, const Ipp64fc* pSrc2,
       Ipp64fc* pDst, int len) {
  return ippsDiv_64fc(pSrc1,pSrc2,pDst,len);
}
inline IppStatus ippsDiv_Sfs(const Ipp16s* pSrc1, const Ipp16s* pSrc2,
       Ipp16s* pDst, int len, int scaleFactor) {
  return ippsDiv_16s_Sfs(pSrc1,pSrc2,pDst,len,scaleFactor);
}
inline IppStatus ippsDiv_Sfs(const Ipp8u* pSrc1, const Ipp8u* pSrc2,
       Ipp8u* pDst, int len, int scaleFactor) {
  return ippsDiv_8u_Sfs(pSrc1,pSrc2,pDst,len,scaleFactor);
}
inline IppStatus ippsDiv_Sfs(const Ipp16sc* pSrc1,
       const Ipp16sc* pSrc2, Ipp16sc* pDst, int len, int scaleFactor) {
  return ippsDiv_16sc_Sfs(pSrc1,pSrc2,pDst,len,scaleFactor);
}
inline IppStatus ippsDivC(const Ipp32f* pSrc, Ipp32f val,
       Ipp32f* pDst, int len) {
  return ippsDivC_32f(pSrc,val,pDst,len);
}
inline IppStatus ippsDivC(const Ipp32fc* pSrc, Ipp32fc val,
       Ipp32fc* pDst, int len) {
  return ippsDivC_32fc(pSrc,val,pDst,len);
}
inline IppStatus ippsDivC(const Ipp64f* pSrc, Ipp64f val,
       Ipp64f* pDst, int len) {
  return ippsDivC_64f(pSrc,val,pDst,len);
}
inline IppStatus ippsDivC(const Ipp64fc* pSrc, Ipp64fc val,
       Ipp64fc* pDst, int len) {
  return ippsDivC_64fc(pSrc,val,pDst,len);
}
inline IppStatus ippsDivC_Sfs(const Ipp16s* pSrc, Ipp16s val,
       Ipp16s* pDst, int len, int scaleFactor) {
  return ippsDivC_16s_Sfs(pSrc,val,pDst,len,scaleFactor);
}
inline IppStatus ippsDivC_Sfs(const Ipp8u* pSrc, Ipp8u val,
       Ipp8u* pDst, int len, int scaleFactor) {
  return ippsDivC_8u_Sfs(pSrc,val,pDst,len,scaleFactor);
}
inline IppStatus ippsDivC_Sfs(const Ipp16sc* pSrc, Ipp16sc val,
       Ipp16sc* pDst, int len, int scaleFactor) {
  return ippsDivC_16sc_Sfs(pSrc,val,pDst,len,scaleFactor);
}
inline IppStatus ippsDiv_I(const Ipp32f* pSrc,
       Ipp32f* pSrcDst, int len) {
  return ippsDiv_32f_I(pSrc,pSrcDst,len);
}
inline IppStatus ippsDiv_I(const Ipp32fc* pSrc,
       Ipp32fc* pSrcDst, int len) {
  return ippsDiv_32fc_I(pSrc,pSrcDst,len);
}
inline IppStatus ippsDiv_I(const Ipp64f* pSrc,
       Ipp64f* pSrcDst, int len) {
  return ippsDiv_64f_I(pSrc,pSrcDst,len);
}
inline IppStatus ippsDiv_I(const Ipp64fc* pSrc,
       Ipp64fc* pSrcDst, int len) {
  return ippsDiv_64fc_I(pSrc,pSrcDst,len);
}
inline IppStatus ippsDiv_ISfs(const Ipp16s* pSrc, Ipp16s* pSrcDst,
       int len, int scaleFactor) {
  return ippsDiv_16s_ISfs(pSrc,pSrcDst,len,scaleFactor);
}
inline IppStatus ippsDiv_ISfs(const Ipp8u* pSrc, Ipp8u* pSrcDst,
       int len, int scaleFactor) {
  return ippsDiv_8u_ISfs(pSrc,pSrcDst,len,scaleFactor);
}
inline IppStatus ippsDiv_ISfs(const Ipp16sc* pSrc, Ipp16sc* pSrcDst,
       int len, int scaleFactor) {
  return ippsDiv_16sc_ISfs(pSrc,pSrcDst,len,scaleFactor);
}
inline IppStatus ippsDiv_Sfs(const Ipp32s* pSrc1, const Ipp32s* pSrc2,
       Ipp32s* pDst, int len, int scaleFactor) {
  return ippsDiv_32s_Sfs(pSrc1,pSrc2,pDst,len,scaleFactor);
}
inline IppStatus ippsDiv_ISfs(const Ipp32s* pSrc, Ipp32s* pSrcDst,
       int len, int ScaleFactor) {
  return ippsDiv_32s_ISfs(pSrc,pSrcDst,len,ScaleFactor);
}
inline IppStatus ippsDiv_Sfs(const Ipp16s* pSrc1, const Ipp32s* pSrc2,
       Ipp16s* pDst, int len, int scaleFactor) {
  return ippsDiv_32s16s_Sfs(pSrc1,pSrc2,pDst,len,scaleFactor);
}
inline IppStatus ippsDivC_I(Ipp32f val, Ipp32f* pSrcDst, int len) {
  return ippsDivC_32f_I(val,pSrcDst,len);
}
inline IppStatus ippsDivC_I(Ipp32fc val, Ipp32fc* pSrcDst, int len) {
  return ippsDivC_32fc_I(val,pSrcDst,len);
}
inline IppStatus ippsDivC_I(Ipp64f val, Ipp64f* pSrcDst, int len) {
  return ippsDivC_64f_I(val,pSrcDst,len);
}
inline IppStatus ippsDivC_I(Ipp64fc val, Ipp64fc* pSrcDst, int len) {
  return ippsDivC_64fc_I(val,pSrcDst,len);
}
inline IppStatus ippsDivC_ISfs(Ipp16s val, Ipp16s* pSrcDst,
       int len, int scaleFactor) {
  return ippsDivC_16s_ISfs(val,pSrcDst,len,scaleFactor);
}
inline IppStatus ippsDivC_ISfs(Ipp8u val, Ipp8u* pSrcDst,
       int len, int scaleFactor) {
  return ippsDivC_8u_ISfs(val,pSrcDst,len,scaleFactor);
}
inline IppStatus ippsDivC_ISfs(Ipp16sc val, Ipp16sc* pSrcDst,
       int len, int scaleFactor) {
  return ippsDivC_16sc_ISfs(val,pSrcDst,len,scaleFactor);
}
inline IppStatus ippsDivCRev(const Ipp16u* pSrc, Ipp16u val,
       Ipp16u* pDst, int len) {
  return ippsDivCRev_16u(pSrc,val,pDst,len);
}
inline IppStatus ippsDivCRev(const Ipp32f* pSrc, Ipp32f val,
      Ipp32f* pDst, int len) {
  return ippsDivCRev_32f(pSrc,val,pDst,len);
}
inline IppStatus ippsDivCRev_I(Ipp16u val, Ipp16u* pSrcDst, int len) {
  return ippsDivCRev_16u_I(val,pSrcDst,len);
}
inline IppStatus ippsDivCRev_I(Ipp32f val, Ipp32f* pSrcDst, int len) {
  return ippsDivCRev_32f_I(val,pSrcDst,len);
}
inline IppStatus ippsSqrt_I(Ipp32f* pSrcDst,int len) {
  return ippsSqrt_32f_I(pSrcDst,len);
}
inline IppStatus ippsSqrt_I(Ipp32fc* pSrcDst,int len) {
  return ippsSqrt_32fc_I(pSrcDst,len);
}
inline IppStatus ippsSqrt_I(Ipp64f* pSrcDst,int len) {
  return ippsSqrt_64f_I(pSrcDst,len);
}
inline IppStatus ippsSqrt_I(Ipp64fc* pSrcDst,int len) {
  return ippsSqrt_64fc_I(pSrcDst,len);
}
inline IppStatus ippsSqrt(const Ipp32f* pSrc,Ipp32f* pDst,int len) {
  return ippsSqrt_32f(pSrc,pDst,len);
}
inline IppStatus ippsSqrt(const Ipp32fc* pSrc,Ipp32fc* pDst,int len) {
  return ippsSqrt_32fc(pSrc,pDst,len);
}
inline IppStatus ippsSqrt(const Ipp64f* pSrc,Ipp64f* pDst,int len) {
  return ippsSqrt_64f(pSrc,pDst,len);
}
inline IppStatus ippsSqrt(const Ipp64fc* pSrc,Ipp64fc* pDst,int len) {
  return ippsSqrt_64fc(pSrc,pDst,len);
}
inline IppStatus ippsSqrt_ISfs(Ipp16s* pSrcDst,int len,int scaleFactor) {
  return ippsSqrt_16s_ISfs(pSrcDst,len,scaleFactor);
}
inline IppStatus ippsSqrt_ISfs(Ipp16sc* pSrcDst,int len,int scaleFactor) {
  return ippsSqrt_16sc_ISfs(pSrcDst,len,scaleFactor);
}
inline IppStatus ippsSqrt_Sfs(const Ipp16s* pSrc,Ipp16s* pDst,int len,
                                   int scaleFactor) {
  return ippsSqrt_16s_Sfs(pSrc,pDst,len,scaleFactor);
}
inline IppStatus ippsSqrt_Sfs(const Ipp16sc* pSrc,Ipp16sc* pDst,int len,
                                    int scaleFactor) {
  return ippsSqrt_16sc_Sfs(pSrc,pDst,len,scaleFactor);
}
inline IppStatus ippsSqrt_ISfs(Ipp64s* pSrcDst,int len,int scaleFactor) {
  return ippsSqrt_64s_ISfs(pSrcDst,len,scaleFactor);
}
inline IppStatus ippsSqrt_Sfs(const Ipp64s* pSrc,Ipp64s* pDst,int len,
                                   int scaleFactor) {
  return ippsSqrt_64s_Sfs(pSrc,pDst,len,scaleFactor);
}
inline IppStatus ippsSqrt_ISfs(Ipp8u* pSrcDst, int len, int scaleFactor) {
  return ippsSqrt_8u_ISfs(pSrcDst,len,scaleFactor);
}
inline IppStatus ippsSqrt_Sfs(const Ipp8u* pSrc, Ipp8u* pDst, int len,
                                  int scaleFactor) {
  return ippsSqrt_8u_Sfs(pSrc,pDst,len,scaleFactor);
}
inline IppStatus ippsSqrt_ISfs(Ipp16u* pSrcDst, int len, int scaleFactor) {
  return ippsSqrt_16u_ISfs(pSrcDst,len,scaleFactor);
}
inline IppStatus ippsSqrt_Sfs(const Ipp16u* pSrc, Ipp16u* pDst, int len,
                                   int scaleFactor) {
  return ippsSqrt_16u_Sfs(pSrc,pDst,len,scaleFactor);
}
inline IppStatus ippsSqrt_Sfs(const Ipp32s* pSrc,Ipp16s* pDst,
        int len, int scaleFactor) {
  return ippsSqrt_32s16s_Sfs(pSrc,pDst,len,scaleFactor);
}
inline IppStatus ippsSqrt_Sfs(const Ipp64s* pSrc,Ipp16s* pDst,
       int len, int scaleFactor) {
  return ippsSqrt_64s16s_Sfs(pSrc,pDst,len,scaleFactor);
}
inline IppStatus ippsCubrt_Sfs( const Ipp32s* pSrc, Ipp16s* pDst, int Len, int sFactor) {
  return ippsCubrt_32s16s_Sfs(pSrc,pDst,Len,sFactor);
}
inline IppStatus ippsCubrt( const Ipp32f* pSrc, Ipp32f* pDst, int Len) {
  return ippsCubrt_32f(pSrc,pDst,Len);
}
inline IppStatus ippsAbs_I(Ipp32f* pSrcDst,int len) {
  return ippsAbs_32f_I(pSrcDst,len);
}
inline IppStatus ippsAbs_I(Ipp64f* pSrcDst,int len) {
  return ippsAbs_64f_I(pSrcDst,len);
}
inline IppStatus ippsAbs_I(Ipp16s* pSrcDst,int len) {
  return ippsAbs_16s_I(pSrcDst,len);
}
inline IppStatus ippsAbs(const Ipp32f* pSrc, Ipp32f* pDst,int len) {
  return ippsAbs_32f(pSrc,pDst,len);
}
inline IppStatus ippsAbs(const Ipp64f* pSrc, Ipp64f* pDst,int len) {
  return ippsAbs_64f(pSrc,pDst,len);
}
inline IppStatus ippsAbs(const Ipp16s* pSrc, Ipp16s* pDst,int len) {
  return ippsAbs_16s(pSrc,pDst,len);
}
inline IppStatus ippsAbs_I(Ipp32s* pSrcDst,int len) {
  return ippsAbs_32s_I(pSrcDst,len);
}
inline IppStatus ippsAbs(const Ipp32s* pSrc, Ipp32s* pDst,int len) {
  return ippsAbs_32s(pSrc,pDst,len);
}
inline IppStatus ippsMagnitude(const Ipp32fc* pSrc,Ipp32f* pDst,int len) {
  return ippsMagnitude_32fc(pSrc,pDst,len);
}
inline IppStatus ippsMagnitude(const Ipp64fc* pSrc,Ipp64f* pDst,int len) {
  return ippsMagnitude_64fc(pSrc,pDst,len);
}
inline IppStatus ippsMagnitude(const Ipp16sc* pSrc,Ipp32f* pDst,int len) {
  return ippsMagnitude_16sc32f(pSrc,pDst,len);
}
inline IppStatus ippsMagnitude_Sfs(const Ipp16sc* pSrc,Ipp16s* pDst,
                                    int len,int scaleFactor) {
  return ippsMagnitude_16sc_Sfs(pSrc,pDst,len,scaleFactor);
}
inline IppStatus ippsMagnitude(const Ipp32f* pSrcRe,const Ipp32f* pSrcIm,
                               Ipp32f* pDst,int len) {
  return ippsMagnitude_32f(pSrcRe,pSrcIm,pDst,len);
}
inline IppStatus ippsMagnitude(const Ipp64f* pSrcRe,const Ipp64f* pSrcIm,
                               Ipp64f* pDst,int len) {
  return ippsMagnitude_64f(pSrcRe,pSrcIm,pDst,len);
}
inline IppStatus ippsMagnitude_Sfs(const Ipp16s* pSrcRe,const Ipp16s* pSrcIm,
                               Ipp16s* pDst,int len,int scaleFactor) {
  return ippsMagnitude_16s_Sfs(pSrcRe,pSrcIm,pDst,len,scaleFactor);
}
inline IppStatus ippsMagnitude_Sfs(const Ipp32sc* pSrc,Ipp32s* pDst,
                                    int len,int scaleFactor) {
  return ippsMagnitude_32sc_Sfs(pSrc,pDst,len,scaleFactor);
}
inline IppStatus ippsMagnitude(const Ipp16s* pSrcRe, const Ipp16s* pSrcIm,
                                                             Ipp32f* pDst, int len) {
  return ippsMagnitude_16s32f(pSrcRe,pSrcIm,pDst,len);
}
inline IppStatus ippsMagSquared_Sfs(const Ipp32sc* pSrc,Ipp32s* pDst, int len, int scaleFactor) {
  return ippsMagSquared_32sc32s_Sfs(pSrc,pDst,len,scaleFactor);
}
inline IppStatus ippsExp_I(Ipp32f* pSrcDst, int len) {
  return ippsExp_32f_I(pSrcDst,len);
}
inline IppStatus ippsExp_I(Ipp64f* pSrcDst, int len) {
  return ippsExp_64f_I(pSrcDst,len);
}
inline IppStatus ippsExp_ISfs(Ipp16s* pSrcDst, int len, int scaleFactor) {
  return ippsExp_16s_ISfs(pSrcDst,len,scaleFactor);
}
inline IppStatus ippsExp_ISfs(Ipp32s* pSrcDst, int len, int scaleFactor) {
  return ippsExp_32s_ISfs(pSrcDst,len,scaleFactor);
}
inline IppStatus ippsExp_ISfs(Ipp64s* pSrcDst, int len, int scaleFactor) {
  return ippsExp_64s_ISfs(pSrcDst,len,scaleFactor);
}
inline IppStatus ippsExp(const Ipp32f* pSrc, Ipp32f* pDst, int len) {
  return ippsExp_32f(pSrc,pDst,len);
}
inline IppStatus ippsExp(const Ipp64f* pSrc, Ipp64f* pDst, int len) {
  return ippsExp_64f(pSrc,pDst,len);
}
inline IppStatus ippsExp_Sfs(const Ipp16s* pSrc, Ipp16s* pDst, int len,
   int scaleFactor) {
  return ippsExp_16s_Sfs(pSrc,pDst,len,scaleFactor);
}
inline IppStatus ippsExp_Sfs(const Ipp32s* pSrc, Ipp32s* pDst, int len,
   int scaleFactor) {
  return ippsExp_32s_Sfs(pSrc,pDst,len,scaleFactor);
}
inline IppStatus ippsExp_Sfs(const Ipp64s* pSrc, Ipp64s* pDst, int len,
   int scaleFactor) {
  return ippsExp_64s_Sfs(pSrc,pDst,len,scaleFactor);
}
inline IppStatus ippsExp(const Ipp32f* pSrc, Ipp64f* pDst, int len) {
  return ippsExp_32f64f(pSrc,pDst,len);
}
inline IppStatus ippsLn_I(Ipp32f* pSrcDst, int len) {
  return ippsLn_32f_I(pSrcDst,len);
}
inline IppStatus ippsLn_I(Ipp64f* pSrcDst, int len) {
  return ippsLn_64f_I(pSrcDst,len);
}
inline IppStatus ippsLn(const Ipp32f* pSrc, Ipp32f* pDst, int len) {
  return ippsLn_32f(pSrc,pDst,len);
}
inline IppStatus ippsLn(const Ipp64f* pSrc, Ipp64f* pDst, int len) {
  return ippsLn_64f(pSrc,pDst,len);
}
inline IppStatus ippsLn(const Ipp64f* pSrc, Ipp32f* pDst, int len) {
  return ippsLn_64f32f(pSrc,pDst,len);
}
inline IppStatus ippsLn_ISfs(Ipp16s* pSrcDst, int len, int scaleFactor) {
  return ippsLn_16s_ISfs(pSrcDst,len,scaleFactor);
}
inline IppStatus ippsLn_Sfs(const Ipp16s* pSrc, Ipp16s* pDst, int len, int scaleFactor) {
  return ippsLn_16s_Sfs(pSrc,pDst,len,scaleFactor);
}
inline IppStatus ippsLn_Sfs( const Ipp32s* pSrc, Ipp16s* pDst, int Len, int scaleFactor) {
  return ippsLn_32s16s_Sfs(pSrc,pDst,Len,scaleFactor);
}
inline IppStatus ippsLn_ISfs( Ipp32s* pSrcDst, int Len, int scaleFactor) {
  return ippsLn_32s_ISfs(pSrcDst,Len,scaleFactor);
}
inline IppStatus ippsLn_Sfs( const Ipp32s* pSrc, Ipp32s* pDst, int Len, int scaleFactor) {
  return ippsLn_32s_Sfs(pSrc,pDst,Len,scaleFactor);
}
inline IppStatus ipps10Log10_ISfs( Ipp32s* pSrcDst, int Len, int scaleFactor) {
  return ipps10Log10_32s_ISfs(pSrcDst,Len,scaleFactor);
}
inline IppStatus ipps10Log10_Sfs( const Ipp32s* pSrc, Ipp32s* pDst, int Len, int scaleFactor) {
  return ipps10Log10_32s_Sfs(pSrc,pDst,Len,scaleFactor);
}
inline IppStatus ippsSumLn(const Ipp32f* pSrc, int len, Ipp32f* pSum) {
  return ippsSumLn_32f(pSrc,len,pSum);
}
inline IppStatus ippsSumLn(const Ipp64f* pSrc, int len, Ipp64f* pSum) {
  return ippsSumLn_64f(pSrc,len,pSum);
}
inline IppStatus ippsSumLn(const Ipp32f* pSrc, int len, Ipp64f* pSum) {
  return ippsSumLn_32f64f(pSrc,len,pSum);
}
inline IppStatus ippsSumLn(const Ipp16s* pSrc, int len, Ipp32f* pSum) {
  return ippsSumLn_16s32f(pSrc,len,pSum);
}
inline IppStatus ippsSortAscend_I(Ipp8u*  pSrcDst, int len) {
  return ippsSortAscend_8u_I(pSrcDst,len);
}
inline IppStatus ippsSortAscend_I(Ipp16s* pSrcDst, int len) {
  return ippsSortAscend_16s_I(pSrcDst,len);
}
inline IppStatus ippsSortAscend_I(Ipp32s* pSrcDst, int len) {
  return ippsSortAscend_32s_I(pSrcDst,len);
}
inline IppStatus ippsSortAscend_I(Ipp32f* pSrcDst, int len) {
  return ippsSortAscend_32f_I(pSrcDst,len);
}
inline IppStatus ippsSortAscend_I(Ipp64f* pSrcDst, int len) {
  return ippsSortAscend_64f_I(pSrcDst,len);
}
inline IppStatus ippsSortDescend_I(Ipp8u*  pSrcDst, int len) {
  return ippsSortDescend_8u_I(pSrcDst,len);
}
inline IppStatus ippsSortDescend_I(Ipp16s* pSrcDst, int len) {
  return ippsSortDescend_16s_I(pSrcDst,len);
}
inline IppStatus ippsSortDescend_I(Ipp32s* pSrcDst, int len) {
  return ippsSortDescend_32s_I(pSrcDst,len);
}
inline IppStatus ippsSortDescend_I(Ipp32f* pSrcDst, int len) {
  return ippsSortDescend_32f_I(pSrcDst,len);
}
inline IppStatus ippsSortDescend_I(Ipp64f* pSrcDst, int len) {
  return ippsSortDescend_64f_I(pSrcDst,len);
}
inline IppStatus ippsSum(const Ipp32f*  pSrc,int len, Ipp32f* pSum,
       IppHintAlgorithm hint=ippAlgHintNone) {
  return ippsSum_32f(pSrc,len,pSum,hint);
}
inline IppStatus ippsSum(const Ipp64f*  pSrc,int len, Ipp64f* pSum) {
  return ippsSum_64f(pSrc,len,pSum);
}
inline IppStatus ippsSum(const Ipp32fc* pSrc,int len, Ipp32fc* pSum,
       IppHintAlgorithm hint=ippAlgHintNone) {
  return ippsSum_32fc(pSrc,len,pSum,hint);
}
inline IppStatus ippsSum_Sfs(const Ipp16s*  pSrc, int len,
                                       Ipp32s*  pSum, int scaleFactor) {
  return ippsSum_16s32s_Sfs(pSrc,len,pSum,scaleFactor);
}
inline IppStatus ippsSum_Sfs(const Ipp16sc* pSrc, int len,
                                       Ipp32sc* pSum, int scaleFactor) {
  return ippsSum_16sc32sc_Sfs(pSrc,len,pSum,scaleFactor);
}
inline IppStatus ippsSum_Sfs(const Ipp16s*  pSrc, int len,
                                       Ipp16s*  pSum, int scaleFactor) {
  return ippsSum_16s_Sfs(pSrc,len,pSum,scaleFactor);
}
inline IppStatus ippsSum_Sfs(const Ipp16sc* pSrc, int len,
                                       Ipp16sc* pSum, int scaleFactor) {
  return ippsSum_16sc_Sfs(pSrc,len,pSum,scaleFactor);
}
inline IppStatus ippsSum_Sfs(const Ipp32s*  pSrc, int len,
                                       Ipp32s*  pSum, int scaleFactor) {
  return ippsSum_32s_Sfs(pSrc,len,pSum,scaleFactor);
}
inline IppStatus ippsSum(const Ipp64fc* pSrc,int len, Ipp64fc* pSum) {
  return ippsSum_64fc(pSrc,len,pSum);
}
inline IppStatus ippsMean(const Ipp32f*  pSrc,int len,Ipp32f*  pMean,
       IppHintAlgorithm hint=ippAlgHintNone) {
  return ippsMean_32f(pSrc,len,pMean,hint);
}
inline IppStatus ippsMean(const Ipp32fc* pSrc,int len,Ipp32fc* pMean,
       IppHintAlgorithm hint=ippAlgHintNone) {
  return ippsMean_32fc(pSrc,len,pMean,hint);
}
inline IppStatus ippsMean(const Ipp64f*  pSrc,int len,Ipp64f*  pMean) {
  return ippsMean_64f(pSrc,len,pMean);
}
inline IppStatus ippsMean_Sfs(const Ipp16s*  pSrc,int len,
                                    Ipp16s*  pMean,int scaleFactor) {
  return ippsMean_16s_Sfs(pSrc,len,pMean,scaleFactor);
}
inline IppStatus ippsMean_Sfs(const Ipp16sc* pSrc,int len,
                                    Ipp16sc* pMean,int scaleFactor) {
  return ippsMean_16sc_Sfs(pSrc,len,pMean,scaleFactor);
}
inline IppStatus ippsMean(const Ipp64fc* pSrc,int len,Ipp64fc* pMean) {
  return ippsMean_64fc(pSrc,len,pMean);
}
inline IppStatus ippsStdDev(const Ipp32f* pSrc,int len,Ipp32f* pStdDev,
       IppHintAlgorithm hint=ippAlgHintNone) {
  return ippsStdDev_32f(pSrc,len,pStdDev,hint);
}
inline IppStatus ippsStdDev(const Ipp64f* pSrc,int len,Ipp64f* pStdDev) {
  return ippsStdDev_64f(pSrc,len,pStdDev);
}
inline IppStatus ippsStdDev_Sfs(const Ipp16s* pSrc,int len,
                                        Ipp32s* pStdDev,int scaleFactor) {
  return ippsStdDev_16s32s_Sfs(pSrc,len,pStdDev,scaleFactor);
}
inline IppStatus ippsStdDev_Sfs(const Ipp16s* pSrc,int len,
                                     Ipp16s* pStdDev,int scaleFactor) {
  return ippsStdDev_16s_Sfs(pSrc,len,pStdDev,scaleFactor);
}
inline IppStatus ippsMax(const Ipp32f* pSrc,int len,Ipp32f* pMax) {
  return ippsMax_32f(pSrc,len,pMax);
}
inline IppStatus ippsMax(const Ipp64f* pSrc,int len,Ipp64f* pMax) {
  return ippsMax_64f(pSrc,len,pMax);
}
inline IppStatus ippsMax(const Ipp16s* pSrc,int len,Ipp16s* pMax) {
  return ippsMax_16s(pSrc,len,pMax);
}
inline IppStatus ippsMaxIndx( const Ipp16s* pSrc, int len, Ipp16s* pMax, int* pIndx ) {
  return ippsMaxIndx_16s(pSrc,len,pMax,pIndx);
}
inline IppStatus ippsMaxIndx( const Ipp32f* pSrc, int len, Ipp32f* pMax, int* pIndx ) {
  return ippsMaxIndx_32f(pSrc,len,pMax,pIndx);
}
inline IppStatus ippsMaxIndx( const Ipp64f* pSrc, int len, Ipp64f* pMax, int* pIndx ) {
  return ippsMaxIndx_64f(pSrc,len,pMax,pIndx);
}
inline IppStatus ippsMin(const Ipp32f* pSrc,int len,Ipp32f* pMin) {
  return ippsMin_32f(pSrc,len,pMin);
}
inline IppStatus ippsMin(const Ipp64f* pSrc,int len,Ipp64f* pMin) {
  return ippsMin_64f(pSrc,len,pMin);
}
inline IppStatus ippsMin(const Ipp16s* pSrc,int len,Ipp16s* pMin) {
  return ippsMin_16s(pSrc,len,pMin);
}
inline IppStatus ippsMinIndx( const Ipp16s* pSrc, int len, Ipp16s* pMin, int* pIndx ) {
  return ippsMinIndx_16s(pSrc,len,pMin,pIndx);
}
inline IppStatus ippsMinIndx( const Ipp32f* pSrc, int len, Ipp32f* pMin, int* pIndx ) {
  return ippsMinIndx_32f(pSrc,len,pMin,pIndx);
}
inline IppStatus ippsMinIndx( const Ipp64f* pSrc, int len, Ipp64f* pMin, int* pIndx ) {
  return ippsMinIndx_64f(pSrc,len,pMin,pIndx);
}
inline IppStatus ippsMinEvery_I(const Ipp16s* pSrc, Ipp16s* pSrcDst, int len) {
  return ippsMinEvery_16s_I(pSrc,pSrcDst,len);
}
inline IppStatus ippsMinEvery_I(const Ipp32s* pSrc, Ipp32s* pSrcDst, int len) {
  return ippsMinEvery_32s_I(pSrc,pSrcDst,len);
}
inline IppStatus ippsMinEvery_I(const Ipp32f* pSrc, Ipp32f* pSrcDst, int len) {
  return ippsMinEvery_32f_I(pSrc,pSrcDst,len);
}
inline IppStatus ippsMaxEvery_I(const Ipp16s* pSrc, Ipp16s* pSrcDst, int len) {
  return ippsMaxEvery_16s_I(pSrc,pSrcDst,len);
}
inline IppStatus ippsMaxEvery_I(const Ipp32s* pSrc, Ipp32s* pSrcDst, int len) {
  return ippsMaxEvery_32s_I(pSrc,pSrcDst,len);
}
inline IppStatus ippsMaxEvery_I(const Ipp32f* pSrc, Ipp32f* pSrcDst, int len) {
  return ippsMaxEvery_32f_I(pSrc,pSrcDst,len);
}
inline IppStatus ippsMinMax(const Ipp64f* pSrc, int len, Ipp64f* pMin, Ipp64f* pMax) {
  return ippsMinMax_64f(pSrc,len,pMin,pMax);
}
inline IppStatus ippsMinMax(const Ipp32f* pSrc, int len, Ipp32f* pMin, Ipp32f* pMax) {
  return ippsMinMax_32f(pSrc,len,pMin,pMax);
}
inline IppStatus ippsMinMax(const Ipp32s* pSrc, int len, Ipp32s* pMin, Ipp32s* pMax) {
  return ippsMinMax_32s(pSrc,len,pMin,pMax);
}
inline IppStatus ippsMinMax(const Ipp32u* pSrc, int len, Ipp32u* pMin, Ipp32u* pMax) {
  return ippsMinMax_32u(pSrc,len,pMin,pMax);
}
inline IppStatus ippsMinMax(const Ipp16s* pSrc, int len, Ipp16s* pMin, Ipp16s* pMax) {
  return ippsMinMax_16s(pSrc,len,pMin,pMax);
}
inline IppStatus ippsMinMax(const Ipp16u* pSrc, int len, Ipp16u* pMin, Ipp16u* pMax) {
  return ippsMinMax_16u(pSrc,len,pMin,pMax);
}
inline IppStatus ippsMinMax(const Ipp8u*  pSrc, int len, Ipp8u*  pMin, Ipp8u*  pMax) {
  return ippsMinMax_8u(pSrc,len,pMin,pMax);
}
inline IppStatus ippsMinMaxIndx(const Ipp64f* pSrc, int len, Ipp64f* pMin, int* pMinIndx,
                                                                   Ipp64f* pMax, int* pMaxIndx) {
  return ippsMinMaxIndx_64f(pSrc,len,pMin,pMinIndx,pMax,pMaxIndx);
}
inline IppStatus ippsMinMaxIndx(const Ipp32f* pSrc, int len, Ipp32f* pMin, int* pMinIndx,
                                                                   Ipp32f* pMax, int* pMaxIndx) {
  return ippsMinMaxIndx_32f(pSrc,len,pMin,pMinIndx,pMax,pMaxIndx);
}
inline IppStatus ippsMinMaxIndx(const Ipp32s* pSrc, int len, Ipp32s* pMin, int* pMinIndx,
                                                                   Ipp32s* pMax, int* pMaxIndx) {
  return ippsMinMaxIndx_32s(pSrc,len,pMin,pMinIndx,pMax,pMaxIndx);
}
inline IppStatus ippsMinMaxIndx(const Ipp32u* pSrc, int len, Ipp32u* pMin, int* pMinIndx,
                                                                   Ipp32u* pMax, int* pMaxIndx) {
  return ippsMinMaxIndx_32u(pSrc,len,pMin,pMinIndx,pMax,pMaxIndx);
}
inline IppStatus ippsMinMaxIndx(const Ipp16s* pSrc, int len, Ipp16s* pMin, int* pMinIndx,
                                                                   Ipp16s* pMax, int* pMaxIndx) {
  return ippsMinMaxIndx_16s(pSrc,len,pMin,pMinIndx,pMax,pMaxIndx);
}
inline IppStatus ippsMinMaxIndx(const Ipp16u* pSrc, int len, Ipp16u* pMin, int* pMinIndx,
                                                                   Ipp16u* pMax, int* pMaxIndx) {
  return ippsMinMaxIndx_16u(pSrc,len,pMin,pMinIndx,pMax,pMaxIndx);
}
inline IppStatus ippsMinMaxIndx(const Ipp8u*  pSrc, int len, Ipp8u*  pMin, int* pMinIndx,
                                                                   Ipp8u*  pMax, int* pMaxIndx) {
  return ippsMinMaxIndx_8u(pSrc,len,pMin,pMinIndx,pMax,pMaxIndx);
}
inline IppStatus ippsMin(const Ipp32s* pSrc, int len, Ipp32s* pMin) {
  return ippsMin_32s(pSrc,len,pMin);
}
inline IppStatus ippsMax(const Ipp32s* pSrc, int len, Ipp32s* pMax) {
  return ippsMax_32s(pSrc,len,pMax);
}
inline IppStatus ippsMinIndx(const Ipp32s* pSrc, int len, Ipp32s* pMin, int* pIndx) {
  return ippsMinIndx_32s(pSrc,len,pMin,pIndx);
}
inline IppStatus ippsMaxIndx(const Ipp32s* pSrc, int len, Ipp32s* pMax, int* pIndx) {
  return ippsMaxIndx_32s(pSrc,len,pMax,pIndx);
}
inline IppStatus ippsMinAbs(const Ipp16s* pSrc, int len, Ipp16s* pMinAbs) {
  return ippsMinAbs_16s(pSrc,len,pMinAbs);
}
inline IppStatus ippsMaxAbs(const Ipp16s* pSrc, int len, Ipp16s* pMaxAbs) {
  return ippsMaxAbs_16s(pSrc,len,pMaxAbs);
}
inline IppStatus ippsMinAbsIndx(const Ipp16s* pSrc, int len, Ipp16s* pMinAbs, int* pIndx) {
  return ippsMinAbsIndx_16s(pSrc,len,pMinAbs,pIndx);
}
inline IppStatus ippsMaxAbsIndx(const Ipp16s* pSrc, int len, Ipp16s* pMaxAbs, int* pIndx) {
  return ippsMaxAbsIndx_16s(pSrc,len,pMaxAbs,pIndx);
}
inline IppStatus ippsMinAbs(const Ipp32s* pSrc, int len, Ipp32s* pMinAbs) {
  return ippsMinAbs_32s(pSrc,len,pMinAbs);
}
inline IppStatus ippsMaxAbs(const Ipp32s* pSrc, int len, Ipp32s* pMaxAbs) {
  return ippsMaxAbs_32s(pSrc,len,pMaxAbs);
}
inline IppStatus ippsMinAbsIndx(const Ipp32s* pSrc, int len, Ipp32s* pMinAbs, int* pIndx) {
  return ippsMinAbsIndx_32s(pSrc,len,pMinAbs,pIndx);
}
inline IppStatus ippsMaxAbsIndx(const Ipp32s* pSrc, int len, Ipp32s* pMaxAbs, int* pIndx) {
  return ippsMaxAbsIndx_32s(pSrc,len,pMaxAbs,pIndx);
}
inline IppStatus ippsPhase(const Ipp64fc* pSrc, Ipp64f* pDst, int len) {
  return ippsPhase_64fc(pSrc,pDst,len);
}
inline IppStatus ippsPhase(const Ipp32fc* pSrc, Ipp32f* pDst, int len) {
  return ippsPhase_32fc(pSrc,pDst,len);
}
inline IppStatus ippsPhase(const Ipp16sc* pSrc, Ipp32f* pDst, int len) {
  return ippsPhase_16sc32f(pSrc,pDst,len);
}
inline IppStatus ippsPhase_Sfs(const Ipp16sc* pSrc, Ipp16s* pDst, int len,
                                                                int scaleFactor) {
  return ippsPhase_16sc_Sfs(pSrc,pDst,len,scaleFactor);
}
inline IppStatus ippsPhase(const Ipp64f* pSrcRe, const Ipp64f* pSrcIm,
                                                            Ipp64f* pDst, int len) {
  return ippsPhase_64f(pSrcRe,pSrcIm,pDst,len);
}
inline IppStatus ippsPhase(const Ipp32f* pSrcRe, const Ipp32f* pSrcIm,
                                                            Ipp32f* pDst, int len) {
  return ippsPhase_32f(pSrcRe,pSrcIm,pDst,len);
}
inline IppStatus ippsPhase_Sfs(const Ipp16s* pSrcRe, const Ipp16s* pSrcIm,
                                           Ipp16s* pDst, int len, int scaleFactor) {
  return ippsPhase_16s_Sfs(pSrcRe,pSrcIm,pDst,len,scaleFactor);
}
inline IppStatus ippsPhase(const Ipp16s* pSrcRe, const Ipp16s* pSrcIm,
                                                            Ipp32f* pDst, int len) {
  return ippsPhase_16s32f(pSrcRe,pSrcIm,pDst,len);
}
inline IppStatus ippsPhase_Sfs(const Ipp32sc* pSrc, Ipp32s* pDst, int len,
                                                                int scaleFactor) {
  return ippsPhase_32sc_Sfs(pSrc,pDst,len,scaleFactor);
}
inline IppStatus ippsMaxOrder(const Ipp64f* pSrc, int len, int* pOrder) {
  return ippsMaxOrder_64f(pSrc,len,pOrder);
}
inline IppStatus ippsMaxOrder(const Ipp32f* pSrc, int len, int* pOrder) {
  return ippsMaxOrder_32f(pSrc,len,pOrder);
}
inline IppStatus ippsMaxOrder(const Ipp32s* pSrc, int len, int* pOrder) {
  return ippsMaxOrder_32s(pSrc,len,pOrder);
}
inline IppStatus ippsMaxOrder(const Ipp16s* pSrc, int len, int* pOrder) {
  return ippsMaxOrder_16s(pSrc,len,pOrder);
}
inline IppStatus ippsArctan_I(      Ipp32f* pSrcDst, int len) {
  return ippsArctan_32f_I(pSrcDst,len);
}
inline IppStatus ippsArctan(const Ipp32f* pSrc, Ipp32f* pDst, int len) {
  return ippsArctan_32f(pSrc,pDst,len);
}
inline IppStatus ippsArctan_I(      Ipp64f* pSrcDst, int len) {
  return ippsArctan_64f_I(pSrcDst,len);
}
inline IppStatus ippsArctan(const Ipp64f* pSrc, Ipp64f* pDst, int len) {
  return ippsArctan_64f(pSrc,pDst,len);
}
inline IppStatus ippsFindNearestOne(Ipp16u inpVal, Ipp16u* pOutVal, int* pOutIndex, const Ipp16u *pTable, int tblLen) {
  return ippsFindNearestOne_16u(inpVal,pOutVal,pOutIndex,pTable,tblLen);
}
inline IppStatus ippsFindNearest(const Ipp16u* pVals, Ipp16u* pOutVals, int* pOutIndexes, int len, const Ipp16u *pTable, int tblLen) {
  return ippsFindNearest_16u(pVals,pOutVals,pOutIndexes,len,pTable,tblLen);
}
inline IppStatus ippsAndC_I(Ipp8u val, Ipp8u* pSrcDst, int len) {
  return ippsAndC_8u_I(val,pSrcDst,len);
}
inline IppStatus ippsAndC(const Ipp8u* pSrc, Ipp8u val, Ipp8u* pDst, int len) {
  return ippsAndC_8u(pSrc,val,pDst,len);
}
inline IppStatus ippsAndC_I(Ipp16u val, Ipp16u* pSrcDst, int len) {
  return ippsAndC_16u_I(val,pSrcDst,len);
}
inline IppStatus ippsAndC(const Ipp16u* pSrc, Ipp16u val, Ipp16u* pDst, int len) {
  return ippsAndC_16u(pSrc,val,pDst,len);
}
inline IppStatus ippsAndC_I(Ipp32u val, Ipp32u* pSrcDst, int len) {
  return ippsAndC_32u_I(val,pSrcDst,len);
}
inline IppStatus ippsAndC(const Ipp32u* pSrc, Ipp32u val, Ipp32u* pDst, int len) {
  return ippsAndC_32u(pSrc,val,pDst,len);
}
inline IppStatus ippsAnd_I(const Ipp8u* pSrc, Ipp8u* pSrcDst, int len) {
  return ippsAnd_8u_I(pSrc,pSrcDst,len);
}
inline IppStatus ippsAnd(const Ipp8u* pSrc1, const Ipp8u* pSrc2, Ipp8u* pDst, int len) {
  return ippsAnd_8u(pSrc1,pSrc2,pDst,len);
}
inline IppStatus ippsAnd_I(const Ipp16u* pSrc, Ipp16u* pSrcDst, int len) {
  return ippsAnd_16u_I(pSrc,pSrcDst,len);
}
inline IppStatus ippsAnd(const Ipp16u* pSrc1, const Ipp16u* pSrc2, Ipp16u* pDst, int len) {
  return ippsAnd_16u(pSrc1,pSrc2,pDst,len);
}
inline IppStatus ippsAnd_I(const Ipp32u* pSrc, Ipp32u* pSrcDst, int len) {
  return ippsAnd_32u_I(pSrc,pSrcDst,len);
}
inline IppStatus ippsAnd(const Ipp32u* pSrc1, const Ipp32u* pSrc2, Ipp32u* pDst, int len) {
  return ippsAnd_32u(pSrc1,pSrc2,pDst,len);
}
inline IppStatus ippsOrC_I(Ipp8u val, Ipp8u* pSrcDst, int len) {
  return ippsOrC_8u_I(val,pSrcDst,len);
}
inline IppStatus ippsOrC(const Ipp8u* pSrc, Ipp8u val, Ipp8u* pDst, int len) {
  return ippsOrC_8u(pSrc,val,pDst,len);
}
inline IppStatus ippsOrC_I(Ipp16u val, Ipp16u* pSrcDst, int len) {
  return ippsOrC_16u_I(val,pSrcDst,len);
}
inline IppStatus ippsOrC(const Ipp16u* pSrc, Ipp16u val, Ipp16u* pDst, int len) {
  return ippsOrC_16u(pSrc,val,pDst,len);
}
inline IppStatus ippsOrC_I(Ipp32u val, Ipp32u* pSrcDst, int len) {
  return ippsOrC_32u_I(val,pSrcDst,len);
}
inline IppStatus ippsOrC(const Ipp32u* pSrc, Ipp32u val, Ipp32u* pDst, int len) {
  return ippsOrC_32u(pSrc,val,pDst,len);
}
inline IppStatus ippsOr_I(const Ipp8u* pSrc, Ipp8u* pSrcDst, int len) {
  return ippsOr_8u_I(pSrc,pSrcDst,len);
}
inline IppStatus ippsOr(const Ipp8u* pSrc1, const Ipp8u* pSrc2, Ipp8u* pDst, int len) {
  return ippsOr_8u(pSrc1,pSrc2,pDst,len);
}
inline IppStatus ippsOr_I(const Ipp16u* pSrc, Ipp16u* pSrcDst, int len) {
  return ippsOr_16u_I(pSrc,pSrcDst,len);
}
inline IppStatus ippsOr(const Ipp16u* pSrc1, const Ipp16u* pSrc2, Ipp16u* pDst, int len) {
  return ippsOr_16u(pSrc1,pSrc2,pDst,len);
}
inline IppStatus ippsOr_I(const Ipp32u* pSrc, Ipp32u* pSrcDst, int len) {
  return ippsOr_32u_I(pSrc,pSrcDst,len);
}
inline IppStatus ippsOr(const Ipp32u* pSrc1, const Ipp32u* pSrc2, Ipp32u* pDst, int len) {
  return ippsOr_32u(pSrc1,pSrc2,pDst,len);
}
inline IppStatus ippsXorC_I(Ipp8u val, Ipp8u* pSrcDst, int len) {
  return ippsXorC_8u_I(val,pSrcDst,len);
}
inline IppStatus ippsXorC(const Ipp8u* pSrc, Ipp8u val, Ipp8u* pDst, int len) {
  return ippsXorC_8u(pSrc,val,pDst,len);
}
inline IppStatus ippsXorC_I(Ipp16u val, Ipp16u* pSrcDst, int len) {
  return ippsXorC_16u_I(val,pSrcDst,len);
}
inline IppStatus ippsXorC(const Ipp16u* pSrc, Ipp16u val, Ipp16u* pDst, int len) {
  return ippsXorC_16u(pSrc,val,pDst,len);
}
inline IppStatus ippsXorC_I(Ipp32u val, Ipp32u* pSrcDst, int len) {
  return ippsXorC_32u_I(val,pSrcDst,len);
}
inline IppStatus ippsXorC(const Ipp32u* pSrc, Ipp32u val, Ipp32u* pDst, int len) {
  return ippsXorC_32u(pSrc,val,pDst,len);
}
inline IppStatus ippsXor_I(const Ipp8u* pSrc, Ipp8u* pSrcDst, int len) {
  return ippsXor_8u_I(pSrc,pSrcDst,len);
}
inline IppStatus ippsXor(const Ipp8u* pSrc1, const Ipp8u* pSrc2, Ipp8u* pDst, int len) {
  return ippsXor_8u(pSrc1,pSrc2,pDst,len);
}
inline IppStatus ippsXor_I(const Ipp16u* pSrc, Ipp16u* pSrcDst, int len) {
  return ippsXor_16u_I(pSrc,pSrcDst,len);
}
inline IppStatus ippsXor(const Ipp16u* pSrc1, const Ipp16u* pSrc2, Ipp16u* pDst, int len) {
  return ippsXor_16u(pSrc1,pSrc2,pDst,len);
}
inline IppStatus ippsXor_I(const Ipp32u* pSrc, Ipp32u* pSrcDst, int len) {
  return ippsXor_32u_I(pSrc,pSrcDst,len);
}
inline IppStatus ippsXor(const Ipp32u* pSrc1, const Ipp32u* pSrc2, Ipp32u* pDst, int len) {
  return ippsXor_32u(pSrc1,pSrc2,pDst,len);
}
inline IppStatus ippsNot_I(Ipp8u* pSrcDst, int len) {
  return ippsNot_8u_I(pSrcDst,len);
}
inline IppStatus ippsNot(const Ipp8u* pSrc, Ipp8u* pDst, int len) {
  return ippsNot_8u(pSrc,pDst,len);
}
inline IppStatus ippsNot_I(Ipp16u* pSrcDst, int len) {
  return ippsNot_16u_I(pSrcDst,len);
}
inline IppStatus ippsNot(const Ipp16u* pSrc, Ipp16u* pDst, int len) {
  return ippsNot_16u(pSrc,pDst,len);
}
inline IppStatus ippsNot_I(Ipp32u* pSrcDst, int len) {
  return ippsNot_32u_I(pSrcDst,len);
}
inline IppStatus ippsNot(const Ipp32u* pSrc, Ipp32u* pDst, int len) {
  return ippsNot_32u(pSrc,pDst,len);
}
inline IppStatus ippsLShiftC_I(int val, Ipp8u* pSrcDst, int len) {
  return ippsLShiftC_8u_I(val,pSrcDst,len);
}
inline IppStatus ippsLShiftC(const Ipp8u* pSrc, int val, Ipp8u* pDst, int len) {
  return ippsLShiftC_8u(pSrc,val,pDst,len);
}
inline IppStatus ippsLShiftC_I(int val, Ipp16u* pSrcDst, int len) {
  return ippsLShiftC_16u_I(val,pSrcDst,len);
}
inline IppStatus ippsLShiftC(const Ipp16u* pSrc, int val, Ipp16u* pDst, int len) {
  return ippsLShiftC_16u(pSrc,val,pDst,len);
}
inline IppStatus ippsLShiftC_I(int val, Ipp16s* pSrcDst, int len) {
  return ippsLShiftC_16s_I(val,pSrcDst,len);
}
inline IppStatus ippsLShiftC(const Ipp16s* pSrc, int val, Ipp16s* pDst, int len) {
  return ippsLShiftC_16s(pSrc,val,pDst,len);
}
inline IppStatus ippsLShiftC_I(int val, Ipp32s* pSrcDst, int len) {
  return ippsLShiftC_32s_I(val,pSrcDst,len);
}
inline IppStatus ippsLShiftC(const Ipp32s* pSrc, int val, Ipp32s* pDst, int len) {
  return ippsLShiftC_32s(pSrc,val,pDst,len);
}
inline IppStatus ippsRShiftC_I(int val, Ipp8u* pSrcDst, int len) {
  return ippsRShiftC_8u_I(val,pSrcDst,len);
}
inline IppStatus ippsRShiftC(const Ipp8u* pSrc, int val, Ipp8u* pDst, int len) {
  return ippsRShiftC_8u(pSrc,val,pDst,len);
}
inline IppStatus ippsRShiftC_I(int val, Ipp16u* pSrcDst, int len) {
  return ippsRShiftC_16u_I(val,pSrcDst,len);
}
inline IppStatus ippsRShiftC(const Ipp16u* pSrc, int val, Ipp16u* pDst, int len) {
  return ippsRShiftC_16u(pSrc,val,pDst,len);
}
inline IppStatus ippsRShiftC_I(int val, Ipp16s* pSrcDst, int len) {
  return ippsRShiftC_16s_I(val,pSrcDst,len);
}
inline IppStatus ippsRShiftC(const Ipp16s* pSrc, int val, Ipp16s* pDst, int len) {
  return ippsRShiftC_16s(pSrc,val,pDst,len);
}
inline IppStatus ippsRShiftC_I(int val, Ipp32s* pSrcDst, int len) {
  return ippsRShiftC_32s_I(val,pSrcDst,len);
}
inline IppStatus ippsRShiftC(const Ipp32s* pSrc, int val, Ipp32s* pDst, int len) {
  return ippsRShiftC_32s(pSrc,val,pDst,len);
}
inline IppStatus ippsDotProd(const Ipp32f* pSrc1,
       const Ipp32f* pSrc2, int len, Ipp32f* pDp) {
  return ippsDotProd_32f(pSrc1,pSrc2,len,pDp);
}
inline IppStatus ippsDotProd(const Ipp32fc* pSrc1,
       const Ipp32fc* pSrc2, int len, Ipp32fc* pDp) {
  return ippsDotProd_32fc(pSrc1,pSrc2,len,pDp);
}
inline IppStatus ippsDotProd(const Ipp32f* pSrc1,
       const Ipp32fc* pSrc2, int len, Ipp32fc* pDp) {
  return ippsDotProd_32f32fc(pSrc1,pSrc2,len,pDp);
}
inline IppStatus ippsDotProd(const Ipp64f* pSrc1,
       const Ipp64f* pSrc2, int len, Ipp64f* pDp) {
  return ippsDotProd_64f(pSrc1,pSrc2,len,pDp);
}
inline IppStatus ippsDotProd(const Ipp64fc* pSrc1,
       const Ipp64fc* pSrc2, int len, Ipp64fc* pDp) {
  return ippsDotProd_64fc(pSrc1,pSrc2,len,pDp);
}
inline IppStatus ippsDotProd(const Ipp64f* pSrc1,
       const Ipp64fc* pSrc2, int len, Ipp64fc* pDp) {
  return ippsDotProd_64f64fc(pSrc1,pSrc2,len,pDp);
}
inline IppStatus ippsDotProd_Sfs(const Ipp16s* pSrc1,
       const Ipp16s* pSrc2, int len, Ipp16s* pDp, int scaleFactor) {
  return ippsDotProd_16s_Sfs(pSrc1,pSrc2,len,pDp,scaleFactor);
}
inline IppStatus ippsDotProd_Sfs(const Ipp16sc* pSrc1,
       const Ipp16sc* pSrc2, int len, Ipp16sc* pDp, int scaleFactor) {
  return ippsDotProd_16sc_Sfs(pSrc1,pSrc2,len,pDp,scaleFactor);
}
inline IppStatus ippsDotProd_Sfs(const Ipp16s* pSrc1,
       const Ipp16sc* pSrc2, int len, Ipp16sc* pDp, int scaleFactor) {
  return ippsDotProd_16s16sc_Sfs(pSrc1,pSrc2,len,pDp,scaleFactor);
}
inline IppStatus ippsDotProd(const Ipp16s*  pSrc1,
       const Ipp16s*  pSrc2, int len, Ipp64s*  pDp) {
  return ippsDotProd_16s64s(pSrc1,pSrc2,len,pDp);
}
inline IppStatus ippsDotProd(const Ipp16sc* pSrc1,
       const Ipp16sc* pSrc2, int len, Ipp64sc* pDp) {
  return ippsDotProd_16sc64sc(pSrc1,pSrc2,len,pDp);
}
inline IppStatus ippsDotProd(const Ipp16s*  pSrc1,
       const Ipp16sc* pSrc2, int len, Ipp64sc* pDp) {
  return ippsDotProd_16s16sc64sc(pSrc1,pSrc2,len,pDp);
}
inline IppStatus ippsDotProd(const Ipp16s*  pSrc1,
       const Ipp16s*  pSrc2, int len, Ipp32f*  pDp) {
  return ippsDotProd_16s32f(pSrc1,pSrc2,len,pDp);
}
inline IppStatus ippsDotProd(const Ipp16sc* pSrc1,
       const Ipp16sc* pSrc2, int len, Ipp32fc* pDp) {
  return ippsDotProd_16sc32fc(pSrc1,pSrc2,len,pDp);
}
inline IppStatus ippsDotProd(const Ipp16s*  pSrc1,
       const Ipp16sc* pSrc2, int len, Ipp32fc* pDp) {
  return ippsDotProd_16s16sc32fc(pSrc1,pSrc2,len,pDp);
}
inline IppStatus ippsDotProd( const Ipp32f* pSrc1, const Ipp32f* pSrc2, int len, Ipp64f* pDp ) {
  return ippsDotProd_32f64f(pSrc1,pSrc2,len,pDp);
}
inline IppStatus ippsDotProd( const Ipp32fc* pSrc1, const Ipp32fc* pSrc2, int len, Ipp64fc* pDp ) {
  return ippsDotProd_32fc64fc(pSrc1,pSrc2,len,pDp);
}
inline IppStatus ippsDotProd( const Ipp32f* pSrc1, const Ipp32fc* pSrc2, int len, Ipp64fc* pDp ) {
  return ippsDotProd_32f32fc64fc(pSrc1,pSrc2,len,pDp);
}
inline IppStatus ippsDotProd_Sfs( const Ipp16s* pSrc1, const Ipp16s* pSrc2,
          int len, Ipp32s* pDp, int scaleFactor ) {
  return ippsDotProd_16s32s_Sfs(pSrc1,pSrc2,len,pDp,scaleFactor);
}
inline IppStatus ippsDotProd_Sfs( const Ipp16sc* pSrc1, const Ipp16sc* pSrc2,
          int len, Ipp32sc* pDp, int scaleFactor ) {
  return ippsDotProd_16sc32sc_Sfs(pSrc1,pSrc2,len,pDp,scaleFactor);
}
inline IppStatus ippsDotProd_Sfs( const Ipp16s* pSrc1, const Ipp16sc* pSrc2,
          int len, Ipp32sc* pDp, int scaleFactor ) {
  return ippsDotProd_16s16sc32sc_Sfs(pSrc1,pSrc2,len,pDp,scaleFactor);
}
inline IppStatus ippsDotProd_Sfs( const Ipp32s* pSrc1, const Ipp32s* pSrc2,
          int len, Ipp32s* pDp, int scaleFactor ) {
  return ippsDotProd_32s_Sfs(pSrc1,pSrc2,len,pDp,scaleFactor);
}
inline IppStatus ippsDotProd_Sfs( const Ipp32sc* pSrc1, const Ipp32sc* pSrc2,
          int len, Ipp32sc* pDp, int scaleFactor ) {
  return ippsDotProd_32sc_Sfs(pSrc1,pSrc2,len,pDp,scaleFactor);
}
inline IppStatus ippsDotProd_Sfs( const Ipp32s* pSrc1, const Ipp32sc* pSrc2,
          int len, Ipp32sc* pDp, int scaleFactor ) {
  return ippsDotProd_32s32sc_Sfs(pSrc1,pSrc2,len,pDp,scaleFactor);
}
inline IppStatus ippsDotProd_Sfs( const Ipp16s* pSrc1, const Ipp32s* pSrc2,
          int len, Ipp32s* pDp, int scaleFactor ) {
  return ippsDotProd_16s32s32s_Sfs(pSrc1,pSrc2,len,pDp,scaleFactor);
}
inline IppStatus ippsPowerSpectr(const Ipp64fc* pSrc, Ipp64f* pDst, int len) {
  return ippsPowerSpectr_64fc(pSrc,pDst,len);
}
inline IppStatus ippsPowerSpectr(const Ipp32fc* pSrc, Ipp32f* pDst, int len) {
  return ippsPowerSpectr_32fc(pSrc,pDst,len);
}
inline IppStatus ippsPowerSpectr_Sfs(const Ipp16sc* pSrc, Ipp16s* pDst,
                                                              int len, int scaleFactor) {
  return ippsPowerSpectr_16sc_Sfs(pSrc,pDst,len,scaleFactor);
}
inline IppStatus ippsPowerSpectr(const Ipp16sc* pSrc, Ipp32f* pDst,
                                                                           int len) {
  return ippsPowerSpectr_16sc32f(pSrc,pDst,len);
}
inline IppStatus ippsPowerSpectr(const Ipp64f* pSrcRe, const Ipp64f* pSrcIm,
                                                          Ipp64f* pDst, int len) {
  return ippsPowerSpectr_64f(pSrcRe,pSrcIm,pDst,len);
}
inline IppStatus ippsPowerSpectr(const Ipp32f* pSrcRe, const Ipp32f* pSrcIm,
                                                          Ipp32f* pDst, int len) {
  return ippsPowerSpectr_32f(pSrcRe,pSrcIm,pDst,len);
}
inline IppStatus ippsPowerSpectr_Sfs(const Ipp16s* pSrcRe, const Ipp16s* pSrcIm,
                                                Ipp16s* pDst, int len, int scaleFactor) {
  return ippsPowerSpectr_16s_Sfs(pSrcRe,pSrcIm,pDst,len,scaleFactor);
}
inline IppStatus ippsPowerSpectr(const Ipp16s* pSrcRe, const Ipp16s* pSrcIm,
                                                             Ipp32f* pDst, int len) {
  return ippsPowerSpectr_16s32f(pSrcRe,pSrcIm,pDst,len);
}
inline IppStatus ippsNormalize(const Ipp64fc* pSrc, Ipp64fc* pDst,
       int len, Ipp64fc vsub, Ipp64f vdiv) {
  return ippsNormalize_64fc(pSrc,pDst,len,vsub,vdiv);
}
inline IppStatus ippsNormalize(const Ipp32fc* pSrc, Ipp32fc* pDst,
       int len, Ipp32fc vsub, Ipp32f vdiv) {
  return ippsNormalize_32fc(pSrc,pDst,len,vsub,vdiv);
}
inline IppStatus ippsNormalize_Sfs(const Ipp16sc* pSrc, Ipp16sc* pDst,
       int len, Ipp16sc vsub, int vdiv, int scaleFactor) {
  return ippsNormalize_16sc_Sfs(pSrc,pDst,len,vsub,vdiv,scaleFactor);
}
inline IppStatus ippsNormalize(const Ipp64f* pSrc, Ipp64f* pDst, int len,
       Ipp64f vsub, Ipp64f vdiv) {
  return ippsNormalize_64f(pSrc,pDst,len,vsub,vdiv);
}
inline IppStatus ippsNormalize(const Ipp32f* pSrc, Ipp32f* pDst, int len,
       Ipp32f vsub, Ipp32f vdiv) {
  return ippsNormalize_32f(pSrc,pDst,len,vsub,vdiv);
}
inline IppStatus ippsNormalize_Sfs(const Ipp16s* pSrc, Ipp16s* pDst,
       int len, Ipp16s vsub, int vdiv, int scaleFactor ) {
  return ippsNormalize_16s_Sfs(pSrc,pDst,len,vsub,vdiv,scaleFactor);
}
inline IppStatus ippsFFTFwd_CToC( const Ipp32fc* pSrc, Ipp32fc* pDst,
                     const IppsFFTSpec_C_32fc* pFFTSpec, Ipp8u* pBuffer ) {
  return ippsFFTFwd_CToC_32fc(pSrc,pDst,pFFTSpec,pBuffer);
}
inline IppStatus ippsFFTInv_CToC( const Ipp32fc* pSrc, Ipp32fc* pDst,
                     const IppsFFTSpec_C_32fc* pFFTSpec, Ipp8u* pBuffer ) {
  return ippsFFTInv_CToC_32fc(pSrc,pDst,pFFTSpec,pBuffer);
}
inline IppStatus ippsFFTFwd_CToC( const Ipp32f* pSrcRe, const Ipp32f* pSrcIm,
                     Ipp32f* pDstRe, Ipp32f* pDstIm,
                     const IppsFFTSpec_C_32f* pFFTSpec, Ipp8u* pBuffer ) {
  return ippsFFTFwd_CToC_32f(pSrcRe,pSrcIm,pDstRe,pDstIm,pFFTSpec,pBuffer);
}
inline IppStatus ippsFFTInv_CToC( const Ipp32f* pSrcRe, const Ipp32f* pSrcIm,
                     Ipp32f* pDstRe, Ipp32f* pDstIm,
                     const IppsFFTSpec_C_32f* pFFTSpec, Ipp8u* pBuffer ) {
  return ippsFFTInv_CToC_32f(pSrcRe,pSrcIm,pDstRe,pDstIm,pFFTSpec,pBuffer);
}
inline IppStatus ippsFFTFwd_CToC_I( Ipp32fc* pSrcDst,
                     const IppsFFTSpec_C_32fc* pFFTSpec, Ipp8u* pBuffer ) {
  return ippsFFTFwd_CToC_32fc_I(pSrcDst,pFFTSpec,pBuffer);
}
inline IppStatus ippsFFTInv_CToC_I( Ipp32fc* pSrcDst,
                     const IppsFFTSpec_C_32fc* pFFTSpec, Ipp8u* pBuffer ) {
  return ippsFFTInv_CToC_32fc_I(pSrcDst,pFFTSpec,pBuffer);
}
inline IppStatus ippsFFTFwd_CToC_I( Ipp32f* pSrcDstRe, Ipp32f* pSrcDstIm,
                     const IppsFFTSpec_C_32f* pFFTSpec, Ipp8u* pBuffer ) {
  return ippsFFTFwd_CToC_32f_I(pSrcDstRe,pSrcDstIm,pFFTSpec,pBuffer);
}
inline IppStatus ippsFFTInv_CToC_I( Ipp32f* pSrcDstRe, Ipp32f* pSrcDstIm,
                     const IppsFFTSpec_C_32f* pFFTSpec, Ipp8u* pBuffer ) {
  return ippsFFTInv_CToC_32f_I(pSrcDstRe,pSrcDstIm,pFFTSpec,pBuffer);
}
inline IppStatus ippsFFTFwd_CToC( const Ipp64fc* pSrc, Ipp64fc* pDst,
                     const IppsFFTSpec_C_64fc* pFFTSpec, Ipp8u* pBuffer ) {
  return ippsFFTFwd_CToC_64fc(pSrc,pDst,pFFTSpec,pBuffer);
}
inline IppStatus ippsFFTInv_CToC( const Ipp64fc* pSrc, Ipp64fc* pDst,
                     const IppsFFTSpec_C_64fc* pFFTSpec, Ipp8u* pBuffer ) {
  return ippsFFTInv_CToC_64fc(pSrc,pDst,pFFTSpec,pBuffer);
}
inline IppStatus ippsFFTFwd_CToC( const Ipp64f* pSrcRe, const Ipp64f* pSrcIm,
                     Ipp64f* pDstRe, Ipp64f* pDstIm,
                     const IppsFFTSpec_C_64f* pFFTSpec, Ipp8u* pBuffer ) {
  return ippsFFTFwd_CToC_64f(pSrcRe,pSrcIm,pDstRe,pDstIm,pFFTSpec,pBuffer);
}
inline IppStatus ippsFFTInv_CToC( const Ipp64f* pSrcRe, const Ipp64f* pSrcIm,
                     Ipp64f* pDstRe, Ipp64f* pDstIm,
                     const IppsFFTSpec_C_64f* pFFTSpec, Ipp8u* pBuffer ) {
  return ippsFFTInv_CToC_64f(pSrcRe,pSrcIm,pDstRe,pDstIm,pFFTSpec,pBuffer);
}
inline IppStatus ippsFFTFwd_CToC_I( Ipp64fc* pSrcDst,
                     const IppsFFTSpec_C_64fc* pFFTSpec, Ipp8u* pBuffer ) {
  return ippsFFTFwd_CToC_64fc_I(pSrcDst,pFFTSpec,pBuffer);
}
inline IppStatus ippsFFTInv_CToC_I( Ipp64fc* pSrcDst,
                     const IppsFFTSpec_C_64fc* pFFTSpec, Ipp8u* pBuffer ) {
  return ippsFFTInv_CToC_64fc_I(pSrcDst,pFFTSpec,pBuffer);
}
inline IppStatus ippsFFTFwd_CToC_I( Ipp64f* pSrcDstRe, Ipp64f* pSrcDstIm,
                     const IppsFFTSpec_C_64f* pFFTSpec, Ipp8u* pBuffer ) {
  return ippsFFTFwd_CToC_64f_I(pSrcDstRe,pSrcDstIm,pFFTSpec,pBuffer);
}
inline IppStatus ippsFFTInv_CToC_I( Ipp64f* pSrcDstRe, Ipp64f* pSrcDstIm,
                     const IppsFFTSpec_C_64f* pFFTSpec, Ipp8u* pBuffer ) {
  return ippsFFTInv_CToC_64f_I(pSrcDstRe,pSrcDstIm,pFFTSpec,pBuffer);
}
inline IppStatus ippsFFTFwd_CToC_Sfs( const Ipp16sc* pSrc, Ipp16sc* pDst,
                     const IppsFFTSpec_C_16sc* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
  return ippsFFTFwd_CToC_16sc_Sfs(pSrc,pDst,pFFTSpec,scaleFactor,pBuffer);
}
inline IppStatus ippsFFTInv_CToC_Sfs( const Ipp16sc* pSrc, Ipp16sc* pDst,
                     const IppsFFTSpec_C_16sc* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
  return ippsFFTInv_CToC_16sc_Sfs(pSrc,pDst,pFFTSpec,scaleFactor,pBuffer);
}
inline IppStatus ippsFFTFwd_CToC_Sfs( const Ipp16s* pSrcRe, const Ipp16s* pSrcIm,
                     Ipp16s* pDstRe, Ipp16s* pDstIm,
                     const IppsFFTSpec_C_16s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
  return ippsFFTFwd_CToC_16s_Sfs(pSrcRe,pSrcIm,pDstRe,pDstIm,pFFTSpec,scaleFactor,pBuffer);
}
inline IppStatus ippsFFTInv_CToC_Sfs( const Ipp16s* pSrcRe, const Ipp16s* pSrcIm,
                     Ipp16s* pDstRe, Ipp16s* pDstIm,
                     const IppsFFTSpec_C_16s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
  return ippsFFTInv_CToC_16s_Sfs(pSrcRe,pSrcIm,pDstRe,pDstIm,pFFTSpec,scaleFactor,pBuffer);
}
inline IppStatus ippsFFTFwd_CToC_ISfs( Ipp16sc* pSrcDst,
                     const IppsFFTSpec_C_16sc* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
  return ippsFFTFwd_CToC_16sc_ISfs(pSrcDst,pFFTSpec,scaleFactor,pBuffer);
}
inline IppStatus ippsFFTInv_CToC_ISfs( Ipp16sc* pSrcDst,
                     const IppsFFTSpec_C_16sc* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
  return ippsFFTInv_CToC_16sc_ISfs(pSrcDst,pFFTSpec,scaleFactor,pBuffer);
}
inline IppStatus ippsFFTFwd_CToC_ISfs( Ipp16s* pSrcDstRe, Ipp16s* pSrcDstIm,
                     const IppsFFTSpec_C_16s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
  return ippsFFTFwd_CToC_16s_ISfs(pSrcDstRe,pSrcDstIm,pFFTSpec,scaleFactor,pBuffer);
}
inline IppStatus ippsFFTInv_CToC_ISfs( Ipp16s* pSrcDstRe, Ipp16s* pSrcDstIm,
                     const IppsFFTSpec_C_16s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
  return ippsFFTInv_CToC_16s_ISfs(pSrcDstRe,pSrcDstIm,pFFTSpec,scaleFactor,pBuffer);
}
inline IppStatus ippsFFTFwd_CToC_Sfs( const Ipp32sc* pSrc, Ipp32sc* pDst,
                     const IppsFFTSpec_C_32sc* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
  return ippsFFTFwd_CToC_32sc_Sfs(pSrc,pDst,pFFTSpec,scaleFactor,pBuffer);
}
inline IppStatus ippsFFTInv_CToC_Sfs( const Ipp32sc* pSrc, Ipp32sc* pDst,
                     const IppsFFTSpec_C_32sc* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
  return ippsFFTInv_CToC_32sc_Sfs(pSrc,pDst,pFFTSpec,scaleFactor,pBuffer);
}
inline IppStatus ippsFFTFwd_CToC_Sfs( const Ipp32s* pSrcRe, const Ipp32s* pSrcIm,
                     Ipp32s* pDstRe, Ipp32s* pDstIm,
                     const IppsFFTSpec_C_32s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
  return ippsFFTFwd_CToC_32s_Sfs(pSrcRe,pSrcIm,pDstRe,pDstIm,pFFTSpec,scaleFactor,pBuffer);
}
inline IppStatus ippsFFTInv_CToC_Sfs( const Ipp32s* pSrcRe, const Ipp32s* pSrcIm,
                     Ipp32s* pDstRe, Ipp32s* pDstIm,
                     const IppsFFTSpec_C_32s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
  return ippsFFTInv_CToC_32s_Sfs(pSrcRe,pSrcIm,pDstRe,pDstIm,pFFTSpec,scaleFactor,pBuffer);
}
inline IppStatus ippsFFTFwd_CToC_ISfs( Ipp32sc* pSrcDst,
                     const IppsFFTSpec_C_32sc* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
  return ippsFFTFwd_CToC_32sc_ISfs(pSrcDst,pFFTSpec,scaleFactor,pBuffer);
}
inline IppStatus ippsFFTInv_CToC_ISfs( Ipp32sc* pSrcDst,
                     const IppsFFTSpec_C_32sc* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
  return ippsFFTInv_CToC_32sc_ISfs(pSrcDst,pFFTSpec,scaleFactor,pBuffer);
}
inline IppStatus ippsFFTFwd_CToC_ISfs( Ipp32s* pSrcDstRe, Ipp32s* pSrcDstIm,
                     const IppsFFTSpec_C_32s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
  return ippsFFTFwd_CToC_32s_ISfs(pSrcDstRe,pSrcDstIm,pFFTSpec,scaleFactor,pBuffer);
}
inline IppStatus ippsFFTInv_CToC_ISfs( Ipp32s* pSrcDstRe, Ipp32s* pSrcDstIm,
                     const IppsFFTSpec_C_32s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
  return ippsFFTInv_CToC_32s_ISfs(pSrcDstRe,pSrcDstIm,pFFTSpec,scaleFactor,pBuffer);
}
inline IppStatus ippsFFTFwd_RToPerm( const Ipp32f* pSrc, Ipp32f* pDst,
                     const IppsFFTSpec_R_32f* pFFTSpec, Ipp8u* pBuffer ) {
  return ippsFFTFwd_RToPerm_32f(pSrc,pDst,pFFTSpec,pBuffer);
}
inline IppStatus ippsFFTFwd_RToPack( const Ipp32f* pSrc, Ipp32f* pDst,
                     const IppsFFTSpec_R_32f* pFFTSpec, Ipp8u* pBuffer ) {
  return ippsFFTFwd_RToPack_32f(pSrc,pDst,pFFTSpec,pBuffer);
}
inline IppStatus ippsFFTFwd_RToCCS( const Ipp32f* pSrc, Ipp32f* pDst,
                     const IppsFFTSpec_R_32f* pFFTSpec, Ipp8u* pBuffer ) {
  return ippsFFTFwd_RToCCS_32f(pSrc,pDst,pFFTSpec,pBuffer);
}
inline IppStatus ippsFFTInv_PermToR( const Ipp32f* pSrc, Ipp32f* pDst,
                     const IppsFFTSpec_R_32f* pFFTSpec, Ipp8u* pBuffer ) {
  return ippsFFTInv_PermToR_32f(pSrc,pDst,pFFTSpec,pBuffer);
}
inline IppStatus ippsFFTInv_PackToR( const Ipp32f* pSrc, Ipp32f* pDst,
                     const IppsFFTSpec_R_32f* pFFTSpec, Ipp8u* pBuffer ) {
  return ippsFFTInv_PackToR_32f(pSrc,pDst,pFFTSpec,pBuffer);
}
inline IppStatus ippsFFTInv_CCSToR( const Ipp32f* pSrc, Ipp32f* pDst,
                     const IppsFFTSpec_R_32f* pFFTSpec, Ipp8u* pBuffer ) {
  return ippsFFTInv_CCSToR_32f(pSrc,pDst,pFFTSpec,pBuffer);
}
inline IppStatus ippsFFTFwd_RToPerm_I( Ipp32f* pSrcDst,
                     const IppsFFTSpec_R_32f* pFFTSpec, Ipp8u* pBuffer ) {
  return ippsFFTFwd_RToPerm_32f_I(pSrcDst,pFFTSpec,pBuffer);
}
inline IppStatus ippsFFTFwd_RToPack_I( Ipp32f* pSrcDst,
                     const IppsFFTSpec_R_32f* pFFTSpec, Ipp8u* pBuffer ) {
  return ippsFFTFwd_RToPack_32f_I(pSrcDst,pFFTSpec,pBuffer);
}
inline IppStatus ippsFFTFwd_RToCCS_I( Ipp32f* pSrcDst,
                     const IppsFFTSpec_R_32f* pFFTSpec, Ipp8u* pBuffer ) {
  return ippsFFTFwd_RToCCS_32f_I(pSrcDst,pFFTSpec,pBuffer);
}
inline IppStatus ippsFFTInv_PermToR_I( Ipp32f* pSrcDst,
                     const IppsFFTSpec_R_32f* pFFTSpec, Ipp8u* pBuffer ) {
  return ippsFFTInv_PermToR_32f_I(pSrcDst,pFFTSpec,pBuffer);
}
inline IppStatus ippsFFTInv_PackToR_I( Ipp32f* pSrcDst,
                     const IppsFFTSpec_R_32f* pFFTSpec, Ipp8u* pBuffer ) {
  return ippsFFTInv_PackToR_32f_I(pSrcDst,pFFTSpec,pBuffer);
}
inline IppStatus ippsFFTInv_CCSToR_I( Ipp32f* pSrcDst,
                     const IppsFFTSpec_R_32f* pFFTSpec, Ipp8u* pBuffer ) {
  return ippsFFTInv_CCSToR_32f_I(pSrcDst,pFFTSpec,pBuffer);
}
inline IppStatus ippsFFTFwd_RToPerm( const Ipp64f* pSrc, Ipp64f* pDst,
                     const IppsFFTSpec_R_64f* pFFTSpec, Ipp8u* pBuffer ) {
  return ippsFFTFwd_RToPerm_64f(pSrc,pDst,pFFTSpec,pBuffer);
}
inline IppStatus ippsFFTFwd_RToPack( const Ipp64f* pSrc, Ipp64f* pDst,
                     const IppsFFTSpec_R_64f* pFFTSpec, Ipp8u* pBuffer ) {
  return ippsFFTFwd_RToPack_64f(pSrc,pDst,pFFTSpec,pBuffer);
}
inline IppStatus ippsFFTFwd_RToCCS( const Ipp64f* pSrc, Ipp64f* pDst,
                     const IppsFFTSpec_R_64f* pFFTSpec, Ipp8u* pBuffer ) {
  return ippsFFTFwd_RToCCS_64f(pSrc,pDst,pFFTSpec,pBuffer);
}
inline IppStatus ippsFFTInv_PermToR( const Ipp64f* pSrc, Ipp64f* pDst,
                     const IppsFFTSpec_R_64f* pFFTSpec, Ipp8u* pBuffer ) {
  return ippsFFTInv_PermToR_64f(pSrc,pDst,pFFTSpec,pBuffer);
}
inline IppStatus ippsFFTInv_PackToR( const Ipp64f* pSrc, Ipp64f* pDst,
                     const IppsFFTSpec_R_64f* pFFTSpec, Ipp8u* pBuffer ) {
  return ippsFFTInv_PackToR_64f(pSrc,pDst,pFFTSpec,pBuffer);
}
inline IppStatus ippsFFTInv_CCSToR( const Ipp64f* pSrc, Ipp64f* pDst,
                     const IppsFFTSpec_R_64f* pFFTSpec, Ipp8u* pBuffer ) {
  return ippsFFTInv_CCSToR_64f(pSrc,pDst,pFFTSpec,pBuffer);
}
inline IppStatus ippsFFTFwd_RToPerm_I( Ipp64f* pSrcDst,
                     const IppsFFTSpec_R_64f* pFFTSpec, Ipp8u* pBuffer ) {
  return ippsFFTFwd_RToPerm_64f_I(pSrcDst,pFFTSpec,pBuffer);
}
inline IppStatus ippsFFTFwd_RToPack_I( Ipp64f* pSrcDst,
                     const IppsFFTSpec_R_64f* pFFTSpec, Ipp8u* pBuffer ) {
  return ippsFFTFwd_RToPack_64f_I(pSrcDst,pFFTSpec,pBuffer);
}
inline IppStatus ippsFFTFwd_RToCCS_I( Ipp64f* pSrcDst,
                     const IppsFFTSpec_R_64f* pFFTSpec, Ipp8u* pBuffer ) {
  return ippsFFTFwd_RToCCS_64f_I(pSrcDst,pFFTSpec,pBuffer);
}
inline IppStatus ippsFFTInv_PermToR_I( Ipp64f* pSrcDst,
                     const IppsFFTSpec_R_64f* pFFTSpec, Ipp8u* pBuffer ) {
  return ippsFFTInv_PermToR_64f_I(pSrcDst,pFFTSpec,pBuffer);
}
inline IppStatus ippsFFTInv_PackToR_I( Ipp64f* pSrcDst,
                     const IppsFFTSpec_R_64f* pFFTSpec, Ipp8u* pBuffer ) {
  return ippsFFTInv_PackToR_64f_I(pSrcDst,pFFTSpec,pBuffer);
}
inline IppStatus ippsFFTInv_CCSToR_I( Ipp64f* pSrcDst,
                     const IppsFFTSpec_R_64f* pFFTSpec, Ipp8u* pBuffer ) {
  return ippsFFTInv_CCSToR_64f_I(pSrcDst,pFFTSpec,pBuffer);
}
inline IppStatus ippsFFTFwd_RToPerm_Sfs( const Ipp16s* pSrc, Ipp16s* pDst,
                     const IppsFFTSpec_R_16s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
  return ippsFFTFwd_RToPerm_16s_Sfs(pSrc,pDst,pFFTSpec,scaleFactor,pBuffer);
}
inline IppStatus ippsFFTFwd_RToPack_Sfs( const Ipp16s* pSrc, Ipp16s* pDst,
                     const IppsFFTSpec_R_16s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
  return ippsFFTFwd_RToPack_16s_Sfs(pSrc,pDst,pFFTSpec,scaleFactor,pBuffer);
}
inline IppStatus ippsFFTFwd_RToCCS_Sfs( const Ipp16s* pSrc, Ipp16s* pDst,
                     const IppsFFTSpec_R_16s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
  return ippsFFTFwd_RToCCS_16s_Sfs(pSrc,pDst,pFFTSpec,scaleFactor,pBuffer);
}
inline IppStatus ippsFFTInv_PermToR_Sfs( const Ipp16s* pSrc, Ipp16s* pDst,
                     const IppsFFTSpec_R_16s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
  return ippsFFTInv_PermToR_16s_Sfs(pSrc,pDst,pFFTSpec,scaleFactor,pBuffer);
}
inline IppStatus ippsFFTInv_PackToR_Sfs( const Ipp16s* pSrc, Ipp16s* pDst,
                     const IppsFFTSpec_R_16s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
  return ippsFFTInv_PackToR_16s_Sfs(pSrc,pDst,pFFTSpec,scaleFactor,pBuffer);
}
inline IppStatus ippsFFTInv_CCSToR_Sfs( const Ipp16s* pSrc, Ipp16s* pDst,
                     const IppsFFTSpec_R_16s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
  return ippsFFTInv_CCSToR_16s_Sfs(pSrc,pDst,pFFTSpec,scaleFactor,pBuffer);
}
inline IppStatus ippsFFTFwd_RToPerm_ISfs( Ipp16s* pSrcDst,
                     const IppsFFTSpec_R_16s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
  return ippsFFTFwd_RToPerm_16s_ISfs(pSrcDst,pFFTSpec,scaleFactor,pBuffer);
}
inline IppStatus ippsFFTFwd_RToPack_ISfs( Ipp16s* pSrcDst,
                     const IppsFFTSpec_R_16s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
  return ippsFFTFwd_RToPack_16s_ISfs(pSrcDst,pFFTSpec,scaleFactor,pBuffer);
}
inline IppStatus ippsFFTFwd_RToCCS_ISfs( Ipp16s* pSrcDst,
                     const IppsFFTSpec_R_16s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
  return ippsFFTFwd_RToCCS_16s_ISfs(pSrcDst,pFFTSpec,scaleFactor,pBuffer);
}
inline IppStatus ippsFFTInv_PermToR_ISfs( Ipp16s* pSrcDst,
                     const IppsFFTSpec_R_16s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
  return ippsFFTInv_PermToR_16s_ISfs(pSrcDst,pFFTSpec,scaleFactor,pBuffer);
}
inline IppStatus ippsFFTInv_PackToR_ISfs( Ipp16s* pSrcDst,
                     const IppsFFTSpec_R_16s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
  return ippsFFTInv_PackToR_16s_ISfs(pSrcDst,pFFTSpec,scaleFactor,pBuffer);
}
inline IppStatus ippsFFTInv_CCSToR_ISfs( Ipp16s* pSrcDst,
                     const IppsFFTSpec_R_16s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
  return ippsFFTInv_CCSToR_16s_ISfs(pSrcDst,pFFTSpec,scaleFactor,pBuffer);
}
inline IppStatus ippsFFTFwd_RToPerm_Sfs( const Ipp32s* pSrc, Ipp32s* pDst,
                     const IppsFFTSpec_R_32s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
  return ippsFFTFwd_RToPerm_32s_Sfs(pSrc,pDst,pFFTSpec,scaleFactor,pBuffer);
}
inline IppStatus ippsFFTFwd_RToPack_Sfs( const Ipp32s* pSrc, Ipp32s* pDst,
                     const IppsFFTSpec_R_32s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
  return ippsFFTFwd_RToPack_32s_Sfs(pSrc,pDst,pFFTSpec,scaleFactor,pBuffer);
}
inline IppStatus ippsFFTFwd_RToCCS_Sfs( const Ipp32s* pSrc, Ipp32s* pDst,
                     const IppsFFTSpec_R_32s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
  return ippsFFTFwd_RToCCS_32s_Sfs(pSrc,pDst,pFFTSpec,scaleFactor,pBuffer);
}
inline IppStatus ippsFFTInv_PermToR_Sfs( const Ipp32s* pSrc, Ipp32s* pDst,
                     const IppsFFTSpec_R_32s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
  return ippsFFTInv_PermToR_32s_Sfs(pSrc,pDst,pFFTSpec,scaleFactor,pBuffer);
}
inline IppStatus ippsFFTInv_PackToR_Sfs( const Ipp32s* pSrc, Ipp32s* pDst,
                     const IppsFFTSpec_R_32s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
  return ippsFFTInv_PackToR_32s_Sfs(pSrc,pDst,pFFTSpec,scaleFactor,pBuffer);
}
inline IppStatus ippsFFTInv_CCSToR_Sfs( const Ipp32s* pSrc, Ipp32s* pDst,
                     const IppsFFTSpec_R_32s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
  return ippsFFTInv_CCSToR_32s_Sfs(pSrc,pDst,pFFTSpec,scaleFactor,pBuffer);
}
inline IppStatus ippsFFTFwd_RToPerm_ISfs( Ipp32s* pSrcDst,
                     const IppsFFTSpec_R_32s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
  return ippsFFTFwd_RToPerm_32s_ISfs(pSrcDst,pFFTSpec,scaleFactor,pBuffer);
}
inline IppStatus ippsFFTFwd_RToPack_ISfs( Ipp32s* pSrcDst,
                     const IppsFFTSpec_R_32s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
  return ippsFFTFwd_RToPack_32s_ISfs(pSrcDst,pFFTSpec,scaleFactor,pBuffer);
}
inline IppStatus ippsFFTFwd_RToCCS_ISfs( Ipp32s* pSrcDst,
                     const IppsFFTSpec_R_32s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
  return ippsFFTFwd_RToCCS_32s_ISfs(pSrcDst,pFFTSpec,scaleFactor,pBuffer);
}
inline IppStatus ippsFFTInv_PermToR_ISfs( Ipp32s* pSrcDst,
                     const IppsFFTSpec_R_32s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
  return ippsFFTInv_PermToR_32s_ISfs(pSrcDst,pFFTSpec,scaleFactor,pBuffer);
}
inline IppStatus ippsFFTInv_PackToR_ISfs( Ipp32s* pSrcDst,
                     const IppsFFTSpec_R_32s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
  return ippsFFTInv_PackToR_32s_ISfs(pSrcDst,pFFTSpec,scaleFactor,pBuffer);
}
inline IppStatus ippsFFTInv_CCSToR_ISfs( Ipp32s* pSrcDst,
                     const IppsFFTSpec_R_32s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
  return ippsFFTInv_CCSToR_32s_ISfs(pSrcDst,pFFTSpec,scaleFactor,pBuffer);
}
inline IppStatus ippsFFTFwd_RToCCS_Sfs( const Ipp16s* pSrc, Ipp32s* pDst,
                     const IppsFFTSpec_R_16s32s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
  return ippsFFTFwd_RToCCS_16s32s_Sfs(pSrc,pDst,pFFTSpec,scaleFactor,pBuffer);
}
inline IppStatus ippsFFTInv_CCSToR_Sfs( const Ipp32s* pSrc, Ipp16s* pDst,
                     const IppsFFTSpec_R_16s32s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
  return ippsFFTInv_CCSToR_32s16s_Sfs(pSrc,pDst,pFFTSpec,scaleFactor,pBuffer);
}
inline IppStatus ippsDFTFwd_CToC_Sfs( const Ipp16sc* pSrc, Ipp16sc* pDst,
                     const IppsDFTSpec_C_16sc* pDFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
  return ippsDFTFwd_CToC_16sc_Sfs(pSrc,pDst,pDFTSpec,scaleFactor,pBuffer);
}
inline IppStatus ippsDFTInv_CToC_Sfs( const Ipp16sc* pSrc, Ipp16sc* pDst,
                     const IppsDFTSpec_C_16sc* pDFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
  return ippsDFTInv_CToC_16sc_Sfs(pSrc,pDst,pDFTSpec,scaleFactor,pBuffer);
}
inline IppStatus ippsDFTFwd_CToC_Sfs( const Ipp16s* pSrcRe, const Ipp16s* pSrcIm,
                     Ipp16s* pDstRe, Ipp16s* pDstIm,
                     const IppsDFTSpec_C_16s* pDFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
  return ippsDFTFwd_CToC_16s_Sfs(pSrcRe,pSrcIm,pDstRe,pDstIm,pDFTSpec,scaleFactor,pBuffer);
}
inline IppStatus ippsDFTInv_CToC_Sfs( const Ipp16s* pSrcRe, const Ipp16s* pSrcIm,
                     Ipp16s* pDstRe, Ipp16s* pDstIm,
                     const IppsDFTSpec_C_16s* pDFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
  return ippsDFTInv_CToC_16s_Sfs(pSrcRe,pSrcIm,pDstRe,pDstIm,pDFTSpec,scaleFactor,pBuffer);
}
inline IppStatus ippsDFTFwd_CToC( const Ipp32fc* pSrc, Ipp32fc* pDst,
                     const IppsDFTSpec_C_32fc* pDFTSpec, Ipp8u* pBuffer ) {
  return ippsDFTFwd_CToC_32fc(pSrc,pDst,pDFTSpec,pBuffer);
}
inline IppStatus ippsDFTInv_CToC( const Ipp32fc* pSrc, Ipp32fc* pDst,
                     const IppsDFTSpec_C_32fc* pDFTSpec, Ipp8u* pBuffer ) {
  return ippsDFTInv_CToC_32fc(pSrc,pDst,pDFTSpec,pBuffer);
}
inline IppStatus ippsDFTFwd_CToC( const Ipp32f* pSrcRe, const Ipp32f* pSrcIm,
                     Ipp32f* pDstRe, Ipp32f* pDstIm,
                     const IppsDFTSpec_C_32f* pDFTSpec, Ipp8u* pBuffer ) {
  return ippsDFTFwd_CToC_32f(pSrcRe,pSrcIm,pDstRe,pDstIm,pDFTSpec,pBuffer);
}
inline IppStatus ippsDFTInv_CToC( const Ipp32f* pSrcRe, const Ipp32f* pSrcIm,
                     Ipp32f* pDstRe, Ipp32f* pDstIm,
                     const IppsDFTSpec_C_32f* pDFTSpec, Ipp8u* pBuffer ) {
  return ippsDFTInv_CToC_32f(pSrcRe,pSrcIm,pDstRe,pDstIm,pDFTSpec,pBuffer);
}
inline IppStatus ippsDFTFwd_CToC( const Ipp64fc* pSrc, Ipp64fc* pDst,
                     const IppsDFTSpec_C_64fc* pDFTSpec, Ipp8u* pBuffer ) {
  return ippsDFTFwd_CToC_64fc(pSrc,pDst,pDFTSpec,pBuffer);
}
inline IppStatus ippsDFTInv_CToC( const Ipp64fc* pSrc, Ipp64fc* pDst,
                     const IppsDFTSpec_C_64fc* pDFTSpec, Ipp8u* pBuffer ) {
  return ippsDFTInv_CToC_64fc(pSrc,pDst,pDFTSpec,pBuffer);
}
inline IppStatus ippsDFTFwd_CToC( const Ipp64f* pSrcRe, const Ipp64f* pSrcIm,
                     Ipp64f* pDstRe, Ipp64f* pDstIm,
                     const IppsDFTSpec_C_64f* pDFTSpec, Ipp8u* pBuffer ) {
  return ippsDFTFwd_CToC_64f(pSrcRe,pSrcIm,pDstRe,pDstIm,pDFTSpec,pBuffer);
}
inline IppStatus ippsDFTInv_CToC( const Ipp64f* pSrcRe, const Ipp64f* pSrcIm,
                     Ipp64f* pDstRe, Ipp64f* pDstIm,
                     const IppsDFTSpec_C_64f* pDFTSpec, Ipp8u* pBuffer ) {
  return ippsDFTInv_CToC_64f(pSrcRe,pSrcIm,pDstRe,pDstIm,pDFTSpec,pBuffer);
}
inline IppStatus ippsDFTOutOrdFwd_CToC( const Ipp32fc* pSrc, Ipp32fc* pDst,
                     const IppsDFTOutOrdSpec_C_32fc* pDFTSpec, Ipp8u* pBuffer ) {
  return ippsDFTOutOrdFwd_CToC_32fc(pSrc,pDst,pDFTSpec,pBuffer);
}
inline IppStatus ippsDFTOutOrdInv_CToC( const Ipp32fc* pSrc, Ipp32fc* pDst,
                     const IppsDFTOutOrdSpec_C_32fc* pDFTSpec, Ipp8u* pBuffer ) {
  return ippsDFTOutOrdInv_CToC_32fc(pSrc,pDst,pDFTSpec,pBuffer);
}
inline IppStatus ippsDFTOutOrdFwd_CToC( const Ipp64fc* pSrc, Ipp64fc* pDst,
                     const IppsDFTOutOrdSpec_C_64fc* pDFTSpec, Ipp8u* pBuffer ) {
  return ippsDFTOutOrdFwd_CToC_64fc(pSrc,pDst,pDFTSpec,pBuffer);
}
inline IppStatus ippsDFTOutOrdInv_CToC( const Ipp64fc* pSrc, Ipp64fc* pDst,
                     const IppsDFTOutOrdSpec_C_64fc* pDFTSpec, Ipp8u* pBuffer ) {
  return ippsDFTOutOrdInv_CToC_64fc(pSrc,pDst,pDFTSpec,pBuffer);
}
inline IppStatus ippsDFTFwd_RToPerm_Sfs( const Ipp16s* pSrc, Ipp16s* pDst,
                     const IppsDFTSpec_R_16s* pDFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
  return ippsDFTFwd_RToPerm_16s_Sfs(pSrc,pDst,pDFTSpec,scaleFactor,pBuffer);
}
inline IppStatus ippsDFTFwd_RToPack_Sfs( const Ipp16s* pSrc, Ipp16s* pDst,
                     const IppsDFTSpec_R_16s* pDFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
  return ippsDFTFwd_RToPack_16s_Sfs(pSrc,pDst,pDFTSpec,scaleFactor,pBuffer);
}
inline IppStatus ippsDFTFwd_RToCCS_Sfs( const Ipp16s* pSrc, Ipp16s* pDst,
                     const IppsDFTSpec_R_16s* pDFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
  return ippsDFTFwd_RToCCS_16s_Sfs(pSrc,pDst,pDFTSpec,scaleFactor,pBuffer);
}
inline IppStatus ippsDFTInv_PermToR_Sfs( const Ipp16s* pSrc, Ipp16s* pDst,
                     const IppsDFTSpec_R_16s* pDFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
  return ippsDFTInv_PermToR_16s_Sfs(pSrc,pDst,pDFTSpec,scaleFactor,pBuffer);
}
inline IppStatus ippsDFTInv_PackToR_Sfs( const Ipp16s* pSrc, Ipp16s* pDst,
                     const IppsDFTSpec_R_16s* pDFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
  return ippsDFTInv_PackToR_16s_Sfs(pSrc,pDst,pDFTSpec,scaleFactor,pBuffer);
}
inline IppStatus ippsDFTInv_CCSToR_Sfs( const Ipp16s* pSrc, Ipp16s* pDst,
                     const IppsDFTSpec_R_16s* pDFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
  return ippsDFTInv_CCSToR_16s_Sfs(pSrc,pDst,pDFTSpec,scaleFactor,pBuffer);
}
inline IppStatus ippsDFTFwd_RToPerm( const Ipp32f* pSrc, Ipp32f* pDst,
                     const IppsDFTSpec_R_32f* pDFTSpec, Ipp8u* pBuffer ) {
  return ippsDFTFwd_RToPerm_32f(pSrc,pDst,pDFTSpec,pBuffer);
}
inline IppStatus ippsDFTFwd_RToPack( const Ipp32f* pSrc, Ipp32f* pDst,
                     const IppsDFTSpec_R_32f* pDFTSpec, Ipp8u* pBuffer ) {
  return ippsDFTFwd_RToPack_32f(pSrc,pDst,pDFTSpec,pBuffer);
}
inline IppStatus ippsDFTFwd_RToCCS( const Ipp32f* pSrc, Ipp32f* pDst,
                     const IppsDFTSpec_R_32f* pDFTSpec, Ipp8u* pBuffer ) {
  return ippsDFTFwd_RToCCS_32f(pSrc,pDst,pDFTSpec,pBuffer);
}
inline IppStatus ippsDFTInv_PermToR( const Ipp32f* pSrc, Ipp32f* pDst,
                     const IppsDFTSpec_R_32f* pDFTSpec, Ipp8u* pBuffer ) {
  return ippsDFTInv_PermToR_32f(pSrc,pDst,pDFTSpec,pBuffer);
}
inline IppStatus ippsDFTInv_PackToR( const Ipp32f* pSrc, Ipp32f* pDst,
                     const IppsDFTSpec_R_32f* pDFTSpec, Ipp8u* pBuffer ) {
  return ippsDFTInv_PackToR_32f(pSrc,pDst,pDFTSpec,pBuffer);
}
inline IppStatus ippsDFTInv_CCSToR( const Ipp32f* pSrc, Ipp32f* pDst,
                     const IppsDFTSpec_R_32f* pDFTSpec, Ipp8u* pBuffer ) {
  return ippsDFTInv_CCSToR_32f(pSrc,pDst,pDFTSpec,pBuffer);
}
inline IppStatus ippsDFTFwd_RToPerm( const Ipp64f* pSrc, Ipp64f* pDst,
                     const IppsDFTSpec_R_64f* pDFTSpec, Ipp8u* pBuffer ) {
  return ippsDFTFwd_RToPerm_64f(pSrc,pDst,pDFTSpec,pBuffer);
}
inline IppStatus ippsDFTFwd_RToPack( const Ipp64f* pSrc, Ipp64f* pDst,
                     const IppsDFTSpec_R_64f* pDFTSpec, Ipp8u* pBuffer ) {
  return ippsDFTFwd_RToPack_64f(pSrc,pDst,pDFTSpec,pBuffer);
}
inline IppStatus ippsDFTFwd_RToCCS( const Ipp64f* pSrc, Ipp64f* pDst,
                     const IppsDFTSpec_R_64f* pDFTSpec, Ipp8u* pBuffer ) {
  return ippsDFTFwd_RToCCS_64f(pSrc,pDst,pDFTSpec,pBuffer);
}
inline IppStatus ippsDFTInv_PermToR( const Ipp64f* pSrc, Ipp64f* pDst,
                     const IppsDFTSpec_R_64f* pDFTSpec, Ipp8u* pBuffer ) {
  return ippsDFTInv_PermToR_64f(pSrc,pDst,pDFTSpec,pBuffer);
}
inline IppStatus ippsDFTInv_PackToR( const Ipp64f* pSrc, Ipp64f* pDst,
                     const IppsDFTSpec_R_64f* pDFTSpec, Ipp8u* pBuffer ) {
  return ippsDFTInv_PackToR_64f(pSrc,pDst,pDFTSpec,pBuffer);
}
inline IppStatus ippsDFTInv_CCSToR( const Ipp64f* pSrc, Ipp64f* pDst,
                     const IppsDFTSpec_R_64f* pDFTSpec, Ipp8u* pBuffer ) {
  return ippsDFTInv_CCSToR_64f(pSrc,pDst,pDFTSpec,pBuffer);
}
inline IppStatus ippsMulPack_ISfs(const Ipp16s* pSrc, Ipp16s* pSrcDst, int length, int scaleFactor) {
  return ippsMulPack_16s_ISfs(pSrc,pSrcDst,length,scaleFactor);
}
inline IppStatus ippsMulPerm_ISfs(const Ipp16s* pSrc, Ipp16s* pSrcDst, int length, int scaleFactor) {
  return ippsMulPerm_16s_ISfs(pSrc,pSrcDst,length,scaleFactor);
}
inline IppStatus ippsMulPack_I(const Ipp32f* pSrc, Ipp32f* pSrcDst, int length) {
  return ippsMulPack_32f_I(pSrc,pSrcDst,length);
}
inline IppStatus ippsMulPerm_I(const Ipp32f* pSrc, Ipp32f* pSrcDst, int length) {
  return ippsMulPerm_32f_I(pSrc,pSrcDst,length);
}
inline IppStatus ippsMulPack_I(const Ipp64f* pSrc, Ipp64f* pSrcDst, int length) {
  return ippsMulPack_64f_I(pSrc,pSrcDst,length);
}
inline IppStatus ippsMulPerm_I(const Ipp64f* pSrc, Ipp64f* pSrcDst, int length) {
  return ippsMulPerm_64f_I(pSrc,pSrcDst,length);
}
inline IppStatus ippsMulPack_Sfs(const Ipp16s* pSrc1, const Ipp16s* pSrc2, Ipp16s* pDst, int length, int scaleFactor) {
  return ippsMulPack_16s_Sfs(pSrc1,pSrc2,pDst,length,scaleFactor);
}
inline IppStatus ippsMulPerm_Sfs(const Ipp16s* pSrc1, const Ipp16s* pSrc2, Ipp16s* pDst, int length, int scaleFactor) {
  return ippsMulPerm_16s_Sfs(pSrc1,pSrc2,pDst,length,scaleFactor);
}
inline IppStatus ippsMulPack(const Ipp32f* pSrc1, const Ipp32f* pSrc2, Ipp32f* pDst, int length) {
  return ippsMulPack_32f(pSrc1,pSrc2,pDst,length);
}
inline IppStatus ippsMulPerm(const Ipp32f* pSrc1, const Ipp32f* pSrc2, Ipp32f* pDst, int length) {
  return ippsMulPerm_32f(pSrc1,pSrc2,pDst,length);
}
inline IppStatus ippsMulPack(const Ipp64f* pSrc1, const Ipp64f* pSrc2, Ipp64f* pDst, int length) {
  return ippsMulPack_64f(pSrc1,pSrc2,pDst,length);
}
inline IppStatus ippsMulPerm(const Ipp64f* pSrc1, const Ipp64f* pSrc2, Ipp64f* pDst, int length) {
  return ippsMulPerm_64f(pSrc1,pSrc2,pDst,length);
}
inline IppStatus ippsMulPackConj_I(const Ipp32f* pSrc, Ipp32f* pSrcDst, int length) {
  return ippsMulPackConj_32f_I(pSrc,pSrcDst,length);
}
inline IppStatus ippsMulPackConj_I(const Ipp64f* pSrc, Ipp64f* pSrcDst, int length) {
  return ippsMulPackConj_64f_I(pSrc,pSrcDst,length);
}
inline IppStatus ippsGoertz(const Ipp32fc* pSrc, int len, Ipp32fc* pVal, Ipp32f freq) {
  return ippsGoertz_32fc(pSrc,len,pVal,freq);
}
inline IppStatus ippsGoertz(const Ipp64fc* pSrc, int len, Ipp64fc* pVal, Ipp64f freq) {
  return ippsGoertz_64fc(pSrc,len,pVal,freq);
}
inline IppStatus ippsGoertz_Sfs(const Ipp16sc* pSrc, int len, Ipp16sc* pVal, Ipp32f freq, int scaleFactor) {
  return ippsGoertz_16sc_Sfs(pSrc,len,pVal,freq,scaleFactor);
}
inline IppStatus ippsGoertz(const Ipp32f* pSrc, int len, Ipp32fc* pVal, Ipp32f freq) {
  return ippsGoertz_32f(pSrc,len,pVal,freq);
}
inline IppStatus ippsGoertz_Sfs(const Ipp16s* pSrc, int len, Ipp16sc* pVal, Ipp32f freq, int scaleFactor) {
  return ippsGoertz_16s_Sfs(pSrc,len,pVal,freq,scaleFactor);
}
inline IppStatus ippsGoertzTwo(const Ipp32fc* pSrc, int len,
       Ipp32fc pVal[2], const Ipp32f freq[2] ) {
  return ippsGoertzTwo_32fc(pSrc,len,pVal,freq);
}
inline IppStatus ippsGoertzTwo(const Ipp64fc* pSrc, int len,
       Ipp64fc pVal[2], const Ipp64f freq[2] ) {
  return ippsGoertzTwo_64fc(pSrc,len,pVal,freq);
}
inline IppStatus ippsGoertzTwo_Sfs(const Ipp16sc* pSrc, int len,
       Ipp16sc pVal[2], const Ipp32f freq[2], int scaleFactor) {
  return ippsGoertzTwo_16sc_Sfs(pSrc,len,pVal,freq,scaleFactor);
}
inline IppStatus ippsGoertzQ15_Sfs(const Ipp16sc* pSrc, int len, Ipp16sc* pVal, Ipp16s rFreqQ15, int scaleFactor) {
  return ippsGoertzQ15_16sc_Sfs(pSrc,len,pVal,rFreqQ15,scaleFactor);
}
inline IppStatus ippsGoertzTwoQ15_Sfs(const Ipp16sc* pSrc, int len, Ipp16sc pVal[2], const Ipp16s rFreqQ15[2], int scaleFactor) {
  return ippsGoertzTwoQ15_16sc_Sfs(pSrc,len,pVal,rFreqQ15,scaleFactor);
}
inline IppStatus ippsDCTFwd_Sfs( const Ipp16s* pSrc, Ipp16s* pDst,
                     const IppsDCTFwdSpec_16s* pDCTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
  return ippsDCTFwd_16s_Sfs(pSrc,pDst,pDCTSpec,scaleFactor,pBuffer);
}
inline IppStatus ippsDCTInv_Sfs( const Ipp16s* pSrc, Ipp16s* pDst,
                     const IppsDCTInvSpec_16s* pDCTSpec,
                     int scaleFactor, Ipp8u* pBuffer ) {
  return ippsDCTInv_16s_Sfs(pSrc,pDst,pDCTSpec,scaleFactor,pBuffer);
}
inline IppStatus ippsDCTFwd( const Ipp32f* pSrc, Ipp32f* pDst,
                     const IppsDCTFwdSpec_32f* pDCTSpec, Ipp8u* pBuffer ) {
  return ippsDCTFwd_32f(pSrc,pDst,pDCTSpec,pBuffer);
}
inline IppStatus ippsDCTInv( const Ipp32f* pSrc, Ipp32f* pDst,
                     const IppsDCTInvSpec_32f* pDCTSpec, Ipp8u* pBuffer ) {
  return ippsDCTInv_32f(pSrc,pDst,pDCTSpec,pBuffer);
}
inline IppStatus ippsDCTFwd( const Ipp64f* pSrc, Ipp64f* pDst,
                     const IppsDCTFwdSpec_64f* pDCTSpec, Ipp8u* pBuffer ) {
  return ippsDCTFwd_64f(pSrc,pDst,pDCTSpec,pBuffer);
}
inline IppStatus ippsDCTInv( const Ipp64f* pSrc, Ipp64f* pDst,
                     const IppsDCTInvSpec_64f* pDCTSpec, Ipp8u* pBuffer ) {
  return ippsDCTInv_64f(pSrc,pDst,pDCTSpec,pBuffer);
}
inline IppStatus ippsWTHaarFwd( const Ipp8s* pSrc, int len,
                        Ipp8s* pDstLow, Ipp8s* pDstHigh ) {
  return ippsWTHaarFwd_8s(pSrc,len,pDstLow,pDstHigh);
}
inline IppStatus ippsWTHaarFwd( const Ipp16s* pSrc, int len,
                        Ipp16s* pDstLow, Ipp16s* pDstHigh ) {
  return ippsWTHaarFwd_16s(pSrc,len,pDstLow,pDstHigh);
}
inline IppStatus ippsWTHaarFwd( const Ipp32s* pSrc, int len,
                        Ipp32s* pDstLow, Ipp32s* pDstHigh ) {
  return ippsWTHaarFwd_32s(pSrc,len,pDstLow,pDstHigh);
}
inline IppStatus ippsWTHaarFwd( const Ipp64s* pSrc, int len,
                        Ipp64s* pDstLow, Ipp64s* pDstHigh ) {
  return ippsWTHaarFwd_64s(pSrc,len,pDstLow,pDstHigh);
}
inline IppStatus ippsWTHaarFwd( const Ipp32f* pSrc, int len,
                        Ipp32f* pDstLow, Ipp32f* pDstHigh ) {
  return ippsWTHaarFwd_32f(pSrc,len,pDstLow,pDstHigh);
}
inline IppStatus ippsWTHaarFwd( const Ipp64f* pSrc, int len,
                        Ipp64f* pDstLow, Ipp64f* pDstHigh ) {
  return ippsWTHaarFwd_64f(pSrc,len,pDstLow,pDstHigh);
}
inline IppStatus ippsWTHaarFwd_Sfs( const Ipp8s* pSrc, int len,
                        Ipp8s* pDstLow, Ipp8s* pDstHigh, int scaleFactor) {
  return ippsWTHaarFwd_8s_Sfs(pSrc,len,pDstLow,pDstHigh,scaleFactor);
}
inline IppStatus ippsWTHaarFwd_Sfs( const Ipp16s* pSrc, int len,
                        Ipp16s* pDstLow, Ipp16s* pDstHigh, int scaleFactor ) {
  return ippsWTHaarFwd_16s_Sfs(pSrc,len,pDstLow,pDstHigh,scaleFactor);
}
inline IppStatus ippsWTHaarFwd_Sfs( const Ipp32s* pSrc, int len,
                        Ipp32s* pDstLow, Ipp32s* pDstHigh, int scaleFactor ) {
  return ippsWTHaarFwd_32s_Sfs(pSrc,len,pDstLow,pDstHigh,scaleFactor);
}
inline IppStatus ippsWTHaarFwd_Sfs( const Ipp64s* pSrc, int len,
                        Ipp64s* pDstLow, Ipp64s* pDstHigh, int scaleFactor ) {
  return ippsWTHaarFwd_64s_Sfs(pSrc,len,pDstLow,pDstHigh,scaleFactor);
}
inline IppStatus ippsWTHaarInv( const Ipp8s* pSrcLow, const Ipp8s* pSrcHigh,
                                Ipp8s* pDst, int len ) {
  return ippsWTHaarInv_8s(pSrcLow,pSrcHigh,pDst,len);
}
inline IppStatus ippsWTHaarInv( const Ipp16s* pSrcLow, const Ipp16s* pSrcHigh,
                                Ipp16s* pDst, int len ) {
  return ippsWTHaarInv_16s(pSrcLow,pSrcHigh,pDst,len);
}
inline IppStatus ippsWTHaarInv( const Ipp32s* pSrcLow, const Ipp32s* pSrcHigh,
                                Ipp32s* pDst, int len ) {
  return ippsWTHaarInv_32s(pSrcLow,pSrcHigh,pDst,len);
}
inline IppStatus ippsWTHaarInv( const Ipp64s* pSrcLow, const Ipp64s* pSrcHigh,
                                Ipp64s* pDst, int len ) {
  return ippsWTHaarInv_64s(pSrcLow,pSrcHigh,pDst,len);
}
inline IppStatus ippsWTHaarInv( const Ipp32f* pSrcLow, const Ipp32f* pSrcHigh,
                                Ipp32f* pDst, int len ) {
  return ippsWTHaarInv_32f(pSrcLow,pSrcHigh,pDst,len);
}
inline IppStatus ippsWTHaarInv( const Ipp64f* pSrcLow, const Ipp64f* pSrcHigh,
                                Ipp64f* pDst, int len ) {
  return ippsWTHaarInv_64f(pSrcLow,pSrcHigh,pDst,len);
}
inline IppStatus ippsWTHaarInv_Sfs( const Ipp8s* pSrcLow, const Ipp8s* pSrcHigh,
                                Ipp8s* pDst, int len, int scaleFactor ) {
  return ippsWTHaarInv_8s_Sfs(pSrcLow,pSrcHigh,pDst,len,scaleFactor);
}
inline IppStatus ippsWTHaarInv_Sfs( const Ipp16s* pSrcLow, const Ipp16s* pSrcHigh,
                                Ipp16s* pDst, int len, int scaleFactor ) {
  return ippsWTHaarInv_16s_Sfs(pSrcLow,pSrcHigh,pDst,len,scaleFactor);
}
inline IppStatus ippsWTHaarInv_Sfs( const Ipp32s* pSrcLow, const Ipp32s* pSrcHigh,
                                Ipp32s* pDst, int len, int scaleFactor ) {
  return ippsWTHaarInv_32s_Sfs(pSrcLow,pSrcHigh,pDst,len,scaleFactor);
}
inline IppStatus ippsWTHaarInv_Sfs( const Ipp64s* pSrcLow, const Ipp64s* pSrcHigh,
                              Ipp64s* pDst, int len, int scaleFactor ) {
  return ippsWTHaarInv_64s_Sfs(pSrcLow,pSrcHigh,pDst,len,scaleFactor);
}
inline IppStatus ippsWTFwdInitAlloc(IppsWTFwdState_32f** pState,
        const Ipp32f* pTapsLow,  int lenLow,  int offsLow,
        const Ipp32f* pTapsHigh, int lenHigh, int offsHigh) {
  return ippsWTFwdInitAlloc_32f(pState,pTapsLow,lenLow,offsLow,pTapsHigh,lenHigh,offsHigh);
}
inline IppStatus ippsWTFwdSetDlyLine(IppsWTFwdState_32f* pState,
        const Ipp32f* pDlyLow, const Ipp32f* pDlyHigh) {
  return ippsWTFwdSetDlyLine_32f(pState,pDlyLow,pDlyHigh);
}
inline IppStatus ippsWTFwdGetDlyLine(IppsWTFwdState_32f* pState,
        Ipp32f* pDlyLow, Ipp32f* pDlyHigh) {
  return ippsWTFwdGetDlyLine_32f(pState,pDlyLow,pDlyHigh);
}
inline IppStatus ippsWTFwd(const Ipp32f* pSrc,
        Ipp32f* pDstLow, Ipp32f* pDstHigh, int dstLen,
        IppsWTFwdState_32f* pState) {
  return ippsWTFwd_32f(pSrc,pDstLow,pDstHigh,dstLen,pState);
}
inline IppStatus ippsWTFwd(const Ipp8s* pSrc,
        Ipp32f* pDstLow, Ipp32f* pDstHigh, int dstLen,
        IppsWTFwdState_8s32f* pState) {
  return ippsWTFwd_8s32f(pSrc,pDstLow,pDstHigh,dstLen,pState);
}
inline IppStatus ippsWTFwd(const Ipp8u* pSrc,
        Ipp32f* pDstLow, Ipp32f* pDstHigh, int dstLen,
        IppsWTFwdState_8u32f* pState) {
  return ippsWTFwd_8u32f(pSrc,pDstLow,pDstHigh,dstLen,pState);
}
inline IppStatus ippsWTFwd(const Ipp16s* pSrc,
        Ipp32f* pDstLow, Ipp32f* pDstHigh, int dstLen,
        IppsWTFwdState_16s32f* pState) {
  return ippsWTFwd_16s32f(pSrc,pDstLow,pDstHigh,dstLen,pState);
}
inline IppStatus ippsWTFwd(
        const Ipp16u* pSrc, Ipp32f* pDstLow, Ipp32f* pDstHigh, int dstLen,
        IppsWTFwdState_16u32f* pState) {
  return ippsWTFwd_16u32f(pSrc,pDstLow,pDstHigh,dstLen,pState);
}
inline IppStatus ippsWTInvInitAlloc(IppsWTInvState_32f** pState,
        const Ipp32f* pTapsLow,  int lenLow,  int offsLow,
        const Ipp32f* pTapsHigh, int lenHigh, int offsHigh) {
  return ippsWTInvInitAlloc_32f(pState,pTapsLow,lenLow,offsLow,pTapsHigh,lenHigh,offsHigh);
}
inline IppStatus ippsWTInvSetDlyLine(IppsWTInvState_32f* pState,
        const Ipp32f* pDlyLow, const Ipp32f* pDlyHigh) {
  return ippsWTInvSetDlyLine_32f(pState,pDlyLow,pDlyHigh);
}
inline IppStatus ippsWTInvGetDlyLine(IppsWTInvState_32f* pState,
        Ipp32f* pDlyLow, Ipp32f* pDlyHigh) {
  return ippsWTInvGetDlyLine_32f(pState,pDlyLow,pDlyHigh);
}
inline IppStatus ippsWTInv(
        const Ipp32f* pSrcLow, const Ipp32f* pSrcHigh, int srcLen, Ipp32f* pDst,
        IppsWTInvState_32f* pState) {
  return ippsWTInv_32f(pSrcLow,pSrcHigh,srcLen,pDst,pState);
}
inline IppStatus ippsWTInv(
        const Ipp32f* pSrcLow, const Ipp32f* pSrcHigh, int srcLen, Ipp8s* pDst,
        IppsWTInvState_32f8s* pState) {
  return ippsWTInv_32f8s(pSrcLow,pSrcHigh,srcLen,pDst,pState);
}
inline IppStatus ippsWTInv(
        const Ipp32f* pSrcLow, const Ipp32f* pSrcHigh, int srcLen, Ipp8u* pDst,
        IppsWTInvState_32f8u* pState) {
  return ippsWTInv_32f8u(pSrcLow,pSrcHigh,srcLen,pDst,pState);
}
inline IppStatus ippsWTInv(
        const Ipp32f* pSrcLow, const Ipp32f* pSrcHigh, int srcLen, Ipp16s* pDst,
        IppsWTInvState_32f16s* pState) {
  return ippsWTInv_32f16s(pSrcLow,pSrcHigh,srcLen,pDst,pState);
}
inline IppStatus ippsWTInv(
        const Ipp32f* pSrcLow, const Ipp32f* pSrcHigh, int srcLen, Ipp16u* pDst,
        IppsWTInvState_32f16u* pState) {
  return ippsWTInv_32f16u(pSrcLow,pSrcHigh,srcLen,pDst,pState);
}
inline IppStatus ippsConv( const Ipp32f* pSrc1, int lenSrc1,
       const Ipp32f* pSrc2, int lenSrc2, Ipp32f* pDst) {
  return ippsConv_32f(pSrc1,lenSrc1,pSrc2,lenSrc2,pDst);
}
inline IppStatus ippsConv_Sfs( const Ipp16s* pSrc1, int lenSrc1,
       const Ipp16s* pSrc2, int lenSrc2, Ipp16s* pDst, int scaleFactor) {
  return ippsConv_16s_Sfs(pSrc1,lenSrc1,pSrc2,lenSrc2,pDst,scaleFactor);
}
inline IppStatus ippsConv( const Ipp64f* pSrc1, int lenSrc1,
        const Ipp64f* pSrc2, int lenSrc2, Ipp64f* pDst) {
  return ippsConv_64f(pSrc1,lenSrc1,pSrc2,lenSrc2,pDst);
}
inline IppStatus ippsConvBiased( const Ipp32f *pSrc1, int len1,
                      const Ipp32f *pSrc2, int len2,
                            Ipp32f *pDst, int lenDst, int bias ) {
  return ippsConvBiased_32f(pSrc1,len1,pSrc2,len2,pDst,lenDst,bias);
}
inline IppStatus ippsConvCyclic8x8( const Ipp32f* x,
       const Ipp32f* h, Ipp32f* y ) {
  return ippsConvCyclic8x8_32f(x,h,y);
}
inline IppStatus ippsConvCyclic8x8_Sfs( const Ipp16s* x,
       const Ipp16s* h, Ipp16s* y, int scaleFactor ) {
  return ippsConvCyclic8x8_16s_Sfs(x,h,y,scaleFactor);
}
inline IppStatus ippsConvCyclic4x4( const Ipp32f* x,
       const Ipp32fc* h, Ipp32fc* y ) {
  return ippsConvCyclic4x4_32f32fc(x,h,y);
}
inline IppStatus ippsIIRInitAlloc(IppsIIRState_32f** pState,
       const Ipp32f* pTaps, int order, const Ipp32f* pDlyLine) {
  return ippsIIRInitAlloc_32f(pState,pTaps,order,pDlyLine);
}
inline IppStatus ippsIIRInitAlloc(IppsIIRState_32fc** pState,
       const Ipp32fc* pTaps, int order, const Ipp32fc* pDlyLine) {
  return ippsIIRInitAlloc_32fc(pState,pTaps,order,pDlyLine);
}
inline IppStatus ippsIIRInitAlloc(IppsIIRState_64f** pState,
       const Ipp64f* pTaps, int order, const Ipp64f* pDlyLine) {
  return ippsIIRInitAlloc_64f(pState,pTaps,order,pDlyLine);
}
inline IppStatus ippsIIRInitAlloc(IppsIIRState_64fc** pState,
       const Ipp64fc* pTaps, int order, const Ipp64fc* pDlyLine) {
  return ippsIIRInitAlloc_64fc(pState,pTaps,order,pDlyLine);
}
inline IppStatus ippsIIRInitAlloc_BiQuad(IppsIIRState_32f** pState,
       const Ipp32f* pTaps, int numBq, const Ipp32f* pDlyLine) {
  return ippsIIRInitAlloc_BiQuad_32f(pState,pTaps,numBq,pDlyLine);
}
inline IppStatus ippsIIRInitAlloc_BiQuad(IppsIIRState_32fc** pState,
       const Ipp32fc* pTaps, int numBq, const Ipp32fc* pDlyLine) {
  return ippsIIRInitAlloc_BiQuad_32fc(pState,pTaps,numBq,pDlyLine);
}
inline IppStatus ippsIIRInitAlloc_BiQuad(IppsIIRState_64f** pState,
       const Ipp64f* pTaps, int numBq, const Ipp64f* pDlyLine) {
  return ippsIIRInitAlloc_BiQuad_64f(pState,pTaps,numBq,pDlyLine);
}
inline IppStatus ippsIIRInitAlloc_BiQuad(IppsIIRState_64fc** pState,
       const Ipp64fc* pTaps, int numBq, const Ipp64fc* pDlyLine) {
  return ippsIIRInitAlloc_BiQuad_64fc(pState,pTaps,numBq,pDlyLine);
}
inline IppStatus ippsIIRGetDlyLine(const IppsIIRState_32f* pState, Ipp32f* pDlyLine) {
  return ippsIIRGetDlyLine_32f(pState,pDlyLine);
}
inline IppStatus ippsIIRSetDlyLine(IppsIIRState_32f* pState, const Ipp32f* pDlyLine) {
  return ippsIIRSetDlyLine_32f(pState,pDlyLine);
}
inline IppStatus ippsIIRGetDlyLine(const IppsIIRState_32fc* pState, Ipp32fc* pDlyLine) {
  return ippsIIRGetDlyLine_32fc(pState,pDlyLine);
}
inline IppStatus ippsIIRSetDlyLine(IppsIIRState_32fc* pState, const Ipp32fc* pDlyLine) {
  return ippsIIRSetDlyLine_32fc(pState,pDlyLine);
}
inline IppStatus ippsIIRGetDlyLine(const IppsIIRState_64f* pState, Ipp64f* pDlyLine) {
  return ippsIIRGetDlyLine_64f(pState,pDlyLine);
}
inline IppStatus ippsIIRSetDlyLine(IppsIIRState_64f* pState, const Ipp64f* pDlyLine) {
  return ippsIIRSetDlyLine_64f(pState,pDlyLine);
}
inline IppStatus ippsIIRGetDlyLine(const IppsIIRState_64fc* pState, Ipp64fc* pDlyLine) {
  return ippsIIRGetDlyLine_64fc(pState,pDlyLine);
}
inline IppStatus ippsIIRSetDlyLine(IppsIIRState_64fc* pState, const Ipp64fc* pDlyLine) {
  return ippsIIRSetDlyLine_64fc(pState,pDlyLine);
}
inline IppStatus ippsIIROne(Ipp32f src, Ipp32f* pDstVal, IppsIIRState_32f* pState) {
  return ippsIIROne_32f(src,pDstVal,pState);
}
inline IppStatus ippsIIROne(Ipp32fc src, Ipp32fc* pDstVal, IppsIIRState_32fc* pState) {
  return ippsIIROne_32fc(src,pDstVal,pState);
}
inline IppStatus ippsIIROne32f_Sfs(Ipp16s src, Ipp16s* pDstVal, IppsIIRState32f_16s* pState, int scaleFactor) {
  return ippsIIROne32f_16s_Sfs(src,pDstVal,pState,scaleFactor);
}
inline IppStatus ippsIIROne32fc_Sfs(Ipp16sc src, Ipp16sc* pDstVal, IppsIIRState32fc_16sc* pState, int scaleFactor) {
  return ippsIIROne32fc_16sc_Sfs(src,pDstVal,pState,scaleFactor);
}
inline IppStatus ippsIIROne(Ipp64f src, Ipp64f* pDstVal, IppsIIRState_64f* pState) {
  return ippsIIROne_64f(src,pDstVal,pState);
}
inline IppStatus ippsIIROne(Ipp64fc src, Ipp64fc* pDstVal, IppsIIRState_64fc* pState) {
  return ippsIIROne_64fc(src,pDstVal,pState);
}
inline IppStatus ippsIIROne64f(Ipp32f src, Ipp32f* pDstVal, IppsIIRState64f_32f* pState) {
  return ippsIIROne64f_32f(src,pDstVal,pState);
}
inline IppStatus ippsIIROne64fc(Ipp32fc src, Ipp32fc* pDstVal, IppsIIRState64fc_32fc* pState) {
  return ippsIIROne64fc_32fc(src,pDstVal,pState);
}
inline IppStatus ippsIIROne64f_Sfs(Ipp32s src, Ipp32s* pDstVal, IppsIIRState64f_32s* pState, int scaleFactor) {
  return ippsIIROne64f_32s_Sfs(src,pDstVal,pState,scaleFactor);
}
inline IppStatus ippsIIROne64fc_Sfs(Ipp32sc src, Ipp32sc* pDstVal, IppsIIRState64fc_32sc* pState, int scaleFactor) {
  return ippsIIROne64fc_32sc_Sfs(src,pDstVal,pState,scaleFactor);
}
inline IppStatus ippsIIROne64f_Sfs(Ipp16s src, Ipp16s* pDstVal, IppsIIRState64f_16s* pState, int scaleFactor) {
  return ippsIIROne64f_16s_Sfs(src,pDstVal,pState,scaleFactor);
}
inline IppStatus ippsIIROne64fc_Sfs(Ipp16sc src, Ipp16sc* pDstVal, IppsIIRState64fc_16sc* pState, int scaleFactor) {
  return ippsIIROne64fc_16sc_Sfs(src,pDstVal,pState,scaleFactor);
}
inline IppStatus ippsIIR(const Ipp32f* pSrc, Ipp32f* pDst, int len,
       IppsIIRState_32f* pState) {
  return ippsIIR_32f(pSrc,pDst,len,pState);
}
inline IppStatus ippsIIR_I(Ipp32f* pSrcDst, int len, IppsIIRState_32f* pState) {
  return ippsIIR_32f_I(pSrcDst,len,pState);
}
inline IppStatus ippsIIR(const Ipp32fc* pSrc, Ipp32fc* pDst, int len,
       IppsIIRState_32fc* pState) {
  return ippsIIR_32fc(pSrc,pDst,len,pState);
}
inline IppStatus ippsIIR_I(Ipp32fc* pSrcDst, int len, IppsIIRState_32fc* pState) {
  return ippsIIR_32fc_I(pSrcDst,len,pState);
}
inline IppStatus ippsIIR32f_Sfs(const Ipp16s* pSrc, Ipp16s* pDst, int len,
       IppsIIRState32f_16s* pState, int scaleFactor) {
  return ippsIIR32f_16s_Sfs(pSrc,pDst,len,pState,scaleFactor);
}
inline IppStatus ippsIIR32f_ISfs(Ipp16s* pSrcDst, int len,
       IppsIIRState32f_16s* pState, int scaleFactor) {
  return ippsIIR32f_16s_ISfs(pSrcDst,len,pState,scaleFactor);
}
inline IppStatus ippsIIR32fc_Sfs(const Ipp16sc* pSrc, Ipp16sc* pDst, int len,
       IppsIIRState32fc_16sc* pState, int scaleFactor) {
  return ippsIIR32fc_16sc_Sfs(pSrc,pDst,len,pState,scaleFactor);
}
inline IppStatus ippsIIR32fc_ISfs(Ipp16sc* pSrcDst, int len,
       IppsIIRState32fc_16sc* pState, int scaleFactor) {
  return ippsIIR32fc_16sc_ISfs(pSrcDst,len,pState,scaleFactor);
}
inline IppStatus ippsIIR(const Ipp64f* pSrc, Ipp64f* pDst, int len,
       IppsIIRState_64f* pState) {
  return ippsIIR_64f(pSrc,pDst,len,pState);
}
inline IppStatus ippsIIR_I(Ipp64f* pSrcDst, int len, IppsIIRState_64f* pState) {
  return ippsIIR_64f_I(pSrcDst,len,pState);
}
inline IppStatus ippsIIR(const Ipp64fc* pSrc, Ipp64fc* pDst, int len,
       IppsIIRState_64fc* pState) {
  return ippsIIR_64fc(pSrc,pDst,len,pState);
}
inline IppStatus ippsIIR_I(Ipp64fc* pSrcDst, int len, IppsIIRState_64fc* pState) {
  return ippsIIR_64fc_I(pSrcDst,len,pState);
}
inline IppStatus ippsIIR64f(const Ipp32f* pSrc, Ipp32f* pDst, int len,
       IppsIIRState64f_32f* pState) {
  return ippsIIR64f_32f(pSrc,pDst,len,pState);
}
inline IppStatus ippsIIR64f_I(Ipp32f* pSrcDst, int len, IppsIIRState64f_32f* pState) {
  return ippsIIR64f_32f_I(pSrcDst,len,pState);
}
inline IppStatus ippsIIR64fc(const Ipp32fc* pSrc, Ipp32fc* pDst, int len,
       IppsIIRState64fc_32fc* pState) {
  return ippsIIR64fc_32fc(pSrc,pDst,len,pState);
}
inline IppStatus ippsIIR64fc_I(Ipp32fc* pSrcDst, int len, IppsIIRState64fc_32fc* pState) {
  return ippsIIR64fc_32fc_I(pSrcDst,len,pState);
}
inline IppStatus ippsIIR64f_Sfs(const Ipp32s* pSrc, Ipp32s* pDst, int len,
       IppsIIRState64f_32s* pState, int scaleFactor) {
  return ippsIIR64f_32s_Sfs(pSrc,pDst,len,pState,scaleFactor);
}
inline IppStatus ippsIIR64f_ISfs(Ipp32s* pSrcDst, int len,
       IppsIIRState64f_32s* pState, int scaleFactor) {
  return ippsIIR64f_32s_ISfs(pSrcDst,len,pState,scaleFactor);
}
inline IppStatus ippsIIR64fc_Sfs(const Ipp32sc* pSrc, Ipp32sc* pDst, int len,
       IppsIIRState64fc_32sc* pState, int scaleFactor) {
  return ippsIIR64fc_32sc_Sfs(pSrc,pDst,len,pState,scaleFactor);
}
inline IppStatus ippsIIR64fc_ISfs(Ipp32sc* pSrcDst, int len,
       IppsIIRState64fc_32sc* pState, int scaleFactor) {
  return ippsIIR64fc_32sc_ISfs(pSrcDst,len,pState,scaleFactor);
}
inline IppStatus ippsIIR64f_Sfs(const Ipp16s* pSrc, Ipp16s* pDst, int len,
       IppsIIRState64f_16s* pState, int scaleFactor) {
  return ippsIIR64f_16s_Sfs(pSrc,pDst,len,pState,scaleFactor);
}
inline IppStatus ippsIIR64f_ISfs(Ipp16s* pSrcDst, int len,
       IppsIIRState64f_16s* pState, int scaleFactor) {
  return ippsIIR64f_16s_ISfs(pSrcDst,len,pState,scaleFactor);
}
inline IppStatus ippsIIR64fc_Sfs(const Ipp16sc* pSrc, Ipp16sc* pDst, int len,
       IppsIIRState64fc_16sc* pState, int scaleFactor) {
  return ippsIIR64fc_16sc_Sfs(pSrc,pDst,len,pState,scaleFactor);
}
inline IppStatus ippsIIR64fc_ISfs(Ipp16sc* pSrcDst, int len,
       IppsIIRState64fc_16sc* pState, int scaleFactor) {
  return ippsIIR64fc_16sc_ISfs(pSrcDst,len,pState,scaleFactor);
}
inline IppStatus ippsIIROne32s_Sfs(Ipp16s src, Ipp16s* pDstVal, IppsIIRState32s_16s* pState, int scaleFactor) {
  return ippsIIROne32s_16s_Sfs(src,pDstVal,pState,scaleFactor);
}
inline IppStatus ippsIIROne32sc_Sfs(Ipp16sc src, Ipp16sc* pDstVal, IppsIIRState32sc_16sc* pState, int scaleFactor) {
  return ippsIIROne32sc_16sc_Sfs(src,pDstVal,pState,scaleFactor);
}
inline IppStatus ippsIIR32s_Sfs(const Ipp16s* pSrc, Ipp16s* pDst, int len,
       IppsIIRState32s_16s* pState, int scaleFactor) {
  return ippsIIR32s_16s_Sfs(pSrc,pDst,len,pState,scaleFactor);
}
inline IppStatus ippsIIR32sc_Sfs(const Ipp16sc* pSrc, Ipp16sc* pDst, int len,
       IppsIIRState32sc_16sc* pState, int scaleFactor) {
  return ippsIIR32sc_16sc_Sfs(pSrc,pDst,len,pState,scaleFactor);
}
inline IppStatus ippsIIR32s_ISfs(Ipp16s* pSrcDst, int len, IppsIIRState32s_16s* pState,
       int scaleFactor) {
  return ippsIIR32s_16s_ISfs(pSrcDst,len,pState,scaleFactor);
}
inline IppStatus ippsIIR32sc_ISfs(Ipp16sc* pSrcDst, int len, IppsIIRState32sc_16sc* pState,
       int scaleFactor) {
  return ippsIIR32sc_16sc_ISfs(pSrcDst,len,pState,scaleFactor);
}
inline IppStatus ippsIIR_Direct( const Ipp16s* pSrc, Ipp16s* pDst,
                 int len, const Ipp16s* pTaps, int order, Ipp32s* pDlyLine ) {
  return ippsIIR_Direct_16s(pSrc,pDst,len,pTaps,order,pDlyLine);
}
inline IppStatus ippsIIR_Direct_I( Ipp16s* pSrcDst, int len,
                          const Ipp16s* pTaps, int order, Ipp32s* pDlyLine ) {
  return ippsIIR_Direct_16s_I(pSrcDst,len,pTaps,order,pDlyLine);
}
inline IppStatus ippsIIROne_Direct( Ipp16s src, Ipp16s* pDstVal,
                          const Ipp16s* pTaps, int order, Ipp32s* pDlyLine ) {
  return ippsIIROne_Direct_16s(src,pDstVal,pTaps,order,pDlyLine);
}
inline IppStatus ippsIIROne_Direct_I( Ipp16s* pSrcDst,
                          const Ipp16s* pTaps, int order, Ipp32s* pDlyLine ) {
  return ippsIIROne_Direct_16s_I(pSrcDst,pTaps,order,pDlyLine);
}
inline IppStatus ippsIIR_BiQuadDirect( const Ipp16s* pSrc, Ipp16s* pDst,
             int len, const Ipp16s* pTaps, int numBq, Ipp32s* pDlyLine ) {
  return ippsIIR_BiQuadDirect_16s(pSrc,pDst,len,pTaps,numBq,pDlyLine);
}
inline IppStatus ippsIIR_BiQuadDirect_I( Ipp16s* pSrcDst, int len,
                     const Ipp16s * pTaps, int numBq, Ipp32s* pDlyLine ) {
  return ippsIIR_BiQuadDirect_16s_I(pSrcDst,len,pTaps,numBq,pDlyLine);
}
inline IppStatus ippsIIROne_BiQuadDirect( Ipp16s src, Ipp16s* pDstVal,
                      const Ipp16s* pTaps, int numBq, Ipp32s* pDlyLine ) {
  return ippsIIROne_BiQuadDirect_16s(src,pDstVal,pTaps,numBq,pDlyLine);
}
inline IppStatus ippsIIROne_BiQuadDirect_I( Ipp16s* pSrcDstVal,
                      const Ipp16s* pTaps, int numBq, Ipp32s* pDlyLine ) {
  return ippsIIROne_BiQuadDirect_16s_I(pSrcDstVal,pTaps,numBq,pDlyLine);
}
inline IppStatus ippsIIRInit( IppsIIRState_32f** pState,
         const Ipp32f* pTaps, int order, const Ipp32f* pDlyLine, Ipp8u* pBuf ) {
  return ippsIIRInit_32f(pState,pTaps,order,pDlyLine,pBuf);
}
inline IppStatus ippsIIRInit( IppsIIRState_32fc** pState,
       const Ipp32fc* pTaps, int order, const Ipp32fc* pDlyLine, Ipp8u* pBuf ) {
  return ippsIIRInit_32fc(pState,pTaps,order,pDlyLine,pBuf);
}
inline IppStatus ippsIIRInit_BiQuad( IppsIIRState_32f** pState,
         const Ipp32f* pTaps, int numBq, const Ipp32f* pDlyLine, Ipp8u* pBuf ) {
  return ippsIIRInit_BiQuad_32f(pState,pTaps,numBq,pDlyLine,pBuf);
}
inline IppStatus ippsIIRInit_BiQuad( IppsIIRState_32fc** pState,
       const Ipp32fc* pTaps, int numBq, const Ipp32fc* pDlyLine, Ipp8u* pBuf ) {
  return ippsIIRInit_BiQuad_32fc(pState,pTaps,numBq,pDlyLine,pBuf);
}
inline IppStatus ippsIIRInit( IppsIIRState_64f** pState,
         const Ipp64f* pTaps, int order, const Ipp64f* pDlyLine, Ipp8u* pBuf ) {
  return ippsIIRInit_64f(pState,pTaps,order,pDlyLine,pBuf);
}
inline IppStatus ippsIIRInit( IppsIIRState_64fc** pState,
       const Ipp64fc* pTaps, int order, const Ipp64fc* pDlyLine, Ipp8u* pBuf ) {
  return ippsIIRInit_64fc(pState,pTaps,order,pDlyLine,pBuf);
}
inline IppStatus ippsIIRInit_BiQuad( IppsIIRState_64f** pState,
         const Ipp64f* pTaps, int numBq, const Ipp64f* pDlyLine, Ipp8u* pBuf ) {
  return ippsIIRInit_BiQuad_64f(pState,pTaps,numBq,pDlyLine,pBuf);
}
inline IppStatus ippsIIRInit_BiQuad( IppsIIRState_64fc** pState,
       const Ipp64fc* pTaps, int numBq, const Ipp64fc* pDlyLine, Ipp8u* pBuf ) {
  return ippsIIRInit_BiQuad_64fc(pState,pTaps,numBq,pDlyLine,pBuf);
}
inline IppStatus ippsIIRSetTaps( const Ipp32f *pTaps,
                                                    IppsIIRState_32f* pState ) {
  return ippsIIRSetTaps_32f(pTaps,pState);
}
inline IppStatus ippsIIRSetTaps( const Ipp32fc *pTaps,
                                                   IppsIIRState_32fc* pState ) {
  return ippsIIRSetTaps_32fc(pTaps,pState);
}
inline IppStatus ippsIIRSetTaps( const Ipp64f *pTaps,
                                                    IppsIIRState_64f* pState ) {
  return ippsIIRSetTaps_64f(pTaps,pState);
}
inline IppStatus ippsIIRSetTaps( const Ipp64fc *pTaps,
                                                   IppsIIRState_64fc* pState ) {
  return ippsIIRSetTaps_64fc(pTaps,pState);
}
inline IppStatus ippsFIRInitAlloc(IppsFIRState_32f** pState,
        const Ipp32f* pTaps, int tapsLen, const Ipp32f* pDlyLine) {
  return ippsFIRInitAlloc_32f(pState,pTaps,tapsLen,pDlyLine);
}
inline IppStatus ippsFIRMRInitAlloc(IppsFIRState_32f** pState,
        const Ipp32f* pTaps, int tapsLen, int upFactor, int upPhase,
        int downFactor, int downPhase, const Ipp32f* pDlyLine) {
  return ippsFIRMRInitAlloc_32f(pState,pTaps,tapsLen,upFactor,upPhase,downFactor,downPhase,pDlyLine);
}
inline IppStatus ippsFIRInitAlloc(IppsFIRState_32fc** pState,
        const Ipp32fc* pTaps, int tapsLen, const Ipp32fc* pDlyLine) {
  return ippsFIRInitAlloc_32fc(pState,pTaps,tapsLen,pDlyLine);
}
inline IppStatus ippsFIRMRInitAlloc(IppsFIRState_32fc** pState,
        const Ipp32fc* pTaps, int tapsLen, int upFactor, int upPhase,
        int downFactor, int downPhase, const Ipp32fc* pDlyLine) {
  return ippsFIRMRInitAlloc_32fc(pState,pTaps,tapsLen,upFactor,upPhase,downFactor,downPhase,pDlyLine);
}
inline IppStatus ippsFIRInitAlloc32f(IppsFIRState32f_16s** pState,
        const Ipp32f* pTaps, int tapsLen, const Ipp16s* pDlyLine) {
  return ippsFIRInitAlloc32f_16s(pState,pTaps,tapsLen,pDlyLine);
}
inline IppStatus ippsFIRMRInitAlloc32f(IppsFIRState32f_16s** pState,
        const Ipp32f* pTaps, int tapsLen, int upFactor, int upPhase,
        int downFactor, int downPhase, const Ipp16s* pDlyLine) {
  return ippsFIRMRInitAlloc32f_16s(pState,pTaps,tapsLen,upFactor,upPhase,downFactor,downPhase,pDlyLine);
}
inline IppStatus ippsFIRInitAlloc32fc(IppsFIRState32fc_16sc** pState,
        const Ipp32fc* pTaps, int tapsLen, const Ipp16sc* pDlyLine) {
  return ippsFIRInitAlloc32fc_16sc(pState,pTaps,tapsLen,pDlyLine);
}
inline IppStatus ippsFIRMRInitAlloc32fc(IppsFIRState32fc_16sc** pState,
        const Ipp32fc* pTaps, int tapsLen, int upFactor, int upPhase,
        int downFactor, int downPhase, const Ipp16sc* pDlyLine) {
  return ippsFIRMRInitAlloc32fc_16sc(pState,pTaps,tapsLen,upFactor,upPhase,downFactor,downPhase,pDlyLine);
}
inline IppStatus ippsFIRInitAlloc(IppsFIRState_64f** pState,
        const Ipp64f* pTaps, int tapsLen, const Ipp64f* pDlyLine) {
  return ippsFIRInitAlloc_64f(pState,pTaps,tapsLen,pDlyLine);
}
inline IppStatus ippsFIRMRInitAlloc(IppsFIRState_64f** pState,
        const Ipp64f* pTaps, int tapsLen, int upFactor, int upPhase,
        int downFactor, int downPhase, const Ipp64f* pDlyLine) {
  return ippsFIRMRInitAlloc_64f(pState,pTaps,tapsLen,upFactor,upPhase,downFactor,downPhase,pDlyLine);
}
inline IppStatus ippsFIRInitAlloc(IppsFIRState_64fc** pState,
        const Ipp64fc* pTaps, int tapsLen, const Ipp64fc* pDlyLine) {
  return ippsFIRInitAlloc_64fc(pState,pTaps,tapsLen,pDlyLine);
}
inline IppStatus ippsFIRMRInitAlloc(IppsFIRState_64fc** pState,
        const Ipp64fc* pTaps, int tapsLen, int upFactor, int upPhase,
        int downFactor, int downPhase, const Ipp64fc* pDlyLine) {
  return ippsFIRMRInitAlloc_64fc(pState,pTaps,tapsLen,upFactor,upPhase,downFactor,downPhase,pDlyLine);
}
inline IppStatus ippsFIRInitAlloc64f(IppsFIRState64f_32f** pState,
        const Ipp64f* pTaps, int tapsLen, const Ipp32f* pDlyLine) {
  return ippsFIRInitAlloc64f_32f(pState,pTaps,tapsLen,pDlyLine);
}
inline IppStatus ippsFIRMRInitAlloc64f(IppsFIRState64f_32f** pState,
        const Ipp64f* pTaps, int tapsLen, int upFactor, int upPhase,
        int downFactor, int downPhase, const Ipp32f* pDlyLine) {
  return ippsFIRMRInitAlloc64f_32f(pState,pTaps,tapsLen,upFactor,upPhase,downFactor,downPhase,pDlyLine);
}
inline IppStatus ippsFIRInitAlloc64fc(IppsFIRState64fc_32fc** pState,
        const Ipp64fc* pTaps, int tapsLen, const Ipp32fc* pDlyLine) {
  return ippsFIRInitAlloc64fc_32fc(pState,pTaps,tapsLen,pDlyLine);
}
inline IppStatus ippsFIRMRInitAlloc64fc(IppsFIRState64fc_32fc** pState,
        const Ipp64fc* pTaps, int tapsLen, int upFactor, int upPhase,
        int downFactor, int downPhase, const Ipp32fc* pDlyLine) {
  return ippsFIRMRInitAlloc64fc_32fc(pState,pTaps,tapsLen,upFactor,upPhase,downFactor,downPhase,pDlyLine);
}
inline IppStatus ippsFIRInitAlloc64f(IppsFIRState64f_32s** pState,
        const Ipp64f* pTaps, int tapsLen, const Ipp32s* pDlyLine) {
  return ippsFIRInitAlloc64f_32s(pState,pTaps,tapsLen,pDlyLine);
}
inline IppStatus ippsFIRMRInitAlloc64f(IppsFIRState64f_32s** pState,
        const Ipp64f* pTaps, int tapsLen, int upFactor, int upPhase,
        int downFactor, int downPhase, const Ipp32s* pDlyLine) {
  return ippsFIRMRInitAlloc64f_32s(pState,pTaps,tapsLen,upFactor,upPhase,downFactor,downPhase,pDlyLine);
}
inline IppStatus ippsFIRInitAlloc64fc(IppsFIRState64fc_32sc** pState,
        const Ipp64fc* pTaps, int tapsLen, const Ipp32sc* pDlyLine) {
  return ippsFIRInitAlloc64fc_32sc(pState,pTaps,tapsLen,pDlyLine);
}
inline IppStatus ippsFIRMRInitAlloc64fc(IppsFIRState64fc_32sc** pState,
        const Ipp64fc* pTaps, int tapsLen, int upFactor, int upPhase,
        int downFactor, int downPhase, const Ipp32sc* pDlyLine) {
  return ippsFIRMRInitAlloc64fc_32sc(pState,pTaps,tapsLen,upFactor,upPhase,downFactor,downPhase,pDlyLine);
}
inline IppStatus ippsFIRInitAlloc64f(IppsFIRState64f_16s** pState,
        const Ipp64f* pTaps, int tapsLen, const Ipp16s* pDlyLine) {
  return ippsFIRInitAlloc64f_16s(pState,pTaps,tapsLen,pDlyLine);
}
inline IppStatus ippsFIRMRInitAlloc64f(IppsFIRState64f_16s** pState,
        const Ipp64f* pTaps, int tapsLen, int upFactor, int upPhase,
        int downFactor, int downPhase, const Ipp16s* pDlyLine) {
  return ippsFIRMRInitAlloc64f_16s(pState,pTaps,tapsLen,upFactor,upPhase,downFactor,downPhase,pDlyLine);
}
inline IppStatus ippsFIRInitAlloc64fc(IppsFIRState64fc_16sc** pState,
        const Ipp64fc* pTaps, int tapsLen, const Ipp16sc* pDlyLine) {
  return ippsFIRInitAlloc64fc_16sc(pState,pTaps,tapsLen,pDlyLine);
}
inline IppStatus ippsFIRMRInitAlloc64fc(IppsFIRState64fc_16sc** pState,
        const Ipp64fc* pTaps, int tapsLen, int upFactor, int upPhase,
        int downFactor, int downPhase, const Ipp16sc* pDlyLine) {
  return ippsFIRMRInitAlloc64fc_16sc(pState,pTaps,tapsLen,upFactor,upPhase,downFactor,downPhase,pDlyLine);
}
inline IppStatus ippsFIRInit32s( IppsFIRState32s_16s** pState,
      const Ipp32s *pTaps, int tapsLen, int tapsFactor, const Ipp16s *pDlyLine,
                                                             Ipp8u* pBuffer ) {
  return ippsFIRInit32s_16s(pState,pTaps,tapsLen,tapsFactor,pDlyLine,pBuffer);
}
inline IppStatus ippsFIRMRInit32s( IppsFIRState32s_16s** pState,
   const Ipp32s *pTaps, int tapsLen, int tapsFactor, int upFactor, int upPhase,
         int downFactor, int downPhase, const Ipp16s *pDlyLine, Ipp8u* pBuffer ) {
  return ippsFIRMRInit32s_16s(pState,pTaps,tapsLen,tapsFactor,upFactor,upPhase,downFactor,downPhase,pDlyLine,pBuffer);
}
inline IppStatus ippsFIRInit32sc( IppsFIRState32sc_16sc** pState,
                             const Ipp32sc *pTaps, int tapsLen, int tapsFactor,
                                       const Ipp16sc *pDlyLine, Ipp8u* pBuffer ) {
  return ippsFIRInit32sc_16sc(pState,pTaps,tapsLen,tapsFactor,pDlyLine,pBuffer);
}
inline IppStatus ippsFIRMRInit32sc( IppsFIRState32sc_16sc** pState,
  const Ipp32sc *pTaps, int tapsLen, int tapsFactor, int upFactor, int upPhase,
        int downFactor, int downPhase, const Ipp16sc *pDlyLine, Ipp8u* pBuffer ) {
  return ippsFIRMRInit32sc_16sc(pState,pTaps,tapsLen,tapsFactor,upFactor,upPhase,downFactor,downPhase,pDlyLine,pBuffer);
}
inline IppStatus ippsFIRInit32s( IppsFIRState32s_16s** pState,
      const Ipp32f *pTaps, int tapsLen, const Ipp16s *pDlyLine, Ipp8u* pBuffer ) {
  return ippsFIRInit32s_16s32f(pState,pTaps,tapsLen,pDlyLine,pBuffer);
}
inline IppStatus ippsFIRMRInit32s( IppsFIRState32s_16s** pState,
                   const Ipp32f *pTaps, int tapsLen, int upFactor, int upPhase,
         int downFactor, int downPhase, const Ipp16s *pDlyLine, Ipp8u* pBuffer ) {
  return ippsFIRMRInit32s_16s32f(pState,pTaps,tapsLen,upFactor,upPhase,downFactor,downPhase,pDlyLine,pBuffer);
}
inline IppStatus ippsFIRInit32sc( IppsFIRState32sc_16sc** pState,
    const Ipp32fc *pTaps, int tapsLen, const Ipp16sc *pDlyLine, Ipp8u* pBuffer ) {
  return ippsFIRInit32sc_16sc32fc(pState,pTaps,tapsLen,pDlyLine,pBuffer);
}
inline IppStatus ippsFIRMRInit32sc( IppsFIRState32sc_16sc** pState,
                  const Ipp32fc *pTaps, int tapsLen, int upFactor, int upPhase,
        int downFactor, int downPhase, const Ipp16sc *pDlyLine, Ipp8u* pBuffer ) {
  return ippsFIRMRInit32sc_16sc32fc(pState,pTaps,tapsLen,upFactor,upPhase,downFactor,downPhase,pDlyLine,pBuffer);
}
inline IppStatus ippsFIRInit( IppsFIRState_32f** pState,
   const Ipp32f *pTaps, int tapsLen, const Ipp32f *pDlyLine, Ipp8u *pBuffer ) {
  return ippsFIRInit_32f(pState,pTaps,tapsLen,pDlyLine,pBuffer);
}
inline IppStatus ippsFIRInit( IppsFIRState_32fc** pState,
 const Ipp32fc *pTaps, int tapsLen, const Ipp32fc *pDlyLine, Ipp8u *pBuffer ) {
  return ippsFIRInit_32fc(pState,pTaps,tapsLen,pDlyLine,pBuffer);
}
inline IppStatus ippsFIRMRInit( IppsFIRState_32f** pState,
                   const Ipp32f* pTaps, int tapsLen, int upFactor, int upPhase,
      int downFactor, int downPhase, const Ipp32f* pDlyLine, Ipp8u* pBuffer ) {
  return ippsFIRMRInit_32f(pState,pTaps,tapsLen,upFactor,upPhase,downFactor,downPhase,pDlyLine,pBuffer);
}
inline IppStatus ippsFIRMRInit( IppsFIRState_32fc** pState,
                  const Ipp32fc *pTaps, int tapsLen, int upFactor, int upPhase,
     int downFactor, int downPhase, const Ipp32fc *pDlyLine, Ipp8u* pBuffer ) {
  return ippsFIRMRInit_32fc(pState,pTaps,tapsLen,upFactor,upPhase,downFactor,downPhase,pDlyLine,pBuffer);
}
inline IppStatus ippsFIRInit32f( IppsFIRState32f_16s** pState,
   const Ipp32f *pTaps, int tapsLen, const Ipp16s *pDlyLine, Ipp8u* pBuffer ) {
  return ippsFIRInit32f_16s(pState,pTaps,tapsLen,pDlyLine,pBuffer);
}
inline IppStatus ippsFIRInit32fc(IppsFIRState32fc_16sc** pState,
 const Ipp32fc *pTaps, int tapsLen, const Ipp16sc *pDlyLine, Ipp8u* pBuffer ) {
  return ippsFIRInit32fc_16sc(pState,pTaps,tapsLen,pDlyLine,pBuffer);
}
inline IppStatus ippsFIRMRInit32f( IppsFIRState32f_16s** pState,
                   const Ipp32f* pTaps, int tapsLen, int upFactor, int upPhase,
      int downFactor, int downPhase, const Ipp16s* pDlyLine, Ipp8u* pBuffer ) {
  return ippsFIRMRInit32f_16s(pState,pTaps,tapsLen,upFactor,upPhase,downFactor,downPhase,pDlyLine,pBuffer);
}
inline IppStatus ippsFIRMRInit32fc( IppsFIRState32fc_16sc** pState,
                  const Ipp32fc *pTaps, int tapsLen, int upFactor, int upPhase,
     int downFactor, int downPhase, const Ipp16sc *pDlyLine, Ipp8u* pBuffer ) {
  return ippsFIRMRInit32fc_16sc(pState,pTaps,tapsLen,upFactor,upPhase,downFactor,downPhase,pDlyLine,pBuffer);
}
inline IppStatus ippsFIRInit( IppsFIRState_64f** pState,
   const Ipp64f *pTaps, int tapsLen, const Ipp64f *pDlyLine, Ipp8u *pBuffer ) {
  return ippsFIRInit_64f(pState,pTaps,tapsLen,pDlyLine,pBuffer);
}
inline IppStatus ippsFIRInit( IppsFIRState_64fc** pState,
 const Ipp64fc *pTaps, int tapsLen, const Ipp64fc *pDlyLine, Ipp8u *pBuffer ) {
  return ippsFIRInit_64fc(pState,pTaps,tapsLen,pDlyLine,pBuffer);
}
inline IppStatus ippsFIRMRInit( IppsFIRState_64f** pState,
                   const Ipp64f* pTaps, int tapsLen, int upFactor, int upPhase,
      int downFactor, int downPhase, const Ipp64f* pDlyLine, Ipp8u* pBuffer ) {
  return ippsFIRMRInit_64f(pState,pTaps,tapsLen,upFactor,upPhase,downFactor,downPhase,pDlyLine,pBuffer);
}
inline IppStatus ippsFIRMRInit( IppsFIRState_64fc** pState,
                  const Ipp64fc *pTaps, int tapsLen, int upFactor, int upPhase,
     int downFactor, int downPhase, const Ipp64fc *pDlyLine, Ipp8u* pBuffer ) {
  return ippsFIRMRInit_64fc(pState,pTaps,tapsLen,upFactor,upPhase,downFactor,downPhase,pDlyLine,pBuffer);
}
inline IppStatus ippsFIRInit64f( IppsFIRState64f_16s** pState,
   const Ipp64f *pTaps, int tapsLen, const Ipp16s *pDlyLine, Ipp8u* pBuffer ) {
  return ippsFIRInit64f_16s(pState,pTaps,tapsLen,pDlyLine,pBuffer);
}
inline IppStatus ippsFIRInit64fc(IppsFIRState64fc_16sc** pState,
 const Ipp64fc *pTaps, int tapsLen, const Ipp16sc *pDlyLine, Ipp8u* pBuffer ) {
  return ippsFIRInit64fc_16sc(pState,pTaps,tapsLen,pDlyLine,pBuffer);
}
inline IppStatus ippsFIRMRInit64f( IppsFIRState64f_16s** pState,
                   const Ipp64f* pTaps, int tapsLen, int upFactor, int upPhase,
      int downFactor, int downPhase, const Ipp16s* pDlyLine, Ipp8u* pBuffer ) {
  return ippsFIRMRInit64f_16s(pState,pTaps,tapsLen,upFactor,upPhase,downFactor,downPhase,pDlyLine,pBuffer);
}
inline IppStatus ippsFIRMRInit64fc( IppsFIRState64fc_16sc** pState,
                  const Ipp64fc *pTaps, int tapsLen, int upFactor, int upPhase,
     int downFactor, int downPhase, const Ipp16sc *pDlyLine, Ipp8u* pBuffer ) {
  return ippsFIRMRInit64fc_16sc(pState,pTaps,tapsLen,upFactor,upPhase,downFactor,downPhase,pDlyLine,pBuffer);
}
inline IppStatus ippsFIRInit64f( IppsFIRState64f_32s** pState,
   const Ipp64f *pTaps, int tapsLen, const Ipp32s *pDlyLine, Ipp8u* pBuffer ) {
  return ippsFIRInit64f_32s(pState,pTaps,tapsLen,pDlyLine,pBuffer);
}
inline IppStatus ippsFIRInit64fc(IppsFIRState64fc_32sc** pState,
 const Ipp64fc *pTaps, int tapsLen, const Ipp32sc *pDlyLine, Ipp8u* pBuffer ) {
  return ippsFIRInit64fc_32sc(pState,pTaps,tapsLen,pDlyLine,pBuffer);
}
inline IppStatus ippsFIRMRInit64f( IppsFIRState64f_32s** pState,
                   const Ipp64f* pTaps, int tapsLen, int upFactor, int upPhase,
      int downFactor, int downPhase, const Ipp32s* pDlyLine, Ipp8u* pBuffer ) {
  return ippsFIRMRInit64f_32s(pState,pTaps,tapsLen,upFactor,upPhase,downFactor,downPhase,pDlyLine,pBuffer);
}
inline IppStatus ippsFIRMRInit64fc( IppsFIRState64fc_32sc** pState,
                  const Ipp64fc *pTaps, int tapsLen, int upFactor, int upPhase,
     int downFactor, int downPhase, const Ipp32sc *pDlyLine, Ipp8u* pBuffer ) {
  return ippsFIRMRInit64fc_32sc(pState,pTaps,tapsLen,upFactor,upPhase,downFactor,downPhase,pDlyLine,pBuffer);
}
inline IppStatus ippsFIRInit64f( IppsFIRState64f_32f** pState,
   const Ipp64f *pTaps, int tapsLen, const Ipp32f *pDlyLine, Ipp8u* pBuffer ) {
  return ippsFIRInit64f_32f(pState,pTaps,tapsLen,pDlyLine,pBuffer);
}
inline IppStatus ippsFIRInit64fc(IppsFIRState64fc_32fc** pState,
 const Ipp64fc *pTaps, int tapsLen, const Ipp32fc *pDlyLine, Ipp8u* pBuffer ) {
  return ippsFIRInit64fc_32fc(pState,pTaps,tapsLen,pDlyLine,pBuffer);
}
inline IppStatus ippsFIRMRInit64f( IppsFIRState64f_32f** pState,
                   const Ipp64f* pTaps, int tapsLen, int upFactor, int upPhase,
      int downFactor, int downPhase, const Ipp32f* pDlyLine, Ipp8u* pBuffer ) {
  return ippsFIRMRInit64f_32f(pState,pTaps,tapsLen,upFactor,upPhase,downFactor,downPhase,pDlyLine,pBuffer);
}
inline IppStatus ippsFIRMRInit64fc( IppsFIRState64fc_32fc** pState,
                  const Ipp64fc *pTaps, int tapsLen, int upFactor, int upPhase,
     int downFactor, int downPhase, const Ipp32fc *pDlyLine, Ipp8u* pBuffer ) {
  return ippsFIRMRInit64fc_32fc(pState,pTaps,tapsLen,upFactor,upPhase,downFactor,downPhase,pDlyLine,pBuffer);
}
inline IppStatus ippsFIRGetTaps(const IppsFIRState_32f* pState, Ipp32f* pTaps) {
  return ippsFIRGetTaps_32f(pState,pTaps);
}
inline IppStatus ippsFIRGetTaps(const IppsFIRState_32fc* pState, Ipp32fc* pTaps) {
  return ippsFIRGetTaps_32fc(pState,pTaps);
}
inline IppStatus ippsFIRGetTaps(const IppsFIRState_64f* pState, Ipp64f* pTaps) {
  return ippsFIRGetTaps_64f(pState,pTaps);
}
inline IppStatus ippsFIRGetTaps(const IppsFIRState_64fc* pState, Ipp64fc* pTaps) {
  return ippsFIRGetTaps_64fc(pState,pTaps);
}
inline IppStatus ippsFIRSetTaps( const Ipp32f *pTaps,
                                                    IppsFIRState_32f* pState ) {
  return ippsFIRSetTaps_32f(pTaps,pState);
}
inline IppStatus ippsFIRSetTaps( const Ipp32fc *pTaps,
                                                   IppsFIRState_32fc* pState ) {
  return ippsFIRSetTaps_32fc(pTaps,pState);
}
inline IppStatus ippsFIRSetTaps( const Ipp64f *pTaps,
                                                    IppsFIRState_64f* pState ) {
  return ippsFIRSetTaps_64f(pTaps,pState);
}
inline IppStatus ippsFIRSetTaps( const Ipp64fc *pTaps,
                                                   IppsFIRState_64fc* pState ) {
  return ippsFIRSetTaps_64fc(pTaps,pState);
}
inline IppStatus ippsFIRGetDlyLine(const IppsFIRState_32f* pState, Ipp32f* pDlyLine) {
  return ippsFIRGetDlyLine_32f(pState,pDlyLine);
}
inline IppStatus ippsFIRSetDlyLine(IppsFIRState_32f* pState, const Ipp32f* pDlyLine) {
  return ippsFIRSetDlyLine_32f(pState,pDlyLine);
}
inline IppStatus ippsFIRGetDlyLine(const IppsFIRState_32fc* pState, Ipp32fc* pDlyLine) {
  return ippsFIRGetDlyLine_32fc(pState,pDlyLine);
}
inline IppStatus ippsFIRSetDlyLine(IppsFIRState_32fc* pState, const Ipp32fc* pDlyLine) {
  return ippsFIRSetDlyLine_32fc(pState,pDlyLine);
}
inline IppStatus ippsFIRGetDlyLine32f(const IppsFIRState32f_16s* pState, Ipp16s* pDlyLine) {
  return ippsFIRGetDlyLine32f_16s(pState,pDlyLine);
}
inline IppStatus ippsFIRSetDlyLine32f(IppsFIRState32f_16s* pState, const Ipp16s* pDlyLine) {
  return ippsFIRSetDlyLine32f_16s(pState,pDlyLine);
}
inline IppStatus ippsFIRGetDlyLine32fc(const IppsFIRState32fc_16sc* pState, Ipp16sc* pDlyLine) {
  return ippsFIRGetDlyLine32fc_16sc(pState,pDlyLine);
}
inline IppStatus ippsFIRSetDlyLine32fc(IppsFIRState32fc_16sc* pState, const Ipp16sc* pDlyLine) {
  return ippsFIRSetDlyLine32fc_16sc(pState,pDlyLine);
}
inline IppStatus ippsFIRGetDlyLine(const IppsFIRState_64f* pState, Ipp64f* pDlyLine) {
  return ippsFIRGetDlyLine_64f(pState,pDlyLine);
}
inline IppStatus ippsFIRSetDlyLine(IppsFIRState_64f* pState, const Ipp64f* pDlyLine) {
  return ippsFIRSetDlyLine_64f(pState,pDlyLine);
}
inline IppStatus ippsFIRGetDlyLine(const IppsFIRState_64fc* pState, Ipp64fc* pDlyLine) {
  return ippsFIRGetDlyLine_64fc(pState,pDlyLine);
}
inline IppStatus ippsFIRSetDlyLine(IppsFIRState_64fc* pState, const Ipp64fc* pDlyLine) {
  return ippsFIRSetDlyLine_64fc(pState,pDlyLine);
}
inline IppStatus ippsFIRGetDlyLine64f(const IppsFIRState64f_32f* pState, Ipp32f* pDlyLine) {
  return ippsFIRGetDlyLine64f_32f(pState,pDlyLine);
}
inline IppStatus ippsFIRSetDlyLine64f(IppsFIRState64f_32f* pState, const Ipp32f* pDlyLine) {
  return ippsFIRSetDlyLine64f_32f(pState,pDlyLine);
}
inline IppStatus ippsFIRGetDlyLine64fc(const IppsFIRState64fc_32fc* pState, Ipp32fc* pDlyLine) {
  return ippsFIRGetDlyLine64fc_32fc(pState,pDlyLine);
}
inline IppStatus ippsFIRSetDlyLine64fc(IppsFIRState64fc_32fc* pState, const Ipp32fc* pDlyLine) {
  return ippsFIRSetDlyLine64fc_32fc(pState,pDlyLine);
}
inline IppStatus ippsFIRGetDlyLine64f(const IppsFIRState64f_32s* pState, Ipp32s* pDlyLine) {
  return ippsFIRGetDlyLine64f_32s(pState,pDlyLine);
}
inline IppStatus ippsFIRSetDlyLine64f(IppsFIRState64f_32s* pState, const Ipp32s* pDlyLine) {
  return ippsFIRSetDlyLine64f_32s(pState,pDlyLine);
}
inline IppStatus ippsFIRGetDlyLine64fc(const IppsFIRState64fc_32sc* pState, Ipp32sc* pDlyLine) {
  return ippsFIRGetDlyLine64fc_32sc(pState,pDlyLine);
}
inline IppStatus ippsFIRSetDlyLine64fc(IppsFIRState64fc_32sc* pState, const Ipp32sc* pDlyLine) {
  return ippsFIRSetDlyLine64fc_32sc(pState,pDlyLine);
}
inline IppStatus ippsFIRGetDlyLine64f(const IppsFIRState64f_16s* pState, Ipp16s* pDlyLine) {
  return ippsFIRGetDlyLine64f_16s(pState,pDlyLine);
}
inline IppStatus ippsFIRSetDlyLine64f(IppsFIRState64f_16s* pState, const Ipp16s* pDlyLine) {
  return ippsFIRSetDlyLine64f_16s(pState,pDlyLine);
}
inline IppStatus ippsFIRGetDlyLine64fc(const IppsFIRState64fc_16sc* pState, Ipp16sc* pDlyLine) {
  return ippsFIRGetDlyLine64fc_16sc(pState,pDlyLine);
}
inline IppStatus ippsFIRSetDlyLine64fc(IppsFIRState64fc_16sc* pState, const Ipp16sc* pDlyLine) {
  return ippsFIRSetDlyLine64fc_16sc(pState,pDlyLine);
}
inline IppStatus ippsFIROne(Ipp32f src, Ipp32f* pDstVal, IppsFIRState_32f* pState) {
  return ippsFIROne_32f(src,pDstVal,pState);
}
inline IppStatus ippsFIROne(Ipp32fc src, Ipp32fc* pDstVal, IppsFIRState_32fc* pState) {
  return ippsFIROne_32fc(src,pDstVal,pState);
}
inline IppStatus ippsFIROne32f_Sfs(Ipp16s src, Ipp16s* pDstVal,
        IppsFIRState32f_16s* pState, int scaleFactor ) {
  return ippsFIROne32f_16s_Sfs(src,pDstVal,pState,scaleFactor);
}
inline IppStatus ippsFIROne32fc_Sfs(Ipp16sc src, Ipp16sc* pDstVal,
        IppsFIRState32fc_16sc* pState,  int scaleFactor ) {
  return ippsFIROne32fc_16sc_Sfs(src,pDstVal,pState,scaleFactor);
}
inline IppStatus ippsFIROne(Ipp64f src, Ipp64f* pDstVal, IppsFIRState_64f* pState) {
  return ippsFIROne_64f(src,pDstVal,pState);
}
inline IppStatus ippsFIROne(Ipp64fc src, Ipp64fc* pDstVal, IppsFIRState_64fc* pState) {
  return ippsFIROne_64fc(src,pDstVal,pState);
}
inline IppStatus ippsFIROne64f(Ipp32f src, Ipp32f* pDstVal, IppsFIRState64f_32f* pState) {
  return ippsFIROne64f_32f(src,pDstVal,pState);
}
inline IppStatus ippsFIROne64fc(Ipp32fc src, Ipp32fc* pDstVal, IppsFIRState64fc_32fc* pState) {
  return ippsFIROne64fc_32fc(src,pDstVal,pState);
}
inline IppStatus ippsFIROne64f_Sfs(Ipp32s src, Ipp32s* pDstVal,
        IppsFIRState64f_32s* pState, int scaleFactor ) {
  return ippsFIROne64f_32s_Sfs(src,pDstVal,pState,scaleFactor);
}
inline IppStatus ippsFIROne64fc_Sfs(Ipp32sc src, Ipp32sc* pDstVal,
        IppsFIRState64fc_32sc* pState,  int scaleFactor ) {
  return ippsFIROne64fc_32sc_Sfs(src,pDstVal,pState,scaleFactor);
}
inline IppStatus ippsFIROne64f_Sfs(Ipp16s src, Ipp16s* pDstVal,
        IppsFIRState64f_16s* pState,  int scaleFactor ) {
  return ippsFIROne64f_16s_Sfs(src,pDstVal,pState,scaleFactor);
}
inline IppStatus ippsFIROne64fc_Sfs(Ipp16sc src, Ipp16sc* pDstVal,
         IppsFIRState64fc_16sc* pState, int scaleFactor ) {
  return ippsFIROne64fc_16sc_Sfs(src,pDstVal,pState,scaleFactor);
}
inline IppStatus ippsFIR(const Ipp32f* pSrc, Ipp32f* pDst, int numIters,
        IppsFIRState_32f* pState) {
  return ippsFIR_32f(pSrc,pDst,numIters,pState);
}
inline IppStatus ippsFIR(const Ipp32fc* pSrc, Ipp32fc* pDst, int numIters,
        IppsFIRState_32fc* pState) {
  return ippsFIR_32fc(pSrc,pDst,numIters,pState);
}
inline IppStatus ippsFIR32f_Sfs(const Ipp16s* pSrc, Ipp16s* pDst, int numIters,
        IppsFIRState32f_16s* pState, int scaleFactor ) {
  return ippsFIR32f_16s_Sfs(pSrc,pDst,numIters,pState,scaleFactor);
}
inline IppStatus ippsFIR32fc_Sfs(const Ipp16sc* pSrc, Ipp16sc* pDst, int numIters,
        IppsFIRState32fc_16sc* pState, int scaleFactor ) {
  return ippsFIR32fc_16sc_Sfs(pSrc,pDst,numIters,pState,scaleFactor);
}
inline IppStatus ippsFIR_I(Ipp32f* pSrcDst, int numIters,
        IppsFIRState_32f* pState) {
  return ippsFIR_32f_I(pSrcDst,numIters,pState);
}
inline IppStatus ippsFIR_I(Ipp32fc* pSrcDst, int numIters,
        IppsFIRState_32fc* pState) {
  return ippsFIR_32fc_I(pSrcDst,numIters,pState);
}
inline IppStatus ippsFIR32f_ISfs(Ipp16s* pSrcDst, int numIters,
        IppsFIRState32f_16s* pState, int scaleFactor ) {
  return ippsFIR32f_16s_ISfs(pSrcDst,numIters,pState,scaleFactor);
}
inline IppStatus ippsFIR32fc_ISfs(Ipp16sc* pSrcDst, int numIters,
        IppsFIRState32fc_16sc* pState, int scaleFactor ) {
  return ippsFIR32fc_16sc_ISfs(pSrcDst,numIters,pState,scaleFactor);
}
inline IppStatus ippsFIR(const Ipp64f* pSrc, Ipp64f* pDst, int numIters,
        IppsFIRState_64f* pState) {
  return ippsFIR_64f(pSrc,pDst,numIters,pState);
}
inline IppStatus ippsFIR(const Ipp64fc* pSrc, Ipp64fc* pDst, int numIters,
        IppsFIRState_64fc* pState) {
  return ippsFIR_64fc(pSrc,pDst,numIters,pState);
}
inline IppStatus ippsFIR_I(Ipp64f* pSrcDst, int numIters,
        IppsFIRState_64f* pState) {
  return ippsFIR_64f_I(pSrcDst,numIters,pState);
}
inline IppStatus ippsFIR_I(Ipp64fc* pSrcDst, int numIters,
        IppsFIRState_64fc* pState) {
  return ippsFIR_64fc_I(pSrcDst,numIters,pState);
}
inline IppStatus ippsFIR64f(const Ipp32f* pSrc, Ipp32f* pDst, int numIters,
        IppsFIRState64f_32f* pState) {
  return ippsFIR64f_32f(pSrc,pDst,numIters,pState);
}
inline IppStatus ippsFIR64fc(const Ipp32fc* pSrc, Ipp32fc* pDst, int numIters,
        IppsFIRState64fc_32fc* pState) {
  return ippsFIR64fc_32fc(pSrc,pDst,numIters,pState);
}
inline IppStatus ippsFIR64f_I(Ipp32f* pSrcDst, int numIters,
        IppsFIRState64f_32f* pState) {
  return ippsFIR64f_32f_I(pSrcDst,numIters,pState);
}
inline IppStatus ippsFIR64fc_I(Ipp32fc* pSrcDst, int numIters,
        IppsFIRState64fc_32fc* pState) {
  return ippsFIR64fc_32fc_I(pSrcDst,numIters,pState);
}
inline IppStatus ippsFIR64f_Sfs(const Ipp32s* pSrc, Ipp32s* pDst, int numIters,
        IppsFIRState64f_32s* pState, int scaleFactor ) {
  return ippsFIR64f_32s_Sfs(pSrc,pDst,numIters,pState,scaleFactor);
}
inline IppStatus ippsFIR64fc_Sfs(const Ipp32sc* pSrc, Ipp32sc* pDst, int numIters,
        IppsFIRState64fc_32sc* pState, int scaleFactor ) {
  return ippsFIR64fc_32sc_Sfs(pSrc,pDst,numIters,pState,scaleFactor);
}
inline IppStatus ippsFIR64f_ISfs(Ipp32s* pSrcDst, int numIters,
        IppsFIRState64f_32s* pState,  int scaleFactor ) {
  return ippsFIR64f_32s_ISfs(pSrcDst,numIters,pState,scaleFactor);
}
inline IppStatus ippsFIR64fc_ISfs(Ipp32sc* pSrcDst, int numIters,
        IppsFIRState64fc_32sc* pState,  int scaleFactor ) {
  return ippsFIR64fc_32sc_ISfs(pSrcDst,numIters,pState,scaleFactor);
}
inline IppStatus ippsFIR64f_Sfs(const Ipp16s* pSrc, Ipp16s* pDst, int numIters,
        IppsFIRState64f_16s* pState,  int scaleFactor ) {
  return ippsFIR64f_16s_Sfs(pSrc,pDst,numIters,pState,scaleFactor);
}
inline IppStatus ippsFIR64fc_Sfs(const Ipp16sc* pSrc, Ipp16sc* pDst, int numIters,
        IppsFIRState64fc_16sc* pState, int scaleFactor ) {
  return ippsFIR64fc_16sc_Sfs(pSrc,pDst,numIters,pState,scaleFactor);
}
inline IppStatus ippsFIR64f_ISfs(Ipp16s* pSrcDst, int numIters,
        IppsFIRState64f_16s* pState, int scaleFactor ) {
  return ippsFIR64f_16s_ISfs(pSrcDst,numIters,pState,scaleFactor);
}
inline IppStatus ippsFIR64fc_ISfs(Ipp16sc* pSrcDst, int numIters,
        IppsFIRState64fc_16sc* pState, int scaleFactor ) {
  return ippsFIR64fc_16sc_ISfs(pSrcDst,numIters,pState,scaleFactor);
}
inline IppStatus ippsFIRInitAlloc32s(IppsFIRState32s_16s** pState,
        const Ipp32s *pTaps, int tapsLen, int tapsFactor, const Ipp16s *pDlyLine) {
  return ippsFIRInitAlloc32s_16s(pState,pTaps,tapsLen,tapsFactor,pDlyLine);
}
inline IppStatus ippsFIRMRInitAlloc32s(IppsFIRState32s_16s** pState,
        const Ipp32s *pTaps, int tapsLen, int tapsFactor, int upFactor,
        int upPhase, int downFactor, int downPhase, const Ipp16s *pDlyLine) {
  return ippsFIRMRInitAlloc32s_16s(pState,pTaps,tapsLen,tapsFactor,upFactor,upPhase,downFactor,downPhase,pDlyLine);
}
inline IppStatus ippsFIRInitAlloc32s(IppsFIRState32s_16s** pState,
        const Ipp32f *pTaps, int tapsLen, const Ipp16s *pDlyLine) {
  return ippsFIRInitAlloc32s_16s32f(pState,pTaps,tapsLen,pDlyLine);
}
inline IppStatus ippsFIRMRInitAlloc32s(IppsFIRState32s_16s **pState,
        const Ipp32f *pTaps, int tapsLen, int upFactor, int upPhase,
        int downFactor, int downPhase, const Ipp16s *pDlyLine) {
  return ippsFIRMRInitAlloc32s_16s32f(pState,pTaps,tapsLen,upFactor,upPhase,downFactor,downPhase,pDlyLine);
}
inline IppStatus ippsFIRInitAlloc32sc(IppsFIRState32sc_16sc** pState,
        const Ipp32sc *pTaps, int tapsLen, int tapsFactor, const Ipp16sc *pDlyLine) {
  return ippsFIRInitAlloc32sc_16sc(pState,pTaps,tapsLen,tapsFactor,pDlyLine);
}
inline IppStatus ippsFIRMRInitAlloc32sc(IppsFIRState32sc_16sc** pState,
        const Ipp32sc *pTaps, int tapsLen, int tapsFactor, int upFactor,
        int upPhase, int downFactor, int downPhase, const Ipp16sc *pDlyLine) {
  return ippsFIRMRInitAlloc32sc_16sc(pState,pTaps,tapsLen,tapsFactor,upFactor,upPhase,downFactor,downPhase,pDlyLine);
}
inline IppStatus ippsFIRInitAlloc32sc(IppsFIRState32sc_16sc** pState,
        const Ipp32fc *pTaps, int tapsLen, const Ipp16sc *pDlyLine) {
  return ippsFIRInitAlloc32sc_16sc32fc(pState,pTaps,tapsLen,pDlyLine);
}
inline IppStatus ippsFIRMRInitAlloc32sc(IppsFIRState32sc_16sc** pState,
        const Ipp32fc *pTaps, int tapsLen, int upFactor, int upPhase,
        int downFactor, int downPhase, const Ipp16sc *pDlyLine) {
  return ippsFIRMRInitAlloc32sc_16sc32fc(pState,pTaps,tapsLen,upFactor,upPhase,downFactor,downPhase,pDlyLine);
}
inline IppStatus ippsFIRGetDlyLine32s(const IppsFIRState32s_16s* pState,
        Ipp16s* pDlyLine) {
  return ippsFIRGetDlyLine32s_16s(pState,pDlyLine);
}
inline IppStatus ippsFIRSetDlyLine32s(IppsFIRState32s_16s* pState,
        const Ipp16s* pDlyLine) {
  return ippsFIRSetDlyLine32s_16s(pState,pDlyLine);
}
inline IppStatus ippsFIRGetDlyLine32sc(const IppsFIRState32sc_16sc* pState,
        Ipp16sc* pDlyLine) {
  return ippsFIRGetDlyLine32sc_16sc(pState,pDlyLine);
}
inline IppStatus ippsFIRSetDlyLine32sc(IppsFIRState32sc_16sc* pState,
        const Ipp16sc* pDlyLine) {
  return ippsFIRSetDlyLine32sc_16sc(pState,pDlyLine);
}
inline IppStatus ippsFIROne32s_Sfs(Ipp16s src, Ipp16s *pDstVal,
        IppsFIRState32s_16s *pState, int scaleFactor ) {
  return ippsFIROne32s_16s_Sfs(src,pDstVal,pState,scaleFactor);
}
inline IppStatus ippsFIROne32sc_Sfs(Ipp16sc src, Ipp16sc *pDstVal,
        IppsFIRState32sc_16sc *pState, int scaleFactor ) {
  return ippsFIROne32sc_16sc_Sfs(src,pDstVal,pState,scaleFactor);
}
inline IppStatus ippsFIR32s_Sfs(const Ipp16s *pSrc, Ipp16s *pDst,
        int numIters, IppsFIRState32s_16s *pState, int scaleFactor ) {
  return ippsFIR32s_16s_Sfs(pSrc,pDst,numIters,pState,scaleFactor);
}
inline IppStatus ippsFIR32sc_Sfs(const Ipp16sc *pSrc, Ipp16sc *pDst,
        int numIters, IppsFIRState32sc_16sc *pState, int scaleFactor ) {
  return ippsFIR32sc_16sc_Sfs(pSrc,pDst,numIters,pState,scaleFactor);
}
inline IppStatus ippsFIR32s_ISfs(Ipp16s *pSrcDst, int numIters,
        IppsFIRState32s_16s *pState, int scaleFactor ) {
  return ippsFIR32s_16s_ISfs(pSrcDst,numIters,pState,scaleFactor);
}
inline IppStatus ippsFIR32sc_ISfs(Ipp16sc *pSrcDst, int numIters,
        IppsFIRState32sc_16sc *pState, int scaleFactor ) {
  return ippsFIR32sc_16sc_ISfs(pSrcDst,numIters,pState,scaleFactor);
}
inline IppStatus ippsFIRInitAlloc( IppsFIRState_32s** pState,
                   const Ipp32s *pTaps, int tapsLen, const Ipp32s *pDlyLine ) {
  return ippsFIRInitAlloc_32s(pState,pTaps,tapsLen,pDlyLine);
}
inline IppStatus ippsFIRInit( IppsFIRState_32s** pState,
      const Ipp32s *pTaps, int tapsLen, const Ipp32s *pDlyLine, Ipp8u* pBuf ) {
  return ippsFIRInit_32s(pState,pTaps,tapsLen,pDlyLine,pBuf);
}
inline IppStatus ippsFIRSetTaps( const Ipp32s *pTaps,
                                                   IppsFIRState_32s* pState ) {
  return ippsFIRSetTaps_32s(pTaps,pState);
}
inline IppStatus ippsFIRGetTaps( const IppsFIRState_32s* pState,
                                                              Ipp32s* pTaps ) {
  return ippsFIRGetTaps_32s(pState,pTaps);
}
inline IppStatus ippsFIROne_Sfs( Ipp32s src, Ipp32s *pDstVal,
                                  IppsFIRState_32s *pState, int scaleFactor ) {
  return ippsFIROne_32s_Sfs(src,pDstVal,pState,scaleFactor);
}
inline IppStatus ippsFIR_Sfs( const Ipp32s *pSrc, Ipp32s *pDst,
                    int numIters, IppsFIRState_32s *pState, int scaleFactor ) {
  return ippsFIR_32s_Sfs(pSrc,pDst,numIters,pState,scaleFactor);
}
inline IppStatus ippsFIR_ISfs( Ipp32s *pSrcDst, int numIters,
                                  IppsFIRState_32s *pState, int scaleFactor ) {
  return ippsFIR_32s_ISfs(pSrcDst,numIters,pState,scaleFactor);
}
inline IppStatus ippsFIRLMSOne_Direct( Ipp32f src, Ipp32f refval,
       Ipp32f* pDstVal, Ipp32f* pTapsInv, int tapsLen, float mu, Ipp32f* pDlyLine,
       int* pDlyIndex ) {
  return ippsFIRLMSOne_Direct_32f(src,refval,pDstVal,pTapsInv,tapsLen,mu,pDlyLine,pDlyIndex);
}
inline IppStatus ippsFIRLMSOne_Direct32f( Ipp16s src, Ipp16s refval,
       Ipp16s* pDstVal, Ipp32f* pTapsInv, int tapsLen, float mu, Ipp16s* pDlyLine,
       int* pDlyIndex ) {
  return ippsFIRLMSOne_Direct32f_16s(src,refval,pDstVal,pTapsInv,tapsLen,mu,pDlyLine,pDlyIndex);
}
inline IppStatus ippsFIRLMSOne_DirectQ15( Ipp16s src, Ipp16s refval,
       Ipp16s* pDstVal, Ipp32s* pTapsInv, int tapsLen, int muQ15, Ipp16s* pDlyLine,
       int* pDlyIndex ) {
  return ippsFIRLMSOne_DirectQ15_16s(src,refval,pDstVal,pTapsInv,tapsLen,muQ15,pDlyLine,pDlyIndex);
}
inline IppStatus ippsFIRLMS( const Ipp32f* pSrc, const Ipp32f* pRef,
       Ipp32f* pDst, int len, float mu, IppsFIRLMSState_32f* pState ) {
  return ippsFIRLMS_32f(pSrc,pRef,pDst,len,mu,pState);
}
inline IppStatus ippsFIRLMS32f( const Ipp16s* pSrc, const Ipp16s* pRef,
       Ipp16s* pDst, int len, float mu, IppsFIRLMSState32f_16s* pStatel ) {
  return ippsFIRLMS32f_16s(pSrc,pRef,pDst,len,mu,pStatel);
}
inline IppStatus ippsFIRLMSInitAlloc( IppsFIRLMSState_32f** pState,
   const Ipp32f* pTaps, int tapsLen, const Ipp32f* pDlyLine, int dlyLineIndex ) {
  return ippsFIRLMSInitAlloc_32f(pState,pTaps,tapsLen,pDlyLine,dlyLineIndex);
}
inline IppStatus ippsFIRLMSInitAlloc32f( IppsFIRLMSState32f_16s** pState,
   const Ipp32f* pTaps, int tapsLen, const Ipp16s* pDlyLine, int dlyLineIndex ) {
  return ippsFIRLMSInitAlloc32f_16s(pState,pTaps,tapsLen,pDlyLine,dlyLineIndex);
}
inline IppStatus ippsFIRLMSGetTaps( const IppsFIRLMSState_32f* pState,
       Ipp32f* pOutTaps ) {
  return ippsFIRLMSGetTaps_32f(pState,pOutTaps);
}
inline IppStatus ippsFIRLMSGetDlyLine( const IppsFIRLMSState_32f* pState,
   Ipp32f* pDlyLine, int* pDlyLineIndex ) {
  return ippsFIRLMSGetDlyLine_32f(pState,pDlyLine,pDlyLineIndex);
}
inline IppStatus ippsFIRLMSGetDlyLine32f( const IppsFIRLMSState32f_16s* pState,
   Ipp16s* pDlyLine, int* pDlyLineIndex ) {
  return ippsFIRLMSGetDlyLine32f_16s(pState,pDlyLine,pDlyLineIndex);
}
inline IppStatus ippsFIRLMSSetDlyLine( IppsFIRLMSState_32f* pState,
   const Ipp32f* pDlyLine, int dlyLineIndex ) {
  return ippsFIRLMSSetDlyLine_32f(pState,pDlyLine,dlyLineIndex);
}
inline IppStatus ippsFIRLMSSetDlyLine32f( IppsFIRLMSState32f_16s* pState,
   const Ipp16s* pDlyLine, int dlyLineIndex ) {
  return ippsFIRLMSSetDlyLine32f_16s(pState,pDlyLine,dlyLineIndex);
}
inline IppStatus ippsFIRLMSMROneVal32s( Ipp16s val, Ipp32s* pDstVal,
                                            IppsFIRLMSMRState32s_16s* pState ) {
  return ippsFIRLMSMROneVal32s_16s(val,pDstVal,pState);
}
inline IppStatus ippsFIRLMSMROneVal32sc( Ipp16sc val, Ipp32sc* pDstVal,
                                            IppsFIRLMSMRState32sc_16sc* pState ) {
  return ippsFIRLMSMROneVal32sc_16sc(val,pDstVal,pState);
}
inline IppStatus ippsFIRLMSMRInitAlloc32s( IppsFIRLMSMRState32s_16s** pState,
   const Ipp32s* pTaps, int tapsLen, const Ipp16s* pDlyLine, int dlyLineIndex,
   int dlyStep, int updateDly, int mu ) {
  return ippsFIRLMSMRInitAlloc32s_16s(pState,pTaps,tapsLen,pDlyLine,dlyLineIndex,dlyStep,updateDly,mu);
}
inline IppStatus ippsFIRLMSMRInitAlloc32sc( IppsFIRLMSMRState32sc_16sc** pState,
   const Ipp32sc* pTaps, int tapsLen, const Ipp16sc* pDlyLine, int dlyLineIndex,
   int dlyStep, int updateDly, int mu ) {
  return ippsFIRLMSMRInitAlloc32sc_16sc(pState,pTaps,tapsLen,pDlyLine,dlyLineIndex,dlyStep,updateDly,mu);
}
inline IppStatus ippsFIRLMSMRSetDlyLine32s( IppsFIRLMSMRState32s_16s* pState,
                                        const Ipp16s* pInDlyLine, int dlyLineIndex ) {
  return ippsFIRLMSMRSetDlyLine32s_16s(pState,pInDlyLine,dlyLineIndex);
}
inline IppStatus ippsFIRLMSMRGetDlyLine32s( IppsFIRLMSMRState32s_16s* pState,
                                        Ipp16s* pOutDlyLine, int* pOutDlyIndex ) {
  return ippsFIRLMSMRGetDlyLine32s_16s(pState,pOutDlyLine,pOutDlyIndex);
}
inline IppStatus ippsFIRLMSMRGetDlyVal32s( IppsFIRLMSMRState32s_16s* pState,
                                        Ipp16s* pOutVal, int index ) {
  return ippsFIRLMSMRGetDlyVal32s_16s(pState,pOutVal,index);
}
inline IppStatus ippsFIRLMSMRSetDlyLine32sc( IppsFIRLMSMRState32sc_16sc* pState,
                                        const Ipp16sc* pInDlyLine, int dlyLineIndex ) {
  return ippsFIRLMSMRSetDlyLine32sc_16sc(pState,pInDlyLine,dlyLineIndex);
}
inline IppStatus ippsFIRLMSMRGetDlyLine32sc( IppsFIRLMSMRState32sc_16sc* pState,
                                        Ipp16sc* pOutDlyLine, int* pOutDlyLineIndex ) {
  return ippsFIRLMSMRGetDlyLine32sc_16sc(pState,pOutDlyLine,pOutDlyLineIndex);
}
inline IppStatus ippsFIRLMSMRGetDlyVal32sc( IppsFIRLMSMRState32sc_16sc* pState,
                                        Ipp16sc* pOutVal, int index ) {
  return ippsFIRLMSMRGetDlyVal32sc_16sc(pState,pOutVal,index);
}
inline IppStatus ippsFIRLMSMRPutVal32s( Ipp16s val,
                                            IppsFIRLMSMRState32s_16s* pState ) {
  return ippsFIRLMSMRPutVal32s_16s(val,pState);
}
inline IppStatus ippsFIRLMSMRPutVal32sc( Ipp16sc val,
                                            IppsFIRLMSMRState32sc_16sc* pState ) {
  return ippsFIRLMSMRPutVal32sc_16sc(val,pState);
}
inline IppStatus ippsFIROne_Direct(Ipp32f src, Ipp32f* pDstVal, const Ipp32f* pTaps, int tapsLen,
        Ipp32f* pDlyLine, int* pDlyLineIndex) {
  return ippsFIROne_Direct_32f(src,pDstVal,pTaps,tapsLen,pDlyLine,pDlyLineIndex);
}
inline IppStatus ippsFIROne_Direct(Ipp32fc src, Ipp32fc* pDstVal, const Ipp32fc* pTaps, int tapsLen,
        Ipp32fc* pDlyLine, int* pDlyLineIndex) {
  return ippsFIROne_Direct_32fc(src,pDstVal,pTaps,tapsLen,pDlyLine,pDlyLineIndex);
}
inline IppStatus ippsFIROne_Direct_I(Ipp32f* pSrcDstVal, const Ipp32f* pTaps, int tapsLen,
        Ipp32f* pDlyLine, int* pDlyLineIndex) {
  return ippsFIROne_Direct_32f_I(pSrcDstVal,pTaps,tapsLen,pDlyLine,pDlyLineIndex);
}
inline IppStatus ippsFIROne_Direct_I(Ipp32fc* pSrcDstVal, const Ipp32fc* pTaps, int tapsLen,
        Ipp32fc* pDlyLine, int* pDlyLineIndex) {
  return ippsFIROne_Direct_32fc_I(pSrcDstVal,pTaps,tapsLen,pDlyLine,pDlyLineIndex);
}
inline IppStatus ippsFIROne32f_Direct_Sfs(Ipp16s src, Ipp16s* pDstVal, const Ipp32f* pTaps, int tapsLen,
        Ipp16s* pDlyLine, int* pDlyLineIndex, int scaleFactor ) {
  return ippsFIROne32f_Direct_16s_Sfs(src,pDstVal,pTaps,tapsLen,pDlyLine,pDlyLineIndex,scaleFactor);
}
inline IppStatus ippsFIROne32fc_Direct_Sfs(Ipp16sc src, Ipp16sc* pDstVal, const Ipp32fc* pTaps, int tapsLen,
        Ipp16sc* pDlyLine, int* pDlyLineIndex, int scaleFactor ) {
  return ippsFIROne32fc_Direct_16sc_Sfs(src,pDstVal,pTaps,tapsLen,pDlyLine,pDlyLineIndex,scaleFactor);
}
inline IppStatus ippsFIROne32f_Direct_ISfs(Ipp16s* pSrcDstVal, const Ipp32f* pTaps, int tapsLen,
        Ipp16s* pDlyLine, int* pDlyLineIndex, int scaleFactor ) {
  return ippsFIROne32f_Direct_16s_ISfs(pSrcDstVal,pTaps,tapsLen,pDlyLine,pDlyLineIndex,scaleFactor);
}
inline IppStatus ippsFIROne32fc_Direct_ISfs(Ipp16sc* pSrcDstVal, const Ipp32fc* pTaps, int tapsLen,
        Ipp16sc* pDlyLine, int* pDlyLineIndex, int scaleFactor ) {
  return ippsFIROne32fc_Direct_16sc_ISfs(pSrcDstVal,pTaps,tapsLen,pDlyLine,pDlyLineIndex,scaleFactor);
}
inline IppStatus ippsFIROne_Direct(Ipp64f src, Ipp64f* pDstVal, const Ipp64f* pTaps, int tapsLen,
        Ipp64f* pDlyLine, int* pDlyLineIndex) {
  return ippsFIROne_Direct_64f(src,pDstVal,pTaps,tapsLen,pDlyLine,pDlyLineIndex);
}
inline IppStatus ippsFIROne_Direct(Ipp64fc src, Ipp64fc* pDstVal, const Ipp64fc* pTaps, int tapsLen,
        Ipp64fc* pDlyLine, int* pDlyLineIndex) {
  return ippsFIROne_Direct_64fc(src,pDstVal,pTaps,tapsLen,pDlyLine,pDlyLineIndex);
}
inline IppStatus ippsFIROne_Direct_I(Ipp64f* pSrcDstVal, const Ipp64f* pTaps, int tapsLen,
        Ipp64f* pDlyLine, int* pDlyLineIndex) {
  return ippsFIROne_Direct_64f_I(pSrcDstVal,pTaps,tapsLen,pDlyLine,pDlyLineIndex);
}
inline IppStatus ippsFIROne_Direct_I(Ipp64fc* pSrcDstVal, const Ipp64fc* pTaps, int tapsLen,
        Ipp64fc* pDlyLine, int* pDlyLineIndex) {
  return ippsFIROne_Direct_64fc_I(pSrcDstVal,pTaps,tapsLen,pDlyLine,pDlyLineIndex);
}
inline IppStatus ippsFIROne64f_Direct(Ipp32f src, Ipp32f* pDstVal, const Ipp64f* pTaps, int tapsLen,
        Ipp32f* pDlyLine, int* pDlyLineIndex) {
  return ippsFIROne64f_Direct_32f(src,pDstVal,pTaps,tapsLen,pDlyLine,pDlyLineIndex);
}
inline IppStatus ippsFIROne64fc_Direct(Ipp32fc src, Ipp32fc* pDstVal, const Ipp64fc* pTaps, int tapsLen,
        Ipp32fc* pDlyLine, int* pDlyLineIndex) {
  return ippsFIROne64fc_Direct_32fc(src,pDstVal,pTaps,tapsLen,pDlyLine,pDlyLineIndex);
}
inline IppStatus ippsFIROne64f_Direct_I(Ipp32f* pSrcDstVal, const Ipp64f* pTaps, int tapsLen,
        Ipp32f* pDlyLine, int* pDlyLineIndex) {
  return ippsFIROne64f_Direct_32f_I(pSrcDstVal,pTaps,tapsLen,pDlyLine,pDlyLineIndex);
}
inline IppStatus ippsFIROne64fc_Direct_I(Ipp32fc* pSrcDstVal, const Ipp64fc* pTaps, int tapsLen,
        Ipp32fc* pDlyLine, int* pDlyLineIndex) {
  return ippsFIROne64fc_Direct_32fc_I(pSrcDstVal,pTaps,tapsLen,pDlyLine,pDlyLineIndex);
}
inline IppStatus ippsFIROne64f_Direct_Sfs(Ipp32s src, Ipp32s* pDstVal, const Ipp64f* pTaps, int tapsLen,
        Ipp32s* pDlyLine, int* pDlyLineIndex, int scaleFactor ) {
  return ippsFIROne64f_Direct_32s_Sfs(src,pDstVal,pTaps,tapsLen,pDlyLine,pDlyLineIndex,scaleFactor);
}
inline IppStatus ippsFIROne64fc_Direct_Sfs(Ipp32sc src, Ipp32sc* pDstVal, const Ipp64fc* pTaps, int tapsLen,
        Ipp32sc* pDlyLine, int* pDlyLineIndex, int scaleFactor ) {
  return ippsFIROne64fc_Direct_32sc_Sfs(src,pDstVal,pTaps,tapsLen,pDlyLine,pDlyLineIndex,scaleFactor);
}
inline IppStatus ippsFIROne64f_Direct_ISfs(Ipp32s* pSrcDstVal, const Ipp64f* pTaps, int tapsLen,
        Ipp32s* pDlyLine, int* pDlyLineIndex, int scaleFactor ) {
  return ippsFIROne64f_Direct_32s_ISfs(pSrcDstVal,pTaps,tapsLen,pDlyLine,pDlyLineIndex,scaleFactor);
}
inline IppStatus ippsFIROne64fc_Direct_ISfs(Ipp32sc* pSrcDstVal, const Ipp64fc* pTaps, int tapsLen,
        Ipp32sc* pDlyLine, int* pDlyLineIndex, int scaleFactor ) {
  return ippsFIROne64fc_Direct_32sc_ISfs(pSrcDstVal,pTaps,tapsLen,pDlyLine,pDlyLineIndex,scaleFactor);
}
inline IppStatus ippsFIROne64f_Direct_Sfs(Ipp16s src, Ipp16s* pDstVal, const Ipp64f* pTaps, int tapsLen,
        Ipp16s* pDlyLine, int* pDlyLineIndex, int scaleFactor ) {
  return ippsFIROne64f_Direct_16s_Sfs(src,pDstVal,pTaps,tapsLen,pDlyLine,pDlyLineIndex,scaleFactor);
}
inline IppStatus ippsFIROne64fc_Direct_Sfs(Ipp16sc src, Ipp16sc* pDstVal, const Ipp64fc* pTaps, int tapsLen,
        Ipp16sc* pDlyLine, int* pDlyLineIndex, int scaleFactor ) {
  return ippsFIROne64fc_Direct_16sc_Sfs(src,pDstVal,pTaps,tapsLen,pDlyLine,pDlyLineIndex,scaleFactor);
}
inline IppStatus ippsFIROne64f_Direct_ISfs(Ipp16s* pSrcDstVal, const Ipp64f* pTaps, int tapsLen,
        Ipp16s* pDlyLine, int* pDlyLineIndex, int scaleFactor ) {
  return ippsFIROne64f_Direct_16s_ISfs(pSrcDstVal,pTaps,tapsLen,pDlyLine,pDlyLineIndex,scaleFactor);
}
inline IppStatus ippsFIROne64fc_Direct_ISfs(Ipp16sc* pSrcDstVal, const Ipp64fc* pTaps, int tapsLen,
        Ipp16sc* pDlyLine, int* pDlyLineIndex, int scaleFactor ) {
  return ippsFIROne64fc_Direct_16sc_ISfs(pSrcDstVal,pTaps,tapsLen,pDlyLine,pDlyLineIndex,scaleFactor);
}
inline IppStatus ippsFIROne32s_Direct_Sfs(Ipp16s src, Ipp16s* pDstVal,
        const Ipp32s* pTaps, int tapsLen, int tapsFactor,
        Ipp16s* pDlyLine, int* pDlyLineIndex, int scaleFactor ) {
  return ippsFIROne32s_Direct_16s_Sfs(src,pDstVal,pTaps,tapsLen,tapsFactor,pDlyLine,pDlyLineIndex,scaleFactor);
}
inline IppStatus ippsFIROne32sc_Direct_Sfs(Ipp16sc src, Ipp16sc* pDstVal,
        const Ipp32sc* pTaps, int tapsLen, int tapsFactor,
        Ipp16sc* pDlyLine, int* pDlyLineIndex, int scaleFactor ) {
  return ippsFIROne32sc_Direct_16sc_Sfs(src,pDstVal,pTaps,tapsLen,tapsFactor,pDlyLine,pDlyLineIndex,scaleFactor);
}
inline IppStatus ippsFIROne32s_Direct_ISfs(Ipp16s* pSrcDstVal,
        const Ipp32s* pTaps, int tapsLen, int tapsFactor,
        Ipp16s* pDlyLine, int* pDlyLineIndex, int scaleFactor ) {
  return ippsFIROne32s_Direct_16s_ISfs(pSrcDstVal,pTaps,tapsLen,tapsFactor,pDlyLine,pDlyLineIndex,scaleFactor);
}
inline IppStatus ippsFIROne32sc_Direct_ISfs(Ipp16sc* pSrcDstVal,
        const Ipp32sc* pTaps, int tapsLen, int tapsFactor,
        Ipp16sc* pDlyLine, int* pDlyLineIndex, int scaleFactor ) {
  return ippsFIROne32sc_Direct_16sc_ISfs(pSrcDstVal,pTaps,tapsLen,tapsFactor,pDlyLine,pDlyLineIndex,scaleFactor);
}
inline IppStatus ippsFIR_Direct(const Ipp32f* pSrc, Ipp32f* pDst, int numIters, const Ipp32f* pTaps, int tapsLen,
        Ipp32f* pDlyLine, int* pDlyLineIndex) {
  return ippsFIR_Direct_32f(pSrc,pDst,numIters,pTaps,tapsLen,pDlyLine,pDlyLineIndex);
}
inline IppStatus ippsFIR_Direct(const Ipp32fc* pSrc, Ipp32fc* pDst, int numIters, const Ipp32fc* pTaps, int tapsLen,
        Ipp32fc* pDlyLine, int* pDlyLineIndex) {
  return ippsFIR_Direct_32fc(pSrc,pDst,numIters,pTaps,tapsLen,pDlyLine,pDlyLineIndex);
}
inline IppStatus ippsFIR_Direct_I(Ipp32f* pSrcDst, int numIters, const Ipp32f* pTaps, int tapsLen,
        Ipp32f* pDlyLine, int* pDlyLineIndex) {
  return ippsFIR_Direct_32f_I(pSrcDst,numIters,pTaps,tapsLen,pDlyLine,pDlyLineIndex);
}
inline IppStatus ippsFIR_Direct_I(Ipp32fc* pSrcDst, int numIters, const Ipp32fc* pTaps, int tapsLen,
        Ipp32fc* pDlyLine, int* pDlyLineIndex) {
  return ippsFIR_Direct_32fc_I(pSrcDst,numIters,pTaps,tapsLen,pDlyLine,pDlyLineIndex);
}
inline IppStatus ippsFIR32f_Direct_Sfs(const Ipp16s* pSrc, Ipp16s* pDst, int numIters, const Ipp32f* pTaps, int tapsLen,
        Ipp16s* pDlyLine, int* pDlyLineIndex, int scaleFactor ) {
  return ippsFIR32f_Direct_16s_Sfs(pSrc,pDst,numIters,pTaps,tapsLen,pDlyLine,pDlyLineIndex,scaleFactor);
}
inline IppStatus ippsFIR32fc_Direct_Sfs(const Ipp16sc* pSrc, Ipp16sc* pDst, int numIters, const Ipp32fc* pTaps, int tapsLen,
        Ipp16sc* pDlyLine, int* pDlyLineIndex, int scaleFactor ) {
  return ippsFIR32fc_Direct_16sc_Sfs(pSrc,pDst,numIters,pTaps,tapsLen,pDlyLine,pDlyLineIndex,scaleFactor);
}
inline IppStatus ippsFIR32f_Direct_ISfs(Ipp16s* pSrcDst, int numIters, const Ipp32f* pTaps, int tapsLen,
        Ipp16s* pDlyLine, int* pDlyLineIndex, int scaleFactor ) {
  return ippsFIR32f_Direct_16s_ISfs(pSrcDst,numIters,pTaps,tapsLen,pDlyLine,pDlyLineIndex,scaleFactor);
}
inline IppStatus ippsFIR32fc_Direct_ISfs(Ipp16sc* pSrcDst, int numIters, const Ipp32fc* pTaps, int tapsLen,
        Ipp16sc* pDlyLine, int* pDlyLineIndex, int scaleFactor ) {
  return ippsFIR32fc_Direct_16sc_ISfs(pSrcDst,numIters,pTaps,tapsLen,pDlyLine,pDlyLineIndex,scaleFactor);
}
inline IppStatus ippsFIR_Direct(const Ipp64f* pSrc, Ipp64f* pDst, int numIters, const Ipp64f* pTaps, int tapsLen,
        Ipp64f* pDlyLine, int* pDlyLineIndex) {
  return ippsFIR_Direct_64f(pSrc,pDst,numIters,pTaps,tapsLen,pDlyLine,pDlyLineIndex);
}
inline IppStatus ippsFIR_Direct(const Ipp64fc* pSrc, Ipp64fc* pDst, int numIters, const Ipp64fc* pTaps, int tapsLen,
        Ipp64fc* pDlyLine, int* pDlyLineIndex) {
  return ippsFIR_Direct_64fc(pSrc,pDst,numIters,pTaps,tapsLen,pDlyLine,pDlyLineIndex);
}
inline IppStatus ippsFIR_Direct_I(Ipp64f* pSrcDst, int numIters, const Ipp64f* pTaps, int tapsLen,
        Ipp64f* pDlyLine, int* pDlyLineIndex) {
  return ippsFIR_Direct_64f_I(pSrcDst,numIters,pTaps,tapsLen,pDlyLine,pDlyLineIndex);
}
inline IppStatus ippsFIR_Direct_I(Ipp64fc* pSrcDst, int numIters, const Ipp64fc* pTaps, int tapsLen,
        Ipp64fc* pDlyLine, int* pDlyLineIndex) {
  return ippsFIR_Direct_64fc_I(pSrcDst,numIters,pTaps,tapsLen,pDlyLine,pDlyLineIndex);
}
inline IppStatus ippsFIR64f_Direct(const Ipp32f* pSrc, Ipp32f* pDst, int numIters, const Ipp64f* pTaps, int tapsLen,
        Ipp32f* pDlyLine, int* pDlyLineIndex) {
  return ippsFIR64f_Direct_32f(pSrc,pDst,numIters,pTaps,tapsLen,pDlyLine,pDlyLineIndex);
}
inline IppStatus ippsFIR64fc_Direct(const Ipp32fc* pSrc, Ipp32fc* pDst, int numIters, const Ipp64fc* pTaps, int tapsLen,
        Ipp32fc* pDlyLine, int* pDlyLineIndex) {
  return ippsFIR64fc_Direct_32fc(pSrc,pDst,numIters,pTaps,tapsLen,pDlyLine,pDlyLineIndex);
}
inline IppStatus ippsFIR64f_Direct_I(Ipp32f* pSrcDst, int numIters, const Ipp64f* pTaps, int tapsLen,
        Ipp32f* pDlyLine, int* pDlyLineIndex) {
  return ippsFIR64f_Direct_32f_I(pSrcDst,numIters,pTaps,tapsLen,pDlyLine,pDlyLineIndex);
}
inline IppStatus ippsFIR64fc_Direct_I(Ipp32fc* pSrcDst, int numIters, const Ipp64fc* pTaps, int tapsLen,
        Ipp32fc* pDlyLine, int* pDlyLineIndex) {
  return ippsFIR64fc_Direct_32fc_I(pSrcDst,numIters,pTaps,tapsLen,pDlyLine,pDlyLineIndex);
}
inline IppStatus ippsFIR64f_Direct_Sfs(const Ipp32s* pSrc, Ipp32s* pDst, int numIters, const Ipp64f* pTaps, int tapsLen,
        Ipp32s* pDlyLine, int* pDlyLineIndex, int scaleFactor ) {
  return ippsFIR64f_Direct_32s_Sfs(pSrc,pDst,numIters,pTaps,tapsLen,pDlyLine,pDlyLineIndex,scaleFactor);
}
inline IppStatus ippsFIR64fc_Direct_Sfs(const Ipp32sc* pSrc, Ipp32sc* pDst, int numIters, const Ipp64fc* pTaps, int tapsLen,
        Ipp32sc* pDlyLine, int* pDlyLineIndex, int scaleFactor ) {
  return ippsFIR64fc_Direct_32sc_Sfs(pSrc,pDst,numIters,pTaps,tapsLen,pDlyLine,pDlyLineIndex,scaleFactor);
}
inline IppStatus ippsFIR64f_Direct_ISfs(Ipp32s* pSrcDst, int numIters, const Ipp64f* pTaps, int tapsLen,
        Ipp32s* pDlyLine, int* pDlyLineIndex, int scaleFactor ) {
  return ippsFIR64f_Direct_32s_ISfs(pSrcDst,numIters,pTaps,tapsLen,pDlyLine,pDlyLineIndex,scaleFactor);
}
inline IppStatus ippsFIR64fc_Direct_ISfs(Ipp32sc* pSrcDst, int numIters, const Ipp64fc* pTaps, int tapsLen,
        Ipp32sc* pDlyLine, int* pDlyLineIndex, int scaleFactor ) {
  return ippsFIR64fc_Direct_32sc_ISfs(pSrcDst,numIters,pTaps,tapsLen,pDlyLine,pDlyLineIndex,scaleFactor);
}
inline IppStatus ippsFIR64f_Direct_Sfs(const Ipp16s* pSrc, Ipp16s* pDst, int numIters, const Ipp64f* pTaps, int tapsLen,
        Ipp16s* pDlyLine, int* pDlyLineIndex, int scaleFactor ) {
  return ippsFIR64f_Direct_16s_Sfs(pSrc,pDst,numIters,pTaps,tapsLen,pDlyLine,pDlyLineIndex,scaleFactor);
}
inline IppStatus ippsFIR64fc_Direct_Sfs(const Ipp16sc* pSrc, Ipp16sc* pDst, int numIters, const Ipp64fc* pTaps, int tapsLen,
        Ipp16sc* pDlyLine, int* pDlyLineIndex, int scaleFactor ) {
  return ippsFIR64fc_Direct_16sc_Sfs(pSrc,pDst,numIters,pTaps,tapsLen,pDlyLine,pDlyLineIndex,scaleFactor);
}
inline IppStatus ippsFIR64f_Direct_ISfs(Ipp16s* pSrcDst, int numIters, const Ipp64f* pTaps, int tapsLen,
        Ipp16s* pDlyLine, int* pDlyLineIndex, int scaleFactor ) {
  return ippsFIR64f_Direct_16s_ISfs(pSrcDst,numIters,pTaps,tapsLen,pDlyLine,pDlyLineIndex,scaleFactor);
}
inline IppStatus ippsFIR64fc_Direct_ISfs(Ipp16sc* pSrcDst, int numIters, const Ipp64fc* pTaps, int tapsLen,
        Ipp16sc* pDlyLine, int* pDlyLineIndex, int scaleFactor ) {
  return ippsFIR64fc_Direct_16sc_ISfs(pSrcDst,numIters,pTaps,tapsLen,pDlyLine,pDlyLineIndex,scaleFactor);
}
inline IppStatus ippsFIR32s_Direct_Sfs(const Ipp16s* pSrc, Ipp16s* pDst, int numIters,
        const Ipp32s* pTaps, int tapsLen, int tapsFactor,
        Ipp16s* pDlyLine, int* pDlyLineIndex, int scaleFactor ) {
  return ippsFIR32s_Direct_16s_Sfs(pSrc,pDst,numIters,pTaps,tapsLen,tapsFactor,pDlyLine,pDlyLineIndex,scaleFactor);
}
inline IppStatus ippsFIR32sc_Direct_Sfs(const Ipp16sc* pSrc, Ipp16sc* pDst, int numIters,
        const Ipp32sc* pTaps, int tapsLen, int tapsFactor,
        Ipp16sc* pDlyLine, int* pDlyLineIndex, int scaleFactor ) {
  return ippsFIR32sc_Direct_16sc_Sfs(pSrc,pDst,numIters,pTaps,tapsLen,tapsFactor,pDlyLine,pDlyLineIndex,scaleFactor);
}
inline IppStatus ippsFIR32s_Direct_ISfs(Ipp16s* pSrcDst, int numIters,
        const Ipp32s* pTaps, int tapsLen, int tapsFactor,
        Ipp16s* pDlyLine, int* pDlyLineIndex, int scaleFactor ) {
  return ippsFIR32s_Direct_16s_ISfs(pSrcDst,numIters,pTaps,tapsLen,tapsFactor,pDlyLine,pDlyLineIndex,scaleFactor);
}
inline IppStatus ippsFIR32sc_Direct_ISfs(Ipp16sc* pSrcDst, int numIters,
        const Ipp32sc* pTaps, int tapsLen, int tapsFactor,
        Ipp16sc* pDlyLine, int* pDlyLineIndex, int scaleFactor ) {
  return ippsFIR32sc_Direct_16sc_ISfs(pSrcDst,numIters,pTaps,tapsLen,tapsFactor,pDlyLine,pDlyLineIndex,scaleFactor);
}
inline IppStatus ippsFIRMR_Direct(const Ipp32f* pSrc, Ipp32f* pDst, int numIters,
        const Ipp32f* pTaps, int tapsLen, int upFactor,int upPhase, int downFactor, int downPhase,
        Ipp32f* pDlyLine) {
  return ippsFIRMR_Direct_32f(pSrc,pDst,numIters,pTaps,tapsLen,upFactor,upPhase,downFactor,downPhase,pDlyLine);
}
inline IppStatus ippsFIRMR_Direct(const Ipp32fc* pSrc, Ipp32fc* pDst, int numIters,
        const Ipp32fc* pTaps, int tapsLen, int upFactor,int upPhase, int downFactor, int downPhase,
        Ipp32fc* pDlyLine) {
  return ippsFIRMR_Direct_32fc(pSrc,pDst,numIters,pTaps,tapsLen,upFactor,upPhase,downFactor,downPhase,pDlyLine);
}
inline IppStatus ippsFIRMR_Direct_I(Ipp32f* pSrcDst, int numIters,
        const Ipp32f* pTaps, int tapsLen, int upFactor,int upPhase, int downFactor, int downPhase,
        Ipp32f* pDlyLine) {
  return ippsFIRMR_Direct_32f_I(pSrcDst,numIters,pTaps,tapsLen,upFactor,upPhase,downFactor,downPhase,pDlyLine);
}
inline IppStatus ippsFIRMR_Direct_I(Ipp32fc* pSrcDst, int numIters,
        const Ipp32fc* pTaps, int tapsLen, int upFactor,int upPhase, int downFactor, int downPhase,
        Ipp32fc* pDlyLine) {
  return ippsFIRMR_Direct_32fc_I(pSrcDst,numIters,pTaps,tapsLen,upFactor,upPhase,downFactor,downPhase,pDlyLine);
}
inline IppStatus ippsFIRMR32f_Direct_Sfs(const Ipp16s* pSrc, Ipp16s* pDst, int numIters,
        const Ipp32f* pTaps, int tapsLen, int upFactor,int upPhase, int downFactor, int downPhase,
        Ipp16s* pDlyLine, int scaleFactor) {
  return ippsFIRMR32f_Direct_16s_Sfs(pSrc,pDst,numIters,pTaps,tapsLen,upFactor,upPhase,downFactor,downPhase,pDlyLine,scaleFactor);
}
inline IppStatus ippsFIRMR32fc_Direct_Sfs(const Ipp16sc* pSrc, Ipp16sc* pDst, int numIters,
        const Ipp32fc* pTaps, int tapsLen, int upFactor,int upPhase, int downFactor, int downPhase,
        Ipp16sc* pDlyLine, int scaleFactor) {
  return ippsFIRMR32fc_Direct_16sc_Sfs(pSrc,pDst,numIters,pTaps,tapsLen,upFactor,upPhase,downFactor,downPhase,pDlyLine,scaleFactor);
}
inline IppStatus ippsFIRMR32f_Direct_ISfs(Ipp16s* pSrcDst, int numIters,
        const Ipp32f* pTaps, int tapsLen, int upFactor,int upPhase, int downFactor, int downPhase,
        Ipp16s* pDlyLine, int scaleFactor) {
  return ippsFIRMR32f_Direct_16s_ISfs(pSrcDst,numIters,pTaps,tapsLen,upFactor,upPhase,downFactor,downPhase,pDlyLine,scaleFactor);
}
inline IppStatus ippsFIRMR32fc_Direct_ISfs(Ipp16sc* pSrcDst, int numIters,
        const Ipp32fc* pTaps, int tapsLen, int upFactor,int upPhase, int downFactor, int downPhase,
        Ipp16sc* pDlyLine, int scaleFactor) {
  return ippsFIRMR32fc_Direct_16sc_ISfs(pSrcDst,numIters,pTaps,tapsLen,upFactor,upPhase,downFactor,downPhase,pDlyLine,scaleFactor);
}
inline IppStatus ippsFIRMR_Direct(const Ipp64f* pSrc, Ipp64f* pDst, int numIters,
        const Ipp64f* pTaps, int tapsLen, int upFactor,int upPhase, int downFactor, int downPhase,
        Ipp64f* pDlyLine) {
  return ippsFIRMR_Direct_64f(pSrc,pDst,numIters,pTaps,tapsLen,upFactor,upPhase,downFactor,downPhase,pDlyLine);
}
inline IppStatus ippsFIRMR_Direct(const Ipp64fc* pSrc, Ipp64fc* pDst, int numIters,
        const Ipp64fc* pTaps, int tapsLen, int upFactor,int upPhase, int downFactor, int downPhase,
        Ipp64fc* pDlyLine) {
  return ippsFIRMR_Direct_64fc(pSrc,pDst,numIters,pTaps,tapsLen,upFactor,upPhase,downFactor,downPhase,pDlyLine);
}
inline IppStatus ippsFIRMR_Direct_I(Ipp64f* pSrcDst, int numIters,
        const Ipp64f* pTaps, int tapsLen, int upFactor,int upPhase, int downFactor, int downPhase,
        Ipp64f* pDlyLine) {
  return ippsFIRMR_Direct_64f_I(pSrcDst,numIters,pTaps,tapsLen,upFactor,upPhase,downFactor,downPhase,pDlyLine);
}
inline IppStatus ippsFIRMR_Direct_I(Ipp64fc* pSrcDst, int numIters,
        const Ipp64fc* pTaps, int tapsLen, int upFactor,int upPhase, int downFactor, int downPhase,
        Ipp64fc* pDlyLine) {
  return ippsFIRMR_Direct_64fc_I(pSrcDst,numIters,pTaps,tapsLen,upFactor,upPhase,downFactor,downPhase,pDlyLine);
}
inline IppStatus ippsFIRMR64f_Direct(const Ipp32f* pSrc, Ipp32f* pDst, int numIters,
        const Ipp64f* pTaps, int tapsLen, int upFactor,int upPhase, int downFactor, int downPhase,
        Ipp32f* pDlyLine) {
  return ippsFIRMR64f_Direct_32f(pSrc,pDst,numIters,pTaps,tapsLen,upFactor,upPhase,downFactor,downPhase,pDlyLine);
}
inline IppStatus ippsFIRMR64fc_Direct(const Ipp32fc* pSrc, Ipp32fc* pDst, int numIters,
        const Ipp64fc* pTaps, int tapsLen, int upFactor,int upPhase, int downFactor, int downPhase,
        Ipp32fc* pDlyLine) {
  return ippsFIRMR64fc_Direct_32fc(pSrc,pDst,numIters,pTaps,tapsLen,upFactor,upPhase,downFactor,downPhase,pDlyLine);
}
inline IppStatus ippsFIRMR64f_Direct_I(Ipp32f* pSrcDst, int numIters,
        const Ipp64f* pTaps, int tapsLen, int upFactor,int upPhase, int downFactor, int downPhase,
        Ipp32f* pDlyLine) {
  return ippsFIRMR64f_Direct_32f_I(pSrcDst,numIters,pTaps,tapsLen,upFactor,upPhase,downFactor,downPhase,pDlyLine);
}
inline IppStatus ippsFIRMR64fc_Direct_I(Ipp32fc* pSrcDst, int numIters,
        const Ipp64fc* pTaps, int tapsLen, int upFactor,int upPhase, int downFactor, int downPhase,
        Ipp32fc* pDlyLine) {
  return ippsFIRMR64fc_Direct_32fc_I(pSrcDst,numIters,pTaps,tapsLen,upFactor,upPhase,downFactor,downPhase,pDlyLine);
}
inline IppStatus ippsFIRMR64f_Direct_Sfs(const Ipp32s* pSrc, Ipp32s* pDst, int numIters,
        const Ipp64f* pTaps, int tapsLen, int upFactor,int upPhase, int downFactor, int downPhase,
        Ipp32s* pDlyLine, int scaleFactor) {
  return ippsFIRMR64f_Direct_32s_Sfs(pSrc,pDst,numIters,pTaps,tapsLen,upFactor,upPhase,downFactor,downPhase,pDlyLine,scaleFactor);
}
inline IppStatus ippsFIRMR64fc_Direct_Sfs(const Ipp32sc* pSrc, Ipp32sc* pDst, int numIters,
        const Ipp64fc* pTaps, int tapsLen, int upFactor,int upPhase, int downFactor, int downPhase,
        Ipp32sc* pDlyLine, int scaleFactor) {
  return ippsFIRMR64fc_Direct_32sc_Sfs(pSrc,pDst,numIters,pTaps,tapsLen,upFactor,upPhase,downFactor,downPhase,pDlyLine,scaleFactor);
}
inline IppStatus ippsFIRMR64f_Direct_ISfs(Ipp32s* pSrcDst, int numIters,
        const Ipp64f* pTaps, int tapsLen, int upFactor,int upPhase, int downFactor, int downPhase,
        Ipp32s* pDlyLine, int scaleFactor) {
  return ippsFIRMR64f_Direct_32s_ISfs(pSrcDst,numIters,pTaps,tapsLen,upFactor,upPhase,downFactor,downPhase,pDlyLine,scaleFactor);
}
inline IppStatus ippsFIRMR64fc_Direct_ISfs(Ipp32sc* pSrcDst, int numIters,
        const Ipp64fc* pTaps, int tapsLen, int upFactor,int upPhase, int downFactor, int downPhase,
        Ipp32sc* pDlyLine, int scaleFactor) {
  return ippsFIRMR64fc_Direct_32sc_ISfs(pSrcDst,numIters,pTaps,tapsLen,upFactor,upPhase,downFactor,downPhase,pDlyLine,scaleFactor);
}
inline IppStatus ippsFIRMR64f_Direct_Sfs(const Ipp16s* pSrc, Ipp16s* pDst, int numIters,
        const Ipp64f* pTaps, int tapsLen, int upFactor,int upPhase, int downFactor, int downPhase,
        Ipp16s* pDlyLine, int scaleFactor) {
  return ippsFIRMR64f_Direct_16s_Sfs(pSrc,pDst,numIters,pTaps,tapsLen,upFactor,upPhase,downFactor,downPhase,pDlyLine,scaleFactor);
}
inline IppStatus ippsFIRMR64fc_Direct_Sfs(const Ipp16sc* pSrc, Ipp16sc* pDst, int numIters,
        const Ipp64fc* pTaps, int tapsLen, int upFactor,int upPhase, int downFactor, int downPhase,
        Ipp16sc* pDlyLine, int scaleFactor) {
  return ippsFIRMR64fc_Direct_16sc_Sfs(pSrc,pDst,numIters,pTaps,tapsLen,upFactor,upPhase,downFactor,downPhase,pDlyLine,scaleFactor);
}
inline IppStatus ippsFIRMR64f_Direct_ISfs(Ipp16s* pSrcDst, int numIters,
        const Ipp64f* pTaps, int tapsLen, int upFactor,int upPhase, int downFactor, int downPhase,
        Ipp16s* pDlyLine, int scaleFactor) {
  return ippsFIRMR64f_Direct_16s_ISfs(pSrcDst,numIters,pTaps,tapsLen,upFactor,upPhase,downFactor,downPhase,pDlyLine,scaleFactor);
}
inline IppStatus ippsFIRMR64fc_Direct_ISfs(Ipp16sc* pSrcDst, int numIters,
        const Ipp64fc* pTaps, int tapsLen, int upFactor,int upPhase, int downFactor, int downPhase,
        Ipp16sc* pDlyLine, int scaleFactor) {
  return ippsFIRMR64fc_Direct_16sc_ISfs(pSrcDst,numIters,pTaps,tapsLen,upFactor,upPhase,downFactor,downPhase,pDlyLine,scaleFactor);
}
inline IppStatus ippsFIRMR32s_Direct_Sfs(const Ipp16s* pSrc, Ipp16s* pDst, int numIters,
        const Ipp32s* pTaps, int tapsLen, int tapsFactor,
        int upFactor,int upPhase, int downFactor, int downPhase,
        Ipp16s* pDlyLine, int scaleFactor) {
  return ippsFIRMR32s_Direct_16s_Sfs(pSrc,pDst,numIters,pTaps,tapsLen,tapsFactor,upFactor,upPhase,downFactor,downPhase,pDlyLine,scaleFactor);
}
inline IppStatus ippsFIRMR32sc_Direct_Sfs(const Ipp16sc* pSrc, Ipp16sc* pDst, int numIters,
        const Ipp32sc* pTaps, int tapsLen, int tapsFactor,
        int upFactor,int upPhase, int downFactor, int downPhase,
        Ipp16sc* pDlyLine, int scaleFactor) {
  return ippsFIRMR32sc_Direct_16sc_Sfs(pSrc,pDst,numIters,pTaps,tapsLen,tapsFactor,upFactor,upPhase,downFactor,downPhase,pDlyLine,scaleFactor);
}
inline IppStatus ippsFIRMR32s_Direct_ISfs(Ipp16s* pSrcDst, int numIters,
        const Ipp32s* pTaps, int tapsLen, int tapsFactor,
        int upFactor,int upPhase, int downFactor, int downPhase,
        Ipp16s* pDlyLine, int scaleFactor) {
  return ippsFIRMR32s_Direct_16s_ISfs(pSrcDst,numIters,pTaps,tapsLen,tapsFactor,upFactor,upPhase,downFactor,downPhase,pDlyLine,scaleFactor);
}
inline IppStatus ippsFIRMR32sc_Direct_ISfs(Ipp16sc* pSrcDst, int numIters,
        const Ipp32sc* pTaps, int tapsLen, int tapsFactor,
        int upFactor,int upPhase, int downFactor, int downPhase,
        Ipp16sc* pDlyLine, int scaleFactor) {
  return ippsFIRMR32sc_Direct_16sc_ISfs(pSrcDst,numIters,pTaps,tapsLen,tapsFactor,upFactor,upPhase,downFactor,downPhase,pDlyLine,scaleFactor);
}
inline IppStatus ippsFIR_Direct_Sfs( const Ipp16s* pSrc, Ipp16s* pDst,
          int numIters, const Ipp16s* pTapsQ15, int tapsLen, Ipp16s* pDlyLine,
                                      int* pDlyLineIndex, int scaleFactor ) {
  return ippsFIR_Direct_16s_Sfs(pSrc,pDst,numIters,pTapsQ15,tapsLen,pDlyLine,pDlyLineIndex,scaleFactor);
}
inline IppStatus ippsFIR_Direct_ISfs( Ipp16s* pSrcDst, int numIters,
                       const Ipp16s* pTapsQ15, int tapsLen, Ipp16s* pDlyLine,
                                      int* pDlyLineIndex, int scaleFactor ) {
  return ippsFIR_Direct_16s_ISfs(pSrcDst,numIters,pTapsQ15,tapsLen,pDlyLine,pDlyLineIndex,scaleFactor);
}
inline IppStatus ippsFIROne_Direct_Sfs( Ipp16s src, Ipp16s* pDstVal,
                       const Ipp16s* pTapsQ15, int tapsLen, Ipp16s* pDlyLine,
                                      int* pDlyLineIndex, int scaleFactor ) {
  return ippsFIROne_Direct_16s_Sfs(src,pDstVal,pTapsQ15,tapsLen,pDlyLine,pDlyLineIndex,scaleFactor);
}
inline IppStatus ippsFIROne_Direct_ISfs( Ipp16s* pSrcDstVal,
                      const Ipp16s* pTapsQ15, int tapsLen, Ipp16s * pDlyLine,
                                      int* pDlyLineIndex, int scaleFactor ) {
  return ippsFIROne_Direct_16s_ISfs(pSrcDstVal,pTapsQ15,tapsLen,pDlyLine,pDlyLineIndex,scaleFactor);
}
inline IppStatus ippsFIRGenLowpass(Ipp64f rfreq, Ipp64f* taps, int tapsLen,
                                            IppWinType winType, IppBool doNormal) {
  return ippsFIRGenLowpass_64f(rfreq,taps,tapsLen,winType,doNormal);
}
inline IppStatus ippsFIRGenHighpass(Ipp64f rfreq, Ipp64f* taps, int tapsLen,
                                             IppWinType winType, IppBool doNormal) {
  return ippsFIRGenHighpass_64f(rfreq,taps,tapsLen,winType,doNormal);
}
inline IppStatus ippsFIRGenBandpass(Ipp64f rLowFreq, Ipp64f rHighFreq, Ipp64f* taps,
                                     int tapsLen, IppWinType winType, IppBool doNormal) {
  return ippsFIRGenBandpass_64f(rLowFreq,rHighFreq,taps,tapsLen,winType,doNormal);
}
inline IppStatus ippsFIRGenBandstop(Ipp64f rLowFreq, Ipp64f rHighFreq, Ipp64f* taps,
                                     int tapsLen, IppWinType winType, IppBool doNormal) {
  return ippsFIRGenBandstop_64f(rLowFreq,rHighFreq,taps,tapsLen,winType,doNormal);
}
inline IppStatus ippsWinBartlett_I(Ipp16s* pSrcDst, int len) {
  return ippsWinBartlett_16s_I(pSrcDst,len);
}
inline IppStatus ippsWinBartlett_I(Ipp16sc* pSrcDst, int len) {
  return ippsWinBartlett_16sc_I(pSrcDst,len);
}
inline IppStatus ippsWinBartlett_I(Ipp32f* pSrcDst, int len) {
  return ippsWinBartlett_32f_I(pSrcDst,len);
}
inline IppStatus ippsWinBartlett_I(Ipp32fc* pSrcDst, int len) {
  return ippsWinBartlett_32fc_I(pSrcDst,len);
}
inline IppStatus ippsWinBartlett(const Ipp16s* pSrc, Ipp16s* pDst, int len) {
  return ippsWinBartlett_16s(pSrc,pDst,len);
}
inline IppStatus ippsWinBartlett(const Ipp16sc* pSrc, Ipp16sc* pDst, int len) {
  return ippsWinBartlett_16sc(pSrc,pDst,len);
}
inline IppStatus ippsWinBartlett(const Ipp32f* pSrc, Ipp32f* pDst, int len) {
  return ippsWinBartlett_32f(pSrc,pDst,len);
}
inline IppStatus ippsWinBartlett(const Ipp32fc* pSrc, Ipp32fc* pDst, int len) {
  return ippsWinBartlett_32fc(pSrc,pDst,len);
}
inline IppStatus ippsWinBartlett(const Ipp64f*  pSrc, Ipp64f*  pDst, int len) {
  return ippsWinBartlett_64f(pSrc,pDst,len);
}
inline IppStatus ippsWinBartlett(const Ipp64fc* pSrc, Ipp64fc* pDst, int len) {
  return ippsWinBartlett_64fc(pSrc,pDst,len);
}
inline IppStatus ippsWinBartlett_I(Ipp64f*  pSrcDst, int len) {
  return ippsWinBartlett_64f_I(pSrcDst,len);
}
inline IppStatus ippsWinBartlett_I(Ipp64fc* pSrcDst, int len) {
  return ippsWinBartlett_64fc_I(pSrcDst,len);
}
inline IppStatus ippsWinHann_I(Ipp16s* pSrcDst, int len) {
  return ippsWinHann_16s_I(pSrcDst,len);
}
inline IppStatus ippsWinHann_I(Ipp16sc* pSrcDst, int len) {
  return ippsWinHann_16sc_I(pSrcDst,len);
}
inline IppStatus ippsWinHann_I(Ipp32f* pSrcDst, int len) {
  return ippsWinHann_32f_I(pSrcDst,len);
}
inline IppStatus ippsWinHann_I(Ipp32fc* pSrcDst, int len) {
  return ippsWinHann_32fc_I(pSrcDst,len);
}
inline IppStatus ippsWinHann(const Ipp16s* pSrc, Ipp16s* pDst, int len) {
  return ippsWinHann_16s(pSrc,pDst,len);
}
inline IppStatus ippsWinHann(const Ipp16sc* pSrc, Ipp16sc* pDst, int len) {
  return ippsWinHann_16sc(pSrc,pDst,len);
}
inline IppStatus ippsWinHann(const Ipp32f* pSrc, Ipp32f* pDst, int len) {
  return ippsWinHann_32f(pSrc,pDst,len);
}
inline IppStatus ippsWinHann(const Ipp32fc* pSrc, Ipp32fc* pDst, int len) {
  return ippsWinHann_32fc(pSrc,pDst,len);
}
inline IppStatus ippsWinHann_I(Ipp64f*  pSrcDst, int len) {
  return ippsWinHann_64f_I(pSrcDst,len);
}
inline IppStatus ippsWinHann_I(Ipp64fc* pSrcDst, int len) {
  return ippsWinHann_64fc_I(pSrcDst,len);
}
inline IppStatus ippsWinHann(const Ipp64f*  pSrc, Ipp64f*  pDst, int len) {
  return ippsWinHann_64f(pSrc,pDst,len);
}
inline IppStatus ippsWinHann(const Ipp64fc* pSrc, Ipp64fc* pDst, int len) {
  return ippsWinHann_64fc(pSrc,pDst,len);
}
inline IppStatus ippsWinHamming_I(Ipp16s* pSrcDst, int len) {
  return ippsWinHamming_16s_I(pSrcDst,len);
}
inline IppStatus ippsWinHamming_I(Ipp16sc* pSrcDst, int len) {
  return ippsWinHamming_16sc_I(pSrcDst,len);
}
inline IppStatus ippsWinHamming_I(Ipp32f* pSrcDst, int len) {
  return ippsWinHamming_32f_I(pSrcDst,len);
}
inline IppStatus ippsWinHamming_I(Ipp32fc* pSrcDst, int len) {
  return ippsWinHamming_32fc_I(pSrcDst,len);
}
inline IppStatus ippsWinHamming(const Ipp16s* pSrc, Ipp16s* pDst, int len) {
  return ippsWinHamming_16s(pSrc,pDst,len);
}
inline IppStatus ippsWinHamming(const Ipp16sc* pSrc, Ipp16sc* pDst, int len) {
  return ippsWinHamming_16sc(pSrc,pDst,len);
}
inline IppStatus ippsWinHamming(const Ipp32f* pSrc, Ipp32f* pDst, int len) {
  return ippsWinHamming_32f(pSrc,pDst,len);
}
inline IppStatus ippsWinHamming(const Ipp32fc* pSrc, Ipp32fc* pDst, int len) {
  return ippsWinHamming_32fc(pSrc,pDst,len);
}
inline IppStatus ippsWinHamming(const Ipp64f*  pSrc, Ipp64f*  pDst, int len) {
  return ippsWinHamming_64f(pSrc,pDst,len);
}
inline IppStatus ippsWinHamming(const Ipp64fc* pSrc, Ipp64fc* pDst, int len) {
  return ippsWinHamming_64fc(pSrc,pDst,len);
}
inline IppStatus ippsWinHamming_I(Ipp64f*  pSrcDst, int len) {
  return ippsWinHamming_64f_I(pSrcDst,len);
}
inline IppStatus ippsWinHamming_I(Ipp64fc* pSrcDst, int len) {
  return ippsWinHamming_64fc_I(pSrcDst,len);
}
inline IppStatus ippsWinBlackmanQ15_ISfs(Ipp16s* pSrcDst, int len,
                                             int alphaQ15, int scaleFactor) {
  return ippsWinBlackmanQ15_16s_ISfs(pSrcDst,len,alphaQ15,scaleFactor);
}
inline IppStatus ippsWinBlackmanQ15_I(Ipp16s* pSrcDst, int len, int alphaQ15) {
  return ippsWinBlackmanQ15_16s_I(pSrcDst,len,alphaQ15);
}
inline IppStatus ippsWinBlackmanQ15_I(Ipp16sc* pSrcDst, int len, int alphaQ15) {
  return ippsWinBlackmanQ15_16sc_I(pSrcDst,len,alphaQ15);
}
inline IppStatus ippsWinBlackman_I(Ipp16s* pSrcDst, int len, float alpha) {
  return ippsWinBlackman_16s_I(pSrcDst,len,alpha);
}
inline IppStatus ippsWinBlackman_I(Ipp16sc* pSrcDst, int len, float alpha) {
  return ippsWinBlackman_16sc_I(pSrcDst,len,alpha);
}
inline IppStatus ippsWinBlackman_I(Ipp32f* pSrcDst, int len, float alpha) {
  return ippsWinBlackman_32f_I(pSrcDst,len,alpha);
}
inline IppStatus ippsWinBlackman_I(Ipp32fc* pSrcDst, int len, float alpha) {
  return ippsWinBlackman_32fc_I(pSrcDst,len,alpha);
}
inline IppStatus ippsWinBlackmanQ15(const Ipp16s* pSrc, Ipp16s* pDst, int len, int alphaQ15) {
  return ippsWinBlackmanQ15_16s(pSrc,pDst,len,alphaQ15);
}
inline IppStatus ippsWinBlackmanQ15(const Ipp16sc* pSrc, Ipp16sc* pDst, int len, int alphaQ15) {
  return ippsWinBlackmanQ15_16sc(pSrc,pDst,len,alphaQ15);
}
inline IppStatus ippsWinBlackman(const Ipp16s* pSrc, Ipp16s* pDst, int len, float alpha) {
  return ippsWinBlackman_16s(pSrc,pDst,len,alpha);
}
inline IppStatus ippsWinBlackman(const Ipp16sc* pSrc, Ipp16sc* pDst, int len, float alpha) {
  return ippsWinBlackman_16sc(pSrc,pDst,len,alpha);
}
inline IppStatus ippsWinBlackman(const Ipp32f* pSrc, Ipp32f* pDst, int len, float alpha) {
  return ippsWinBlackman_32f(pSrc,pDst,len,alpha);
}
inline IppStatus ippsWinBlackman(const Ipp32fc* pSrc, Ipp32fc* pDst, int len, float alpha) {
  return ippsWinBlackman_32fc(pSrc,pDst,len,alpha);
}
inline IppStatus ippsWinBlackmanStd_I(Ipp16s* pSrcDst, int len) {
  return ippsWinBlackmanStd_16s_I(pSrcDst,len);
}
inline IppStatus ippsWinBlackmanStd_I(Ipp16sc* pSrcDst, int len) {
  return ippsWinBlackmanStd_16sc_I(pSrcDst,len);
}
inline IppStatus ippsWinBlackmanStd_I(Ipp32f* pSrcDst, int len) {
  return ippsWinBlackmanStd_32f_I(pSrcDst,len);
}
inline IppStatus ippsWinBlackmanStd_I(Ipp32fc* pSrcDst, int len) {
  return ippsWinBlackmanStd_32fc_I(pSrcDst,len);
}
inline IppStatus ippsWinBlackmanOpt_I(Ipp16s* pSrcDst, int len) {
  return ippsWinBlackmanOpt_16s_I(pSrcDst,len);
}
inline IppStatus ippsWinBlackmanOpt_I(Ipp16sc* pSrcDst, int len) {
  return ippsWinBlackmanOpt_16sc_I(pSrcDst,len);
}
inline IppStatus ippsWinBlackmanOpt_I(Ipp32f* pSrcDst, int len) {
  return ippsWinBlackmanOpt_32f_I(pSrcDst,len);
}
inline IppStatus ippsWinBlackmanOpt_I(Ipp32fc* pSrcDst, int len) {
  return ippsWinBlackmanOpt_32fc_I(pSrcDst,len);
}
inline IppStatus ippsWinBlackmanStd(const Ipp16s* pSrc, Ipp16s* pDst, int len) {
  return ippsWinBlackmanStd_16s(pSrc,pDst,len);
}
inline IppStatus ippsWinBlackmanStd(const Ipp16sc* pSrc, Ipp16sc* pDst, int len) {
  return ippsWinBlackmanStd_16sc(pSrc,pDst,len);
}
inline IppStatus ippsWinBlackmanStd(const Ipp32f* pSrc, Ipp32f* pDst, int len) {
  return ippsWinBlackmanStd_32f(pSrc,pDst,len);
}
inline IppStatus ippsWinBlackmanStd(const Ipp32fc* pSrc, Ipp32fc* pDst, int len) {
  return ippsWinBlackmanStd_32fc(pSrc,pDst,len);
}
inline IppStatus ippsWinBlackmanOpt(const Ipp16s* pSrc, Ipp16s* pDst, int len) {
  return ippsWinBlackmanOpt_16s(pSrc,pDst,len);
}
inline IppStatus ippsWinBlackmanOpt(const Ipp16sc* pSrc, Ipp16sc* pDst, int len) {
  return ippsWinBlackmanOpt_16sc(pSrc,pDst,len);
}
inline IppStatus ippsWinBlackmanOpt(const Ipp32f* pSrc, Ipp32f* pDst, int len) {
  return ippsWinBlackmanOpt_32f(pSrc,pDst,len);
}
inline IppStatus ippsWinBlackmanOpt(const Ipp32fc* pSrc, Ipp32fc* pDst, int len) {
  return ippsWinBlackmanOpt_32fc(pSrc,pDst,len);
}
inline IppStatus ippsWinBlackman_I(Ipp64f*  pSrcDst, int len, double alpha) {
  return ippsWinBlackman_64f_I(pSrcDst,len,alpha);
}
inline IppStatus ippsWinBlackman_I(Ipp64fc* pSrcDst, int len, double alpha) {
  return ippsWinBlackman_64fc_I(pSrcDst,len,alpha);
}
inline IppStatus ippsWinBlackman(const Ipp64f*  pSrc, Ipp64f*  pDst, int len, double alpha) {
  return ippsWinBlackman_64f(pSrc,pDst,len,alpha);
}
inline IppStatus ippsWinBlackman(const Ipp64fc* pSrc, Ipp64fc* pDst, int len, double alpha) {
  return ippsWinBlackman_64fc(pSrc,pDst,len,alpha);
}
inline IppStatus ippsWinBlackmanStd_I(Ipp64f*  pSrcDst, int len) {
  return ippsWinBlackmanStd_64f_I(pSrcDst,len);
}
inline IppStatus ippsWinBlackmanStd_I(Ipp64fc* pSrcDst, int len) {
  return ippsWinBlackmanStd_64fc_I(pSrcDst,len);
}
inline IppStatus ippsWinBlackmanStd(const Ipp64f*  pSrc, Ipp64f*  pDst, int len) {
  return ippsWinBlackmanStd_64f(pSrc,pDst,len);
}
inline IppStatus ippsWinBlackmanStd(const Ipp64fc* pSrc, Ipp64fc* pDst, int len) {
  return ippsWinBlackmanStd_64fc(pSrc,pDst,len);
}
inline IppStatus ippsWinBlackmanOpt_I(Ipp64f*  pSrcDst, int len) {
  return ippsWinBlackmanOpt_64f_I(pSrcDst,len);
}
inline IppStatus ippsWinBlackmanOpt_I(Ipp64fc* pSrcDst, int len) {
  return ippsWinBlackmanOpt_64fc_I(pSrcDst,len);
}
inline IppStatus ippsWinBlackmanOpt(const Ipp64f*  pSrc, Ipp64f*  pDst, int len) {
  return ippsWinBlackmanOpt_64f(pSrc,pDst,len);
}
inline IppStatus ippsWinBlackmanOpt(const Ipp64fc* pSrc, Ipp64fc* pDst, int len) {
  return ippsWinBlackmanOpt_64fc(pSrc,pDst,len);
}
inline IppStatus ippsWinKaiser(const Ipp16s* pSrc, Ipp16s* pDst, int len, float alpha) {
  return ippsWinKaiser_16s(pSrc,pDst,len,alpha);
}
inline IppStatus ippsWinKaiser_I(Ipp16s* pSrcDst, int len, float alpha) {
  return ippsWinKaiser_16s_I(pSrcDst,len,alpha);
}
inline IppStatus ippsWinKaiserQ15(const Ipp16s* pSrc, Ipp16s* pDst, int len, int alphaQ15) {
  return ippsWinKaiserQ15_16s(pSrc,pDst,len,alphaQ15);
}
inline IppStatus ippsWinKaiserQ15_I(Ipp16s* pSrcDst, int len, int alphaQ15) {
  return ippsWinKaiserQ15_16s_I(pSrcDst,len,alphaQ15);
}
inline IppStatus ippsWinKaiser(const Ipp16sc* pSrc, Ipp16sc* pDst, int len, float alpha) {
  return ippsWinKaiser_16sc(pSrc,pDst,len,alpha);
}
inline IppStatus ippsWinKaiser_I(Ipp16sc* pSrcDst, int len, float alpha) {
  return ippsWinKaiser_16sc_I(pSrcDst,len,alpha);
}
inline IppStatus ippsWinKaiserQ15(const Ipp16sc* pSrc, Ipp16sc* pDst, int len, int alphaQ15) {
  return ippsWinKaiserQ15_16sc(pSrc,pDst,len,alphaQ15);
}
inline IppStatus ippsWinKaiserQ15_I(Ipp16sc* pSrcDst, int len, int alphaQ15) {
  return ippsWinKaiserQ15_16sc_I(pSrcDst,len,alphaQ15);
}
inline IppStatus ippsWinKaiser(const Ipp32f* pSrc, Ipp32f* pDst, int len, float alpha) {
  return ippsWinKaiser_32f(pSrc,pDst,len,alpha);
}
inline IppStatus ippsWinKaiser_I(Ipp32f* pSrcDst, int len, float alpha) {
  return ippsWinKaiser_32f_I(pSrcDst,len,alpha);
}
inline IppStatus ippsWinKaiser(const Ipp32fc* pSrc, Ipp32fc* pDst, int len, float alpha) {
  return ippsWinKaiser_32fc(pSrc,pDst,len,alpha);
}
inline IppStatus ippsWinKaiser_I(Ipp32fc* pSrcDst, int len, float alpha) {
  return ippsWinKaiser_32fc_I(pSrcDst,len,alpha);
}
inline IppStatus ippsWinKaiser(const Ipp64f* pSrc, Ipp64f* pDst, int len, float alpha) {
  return ippsWinKaiser_64f(pSrc,pDst,len,alpha);
}
inline IppStatus ippsWinKaiser_I(Ipp64f* pSrcDst, int len, float alpha) {
  return ippsWinKaiser_64f_I(pSrcDst,len,alpha);
}
inline IppStatus ippsWinKaiser_I(Ipp64fc* pSrcDst, int len, float alpha) {
  return ippsWinKaiser_64fc_I(pSrcDst,len,alpha);
}
inline IppStatus ippsWinKaiser(const Ipp64fc* pSrc, Ipp64fc* pDst, int len, float alpha) {
  return ippsWinKaiser_64fc(pSrc,pDst,len,alpha);
}
inline IppStatus ippsFilterMedian_I(Ipp32f* pSrcDst,int len,int maskSize) {
  return ippsFilterMedian_32f_I(pSrcDst,len,maskSize);
}
inline IppStatus ippsFilterMedian_I(Ipp64f* pSrcDst,int len,int maskSize) {
  return ippsFilterMedian_64f_I(pSrcDst,len,maskSize);
}
inline IppStatus ippsFilterMedian_I(Ipp16s* pSrcDst,int len,int maskSize) {
  return ippsFilterMedian_16s_I(pSrcDst,len,maskSize);
}
inline IppStatus ippsFilterMedian_I(Ipp8u* pSrcDst,int len,int maskSize) {
  return ippsFilterMedian_8u_I(pSrcDst,len,maskSize);
}
inline IppStatus ippsFilterMedian(const Ipp32f* pSrc, Ipp32f *pDst,
                                       int len, int maskSize ) {
  return ippsFilterMedian_32f(pSrc,pDst,len,maskSize);
}
inline IppStatus ippsFilterMedian(const Ipp64f* pSrc, Ipp64f *pDst,
                                       int len, int maskSize ) {
  return ippsFilterMedian_64f(pSrc,pDst,len,maskSize);
}
inline IppStatus ippsFilterMedian(const Ipp16s* pSrc, Ipp16s *pDst,
                                       int len, int maskSize ) {
  return ippsFilterMedian_16s(pSrc,pDst,len,maskSize);
}
inline IppStatus ippsFilterMedian(const Ipp8u* pSrc, Ipp8u *pDst,
                                      int len, int maskSize ) {
  return ippsFilterMedian_8u(pSrc,pDst,len,maskSize);
}
inline IppStatus ippsFilterMedian_I(Ipp32s* pSrcDst,int len,int maskSize) {
  return ippsFilterMedian_32s_I(pSrcDst,len,maskSize);
}
inline IppStatus ippsFilterMedian(const Ipp32s* pSrc, Ipp32s *pDst,
                                       int len, int maskSize ) {
  return ippsFilterMedian_32s(pSrc,pDst,len,maskSize);
}
inline IppStatus ippsNorm_Inf(const Ipp16s* pSrc, int len, Ipp32f* pNorm) {
  return ippsNorm_Inf_16s32f(pSrc,len,pNorm);
}
inline IppStatus ippsNorm_Inf_Sfs(const Ipp16s* pSrc, int len, Ipp32s* pNorm, int scaleFactor) {
  return ippsNorm_Inf_16s32s_Sfs(pSrc,len,pNorm,scaleFactor);
}
inline IppStatus ippsNorm_Inf(const Ipp32f* pSrc, int len, Ipp32f* pNorm) {
  return ippsNorm_Inf_32f(pSrc,len,pNorm);
}
inline IppStatus ippsNorm_Inf(const Ipp64f* pSrc, int len, Ipp64f* pNorm) {
  return ippsNorm_Inf_64f(pSrc,len,pNorm);
}
inline IppStatus ippsNorm_L1(const Ipp16s* pSrc, int len, Ipp32f* pNorm) {
  return ippsNorm_L1_16s32f(pSrc,len,pNorm);
}
inline IppStatus ippsNorm_L1_Sfs(const Ipp16s* pSrc, int len, Ipp32s* pNorm, int scaleFactor) {
  return ippsNorm_L1_16s32s_Sfs(pSrc,len,pNorm,scaleFactor);
}
inline IppStatus ippsNorm_L1(const Ipp32f* pSrc, int len, Ipp32f* pNorm) {
  return ippsNorm_L1_32f(pSrc,len,pNorm);
}
inline IppStatus ippsNorm_L1(const Ipp64f* pSrc, int len, Ipp64f* pNorm) {
  return ippsNorm_L1_64f(pSrc,len,pNorm);
}
inline IppStatus ippsNorm_L2(const Ipp16s* pSrc, int len, Ipp32f* pNorm) {
  return ippsNorm_L2_16s32f(pSrc,len,pNorm);
}
inline IppStatus ippsNorm_L2_Sfs(const Ipp16s* pSrc, int len, Ipp32s* pNorm, int scaleFactor) {
  return ippsNorm_L2_16s32s_Sfs(pSrc,len,pNorm,scaleFactor);
}
inline IppStatus ippsNorm_L2(const Ipp32f* pSrc, int len, Ipp32f* pNorm) {
  return ippsNorm_L2_32f(pSrc,len,pNorm);
}
inline IppStatus ippsNorm_L2(const Ipp64f* pSrc, int len, Ipp64f* pNorm) {
  return ippsNorm_L2_64f(pSrc,len,pNorm);
}
inline IppStatus ippsNorm_Inf(const Ipp32fc* pSrc, int len, Ipp32f* pNorm) {
  return ippsNorm_Inf_32fc32f(pSrc,len,pNorm);
}
inline IppStatus ippsNorm_Inf(const Ipp64fc* pSrc, int len, Ipp64f* pNorm) {
  return ippsNorm_Inf_64fc64f(pSrc,len,pNorm);
}
inline IppStatus ippsNorm_L1(const Ipp32fc* pSrc, int len, Ipp64f* pNorm) {
  return ippsNorm_L1_32fc64f(pSrc,len,pNorm);
}
inline IppStatus ippsNorm_L1(const Ipp64fc* pSrc, int len, Ipp64f* pNorm) {
  return ippsNorm_L1_64fc64f(pSrc,len,pNorm);
}
inline IppStatus ippsNorm_L2(const Ipp32fc* pSrc, int len, Ipp64f* pNorm) {
  return ippsNorm_L2_32fc64f(pSrc,len,pNorm);
}
inline IppStatus ippsNorm_L2(const Ipp64fc* pSrc, int len, Ipp64f* pNorm) {
  return ippsNorm_L2_64fc64f(pSrc,len,pNorm);
}
inline IppStatus ippsNorm_L1_Sfs(const Ipp16s* pSrc, int len, Ipp64s* pNorm, int scaleFactor) {
  return ippsNorm_L1_16s64s_Sfs(pSrc,len,pNorm,scaleFactor);
}
inline IppStatus ippsNorm_L2Sqr_Sfs(const Ipp16s* pSrc, int len, Ipp64s* pNorm, int scaleFactor) {
  return ippsNorm_L2Sqr_16s64s_Sfs(pSrc,len,pNorm,scaleFactor);
}
inline IppStatus ippsNormDiff_Inf(const Ipp16s* pSrc1, const Ipp16s* pSrc2, int len, Ipp32f* pNorm) {
  return ippsNormDiff_Inf_16s32f(pSrc1,pSrc2,len,pNorm);
}
inline IppStatus ippsNormDiff_Inf_Sfs(const Ipp16s* pSrc1, const Ipp16s* pSrc2, int len, Ipp32s* pNorm, int scaleFactor) {
  return ippsNormDiff_Inf_16s32s_Sfs(pSrc1,pSrc2,len,pNorm,scaleFactor);
}
inline IppStatus ippsNormDiff_Inf(const Ipp32f* pSrc1, const Ipp32f* pSrc2, int len, Ipp32f* pNorm) {
  return ippsNormDiff_Inf_32f(pSrc1,pSrc2,len,pNorm);
}
inline IppStatus ippsNormDiff_Inf(const Ipp64f* pSrc1, const Ipp64f* pSrc2, int len, Ipp64f* pNorm) {
  return ippsNormDiff_Inf_64f(pSrc1,pSrc2,len,pNorm);
}
inline IppStatus ippsNormDiff_L1(const Ipp16s* pSrc1, const Ipp16s* pSrc2, int len, Ipp32f* pNorm) {
  return ippsNormDiff_L1_16s32f(pSrc1,pSrc2,len,pNorm);
}
inline IppStatus ippsNormDiff_L1_Sfs(const Ipp16s* pSrc1, const Ipp16s* pSrc2, int len, Ipp32s* pNorm, int scaleFactor) {
  return ippsNormDiff_L1_16s32s_Sfs(pSrc1,pSrc2,len,pNorm,scaleFactor);
}
inline IppStatus ippsNormDiff_L1(const Ipp32f* pSrc1, const Ipp32f* pSrc2, int len, Ipp32f* pNorm) {
  return ippsNormDiff_L1_32f(pSrc1,pSrc2,len,pNorm);
}
inline IppStatus ippsNormDiff_L1(const Ipp64f* pSrc1, const Ipp64f* pSrc2, int len, Ipp64f* pNorm) {
  return ippsNormDiff_L1_64f(pSrc1,pSrc2,len,pNorm);
}
inline IppStatus ippsNormDiff_L2(const Ipp16s* pSrc1, const Ipp16s* pSrc2, int len, Ipp32f* pNorm) {
  return ippsNormDiff_L2_16s32f(pSrc1,pSrc2,len,pNorm);
}
inline IppStatus ippsNormDiff_L2_Sfs(const Ipp16s* pSrc1, const Ipp16s* pSrc2, int len, Ipp32s* pNorm, int scaleFactor) {
  return ippsNormDiff_L2_16s32s_Sfs(pSrc1,pSrc2,len,pNorm,scaleFactor);
}
inline IppStatus ippsNormDiff_L2(const Ipp32f* pSrc1, const Ipp32f* pSrc2, int len, Ipp32f* pNorm) {
  return ippsNormDiff_L2_32f(pSrc1,pSrc2,len,pNorm);
}
inline IppStatus ippsNormDiff_L2(const Ipp64f* pSrc1, const Ipp64f* pSrc2, int len, Ipp64f* pNorm) {
  return ippsNormDiff_L2_64f(pSrc1,pSrc2,len,pNorm);
}
inline IppStatus ippsNormDiff_Inf(const Ipp32fc* pSrc1, const Ipp32fc* pSrc2, int len, Ipp32f* pNorm) {
  return ippsNormDiff_Inf_32fc32f(pSrc1,pSrc2,len,pNorm);
}
inline IppStatus ippsNormDiff_Inf(const Ipp64fc* pSrc1, const Ipp64fc* pSrc2, int len, Ipp64f* pNorm) {
  return ippsNormDiff_Inf_64fc64f(pSrc1,pSrc2,len,pNorm);
}
inline IppStatus ippsNormDiff_L1(const Ipp32fc* pSrc1, const Ipp32fc* pSrc2, int len, Ipp64f* pNorm) {
  return ippsNormDiff_L1_32fc64f(pSrc1,pSrc2,len,pNorm);
}
inline IppStatus ippsNormDiff_L1(const Ipp64fc* pSrc1, const Ipp64fc* pSrc2, int len, Ipp64f* pNorm) {
  return ippsNormDiff_L1_64fc64f(pSrc1,pSrc2,len,pNorm);
}
inline IppStatus ippsNormDiff_L2(const Ipp32fc* pSrc1, const Ipp32fc* pSrc2, int len, Ipp64f* pNorm) {
  return ippsNormDiff_L2_32fc64f(pSrc1,pSrc2,len,pNorm);
}
inline IppStatus ippsNormDiff_L2(const Ipp64fc* pSrc1, const Ipp64fc* pSrc2, int len, Ipp64f* pNorm) {
  return ippsNormDiff_L2_64fc64f(pSrc1,pSrc2,len,pNorm);
}
inline IppStatus ippsNormDiff_L1_Sfs(const Ipp16s* pSrc1, const Ipp16s* pSrc2, int len, Ipp64s* pNorm, int scaleFactor) {
  return ippsNormDiff_L1_16s64s_Sfs(pSrc1,pSrc2,len,pNorm,scaleFactor);
}
inline IppStatus ippsNormDiff_L2Sqr_Sfs(const Ipp16s* pSrc1, const Ipp16s* pSrc2, int len, Ipp64s* pNorm, int scaleFactor) {
  return ippsNormDiff_L2Sqr_16s64s_Sfs(pSrc1,pSrc2,len,pNorm,scaleFactor);
}
inline IppStatus ippsCrossCorr(const Ipp32f* pSrc1, int len1, const Ipp32f* pSrc2, int len2, Ipp32f* pDst,  int dstLen, int lowLag) {
  return ippsCrossCorr_32f(pSrc1,len1,pSrc2,len2,pDst,dstLen,lowLag);
}
inline IppStatus ippsCrossCorr(const Ipp64f* pSrc1, int len1, const Ipp64f* pSrc2, int len2, Ipp64f* pDst,  int dstLen, int lowLag) {
  return ippsCrossCorr_64f(pSrc1,len1,pSrc2,len2,pDst,dstLen,lowLag);
}
inline IppStatus ippsCrossCorr(const Ipp32fc* pSrc1, int len1, const Ipp32fc* pSrc2, int len2, Ipp32fc* pDst,  int dstLen, int lowLag) {
  return ippsCrossCorr_32fc(pSrc1,len1,pSrc2,len2,pDst,dstLen,lowLag);
}
inline IppStatus ippsCrossCorr(const Ipp64fc* pSrc1, int len1, const Ipp64fc* pSrc2, int len2, Ipp64fc* pDst,  int dstLen, int lowLag) {
  return ippsCrossCorr_64fc(pSrc1,len1,pSrc2,len2,pDst,dstLen,lowLag);
}
inline IppStatus ippsCrossCorr_Sfs(const Ipp16s* pSrc1, int len1, const Ipp16s* pSrc2, int len2, Ipp16s* pDst, int dstLen, int lowLag, int scaleFactor) {
  return ippsCrossCorr_16s_Sfs(pSrc1,len1,pSrc2,len2,pDst,dstLen,lowLag,scaleFactor);
}
inline IppStatus ippsAutoCorr( const Ipp32f* pSrc, int srcLen, Ipp32f* pDst, int dstLen ) {
  return ippsAutoCorr_32f(pSrc,srcLen,pDst,dstLen);
}
inline IppStatus ippsAutoCorr_NormA( const Ipp32f* pSrc, int srcLen, Ipp32f* pDst, int dstLen ) {
  return ippsAutoCorr_NormA_32f(pSrc,srcLen,pDst,dstLen);
}
inline IppStatus ippsAutoCorr_NormB( const Ipp32f* pSrc, int srcLen, Ipp32f* pDst, int dstLen ) {
  return ippsAutoCorr_NormB_32f(pSrc,srcLen,pDst,dstLen);
}
inline IppStatus ippsAutoCorr( const Ipp64f* pSrc, int srcLen, Ipp64f* pDst, int dstLen ) {
  return ippsAutoCorr_64f(pSrc,srcLen,pDst,dstLen);
}
inline IppStatus ippsAutoCorr_NormA( const Ipp64f* pSrc, int srcLen, Ipp64f* pDst, int dstLen ) {
  return ippsAutoCorr_NormA_64f(pSrc,srcLen,pDst,dstLen);
}
inline IppStatus ippsAutoCorr_NormB( const Ipp64f* pSrc, int srcLen, Ipp64f* pDst, int dstLen ) {
  return ippsAutoCorr_NormB_64f(pSrc,srcLen,pDst,dstLen);
}
inline IppStatus ippsAutoCorr( const Ipp32fc* pSrc, int srcLen, Ipp32fc* pDst, int dstLen ) {
  return ippsAutoCorr_32fc(pSrc,srcLen,pDst,dstLen);
}
inline IppStatus ippsAutoCorr_NormA( const Ipp32fc* pSrc, int srcLen, Ipp32fc* pDst, int dstLen ) {
  return ippsAutoCorr_NormA_32fc(pSrc,srcLen,pDst,dstLen);
}
inline IppStatus ippsAutoCorr_NormB( const Ipp32fc* pSrc, int srcLen, Ipp32fc* pDst, int dstLen ) {
  return ippsAutoCorr_NormB_32fc(pSrc,srcLen,pDst,dstLen);
}
inline IppStatus ippsAutoCorr( const Ipp64fc* pSrc, int srcLen, Ipp64fc* pDst, int dstLen ) {
  return ippsAutoCorr_64fc(pSrc,srcLen,pDst,dstLen);
}
inline IppStatus ippsAutoCorr_NormA( const Ipp64fc* pSrc, int srcLen, Ipp64fc* pDst, int dstLen ) {
  return ippsAutoCorr_NormA_64fc(pSrc,srcLen,pDst,dstLen);
}
inline IppStatus ippsAutoCorr_NormB( const Ipp64fc* pSrc, int srcLen, Ipp64fc* pDst, int dstLen ) {
  return ippsAutoCorr_NormB_64fc(pSrc,srcLen,pDst,dstLen);
}
inline IppStatus ippsAutoCorr_Sfs( const Ipp16s* pSrc, int srcLen, Ipp16s* pDst,
                                                        int dstLen, int scaleFactor ) {
  return ippsAutoCorr_16s_Sfs(pSrc,srcLen,pDst,dstLen,scaleFactor);
}
inline IppStatus ippsAutoCorr_NormA_Sfs( const Ipp16s* pSrc, int srcLen, Ipp16s* pDst,
                                                        int dstLen, int scaleFactor ) {
  return ippsAutoCorr_NormA_16s_Sfs(pSrc,srcLen,pDst,dstLen,scaleFactor);
}
inline IppStatus ippsAutoCorr_NormB_Sfs( const Ipp16s* pSrc, int srcLen, Ipp16s* pDst,
                                                        int dstLen, int scaleFactor ) {
  return ippsAutoCorr_NormB_16s_Sfs(pSrc,srcLen,pDst,dstLen,scaleFactor);
}
inline IppStatus ippsSampleUp(const Ipp32f* pSrc, int  srcLen,
                                             Ipp32f* pDst, int* dstLen,
                                             int factor,   int* phase) {
  return ippsSampleUp_32f(pSrc,srcLen,pDst,dstLen,factor,phase);
}
inline IppStatus ippsSampleUp(const Ipp32fc* pSrc, int  srcLen,
                                              Ipp32fc* pDst, int* dstLen,
                                              int factor,   int* phase) {
  return ippsSampleUp_32fc(pSrc,srcLen,pDst,dstLen,factor,phase);
}
inline IppStatus ippsSampleUp(const Ipp64f* pSrc, int  srcLen,
                                             Ipp64f* pDst, int* dstLen,
                                             int factor,   int* phase) {
  return ippsSampleUp_64f(pSrc,srcLen,pDst,dstLen,factor,phase);
}
inline IppStatus ippsSampleUp(const Ipp64fc* pSrc, int  srcLen,
                                              Ipp64fc* pDst, int* dstLen,
                                              int factor,   int* phase) {
  return ippsSampleUp_64fc(pSrc,srcLen,pDst,dstLen,factor,phase);
}
inline IppStatus ippsSampleUp(const Ipp16s* pSrc, int  srcLen,
                                             Ipp16s* pDst, int* dstLen,
                                             int factor,   int* phase) {
  return ippsSampleUp_16s(pSrc,srcLen,pDst,dstLen,factor,phase);
}
inline IppStatus ippsSampleUp(const Ipp16sc* pSrc, int  srcLen,
                                              Ipp16sc* pDst, int* dstLen,
                                              int factor,   int* phase) {
  return ippsSampleUp_16sc(pSrc,srcLen,pDst,dstLen,factor,phase);
}
inline IppStatus ippsSampleDown(const Ipp32f* pSrc, int  srcLen,
                                               Ipp32f* pDst, int* dstLen,
                                               int factor,   int* phase) {
  return ippsSampleDown_32f(pSrc,srcLen,pDst,dstLen,factor,phase);
}
inline IppStatus ippsSampleDown(const Ipp32fc* pSrc, int  srcLen,
                                                Ipp32fc* pDst, int* dstLen,
                                                int factor,   int* phase) {
  return ippsSampleDown_32fc(pSrc,srcLen,pDst,dstLen,factor,phase);
}
inline IppStatus ippsSampleDown(const Ipp64f* pSrc, int  srcLen,
                                               Ipp64f* pDst, int* dstLen,
                                               int factor,   int* phase) {
  return ippsSampleDown_64f(pSrc,srcLen,pDst,dstLen,factor,phase);
}
inline IppStatus ippsSampleDown(const Ipp64fc* pSrc, int  srcLen,
                                                Ipp64fc* pDst, int* dstLen,
                                                int factor,   int* phase) {
  return ippsSampleDown_64fc(pSrc,srcLen,pDst,dstLen,factor,phase);
}
inline IppStatus ippsSampleDown(const Ipp16s* pSrc, int  srcLen,
                                               Ipp16s* pDst, int* dstLen,
                                               int factor,   int* phase) {
  return ippsSampleDown_16s(pSrc,srcLen,pDst,dstLen,factor,phase);
}
inline IppStatus ippsSampleDown(const Ipp16sc* pSrc, int  srcLen,
                                                Ipp16sc* pDst, int* dstLen,
                                                int factor,   int* phase) {
  return ippsSampleDown_16sc(pSrc,srcLen,pDst,dstLen,factor,phase);
}
inline IppStatus ippsGetVarPointDV(const Ipp16sc *pSrc,Ipp16sc *pDst,
       Ipp16sc *pVariantPoint,const Ipp8u *pLabel,int state) {
  return ippsGetVarPointDV_16sc(pSrc,pDst,pVariantPoint,pLabel,state);
}
inline IppStatus ippsBuildSymblTableDV4D(const Ipp16sc *pVariantPoint,
       Ipp16sc *pCurrentSubsetPoint,int state,int bitInversion ) {
  return ippsBuildSymblTableDV4D_16sc(pVariantPoint,pCurrentSubsetPoint,state,bitInversion);
}
inline IppStatus ippsUpdatePathMetricsDV(Ipp16u *pBranchError,
       Ipp16u *pMinPathError,Ipp8u *pMinSost,Ipp16u *pPathError,int state) {
  return ippsUpdatePathMetricsDV_16u(pBranchError,pMinPathError,pMinSost,pPathError,state);
}
inline IppStatus ippsHilbert(const Ipp32f *pSrc, Ipp32fc *pDst,
                                        IppsHilbertSpec_32f32fc *pSpec) {
  return ippsHilbert_32f32fc(pSrc,pDst,pSpec);
}
inline IppStatus ippsHilbert(const Ipp16s *pSrc, Ipp32fc *pDst,
                                        IppsHilbertSpec_16s32fc *pSpec) {
  return ippsHilbert_16s32fc(pSrc,pDst,pSpec);
}
inline IppStatus ippsHilbert_Sfs(const Ipp16s *pSrc, Ipp16sc *pDst,
                                        IppsHilbertSpec_16s16sc *pSpec, int scaleFactor) {
  return ippsHilbert_16s16sc_Sfs(pSrc,pDst,pSpec,scaleFactor);
}
inline IppStatus ippsFIRSparseInit( IppsFIRSparseState_32f** pState,
    const Ipp32f *pNZTaps, const Ipp32s* pNZTapPos, int nzTapsLen,
    const Ipp32f *pDlyLine, Ipp8u *pBuffer ) {
  return ippsFIRSparseInit_32f(pState,pNZTaps,pNZTapPos,nzTapsLen,pDlyLine,pBuffer);
}
inline IppStatus ippsIIRSparseInit( IppsIIRSparseState_32f** pState,
        const Ipp32f* pNZTaps, const Ipp32s* pNZTapPos, int nzTapsLen1,
        int nzTapsLen2, const Ipp32f* pDlyLine, Ipp8u* pBuf ) {
  return ippsIIRSparseInit_32f(pState,pNZTaps,pNZTapPos,nzTapsLen1,nzTapsLen2,pDlyLine,pBuf);
}
inline IppStatus ippsFIRSparse(const Ipp32f* pSrc, Ipp32f* pDst, int len,
        IppsFIRSparseState_32f* pState) {
  return ippsFIRSparse_32f(pSrc,pDst,len,pState);
}
inline IppStatus ippsIIRSparse(const Ipp32f* pSrc, Ipp32f* pDst, int len,
       IppsIIRSparseState_32f* pState) {
  return ippsIIRSparse_32f(pSrc,pDst,len,pState);
}
inline IppStatus ippsAddProductC( const Ipp32f* pSrc, const Ipp32f val,
                                               Ipp32f* pSrcDst, int len ) {
  return ippsAddProductC_32f(pSrc,val,pSrcDst,len);
}
inline IppStatus ippsSumWindow(const Ipp8u*  pSrc,Ipp32f* pDst,int len, int maskSize ) {
  return ippsSumWindow_8u32f(pSrc,pDst,len,maskSize);
}
inline IppStatus ippsSumWindow(const Ipp16s* pSrc,Ipp32f* pDst,int len, int maskSize ) {
  return ippsSumWindow_16s32f(pSrc,pDst,len,maskSize);
}
inline IppStatus ippmExtract_v(const Ipp32f*  pSrc,  int srcStride2,
                                              Ipp32f*  pDst,  int len) {
  return ippmExtract_v_32f(pSrc,srcStride2,pDst,len);
}
inline IppStatus ippmExtract_v(const Ipp64f*  pSrc,  int srcStride2,
                                              Ipp64f*  pDst,  int len) {
  return ippmExtract_v_64f(pSrc,srcStride2,pDst,len);
}
inline IppStatus ippmExtract_v_P(const Ipp32f** ppSrc, int srcRoiShift,
                                              Ipp32f*  pDst,  int len) {
  return ippmExtract_v_32f_P(ppSrc,srcRoiShift,pDst,len);
}
inline IppStatus ippmExtract_v_P(const Ipp64f** ppSrc, int srcRoiShift,
                                              Ipp64f*  pDst,  int len) {
  return ippmExtract_v_64f_P(ppSrc,srcRoiShift,pDst,len);
}
inline IppStatus ippmExtract_va(const Ipp32f*  pSrc,  int srcStride0, int srcStride2,
                                              Ipp32f*  pDst,  int len, int count) {
  return ippmExtract_va_32f(pSrc,srcStride0,srcStride2,pDst,len,count);
}
inline IppStatus ippmExtract_va(const Ipp64f*  pSrc,  int srcStride0, int srcStride2,
                                              Ipp64f*  pDst,  int len, int count) {
  return ippmExtract_va_64f(pSrc,srcStride0,srcStride2,pDst,len,count);
}
inline IppStatus ippmExtract_va_P(const Ipp32f** ppSrc, int srcRoiShift, int srcStride0,
                                              Ipp32f*  pDst,  int len, int count) {
  return ippmExtract_va_32f_P(ppSrc,srcRoiShift,srcStride0,pDst,len,count);
}
inline IppStatus ippmExtract_va_P(const Ipp64f** ppSrc, int srcRoiShift, int srcStride0,
                                              Ipp64f*  pDst,  int len, int count) {
  return ippmExtract_va_64f_P(ppSrc,srcRoiShift,srcStride0,pDst,len,count);
}
inline IppStatus ippmExtract_va_L(const Ipp32f** ppSrc, int srcRoiShift, int srcStride2,
                                              Ipp32f*  pDst,  int len, int count) {
  return ippmExtract_va_32f_L(ppSrc,srcRoiShift,srcStride2,pDst,len,count);
}
inline IppStatus ippmExtract_va_L(const Ipp64f** ppSrc, int srcRoiShift, int srcStride2,
                                              Ipp64f*  pDst,  int len, int count) {
  return ippmExtract_va_64f_L(ppSrc,srcRoiShift,srcStride2,pDst,len,count);
}
inline IppStatus ippmExtract_m(const Ipp32f*  pSrc,  int srcStride1, int srcStride2,
                                              Ipp32f*  pDst,  int width, int height) {
  return ippmExtract_m_32f(pSrc,srcStride1,srcStride2,pDst,width,height);
}
inline IppStatus ippmExtract_m(const Ipp64f*  pSrc,  int srcStride1, int srcStride2,
                                              Ipp64f*  pDst,  int width, int height) {
  return ippmExtract_m_64f(pSrc,srcStride1,srcStride2,pDst,width,height);
}
inline IppStatus ippmExtract_m_P(const Ipp32f** ppSrc, int srcRoiShift,
                                              Ipp32f*  pDst,  int width, int height) {
  return ippmExtract_m_32f_P(ppSrc,srcRoiShift,pDst,width,height);
}
inline IppStatus ippmExtract_m_P(const Ipp64f** ppSrc, int srcRoiShift,
                                              Ipp64f*  pDst,  int width, int height) {
  return ippmExtract_m_64f_P(ppSrc,srcRoiShift,pDst,width,height);
}
inline IppStatus ippmExtract_t(const Ipp32f*  pSrc,  int srcStride1, int srcStride2,
                                              Ipp32f*  pDst,  int width, int height) {
  return ippmExtract_t_32f(pSrc,srcStride1,srcStride2,pDst,width,height);
}
inline IppStatus ippmExtract_t(const Ipp64f*  pSrc,  int srcStride1, int srcStride2,
                                              Ipp64f*  pDst,  int width, int height) {
  return ippmExtract_t_64f(pSrc,srcStride1,srcStride2,pDst,width,height);
}
inline IppStatus ippmExtract_t_P(const Ipp32f** ppSrc, int srcRoiShift,
                                              Ipp32f*  pDst,  int width, int height) {
  return ippmExtract_t_32f_P(ppSrc,srcRoiShift,pDst,width,height);
}
inline IppStatus ippmExtract_t_P(const Ipp64f** ppSrc, int srcRoiShift,
                                              Ipp64f*  pDst,  int width, int height) {
  return ippmExtract_t_64f_P(ppSrc,srcRoiShift,pDst,width,height);
}
inline IppStatus ippmExtract_ma(const Ipp32f*  pSrc,  int srcStride0, int srcStride1, int srcStride2,
                                              Ipp32f*  pDst,  int width, int height, int count) {
  return ippmExtract_ma_32f(pSrc,srcStride0,srcStride1,srcStride2,pDst,width,height,count);
}
inline IppStatus ippmExtract_ma(const Ipp64f*  pSrc,  int srcStride0, int srcStride1, int srcStride2,
                                              Ipp64f*  pDst,  int width, int height, int count) {
  return ippmExtract_ma_64f(pSrc,srcStride0,srcStride1,srcStride2,pDst,width,height,count);
}
inline IppStatus ippmExtract_ma_P(const Ipp32f** ppSrc, int srcRoiShift, int srcStride0,
                                              Ipp32f*  pDst,  int width, int height, int count) {
  return ippmExtract_ma_32f_P(ppSrc,srcRoiShift,srcStride0,pDst,width,height,count);
}
inline IppStatus ippmExtract_ma_P(const Ipp64f** ppSrc, int srcRoiShift, int srcStride0,
                                              Ipp64f*  pDst,  int width, int height, int count) {
  return ippmExtract_ma_64f_P(ppSrc,srcRoiShift,srcStride0,pDst,width,height,count);
}
inline IppStatus ippmExtract_ma_L(const Ipp32f** ppSrc, int srcRoiShift, int srcStride1, int srcStride2,
                                              Ipp32f*  pDst,  int width, int height, int count) {
  return ippmExtract_ma_32f_L(ppSrc,srcRoiShift,srcStride1,srcStride2,pDst,width,height,count);
}
inline IppStatus ippmExtract_ma_L(const Ipp64f** ppSrc, int srcRoiShift, int srcStride1, int srcStride2,
                                              Ipp64f*  pDst,  int width, int height, int count) {
  return ippmExtract_ma_64f_L(ppSrc,srcRoiShift,srcStride1,srcStride2,pDst,width,height,count);
}
inline IppStatus ippmExtract_ta(const Ipp32f*  pSrc, int srcStride0, int srcStride1, int srcStride2,
                                              Ipp32f*  pDst, int width, int height, int count) {
  return ippmExtract_ta_32f(pSrc,srcStride0,srcStride1,srcStride2,pDst,width,height,count);
}
inline IppStatus ippmExtract_ta(const Ipp64f*  pSrc, int srcStride0, int srcStride1, int srcStride2,
                                              Ipp64f*  pDst, int width, int height, int count) {
  return ippmExtract_ta_64f(pSrc,srcStride0,srcStride1,srcStride2,pDst,width,height,count);
}
inline IppStatus ippmExtract_ta_P(const Ipp32f** ppSrc, int srcRoiShift, int srcStride0,
                                              Ipp32f*  pDst,  int width, int height, int count) {
  return ippmExtract_ta_32f_P(ppSrc,srcRoiShift,srcStride0,pDst,width,height,count);
}
inline IppStatus ippmExtract_ta_P(const Ipp64f** ppSrc, int srcRoiShift, int srcStride0,
                                              Ipp64f*  pDst,  int width, int height, int count) {
  return ippmExtract_ta_64f_P(ppSrc,srcRoiShift,srcStride0,pDst,width,height,count);
}
inline IppStatus ippmExtract_ta_L(const Ipp32f** ppSrc, int srcRoiShift, int srcStride1, int srcStride2,
                                              Ipp32f*  pDst,  int width, int height, int count) {
  return ippmExtract_ta_32f_L(ppSrc,srcRoiShift,srcStride1,srcStride2,pDst,width,height,count);
}
inline IppStatus ippmExtract_ta_L(const Ipp64f** ppSrc, int srcRoiShift, int srcStride1, int srcStride2,
                                              Ipp64f*  pDst,  int width, int height, int count) {
  return ippmExtract_ta_64f_L(ppSrc,srcRoiShift,srcStride1,srcStride2,pDst,width,height,count);
}
inline IppStatus ippmCopy_va_SS(const Ipp32f*  pSrc,  int srcStride0,  int srcStride2,
                                            Ipp32f*  pDst,  int dstStride0,  int dstStride2,
                                            int len, int count) {
  return ippmCopy_va_32f_SS(pSrc,srcStride0,srcStride2,pDst,dstStride0,dstStride2,len,count);
}
inline IppStatus ippmCopy_va_SS(const Ipp64f*  pSrc,  int srcStride0,  int srcStride2,
                                            Ipp64f*  pDst,  int dstStride0,  int dstStride2,
                                            int len, int count) {
  return ippmCopy_va_64f_SS(pSrc,srcStride0,srcStride2,pDst,dstStride0,dstStride2,len,count);
}
inline IppStatus ippmCopy_va_SP(const Ipp32f*  pSrc,  int srcStride0,  int srcStride2,
                                            Ipp32f** ppDst, int dstRoiShift, int dstStride0,
                                            int len, int count) {
  return ippmCopy_va_32f_SP(pSrc,srcStride0,srcStride2,ppDst,dstRoiShift,dstStride0,len,count);
}
inline IppStatus ippmCopy_va_SP(const Ipp64f*  pSrc,  int srcStride0,  int srcStride2,
                                            Ipp64f** ppDst, int dstRoiShift, int dstStride0,
                                            int len, int count) {
  return ippmCopy_va_64f_SP(pSrc,srcStride0,srcStride2,ppDst,dstRoiShift,dstStride0,len,count);
}
inline IppStatus ippmCopy_va_SL(const Ipp32f*  pSrc,  int srcStride0,  int srcStride2,
                                            Ipp32f** ppDst, int dstRoiShift, int dstStride2,
                                            int len, int count) {
  return ippmCopy_va_32f_SL(pSrc,srcStride0,srcStride2,ppDst,dstRoiShift,dstStride2,len,count);
}
inline IppStatus ippmCopy_va_SL(const Ipp64f*  pSrc,  int srcStride0,  int srcStride2,
                                            Ipp64f** ppDst, int dstRoiShift, int dstStride2,
                                            int len, int count) {
  return ippmCopy_va_64f_SL(pSrc,srcStride0,srcStride2,ppDst,dstRoiShift,dstStride2,len,count);
}
inline IppStatus ippmCopy_va_LS(const Ipp32f** ppSrc, int srcRoiShift, int srcStride2,
                                            Ipp32f*  pDst,  int dstStride0,  int dstStride2,
                                            int len, int count) {
  return ippmCopy_va_32f_LS(ppSrc,srcRoiShift,srcStride2,pDst,dstStride0,dstStride2,len,count);
}
inline IppStatus ippmCopy_va_LS(const Ipp64f** ppSrc, int srcRoiShift, int srcStride2,
                                            Ipp64f*  pDst,  int dstStride0,  int dstStride2,
                                            int len, int count) {
  return ippmCopy_va_64f_LS(ppSrc,srcRoiShift,srcStride2,pDst,dstStride0,dstStride2,len,count);
}
inline IppStatus ippmCopy_va_PS(const Ipp32f** ppSrc, int srcRoiShift, int srcStride0,
                                            Ipp32f*  pDst,  int dstStride0,  int dstStride2,
                                            int len, int count) {
  return ippmCopy_va_32f_PS(ppSrc,srcRoiShift,srcStride0,pDst,dstStride0,dstStride2,len,count);
}
inline IppStatus ippmCopy_va_PS(const Ipp64f** ppSrc, int srcRoiShift, int srcStride0,
                                            Ipp64f*  pDst,  int dstStride0,  int dstStride2,
                                            int len, int count) {
  return ippmCopy_va_64f_PS(ppSrc,srcRoiShift,srcStride0,pDst,dstStride0,dstStride2,len,count);
}
inline IppStatus ippmCopy_va_LP(const Ipp32f** ppSrc, int srcRoiShift, int srcStride2,
                                            Ipp32f** ppDst, int dstRoiShift, int dstStride0,
                                            int len, int count) {
  return ippmCopy_va_32f_LP(ppSrc,srcRoiShift,srcStride2,ppDst,dstRoiShift,dstStride0,len,count);
}
inline IppStatus ippmCopy_va_LP(const Ipp64f** ppSrc, int srcRoiShift, int srcStride2,
                                            Ipp64f** ppDst, int dstRoiShift, int dstStride0,
                                            int len, int count) {
  return ippmCopy_va_64f_LP(ppSrc,srcRoiShift,srcStride2,ppDst,dstRoiShift,dstStride0,len,count);
}
inline IppStatus ippmCopy_va_LL(const Ipp32f** ppSrc, int srcRoiShift, int srcStride2,
                                            Ipp32f** ppDst, int dstRoiShift, int dstStride2,
                                            int len, int count) {
  return ippmCopy_va_32f_LL(ppSrc,srcRoiShift,srcStride2,ppDst,dstRoiShift,dstStride2,len,count);
}
inline IppStatus ippmCopy_va_LL(const Ipp64f** ppSrc, int srcRoiShift, int srcStride2,
                                            Ipp64f** ppDst, int dstRoiShift, int dstStride2,
                                            int len, int count) {
  return ippmCopy_va_64f_LL(ppSrc,srcRoiShift,srcStride2,ppDst,dstRoiShift,dstStride2,len,count);
}
inline IppStatus ippmCopy_va_PP(const Ipp32f** ppSrc, int srcRoiShift, int srcStride0,
                                            Ipp32f** ppDst, int dstRoiShift, int dstStride0,
                                            int len, int count) {
  return ippmCopy_va_32f_PP(ppSrc,srcRoiShift,srcStride0,ppDst,dstRoiShift,dstStride0,len,count);
}
inline IppStatus ippmCopy_va_PP(const Ipp64f** ppSrc, int srcRoiShift, int srcStride0,
                                            Ipp64f** ppDst, int dstRoiShift, int dstStride0,
                                            int len, int count) {
  return ippmCopy_va_64f_PP(ppSrc,srcRoiShift,srcStride0,ppDst,dstRoiShift,dstStride0,len,count);
}
inline IppStatus ippmCopy_va_PL(const Ipp32f** ppSrc, int srcRoiShift, int srcStride0,
                                            Ipp32f** ppDst, int dstRoiShift, int dstStride2,
                                            int len, int count) {
  return ippmCopy_va_32f_PL(ppSrc,srcRoiShift,srcStride0,ppDst,dstRoiShift,dstStride2,len,count);
}
inline IppStatus ippmCopy_va_PL(const Ipp64f** ppSrc, int srcRoiShift, int srcStride0,
                                            Ipp64f** ppDst, int dstRoiShift, int dstStride2,
                                            int len, int count) {
  return ippmCopy_va_64f_PL(ppSrc,srcRoiShift,srcStride0,ppDst,dstRoiShift,dstStride2,len,count);
}
inline IppStatus ippmCopy_ma_SS(const Ipp32f*  pSrc,  int srcStride0, int srcStride1, int srcStride2,
                                            Ipp32f*  pDst,  int dstStride0, int dstStride1, int dstStride2,
                                            int width, int height, int count) {
  return ippmCopy_ma_32f_SS(pSrc,srcStride0,srcStride1,srcStride2,pDst,dstStride0,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmCopy_ma_SS(const Ipp64f*  pSrc,  int srcStride0, int srcStride1, int srcStride2,
                                            Ipp64f*  pDst,  int dstStride0, int dstStride1, int dstStride2,
                                            int width, int height, int count) {
  return ippmCopy_ma_64f_SS(pSrc,srcStride0,srcStride1,srcStride2,pDst,dstStride0,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmCopy_ma_SP(const Ipp32f*  pSrc,  int srcStride0, int srcStride1, int srcStride2,
                                            Ipp32f** ppDst, int dstRoiShift, int dstStride0,
                                            int width, int height, int count) {
  return ippmCopy_ma_32f_SP(pSrc,srcStride0,srcStride1,srcStride2,ppDst,dstRoiShift,dstStride0,width,height,count);
}
inline IppStatus ippmCopy_ma_SP(const Ipp64f*  pSrc,  int srcStride0, int srcStride1, int srcStride2,
                                            Ipp64f** ppDst, int dstRoiShift, int dstStride0,
                                            int width, int height, int count) {
  return ippmCopy_ma_64f_SP(pSrc,srcStride0,srcStride1,srcStride2,ppDst,dstRoiShift,dstStride0,width,height,count);
}
inline IppStatus ippmCopy_ma_SL(const Ipp32f*  pSrc,  int srcStride0, int srcStride1, int srcStride2,
                                            Ipp32f** ppDst, int dstRoiShift, int dstStride1, int dstStride2,
                                            int width, int height, int count) {
  return ippmCopy_ma_32f_SL(pSrc,srcStride0,srcStride1,srcStride2,ppDst,dstRoiShift,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmCopy_ma_SL(const Ipp64f*  pSrc,  int srcStride0, int srcStride1, int srcStride2,
                                            Ipp64f** ppDst, int dstRoiShift, int dstStride1, int dstStride2,
                                            int width, int height, int count) {
  return ippmCopy_ma_64f_SL(pSrc,srcStride0,srcStride1,srcStride2,ppDst,dstRoiShift,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmCopy_ma_LS(const Ipp32f** ppSrc, int srcRoiShift, int srcStride1, int srcStride2,
                                            Ipp32f*  pDst,  int dstStride0, int dstStride1, int dstStride2,
                                            int width, int height, int count) {
  return ippmCopy_ma_32f_LS(ppSrc,srcRoiShift,srcStride1,srcStride2,pDst,dstStride0,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmCopy_ma_LS(const Ipp64f** ppSrc, int srcRoiShift, int srcStride1, int srcStride2,
                                            Ipp64f*  pDst,  int dstStride0, int dstStride1, int dstStride2,
                                            int width, int height, int count) {
  return ippmCopy_ma_64f_LS(ppSrc,srcRoiShift,srcStride1,srcStride2,pDst,dstStride0,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmCopy_ma_PS(const Ipp32f** ppSrc, int srcRoiShift, int srcStride0,
                                            Ipp32f*  pDst,  int dstStride0, int dstStride1, int dstStride2,
                                            int width, int height, int count) {
  return ippmCopy_ma_32f_PS(ppSrc,srcRoiShift,srcStride0,pDst,dstStride0,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmCopy_ma_PS(const Ipp64f** ppSrc, int srcRoiShift, int srcStride0,
                                            Ipp64f*  pDst,  int dstStride0, int dstStride1, int dstStride2,
                                            int width, int height, int count) {
  return ippmCopy_ma_64f_PS(ppSrc,srcRoiShift,srcStride0,pDst,dstStride0,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmCopy_ma_LP(const Ipp32f** ppSrc, int srcRoiShift, int srcStride1, int srcStride2,
                                            Ipp32f** ppDst, int dstRoiShift, int dstStride0,
                                            int width, int height, int count) {
  return ippmCopy_ma_32f_LP(ppSrc,srcRoiShift,srcStride1,srcStride2,ppDst,dstRoiShift,dstStride0,width,height,count);
}
inline IppStatus ippmCopy_ma_LP(const Ipp64f** ppSrc, int srcRoiShift, int srcStride1, int srcStride2,
                                            Ipp64f** ppDst, int dstRoiShift, int dstStride0,
                                            int width, int height, int count) {
  return ippmCopy_ma_64f_LP(ppSrc,srcRoiShift,srcStride1,srcStride2,ppDst,dstRoiShift,dstStride0,width,height,count);
}
inline IppStatus ippmCopy_ma_LL(const Ipp32f** ppSrc, int srcRoiShift, int srcStride1, int srcStride2,
                                            Ipp32f** ppDst, int dstRoiShift, int dstStride1, int dstStride2,
                                            int width, int height, int count) {
  return ippmCopy_ma_32f_LL(ppSrc,srcRoiShift,srcStride1,srcStride2,ppDst,dstRoiShift,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmCopy_ma_LL(const Ipp64f** ppSrc, int srcRoiShift, int srcStride1, int srcStride2,
                                            Ipp64f** ppDst, int dstRoiShift, int dstStride1, int dstStride2,
                                            int width, int height, int count) {
  return ippmCopy_ma_64f_LL(ppSrc,srcRoiShift,srcStride1,srcStride2,ppDst,dstRoiShift,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmCopy_ma_PP(const Ipp32f** ppSrc, int srcRoiShift, int srcStride0,
                                            Ipp32f** ppDst, int dstRoiShift, int dstStride0,
                                            int width, int height, int count) {
  return ippmCopy_ma_32f_PP(ppSrc,srcRoiShift,srcStride0,ppDst,dstRoiShift,dstStride0,width,height,count);
}
inline IppStatus ippmCopy_ma_PP(const Ipp64f** ppSrc, int srcRoiShift, int srcStride0,
                                            Ipp64f** ppDst, int dstRoiShift, int dstStride0,
                                            int width, int height, int count) {
  return ippmCopy_ma_64f_PP(ppSrc,srcRoiShift,srcStride0,ppDst,dstRoiShift,dstStride0,width,height,count);
}
inline IppStatus ippmCopy_ma_PL(const Ipp32f** ppSrc, int srcRoiShift, int srcStride0,
                                            Ipp32f** ppDst, int dstRoiShift, int dstStride1, int dstStride2,
                                            int width, int height, int count) {
  return ippmCopy_ma_32f_PL(ppSrc,srcRoiShift,srcStride0,ppDst,dstRoiShift,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmCopy_ma_PL(const Ipp64f** ppSrc, int srcRoiShift, int srcStride0,
                                            Ipp64f** ppDst, int dstRoiShift, int dstStride1, int dstStride2,
                                            int width, int height, int count) {
  return ippmCopy_ma_64f_PL(ppSrc,srcRoiShift,srcStride0,ppDst,dstRoiShift,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmLoadIdentity_ma(Ipp32f*  pDst,  int dstStride0, int dstStride1, int dstStride2,
                                             int width, int height, int count) {
  return ippmLoadIdentity_ma_32f(pDst,dstStride0,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmLoadIdentity_ma(Ipp64f*  pDst,  int dstStride0, int dstStride1, int dstStride2,
                                             int width, int height, int count) {
  return ippmLoadIdentity_ma_64f(pDst,dstStride0,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmLoadIdentity_ma_P(Ipp32f** ppDst, int dstRoiShift, int dstStride0,
                                             int width, int height, int count) {
  return ippmLoadIdentity_ma_32f_P(ppDst,dstRoiShift,dstStride0,width,height,count);
}
inline IppStatus ippmLoadIdentity_ma_P(Ipp64f** ppDst, int dstRoiShift, int dstStride0,
                                             int width, int height, int count) {
  return ippmLoadIdentity_ma_64f_P(ppDst,dstRoiShift,dstStride0,width,height,count);
}
inline IppStatus ippmLoadIdentity_ma_L(Ipp32f** ppDst, int dstRoiShift, int dstStride1, int dstStride2,
                                             int width, int height, int count) {
  return ippmLoadIdentity_ma_32f_L(ppDst,dstRoiShift,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmLoadIdentity_ma_L(Ipp64f** ppDst, int dstRoiShift, int dstStride1, int dstStride2,
                                             int width, int height, int count) {
  return ippmLoadIdentity_ma_64f_L(ppDst,dstRoiShift,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmSaxpy_vv(const Ipp32f* pSrc1, int src1Stride2, Ipp32f scale,
                                       const Ipp32f* pSrc2, int src2Stride2,
                                             Ipp32f* pDst,  int dstStride2,
                                             int len) {
  return ippmSaxpy_vv_32f(pSrc1,src1Stride2,scale,pSrc2,src2Stride2,pDst,dstStride2,len);
}
inline IppStatus ippmSaxpy_vv(const Ipp64f* pSrc1, int src1Stride2, Ipp64f scale,
                                       const Ipp64f* pSrc2, int src2Stride2,
                                             Ipp64f* pDst,  int dstStride2,
                                             int len) {
  return ippmSaxpy_vv_64f(pSrc1,src1Stride2,scale,pSrc2,src2Stride2,pDst,dstStride2,len);
}
inline IppStatus ippmSaxpy_vv_P(const Ipp32f** ppSrc1, int src1RoiShift, Ipp32f scale,
                                       const Ipp32f** ppSrc2, int src2RoiShift,
                                             Ipp32f** ppDst,  int dstRoiShift,
                                             int len) {
  return ippmSaxpy_vv_32f_P(ppSrc1,src1RoiShift,scale,ppSrc2,src2RoiShift,ppDst,dstRoiShift,len);
}
inline IppStatus ippmSaxpy_vv_P(const Ipp64f** ppSrc1, int src1RoiShift, Ipp64f scale,
                                       const Ipp64f** ppSrc2, int src2RoiShift,
                                             Ipp64f** ppDst,  int dstRoiShift,
                                             int len) {
  return ippmSaxpy_vv_64f_P(ppSrc1,src1RoiShift,scale,ppSrc2,src2RoiShift,ppDst,dstRoiShift,len);
}
inline IppStatus ippmSaxpy_vva(const Ipp32f* pSrc1, int src1Stride2, Ipp32f scale,
                                       const Ipp32f* pSrc2, int src2Stride0, int src2Stride2,
                                             Ipp32f* pDst,  int dstStride0,  int dstStride2,
                                             int len, int count) {
  return ippmSaxpy_vva_32f(pSrc1,src1Stride2,scale,pSrc2,src2Stride0,src2Stride2,pDst,dstStride0,dstStride2,len,count);
}
inline IppStatus ippmSaxpy_vva(const Ipp64f* pSrc1, int src1Stride2, Ipp64f scale,
                                       const Ipp64f* pSrc2, int src2Stride0, int src2Stride2,
                                             Ipp64f* pDst,  int dstStride0,  int dstStride2,
                                             int len, int count) {
  return ippmSaxpy_vva_64f(pSrc1,src1Stride2,scale,pSrc2,src2Stride0,src2Stride2,pDst,dstStride0,dstStride2,len,count);
}
inline IppStatus ippmSaxpy_vva_P(const Ipp32f** ppSrc1, int src1RoiShift, Ipp32f scale,
                                       const Ipp32f** ppSrc2, int src2RoiShift, int src2Stride0,
                                             Ipp32f** ppDst,  int dstRoiShift,  int dstStride0,
                                             int len, int count) {
  return ippmSaxpy_vva_32f_P(ppSrc1,src1RoiShift,scale,ppSrc2,src2RoiShift,src2Stride0,ppDst,dstRoiShift,dstStride0,len,count);
}
inline IppStatus ippmSaxpy_vva_P(const Ipp64f** ppSrc1, int src1RoiShift, Ipp64f scale,
                                       const Ipp64f** ppSrc2, int src2RoiShift, int src2Stride0,
                                             Ipp64f** ppDst,  int dstRoiShift,  int dstStride0,
                                             int len, int count) {
  return ippmSaxpy_vva_64f_P(ppSrc1,src1RoiShift,scale,ppSrc2,src2RoiShift,src2Stride0,ppDst,dstRoiShift,dstStride0,len,count);
}
inline IppStatus ippmSaxpy_vva_L(const Ipp32f*  pSrc1,  int src1Stride2, Ipp32f scale,
                                       const Ipp32f** ppSrc2, int src2RoiShift, int src2Stride2,
                                             Ipp32f** ppDst,  int dstRoiShift,  int dstStride2,
                                             int len, int count) {
  return ippmSaxpy_vva_32f_L(pSrc1,src1Stride2,scale,ppSrc2,src2RoiShift,src2Stride2,ppDst,dstRoiShift,dstStride2,len,count);
}
inline IppStatus ippmSaxpy_vva_L(const Ipp64f*  pSrc1,  int src1Stride2, Ipp64f scale,
                                       const Ipp64f** ppSrc2, int src2RoiShift, int src2Stride2,
                                             Ipp64f** ppDst,  int dstRoiShift,  int dstStride2,
                                             int len, int count) {
  return ippmSaxpy_vva_64f_L(pSrc1,src1Stride2,scale,ppSrc2,src2RoiShift,src2Stride2,ppDst,dstRoiShift,dstStride2,len,count);
}
inline IppStatus ippmSaxpy_vav(const Ipp32f*  pSrc1,  int src1Stride0, int src1Stride2, Ipp32f scale,
                                       const Ipp32f*  pSrc2,  int src2Stride2,
                                             Ipp32f*  pDst,   int dstStride0,  int dstStride2,
                                             int len, int count) {
  return ippmSaxpy_vav_32f(pSrc1,src1Stride0,src1Stride2,scale,pSrc2,src2Stride2,pDst,dstStride0,dstStride2,len,count);
}
inline IppStatus ippmSaxpy_vav(const Ipp64f* pSrc1, int src1Stride0, int src1Stride2, Ipp64f scale,
                                       const Ipp64f* pSrc2, int src2Stride2,
                                             Ipp64f* pDst,  int dstStride0,  int dstStride2,
                                             int len, int count) {
  return ippmSaxpy_vav_64f(pSrc1,src1Stride0,src1Stride2,scale,pSrc2,src2Stride2,pDst,dstStride0,dstStride2,len,count);
}
inline IppStatus ippmSaxpy_vav_P(const Ipp32f** ppSrc1, int src1RoiShift, int src1Stride0, Ipp32f scale,
                                        const Ipp32f** ppSrc2, int src2RoiShift,
                                              Ipp32f** ppDst,  int dstRoiShift,  int dstStride0,
                                              int len, int count) {
  return ippmSaxpy_vav_32f_P(ppSrc1,src1RoiShift,src1Stride0,scale,ppSrc2,src2RoiShift,ppDst,dstRoiShift,dstStride0,len,count);
}
inline IppStatus ippmSaxpy_vav_P(const Ipp64f** ppSrc1, int src1RoiShift, int src1Stride0, Ipp64f scale,
                                        const Ipp64f** ppSrc2, int src2RoiShift,
                                              Ipp64f** ppDst,  int dstRoiShift,  int dstStride0,
                                              int len, int count) {
  return ippmSaxpy_vav_64f_P(ppSrc1,src1RoiShift,src1Stride0,scale,ppSrc2,src2RoiShift,ppDst,dstRoiShift,dstStride0,len,count);
}
inline IppStatus ippmSaxpy_vav_L(const Ipp32f** ppSrc1, int src1RoiShift, int src1Stride2, Ipp32f scale,
                                        const Ipp32f*  pSrc2,  int src2Stride2,
                                              Ipp32f** ppDst,  int dstRoiShift,  int dstStride2,
                                              int len, int count) {
  return ippmSaxpy_vav_32f_L(ppSrc1,src1RoiShift,src1Stride2,scale,pSrc2,src2Stride2,ppDst,dstRoiShift,dstStride2,len,count);
}
inline IppStatus ippmSaxpy_vav_L(const Ipp64f** ppSrc1, int src1RoiShift, int src1Stride2, Ipp64f scale,
                                        const Ipp64f*  pSrc2,  int src2Stride2,
                                              Ipp64f** ppDst,  int dstRoiShift,  int dstStride2,
                                              int len, int count) {
  return ippmSaxpy_vav_64f_L(ppSrc1,src1RoiShift,src1Stride2,scale,pSrc2,src2Stride2,ppDst,dstRoiShift,dstStride2,len,count);
}
inline IppStatus ippmSaxpy_vava(const Ipp32f*  pSrc1,  int src1Stride0,  int src1Stride2, Ipp32f scale,
                                        const Ipp32f*  pSrc2,  int src2Stride0,  int src2Stride2,
                                              Ipp32f*  pDst,   int dstStride0,   int dstStride2,
                                              int len, int count) {
  return ippmSaxpy_vava_32f(pSrc1,src1Stride0,src1Stride2,scale,pSrc2,src2Stride0,src2Stride2,pDst,dstStride0,dstStride2,len,count);
}
inline IppStatus ippmSaxpy_vava(const Ipp64f*  pSrc1,  int src1Stride0,  int src1Stride2, Ipp64f scale,
                                        const Ipp64f*  pSrc2,  int src2Stride0,  int src2Stride2,
                                              Ipp64f*  pDst,   int dstStride0,   int dstStride2,
                                              int len, int count) {
  return ippmSaxpy_vava_64f(pSrc1,src1Stride0,src1Stride2,scale,pSrc2,src2Stride0,src2Stride2,pDst,dstStride0,dstStride2,len,count);
}
inline IppStatus ippmSaxpy_vava_P(const Ipp32f** ppSrc1, int src1RoiShift, int src1Stride0, Ipp32f scale,
                                        const Ipp32f** ppSrc2, int src2RoiShift, int src2Stride0,
                                              Ipp32f** ppDst,  int dstRoiShift,  int dstStride0,
                                              int len, int count) {
  return ippmSaxpy_vava_32f_P(ppSrc1,src1RoiShift,src1Stride0,scale,ppSrc2,src2RoiShift,src2Stride0,ppDst,dstRoiShift,dstStride0,len,count);
}
inline IppStatus ippmSaxpy_vava_P(const Ipp64f** ppSrc1, int src1RoiShift, int src1Stride0, Ipp64f scale,
                                        const Ipp64f** ppSrc2, int src2RoiShift, int src2Stride0,
                                              Ipp64f** ppDst,  int dstRoiShift,  int dstStride0,
                                              int len, int count) {
  return ippmSaxpy_vava_64f_P(ppSrc1,src1RoiShift,src1Stride0,scale,ppSrc2,src2RoiShift,src2Stride0,ppDst,dstRoiShift,dstStride0,len,count);
}
inline IppStatus ippmSaxpy_vava_L(const Ipp32f** ppSrc1, int src1RoiShift, int src1Stride2, Ipp32f scale,
                                        const Ipp32f** ppSrc2, int src2RoiShift, int src2Stride2,
                                              Ipp32f** ppDst,  int dstRoiShift,  int dstStride2,
                                              int len, int count) {
  return ippmSaxpy_vava_32f_L(ppSrc1,src1RoiShift,src1Stride2,scale,ppSrc2,src2RoiShift,src2Stride2,ppDst,dstRoiShift,dstStride2,len,count);
}
inline IppStatus ippmSaxpy_vava_L(const Ipp64f** ppSrc1, int src1RoiShift, int src1Stride2, Ipp64f scale,
                                        const Ipp64f** ppSrc2, int src2RoiShift, int src2Stride2,
                                              Ipp64f** ppDst,  int dstRoiShift,  int dstStride2,
                                              int len, int count) {
  return ippmSaxpy_vava_64f_L(ppSrc1,src1RoiShift,src1Stride2,scale,ppSrc2,src2RoiShift,src2Stride2,ppDst,dstRoiShift,dstStride2,len,count);
}
inline IppStatus ippmAdd_vc(const Ipp32f*  pSrc,  int srcStride2, Ipp32f val,
                                           Ipp32f*  pDst,  int dstStride2,
                                           int len) {
  return ippmAdd_vc_32f(pSrc,srcStride2,val,pDst,dstStride2,len);
}
inline IppStatus ippmAdd_vc(const Ipp64f*  pSrc,  int srcStride2, Ipp64f val,
                                           Ipp64f*  pDst,  int dstStride2,
                                           int len) {
  return ippmAdd_vc_64f(pSrc,srcStride2,val,pDst,dstStride2,len);
}
inline IppStatus ippmAdd_vc_P(const Ipp32f** ppSrc, int srcRoiShift, Ipp32f val,
                                           Ipp32f** ppDst, int dstRoiShift,
                                           int len) {
  return ippmAdd_vc_32f_P(ppSrc,srcRoiShift,val,ppDst,dstRoiShift,len);
}
inline IppStatus ippmAdd_vc_P(const Ipp64f** ppSrc, int srcRoiShift, Ipp64f val,
                                           Ipp64f** ppDst, int dstRoiShift,
                                           int len) {
  return ippmAdd_vc_64f_P(ppSrc,srcRoiShift,val,ppDst,dstRoiShift,len);
}
inline IppStatus ippmAdd_vac(const Ipp32f*  pSrc,  int srcStride0, int srcStride2, Ipp32f val,
                                           Ipp32f*  pDst,  int dstStride0, int dstStride2,
                                           int len, int count) {
  return ippmAdd_vac_32f(pSrc,srcStride0,srcStride2,val,pDst,dstStride0,dstStride2,len,count);
}
inline IppStatus ippmAdd_vac(const Ipp64f*  pSrc,  int srcStride0, int srcStride2, Ipp64f val,
                                           Ipp64f*  pDst,  int dstStride0, int dstStride2,
                                           int len, int count) {
  return ippmAdd_vac_64f(pSrc,srcStride0,srcStride2,val,pDst,dstStride0,dstStride2,len,count);
}
inline IppStatus ippmAdd_vac_P(const Ipp32f** ppSrc, int srcRoiShift, int srcStride0, Ipp32f val,
                                           Ipp32f** ppDst, int dstRoiShift, int dstStride0,
                                           int len, int count) {
  return ippmAdd_vac_32f_P(ppSrc,srcRoiShift,srcStride0,val,ppDst,dstRoiShift,dstStride0,len,count);
}
inline IppStatus ippmAdd_vac_P(const Ipp64f** ppSrc, int srcRoiShift, int srcStride0, Ipp64f val,
                                           Ipp64f** ppDst, int dstRoiShift, int dstStride0,
                                           int len, int count) {
  return ippmAdd_vac_64f_P(ppSrc,srcRoiShift,srcStride0,val,ppDst,dstRoiShift,dstStride0,len,count);
}
inline IppStatus ippmAdd_vac_L(const Ipp32f** ppSrc, int srcRoiShift, int srcStride2, Ipp32f val,
                                           Ipp32f** ppDst, int dstRoiShift, int dstStride2,
                                           int len, int count) {
  return ippmAdd_vac_32f_L(ppSrc,srcRoiShift,srcStride2,val,ppDst,dstRoiShift,dstStride2,len,count);
}
inline IppStatus ippmAdd_vac_L(const Ipp64f** ppSrc, int srcRoiShift, int srcStride2, Ipp64f val,
                                           Ipp64f** ppDst, int dstRoiShift, int dstStride2,
                                           int len, int count) {
  return ippmAdd_vac_64f_L(ppSrc,srcRoiShift,srcStride2,val,ppDst,dstRoiShift,dstStride2,len,count);
}
inline IppStatus ippmAdd_vv(const Ipp32f*  pSrc1, int src1Stride2,
                                     const Ipp32f*  pSrc2, int src2Stride2,
                                           Ipp32f*  pDst,  int dstStride2,
                                           int len) {
  return ippmAdd_vv_32f(pSrc1,src1Stride2,pSrc2,src2Stride2,pDst,dstStride2,len);
}
inline IppStatus ippmAdd_vv(const Ipp64f*  pSrc1, int src1Stride2,
                                     const Ipp64f*  pSrc2, int src2Stride2,
                                           Ipp64f*  pDst,  int dstStride2,
                                           int len) {
  return ippmAdd_vv_64f(pSrc1,src1Stride2,pSrc2,src2Stride2,pDst,dstStride2,len);
}
inline IppStatus ippmAdd_vv_P(const Ipp32f** ppSrc1, int src1RoiShift,
                                     const Ipp32f** ppSrc2, int src2RoiShift,
                                           Ipp32f** ppDst,  int dstRoiShift,
                                           int len) {
  return ippmAdd_vv_32f_P(ppSrc1,src1RoiShift,ppSrc2,src2RoiShift,ppDst,dstRoiShift,len);
}
inline IppStatus ippmAdd_vv_P(const Ipp64f** ppSrc1, int src1RoiShift,
                                     const Ipp64f** ppSrc2, int src2RoiShift,
                                           Ipp64f** ppDst,  int dstRoiShift,
                                           int len) {
  return ippmAdd_vv_64f_P(ppSrc1,src1RoiShift,ppSrc2,src2RoiShift,ppDst,dstRoiShift,len);
}
inline IppStatus ippmAdd_vav(const Ipp32f*  pSrc1,  int src1Stride0, int src1Stride2,
                                     const Ipp32f*  pSrc2,  int src2Stride2,
                                           Ipp32f*  pDst,   int dstStride0,  int dstStride2,
                                           int len, int count) {
  return ippmAdd_vav_32f(pSrc1,src1Stride0,src1Stride2,pSrc2,src2Stride2,pDst,dstStride0,dstStride2,len,count);
}
inline IppStatus ippmAdd_vav(const Ipp64f*  pSrc1,  int src1Stride0, int src1Stride2,
                                     const Ipp64f*  pSrc2,  int src2Stride2,
                                           Ipp64f*  pDst,   int dstStride0,  int dstStride2,
                                           int len, int count) {
  return ippmAdd_vav_64f(pSrc1,src1Stride0,src1Stride2,pSrc2,src2Stride2,pDst,dstStride0,dstStride2,len,count);
}
inline IppStatus ippmAdd_vav_P(const Ipp32f** ppSrc1, int src1RoiShift, int src1Stride0,
                                     const Ipp32f** ppSrc2, int src2RoiShift,
                                           Ipp32f** ppDst,  int dstRoiShift,  int dstStride0,
                                           int len, int count) {
  return ippmAdd_vav_32f_P(ppSrc1,src1RoiShift,src1Stride0,ppSrc2,src2RoiShift,ppDst,dstRoiShift,dstStride0,len,count);
}
inline IppStatus ippmAdd_vav_P(const Ipp64f** ppSrc1, int src1RoiShift, int src1Stride0,
                                     const Ipp64f** ppSrc2, int src2RoiShift,
                                           Ipp64f** ppDst,  int dstRoiShift,  int dstStride0,
                                           int len, int count) {
  return ippmAdd_vav_64f_P(ppSrc1,src1RoiShift,src1Stride0,ppSrc2,src2RoiShift,ppDst,dstRoiShift,dstStride0,len,count);
}
inline IppStatus ippmAdd_vav_L(const Ipp32f** ppSrc1, int src1RoiShift, int src1Stride2,
                                     const Ipp32f*  pSrc2,  int src2Stride2,
                                           Ipp32f** ppDst,  int dstRoiShift,  int dstStride2,
                                           int len, int count) {
  return ippmAdd_vav_32f_L(ppSrc1,src1RoiShift,src1Stride2,pSrc2,src2Stride2,ppDst,dstRoiShift,dstStride2,len,count);
}
inline IppStatus ippmAdd_vav_L(const Ipp64f** ppSrc1, int src1RoiShift, int src1Stride2,
                                     const Ipp64f*  pSrc2,  int src2Stride2,
                                           Ipp64f** ppDst,  int dstRoiShift,  int dstStride2,
                                           int len, int count) {
  return ippmAdd_vav_64f_L(ppSrc1,src1RoiShift,src1Stride2,pSrc2,src2Stride2,ppDst,dstRoiShift,dstStride2,len,count);
}
inline IppStatus ippmAdd_vava(const Ipp32f*  pSrc1,  int src1Stride0, int src1Stride2,
                                     const Ipp32f*  pSrc2,  int src2Stride0, int src2Stride2,
                                           Ipp32f*  pDst,   int dstStride0,  int dstStride2,
                                           int len, int count) {
  return ippmAdd_vava_32f(pSrc1,src1Stride0,src1Stride2,pSrc2,src2Stride0,src2Stride2,pDst,dstStride0,dstStride2,len,count);
}
inline IppStatus ippmAdd_vava(const Ipp64f*  pSrc1,  int src1Stride0, int src1Stride2,
                                     const Ipp64f*  pSrc2,  int src2Stride0, int src2Stride2,
                                           Ipp64f*  pDst,   int dstStride0,  int dstStride2,
                                           int len, int count) {
  return ippmAdd_vava_64f(pSrc1,src1Stride0,src1Stride2,pSrc2,src2Stride0,src2Stride2,pDst,dstStride0,dstStride2,len,count);
}
inline IppStatus ippmAdd_vava_P(const Ipp32f** ppSrc1, int src1RoiShift, int src1Stride0,
                                      const Ipp32f** ppSrc2, int src2RoiShift, int src2Stride0,
                                            Ipp32f** ppDst,  int dstRoiShift,  int dstStride0,
                                            int len, int count) {
  return ippmAdd_vava_32f_P(ppSrc1,src1RoiShift,src1Stride0,ppSrc2,src2RoiShift,src2Stride0,ppDst,dstRoiShift,dstStride0,len,count);
}
inline IppStatus ippmAdd_vava_P(const Ipp64f** ppSrc1, int src1RoiShift, int src1Stride0,
                                      const Ipp64f** ppSrc2, int src2RoiShift, int src2Stride0,
                                            Ipp64f** ppDst,  int dstRoiShift,  int dstStride0,
                                            int len, int count) {
  return ippmAdd_vava_64f_P(ppSrc1,src1RoiShift,src1Stride0,ppSrc2,src2RoiShift,src2Stride0,ppDst,dstRoiShift,dstStride0,len,count);
}
inline IppStatus ippmAdd_vava_L(const Ipp32f** ppSrc1, int src1RoiShift, int src1Stride2,
                                      const Ipp32f** ppSrc2, int src2RoiShift, int src2Stride2,
                                            Ipp32f** ppDst,  int dstRoiShift,  int dstStride2,
                                            int len, int count) {
  return ippmAdd_vava_32f_L(ppSrc1,src1RoiShift,src1Stride2,ppSrc2,src2RoiShift,src2Stride2,ppDst,dstRoiShift,dstStride2,len,count);
}
inline IppStatus ippmAdd_vava_L(const Ipp64f** ppSrc1, int src1RoiShift, int src1Stride2,
                                      const Ipp64f** ppSrc2, int src2RoiShift, int src2Stride2,
                                            Ipp64f** ppDst,  int dstRoiShift,  int dstStride2,
                                            int len, int count) {
  return ippmAdd_vava_64f_L(ppSrc1,src1RoiShift,src1Stride2,ppSrc2,src2RoiShift,src2Stride2,ppDst,dstRoiShift,dstStride2,len,count);
}
inline IppStatus ippmSub_vc(const Ipp32f*  pSrc,  int srcStride2, Ipp32f val,
                                           Ipp32f*  pDst,  int dstStride2,
                                           int len) {
  return ippmSub_vc_32f(pSrc,srcStride2,val,pDst,dstStride2,len);
}
inline IppStatus ippmSub_vc(const Ipp64f*  pSrc,  int srcStride2, Ipp64f val,
                                           Ipp64f*  pDst,  int dstStride2,
                                           int len) {
  return ippmSub_vc_64f(pSrc,srcStride2,val,pDst,dstStride2,len);
}
inline IppStatus ippmSub_vc_P(const Ipp32f** ppSrc, int srcRoiShift, Ipp32f val,
                                           Ipp32f** ppDst, int dstRoiShift,
                                           int len) {
  return ippmSub_vc_32f_P(ppSrc,srcRoiShift,val,ppDst,dstRoiShift,len);
}
inline IppStatus ippmSub_vc_P(const Ipp64f** ppSrc, int srcRoiShift, Ipp64f val,
                                           Ipp64f** ppDst, int dstRoiShift,
                                           int len) {
  return ippmSub_vc_64f_P(ppSrc,srcRoiShift,val,ppDst,dstRoiShift,len);
}
inline IppStatus ippmSub_cv(const Ipp32f*  pSrc,  int srcStride2, Ipp32f val,
                                           Ipp32f*  pDst,  int dstStride2,
                                           int len) {
  return ippmSub_cv_32f(pSrc,srcStride2,val,pDst,dstStride2,len);
}
inline IppStatus ippmSub_cv(const Ipp64f*  pSrc,  int srcStride2, Ipp64f val,
                                           Ipp64f*  pDst,  int dstStride2,
                                           int len) {
  return ippmSub_cv_64f(pSrc,srcStride2,val,pDst,dstStride2,len);
}
inline IppStatus ippmSub_cv_P(const Ipp32f** ppSrc, int srcRoiShift, Ipp32f val,
                                           Ipp32f** ppDst, int dstRoiShift,
                                           int len) {
  return ippmSub_cv_32f_P(ppSrc,srcRoiShift,val,ppDst,dstRoiShift,len);
}
inline IppStatus ippmSub_cv_P(const Ipp64f** ppSrc, int srcRoiShift, Ipp64f val,
                                           Ipp64f** ppDst, int dstRoiShift,
                                           int len) {
  return ippmSub_cv_64f_P(ppSrc,srcRoiShift,val,ppDst,dstRoiShift,len);
}
inline IppStatus ippmSub_vac(const Ipp32f*  pSrc,  int srcStride0, int srcStride2, Ipp32f val,
                                           Ipp32f*  pDst,  int dstStride0, int dstStride2,
                                           int len, int count) {
  return ippmSub_vac_32f(pSrc,srcStride0,srcStride2,val,pDst,dstStride0,dstStride2,len,count);
}
inline IppStatus ippmSub_vac(const Ipp64f*  pSrc,  int srcStride0, int srcStride2, Ipp64f val,
                                           Ipp64f*  pDst,  int dstStride0, int dstStride2,
                                           int len, int count) {
  return ippmSub_vac_64f(pSrc,srcStride0,srcStride2,val,pDst,dstStride0,dstStride2,len,count);
}
inline IppStatus ippmSub_vac_P(const Ipp32f** ppSrc, int srcRoiShift, int srcStride0, Ipp32f val,
                                           Ipp32f** ppDst, int dstRoiShift, int dstStride0,
                                           int len, int count) {
  return ippmSub_vac_32f_P(ppSrc,srcRoiShift,srcStride0,val,ppDst,dstRoiShift,dstStride0,len,count);
}
inline IppStatus ippmSub_vac_P(const Ipp64f** ppSrc, int srcRoiShift, int srcStride0, Ipp64f val,
                                           Ipp64f** ppDst, int dstRoiShift, int dstStride0,
                                           int len, int count) {
  return ippmSub_vac_64f_P(ppSrc,srcRoiShift,srcStride0,val,ppDst,dstRoiShift,dstStride0,len,count);
}
inline IppStatus ippmSub_vac_L(const Ipp32f** ppSrc, int srcRoiShift, int srcStride2, Ipp32f val,
                                           Ipp32f** ppDst, int dstRoiShift, int dstStride2,
                                           int len, int count) {
  return ippmSub_vac_32f_L(ppSrc,srcRoiShift,srcStride2,val,ppDst,dstRoiShift,dstStride2,len,count);
}
inline IppStatus ippmSub_vac_L(const Ipp64f** ppSrc, int srcRoiShift, int srcStride2, Ipp64f val,
                                           Ipp64f** ppDst, int dstRoiShift, int dstStride2,
                                           int len, int count) {
  return ippmSub_vac_64f_L(ppSrc,srcRoiShift,srcStride2,val,ppDst,dstRoiShift,dstStride2,len,count);
}
inline IppStatus ippmSub_cva(const Ipp32f*  pSrc,  int srcStride0, int srcStride2, Ipp32f val,
                                           Ipp32f*  pDst,  int dstStride0, int dstStride2,
                                           int len, int count) {
  return ippmSub_cva_32f(pSrc,srcStride0,srcStride2,val,pDst,dstStride0,dstStride2,len,count);
}
inline IppStatus ippmSub_cva(const Ipp64f*  pSrc,  int srcStride0, int srcStride2, Ipp64f val,
                                           Ipp64f*  pDst,  int dstStride0, int dstStride2,
                                           int len, int count) {
  return ippmSub_cva_64f(pSrc,srcStride0,srcStride2,val,pDst,dstStride0,dstStride2,len,count);
}
inline IppStatus ippmSub_cva_P(const Ipp32f** ppSrc, int srcRoiShift, int srcStride0, Ipp32f val,
                                           Ipp32f** ppDst, int dstRoiShift, int dstStride0,
                                           int len, int count) {
  return ippmSub_cva_32f_P(ppSrc,srcRoiShift,srcStride0,val,ppDst,dstRoiShift,dstStride0,len,count);
}
inline IppStatus ippmSub_cva_P(const Ipp64f** ppSrc, int srcRoiShift, int srcStride0, Ipp64f val,
                                           Ipp64f** ppDst, int dstRoiShift, int dstStride0,
                                           int len, int count) {
  return ippmSub_cva_64f_P(ppSrc,srcRoiShift,srcStride0,val,ppDst,dstRoiShift,dstStride0,len,count);
}
inline IppStatus ippmSub_cva_L(const Ipp32f** ppSrc, int srcRoiShift, int srcStride2, Ipp32f val,
                                           Ipp32f** ppDst, int dstRoiShift, int dstStride2,
                                           int len, int count) {
  return ippmSub_cva_32f_L(ppSrc,srcRoiShift,srcStride2,val,ppDst,dstRoiShift,dstStride2,len,count);
}
inline IppStatus ippmSub_cva_L(const Ipp64f** ppSrc, int srcRoiShift, int srcStride2, Ipp64f val,
                                           Ipp64f** ppDst, int dstRoiShift, int dstStride2,
                                           int len, int count) {
  return ippmSub_cva_64f_L(ppSrc,srcRoiShift,srcStride2,val,ppDst,dstRoiShift,dstStride2,len,count);
}
inline IppStatus ippmSub_vv(const Ipp32f*  pSrc1, int src1Stride2,
                                     const Ipp32f*  pSrc2, int src2Stride2,
                                           Ipp32f*  pDst,  int dstStride2,
                                           int len) {
  return ippmSub_vv_32f(pSrc1,src1Stride2,pSrc2,src2Stride2,pDst,dstStride2,len);
}
inline IppStatus ippmSub_vv(const Ipp64f*  pSrc1, int src1Stride2,
                                     const Ipp64f*  pSrc2, int src2Stride2,
                                           Ipp64f*  pDst,  int dstStride2,
                                           int len) {
  return ippmSub_vv_64f(pSrc1,src1Stride2,pSrc2,src2Stride2,pDst,dstStride2,len);
}
inline IppStatus ippmSub_vv_P(const Ipp32f** ppSrc1, int src1RoiShift,
                                     const Ipp32f** ppSrc2, int src2RoiShift,
                                           Ipp32f** ppDst,  int dstRoiShift,
                                           int len) {
  return ippmSub_vv_32f_P(ppSrc1,src1RoiShift,ppSrc2,src2RoiShift,ppDst,dstRoiShift,len);
}
inline IppStatus ippmSub_vv_P(const Ipp64f** ppSrc1, int src1RoiShift,
                                     const Ipp64f** ppSrc2, int src2RoiShift,
                                           Ipp64f** ppDst,  int dstRoiShift,
                                           int len) {
  return ippmSub_vv_64f_P(ppSrc1,src1RoiShift,ppSrc2,src2RoiShift,ppDst,dstRoiShift,len);
}
inline IppStatus ippmSub_vav(const Ipp32f*  pSrc1,  int src1Stride0, int src1Stride2,
                                     const Ipp32f*  pSrc2,  int src2Stride2,
                                           Ipp32f*  pDst,   int dstStride0,  int dstStride2,
                                           int len, int count) {
  return ippmSub_vav_32f(pSrc1,src1Stride0,src1Stride2,pSrc2,src2Stride2,pDst,dstStride0,dstStride2,len,count);
}
inline IppStatus ippmSub_vav(const Ipp64f*  pSrc1,  int src1Stride0, int src1Stride2,
                                     const Ipp64f*  pSrc2,  int src2Stride2,
                                           Ipp64f*  pDst,   int dstStride0,  int dstStride2,
                                           int len, int count) {
  return ippmSub_vav_64f(pSrc1,src1Stride0,src1Stride2,pSrc2,src2Stride2,pDst,dstStride0,dstStride2,len,count);
}
inline IppStatus ippmSub_vav_P(const Ipp32f** ppSrc1, int src1RoiShift, int src1Stride0,
                                     const Ipp32f** ppSrc2, int src2RoiShift,
                                           Ipp32f** ppDst,  int dstRoiShift,  int dstStride0,
                                           int len, int count) {
  return ippmSub_vav_32f_P(ppSrc1,src1RoiShift,src1Stride0,ppSrc2,src2RoiShift,ppDst,dstRoiShift,dstStride0,len,count);
}
inline IppStatus ippmSub_vav_P(const Ipp64f** ppSrc1, int src1RoiShift, int src1Stride0,
                                     const Ipp64f** ppSrc2, int src2RoiShift,
                                           Ipp64f** ppDst,  int dstRoiShift,  int dstStride0,
                                           int len, int count) {
  return ippmSub_vav_64f_P(ppSrc1,src1RoiShift,src1Stride0,ppSrc2,src2RoiShift,ppDst,dstRoiShift,dstStride0,len,count);
}
inline IppStatus ippmSub_vav_L(const Ipp32f** ppSrc1, int src1RoiShift, int src1Stride2,
                                     const Ipp32f*  pSrc2,  int src2Stride2,
                                           Ipp32f** ppDst,  int dstRoiShift,  int dstStride2,
                                           int len, int count) {
  return ippmSub_vav_32f_L(ppSrc1,src1RoiShift,src1Stride2,pSrc2,src2Stride2,ppDst,dstRoiShift,dstStride2,len,count);
}
inline IppStatus ippmSub_vav_L(const Ipp64f** ppSrc1, int src1RoiShift, int src1Stride2,
                                     const Ipp64f*  pSrc2,  int src2Stride2,
                                           Ipp64f** ppDst,  int dstRoiShift,  int dstStride2,
                                           int len, int count) {
  return ippmSub_vav_64f_L(ppSrc1,src1RoiShift,src1Stride2,pSrc2,src2Stride2,ppDst,dstRoiShift,dstStride2,len,count);
}
inline IppStatus ippmSub_vva(const Ipp32f*  pSrc1,  int src1Stride2,
                                     const Ipp32f*  pSrc2,  int src2Stride0, int src2Stride2,
                                           Ipp32f*  pDst,   int dstStride0,  int dstStride2,
                                           int len, int count) {
  return ippmSub_vva_32f(pSrc1,src1Stride2,pSrc2,src2Stride0,src2Stride2,pDst,dstStride0,dstStride2,len,count);
}
inline IppStatus ippmSub_vva(const Ipp64f*  pSrc1,  int src1Stride2,
                                     const Ipp64f*  pSrc2,  int src2Stride0, int src2Stride2,
                                           Ipp64f*  pDst,   int dstStride0,  int dstStride2,
                                           int len, int count) {
  return ippmSub_vva_64f(pSrc1,src1Stride2,pSrc2,src2Stride0,src2Stride2,pDst,dstStride0,dstStride2,len,count);
}
inline IppStatus ippmSub_vva_P(const Ipp32f** ppSrc1, int src1RoiShift,
                                     const Ipp32f** ppSrc2, int src2RoiShift, int src2Stride0,
                                           Ipp32f** ppDst,  int dstRoiShift,  int dstStride0,
                                           int len, int count) {
  return ippmSub_vva_32f_P(ppSrc1,src1RoiShift,ppSrc2,src2RoiShift,src2Stride0,ppDst,dstRoiShift,dstStride0,len,count);
}
inline IppStatus ippmSub_vva_P(const Ipp64f** ppSrc1, int src1RoiShift,
                                     const Ipp64f** ppSrc2, int src2RoiShift, int src2Stride0,
                                           Ipp64f** ppDst,  int dstRoiShift,  int dstStride0,
                                           int len, int count) {
  return ippmSub_vva_64f_P(ppSrc1,src1RoiShift,ppSrc2,src2RoiShift,src2Stride0,ppDst,dstRoiShift,dstStride0,len,count);
}
inline IppStatus ippmSub_vva_L(const Ipp32f*  pSrc1,  int src1Stride2,
                                     const Ipp32f** ppSrc2, int src2RoiShift, int src2Stride2,
                                           Ipp32f** ppDst,  int dstRoiShift,  int dstStride2,
                                           int len, int count) {
  return ippmSub_vva_32f_L(pSrc1,src1Stride2,ppSrc2,src2RoiShift,src2Stride2,ppDst,dstRoiShift,dstStride2,len,count);
}
inline IppStatus ippmSub_vva_L(const Ipp64f*  pSrc1,  int src1Stride2,
                                     const Ipp64f** ppSrc2, int src2RoiShift, int src2Stride2,
                                           Ipp64f** ppDst,  int dstRoiShift,  int dstStride2,
                                           int len, int count) {
  return ippmSub_vva_64f_L(pSrc1,src1Stride2,ppSrc2,src2RoiShift,src2Stride2,ppDst,dstRoiShift,dstStride2,len,count);
}
inline IppStatus ippmSub_vava(const Ipp32f*  pSrc1,  int src1Stride0, int src1Stride2,
                                     const Ipp32f*  pSrc2,  int src2Stride0, int src2Stride2,
                                           Ipp32f*  pDst,   int dstStride0,  int dstStride2,
                                           int len, int count) {
  return ippmSub_vava_32f(pSrc1,src1Stride0,src1Stride2,pSrc2,src2Stride0,src2Stride2,pDst,dstStride0,dstStride2,len,count);
}
inline IppStatus ippmSub_vava(const Ipp64f*  pSrc1,  int src1Stride0, int src1Stride2,
                                     const Ipp64f*  pSrc2,  int src2Stride0, int src2Stride2,
                                           Ipp64f*  pDst,   int dstStride0,  int dstStride2,
                                           int len, int count) {
  return ippmSub_vava_64f(pSrc1,src1Stride0,src1Stride2,pSrc2,src2Stride0,src2Stride2,pDst,dstStride0,dstStride2,len,count);
}
inline IppStatus ippmSub_vava_P(const Ipp32f** ppSrc1, int src1RoiShift, int src1Stride0,
                                      const Ipp32f** ppSrc2, int src2RoiShift, int src2Stride0,
                                            Ipp32f** ppDst,  int dstRoiShift,  int dstStride0,
                                            int len, int count) {
  return ippmSub_vava_32f_P(ppSrc1,src1RoiShift,src1Stride0,ppSrc2,src2RoiShift,src2Stride0,ppDst,dstRoiShift,dstStride0,len,count);
}
inline IppStatus ippmSub_vava_P(const Ipp64f** ppSrc1, int src1RoiShift, int src1Stride0,
                                      const Ipp64f** ppSrc2, int src2RoiShift, int src2Stride0,
                                            Ipp64f** ppDst,  int dstRoiShift,  int dstStride0,
                                            int len, int count) {
  return ippmSub_vava_64f_P(ppSrc1,src1RoiShift,src1Stride0,ppSrc2,src2RoiShift,src2Stride0,ppDst,dstRoiShift,dstStride0,len,count);
}
inline IppStatus ippmSub_vava_L(const Ipp32f** ppSrc1, int src1RoiShift, int src1Stride2,
                                      const Ipp32f** ppSrc2, int src2RoiShift, int src2Stride2,
                                            Ipp32f** ppDst,  int dstRoiShift,  int dstStride2,
                                            int len, int count) {
  return ippmSub_vava_32f_L(ppSrc1,src1RoiShift,src1Stride2,ppSrc2,src2RoiShift,src2Stride2,ppDst,dstRoiShift,dstStride2,len,count);
}
inline IppStatus ippmSub_vava_L(const Ipp64f** ppSrc1, int src1RoiShift, int src1Stride2,
                                      const Ipp64f** ppSrc2, int src2RoiShift, int src2Stride2,
                                            Ipp64f** ppDst,  int dstRoiShift,  int dstStride2,
                                            int len, int count) {
  return ippmSub_vava_64f_L(ppSrc1,src1RoiShift,src1Stride2,ppSrc2,src2RoiShift,src2Stride2,ppDst,dstRoiShift,dstStride2,len,count);
}
inline IppStatus ippmMul_vc(const Ipp32f*  pSrc,  int srcStride2, Ipp32f val,
                                           Ipp32f*  pDst,  int dstStride2,
                                           int len) {
  return ippmMul_vc_32f(pSrc,srcStride2,val,pDst,dstStride2,len);
}
inline IppStatus ippmMul_vc(const Ipp64f*  pSrc,  int srcStride2, Ipp64f val,
                                           Ipp64f*  pDst,  int dstStride2,
                                           int len) {
  return ippmMul_vc_64f(pSrc,srcStride2,val,pDst,dstStride2,len);
}
inline IppStatus ippmMul_vc_P(const Ipp32f** ppSrc, int srcRoiShift, Ipp32f val,
                                           Ipp32f** ppDst, int dstRoiShift,
                                           int len) {
  return ippmMul_vc_32f_P(ppSrc,srcRoiShift,val,ppDst,dstRoiShift,len);
}
inline IppStatus ippmMul_vc_P(const Ipp64f** ppSrc, int srcRoiShift, Ipp64f val,
                                           Ipp64f** ppDst, int dstRoiShift,
                                           int len) {
  return ippmMul_vc_64f_P(ppSrc,srcRoiShift,val,ppDst,dstRoiShift,len);
}
inline IppStatus ippmMul_vac(const Ipp32f*  pSrc,  int srcStride0, int srcStride2, Ipp32f val,
                                           Ipp32f*  pDst,  int dstStride0, int dstStride2,
                                           int len, int count) {
  return ippmMul_vac_32f(pSrc,srcStride0,srcStride2,val,pDst,dstStride0,dstStride2,len,count);
}
inline IppStatus ippmMul_vac(const Ipp64f*  pSrc,  int srcStride0, int srcStride2, Ipp64f val,
                                           Ipp64f*  pDst,  int dstStride0, int dstStride2,
                                           int len, int count) {
  return ippmMul_vac_64f(pSrc,srcStride0,srcStride2,val,pDst,dstStride0,dstStride2,len,count);
}
inline IppStatus ippmMul_vac_P(const Ipp32f** ppSrc, int srcRoiShift, int srcStride0, Ipp32f val,
                                           Ipp32f** ppDst, int dstRoiShift, int dstStride0,
                                           int len, int count) {
  return ippmMul_vac_32f_P(ppSrc,srcRoiShift,srcStride0,val,ppDst,dstRoiShift,dstStride0,len,count);
}
inline IppStatus ippmMul_vac_P(const Ipp64f** ppSrc, int srcRoiShift, int srcStride0, Ipp64f val,
                                           Ipp64f** ppDst, int dstRoiShift, int dstStride0,
                                           int len, int count) {
  return ippmMul_vac_64f_P(ppSrc,srcRoiShift,srcStride0,val,ppDst,dstRoiShift,dstStride0,len,count);
}
inline IppStatus ippmMul_vac_L(const Ipp32f** ppSrc, int srcRoiShift, int srcStride2, Ipp32f val,
                                           Ipp32f** ppDst, int dstRoiShift, int dstStride2,
                                           int len, int count) {
  return ippmMul_vac_32f_L(ppSrc,srcRoiShift,srcStride2,val,ppDst,dstRoiShift,dstStride2,len,count);
}
inline IppStatus ippmMul_vac_L(const Ipp64f** ppSrc, int srcRoiShift, int srcStride2, Ipp64f val,
                                           Ipp64f** ppDst, int dstRoiShift, int dstStride2,
                                           int len, int count) {
  return ippmMul_vac_64f_L(ppSrc,srcRoiShift,srcStride2,val,ppDst,dstRoiShift,dstStride2,len,count);
}
inline IppStatus ippmCrossProduct_vv(const Ipp32f*  pSrc1,  int src1Stride2,
                                               const Ipp32f*  pSrc2,  int src2Stride2,
                                                     Ipp32f*  pDst,   int dstStride2) {
  return ippmCrossProduct_vv_32f(pSrc1,src1Stride2,pSrc2,src2Stride2,pDst,dstStride2);
}
inline IppStatus ippmCrossProduct_vv(const Ipp64f*  pSrc1,  int src1Stride2,
                                               const Ipp64f*  pSrc2,  int src2Stride2,
                                                     Ipp64f*  pDst,   int dstStride2) {
  return ippmCrossProduct_vv_64f(pSrc1,src1Stride2,pSrc2,src2Stride2,pDst,dstStride2);
}
inline IppStatus ippmCrossProduct_vv_P(const Ipp32f** ppSrc1, int src1RoiShift,
                                               const Ipp32f** ppSrc2, int src2RoiShift,
                                                     Ipp32f** ppDst,  int dstRoiShift) {
  return ippmCrossProduct_vv_32f_P(ppSrc1,src1RoiShift,ppSrc2,src2RoiShift,ppDst,dstRoiShift);
}
inline IppStatus ippmCrossProduct_vv_P(const Ipp64f** ppSrc1, int src1RoiShift,
                                               const Ipp64f** ppSrc2, int src2RoiShift,
                                                     Ipp64f** ppDst,  int dstRoiShift) {
  return ippmCrossProduct_vv_64f_P(ppSrc1,src1RoiShift,ppSrc2,src2RoiShift,ppDst,dstRoiShift);
}
inline IppStatus ippmCrossProduct_vva(const Ipp32f*  pSrc1,  int src1Stride2,
                                               const Ipp32f*  pSrc2,  int src2Stride0, int src2Stride2,
                                                     Ipp32f*  pDst,   int dstStride0,  int dstStride2,
                                                     int count) {
  return ippmCrossProduct_vva_32f(pSrc1,src1Stride2,pSrc2,src2Stride0,src2Stride2,pDst,dstStride0,dstStride2,count);
}
inline IppStatus ippmCrossProduct_vva(const Ipp64f*  pSrc1,  int src1Stride2,
                                               const Ipp64f*  pSrc2,  int src2Stride0, int src2Stride2,
                                                     Ipp64f*  pDst,   int dstStride0,  int dstStride2,
                                                     int count) {
  return ippmCrossProduct_vva_64f(pSrc1,src1Stride2,pSrc2,src2Stride0,src2Stride2,pDst,dstStride0,dstStride2,count);
}
inline IppStatus ippmCrossProduct_vva_P(const Ipp32f** ppSrc1, int src1RoiShift,
                                               const Ipp32f** ppSrc2, int src2RoiShift, int src2Stride0,
                                                     Ipp32f** ppDst,  int dstRoiShift,  int dstStride0,
                                                     int count) {
  return ippmCrossProduct_vva_32f_P(ppSrc1,src1RoiShift,ppSrc2,src2RoiShift,src2Stride0,ppDst,dstRoiShift,dstStride0,count);
}
inline IppStatus ippmCrossProduct_vva_P(const Ipp64f** ppSrc1, int src1RoiShift,
                                               const Ipp64f** ppSrc2, int src2RoiShift, int src2Stride0,
                                                     Ipp64f** ppDst,  int dstRoiShift,  int dstStride0,
                                                     int count) {
  return ippmCrossProduct_vva_64f_P(ppSrc1,src1RoiShift,ppSrc2,src2RoiShift,src2Stride0,ppDst,dstRoiShift,dstStride0,count);
}
inline IppStatus ippmCrossProduct_vva_L(const Ipp32f*  pSrc1,  int src1Stride2,
                                               const Ipp32f** ppSrc2, int src2RoiShift, int src2Stride2,
                                                     Ipp32f** ppDst,  int dstRoiShift,  int dstStride2,
                                                     int count) {
  return ippmCrossProduct_vva_32f_L(pSrc1,src1Stride2,ppSrc2,src2RoiShift,src2Stride2,ppDst,dstRoiShift,dstStride2,count);
}
inline IppStatus ippmCrossProduct_vva_L(const Ipp64f*  pSrc1,  int src1Stride2,
                                               const Ipp64f** ppSrc2, int src2RoiShift, int src2Stride2,
                                                     Ipp64f** ppDst,  int dstRoiShift,  int dstStride2,
                                                     int count) {
  return ippmCrossProduct_vva_64f_L(pSrc1,src1Stride2,ppSrc2,src2RoiShift,src2Stride2,ppDst,dstRoiShift,dstStride2,count);
}
inline IppStatus ippmCrossProduct_vav(const Ipp32f*  pSrc1,  int src1Stride0, int src1Stride2,
                                               const Ipp32f*  pSrc2,  int src2Stride2,
                                                     Ipp32f*  pDst,   int dstStride0, int dstStride2,
                                                     int count) {
  return ippmCrossProduct_vav_32f(pSrc1,src1Stride0,src1Stride2,pSrc2,src2Stride2,pDst,dstStride0,dstStride2,count);
}
inline IppStatus ippmCrossProduct_vav(const Ipp64f*  pSrc1,  int src1Stride0, int src1Stride2,
                                               const Ipp64f*  pSrc2,  int src2Stride2,
                                                     Ipp64f*  pDst,   int dstStride0, int dstStride2,
                                                     int count) {
  return ippmCrossProduct_vav_64f(pSrc1,src1Stride0,src1Stride2,pSrc2,src2Stride2,pDst,dstStride0,dstStride2,count);
}
inline IppStatus ippmCrossProduct_vav_P(const Ipp32f** ppSrc1, int src1RoiShift, int src1Stride0,
                                               const Ipp32f** ppSrc2, int src2RoiShift,
                                                     Ipp32f** ppDst,  int dstRoiShift, int dstStride0,
                                                     int count) {
  return ippmCrossProduct_vav_32f_P(ppSrc1,src1RoiShift,src1Stride0,ppSrc2,src2RoiShift,ppDst,dstRoiShift,dstStride0,count);
}
inline IppStatus ippmCrossProduct_vav_P(const Ipp64f** ppSrc1, int src1RoiShift, int src1Stride0,
                                               const Ipp64f** ppSrc2, int src2RoiShift,
                                                     Ipp64f** ppDst,  int dstRoiShift, int dstStride0,
                                                     int count) {
  return ippmCrossProduct_vav_64f_P(ppSrc1,src1RoiShift,src1Stride0,ppSrc2,src2RoiShift,ppDst,dstRoiShift,dstStride0,count);
}
inline IppStatus ippmCrossProduct_vav_L(const Ipp32f** ppSrc1, int src1RoiShift, int src1Stride2,
                                               const Ipp32f*  pSrc2,  int src2Stride2,
                                                     Ipp32f** ppDst,  int dstRoiShift, int dstStride2,
                                                     int count) {
  return ippmCrossProduct_vav_32f_L(ppSrc1,src1RoiShift,src1Stride2,pSrc2,src2Stride2,ppDst,dstRoiShift,dstStride2,count);
}
inline IppStatus ippmCrossProduct_vav_L(const Ipp64f** ppSrc1, int src1RoiShift, int src1Stride2,
                                               const Ipp64f*  pSrc2,  int src2Stride2,
                                                     Ipp64f** ppDst,  int dstRoiShift, int dstStride2,
                                                     int count) {
  return ippmCrossProduct_vav_64f_L(ppSrc1,src1RoiShift,src1Stride2,pSrc2,src2Stride2,ppDst,dstRoiShift,dstStride2,count);
}
inline IppStatus ippmCrossProduct_vava(const Ipp32f* pSrc1, int src1Stride0, int src1Stride2,
                                               const Ipp32f* pSrc2, int src2Stride0, int src2Stride2,
                                                     Ipp32f* pDst,  int dstStride0,  int dstStride2,
                                                     int count) {
  return ippmCrossProduct_vava_32f(pSrc1,src1Stride0,src1Stride2,pSrc2,src2Stride0,src2Stride2,pDst,dstStride0,dstStride2,count);
}
inline IppStatus ippmCrossProduct_vava(const Ipp64f* pSrc1, int src1Stride0, int src1Stride2,
                                               const Ipp64f* pSrc2, int src2Stride0, int src2Stride2,
                                                     Ipp64f* pDst,  int dstStride0,  int dstStride2,
                                                     int count) {
  return ippmCrossProduct_vava_64f(pSrc1,src1Stride0,src1Stride2,pSrc2,src2Stride0,src2Stride2,pDst,dstStride0,dstStride2,count);
}
inline IppStatus ippmCrossProduct_vava_P(const Ipp32f** ppSrc1, int src1RoiShift, int src1Stride0,
                                               const Ipp32f** ppSrc2, int src2RoiShift, int src2Stride0,
                                                     Ipp32f** ppDst,  int dstRoiShift,  int dstStride0,
                                                     int count) {
  return ippmCrossProduct_vava_32f_P(ppSrc1,src1RoiShift,src1Stride0,ppSrc2,src2RoiShift,src2Stride0,ppDst,dstRoiShift,dstStride0,count);
}
inline IppStatus ippmCrossProduct_vava_P(const Ipp64f** ppSrc1, int src1RoiShift, int src1Stride0,
                                               const Ipp64f** ppSrc2, int src2RoiShift, int src2Stride0,
                                                     Ipp64f** ppDst,  int dstRoiShift,  int dstStride0,
                                                     int count) {
  return ippmCrossProduct_vava_64f_P(ppSrc1,src1RoiShift,src1Stride0,ppSrc2,src2RoiShift,src2Stride0,ppDst,dstRoiShift,dstStride0,count);
}
inline IppStatus ippmCrossProduct_vava_L(const Ipp32f** ppSrc1, int src1RoiShift, int src1Stride2,
                                               const Ipp32f** ppSrc2, int src2RoiShift, int src2Stride2,
                                                     Ipp32f** ppDst,  int dstRoiShift,  int dstStride2,
                                                     int count) {
  return ippmCrossProduct_vava_32f_L(ppSrc1,src1RoiShift,src1Stride2,ppSrc2,src2RoiShift,src2Stride2,ppDst,dstRoiShift,dstStride2,count);
}
inline IppStatus ippmCrossProduct_vava_L(const Ipp64f** ppSrc1, int src1RoiShift, int src1Stride2,
                                               const Ipp64f** ppSrc2, int src2RoiShift, int src2Stride2,
                                                     Ipp64f** ppDst,  int dstRoiShift,  int dstStride2,
                                                     int count) {
  return ippmCrossProduct_vava_64f_L(ppSrc1,src1RoiShift,src1Stride2,ppSrc2,src2RoiShift,src2Stride2,ppDst,dstRoiShift,dstStride2,count);
}
inline IppStatus ippmDotProduct_vv(const Ipp32f*  pSrc1,  int src1Stride2,
                                             const Ipp32f*  pSrc2,  int src2Stride2,
                                                   Ipp32f*  pDst,   int len) {
  return ippmDotProduct_vv_32f(pSrc1,src1Stride2,pSrc2,src2Stride2,pDst,len);
}
inline IppStatus ippmDotProduct_vv(const Ipp64f*  pSrc1,  int src1Stride2,
                                             const Ipp64f*  pSrc2,  int src2Stride2,
                                                   Ipp64f*  pDst,   int len) {
  return ippmDotProduct_vv_64f(pSrc1,src1Stride2,pSrc2,src2Stride2,pDst,len);
}
inline IppStatus ippmDotProduct_vv_P(const Ipp32f** ppSrc1, int src1RoiShift,
                                             const Ipp32f** ppSrc2, int src2RoiShift,
                                                   Ipp32f*  pDst,   int len) {
  return ippmDotProduct_vv_32f_P(ppSrc1,src1RoiShift,ppSrc2,src2RoiShift,pDst,len);
}
inline IppStatus ippmDotProduct_vv_P(const Ipp64f** ppSrc1, int src1RoiShift,
                                             const Ipp64f** ppSrc2, int src2RoiShift,
                                                   Ipp64f*  pDst,  int len) {
  return ippmDotProduct_vv_64f_P(ppSrc1,src1RoiShift,ppSrc2,src2RoiShift,pDst,len);
}
inline IppStatus ippmDotProduct_vav(const Ipp32f*  pSrc1,  int src1Stride0, int src1Stride2,
                                             const Ipp32f*  pSrc2,  int src2Stride2,
                                                   Ipp32f*  pDst,   int len, int count) {
  return ippmDotProduct_vav_32f(pSrc1,src1Stride0,src1Stride2,pSrc2,src2Stride2,pDst,len,count);
}
inline IppStatus ippmDotProduct_vav(const Ipp64f*  pSrc1,  int src1Stride0, int src1Stride2,
                                             const Ipp64f*  pSrc2,  int src2Stride2,
                                                   Ipp64f*  pDst,   int len, int count) {
  return ippmDotProduct_vav_64f(pSrc1,src1Stride0,src1Stride2,pSrc2,src2Stride2,pDst,len,count);
}
inline IppStatus ippmDotProduct_vav_P(const Ipp32f** ppSrc1, int src1RoiShift, int src1Stride0,
                                             const Ipp32f** ppSrc2, int src2RoiShift,
                                                   Ipp32f*  pDst,   int len, int count) {
  return ippmDotProduct_vav_32f_P(ppSrc1,src1RoiShift,src1Stride0,ppSrc2,src2RoiShift,pDst,len,count);
}
inline IppStatus ippmDotProduct_vav_P(const Ipp64f** ppSrc1, int src1RoiShift, int src1Stride0,
                                             const Ipp64f** ppSrc2, int src2RoiShift,
                                                   Ipp64f*  pDst,   int len, int count) {
  return ippmDotProduct_vav_64f_P(ppSrc1,src1RoiShift,src1Stride0,ppSrc2,src2RoiShift,pDst,len,count);
}
inline IppStatus ippmDotProduct_vav_L(const Ipp32f** ppSrc1, int src1RoiShift, int src1Stride2,
                                             const Ipp32f*  pSrc2,  int src2Stride2,
                                                   Ipp32f*  pDst,   int len, int count) {
  return ippmDotProduct_vav_32f_L(ppSrc1,src1RoiShift,src1Stride2,pSrc2,src2Stride2,pDst,len,count);
}
inline IppStatus ippmDotProduct_vav_L(const Ipp64f** ppSrc1, int src1RoiShift, int src1Stride2,
                                             const Ipp64f*  pSrc2,  int src2Stride2,
                                                   Ipp64f*  pDst,  int len, int count) {
  return ippmDotProduct_vav_64f_L(ppSrc1,src1RoiShift,src1Stride2,pSrc2,src2Stride2,pDst,len,count);
}
inline IppStatus ippmDotProduct_vava(const Ipp32f* pSrc1, int src1Stride0, int src1Stride2,
                                             const Ipp32f* pSrc2, int src2Stride0, int src2Stride2,
                                                   Ipp32f* pDst,  int len, int count) {
  return ippmDotProduct_vava_32f(pSrc1,src1Stride0,src1Stride2,pSrc2,src2Stride0,src2Stride2,pDst,len,count);
}
inline IppStatus ippmDotProduct_vava(const Ipp64f* pSrc1, int src1Stride0, int src1Stride2,
                                             const Ipp64f* pSrc2, int src2Stride0, int src2Stride2,
                                                   Ipp64f* pDst,  int len, int count) {
  return ippmDotProduct_vava_64f(pSrc1,src1Stride0,src1Stride2,pSrc2,src2Stride0,src2Stride2,pDst,len,count);
}
inline IppStatus ippmDotProduct_vava_P(const Ipp32f** ppSrc1, int src1RoiShift, int src1Stride0,
                                             const Ipp32f** ppSrc2, int src2RoiShift, int src2Stride0,
                                                   Ipp32f*  pDst,   int len, int count) {
  return ippmDotProduct_vava_32f_P(ppSrc1,src1RoiShift,src1Stride0,ppSrc2,src2RoiShift,src2Stride0,pDst,len,count);
}
inline IppStatus ippmDotProduct_vava_P(const Ipp64f** ppSrc1, int src1RoiShift, int src1Stride0,
                                             const Ipp64f** ppSrc2, int src2RoiShift, int src2Stride0,
                                                   Ipp64f*  pDst,   int len, int count) {
  return ippmDotProduct_vava_64f_P(ppSrc1,src1RoiShift,src1Stride0,ppSrc2,src2RoiShift,src2Stride0,pDst,len,count);
}
inline IppStatus ippmDotProduct_vava_L(const Ipp32f** ppSrc1, int src1RoiShift, int src1Stride2,
                                             const Ipp32f** ppSrc2, int src2RoiShift, int src2Stride2,
                                                   Ipp32f*  pDst,   int len, int count) {
  return ippmDotProduct_vava_32f_L(ppSrc1,src1RoiShift,src1Stride2,ppSrc2,src2RoiShift,src2Stride2,pDst,len,count);
}
inline IppStatus ippmDotProduct_vava_L(const Ipp64f** ppSrc1, int src1RoiShift, int src1Stride2,
                                             const Ipp64f** ppSrc2, int src2RoiShift, int src2Stride2,
                                                   Ipp64f*  pDst,   int len, int count) {
  return ippmDotProduct_vava_64f_L(ppSrc1,src1RoiShift,src1Stride2,ppSrc2,src2RoiShift,src2Stride2,pDst,len,count);
}
inline IppStatus ippmL2Norm_v(const Ipp32f*  pSrc, int srcStride2,
                                             Ipp32f*  pDst, int len) {
  return ippmL2Norm_v_32f(pSrc,srcStride2,pDst,len);
}
inline IppStatus ippmL2Norm_v(const Ipp64f*  pSrc, int srcStride2,
                                             Ipp64f*  pDst, int len) {
  return ippmL2Norm_v_64f(pSrc,srcStride2,pDst,len);
}
inline IppStatus ippmL2Norm_v_P(const Ipp32f** ppSrc, int srcRoiShift,
                                             Ipp32f*  pDst,  int len) {
  return ippmL2Norm_v_32f_P(ppSrc,srcRoiShift,pDst,len);
}
inline IppStatus ippmL2Norm_v_P(const Ipp64f** ppSrc, int srcRoiShift,
                                             Ipp64f*  pDst,  int len) {
  return ippmL2Norm_v_64f_P(ppSrc,srcRoiShift,pDst,len);
}
inline IppStatus ippmL2Norm_va(const Ipp32f*  pSrc,  int srcStride0, int srcStride2,
                                             Ipp32f*  pDst,  int len, int count) {
  return ippmL2Norm_va_32f(pSrc,srcStride0,srcStride2,pDst,len,count);
}
inline IppStatus ippmL2Norm_va(const Ipp64f*  pSrc,  int srcStride0, int srcStride2,
                                             Ipp64f*  pDst,  int len, int count) {
  return ippmL2Norm_va_64f(pSrc,srcStride0,srcStride2,pDst,len,count);
}
inline IppStatus ippmL2Norm_va_P(const Ipp32f** ppSrc, int srcRoiShift, int srcStride0,
                                             Ipp32f*  pDst,  int len, int count) {
  return ippmL2Norm_va_32f_P(ppSrc,srcRoiShift,srcStride0,pDst,len,count);
}
inline IppStatus ippmL2Norm_va_P(const Ipp64f** ppSrc, int srcRoiShift, int srcStride0,
                                             Ipp64f*  pDst,  int len, int count) {
  return ippmL2Norm_va_64f_P(ppSrc,srcRoiShift,srcStride0,pDst,len,count);
}
inline IppStatus ippmL2Norm_va_L(const Ipp32f** ppSrc, int srcRoiShift, int srcStride2,
                                             Ipp32f*  pDst,  int len, int count) {
  return ippmL2Norm_va_32f_L(ppSrc,srcRoiShift,srcStride2,pDst,len,count);
}
inline IppStatus ippmL2Norm_va_L(const Ipp64f** ppSrc, int srcRoiShift, int srcStride2,
                                             Ipp64f*  pDst,  int len, int count) {
  return ippmL2Norm_va_64f_L(ppSrc,srcRoiShift,srcStride2,pDst,len,count);
}
inline IppStatus ippmLComb_vv(const Ipp32f*  pSrc1,  int src1Stride2, Ipp32f scale1,
                                        const Ipp32f*  pSrc2,  int src2Stride2, Ipp32f scale2,
                                              Ipp32f*  pDst,   int dstStride2,
                                              int len) {
  return ippmLComb_vv_32f(pSrc1,src1Stride2,scale1,pSrc2,src2Stride2,scale2,pDst,dstStride2,len);
}
inline IppStatus ippmLComb_vv(const Ipp64f*  pSrc1,  int src1Stride2, Ipp64f scale1,
                                        const Ipp64f*  pSrc2,  int src2Stride2, Ipp64f scale2,
                                              Ipp64f*  pDst,   int dstStride2,
                                              int len) {
  return ippmLComb_vv_64f(pSrc1,src1Stride2,scale1,pSrc2,src2Stride2,scale2,pDst,dstStride2,len);
}
inline IppStatus ippmLComb_vv_P(const Ipp32f** ppSrc1, int src1RoiShift, Ipp32f scale1,
                                        const Ipp32f** ppSrc2, int src2RoiShift, Ipp32f scale2,
                                              Ipp32f** ppDst,  int dstRoiShift,
                                              int len) {
  return ippmLComb_vv_32f_P(ppSrc1,src1RoiShift,scale1,ppSrc2,src2RoiShift,scale2,ppDst,dstRoiShift,len);
}
inline IppStatus ippmLComb_vv_P(const Ipp64f** ppSrc1, int src1RoiShift, Ipp64f scale1,
                                        const Ipp64f** ppSrc2, int src2RoiShift, Ipp64f scale2,
                                              Ipp64f** ppDst,  int dstRoiShift,
                                              int len) {
  return ippmLComb_vv_64f_P(ppSrc1,src1RoiShift,scale1,ppSrc2,src2RoiShift,scale2,ppDst,dstRoiShift,len);
}
inline IppStatus ippmLComb_vav(const Ipp32f*  pSrc1,  int src1Stride0, int src1Stride2, Ipp32f scale1,
                                        const Ipp32f*  pSrc2,  int src2Stride2, Ipp32f scale2,
                                              Ipp32f*  pDst,   int dstStride0,  int dstStride2,
                                              int len, int count) {
  return ippmLComb_vav_32f(pSrc1,src1Stride0,src1Stride2,scale1,pSrc2,src2Stride2,scale2,pDst,dstStride0,dstStride2,len,count);
}
inline IppStatus ippmLComb_vav(const Ipp64f*  pSrc1,  int src1Stride0, int src1Stride2, Ipp64f scale1,
                                        const Ipp64f*  pSrc2,  int src2Stride2, Ipp64f scale2,
                                              Ipp64f*  pDst,   int dstStride0,  int dstStride2,
                                              int len, int count) {
  return ippmLComb_vav_64f(pSrc1,src1Stride0,src1Stride2,scale1,pSrc2,src2Stride2,scale2,pDst,dstStride0,dstStride2,len,count);
}
inline IppStatus ippmLComb_vav_P(const Ipp32f** ppSrc1, int src1RoiShift, int src1Stride0, Ipp32f scale1,
                                        const Ipp32f** ppSrc2, int src2RoiShift, Ipp32f scale2,
                                              Ipp32f** ppDst,  int dstRoiShift,  int dstStride0,
                                              int len, int count) {
  return ippmLComb_vav_32f_P(ppSrc1,src1RoiShift,src1Stride0,scale1,ppSrc2,src2RoiShift,scale2,ppDst,dstRoiShift,dstStride0,len,count);
}
inline IppStatus ippmLComb_vav_P(const Ipp64f** ppSrc1, int src1RoiShift, int src1Stride0, Ipp64f scale1,
                                        const Ipp64f** ppSrc2, int src2RoiShift, Ipp64f scale2,
                                              Ipp64f** ppDst,  int dstRoiShift,  int dstStride0,
                                              int len, int count) {
  return ippmLComb_vav_64f_P(ppSrc1,src1RoiShift,src1Stride0,scale1,ppSrc2,src2RoiShift,scale2,ppDst,dstRoiShift,dstStride0,len,count);
}
inline IppStatus ippmLComb_vav_L(const Ipp32f** ppSrc1, int src1RoiShift, int src1Stride2, Ipp32f scale1,
                                        const Ipp32f*  pSrc2,  int src2Stride2,  Ipp32f scale2,
                                              Ipp32f** ppDst,  int dstRoiShift,  int dstStride2,
                                              int len, int count) {
  return ippmLComb_vav_32f_L(ppSrc1,src1RoiShift,src1Stride2,scale1,pSrc2,src2Stride2,scale2,ppDst,dstRoiShift,dstStride2,len,count);
}
inline IppStatus ippmLComb_vav_L(const Ipp64f** ppSrc1, int src1RoiShift, int src1Stride2, Ipp64f scale1,
                                        const Ipp64f*  pSrc2,  int src2Stride2,  Ipp64f scale2,
                                              Ipp64f** ppDst,  int dstRoiShift,  int dstStride2,
                                              int len, int count) {
  return ippmLComb_vav_64f_L(ppSrc1,src1RoiShift,src1Stride2,scale1,pSrc2,src2Stride2,scale2,ppDst,dstRoiShift,dstStride2,len,count);
}
inline IppStatus ippmLComb_vava(const Ipp32f*  pSrc1,  int src1Stride0, int src1Stride2, Ipp32f scale1,
                                        const Ipp32f*  pSrc2,  int src2Stride0, int src2Stride2, Ipp32f scale2,
                                              Ipp32f*  pDst,   int dstStride0,  int dstStride2,
                                              int len, int count) {
  return ippmLComb_vava_32f(pSrc1,src1Stride0,src1Stride2,scale1,pSrc2,src2Stride0,src2Stride2,scale2,pDst,dstStride0,dstStride2,len,count);
}
inline IppStatus ippmLComb_vava(const Ipp64f*  pSrc1,  int src1Stride0, int src1Stride2, Ipp64f scale1,
                                        const Ipp64f*  pSrc2,  int src2Stride0, int src2Stride2, Ipp64f scale2,
                                              Ipp64f*  pDst,   int dstStride0,  int dstStride2,
                                              int len, int count) {
  return ippmLComb_vava_64f(pSrc1,src1Stride0,src1Stride2,scale1,pSrc2,src2Stride0,src2Stride2,scale2,pDst,dstStride0,dstStride2,len,count);
}
inline IppStatus ippmLComb_vava_P(const Ipp32f** ppSrc1, int src1RoiShift, int src1Stride0, Ipp32f scale1,
                                        const Ipp32f** ppSrc2, int src2RoiShift, int src2Stride0, Ipp32f scale2,
                                              Ipp32f** ppDst,  int dstRoiShift,  int dstStride0,
                                              int len, int count) {
  return ippmLComb_vava_32f_P(ppSrc1,src1RoiShift,src1Stride0,scale1,ppSrc2,src2RoiShift,src2Stride0,scale2,ppDst,dstRoiShift,dstStride0,len,count);
}
inline IppStatus ippmLComb_vava_P(const Ipp64f** ppSrc1, int src1RoiShift, int src1Stride0, Ipp64f scale1,
                                        const Ipp64f** ppSrc2, int src2RoiShift, int src2Stride0, Ipp64f scale2,
                                              Ipp64f** ppDst,  int dstRoiShift,  int dstStride0,
                                              int len, int count) {
  return ippmLComb_vava_64f_P(ppSrc1,src1RoiShift,src1Stride0,scale1,ppSrc2,src2RoiShift,src2Stride0,scale2,ppDst,dstRoiShift,dstStride0,len,count);
}
inline IppStatus ippmLComb_vava_L(const Ipp32f** ppSrc1, int src1RoiShift, int src1Stride2, Ipp32f scale1,
                                        const Ipp32f** ppSrc2, int src2RoiShift, int src2Stride2, Ipp32f scale2,
                                              Ipp32f** ppDst,  int dstRoiShift,  int dstStride2,
                                              int len, int count) {
  return ippmLComb_vava_32f_L(ppSrc1,src1RoiShift,src1Stride2,scale1,ppSrc2,src2RoiShift,src2Stride2,scale2,ppDst,dstRoiShift,dstStride2,len,count);
}
inline IppStatus ippmLComb_vava_L(const Ipp64f** ppSrc1, int src1RoiShift, int src1Stride2, Ipp64f scale1,
                                        const Ipp64f** ppSrc2, int src2RoiShift, int src2Stride2, Ipp64f scale2,
                                              Ipp64f** ppDst,  int dstRoiShift,  int dstStride2,
                                              int len, int count) {
  return ippmLComb_vava_64f_L(ppSrc1,src1RoiShift,src1Stride2,scale1,ppSrc2,src2RoiShift,src2Stride2,scale2,ppDst,dstRoiShift,dstStride2,len,count);
}
inline IppStatus ippmTranspose_m(const Ipp32f* pSrc, int srcStride1, int srcStride2,
                                                int width, int height,
                                                Ipp32f* pDst, int dstStride1, int dstStride2) {
  return ippmTranspose_m_32f(pSrc,srcStride1,srcStride2,width,height,pDst,dstStride1,dstStride2);
}
inline IppStatus ippmTranspose_m(const Ipp64f* pSrc, int srcStride1, int srcStride2,
                                                int width, int height,
                                                Ipp64f* pDst, int dstStride1, int dstStride2) {
  return ippmTranspose_m_64f(pSrc,srcStride1,srcStride2,width,height,pDst,dstStride1,dstStride2);
}
inline IppStatus ippmTranspose_m_P(const Ipp32f** ppSrc, int srcRoiShift,
                                                int width, int height,
                                                Ipp32f** ppDst, int dstRoiShift) {
  return ippmTranspose_m_32f_P(ppSrc,srcRoiShift,width,height,ppDst,dstRoiShift);
}
inline IppStatus ippmTranspose_m_P(const Ipp64f** ppSrc, int srcRoiShift,
                                                int width, int height,
                                                Ipp64f** ppDst, int dstRoiShift) {
  return ippmTranspose_m_64f_P(ppSrc,srcRoiShift,width,height,ppDst,dstRoiShift);
}
inline IppStatus ippmTranspose_ma(const Ipp32f* pSrc, int srcStride0, int srcStride1, int srcStride2,
                                                int width, int height,
                                                Ipp32f* pDst, int dstStride0, int dstStride1, int dstStride2,
                                                int count) {
  return ippmTranspose_ma_32f(pSrc,srcStride0,srcStride1,srcStride2,width,height,pDst,dstStride0,dstStride1,dstStride2,count);
}
inline IppStatus ippmTranspose_ma(const Ipp64f* pSrc, int srcStride0, int srcStride1, int srcStride2,
                                                int width, int height,
                                                Ipp64f* pDst, int dstStride0, int dstStride1, int dstStride2,
                                                int count) {
  return ippmTranspose_ma_64f(pSrc,srcStride0,srcStride1,srcStride2,width,height,pDst,dstStride0,dstStride1,dstStride2,count);
}
inline IppStatus ippmTranspose_ma_P(const Ipp32f** ppSrc, int srcRoiShift, int srcStride0,
                                                int width, int height,
                                                Ipp32f** ppDst, int dstRoiShift, int dstStride0,
                                                int count) {
  return ippmTranspose_ma_32f_P(ppSrc,srcRoiShift,srcStride0,width,height,ppDst,dstRoiShift,dstStride0,count);
}
inline IppStatus ippmTranspose_ma_P(const Ipp64f** ppSrc, int srcRoiShift, int srcStride0,
                                                int width, int height,
                                                Ipp64f** ppDst, int dstRoiShift, int dstStride0,
                                                int count) {
  return ippmTranspose_ma_64f_P(ppSrc,srcRoiShift,srcStride0,width,height,ppDst,dstRoiShift,dstStride0,count);
}
inline IppStatus ippmTranspose_ma_L(const Ipp32f** ppSrc, int srcRoiShift, int srcStride1, int srcStride2,
                                                int width, int height,
                                                Ipp32f** ppDst, int dstRoiShift, int dstStride1, int dstStride2,
                                                int count) {
  return ippmTranspose_ma_32f_L(ppSrc,srcRoiShift,srcStride1,srcStride2,width,height,ppDst,dstRoiShift,dstStride1,dstStride2,count);
}
inline IppStatus ippmTranspose_ma_L(const Ipp64f** ppSrc, int srcRoiShift, int srcStride1, int srcStride2,
                                                int width, int height,
                                                Ipp64f** ppDst, int dstRoiShift, int dstStride1, int dstStride2,
                                                int count) {
  return ippmTranspose_ma_64f_L(ppSrc,srcRoiShift,srcStride1,srcStride2,width,height,ppDst,dstRoiShift,dstStride1,dstStride2,count);
}
inline IppStatus ippmInvert_m(const Ipp32f* pSrc, int srcStride1, int srcStride2,
                                             Ipp32f* pBuffer,
                                             Ipp32f* pDst, int dstStride1, int dstStride2,
                                             int widthHeight) {
  return ippmInvert_m_32f(pSrc,srcStride1,srcStride2,pBuffer,pDst,dstStride1,dstStride2,widthHeight);
}
inline IppStatus ippmInvert_m(const Ipp64f* pSrc, int srcStride1, int srcStride2,
                                             Ipp64f* pBuffer,
                                             Ipp64f* pDst, int dstStride1, int dstStride2,
                                             int widthHeight) {
  return ippmInvert_m_64f(pSrc,srcStride1,srcStride2,pBuffer,pDst,dstStride1,dstStride2,widthHeight);
}
inline IppStatus ippmInvert_m_P(const Ipp32f** ppSrc, int srcRoiShift,
                                             Ipp32f*  pBuffer,
                                             Ipp32f** ppDst, int dstRoiShift,
                                             int widthHeight ) {
  return ippmInvert_m_32f_P(ppSrc,srcRoiShift,pBuffer,ppDst,dstRoiShift,widthHeight);
}
inline IppStatus ippmInvert_m_P(const Ipp64f** ppSrc, int srcRoiShift,
                                             Ipp64f*  pBuffer,
                                             Ipp64f** ppDst, int dstRoiShift,
                                             int widthHeight ) {
  return ippmInvert_m_64f_P(ppSrc,srcRoiShift,pBuffer,ppDst,dstRoiShift,widthHeight);
}
inline IppStatus ippmInvert_ma(const Ipp32f* pSrc, int srcStride0, int srcStride1, int srcStride2,
                                             Ipp32f* pBuffer,
                                             Ipp32f* pDst, int dstStride0, int dstStride1, int dstStride2,
                                             int widthHeight, int count) {
  return ippmInvert_ma_32f(pSrc,srcStride0,srcStride1,srcStride2,pBuffer,pDst,dstStride0,dstStride1,dstStride2,widthHeight,count);
}
inline IppStatus ippmInvert_ma(const Ipp64f* pSrc, int srcStride0, int srcStride1, int srcStride2,
                                             Ipp64f* pBuffer,
                                             Ipp64f* pDst, int dstStride0, int dstStride1, int dstStride2,
                                             int widthHeight, int count) {
  return ippmInvert_ma_64f(pSrc,srcStride0,srcStride1,srcStride2,pBuffer,pDst,dstStride0,dstStride1,dstStride2,widthHeight,count);
}
inline IppStatus ippmInvert_ma_P(const Ipp32f** ppSrc, int srcRoiShift, int srcStride0,
                                             Ipp32f* pBuffer,
                                             Ipp32f** ppDst, int dstRoiShift, int dstStride0,
                                             int widthHeight, int count) {
  return ippmInvert_ma_32f_P(ppSrc,srcRoiShift,srcStride0,pBuffer,ppDst,dstRoiShift,dstStride0,widthHeight,count);
}
inline IppStatus ippmInvert_ma_P(const Ipp64f** ppSrc, int srcRoiShift, int srcStride0,
                                             Ipp64f* pBuffer,
                                             Ipp64f** ppDst, int dstRoiShift, int dstStride0,
                                             int widthHeight, int count) {
  return ippmInvert_ma_64f_P(ppSrc,srcRoiShift,srcStride0,pBuffer,ppDst,dstRoiShift,dstStride0,widthHeight,count);
}
inline IppStatus ippmInvert_ma_L(const Ipp32f** ppSrc, int srcRoiShift, int srcStride1, int srcStride2,
                                             Ipp32f*  pBuffer,
                                             Ipp32f** ppDst, int dstRoiShift, int dstStride1, int dstStride2,
                                             int widthHeight, int count) {
  return ippmInvert_ma_32f_L(ppSrc,srcRoiShift,srcStride1,srcStride2,pBuffer,ppDst,dstRoiShift,dstStride1,dstStride2,widthHeight,count);
}
inline IppStatus ippmInvert_ma_L(const Ipp64f** ppSrc, int srcRoiShift, int srcStride1, int srcStride2,
                                             Ipp64f*  pBuffer,
                                             Ipp64f** ppDst, int dstRoiShift, int dstStride1, int dstStride2,
                                             int widthHeight, int count) {
  return ippmInvert_ma_64f_L(ppSrc,srcRoiShift,srcStride1,srcStride2,pBuffer,ppDst,dstRoiShift,dstStride1,dstStride2,widthHeight,count);
}
inline IppStatus ippmFrobNorm_m(const Ipp32f* pSrc, int srcStride1, int srcStride2,
                                               int width, int height,
                                               Ipp32f* pDst) {
  return ippmFrobNorm_m_32f(pSrc,srcStride1,srcStride2,width,height,pDst);
}
inline IppStatus ippmFrobNorm_m(const Ipp64f* pSrc, int srcStride1, int srcStride2,
                                               int width, int height,
                                               Ipp64f* pDst) {
  return ippmFrobNorm_m_64f(pSrc,srcStride1,srcStride2,width,height,pDst);
}
inline IppStatus ippmFrobNorm_m_P(const Ipp32f** ppSrc, int srcRoiShift,
                                               int width, int height,
                                               Ipp32f* pDst) {
  return ippmFrobNorm_m_32f_P(ppSrc,srcRoiShift,width,height,pDst);
}
inline IppStatus ippmFrobNorm_m_P(const Ipp64f** ppSrc, int srcRoiShift,
                                               int width, int height,
                                               Ipp64f* pDst) {
  return ippmFrobNorm_m_64f_P(ppSrc,srcRoiShift,width,height,pDst);
}
inline IppStatus ippmFrobNorm_ma(const Ipp32f* pSrc, int srcStride0, int srcStride1, int srcStride2,
                                               int width, int height,
                                               Ipp32f* pDst,
                                               int count) {
  return ippmFrobNorm_ma_32f(pSrc,srcStride0,srcStride1,srcStride2,width,height,pDst,count);
}
inline IppStatus ippmFrobNorm_ma(const Ipp64f* pSrc, int srcStride0, int srcStride1, int srcStride2,
                                               int width, int height,
                                               Ipp64f* pDst,
                                               int count) {
  return ippmFrobNorm_ma_64f(pSrc,srcStride0,srcStride1,srcStride2,width,height,pDst,count);
}
inline IppStatus ippmFrobNorm_ma_P(const Ipp32f** ppSrc, int srcRoiShift, int srcStride0,
                                               int width, int height,
                                               Ipp32f* pDst,
                                               int count) {
  return ippmFrobNorm_ma_32f_P(ppSrc,srcRoiShift,srcStride0,width,height,pDst,count);
}
inline IppStatus ippmFrobNorm_ma_P(const Ipp64f** ppSrc, int srcRoiShift, int srcStride0,
                                               int width, int height,
                                               Ipp64f* pDst,
                                               int count) {
  return ippmFrobNorm_ma_64f_P(ppSrc,srcRoiShift,srcStride0,width,height,pDst,count);
}
inline IppStatus ippmFrobNorm_ma_L(const Ipp32f** ppSrc, int srcRoiShift, int srcStride1, int srcStride2,
                                               int width, int height,
                                               Ipp32f* pDst,
                                               int count) {
  return ippmFrobNorm_ma_32f_L(ppSrc,srcRoiShift,srcStride1,srcStride2,width,height,pDst,count);
}
inline IppStatus ippmFrobNorm_ma_L(const Ipp64f** ppSrc, int srcRoiShift, int srcStride1, int srcStride2,
                                               int width, int height,
                                               Ipp64f* pDst,
                                               int count) {
  return ippmFrobNorm_ma_64f_L(ppSrc,srcRoiShift,srcStride1,srcStride2,width,height,pDst,count);
}
inline IppStatus ippmDet_m(const Ipp32f*  pSrc, int srcStride1, int srcStride2,
                                          int widthHeight, Ipp32f* pBuffer,
                                          Ipp32f*  pDst) {
  return ippmDet_m_32f(pSrc,srcStride1,srcStride2,widthHeight,pBuffer,pDst);
}
inline IppStatus ippmDet_m(const Ipp64f*  pSrc, int srcStride1, int srcStride2,
                                          int widthHeight, Ipp64f* pBuffer,
                                          Ipp64f*  pDst) {
  return ippmDet_m_64f(pSrc,srcStride1,srcStride2,widthHeight,pBuffer,pDst);
}
inline IppStatus ippmDet_m_P(const Ipp32f** ppSrc, int srcRoiShift,
                                          int widthHeight, Ipp32f* pBuffer,
                                          Ipp32f*  pDst) {
  return ippmDet_m_32f_P(ppSrc,srcRoiShift,widthHeight,pBuffer,pDst);
}
inline IppStatus ippmDet_m_P(const Ipp64f** ppSrc, int srcRoiShift,
                                          int widthHeight, Ipp64f* pBuffer,
                                          Ipp64f*  pDst) {
  return ippmDet_m_64f_P(ppSrc,srcRoiShift,widthHeight,pBuffer,pDst);
}
inline IppStatus ippmDet_ma(const Ipp32f*   pSrc, int srcStride0, int srcStride1, int srcStride2,
                                          int widthHeight, Ipp32f* pBuffer,
                                          Ipp32f*  pDst, int count) {
  return ippmDet_ma_32f(pSrc,srcStride0,srcStride1,srcStride2,widthHeight,pBuffer,pDst,count);
}
inline IppStatus ippmDet_ma(const Ipp64f*   pSrc, int srcStride0, int srcStride1, int srcStride2,
                                          int widthHeight, Ipp64f* pBuffer,
                                          Ipp64f*  pDst, int count) {
  return ippmDet_ma_64f(pSrc,srcStride0,srcStride1,srcStride2,widthHeight,pBuffer,pDst,count);
}
inline IppStatus ippmDet_ma_P(const Ipp32f** ppSrc, int srcRoiShift, int srcStride0,
                                          int widthHeight, Ipp32f* pBuffer,
                                          Ipp32f*  pDst,  int count) {
  return ippmDet_ma_32f_P(ppSrc,srcRoiShift,srcStride0,widthHeight,pBuffer,pDst,count);
}
inline IppStatus ippmDet_ma_P(const Ipp64f** ppSrc, int srcRoiShift, int srcStride0,
                                          int widthHeight, Ipp64f* pBuffer,
                                          Ipp64f*  pDst,  int count) {
  return ippmDet_ma_64f_P(ppSrc,srcRoiShift,srcStride0,widthHeight,pBuffer,pDst,count);
}
inline IppStatus ippmDet_ma_L(const Ipp32f** ppSrc, int srcRoiShift, int srcStride1, int srcStride2,
                                          int widthHeight, Ipp32f* pBuffer,
                                          Ipp32f*  pDst,  int count) {
  return ippmDet_ma_32f_L(ppSrc,srcRoiShift,srcStride1,srcStride2,widthHeight,pBuffer,pDst,count);
}
inline IppStatus ippmDet_ma_L(const Ipp64f** ppSrc, int srcRoiShift, int srcStride1, int srcStride2,
                                          int widthHeight, Ipp64f* pBuffer,
                                          Ipp64f*  pDst,  int count) {
  return ippmDet_ma_64f_L(ppSrc,srcRoiShift,srcStride1,srcStride2,widthHeight,pBuffer,pDst,count);
}
inline IppStatus ippmTrace_m(const Ipp32f*  pSrc,   int srcStride1, int srcStride2,
                                            int widthHeight, Ipp32f* pDst) {
  return ippmTrace_m_32f(pSrc,srcStride1,srcStride2,widthHeight,pDst);
}
inline IppStatus ippmTrace_m(const Ipp64f*  pSrc,   int srcStride1, int srcStride2,
                                            int widthHeight, Ipp64f* pDst) {
  return ippmTrace_m_64f(pSrc,srcStride1,srcStride2,widthHeight,pDst);
}
inline IppStatus ippmTrace_m_P(const Ipp32f** ppSrc,  int srcRoiShift,
                                            int widthHeight, Ipp32f* pDst) {
  return ippmTrace_m_32f_P(ppSrc,srcRoiShift,widthHeight,pDst);
}
inline IppStatus ippmTrace_m_P(const Ipp64f** ppSrc,  int srcRoiShift,
                                            int widthHeight, Ipp64f* pDst) {
  return ippmTrace_m_64f_P(ppSrc,srcRoiShift,widthHeight,pDst);
}
inline IppStatus ippmTrace_ma(const Ipp32f*   pSrc,   int srcStride0, int srcStride1, int srcStride2,
                                           int widthHeight,  Ipp32f* pDst,   int count) {
  return ippmTrace_ma_32f(pSrc,srcStride0,srcStride1,srcStride2,widthHeight,pDst,count);
}
inline IppStatus ippmTrace_ma(const Ipp64f*   pSrc,   int srcStride0, int srcStride1, int srcStride2,
                                           int widthHeight,  Ipp64f* pDst,   int count) {
  return ippmTrace_ma_64f(pSrc,srcStride0,srcStride1,srcStride2,widthHeight,pDst,count);
}
inline IppStatus ippmTrace_ma_P(const Ipp32f** ppSrc,  int srcRoiShift, int srcStride0,
                                            int widthHeight, Ipp32f* pDst,    int count) {
  return ippmTrace_ma_32f_P(ppSrc,srcRoiShift,srcStride0,widthHeight,pDst,count);
}
inline IppStatus ippmTrace_ma_P(const Ipp64f** ppSrc,  int srcRoiShift, int srcStride0,
                                            int widthHeight, Ipp64f* pDst,    int count) {
  return ippmTrace_ma_64f_P(ppSrc,srcRoiShift,srcStride0,widthHeight,pDst,count);
}
inline IppStatus ippmTrace_ma_L(const Ipp32f** ppSrc,  int srcRoiShift, int srcStride1, int srcStride2,
                                            int widthHeight, Ipp32f* pDst,    int count) {
  return ippmTrace_ma_32f_L(ppSrc,srcRoiShift,srcStride1,srcStride2,widthHeight,pDst,count);
}
inline IppStatus ippmTrace_ma_L(const Ipp64f** ppSrc,  int srcRoiShift, int srcStride1, int srcStride2,
                                            int widthHeight, Ipp64f* pDst,    int count) {
  return ippmTrace_ma_64f_L(ppSrc,srcRoiShift,srcStride1,srcStride2,widthHeight,pDst,count);
}
inline IppStatus ippmMul_mc(const Ipp32f*  pSrc, int srcStride1, int srcStride2,
                                           Ipp32f   val,
                                           Ipp32f*  pDst, int dstStride1, int dstStride2,
                                           int width, int height) {
  return ippmMul_mc_32f(pSrc,srcStride1,srcStride2,val,pDst,dstStride1,dstStride2,width,height);
}
inline IppStatus ippmMul_mc(const Ipp64f*  pSrc, int srcStride1, int srcStride2,
                                           Ipp64f   val,
                                           Ipp64f*  pDst, int dstStride1, int dstStride2,
                                           int width, int height) {
  return ippmMul_mc_64f(pSrc,srcStride1,srcStride2,val,pDst,dstStride1,dstStride2,width,height);
}
inline IppStatus ippmMul_mc_P(const Ipp32f** ppSrc, int srcRoiShift,
                                           Ipp32f   val,
                                           Ipp32f** ppDst, int dstRoiShift,
                                           int width, int height) {
  return ippmMul_mc_32f_P(ppSrc,srcRoiShift,val,ppDst,dstRoiShift,width,height);
}
inline IppStatus ippmMul_mc_P(const Ipp64f** ppSrc, int srcRoiShift,
                                           Ipp64f   val,
                                           Ipp64f** ppDst, int dstRoiShift,
                                           int width, int height) {
  return ippmMul_mc_64f_P(ppSrc,srcRoiShift,val,ppDst,dstRoiShift,width,height);
}
inline IppStatus ippmMul_tc(const Ipp32f*  pSrc, int srcStride1, int srcStride2,
                                           Ipp32f   val,
                                           Ipp32f*  pDst, int dstStride1, int dstStride2,
                                           int width, int height) {
  return ippmMul_tc_32f(pSrc,srcStride1,srcStride2,val,pDst,dstStride1,dstStride2,width,height);
}
inline IppStatus ippmMul_tc(const Ipp64f*  pSrc, int srcStride1, int srcStride2,
                                           Ipp64f   val,
                                           Ipp64f*  pDst, int dstStride1, int dstStride2,
                                           int width, int height) {
  return ippmMul_tc_64f(pSrc,srcStride1,srcStride2,val,pDst,dstStride1,dstStride2,width,height);
}
inline IppStatus ippmMul_tc_P(const Ipp32f** ppSrc, int srcRoiShift,
                                           Ipp32f   val,
                                           Ipp32f** ppDst, int dstRoiShift,
                                           int width, int height) {
  return ippmMul_tc_32f_P(ppSrc,srcRoiShift,val,ppDst,dstRoiShift,width,height);
}
inline IppStatus ippmMul_tc_P(const Ipp64f** ppSrc, int srcRoiShift,
                                           Ipp64f   val,
                                           Ipp64f** ppDst, int dstRoiShift,
                                           int width, int height) {
  return ippmMul_tc_64f_P(ppSrc,srcRoiShift,val,ppDst,dstRoiShift,width,height);
}
inline IppStatus ippmMul_mac(const Ipp32f*  pSrc, int srcStride0, int srcStride1, int srcStride2,
                                           Ipp32f   val,
                                           Ipp32f*  pDst, int dstStride0, int dstStride1, int dstStride2,
                                           int width, int height, int count) {
  return ippmMul_mac_32f(pSrc,srcStride0,srcStride1,srcStride2,val,pDst,dstStride0,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmMul_mac(const Ipp64f*  pSrc, int srcStride0, int srcStride1, int srcStride2,
                                           Ipp64f   val,
                                           Ipp64f*  pDst, int dstStride0, int dstStride1, int dstStride2,
                                           int width, int height, int count) {
  return ippmMul_mac_64f(pSrc,srcStride0,srcStride1,srcStride2,val,pDst,dstStride0,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmMul_mac_P(const Ipp32f** ppSrc, int srcRoiShift, int srcStride0,
                                           Ipp32f   val,
                                           Ipp32f** ppDst, int dstRoiShift, int dstStride0,
                                           int width, int height, int count) {
  return ippmMul_mac_32f_P(ppSrc,srcRoiShift,srcStride0,val,ppDst,dstRoiShift,dstStride0,width,height,count);
}
inline IppStatus ippmMul_mac_P(const Ipp64f** ppSrc, int srcRoiShift, int srcStride0,
                                           Ipp64f   val,
                                           Ipp64f** ppDst, int dstRoiShift, int dstStride0,
                                           int width, int height, int count) {
  return ippmMul_mac_64f_P(ppSrc,srcRoiShift,srcStride0,val,ppDst,dstRoiShift,dstStride0,width,height,count);
}
inline IppStatus ippmMul_mac_L(const Ipp32f** ppSrc, int srcRoiShift, int srcStride1, int srcStride2,
                                           Ipp32f   val,
                                           Ipp32f** ppDst, int dstRoiShift, int dstStride1, int dstStride2,
                                           int width, int height, int count) {
  return ippmMul_mac_32f_L(ppSrc,srcRoiShift,srcStride1,srcStride2,val,ppDst,dstRoiShift,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmMul_mac_L(const Ipp64f** ppSrc, int srcRoiShift, int srcStride1, int srcStride2,
                                           Ipp64f   val,
                                           Ipp64f** ppDst, int dstRoiShift, int dstStride1, int dstStride2,
                                           int width, int height, int count) {
  return ippmMul_mac_64f_L(ppSrc,srcRoiShift,srcStride1,srcStride2,val,ppDst,dstRoiShift,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmMul_tac(const Ipp32f*  pSrc, int srcStride0, int srcStride1, int srcStride2,
                                           Ipp32f   val,
                                           Ipp32f*  pDst, int dstStride0, int dstStride1, int dstStride2,
                                           int width, int height, int count) {
  return ippmMul_tac_32f(pSrc,srcStride0,srcStride1,srcStride2,val,pDst,dstStride0,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmMul_tac(const Ipp64f*  pSrc, int srcStride0, int srcStride1, int srcStride2,
                                           Ipp64f   val,
                                           Ipp64f*  pDst, int dstStride0, int dstStride1, int dstStride2,
                                           int width, int height, int count) {
  return ippmMul_tac_64f(pSrc,srcStride0,srcStride1,srcStride2,val,pDst,dstStride0,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmMul_tac_P(const Ipp32f** ppSrc, int srcRoiShift, int srcStride0,
                                           Ipp32f   val,
                                           Ipp32f** ppDst, int dstRoiShift, int dstStride0,
                                           int width, int height, int count) {
  return ippmMul_tac_32f_P(ppSrc,srcRoiShift,srcStride0,val,ppDst,dstRoiShift,dstStride0,width,height,count);
}
inline IppStatus ippmMul_tac_P(const Ipp64f** ppSrc, int srcRoiShift, int srcStride0,
                                           Ipp64f   val,
                                           Ipp64f** ppDst, int dstRoiShift, int dstStride0,
                                           int width, int height, int count) {
  return ippmMul_tac_64f_P(ppSrc,srcRoiShift,srcStride0,val,ppDst,dstRoiShift,dstStride0,width,height,count);
}
inline IppStatus ippmMul_tac_L(const Ipp32f** ppSrc, int srcRoiShift, int srcStride1, int srcStride2,
                                           Ipp32f   val,
                                           Ipp32f** ppDst, int dstRoiShift, int dstStride1, int dstStride2,
                                           int width, int height, int count) {
  return ippmMul_tac_32f_L(ppSrc,srcRoiShift,srcStride1,srcStride2,val,ppDst,dstRoiShift,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmMul_tac_L(const Ipp64f** ppSrc, int srcRoiShift, int srcStride1, int srcStride2,
                                           Ipp64f   val,
                                           Ipp64f** ppDst, int dstRoiShift, int dstStride1, int dstStride2,
                                           int width, int height, int count) {
  return ippmMul_tac_64f_L(ppSrc,srcRoiShift,srcStride1,srcStride2,val,ppDst,dstRoiShift,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmMul_mv(const Ipp32f*  pSrc1, int src1Stride1, int src1Stride2,
                                            int src1Width,  int src1Height,
                                      const Ipp32f*  pSrc2, int src2Stride2, int src2Len,
                                            Ipp32f*  pDst,  int dstStride2) {
  return ippmMul_mv_32f(pSrc1,src1Stride1,src1Stride2,src1Width,src1Height,pSrc2,src2Stride2,src2Len,pDst,dstStride2);
}
inline IppStatus ippmMul_mv(const Ipp64f*  pSrc1, int src1Stride1, int src1Stride2,
                                            int src1Width,  int src1Height,
                                      const Ipp64f*  pSrc2, int src2Stride2, int src2Len,
                                            Ipp64f*  pDst,  int dstStride2) {
  return ippmMul_mv_64f(pSrc1,src1Stride1,src1Stride2,src1Width,src1Height,pSrc2,src2Stride2,src2Len,pDst,dstStride2);
}
inline IppStatus ippmMul_mv_P(const Ipp32f** ppSrc1, int src1RoiShift,
                                            int src1Width,   int src1Height,
                                      const Ipp32f** ppSrc2, int src2RoiShift, int src2Len,
                                            Ipp32f** ppDst,  int dstRoiShift) {
  return ippmMul_mv_32f_P(ppSrc1,src1RoiShift,src1Width,src1Height,ppSrc2,src2RoiShift,src2Len,ppDst,dstRoiShift);
}
inline IppStatus ippmMul_mv_P(const Ipp64f** ppSrc1, int src1RoiShift,
                                            int src1Width,   int src1Height,
                                      const Ipp64f** ppSrc2, int src2RoiShift, int src2Len,
                                            Ipp64f** ppDst,  int dstRoiShift) {
  return ippmMul_mv_64f_P(ppSrc1,src1RoiShift,src1Width,src1Height,ppSrc2,src2RoiShift,src2Len,ppDst,dstRoiShift);
}
inline IppStatus ippmMul_tv(const Ipp32f*  pSrc1, int src1Stride1, int src1Stride2,
                                            int src1Width,  int src1Height,
                                      const Ipp32f*  pSrc2, int src2Stride2, int src2Len,
                                            Ipp32f*  pDst,  int dstStride2) {
  return ippmMul_tv_32f(pSrc1,src1Stride1,src1Stride2,src1Width,src1Height,pSrc2,src2Stride2,src2Len,pDst,dstStride2);
}
inline IppStatus ippmMul_tv(const Ipp64f*  pSrc1, int src1Stride1, int src1Stride2,
                                            int src1Width,  int src1Height,
                                      const Ipp64f*  pSrc2, int src2Stride2, int src2Len,
                                            Ipp64f*  pDst,  int dstStride2) {
  return ippmMul_tv_64f(pSrc1,src1Stride1,src1Stride2,src1Width,src1Height,pSrc2,src2Stride2,src2Len,pDst,dstStride2);
}
inline IppStatus ippmMul_tv_P(const Ipp32f** ppSrc1, int src1RoiShift,
                                            int src1Width,   int src1Height,
                                      const Ipp32f** ppSrc2, int src2RoiShift, int src2Len,
                                            Ipp32f** ppDst,  int dstRoiShift) {
  return ippmMul_tv_32f_P(ppSrc1,src1RoiShift,src1Width,src1Height,ppSrc2,src2RoiShift,src2Len,ppDst,dstRoiShift);
}
inline IppStatus ippmMul_tv_P(const Ipp64f** ppSrc1, int src1RoiShift,
                                            int src1Width,   int src1Height,
                                      const Ipp64f** ppSrc2, int src2RoiShift, int src2Len,
                                            Ipp64f** ppDst,  int dstRoiShift) {
  return ippmMul_tv_64f_P(ppSrc1,src1RoiShift,src1Width,src1Height,ppSrc2,src2RoiShift,src2Len,ppDst,dstRoiShift);
}
inline IppStatus ippmMul_mva(const Ipp32f*  pSrc1, int src1Stride1, int src1Stride2,
                                            int src1Width,  int src1Height,
                                      const Ipp32f*  pSrc2, int src2Stride0, int src2Stride2, int src2Len,
                                            Ipp32f*  pDst,  int dstStride0,  int dstStride2, int count) {
  return ippmMul_mva_32f(pSrc1,src1Stride1,src1Stride2,src1Width,src1Height,pSrc2,src2Stride0,src2Stride2,src2Len,pDst,dstStride0,dstStride2,count);
}
inline IppStatus ippmMul_mva(const Ipp64f*  pSrc1, int src1Stride1, int src1Stride2,
                                            int src1Width,  int src1Height,
                                      const Ipp64f*  pSrc2, int src2Stride0, int src2Stride2, int src2Len,
                                            Ipp64f*  pDst,  int dstStride0,  int dstStride2, int count) {
  return ippmMul_mva_64f(pSrc1,src1Stride1,src1Stride2,src1Width,src1Height,pSrc2,src2Stride0,src2Stride2,src2Len,pDst,dstStride0,dstStride2,count);
}
inline IppStatus ippmMul_mva_P(const Ipp32f** ppSrc1, int src1RoiShift,
                                            int src1Width,   int src1Height,
                                      const Ipp32f** ppSrc2, int src2RoiShift, int src2Stride0, int src2Len,
                                            Ipp32f** ppDst,  int dstRoiShift,  int dstStride0,  int count) {
  return ippmMul_mva_32f_P(ppSrc1,src1RoiShift,src1Width,src1Height,ppSrc2,src2RoiShift,src2Stride0,src2Len,ppDst,dstRoiShift,dstStride0,count);
}
inline IppStatus ippmMul_mva_P(const Ipp64f** ppSrc1, int src1RoiShift,
                                            int src1Width,   int src1Height,
                                      const Ipp64f** ppSrc2, int src2RoiShift, int src2Stride0, int src2Len,
                                            Ipp64f** ppDst,  int dstRoiShift,  int dstStride0,  int count) {
  return ippmMul_mva_64f_P(ppSrc1,src1RoiShift,src1Width,src1Height,ppSrc2,src2RoiShift,src2Stride0,src2Len,ppDst,dstRoiShift,dstStride0,count);
}
inline IppStatus ippmMul_mva_L(const Ipp32f*  pSrc1,  int src1Stride1,  int src1Stride2,
                                            int src1Width,   int src1Height,
                                      const Ipp32f** ppSrc2, int src2RoiShift, int src2Stride2, int src2Len,
                                            Ipp32f** ppDst,  int dstRoiShift,  int dstStride2,  int count) {
  return ippmMul_mva_32f_L(pSrc1,src1Stride1,src1Stride2,src1Width,src1Height,ppSrc2,src2RoiShift,src2Stride2,src2Len,ppDst,dstRoiShift,dstStride2,count);
}
inline IppStatus ippmMul_mva_L(const Ipp64f*  pSrc1,  int src1Stride1,  int src1Stride2,
                                            int src1Width,   int src1Height,
                                      const Ipp64f** ppSrc2, int src2RoiShift, int src2Stride2, int src2Len,
                                            Ipp64f** ppDst,  int dstRoiShift,  int dstStride2,  int count) {
  return ippmMul_mva_64f_L(pSrc1,src1Stride1,src1Stride2,src1Width,src1Height,ppSrc2,src2RoiShift,src2Stride2,src2Len,ppDst,dstRoiShift,dstStride2,count);
}
inline IppStatus ippmMul_tva(const Ipp32f*  pSrc1, int src1Stride1, int src1Stride2,
                                            int src1Width,  int src1Height,
                                      const Ipp32f*  pSrc2, int src2Stride0, int src2Stride2, int src2Len,
                                            Ipp32f*  pDst,  int dstStride0,  int dstStride2,  int count) {
  return ippmMul_tva_32f(pSrc1,src1Stride1,src1Stride2,src1Width,src1Height,pSrc2,src2Stride0,src2Stride2,src2Len,pDst,dstStride0,dstStride2,count);
}
inline IppStatus ippmMul_tva(const Ipp64f*  pSrc1, int src1Stride1, int src1Stride2,
                                            int src1Width,  int src1Height,
                                      const Ipp64f*  pSrc2, int src2Stride0, int src2Stride2, int src2Len,
                                            Ipp64f*  pDst,  int dstStride0,  int dstStride2,  int count) {
  return ippmMul_tva_64f(pSrc1,src1Stride1,src1Stride2,src1Width,src1Height,pSrc2,src2Stride0,src2Stride2,src2Len,pDst,dstStride0,dstStride2,count);
}
inline IppStatus ippmMul_tva_P(const Ipp32f** ppSrc1, int src1RoiShift,
                                            int src1Width,   int src1Height,
                                      const Ipp32f** ppSrc2, int src2RoiShift, int src2Stride0, int src2Len,
                                            Ipp32f** ppDst,  int dstRoiShift,  int dstStride0,  int count) {
  return ippmMul_tva_32f_P(ppSrc1,src1RoiShift,src1Width,src1Height,ppSrc2,src2RoiShift,src2Stride0,src2Len,ppDst,dstRoiShift,dstStride0,count);
}
inline IppStatus ippmMul_tva_P(const Ipp64f** ppSrc1, int src1RoiShift,
                                            int src1Width,   int src1Height,
                                      const Ipp64f** ppSrc2, int src2RoiShift, int src2Stride0, int src2Len,
                                            Ipp64f** ppDst,  int dstRoiShift,  int dstStride0,  int count) {
  return ippmMul_tva_64f_P(ppSrc1,src1RoiShift,src1Width,src1Height,ppSrc2,src2RoiShift,src2Stride0,src2Len,ppDst,dstRoiShift,dstStride0,count);
}
inline IppStatus ippmMul_tva_L(const Ipp32f*  pSrc1,  int src1Stride1,  int src1Stride2,
                                            int src1Width,   int src1Height,
                                      const Ipp32f** ppSrc2, int src2RoiShift, int src2Stride2, int src2Len,
                                            Ipp32f** ppDst,  int dstRoiShift,  int dstStride2,  int count) {
  return ippmMul_tva_32f_L(pSrc1,src1Stride1,src1Stride2,src1Width,src1Height,ppSrc2,src2RoiShift,src2Stride2,src2Len,ppDst,dstRoiShift,dstStride2,count);
}
inline IppStatus ippmMul_tva_L(const Ipp64f*  pSrc1,  int src1Stride1,  int src1Stride2,
                                            int src1Width,   int src1Height,
                                      const Ipp64f** ppSrc2, int src2RoiShift, int src2Stride2, int src2Len,
                                            Ipp64f** ppDst,  int dstRoiShift,  int dstStride2,  int count) {
  return ippmMul_tva_64f_L(pSrc1,src1Stride1,src1Stride2,src1Width,src1Height,ppSrc2,src2RoiShift,src2Stride2,src2Len,ppDst,dstRoiShift,dstStride2,count);
}
inline IppStatus ippmMul_mav(const Ipp32f*  pSrc1, int src1Stride0, int src1Stride1, int src1Stride2,
                                            int src1Width,  int src1Height,
                                      const Ipp32f*  pSrc2, int src2Stride2, int src2Len,
                                            Ipp32f*  pDst,  int dstStride0,  int dstStride2, int count) {
  return ippmMul_mav_32f(pSrc1,src1Stride0,src1Stride1,src1Stride2,src1Width,src1Height,pSrc2,src2Stride2,src2Len,pDst,dstStride0,dstStride2,count);
}
inline IppStatus ippmMul_mav(const Ipp64f*  pSrc1, int src1Stride0, int src1Stride1, int src1Stride2,
                                            int src1Width,  int src1Height,
                                      const Ipp64f*  pSrc2, int src2Stride2, int src2Len,
                                            Ipp64f*  pDst,  int dstStride0,  int dstStride2, int count) {
  return ippmMul_mav_64f(pSrc1,src1Stride0,src1Stride1,src1Stride2,src1Width,src1Height,pSrc2,src2Stride2,src2Len,pDst,dstStride0,dstStride2,count);
}
inline IppStatus ippmMul_mav_P(const Ipp32f** ppSrc1, int src1RoiShift, int src1Stride0,
                                            int src1Width,   int src1Height,
                                      const Ipp32f** ppSrc2, int src2RoiShift, int src2Len,
                                            Ipp32f** ppDst,  int dstRoiShift,  int dstStride0, int count) {
  return ippmMul_mav_32f_P(ppSrc1,src1RoiShift,src1Stride0,src1Width,src1Height,ppSrc2,src2RoiShift,src2Len,ppDst,dstRoiShift,dstStride0,count);
}
inline IppStatus ippmMul_mav_P(const Ipp64f** ppSrc1, int src1RoiShift, int src1Stride0,
                                            int src1Width,   int src1Height,
                                      const Ipp64f** ppSrc2, int src2RoiShift, int src2Len,
                                            Ipp64f** ppDst,  int dstRoiShift,  int dstStride0, int count) {
  return ippmMul_mav_64f_P(ppSrc1,src1RoiShift,src1Stride0,src1Width,src1Height,ppSrc2,src2RoiShift,src2Len,ppDst,dstRoiShift,dstStride0,count);
}
inline IppStatus ippmMul_mav_L(const Ipp32f** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                            int src1Width,   int src1Height,
                                      const Ipp32f*  pSrc2,  int src2Stride2,  int src2Len,
                                            Ipp32f** ppDst,  int dstRoiShift,  int dstStride2, int count) {
  return ippmMul_mav_32f_L(ppSrc1,src1RoiShift,src1Stride1,src1Stride2,src1Width,src1Height,pSrc2,src2Stride2,src2Len,ppDst,dstRoiShift,dstStride2,count);
}
inline IppStatus ippmMul_mav_L(const Ipp64f** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                            int src1Width,   int src1Height,
                                      const Ipp64f*  pSrc2,  int src2Stride2,  int src2Len,
                                            Ipp64f** ppDst,  int dstRoiShift,  int dstStride2, int count) {
  return ippmMul_mav_64f_L(ppSrc1,src1RoiShift,src1Stride1,src1Stride2,src1Width,src1Height,pSrc2,src2Stride2,src2Len,ppDst,dstRoiShift,dstStride2,count);
}
inline IppStatus ippmMul_tav(const Ipp32f*  pSrc1, int src1Stride0, int src1Stride1, int src1Stride2,
                                            int src1Width,  int src1Height,
                                      const Ipp32f*  pSrc2, int src2Stride2, int src2Len,
                                            Ipp32f*  pDst,  int dstStride0,  int dstStride2, int count) {
  return ippmMul_tav_32f(pSrc1,src1Stride0,src1Stride1,src1Stride2,src1Width,src1Height,pSrc2,src2Stride2,src2Len,pDst,dstStride0,dstStride2,count);
}
inline IppStatus ippmMul_tav(const Ipp64f*  pSrc1, int src1Stride0, int src1Stride1, int src1Stride2,
                                            int src1Width,  int src1Height,
                                      const Ipp64f*  pSrc2, int src2Stride2, int src2Len,
                                            Ipp64f*  pDst,  int dstStride0,  int dstStride2, int count) {
  return ippmMul_tav_64f(pSrc1,src1Stride0,src1Stride1,src1Stride2,src1Width,src1Height,pSrc2,src2Stride2,src2Len,pDst,dstStride0,dstStride2,count);
}
inline IppStatus ippmMul_tav_P(const Ipp32f** ppSrc1, int src1RoiShift, int src1Stride0,
                                            int src1Width,   int src1Height,
                                      const Ipp32f** ppSrc2, int src2RoiShift, int src2Len,
                                            Ipp32f** ppDst,  int dstRoiShift,  int dstStride0, int count) {
  return ippmMul_tav_32f_P(ppSrc1,src1RoiShift,src1Stride0,src1Width,src1Height,ppSrc2,src2RoiShift,src2Len,ppDst,dstRoiShift,dstStride0,count);
}
inline IppStatus ippmMul_tav_P(const Ipp64f** ppSrc1, int src1RoiShift, int src1Stride0,
                                            int src1Width,   int src1Height,
                                      const Ipp64f** ppSrc2, int src2RoiShift, int src2Len,
                                            Ipp64f** ppDst,  int dstRoiShift,  int dstStride0, int count) {
  return ippmMul_tav_64f_P(ppSrc1,src1RoiShift,src1Stride0,src1Width,src1Height,ppSrc2,src2RoiShift,src2Len,ppDst,dstRoiShift,dstStride0,count);
}
inline IppStatus ippmMul_tav_L(const Ipp32f** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                            int src1Width,   int src1Height,
                                      const Ipp32f*  pSrc2,  int src2Stride2,  int src2Len,
                                            Ipp32f** ppDst,  int dstRoiShift,  int dstStride2, int count) {
  return ippmMul_tav_32f_L(ppSrc1,src1RoiShift,src1Stride1,src1Stride2,src1Width,src1Height,pSrc2,src2Stride2,src2Len,ppDst,dstRoiShift,dstStride2,count);
}
inline IppStatus ippmMul_tav_L(const Ipp64f** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                            int src1Width,   int src1Height,
                                      const Ipp64f*  pSrc2,  int src2Stride2,  int src2Len,
                                            Ipp64f** ppDst,  int dstRoiShift,  int dstStride2, int count) {
  return ippmMul_tav_64f_L(ppSrc1,src1RoiShift,src1Stride1,src1Stride2,src1Width,src1Height,pSrc2,src2Stride2,src2Len,ppDst,dstRoiShift,dstStride2,count);
}
inline IppStatus ippmMul_mava(const Ipp32f*  pSrc1, int src1Stride0, int src1Stride1, int src1Stride2,
                                            int src1Width,  int src1Height,
                                      const Ipp32f*  pSrc2, int src2Stride0, int src2Stride2, int src2Len,
                                            Ipp32f*  pDst,  int dstStride0,  int dstStride2,  int count) {
  return ippmMul_mava_32f(pSrc1,src1Stride0,src1Stride1,src1Stride2,src1Width,src1Height,pSrc2,src2Stride0,src2Stride2,src2Len,pDst,dstStride0,dstStride2,count);
}
inline IppStatus ippmMul_mava(const Ipp64f*  pSrc1, int src1Stride0, int src1Stride1, int src1Stride2,
                                            int src1Width,  int src1Height,
                                      const Ipp64f*  pSrc2, int src2Stride0, int src2Stride2, int src2Len,
                                            Ipp64f*  pDst,  int dstStride0,  int dstStride2,  int count) {
  return ippmMul_mava_64f(pSrc1,src1Stride0,src1Stride1,src1Stride2,src1Width,src1Height,pSrc2,src2Stride0,src2Stride2,src2Len,pDst,dstStride0,dstStride2,count);
}
inline IppStatus ippmMul_mava_P(const Ipp32f** ppSrc1, int src1RoiShift, int src1Stride0,
                                            int src1Width,   int src1Height,
                                      const Ipp32f** ppSrc2, int src2RoiShift, int src2Stride0, int src2Len,
                                            Ipp32f** ppDst,  int dstRoiShift,  int dstStride0, int count) {
  return ippmMul_mava_32f_P(ppSrc1,src1RoiShift,src1Stride0,src1Width,src1Height,ppSrc2,src2RoiShift,src2Stride0,src2Len,ppDst,dstRoiShift,dstStride0,count);
}
inline IppStatus ippmMul_mava_P(const Ipp64f** ppSrc1, int src1RoiShift, int src1Stride0,
                                            int src1Width,   int src1Height,
                                      const Ipp64f** ppSrc2, int src2RoiShift, int src2Stride0, int src2Len,
                                            Ipp64f** ppDst,  int dstRoiShift,  int dstStride0, int count) {
  return ippmMul_mava_64f_P(ppSrc1,src1RoiShift,src1Stride0,src1Width,src1Height,ppSrc2,src2RoiShift,src2Stride0,src2Len,ppDst,dstRoiShift,dstStride0,count);
}
inline IppStatus ippmMul_mava_L(const Ipp32f** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                            int src1Width,   int src1Height,
                                      const Ipp32f** ppSrc2, int src2RoiShift, int src2Stride2, int src2Len,
                                            Ipp32f** ppDst,  int dstRoiShift,  int dstStride2,  int count) {
  return ippmMul_mava_32f_L(ppSrc1,src1RoiShift,src1Stride1,src1Stride2,src1Width,src1Height,ppSrc2,src2RoiShift,src2Stride2,src2Len,ppDst,dstRoiShift,dstStride2,count);
}
inline IppStatus ippmMul_mava_L(const Ipp64f** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                            int src1Width,   int src1Height,
                                      const Ipp64f** ppSrc2, int src2RoiShift, int src2Stride2, int src2Len,
                                            Ipp64f** ppDst,  int dstRoiShift,  int dstStride2,  int count) {
  return ippmMul_mava_64f_L(ppSrc1,src1RoiShift,src1Stride1,src1Stride2,src1Width,src1Height,ppSrc2,src2RoiShift,src2Stride2,src2Len,ppDst,dstRoiShift,dstStride2,count);
}
inline IppStatus ippmMul_tava(const Ipp32f*  pSrc1, int src1Stride0, int src1Stride1, int src1Stride2,
                                            int src1Width,  int src1Height,
                                      const Ipp32f*  pSrc2, int src2Stride0, int src2Stride2, int src2Len,
                                            Ipp32f*  pDst,  int dstStride0,  int dstStride2,  int count) {
  return ippmMul_tava_32f(pSrc1,src1Stride0,src1Stride1,src1Stride2,src1Width,src1Height,pSrc2,src2Stride0,src2Stride2,src2Len,pDst,dstStride0,dstStride2,count);
}
inline IppStatus ippmMul_tava(const Ipp64f*  pSrc1, int src1Stride0, int src1Stride1, int src1Stride2,
                                            int src1Width,  int src1Height,
                                      const Ipp64f*  pSrc2, int src2Stride0, int src2Stride2, int src2Len,
                                            Ipp64f*  pDst,  int dstStride0,  int dstStride2,  int count) {
  return ippmMul_tava_64f(pSrc1,src1Stride0,src1Stride1,src1Stride2,src1Width,src1Height,pSrc2,src2Stride0,src2Stride2,src2Len,pDst,dstStride0,dstStride2,count);
}
inline IppStatus ippmMul_tava_P(const Ipp32f** ppSrc1, int src1RoiShift, int src1Stride0,
                                            int src1Width,   int src1Height,
                                      const Ipp32f** ppSrc2, int src2RoiShift, int src2Stride0, int src2Len,
                                            Ipp32f** ppDst,  int dstRoiShift,  int dstStride0,  int count) {
  return ippmMul_tava_32f_P(ppSrc1,src1RoiShift,src1Stride0,src1Width,src1Height,ppSrc2,src2RoiShift,src2Stride0,src2Len,ppDst,dstRoiShift,dstStride0,count);
}
inline IppStatus ippmMul_tava_P(const Ipp64f** ppSrc1, int src1RoiShift, int src1Stride0,
                                            int src1Width,   int src1Height,
                                      const Ipp64f** ppSrc2, int src2RoiShift, int src2Stride0, int src2Len,
                                            Ipp64f** ppDst,  int dstRoiShift,  int dstStride0,  int count) {
  return ippmMul_tava_64f_P(ppSrc1,src1RoiShift,src1Stride0,src1Width,src1Height,ppSrc2,src2RoiShift,src2Stride0,src2Len,ppDst,dstRoiShift,dstStride0,count);
}
inline IppStatus ippmMul_tava_L(const Ipp32f** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                            int src1Width,   int src1Height,
                                      const Ipp32f** ppSrc2, int src2RoiShift, int src2Stride2, int src2Len,
                                            Ipp32f** ppDst,  int dstRoiShift,  int dstStride2,  int count) {
  return ippmMul_tava_32f_L(ppSrc1,src1RoiShift,src1Stride1,src1Stride2,src1Width,src1Height,ppSrc2,src2RoiShift,src2Stride2,src2Len,ppDst,dstRoiShift,dstStride2,count);
}
inline IppStatus ippmMul_tava_L(const Ipp64f** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                            int src1Width,   int src1Height,
                                      const Ipp64f** ppSrc2, int src2RoiShift, int src2Stride2, int src2Len,
                                            Ipp64f** ppDst,  int dstRoiShift,  int dstStride2,  int count) {
  return ippmMul_tava_64f_L(ppSrc1,src1RoiShift,src1Stride1,src1Stride2,src1Width,src1Height,ppSrc2,src2RoiShift,src2Stride2,src2Len,ppDst,dstRoiShift,dstStride2,count);
}
inline IppStatus ippmMul_mm(const Ipp32f*  pSrc1, int src1Stride1, int src1Stride2,
                                            int src1Width,  int src1Height,
                                      const Ipp32f*  pSrc2, int src2Stride1, int src2Stride2,
                                            int src2Width,  int src2Height,
                                            Ipp32f*  pDst,  int dstStride1,  int dstStride2) {
  return ippmMul_mm_32f(pSrc1,src1Stride1,src1Stride2,src1Width,src1Height,pSrc2,src2Stride1,src2Stride2,src2Width,src2Height,pDst,dstStride1,dstStride2);
}
inline IppStatus ippmMul_mm(const Ipp64f*  pSrc1, int src1Stride1, int src1Stride2,
                                            int src1Width,  int src1Height,
                                      const Ipp64f*  pSrc2, int src2Stride1, int src2Stride2,
                                            int src2Width,  int src2Height,
                                            Ipp64f*  pDst,  int dstStride1,  int dstStride2) {
  return ippmMul_mm_64f(pSrc1,src1Stride1,src1Stride2,src1Width,src1Height,pSrc2,src2Stride1,src2Stride2,src2Width,src2Height,pDst,dstStride1,dstStride2);
}
inline IppStatus ippmMul_mm_P(const Ipp32f** ppSrc1, int src1RoiShift,
                                            int src1Width,   int src1Height,
                                      const Ipp32f** ppSrc2, int src2RoiShift,
                                            int src2Width,   int src2Height,
                                            Ipp32f** ppDst,  int dstRoiShift) {
  return ippmMul_mm_32f_P(ppSrc1,src1RoiShift,src1Width,src1Height,ppSrc2,src2RoiShift,src2Width,src2Height,ppDst,dstRoiShift);
}
inline IppStatus ippmMul_mm_P(const Ipp64f** ppSrc1, int src1RoiShift,
                                            int src1Width,   int src1Height,
                                      const Ipp64f** ppSrc2, int src2RoiShift,
                                            int src2Width,   int src2Height,
                                            Ipp64f** ppDst,  int dstRoiShift) {
  return ippmMul_mm_64f_P(ppSrc1,src1RoiShift,src1Width,src1Height,ppSrc2,src2RoiShift,src2Width,src2Height,ppDst,dstRoiShift);
}
inline IppStatus ippmMul_tm(const Ipp32f*  pSrc1, int src1Stride1, int src1Stride2,
                                            int src1Width,  int src1Height,
                                      const Ipp32f*  pSrc2, int src2Stride1, int src2Stride2,
                                            int src2Width,  int src2Height,
                                            Ipp32f*  pDst,  int dstStride1,  int dstStride2) {
  return ippmMul_tm_32f(pSrc1,src1Stride1,src1Stride2,src1Width,src1Height,pSrc2,src2Stride1,src2Stride2,src2Width,src2Height,pDst,dstStride1,dstStride2);
}
inline IppStatus ippmMul_tm(const Ipp64f*  pSrc1, int src1Stride1, int src1Stride2,
                                            int src1Width,  int src1Height,
                                      const Ipp64f*  pSrc2, int src2Stride1, int src2Stride2,
                                            int src2Width,  int src2Height,
                                            Ipp64f*  pDst,  int dstStride1,  int dstStride2) {
  return ippmMul_tm_64f(pSrc1,src1Stride1,src1Stride2,src1Width,src1Height,pSrc2,src2Stride1,src2Stride2,src2Width,src2Height,pDst,dstStride1,dstStride2);
}
inline IppStatus ippmMul_tm_P(const Ipp32f** ppSrc1, int src1RoiShift,
                                            int src1Width,   int src1Height,
                                      const Ipp32f** ppSrc2, int src2RoiShift,
                                            int src2Width,   int src2Height,
                                            Ipp32f** ppDst,  int dstRoiShift) {
  return ippmMul_tm_32f_P(ppSrc1,src1RoiShift,src1Width,src1Height,ppSrc2,src2RoiShift,src2Width,src2Height,ppDst,dstRoiShift);
}
inline IppStatus ippmMul_tm_P(const Ipp64f** ppSrc1, int src1RoiShift,
                                            int src1Width,   int src1Height,
                                      const Ipp64f** ppSrc2, int src2RoiShift,
                                            int src2Width,   int src2Height,
                                            Ipp64f** ppDst,  int dstRoiShift) {
  return ippmMul_tm_64f_P(ppSrc1,src1RoiShift,src1Width,src1Height,ppSrc2,src2RoiShift,src2Width,src2Height,ppDst,dstRoiShift);
}
inline IppStatus ippmMul_mt(const Ipp32f*  pSrc1, int src1Stride1, int src1Stride2,
                                            int src1Width,  int src1Height,
                                      const Ipp32f*  pSrc2, int src2Stride1, int src2Stride2,
                                            int src2Width,  int src2Height,
                                            Ipp32f*  pDst,  int dstStride1,  int dstStride2) {
  return ippmMul_mt_32f(pSrc1,src1Stride1,src1Stride2,src1Width,src1Height,pSrc2,src2Stride1,src2Stride2,src2Width,src2Height,pDst,dstStride1,dstStride2);
}
inline IppStatus ippmMul_mt(const Ipp64f*  pSrc1, int src1Stride1, int src1Stride2,
                                            int src1Width,  int src1Height,
                                      const Ipp64f*  pSrc2, int src2Stride1, int src2Stride2,
                                            int src2Width,  int src2Height,
                                            Ipp64f*  pDst,  int dstStride1,  int dstStride2) {
  return ippmMul_mt_64f(pSrc1,src1Stride1,src1Stride2,src1Width,src1Height,pSrc2,src2Stride1,src2Stride2,src2Width,src2Height,pDst,dstStride1,dstStride2);
}
inline IppStatus ippmMul_mt_P(const Ipp32f** ppSrc1, int src1RoiShift,
                                            int src1Width,   int src1Height,
                                      const Ipp32f** ppSrc2, int src2RoiShift,
                                            int src2Width,   int src2Height,
                                            Ipp32f** ppDst,  int dstRoiShift) {
  return ippmMul_mt_32f_P(ppSrc1,src1RoiShift,src1Width,src1Height,ppSrc2,src2RoiShift,src2Width,src2Height,ppDst,dstRoiShift);
}
inline IppStatus ippmMul_mt_P(const Ipp64f** ppSrc1, int src1RoiShift,
                                            int src1Width,   int src1Height,
                                      const Ipp64f** ppSrc2, int src2RoiShift,
                                            int src2Width,   int src2Height,
                                            Ipp64f** ppDst,  int dstRoiShift) {
  return ippmMul_mt_64f_P(ppSrc1,src1RoiShift,src1Width,src1Height,ppSrc2,src2RoiShift,src2Width,src2Height,ppDst,dstRoiShift);
}
inline IppStatus ippmMul_tt(const Ipp32f*  pSrc1, int src1Stride1, int src1Stride2,
                                            int src1Width,  int src1Height,
                                      const Ipp32f*  pSrc2, int src2Stride1, int src2Stride2,
                                            int src2Width,  int src2Height,
                                            Ipp32f*  pDst,  int dstStride1,  int dstStride2) {
  return ippmMul_tt_32f(pSrc1,src1Stride1,src1Stride2,src1Width,src1Height,pSrc2,src2Stride1,src2Stride2,src2Width,src2Height,pDst,dstStride1,dstStride2);
}
inline IppStatus ippmMul_tt(const Ipp64f*  pSrc1, int src1Stride1, int src1Stride2,
                                            int src1Width,  int src1Height,
                                      const Ipp64f*  pSrc2, int src2Stride1, int src2Stride2,
                                            int src2Width,  int src2Height,
                                            Ipp64f*  pDst,  int dstStride1,  int dstStride2) {
  return ippmMul_tt_64f(pSrc1,src1Stride1,src1Stride2,src1Width,src1Height,pSrc2,src2Stride1,src2Stride2,src2Width,src2Height,pDst,dstStride1,dstStride2);
}
inline IppStatus ippmMul_tt_P(const Ipp32f** ppSrc1, int src1RoiShift,
                                            int src1Width,   int src1Height,
                                      const Ipp32f** ppSrc2, int src2RoiShift,
                                            int src2Width,   int src2Height,
                                            Ipp32f** ppDst,  int dstRoiShift) {
  return ippmMul_tt_32f_P(ppSrc1,src1RoiShift,src1Width,src1Height,ppSrc2,src2RoiShift,src2Width,src2Height,ppDst,dstRoiShift);
}
inline IppStatus ippmMul_tt_P(const Ipp64f** ppSrc1, int src1RoiShift,
                                            int src1Width,   int src1Height,
                                      const Ipp64f** ppSrc2, int src2RoiShift,
                                            int src2Width,   int src2Height,
                                            Ipp64f** ppDst,  int dstRoiShift) {
  return ippmMul_tt_64f_P(ppSrc1,src1RoiShift,src1Width,src1Height,ppSrc2,src2RoiShift,src2Width,src2Height,ppDst,dstRoiShift);
}
inline IppStatus ippmMul_mma(const Ipp32f*  pSrc1, int src1Stride1, int src1Stride2,
                                            int src1Width,  int src1Height,
                                      const Ipp32f*  pSrc2, int src2Stride0, int src2Stride1, int src2Stride2,
                                            int src2Width,  int src2Height,
                                            Ipp32f*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int count) {
  return ippmMul_mma_32f(pSrc1,src1Stride1,src1Stride2,src1Width,src1Height,pSrc2,src2Stride0,src2Stride1,src2Stride2,src2Width,src2Height,pDst,dstStride0,dstStride1,dstStride2,count);
}
inline IppStatus ippmMul_mma(const Ipp64f*  pSrc1, int src1Stride1, int src1Stride2,
                                            int src1Width,  int src1Height,
                                      const Ipp64f*  pSrc2, int src2Stride0, int src2Stride1, int src2Stride2,
                                            int src2Width,  int src2Height,
                                            Ipp64f*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int count) {
  return ippmMul_mma_64f(pSrc1,src1Stride1,src1Stride2,src1Width,src1Height,pSrc2,src2Stride0,src2Stride1,src2Stride2,src2Width,src2Height,pDst,dstStride0,dstStride1,dstStride2,count);
}
inline IppStatus ippmMul_mma_P(const Ipp32f** ppSrc1, int src1RoiShift,
                                            int src1Width,   int src1Height,
                                      const Ipp32f** ppSrc2, int src2RoiShift, int src2Stride0,
                                            int src2Width,   int src2Height,
                                            Ipp32f** ppDst,  int dstRoiShift,  int dstStride0,
                                            int count) {
  return ippmMul_mma_32f_P(ppSrc1,src1RoiShift,src1Width,src1Height,ppSrc2,src2RoiShift,src2Stride0,src2Width,src2Height,ppDst,dstRoiShift,dstStride0,count);
}
inline IppStatus ippmMul_mma_P(const Ipp64f** ppSrc1, int src1RoiShift,
                                            int src1Width,   int src1Height,
                                      const Ipp64f** ppSrc2, int src2RoiShift, int src2Stride0,
                                            int src2Width,   int src2Height,
                                            Ipp64f** ppDst,  int dstRoiShift,  int dstStride0,
                                            int count) {
  return ippmMul_mma_64f_P(ppSrc1,src1RoiShift,src1Width,src1Height,ppSrc2,src2RoiShift,src2Stride0,src2Width,src2Height,ppDst,dstRoiShift,dstStride0,count);
}
inline IppStatus ippmMul_mma_L(const Ipp32f*  pSrc1,  int src1Stride1,  int src1Stride2,
                                            int src1Width,   int src1Height,
                                      const Ipp32f** ppSrc2, int src2RoiShift, int src2Stride1, int src2Stride2,
                                            int src2Width,   int src2Height,
                                            Ipp32f** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int count) {
  return ippmMul_mma_32f_L(pSrc1,src1Stride1,src1Stride2,src1Width,src1Height,ppSrc2,src2RoiShift,src2Stride1,src2Stride2,src2Width,src2Height,ppDst,dstRoiShift,dstStride1,dstStride2,count);
}
inline IppStatus ippmMul_mma_L(const Ipp64f*  pSrc1,  int src1Stride1,  int src1Stride2,
                                            int src1Width,   int src1Height,
                                      const Ipp64f** ppSrc2, int src2RoiShift, int src2Stride1, int src2Stride2,
                                            int src2Width,   int src2Height,
                                            Ipp64f** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int count) {
  return ippmMul_mma_64f_L(pSrc1,src1Stride1,src1Stride2,src1Width,src1Height,ppSrc2,src2RoiShift,src2Stride1,src2Stride2,src2Width,src2Height,ppDst,dstRoiShift,dstStride1,dstStride2,count);
}
inline IppStatus ippmMul_tma(const Ipp32f*  pSrc1, int src1Stride1, int src1Stride2,
                                            int src1Width,  int src1Height,
                                      const Ipp32f*  pSrc2, int src2Stride0, int src2Stride1, int src2Stride2,
                                            int src2Width,  int src2Height,
                                            Ipp32f*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int count) {
  return ippmMul_tma_32f(pSrc1,src1Stride1,src1Stride2,src1Width,src1Height,pSrc2,src2Stride0,src2Stride1,src2Stride2,src2Width,src2Height,pDst,dstStride0,dstStride1,dstStride2,count);
}
inline IppStatus ippmMul_tma(const Ipp64f*  pSrc1, int src1Stride1, int src1Stride2,
                                            int src1Width,  int src1Height,
                                      const Ipp64f*  pSrc2, int src2Stride0, int src2Stride1, int src2Stride2,
                                            int src2Width,  int src2Height,
                                            Ipp64f*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int count) {
  return ippmMul_tma_64f(pSrc1,src1Stride1,src1Stride2,src1Width,src1Height,pSrc2,src2Stride0,src2Stride1,src2Stride2,src2Width,src2Height,pDst,dstStride0,dstStride1,dstStride2,count);
}
inline IppStatus ippmMul_tma_P(const Ipp32f** ppSrc1, int src1RoiShift,
                                            int src1Width,   int src1Height,
                                      const Ipp32f** ppSrc2, int src2RoiShift, int src2Stride0,
                                            int src2Width,   int src2Height,
                                            Ipp32f** ppDst,  int dstRoiShift,  int dstStride0,
                                            int count) {
  return ippmMul_tma_32f_P(ppSrc1,src1RoiShift,src1Width,src1Height,ppSrc2,src2RoiShift,src2Stride0,src2Width,src2Height,ppDst,dstRoiShift,dstStride0,count);
}
inline IppStatus ippmMul_tma_P(const Ipp64f** ppSrc1, int src1RoiShift,
                                            int src1Width,   int src1Height,
                                      const Ipp64f** ppSrc2, int src2RoiShift, int src2Stride0,
                                            int src2Width,   int src2Height,
                                            Ipp64f** ppDst,  int dstRoiShift,  int dstStride0,
                                            int count) {
  return ippmMul_tma_64f_P(ppSrc1,src1RoiShift,src1Width,src1Height,ppSrc2,src2RoiShift,src2Stride0,src2Width,src2Height,ppDst,dstRoiShift,dstStride0,count);
}
inline IppStatus ippmMul_tma_L(const Ipp32f*  pSrc1,  int src1Stride1,  int src1Stride2,
                                            int src1Width,   int src1Height,
                                      const Ipp32f** ppSrc2, int src2RoiShift, int src2Stride1, int src2Stride2,
                                            int src2Width,   int src2Height,
                                            Ipp32f** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int count) {
  return ippmMul_tma_32f_L(pSrc1,src1Stride1,src1Stride2,src1Width,src1Height,ppSrc2,src2RoiShift,src2Stride1,src2Stride2,src2Width,src2Height,ppDst,dstRoiShift,dstStride1,dstStride2,count);
}
inline IppStatus ippmMul_tma_L(const Ipp64f*  pSrc1,  int src1Stride1,  int src1Stride2,
                                            int src1Width,   int src1Height,
                                      const Ipp64f** ppSrc2, int src2RoiShift, int src2Stride1, int src2Stride2,
                                            int src2Width,   int src2Height,
                                            Ipp64f** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int count) {
  return ippmMul_tma_64f_L(pSrc1,src1Stride1,src1Stride2,src1Width,src1Height,ppSrc2,src2RoiShift,src2Stride1,src2Stride2,src2Width,src2Height,ppDst,dstRoiShift,dstStride1,dstStride2,count);
}
inline IppStatus ippmMul_mta(const Ipp32f*  pSrc1, int src1Stride1, int src1Stride2,
                                            int src1Width,  int src1Height,
                                      const Ipp32f*  pSrc2, int src2Stride0, int src2Stride1, int src2Stride2,
                                            int src2Width,  int src2Height,
                                            Ipp32f*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int count) {
  return ippmMul_mta_32f(pSrc1,src1Stride1,src1Stride2,src1Width,src1Height,pSrc2,src2Stride0,src2Stride1,src2Stride2,src2Width,src2Height,pDst,dstStride0,dstStride1,dstStride2,count);
}
inline IppStatus ippmMul_mta(const Ipp64f*  pSrc1, int src1Stride1, int src1Stride2,
                                            int src1Width,  int src1Height,
                                      const Ipp64f*  pSrc2, int src2Stride0, int src2Stride1, int src2Stride2,
                                            int src2Width,  int src2Height,
                                            Ipp64f*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int count) {
  return ippmMul_mta_64f(pSrc1,src1Stride1,src1Stride2,src1Width,src1Height,pSrc2,src2Stride0,src2Stride1,src2Stride2,src2Width,src2Height,pDst,dstStride0,dstStride1,dstStride2,count);
}
inline IppStatus ippmMul_mta_P(const Ipp32f** ppSrc1, int src1RoiShift,
                                            int src1Width,   int src1Height,
                                      const Ipp32f** ppSrc2, int src2RoiShift, int src2Stride0,
                                            int src2Width,   int src2Height,
                                            Ipp32f** ppDst,  int dstRoiShift,  int dstStride0,
                                            int count) {
  return ippmMul_mta_32f_P(ppSrc1,src1RoiShift,src1Width,src1Height,ppSrc2,src2RoiShift,src2Stride0,src2Width,src2Height,ppDst,dstRoiShift,dstStride0,count);
}
inline IppStatus ippmMul_mta_P(const Ipp64f** ppSrc1, int src1RoiShift,
                                            int src1Width,   int src1Height,
                                      const Ipp64f** ppSrc2, int src2RoiShift, int src2Stride0,
                                            int src2Width,   int src2Height,
                                            Ipp64f** ppDst,  int dstRoiShift,  int dstStride0,
                                            int count) {
  return ippmMul_mta_64f_P(ppSrc1,src1RoiShift,src1Width,src1Height,ppSrc2,src2RoiShift,src2Stride0,src2Width,src2Height,ppDst,dstRoiShift,dstStride0,count);
}
inline IppStatus ippmMul_mta_L(const Ipp32f*  pSrc1,  int src1Stride1,  int src1Stride2,
                                            int src1Width,   int src1Height,
                                      const Ipp32f** ppSrc2, int src2RoiShift, int src2Stride1, int src2Stride2,
                                            int src2Width,   int src2Height,
                                            Ipp32f** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int count) {
  return ippmMul_mta_32f_L(pSrc1,src1Stride1,src1Stride2,src1Width,src1Height,ppSrc2,src2RoiShift,src2Stride1,src2Stride2,src2Width,src2Height,ppDst,dstRoiShift,dstStride1,dstStride2,count);
}
inline IppStatus ippmMul_mta_L(const Ipp64f*  pSrc1,  int src1Stride1,  int src1Stride2,
                                            int src1Width,   int src1Height,
                                      const Ipp64f** ppSrc2, int src2RoiShift, int src2Stride1, int src2Stride2,
                                            int src2Width,   int src2Height,
                                            Ipp64f** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int count) {
  return ippmMul_mta_64f_L(pSrc1,src1Stride1,src1Stride2,src1Width,src1Height,ppSrc2,src2RoiShift,src2Stride1,src2Stride2,src2Width,src2Height,ppDst,dstRoiShift,dstStride1,dstStride2,count);
}
inline IppStatus ippmMul_tta(const Ipp32f*  pSrc1, int src1Stride1, int src1Stride2,
                                            int src1Width,  int src1Height,
                                      const Ipp32f*  pSrc2, int src2Stride0, int src2Stride1, int src2Stride2,
                                            int src2Width,  int src2Height,
                                            Ipp32f*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int count) {
  return ippmMul_tta_32f(pSrc1,src1Stride1,src1Stride2,src1Width,src1Height,pSrc2,src2Stride0,src2Stride1,src2Stride2,src2Width,src2Height,pDst,dstStride0,dstStride1,dstStride2,count);
}
inline IppStatus ippmMul_tta(const Ipp64f*  pSrc1, int src1Stride1, int src1Stride2,
                                            int src1Width,  int src1Height,
                                      const Ipp64f*  pSrc2, int src2Stride0, int src2Stride1, int src2Stride2,
                                            int src2Width,  int src2Height,
                                            Ipp64f*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int count) {
  return ippmMul_tta_64f(pSrc1,src1Stride1,src1Stride2,src1Width,src1Height,pSrc2,src2Stride0,src2Stride1,src2Stride2,src2Width,src2Height,pDst,dstStride0,dstStride1,dstStride2,count);
}
inline IppStatus ippmMul_tta_P(const Ipp32f** ppSrc1, int src1RoiShift,
                                            int src1Width,   int src1Height,
                                      const Ipp32f** ppSrc2, int src2RoiShift, int src2Stride0,
                                            int src2Width,   int src2Height,
                                            Ipp32f** ppDst,  int dstRoiShift,  int dstStride0,
                                            int count) {
  return ippmMul_tta_32f_P(ppSrc1,src1RoiShift,src1Width,src1Height,ppSrc2,src2RoiShift,src2Stride0,src2Width,src2Height,ppDst,dstRoiShift,dstStride0,count);
}
inline IppStatus ippmMul_tta_P(const Ipp64f** ppSrc1, int src1RoiShift,
                                            int src1Width,   int src1Height,
                                      const Ipp64f** ppSrc2, int src2RoiShift, int src2Stride0,
                                            int src2Width,   int src2Height,
                                            Ipp64f** ppDst,  int dstRoiShift,  int dstStride0,
                                            int count) {
  return ippmMul_tta_64f_P(ppSrc1,src1RoiShift,src1Width,src1Height,ppSrc2,src2RoiShift,src2Stride0,src2Width,src2Height,ppDst,dstRoiShift,dstStride0,count);
}
inline IppStatus ippmMul_tta_L(const Ipp32f*  pSrc1,  int src1Stride1,  int src1Stride2,
                                            int src1Width,   int src1Height,
                                      const Ipp32f** ppSrc2, int src2RoiShift, int src2Stride1, int src2Stride2,
                                            int src2Width,   int src2Height,
                                            Ipp32f** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int count) {
  return ippmMul_tta_32f_L(pSrc1,src1Stride1,src1Stride2,src1Width,src1Height,ppSrc2,src2RoiShift,src2Stride1,src2Stride2,src2Width,src2Height,ppDst,dstRoiShift,dstStride1,dstStride2,count);
}
inline IppStatus ippmMul_tta_L(const Ipp64f*  pSrc1,  int src1Stride1,  int src1Stride2,
                                            int src1Width,   int src1Height,
                                      const Ipp64f** ppSrc2, int src2RoiShift, int src2Stride1, int src2Stride2,
                                            int src2Width,   int src2Height,
                                            Ipp64f** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int count) {
  return ippmMul_tta_64f_L(pSrc1,src1Stride1,src1Stride2,src1Width,src1Height,ppSrc2,src2RoiShift,src2Stride1,src2Stride2,src2Width,src2Height,ppDst,dstRoiShift,dstStride1,dstStride2,count);
}
inline IppStatus ippmMul_mam(const Ipp32f*  pSrc1, int src1Stride0, int src1Stride1, int src1Stride2,
                                            int src1Width,  int src1Height,
                                      const Ipp32f*  pSrc2, int src2Stride1, int src2Stride2,
                                            int src2Width,  int src2Height,
                                            Ipp32f*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int count) {
  return ippmMul_mam_32f(pSrc1,src1Stride0,src1Stride1,src1Stride2,src1Width,src1Height,pSrc2,src2Stride1,src2Stride2,src2Width,src2Height,pDst,dstStride0,dstStride1,dstStride2,count);
}
inline IppStatus ippmMul_mam(const Ipp64f*  pSrc1, int src1Stride0, int src1Stride1, int src1Stride2,
                                            int src1Width,  int src1Height,
                                      const Ipp64f*  pSrc2, int src2Stride1, int src2Stride2,
                                            int src2Width,  int src2Height,
                                            Ipp64f*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int count) {
  return ippmMul_mam_64f(pSrc1,src1Stride0,src1Stride1,src1Stride2,src1Width,src1Height,pSrc2,src2Stride1,src2Stride2,src2Width,src2Height,pDst,dstStride0,dstStride1,dstStride2,count);
}
inline IppStatus ippmMul_mam_P(const Ipp32f** ppSrc1, int src1RoiShift, int src1Stride0,
                                            int src1Width,   int src1Height,
                                      const Ipp32f** ppSrc2, int src2RoiShift,
                                            int src2Width,   int src2Height,
                                            Ipp32f** ppDst,  int dstRoiShift,  int dstStride0,
                                            int count) {
  return ippmMul_mam_32f_P(ppSrc1,src1RoiShift,src1Stride0,src1Width,src1Height,ppSrc2,src2RoiShift,src2Width,src2Height,ppDst,dstRoiShift,dstStride0,count);
}
inline IppStatus ippmMul_mam_P(const Ipp64f** ppSrc1, int src1RoiShift, int src1Stride0,
                                            int src1Width,   int src1Height,
                                      const Ipp64f** ppSrc2, int src2RoiShift,
                                            int src2Width,   int src2Height,
                                            Ipp64f** ppDst,  int dstRoiShift,  int dstStride0,
                                            int count) {
  return ippmMul_mam_64f_P(ppSrc1,src1RoiShift,src1Stride0,src1Width,src1Height,ppSrc2,src2RoiShift,src2Width,src2Height,ppDst,dstRoiShift,dstStride0,count);
}
inline IppStatus ippmMul_mam_L(const Ipp32f** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                            int src1Width,   int src1Height,
                                      const Ipp32f*  pSrc2,  int src2Stride1, int src2Stride2,
                                            int src2Width,   int src2Height,
                                            Ipp32f** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int count) {
  return ippmMul_mam_32f_L(ppSrc1,src1RoiShift,src1Stride1,src1Stride2,src1Width,src1Height,pSrc2,src2Stride1,src2Stride2,src2Width,src2Height,ppDst,dstRoiShift,dstStride1,dstStride2,count);
}
inline IppStatus ippmMul_mam_L(const Ipp64f** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                            int src1Width,   int src1Height,
                                      const Ipp64f*  pSrc2,  int src2Stride1, int src2Stride2,
                                            int src2Width,   int src2Height,
                                            Ipp64f** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int count) {
  return ippmMul_mam_64f_L(ppSrc1,src1RoiShift,src1Stride1,src1Stride2,src1Width,src1Height,pSrc2,src2Stride1,src2Stride2,src2Width,src2Height,ppDst,dstRoiShift,dstStride1,dstStride2,count);
}
inline IppStatus ippmMul_tam(const Ipp32f*  pSrc1, int src1Stride0, int src1Stride1, int src1Stride2,
                                            int src1Width,  int src1Height,
                                      const Ipp32f*  pSrc2, int src2Stride1, int src2Stride2,
                                            int src2Width,  int src2Height,
                                            Ipp32f*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int count) {
  return ippmMul_tam_32f(pSrc1,src1Stride0,src1Stride1,src1Stride2,src1Width,src1Height,pSrc2,src2Stride1,src2Stride2,src2Width,src2Height,pDst,dstStride0,dstStride1,dstStride2,count);
}
inline IppStatus ippmMul_tam(const Ipp64f*  pSrc1, int src1Stride0, int src1Stride1, int src1Stride2,
                                            int src1Width,  int src1Height,
                                      const Ipp64f*  pSrc2, int src2Stride1, int src2Stride2,
                                            int src2Width,  int src2Height,
                                            Ipp64f*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int count) {
  return ippmMul_tam_64f(pSrc1,src1Stride0,src1Stride1,src1Stride2,src1Width,src1Height,pSrc2,src2Stride1,src2Stride2,src2Width,src2Height,pDst,dstStride0,dstStride1,dstStride2,count);
}
inline IppStatus ippmMul_tam_P(const Ipp32f** ppSrc1, int src1RoiShift, int src1Stride0,
                                            int src1Width,   int src1Height,
                                      const Ipp32f** ppSrc2, int src2RoiShift,
                                            int src2Width,   int src2Height,
                                            Ipp32f** ppDst,  int dstRoiShift,  int dstStride0,
                                            int count) {
  return ippmMul_tam_32f_P(ppSrc1,src1RoiShift,src1Stride0,src1Width,src1Height,ppSrc2,src2RoiShift,src2Width,src2Height,ppDst,dstRoiShift,dstStride0,count);
}
inline IppStatus ippmMul_tam_P(const Ipp64f** ppSrc1, int src1RoiShift, int src1Stride0,
                                            int src1Width,   int src1Height,
                                      const Ipp64f** ppSrc2, int src2RoiShift,
                                            int src2Width,   int src2Height,
                                            Ipp64f** ppDst,  int dstRoiShift,  int dstStride0,
                                            int count) {
  return ippmMul_tam_64f_P(ppSrc1,src1RoiShift,src1Stride0,src1Width,src1Height,ppSrc2,src2RoiShift,src2Width,src2Height,ppDst,dstRoiShift,dstStride0,count);
}
inline IppStatus ippmMul_tam_L(const Ipp32f** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                            int src1Width,   int src1Height,
                                      const Ipp32f*  pSrc2,  int src2Stride1, int src2Stride2,
                                            int src2Width,   int src2Height,
                                            Ipp32f** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int count) {
  return ippmMul_tam_32f_L(ppSrc1,src1RoiShift,src1Stride1,src1Stride2,src1Width,src1Height,pSrc2,src2Stride1,src2Stride2,src2Width,src2Height,ppDst,dstRoiShift,dstStride1,dstStride2,count);
}
inline IppStatus ippmMul_tam_L(const Ipp64f** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                            int src1Width,   int src1Height,
                                      const Ipp64f*  pSrc2,  int src2Stride1, int src2Stride2,
                                            int src2Width,   int src2Height,
                                            Ipp64f** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int count) {
  return ippmMul_tam_64f_L(ppSrc1,src1RoiShift,src1Stride1,src1Stride2,src1Width,src1Height,pSrc2,src2Stride1,src2Stride2,src2Width,src2Height,ppDst,dstRoiShift,dstStride1,dstStride2,count);
}
inline IppStatus ippmMul_mat(const Ipp32f*  pSrc1, int src1Stride0, int src1Stride1, int src1Stride2,
                                            int src1Width,  int src1Height,
                                      const Ipp32f*  pSrc2, int src2Stride1, int src2Stride2,
                                            int src2Width,  int src2Height,
                                            Ipp32f*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int count) {
  return ippmMul_mat_32f(pSrc1,src1Stride0,src1Stride1,src1Stride2,src1Width,src1Height,pSrc2,src2Stride1,src2Stride2,src2Width,src2Height,pDst,dstStride0,dstStride1,dstStride2,count);
}
inline IppStatus ippmMul_mat(const Ipp64f*  pSrc1, int src1Stride0, int src1Stride1, int src1Stride2,
                                            int src1Width,  int src1Height,
                                      const Ipp64f*  pSrc2, int src2Stride1, int src2Stride2,
                                            int src2Width,  int src2Height,
                                            Ipp64f*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int count) {
  return ippmMul_mat_64f(pSrc1,src1Stride0,src1Stride1,src1Stride2,src1Width,src1Height,pSrc2,src2Stride1,src2Stride2,src2Width,src2Height,pDst,dstStride0,dstStride1,dstStride2,count);
}
inline IppStatus ippmMul_mat_P(const Ipp32f** ppSrc1, int src1RoiShift, int src1Stride0,
                                            int src1Width,   int src1Height,
                                      const Ipp32f** ppSrc2, int src2RoiShift,
                                            int src2Width,   int src2Height,
                                            Ipp32f** ppDst,  int dstRoiShift,  int dstStride0,
                                            int count) {
  return ippmMul_mat_32f_P(ppSrc1,src1RoiShift,src1Stride0,src1Width,src1Height,ppSrc2,src2RoiShift,src2Width,src2Height,ppDst,dstRoiShift,dstStride0,count);
}
inline IppStatus ippmMul_mat_P(const Ipp64f** ppSrc1, int src1RoiShift, int src1Stride0,
                                            int src1Width,   int src1Height,
                                      const Ipp64f** ppSrc2, int src2RoiShift,
                                            int src2Width,   int src2Height,
                                            Ipp64f** ppDst,  int dstRoiShift,  int dstStride0,
                                            int count) {
  return ippmMul_mat_64f_P(ppSrc1,src1RoiShift,src1Stride0,src1Width,src1Height,ppSrc2,src2RoiShift,src2Width,src2Height,ppDst,dstRoiShift,dstStride0,count);
}
inline IppStatus ippmMul_mat_L(const Ipp32f** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                            int src1Width,   int src1Height,
                                      const Ipp32f*  pSrc2,  int src2Stride1, int src2Stride2,
                                            int src2Width,   int src2Height,
                                            Ipp32f** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int count) {
  return ippmMul_mat_32f_L(ppSrc1,src1RoiShift,src1Stride1,src1Stride2,src1Width,src1Height,pSrc2,src2Stride1,src2Stride2,src2Width,src2Height,ppDst,dstRoiShift,dstStride1,dstStride2,count);
}
inline IppStatus ippmMul_mat_L(const Ipp64f** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                            int src1Width,   int src1Height,
                                      const Ipp64f*  pSrc2,  int src2Stride1, int src2Stride2,
                                            int src2Width,   int src2Height,
                                            Ipp64f** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int count) {
  return ippmMul_mat_64f_L(ppSrc1,src1RoiShift,src1Stride1,src1Stride2,src1Width,src1Height,pSrc2,src2Stride1,src2Stride2,src2Width,src2Height,ppDst,dstRoiShift,dstStride1,dstStride2,count);
}
inline IppStatus ippmMul_tat(const Ipp32f*  pSrc1, int src1Stride0, int src1Stride1, int src1Stride2,
                                            int src1Width,  int src1Height,
                                      const Ipp32f*  pSrc2, int src2Stride1, int src2Stride2,
                                            int src2Width,  int src2Height,
                                            Ipp32f*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int count) {
  return ippmMul_tat_32f(pSrc1,src1Stride0,src1Stride1,src1Stride2,src1Width,src1Height,pSrc2,src2Stride1,src2Stride2,src2Width,src2Height,pDst,dstStride0,dstStride1,dstStride2,count);
}
inline IppStatus ippmMul_tat(const Ipp64f*  pSrc1, int src1Stride0, int src1Stride1, int src1Stride2,
                                            int src1Width,  int src1Height,
                                      const Ipp64f*  pSrc2, int src2Stride1, int src2Stride2,
                                            int src2Width,  int src2Height,
                                            Ipp64f*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int count) {
  return ippmMul_tat_64f(pSrc1,src1Stride0,src1Stride1,src1Stride2,src1Width,src1Height,pSrc2,src2Stride1,src2Stride2,src2Width,src2Height,pDst,dstStride0,dstStride1,dstStride2,count);
}
inline IppStatus ippmMul_tat_P(const Ipp32f** ppSrc1, int src1RoiShift, int src1Stride0,
                                            int src1Width,   int src1Height,
                                      const Ipp32f** ppSrc2, int src2RoiShift,
                                            int src2Width,   int src2Height,
                                            Ipp32f** ppDst,  int dstRoiShift,  int dstStride0,
                                            int count) {
  return ippmMul_tat_32f_P(ppSrc1,src1RoiShift,src1Stride0,src1Width,src1Height,ppSrc2,src2RoiShift,src2Width,src2Height,ppDst,dstRoiShift,dstStride0,count);
}
inline IppStatus ippmMul_tat_P(const Ipp64f** ppSrc1, int src1RoiShift, int src1Stride0,
                                            int src1Width,   int src1Height,
                                      const Ipp64f** ppSrc2, int src2RoiShift,
                                            int src2Width,   int src2Height,
                                            Ipp64f** ppDst,  int dstRoiShift,  int dstStride0,
                                            int count) {
  return ippmMul_tat_64f_P(ppSrc1,src1RoiShift,src1Stride0,src1Width,src1Height,ppSrc2,src2RoiShift,src2Width,src2Height,ppDst,dstRoiShift,dstStride0,count);
}
inline IppStatus ippmMul_tat_L(const Ipp32f** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                            int src1Width,   int src1Height,
                                      const Ipp32f*  pSrc2,  int src2Stride1, int src2Stride2,
                                            int src2Width,   int src2Height,
                                            Ipp32f** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int count) {
  return ippmMul_tat_32f_L(ppSrc1,src1RoiShift,src1Stride1,src1Stride2,src1Width,src1Height,pSrc2,src2Stride1,src2Stride2,src2Width,src2Height,ppDst,dstRoiShift,dstStride1,dstStride2,count);
}
inline IppStatus ippmMul_tat_L(const Ipp64f** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                            int src1Width,   int src1Height,
                                      const Ipp64f*  pSrc2,  int src2Stride1, int src2Stride2,
                                            int src2Width,   int src2Height,
                                            Ipp64f** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int count) {
  return ippmMul_tat_64f_L(ppSrc1,src1RoiShift,src1Stride1,src1Stride2,src1Width,src1Height,pSrc2,src2Stride1,src2Stride2,src2Width,src2Height,ppDst,dstRoiShift,dstStride1,dstStride2,count);
}
inline IppStatus ippmMul_mama(const Ipp32f*  pSrc1, int src1Stride0, int src1Stride1, int src1Stride2,
                                            int src1Width,  int src1Height,
                                      const Ipp32f*  pSrc2, int src2Stride0, int src2Stride1, int src2Stride2,
                                            int src2Width,  int src2Height,
                                            Ipp32f*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int count) {
  return ippmMul_mama_32f(pSrc1,src1Stride0,src1Stride1,src1Stride2,src1Width,src1Height,pSrc2,src2Stride0,src2Stride1,src2Stride2,src2Width,src2Height,pDst,dstStride0,dstStride1,dstStride2,count);
}
inline IppStatus ippmMul_mama(const Ipp64f*  pSrc1, int src1Stride0, int src1Stride1, int src1Stride2,
                                            int src1Width,  int src1Height,
                                      const Ipp64f*  pSrc2, int src2Stride0, int src2Stride1, int src2Stride2,
                                            int src2Width,  int src2Height,
                                            Ipp64f*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int count) {
  return ippmMul_mama_64f(pSrc1,src1Stride0,src1Stride1,src1Stride2,src1Width,src1Height,pSrc2,src2Stride0,src2Stride1,src2Stride2,src2Width,src2Height,pDst,dstStride0,dstStride1,dstStride2,count);
}
inline IppStatus ippmMul_mama_P(const Ipp32f** ppSrc1, int src1RoiShift, int src1Stride0,
                                            int src1Width,   int src1Height,
                                      const Ipp32f** ppSrc2, int src2RoiShift, int src2Stride0,
                                            int src2Width,   int src2Height,
                                            Ipp32f** ppDst,  int dstRoiShift,  int dstStride0,
                                            int count) {
  return ippmMul_mama_32f_P(ppSrc1,src1RoiShift,src1Stride0,src1Width,src1Height,ppSrc2,src2RoiShift,src2Stride0,src2Width,src2Height,ppDst,dstRoiShift,dstStride0,count);
}
inline IppStatus ippmMul_mama_P(const Ipp64f** ppSrc1, int src1RoiShift, int src1Stride0,
                                            int src1Width,   int src1Height,
                                      const Ipp64f** ppSrc2, int src2RoiShift, int src2Stride0,
                                            int src2Width,   int src2Height,
                                            Ipp64f** ppDst,  int dstRoiShift,  int dstStride0,
                                            int count) {
  return ippmMul_mama_64f_P(ppSrc1,src1RoiShift,src1Stride0,src1Width,src1Height,ppSrc2,src2RoiShift,src2Stride0,src2Width,src2Height,ppDst,dstRoiShift,dstStride0,count);
}
inline IppStatus ippmMul_mama_L(const Ipp32f** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                            int src1Width,   int src1Height,
                                      const Ipp32f** ppSrc2, int src2RoiShift, int src2Stride1, int src2Stride2,
                                            int src2Width,   int src2Height,
                                            Ipp32f** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int count) {
  return ippmMul_mama_32f_L(ppSrc1,src1RoiShift,src1Stride1,src1Stride2,src1Width,src1Height,ppSrc2,src2RoiShift,src2Stride1,src2Stride2,src2Width,src2Height,ppDst,dstRoiShift,dstStride1,dstStride2,count);
}
inline IppStatus ippmMul_mama_L(const Ipp64f** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                            int src1Width,   int src1Height,
                                      const Ipp64f** ppSrc2, int src2RoiShift, int src2Stride1, int src2Stride2,
                                            int src2Width,   int src2Height,
                                            Ipp64f** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int count) {
  return ippmMul_mama_64f_L(ppSrc1,src1RoiShift,src1Stride1,src1Stride2,src1Width,src1Height,ppSrc2,src2RoiShift,src2Stride1,src2Stride2,src2Width,src2Height,ppDst,dstRoiShift,dstStride1,dstStride2,count);
}
inline IppStatus ippmMul_tama(const Ipp32f*  pSrc1, int src1Stride0, int src1Stride1, int src1Stride2,
                                            int src1Width,  int src1Height,
                                      const Ipp32f*  pSrc2, int src2Stride0, int src2Stride1, int src2Stride2,
                                            int src2Width,  int src2Height,
                                            Ipp32f*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int count) {
  return ippmMul_tama_32f(pSrc1,src1Stride0,src1Stride1,src1Stride2,src1Width,src1Height,pSrc2,src2Stride0,src2Stride1,src2Stride2,src2Width,src2Height,pDst,dstStride0,dstStride1,dstStride2,count);
}
inline IppStatus ippmMul_tama(const Ipp64f*  pSrc1, int src1Stride0, int src1Stride1, int src1Stride2,
                                            int src1Width,  int src1Height,
                                      const Ipp64f*  pSrc2, int src2Stride0, int src2Stride1, int src2Stride2,
                                            int src2Width,  int src2Height,
                                            Ipp64f*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int count) {
  return ippmMul_tama_64f(pSrc1,src1Stride0,src1Stride1,src1Stride2,src1Width,src1Height,pSrc2,src2Stride0,src2Stride1,src2Stride2,src2Width,src2Height,pDst,dstStride0,dstStride1,dstStride2,count);
}
inline IppStatus ippmMul_tama_P(const Ipp32f** ppSrc1, int src1RoiShift, int src1Stride0,
                                            int src1Width,   int src1Height,
                                      const Ipp32f** ppSrc2, int src2RoiShift, int src2Stride0,
                                            int src2Width,   int src2Height,
                                            Ipp32f** ppDst,  int dstRoiShift,  int dstStride0,
                                            int count) {
  return ippmMul_tama_32f_P(ppSrc1,src1RoiShift,src1Stride0,src1Width,src1Height,ppSrc2,src2RoiShift,src2Stride0,src2Width,src2Height,ppDst,dstRoiShift,dstStride0,count);
}
inline IppStatus ippmMul_tama_P(const Ipp64f** ppSrc1, int src1RoiShift, int src1Stride0,
                                            int src1Width,   int src1Height,
                                      const Ipp64f** ppSrc2, int src2RoiShift, int src2Stride0,
                                            int src2Width,   int src2Height,
                                            Ipp64f** ppDst,  int dstRoiShift,  int dstStride0,
                                            int count) {
  return ippmMul_tama_64f_P(ppSrc1,src1RoiShift,src1Stride0,src1Width,src1Height,ppSrc2,src2RoiShift,src2Stride0,src2Width,src2Height,ppDst,dstRoiShift,dstStride0,count);
}
inline IppStatus ippmMul_tama_L(const Ipp32f** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                            int src1Width,   int src1Height,
                                      const Ipp32f** ppSrc2, int src2RoiShift, int src2Stride1, int src2Stride2,
                                            int src2Width,   int src2Height,
                                            Ipp32f** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int count) {
  return ippmMul_tama_32f_L(ppSrc1,src1RoiShift,src1Stride1,src1Stride2,src1Width,src1Height,ppSrc2,src2RoiShift,src2Stride1,src2Stride2,src2Width,src2Height,ppDst,dstRoiShift,dstStride1,dstStride2,count);
}
inline IppStatus ippmMul_tama_L(const Ipp64f** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                            int src1Width,   int src1Height,
                                      const Ipp64f** ppSrc2, int src2RoiShift, int src2Stride1, int src2Stride2,
                                            int src2Width,   int src2Height,
                                            Ipp64f** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int count) {
  return ippmMul_tama_64f_L(ppSrc1,src1RoiShift,src1Stride1,src1Stride2,src1Width,src1Height,ppSrc2,src2RoiShift,src2Stride1,src2Stride2,src2Width,src2Height,ppDst,dstRoiShift,dstStride1,dstStride2,count);
}
inline IppStatus ippmMul_mata(const Ipp32f*  pSrc1, int src1Stride0, int src1Stride1, int src1Stride2,
                                            int src1Width,  int src1Height,
                                      const Ipp32f*  pSrc2, int src2Stride0, int src2Stride1, int src2Stride2,
                                            int src2Width,  int src2Height,
                                            Ipp32f*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int count) {
  return ippmMul_mata_32f(pSrc1,src1Stride0,src1Stride1,src1Stride2,src1Width,src1Height,pSrc2,src2Stride0,src2Stride1,src2Stride2,src2Width,src2Height,pDst,dstStride0,dstStride1,dstStride2,count);
}
inline IppStatus ippmMul_mata(const Ipp64f*  pSrc1, int src1Stride0, int src1Stride1, int src1Stride2,
                                            int src1Width,  int src1Height,
                                      const Ipp64f*  pSrc2, int src2Stride0, int src2Stride1, int src2Stride2,
                                            int src2Width,  int src2Height,
                                            Ipp64f*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int count) {
  return ippmMul_mata_64f(pSrc1,src1Stride0,src1Stride1,src1Stride2,src1Width,src1Height,pSrc2,src2Stride0,src2Stride1,src2Stride2,src2Width,src2Height,pDst,dstStride0,dstStride1,dstStride2,count);
}
inline IppStatus ippmMul_mata_P(const Ipp32f** ppSrc1, int src1RoiShift, int src1Stride0,
                                            int src1Width,   int src1Height,
                                      const Ipp32f** ppSrc2, int src2RoiShift, int src2Stride0,
                                            int src2Width,   int src2Height,
                                            Ipp32f** ppDst,  int dstRoiShift,  int dstStride0,
                                            int count) {
  return ippmMul_mata_32f_P(ppSrc1,src1RoiShift,src1Stride0,src1Width,src1Height,ppSrc2,src2RoiShift,src2Stride0,src2Width,src2Height,ppDst,dstRoiShift,dstStride0,count);
}
inline IppStatus ippmMul_mata_P(const Ipp64f** ppSrc1, int src1RoiShift, int src1Stride0,
                                            int src1Width,   int src1Height,
                                      const Ipp64f** ppSrc2, int src2RoiShift, int src2Stride0,
                                            int src2Width,   int src2Height,
                                            Ipp64f** ppDst,  int dstRoiShift,  int dstStride0,
                                            int count) {
  return ippmMul_mata_64f_P(ppSrc1,src1RoiShift,src1Stride0,src1Width,src1Height,ppSrc2,src2RoiShift,src2Stride0,src2Width,src2Height,ppDst,dstRoiShift,dstStride0,count);
}
inline IppStatus ippmMul_mata_L(const Ipp32f** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                            int src1Width,   int src1Height,
                                      const Ipp32f** ppSrc2, int src2RoiShift, int src2Stride1, int src2Stride2,
                                            int src2Width,   int src2Height,
                                            Ipp32f** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int count) {
  return ippmMul_mata_32f_L(ppSrc1,src1RoiShift,src1Stride1,src1Stride2,src1Width,src1Height,ppSrc2,src2RoiShift,src2Stride1,src2Stride2,src2Width,src2Height,ppDst,dstRoiShift,dstStride1,dstStride2,count);
}
inline IppStatus ippmMul_mata_L(const Ipp64f** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                            int src1Width,   int src1Height,
                                      const Ipp64f** ppSrc2, int src2RoiShift, int src2Stride1, int src2Stride2,
                                            int src2Width,   int src2Height,
                                            Ipp64f** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int count) {
  return ippmMul_mata_64f_L(ppSrc1,src1RoiShift,src1Stride1,src1Stride2,src1Width,src1Height,ppSrc2,src2RoiShift,src2Stride1,src2Stride2,src2Width,src2Height,ppDst,dstRoiShift,dstStride1,dstStride2,count);
}
inline IppStatus ippmMul_tata(const Ipp32f*  pSrc1, int src1Stride0, int src1Stride1, int src1Stride2,
                                            int src1Width,  int src1Height,
                                      const Ipp32f*  pSrc2, int src2Stride0, int src2Stride1, int src2Stride2,
                                            int src2Width,  int src2Height,
                                            Ipp32f*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int count) {
  return ippmMul_tata_32f(pSrc1,src1Stride0,src1Stride1,src1Stride2,src1Width,src1Height,pSrc2,src2Stride0,src2Stride1,src2Stride2,src2Width,src2Height,pDst,dstStride0,dstStride1,dstStride2,count);
}
inline IppStatus ippmMul_tata(const Ipp64f*  pSrc1, int src1Stride0, int src1Stride1, int src1Stride2,
                                            int src1Width,  int src1Height,
                                      const Ipp64f*  pSrc2, int src2Stride0, int src2Stride1, int src2Stride2,
                                            int src2Width,  int src2Height,
                                            Ipp64f*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int count) {
  return ippmMul_tata_64f(pSrc1,src1Stride0,src1Stride1,src1Stride2,src1Width,src1Height,pSrc2,src2Stride0,src2Stride1,src2Stride2,src2Width,src2Height,pDst,dstStride0,dstStride1,dstStride2,count);
}
inline IppStatus ippmMul_tata_P(const Ipp32f** ppSrc1, int src1RoiShift, int src1Stride0,
                                            int src1Width,   int src1Height,
                                      const Ipp32f** ppSrc2, int src2RoiShift, int src2Stride0,
                                            int src2Width,   int src2Height,
                                            Ipp32f** ppDst,  int dstRoiShift,  int dstStride0,
                                            int count) {
  return ippmMul_tata_32f_P(ppSrc1,src1RoiShift,src1Stride0,src1Width,src1Height,ppSrc2,src2RoiShift,src2Stride0,src2Width,src2Height,ppDst,dstRoiShift,dstStride0,count);
}
inline IppStatus ippmMul_tata_P(const Ipp64f** ppSrc1, int src1RoiShift, int src1Stride0,
                                            int src1Width,   int src1Height,
                                      const Ipp64f** ppSrc2, int src2RoiShift, int src2Stride0,
                                            int src2Width,   int src2Height,
                                            Ipp64f** ppDst,  int dstRoiShift,  int dstStride0,
                                            int count) {
  return ippmMul_tata_64f_P(ppSrc1,src1RoiShift,src1Stride0,src1Width,src1Height,ppSrc2,src2RoiShift,src2Stride0,src2Width,src2Height,ppDst,dstRoiShift,dstStride0,count);
}
inline IppStatus ippmMul_tata_L(const Ipp32f** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                            int src1Width,   int src1Height,
                                      const Ipp32f** ppSrc2, int src2RoiShift, int src2Stride1, int src2Stride2,
                                            int src2Width,   int src2Height,
                                            Ipp32f** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int count) {
  return ippmMul_tata_32f_L(ppSrc1,src1RoiShift,src1Stride1,src1Stride2,src1Width,src1Height,ppSrc2,src2RoiShift,src2Stride1,src2Stride2,src2Width,src2Height,ppDst,dstRoiShift,dstStride1,dstStride2,count);
}
inline IppStatus ippmMul_tata_L(const Ipp64f** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                            int src1Width,   int src1Height,
                                      const Ipp64f** ppSrc2, int src2RoiShift, int src2Stride1, int src2Stride2,
                                            int src2Width,   int src2Height,
                                            Ipp64f** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int count) {
  return ippmMul_tata_64f_L(ppSrc1,src1RoiShift,src1Stride1,src1Stride2,src1Width,src1Height,ppSrc2,src2RoiShift,src2Stride1,src2Stride2,src2Width,src2Height,ppDst,dstRoiShift,dstStride1,dstStride2,count);
}
inline IppStatus ippmAdd_mm(const Ipp32f*  pSrc1, int src1Stride1, int src1Stride2,
                                      const Ipp32f*  pSrc2, int src2Stride1, int src2Stride2,
                                            Ipp32f*  pDst,  int dstStride1,  int dstStride2,
                                            int width, int height) {
  return ippmAdd_mm_32f(pSrc1,src1Stride1,src1Stride2,pSrc2,src2Stride1,src2Stride2,pDst,dstStride1,dstStride2,width,height);
}
inline IppStatus ippmAdd_mm(const Ipp64f*  pSrc1, int src1Stride1, int src1Stride2,
                                      const Ipp64f*  pSrc2, int src2Stride1, int src2Stride2,
                                            Ipp64f*  pDst,  int dstStride1,  int dstStride2,
                                            int width, int height) {
  return ippmAdd_mm_64f(pSrc1,src1Stride1,src1Stride2,pSrc2,src2Stride1,src2Stride2,pDst,dstStride1,dstStride2,width,height);
}
inline IppStatus ippmAdd_mm_P(const Ipp32f** ppSrc1, int src1RoiShift,
                                      const Ipp32f** ppSrc2, int src2RoiShift,
                                            Ipp32f** ppDst,  int dstRoiShift,
                                            int width, int height) {
  return ippmAdd_mm_32f_P(ppSrc1,src1RoiShift,ppSrc2,src2RoiShift,ppDst,dstRoiShift,width,height);
}
inline IppStatus ippmAdd_mm_P(const Ipp64f** ppSrc1, int src1RoiShift,
                                      const Ipp64f** ppSrc2, int src2RoiShift,
                                            Ipp64f** ppDst,  int dstRoiShift,
                                            int width, int height) {
  return ippmAdd_mm_64f_P(ppSrc1,src1RoiShift,ppSrc2,src2RoiShift,ppDst,dstRoiShift,width,height);
}
inline IppStatus ippmAdd_tm(const Ipp32f*  pSrc1, int src1Stride1, int src1Stride2,
                                      const Ipp32f*  pSrc2, int src2Stride1, int src2Stride2,
                                            Ipp32f*  pDst,  int dstStride1,  int dstStride2,
                                            int width, int height) {
  return ippmAdd_tm_32f(pSrc1,src1Stride1,src1Stride2,pSrc2,src2Stride1,src2Stride2,pDst,dstStride1,dstStride2,width,height);
}
inline IppStatus ippmAdd_tm(const Ipp64f*  pSrc1, int src1Stride1, int src1Stride2,
                                      const Ipp64f*  pSrc2, int src2Stride1, int src2Stride2,
                                            Ipp64f*  pDst,  int dstStride1,  int dstStride2,
                                            int width, int height) {
  return ippmAdd_tm_64f(pSrc1,src1Stride1,src1Stride2,pSrc2,src2Stride1,src2Stride2,pDst,dstStride1,dstStride2,width,height);
}
inline IppStatus ippmAdd_tm_P(const Ipp32f** ppSrc1, int src1RoiShift,
                                      const Ipp32f** ppSrc2, int src2RoiShift,
                                            Ipp32f** ppDst,  int dstRoiShift,
                                            int width, int height) {
  return ippmAdd_tm_32f_P(ppSrc1,src1RoiShift,ppSrc2,src2RoiShift,ppDst,dstRoiShift,width,height);
}
inline IppStatus ippmAdd_tm_P(const Ipp64f** ppSrc1, int src1RoiShift,
                                      const Ipp64f** ppSrc2, int src2RoiShift,
                                            Ipp64f** ppDst,  int dstRoiShift,
                                            int width, int height) {
  return ippmAdd_tm_64f_P(ppSrc1,src1RoiShift,ppSrc2,src2RoiShift,ppDst,dstRoiShift,width,height);
}
inline IppStatus ippmAdd_tt(const Ipp32f*  pSrc1, int src1Stride1, int src1Stride2,
                                      const Ipp32f*  pSrc2, int src2Stride1, int src2Stride2,
                                            Ipp32f*  pDst,  int dstStride1,  int dstStride2,
                                            int width, int height) {
  return ippmAdd_tt_32f(pSrc1,src1Stride1,src1Stride2,pSrc2,src2Stride1,src2Stride2,pDst,dstStride1,dstStride2,width,height);
}
inline IppStatus ippmAdd_tt(const Ipp64f*  pSrc1, int src1Stride1, int src1Stride2,
                                      const Ipp64f*  pSrc2, int src2Stride1, int src2Stride2,
                                            Ipp64f*  pDst,  int dstStride1,  int dstStride2,
                                            int width, int height) {
  return ippmAdd_tt_64f(pSrc1,src1Stride1,src1Stride2,pSrc2,src2Stride1,src2Stride2,pDst,dstStride1,dstStride2,width,height);
}
inline IppStatus ippmAdd_tt_P(const Ipp32f** ppSrc1, int src1RoiShift,
                                      const Ipp32f** ppSrc2, int src2RoiShift,
                                            Ipp32f** ppDst,  int dstRoiShift,
                                            int width, int height) {
  return ippmAdd_tt_32f_P(ppSrc1,src1RoiShift,ppSrc2,src2RoiShift,ppDst,dstRoiShift,width,height);
}
inline IppStatus ippmAdd_tt_P(const Ipp64f** ppSrc1, int src1RoiShift,
                                      const Ipp64f** ppSrc2, int src2RoiShift,
                                            Ipp64f** ppDst,  int dstRoiShift,
                                            int width, int height) {
  return ippmAdd_tt_64f_P(ppSrc1,src1RoiShift,ppSrc2,src2RoiShift,ppDst,dstRoiShift,width,height);
}
inline IppStatus ippmAdd_mam(const Ipp32f*  pSrc1, int src1Stride0, int src1Stride1, int src1Stride2,
                                      const Ipp32f*  pSrc2, int src2Stride1, int src2Stride2,
                                            Ipp32f*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
  return ippmAdd_mam_32f(pSrc1,src1Stride0,src1Stride1,src1Stride2,pSrc2,src2Stride1,src2Stride2,pDst,dstStride0,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmAdd_mam(const Ipp64f*  pSrc1, int src1Stride0, int src1Stride1, int src1Stride2,
                                      const Ipp64f*  pSrc2, int src2Stride1, int src2Stride2,
                                            Ipp64f*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
  return ippmAdd_mam_64f(pSrc1,src1Stride0,src1Stride1,src1Stride2,pSrc2,src2Stride1,src2Stride2,pDst,dstStride0,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmAdd_mam_P(const Ipp32f** ppSrc1, int src1RoiShift, int src1Stride0,
                                      const Ipp32f** ppSrc2, int src2RoiShift,
                                            Ipp32f** ppDst,  int dstRoiShift,  int dstStride0,
                                            int width, int height, int count) {
  return ippmAdd_mam_32f_P(ppSrc1,src1RoiShift,src1Stride0,ppSrc2,src2RoiShift,ppDst,dstRoiShift,dstStride0,width,height,count);
}
inline IppStatus ippmAdd_mam_P(const Ipp64f** ppSrc1, int src1RoiShift, int src1Stride0,
                                      const Ipp64f** ppSrc2, int src2RoiShift,
                                            Ipp64f** ppDst,  int dstRoiShift,  int dstStride0,
                                            int width, int height, int count) {
  return ippmAdd_mam_64f_P(ppSrc1,src1RoiShift,src1Stride0,ppSrc2,src2RoiShift,ppDst,dstRoiShift,dstStride0,width,height,count);
}
inline IppStatus ippmAdd_mam_L(const Ipp32f** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                      const Ipp32f*  pSrc2,  int src2Stride1,  int src2Stride2,
                                            Ipp32f** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
  return ippmAdd_mam_32f_L(ppSrc1,src1RoiShift,src1Stride1,src1Stride2,pSrc2,src2Stride1,src2Stride2,ppDst,dstRoiShift,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmAdd_mam_L(const Ipp64f** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                      const Ipp64f*  pSrc2,  int src2Stride1,  int src2Stride2,
                                            Ipp64f** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
  return ippmAdd_mam_64f_L(ppSrc1,src1RoiShift,src1Stride1,src1Stride2,pSrc2,src2Stride1,src2Stride2,ppDst,dstRoiShift,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmAdd_tam(const Ipp32f*  pSrc1, int src1Stride0, int src1Stride1, int src1Stride2,
                                      const Ipp32f*  pSrc2, int src2Stride1, int src2Stride2,
                                            Ipp32f*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
  return ippmAdd_tam_32f(pSrc1,src1Stride0,src1Stride1,src1Stride2,pSrc2,src2Stride1,src2Stride2,pDst,dstStride0,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmAdd_tam(const Ipp64f*  pSrc1, int src1Stride0, int src1Stride1, int src1Stride2,
                                      const Ipp64f*  pSrc2, int src2Stride1, int src2Stride2,
                                            Ipp64f*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
  return ippmAdd_tam_64f(pSrc1,src1Stride0,src1Stride1,src1Stride2,pSrc2,src2Stride1,src2Stride2,pDst,dstStride0,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmAdd_tam_P(const Ipp32f** ppSrc1, int src1RoiShift, int src1Stride0,
                                      const Ipp32f** ppSrc2, int src2RoiShift,
                                            Ipp32f** ppDst,  int dstRoiShift,  int dstStride0,
                                            int width, int height, int count) {
  return ippmAdd_tam_32f_P(ppSrc1,src1RoiShift,src1Stride0,ppSrc2,src2RoiShift,ppDst,dstRoiShift,dstStride0,width,height,count);
}
inline IppStatus ippmAdd_tam_P(const Ipp64f** ppSrc1, int src1RoiShift, int src1Stride0,
                                      const Ipp64f** ppSrc2, int src2RoiShift,
                                            Ipp64f** ppDst,  int dstRoiShift,  int dstStride0,
                                            int width, int height, int count) {
  return ippmAdd_tam_64f_P(ppSrc1,src1RoiShift,src1Stride0,ppSrc2,src2RoiShift,ppDst,dstRoiShift,dstStride0,width,height,count);
}
inline IppStatus ippmAdd_tam_L(const Ipp32f** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                      const Ipp32f*  pSrc2,  int src2Stride1,  int src2Stride2,
                                            Ipp32f** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
  return ippmAdd_tam_32f_L(ppSrc1,src1RoiShift,src1Stride1,src1Stride2,pSrc2,src2Stride1,src2Stride2,ppDst,dstRoiShift,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmAdd_tam_L(const Ipp64f** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                      const Ipp64f*  pSrc2,  int src2Stride1,  int src2Stride2,
                                            Ipp64f** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
  return ippmAdd_tam_64f_L(ppSrc1,src1RoiShift,src1Stride1,src1Stride2,pSrc2,src2Stride1,src2Stride2,ppDst,dstRoiShift,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmAdd_mat(const Ipp32f*  pSrc1, int src1Stride0, int src1Stride1, int src1Stride2,
                                      const Ipp32f*  pSrc2, int src2Stride1, int src2Stride2,
                                            Ipp32f*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
  return ippmAdd_mat_32f(pSrc1,src1Stride0,src1Stride1,src1Stride2,pSrc2,src2Stride1,src2Stride2,pDst,dstStride0,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmAdd_mat(const Ipp64f*  pSrc1, int src1Stride0, int src1Stride1, int src1Stride2,
                                      const Ipp64f*  pSrc2, int src2Stride1, int src2Stride2,
                                            Ipp64f*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
  return ippmAdd_mat_64f(pSrc1,src1Stride0,src1Stride1,src1Stride2,pSrc2,src2Stride1,src2Stride2,pDst,dstStride0,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmAdd_mat_P(const Ipp32f** ppSrc1, int src1RoiShift, int src1Stride0,
                                      const Ipp32f** ppSrc2, int src2RoiShift,
                                            Ipp32f** ppDst,  int dstRoiShift,  int dstStride0,
                                            int width, int height, int count) {
  return ippmAdd_mat_32f_P(ppSrc1,src1RoiShift,src1Stride0,ppSrc2,src2RoiShift,ppDst,dstRoiShift,dstStride0,width,height,count);
}
inline IppStatus ippmAdd_mat_P(const Ipp64f** ppSrc1, int src1RoiShift, int src1Stride0,
                                      const Ipp64f** ppSrc2, int src2RoiShift,
                                            Ipp64f** ppDst,  int dstRoiShift,  int dstStride0,
                                            int width, int height, int count) {
  return ippmAdd_mat_64f_P(ppSrc1,src1RoiShift,src1Stride0,ppSrc2,src2RoiShift,ppDst,dstRoiShift,dstStride0,width,height,count);
}
inline IppStatus ippmAdd_mat_L(const Ipp32f** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                      const Ipp32f*  pSrc2,  int src2Stride1,  int src2Stride2,
                                            Ipp32f** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
  return ippmAdd_mat_32f_L(ppSrc1,src1RoiShift,src1Stride1,src1Stride2,pSrc2,src2Stride1,src2Stride2,ppDst,dstRoiShift,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmAdd_mat_L(const Ipp64f** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                      const Ipp64f*  pSrc2,  int src2Stride1,  int src2Stride2,
                                            Ipp64f** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
  return ippmAdd_mat_64f_L(ppSrc1,src1RoiShift,src1Stride1,src1Stride2,pSrc2,src2Stride1,src2Stride2,ppDst,dstRoiShift,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmAdd_tat(const Ipp32f*  pSrc1, int src1Stride0, int src1Stride1, int src1Stride2,
                                      const Ipp32f*  pSrc2, int src2Stride1, int src2Stride2,
                                            Ipp32f*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
  return ippmAdd_tat_32f(pSrc1,src1Stride0,src1Stride1,src1Stride2,pSrc2,src2Stride1,src2Stride2,pDst,dstStride0,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmAdd_tat(const Ipp64f*  pSrc1, int src1Stride0, int src1Stride1, int src1Stride2,
                                      const Ipp64f*  pSrc2, int src2Stride1, int src2Stride2,
                                            Ipp64f*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
  return ippmAdd_tat_64f(pSrc1,src1Stride0,src1Stride1,src1Stride2,pSrc2,src2Stride1,src2Stride2,pDst,dstStride0,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmAdd_tat_P(const Ipp32f** ppSrc1, int src1RoiShift, int src1Stride0,
                                      const Ipp32f** ppSrc2, int src2RoiShift,
                                            Ipp32f** ppDst,  int dstRoiShift,  int dstStride0,
                                            int width, int height, int count) {
  return ippmAdd_tat_32f_P(ppSrc1,src1RoiShift,src1Stride0,ppSrc2,src2RoiShift,ppDst,dstRoiShift,dstStride0,width,height,count);
}
inline IppStatus ippmAdd_tat_P(const Ipp64f** ppSrc1, int src1RoiShift, int src1Stride0,
                                      const Ipp64f** ppSrc2, int src2RoiShift,
                                            Ipp64f** ppDst,  int dstRoiShift,  int dstStride0,
                                            int width, int height, int count) {
  return ippmAdd_tat_64f_P(ppSrc1,src1RoiShift,src1Stride0,ppSrc2,src2RoiShift,ppDst,dstRoiShift,dstStride0,width,height,count);
}
inline IppStatus ippmAdd_tat_L(const Ipp32f** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                      const Ipp32f*  pSrc2,  int src2Stride1,  int src2Stride2,
                                            Ipp32f** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
  return ippmAdd_tat_32f_L(ppSrc1,src1RoiShift,src1Stride1,src1Stride2,pSrc2,src2Stride1,src2Stride2,ppDst,dstRoiShift,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmAdd_tat_L(const Ipp64f** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                      const Ipp64f*  pSrc2,  int src2Stride1,  int src2Stride2,
                                            Ipp64f** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
  return ippmAdd_tat_64f_L(ppSrc1,src1RoiShift,src1Stride1,src1Stride2,pSrc2,src2Stride1,src2Stride2,ppDst,dstRoiShift,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmAdd_mama(const Ipp32f*  pSrc1, int src1Stride0, int src1Stride1, int src1Stride2,
                                      const Ipp32f*  pSrc2, int src2Stride0, int src2Stride1, int src2Stride2,
                                            Ipp32f*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
  return ippmAdd_mama_32f(pSrc1,src1Stride0,src1Stride1,src1Stride2,pSrc2,src2Stride0,src2Stride1,src2Stride2,pDst,dstStride0,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmAdd_mama(const Ipp64f*  pSrc1, int src1Stride0, int src1Stride1, int src1Stride2,
                                      const Ipp64f*  pSrc2, int src2Stride0, int src2Stride1, int src2Stride2,
                                            Ipp64f*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
  return ippmAdd_mama_64f(pSrc1,src1Stride0,src1Stride1,src1Stride2,pSrc2,src2Stride0,src2Stride1,src2Stride2,pDst,dstStride0,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmAdd_mama_P(const Ipp32f** ppSrc1, int src1RoiShift, int src1Stride0,
                                      const Ipp32f** ppSrc2, int src2RoiShift, int src2Stride0,
                                            Ipp32f** ppDst,  int dstRoiShift,  int dstStride0,
                                            int width, int height, int count) {
  return ippmAdd_mama_32f_P(ppSrc1,src1RoiShift,src1Stride0,ppSrc2,src2RoiShift,src2Stride0,ppDst,dstRoiShift,dstStride0,width,height,count);
}
inline IppStatus ippmAdd_mama_P(const Ipp64f** ppSrc1, int src1RoiShift, int src1Stride0,
                                      const Ipp64f** ppSrc2, int src2RoiShift, int src2Stride0,
                                            Ipp64f** ppDst,  int dstRoiShift,  int dstStride0,
                                            int width, int height, int count) {
  return ippmAdd_mama_64f_P(ppSrc1,src1RoiShift,src1Stride0,ppSrc2,src2RoiShift,src2Stride0,ppDst,dstRoiShift,dstStride0,width,height,count);
}
inline IppStatus ippmAdd_mama_L(const Ipp32f** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                      const Ipp32f** ppSrc2, int src2RoiShift, int src2Stride1, int src2Stride2,
                                            Ipp32f** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
  return ippmAdd_mama_32f_L(ppSrc1,src1RoiShift,src1Stride1,src1Stride2,ppSrc2,src2RoiShift,src2Stride1,src2Stride2,ppDst,dstRoiShift,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmAdd_mama_L(const Ipp64f** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                      const Ipp64f** ppSrc2, int src2RoiShift, int src2Stride1, int src2Stride2,
                                            Ipp64f** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
  return ippmAdd_mama_64f_L(ppSrc1,src1RoiShift,src1Stride1,src1Stride2,ppSrc2,src2RoiShift,src2Stride1,src2Stride2,ppDst,dstRoiShift,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmAdd_tama(const Ipp32f*  pSrc1, int src1Stride0, int src1Stride1, int src1Stride2,
                                      const Ipp32f*  pSrc2, int src2Stride0, int src2Stride1, int src2Stride2,
                                            Ipp32f*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
  return ippmAdd_tama_32f(pSrc1,src1Stride0,src1Stride1,src1Stride2,pSrc2,src2Stride0,src2Stride1,src2Stride2,pDst,dstStride0,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmAdd_tama(const Ipp64f*  pSrc1, int src1Stride0, int src1Stride1, int src1Stride2,
                                      const Ipp64f*  pSrc2, int src2Stride0, int src2Stride1, int src2Stride2,
                                            Ipp64f*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
  return ippmAdd_tama_64f(pSrc1,src1Stride0,src1Stride1,src1Stride2,pSrc2,src2Stride0,src2Stride1,src2Stride2,pDst,dstStride0,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmAdd_tama_P(const Ipp32f** ppSrc1, int src1RoiShift, int src1Stride0,
                                      const Ipp32f** ppSrc2, int src2RoiShift, int src2Stride0,
                                            Ipp32f** ppDst,  int dstRoiShift,  int dstStride0,
                                            int width, int height, int count) {
  return ippmAdd_tama_32f_P(ppSrc1,src1RoiShift,src1Stride0,ppSrc2,src2RoiShift,src2Stride0,ppDst,dstRoiShift,dstStride0,width,height,count);
}
inline IppStatus ippmAdd_tama_P(const Ipp64f** ppSrc1, int src1RoiShift, int src1Stride0,
                                      const Ipp64f** ppSrc2, int src2RoiShift, int src2Stride0,
                                            Ipp64f** ppDst,  int dstRoiShift,  int dstStride0,
                                            int width, int height, int count) {
  return ippmAdd_tama_64f_P(ppSrc1,src1RoiShift,src1Stride0,ppSrc2,src2RoiShift,src2Stride0,ppDst,dstRoiShift,dstStride0,width,height,count);
}
inline IppStatus ippmAdd_tama_L(const Ipp32f** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                      const Ipp32f** ppSrc2, int src2RoiShift, int src2Stride1, int src2Stride2,
                                            Ipp32f** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
  return ippmAdd_tama_32f_L(ppSrc1,src1RoiShift,src1Stride1,src1Stride2,ppSrc2,src2RoiShift,src2Stride1,src2Stride2,ppDst,dstRoiShift,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmAdd_tama_L(const Ipp64f** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                      const Ipp64f** ppSrc2, int src2RoiShift, int src2Stride1, int src2Stride2,
                                            Ipp64f** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
  return ippmAdd_tama_64f_L(ppSrc1,src1RoiShift,src1Stride1,src1Stride2,ppSrc2,src2RoiShift,src2Stride1,src2Stride2,ppDst,dstRoiShift,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmAdd_tata(const Ipp32f*  pSrc1, int src1Stride0, int src1Stride1, int src1Stride2,
                                      const Ipp32f*  pSrc2, int src2Stride0, int src2Stride1, int src2Stride2,
                                            Ipp32f*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
  return ippmAdd_tata_32f(pSrc1,src1Stride0,src1Stride1,src1Stride2,pSrc2,src2Stride0,src2Stride1,src2Stride2,pDst,dstStride0,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmAdd_tata(const Ipp64f*  pSrc1, int src1Stride0, int src1Stride1, int src1Stride2,
                                      const Ipp64f*  pSrc2, int src2Stride0, int src2Stride1, int src2Stride2,
                                            Ipp64f*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
  return ippmAdd_tata_64f(pSrc1,src1Stride0,src1Stride1,src1Stride2,pSrc2,src2Stride0,src2Stride1,src2Stride2,pDst,dstStride0,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmAdd_tata_P(const Ipp32f** ppSrc1, int src1RoiShift, int src1Stride0,
                                      const Ipp32f** ppSrc2, int src2RoiShift, int src2Stride0,
                                            Ipp32f** ppDst,  int dstRoiShift,  int dstStride0,
                                            int width, int height, int count) {
  return ippmAdd_tata_32f_P(ppSrc1,src1RoiShift,src1Stride0,ppSrc2,src2RoiShift,src2Stride0,ppDst,dstRoiShift,dstStride0,width,height,count);
}
inline IppStatus ippmAdd_tata_P(const Ipp64f** ppSrc1, int src1RoiShift, int src1Stride0,
                                      const Ipp64f** ppSrc2, int src2RoiShift, int src2Stride0,
                                            Ipp64f** ppDst,  int dstRoiShift,  int dstStride0,
                                            int width, int height, int count) {
  return ippmAdd_tata_64f_P(ppSrc1,src1RoiShift,src1Stride0,ppSrc2,src2RoiShift,src2Stride0,ppDst,dstRoiShift,dstStride0,width,height,count);
}
inline IppStatus ippmAdd_tata_L(const Ipp32f** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                      const Ipp32f** ppSrc2, int src2RoiShift, int src2Stride1, int src2Stride2,
                                            Ipp32f** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
  return ippmAdd_tata_32f_L(ppSrc1,src1RoiShift,src1Stride1,src1Stride2,ppSrc2,src2RoiShift,src2Stride1,src2Stride2,ppDst,dstRoiShift,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmAdd_tata_L(const Ipp64f** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                      const Ipp64f** ppSrc2, int src2RoiShift, int src2Stride1, int src2Stride2,
                                            Ipp64f** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
  return ippmAdd_tata_64f_L(ppSrc1,src1RoiShift,src1Stride1,src1Stride2,ppSrc2,src2RoiShift,src2Stride1,src2Stride2,ppDst,dstRoiShift,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmSub_mm(const Ipp32f*  pSrc1, int src1Stride1, int src1Stride2,
                                      const Ipp32f*  pSrc2, int src2Stride1, int src2Stride2,
                                            Ipp32f*  pDst,  int dstStride1,  int dstStride2,
                                            int width, int height) {
  return ippmSub_mm_32f(pSrc1,src1Stride1,src1Stride2,pSrc2,src2Stride1,src2Stride2,pDst,dstStride1,dstStride2,width,height);
}
inline IppStatus ippmSub_mm(const Ipp64f*  pSrc1, int src1Stride1, int src1Stride2,
                                      const Ipp64f*  pSrc2, int src2Stride1, int src2Stride2,
                                            Ipp64f*  pDst,  int dstStride1,  int dstStride2,
                                            int width, int height) {
  return ippmSub_mm_64f(pSrc1,src1Stride1,src1Stride2,pSrc2,src2Stride1,src2Stride2,pDst,dstStride1,dstStride2,width,height);
}
inline IppStatus ippmSub_mm_P(const Ipp32f** ppSrc1, int src1RoiShift,
                                      const Ipp32f** ppSrc2, int src2RoiShift,
                                            Ipp32f** ppDst,  int dstRoiShift,
                                            int width, int height) {
  return ippmSub_mm_32f_P(ppSrc1,src1RoiShift,ppSrc2,src2RoiShift,ppDst,dstRoiShift,width,height);
}
inline IppStatus ippmSub_mm_P(const Ipp64f** ppSrc1, int src1RoiShift,
                                      const Ipp64f** ppSrc2, int src2RoiShift,
                                            Ipp64f** ppDst,  int dstRoiShift,
                                            int width, int height) {
  return ippmSub_mm_64f_P(ppSrc1,src1RoiShift,ppSrc2,src2RoiShift,ppDst,dstRoiShift,width,height);
}
inline IppStatus ippmSub_tm(const Ipp32f*  pSrc1, int src1Stride1, int src1Stride2,
                                      const Ipp32f*  pSrc2, int src2Stride1, int src2Stride2,
                                            Ipp32f*  pDst,  int dstStride1,  int dstStride2,
                                            int width, int height) {
  return ippmSub_tm_32f(pSrc1,src1Stride1,src1Stride2,pSrc2,src2Stride1,src2Stride2,pDst,dstStride1,dstStride2,width,height);
}
inline IppStatus ippmSub_tm(const Ipp64f*  pSrc1, int src1Stride1, int src1Stride2,
                                      const Ipp64f*  pSrc2, int src2Stride1, int src2Stride2,
                                            Ipp64f*  pDst,  int dstStride1,  int dstStride2,
                                            int width, int height) {
  return ippmSub_tm_64f(pSrc1,src1Stride1,src1Stride2,pSrc2,src2Stride1,src2Stride2,pDst,dstStride1,dstStride2,width,height);
}
inline IppStatus ippmSub_tm_P(const Ipp32f** ppSrc1, int src1RoiShift,
                                      const Ipp32f** ppSrc2, int src2RoiShift,
                                            Ipp32f** ppDst,  int dstRoiShift,
                                            int width, int height) {
  return ippmSub_tm_32f_P(ppSrc1,src1RoiShift,ppSrc2,src2RoiShift,ppDst,dstRoiShift,width,height);
}
inline IppStatus ippmSub_tm_P(const Ipp64f** ppSrc1, int src1RoiShift,
                                      const Ipp64f** ppSrc2, int src2RoiShift,
                                            Ipp64f** ppDst,  int dstRoiShift,
                                            int width, int height) {
  return ippmSub_tm_64f_P(ppSrc1,src1RoiShift,ppSrc2,src2RoiShift,ppDst,dstRoiShift,width,height);
}
inline IppStatus ippmSub_mt(const Ipp32f*  pSrc1, int src1Stride1, int src1Stride2,
                                      const Ipp32f*  pSrc2, int src2Stride1, int src2Stride2,
                                            Ipp32f*  pDst,  int dstStride1,  int dstStride2,
                                            int width, int height) {
  return ippmSub_mt_32f(pSrc1,src1Stride1,src1Stride2,pSrc2,src2Stride1,src2Stride2,pDst,dstStride1,dstStride2,width,height);
}
inline IppStatus ippmSub_mt(const Ipp64f*  pSrc1, int src1Stride1, int src1Stride2,
                                      const Ipp64f*  pSrc2, int src2Stride1, int src2Stride2,
                                            Ipp64f*  pDst,  int dstStride1,  int dstStride2,
                                            int width, int height) {
  return ippmSub_mt_64f(pSrc1,src1Stride1,src1Stride2,pSrc2,src2Stride1,src2Stride2,pDst,dstStride1,dstStride2,width,height);
}
inline IppStatus ippmSub_mt_P(const Ipp32f** ppSrc1, int src1RoiShift,
                                      const Ipp32f** ppSrc2, int src2RoiShift,
                                            Ipp32f** ppDst,  int dstRoiShift,
                                            int width, int height) {
  return ippmSub_mt_32f_P(ppSrc1,src1RoiShift,ppSrc2,src2RoiShift,ppDst,dstRoiShift,width,height);
}
inline IppStatus ippmSub_mt_P(const Ipp64f** ppSrc1, int src1RoiShift,
                                      const Ipp64f** ppSrc2, int src2RoiShift,
                                            Ipp64f** ppDst,  int dstRoiShift,
                                            int width, int height) {
  return ippmSub_mt_64f_P(ppSrc1,src1RoiShift,ppSrc2,src2RoiShift,ppDst,dstRoiShift,width,height);
}
inline IppStatus ippmSub_tt(const Ipp32f*  pSrc1, int src1Stride1, int src1Stride2,
                                      const Ipp32f*  pSrc2, int src2Stride1, int src2Stride2,
                                            Ipp32f*  pDst,  int dstStride1,  int dstStride2,
                                            int width, int height) {
  return ippmSub_tt_32f(pSrc1,src1Stride1,src1Stride2,pSrc2,src2Stride1,src2Stride2,pDst,dstStride1,dstStride2,width,height);
}
inline IppStatus ippmSub_tt(const Ipp64f*  pSrc1, int src1Stride1, int src1Stride2,
                                      const Ipp64f*  pSrc2, int src2Stride1, int src2Stride2,
                                            Ipp64f*  pDst,  int dstStride1,  int dstStride2,
                                            int width, int height) {
  return ippmSub_tt_64f(pSrc1,src1Stride1,src1Stride2,pSrc2,src2Stride1,src2Stride2,pDst,dstStride1,dstStride2,width,height);
}
inline IppStatus ippmSub_tt_P(const Ipp32f** ppSrc1, int src1RoiShift,
                                      const Ipp32f** ppSrc2, int src2RoiShift,
                                            Ipp32f** ppDst,  int dstRoiShift,
                                            int width, int height) {
  return ippmSub_tt_32f_P(ppSrc1,src1RoiShift,ppSrc2,src2RoiShift,ppDst,dstRoiShift,width,height);
}
inline IppStatus ippmSub_tt_P(const Ipp64f** ppSrc1, int src1RoiShift,
                                      const Ipp64f** ppSrc2, int src2RoiShift,
                                            Ipp64f** ppDst,  int dstRoiShift,
                                            int width, int height) {
  return ippmSub_tt_64f_P(ppSrc1,src1RoiShift,ppSrc2,src2RoiShift,ppDst,dstRoiShift,width,height);
}
inline IppStatus ippmSub_mma(const Ipp32f*  pSrc1, int src1Stride1, int src1Stride2,
                                      const Ipp32f*  pSrc2, int src2Stride0, int src2Stride1, int src2Stride2,
                                            Ipp32f*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
  return ippmSub_mma_32f(pSrc1,src1Stride1,src1Stride2,pSrc2,src2Stride0,src2Stride1,src2Stride2,pDst,dstStride0,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmSub_mma(const Ipp64f*  pSrc1, int src1Stride1, int src1Stride2,
                                      const Ipp64f*  pSrc2, int src2Stride0, int src2Stride1, int src2Stride2,
                                            Ipp64f*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
  return ippmSub_mma_64f(pSrc1,src1Stride1,src1Stride2,pSrc2,src2Stride0,src2Stride1,src2Stride2,pDst,dstStride0,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmSub_mma_P(const Ipp32f** ppSrc1, int src1RoiShift,
                                      const Ipp32f** ppSrc2, int src2RoiShift, int src2Stride0,
                                            Ipp32f** ppDst,  int dstRoiShift,  int dstStride0,
                                            int width, int height, int count) {
  return ippmSub_mma_32f_P(ppSrc1,src1RoiShift,ppSrc2,src2RoiShift,src2Stride0,ppDst,dstRoiShift,dstStride0,width,height,count);
}
inline IppStatus ippmSub_mma_P(const Ipp64f** ppSrc1, int src1RoiShift,
                                      const Ipp64f** ppSrc2, int src2RoiShift, int src2Stride0,
                                            Ipp64f** ppDst,  int dstRoiShift,  int dstStride0,
                                            int width, int height, int count) {
  return ippmSub_mma_64f_P(ppSrc1,src1RoiShift,ppSrc2,src2RoiShift,src2Stride0,ppDst,dstRoiShift,dstStride0,width,height,count);
}
inline IppStatus ippmSub_mma_L(const Ipp32f*  pSrc1,  int src1Stride1,  int src1Stride2,
                                      const Ipp32f** ppSrc2, int src2RoiShift, int src2Stride1, int src2Stride2,
                                            Ipp32f** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
  return ippmSub_mma_32f_L(pSrc1,src1Stride1,src1Stride2,ppSrc2,src2RoiShift,src2Stride1,src2Stride2,ppDst,dstRoiShift,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmSub_mma_L(const Ipp64f*  pSrc1,  int src1Stride1,  int src1Stride2,
                                      const Ipp64f** ppSrc2, int src2RoiShift, int src2Stride1, int src2Stride2,
                                            Ipp64f** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
  return ippmSub_mma_64f_L(pSrc1,src1Stride1,src1Stride2,ppSrc2,src2RoiShift,src2Stride1,src2Stride2,ppDst,dstRoiShift,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmSub_tma(const Ipp32f*  pSrc1, int src1Stride1, int src1Stride2,
                                      const Ipp32f*  pSrc2, int src2Stride0, int src2Stride1, int src2Stride2,
                                            Ipp32f*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
  return ippmSub_tma_32f(pSrc1,src1Stride1,src1Stride2,pSrc2,src2Stride0,src2Stride1,src2Stride2,pDst,dstStride0,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmSub_tma(const Ipp64f*  pSrc1, int src1Stride1, int src1Stride2,
                                      const Ipp64f*  pSrc2, int src2Stride0, int src2Stride1, int src2Stride2,
                                            Ipp64f*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
  return ippmSub_tma_64f(pSrc1,src1Stride1,src1Stride2,pSrc2,src2Stride0,src2Stride1,src2Stride2,pDst,dstStride0,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmSub_tma_P(const Ipp32f** ppSrc1, int src1RoiShift,
                                      const Ipp32f** ppSrc2, int src2RoiShift, int src2Stride0,
                                            Ipp32f** ppDst,  int dstRoiShift,  int dstStride0,
                                            int width, int height, int count) {
  return ippmSub_tma_32f_P(ppSrc1,src1RoiShift,ppSrc2,src2RoiShift,src2Stride0,ppDst,dstRoiShift,dstStride0,width,height,count);
}
inline IppStatus ippmSub_tma_P(const Ipp64f** ppSrc1, int src1RoiShift,
                                      const Ipp64f** ppSrc2, int src2RoiShift, int src2Stride0,
                                            Ipp64f** ppDst,  int dstRoiShift,  int dstStride0,
                                            int width, int height, int count) {
  return ippmSub_tma_64f_P(ppSrc1,src1RoiShift,ppSrc2,src2RoiShift,src2Stride0,ppDst,dstRoiShift,dstStride0,width,height,count);
}
inline IppStatus ippmSub_tma_L(const Ipp32f*  pSrc1,  int src1Stride1,  int src1Stride2,
                                      const Ipp32f** ppSrc2, int src2RoiShift, int src2Stride1, int src2Stride2,
                                            Ipp32f** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
  return ippmSub_tma_32f_L(pSrc1,src1Stride1,src1Stride2,ppSrc2,src2RoiShift,src2Stride1,src2Stride2,ppDst,dstRoiShift,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmSub_tma_L(const Ipp64f*  pSrc1,  int src1Stride1,  int src1Stride2,
                                      const Ipp64f** ppSrc2, int src2RoiShift, int src2Stride1, int src2Stride2,
                                            Ipp64f** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
  return ippmSub_tma_64f_L(pSrc1,src1Stride1,src1Stride2,ppSrc2,src2RoiShift,src2Stride1,src2Stride2,ppDst,dstRoiShift,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmSub_mta(const Ipp32f*  pSrc1, int src1Stride1, int src1Stride2,
                                      const Ipp32f*  pSrc2, int src2Stride0, int src2Stride1, int src2Stride2,
                                            Ipp32f*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
  return ippmSub_mta_32f(pSrc1,src1Stride1,src1Stride2,pSrc2,src2Stride0,src2Stride1,src2Stride2,pDst,dstStride0,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmSub_mta(const Ipp64f*  pSrc1, int src1Stride1, int src1Stride2,
                                      const Ipp64f*  pSrc2, int src2Stride0, int src2Stride1, int src2Stride2,
                                            Ipp64f*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
  return ippmSub_mta_64f(pSrc1,src1Stride1,src1Stride2,pSrc2,src2Stride0,src2Stride1,src2Stride2,pDst,dstStride0,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmSub_mta_P(const Ipp32f** ppSrc1, int src1RoiShift,
                                      const Ipp32f** ppSrc2, int src2RoiShift, int src2Stride0,
                                            Ipp32f** ppDst,  int dstRoiShift,  int dstStride0,
                                            int width, int height, int count) {
  return ippmSub_mta_32f_P(ppSrc1,src1RoiShift,ppSrc2,src2RoiShift,src2Stride0,ppDst,dstRoiShift,dstStride0,width,height,count);
}
inline IppStatus ippmSub_mta_P(const Ipp64f** ppSrc1, int src1RoiShift,
                                      const Ipp64f** ppSrc2, int src2RoiShift, int src2Stride0,
                                            Ipp64f** ppDst,  int dstRoiShift,  int dstStride0,
                                            int width, int height, int count) {
  return ippmSub_mta_64f_P(ppSrc1,src1RoiShift,ppSrc2,src2RoiShift,src2Stride0,ppDst,dstRoiShift,dstStride0,width,height,count);
}
inline IppStatus ippmSub_mta_L(const Ipp32f*  pSrc1,  int src1Stride1,  int src1Stride2,
                                      const Ipp32f** ppSrc2, int src2RoiShift, int src2Stride1, int src2Stride2,
                                            Ipp32f** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
  return ippmSub_mta_32f_L(pSrc1,src1Stride1,src1Stride2,ppSrc2,src2RoiShift,src2Stride1,src2Stride2,ppDst,dstRoiShift,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmSub_mta_L(const Ipp64f*  pSrc1,  int src1Stride1,  int src1Stride2,
                                      const Ipp64f** ppSrc2, int src2RoiShift, int src2Stride1, int src2Stride2,
                                            Ipp64f** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
  return ippmSub_mta_64f_L(pSrc1,src1Stride1,src1Stride2,ppSrc2,src2RoiShift,src2Stride1,src2Stride2,ppDst,dstRoiShift,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmSub_tta(const Ipp32f*  pSrc1, int src1Stride1, int src1Stride2,
                                      const Ipp32f*  pSrc2, int src2Stride0, int src2Stride1, int src2Stride2,
                                            Ipp32f*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
  return ippmSub_tta_32f(pSrc1,src1Stride1,src1Stride2,pSrc2,src2Stride0,src2Stride1,src2Stride2,pDst,dstStride0,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmSub_tta(const Ipp64f*  pSrc1, int src1Stride1, int src1Stride2,
                                      const Ipp64f*  pSrc2, int src2Stride0, int src2Stride1, int src2Stride2,
                                            Ipp64f*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
  return ippmSub_tta_64f(pSrc1,src1Stride1,src1Stride2,pSrc2,src2Stride0,src2Stride1,src2Stride2,pDst,dstStride0,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmSub_tta_P(const Ipp32f** ppSrc1, int src1RoiShift,
                                      const Ipp32f** ppSrc2, int src2RoiShift, int src2Stride0,
                                            Ipp32f** ppDst,  int dstRoiShift,  int dstStride0,
                                            int width, int height, int count) {
  return ippmSub_tta_32f_P(ppSrc1,src1RoiShift,ppSrc2,src2RoiShift,src2Stride0,ppDst,dstRoiShift,dstStride0,width,height,count);
}
inline IppStatus ippmSub_tta_P(const Ipp64f** ppSrc1, int src1RoiShift,
                                      const Ipp64f** ppSrc2, int src2RoiShift, int src2Stride0,
                                            Ipp64f** ppDst,  int dstRoiShift,  int dstStride0,
                                            int width, int height, int count) {
  return ippmSub_tta_64f_P(ppSrc1,src1RoiShift,ppSrc2,src2RoiShift,src2Stride0,ppDst,dstRoiShift,dstStride0,width,height,count);
}
inline IppStatus ippmSub_tta_L(const Ipp32f*  pSrc1,  int src1Stride1,  int src1Stride2,
                                      const Ipp32f** ppSrc2, int src2RoiShift, int src2Stride1, int src2Stride2,
                                            Ipp32f** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
  return ippmSub_tta_32f_L(pSrc1,src1Stride1,src1Stride2,ppSrc2,src2RoiShift,src2Stride1,src2Stride2,ppDst,dstRoiShift,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmSub_tta_L(const Ipp64f*  pSrc1,  int src1Stride1,  int src1Stride2,
                                      const Ipp64f** ppSrc2, int src2RoiShift, int src2Stride1, int src2Stride2,
                                            Ipp64f** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
  return ippmSub_tta_64f_L(pSrc1,src1Stride1,src1Stride2,ppSrc2,src2RoiShift,src2Stride1,src2Stride2,ppDst,dstRoiShift,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmSub_mam(const Ipp32f*  pSrc1, int src1Stride0, int src1Stride1, int src1Stride2,
                                      const Ipp32f*  pSrc2, int src2Stride1, int src2Stride2,
                                            Ipp32f*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
  return ippmSub_mam_32f(pSrc1,src1Stride0,src1Stride1,src1Stride2,pSrc2,src2Stride1,src2Stride2,pDst,dstStride0,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmSub_mam(const Ipp64f*  pSrc1, int src1Stride0, int src1Stride1, int src1Stride2,
                                      const Ipp64f*  pSrc2, int src2Stride1, int src2Stride2,
                                            Ipp64f*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
  return ippmSub_mam_64f(pSrc1,src1Stride0,src1Stride1,src1Stride2,pSrc2,src2Stride1,src2Stride2,pDst,dstStride0,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmSub_mam_P(const Ipp32f** ppSrc1, int src1RoiShift, int src1Stride0,
                                      const Ipp32f** ppSrc2, int src2RoiShift,
                                            Ipp32f** ppDst,  int dstRoiShift,  int dstStride0,
                                            int width, int height, int count) {
  return ippmSub_mam_32f_P(ppSrc1,src1RoiShift,src1Stride0,ppSrc2,src2RoiShift,ppDst,dstRoiShift,dstStride0,width,height,count);
}
inline IppStatus ippmSub_mam_P(const Ipp64f** ppSrc1, int src1RoiShift, int src1Stride0,
                                      const Ipp64f** ppSrc2, int src2RoiShift,
                                            Ipp64f** ppDst,  int dstRoiShift,  int dstStride0,
                                            int width, int height, int count) {
  return ippmSub_mam_64f_P(ppSrc1,src1RoiShift,src1Stride0,ppSrc2,src2RoiShift,ppDst,dstRoiShift,dstStride0,width,height,count);
}
inline IppStatus ippmSub_mam_L(const Ipp32f** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                      const Ipp32f*  pSrc2,  int src2Stride1,  int src2Stride2,
                                            Ipp32f** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
  return ippmSub_mam_32f_L(ppSrc1,src1RoiShift,src1Stride1,src1Stride2,pSrc2,src2Stride1,src2Stride2,ppDst,dstRoiShift,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmSub_mam_L(const Ipp64f** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                      const Ipp64f*  pSrc2,  int src2Stride1,  int src2Stride2,
                                            Ipp64f** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
  return ippmSub_mam_64f_L(ppSrc1,src1RoiShift,src1Stride1,src1Stride2,pSrc2,src2Stride1,src2Stride2,ppDst,dstRoiShift,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmSub_tam(const Ipp32f*  pSrc1, int src1Stride0, int src1Stride1, int src1Stride2,
                                      const Ipp32f*  pSrc2, int src2Stride1, int src2Stride2,
                                            Ipp32f*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
  return ippmSub_tam_32f(pSrc1,src1Stride0,src1Stride1,src1Stride2,pSrc2,src2Stride1,src2Stride2,pDst,dstStride0,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmSub_tam(const Ipp64f*  pSrc1, int src1Stride0, int src1Stride1, int src1Stride2,
                                      const Ipp64f*  pSrc2, int src2Stride1, int src2Stride2,
                                            Ipp64f*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
  return ippmSub_tam_64f(pSrc1,src1Stride0,src1Stride1,src1Stride2,pSrc2,src2Stride1,src2Stride2,pDst,dstStride0,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmSub_tam_P(const Ipp32f** ppSrc1, int src1RoiShift, int src1Stride0,
                                      const Ipp32f** ppSrc2, int src2RoiShift,
                                            Ipp32f** ppDst,  int dstRoiShift,  int dstStride0,
                                            int width, int height, int count) {
  return ippmSub_tam_32f_P(ppSrc1,src1RoiShift,src1Stride0,ppSrc2,src2RoiShift,ppDst,dstRoiShift,dstStride0,width,height,count);
}
inline IppStatus ippmSub_tam_P(const Ipp64f** ppSrc1, int src1RoiShift, int src1Stride0,
                                      const Ipp64f** ppSrc2, int src2RoiShift,
                                            Ipp64f** ppDst,  int dstRoiShift,  int dstStride0,
                                            int width, int height, int count) {
  return ippmSub_tam_64f_P(ppSrc1,src1RoiShift,src1Stride0,ppSrc2,src2RoiShift,ppDst,dstRoiShift,dstStride0,width,height,count);
}
inline IppStatus ippmSub_tam_L(const Ipp32f** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                      const Ipp32f*  pSrc2,  int src2Stride1,  int src2Stride2,
                                            Ipp32f** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
  return ippmSub_tam_32f_L(ppSrc1,src1RoiShift,src1Stride1,src1Stride2,pSrc2,src2Stride1,src2Stride2,ppDst,dstRoiShift,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmSub_tam_L(const Ipp64f** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                      const Ipp64f*  pSrc2,  int src2Stride1,  int src2Stride2,
                                            Ipp64f** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
  return ippmSub_tam_64f_L(ppSrc1,src1RoiShift,src1Stride1,src1Stride2,pSrc2,src2Stride1,src2Stride2,ppDst,dstRoiShift,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmSub_mat(const Ipp32f*  pSrc1, int src1Stride0, int src1Stride1, int src1Stride2,
                                      const Ipp32f*  pSrc2, int src2Stride1, int src2Stride2,
                                            Ipp32f*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
  return ippmSub_mat_32f(pSrc1,src1Stride0,src1Stride1,src1Stride2,pSrc2,src2Stride1,src2Stride2,pDst,dstStride0,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmSub_mat(const Ipp64f*  pSrc1, int src1Stride0, int src1Stride1, int src1Stride2,
                                      const Ipp64f*  pSrc2, int src2Stride1, int src2Stride2,
                                            Ipp64f*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
  return ippmSub_mat_64f(pSrc1,src1Stride0,src1Stride1,src1Stride2,pSrc2,src2Stride1,src2Stride2,pDst,dstStride0,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmSub_mat_P(const Ipp32f** ppSrc1, int src1RoiShift, int src1Stride0,
                                      const Ipp32f** ppSrc2, int src2RoiShift,
                                            Ipp32f** ppDst,  int dstRoiShift,  int dstStride0,
                                            int width, int height, int count) {
  return ippmSub_mat_32f_P(ppSrc1,src1RoiShift,src1Stride0,ppSrc2,src2RoiShift,ppDst,dstRoiShift,dstStride0,width,height,count);
}
inline IppStatus ippmSub_mat_P(const Ipp64f** ppSrc1, int src1RoiShift, int src1Stride0,
                                      const Ipp64f** ppSrc2, int src2RoiShift,
                                            Ipp64f** ppDst,  int dstRoiShift,  int dstStride0,
                                            int width, int height, int count) {
  return ippmSub_mat_64f_P(ppSrc1,src1RoiShift,src1Stride0,ppSrc2,src2RoiShift,ppDst,dstRoiShift,dstStride0,width,height,count);
}
inline IppStatus ippmSub_mat_L(const Ipp32f** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                      const Ipp32f*  pSrc2,  int src2Stride1,  int src2Stride2,
                                            Ipp32f** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
  return ippmSub_mat_32f_L(ppSrc1,src1RoiShift,src1Stride1,src1Stride2,pSrc2,src2Stride1,src2Stride2,ppDst,dstRoiShift,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmSub_mat_L(const Ipp64f** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                      const Ipp64f*  pSrc2,  int src2Stride1,  int src2Stride2,
                                            Ipp64f** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
  return ippmSub_mat_64f_L(ppSrc1,src1RoiShift,src1Stride1,src1Stride2,pSrc2,src2Stride1,src2Stride2,ppDst,dstRoiShift,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmSub_tat(const Ipp32f*  pSrc1, int src1Stride0, int src1Stride1, int src1Stride2,
                                      const Ipp32f*  pSrc2, int src2Stride1, int src2Stride2,
                                            Ipp32f*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
  return ippmSub_tat_32f(pSrc1,src1Stride0,src1Stride1,src1Stride2,pSrc2,src2Stride1,src2Stride2,pDst,dstStride0,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmSub_tat(const Ipp64f*  pSrc1, int src1Stride0, int src1Stride1, int src1Stride2,
                                      const Ipp64f*  pSrc2, int src2Stride1, int src2Stride2,
                                            Ipp64f*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
  return ippmSub_tat_64f(pSrc1,src1Stride0,src1Stride1,src1Stride2,pSrc2,src2Stride1,src2Stride2,pDst,dstStride0,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmSub_tat_P(const Ipp32f** ppSrc1, int src1RoiShift, int src1Stride0,
                                      const Ipp32f** ppSrc2, int src2RoiShift,
                                            Ipp32f** ppDst,  int dstRoiShift,  int dstStride0,
                                            int width, int height, int count) {
  return ippmSub_tat_32f_P(ppSrc1,src1RoiShift,src1Stride0,ppSrc2,src2RoiShift,ppDst,dstRoiShift,dstStride0,width,height,count);
}
inline IppStatus ippmSub_tat_P(const Ipp64f** ppSrc1, int src1RoiShift, int src1Stride0,
                                      const Ipp64f** ppSrc2, int src2RoiShift,
                                            Ipp64f** ppDst,  int dstRoiShift,  int dstStride0,
                                            int width, int height, int count) {
  return ippmSub_tat_64f_P(ppSrc1,src1RoiShift,src1Stride0,ppSrc2,src2RoiShift,ppDst,dstRoiShift,dstStride0,width,height,count);
}
inline IppStatus ippmSub_tat_L(const Ipp32f** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                      const Ipp32f*  pSrc2,  int src2Stride1,  int src2Stride2,
                                            Ipp32f** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
  return ippmSub_tat_32f_L(ppSrc1,src1RoiShift,src1Stride1,src1Stride2,pSrc2,src2Stride1,src2Stride2,ppDst,dstRoiShift,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmSub_tat_L(const Ipp64f** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                      const Ipp64f*  pSrc2,  int src2Stride1,  int src2Stride2,
                                            Ipp64f** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
  return ippmSub_tat_64f_L(ppSrc1,src1RoiShift,src1Stride1,src1Stride2,pSrc2,src2Stride1,src2Stride2,ppDst,dstRoiShift,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmSub_mama(const Ipp32f*  pSrc1, int src1Stride0, int src1Stride1, int src1Stride2,
                                      const Ipp32f*  pSrc2, int src2Stride0, int src2Stride1, int src2Stride2,
                                            Ipp32f*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
  return ippmSub_mama_32f(pSrc1,src1Stride0,src1Stride1,src1Stride2,pSrc2,src2Stride0,src2Stride1,src2Stride2,pDst,dstStride0,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmSub_mama(const Ipp64f*  pSrc1, int src1Stride0, int src1Stride1, int src1Stride2,
                                      const Ipp64f*  pSrc2, int src2Stride0, int src2Stride1, int src2Stride2,
                                            Ipp64f*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
  return ippmSub_mama_64f(pSrc1,src1Stride0,src1Stride1,src1Stride2,pSrc2,src2Stride0,src2Stride1,src2Stride2,pDst,dstStride0,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmSub_mama_P(const Ipp32f** ppSrc1, int src1RoiShift, int src1Stride0,
                                      const Ipp32f** ppSrc2, int src2RoiShift, int src2Stride0,
                                            Ipp32f** ppDst,  int dstRoiShift,  int dstStride0,
                                            int width, int height, int count) {
  return ippmSub_mama_32f_P(ppSrc1,src1RoiShift,src1Stride0,ppSrc2,src2RoiShift,src2Stride0,ppDst,dstRoiShift,dstStride0,width,height,count);
}
inline IppStatus ippmSub_mama_P(const Ipp64f** ppSrc1, int src1RoiShift, int src1Stride0,
                                      const Ipp64f** ppSrc2, int src2RoiShift, int src2Stride0,
                                            Ipp64f** ppDst,  int dstRoiShift,  int dstStride0,
                                            int width, int height, int count) {
  return ippmSub_mama_64f_P(ppSrc1,src1RoiShift,src1Stride0,ppSrc2,src2RoiShift,src2Stride0,ppDst,dstRoiShift,dstStride0,width,height,count);
}
inline IppStatus ippmSub_mama_L(const Ipp32f** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                      const Ipp32f** ppSrc2, int src2RoiShift, int src2Stride1, int src2Stride2,
                                            Ipp32f** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
  return ippmSub_mama_32f_L(ppSrc1,src1RoiShift,src1Stride1,src1Stride2,ppSrc2,src2RoiShift,src2Stride1,src2Stride2,ppDst,dstRoiShift,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmSub_mama_L(const Ipp64f** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                      const Ipp64f** ppSrc2, int src2RoiShift, int src2Stride1, int src2Stride2,
                                            Ipp64f** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
  return ippmSub_mama_64f_L(ppSrc1,src1RoiShift,src1Stride1,src1Stride2,ppSrc2,src2RoiShift,src2Stride1,src2Stride2,ppDst,dstRoiShift,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmSub_tama(const Ipp32f*  pSrc1, int src1Stride0, int src1Stride1, int src1Stride2,
                                      const Ipp32f*  pSrc2, int src2Stride0, int src2Stride1, int src2Stride2,
                                            Ipp32f*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
  return ippmSub_tama_32f(pSrc1,src1Stride0,src1Stride1,src1Stride2,pSrc2,src2Stride0,src2Stride1,src2Stride2,pDst,dstStride0,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmSub_tama(const Ipp64f*  pSrc1, int src1Stride0, int src1Stride1, int src1Stride2,
                                      const Ipp64f*  pSrc2, int src2Stride0, int src2Stride1, int src2Stride2,
                                            Ipp64f*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
  return ippmSub_tama_64f(pSrc1,src1Stride0,src1Stride1,src1Stride2,pSrc2,src2Stride0,src2Stride1,src2Stride2,pDst,dstStride0,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmSub_tama_P(const Ipp32f** ppSrc1, int src1RoiShift, int src1Stride0,
                                      const Ipp32f** ppSrc2, int src2RoiShift, int src2Stride0,
                                            Ipp32f** ppDst,  int dstRoiShift,  int dstStride0,
                                            int width, int height, int count) {
  return ippmSub_tama_32f_P(ppSrc1,src1RoiShift,src1Stride0,ppSrc2,src2RoiShift,src2Stride0,ppDst,dstRoiShift,dstStride0,width,height,count);
}
inline IppStatus ippmSub_tama_P(const Ipp64f** ppSrc1, int src1RoiShift, int src1Stride0,
                                      const Ipp64f** ppSrc2, int src2RoiShift, int src2Stride0,
                                            Ipp64f** ppDst,  int dstRoiShift,  int dstStride0,
                                            int width, int height, int count) {
  return ippmSub_tama_64f_P(ppSrc1,src1RoiShift,src1Stride0,ppSrc2,src2RoiShift,src2Stride0,ppDst,dstRoiShift,dstStride0,width,height,count);
}
inline IppStatus ippmSub_tama_L(const Ipp32f** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                      const Ipp32f** ppSrc2, int src2RoiShift, int src2Stride1, int src2Stride2,
                                            Ipp32f** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
  return ippmSub_tama_32f_L(ppSrc1,src1RoiShift,src1Stride1,src1Stride2,ppSrc2,src2RoiShift,src2Stride1,src2Stride2,ppDst,dstRoiShift,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmSub_tama_L(const Ipp64f** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                      const Ipp64f** ppSrc2, int src2RoiShift, int src2Stride1, int src2Stride2,
                                            Ipp64f** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
  return ippmSub_tama_64f_L(ppSrc1,src1RoiShift,src1Stride1,src1Stride2,ppSrc2,src2RoiShift,src2Stride1,src2Stride2,ppDst,dstRoiShift,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmSub_mata(const Ipp32f*  pSrc1, int src1Stride0, int src1Stride1, int src1Stride2,
                                      const Ipp32f*  pSrc2, int src2Stride0, int src2Stride1, int src2Stride2,
                                            Ipp32f*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
  return ippmSub_mata_32f(pSrc1,src1Stride0,src1Stride1,src1Stride2,pSrc2,src2Stride0,src2Stride1,src2Stride2,pDst,dstStride0,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmSub_mata(const Ipp64f*  pSrc1, int src1Stride0, int src1Stride1, int src1Stride2,
                                      const Ipp64f*  pSrc2, int src2Stride0, int src2Stride1, int src2Stride2,
                                            Ipp64f*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
  return ippmSub_mata_64f(pSrc1,src1Stride0,src1Stride1,src1Stride2,pSrc2,src2Stride0,src2Stride1,src2Stride2,pDst,dstStride0,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmSub_mata_P(const Ipp32f** ppSrc1, int src1RoiShift, int src1Stride0,
                                      const Ipp32f** ppSrc2, int src2RoiShift, int src2Stride0,
                                            Ipp32f** ppDst,  int dstRoiShift,  int dstStride0,
                                            int width, int height, int count) {
  return ippmSub_mata_32f_P(ppSrc1,src1RoiShift,src1Stride0,ppSrc2,src2RoiShift,src2Stride0,ppDst,dstRoiShift,dstStride0,width,height,count);
}
inline IppStatus ippmSub_mata_P(const Ipp64f** ppSrc1, int src1RoiShift, int src1Stride0,
                                      const Ipp64f** ppSrc2, int src2RoiShift, int src2Stride0,
                                            Ipp64f** ppDst,  int dstRoiShift,  int dstStride0,
                                            int width, int height, int count) {
  return ippmSub_mata_64f_P(ppSrc1,src1RoiShift,src1Stride0,ppSrc2,src2RoiShift,src2Stride0,ppDst,dstRoiShift,dstStride0,width,height,count);
}
inline IppStatus ippmSub_mata_L(const Ipp32f** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                      const Ipp32f** ppSrc2, int src2RoiShift, int src2Stride1, int src2Stride2,
                                            Ipp32f** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
  return ippmSub_mata_32f_L(ppSrc1,src1RoiShift,src1Stride1,src1Stride2,ppSrc2,src2RoiShift,src2Stride1,src2Stride2,ppDst,dstRoiShift,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmSub_mata_L(const Ipp64f** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                      const Ipp64f** ppSrc2, int src2RoiShift, int src2Stride1, int src2Stride2,
                                            Ipp64f** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
  return ippmSub_mata_64f_L(ppSrc1,src1RoiShift,src1Stride1,src1Stride2,ppSrc2,src2RoiShift,src2Stride1,src2Stride2,ppDst,dstRoiShift,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmSub_tata(const Ipp32f*  pSrc1, int src1Stride0, int src1Stride1, int src1Stride2,
                                      const Ipp32f*  pSrc2, int src2Stride0, int src2Stride1, int src2Stride2,
                                            Ipp32f*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
  return ippmSub_tata_32f(pSrc1,src1Stride0,src1Stride1,src1Stride2,pSrc2,src2Stride0,src2Stride1,src2Stride2,pDst,dstStride0,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmSub_tata(const Ipp64f*  pSrc1, int src1Stride0, int src1Stride1, int src1Stride2,
                                      const Ipp64f*  pSrc2, int src2Stride0, int src2Stride1, int src2Stride2,
                                            Ipp64f*  pDst,  int dstStride0,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
  return ippmSub_tata_64f(pSrc1,src1Stride0,src1Stride1,src1Stride2,pSrc2,src2Stride0,src2Stride1,src2Stride2,pDst,dstStride0,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmSub_tata_P(const Ipp32f** ppSrc1, int src1RoiShift, int src1Stride0,
                                      const Ipp32f** ppSrc2, int src2RoiShift, int src2Stride0,
                                            Ipp32f** ppDst,  int dstRoiShift,  int dstStride0,
                                            int width, int height, int count) {
  return ippmSub_tata_32f_P(ppSrc1,src1RoiShift,src1Stride0,ppSrc2,src2RoiShift,src2Stride0,ppDst,dstRoiShift,dstStride0,width,height,count);
}
inline IppStatus ippmSub_tata_P(const Ipp64f** ppSrc1, int src1RoiShift, int src1Stride0,
                                      const Ipp64f** ppSrc2, int src2RoiShift, int src2Stride0,
                                            Ipp64f** ppDst,  int dstRoiShift,  int dstStride0,
                                            int width, int height, int count) {
  return ippmSub_tata_64f_P(ppSrc1,src1RoiShift,src1Stride0,ppSrc2,src2RoiShift,src2Stride0,ppDst,dstRoiShift,dstStride0,width,height,count);
}
inline IppStatus ippmSub_tata_L(const Ipp32f** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                      const Ipp32f** ppSrc2, int src2RoiShift, int src2Stride1, int src2Stride2,
                                            Ipp32f** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
  return ippmSub_tata_32f_L(ppSrc1,src1RoiShift,src1Stride1,src1Stride2,ppSrc2,src2RoiShift,src2Stride1,src2Stride2,ppDst,dstRoiShift,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmSub_tata_L(const Ipp64f** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                      const Ipp64f** ppSrc2, int src2RoiShift, int src2Stride1, int src2Stride2,
                                            Ipp64f** ppDst,  int dstRoiShift,  int dstStride1,  int dstStride2,
                                            int width, int height, int count) {
  return ippmSub_tata_64f_L(ppSrc1,src1RoiShift,src1Stride1,src1Stride2,ppSrc2,src2RoiShift,src2Stride1,src2Stride2,ppDst,dstRoiShift,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmGaxpy_mv(const Ipp32f*  pSrc1, int src1Stride1, int src1Stride2,
                                             int src1Width,  int src1Height,
                                       const Ipp32f*  pSrc2, int src2Stride2, int src2Len,
                                       const Ipp32f*  pSrc3, int src2Stride3, int src3Len,
                                             Ipp32f*  pDst,  int dstStride2) {
  return ippmGaxpy_mv_32f(pSrc1,src1Stride1,src1Stride2,src1Width,src1Height,pSrc2,src2Stride2,src2Len,pSrc3,src2Stride3,src3Len,pDst,dstStride2);
}
inline IppStatus ippmGaxpy_mv(const Ipp64f*  pSrc1, int src1Stride1, int src1Stride2,
                                             int src1Width,  int src1Height,
                                       const Ipp64f*  pSrc2, int src2Stride2, int src2Len,
                                       const Ipp64f*  pSrc3, int src3Stride2, int src3Len,
                                             Ipp64f*  pDst,  int dstStride2) {
  return ippmGaxpy_mv_64f(pSrc1,src1Stride1,src1Stride2,src1Width,src1Height,pSrc2,src2Stride2,src2Len,pSrc3,src3Stride2,src3Len,pDst,dstStride2);
}
inline IppStatus ippmGaxpy_mv_P(const Ipp32f** ppSrc1, int src1RoiShift,
                                             int src1Width,   int src1Height,
                                       const Ipp32f** ppSrc2, int src2RoiShift, int src2Len,
                                       const Ipp32f** ppSrc3, int src3RoiShift, int src3Len,
                                             Ipp32f** ppDst,  int dstRoiShift) {
  return ippmGaxpy_mv_32f_P(ppSrc1,src1RoiShift,src1Width,src1Height,ppSrc2,src2RoiShift,src2Len,ppSrc3,src3RoiShift,src3Len,ppDst,dstRoiShift);
}
inline IppStatus ippmGaxpy_mv_P(const Ipp64f** ppSrc1, int src1RoiShift,
                                             int src1Width,   int src1Height,
                                       const Ipp64f** ppSrc2, int src2RoiShift, int src2Len,
                                       const Ipp64f** ppSrc3, int src3RoiShift, int src3Len,
                                             Ipp64f** ppDst,  int dstRoiShift) {
  return ippmGaxpy_mv_64f_P(ppSrc1,src1RoiShift,src1Width,src1Height,ppSrc2,src2RoiShift,src2Len,ppSrc3,src3RoiShift,src3Len,ppDst,dstRoiShift);
}
inline IppStatus ippmGaxpy_mva(const Ipp32f*  pSrc1, int src1Stride1, int src1Stride2,
                                             int src1Width,  int src1Height,
                                       const Ipp32f*  pSrc2, int src2Stride0, int src2Stride2, int src2Len,
                                       const Ipp32f*  pSrc3, int src3Stride0, int src3Stride2, int src3Len,
                                             Ipp32f*  pDst,  int dstStride0,  int dstStride2, int count) {
  return ippmGaxpy_mva_32f(pSrc1,src1Stride1,src1Stride2,src1Width,src1Height,pSrc2,src2Stride0,src2Stride2,src2Len,pSrc3,src3Stride0,src3Stride2,src3Len,pDst,dstStride0,dstStride2,count);
}
inline IppStatus ippmGaxpy_mva(const Ipp64f*  pSrc1, int src1Stride1, int src1Stride2,
                                             int src1Width,  int src1Height,
                                       const Ipp64f*  pSrc2, int src2Stride0, int src2Stride2, int src2Len,
                                       const Ipp64f*  pSrc3, int src3Stride0, int src3Stride2, int src3Len,
                                             Ipp64f*  pDst,  int dstStride0,  int dstStride2, int count) {
  return ippmGaxpy_mva_64f(pSrc1,src1Stride1,src1Stride2,src1Width,src1Height,pSrc2,src2Stride0,src2Stride2,src2Len,pSrc3,src3Stride0,src3Stride2,src3Len,pDst,dstStride0,dstStride2,count);
}
inline IppStatus ippmGaxpy_mva_P(const Ipp32f** ppSrc1, int src1RoiShift,
                                             int src1Width,   int src1Height,
                                       const Ipp32f** ppSrc2, int src2RoiShift, int src2Stride0, int src2Len,
                                       const Ipp32f** ppSrc3, int src3RoiShift, int src3Stride0, int src3Len,
                                             Ipp32f** ppDst,  int dstRoiShift,  int dstStride0,  int count) {
  return ippmGaxpy_mva_32f_P(ppSrc1,src1RoiShift,src1Width,src1Height,ppSrc2,src2RoiShift,src2Stride0,src2Len,ppSrc3,src3RoiShift,src3Stride0,src3Len,ppDst,dstRoiShift,dstStride0,count);
}
inline IppStatus ippmGaxpy_mva_P(const Ipp64f** ppSrc1, int src1RoiShift,
                                             int src1Width,   int src1Height,
                                       const Ipp64f** ppSrc2, int src2RoiShift, int src2Stride0, int src2Len,
                                       const Ipp64f** ppSrc3, int src3RoiShift, int src3Stride0, int src3Len,
                                             Ipp64f** ppDst,  int dstRoiShift,  int dstStride0,  int count) {
  return ippmGaxpy_mva_64f_P(ppSrc1,src1RoiShift,src1Width,src1Height,ppSrc2,src2RoiShift,src2Stride0,src2Len,ppSrc3,src3RoiShift,src3Stride0,src3Len,ppDst,dstRoiShift,dstStride0,count);
}
inline IppStatus ippmGaxpy_mva_L(const Ipp32f*  pSrc1,  int src1Stride1,  int src1Stride2,
                                             int src1Width,   int src1Height,
                                       const Ipp32f** ppSrc2, int src2RoiShift, int src2Stride2, int src2Len,
                                       const Ipp32f** ppSrc3, int src3RoiShift, int src3Stride2, int src3Len,
                                             Ipp32f** ppDst,  int dstRoiShift,  int dstStride2,  int count) {
  return ippmGaxpy_mva_32f_L(pSrc1,src1Stride1,src1Stride2,src1Width,src1Height,ppSrc2,src2RoiShift,src2Stride2,src2Len,ppSrc3,src3RoiShift,src3Stride2,src3Len,ppDst,dstRoiShift,dstStride2,count);
}
inline IppStatus ippmGaxpy_mva_L(const Ipp64f*  pSrc1,  int src1Stride1,  int src1Stride2,
                                             int src1Width,   int src1Height,
                                       const Ipp64f** ppSrc2, int src2RoiShift, int src2Stride2, int src2Len,
                                       const Ipp64f** ppSrc3, int src3RoiShift, int src3Stride2, int sr32Len,
                                             Ipp64f** ppDst,  int dstRoiShift,  int dstStride2,  int count) {
  return ippmGaxpy_mva_64f_L(pSrc1,src1Stride1,src1Stride2,src1Width,src1Height,ppSrc2,src2RoiShift,src2Stride2,src2Len,ppSrc3,src3RoiShift,src3Stride2,sr32Len,ppDst,dstRoiShift,dstStride2,count);
}
inline IppStatus ippmLUDecomp_m(const Ipp32f*  pSrc,  int srcStride1, int srcStride2,
                                               int*     pDstIndex,
                                               Ipp32f*  pDst,  int dstStride1, int dstStride2,
                                               int widthHeight) {
  return ippmLUDecomp_m_32f(pSrc,srcStride1,srcStride2,pDstIndex,pDst,dstStride1,dstStride2,widthHeight);
}
inline IppStatus ippmLUDecomp_m(const Ipp64f*  pSrc,  int srcStride1, int srcStride2,
                                               int*     pDstIndex,
                                               Ipp64f*  pDst,  int dstStride1, int dstStride2,
                                               int widthHeight) {
  return ippmLUDecomp_m_64f(pSrc,srcStride1,srcStride2,pDstIndex,pDst,dstStride1,dstStride2,widthHeight);
}
inline IppStatus ippmLUDecomp_m_P(const Ipp32f** ppSrc, int srcRoiShift,
                                               int*     pDstIndex,
                                               Ipp32f** ppDst, int dstRoiShift,
                                               int widthHeight) {
  return ippmLUDecomp_m_32f_P(ppSrc,srcRoiShift,pDstIndex,ppDst,dstRoiShift,widthHeight);
}
inline IppStatus ippmLUDecomp_m_P(const Ipp64f** ppSrc, int srcRoiShift,
                                               int*     pDstIndex,
                                               Ipp64f** ppDst, int dstRoiShift,
                                               int widthHeight) {
  return ippmLUDecomp_m_64f_P(ppSrc,srcRoiShift,pDstIndex,ppDst,dstRoiShift,widthHeight);
}
inline IppStatus ippmLUDecomp_ma(const Ipp32f*  pSrc,   int srcStride0, int srcStride1, int srcStride2,
                                               int*     pDstIndex,
                                               Ipp32f*  pDst,   int dstStride0, int dstStride1, int dstStride2,
                                               int widthHeight, int count) {
  return ippmLUDecomp_ma_32f(pSrc,srcStride0,srcStride1,srcStride2,pDstIndex,pDst,dstStride0,dstStride1,dstStride2,widthHeight,count);
}
inline IppStatus ippmLUDecomp_ma(const Ipp64f*  pSrc,   int srcStride0, int srcStride1, int srcStride2,
                                               int*     pDstIndex,
                                               Ipp64f*  pDst,   int dstStride0, int dstStride1, int dstStride2,
                                               int widthHeight, int count) {
  return ippmLUDecomp_ma_64f(pSrc,srcStride0,srcStride1,srcStride2,pDstIndex,pDst,dstStride0,dstStride1,dstStride2,widthHeight,count);
}
inline IppStatus ippmLUDecomp_ma_P(const Ipp32f** ppSrc,  int srcRoiShift, int srcStride0,
                                               int*     pDstIndex,
                                               Ipp32f** ppDst,  int dstRoiShift, int dstStride0,
                                               int widthHeight, int count) {
  return ippmLUDecomp_ma_32f_P(ppSrc,srcRoiShift,srcStride0,pDstIndex,ppDst,dstRoiShift,dstStride0,widthHeight,count);
}
inline IppStatus ippmLUDecomp_ma_P(const Ipp64f** ppSrc,  int srcRoiShift, int srcStride0,
                                               int*     pDstIndex,
                                               Ipp64f** ppDst,  int dstRoiShift, int dstStride0,
                                               int widthHeight, int count) {
  return ippmLUDecomp_ma_64f_P(ppSrc,srcRoiShift,srcStride0,pDstIndex,ppDst,dstRoiShift,dstStride0,widthHeight,count);
}
inline IppStatus ippmLUDecomp_ma_L(const Ipp32f** ppSrc,  int srcRoiShift, int srcStride1, int srcStride2,
                                               int*     pDstIndex,
                                               Ipp32f** ppDst,  int dstRoiShift, int dstStride1, int dstStride2,
                                               int widthHeight, int count) {
  return ippmLUDecomp_ma_32f_L(ppSrc,srcRoiShift,srcStride1,srcStride2,pDstIndex,ppDst,dstRoiShift,dstStride1,dstStride2,widthHeight,count);
}
inline IppStatus ippmLUDecomp_ma_L(const Ipp64f** ppSrc,  int srcRoiShift, int srcStride1, int srcStride2,
                                               int*     pDstIndex,
                                               Ipp64f** ppDst,  int dstRoiShift, int dstStride1, int dstStride2,
                                               int widthHeight, int count) {
  return ippmLUDecomp_ma_64f_L(ppSrc,srcRoiShift,srcStride1,srcStride2,pDstIndex,ppDst,dstRoiShift,dstStride1,dstStride2,widthHeight,count);
}
inline IppStatus ippmLUBackSubst_mv(const Ipp32f*  pSrc1,  int src1Stride1, int src1Stride2,
                                                    int* pSrcIndex,
                                              const Ipp32f*  pSrc2,  int src2Stride2,
                                                    Ipp32f*  pDst,   int dstStride2,
                                                    int widthHeight) {
  return ippmLUBackSubst_mv_32f(pSrc1,src1Stride1,src1Stride2,pSrcIndex,pSrc2,src2Stride2,pDst,dstStride2,widthHeight);
}
inline IppStatus ippmLUBackSubst_mv(const Ipp64f*  pSrc1,  int src1Stride1, int src1Stride2,
                                                    int* pSrcIndex,
                                              const Ipp64f*  pSrc2,  int src2Stride2,
                                                    Ipp64f*  pDst,   int dstStride2,
                                                    int widthHeight) {
  return ippmLUBackSubst_mv_64f(pSrc1,src1Stride1,src1Stride2,pSrcIndex,pSrc2,src2Stride2,pDst,dstStride2,widthHeight);
}
inline IppStatus ippmLUBackSubst_mv_P(const Ipp32f** ppSrc1, int src1RoiShift,
                                                    int* pSrcIndex,
                                              const Ipp32f** ppSrc2, int src2RoiShift,
                                                    Ipp32f** ppDst,  int dstRoiShift,
                                                    int widthHeight) {
  return ippmLUBackSubst_mv_32f_P(ppSrc1,src1RoiShift,pSrcIndex,ppSrc2,src2RoiShift,ppDst,dstRoiShift,widthHeight);
}
inline IppStatus ippmLUBackSubst_mv_P(const Ipp64f** ppSrc1, int src1RoiShift,
                                                    int* pSrcIndex,
                                              const Ipp64f** ppSrc2, int src2RoiShift,
                                                    Ipp64f** ppDst,  int dstRoiShift,
                                                    int widthHeight) {
  return ippmLUBackSubst_mv_64f_P(ppSrc1,src1RoiShift,pSrcIndex,ppSrc2,src2RoiShift,ppDst,dstRoiShift,widthHeight);
}
inline IppStatus ippmLUBackSubst_mva(const Ipp32f*  pSrc1,  int src1Stride1, int src1Stride2,
                                                    int* pSrcIndex,
                                              const Ipp32f*  pSrc2,  int src2Stride0, int src2Stride2,
                                                    Ipp32f*  pDst,   int dstStride0,  int dstStride2,
                                                    int widthHeight, int count) {
  return ippmLUBackSubst_mva_32f(pSrc1,src1Stride1,src1Stride2,pSrcIndex,pSrc2,src2Stride0,src2Stride2,pDst,dstStride0,dstStride2,widthHeight,count);
}
inline IppStatus ippmLUBackSubst_mva(const Ipp64f*  pSrc1,  int src1Stride1, int src1Stride2,
                                                    int* pSrcIndex,
                                              const Ipp64f*  pSrc2,  int src2Stride0, int src2Stride2,
                                                    Ipp64f*  pDst,   int dstStride0,  int dstStride2,
                                                    int widthHeight, int count) {
  return ippmLUBackSubst_mva_64f(pSrc1,src1Stride1,src1Stride2,pSrcIndex,pSrc2,src2Stride0,src2Stride2,pDst,dstStride0,dstStride2,widthHeight,count);
}
inline IppStatus ippmLUBackSubst_mva_P(const Ipp32f** ppSrc1, int src1RoiShift,
                                                    int* pSrcIndex,
                                              const Ipp32f** ppSrc2, int src2RoiShift, int src2Stride0,
                                                    Ipp32f** ppDst,  int dstRoiShift,  int dstStride0,
                                                    int widthHeight, int count) {
  return ippmLUBackSubst_mva_32f_P(ppSrc1,src1RoiShift,pSrcIndex,ppSrc2,src2RoiShift,src2Stride0,ppDst,dstRoiShift,dstStride0,widthHeight,count);
}
inline IppStatus ippmLUBackSubst_mva_P(const Ipp64f** ppSrc1, int src1RoiShift,
                                                    int* pSrcIndex,
                                              const Ipp64f** ppSrc2, int src2RoiShift, int src2Stride0,
                                                    Ipp64f** ppDst,  int dstRoiShift,  int dstStride0,
                                                    int widthHeight, int count) {
  return ippmLUBackSubst_mva_64f_P(ppSrc1,src1RoiShift,pSrcIndex,ppSrc2,src2RoiShift,src2Stride0,ppDst,dstRoiShift,dstStride0,widthHeight,count);
}
inline IppStatus ippmLUBackSubst_mva_L(const Ipp32f*  pSrc1,  int src1Stride1,  int src1Stride2,
                                                    int* pSrcIndex,
                                              const Ipp32f** ppSrc2, int src2RoiShift, int src2Stride2,
                                                    Ipp32f** ppDst,  int dstRoiShift,  int dstStride2,
                                                    int widthHeight, int count) {
  return ippmLUBackSubst_mva_32f_L(pSrc1,src1Stride1,src1Stride2,pSrcIndex,ppSrc2,src2RoiShift,src2Stride2,ppDst,dstRoiShift,dstStride2,widthHeight,count);
}
inline IppStatus ippmLUBackSubst_mva_L(const Ipp64f*  pSrc1,  int src1Stride1,  int src1Stride2,
                                                    int* pSrcIndex,
                                              const Ipp64f** ppSrc2, int src2RoiShift, int src2Stride2,
                                                    Ipp64f** ppDst,  int dstRoiShift,  int dstStride2,
                                                    int widthHeight, int count) {
  return ippmLUBackSubst_mva_64f_L(pSrc1,src1Stride1,src1Stride2,pSrcIndex,ppSrc2,src2RoiShift,src2Stride2,ppDst,dstRoiShift,dstStride2,widthHeight,count);
}
inline IppStatus ippmLUBackSubst_mava(const Ipp32f*  pSrc1,  int src1Stride0, int src1Stride1, int src1Stride2,
                                                    int* pSrcIndex,
                                              const Ipp32f*  pSrc2,  int src2Stride0, int src2Stride2,
                                                    Ipp32f*  pDst,   int dstStride0,  int dstStride2,
                                                    int widthHeight, int count) {
  return ippmLUBackSubst_mava_32f(pSrc1,src1Stride0,src1Stride1,src1Stride2,pSrcIndex,pSrc2,src2Stride0,src2Stride2,pDst,dstStride0,dstStride2,widthHeight,count);
}
inline IppStatus ippmLUBackSubst_mava(const Ipp64f*  pSrc1,  int src1Stride0, int src1Stride1, int src1Stride2,
                                                    int* pSrcIndex,
                                              const Ipp64f*  pSrc2,  int src2Stride0, int src2Stride2,
                                                    Ipp64f*  pDst,   int dstStride0,  int dstStride2,
                                                    int widthHeight, int count) {
  return ippmLUBackSubst_mava_64f(pSrc1,src1Stride0,src1Stride1,src1Stride2,pSrcIndex,pSrc2,src2Stride0,src2Stride2,pDst,dstStride0,dstStride2,widthHeight,count);
}
inline IppStatus ippmLUBackSubst_mava_P(const Ipp32f** ppSrc1, int src1RoiShift, int src1Stride0,
                                                    int* pSrcIndex,
                                              const Ipp32f** ppSrc2, int src2RoiShift, int src2Stride0,
                                                    Ipp32f** ppDst,  int dstRoiShift,  int dstStride0,
                                                    int widthHeight, int count) {
  return ippmLUBackSubst_mava_32f_P(ppSrc1,src1RoiShift,src1Stride0,pSrcIndex,ppSrc2,src2RoiShift,src2Stride0,ppDst,dstRoiShift,dstStride0,widthHeight,count);
}
inline IppStatus ippmLUBackSubst_mava_P(const Ipp64f** ppSrc1, int src1RoiShift, int src1Stride0,
                                                    int* pSrcIndex,
                                              const Ipp64f** ppSrc2, int src2RoiShift, int src2Stride0,
                                                    Ipp64f** ppDst,  int dstRoiShift,  int dstStride0,
                                                    int widthHeight, int count) {
  return ippmLUBackSubst_mava_64f_P(ppSrc1,src1RoiShift,src1Stride0,pSrcIndex,ppSrc2,src2RoiShift,src2Stride0,ppDst,dstRoiShift,dstStride0,widthHeight,count);
}
inline IppStatus ippmLUBackSubst_mava_L(const Ipp32f** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                                    int* pSrcIndex,
                                              const Ipp32f** ppSrc2, int src2RoiShift, int src2Stride2,
                                                    Ipp32f** ppDst,  int dstRoiShift,  int dstStride2,
                                                    int widthHeight, int count) {
  return ippmLUBackSubst_mava_32f_L(ppSrc1,src1RoiShift,src1Stride1,src1Stride2,pSrcIndex,ppSrc2,src2RoiShift,src2Stride2,ppDst,dstRoiShift,dstStride2,widthHeight,count);
}
inline IppStatus ippmLUBackSubst_mava_L(const Ipp64f** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                                    int* pSrcIndex,
                                              const Ipp64f** ppSrc2, int src2RoiShift, int src2Stride2,
                                                    Ipp64f** ppDst,  int dstRoiShift,  int dstStride2,
                                                    int widthHeight, int count) {
  return ippmLUBackSubst_mava_64f_L(ppSrc1,src1RoiShift,src1Stride1,src1Stride2,pSrcIndex,ppSrc2,src2RoiShift,src2Stride2,ppDst,dstRoiShift,dstStride2,widthHeight,count);
}
inline IppStatus ippmCholeskyDecomp_m(const Ipp32f*  pSrc,  int srcStride1, int srcStride2,
                                                     Ipp32f*  pDst,  int dstStride1, int dstStride2,
                                                     int widthHeight) {
  return ippmCholeskyDecomp_m_32f(pSrc,srcStride1,srcStride2,pDst,dstStride1,dstStride2,widthHeight);
}
inline IppStatus ippmCholeskyDecomp_m(const Ipp64f*  pSrc,  int srcStride1, int srcStride2,
                                                     Ipp64f*  pDst,  int dstStride1, int dstStride2,
                                                     int widthHeight) {
  return ippmCholeskyDecomp_m_64f(pSrc,srcStride1,srcStride2,pDst,dstStride1,dstStride2,widthHeight);
}
inline IppStatus ippmCholeskyDecomp_m_P(const Ipp32f** ppSrc, int srcRoiShift,
                                                     Ipp32f** ppDst, int dstRoiShift,
                                                     int widthHeight) {
  return ippmCholeskyDecomp_m_32f_P(ppSrc,srcRoiShift,ppDst,dstRoiShift,widthHeight);
}
inline IppStatus ippmCholeskyDecomp_m_P(const Ipp64f** ppSrc, int srcRoiShift,
                                                     Ipp64f** ppDst, int dstRoiShift,
                                                     int widthHeight) {
  return ippmCholeskyDecomp_m_64f_P(ppSrc,srcRoiShift,ppDst,dstRoiShift,widthHeight);
}
inline IppStatus ippmCholeskyDecomp_ma(const Ipp32f*  pSrc,   int srcStride0, int srcStride1, int srcStride2,
                                                     Ipp32f*  pDst,   int dstStride0, int dstStride1, int dstStride2,
                                                     int widthHeight, int count) {
  return ippmCholeskyDecomp_ma_32f(pSrc,srcStride0,srcStride1,srcStride2,pDst,dstStride0,dstStride1,dstStride2,widthHeight,count);
}
inline IppStatus ippmCholeskyDecomp_ma(const Ipp64f*  pSrc,   int srcStride0, int srcStride1, int srcStride2,
                                                     Ipp64f*  pDst,   int dstStride0, int dstStride1, int dstStride2,
                                                     int widthHeight, int count) {
  return ippmCholeskyDecomp_ma_64f(pSrc,srcStride0,srcStride1,srcStride2,pDst,dstStride0,dstStride1,dstStride2,widthHeight,count);
}
inline IppStatus ippmCholeskyDecomp_ma_P(const Ipp32f** ppSrc,  int srcRoiShift, int srcStride0,
                                                     Ipp32f** ppDst,  int dstRoiShift, int dstStride0,
                                                     int widthHeight, int count) {
  return ippmCholeskyDecomp_ma_32f_P(ppSrc,srcRoiShift,srcStride0,ppDst,dstRoiShift,dstStride0,widthHeight,count);
}
inline IppStatus ippmCholeskyDecomp_ma_P(const Ipp64f** ppSrc,  int srcRoiShift, int srcStride0,
                                                     Ipp64f** ppDst,  int dstRoiShift, int dstStride0,
                                                     int widthHeight, int count) {
  return ippmCholeskyDecomp_ma_64f_P(ppSrc,srcRoiShift,srcStride0,ppDst,dstRoiShift,dstStride0,widthHeight,count);
}
inline IppStatus ippmCholeskyDecomp_ma_L(const Ipp32f** ppSrc,  int srcRoiShift, int srcStride1, int srcStride2,
                                                     Ipp32f** ppDst,  int dstRoiShift, int dstStride1, int dstStride2,
                                                     int widthHeight, int count) {
  return ippmCholeskyDecomp_ma_32f_L(ppSrc,srcRoiShift,srcStride1,srcStride2,ppDst,dstRoiShift,dstStride1,dstStride2,widthHeight,count);
}
inline IppStatus ippmCholeskyDecomp_ma_L(const Ipp64f** ppSrc,  int srcRoiShift, int srcStride1, int srcStride2,
                                                     Ipp64f** ppDst,  int dstRoiShift, int dstStride1, int dstStride2,
                                                     int widthHeight, int count) {
  return ippmCholeskyDecomp_ma_64f_L(ppSrc,srcRoiShift,srcStride1,srcStride2,ppDst,dstRoiShift,dstStride1,dstStride2,widthHeight,count);
}
inline IppStatus ippmCholeskyBackSubst_mv(const Ipp32f*  pSrc1,  int src1Stride1, int src1Stride2,
                                                    const Ipp32f*  pSrc2,  int src2Stride2,
                                                          Ipp32f*  pDst,   int dstStride2,
                                                          int widthHeight) {
  return ippmCholeskyBackSubst_mv_32f(pSrc1,src1Stride1,src1Stride2,pSrc2,src2Stride2,pDst,dstStride2,widthHeight);
}
inline IppStatus ippmCholeskyBackSubst_mv(const Ipp64f*  pSrc1,  int src1Stride1, int src1Stride2,
                                                    const Ipp64f*  pSrc2,  int src2Stride2,
                                                          Ipp64f*  pDst,   int dstStride2,
                                                          int widthHeight) {
  return ippmCholeskyBackSubst_mv_64f(pSrc1,src1Stride1,src1Stride2,pSrc2,src2Stride2,pDst,dstStride2,widthHeight);
}
inline IppStatus ippmCholeskyBackSubst_mv_P(const Ipp32f** ppSrc1, int src1RoiShift,
                                                    const Ipp32f** ppSrc2, int src2RoiShift,
                                                          Ipp32f** ppDst,  int dstRoiShift,
                                                          int widthHeight) {
  return ippmCholeskyBackSubst_mv_32f_P(ppSrc1,src1RoiShift,ppSrc2,src2RoiShift,ppDst,dstRoiShift,widthHeight);
}
inline IppStatus ippmCholeskyBackSubst_mv_P(const Ipp64f** ppSrc1, int src1RoiShift,
                                                    const Ipp64f** ppSrc2, int src2RoiShift,
                                                          Ipp64f** ppDst,  int dstRoiShift,
                                                          int widthHeight) {
  return ippmCholeskyBackSubst_mv_64f_P(ppSrc1,src1RoiShift,ppSrc2,src2RoiShift,ppDst,dstRoiShift,widthHeight);
}
inline IppStatus ippmCholeskyBackSubst_mva(const Ipp32f*  pSrc1,  int src1Stride1, int src1Stride2,
                                                    const Ipp32f*  pSrc2,  int src2Stride0, int src2Stride2,
                                                          Ipp32f*  pDst,   int dstStride0,  int dstStride2,
                                                          int widthHeight, int count) {
  return ippmCholeskyBackSubst_mva_32f(pSrc1,src1Stride1,src1Stride2,pSrc2,src2Stride0,src2Stride2,pDst,dstStride0,dstStride2,widthHeight,count);
}
inline IppStatus ippmCholeskyBackSubst_mva(const Ipp64f*  pSrc1,  int src1Stride1, int src1Stride2,
                                                    const Ipp64f*  pSrc2,  int src2Stride0, int src2Stride2,
                                                          Ipp64f*  pDst,   int dstStride0,  int dstStride2,
                                                          int widthHeight, int count) {
  return ippmCholeskyBackSubst_mva_64f(pSrc1,src1Stride1,src1Stride2,pSrc2,src2Stride0,src2Stride2,pDst,dstStride0,dstStride2,widthHeight,count);
}
inline IppStatus ippmCholeskyBackSubst_mva_P(const Ipp32f** ppSrc1, int src1RoiShift,
                                                    const Ipp32f** ppSrc2, int src2RoiShift, int src2Stride0,
                                                          Ipp32f** ppDst,  int dstRoiShift,  int dstStride0,
                                                          int widthHeight, int count) {
  return ippmCholeskyBackSubst_mva_32f_P(ppSrc1,src1RoiShift,ppSrc2,src2RoiShift,src2Stride0,ppDst,dstRoiShift,dstStride0,widthHeight,count);
}
inline IppStatus ippmCholeskyBackSubst_mva_P(const Ipp64f** ppSrc1, int src1RoiShift,
                                                    const Ipp64f** ppSrc2, int src2RoiShift, int src2Stride0,
                                                          Ipp64f** ppDst,  int dstRoiShift,  int dstStride0,
                                                          int widthHeight, int count) {
  return ippmCholeskyBackSubst_mva_64f_P(ppSrc1,src1RoiShift,ppSrc2,src2RoiShift,src2Stride0,ppDst,dstRoiShift,dstStride0,widthHeight,count);
}
inline IppStatus ippmCholeskyBackSubst_mva_L(const Ipp32f*  pSrc1,  int src1Stride1,  int src1Stride2,
                                                    const Ipp32f** ppSrc2, int src2RoiShift, int src2Stride2,
                                                          Ipp32f** ppDst,  int dstRoiShift,  int dstStride2,
                                                          int widthHeight, int count) {
  return ippmCholeskyBackSubst_mva_32f_L(pSrc1,src1Stride1,src1Stride2,ppSrc2,src2RoiShift,src2Stride2,ppDst,dstRoiShift,dstStride2,widthHeight,count);
}
inline IppStatus ippmCholeskyBackSubst_mva_L(const Ipp64f*  pSrc1,  int src1Stride1,  int src1Stride2,
                                                    const Ipp64f** ppSrc2, int src2RoiShift, int src2Stride2,
                                                          Ipp64f** ppDst,  int dstRoiShift,  int dstStride2,
                                                          int widthHeight, int count) {
  return ippmCholeskyBackSubst_mva_64f_L(pSrc1,src1Stride1,src1Stride2,ppSrc2,src2RoiShift,src2Stride2,ppDst,dstRoiShift,dstStride2,widthHeight,count);
}
inline IppStatus ippmCholeskyBackSubst_mava(const Ipp32f*  pSrc1,  int src1Stride0, int src1Stride1, int src1Stride2,
                                                    const Ipp32f*  pSrc2,  int src2Stride0, int src2Stride2,
                                                          Ipp32f*  pDst,   int dstStride0,  int dstStride2,
                                                          int widthHeight, int count) {
  return ippmCholeskyBackSubst_mava_32f(pSrc1,src1Stride0,src1Stride1,src1Stride2,pSrc2,src2Stride0,src2Stride2,pDst,dstStride0,dstStride2,widthHeight,count);
}
inline IppStatus ippmCholeskyBackSubst_mava(const Ipp64f*  pSrc1,  int src1Stride0, int src1Stride1, int src1Stride2,
                                                    const Ipp64f*  pSrc2,  int src2Stride0, int src2Stride2,
                                                          Ipp64f*  pDst,   int dstStride0,  int dstStride2,
                                                          int widthHeight, int count) {
  return ippmCholeskyBackSubst_mava_64f(pSrc1,src1Stride0,src1Stride1,src1Stride2,pSrc2,src2Stride0,src2Stride2,pDst,dstStride0,dstStride2,widthHeight,count);
}
inline IppStatus ippmCholeskyBackSubst_mava_P(const Ipp32f** ppSrc1, int src1RoiShift, int src1Stride0,
                                                    const Ipp32f** ppSrc2, int src2RoiShift, int src2Stride0,
                                                          Ipp32f** ppDst,  int dstRoiShift,  int dstStride0,
                                                          int widthHeight, int count) {
  return ippmCholeskyBackSubst_mava_32f_P(ppSrc1,src1RoiShift,src1Stride0,ppSrc2,src2RoiShift,src2Stride0,ppDst,dstRoiShift,dstStride0,widthHeight,count);
}
inline IppStatus ippmCholeskyBackSubst_mava_P(const Ipp64f** ppSrc1, int src1RoiShift, int src1Stride0,
                                                    const Ipp64f** ppSrc2, int src2RoiShift, int src2Stride0,
                                                          Ipp64f** ppDst,  int dstRoiShift,  int dstStride0,
                                                          int widthHeight, int count) {
  return ippmCholeskyBackSubst_mava_64f_P(ppSrc1,src1RoiShift,src1Stride0,ppSrc2,src2RoiShift,src2Stride0,ppDst,dstRoiShift,dstStride0,widthHeight,count);
}
inline IppStatus ippmCholeskyBackSubst_mava_L(const Ipp32f** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                                    const Ipp32f** ppSrc2, int src2RoiShift, int src2Stride2,
                                                          Ipp32f** ppDst,  int dstRoiShift,  int dstStride2,
                                                          int widthHeight, int count) {
  return ippmCholeskyBackSubst_mava_32f_L(ppSrc1,src1RoiShift,src1Stride1,src1Stride2,ppSrc2,src2RoiShift,src2Stride2,ppDst,dstRoiShift,dstStride2,widthHeight,count);
}
inline IppStatus ippmCholeskyBackSubst_mava_L(const Ipp64f** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                                    const Ipp64f** ppSrc2, int src2RoiShift, int src2Stride2,
                                                          Ipp64f** ppDst,  int dstRoiShift,  int dstStride2,
                                                          int widthHeight, int count) {
  return ippmCholeskyBackSubst_mava_64f_L(ppSrc1,src1RoiShift,src1Stride1,src1Stride2,ppSrc2,src2RoiShift,src2Stride2,ppDst,dstRoiShift,dstStride2,widthHeight,count);
}
inline IppStatus ippmQRDecomp_m(const Ipp32f*  pSrc,  int srcStride1, int srcStride2,
                                               Ipp32f*  pBuffer,
                                               Ipp32f*  pDst,  int dstStride1, int dstStride2,
                                               int width, int height) {
  return ippmQRDecomp_m_32f(pSrc,srcStride1,srcStride2,pBuffer,pDst,dstStride1,dstStride2,width,height);
}
inline IppStatus ippmQRDecomp_m(const Ipp64f*  pSrc,  int srcStride1, int srcStride2,
                                               Ipp64f*  pBuffer,
                                               Ipp64f*  pDst,  int dstStride1, int dstStride2,
                                               int width, int height) {
  return ippmQRDecomp_m_64f(pSrc,srcStride1,srcStride2,pBuffer,pDst,dstStride1,dstStride2,width,height);
}
inline IppStatus ippmQRDecomp_m_P(const Ipp32f** ppSrc, int srcRoiShift,
                                               Ipp32f*  pBuffer,
                                               Ipp32f** ppDst, int dstRoiShift,
                                               int width, int height) {
  return ippmQRDecomp_m_32f_P(ppSrc,srcRoiShift,pBuffer,ppDst,dstRoiShift,width,height);
}
inline IppStatus ippmQRDecomp_m_P(const Ipp64f** ppSrc, int srcRoiShift,
                                               Ipp64f*  pBuffer,
                                               Ipp64f** ppDst, int dstRoiShift,
                                               int width, int height) {
  return ippmQRDecomp_m_64f_P(ppSrc,srcRoiShift,pBuffer,ppDst,dstRoiShift,width,height);
}
inline IppStatus ippmQRDecomp_ma(const Ipp32f*  pSrc,   int srcStride0, int srcStride1, int srcStride2,
                                               Ipp32f*  pBuffer,
                                               Ipp32f*  pDst,   int dstStride0, int dstStride1, int dstStride2,
                                               int width, int height, int count) {
  return ippmQRDecomp_ma_32f(pSrc,srcStride0,srcStride1,srcStride2,pBuffer,pDst,dstStride0,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmQRDecomp_ma(const Ipp64f*  pSrc,   int srcStride0, int srcStride1, int srcStride2,
                                               Ipp64f*  pBuffer,
                                               Ipp64f*  pDst,   int dstStride0, int dstStride1, int dstStride2,
                                               int width, int height, int count) {
  return ippmQRDecomp_ma_64f(pSrc,srcStride0,srcStride1,srcStride2,pBuffer,pDst,dstStride0,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmQRDecomp_ma_P(const Ipp32f** ppSrc,  int srcRoiShift, int srcStride0,
                                               Ipp32f*  pBuffer,
                                               Ipp32f** ppDst,  int dstRoiShift, int dstStride0,
                                               int width, int height, int count) {
  return ippmQRDecomp_ma_32f_P(ppSrc,srcRoiShift,srcStride0,pBuffer,ppDst,dstRoiShift,dstStride0,width,height,count);
}
inline IppStatus ippmQRDecomp_ma_P(const Ipp64f** ppSrc,  int srcRoiShift, int srcStride0,
                                               Ipp64f*  pBuffer,
                                               Ipp64f** ppDst,  int dstRoiShift, int dstStride0,
                                               int width, int height, int count) {
  return ippmQRDecomp_ma_64f_P(ppSrc,srcRoiShift,srcStride0,pBuffer,ppDst,dstRoiShift,dstStride0,width,height,count);
}
inline IppStatus ippmQRDecomp_ma_L(const Ipp32f** ppSrc,  int srcRoiShift, int srcStride1, int srcStride2,
                                               Ipp32f*  pBuffer,
                                               Ipp32f** ppDst,  int dstRoiShift, int dstStride1, int dstStride2,
                                               int width, int height, int count) {
  return ippmQRDecomp_ma_32f_L(ppSrc,srcRoiShift,srcStride1,srcStride2,pBuffer,ppDst,dstRoiShift,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmQRDecomp_ma_L(const Ipp64f** ppSrc,  int srcRoiShift, int srcStride1, int srcStride2,
                                               Ipp64f*  pBuffer,
                                               Ipp64f** ppDst,  int dstRoiShift, int dstStride1, int dstStride2,
                                               int width, int height, int count) {
  return ippmQRDecomp_ma_64f_L(ppSrc,srcRoiShift,srcStride1,srcStride2,pBuffer,ppDst,dstRoiShift,dstStride1,dstStride2,width,height,count);
}
inline IppStatus ippmQRBackSubst_mv(const Ipp32f*  pSrc1,  int src1Stride1, int src1Stride2,
                                                    Ipp32f*  pBuffer,
                                              const Ipp32f*  pSrc2,  int src2Stride2,
                                                    Ipp32f*  pDst,   int dstStride2,
                                                    int width, int height) {
  return ippmQRBackSubst_mv_32f(pSrc1,src1Stride1,src1Stride2,pBuffer,pSrc2,src2Stride2,pDst,dstStride2,width,height);
}
inline IppStatus ippmQRBackSubst_mv(const Ipp64f*  pSrc1,  int src1Stride1, int src1Stride2,
                                                    Ipp64f*  pBuffer,
                                              const Ipp64f*  pSrc2,  int src2Stride2,
                                                    Ipp64f*  pDst,   int dstStride2,
                                                    int width, int height) {
  return ippmQRBackSubst_mv_64f(pSrc1,src1Stride1,src1Stride2,pBuffer,pSrc2,src2Stride2,pDst,dstStride2,width,height);
}
inline IppStatus ippmQRBackSubst_mv_P(const Ipp32f** ppSrc1, int src1RoiShift,
                                                    Ipp32f*  pBuffer,
                                              const Ipp32f** ppSrc2, int src2RoiShift,
                                                    Ipp32f** ppDst,  int dstRoiShift,
                                                    int width, int height) {
  return ippmQRBackSubst_mv_32f_P(ppSrc1,src1RoiShift,pBuffer,ppSrc2,src2RoiShift,ppDst,dstRoiShift,width,height);
}
inline IppStatus ippmQRBackSubst_mv_P(const Ipp64f** ppSrc1, int src1RoiShift,
                                                    Ipp64f*  pBuffer,
                                              const Ipp64f** ppSrc2, int src2RoiShift,
                                                    Ipp64f** ppDst,  int dstRoiShift,
                                                    int width, int height) {
  return ippmQRBackSubst_mv_64f_P(ppSrc1,src1RoiShift,pBuffer,ppSrc2,src2RoiShift,ppDst,dstRoiShift,width,height);
}
inline IppStatus ippmQRBackSubst_mva(const Ipp32f*  pSrc1,  int src1Stride1, int src1Stride2,
                                                    Ipp32f*  pBuffer,
                                              const Ipp32f*  pSrc2,  int src2Stride0, int src2Stride2,
                                                    Ipp32f*  pDst,   int dstStride0,  int dstStride2,
                                                    int width, int height, int count) {
  return ippmQRBackSubst_mva_32f(pSrc1,src1Stride1,src1Stride2,pBuffer,pSrc2,src2Stride0,src2Stride2,pDst,dstStride0,dstStride2,width,height,count);
}
inline IppStatus ippmQRBackSubst_mva(const Ipp64f*  pSrc1,  int src1Stride1, int src1Stride2,
                                                    Ipp64f*  pBuffer,
                                              const Ipp64f*  pSrc2,  int src2Stride0, int src2Stride2,
                                                    Ipp64f*  pDst,   int dstStride0,  int dstStride2,
                                                    int width, int height, int count) {
  return ippmQRBackSubst_mva_64f(pSrc1,src1Stride1,src1Stride2,pBuffer,pSrc2,src2Stride0,src2Stride2,pDst,dstStride0,dstStride2,width,height,count);
}
inline IppStatus ippmQRBackSubst_mva_P(const Ipp32f** ppSrc1, int src1RoiShift,
                                                    Ipp32f*  pBuffer,
                                              const Ipp32f** ppSrc2, int src2RoiShift, int src2Stride0,
                                                    Ipp32f** ppDst,  int dstRoiShift,  int dstStride0,
                                                    int width, int height, int count) {
  return ippmQRBackSubst_mva_32f_P(ppSrc1,src1RoiShift,pBuffer,ppSrc2,src2RoiShift,src2Stride0,ppDst,dstRoiShift,dstStride0,width,height,count);
}
inline IppStatus ippmQRBackSubst_mva_P(const Ipp64f** ppSrc1, int src1RoiShift,
                                                    Ipp64f*  pBuffer,
                                              const Ipp64f** ppSrc2, int src2RoiShift, int src2Stride0,
                                                    Ipp64f** ppDst,  int dstRoiShift,  int dstStride0,
                                                    int width, int height, int count) {
  return ippmQRBackSubst_mva_64f_P(ppSrc1,src1RoiShift,pBuffer,ppSrc2,src2RoiShift,src2Stride0,ppDst,dstRoiShift,dstStride0,width,height,count);
}
inline IppStatus ippmQRBackSubst_mva_L(const Ipp32f*  pSrc1,  int src1Stride1,  int src1Stride2,
                                                    Ipp32f*  pBuffer,
                                              const Ipp32f** ppSrc2, int src2RoiShift, int src2Stride2,
                                                    Ipp32f** ppDst,  int dstRoiShift,  int dstStride2,
                                                    int width, int height, int count) {
  return ippmQRBackSubst_mva_32f_L(pSrc1,src1Stride1,src1Stride2,pBuffer,ppSrc2,src2RoiShift,src2Stride2,ppDst,dstRoiShift,dstStride2,width,height,count);
}
inline IppStatus ippmQRBackSubst_mva_L(const Ipp64f*  pSrc1,  int src1Stride1,  int src1Stride2,
                                                    Ipp64f*  pBuffer,
                                              const Ipp64f** ppSrc2, int src2RoiShift, int src2Stride2,
                                                    Ipp64f** ppDst,  int dstRoiShift,  int dstStride2,
                                                    int width, int height, int count) {
  return ippmQRBackSubst_mva_64f_L(pSrc1,src1Stride1,src1Stride2,pBuffer,ppSrc2,src2RoiShift,src2Stride2,ppDst,dstRoiShift,dstStride2,width,height,count);
}
inline IppStatus ippmQRBackSubst_mava(const Ipp32f*  pSrc1,  int src1Stride0, int src1Stride1, int src1Stride2,
                                                    Ipp32f*  pBuffer,
                                              const Ipp32f*  pSrc2,  int src2Stride0, int src2Stride2,
                                                    Ipp32f*  pDst,   int dstStride0,  int dstStride2,
                                                    int width, int height, int count) {
  return ippmQRBackSubst_mava_32f(pSrc1,src1Stride0,src1Stride1,src1Stride2,pBuffer,pSrc2,src2Stride0,src2Stride2,pDst,dstStride0,dstStride2,width,height,count);
}
inline IppStatus ippmQRBackSubst_mava(const Ipp64f*  pSrc1,  int src1Stride0, int src1Stride1, int src1Stride2,
                                                    Ipp64f*  pBuffer,
                                              const Ipp64f*  pSrc2,  int src2Stride0, int src2Stride2,
                                                    Ipp64f*  pDst,   int dstStride0,  int dstStride2,
                                                    int width, int height, int count) {
  return ippmQRBackSubst_mava_64f(pSrc1,src1Stride0,src1Stride1,src1Stride2,pBuffer,pSrc2,src2Stride0,src2Stride2,pDst,dstStride0,dstStride2,width,height,count);
}
inline IppStatus ippmQRBackSubst_mava_P(const Ipp32f** ppSrc1, int src1RoiShift, int src1Stride0,
                                                    Ipp32f*  pBuffer,
                                              const Ipp32f** ppSrc2, int src2RoiShift, int src2Stride0,
                                                    Ipp32f** ppDst,  int dstRoiShift,  int dstStride0,
                                                    int width, int height, int count) {
  return ippmQRBackSubst_mava_32f_P(ppSrc1,src1RoiShift,src1Stride0,pBuffer,ppSrc2,src2RoiShift,src2Stride0,ppDst,dstRoiShift,dstStride0,width,height,count);
}
inline IppStatus ippmQRBackSubst_mava_P(const Ipp64f** ppSrc1, int src1RoiShift, int src1Stride0,
                                                    Ipp64f*  pBuffer,
                                              const Ipp64f** ppSrc2, int src2RoiShift, int src2Stride0,
                                                    Ipp64f** ppDst,  int dstRoiShift,  int dstStride0,
                                                    int width, int height, int count) {
  return ippmQRBackSubst_mava_64f_P(ppSrc1,src1RoiShift,src1Stride0,pBuffer,ppSrc2,src2RoiShift,src2Stride0,ppDst,dstRoiShift,dstStride0,width,height,count);
}
inline IppStatus ippmQRBackSubst_mava_L(const Ipp32f** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                                    Ipp32f*  pBuffer,
                                              const Ipp32f** ppSrc2, int src2RoiShift, int src2Stride2,
                                                    Ipp32f** ppDst,  int dstRoiShift,  int dstStride2,
                                                    int width, int height, int count) {
  return ippmQRBackSubst_mava_32f_L(ppSrc1,src1RoiShift,src1Stride1,src1Stride2,pBuffer,ppSrc2,src2RoiShift,src2Stride2,ppDst,dstRoiShift,dstStride2,width,height,count);
}
inline IppStatus ippmQRBackSubst_mava_L(const Ipp64f** ppSrc1, int src1RoiShift, int src1Stride1, int src1Stride2,
                                                    Ipp64f*  pBuffer,
                                              const Ipp64f** ppSrc2, int src2RoiShift, int src2Stride2,
                                                    Ipp64f** ppDst,  int dstRoiShift,  int dstStride2,
                                                    int width, int height, int count) {
  return ippmQRBackSubst_mava_64f_L(ppSrc1,src1RoiShift,src1Stride1,src1Stride2,pBuffer,ppSrc2,src2RoiShift,src2Stride2,ppDst,dstRoiShift,dstStride2,width,height,count);
}

inline IppStatus ippmEigenValuesVectorsSym_m(const Ipp32f* pSrc, int srcStride1, int srcStride2,
                                                           Ipp32f* pBuffer,
                                                           Ipp32f* pDstVectors, int dstStride1, int dstStride2,
                                                           Ipp32f* pDstValues,  int widthHeight) {
  return ippmEigenValuesVectorsSym_m_32f(pSrc,srcStride1,srcStride2,pBuffer,pDstVectors,dstStride1,dstStride2,pDstValues,widthHeight);
}
inline IppStatus ippmEigenValuesVectorsSym_m(const Ipp64f* pSrc, int srcStride1, int srcStride2,
                                                           Ipp64f* pBuffer,
                                                           Ipp64f* pDstVectors, int dstStride1, int dstStride2,
                                                           Ipp64f* pDstValues,  int widthHeight) {
  return ippmEigenValuesVectorsSym_m_64f(pSrc,srcStride1,srcStride2,pBuffer,pDstVectors,dstStride1,dstStride2,pDstValues,widthHeight);
}
inline IppStatus ippmEigenValuesVectorsSym_m_P(const Ipp32f** ppSrc, int srcRoiShift,
                                                           Ipp32f*  pBuffer,
                                                           Ipp32f** ppDstVectors, int dstRoiShift,
                                                           Ipp32f*  pDstValues,   int widthHeight) {
  return ippmEigenValuesVectorsSym_m_32f_P(ppSrc,srcRoiShift,pBuffer,ppDstVectors,dstRoiShift,pDstValues,widthHeight);
}
inline IppStatus ippmEigenValuesVectorsSym_m_P(const Ipp64f** ppSrc, int srcRoiShift,
                                                           Ipp64f*  pBuffer,
                                                           Ipp64f** ppDstVectors, int dstRoiShift,
                                                           Ipp64f*  pDstValues,   int widthHeight) {
  return ippmEigenValuesVectorsSym_m_64f_P(ppSrc,srcRoiShift,pBuffer,ppDstVectors,dstRoiShift,pDstValues,widthHeight);
}
inline IppStatus ippmEigenValuesVectorsSym_ma(const Ipp32f* pSrc, int srcStride0, int srcStride1, int srcStride2,
                                                            Ipp32f* pBuffer,
                                                            Ipp32f* pDstVectors, int dstStride0, int dstStride1, int dstStride2,
                                                            Ipp32f* pDstValues,  int widthHeight, int count) {
  return ippmEigenValuesVectorsSym_ma_32f(pSrc,srcStride0,srcStride1,srcStride2,pBuffer,pDstVectors,dstStride0,dstStride1,dstStride2,pDstValues,widthHeight,count);
}
inline IppStatus ippmEigenValuesVectorsSym_ma(const Ipp64f* pSrc, int srcStride0, int srcStride1, int srcStride2,
                                                            Ipp64f* pBuffer,
                                                            Ipp64f* pDstVectors, int dstStride0, int dstStride1, int dstStride2,
                                                            Ipp64f* pDstValues,  int widthHeight, int count) {
  return ippmEigenValuesVectorsSym_ma_64f(pSrc,srcStride0,srcStride1,srcStride2,pBuffer,pDstVectors,dstStride0,dstStride1,dstStride2,pDstValues,widthHeight,count);
}
inline IppStatus ippmEigenValuesVectorsSym_ma_P(const Ipp32f** ppSrc, int srcRoiShift, int srcStride0,
                                                            Ipp32f*  pBuffer,
                                                            Ipp32f** ppDstVectors, int dstRoiShift, int dstStride0,
                                                            Ipp32f*  pDstValues,   int widthHeight, int count) {
  return ippmEigenValuesVectorsSym_ma_32f_P(ppSrc,srcRoiShift,srcStride0,pBuffer,ppDstVectors,dstRoiShift,dstStride0,pDstValues,widthHeight,count);
}
inline IppStatus ippmEigenValuesVectorsSym_ma_P(const Ipp64f** ppSrc, int srcRoiShift, int srcStride0,
                                                            Ipp64f*  pBuffer,
                                                            Ipp64f** ppDstVectors, int dstRoiShift, int dstStride0,
                                                            Ipp64f*  pDstValues,   int widthHeight, int count) {
  return ippmEigenValuesVectorsSym_ma_64f_P(ppSrc,srcRoiShift,srcStride0,pBuffer,ppDstVectors,dstRoiShift,dstStride0,pDstValues,widthHeight,count);
}
inline IppStatus ippmEigenValuesVectorsSym_ma_L(const Ipp32f** ppSrc, int srcRoiShift, int srcStride1, int srcStride2,
                                                            Ipp32f*  pBuffer,
                                                            Ipp32f** ppDstVectors, int dstRoiShift, int dstStride1, int dstStride2,
                                                            Ipp32f*  pDstValues,   int widthHeight, int count) {
  return ippmEigenValuesVectorsSym_ma_32f_L(ppSrc,srcRoiShift,srcStride1,srcStride2,pBuffer,ppDstVectors,dstRoiShift,dstStride1,dstStride2,pDstValues,widthHeight,count);
}
inline IppStatus ippmEigenValuesVectorsSym_ma_L(const Ipp64f** ppSrc, int srcRoiShift, int srcStride1, int srcStride2,
                                                            Ipp64f*  pBuffer,
                                                            Ipp64f** ppDstVectors, int dstRoiShift, int dstStride1, int dstStride2,
                                                            Ipp64f*  pDstValues,   int widthHeight, int count) {
  return ippmEigenValuesVectorsSym_ma_64f_L(ppSrc,srcRoiShift,srcStride1,srcStride2,pBuffer,ppDstVectors,dstRoiShift,dstStride1,dstStride2,pDstValues,widthHeight,count);
}
inline IppStatus ippmEigenValuesSym_m(const Ipp32f* pSrc, int srcStride1, int srcStride2,
                                                    Ipp32f* pBuffer,
                                                    Ipp32f* pDstValues, int widthHeight) {
  return ippmEigenValuesSym_m_32f(pSrc,srcStride1,srcStride2,pBuffer,pDstValues,widthHeight);
}
inline IppStatus ippmEigenValuesSym_m(const Ipp64f* pSrc, int srcStride1, int srcStride2,
                                                    Ipp64f* pBuffer,
                                                    Ipp64f* pDstValues, int widthHeight) {
  return ippmEigenValuesSym_m_64f(pSrc,srcStride1,srcStride2,pBuffer,pDstValues,widthHeight);
}
inline IppStatus ippmEigenValuesSym_m_P(const Ipp32f** ppSrc, int srcRoiShift,
                                                    Ipp32f*  pBuffer,
                                                    Ipp32f*  pDstValues, int widthHeight) {
  return ippmEigenValuesSym_m_32f_P(ppSrc,srcRoiShift,pBuffer,pDstValues,widthHeight);
}
inline IppStatus ippmEigenValuesSym_m_P(const Ipp64f** ppSrc, int srcRoiShift,
                                                    Ipp64f*  pBuffer,
                                                    Ipp64f*  pDstValues, int widthHeight) {
  return ippmEigenValuesSym_m_64f_P(ppSrc,srcRoiShift,pBuffer,pDstValues,widthHeight);
}
inline IppStatus ippmEigenValuesSym_ma(const Ipp32f* pSrc, int srcStride0, int srcStride1, int srcStride2,
                                                     Ipp32f* pBuffer,
                                                     Ipp32f* pDstValues, int widthHeight, int count) {
  return ippmEigenValuesSym_ma_32f(pSrc,srcStride0,srcStride1,srcStride2,pBuffer,pDstValues,widthHeight,count);
}
inline IppStatus ippmEigenValuesSym_ma(const Ipp64f* pSrc, int srcStride0, int srcStride1, int srcStride2,
                                                     Ipp64f* pBuffer,
                                                     Ipp64f* pDstValues, int widthHeight, int count) {
  return ippmEigenValuesSym_ma_64f(pSrc,srcStride0,srcStride1,srcStride2,pBuffer,pDstValues,widthHeight,count);
}
inline IppStatus ippmEigenValuesSym_ma_P(const Ipp32f** ppSrc, int srcRoiShift, int srcStride0,
                                                     Ipp32f*  pBuffer,
                                                     Ipp32f*  pDstValues, int widthHeight, int count) {
  return ippmEigenValuesSym_ma_32f_P(ppSrc,srcRoiShift,srcStride0,pBuffer,pDstValues,widthHeight,count);
}
inline IppStatus ippmEigenValuesSym_ma_P(const Ipp64f** ppSrc, int srcRoiShift, int srcStride0,
                                                     Ipp64f*  pBuffer,
                                                     Ipp64f*  pDstValues, int widthHeight, int count) {
  return ippmEigenValuesSym_ma_64f_P(ppSrc,srcRoiShift,srcStride0,pBuffer,pDstValues,widthHeight,count);
}
inline IppStatus ippmEigenValuesSym_ma_L(const Ipp32f** ppSrc, int srcRoiShift, int srcStride1, int srcStride2,
                                                     Ipp32f*  pBuffer,
                                                     Ipp32f*  pDstValues, int widthHeight, int count) {
  return ippmEigenValuesSym_ma_32f_L(ppSrc,srcRoiShift,srcStride1,srcStride2,pBuffer,pDstValues,widthHeight,count);
}
inline IppStatus ippmEigenValuesSym_ma_L(const Ipp64f** ppSrc, int srcRoiShift, int srcStride1, int srcStride2,
                                                     Ipp64f*  pBuffer,
                                                     Ipp64f*  pDstValues, int widthHeight, int count) {
  return ippmEigenValuesSym_ma_64f_L(ppSrc,srcRoiShift,srcStride1,srcStride2,pBuffer,pDstValues,widthHeight,count);
}

#endif
