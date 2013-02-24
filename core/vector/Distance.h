
/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libbasicvector - A simple vector library
 * See file License for license information.
 */

#ifndef __VECTOR_DISTANCE_H__
#define __VECTOR_DISTANCE_H__

 
#include "core/vector/ippwrapper.h"
#include "core/vector/VectorT.h"

namespace NICE {

/**
 * @struct VectorDistance
 * @brief  baseclass for vector distances
 */
template<class T>
class VectorDistance {

public:
    virtual ~VectorDistance(){};

    inline T calculate(const VectorT<T>& v1 , const VectorT<T>& v2) const;
    inline T operator()(const VectorT<T>& v1 , const VectorT<T>& v2) const;

protected:

    virtual T doCalculate(const VectorT<T>& v1 , const VectorT<T>& v2) const = 0;
};

/**
 * @struct ManhattanDistance 
 * @brief  calculate the Manhattan Distance (L1 Norm)
 */
template<class T>
class ManhattanDistance : public VectorDistance<T> {

public:
    virtual ~ManhattanDistance(){};

protected:
    T doCalculate(const VectorT<T>& v1, const VectorT<T>& v2) const;
};

/**
 * @struct EuclidianDistance 
 * @brief  calculate the Euclidean Distance (L2 Norm)
 */
template<class T>
class EuclidianDistance : public VectorDistance<T> {

public:
    virtual ~EuclidianDistance(){};

protected:
    T doCalculate(const VectorT<T>& v1, const VectorT<T>& v2) const;
};

template<>
Ipp32f EuclidianDistance<Ipp32f>::doCalculate(const VectorT<Ipp32f>& v1, const VectorT<Ipp32f>& v2) const;

/**
 * @struct MahalanobisDistance 
 * @brief  calculate the Mahalanobis Distance
 */
template<class T>

class MahalanobisDistance : public VectorDistance<T>
{
public:
  //! @param matrix the mahalanobis matrix
  MahalanobisDistance (const MatrixT<T>& matrix) : m_matrix(matrix) {};

  virtual ~MahalanobisDistance() {};

protected:
  T doCalculate( const VectorT<T>& v1, const VectorT<T>& v2 ) const;
  
private:
  MatrixT<T> m_matrix;
};

/**
 * @struct MaximumDistance 
 * @brief  calculate the Maximum Distance (L-inf Norm)
 */
template<class T>
class MaximumDistance : public VectorDistance<T> {

public:
    virtual ~MaximumDistance(){};

protected:
    T doCalculate(const VectorT<T>& v1, const VectorT<T>& v2) const;
};

/**
 * @struct MedianDistance 
 * @brief  calculate the Median of the absolute distances
 */
template<class T>
class MedianDistance : public VectorDistance<T> {

public:
    virtual ~MedianDistance(){};

protected:
    T doCalculate(const VectorT<T>& v1, const VectorT<T>& v2) const;
};

/**
 * @struct Chi2Distance 
 * @brief  calculate the chi^2 distance
 */
template<class T>
class Chi2Distance : public VectorDistance<T> {

public:
    virtual ~Chi2Distance(){};

protected:
    T doCalculate(const VectorT<T>& v1, const VectorT<T>& v2) const;
};

/**
 * @struct SphericalDistance 
 * @brief  calculate the distance between two sphereical angles
 * @note first parameter is the longitude and the second the latitude of the sphere
 */
template<class T>
class SphericalDistance : public VectorDistance<T> {

public:
    virtual ~SphericalDistance(){};

protected:
    T doCalculate(const VectorT<T>& v1, const VectorT<T>& v2) const;
};

/**
 * @struct SinDistance 
 * @brief  calculate the sinus of the in-between angle
 */
template<class T>
class SinDistance : public VectorDistance<T> {

public:
    virtual ~SinDistance(){};

protected:
    T doCalculate(const VectorT<T>& v1, const VectorT<T>& v2) const;
};

/**
 * @struct CosDistance 
 * @brief  calculates the cosinus distance
 */
template<class T>
class CosDistance : public VectorDistance<T> {

public:
    virtual ~CosDistance(){};

protected:
    T doCalculate(const VectorT<T>& v1, const VectorT<T>& v2) const;
};
                                                                                                                        
/**
 * @struct KLDistance
 * @brief  calculate the Kullback Leibler distance
 * @note   value of the i-th entry of \c v1 and \c v2 is only calculated
 *         if v1[i]>0 and v2[i]>0
 */
template<class T>
class KLDistance : public VectorDistance<T> {

public:
    virtual ~KLDistance(){};

protected:
    T doCalculate(const VectorT<T>& v1, const VectorT<T>& v2) const;
};

/**
 * @struct SwappedKLDistance 
 * @brief  calculate the swapped Kullback Leibler distance 
 */
template<class T>
class SwappedKLDistance : public VectorDistance<T> {

public:
    SwappedKLDistance();
    ~SwappedKLDistance();

protected:
    T doCalculate(const VectorT<T>& v1, const VectorT<T>& v2) const;

private:
    KLDistance<T>* pKLDistance;
};

/**
 * @struct ExtendedKLDistance
 * @brief  calculate the extended Kullback Leibler distance
 */
template<class T>
class ExtendedKLDistance : public VectorDistance<T> {

public:
    ExtendedKLDistance();
    ~ExtendedKLDistance();

protected:
    T doCalculate(const VectorT<T>& v1, const VectorT<T>& v2) const;

private:
    KLDistance<T>* pKLDistance;
};

/**
 * @struct BhattacharyyaDistance
 * @brief  calculate the Bhattacharyya distance
 */
template<class T>
class BhattacharyyaDistance : public VectorDistance<T> {

public:
    virtual ~BhattacharyyaDistance(){};

protected:
    T doCalculate(const VectorT<T>& v1, const VectorT<T>& v2) const;
};

template<>
Ipp32f BhattacharyyaDistance<Ipp32f>::doCalculate(const VectorT<Ipp32f>& v1, const VectorT<Ipp32f>& v2) const;

/**
 * @struct ScalarProductDistance
 * @brief  calculate the scalar product distance
 */
template<class T>
class ScalarProductDistance : public VectorDistance<T> {

public:
    virtual ~ScalarProductDistance(){};

protected:
    T doCalculate(const VectorT<T>& v1, const VectorT<T>& v2) const;
};

} // namespace NICE

//#ifdef __GNUC__
    #include <core/vector/Distance.tcc>
//#endif

#endif // __VECTOR_DISTANCE_H__
