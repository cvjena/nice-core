/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libbasicvector - A simple vector library
 * See file License for license information.
 */
#ifndef BASICVECTOR_SVD_H
#define BASICVECTOR_SVD_H

#include "core/vector/VectorT.h"
#include "core/vector/MatrixT.h"
#include "core/vector/RowMatrixT.h"

#ifdef NICE_USELIB_LINAL
#include <LinAl/algorithms.h>
#endif

namespace NICE {

#ifdef NICE_USELIB_LINAL
template<class T>
class SVD {
public:
  /**
   * Constructor
   * @param matrix Input matrix
   */
  inline SVD(const MatrixT<T>& matrix) {
    LinAl::MatrixCF<double> _u;
    LinAl::MatrixCF<double> _vt;
    LinAl::VectorCC<double> _s;
    LinAl::svdfull(matrix.linal(), _u, _s, _vt);
    u = _u;
    vt = _vt;
    s = _s;
  }

  /**
   * Get the first factor U.
   * @return
   */
  inline MatrixT<T> getU() {
    return u;
  }

  /**
   * Get the third factor V.
   * @return
   */
  inline MatrixT<T> getV() {
    return vt.transpose();
  }

  /**
   * Get the transposed third factor V^T.
   * @return
   */
  inline MatrixT<T> getVt() {
    return vt;
  }

  /**
   * Get the singular values as a vector.
   * @return
   */
  inline VectorT<T> getSingularValues() {
    return s;
  }

  /**
   * Get the singular values as a diagonal matrix.
   * @return
   */
  inline MatrixT<T> getS() {
    MatrixT<T> result(s.size(), s.size());
    result = 0.0;
    for (uint i = 0; i < s.size(); ++i) {
      result(i,i) = s[i];
    }
    return result;
  }

// double  norm2 ()
// double  cond ()
// int   rank ()
private:
  MatrixT<T> u;
  VectorT<T> s;
  MatrixT<T> vt;
};

/** enforce predefined singular values of a square matrix */
template<class T>
inline void enforceSingularValues(MatrixT<T>& m, const VectorT<T>& sNew) {
  SVD<T> svd(m);
  MatrixT<T> u = svd.getU();
  MatrixT<T> s = svd.getS();
  MatrixT<T> vt = svd.getVt();
  for (unsigned int i = 0; i < sNew.size(); i++) {
    s(i, i) = sNew[i];
  }
  MatrixT<T> us;
  us.multiply(u, s);
  m.multiply(us, vt);
}

template<class T>
inline void enforceRankDefect(MatrixT<T>& m, const uint defect) {
  SVD<T> svd(m);
  MatrixT<T> u = svd.getU();
  MatrixT<T> s = svd.getS();
  MatrixT<T> vt = svd.getVt();
  for (unsigned int i = 0; i < s.rows(); i++) {
    s(i, i) = ((int)i < (int)s.rows() - (int)defect ? s(i,i) : 0.0);
  }
  MatrixT<T> us;
  us.multiply(u, s);
  m.multiply(us, vt);
}

#else // no LinAl
#ifndef SVDLINAL_WARNING
#warning SVD requires LinAl.
#define SVDLINAL_WARNING
#endif
#endif

} // namespace

#endif

