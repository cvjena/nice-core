/** 
* @file PartialGenericMatrix.h
* @brief matrix interface for indirect sub-matrix multiplications
* @author Erik Rodner
* @date 01/26/2011
*/
#ifndef PARTIALGENERICMATRIXINCLUDE
#define PARTIALGENERICMATRIXINCLUDE

#include <set> 
#include <vector> 

#include "GenericMatrix.h"


namespace NICE
{

/** matrix interface for indirect sub-matrix multiplications */
class PartialGenericMatrix : public GenericMatrix
{
  public:

    typedef std::vector<int> SetType;

    /** multiply a sub-matrix with a given vector: Asub * xsub = ysub */
    virtual void multiply ( const SetType & rowSet, const SetType & columnSet, NICE::Vector & y, const NICE::Vector & x) const = 0;

    /** multiply with a vector: A*x = y */
    virtual void multiply (NICE::Vector & y, const NICE::Vector & x) const = 0;

    virtual double getDiagonalElement ( uint i ) const = 0;

    /** simple destructor */
    virtual ~ PartialGenericMatrix ()
    {
    };

};



}		// namespace

#endif
