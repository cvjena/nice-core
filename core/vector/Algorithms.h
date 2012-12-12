#ifndef ALGORITHMS_H
#define ALGORITHMS_H
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
   * @brief Calculate mean of VectorT \c v
   * @param v vector
   * @return mean of vector
   */
template<class T>
inline T mean(const VectorT<T> &v);

  /**
   * @brief Calculate determinate of MatrixT \c A
   * @param A matrix
   * @return determinate of matrix A
   */
template<class T>
inline T det(const MatrixT<T> &A);

/** 
 * @brief Compute cholesky decomposition of MatrixT \c A (A = G*G^T), with
 * G being an lower triangle matrix.
 * If the flag \c resetUpperTriangle is set to false, only the lower triangle of G is set, 
 * without setting the upper triangle to zero !
 * @param A matrix
 * @param G square root of A
 */
template<class T>
void choleskyDecomp ( const MatrixT<T> & A, MatrixT<T> & G, bool resetUpperTriangle = true );

/** 
 * @brief Compute the inverse matrix of a matrix given by its square root \c G (lower triangle)
 * @param G square root of A
 * @param Ainv matrix
 */
template<class T>
void choleskyInvert ( const MatrixT<T> & G, MatrixT<T> & Ainv );

/** 
 * @brief Compute cholesky decomposition of MatrixT \c A (A = G*G^T), with
 * G being an lower triangle matrix.
 * If the flag \c resetUpperTriangle is set to false, only the lower triangle of G is set, 
 * without setting the upper triangle to zero !
 * This method uses Lapack (LinAl) if available and should be used for large matrices (e.g. dim=1000).
 * @param A matrix
 * @param G square root of A
 */
void choleskyDecompLargeScale ( const Matrix & A, Matrix & G, bool resetUpperTriangle = true );

/** 
 * @brief Compute the inverse matrix of a matrix given by its square root \c G (lower triangle)
 * This method uses Lapack (LinAl) if available and should be used for large matrices (e.g. dim=1000).
 * @param G square root of A
 * @param Ainv matrix
 */
void choleskyInvertLargeScale ( const Matrix & G, Matrix & Ainv );

/** 
 * @brief Solves a linear equation system using the cholesky decomposition
 * of the coefficient matrix.
 * @param G square root of A (lower triangle)
 * @param b right hand side of the equation system
 * @param x solution of A x = b
 */
template<class T>
void choleskySolve ( const MatrixT<T> & G, const VectorT<T> & b, VectorT<T> & x );

/** 
 * @brief Solves a linear equation system using the cholesky decomposition
 * of the coefficient matrix.
 * This method uses Lapack (LinAl) if available and should be used for large matrices (e.g. dim=1000).
 * @param G square root of A (lower triangle)
 * @param b right hand side of the equation system
 * @param x solution of A x = b
 */
void choleskySolveLargeScale ( const Matrix & G, const Vector & b, Vector & x );

/** 
 * @brief Solves multiple linear equation systems using the cholesky decomposition
 * of the coefficient matrix.
 * This method uses Lapack (LinAl) if available and should be used for large matrices (e.g. dim=1000).
 * @param G square root of A (lower triangle)
 * @param B right hand side of the equation system AND solution of the system
 */
void choleskySolveMatrixLargeScale ( const Matrix & G, Matrix & B );

/** 
 * @brief Solves multiple linear equation systems with a triangular coefficient matrix
 * @param G coefficient matrix (lower triangular!!)
 * @param B right hand side of the equation system AND solution of the system
 * @param transposedMatrix if set to true the system G^T B = X is solved instead of G B = X
 */
void triangleSolveMatrix ( const Matrix & G, Matrix & B, bool transposedMatrix = false );

/** 
 * @brief Solves a linear equation system with a triangular coefficient matrix
 * @param G coefficient matrix (lower triangular!!)
 * @param b right hand side of the equation system 
 * @param x solution of the system
 * @param transposedMatrix if set to true the system G^T B = X is solved instead of G B = X
 */
void triangleSolve ( const Matrix & G, const Vector & x, Vector & b, bool transposedMatrix = false );

/** 
 * @brief Compute the determinant of a triangular matrix
 * @param G matrix
 * @param ignoreZero ignore all zero elements on the diagonal
 */
template<class T>
double triangleMatrixDet ( const MatrixT<T> & G, bool ignoreZero = false );

/** 
 * @brief Compute the logarithm of the determinant of a triangular matrix.
 * Computing the logarithm is often numerically more robust.
 * @param G matrix
 * @param ignoreZero ignore all zero elements on the diagonal
 */
