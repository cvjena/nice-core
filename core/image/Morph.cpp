
#include "core/image/Morph.h"
#include "core/image/ImageTools.h"
#include <math.h>
#include <limits>

#include <iostream>
using namespace std;

namespace NICE {

// little helper function

    static inline size_t getHistRank(const Histogram& hist, const size_t& rank)
    {
        uint sum = 0;
        for(Histogram::const_iterator i=hist.begin(); i!=hist.end(); ++i) {
            sum += *i;
            if(sum<rank) continue;
            return(i-hist.begin());
        }
        return hist.size();
    }

    static inline Ipp32s erodeNext(const Image& src, Histogram& hist, const int& size,
                            int& hist_val, int& hist_min, const int& x, const int& y)
    {
        int i;

        i=-size;
        do {
            hist_val = src.getPixelQuick(x+1,y+i);
            ++hist[hist_val];
            hist_min = (hist_val<hist_min)?hist_val:hist_min;

            ++i;
        } while(i<=size);

        i=-size;
        do {
            hist_val = src.getPixelQuick(x-2,y+i);
            --hist[hist_val];
            if( (hist_val-hist_min)==0 )
                if(hist[hist_val]==0)
                    while(hist[hist_min]==0)
                        ++hist_min;

            ++i;
        } while(i<=size);

        return hist_min;
    }

    static inline Ipp32s dilateNext(const Image& src, Histogram& hist, const int& isize,
                             int& hist_val, int& hist_max, int x, int y)
    {
        int i;

        i=-isize;
        do {
            hist_val = src.getPixelQuick(x+isize,y+i);
            ++hist[hist_val];
            hist_max = (hist_val>hist_max)?hist_val:hist_max;

            ++i;
        } while(i<=isize);

        i=-isize;
        do {
            hist_val = src.getPixelQuick(x-isize-1,y+i);
            --hist[hist_val];
            if((hist_val-hist_max)==0)
                if(hist[hist_max]==0)
                    while(hist[hist_max]==0)
                        --hist_max;

            ++i;
        } while(i<=isize);

        return hist_max;
    }

