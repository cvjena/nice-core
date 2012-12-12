//
// C++ Interface: Fourier
//
// Description: 
//
//
// Author: Michael Koch <Koch.Michael@uni-jena.de>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
/** 
 * @file Fourier.h
 * @brief Fourier Transformation of Float Images
 * @author Michael Koch
 * @date Fr Jul 24 2009
 */
 
#ifndef NICE_Fourier_INCLUDE
#define NICE_Fourier_INCLUDE
#include "core/image/ImageT.h"

#ifdef NICE_USELIB_ICE 

namespace NICE {

     class Fourier
     {
          public:
          
               /**
                * @param space_real real image in signalspace 
                * @param space_imag imaginary image in signalspace
                * @param freq_real real image in frequencyspace
                * @param freq_imag imaginary image in frequencyspace
                */
               static void FourierTransform (FloatImage &space_real, FloatImage &space_imag, FloatImage &freq_real, FloatImage &freq_imag );
               /**
                * @param freq_real real image in frequencyspace
                * @param freq_imag imaginary image in frequencyspace
                * @param space_real real image in signalspace 
                * @param space_imag imaginary image in signalspace
                */
               static void FourierTransformInverse (NICE::FloatImage &freq_real, NICE::FloatImage &freq_imag,NICE::FloatImage &space_real, NICE::FloatImage &space_imag);
               
               /**
                * Cross Correlation of two FloatImages
                * @param img1 Image 1
                * @param img2 Image 2
                * @param cc Crosscorrelation of Image 1 and Image 2
                */
               static void CrossCorrelation(const NICE::FloatImage &img1,const NICE::FloatImage &img2, NICE::FloatImage &cc);
     };
}//namespace
#endif
#endif
