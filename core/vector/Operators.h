#ifndef OPERATORS_H
#define OPERATORS_H

#include <core/vector/MatrixT.h>
#include <core/vector/VectorT.h>

template <class T> 
inline MatrixT<T> operator*(const MatrixT<T>& A, const MatrixT<T>& B) {
    MatrixT<T> result(A.rows(),B.cols());
    result.multiply(A,B);
    return result;
}

template <class T> 
inline VectorT<T> operator*(const MatrixT<T>& A, const VectorT<T>& v) {
    VectorT<T> result(A.rows(),v.size());
    result.multiply(A,v);
    return result;
}

template <class T> 
inline VectorT<T> operator*(const VectorT<T>& v, const MatrixT<T>& B) {
    VectorT<T> result(v.size(),B.cols());
    result.multiply(v,B);
    return result;
}

#endif // OPERATORS_H
