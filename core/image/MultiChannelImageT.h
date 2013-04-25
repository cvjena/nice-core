#ifndef _NICE_CORE_MULTICHANNELIMAGET_H
#define _NICE_CORE_MULTICHANNELIMAGET_H

#include <core/image/MultiChannelImageAccess.h>
#include <core/image/ImageT.h>

namespace NICE {

/**
 * @class MultiChannelImageT
 * An image consisting of an arbitrary number of channels.
 *
 * formaly known as Generic Image
 *
 * @author Erik Rodner and Björn Fröhlich
 * @example notyet
 */

template <class P>
class MultiChannelImageT : public MultiChannelImageAccess {
protected:
  typedef P Value;
  typedef unsigned int uint;

  /** image data, use carefully !!! data[channel][pixel_offset] */
  P **data;
  
  /** image width */
  int xsize;
  
  /** image height */
  int ysize;
  
  /** number of image channels */
  uint numChannels;
  
public:

  virtual inline int width() const;
  virtual inline int height() const;

  virtual inline int channels() const;

  virtual int getPixelInt( int x, int y, int channel ) const;

  virtual double getPixelFloat( int x, int y, int channel ) const;

  virtual void setPixelInt( int x, int y, int channel, int pixel );

  virtual void setPixelFloat( int x, int y, int channel, double pixel );

  /** simple constructor */
  MultiChannelImageT( int xsize, int ysize, uint numChannels = 1);

  /** very simple constructor */
  MultiChannelImageT();

  /** copy constructor */
  MultiChannelImageT( const MultiChannelImageT<P>& p );

  /** simple destructor */
  virtual ~MultiChannelImageT();

  /** free all memory */
  void freeData();

  /** reinit */
  void reInit( int xsize, int ysize, int numChannels = 1);

  /** reinit data structure using the same dimensions and
   number of channels as another image */
  template<class SrcP>
  void reInitFrom( const MultiChannelImageT<SrcP> & src);

  void addChannel( int newChans = 1 );

  /** add a channel to Multichannel Image */
  template<class SrcP>
  void addChannel(const NICE::ImageT<SrcP> &newImg);
  
  template<class SrcP>
  void addChannel(const NICE::MultiChannelImageT<SrcP> &newImg);
  
  /** get value */
  P get( int x, int y, uint channel = 0 ) const;
  
  /** get data pointer */
  P** getDataPointer();

  /** set value */
  void set( int x, int y, P val, uint channel = 0 );

  /** set value */
  void set( P val, uint channel);

  /** set value */
  void setAll( P val );

  /** calc integral image */
  void calcIntegral( uint channel = 0 );
  
  /**
   * @brief calculate the integral value in the area given by upper left corner and lower right corner, including out of boundary check
   * @warning make sure that the given channel is an integral image
   * @param ulx upper left x coordinate
   * @param uly upper left y coordinate
   * @param lrx lower right x coordinate
   * @param lry lower right y coordinate
   * @param channel channel
   * @return P mean value of given area
   **/
  P getIntegralValue(int ulx, int uly, int lrx, int lry, int channel);

  /** convert to ice image */
  void convertToGrey( NICE::Image & img, uint channel = 0, bool normalize = true ) const;

  /** convert to ice colorimage */
  void convertToColor( NICE::ColorImage & img, const int chan1 = 0, const int chan2 = 1, const int chan3 = 2 ) const;

  /** return image for visualization */
  Image getChannel( uint channel = 0 ) const;

  /** return rgb image for visualization */
  ColorImage getColor() const;

  /** calculate image statistics */
  void statistics( P & min, P & max, uint channel = 0 ) const;

  /** dump all data to RAW format: xsize, ysize, numChannels, <data> */
  void store( std::string filename ) const;

  /** read all data from RAW format: xsize, ysize, numChannels, <data> */
  void restore( std::string filename );

  /** copy alls data to new object */
  MultiChannelImageT<P>& operator=( const MultiChannelImageT<P>& orig );
  
  /** element operator */
  P & operator() (int x, int y, uint channel = 0);
  
  /** element operator */
  ImageT<P> operator[] (uint c);
};

} // namespace

#include "core/image/MultiChannelImageT.tcc"

#endif
