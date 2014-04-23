#include <iostream>
#include <assert.h>
#include <stdio.h>
#include <vector>

namespace NICE {
template<class P>
MultiChannelImage3DT<P>::MultiChannelImage3DT( int _xsize, int _ysize, int _zsize, uint _numChannels)
{
  data = NULL;
  numChannels = 0;
  xsize = 0;
  ysize = 0;
  zsize = 0;
  reInit( _xsize, _ysize, _zsize, _numChannels);
}

template<class P>
MultiChannelImage3DT<P>::MultiChannelImage3DT()
{
  xsize = 0;
  ysize = 0;
  zsize = 0;
  numChannels = 0;
  data = NULL;
}

template<class P>
P & MultiChannelImage3DT<P>::operator() (int x, int y, int z, uint channel)
{
  assert( channel < numChannels );
  assert(( x < xsize ) && ( x >= 0 ) );
  assert(( y < ysize ) && ( y >= 0 ) );
  assert(( z < zsize ) && ( z >= 0 ) );
  assert( data[channel] != NULL );
  return data[channel][x + y*xsize + z*xsize*ysize];
}

template<class P>
MultiChannelImageT<P> MultiChannelImage3DT<P>::operator[] (uint z)
{
  MultiChannelImageT<P> img;
  for( int c = 0; c < numChannels; c++ )
  {
    P * datatmp = data[c];
    ImageT<P> tmp ( &datatmp[z*(xsize*ysize)], xsize, ysize, xsize*sizeof(P), GrayColorImageCommonImplementation::shallowCopy );
    img.addChannel(tmp);
  }
  return img;
}

template<class P>
MultiChannelImage3DT<P>& MultiChannelImage3DT<P>::operator=(const MultiChannelImage3DT<P>& orig) 
{
  if(!(xsize == orig.xsize && ysize == orig.ysize && zsize == orig.zsize && numChannels == orig.numChannels))
  {
    freeData();
    xsize = orig.xsize;
    ysize = orig.ysize;
    zsize = orig.zsize;
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
          data[c] = new P [xsize*ysize*zsize];
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
      for ( int x = 0; x < xsize*ysize*zsize; x++ )
      {
        data[c][x] = orig.data[c][x];
      }
    }
  }
  
  return *this;
}

template<class P>
MultiChannelImage3DT<P>::MultiChannelImage3DT( const MultiChannelImage3DT<P>& p )
{
  data = NULL;
  xsize = p.xsize;
  ysize = p.ysize;
  zsize = p.zsize;
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
      data[c] = new P [xsize*ysize*zsize];
      for ( int x = 0; x < xsize*ysize*zsize; x++ )
      {
        data[c][x] = p.data[c][x];
      }
    }
  }
}


template<class P>
void MultiChannelImage3DT<P>::addChannel( int newChans )
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
      tmpData[i] = new P [xsize*ysize*zsize];
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
void MultiChannelImage3DT<P>::addChannel(NICE::MultiChannelImageT<SrcP> &newMCImg)
{
  int oldchan = numChannels;
  if(this->xsize > 0)
  {
    assert(newMCImg.width() == this->width() && newMCImg.height() == this->height());
    assert(newMCImg.channels() == this->zsize);
    addChannel(1);
  }
  else
  {
    reInit( newMCImg.width(), newMCImg.height(), newMCImg.channels(), 1 );
  }
  
  for(int z = 0; z < this->zsize; z++)
  {
    NICE::ImageT<SrcP> newImg = newMCImg[z];
    for(int y = 0; y < this->ysize; y++)
    {
      for(int x = 0; x < this->xsize; x++)
      {
        data[oldchan][x + y*xsize + z*xsize*ysize] = (P)newImg(x,y);
      }
    }
  }
}

