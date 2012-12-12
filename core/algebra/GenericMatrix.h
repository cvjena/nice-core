/**
* @file GenericMatrix.h
* @brief matrix interface for indirect matrix multiplications
* @author Erik Rodner
* @date 05/14/2009

*/
#ifndef GENERICMATRIXINCLUDE
#define GENERICMATRIXINCLUDE

#include "core/basics/triplet.h"
#include "core/vector/SparseVectorT.h"


namespace NICE
{

/** matrix interface for indirect matrix multiplications */
class GenericMatrix
{
  public:

    /** multiply with a vector: A*x = y */
    virtual void multiply ( NICE::Vector & y, const NICE::Vector & x ) const = 0;

    /** get the number of rows in A */
    virtual uint rows () const = 0;

    /** get the number of columns in A */
    virtual uint cols () const = 0;

    /** simple destructor */
    virtual ~ GenericMatrix ()
    {
    };

};


/** sparse matrix vector multiplication */
class GMSparse : public GenericMatrix
{
  protected:
    // our representation of sparse matrices
    std::vector < NICE::triplet < int, int, double > > A;

    // we also have to store the size of the matrix
    uint m_rows;
    uint m_cols;

  public:

    /**
    * @brief empty constructor only initializing the size
    *
    * @param _rows number of rows of the matrix
    * @param _cols number of cols of the matrix
    */
    GMSparse ( uint _rows, uint _cols ) : m_rows ( _rows ), m_cols ( _cols )
    {
    }

    /**
    * @brief initialize the sparse structure with a dense matrix and a given
    * sparseness threshold
    *
    * @param A input matrix
    * @param epsilon if fabs(x) < epsilon, x is considered as zero
    */
    GMSparse ( const NICE::Matrix & A, double epsilon = 1e-9 );

    /** get the number of rows in A */
    uint rows () const
    {
      return m_rows;
    };

    /** get the number of columns in A */
    uint cols () const
    {
      return m_cols;
    };

    /** multiply with a vector: A*x = y */
    void multiply ( NICE::Vector & y, const NICE::Vector & x ) const;

};

/** implicit representation of a covariance matrix */
class GMCovariance: public GenericMatrix
{
  protected:

    // our data vectors stored in a matrix
    const NICE::Matrix *data;

  public:
    GMCovariance ( const NICE::Matrix * data );

    /** get the number of rows in A */
    uint rows () const
    {
      return data->rows();
    };

    /** get the number of columns in A */
    uint cols () const
    {
      return data->rows();
    };

    /** multiply with a vector: A*x = y */
    void multiply ( NICE::Vector & y, const NICE::Vector & x ) const;

};



}                // namespace

#endif
