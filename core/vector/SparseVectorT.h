/**
* @file SparseVectorT.h
* @brief sparse vector template class
* @author Erik Rodner and Björn Fröhlich
* @date 06.03.2012

*/
#ifndef SPARSEVECTORTINCLUDE
#define SPARSEVECTORTINCLUDE

#include <vector>
#include <map>
#include <iostream>

#include "core/basics/Persistent.h"
#include "core/vector/VectorT.h"

namespace NICE {

/** sparse vector template*/
template<class I, class V>
class SparseVectorT : public std::map<I, V>, public Persistent
{
  public:
    //! input/ouput formats
    enum {
      // SVECTOR dimension size index value index value ... END
      FORMAT_INDEX = 0,
      // index:value index:value \n
      FORMAT_INDEX_LINE = -9999 
    };

  protected:
    //! dimension of the SparseVector, not properly implemented! FIXME
    uint dim;
    

  public:

    /**
     * constructor which add one element to the SparseVector
     * @param k position of the value
     * @param v value
     */
    SparseVectorT ( I _k, 
                    V _v
                  );
    SparseVectorT ( const std::map<I, V> & _mymap );

    /**
     * simple constructor -> does nothing
     */
    SparseVectorT ():dim(0) {}

    /**
     * Constructor with the dimension
     * @param _dim dimension of the SparseVector
     */
    SparseVectorT ( uint _dim );

    /**
     * converts a ICE::Vector to a SparseVector with a tolerance factor
     * @param v input ICE::Vector
     * @param tolerance tolerance value
     */
    SparseVectorT ( const NICE::Vector & _v, 
                    double _tolerance = 1e-15
                  );

    /**
     * simple destructor
     */
    virtual ~SparseVectorT () {};

    /**
     * add the elements of a SparseVector to this SparseVector
     * @param v input SparseVector
     */
    void add ( const SparseVectorT<I,V> & _v );

    /**
     * add the elements of a SparseVector to this NICE::Vector and multiply each element with a constant lambda
     * @param v
     * @param lambda
     */
    void add ( const SparseVectorT<I,V> & _v, 
               double _lambda 
             );
    
    /**
     * add to each element a constant
     * @param value
     */
    void add ( V _value );
    
    /**
     * sub the elements of a SparseVector from this SparseVector
     * @param v input SparseVector
     */
    void sub ( const SparseVectorT<I,V> & _v );

    /** add a sparse vector given as a STL map with integer values multiplied with a scalar to the current vector */
    void addMap ( const std::map<uint, int> & _v, 
                  double _lambda = 1.0
                );

    /** add a sparse vector given as a STL map with double values multiplied with a scalar to the current vector */
    void addMap ( const std::map<uint, double> & _v, 
                  double _lambda = 1.0 
                );

    /** normalize, such that all elements sum to one */
    void normalize ();
    
    /** normalize in given interval between maxv and minv */
    void normalize (V _minv, 
                    V _maxv
                   );

    /** read from a stream */
    void restore ( std::istream & _is, 
                   int _format = 0 
                 );

    /** write to a stream */
    void store ( std::ostream & _os,
                 int _format = 0 
               ) const;

    /** clear the data of the vector */
    void clear ();

    /** calculate the entropy of the vector */
    double entropy () const;

    /**
     * each element of the SparseVector is multiplied by the elements of the input SparseVector
     * @param v input SparseVector
     */
    void multiply ( const SparseVectorT<I,V> & _v );

    /**
     * each element of the SparseVector is multiplied by a constant value
     * @param val factor
     */
    void multiply ( V _val );

    /**
     * each element of the SparseVector is divided by the elements of the input SparseVector
     * @param v input SparseVector
     */
    void divide ( const SparseVectorT<I,V> & _v );

    /**
     * each element of the SparseVector is divided by a constant value
     * @param v divisor
     */
    void divide ( V _v );

    /**
     * computes the inner product of two SparseVectors
     * @param v the second sparse vector
     * @return inner product
     */
    double innerProduct ( const SparseVectorT<I,V> & _v ) const;

    /** get the sum of all elements */
    V sum () const;

    /** get the maximum of all non-zero elements */
    V max () const;
    
    /** get the minimum of all non-zero elements */
    V min () const;

    /** get the index of the element with maximum value */
    I maxElement () const;

    /** get the index of the element with maximum value but do not consider a specific element */
    I maxElementExclusive ( I key ) const;

    /** get all indices of elements with non-zero values as a sorted STL vector */
    void getSortedIndices ( std::vector<I> & _indizes ) const;

    /** get an element */
    V get ( I _i ) const;

    /** set an element */
    bool set ( I _i , 
               V _newValue 
             );

    /**
     * set the dimension of the SparseVector
     * @param _dim
     */
    void setDim ( uint _dim );

    /**
     * returns the dimension of the SparseVector
     * @return dimension
     */
    uint getDim() const;
    
    /**
    * @brief calculate the value of the minimum kernel
    *
    * @param b 2nd argument of the minimum kernel, which is symmetric
    * @return resulting value of the minimum kernel
    */
    double minimumKernel ( const SparseVectorT<I,V> & _b ) const;

    /** pick a random index by interpreting the elements of the vector as
        an unnormalized multinomial distribution */
    I pickRandomSample() const;
    
    /** 
     * @brief computes a full NICE::VectorT from the current SparseVectorT object. the dimension has to be set properly for this method!
     * @param v resulting NICE::VectorT
     */
    void convertToVectorT(NICE::VectorT<V> & _v ) const ;     
};

typedef SparseVectorT<unsigned long, double> SparseVectorLong;
typedef SparseVectorT<unsigned int, double> SparseVectorInt;
typedef SparseVectorT<unsigned short, double> SparseVector;

} // namespace

#include "core/vector/SparseVectorT.tcc"



#endif