template<class P>
template<class SrcP>
void MultiChannelImage3DT<P>::addChannel(const NICE::MultiChannelImage3DT<SrcP> &newImg)
{
  int oldchan = numChannels;
  if(numChannels > 0)
  {
    assert(newImg.width() == this->width() && newImg.height() == this->height() && newImg.depth() == this->depth());
    addChannel(newImg.channels());
  }
  else
  {
      reInit( newImg.width(), newImg.height(), newImg.depth(), newImg.channels() );
  }
  
  int chanNI = 0;
  
  for(int c = oldchan; c < (int)numChannels; c++, chanNI++)
  {
    int val = 0;
    for(int z = 0; z < this->zsize; z++)
    {
      for(int y = 0; y < this->ysize; y++)
      {
        for(int x = 0; x < this->xsize; x++, val++)
        {
          data[c][val] = newImg.get(x,y,z,chanNI);
        }
      }
    }
  }
}

template<class P>
MultiChannelImage3DT<P>::~MultiChannelImage3DT()
{
  freeData();
}

template<class P>
void MultiChannelImage3DT<P>::freeData()
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
void MultiChannelImage3DT<P>::reInit( int _xsize, int _ysize, int _zsize, int _numChannels )
{
  freeData();
  xsize = _xsize;
  ysize = _ysize;
  zsize = _zsize;
  numChannels = _numChannels;
  data = new P *[numChannels];

  for ( uint i = 0 ; i < numChannels; i++ )
    data[i] = new P [xsize*ysize*zsize];
}

template<class P>
template<class SrcP>
void MultiChannelImage3DT<P>::reInitFrom( const MultiChannelImage3DT<SrcP> & src )
{
  freeData();

  xsize = src.width();
  ysize = src.height();
  zsize = src.depth();
  numChannels = src.channels();

  data = new P *[numChannels];

  for ( uint i = 0 ; i < numChannels; i++ )
    data[i] = new P [xsize*ysize*zsize];
}

template<class P>
P MultiChannelImage3DT<P>::get( int x, int y, int z, uint channel ) const
{
  assert( channel < numChannels );
  assert(( x < xsize ) && ( x >= 0 ) );
  assert(( y < ysize ) && ( y >= 0 ) );
  assert(( z < zsize ) && ( z >= 0 ) );
  assert( data[channel] != NULL );

  return data[channel][x + y*xsize + z*xsize*ysize];
}

template<class P>
P ** MultiChannelImage3DT<P>::getDataPointer()
{
  return data;
}

template<class P>
void MultiChannelImage3DT<P>::set( int x, int y, int z, P val, uint channel )
{
  assert( channel < numChannels );
  assert(( x < xsize ) && ( x >= 0 ) );
  assert(( y < ysize ) && ( y >= 0 ) );
  assert(( z < zsize ) && ( z >= 0 ) );
  assert( data[channel] != NULL );

  data[channel][x + y*xsize + z*xsize*ysize] = val;
}

template<class P>
void MultiChannelImage3DT<P>::set( P val, uint channel )
{
  assert( channel < numChannels );
  assert( data[channel] != NULL );

  for ( int k = 0 ; k < xsize*ysize*zsize ; k++ )
    data[channel][k] = val;
}

template<class P>
void MultiChannelImage3DT<P>::setAll( P val )
{
  for ( uint channel = 0 ; channel < numChannels ; channel++ )
    if ( data[channel] != NULL )
      set( val, channel );
}

template<class P>
void MultiChannelImage3DT<P>::statistics( P & min, P & max, uint channel ) const
{
  assert( channel < numChannels );
  P val = 0;

  for ( long k = 0 ; k < xsize*ysize*zsize ; k++ )
  {
    val = data [channel][k];
    if (( k == 0 ) || ( val > max ) ) max = val;
    if (( k == 0 ) || ( val < min ) ) min = val;
  }
  
  assert(finite(max));
  assert(finite(min));
}

