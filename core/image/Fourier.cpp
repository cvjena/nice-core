//
// C++ Implementation: Fourier
//
// Description:
//
//
// Author: Michael Koch <Koch.Michael@uni-jena.de>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
/**
 * @file Fourier.cpp
 * @brief Fourier
 * @author Michael Koch
 * @date Fr Jul 24 2009
 */

// #define DEBUG
#undef DEBUG

//normal includes
#include "Fourier.h"

//IF ICE is available TODO REPLACE BY FFTW DIRECTLY
#ifdef NICE_USELIB_ICE 
#include "core/iceconversion/image_convertice.h"
#include <image_nonvis.h>

using namespace NICE;

void Fourier::FourierTransform(NICE::FloatImage &space_real, NICE::FloatImage &space_imag, NICE::FloatImage &freq_real, NICE::FloatImage &freq_imag)
{
#ifdef NICE_USELIB_ICE 
    if (space_real.width() != space_imag.width() || space_real.height() != space_imag.height())
    {
         fthrow(ImageException, "Fourier_FourierTransform: Image Dimension do not agree.");
    }
    else
    {
        freq_real.resize(space_real.width(), space_real.height());
        freq_imag.resize(space_real.width(), space_real.height());
        freq_real.set(0);
        freq_imag.set(0);
        //create ICE Images
        ice::ImageD space_realD, space_imagD, freq_realD, freq_imagD;
        space_realD = NICE::createIceImageD(space_real);
        space_imagD = NICE::createIceImageD(space_imag);
        freq_realD=NICE::createIceImageD(freq_real);
        freq_imagD=NICE::createIceImageD(freq_imag);
        //Fourier Transform and store results
        ice::FourierImgD(space_realD, space_imagD, 15, freq_realD, freq_imagD);
        NICE::copyFloatImage(freq_realD, freq_real);
        NICE::copyFloatImage(freq_imagD, freq_imag);
        FreeImgD(space_realD);FreeImgD(space_imagD);FreeImgD(freq_realD);FreeImgD(freq_imagD);
    }
#else
    fthrow(ImageException, "ICE essential, TODO: Change to FFTW directly");
#endif
    
}


void Fourier::FourierTransformInverse(NICE::FloatImage &freq_real, NICE::FloatImage &freq_imag, NICE::FloatImage &space_real, NICE::FloatImage &space_imag)
{
#ifdef NICE_USELIB_ICE 
     if (freq_real.width() != freq_imag.width() || freq_real.height() != freq_imag.height())
     {
          fprintf(stderr, "Fourier_FourierTransformInverse: Image Dimension must agree!\n");
          fthrow(ImageException, "Fourier_FourierTransformInverse: Image Dimension do not agree.");
     }
     else
     {
          space_real.resize(freq_real.width(), freq_real.height());
          space_imag.resize(freq_real.width(), freq_real.height());
          space_real.set(0);
          space_imag.set(0);
        //create ICE Images
          ice::ImageD space_realD, space_imagD, freq_realD, freq_imagD;
          space_realD = NICE::createIceImageD(space_real);
          space_imagD = NICE::createIceImageD(space_imag);
          freq_realD = NICE::createIceImageD(freq_real);
          freq_imagD = NICE::createIceImageD(freq_imag);
        //Fourier Transform Inverse and store results
          ice::FourierImgD(freq_realD, freq_imagD,16,space_realD, space_imagD );
          NICE::copyFloatImage(space_realD, space_real);
          NICE::copyFloatImage(space_imagD, space_imag);
          FreeImgD(space_realD);FreeImgD(space_imagD);FreeImgD(freq_realD);FreeImgD(freq_imagD);
     }
#else
     fthrow(ImageException, "ICE essential, TODO: Change to FFTW directly");
#endif
}

void Fourier::CrossCorrelation(const NICE::FloatImage &img1, const NICE::FloatImage &img2, NICE::FloatImage &cc)
{
#ifdef NICE_USELIB_ICE 
     if (img1.width() != img2.width() || img1.height() != img2.height())
     {
          fprintf(stderr, "Fourier_CrossCorrelation: Image Dimension must agree!\n");
          fthrow(ImageException, "Fourier_CrossCorrelation: Image Dimension do not agree.");
     }
     else
     {
          //create ICE Images
          ice::ImageD img1D, img2D,ccD;
          img1D=NICE::createIceImageD(img1);
          img2D=NICE::createIceImageD(img2);
          ccD=ice::NewImgD(img1.width(),img1.height());

          CrossCorrelationImgD(img1D,img2D,ccD);
        
          NICE::copyFloatImage(ccD,cc);
          FreeImgD(img1D);FreeImgD(img2D);FreeImgD(ccD);
     }
#else
     fthrow(ImageException, "ICE essential, TODO: Change to FFTW directly");
#endif
}
#endif
