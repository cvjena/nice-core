#ifndef GMSTANDARDINCLUDE
#define GMSTANDARDINCLUDE

#include "PartialGenericMatrix.h"


namespace NICE
{


/** implementation of PartialGenericMatrix using simple direct multiplication */
class GMStandard : public PartialGenericMatrix
{
	protected:
		NICE::Matrix A;

	public:
		GMStandard (const NICE::Matrix & _A):A (_A)
		{
		};

    /** get the number of rows in A */
		uint rows () const
		{
			return A.rows ();
		};

    /** get the number of columns in A */
		uint cols () const
		{
			return A.cols ();
		};

    /** multiply with a vector: A*x = y */
		void multiply (NICE::Vector & y, const NICE::Vector & x) const
		{
      y.resize(rows());
			y.multiply (A, x);
		};

    virtual void multiply ( const PartialGenericMatrix::SetType & rowSet, const PartialGenericMatrix::SetType & columnSet, NICE::Vector & y, const NICE::Vector & x) const;
    
    virtual double getDiagonalElement ( uint i ) const;
};

}

#endif
