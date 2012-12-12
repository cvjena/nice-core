
#include <core/image/ImageTools.h>
#include <core/image/ippwrapper.h>

namespace NICE {

template<class P>
ImageT<P>* addConstBorder(const ImageT<P> &src, uint width, uint height, P value, ImageT<P>* dst)
{
    ImageT<P>* result = createResultBuffer(src.width()+2*width, src.height()+2*height, dst);

    #ifdef NICE_USELIB_IPP
        IppStatus ret = ippiCopyConstBorder_C1R(src.getPixelPointer(), src.getStepsize(),
                                                makeROIFullImage(src),
                                                result->getPixelPointer(), result->getStepsize(),
                                                makeROIFullImage(*result),
                                                height, width, value);

        if(ret!=ippStsNoErr)
            fthrow(ImageException, ippGetStatusString(ret));

    #else // NICE_USELIB_IPP
        fthrow(ImageException,"Not yet supported without IPP.");
    #endif // NICE_USELIB_IPP

    return(result);
}

template<class P>
ImageT<P>* copyBorder(const ImageT<P> &src, uint width, uint height, ImageT<P>* dst)
{
    ImageT<P>* result = createResultBuffer(src.width(), src.height(), dst);
    if ( (2*(int)width > src.width()) || (2*(int)height > src.height()) ) 
	fthrow(ImageException,"Border exceeds image size.");

    // inefficient version
    for ( int y = 0 ; y < (int)height ; y++ ) 
	for ( int x = 0 ; x < src.width() ; x++ )
	    result->setPixel ( x, y, src.getPixel ( x, y ) );

    for ( int y = src.height() - height ; y < src.height() ; y++ ) 
	for ( int x = 0 ; x < src.width() ; x++ )
	    result->setPixel ( x, y, src.getPixel ( x, y ) );

    for ( int x = 0 ; x < (int)width ; x++ ) 
	for ( int y = (int)height ; y < src.height() - (int)height ; y++ )
	    result->setPixel ( x, y, src.getPixel ( x, y ) );

    for ( int x = src.width()-width ; x < src.width() ; x++ ) 
	for ( int y = (int)height ; y < src.height() - (int)height ; y++ )
	    result->setPixel ( x, y, src.getPixel ( x, y ) );

    return result;

}

template<class P>
void autoCropRect(const ImageT<P> &src, P color, Rect &rect)
{
    bool quit=false;
    for(int y=0;y<src.height();y++) {
        for(int x=0;x<src.width();x++) {
            if(src(x,y)>color) {
                rect.top=y;
                quit=true;
                break;
            }
        }
        if(quit)
            break;
    }
    quit=false;
    for(int y=src.height()-1;y>=0;y--) {
        for(int x=0;x<src.width();x++) {
            if(src(x,y)>color) {
                rect.height=y-rect.top+1;
                quit=true;
                break;
            }
        }
        if(quit)
            break;
    }
    quit=false;
    for(int x=0;x<src.width();x++) {
        for(int y=0;y<src.height();y++) {
            if(src(x,y)>color) {
                rect.left=x;
                quit=true;
                break;
            }
        }
        if(quit)
            break;
    }
    quit=false;
    for(int x=src.width()-1;x>=0;x--) {
        for(int y=0;y<src.height();y++) {
            if(src(x,y)>color) {
                rect.width=x-rect.left+1;
                quit=true;
                break;
            }
        }
        if(quit)
            break;
    }
}

template<class P>
void normalizeToRange(const ImageT<P> &src, ImageT<P> &dst , P min, P max)
{
     ImageT<P> cpy=src;
     normalizeToRange(cpy,min,max);
     dst=cpy;
}
    
template<class P>
void normalizeToRange(ImageT<P> &src, P min, P max)
{
     //compute scale
	 P src_max,src_min;
	 src.minmax(src_min,src_max);
	 
     if(src_max-src_min > static_cast<P>(1e-8))
     {
          P scale=(max-min)/(src_max-src_min);
          for (int y=0;y<src.height();y++)
          {
               for (int x=0;x<src.width();x++)
               {
                    P value=src.getPixelQuick(x,y);
               //shift to zero
                    value-=src_min;
               //scale to destined range
                    value*=scale;
                    //shift to new minimum;
                    value+=min;
                    src.setPixelQuick(x,y,value);
               }
          }
     }
     else
     {//maybe exception, but clever handling seems the better choice
          for (int y=0;y<src.height();y++)
          {
               for (int x=0;x<src.width();x++)
               {
				   P value=src.getPixelQuick(x,y);
               //shift to zero
                    value-=src_min;
                    //shift to new minimum;
                    value+=min;
					src.setPixelQuick(x,y,value);
               }
          }
          
          fprintf(stderr,"normalizeToRange: Input-Image max value = min value");
     }
     
}

template<class P>
void findLocalMinima(const ImageT<P> &src, P thresh, int dist, std::vector<Coord> &minima)
{
    ImageT<P> cpy=src;
    Coord minidx = cpy.minIndex();
    P min = cpy(minidx);
    while(min<thresh) {
        minima.push_back(minidx);
        int top  = (minidx.y>dist)? minidx.y-dist : 0;
        int left = (minidx.x>dist)? minidx.x-dist : 0;
        int height = (minidx.y+dist<src.height())? minidx.y-top+dist : src.height()-top;
        int width = (minidx.x+dist<src.width())? minidx.x-left+dist : src.width()-left;
        Rect area(left, top, width, height);
        ImageT<P> simage = cpy.subImage(area);
        simage=std::numeric_limits<P>::max();
        minidx = cpy.minIndex();
        min = cpy(minidx);
    }
}

template<class P>
void findLocalMaxima(const ImageT<P> &src, P thresh, int dist, std::vector<Coord> &maxima)
{
    ImageT<P> cpy=src;
    Coord maxidx = cpy.maxIndex();
    P max = cpy(maxidx);
    while(max>thresh) {
        maxima.push_back(maxidx);
        int top  = (maxidx.y>dist)? maxidx.y-dist : 0;
        int left = (maxidx.x>dist)? maxidx.x-dist : 0;
        int height = (maxidx.y+dist<src.height())? maxidx.y-top+dist : src.height()-top;
        int width = (maxidx.x+dist<src.width())? maxidx.x-left+dist : src.width()-left;
        Rect area(left, top, width, height);
        ImageT<P> simage = cpy.subImage(area);
        simage=std::numeric_limits<P>::min();
        maxidx = cpy.maxIndex();
        max = cpy(maxidx);
    }
}

template<class P>
IppiConnectedComp* floodFill4Connected(ImageT<P>&  src,
                                       const IppiPoint&      seed,
                                       const P&              newVal,
                                       IppiConnectedComp*    compBuffer) {

    if(compBuffer==NULL)
        compBuffer = new IppiConnectedComp;
    
    #ifdef NICE_USELIB_IPP
        IppiSize roiSize = {src.width(), src.height()};
        
        Ipp32s buffSize; 
        ippiFloodFillGetSize(roiSize, &buffSize);
        Ipp8u* floodBuffer = new Ipp8u[buffSize];

        IppStatus ret = ippiFloodFill_4Con_C1IR(src.getPixelPointer(),
                                                src.getStepsize(), 
                                                roiSize, seed, newVal, 
                                                compBuffer, floodBuffer);

        if(ret!=ippStsNoErr)
            fthrow(ImageException, ippGetStatusString(ret));

        // clean up
        delete floodBuffer;

        return compBuffer;

    #else
        fthrow(ImageException,"Not yet supportet without IPP.");
    #endif // NICE_USELIB_IPP

    return NULL;
}

template<class P>
IppiConnectedComp* floodFill8Connected(ImageT<P>&  src,
                                       const IppiPoint&      seed,
                                       const P&              newVal,
                                       IppiConnectedComp*    compBuffer) {

    if(compBuffer==NULL)
        compBuffer = new IppiConnectedComp;
    
    #ifdef NICE_USELIB_IPP
        IppiSize roiSize = {src.width(), src.height()};
        
        Ipp32s buffSize; 
        ippiFloodFillGetSize(roiSize, &buffSize);
        Ipp8u* floodBuffer = new Ipp8u[buffSize];

        IppStatus ret = ippiFloodFill_8Con_C1IR(src.getPixelPointer(),
                                                src.getStepsize(), 
                                                roiSize, seed, newVal, 
                                                compBuffer, floodBuffer);

        if(ret!=ippStsNoErr)
            fthrow(ImageException, ippGetStatusString(ret));

        // clean up
        delete floodBuffer;

        return compBuffer;

    #else
        fthrow(ImageException,"Not yet supportet without IPP.");
    #endif // NICE_USELIB_IPP

    return NULL;
}

template<class P>
void Floodfill(ImageT<P>& src, int startx, int starty, uint _newVal, uint _minDelta, uint _maxDelta)
{
    #ifdef NICE_USELIB_IPP
        int pBufferSize;
        IppStatus ret = ippiFloodFillGetSize_Grad(makeROIFullImage(src), &pBufferSize);

        if(ret!=ippStsNoErr)
            fthrow(ImageException, ippGetStatusString(ret));

        Ipp8u pBuffer[pBufferSize];
        IppiPoint seed = {startx, starty};

        IppiConnectedComp pRegion;

        ret = ippiFloodFill_Grad8Con_C1IR(src.getPixelPointer(), src.getStepsize(),
                                          makeROIFullImage(src), seed,
                                          static_cast<Ipp8u>(_newVal),
                                          static_cast<Ipp8u>(_minDelta),
                                          static_cast<Ipp8u>(_maxDelta),
                                          &pRegion,  pBuffer);

        if(ret!=ippStsNoErr)
            fthrow(ImageException, ippGetStatusString(ret));

    #else // NICE_USELIB_IPP
        fthrow(ImageException,"Not yet supportet without IPP.");
    #endif // NICE_USELIB_IPP
}

template<class P>
void Floodfill(ColorImageT<P>& src, int startx, int starty, uint _newVal, uint _minDelta, uint _maxDelta)
{
    FloodfillRGB(src,startx,starty,_newVal,_newVal,_newVal,
                 _minDelta,_minDelta,_minDelta,_maxDelta,_maxDelta,_maxDelta);
}

template<class P>
void FloodfillRGB(ColorImageT<P>& src, int startx, int starty,
                  uint _newValR,   uint _newValG,   uint _newValB,
                  uint _minDeltaR, uint _minDeltaG, uint _minDeltaB,
                  uint _maxDeltaR, uint _maxDeltaG, uint _maxDeltaB)
{
    #ifdef NICE_USELIB_IPP
        int pBufferSize;
        IppStatus ret = ippiFloodFillGetSize_Grad(makeROIFullImage(src), &pBufferSize);

        if(ret!=ippStsNoErr)
            fthrow(ImageException, ippGetStatusString(ret));

        Ipp8u pBuffer[pBufferSize];
        IppiPoint seed = {startx, starty};
        IppiConnectedComp pRegion;
        Ipp8u newVal[3]   = {_newValR,_newValG,_newValB};
        Ipp8u minDelta[3] = {_minDeltaR,_minDeltaG,_minDeltaB};
        Ipp8u maxDelta[3] = {_maxDeltaR,_maxDeltaG,_maxDeltaB};

        ret = ippiFloodFill_Grad8Con_C3IR(src.getPixelPointer(), src.getStepsize(),
                                          makeROIFullImage(src),
                                          seed, newVal, minDelta, maxDelta,
                                          &pRegion, pBuffer);

        if(ret!=ippStsNoErr)
            fthrow(ImageException, ippGetStatusString(ret));

    #else // NICE_USELIB_IPP
        fthrow(ImageException,"Not yet supportet without IPP.");
    #endif // NICE_USELIB_IPP
}

}
