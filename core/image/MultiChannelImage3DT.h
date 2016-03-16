#ifndef _NICE_CORE_MULTICHANNELIMAGE3DT_H
#define _NICE_CORE_MULTICHANNELIMAGE3DT_H

#include "MultiChannelImageAccess3D.h"
#include "ImageT.h"
#include "MultiChannelImageT.h"
#include "Histogram.h"

#include <vector>
#include <fstream>

namespace NICE {

/**
 * @class MultiChannelImage3DT
 * A 3d image (arbitrary number of cross section images) consisting of an arbitrary number of channels.
 *
 * formaly known as Generic Image
 *
 * @author Björn Fröhlich and Sven Sickert
 * @example notyet
 */

template <class P>
class MultiChannelImage3DT : public MultiChannelImageAccess3D {
protected:
  typedef P Value;
  typedef unsigned int uint;

  /** image data, use carefully !!! data[channel][pixel_offset] */
  std::vector<P*> data;
//    P **data;
  
  /** image width */
  int xsize;
  
  /** image height */
  int ysize;

  /** image depth */
  int zsize;
  
  /** number of image channels */
  uint numChannels;
  
public:

  virtual inline int width() const;
  virtual inline int height() const;
  virtual inline int depth() const;

  virtual inline int channels() const;

  virtual int getPixelInt( int x, int y, int z, int channel ) const;

  virtual double getPixelFloat( int x, int y, int z, int channel ) const;

  virtual void setPixelInt( int x, int y, int z, int channel, int pixel );

  virtual void setPixelFloat( int x, int y, int z, int channel, double pixel );

  /** simple constructor */
  MultiChannelImage3DT( int xsize, int ysize, int zsize, uint numChannels = 1);

  /** very simple constructor */
  MultiChannelImage3DT();

  /** copy constructor */
  MultiChannelImage3DT( const MultiChannelImage3DT<P>& p );

  /** simple destructor */
  virtual ~MultiChannelImage3DT();

  /** free all memory */
  void freeData();

  /**
   * @brief free only the pointer to the actual data, but leaves the actual data in the memory.
   *
   * Usefull for when the underlying data (e.g data[0] ptrs are passed to an other multi channel
   * image for further use and memcopy should be avoided.
   * Detail: Only frees variable 'data', not the memory data[0:numChannels] is pointing to
   * @author Johannes Ruehle
   * @date 2014-07-18
   */
  void freeShallowData();

  /** reinit */
  void reInit( int xsize, int ysize, int zsize, int numChannels = 1);

  /** reinit data structure using the same dimensions and
   number of channels as another image */
  template<class SrcP>
  void reInitFrom( const MultiChannelImage3DT<SrcP> & src);

  void addChannel( int newChans = 1 );

  /** add a channel to Multichannel Image */
  template<class SrcP>
  void addChannel(const NICE::MultiChannelImageT<SrcP> &newImg );
  
  template<class SrcP>
  void addChannel(const NICE::MultiChannelImage3DT<SrcP> &newImg);

  /** add channels only as references (no deep memory copy) */
  template<class SrcP>
  void addChannelReferences(const NICE::MultiChannelImage3DT<SrcP> &newImg);
  
  /** get value */
  P get( int x, int y, int z, uint channel = 0 ) const;
  
  /** get data pointer */
  std::vector<P*> getDataPointer() const;
  //P** getDataPointer();

  /** set value */
  void set( int x, int y, int z, P val, uint channel = 0 );

  /** set value */
  void set( P val, uint channel = 0 );

  /** set value */
  void setAll( P val );

  /** calc integral image */
  void calcIntegral( uint channel = 0 );
  
  /** 
   * @brief calculate the variance image map of a channel
   * @param srcchan source channel with raw data
   * @param tarchan target channel for the variance map
   */
  void calcVariance( uint srcchan = 0, uint tarchan = 1 );
  
  /**
   * @brief calculate the integral value in the volume given by upper left front corner and lower right back corner, including out of boundary check
   * @warning make sure that the given channel is an integral 3d image
   * @param ulfx upper left front x coordinate
   * @param ulfy upper left front y coordinate
   * @param ulfz upper left front z coordinate
   * @param lrbx lower right back x coordinate
   * @param lrby lower right back y coordinate
   * @param lrbz lower right back z coordinate
   * @param channel channel
   * @return P mean value of given volume
   **/
  P getIntegralValue(int ulfx, int ulfy, int ulfz, int lrbx, int lrby, int lrbz, int channel) const;

  /** convert to ice image */
  void convertToGrey( NICE::Image & img, int z, uint channel = 0, bool normalize = true ) const;

  /** convert to ice colorimage */
  void convertToColor( NICE::ColorImage & img, int z, const int chan1 = 0, const int chan2 = 1, const int chan3 = 2 ) const;

  /** return image for visualization */
  Image getChannel( int z, uint channel = 0 ) const;

	/** return image for visualization */
  ImageT<P> getChannelT( int z, uint channel = 0 ) const;

  /** return x-slice as image */
  ImageT<P> getXSlice ( int x, uint channel = 0 ) const;

  /** return rgb image (reading channels 0, 1, 2) for visualization */
  ColorImage getColor(int z) const;

  /** return rgb image (reading arbitrary three channels) for visualization */
  ColorImage getColorImageFromChannels(int z, int channel0, int channel1, int channel2) const;

  /** calculate image statistics */
  void statistics( P & min, P & max, uint channel = 0 ) const;

  /** correct inhomogeneous illuminations between the image slices
   *  ! Deprecated, use 'equalizeHistogram' instead !
   */
  void correctShading( uint channel = 0 ) const;

  /** do a histogram equalization */
  void equalizeHistogram( uint channel = 0 ) const;
  
  /** dump all data to RAW format: xsize, ysize, numChannels, <data> */
  void store( std::string filename ) const;

  /** read all data from RAW format: xsize, ysize, numChannels, <data> */
  void restore( std::string filename );
  
  /** copy alls data to new object */
  MultiChannelImage3DT<P>& operator=( const MultiChannelImage3DT<P>& orig );
  
  /** element operator */
  P & operator() (int x, int y, int z, uint channel = 0);
  
  /** element operator */
  MultiChannelImageT<P> operator[] (uint c);
};

} // namespace

#include "MultiChannelImage3DT.tcc"

#endif
