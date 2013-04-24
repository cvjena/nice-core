#include <iostream>
#include <assert.h>
#include <stdio.h>

namespace NICE {
template<class P>
MultiChannelImageT<P>::MultiChannelImageT( int _xsize, int _ysize, uint _numChannels)
{
  data = NULL;
  numChannels = 0;
  xsize = 0;
  ysize = 0;
  reInit( _xsize, _ysize, _numChannels);
}

template<class P>
MultiChannelImageT<P>::MultiChannelImageT()
{
  xsize = 0;
  ysize = 0;
  numChannels = 0;
  data = NULL;
}

template<class P>
P & MultiChannelImageT<P>::operator() (int x, int y, uint channel)
{
  assert( channel < numChannels );
  assert(( x < xsize ) && ( x >= 0 ) );
  assert(( y < ysize ) && ( y >= 0 ) );
  assert( data[channel] != NULL );
  return data[channel][x + y*xsize];
}

template<class P>
ImageT<P> MultiChannelImageT<P>::operator[] (uint c)
{
  // This was our first idea ... but it creates a real copy
  // ImageT<P> tmp ( data[c], xsize, ysize, xsize*sizeof(P), GrayColorImageCommonImplementation::noAlignment );
  // This is the correct version. The funny thing about this is that shallowCopy
  // is not an enum parameter, but an instance of ShallowCopyMode, which is a class.
  // This fancy trick was done in older to prevent automatic conversion between enum types
  // as done implicitly by C++.
  ImageT<P> tmp ( data[c], xsize, ysize, xsize*sizeof(P), GrayColorImageCommonImplementation::shallowCopy );
  return tmp;
}

template<class P>
MultiChannelImageT<P>& MultiChannelImageT<P>::operator=(const MultiChannelImageT<P>& orig) 
{
  if(!(xsize == orig.xsize && ysize == orig.ysize && numChannels == orig.numChannels))
  {
    freeData();
    xsize = orig.xsize;
    ysize = orig.ysize;
    numChannels = orig.numChannels;
    if(orig.data != NULL)
    {
      data = new P *[numChannels];
      for ( int c = 0; c < ( int )numChannels; c++ )
      {
        if ( orig.data[c] == NULL )
        {
          data[c] = NULL;
        }
        else
        {
          data[c] = new P [xsize*ysize];
        }
      }
    }
    else
      data = NULL;
  }

  for ( int c = 0; c < ( int )numChannels; c++ )
  {
    if ( orig.data[c] != NULL )
    {
      for ( int x = 0; x < xsize*ysize; x++ )
      {
        data[c][x] = orig.data[c][x];
      }
    }
  }
  
  return *this;
}

template<class P>
MultiChannelImageT<P>::MultiChannelImageT( const MultiChannelImageT<P>& p )
{
  data = NULL;
  xsize = p.xsize;
  ysize = p.ysize;
  numChannels = p.numChannels;
   
  if(p.data != NULL)
    data = new P *[numChannels];
  else
    data = NULL;

  for ( int c = 0; c < ( int )numChannels; c++ )
  {
    if ( p.data[c] == NULL )
    {
      data[c] = NULL;
    }
    else
    {
      data[c] = new P [xsize*ysize];
      for ( int x = 0; x < xsize*ysize; x++ )
      {
        data[c][x] = p.data[c][x];
      }
    }
  }
}


template<class P>
void MultiChannelImageT<P>::addChannel( int newChans )
{
  P **tmpData = new P *[numChannels+newChans];

  bool allocMem = false;
  int i = 0;

  for ( ; i < (int)numChannels; i++ )
  {
    tmpData[i] = data[i];

    if ( data[i] != NULL )
      allocMem = true;
  }

  if ( allocMem )
  {
    for ( ; i < newChans + (int)numChannels; i++ )
    {
      tmpData[i] = new P [xsize*ysize];
    }
  }

  numChannels += newChans;

  delete [] data;

  data = new P *[numChannels];

  for ( i = 0; i < (int)numChannels; i++ )
  {
    data[i] = tmpData[i];
  }

  delete [] tmpData;
}

template<class P>
template<class SrcP>
void MultiChannelImageT<P>::addChannel(const NICE::ImageT<SrcP> &newImg)
{
  int oldchan = numChannels;
  if(this->xsize > 0)
  {
    assert(newImg.width() == this->width() && newImg.height() == this->height());
    addChannel(1);
  }
  else
  {
      reInit( newImg.width(), newImg.height(), 1 );
  }
  
  for(int y = 0; y < this->ysize; y++)
  {
    for(int x = 0; x < this->xsize; x++)
    {
      data[oldchan][x + y*xsize] = (P)newImg(x,y);
    }
  }
}

template<class P>
template<class SrcP>
void MultiChannelImageT<P>::addChannel(const NICE::MultiChannelImageT<SrcP> &newImg)
{
  int oldchan = numChannels;
  if(numChannels > 0)
  {
    assert(newImg.width() == this->width() && newImg.height() == this->height());
    addChannel(newImg.channels());
  }
  else
  {
      reInit( newImg.width(), newImg.height(), newImg.channels() );
  }
  
  int chanNI = 0;
  
  for(int c = oldchan; c < (int)numChannels; c++, chanNI++)
  {
    int val = 0;
    for(int y = 0; y < this->ysize; y++)
    {
      for(int x = 0; x < this->xsize; x++, val++)
      {
        data[c][val] = newImg.get(x,y,chanNI);
      }
    }
  }
}

template<class P>
MultiChannelImageT<P>::~MultiChannelImageT()
{
  freeData();
}

template<class P>
void MultiChannelImageT<P>::freeData()
{
  if ( data != NULL )
  {
    for ( uint i = 0 ; i < numChannels ; i++ )
      if ( data[i] != NULL )
        delete [] data[i];

    delete [] data;

    data = NULL;
  }
}

template<class P>
void MultiChannelImageT<P>::reInit( int _xsize, int _ysize, int _numChannels )
{
  freeData();
  xsize = _xsize;
  ysize = _ysize;
  numChannels = _numChannels;
  data = new P *[numChannels];

  for ( uint i = 0 ; i < numChannels; i++ )
    data[i] = new P [xsize*ysize];
}

template<class P>
template<class SrcP>
void MultiChannelImageT<P>::reInitFrom( const MultiChannelImageT<SrcP> & src )
{
  freeData();

  xsize = src.width();
  ysize = src.height();
  numChannels = src.channels();

  data = new P *[numChannels];

  for ( uint i = 0 ; i < numChannels; i++ )
    data[i] = new P [xsize*ysize];
}

template<class P>
P MultiChannelImageT<P>::get( int x, int y, uint channel ) const
{
  assert( channel < numChannels );
  assert(( x < xsize ) && ( x >= 0 ) );
  assert(( y < ysize ) && ( y >= 0 ) );
  assert( data[channel] != NULL );

  return data[channel][x + y*xsize];
}

template<class P>
P ** MultiChannelImageT<P>::getDataPointer()
{
  return data;
}

template<class P>
void MultiChannelImageT<P>::set( int x, int y, P val, uint channel )
{
  assert( channel < numChannels );
  assert(( x < xsize ) && ( x >= 0 ) );
  assert(( y < ysize ) && ( y >= 0 ) );
  assert( data[channel] != NULL );

  data[channel][x + y*xsize] = val;
}

template<class P>
void MultiChannelImageT<P>::set( P val, uint channel )
{
  assert( channel < numChannels );
  assert( data[channel] != NULL );

  for ( int k = 0 ; k < xsize*ysize ; k++ )
    data[channel][k] = val;
}

template<class P>
void MultiChannelImageT<P>::setAll( P val )
{
  for ( uint channel = 0 ; channel < numChannels ; channel++ )
    if ( data[channel] != NULL )
      set( val, channel );
}

template<class P>
void MultiChannelImageT<P>::statistics( P & min, P & max, uint channel ) const
{
  assert( channel < numChannels );

  for ( long k = 0 ; k < xsize*ysize ; k++ )
  {
    P val = data [channel][k];
    if (( k == 0 ) || ( val > max ) ) max = val;
    if (( k == 0 ) || ( val < min ) ) min = val;
  }
  
  assert(finite(max));
  assert(finite(min));
}

template<class P>
Image MultiChannelImageT<P>::getChannel( uint channel ) const
{
  assert( channel < numChannels );

  NICE::Image img;
  convertToGrey( img, channel, true );
  /*
      P min, max;
      statistics ( min, max, channel );
      fprintf (stderr, "MultiChannelImageT<>::showChannel: max %f min %f\n", (double)max, (double)min );*/

  return img;
}

/** convert to ice image */
template<class P>
void MultiChannelImageT<P>::convertToGrey( NICE::Image & img, uint channel, bool normalize ) const
{
  assert( channel < numChannels );

  P min, max;

  if ( normalize ) {
    statistics( min, max, channel );
    fprintf( stderr, "MultiChannelImageT<>::showChannel: max %f min %f\n", ( double )max, ( double )min );
  }

  bool skip_assignment = false;

  img.resize( xsize, ysize );

  if ( normalize )
    if ( max - min < std::numeric_limits<double>::min() )
    {
      img.set( max );
      skip_assignment = true;
      fprintf( stderr, "MultiChannelImageT::showChannel: image is uniform! (%f)\n", ( double )max );
    }


  if ( ! skip_assignment )
  {
    long k = 0;

    for ( int y = 0 ; y < ysize; y++ )
      for ( int x = 0 ; x < xsize ; x++, k++ )
        if ( normalize )
          img.setPixel( x, y, ( int )(( data[channel][k] - min ) * 255 / ( max - min ) ) );
        else
          img.setPixel( x, y, ( int )( data[channel][k] ) );
  }
}

template<class P>
void MultiChannelImageT<P>::convertToColor( NICE::ColorImage & img, const int chan1, const int chan2, const int chan3) const
{
  assert( chan1 < numChannels && chan2 < numChannels && chan3 < numChannels);

  img.resize( xsize, ysize );

  long k = 0;

  for ( int y = 0 ; y < ysize; y++ )
    for ( int x = 0 ; x < xsize ; x++, k++ )
    {
      img.setPixel( x, y, 0, ( int )( data[chan1][k] ) );
      img.setPixel( x, y, 1, ( int )( data[chan2][k] ) );
      img.setPixel( x, y, 2, ( int )( data[chan3][k] ) );
    }
}


template<class P>
ColorImage MultiChannelImageT<P>::getColor() const
{
  assert( numChannels == 3 );

  NICE::ColorImage img( xsize, ysize );

  long k = 0;

  for ( int y = 0 ; y < ysize; y++ )
    for ( int x = 0 ; x < xsize ; x++, k++ )
    {
      img.setPixel( x, y, 0, ( int )( data[0][k] ) );
      img.setPixel( x, y, 1, ( int )( data[1][k] ) );
      img.setPixel( x, y, 2, ( int )( data[2][k] ) );
    }

  //showImage(img);
  //getchar();
  return img;
}

template<class P>
void MultiChannelImageT<P>::calcIntegral( uint channel )
{
  assert( channel < numChannels );
  assert( data[channel] != NULL );

  int k;
  P *integralImage = data[channel];

  k = xsize;

  for ( int y = 1 ; y < ysize; y++, k += xsize )
    integralImage[k] += integralImage[k-xsize];

  k = 1;

  for ( int x = 1 ; x < xsize; x++, k++ )
    integralImage[k] += integralImage[k-1];

  k = xsize + 1;

  for ( int y = 1 ; y < ysize ; y++, k++ )
    for ( int x = 1 ; x < xsize ; x++, k++ )
    {
      integralImage[k] += integralImage[k-1];
      integralImage[k] += integralImage[k - xsize];
      integralImage[k] -= integralImage[k - xsize - 1];
    }
}

template<class P>
P MultiChannelImageT<P>::getIntegralValue(int ulx, int uly, int lrx, int lry, int channel) const
{
  ulx = std::max(ulx-1, -1);
  ulx = std::min(ulx, xsize-1);
  uly = std::max(uly-1, -1);
  uly = std::min(uly, ysize-1);
  lrx = std::max(lrx, 0);
  lrx = std::min(lrx, xsize-1);
  lry = std::max(lry, 0);
  lry = std::min(lry, ysize-1);
  
  P val1, val2, val3, val4;
  val1 = get(lrx, lry, channel);
  if(uly > -1)
    val2 = get(lrx, uly, channel);
  else
    val2 = 0;
  if(ulx > -1)
    val3 = get(ulx, lry, channel);
  else
    val3 = 0;
  if(ulx > -1 && uly > -1)
    val4 = get(ulx, uly, channel);
  else
    val4 = 0;
  
  P area = abs((P)(lrx-ulx)*(lry-uly));
  P val = val1 - val2 - val3 + val4;
  return val/area;
}

template<class P>
void MultiChannelImageT<P>::store( std::string filename ) const
{
  // simple raw format
  FILE *f = fopen( filename.c_str(), "w" );

  if ( f == NULL ) {
    fprintf( stderr, "MultiChannelImageT::store: error writing to %s\n", filename.c_str() );
    exit( -1 );
  }

  fwrite( &xsize, sizeof( int ), 1, f );

  fwrite( &ysize, sizeof( int ), 1, f );
  fwrite( &numChannels, sizeof( uint ), 1, f );

  for ( uint channel = 0 ; channel < numChannels ; channel++ )
  {
    assert( data[channel] != NULL );
    fwrite( data[channel], sizeof( P ), xsize*ysize, f );
  }

  fclose( f );
}

template<class P>
void MultiChannelImageT<P>::restore( std::string filename )
{
  // simple raw format
  FILE *f = fopen( filename.c_str(), "r" );

  if ( f == NULL ) {
    fprintf( stderr, "MultiChannelImageT::store: error reading from %s\n", filename.c_str() );
    exit( -1 );
  }

  fread( &xsize, sizeof( int ), 1, f );

  fread( &ysize, sizeof( int ), 1, f );
  fread( &numChannels, sizeof( uint ), 1, f );

  if ( numChannels > 0 ) {
    reInit( xsize, ysize, numChannels );

    for ( uint channel = 0 ; channel < numChannels ; channel++ )
    {
      assert( data[channel] != NULL );
      fread( data[channel], sizeof( P ), xsize*ysize, f );
    }
  } else {
    freeData();
    data = NULL;
  }

  fclose( f );
}

template<class P>
int MultiChannelImageT<P>::width() const
{
  return xsize;
}

template<class P>
int MultiChannelImageT<P>::height() const
{
  return ysize;
}

template<class P>
int MultiChannelImageT<P>::channels() const
{
  return ( int )numChannels;
}

template<class P>
int MultiChannelImageT<P>::getPixelInt( int x, int y, int channel ) const
{
  throw( "this type is not implemented\n" );
  return -1;
}

template<class P>
double MultiChannelImageT<P>::getPixelFloat( int x, int y, int channel ) const
{
  throw( "this type is not implemented\n" );
  return -1.0;
}

template<class P>
void MultiChannelImageT<P>::setPixelInt( int x, int y, int channel, int pixel )
{
  throw( "this type is not implemented\n" );
}

template<class P>
void MultiChannelImageT<P>::setPixelFloat( int x, int y, int channel, double pixel )
{
  throw( "this type is not implemented\n" );
}

#define SET_FUNCS_PROTO_MACRO(MYTYPE) \
template<>\
int MultiChannelImageT<MYTYPE>::getPixelInt(int x, int y, int channel) const;\
template<>\
double MultiChannelImageT<MYTYPE>::getPixelFloat(int x, int y, int channel) const;\
template<>\
void MultiChannelImageT<MYTYPE>::setPixelInt(int x, int y, int channel, int pixel);\
template<>\
void MultiChannelImageT<MYTYPE>::setPixelFloat(int x, int y, int channel, double pixel);

SET_FUNCS_PROTO_MACRO( double )
SET_FUNCS_PROTO_MACRO( int )
SET_FUNCS_PROTO_MACRO( long int )
SET_FUNCS_PROTO_MACRO( float )
SET_FUNCS_PROTO_MACRO( unsigned int )

} // namespace


