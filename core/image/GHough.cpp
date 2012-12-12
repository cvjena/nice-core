/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libimage - An image/template for new NICE libraries
 * See file License for license information.
 */
/*****************************************************************************/
/*! \file GHough.cpp
    \brief GHough class definitions
 */
/*****************************************************************************/
/*
 *  $Author: bajramov $
 *  $Date: 2009/05/28 11:36:30 $
 *  $Revision: 1.2 $
 */
/*****************************************************************************/

#include "core/image/GHough.h"

namespace NICE {

// Constructors:
// -------------
GHough::GHough() 
{
    isInitialized = false;
}

GHough::GHough(IppiSize imageSize,IppiSize transformSize, NeighborType addMode)
{                    
    isInitialized = false;
    initialize(imageSize, transformSize, addMode);
}

GHough::GHough(const GHough& ex)
{
	*this=ex;
}

// Operators:
// ----------
GHough& GHough::operator=(const GHough& ex)
{
  houghmap=ex.houghmap;  
  imageSize=ex.imageSize; 
  transformSize=ex.transformSize;  
  isInitialized=ex.isInitialized;  
  addMode=ex.addMode;  
  return *this;
}

void GHough::initialize(IppiSize imageSize,IppiSize transformSize, NeighborType addMode)
{
    this->imageSize = imageSize;
    transformSize = transformSize;
    this->addMode = addMode;
    
    //! Allocates memory for data
    houghmap.resize(transformSize.width,transformSize.height);
    clear();

    //! Indicates that initialization has been performed
    isInitialized = true;
}

void GHough::initialize(int width, int height, float scalefactor, NeighborType addMode)
{
    imageSize.width=width; 
    imageSize.height=height; 
    transformSize.width = int(width*scalefactor); 
    transformSize.height = int(height*scalefactor);
    this->addMode = addMode;
    
    //! Allocates memory for data
    houghmap.resize(transformSize.width,transformSize.height);
    clear();

    //! Indicates that initialization has been performed
    isInitialized = true;

}

template<class IMAGE>
void GHough::initialize(const IMAGE &image, float scalefactor, NeighborType addMode)
{
    imageSize.width=image.width(); 
    imageSize.height=image.height(); 
    transformSize.width = image.width()*scalefactor; 
    transformSize.height = image.height()*scalefactor;
    this->addMode = addMode;
    
    //! Allocates memory for data
    houghmap.resize(transformSize.width,transformSize.height);
    clear();

    //! Indicates that initialization has been performed
    isInitialized = true;
}

void GHough::addPoint(float x, float y, float activation)
{
    Coord c;
    c.x=(int)(x+0.5);
    c.y=(int)(y+0.5);
    addPoint(c,activation);
}

void GHough::addPoint(const Coord &pt, float activation)
{
    if(!isInitialized) {
        fthrow(ImageException,"Hough map must be initialized first!");
    }
	
    int h,v;
    Coord transformLoc = transformPoint(pt);
    Coord loc;
    
    switch(addMode) {
    	case EIGHT_NEIGHBORS:
            loc = Coord(transformLoc.x-1,transformLoc.y-1);
	        for(h = -1; h < 2; h++, loc.y++) {
             loc.x=transformLoc.x-1;   
	    	 for(v = -1; v < 2; v++, loc.x++) {
		        if(boundsOkay(loc,transformSize))
                    houghmap(loc)+=activation;
             }
            }
	    break;
	    case FOUR_NEIGHBORS:
            loc = Coord(transformLoc.x-1,transformLoc.y);
	    	for(v = -1; v < 2; v++, loc.x++) {
		        if(boundsOkay(loc,transformSize)) 
                    houghmap(loc)+=activation;
            }
            loc = Coord(transformLoc.x,transformLoc.y-1);
		    if(boundsOkay(loc,transformSize)) 
                    houghmap(loc)+=activation;
            loc.y+=2;
		    if(boundsOkay(loc,transformSize)) 
                    houghmap(loc)+=activation;
	    break;
	    case SINGLE_BIN:
    	    if(boundsOkay(transformLoc,transformSize)) 
                houghmap(loc)+=activation;
	    break;
	    case HALF_OVERLAP:
            loc = transformLoc;
	        for(h = 0; h < 2; h++, loc.y++) {
             loc.x=transformLoc.x;   
	    	 for(v = 0; v < 2; v++, loc.x++) {
		        if(boundsOkay(loc,transformSize)) {
                    houghmap(loc)+=activation;
                }
             }
            }
    }
}

//! Returns true if the point pt is within zero and the bounds
bool GHough::boundsOkay(const Coord &pt,const IppiSize &bounds) const
{
    if( pt.y >= 0 && pt.x >= 0 && pt.y < bounds.height && pt.x < bounds.width)
    	return true;
    else {
    	return false;
    }
}

Coord GHough::transformPoint(const Coord &pt) const
{
    double xBinPerPix;
    double yBinPerPix;

    if(addMode == HALF_OVERLAP)  {
    	//gets top-left bin of 4 overlapping at transform pt if HALF_OVERLAP
    	xBinPerPix = (transformSize.width + 1) / static_cast<double>(imageSize.width);  
    	yBinPerPix = (transformSize.height + 1) / static_cast<double>(imageSize.height);
    } else {
    	xBinPerPix = transformSize.width / static_cast<double>(imageSize.width);
    	yBinPerPix = transformSize.height / static_cast<double>(imageSize.height);
    }
    return Coord(static_cast<int>(round(pt.x * xBinPerPix - .5)), static_cast<int>(round(pt.y * yBinPerPix - .5)));
}

Coord GHough::nearestTransformPoint(const Coord &pt) const
{
    if(addMode == HALF_OVERLAP)  {
    	//gets closest bin of 4 overlapping at transform pt if HALF_OVERLAP
    	double xBinPerPix = (transformSize.width + 1) / static_cast<double>(imageSize.width);  
    	double yBinPerPix = (transformSize.height + 1) / static_cast<double>(imageSize.height);
    	return Coord(static_cast<int>(round(pt.x * xBinPerPix)), static_cast<int>(round(pt.y * yBinPerPix)));
    } else {
    	return transformPoint(pt);
    }
}

Coord GHough::invTransformPoint(const Coord &pt) const
{
    double xPixPerBin; 
    double yPixPerBin;
    
    if(addMode == HALF_OVERLAP)  {
    	xPixPerBin = static_cast<double>(imageSize.width) / (transformSize.width + 1);   
    	yPixPerBin = static_cast<double>(imageSize.height) / (transformSize.height + 1);
    	return Coord(static_cast<int>(round(xPixPerBin * (pt.x + 1))), static_cast<int>(round(yPixPerBin * (pt.y + 1))));
    } else {
    	xPixPerBin = static_cast<double>(imageSize.width) / transformSize.width;   
    	yPixPerBin = static_cast<double>(imageSize.height) / transformSize.height;
	    return Coord(static_cast<int>(round(xPixPerBin * (pt.x + 0.5))), static_cast<int>(round(yPixPerBin * (pt.y + 0.5))));
    }
}

//! Finds the location with the maximum activation
Coord GHough::getMaxLoc() const
{
    if(!isInitialized) 
        fthrow(ImageException,"Hough map must be initialized first!");
    return houghmap.maxIndex(); 
}

float GHough::getMax() const
{
    if(!isInitialized) 
        fthrow(ImageException,"Hough map must be initialized first!");
    return houghmap.max();
}

float GHough::getVal(int x, int y) const
{
    if(!isInitialized) {
        fthrow(ImageException,"Hough map must be initialized first!");
    }
    return houghmap.getPixel(transformPoint(Coord(x,y)));
}

float GHough::getVal(const Coord &pt) const
{
    if(!isInitialized) {
        fthrow(ImageException,"Hough map must be initialized first!");
    }
    return houghmap.getPixel(transformPoint(pt));
}

const FloatImage &GHough::getMap() const
{
    if(!isInitialized) {
        fthrow(ImageException,"Hough map must be initialized first!");
    }
    return houghmap;
}

void GHough::clear()
{
    houghmap=0; 
}


} // namespace NICE 

/*****************************************************************************/
/*
 *  $Log: GHough.cpp,v $
 *  Revision 1.2  2009/05/28 11:36:30  bajramov
 *  renamed a few things for consistency
 *
 *  Revision 1.1.1.1  2007/05/22 19:26:35  bajramov
 *  limun2
 *
 *  Revision 1.3  2007/02/07 19:09:42  zimmermann
 *  * fixed documentation warnings
 *
 *  Revision 1.2  2006/09/21 14:03:54  mattern
 *  .
 *
 *  Revision 1.1  2006/09/15 15:23:58  mattern
 *  general hough transformation
 *
 */
