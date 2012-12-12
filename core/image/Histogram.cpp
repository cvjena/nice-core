
/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libimage - An image/template for new NICE libraries
 * See file License for license information.
 */
/*****************************************************************************/

/*! \file Histogram.cpp
    \brief Histogram class definitions
 */

#include <core/image/Histogram.h>

namespace NICE {

Histogram::Histogram() {

    _channels   = 1;
    _min        = 0;
    _max        = 0;
    _nobins     = 0;
    _diff       = 0;
    _data       = NULL;
}

Histogram::Histogram(const Ipp32s& bins) {

    _channels   = 1;
    _min        = 0;
    _max        = 256;
    _nobins     = bins;
    _diff       = 256;
    _data       = new VectorT<value_type>(_nobins,0);
}

Histogram::Histogram(const Ipp32s& min, const Ipp32s& max, const Ipp32s& bins) {

    _channels   = 1;
    _min        = min;
    _max        = max;
    _nobins     = (bins<0)?_max-_min:bins;
    _diff       = _max-_min;
    _data       = new VectorT<value_type>(_nobins,0);
}

Histogram::Histogram(const Image& src, const Ipp32s& min, const Ipp32s& max, const Ipp32s& bins) {

    _channels   = 1;
    _min        = min;
    _max        = max;
    _nobins     = (bins<0)?_max-_min:bins;
    _diff       = _max-_min;
    _data       = new VectorT<value_type>(_nobins,0);

    #ifdef NICE_USELIB_IPP

        Ipp32u noLevels = _nobins+1;
        Ipp32s pLevels[noLevels];

        IppStatus ret = ippiHistogramEven_C1R(src.getPixelPointer(), src.getStepsize(),
                                              makeROIFullImage(src),
                                              (Ipp32s*)_data->getDataPointer(),
                                              pLevels, noLevels, min, max);

        if(ret!=ippStsNoErr)
            fthrow(ImageException, ippGetStatusString(ret));

    #else // NICE_USELIB_IPP
        const Ipp8u* pSrc;
        const Ipp8u* pSrcStart = src.getPixelPointer();

        if(_min==0&&_max==256)
            for(int y=0; y<src.height(); ++y) {
                pSrc = pSrcStart;

                for(int x=0; x<src.width(); ++x,++pSrc)
                    (*_data)[((*pSrc-_min)*_nobins)/_diff]++;

                pSrcStart += src.getStepsize();
            }
        else
            for(int y=0; y<src.height(); ++y) {
                pSrc = pSrcStart;

                for(int x=0; x<src.width(); ++x,++pSrc)
                    if(isWithin(*pSrc))
                        (*_data)[((*pSrc-_min)*_nobins)/_diff]++;

                pSrcStart += src.getStepsize();
            }
    #endif // NICE_USELIB_IPP
}

Histogram::Histogram(const Image& src, const Ipp32s& min, const Ipp32s& max,
                     const Rect& rect, const Ipp32s& bins) {

          Rect      tgtRect = clipRect(src, rect);
    const Image tgtImg  = src.subImage(tgtRect);

    _channels   = 1;
    _min        = min;
    _max        = max;
    _nobins     = (bins<0)?_max-_min:bins;
    _diff       = _max-_min;
    _data       = new VectorT<value_type>(_nobins,0);

    #ifdef NICE_USELIB_IPP

        Ipp32u noLevels = _nobins+1;
        Ipp32s pLevels[noLevels];

        IppStatus ret = ippiHistogramEven_C1R(tgtImg.getPixelPointer(), 
                                              tgtImg.getStepsize(),
                                              makeROIFullImage(tgtImg),
                                              _data->getDataPointer(),
                                              pLevels, noLevels, min, max);

        if(ret!=ippStsNoErr)
            fthrow(ImageException, ippGetStatusString(ret));

    #else // NICE_USELIB_IPP
        const Ipp8u* pSrc;
        const Ipp8u* pSrcStart = tgtImg.getPixelPointer();

        if(_min==0&&_max==256)
            for(int y=0; y<tgtImg.height(); ++y) {
                pSrc = pSrcStart;

                for(int x=0; x<tgtImg.width(); ++x,++pSrc)
                    (*_data)[((*pSrc-_min)*_nobins)/_diff]++;

                pSrcStart += src.getStepsize();
            }
        else
            for(int y=0; y<tgtImg.height(); ++y) {
                pSrc = pSrcStart;

                for(int x=0; x<tgtImg.width(); ++x,++pSrc)
                    if(isWithin(*pSrc))
                        (*_data)[((*pSrc-_min)*_nobins)/_diff]++;

                pSrcStart += src.getStepsize();
            }
    #endif // NICE_USELIB_IPP   
}

Histogram::Histogram(const ColorImage& src, const Ipp32s& min, const Ipp32s& max, const Ipp32s& bins) {

    _channels   = 3;
    _min        = min;
    _max        = max;
    _nobins     = (bins<0)?_max-_min:bins;
    _diff       = _max-_min;    
    _data       = new VectorT<value_type>(3*_nobins,0);

    #ifdef NICE_USELIB_IPP
        Ipp32u noLevels = _nobins+1;
        Ipp32s *pLevels[_channels];
        int     nLevels[_channels];
        Ipp32s  tLevels[3*noLevels];

        Ipp32s *pHist[_channels], pmin[_channels], pmax[_channels];

        for(int i=0;i<3;i++) {
            pHist[i]     = (Ipp32s*)(_data->getDataPointer() + i*_nobins);
            pLevels[i]   = &tLevels[i*noLevels];
            nLevels[i]   = noLevels;
            pmin[i]      = _min;
            pmax[i]      = _max;
        }

        IppStatus ret = ippiHistogramEven_C3R(src.getPixelPointer(), src.getStepsize(),
                                              makeROIFullImage(src), pHist,
                                              pLevels, nLevels, pmin, pmax);

        if(ret!=ippStsNoErr)
            fthrow(ImageException, ippGetStatusString(ret));

    #else // NICE_USELIB_IPP
        const Ipp8u* pSrc;
        const Ipp8u* pSrcStart = src.getPixelPointer();

        Ipp32u index;

        if(_min==0 && _max==256)
            for(int y=0; y<src.height(); ++y) {
                pSrc = pSrcStart;

                for(int x=0; x<src.width(); ++x)
                    for(int i=0; i<3; ++i,++pSrc) {
                        index  = ((*pSrc-_min)*_nobins)/_diff;
                        (*_data)[index + i*_nobins]++;
                    }

                pSrcStart += src.getStepsize();
            }
        else
            for(int y=0; y<src.height(); ++y) {
                pSrc = pSrcStart;

                for(int x=0; x<src.width(); ++x)
                    for(int i=0; i<3; ++i,++pSrc)
                        if(isWithin(*pSrc)) {
                            index  = ((*pSrc-_min)*_nobins)/_diff;
                            (*_data)[index + i*_nobins]++;
                        }

                pSrcStart += src.getStepsize();
            }
    #endif // NICE_USELIB_IPP
}

Histogram::Histogram(const ColorImage& src, const Ipp32s& min, const Ipp32s& max,
                     const Ipp32s& bins, const bool noLum) {

    _min        = min;
    _max        = max;
    _nobins     = (bins<0)?_max-_min:bins;
    init_b();
    _diff       = _max-_min;
    _channels   = (noLum==false)?3:2;
    _data     = new VectorT<value_type>( (_channels==3)?(_b[0]+_b[1]+_b[2]):(_b[1]+_b[2]), 0 );

    const Ipp8u* pSrc;
    const Ipp8u* pSrcStart = src.getPixelPointer();

    // noLum = false, include lum channel into calculation
    if(!noLum) {
        if(_min==0 && _max==256)
            for(int y=0; y<src.height(); ++y) {
                pSrc = pSrcStart;

                for(int x=0; x<src.width(); ++x,pSrc+=3)
                    (*_data)[ ((*pSrc-_min)*_b[0] + (*(pSrc+1)-_min)*_b[1] + (*(pSrc+2)-_min)*_b[2])/_diff ]++;

                pSrcStart += src.getStepsize();
            }
        else
            for(int y=0; y<src.height(); ++y) {
                pSrc = pSrcStart;

                for(int x=0; x<src.width(); ++x,pSrc+=3)
                    if(isWithin(*pSrc) && isWithin(*(pSrc+1)) && isWithin(*(pSrc+2)) )
                        (*_data)[ ((*pSrc-_min)*_b[0] + (*(pSrc+1)-_min)*_b[1] + (*(pSrc+2)-_min)*_b[2])/_diff ]++;

                pSrcStart += src.getStepsize();
            }
    }
    // first channel is ignored
    else {
        if(_min==0 && _max==256)
            for(int y=0; y<src.height(); ++y) {
                pSrc = pSrcStart;

                for(int x=0; x<src.width(); ++x,pSrc+=3)
                    (*_data)[ ((*(pSrc+1)-_min)*_b[1]+(*(pSrc+2)-_min)*_b[2])/_diff ]++;

                pSrcStart += src.getStepsize();
            }
        else
            for(int y=0; y<src.height(); ++y) {
                pSrc = pSrcStart;

                for(int x=0; x<src.width(); ++x,pSrc+=3)
                    if( isWithin(*(pSrc+1)) && isWithin(*(pSrc+2)) )
                        (*_data)[ ((*(pSrc+1)-_min)*_b[1]+(*(pSrc+2)-_min)*_b[2])/_diff ]++;

                pSrcStart += src.getStepsize();
            }
    }
}

Ipp32u Histogram::reproject(const Ipp8u& c1, const Ipp8u& c2, const Ipp8u& c3) {
    if(channels()==1 || (size()>0 && size()==3*bins()))
    	fthrow(ImageException,"No combined histogram is used.");

    if(_channels==2)
        return ((c2-_min)*_b[1]+(c3-_min)*_b[2])/_diff;
    else
        return ((c1-_min)*_b[0]+(c2-_min)*_b[1]+(c3-_min)*_b[2])/_diff;
}

Histogram::value_type Histogram::sum() const{
    return _data->Sum();
}

//

FloatVector* Histogram::normalized() {

    FloatVector* result        = new FloatVector(size());
    Ipp32f sum                 = static_cast<Ipp32f>(this->sum());

    #ifdef NICE_USELIB_IPP

        IppStatus ret;

        ret = ippsConvert_32s32f(getDataPointer(),
                                 result->getDataPointer(),
                                 size());

        if(ret!=ippStsNoErr)
            fthrow(ImageException, ippGetStatusString(ret));

        ret = ippsNormalize_32f(result->getDataPointer(),
                                result->getDataPointer(),
                                result->size(),
                                0.0, sum);

        if(ret!=ippStsNoErr)
            fthrow(ImageException, ippGetStatusString(ret));

    #else // NICE_USELIB_IPP
        
        FloatVector::iterator pDst = result->begin();
        for(iterator i=begin(); i!=end(); ++i,++pDst)
            *pDst = *i/sum;

    #endif

    return result;
}

IntVector* Histogram::cumulative() {
    IntVector* result        = new IntVector(size());
    IntVector::iterator pDst =  result->begin();
    *pDst++                  = *(_data->begin());
    for(VectorT<value_type>::iterator i=begin()+1; i!=end(); ++i,++pDst)
        *pDst = *i+*(pDst-1);

    return result;
}

//

Ipp32u Histogram::minIndex() const {
    return _data->MinIndex();
}

Ipp32u Histogram::maxIndex() const {
    return _data->MaxIndex();
}

// // // // // Input / Output // // // // //

bool Histogram::read(const std::string &filename) {
    std::ifstream ifs(filename.c_str());

    if(!ifs)
        return false;

    int tsize;
    ifs >> tsize >> _channels >> _nobins >> _min >> _max;

    init_b();
    _diff = _max-_min;
    _data = new VectorT<value_type>(tsize);

    for(iterator i=begin(); i!=end(); ++i)
        ifs >> *i;

    ifs.close();

    return true;
}

bool Histogram::write(const std::string &filename) {
    std::ofstream ofs(filename.c_str());

    if(!ofs)
        return false;

    ofs << size() << "\n" << _channels << "\n" << _nobins << "\n" << _min << "\n" << _max << "\n";

    for(iterator i=begin(); i!=end(); ++i)
        ofs << *i << "\n";

    ofs.close();

    return true;
}





} // namespace NICE




