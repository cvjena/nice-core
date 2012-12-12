#ifndef COORDT_H
#define COORDT_H


#include <ostream>

namespace NICE {
  
/**
 * A simple 2D coordinate. 
 * 
 * @author Frank Mattern 
 */
template<class T>
class CoordT {
 public:
  T x;
  T y;
  
 public:
  /**
   * Create an zero coordinate.
   */
	CoordT() {
    x = 0;
    y = 0;
  }
  
  /**
   * Create a coordinate with given parameters.
   * @param _x 
   * @param _y 
   */
  CoordT(const T _x, const T _y) {
    x = _x;
    y = _y;
  }

  /**
   * Copy-constructor.
   * @param other Original coordinate.
   */
  CoordT(const CoordT<T>& other) {
    x = other.x;
    y = other.y;
  }

  ~CoordT() {
  }

  //! Assignment operator
  /*! \param ex class to copy
   *  \return a reference to this class 
   */
  CoordT<T>& operator=(const CoordT<T>& ex)
  {
      x=ex.x;
      y=ex.y;
      return *this;
  }

  //! Compare operator
  /*! \param ex class to compare
   *  \return true if class content is equal
   */
  bool operator==(const CoordT<T>& ex) const
  {
      if(ex.x==x && ex.y == y)
          return true;
      else 
          return false;
  }
  
  CoordT<T> &operator+=(const CoordT<T>& ex) 
  {
    x += ex.x;
    y += ex.y;
    return *this;
  }

  CoordT<T> &operator-=(const CoordT<T>& ex) 
  {
    x -= ex.x;
    y -= ex.y;
    return *this;
  }

  CoordT<T> &operator*=(const T& v) 
  {
    x *= v;
    y *= v;
    return *this;
  }

  CoordT<T> &operator/=(const T& v) 
  {
    x /= v;
    y /= v;
    return *this;
  }

  CoordT<T> operator+(const CoordT<T>& ex) const
  {
    CoordT<T> result(x,y);
    result+=ex;
    return result;
  }
  
  CoordT<T> operator-(const CoordT<T>& ex) const
  {
    CoordT<T> result(x,y);
    result-=ex;
    return result;
  }

  CoordT<T> operator*(const T& v) const
  {
    CoordT<T> result(x,y);
    result*=v; 
    return result;
  }

  CoordT<T> operator/(const T& v) const
  {
    CoordT<T> result(x,y);
    result/=v; 
    return result;
  }
};

template<class T>
inline std::ostream& operator<< (std::ostream& out, const CoordT<T>& coord) {
  out << coord.x << " " << coord.y;
  return out;
}

typedef CoordT<int> Coord;

} // namespace
#endif // COORDT_H
