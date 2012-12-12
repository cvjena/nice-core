/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libicelink - An icelink/template for new NICE libraries
 * See file License for license information.
 */
/*****************************************************************************/
/**
 * @file convertice.h
 * Conversion to/from ICE vectors (and maybe some day also matrices).
 * @note
 * This file requires the ICE library.
 * However, that library is NOT defined as a dependency in the
 * limun image library. If you use this file, you have to use ICE, too.
 * This shouldn't be a problem, as this file is only useful if you are using
 * ICE already.
 */
#ifndef _CONVERTICE_BASICVECTOR_H
#define _CONVERTICE_BASICVECTOR_H

#include <core/vector/VectorT.h>
// #include <core/vector/MatrixT.h>
// #include <core/vector/RowMatrixT.h>

// ICE
#include <image_nonvis.h>

namespace NICE {

/**
 * Convert a \c basicvector::VectorT<T> into an \c ice::VectorT<T>.
 * This also works for \c basicvector::VectorT<double> to \c ice::Vector.
 * @param v original vector
 * @result ICE vector
 */
template<class T> inline
ice::VectorT<T> makeIceVectorT(const NICE::VectorT<T>& v) {
  ice::VectorT<T> result(v.size());
  for (unsigned int i = 0; i < v.size(); i++) {
    result[i] = v[i];
  }
  return result;
}


/**
* Convert a \c basicvector::MatrixT<T> into an \c ice::Matrix (double values).
* @param m original matrix
* @result ICE Matrix
*/
template<class T> inline
ice::Matrix makeICEMatrix(const NICE::MatrixT<T>& m) {
  ice::Matrix result(m.rows(), m.cols());
  for(unsigned int j= 0; j < m.rows(); ++j)
    {
      for(unsigned int i= 0; i < m.cols(); ++i)
      {
        result[j][i]= (double)m(j,i);
      }
    }
  return result;
}

/**
* Convert a \c ice::IMatrix (integer values) into an \c basicvector::MatrixT<int>.
* @param m ICE Matrix
* @result Matrix
*/
template<class T> inline
NICE::MatrixT<int> makeIntegerMatrix ( const ice::IMatrix& m ){
  NICE::MatrixT<int> result(m.rows(),m.cols());
  for(int j= 0; j < m.rows(); ++j)
    {
      for(int i= 0; i < m.cols(); ++i)
      {
        result(j,i)= m[j][i];
      }
    }
  return result;
}


/**
* Convert a \c ice::Matrix (double values) into an \c basicvector::MatrixT<T>.
* @param m ICE Matrix
* @result Matrix
*/
inline NICE::MatrixT<double> makeDoubleMatrix(const ice::Matrix& m){
  NICE::MatrixT<double> result(m.rows(),m.cols());
  for(int j= 0; j < m.rows(); ++j)
    {
      for(int i= 0; i < m.cols(); ++i)
      {
        result(j,i)= m[j][i];
      }
    }
  return result;
}


/**
* Convert a \c ice::Matrix (double values) into an \c basicvector::MatrixT<T>.
* @param m ICE Matrix
* @result FloatMatrix
*/
inline NICE::MatrixT<float> makeFloatMatrix(const ice::Matrix& m){
  NICE::MatrixT<float> result(m.rows(),m.cols());
  for(int j= 0; j < m.rows(); ++j)
    {
      for(int i= 0; i < m.cols(); ++i)
      {
        result(j,i)= (float)m[j][i];
      }
    }
  return result;
}



/**
 * Convert a \c basicvector::VectorT<T> into an \c ice::VectorT<T>.
 * This also works for \c basicvector::VectorT<double> to \c ice::Vector.
 * @param v original vector
 * @result ICE vector as a new object (ownership given away!)
 */
template<class T> inline
ice::VectorT<T>* createIceVectorT(const NICE::VectorT<T>& v) {
  // auto_ptr for exception safety
  std::auto_ptr<ice::VectorT<T> > result(new ice::VectorT<T>(v.size()));
  for (unsigned int i = 0; i < v.size(); i++) {
    (*result)[i] = v[i];
  }
  return result.release();
}

/**
 * Convert an \c ice::VectorT<T> into a \c basicvector::VectorT<T>.
 * This also works for \c ice::Vector to \c basicvector::VectorT<double>.
 * @param v original vector
 * @result LImUn vector
 */
template<class T> inline
NICE::VectorT<T> makeEVector(const ice::VectorT<T>& v) {
  NICE::VectorT<T> result(v.Size());
  for (int i = 0; i < v.Size(); i++) {
    result[i] = v[i];
  }
  return result;
}

/**
 * Convert an \c ice::VectorT<T> into a \c basicvector::VectorT<T>.
 * This also works for \c ice::Vector to \c basicvector::VectorT<double>.
 * @param v original vector
 * @result LImUn vector as a new object (ownership given away!)
 */
template<class T> inline
NICE::VectorT<T>* createEVector(const ice::VectorT<T>& v) {
  // auto_ptr for exception safety
  std::auto_ptr<NICE::VectorT<T> >
    result(new NICE::VectorT<T>(v.Size()));
  for (int i = 0; i < v.Size(); i++) {
    (*result)[i] = v[i];
  }
  return result.release();
}

}; // namespace

#endif
