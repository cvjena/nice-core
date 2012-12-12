
#include <iostream>

namespace NICE {

template<class P>
ImageT<P>* median(const ImageT<P>& src, int anchorx, int anchory, uint maskx, uint masky, ImageT<P>* dst)
{
    if(anchorx==-1)
        anchorx=maskx/2;
    if(anchory==-1)
        anchory=masky/2;

    ImageT<P> *result = createResultBuffer(src, dst);

    if( src.width()!=result->width() || src.height()!=result->height() )
        fthrow(ImageException,"src and dst must have the same size.");

    #ifdef NICE_USELIB_IPP
        IppiPoint anchor={anchorx,anchory};
        IppiSize ippiSize = { src.width()-maskx+1, src.height()-masky+1 };
        IppiSize mask={maskx,masky};

        IppStatus ret = ippiFilterMedian_C1R(
                src.getPixelPointerXY(maskx-1-anchorx,masky-1-anchory),
                src.getStepsize(), 
                result->getPixelPointerXY(anchorx,anchory),
                result->getStepsize(),
                ippiSize,
                mask,
                anchor);

        if(ret!=ippStsNoErr)
            fthrow(ImageException, ippGetStatusString(ret));
    #else // NICE_USELIB_IPP
        fthrow(ImageException,"Not yet supportet without IPP.");
    #endif // NICE_USELIB_IPP

    return result;
}

template<class P>
ColorImageT<P>* median(const ColorImageT<P>& src,bool mask, ColorImageT<P>* dst)
{
    ColorImageT<P> *result = createResultBuffer(src, dst);

    if( src.width()!=result->width() || src.height()!=result->height() )
        fthrow(ImageException,"src and dst must have the same size.");

    #ifdef NICE_USELIB_IPP
            IppiMaskSize masksize;
            if (mask)
            {
                masksize=ippMskSize5x5;
            }
            else
            {
                masksize=ippMskSize3x3;
            }
            IppiSize ippiSize = { src.width()-4, src.height()-4 };
            
            IppStatus ret = ippiFilterMedianColor_C3R(
                    src.getPixelPointerXY(4,4),
            src.getStepsize(), 
            result->getPixelPointerXY(0,0), 
            result->getStepsize(),
            ippiSize,
            masksize);

            if(ret!=ippStsNoErr)
                fthrow(ImageException, ippGetStatusString(ret));
    #else // NICE_USELIB_IPP
        fthrow(ImageException,"Not yet supportet without IPP.");
    #endif // NICE_USELIB_IPP

    return result;
}

}
