#ifndef EIGEN_H
#define EIGEN_H
/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libbasicvector - A simple vector library
 * See file License for license information.
 */
#include "core/vector/ippwrapper.h"
#include "core/vector/VectorT.h"
#include "core/vector/MatrixT.h"
#include "core/vector/RowMatrixT.h"
#include <cmath>

namespace NICE {

/**
 * Compute the eigenvector of the eigenvalue with largest absolute eigenvalue
 * of a <b>symmetric</b> matrix.
 * @param a symmetric matrix
 * @return resulting eigenvector
 * @note If the matrix is not symmetric, the result will just be nonsense.
 *       (No exception or other error notification).
 */
template<class T>
VectorT<T> maxEigenVector(const MatrixT<T>& a);


/**
 * Calculate eigenvalues of a <b>symmetric</b> matrix.
 * @param A symmetric matrix
 * @param evals eigenvalue buffer
 * @return eigenvalues
 */
template<class T>
VectorT<T> *eigenvalues(const MatrixT<T> &A, VectorT<T> *evals=NULL);

/**
 * Calculate eigenvalues of a <b>symmetric</b> matrix.
 * See \c eigenvalues(const MatrixT<T>&, VectorT<T>*)
 */
template<class T>
VectorT<T> *eigenvalues(const RowMatrixT<T> &A, VectorT<T> *evals=NULL);

/**
 * Calculate eigenvectors and eigenvalues of a <b>symmetric</b> matrix.
 * Eigenvectors are columns of the parameter evecs.
 * A = evecs * diag(evals) * evecs^T
 * @param A symmetric matrix
 * @param evecs eigenvector matrix
 * @param evals vector of eigenvalues (decreasing order)
 */
template<class T>
void eigenvectorvalues(const MatrixT<T> &A, MatrixT<T> &evecs, VectorT<T> &evals);

/**
 * Calculate eigenvectors and eigenvalues of a <b>symmetric</b> matrix.
 * See \c eigenvectorvalues(const MatrixT<T> &A, MatrixT<T> &evecs, VectorT<T> &evals).
 */
template<class T>
void eigenvectorvalues(const RowMatrixT<T> &A, RowMatrixT<T> &evecs,  VectorT<T> &evals);

/*
 * Calculate Eigenvectors of a <b>symmetric</b> matrix.
 * @param A symmetric matrix
 * @param v start vector
 * @return eigenvector
 */
/*
template<class T>
VectorT<T> *Arnoldi_MGS(const MatrixT<T> &A, size_t nr, VectorT<T> *v=NULL)

    int vsize=A.cols();
    if(v==NULL)
        v=new VectorT<T>(vsize,static_cast<T>(1));
    MatrixT<T> Q(vsize,nr);
    VectorT<T> q(Q,vsize,VectorBase::external);
    for(int k=0;k<nr;k++) {
        Q = v/v.normL2();
        v = A * q[k];
        for(int j=1;j<=k;j++) {
             v  -= q[j] * (q[j].transpose() * v);
        }
    }
    return v;
}
*/

}

//#ifdef __GNUC__
  #include <core/vector/Eigen.tcc>
//#endif

#endif // EIGEN_H