    static inline Ipp32s medianNext(const Ipp8u& hist_val, Histogram& hist, int& hist_temp,
                                    int& hist_med, uint& hist_lower, uint& hist_upper, bool add=true)
    {
        if(add) {
            ++hist[hist_val];
            if(hist_med<0) {
                hist_lower = hist_upper = 0;
                hist_med   = hist_val;
            }
            else if(hist_val < hist_med)
                ++hist_lower;
            else if(hist_val > hist_med)
                ++hist_upper;
        }
        else {
            --hist[hist_val];
            if(hist_val < hist_med)
                --hist_lower;
            else if(hist_val > hist_med)
                --hist_upper;
        }

        if(hist_lower>hist[hist_med]+hist_upper) {
            hist_temp = hist_med-1;
            while(hist[hist_temp]==0)
                --hist_temp;

            hist_lower -= hist[hist_temp];
            hist_upper += hist[hist_med];
            hist_med    = hist_temp;
        }
        else if(hist_upper>=hist[hist_med]+hist_lower) {
            hist_temp = hist_med+1;
            while(hist[hist_temp]==0)
                ++hist_temp;

            hist_upper -= hist[hist_temp];
            hist_lower += hist[hist_med];
            hist_med    = hist_temp;
        }

        return hist_med;
    }

// // // // // Ranking Operations

Image* rank(const Image& src, const uint& size, const uint& rank, Image* dst)
{
    if( rank>((2*size+1)*(2*size+1)) || rank<1 )
        fthrow(ImageException,"Rank smaller 1 or bigger than (2*size+1)x(2*size+1) not allowed.");

    Image* result = createResultBuffer(src, dst);
    copyBorder ( src, size, size, dst );

    int isize  = size;
    uint msize = 2*isize+1;

    const Image *imgSub = NULL;
    Histogram hist;

    int xstart = size+1;
    int xend   = src.width()-isize;
    int ystart = size;
    int yend   = src.height()-isize;

    Image::Pixel *p;
    for(int y=ystart; y<yend; ++y) {
        delete imgSub;
        imgSub = src.createSubImage(Rect(0,y-isize,msize,msize));

        hist = Histogram(*imgSub,0,256);
        p    = result->getPixelPointerXY(isize,y);
        *p++ = getHistRank(hist, rank);

        for(int x=xstart; x<xend; ++x,++p) {
            for(int i=-isize; i<=+isize; ++i) {
                hist[src.getPixelQuick(x-isize-1,y+i)] -= 1;
                hist[src.getPixelQuick(x+isize  ,y+i)] += 1;
            }
            *p = getHistRank(hist, rank);
        }
    }

    // clean up
    delete imgSub;

    return result;
};

Image* erode(const Image& src, Image* dst, const size_t& size)
{
    Image* result = createResultBuffer(src, dst);
    copyBorder ( src, size, size, dst );

    #ifdef NICE_USELIB_IPP
        IppStatus ret;
        IppiPoint anchor = {(int)size, (int)size};
        IppiSize ROIsize = {(int)(src.width()-2*size), (int)(src.height()-2*size)};

        // 3x3
        if(size==1) {
            ret = ippiErode3x3_8u_C1R(src.getPixelPointerXY(1,1),
                                      src.getStepsize(),
                                      result->getPixelPointerXY(1,1),
                                      result->getStepsize(), ROIsize);
        }
        else
        {
            IppiSize maskSize  = {(int)(2*size+1), (int)(2*size+1)};
            Ipp8u *pMask       = new Ipp8u[(2*size+1)*(2*size+1)];
            ippiSet_8u_C1R(1,pMask,2*size+1,maskSize);

            ret = ippiErode_8u_C1R(src.getPixelPointerXY(anchor.x, anchor.y),
                                   src.getStepsize(),
                                   result->getPixelPointerXY(anchor.x, anchor.y),
                                   result->getStepsize(),
                                   ROIsize, pMask, maskSize, anchor);
        }

        if(ret!=ippStsNoErr)
                fthrow(ImageException, ippGetStatusString(ret));

    #else // NICE_USELIB_IPP
        int isize  = size;
        int xstart = size+1;
        int xend   = src.width()-isize;

        Histogram hist(256);
        int hist_min, hist_val;

        const Image::Pixel* pSrc;
        Image::Pixel*       pDst;
        for(int y=size; y<src.height()-isize; ++y) {
            hist     = 0;
            hist_min = std::numeric_limits<int>::max();
            for(int sy=-isize; sy<=isize; ++sy) {
                for(int sx=-isize; sx<=+isize; ++sx,++pSrc) {
                    hist_val = src.getPixelQuick(size+sx,y+sy);
                    ++hist[hist_val];
                    if(hist_val<hist_min)
                        hist_min = hist_val;
                }
            }
            pDst  = result->getPixelPointerXY(isize,y);
            *pDst = hist_min;
            ++pDst;

            pSrc = src.getPixelPointerXY(xstart,y);
            for(int x=xstart; x<xend; ++x,++pSrc,++pDst)
                *pDst = erodeNext(src,hist,isize,hist_val,hist_min,x,y);
        }
        #endif // NICE_USELIB_IPP

        return result;
}

Image* median(const Image& src, Image* dst, const size_t& size)
{
    Image* result = createResultBuffer(src, dst);
    copyBorder ( src, size, size, dst );

    #ifdef NICE_USELIB_IPP
        IppiSize maskSize  = {(int)(2*size+1), (int)(2*size+1)};
        IppiPoint anchor   = {(int)size, (int)size};
        IppiSize ROIsize   = {(int)(src.width()-2*size), (int)(src.height()-2*size)};

        IppStatus ret = ippiFilterMedian_8u_C1R(src.getPixelPointerXY(anchor.x, anchor.y),
                                                src.getStepsize(),
                                                result->getPixelPointerXY(anchor.x, anchor.y),
                                                result->getStepsize(),
                                                ROIsize, maskSize, anchor);

        if(ret!=ippStsNoErr)
                fthrow(ImageException, ippGetStatusString(ret));

    #else // NICE_USELIB_IPP
        int isize  = size;
        int xstart = size+1;
        int xend   = src.width()-isize;

        Histogram hist(256);

        int  hist_med, hist_temp;
        uint hist_lower = 0;
        uint hist_upper = 0;

        const Image::Pixel* pSrc;
        Image::Pixel*       pDst;

        for(int y=size; y<src.height()-isize; ++y) {
            hist_med   = -1;
            hist       = 0;
            for(int sy=-isize; sy<=isize; ++sy)
                for(int sx=-isize; sx<=isize; ++sx)
                    medianNext(src(1+sx,y+sy),hist,hist_temp,hist_med,hist_lower,hist_upper,true);
            pDst    = result->getPixelPointerXY(isize,y);
            *pDst   = hist_med;
            ++pDst;

            for(int x=xstart; x<xend; ++x,++pSrc,++pDst) {
                for(int i=-isize; i<=+isize; ++i) {
                    medianNext(src.getPixelQuick(x+isize  ,y+i),hist,hist_temp,hist_med,hist_lower,hist_upper,true);
                    medianNext(src.getPixelQuick(x-isize-1,y+i),hist,hist_temp,hist_med,hist_lower,hist_upper,false);
                }
                *pDst = hist_med;
            }
        }
    #endif // NICE_USELIB_IPP

    return result;
}

Image* dilate(const Image& src, Image* dst, const size_t& size)
{
    Image* result = createResultBuffer(src, dst);
    copyBorder ( src, size, size, dst );

    #ifdef NICE_USELIB_IPP
        IppStatus ret;
        IppiPoint anchor = {(int)size, (int)size};
        IppiSize ROIsize = {(int)(src.width()-2*size), (int)(src.height()-2*size)};

        // 3x3
        if(size==1)
            ret = ippiDilate3x3_8u_C1R(src.getPixelPointerXY(anchor.x, anchor.y),
                                       src.getStepsize(),
                                       result->getPixelPointerXY(anchor.x, anchor.y),
                                       result->getStepsize(),
                                       ROIsize);
        else
        {
            IppiSize maskSize  = {(int)(2*size+1), (int)(2*size+1)};
            Ipp8u *pMask       = new Ipp8u[(2*size+1)*(2*size+1)];

            ippiSet_8u_C1R(1,pMask,2*size+1,maskSize);

            ret = ippiDilate_8u_C1R(src.getPixelPointerXY(anchor.x, anchor.y),
                                    src.getStepsize(),
                                    result->getPixelPointerXY(anchor.x, anchor.y),
                                    result->getStepsize(),
                                    ROIsize, pMask, maskSize, anchor);
        }

        if(ret!=ippStsNoErr)
            fthrow(ImageException, ippGetStatusString(ret));

    #else // NICE_USELIB_IPP
        int isize  = size;
        int xstart = size+1;
        int xend   = src.width()-isize;

        Histogram hist(256);
        int hist_max, hist_val;

        const Image::Pixel* pSrc;
        Image::Pixel*       pDst;
        for(int y=size; y<src.height()-isize; ++y) {
            hist     = 0;
            hist_max = std::numeric_limits<int>::min();
            for(int sy=-isize; sy<=isize; ++sy)
                for(int sx=-isize; sx<=+isize; ++sx,++pSrc) {
                    hist_val = src.getPixelQuick(size+sx,y+sy);
                    ++hist[hist_val];
                    if(hist_val>hist_max)
                        hist_max = hist_val;
                }
            pDst    = result->getPixelPointerXY(isize,y);
            *pDst   = hist_max;
            ++pDst;

            // now the rest of the line
            pSrc = src.getPixelPointerXY(xstart,y);
            for(int x=xstart; x<xend; ++x,++pSrc,++pDst)
                *pDst = dilateNext(src,hist,isize,hist_val,hist_max,x,y);
        }
    #endif // NICE_USELIB_IPP

    return result;
}

Image* opening(const Image& src, Image* dst, const size_t& size)
{
    Image* temp   = new Image(src.width(), src.height());
    temp              = erode(src, temp, size);

    Image* result = createResultBuffer(src.width(), src.height(), dst);
    result            = dilate(*temp, result, size);

        // clean up
        delete temp;

    return result;
}

Image* closing(const Image& src, Image* dst, const size_t& size)
{
    Image* temp   = new Image(src.width(), src.height());
    temp              = dilate(src, temp, size);

    Image* result = createResultBuffer(src.width(), src.height(), dst);
    result            = erode(*temp, result, size);

        // clean up
        delete temp;

    return result;
}

// // // // // ranking operations with a given mask // // // // //