template<class P>
void MultiChannelImage3DT<P>::correctShading( uint channel ) const
{
  assert( channel < numChannels );
  
  // some sort of correction trick hardly understandable :-)
  std::vector<double> meanVals;
  for( int z = 0; z < zsize; z++ )
  {
    double sumVal = 0;
    for( int y = 0; y < ysize; y++ )
    {
      for( int x = 0; x < xsize; x++ )
      {
        sumVal += data [channel][x + y*xsize + z*xsize*ysize];
      }
    }
    sumVal /= (xsize*ysize);
    meanVals.push_back( sumVal );

  }

  P newMax = std::numeric_limits<P>::min();

  const short int maxVal = 255;
  for ( int z = 0; z < zsize; z++ )
  {
    for ( int y = 0; y < ysize; y++ )
    {
      for ( int x = 0; x < xsize; x++ )
      {
        P tmp = data [channel][x + y*xsize + z*xsize*ysize];
        double newVal = maxVal * ( (double) tmp / meanVals[z] );
        if ( ( P ) newVal > newMax )
          newMax = ( P ) newVal;
        data [channel][x + y*xsize + z*xsize*ysize] = newVal;
      }
    }
  }
  
  for ( long k = 0 ; k < xsize*ysize*zsize ; k++ )
  {
    data [channel][k] = data [channel][k] / newMax * maxVal;
  }
}

template<class P>
void MultiChannelImage3DT<P>::equalizeHistogram( uint channel ) const
{
  assert(channel < numChannels );

  for( int z = 0; z < zsize; z++ )
  {
    NICE::Image img = getChannel(z, channel );
    NICE::Histogram hist(img,0,255,256);

    NICE::IntVector *histVec = NULL;
    histVec = hist.cumulative();
    for ( int i = 0; i < (int)histVec->size(); i++)
    {
      histVec->set(i, histVec->get(i) * 255 / (double)histVec->get(histVec->size()-1));
    }

    for ( int y = 0; y < ysize; y++ )
    {
      for ( int x = 0; x < xsize; x++ )
      {
        data [channel][x + y*xsize + z*xsize*ysize] = histVec->get( img.getPixel(x,y) );
      }
    }

    delete histVec;
  }
}

template<class P>
Image MultiChannelImage3DT<P>::getChannel( int z, uint channel ) const
{
  assert( channel < numChannels );

  NICE::Image img(xsize, ysize);
  convertToGrey( img, z, channel, true );

  return img;
}

template<class P>
ImageT<P> MultiChannelImage3DT<P>::getChannelT( int z, uint channel ) const
{
  assert( channel < numChannels );

  //  P min, max;
  //  statistics ( min, max, channel );
  //  fprintf (stderr, "MultiChannelImage3DT<>::showChannel: max %f min %f\n", (double)max, (double)min );

  NICE::ImageT<P> img(xsize,ysize);

  long k = 0;
  for ( int y = 0; y < ysize; y++ )
    for( int x = 0; x < xsize; x++, k++ )
    {
      img.setPixel( x, y, data[channel][z*xsize*ysize + k] );
    }

  return img;
}

/** convert to ice image */
template<class P>
void MultiChannelImage3DT<P>::convertToGrey( NICE::Image & img, int z, uint channel,  bool normalize ) const
{
  assert( channel < numChannels );

  P min, max;

  if ( normalize )
    statistics( min, max, channel );

  bool skip_assignment = false;

  img.resize( xsize, ysize );

  if ( normalize )
    if ( max - min < std::numeric_limits<double>::min() )
    {
      fprintf( stderr, "MultiChannelImage3DT<>::showChannel: max %f min %f\n", ( double )max, ( double )min );
      img.set( max );
      skip_assignment = true;
      fprintf( stderr, "MultiChannelImage3DT<>::showChannel: image is uniform! (%f)\n", ( double )max );
    }


  if ( ! skip_assignment )
  {
    long k = 0;

    for ( int y = 0 ; y < ysize; y++ )
    {
      for ( int x = 0 ; x < xsize ; x++, k++ )
      {
        if ( normalize )
        {
          img.setPixel( x, y, ( int )(( data[channel][z*xsize*ysize + k] - min ) * 255 / ( max - min ) ) );
        }
        else
        {
          img.setPixel( x, y, ( int )( data[channel][z*xsize*ysize + k] ) );
        }
      }
    }
  }
}

