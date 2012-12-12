/** 
 * @file VVector.h
 * @brief vector of vector
 * @author Erik Rodner
 * @date 02/15/2008
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "VVector.h"

using namespace std;
using namespace NICE;


VVector::VVector()
{
    bufsize = 0;
    ioUntilEndOfFile = true;
}

VVector::VVector( const std::string & filename )
{
    read(filename);
    ioUntilEndOfFile = true;
}

VVector::VVector( int count, int dim)
{
	reSize(count,dim);
  ioUntilEndOfFile = true;
}

void VVector::reSize(int count, int dim)
{
	clear();
	for(int i = 0; i < count; i++)
	{
		Vector vec(dim);
		vec.set(0.0);
		push_back(vec);
	}
}

VVector::~VVector()
{
}

void VVector::restore ( istream & is, int format )
{
  NICE::Vector f;
  double val;
  
  int nrOfVectors(0);
  int nrOfEntries(0);
  //if we do not want to read until eof, we say how many entries we have
  if (!ioUntilEndOfFile)
  {
    try{
      is >> nrOfVectors;
      std::string tmp;
      is >> tmp;
      is >> nrOfEntries;
    }
    catch ( ...)
    {
      //keep the default settings of size 0
    }
  } 
  
  if ( format == FILEFORMAT_NICE )
  {
    if (ioUntilEndOfFile)
    {
      while ( ! is.eof() )
      {
        try {
          is >> f;
        }
        catch ( ... )
        {
          break;
        }
        push_back ( f );
      }
    }
    else
    {
      for (int i = 0; i < nrOfVectors; i++)
      {
        try {
          is >> f;
        }
        catch ( ... )
        {
          break;
        }
        push_back ( f );
      }
    }
  } else if ( format == FILEFORMAT_LINE ) 
  {
    char line[65535];
    if (ioUntilEndOfFile)
    {
      while ( ! is.eof() )
      {
        vector<double> fdyn;
        if ( ! is.getline ( line, 65535 ) )
          break;

        std::istringstream ss ( line );
        while ( ss >> val )
          fdyn.push_back ( val );

        if ( fdyn.size() != 0 ) {
          f.resize ( fdyn.size() );
          f = NICE::Vector ( fdyn );
          push_back ( f );
        }
      }
    }
    else
    {
      for (int i = 0; i < nrOfVectors; i++)
      {
        vector<double> fdyn;
        if ( ! is.getline ( line, 65535 ) )
          break;

        std::istringstream ss ( line );
        while ( ss >> val )
          fdyn.push_back ( val );

        if ( fdyn.size() != 0 ) {
          f.resize ( fdyn.size() );
          f = NICE::Vector ( fdyn );
          push_back ( f );
        }        
      }
    }
  } else if ( format == FILEFORMAT_BINARY_CHAR ) 
  {

    if ( bufsize <= 0 ) {
      fprintf ( stderr, "VVector: you have to set buf size !!\n" );
      exit ( -1 );
    }
    unsigned char *buf = new unsigned char[bufsize];
    f = Vector ( bufsize );
    if (ioUntilEndOfFile)
    {    
      while ( ! is.eof() )
      {
        is.read ( ( char * ) buf, sizeof ( unsigned char ) *bufsize );
        if ( is.gcount() != ( int ) ( sizeof ( unsigned char ) *bufsize ) ) break;
        for ( size_t k = 0 ; k < bufsize ; k++ )
          f[k] = buf[k] / 512.0;
        push_back ( f );
      }
    }
    else
    {
      for (int i = 0; i < nrOfVectors; i++)
      {
        is.read ( ( char * ) buf, sizeof ( unsigned char ) *bufsize );
        if ( is.gcount() != ( int ) ( sizeof ( unsigned char ) *bufsize ) ) break;
        for ( size_t k = 0 ; k < bufsize ; k++ )
          f[k] = buf[k] / 512.0;
        push_back ( f );        
      }
    }
    delete [] buf;
  } else if ( format == FILEFORMAT_BINARY_DOUBLE ) 
  {

    if ( bufsize <= 0 ) {
      fprintf ( stderr, "VVector: you have to set buf size !!\n" );
      exit ( -1 );
    }

    double *buf = new double[bufsize];
    f = Vector ( bufsize );
    if (ioUntilEndOfFile)
    {     
      while ( ! is.eof() )
      {
        is.read ( ( char * ) buf, sizeof ( double ) *bufsize );
        if ( is.gcount() != ( int ) ( sizeof ( double ) *bufsize ) ) break;
        for ( size_t k = 0 ; k < bufsize ; k++ )
          f[k] = buf[k];
        push_back ( f );
      }
    }
    else
    {
      for (int i = 0; i < nrOfVectors; i++)
      {
        is.read ( ( char * ) buf, sizeof ( double ) *bufsize );
        if ( is.gcount() != ( int ) ( sizeof ( double ) *bufsize ) ) break;
        for ( size_t k = 0 ; k < bufsize ; k++ )
          f[k] = buf[k];
        push_back ( f );        
      }
    } 
    delete [] buf;
  }

}

void VVector::store ( ostream & os, int format ) const
{
  //if we do not want to read until eof, we say how many entries we have
  if (!ioUntilEndOfFile)
  {
    if (this->size() > 0)
    {
      os << this->size() << " x " << (*this)[0].size() << std::endl;
    }
  } 
  //now write the actual data    
  if ( format == FILEFORMAT_NICE )
  {
    for ( const_iterator i = begin();
          i != end();
          i++ )
    {
      const NICE::Vector & cluster = *i;
      os << cluster << endl;
    }
  } else if ( format == FILEFORMAT_LINE )
  {
    for ( const_iterator i = begin();
          i != end();
          i++ )
    {
      const NICE::Vector & cluster = *i;
      for ( size_t k = 0 ; k < cluster.size() ; k++ )
        os << cluster[k] << "\t";
      os << "\n";
    }
  } else if ( format == FILEFORMAT_BINARY_CHAR ) 
  {
    for ( const_iterator i = begin();
          i != end();
          i++ )
    {
      const NICE::Vector & cluster = *i;
      unsigned char *buf = new unsigned char[cluster.size() ];
      for ( size_t k = 0 ; k < cluster.size() ; k++ )
        buf[k] = ( unsigned char ) ( cluster[k] * 512 );
      os.write ( ( char * ) buf, sizeof ( unsigned char ) *cluster.size() );
      delete [] buf;
    }
  } else if ( format == FILEFORMAT_BINARY_DOUBLE ) {
    for ( const_iterator i = begin();
          i != end();
          i++ )
    {
      const NICE::Vector & cluster = *i;
      double *buf = new double[cluster.size() ];
      for ( size_t k = 0 ; k < cluster.size() ; k++ )
        buf[k] = ( double ) cluster[k];
      os.write ( ( char * ) buf, sizeof ( double ) *cluster.size() );
      delete [] buf;
    }
    }
}

void VVector::clear()
{
    vector<Vector>::clear();
}
	
void VVector::setBufSize ( size_t _bufsize )
{
    bufsize = _bufsize;
}


static size_t index_global = 0;
bool compareComponent ( const NICE::Vector & x, const NICE::Vector & y )
{
    return x[index_global] < y[index_global];
}


void VVector::sort ( size_t index )
{
    index_global = index;
    std::sort ( begin(), end(), compareComponent );
    index_global = 0;
}
	
void VVector::toMatrix ( NICE::Matrix & M, bool rowOriented ) const
{
	if ( size() > 0 ) {
		// check if there is a constant dimension
		int dimension = -1;
		for ( VVector::const_iterator i = begin(); i != end(); i++ )
			if ( dimension < 0 )
				dimension = i->size();
			else if ( (int)(i->size()) != dimension )
				fthrow(Exception, "Non-constant dimension inside of VVector, unable to convert this structure into a Matrix" );

		if ( rowOriented ) 
			M.resize ( size(), dimension );
		else
			M.resize ( dimension, size() );
		uint k = 0;
		for ( VVector::const_iterator i = begin(); i != end(); i++,k++ )
		{
			const Vector & x = *i;
			for ( int l = 0 ; l < dimension; l++ )
				if ( rowOriented )
					M ( k, l ) = x[l];
				else
					M ( l, k ) = x[l];
		}
	}
}
