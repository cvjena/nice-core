/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libbasicvector - A simple vector library
 * See file License for license information.
 */
#include "core/vector/Eigen.h"

namespace NICE {

template<class T>
VectorT<T> maxEigenVector(const MatrixT<T>& a) {
  if (a.rows() != a.cols()) {
    fthrow(Exception, "Matrix must be a squarematrix.");
  }
  VectorT<T> v(a.rows());
  v.set(T(1));
  v.normalizeL2();
  while (true) {
    VectorT<T> w(v.size());
    w.multiply(a, v);
    w.normalizeL2();
    VectorT<T> diff(v);
    diff -= w;
    v = w;
    if (diff.normL2() < 10.0 * std::numeric_limits<T>::epsilon()) {
      break;
    }
  }
  return v;
}

template<class T>
VectorT<T> *eigenvalues(const MatrixT<T> &A, VectorT<T> *evals=NULL)
{
    size_t vsize=A.cols();
    if(A.rows()!=vsize)
        fthrow(Exception,"Matrix must be a squarematrix.");
    if(evals==NULL)
        evals=new VectorT<T>(vsize);
    if(evals->size()!=vsize)
        fthrow(Exception,"vectorsize != vsize.");
    T buffer[vsize*vsize];
    size_t tsize=sizeof(T);
    IppStatus ret = ippmEigenValuesSym_m(A.getDataPointer(), vsize*tsize, tsize, buffer, evals->getDataPointer(), vsize);
	/* ippStsSingularErr not defined
    	if(ret==ippStsSingularErr)
    	    return evals;
	*/
	if(ret!=ippStsNoErr)
	   _THROW_EVector(ippGetStatusString(ret));
    return evals;
}

template<class T>
void eigenvectorvalues(const MatrixT<T> &A, MatrixT<T> &evecs,  VectorT<T> &evals)
{
    size_t vsize=A.cols();
    if(A.rows()!=vsize)
        fthrow(Exception,"Matrix must be a squarematrix.");
    if(evecs.rows() != vsize && evecs.cols() != vsize)
        evecs.resize(vsize,vsize);
    if(evals.size()!=vsize)
        evals.resize(vsize);
    T buffer[vsize*vsize];
    size_t tsize=sizeof(T);
    IppStatus ret = ippmEigenValuesVectorsSym_m(A.getDataPointer(), vsize*tsize, tsize, buffer,
                                                evecs.getDataPointer(), vsize*tsize, tsize, evals.getDataPointer(), vsize);
    evecs.transposeInplace();
	if(ret!=ippStsNoErr)
	   _THROW_EVector(ippGetStatusString(ret));
}

template<class T>
VectorT<T> *eigenvalues(const RowMatrixT<T> &A, VectorT<T> *evals=NULL)
{
    size_t vsize=A.cols();
    if(A.rows()!=vsize)
        fthrow(Exception,"Matrix must be a squarematrix.");
    if(evals==NULL)
        evals=new VectorT<T>(vsize);
    if(evals->size()!=vsize)
        fthrow(Exception,"vectorsize != vsize.");
    T buffer[vsize*vsize];
    size_t tsize=sizeof(T);
    IppStatus ret = ippmEigenValuesSym_m(A.getDataPointer(), vsize*tsize, tsize, buffer, evals->getDataPointer(), vsize);
	/* ippStsSingularErr not defined
    	if(ret==ippStsSingularErr)
    	    return evals;
	*/
	if(ret!=ippStsNoErr)
	   _THROW_EVector(ippGetStatusString(ret));
    return evals;
}

template<class T>
void eigenvectorvalues(const RowMatrixT<T> &A, RowMatrixT<T> &evecs,  VectorT<T> &evals)
{
    size_t vsize=A.cols();
    if(A.rows()!=vsize)
        fthrow(Exception,"Matrix must be a squarematrix.");
    if(evecs.rows() != vsize && evecs.cols() != vsize)
        evecs.resize(vsize,vsize);
    if(evals.size()!=vsize)
        evals.resize(vsize);
    T buffer[vsize*vsize];
    size_t tsize=sizeof(T);
    IppStatus ret = ippmEigenValuesVectorsSym_m(A.getDataPointer(), vsize*tsize, tsize, buffer,
                                                evecs.getDataPointer(), vsize*tsize, tsize, evals.getDataPointer(), vsize);
	if(ret!=ippStsNoErr)
	   _THROW_EVector(ippGetStatusString(ret));
}

}
