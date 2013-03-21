#ifndef  _EVECTOR_BASICVECTOR_TCC
#define  _EVECTOR_BASICVECTOR_TCC

#include <string>
#include <sstream>
#include <stdexcept>
#include "core/basics/Exception.h"
#define _THROW_EVector(string) fthrow(Exception, string)
#include "core/vector/ippwrapper.h"
#include "core/vector/VectorT.h"
#include "core/vector/MatrixT.h"

#include <iostream>

namespace NICE {

template<typename ElementType>
inline VectorT<ElementType>::VectorT() {
  setDataPointer(NULL, 0, false);
}

template<typename ElementType>
inline VectorT<ElementType>::VectorT(const size_t size) {
  setDataPointer(new ElementType[size], size, false);
}

template<typename ElementType>
inline VectorT<ElementType>::VectorT(const size_t size,
                                     const ElementType& element) {
  setDataPointer(new ElementType[size], size, false);
  ippsSet(element, getDataPointer(), size);
}

template<typename ElementType>
inline VectorT<ElementType>::VectorT(const ElementType* _data,
                                     const size_t size) {
  setDataPointer(new ElementType[size], size, false);
  ippsCopy(_data, getDataPointer(), size);
}

template<typename ElementType>
inline VectorT<ElementType>::VectorT(ElementType* _data, const size_t size,
                                     const VectorBase::Mode mode) {
  switch (mode) {
  case external:
    setDataPointer(_data, size, true);
    break;
  case copy:
    setDataPointer(new ElementType[size], size, false);
    ippsCopy(_data, getDataPointer(), size);
    break;
   default:
     setDataPointer(NULL, 0, false);
     _THROW_EVector("Unknown Mode-enum.");
  }
}

template<typename ElementType>
VectorT<ElementType>::VectorT(const std::vector<ElementType>& v) {

    setDataPointer(new ElementType[v.size()], v.size(), false);
    ippsCopy(&(*v.begin()), getDataPointer(), v.size());
}


template <class ElementType>
VectorT<ElementType>::VectorT(std::istream& input, const bool & AwAFormat) {

  if (AwAFormat) //count, how many elements the vector contains
  {
    dataSize = 0;
    while (true)
    {
      ElementType c;
      input >> c;
      if (input.eof()) {
        break;
      }
      dataSize++;
    }
    //reset our stream to the beginning of the file
    input.clear() ;
    input.seekg(0, std::ios::beg) ;
  }
  else
    input >> dataSize;

  setDataPointer(new ElementType[dataSize], dataSize, false);

  if (AwAFormat)
  {
    int i = -1;
    while (true)
    {
      if (input.eof()) {
        break;
        // FIXME check if end of stream or followed by whitespace
      }
      i++;
      //ElementType c;
      //input >> c;
      //data[i] = c;
      input >> getDataPointer()[i];

    }
  }
  else
  {
    char c;
    input >> c;

    if (c != '<') {
      input.putback ( c );
    }

    int i = -1;
    while (true) {
      ws(input);
      if (input.peek() == int('>')) {
        std::string s;
        input >> s;
        break;
      }
      ++i;
      if (i >= int(dataSize)) {
        _THROW_EVector("syntax error 2 reading VectorT");
      }
      input >> getDataPointer()[i];
    }
  }
}

template<typename ElementType>
VectorT<ElementType>::VectorT(const VectorT<ElementType>& v) {
  setDataPointer(new ElementType[v.dataSize], v.dataSize, false);
  ippsCopy(v.getDataPointer(), getDataPointer(), dataSize);
}


#ifdef NICE_USELIB_LINAL
template<typename ElementType>
inline VectorT<ElementType>::VectorT(const LinAl::VectorC<ElementType>& v) {
  setDataPointer(new ElementType[v.size()], v.size(), false);
  for (unsigned int i = 0; i < size(); i++) {
      (*this)(i) = v(i);
  }
}

template<typename ElementType>
inline VectorT<ElementType>&
VectorT<ElementType>::operator=(const LinAl::VectorCC<ElementType>& v) {
  if (size() == 0 && !externalStorage && getDataPointer() == NULL) {
    setDataPointer(new ElementType[v.size()], v.size(), false);
  } else if (this->size() != (unsigned int) v.size()) {
    this->resize(v.size());
  }
  for (unsigned int i = 0; i < size(); i++) {
    (*this)[i] = v(i);
  }
  return *this;
}

#endif // NICE_USELIB_LINAL

template<typename ElementType>
inline VectorT<ElementType>::~VectorT() {
  if (!externalStorage && data != NULL) {
    delete[] data;
    setDataPointer(NULL, 0, false);
  }
}

template<typename ElementType>
void VectorT<ElementType>::resize(size_t size) {
  if(dataSize==size)
    return;

  // resize(0) simply means we want to empty the vector
  if(size==0)
  {
    ElementType *tmp = getDataPointer();
    if ( tmp != NULL )
      delete [] tmp;
    setDataPointer(NULL,0, false);
  }
  if(externalStorage) {
      if(size<dataSize) {
        dataSize = size;
        return;
      }
      _THROW_EVector("Cannot resize VectorT (external storage used)");
  }

  if(getDataPointer() != NULL) {
    size_t oldSize = dataSize;
    ElementType *tmp=getDataPointer();
    setDataPointer(new ElementType[size], size, false);
    ippsCopy(tmp, getDataPointer(), std::min(size, oldSize));
    delete[] tmp;
  } else {
    setDataPointer(new ElementType[size], size, false);
  }
}

template<typename ElementType>
void VectorT<ElementType>::append( const VectorT<ElementType> & v )
{
    unsigned int oldsize = size();
    resize ( oldsize + v.size() );
    VectorT<ElementType> subvec = getRangeRef(oldsize, size()-1);
    subvec = v;
}

template<typename ElementType>
void VectorT<ElementType>::append( const ElementType & v )
{
    unsigned int oldsize = size();
    resize ( oldsize + 1 );
    (*this)[oldsize] = v;
}


template<typename ElementType>
VectorT<ElementType> VectorT<ElementType>::getRange ( const ptrdiff_t i, const ptrdiff_t j ) const
{
    const ElementType *subDataPtr = getDataPointer() + i;
    VectorT<ElementType> subvec ( subDataPtr, j-i+1 );

    return subvec;
}

template<typename ElementType>
VectorT<ElementType> VectorT<ElementType>::getRangeRef ( const ptrdiff_t i, const ptrdiff_t j )
{
    ElementType *subDataPtr = getDataPointer() + i;
    
    VectorT<ElementType> subvec ( subDataPtr, j-i+1, 
	VectorBase::external );

    return subvec;
}

template<typename ElementType>
void VectorT<ElementType>::clear(void) {
  if (externalStorage) {
      _THROW_EVector("Cannot clear VectorT (external storage used)");
  }
  if (data != NULL) {
    delete[] data;
    setDataPointer(NULL, 0, false);
  }
}


template<class ElementType>
inline const VectorT<ElementType>*
VectorT<ElementType>::createConst(const ElementType* _data,
                                  const size_t size) {
  VectorT<ElementType>* result = new VectorT<ElementType>;
  result->setConstDataPointer(_data, size);
  return result;
}

template<class ElementType>
const ElementType& VectorT<ElementType>::operator()(const ptrdiff_t i) const
{
    if((ptrdiff_t)dataSize<=i||i<0) {
        //std::__throw_out_of_range("VectorT () access out of range");
		throw std::out_of_range("VectorT () access out of range");
    }
    return constData[i];
}

template<class ElementType>
ElementType& VectorT<ElementType>::operator()(const ptrdiff_t i) {
    if((ptrdiff_t)dataSize<=i||i<0) {
        //std::__throw_out_of_range("VectorT () access out of range");
		throw std::out_of_range("VectorT () access out of range");
    }
    return data[i];
}

template<class ElementType>
inline bool
VectorT<ElementType>::operator==(const VectorT<ElementType>& v) const {
  if (size() != v.size()) {
     throw std::invalid_argument("VectorT::operator==(): v.size() != size()");
  } else if (size() == 0) {
    return true;
  }
  for (unsigned int i = 0; i < size(); i++) {
    if(!(operator[](i) == v[i]))
        return false;
  }
  return true;
}

template<class ElementType>
inline bool
VectorT<ElementType>::operator!=(const VectorT<ElementType>& v) const {
  if (size() != v.size()) {
    throw std::invalid_argument("VectorT::operator!=(): v.size() != size()");
  } else if (size() == 0) {
    return false;
  }
  for (unsigned int i = 0; i < size(); i++) {
    if(!(operator[](i) == v[i]))
        return true;
  }
  return false;
}

template<typename ElementType>
void VectorT<ElementType>::multiply(const MatrixT<ElementType>& a, const VectorT<ElementType>& v, bool atranspose)
{
    size_t arows, acols;
    if(atranspose) {
        arows=a.cols();
        acols=a.rows();
    } else {
        arows=a.rows();
        acols=a.cols();
    }

    if (size() == 0)
        resize(arows);
    if (arows != size() || acols != v.size())
        _THROW_EVector("Matrix multiplication: inconsistent sizes.");

#ifdef NICE_USELIB_IPP
        size_t tsize=sizeof(ElementType);
        IppStatus ret;

        if(atranspose)
        {
            ret = ippmMul_mv(a.getDataPointer(), a.rows()*tsize, tsize, a.rows(), a.cols(),
                             v.getDataPointer(), tsize, v.size(),
                             this->getDataPointer(), tsize);
        }
        else
        {
            ret = ippmMul_tv(a.getDataPointer(), a.rows()*tsize, tsize, a.rows(), a.cols(),
                             v.getDataPointer(), tsize, v.size(),
                             this->getDataPointer(), tsize);
        }

        if(ret!=ippStsNoErr)
           _THROW_EVector(ippGetStatusString(ret));

#else
    #pragma omp parallel for
    // FIXME not very efficient
    for (int i = 0; i < int(arows); i++)
    {
        ElementType sum = ElementType(0);
        for (unsigned int k = 0; k < acols; k++)
        {
            ElementType ela = atranspose ? a(k, i) : a(i, k);
            sum += ela * v(k);
        }
        (*this)(i) = sum;
    }
#endif
}

template<typename ElementType>
void VectorT<ElementType>::multiply(const VectorT<ElementType>& v, const RowMatrixT<ElementType>& a, bool atranspose)
{
    size_t arows, acols;
    if(atranspose) {
        arows=a.cols();
        acols=a.rows();
    } else {
        arows=a.rows();
        acols=a.cols();
    }

    if (size() == 0)
        resize(acols);
    if (acols != size() || arows != v.size())
        _THROW_EVector("Matrix multiplication: inconsistent sizes.");

#ifdef NICE_USELIB_IPP
        size_t tsize=sizeof(ElementType);
        IppStatus ret;
        if(atranspose)
        {
                ret = ippmMul_mv(a.getDataPointer(), a.cols()*tsize, tsize, a.cols(), a.rows(),
                                v.getDataPointer(), tsize, v.size(),
                                this->getDataPointer(), tsize);
        }
        else
        {
                ret = ippmMul_tv(a.getDataPointer(), a.cols()*tsize, tsize, a.cols(), a.rows(),
                                v.getDataPointer(), tsize, v.size(),
                                this->getDataPointer(), tsize);
        }

        if(ret!=ippStsNoErr)
	   _THROW_EVector(ippGetStatusString(ret));

#else
        #pragma omp parallel for
        // FIXME not very efficient
        for (int i = 0; i < int(acols); i++)
        {
            ElementType sum = ElementType(0);
            for (unsigned int k = 0; k < arows; k++)
            {
                ElementType ela = atranspose ? a(i, k) : a(k, i);
                sum += v(k) * ela;
            }
            (*this)(i) = sum;
        }
#endif
}

template<typename ElementType>
void VectorT<ElementType>::multiply(const RowMatrixT<ElementType>& a, const VectorT<ElementType>& v, bool atranspose)
{
    size_t arows, acols;
    if(atranspose) {
        arows=a.cols();
        acols=a.rows();
    } else {
        arows=a.rows();
        acols=a.cols();
    }

    if (size() == 0)
        resize(arows);
    if (arows != size() || acols != v.size())
        _THROW_EVector("Matrix multiplication: inconsistent sizes.");

    #ifdef NICE_USELIB_IPP
        size_t tsize=sizeof(ElementType);
        IppStatus ret;
        if(atranspose) {
                ret = ippmMul_tv(a.getDataPointer(), a.cols()*tsize, tsize, a.cols(), a.rows(),
                                v.getDataPointer(), tsize, v.size(),
                                this->getDataPointer(), tsize);
        } else {
                ret = ippmMul_mv(a.getDataPointer(), a.cols()*tsize, tsize, a.cols(), a.rows(),
                                v.getDataPointer(), tsize, v.size(),
                                this->getDataPointer(), tsize);
        }

        if(ret!=ippStsNoErr)
            _THROW_EVector(ippGetStatusString(ret));

    #else
    // FIXME not very efficient
    ElementType ela;
    for (unsigned int i = 0; i < arows; i++)
    {
        ElementType sum = ElementType(0);
        for (unsigned int k = 0; k < acols; k++)
        {
            ela = atranspose ? a(k, i) : a(i, k);
            sum += ela * v(k);
        }
        (*this)(i) = sum;
    }
    #endif
}

template<typename ElementType>
void VectorT<ElementType>::multiply(const VectorT<ElementType>& v, const MatrixT<ElementType>& a, bool atranspose)
{
    size_t arows, acols;
    if(atranspose) {
        arows=a.cols();
        acols=a.rows();
    } else {
        arows=a.rows();
        acols=a.cols();
    }

    if (size() == 0)
        resize(acols);
    if (acols != size() || arows != v.size())
        _THROW_EVector("Matrix multiplication: inconsistent sizes.");

    #ifdef NICE_USELIB_IPP
        size_t tsize=sizeof(ElementType);
        IppStatus ret;
        if(atranspose) {
                ret = ippmMul_tv(a.getDataPointer(), a.rows()*tsize, tsize, a.rows(), a.cols(),
                                v.getDataPointer(), tsize, v.size(),
                                this->getDataPointer(), tsize);
        } else {
                ret = ippmMul_mv(a.getDataPointer(), a.rows()*tsize, tsize, a.rows(), a.cols(),
                                v.getDataPointer(), tsize, v.size(),
                                this->getDataPointer(), tsize);
        }

        if(ret!=ippStsNoErr)
            _THROW_EVector(ippGetStatusString(ret));
    #else
        // FIXME not very efficient
        ElementType ela;
        for (unsigned int i = 0; i < acols; i++)
        {
            ElementType sum = ElementType(0);
            for (unsigned int k = 0; k < arows; k++)
            {
                ela = atranspose ? a(i, k) : a(k, i);
                sum += v(k) * ela;
            }
            (*this)(i) = sum;
        }
    #endif
}

template<class ElementType>
inline ElementType
VectorT<ElementType>::scalarProduct(
                           const VectorT<ElementType>& v) const {
  if (size() != v.size()) {
    throw std::invalid_argument("VectorT::scalarProduct(): v.size() != size()");
  } else if (size() == 0) {
    throw std::invalid_argument("VectorT::scalarProduct(): size() == 0");
  }

  ElementType result;
  IppStatus ret = ippsDotProd(getDataPointer(),v.getDataPointer(),dataSize,&result);
  if(ret!=ippStsNoErr)
       _THROW_EVector(ippGetStatusString(ret));
  return result;
}

template<class ElementType>
inline ElementType VectorT<ElementType>::Median() const {
   VectorT<ElementType> sorted(*this);
   sorted.sortAscend();
   return sorted[dataSize/2];
}

#define _DEFINE_EVECTOR_CONSTVOIDELEMENTFUNC(_IppName,_Name)           \
template<class ElementType>                                            \
inline ElementType                                                     \
VectorT<ElementType>::_Name() const {                                  \
  ElementType result=0;                                                \
  IppStatus ret = ipps##_IppName(getDataPointer(), dataSize, &result);    \
  if(ret!=ippStsNoErr)                                                 \
       _THROW_EVector(ippGetStatusString(ret));                        \
  return result;                                                       \
}


#ifndef DISABLE_IPP_MAXMIN
// in the current version of valgrind, valgrind
// does not recognize some cpu operations used
// in the IPP routines of ippMax and ippMin
_DEFINE_EVECTOR_CONSTVOIDELEMENTFUNC(Max,Max)
_DEFINE_EVECTOR_CONSTVOIDELEMENTFUNC(Min,Min)
#else

template<class ElementType>
inline ElementType
VectorT<ElementType>::Max() const 
{
	ElementType maximum = - std::numeric_limits<ElementType>::max();
	for ( uint i = 0 ; i < size() ; i++ )
		if ( (*this)(i) > maximum ) 
			maximum = (*this)(i);
	return maximum;
}

template<class ElementType>
inline ElementType
VectorT<ElementType>::Min() const 
{
	ElementType minimum = std::numeric_limits<ElementType>::max();
	for ( uint i = 0 ; i < size() ; i++ )
		if ( (*this)(i) < minimum ) 
			minimum = (*this)(i);
	return minimum;
}

#endif

_DEFINE_EVECTOR_CONSTVOIDELEMENTFUNC(Sum,Sum)
_DEFINE_EVECTOR_CONSTVOIDELEMENTFUNC(Mean,Mean)
_DEFINE_EVECTOR_CONSTVOIDELEMENTFUNC(StdDev,StdDev)
#ifdef NICE_USELIB_IPP
_DEFINE_EVECTOR_CONSTVOIDELEMENTFUNC(Norm_Inf,normInf)
#else
// The previous standard implementation didn't work for negative values!
template<class ElementType>
inline ElementType
VectorT<ElementType>::normInf() const 
{
  ElementType zero ( 0 );
  ElementType minusOne ( -1 );

  ElementType infNorm = zero;
  for ( uint i = 0 ; i < size() ; i++ ) 
  {
    if ( (*this)(i) < zero ) //negative entry
    {
      if ( ((*this)(i) * minusOne) > infNorm)
        infNorm = ((*this)(i) * minusOne);
    }
    else //positive entry
    {
      if ( (*this)(i) > infNorm)
        infNorm = (*this)(i) ;
    }
  }
  return infNorm;
}
#endif
_DEFINE_EVECTOR_CONSTVOIDELEMENTFUNC(Norm_L1,normL1)
_DEFINE_EVECTOR_CONSTVOIDELEMENTFUNC(Norm_L2,normL2)

#define _DEFINE_EVECTOR_VOIDIPFUNC(_IppName,_Name)           \
template<class ElementType>                                            \
inline void VectorT<ElementType>::_Name() {                                  \
  IppStatus ret = ipps##_IppName(getDataPointer(), dataSize);    \
  if(ret!=ippStsNoErr)                                                 \
       _THROW_EVector(ippGetStatusString(ret));                        \
}

_DEFINE_EVECTOR_VOIDIPFUNC(Abs_I,absInplace)

#define _DEFINE_EVECTOR_VOIDEVECTORFUNC(_IppName,_Name)           \
template<class ElementType>                                            \
inline VectorT<ElementType> VectorT<ElementType>::_Name() const {                                  \
  VectorT<ElementType> result(dataSize);                                                \
  IppStatus ret = ipps##_IppName(getDataPointer(),result.getDataPointer(), dataSize);    \
  if(ret!=ippStsNoErr)                                                 \
       _THROW_EVector(ippGetStatusString(ret));                        \
  return result;                                                       \
}

_DEFINE_EVECTOR_VOIDEVECTORFUNC(Abs,abs)

template<class ElementType>
inline int
VectorT<ElementType>::MaxIndex() const {
  int result;
  ElementType elem;
  IppStatus ret = ippsMaxIndx(getDataPointer(), dataSize, &elem, &result);
  if(ret!=ippStsNoErr)
       _THROW_EVector(ippGetStatusString(ret));
  return result;
}

template<class ElementType>
inline int
VectorT<ElementType>::MinIndex() const {
  int result;
  ElementType elem;
  IppStatus ret = ippsMinIndx(getDataPointer(), dataSize, &elem, &result);
  if(ret!=ippStsNoErr)
       _THROW_EVector(ippGetStatusString(ret));
  return result;
}

template<class ElementType>
inline VectorT<ElementType> VectorT<ElementType>::UniformRandom(const size_t size, ElementType min,
                                                                ElementType max, unsigned int seed)
    {
		VectorT result(size);
        IppStatus ret = ippsRandUniform_Direct(result.getDataPointer(),size,min,max,&seed);
		if(ret!=ippStsNoErr)
		   _THROW_EVector(ippGetStatusString(ret));
		return result;
    }

template<class ElementType>
inline VectorT<ElementType> VectorT<ElementType>::UniformRandom(const size_t size, ElementType min,
                                                                ElementType max)
    {
		VectorT result(size);
		for (uint i = 0 ; i < size ; i++ )
			result[i] = (ElementType) ( randDouble((double)(max-min)) + (double)min );
		return result;
    }

template<class ElementType>
inline VectorT<ElementType> VectorT<ElementType>::GaussRandom(const size_t size, ElementType mean,
                                                              ElementType stdev, unsigned int seed)
{
    VectorT result(size);
#ifdef NICE_USELIB_IPP
    IppStatus ret = ippsRandGauss_Direct(result.getDataPointer(),size,mean,stdev,&seed);

    if(ret!=ippStsNoErr)
        _THROW_EVector(ippGetStatusString(ret));

#else
	initRand ( true, seed );
	for ( int i = 0 ; i < size ; i++ )
		result[i] = randGaussDouble ( stdev ) + mean;
#endif
    return result;
}

template<class ElementType>
inline VectorT<ElementType> VectorT<ElementType>::GaussRandom(const size_t size, ElementType mean,
                                                              ElementType stdev)
{
    VectorT result(size);
	for ( uint i = 0 ; i < size ; i++ )
		result[i] = randGaussDouble ( stdev ) + mean;
    return result;
}

template<typename ElementType>
inline VectorT<ElementType>&
VectorT<ElementType>::operator=(const VectorT<ElementType>& v) {
  if (dataSize == 0 && !externalStorage && getDataPointer() == NULL) {
    setDataPointer(new ElementType[v.size()], v.size(), false);
  } else if (this->dataSize != v.size()) {
    this->resize(v.size());
  }
  ippsCopy(v.getDataPointer(), getDataPointer(), v.dataSize);
  return *this;
}

template<typename ElementType>
inline VectorT<ElementType>&
VectorT<ElementType>::operator=(const ElementType& element) {
  ippsSet(element, getDataPointer(), this->dataSize);
  return *this;
}

template<typename ElementType>
void VectorT<ElementType>::flip() {
  ippsFlip_I(getDataPointer(), this->dataSize);
}

template<typename ElementType>
void VectorT<ElementType>::sortAscend() {
  ippsSortAscend_I(getDataPointer(), this->dataSize);
}
template<typename ElementType>
void VectorT<ElementType>::sortDescend() {
  ippsSortDescend_I(getDataPointer(), this->dataSize);
}

/**
 * @brief sort elements in an descending order.
 */
template<typename ElementType>
void VectorT<ElementType>::sortDescend(VectorT<int> & permutation) {
//	VectorT<ElementType> tmp_cp(*this);
	ippsSortDescend_I(getDataPointer(), this->dataSize);
//	permutation.resize(this->size());
//	for (int i = 0; i < this->size(); i++)
//	{
//		ElementTyp entry((*this)[i]);
//		for (int i = 0; i < this->size(); i++)
//		{
//			
//		}
//	}
}

template<typename ElementType>
MatrixT<ElementType> VectorT<ElementType>::toCrossProductMatrix() const {
  MatrixT<ElementType> result(size(), size());
  result(0, 0) = 0.0;
  result(0, 1) = -(*this)[2];
  result(0, 2) = (*this)[1];
  result(1, 0) = (*this)[2];
  result(1, 1) = 0.0;
  result(1, 2) = -(*this)[0];
  result(2, 0) = -(*this)[1];
  result(2, 1) = (*this)[0];
  result(2, 2) = 0.0;
  return result;
}


#define _DEFINE_EVECTOR_AUGMENTED_ASSIGNMENT(_Op, _Name)               \
template<class ElementType>                                            \
inline VectorT<ElementType> &                                          \
VectorT<ElementType>::operator _Op##= (const ElementType& v) {         \
  ipps##_Name##C_I(v, getDataPointer(), this->dataSize);               \
  return *this;                                                        \
}