    // little Helperfunction, counts the number of nonZero elements in the structureElement
    static inline size_t getNonZeroElements(const CharMatrix& structureElement)
    {
        size_t entries = 0;
        for(size_t j=0; j<structureElement.rows(); ++j)
            for(size_t i=0; i<structureElement.cols(); ++i)
                if(structureElement(j,i)!=0)
                    ++entries;

        return entries;
    }

    // little Helperfunction, creates a Matrix with coordinates of nonzero Elements
    // referring to the center of the structureElement
    static inline IntMatrix* getStructureList(const CharMatrix& structureElement, IppiPoint& min, IppiPoint& max)
    {
        size_t entries  = getNonZeroElements(structureElement);
        int anchorx     = static_cast<int>(structureElement.cols()/2);
        int anchory     = static_cast<int>(structureElement.rows()/2);
        min.x           = std::numeric_limits<int>::max();
        min.y           = std::numeric_limits<int>::max();
        max.x           = std::numeric_limits<int>::min();
        max.y           = std::numeric_limits<int>::min();

        IntMatrix *pRes = new IntMatrix(entries,2);
        size_t aPos     = 0;

        for(size_t j=0; j<structureElement.rows(); ++j)
            for(size_t i=0; i<structureElement.cols(); ++i)
                if(structureElement(j,i)!=0) {
                    (*pRes)(aPos,0) = i-anchorx;
                    (*pRes)(aPos,1) = j-anchory;

                    max.x = std::max((*pRes)(aPos,0),max.x);
                    min.x = std::min((*pRes)(aPos,0),min.x);
                    min.y = std::min((*pRes)(aPos,1),min.y);
                    max.y = std::max((*pRes)(aPos,1),max.y);

                    ++aPos;
                }
        return pRes;
    }

Image* rank(const Image& src, const CharMatrix& structureElement, const size_t& rank, Image* dst)
{
    Image* result   = createResultBuffer(src, dst);
    copyBorder ( src, structureElement.cols()/2, structureElement.rows()/2, dst );
    size_t entries      = getNonZeroElements(structureElement);

    if( entries==0 )
        fthrow(ImageException,"No Elements specified for the ranking operation.");
    if( rank>entries || rank<1 )
        fthrow(ImageException,"Rank smaller 1 or bigger than nonzero entries in the structureElement are not allowed.");

    Histogram hist(256);
    IppiPoint min,max;
    IntMatrix* strucList = getStructureList(structureElement, min, max);

    int xstart = -min.x;
    int xend   = src.width()-max.x;
    int i;

    Image::Pixel* p;
    for(int y=-min.y; y<src.height()-max.y; ++y) {
       p = result->getPixelPointerXY(xstart,y);
       for(int x=xstart; x<xend; ++x,++p) {
            hist = 0;

            i = strucList->rows()-1;
            do {
                ++hist[src(x+(*strucList)(i,0), y+(*strucList)(i,1))];
                --i;
            }
            while(i>=0);

            *p = getHistRank(hist,rank);
       }
    }

        // clean up
        delete strucList;

    return result;
};

Image* median(const Image& src, const CharMatrix& structureElement, Image* dst)
{
    Image* result = createResultBuffer(src, dst);
    size_t nonZero    = getNonZeroElements(structureElement);

    return rank(src, structureElement, ((nonZero%2==0)?nonZero/2:nonZero/2+1), result);
}

Image* erode(const Image& src, const CharMatrix& structureElement, Image* dst)
{
     Image* result = createResultBuffer(src, dst);
     copyBorder ( src, structureElement.cols()/2, structureElement.rows()/2, dst );

#ifdef NICE_USELIB_IPP
// temporary bugfix: do not use IPP (bug on 64bit systems)
//#define NICE_USELIB_IPP_ERODE
#endif
     
#ifdef NICE_USELIB_IPP_ERODE
        IppiPoint anchor  = {structureElement.cols()/2, structureElement.rows()/2};
        IppiSize maskSize = {structureElement.cols()  , structureElement.rows()};
        IppiSize ROIsize  = {src.width()-structureElement.cols()-1, src.height()-structureElement.rows()-1};

        MatrixT<unsigned char> sEl(structureElement.cols(), structureElement.rows());
        for(uint j=0; j<structureElement.rows(); ++j)
            for(uint i=0; i<structureElement.cols(); ++i)
                sEl(i,j) = (structureElement(j,i)==0)?0:1;

        IppStatus ret = ippiErode_8u_C1R(src.getPixelPointerXY(anchor.x,anchor.y),
                                         src.getStepsize(),
                                         result->getPixelPointerXY(anchor.x,anchor.y),
                                         result->getStepsize(),
                                         ROIsize, sEl.getDataPointer(),
                                         maskSize, anchor);

        if(ret!=ippStsNoErr)
                fthrow(ImageException, ippGetStatusString(ret));

#else // NICE_USELIB_IPP_ERODE
        result = rank(src, structureElement, 1, dst);
#endif // NICE_USELIB_IPP_ERODE

    return result;
}

Image* dilate(const Image& src, const CharMatrix& structureElement, Image* dst)
{
    Image* result = createResultBuffer(src, dst);
    copyBorder ( src, structureElement.cols()/2,  structureElement.rows()/2, dst );

    #ifdef NICE_USELIB_IPP
        IppiPoint anchor  = {(int)(structureElement.cols()/2), (int)(structureElement.rows()/2)};
        IppiSize maskSize = {(int)(structureElement.cols()), (int)(structureElement.rows())};
        IppiSize ROIsize  = {(int)(src.width()-structureElement.cols()-1), (int)(src.height()-structureElement.rows()-1)};

        MatrixT<unsigned char> sEl(structureElement.rows(), structureElement.cols());
        for(uint j=0; j<structureElement.rows(); ++j)
            for(uint i=0; i<structureElement.cols(); ++i)
                sEl(j,i) = (structureElement(j,i)==0) ? 0 : 1;

		// IPP seems to ignore black patches and we get a strange image 
		// afterwards (one some machines!!) with grayvalues of 128 etc.
		// Fixed 15.12.2011 by erik after a TestMorph test case failed
		result->set(0.0);

        IppStatus ret = ippiDilate_8u_C1R(src.getPixelPointerXY(anchor.x,anchor.y),
                                          src.getStepsize(),
                                          result->getPixelPointerXY(anchor.x,anchor.y),
                                          result->getStepsize(),
                                          ROIsize, sEl.getDataPointer(),
                                          maskSize, anchor);

        if(ret!=ippStsNoErr)
                fthrow(ImageException, ippGetStatusString(ret));

    #else // NICE_USELIB_IPP
        result = rank(src, structureElement, getNonZeroElements(structureElement), dst);
    #endif // NICE_USELIB_IPP

    return result;
}

Image* opening(const Image& src, const CharMatrix& structureElement, Image* dst)
{
    Image* temp   = new Image(src.width(), src.height());
    temp              = erode(src, structureElement, temp);

    Image* result = createResultBuffer(src.width(), src.height(), dst);
    result            = dilate(*temp, structureElement, result);

    // clean up
    delete temp;

    return result;
}

Image* closing(const Image& src, const CharMatrix& structureElement, Image* dst)
{
    Image* temp   = new Image(src.width(), src.height());
    temp              = dilate(src, structureElement, temp);

    Image* result = createResultBuffer(src.width(), src.height(), dst);
    result            = erode(*temp, structureElement, result);

        // clean up
        delete temp;

    return result;
}





// // // // // IP Operations // // // // //

void rankingIP(Image& src, const uint& rank)
{
    if( rank>9 || rank<1 )
        fthrow(ImageException,"Rank is out of range.");

    Histogram hist(256);
    Image::Pixel* p;

    Ipp8u* buffer     = new Ipp8u[src.width()];
    buffer[0]         = buffer[src.width()-1] = 0;
    Ipp8u* temp       = new Ipp8u[2];

        // init buffer with the first image line (y=1)
        hist = 0;
        for(int j=-1; j<=+1; ++j)
            for(int i=-1; i<=+1; ++i)
                ++hist[src(1+i,1+j)];
        buffer[1] = getHistRank(hist, rank);

        p = src.getPixelPointerXY(2,1);
        for(int x=2; x<src.width()-1; ++x,++p)
            for(int i=-1; i<=+1; ++i) {
            ++hist[*(p+1+i*src.getStepsize())];
            --hist[*(p-2+i*src.getStepsize())];
            buffer[x] = getHistRank(hist, rank);
        }

    for(int y=2; y<=src.height()-2; ++y) {
        hist = 0;
        for(int j=-1; j<=+1; ++j)
            for(int x=0; x<=2; ++x)
                ++hist[src(x,y+j)];
        temp[0] = getHistRank(hist, rank);

        for(int i=-1; i<=+1; ++i) {
            ++hist[src(3,y+i)];
            --hist[src(0,y+i)];
        }
        temp[1] = getHistRank(hist, rank);

        p = src.getPixelPointerXY(1,y-1);
        for(int x=3; x<=src.width()-2; ++x) {
            for(int i=-1; i<=+1; ++i) {
                ++hist[*(p+3+(i+1)*src.getStepsize())];
                --hist[*(p  +(i+1)*src.getStepsize())];
            }

            *p++        = buffer[x-2];
            buffer[x-2] = temp[0];
            temp[0]     = temp[1];
            temp[1]     = getHistRank(hist,rank);
        }

        // write buffer
        *p++                  = buffer[src.width()-3];
        *p++                  = buffer[src.width()-2];
        buffer[src.width()-3] = temp[0];
        buffer[src.width()-2] = temp[1];
    }

    // copy buffer to last line
    memcpy(src.getPixelPointerXY(1,src.height()-2), &buffer[1], src.width()-2);

    // clean up
    delete[] buffer;
    delete[] temp;
}

void erodeIP(Image& src)
{
    #ifdef NICE_USELIB_IPP
        IppiSize ROIsize = {src.width()-2, src.height()-2};
        IppStatus ret    = ippiErode3x3_8u_C1IR(src.getPixelPointerXY(1,1), src.getStepsize(), ROIsize);

        if(ret!=ippStsNoErr)
            fthrow(ImageException, ippGetStatusString(ret));

    #else
        Histogram hist(256);
        int hist_min, hist_val;

        Image::Pixel* p;

        Ipp8u* buffer     = new Ipp8u[src.width()];
        buffer[0]         = buffer[src.width()-1] = 0;
        Ipp8u* temp       = new Ipp8u[2];

        // init buffer with the first image line (y=1)
            // init hist
            hist     = 0;
            hist_min = std::numeric_limits<int>::max();
            for(int y=0; y<=2; ++y)
                for(int x=0; x<=2; ++x) {
                    hist_val = src.getPixelQuick(x,y);
                    hist_min = (hist_val<hist_min)?hist_val:hist_min;
                    ++hist[hist_val];
                }
            buffer[0] = buffer[src.width()-1] = 0;
            buffer[1] = hist_min;
            // init buffer
            for(int x=2; x<src.width()-1; ++x)
                buffer[x] = erodeNext(src,hist,1,hist_val,hist_min,x,1);

        for(int y=2; y<=src.height()-2; ++y) {
            // init hist && fill up temp buffer
            hist     = 0;
            hist_min = std::numeric_limits<int>::max();
            for(int j=-1; j<=1; ++j)
                for(int i=-1; i<=1; ++i) {
                    hist_val = src(1+i,y+j);
                    hist_min = (hist_val<hist_min)?hist_val:hist_min;
                    ++hist[hist_val];
                }
            temp[0] = hist_min;
            temp[1] = erodeNext(src,hist,1,hist_val,hist_min,2,y);

            // rest of line
            p = src.getPixelPointerXY(1,y-1);
            for(int x=3; x<=src.width()-2; ++x) {
                erodeNext(src,hist,1,hist_val,hist_min,x,y);

                *p          = buffer[x-2]; ++p;
                buffer[x-2] = temp[0];
                temp[0]     = temp[1];
                temp[1]     = hist_min;
            }

        // write buffer
        *p = buffer[src.width()-3]; ++p;
        *p = buffer[src.width()-2]; ++p;
        buffer[src.width()-3] = temp[0];
        buffer[src.width()-2] = temp[1];
    }

    // copy buffer to last line
    memcpy(src.getPixelPointerXY(1,src.height()-2), &buffer[1], src.width()-2);

        // clean up
        delete[] buffer;
        delete[] temp;

    #endif
}

void medianIP(Image& src) {
    Histogram hist(256);
    int  hist_med, hist_temp;
    uint hist_lower = 0;
    uint hist_upper = 0;

    Ipp8u* buffer     = new Ipp8u[src.width()];
    buffer[0]         = buffer[src.width()-1] = 0;
    Ipp8u* temp       = new Ipp8u[2];

    Ipp8u* p;

        // init buffer with the first image line (y=1)
            // init hist
            hist       = 0;
            hist_med   = -1;
            for(int y=0; y<=2; ++y)
                for(int x=0; x<=2; ++x)
                    medianNext(src.getPixelQuick(x,y),hist,hist_temp,hist_med,hist_lower,hist_upper);

            buffer[1] = hist_med;
            for(int x=2; x<src.width()-1; ++x) {
                for(int i=-1; i<=+1; ++i) {
                    medianNext(src.getPixelQuick(x+1,1+i),hist,hist_temp,hist_med,hist_lower,hist_upper,true);
                    medianNext(src.getPixelQuick(x-2,1+i),hist,hist_temp,hist_med,hist_lower,hist_upper,false);
                }
                buffer[x] = hist_med;
            }

        for(int y=2; y<=src.height()-2; ++y) {
            hist       = 0;
            hist_med   = -1;
            for(int j=-1; j<=1; ++j)
                for(int i=-1; i<=1; ++i,++p)
                    medianNext(src.getPixelQuick(1+i,y+j),hist,hist_temp,hist_med,hist_lower,hist_upper,true);
            temp[0] = hist_med;
            for(int i=-1; i<=1; ++i) {
                medianNext(src.getPixelQuick(3,y+i),hist,hist_temp,hist_med,hist_lower,hist_upper,true);
                medianNext(src.getPixelQuick(0,y+i),hist,hist_temp,hist_med,hist_lower,hist_upper,false);
            }
            temp[1] = hist_med;

            // rest of line
            p = src.getPixelPointerXY(1,y-1);
            for(int x=3; x<=src.width()-2; ++x,++p) {
                for(int i=-1; i<=1; ++i) {
                    medianNext(src.getPixelQuick(x+1,y+i),hist,hist_temp,hist_med,hist_lower,hist_upper);
                    medianNext(src.getPixelQuick(x-2,y+i),hist,hist_temp,hist_med,hist_lower,hist_upper,false);
                }

                *p          = buffer[x-2];
                buffer[x-2] = temp[0];
                temp[0]     = temp[1];
                temp[1]     = hist_med;
            }

        // write buffer
        *p                    = buffer[src.width()-3]; ++p;
        *p                    = buffer[src.width()-2]; ++p;
        buffer[src.width()-3] = temp[0];
        buffer[src.width()-2] = temp[1];
    }

    // copy buffer to last line
    memcpy(src.getPixelPointerXY(1,src.height()-2), &buffer[1], src.width()-2);

        // clean up
        delete[] buffer;
        delete[] temp;
}

void dilateIP(Image& src)
{
    #ifdef NICE_USELIB_IPP
        IppiSize ROIsize = {src.width()-2, src.height()-2};
        IppStatus ret    = ippiDilate3x3_8u_C1IR(src.getPixelPointerXY(1,1), src.getStepsize(), ROIsize);

        if(ret!=ippStsNoErr)
            fthrow(ImageException, ippGetStatusString(ret));

    #else
        Histogram hist(256);
        int hist_max, hist_val;

        Ipp8u* p;
        Ipp8u* buffer     = new Ipp8u[src.width()];
        buffer[0]         = buffer[src.width()-1] = 0;
        Ipp8u* temp       = new Ipp8u[2];

        // init buffer with the first image line (y=1)
            // init hist
            hist     = 0;
            hist_max = std::numeric_limits<int>::min();
            for(int y=0; y<=2; ++y)
                for(int x=0; x<=2; ++x) {
                    hist_val = src(x,y);
                    if(hist_val>hist_max)
                        hist_max = hist_val;
                    ++hist[hist_val];
                }
            buffer[1] = hist_max;
            // init buffer
            for(int x=2; x<src.width()-1; ++x)
                buffer[x] = dilateNext(src,hist,1,hist_val,hist_max,x,1);

        for(int y=2; y<=src.height()-2; ++y) {
            // init hist && fill up temp buffer
            hist     = 0;
            hist_max = std::numeric_limits<int>::min();
            for(int j=-1; j<=1; ++j)
                for(int i=-1; i<=1; ++i) {
                    hist_val = src(1+i,y+j);
                    if(hist_val>hist_max)
                        hist_max = hist_val;
                    ++hist[hist_val];
                }
            temp[0] = hist_max;

            temp[1] = dilateNext(src,hist,1,hist_val,hist_max,2,y);

            // rest of line
            p = src.getPixelPointerXY(1,y-1);
            for(int x=3; x<=src.width()-2; ++x) {
                dilateNext(src,hist,1,hist_val,hist_max,x,y);

                *p          = buffer[x-2]; ++p;
                buffer[x-2] = temp[0];
                temp[0]     = temp[1];
                temp[1]     = hist_max;
            }

        // write buffer
        *p = buffer[src.width()-3]; ++p;
        *p = buffer[src.width()-2]; ++p;
        buffer[src.width()-3] = temp[0];
        buffer[src.width()-2] = temp[1];
    }

    // copy buffer to last line
    memcpy(src.getPixelPointerXY(1,src.height()-2), &buffer[1], src.width()-2);

        // clean up
        delete[] buffer;
        delete[] temp;

    #endif
}

void openingIP(Image& src)
{
    erodeIP(src);
    dilateIP(src);
}

void closingIP(Image& src)
{
    dilateIP(src);
    erodeIP(src);
}





// // // // // Matching Operations // // // // //

Image* hitAndMiss(const Image& src, const CharMatrix& structureElement, Image* dst)
{
    Image* result = createResultBuffer(src, dst);
    Image* temp   = erode(src, structureElement);

        // invert the structure element and source image
        CharMatrix* invStructure = new CharMatrix(structureElement.rows(), structureElement.cols());
        for(size_t j=0; j<structureElement.rows(); ++j)
            for(size_t i=0; i<structureElement.cols(); ++i)
                (*invStructure)(j,i) = (structureElement(j,i)==0)?1:0;

        // invert the source image
        Image* invSrc = new Image(src);
        invSrc->invert();

    result = erode(*invSrc, *invStructure);

        // do an and-combination
        const Image::Pixel *pSrc;
              Image::Pixel *pDst;
        for(int y=0; y<result->height(); ++y) {
            pSrc = temp->getPixelPointerY(y);
            pDst = result->getPixelPointerY(y);
            for(int x=0; x<result->width(); ++x,++pSrc,++pDst)
                *pDst = (*pSrc==*pDst && *pSrc!=0)?255:0;
        }

    // cleanUp
    delete invStructure;
    delete invSrc;
    delete temp;

    return result;
}

} // namespace NICE