template<class T>
double triangleMatrixLogDet ( const MatrixT<T> & G, bool ignoreZero = false );

  /**
   * @brief Calculate determinate of MatrixT \c A
   * @param A matrix
   * @return determinate of matrix A
   */
template<class T>
inline T det(const RowMatrixT<T> &A);

  /**
   * @brief Calculate natural logarithm of VectorT \c v in place.
   * @param v source and destination of vector
   */
template<class T>
inline void lnIP(VectorT<T> &v);

  /**
   * @brief Calculate natural logarithm of VectorT \c v.
   * @param v source vector
   * @param buffer pointer to destination vector
   * @return pointer to VectorT with logarithmic values.
   */
template<class T>
inline VectorT<T> *ln(const VectorT<T> &v, VectorT<T> *buffer=NULL);

  /**
   * @brief Create a 1D Gauss function
   * @param sigma  if sigma>0 determine Gauss function with standard derivation \c sigma
   * @param buffer pointer to destination vector (size of detination vector is automatically calculated if buffer pointer is NULL or size of buffer pointer is 0)
   * @return pointer to VectorT with Gauss function
   */
template<class T>
inline VectorT<T> *createGaussFunc(float sigma, VectorT<T> *buffer=NULL);

  /**
   * @brief solve linear equation given by the matrix A and the right-vector b: A*x = b.
   * @param A matrix
   * @param b vector
   * @param x solution vector
   */
template<class T>
inline void solveLinearEquationQR(const MatrixT<T> &A, const VectorT<T> &b, VectorT<T> &x);

  /**
   * @brief solve linear equation given by the matrix A and the right-vector b: A*x = b.
   * @param A matrix
   * @param b vector
   * @param x solution vector
   */
template<class T>
inline void solveLinearEquationQR(const RowMatrixT<T> &A, const VectorT<T> &b, VectorT<T> &x);

  /**
   * @brief solve Minimum Description Length based on greedy algorithm
   * @param C quadratic matrix
   * @param h solution vector
   */
template<class T>
inline void solveMDLgreedy(const MatrixT<T> &C, VectorT<T> &h);

/**
 * Invert a square matrix.
 */
template<class T>
MatrixT<T> invert(const MatrixT<T>& w);

/**
 * Invert a 3x3 upper triangle matrix (inplace).
 * @note There is no check if the matrix is invertable.
 */
template<class T>
void invert3x3UpperTriangle(MatrixT<T>& w);

/**
 * Invert a 3x3 lower triangle matrix (inplace).
 * @note There is no check if the matrix is invertable.
 */
template<class T>
void invert3x3LowerTriangle(MatrixT<T>& w);

/**
 * Compute the angle (in radian, -M_PI to M_PI) between two vectors.
 * If one of the vectors is zero, the result will be M_PI/2.0.
 */
inline double angleBetweenVectors(
                  const Vector& v1, const Vector& v2) {
  const double denominator = v1.normL2() * v2.normL2();
  // if one of the vectors is zero, they are orthogonal -> return PI/2
  if (isZero(denominator, 1e-16)) {
    return M_PI / 2.0;
  }
  const double arg = v1.scalarProduct(v2) / denominator;
  // allow for values slightly larger than 1.0 or slightly smaller than -1.0
  if (arg >= 1.0 && arg < 1.0 + 1e-10) {
    return 0.0;
  } else if (arg <= -1.0 && arg > -1.0 - 1e-10) {
    return -M_PI;
  } else {
    return acos(arg);
  }
}

/**
 * Compute the angle (in radian, -M_PI/2 to M_PI/2) between
 * two vectors ignoring the direction.
 */
inline double angleBetweenVectorsIgnoringDirection(
                  const Vector& v1, const Vector& v2) {
  double a = fabs(v1.scalarProduct(v2) / (v1.normL2() * v2.normL2()));
  if (a > 1.0)
    a = 1.0;
  return acos(a);
}

/**
 * Compute the absolute angle (in radian, 0 to M_PI/2) between
 * two vectors ignoring the direction.
 */
inline double absoluteAngleBetweenVectorsIgnoringDirection(
                  const Vector& v1, const Vector& v2) {
  return fabs(angleBetweenVectorsIgnoringDirection(v1, v2));
}

} // namespace

#ifdef __GNUC__
  #include <core/vector/Algorithms.tcc>
#endif

#endif // ALGORITHMS_H
