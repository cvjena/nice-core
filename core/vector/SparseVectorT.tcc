#ifndef SPARSEVECTORT_TCC
#define SPARSEVECTORT_TCC

#include <iostream>
#include <algorithm>

#include <math.h>
#include <assert.h>
#include <limits>

#include <stdio.h>

#include "core/vector/SparseVectorT.h"

namespace NICE {
template<typename I, typename V>
SparseVectorT<I,V>::SparseVectorT ( const std::map<I, V> & mymap ):std::map<I, V> ( mymap )
{
  //we assume that the last element specifies the maximal size :)
  if ( mymap.size() > 0 )
  {
    typename std::map<I, V>::const_reverse_iterator lastElem = mymap.rbegin();
    dim = lastElem->first;
  }
}

template<typename I, typename V>
SparseVectorT<I,V>::SparseVectorT ( I k, V v )
{
  this->insert ( std::pair<short, double> ( k, v ) );
  dim = k;
}

template<typename I, typename V>
SparseVectorT<I,V>::SparseVectorT ( int _dim ) : dim ( _dim )
{
}

template<typename I, typename V>
SparseVectorT<I,V>::SparseVectorT ( const NICE::Vector &v, double tolerance )
{
  dim = (int)v.size();
  for ( int i = 0; i < dim; i++ )
  {
    if ( fabs ( v[i] ) > tolerance )
      this->insert ( std::pair<I, V> ( i, v[i] ) );
  }
}

template<typename I, typename V>
void SparseVectorT<I,V>::sub ( const SparseVectorT<I,V> & v )
{
  for ( typename SparseVectorT<I,V>::const_iterator v_it = v.begin(); v_it != v.end(); v_it++ )
    ( *this ) [v_it->first] -= v_it->second;
}

template<typename I, typename V>
void SparseVectorT<I,V>::add ( const SparseVectorT<I,V> & v )
{
  add ( v, 1.0 );
}

template<typename I, typename V>
void SparseVectorT<I,V>::add ( const SparseVectorT<I,V> & v, double lambda )
{
  for ( typename SparseVectorT<I,V>::const_iterator v_it = v.begin();
        v_it != v.end();
        v_it++ )
    ( *this ) [v_it->first] += v_it->second * lambda;
}

template<typename I, typename V>
void SparseVectorT<I,V>::add ( V val )
{
  for ( typename SparseVectorT<I,V>::iterator it  = this->begin(); it != this->end(); it++ )
    it->second += val;
}

template<typename I, typename V>
void SparseVectorT<I,V>::divide ( const SparseVectorT<I,V> & v )
{
  for ( typename SparseVectorT<I,V>::iterator it = this->begin(); it != this->end(); )
  {
    bool deleteEntry = false;
    typename SparseVectorT<I,V>::const_iterator v_it = v.find ( it->first );

    if ( v_it == v.end() ) {
      fthrow ( Exception, "Division by Zero !" );
    } else {
      it->second /= v_it->second;
      if ( fabs ( it->second ) < 1e-20 )
        deleteEntry = true;
    }

    if ( deleteEntry )
      this->erase ( it++ );
    else
      it++;
  }
}

template<typename I, typename V>
void SparseVectorT<I,V>::divide ( V v )
{
  if ( fabs ( v ) <  1e-20 )
    fthrow ( Exception, "Division by Zero !" );

  for ( typename SparseVectorT<I,V>::iterator it = this->begin(); it != this->end(); )
  {
    bool deleteEntry = false;

    it->second /= v;
    if ( fabs ( it->second ) < 1e-20 )
      deleteEntry = true;

    if ( deleteEntry )
      this->erase ( it++ );
    else
      it++;
  }
}

template<typename I, typename V>
void SparseVectorT<I,V>::multiply ( const SparseVectorT<I,V> & v )
{
  for ( typename SparseVectorT<I,V>::iterator it = this->begin(); it != this->end(); )
  {
    bool deleteEntry = false;
    typename SparseVectorT<I,V>::const_iterator v_it = v.find ( it->first );

    if ( v_it == v.end() )
      deleteEntry = true;
    else {
      it->second *= v_it->second;
      if ( fabs ( it->second ) < 1e-20 )
        deleteEntry = true;
    }

    if ( deleteEntry )
      this->erase ( it++ );
    else
      it++;
  }
}

template<typename I, typename V>
void SparseVectorT<I,V>::multiply ( V val )
{
  for ( typename SparseVectorT<I,V>::iterator it = this->begin(); it != this->end(); )
  {
    it->second *= val;
    if ( fabs ( it->second ) < 1e-20 )
    {
      this->erase ( it++ );
    } else {
      it++;
    }
  }
}

template<typename I, typename V>
double SparseVectorT<I,V>::innerProduct ( const SparseVectorT<I,V> & v ) const
{
  V prod = 0.0;

  typename SparseVectorT<I,V>::const_iterator it1 = this->begin();
  typename SparseVectorT<I,V>::const_iterator it2 = v.begin();

  while ( ( it1 != this->end() ) && ( it2 != v.end() ) )
  {
    if ( it1->first == it2->first )
    {
      prod += it1->second * it2->second;
      ++it1;
      ++it2;
    }
    else if ( it1->first < it2->first )
      ++it1;
    else
      ++it2;
  }

  return prod;
}

template<typename I, typename V>
void SparseVectorT<I,V>::restore ( std::istream & is, int format )
{
  I first;
  V second;

  if ( format == FORMAT_INDEX ) 
  {
    std::string tag;
    is >> tag;
    if ( tag != "SVECTOR" ) {
      fthrow ( Exception, "Format error: starting tag is " << tag << " instead of SVECTOR" );
    }

    is >> dim;
    I size;
    is >> size;

    for ( int i = 0; i < size; i++ )
    {
      is >> first;
      is >> second;
      ( *this ) [first] = second;
    }

    is >> tag;

    if ( tag != "END" ) {
      fthrow ( Exception, "Format error: end tag is " << tag << " instead of END" );
    }
  } else if ( format == FORMAT_INDEX_LINE ) {
    
    std::string line;
    std::getline ( is, line );
    std::istringstream iss ( line, std::istringstream::in);

    while ( !iss.eof() )
    {
      char c;
      if ( !( iss >> first) ) break;
      if ( !( iss >> c ) ) break;
      if ( !( iss >> second ) ) break;
      ( *this ) [first] = second;
    }

    // preserve dimension setting
    //dimension = -1;
  } else {
    fthrow(Exception, "Unknown format! (see SparseVectorT.h for details)");
  }
}

template<typename I, typename V>
void SparseVectorT<I,V>::store ( std::ostream & os, int format ) const
{
  if ( format == FORMAT_INDEX ) {
    os << "SVECTOR ";

    os << dim << " " << this->size() << std::endl;

    for ( typename SparseVectorT<I,V>::const_iterator it = this->begin(); it != this->end(); it++ )
    {
      os << it->first << " " << it->second << " ";
    }
    os << "END" << std::endl;
  } 
  else if ( format == FORMAT_INDEX_LINE ) 
  {
    for ( typename SparseVectorT<I,V>::const_iterator it = this->begin(); it != this->end(); it++ )
    {
      if ( it != this->begin() )
        os << " ";
      os << it->first << ":" << it->second;
    }
    os << std::endl;
  } else {
    fthrow(Exception, "Unknown format! (see SparseVectorT.h for details)");
  }
}

template<typename I, typename V>
void SparseVectorT<I,V>::clear ()
{
  std::map<I, V>::clear();
}

template<typename I, typename V>
V SparseVectorT<I,V>::sum () const
{
  V sumv = 0.0;
  for ( typename SparseVectorT<I,V>::const_iterator it = this->begin(); it != this->end(); it++ )
    sumv += it->second;

  return sumv;
}

template<typename I, typename V>
void SparseVectorT<I,V>::normalize ()
{
  V sum = this->sum();

  if ( fabs ( sum ) < 1e-20 )
  {
    fprintf ( stderr, "WARNING: normalization failed !\n" );
    for ( typename SparseVectorT<I,V>::iterator it = this->begin(); it != this->end(); it++ )
      it->second = 0.0;
  } else 
  {
    for ( typename SparseVectorT<I,V>::iterator it = this->begin(); it != this->end(); it++ )
      it->second /= sum;
  }
}

template<typename I, typename V>
void SparseVectorT<I,V>::normalize ( V minv, V maxv )
{
  typename SparseVectorT<I,V>::iterator it = this->begin();
  V oldmin = it->second;
  V oldmax = it->second;
  it++;
  for ( ; it != this->end(); it++ )
  {
    oldmin = std::min ( oldmin, it->second );
    oldmax = std::max ( oldmax, it->second );
  }

  V diff = oldmax - oldmin;
  if ( diff == 0.0 )
  {
    for ( it = this->begin(); it != this->end(); it++ )
    {
      it->second = 0;
    }
    return;
  }

  for ( it = this->begin(); it != this->end(); it++ )
  {
    it->second = ( ( ( it->second - oldmin ) / diff ) * ( maxv - minv ) ) + minv;
  }
}

template<typename I, typename V>
void SparseVectorT<I,V>::addMap ( const std::map<int, int> & v, double lambda )
{
  for ( std::map<int, int>::const_iterator v_it = v.begin(); v_it != v.end(); v_it++ )
    ( *this ) [(I)v_it->first] += (V)v_it->second * lambda;
}

template<typename I, typename V>
void SparseVectorT<I,V>::addMap ( const std::map<int, double> & v, double lambda )
{
  for ( std::map<int, double>::const_iterator v_it = v.begin(); v_it != v.end(); v_it++ )
    ( *this ) [(I)v_it->first] += (V)v_it->second * lambda;
}

template<typename I, typename V>
I SparseVectorT<I,V>::maxElement () const
{
  I maxindex = 0;
  V max = -std::numeric_limits<V>::max();
  for ( typename SparseVectorT<I,V>::const_iterator it = this->begin(); it != this->end(); it++ )
  {
    if ( it->second > max )
    {
      maxindex = it->first;
      max = it->second;
    }
  }
  return maxindex;
}

template<typename I, typename V>
I SparseVectorT<I,V>::maxElementExclusive ( I key ) const
{
  I maxindex = ( key == 0 ) ? 1 : 0;
  double max = - std::numeric_limits<double>::max();
  for ( typename SparseVectorT<I,V>::const_iterator it = this->begin(); it != this->end(); it++ )
  {
    if ( ( it->first != key ) && ( it->second > max ) )
    {
      maxindex = it->first;
      max = it->second;
    }
  }
  return maxindex;
}

template<typename I, typename V>
double SparseVectorT<I,V>::entropy () const
{
  double entropy = 0.0;
  double sum = 0.0;
  for ( typename SparseVectorT<I,V>::const_iterator j = this->begin(); j != this->end(); j++ )
  {
    if ( j->second <= 0.0 ) 
      continue;
    entropy -= (double)j->second * log ( (double)j->second );
    sum += (double)j->second;
  }
  entropy /= sum;
  entropy += log ( sum );
  return entropy;
}

template<typename I, typename V>
void SparseVectorT<I,V>::getSortedIndices ( std::vector<I> & indizes ) const
{
  typename std::vector< std::pair<V, I> > tmp;
  for ( typename SparseVectorT<I,V>::const_iterator i = this->begin(); i != this->end() ; i++ )
    tmp.push_back ( std::pair<V, I> ( i->second, i->first ) );

  std::sort ( tmp.begin(), tmp.end() );

  for (typename std::vector<std::pair<V, I> >::const_iterator j = tmp.begin(); j != tmp.end(); j++ )
    indizes.push_back ( j->second );
}

template<typename I, typename V>
V SparseVectorT<I,V>::max () const
{
  V max = - std::numeric_limits<V>::max();
  for ( typename SparseVectorT<I,V>::const_iterator it = this->begin(); it != this->end(); it++ )
  {
    if ( it->second > max )
      max = it->second;
  }
  return max;
}

template<typename I, typename V>
V SparseVectorT<I,V>::min () const
{
  V min = std::numeric_limits<V>::max();
  for ( typename SparseVectorT<I,V>::const_iterator it = this->begin(); it != this->end(); it++ )
  {
    if ( it->second < min )
      min = it->second;
  }
  return min;
}

template<typename I, typename V>
V SparseVectorT<I,V>::get ( I i ) const
{
  typename SparseVectorT<I,V>::const_iterator it = this->find ( i );
  if ( it == this->end() )
    return 0.0;
  else
    return it->second;
}

template<typename I, typename V>
bool SparseVectorT<I,V>::set ( I i , V newValue ) 
{
  typename SparseVectorT<I,V>::iterator it = this->find ( i );
  if ( it == this->end() ) 
  {
    // behavior change (2/2/2012 by erik)
    if ( newValue > 1e-20 )
      insert ( std::pair<I, V> ( i, newValue ) );
    //update our dimensions
    if ( i > dim ) //changed on 10-02-2012 by alex
      dim = i;
    return false;
  } else 
  {
    it->second = newValue;
    return true;
  }
}

template<typename I, typename V>
void SparseVectorT<I,V>::setDim ( int _dim )
{
  dim = _dim;
}

template<typename I, typename V>
int SparseVectorT<I,V>::getDim() const
{
  return dim;
}

template<typename I, typename V>
double SparseVectorT<I,V>::minimumKernel ( const SparseVectorT<I,V> & b ) const
{
  V sum = 0.0;

  typename SparseVectorT<I,V>::const_iterator i = this->begin();
  typename SparseVectorT<I,V>::const_iterator j = b.begin();

  while ( ( i != this->end() ) && ( j != b.end() ) )
  {
    I idx1 = i->first;
    I idx2 = j->first;
    if ( idx1 == idx2 ) {
      sum += std::min ( i->second, j->second );
      i++;
      j++;
    } else if ( idx1 > idx2 ) {
      j++;
    } else {
      i++;
    }
  }
  return sum;
}

    
template<typename I, typename V>
I SparseVectorT<I,V>::pickRandomSample() const
{
  typedef typename std::vector< std::pair<V, I> > CumSumType;
  CumSumType cumsum;

  // calculate the cumulative sum, also known
  // as the distribution function F
  typename SparseVectorT<I,V>::const_iterator i = this->begin();
  for ( ; i != this->end(); i++ )
  {
    V value;
    if ( i == this->begin() )
      value = i->second;
    else
      value = cumsum.rbegin()->first + i->second;

    cumsum.push_back( std::pair<V, I> ( value, i->first ) );
  }

  V sum = cumsum.rbegin()->first;

  // sample between 0 and sum
  V t = (V)(randDouble() * sum);

  // find the position to calculate F^{-1}
  //
  std::pair<V, I> searchElement ( (V)t, (I)0 );
  typename CumSumType::const_iterator j = std::lower_bound(cumsum.begin(), cumsum.end(), searchElement );

  // return element index
  return j->second;
}

template<typename I, typename V>
void SparseVectorT<I,V>::convertToVectorT(NICE::VectorT<V> & v ) const
{
  int dimension (this->getDim());
  //dimension flag was not set properly
  if (dimension < 0)
  {
    typename SparseVectorT<I,V>::const_iterator i = this->end(); i--;
    int dist (distance(this->begin(), this->end()) );
    if (dist > 0)
      dimension = i->first+1; //plus one, since this is the index, but we need the resulting size
    //we're not allowed here to set the dimension flag, since we want to have this method to be a const one
  }

  //our sparse vector is empty
  if (dimension <= 0)
  {
    v.clear();
    v.resize(0);
    return;
  }

  //resize the new VectorT
  v.resize(dimension);

  //set default values to zero
  v.set( (V) 0.0);

  //add the actual content
  typename SparseVectorT<I,V>::const_iterator i = this->begin();
  for ( ; i != this->end(); i++ )
  {
    //just to be sure that we do not get some errors due to badly set dimension flags
    if (i->first < dimension)
      v[i->first] = i->second;
  }
}

} //namepspace NICE
#endif