template<class P>
void MultiChannelImage3DT<P>::convertToColor( NICE::ColorImage & img, int z, const int chan1, const int chan2, const int chan3) const
{
  assert( chan1 < numChannels && chan2 < numChannels && chan3 < numChannels);

  img.resize( xsize, ysize );

  long k = 0;

  for ( int y = 0 ; y < ysize; y++ )
  {
    for ( int x = 0 ; x < xsize ; x++, k++ )
    {
      img.setPixel( x, y, 0, ( int )( data[chan1][z*xsize*ysize + k] ) );
      img.setPixel( x, y, 1, ( int )( data[chan2][z*xsize*ysize + k] ) );
      img.setPixel( x, y, 2, ( int )( data[chan3][z*xsize*ysize + k] ) );
    }
  }
}

template<class P>
ColorImage MultiChannelImage3DT<P>::getColor(int z) const
{
  assert( z < zsize );
	assert( numChannels >= 3 );

  NICE::ColorImage img( xsize, ysize );

  long k = 0;

  for ( int y = 0 ; y < ysize; y++ )
  {
    for ( int x = 0 ; x < xsize ; x++, k++ )
    {
      img.setPixel( x, y, 0, ( int )( data[0][z*xsize*ysize + k] ) );
      img.setPixel( x, y, 1, ( int )( data[1][z*xsize*ysize + k] ) );
      img.setPixel( x, y, 2, ( int )( data[2][z*xsize*ysize + k] ) );
    }
  }
  //showImage(img);
  //getchar();
  return img;
}

template<class P>
void MultiChannelImage3DT<P>::calcIntegral( uint channel )
{
  assert( channel < numChannels );
  assert( data[channel] != NULL );

  P *integralImage = data[channel];

  /** first column **/
  int k = xsize;
  for ( int y = 1 ; y < ysize; y++, k += xsize )
    integralImage[k] += integralImage[k-xsize];

  /** first row **/
  k = 1;
  for ( int x = 1 ; x < xsize; x++, k++ )
    integralImage[k] += integralImage[k-1];

  /** first stack (depth) **/
  k = xsize * ysize;
  for ( int z = 1 ; z < zsize; z++, k += (xsize*ysize) )
    integralImage[k] += integralImage[k-(xsize*ysize)];

  /** x-y plane **/
  k = xsize + 1;
  for ( int y = 1 ; y < ysize ; y++, k++ )
    for ( int x = 1 ; x < xsize ; x++, k++ )
    {
      integralImage[k] += integralImage[k-1];
      integralImage[k] += integralImage[k - xsize];
      integralImage[k] -= integralImage[k - xsize - 1];
    }

  /** y-z plane **/
  k = xsize*ysize + xsize;
  for ( int z = 1 ; z < zsize ; z++, k+=xsize )
    for ( int y = 1 ; y < zsize ; y++, k+=xsize )
    {
      integralImage[k] += integralImage[k-(xsize*ysize)];
      integralImage[k] += integralImage[k - xsize];
      integralImage[k] -= integralImage[k - xsize - (xsize*ysize)];
    }
  
  /** x-z plane **/
  k = xsize*ysize + 1;
  for ( int z = 1 ; z < zsize ; z++, k+=((xsize*ysize)-(xsize-1)) )
    for ( int x = 1 ; x < xsize ; x++, k++ )
    {
      integralImage[k] += integralImage[k-1];
      integralImage[k] += integralImage[k - (xsize*ysize)];
      integralImage[k] -= integralImage[k - (xsize*ysize) - 1];
    }
    
  /** all other pixels **/
  k = xsize*ysize + xsize + 1;
  for ( int z = 1 ; z < zsize ; z++, k+= xsize )
  {
    for ( int y = 1 ; y < ysize ; y++, k++ )
    {
      for ( int x = 1 ; x < xsize ; x++, k++ )
      {
        integralImage[k] += integralImage[k - (xsize*ysize)];
        integralImage[k] += integralImage[k - xsize];
        integralImage[k] += integralImage[k - 1];
        integralImage[k] += integralImage[k - (xsize*ysize) - xsize - 1];
        integralImage[k] -= integralImage[k - (xsize*ysize) - xsize];
        integralImage[k] -= integralImage[k - (xsize*ysize) - 1];
        integralImage[k] -= integralImage[k - xsize - 1];
      }
    }
  }
}