_DEFINE_EVECTOR_AUGMENTED_ASSIGNMENT(+, Add)
_DEFINE_EVECTOR_AUGMENTED_ASSIGNMENT(-, Sub)
_DEFINE_EVECTOR_AUGMENTED_ASSIGNMENT(*, Mul)
_DEFINE_EVECTOR_AUGMENTED_ASSIGNMENT(/, Div)

#define _DEFINE_EVECTOR_ASSIGNMENT(_Op, _Name)                             \
template<class ElementType>                                                \
inline VectorT<ElementType> &                                              \
VectorT<ElementType>::operator _Op##= (const VectorT<ElementType>& v) {    \
  if(this->dataSize!=v.size())                                             \
	   _THROW_EVector("VectorT: different data size");                 \
  ipps##_Name##_I(v.getDataPointer(), getDataPointer(), this->dataSize);   \
  return *this;                                                            \
}

_DEFINE_EVECTOR_ASSIGNMENT(+, Add)
_DEFINE_EVECTOR_ASSIGNMENT(-, Sub)
_DEFINE_EVECTOR_ASSIGNMENT(*, Mul)
_DEFINE_EVECTOR_ASSIGNMENT(/, Div)





// shift operations

template<typename ElementType>
VectorT<ElementType> VectorT<ElementType>::LShiftCircular(const uint b) {
    VectorT<ElementType> result(size());

    Ipp32u bShift = b%size();

    #ifdef NICE_USELIB_IPP

        ippsCopy(getDataPointer()+bShift, result.getDataPointer()              , size()-bShift);
        ippsCopy(getDataPointer()       , result.getDataPointer()+size()-bShift, bShift       );

    #else // NICE_USELIB_IPP

        memcpy(result.getDataPointer(), getDataPointer()+bShift, (size()-bShift)*sizeof(ElementType));
        memcpy(result.getDataPointer()+size()-bShift, getDataPointer(), bShift*sizeof(ElementType));

    #endif

    return result;
}

