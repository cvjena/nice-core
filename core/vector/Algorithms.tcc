/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libbasicvector - A simple vector library
 * See file License for license information.
 */
#include "core/vector/Algorithms.h"

#include <core/basics/Log.h>
#include <core/vector/SVD.h>

#ifdef NICE_USELIB_LINAL
#include <LinAl/algorithms.h>
#endif


namespace NICE {

template<class T>
inline T mean(const VectorT<T> &v) {
//#ifdef NICE_USELIB_IPP
  T m;
  IppStatus ret = ippsMean(v.getDataPointer(),v.size(),&m,ippAlgHintFast);
  if(ret!=ippStsNoErr)
    _THROW_EVector(ippGetStatusString(ret));
  return m;
//#else
//  _THROW_EVector("Not yet implementent without IPP.");
//#endif // NICE_USELIB_IPP
}

template<class T>
inline T det(const MatrixT<T> &A) {
#ifdef NICE_USELIB_IPP
  size_t msize=A.cols();
  if(msize!=A.rows())
    _THROW_EMatrix("det(MatrixT<T>): matrix is not symmetric");
  size_t tsize=sizeof(T);
  T buffer[msize*msize+msize];
  T result;
  IppStatus ret = ippmDet_m(A.getDataPointer(),msize*tsize,tsize,msize,buffer,&result);
  // ippStsSingularErr not defined
  if(ret==ippStsSingularErr)
    return static_cast<T>(0);
  if(ret!=ippStsNoErr)
    _THROW_EMatrix(ippGetStatusString(ret));
  return result;
#else
#ifdef NICE_USELIB_LINAL
  return LinAl::det(A.linal());
#else
  _THROW_EVector("Not yet implementent without IPP.");
#endif
#endif // NICE_USELIB_IPP
}

template<class T>
inline T det(const RowMatrixT<T> &A) {
#ifdef NICE_USELIB_IPP
  size_t msize=A.cols();
  if(msize!=A.rows())
    _THROW_EMatrix("det(MatrixT<T>): matrix is not symmetric");
  size_t tsize=sizeof(T);
  T buffer[msize*msize+msize];
  T result;
  IppStatus ret = ippmDet_m(A.getDataPointer(),msize*tsize,tsize,msize,buffer,&result);
  // ippStsSingularErr not defined
  if(ret==ippStsSingularErr)
    return static_cast<T>(0);
  if(ret!=ippStsNoErr)
    _THROW_EMatrix(ippGetStatusString(ret));
  return result;
#else
#ifdef NICE_USELIB_LINAL
  return LinAl::det(A.linal());
#else
  _THROW_EVector("Not yet implementent without IPP.");
#endif
#endif // NICE_USELIB_IPP
}

template<class T>
void choleskyDecomp ( const MatrixT<T> & A, MatrixT<T> & G, bool resetUpperTriangle )
{
  if ( A.rows() != A.cols() )
	  fthrow(Exception, "Matrix is not quadratic !");

  const int size = A.rows();
  G.resize ( size, size );
  if ( resetUpperTriangle ) 
	  G.set(0.0);
  
  int i,j,k;
  double sum;

  for (i=0;i<size;i++) {
    bool divide=true;
    for (j=0;j<i;j++) G(j,i)=0.0;
    for (;j<size;j++) {
      sum=A(i,j);
      for (k=i-1;k>=0;k--) sum -= G(i,k)*G(j,k);
      if (i == j) {
        // The following applies if A, with rounding errors, is not positive definite
        if (isZero(sum, 1e-16)) {
          G(i,i)=0.0;
          divide=false;
        } else if (sum<0.0) {
          // A is (numerically) not positive definite.
          fthrow(Exception, "Cholesky decomposition failed (sum=" << sum << ")");
        }
        G(i,i)=sqrt(sum);
      } else {
        if (!divide) G(j,i)=0.0;
        else G(j,i)=sum/G(i,i);
      }
    }
  }
}

template<class T>
void choleskyInvert ( const MatrixT<T> & Gmatrix, MatrixT<T> & AinvMatrix )
{
	if ( Gmatrix.rows() != Gmatrix.cols() )
	  fthrow(Exception, "Matrix is not quadratic !");

	AinvMatrix.resize ( Gmatrix.rows(), Gmatrix.cols() );
	const T *G = Gmatrix.getDataPointer();
	T *Ainv = AinvMatrix.getDataPointer();

	int i,k,j;
	T sum;
	int size = Gmatrix.rows();
	for (j=0;j<size;j++) {
		for (i=0;i<size;i++) {
			sum = (i==j)?1.0:0.0;
			for (k=i-1;k>=0;k--) sum -= G[k*size+i]*Ainv[k+j*size];

			if (almostZero(G[i*size+i])) Ainv[i+j*size]=0.0;
			else Ainv[i+j*size]=sum/G[i*size+i];
		}
		for (i=size-1;i>=0;i--) {
			for (sum=Ainv[i+j*size],k=i+1;k<size;k++) sum -= G[i*size+k]*Ainv[k+j*size];
			if (almostZero(G[i*size+i])) Ainv[i+j*size]=0.0;
			else Ainv[i+j*size]=sum/G[i*size+i];
		}
	}

}

template<class T>
void choleskySolve ( const MatrixT<T> & Gmatrix, const VectorT<T> & b, VectorT<T> & x )
{
	if ( Gmatrix.rows() != Gmatrix.cols() )
	  fthrow(Exception, "Matrix is not quadratic !");

	if ( b.size() != Gmatrix.cols() )
		fthrow(Exception, "Matrix or right hand side of the linear system has wrong dimensions !");

	int size = Gmatrix.rows();
	const T* G = Gmatrix.getDataPointer();
	int i,k;
	double sum;

	x.resize(size);

	// Solve L y = b, storing y in x.
	for (i=0;i<size;i++) {
		for (sum=b[i],k=i-1;k>=0;k--) sum -= G[k*size+i]*x[k];
		x[i]=sum/G[i*size+i];
	}
	// Solve LT x = y
	for (i=size-1;i>=0;i--) {
		for (sum=x[i],k=i+1;k<size;k++) sum -= G[i*size+k]*x[k];
		x[i]=sum/G[i*size+i];
	}
}

template<class T>
double triangleMatrixDet ( const MatrixT<T> & Gmatrix, bool ignoreZero )
{
	if ( Gmatrix.rows() != Gmatrix.cols() )
	  fthrow(Exception, "Matrix is not quadratic !");

	int i;
	int size = Gmatrix.rows();
	const T* G = Gmatrix.getDataPointer();
	double ret = 1.0;
	for (i=0;i<size;i++) {
		if (almostZero(G[i*size+i])) {
			if (ignoreZero) continue;
			else return 0.0;
		}
		ret *= G[i*size+i];
	}
	return ret;
}

template<class T>
double triangleMatrixLogDet ( const MatrixT<T> & Gmatrix, bool ignoreZero )
{
	int i;
	int size = Gmatrix.rows();
	const T* G = Gmatrix.getDataPointer();

	double ret = 0.0;
	for (i=0;i<size;i++) {
		if (almostZero(G[i*size+i])) {
			if (ignoreZero) continue;
			else return - std::numeric_limits<double>::infinity();
		}
		ret += log(G[i*size+i]);
	}
	return ret;
}

template<class T>
inline void lnIP(VectorT<T> &v) {
#ifdef NICE_USELIB_IPP
  IppStatus ret = ippsLn_I(v.getDataPointer(),v.size());
  if(ret!=ippStsNoErr)
    _THROW_EVector(ippGetStatusString(ret));
#else
  _THROW_EVector("Not yet implementent without IPP.");
#endif // NICE_USELIB_IPP
}

template<class T>
inline VectorT<T> *ln(const VectorT<T> &v, VectorT<T> *buffer=NULL) {
#ifdef NICE_USELIB_IPP
  VectorT<T> *result;
  if(buffer==NULL || buffer->size()!=v.size()) {
    result=new VectorT<T>(v.size());
  } else {
    result=buffer;
  }

  IppStatus ret = ippsLn(v.getDataPointer(),result->getDataPointer(),v.size());
  if(ret!=ippStsNoErr)
   _THROW_EVector(ippGetStatusString(ret));
  return result;
#else
  _THROW_EVector("Not yet implementent without IPP.");
#endif // NICE_USELIB_IPP
}

template<class T>
inline VectorT<T> *createGaussFunc(float sigma, VectorT<T> *buffer=NULL)
{
#ifdef NICE_USELIB_IPP
    int resultlength;
    VectorT<T> *result;
    if(buffer==NULL || buffer->size()<3) {
        int length=static_cast<int>(2.0*sigma*sigma-0.5);
        if(length<1) length=0;
        float base[] = {0.25, 0.5, 0.25};
        resultlength=3+length*2;
        result= new VectorT<T>(resultlength);
        ippsCopy(base, result->getDataPointer(), 3);
        T tmp[resultlength];
        for(int i=0;i<length;i++) {
            ippsConv(base,3,result->getDataPointer(),3+i*2,tmp);
            ippsCopy(tmp, result->getDataPointer(), 3+(i+1)*2);
        }
    } else {
        resultlength=buffer->size();
        result=buffer;
        float ssq=sigma*sigma;
        if(sigma<=0) {
            ssq=(resultlength-1)/4;
        }
        float norm=sqrt(2.*M_PI*ssq);
        float l=-(resultlength-1)/2.0;
        for(int i=0;i<resultlength;l+=1.0,i++) {
            (*result)[i]=exp(-l*l/(2*ssq))/norm;
        }
    }
    return result;
#else
  _THROW_EVector("Not yet implementent without IPP.");
#endif // NICE_USELIB_IPP
}

template<class T>
inline void solveLinearEquationQR(const MatrixT<T> &A, const VectorT<T> &b, VectorT<T> &x)
{
#ifdef NICE_USELIB_IPP
	// FIXME: this method seems to be buggy :)
    size_t in_s = A.cols();
    if (in_s != b.size())
        _THROW_EMatrix("solveLinearEquationQR: size of input vector b does not fit");

    size_t out_s = A.rows();
    if (x.size() == 0) {
      x.resize(out_s);
    }
    if (out_s != x.size())
        _THROW_EMatrix("solveLinearEquationQR: size of output vector x does not fit");

    T QR[in_s*out_s];
    int stride = sizeof(T);
    int stride_src = out_s*sizeof(T);
    T Buffer[in_s];

    IppStatus status
        = ippmQRDecomp_m(A.getDataPointer(),stride_src, stride, Buffer,
                         QR, stride_src, stride, out_s, in_s);

    if (status != ippStsOk)
         _THROW_EVector(ippGetStatusString(status));

    status = ippmQRBackSubst_mv(QR, stride_src, stride, Buffer,
                                b.getDataPointer(), stride,
                                x.getDataPointer(), stride, out_s, in_s);

    if (status != ippStsOk)
         _THROW_EVector(ippGetStatusString(status));
#else
  _THROW_EVector("Not yet implementent without IPP.");
#endif // NICE_USELIB_IPP
}

template<class T>
inline void solveMDLgreedy(const MatrixT<T> &C, VectorT<T> &h)
{
#ifdef NICE_USELIB_IPP
    if (C.rows() != C.cols())
        _THROW_EMatrix("solveMDLgreedy: matrix C is not quadratic");

    size_t size = h.size();
    if (C.rows() != size)
        _THROW_EMatrix("solveMDLgreedy: size of output vector h does not fit");

    VectorT<T> temp(size);
    T maximum = 0.0;
    T current = 0.0;
    int position = -1;
    h *= 0;

    int Stride = sizeof(T);
    int srcStride = size * sizeof(T);

    do {
        position = -1;
        for (uint i = 0; i < size; i++) {
            if (not h(i)) {
                h(i) = 1;
                ippmMul_tv_32f(C.getDataPointer(), srcStride,
                               Stride, size, size,
                               h.getDataPointer(), Stride, size,
                               temp.getDataPointer(), Stride);
                temp *= h;
                current = temp.Sum();
                if (current > maximum) {
                    maximum = current;
                    position = i;
                }
                h(i) = 0;
            }
        }
        if (position > -1)
            h(position) = 1;
    } while (position > -1);
#else
  _THROW_EVector("Not yet implementent without IPP.");
#endif // NICE_USELIB_IPP
}

template<class T>
MatrixT<T> invert(const MatrixT<T>& w) {
#ifdef NICE_USELIB_IPP
  size_t size = w.cols();
  if (size != w.rows()) {
    _THROW_EMatrix("invert: matrix is not square.");
  }

  MatrixT<T> result(w.rows(), w.cols());
  T* buffer = new T[size * size + size];
  int stride1 = sizeof(T);
  int stride2 = size * sizeof(T);

  IppStatus status = ippmInvert_m(w.getDataPointer(), stride1, stride2,
                                  buffer, result.getDataPointer(),
                                  stride1, stride2, size);

  if (status != ippStsOk) {
    _THROW_EVector(ippGetStatusString(status));
  }

  return result;
#else
#ifdef NICE_USELIB_LINAL
  LinAl::MatrixCF<T> copy(w.linal());
  try {
    copy.LUinvert();
  } catch (std::exception& e) {
    fthrowc(Exception, "Invert failed", e);
  }
  MatrixT<T> result(copy);
  return result;
#else
  _THROW_EVector("Not yet implementent without IPP or LinAl.");
#endif
#endif // NICE_USELIB_IPP
}

template<class T>
void invert3x3UpperTriangle(MatrixT<T>& w) {
  w(0, 2) = (w(0, 1) * w(1, 2) - w(0, 2) * w(1, 1))
            / (w(0, 0) * w(1, 1) * w(2, 2));
  w(1, 2) = -w(1, 2) / (w(1, 1) * w(2, 2));
  w(2, 2) = 1.0 / w(2, 2);
  w(0, 1) = -w(0, 1) / (w(0, 0) * w(1, 1));
  w(1, 1) = 1.0 / w(1, 1);
  w(0, 0) = 1.0 / w(0, 0);
}

template<class T>
void invert3x3LowerTriangle(MatrixT<T>& w) {
  w(2, 0) = (w(1, 0) * w(2, 1) - w(2, 0) * w(1, 1))
            / (w(0, 0) * w(1, 1) * w(2, 2));
  w(2, 1) = -w(2, 1) / (w(1, 1) * w(2, 2));
  w(2, 2) = 1.0 / w(2, 2);
  w(1, 0) = -w(1, 0) / (w(0, 0) * w(1, 1));
  w(1, 1) = 1.0 / w(1, 1);
  w(0, 0) = 1.0 / w(0, 0);
}

}