template<class P>
void MultiChannelImage3DT<P>::calcVariance( uint srcchan, uint tarchan )
{
  assert( srcchan < tarchan );
  assert( tarchan < numChannels );
  assert( data[srcchan] != NULL );
  assert( data[tarchan] != NULL );
  
  uint windowsize = 3;
  int win = (windowsize-1)/2;
  
  for ( int z = 0; z < zsize; z++ )
  {
    for ( int y = 0; y < ysize; y++ )
    {
      for ( int x = 0; x < xsize; x++ )
      {
        int meansum = 0;
          for ( int u = -win; u <= win; u++ ) 
          {
            for ( int v = -win; v <= win; v++ )
            {
              for ( int w = -win; w <= win; w++)
              {
                int u_tmp = u;
                int v_tmp = v;
                int w_tmp = w;
                if ( (x+u<0) || (x+u>=xsize) )
                  u_tmp = -u_tmp;
                if ( (y+v<0) || (y+v>=ysize) )
                  v_tmp = -v_tmp;
                if ( (z+w<0) || (z+w>=zsize) )
                  w_tmp = -w_tmp;
                meansum += get( x+u_tmp, y+v_tmp, z+w_tmp, srcchan );
              }
            }
          }
        meansum /= (windowsize*windowsize*windowsize);
        
        unsigned long varsum = 0;
        for ( int u = -win; u <= win; u++ ) 
        {
          for ( int v = -win; v <= win; v++ )
          {
            for ( int w = -win; w <= win; w++)
            {
              int u_tmp = u;
              int v_tmp = v;
              int w_tmp = w;
              if ( (x+u<0) || (x+u>=xsize) )
                u_tmp = -u_tmp;
              if ( (y+v<0) || (y+v>=ysize) )
                v_tmp = -v_tmp;
              if ( (z+w<0) || (z+w>=zsize) )
                  w_tmp = -w_tmp;
              
              long sdev = (get( x+u_tmp, y+v_tmp, z+w_tmp, srcchan ) - meansum );
              varsum += (sdev*sdev);
            }
          }
        }
        varsum /= (windowsize*windowsize+windowsize)-1;
        set( x, y, z, varsum, tarchan );
      }
    }
  }
}

template<class P>
P MultiChannelImage3DT<P>::getIntegralValue(int ulfx, int ulfy, int ulfz, int lrbx, int lrby, int lrbz, int channel) const
{
  ulfx = std::max(ulfx-1, -1);
  ulfx = std::min(ulfx, xsize-1);
  ulfy = std::max(ulfy-1, -1);
  ulfy = std::min(ulfy, ysize-1);
  ulfz = std::max(ulfz-1, -1);
  ulfz = std::min(ulfz, zsize-1);

  lrbx = std::max(lrbx, 0);
  lrbx = std::min(lrbx, xsize-1);
  lrby = std::max(lrby, 0);
  lrby = std::min(lrby, ysize-1);
  lrbz = std::max(lrbz, 0);
  lrbz = std::min(lrbz, zsize-1);
  
  double val1, val2, val3, val4, val5, val6, val7, val8;
  val1 = get(lrbx, lrby, lrbz, channel);
  if( ulfz > -1 )
    val2 = get(lrbx, lrby, ulfz, channel);
  else
    val2 = 0;
  if( ulfx > -1 )
    val3 = get(ulfx, lrby, lrbz, channel);
  else
    val3 = 0;
  if( ulfx > -1 && ulfz > -1 )
    val4 = get(ulfx, lrby, ulfz, channel);
  else
    val4 = 0;
  if( ulfy > -1 )
    val5 = get(lrbx, ulfy, lrbz, channel);
  else
    val5 = 0;
  if( ulfy > -1 && ulfz > -1 )
    val6 = get(lrbx, ulfy, ulfz, channel);
  else
    val6 = 0;
  if( ulfx > -1 && ulfy > -1 )
    val7 = get(ulfx, ulfy, lrbz, channel);
  else
    val7 = 0;
  if(ulfx > -1 && ulfy > -1 && ulfz > -1)
    val8 = get(ulfx, ulfy, ulfz, channel);
  else
    val8 = 0;
  
  P volume = abs((lrbx-ulfx)*(lrby-ulfy)*(lrbz-ulfz));
  P val = val1 - val2 - val3 + val4 - ( val5 - val6 - val7 + val8 );

  if (volume != 0)
    return val/volume;
  else
    return 0.0;
}