template<typename ElementType>
void VectorT<ElementType>::LShiftCircularInplace(const uint b) {

    VectorT<ElementType> buffer = this->LShiftCircular(b);
    *this = buffer;
}

template<typename ElementType>
VectorT<ElementType> VectorT<ElementType>::RShiftCircular(const uint b) {

    VectorT<ElementType> result(size());

    Ipp32u bShift = b%size();

    #ifdef NICE_USELIB_IPP

        ippsCopy(getDataPointer(), result.getDataPointer()+bShift, size()-bShift);
        ippsCopy(getDataPointer()+size()-bShift, result.getDataPointer(), bShift);

    #else // NICE_USELIB_IPP

        memcpy(result.getDataPointer()+bShift, getDataPointer(), (size()-bShift)*sizeof(ElementType));
        memcpy(result.getDataPointer(), getDataPointer()+size()-bShift, bShift*sizeof(ElementType));

    #endif

    return result;
}

template<typename ElementType>
void VectorT<ElementType>::RShiftCircularInplace(const uint b) {

    VectorT<ElementType> buffer = this->RShiftCircular(b);
    *this = buffer;
}

template<typename ElementType>
inline bool VectorT<ElementType>::isEqual(const VectorT<ElementType> &v, ElementType threshold) const
{
  if( this->size() != v.size() )
     _THROW_EVector("VectorT: different data size");
  for (unsigned int j = 0; j < size(); j++) {
       if(fabs((*this)[j]-v[j])>threshold)
           return false;
  }
  return true;
}

template<typename ElementType>
unsigned long VectorT<ElementType>::getHashValue() const
{
  const char *buf = (const char*)getDataPointer();
  uint len = size() * sizeof(ElementType);

  // might overflow...but we do not care about it
  // According to http://www.ntecs.de/projects/guugelhupf/doc/html/x435.html
  // this is what STL is using
  unsigned long hash = 0;
  for ( int i = 0 ; i < len ; i++ )
    hash = 5*hash + buf[i];

  return hash;
}


template<typename ElementType>
std::vector<ElementType> VectorT<ElementType>::std_vector () const
{
	std::vector<ElementType> dst ( this->size() );
	for ( unsigned int i = 0 ; i < size(); i++ )
		dst[i] = (*this)[i];
	return dst;
}


} // namespace NICE

#endif