template<class P>
void MultiChannelImage3DT<P>::store( std::string filename ) const
{
  // simple raw format
  FILE *f = fopen( filename.c_str(), "w" );

  if ( f == NULL ) {
    fprintf( stderr, "MultiChannelImage3DT::store: error writing to %s\n", filename.c_str() );
    exit( -1 );
  }

  fwrite( &xsize, sizeof( int ), 1, f );
  fwrite( &ysize, sizeof( int ), 1, f );
  fwrite( &zsize, sizeof( int ), 1, f );
  fwrite( &numChannels, sizeof( uint ), 1, f );

  for ( uint channel = 0 ; channel < numChannels ; channel++ )
  {
    assert( data[channel] != NULL );
    fwrite( data[channel], sizeof( P ), xsize*ysize*zsize, f );
  }

  fclose( f );
}

template<class P>
void MultiChannelImage3DT<P>::restore( std::string filename )
{
  // simple raw format
  FILE *f = fopen( filename.c_str(), "r" );

  if ( f == NULL ) {
    fprintf( stderr, "MultiChannelImage3DT::store: error reading from %s\n", filename.c_str() );
    exit( -1 );
  }

  fread( &xsize, sizeof( int ), 1, f );
  fread( &ysize, sizeof( int ), 1, f );
  fread( &zsize, sizeof( int ), 1, f );
  fread( &numChannels, sizeof( uint ), 1, f );

  if ( numChannels > 0 ) {
    reInit( xsize, ysize, zsize, numChannels );

    for ( uint channel = 0 ; channel < numChannels ; channel++ )
    {
      assert( data[channel] != NULL );
      fread( data[channel], sizeof( P ), xsize*ysize*zsize, f );
    }
  } else {
    freeData();
    data = NULL;
  }

  fclose( f );
}

template<class P>
int MultiChannelImage3DT<P>::width() const
{
  return xsize;
}

template<class P>
int MultiChannelImage3DT<P>::height() const
{
  return ysize;
}

template<class P>
int MultiChannelImage3DT<P>::depth() const
{
  return zsize;
}

template<class P>
int MultiChannelImage3DT<P>::channels() const
{
  return ( int )numChannels;
}

template<class P>
int MultiChannelImage3DT<P>::getPixelInt( int x, int y, int z, int channel ) const
{
  throw( "this type is not implemented\n" );
  return -1;
}

template<class P>
double MultiChannelImage3DT<P>::getPixelFloat( int x, int y, int z, int channel ) const
{
  throw( "this type is not implemented\n" );
  return -1.0;
}

template<class P>
void MultiChannelImage3DT<P>::setPixelInt( int x, int y, int z, int channel, int pixel )
{
  throw( "this type is not implemented\n" );
}

template<class P>
void MultiChannelImage3DT<P>::setPixelFloat( int x, int y, int z, int channel, double pixel )
{
  throw( "this type is not implemented\n" );
}

#define SET_FUNCS_PROTO_MACRO3D(MYTYPE) \
template<>\
int MultiChannelImage3DT<MYTYPE>::getPixelInt(int x, int y, int z, int channel) const;\
template<>\
double MultiChannelImage3DT<MYTYPE>::getPixelFloat(int x, int y, int z, int channel) const;\
template<>\
void MultiChannelImage3DT<MYTYPE>::setPixelInt(int x, int y, int z, int channel, int pixel);\
template<>\
void MultiChannelImage3DT<MYTYPE>::setPixelFloat(int x, int y, int z, int channel, double pixel);

SET_FUNCS_PROTO_MACRO3D( double )
SET_FUNCS_PROTO_MACRO3D( int )
SET_FUNCS_PROTO_MACRO3D( long int )
SET_FUNCS_PROTO_MACRO3D( float )
SET_FUNCS_PROTO_MACRO3D( unsigned int )

} // namespace


