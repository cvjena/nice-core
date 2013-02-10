#ifndef _NUMERICTOOLS_FBASICS_H
#define _NUMERICTOOLS_FBASICS_H
/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libfbasics - library of some basic tools
 * See file License for license information.
 */
#define _USE_MATH_DEFINES
#include <cmath>
#ifdef WIN32
	#include <math.h>
#endif

#include "CrossplatformDefines.h"

#ifdef NICE_BOOST_FOUND
#include <boost/math/special_functions/fpclassify.hpp> // isnan
#endif

#include <stdlib.h>
#include <limits>
#include <string>

#ifdef LIMUN_AIBO_MODE
  // some functions missing in math.h (NOT in linum namespace!!)

  inline float roundf(float x) {
    return floor(x + 0.5);
  }

  inline double round(double x) {
    return floor(x + 0.5);
  }

  inline long double roundl(long double x) {
    return floor(x + 0.5);
  }

  inline long lroundf(float x) {
    return (long) floor(x + 0.5);
  }

  inline long lround(double x) {
    return (long) floor(x + 0.5);
  }

  inline long lroundl(long double x) {
    return (long) floor(x + 0.5);
  }
#endif // LIMUN_AIBO_MODE


namespace NICE  {

/**
 * Is a numerical value zero?
 */
template<class T>
inline bool isZero(const T& x) {
  return x == (T)0;
}

/**
 * Is a numerical value zero up to a tolerance?
 */
inline bool isZero(float x, float tolerance) {
  return fabs(x) < tolerance;
}

/**
 * Is a numerical value zero up to a tolerance?
 */
inline bool isZero(double x, double tolerance) {
  return fabs(x) < tolerance;
}

/**
 * Is a numerical value zero?
 * Specialization for floating point: Zero up to machine precision?
 */
template<>
inline bool isZero(const float& x) {
  return isZero(x, std::numeric_limits<float>::epsilon());
}

/**
 * Is a numerical value zero?
 * Specialization for floating point: Zero up to machine precision?
 */
template<>
inline bool isZero(const double& x) {
  return isZero(x, std::numeric_limits<double>::epsilon());
}

/**
 * Is a numerical value almost zero ? :) up to 1e-15
 */
inline bool almostZero(const double a) {
	return (fabs(a)<1e-15);
}

/**
 * Is \c x = \c y up to a tolerance?
 */
inline bool isEqual(float x, float y, float tolerance) {
  return fabs(x - y) < tolerance;
}

/**
 * Is \c x = \c y up to a tolerance?
 */
inline bool isEqual(double x, double y, double tolerance) {
  return fabs(x - y) < tolerance;
}

/**
 * Is \c x = \c y up to machine precision?
 */
inline bool isEqual(float x, float y) {
  return isEqual(x, y, std::numeric_limits<float>::epsilon());
}

/**
 * Is \c x = \c y up to machine precision?
 */
inline bool isEqual(double x, double y) {
  return isEqual(x, y, std::numeric_limits<double>::epsilon());
}

/**
 * Sign of a numerical value?
 * (For floating point values, zero is checked up to machine precision,
 *  see isZero()).
 */
template<class T>
inline T sign(const T& x) {
  if (isZero(x)) {
    return (T)0;
  } else if (x > (T)0) {
    return (T)1;
  } else {
    return (T)(-1);
  }
}

/**
 * Absolute value (as std::abs() or fabs() for floating point values).
 */
template<class T>
inline T absolute(const T& x) {
  //return std::abs(x);
  if (x >= T(0)) {
    return x;
  } else {
    return -x;
  }
}

/**
 * Absolute value (as fabs()).
 */
template<>
inline float absolute(const float& x) {
  return (float) fabs(x);
}

/**
 * Absolute value (as fabs()).
 */
template<>
inline double absolute(const double& x) {
  return (double) fabs(x);
}

/**
 * Impose the sign of a numerical value to the sign of another value.
 * (For floating point values, zero is checked/handled up to machine precision,
 *  see isZero()).
 * @param x The input value
 * @param s The value supplying the sign (its absolute value may be arbitrary)
 * @return \c x with the same sign as \c s
 */
template<class T>
inline T imposeSign(const T& x, const T& s) {
  return absolute(x) * sign(s);
}

/**
 * Square.
 */
template<class T>
inline T square(const T& t) {
  return t * t;
}

/**
 * Cube.
 */
template<class T>
inline T cube(const T& t) {
  return t * t * t;
}

/**
 * Cube root: t^(1/3)
 */
inline double cubeRoot(const double& t) {
  return sign(t) * pow(fabs(t), 1.0 / 3.0);
}

/**
 * Check if a floating point value is NaN
 */
inline bool isNaN(double x) {
	

#ifdef NICE_BOOST_FOUND
	return  boost::math::isnan(x);
#else
	#if (__GNUC__ > 3)
	  return isnan(x);
	#else
	  return x != x;
	#endif
#endif
}

/**
 * Check if a floating point value is NaN
 */
inline bool isNaN(float x) {
#ifdef NICE_BOOST_FOUND
	return  boost::math::isnan(x);
#else
	#if (__GNUC__ > 3)
	  return isnan(x);
	#else
	  return x != x;
	#endif
#endif
}

inline bool isFinite(double x)
{
#ifdef WIN32
	#ifdef NICE_BOOST_FOUND
	    return boost::math::isfinite(x);
	#else
		ERROR("isFinite() not defined (and neither is boost found for compensation...)")
	#endif
#else
	return finite(x);
#endif
}

/**
 * Create NaN
 */
inline double doubleNaN() {
  double zero = 1.0;
  zero -= zero;
  return 0.0 / zero;
}

/**
 * Create NaN
 */
inline float floatNaN() {
  float zero = 1.0f;
  zero -= zero;
  return 0.0f / zero;
}

/**
 * Restrict \c value to be within [\c min, \c max].
 */
template<class T>
inline const T& limitValue(const T& value, const T& min, const T& max) {
  if (value < min) {
    return min;
  } else if (value > max) {
    return max;
  } else {
    return value;
  }
}

/**
 * Degree to radian.
 */
inline double degreeToRadian(double a) {
  return a * M_PI / 180.0;
}

/**
 * Radian to degree.
 */
inline double radianToDegree(double a) {
  return a / M_PI * 180.0;
}

/**
 * Normalize an angle to be between 0 and 2 Pi.
 */
inline double normalizeAngle(double a) {
  const double TWO_PI = 2.0 * M_PI;
  return a - floor(a / TWO_PI) * TWO_PI;
}

/**
 * Initialize random number generator.
 */
void initRand( bool fixedSeed = false, unsigned int seed = 0 );

/**
 * A pseudo random number in the range [0,limit), based on \c rand().
 * (Initialize generator with \c initRand()).
 */
inline int randInt(const int limit) {
  if (limit == 0) {
    return 0;
  } else {
    return rand() % limit;
  }
}

/**
 * A pseudo random number in the range [0,1), based on \c rand().
 * (Initialize generator with \c initRand()).
 */
inline double randDouble() {
  return ((double)rand() / ((double)(RAND_MAX)+1.0));
}


/**
 * A pseudo random number in the range [0,limit), based on \c rand().
 * (Initialize generator with \c initRand()).
 */
inline double randDouble(const double limit) {
  return ((double)rand() / ((double)(RAND_MAX)+1.0)) * limit;
}

/**
 * A pseudo random number in the range [0,1), based on \c rand().
 * (Initialize generator with \c initRand()).
 */
inline float randFloat() {
  return ((float)rand() / ((float)(RAND_MAX)+1.0f));
}

/**
 * A pseudo random number in the range [0,limit), based on \c rand().
 * (Initialize generator with \c initRand()).
 */
inline float randFloat(const float limit) {
  return ((float)rand() / ((float)(RAND_MAX)+1.0f)) * limit;
}

/** 
 * A pseudo random number generated using a normal distribution
 * with an arbitrary standard deviation \c s and zero mean.
 */
inline double randGaussDouble ( const double stddev ) {
	// adapted from k_reconstruction (Olaf Kähler)
        double r1, r2, d;
        do {
                r1 = 2.0 * randDouble() - 1.0;
                r2 = 2.0 * randDouble() - 1.0;
                d = r1*r1 + r2*r2;
        } while ((d >= 1.0)||(isZero(d)));
        d = sqrt((-2.0 * log(d))/d);
        double y1 = r1*d;
        // y2 = r2*d; this is another random variable
	return y1*stddev;
}

/**
 * If \c x is NaN, return infinity, x otherwise.
 */
inline double nanToInf(double x) {
  if (isNaN(x)) {
    return std::numeric_limits<double>::infinity();
  } else {
    return x;
  }
}

/**
 * Convert string to double, including inf and nan.
 * @param s Input string
 * @return the double represented by s
 * @throw Exception if format not ok
 */
double stringToDouble(const char* s);

inline double stringToDouble(std::string s) {
  return stringToDouble(s.c_str());
}

/**
 * Read double from istream, including inf and nan.
 *
 * Example1: double x; cin >> x;
 *
 * Example2: double y; readDouble(y);
 *
 * If a correct double can be read from the stream,
 * both examples do the same. In case of inf and nan,
 * only the second version reads correctly.
 * Also: errors are signaled differently.
 *
 * @param s Input string
 * @return the double represented by s
 * @throw Exception if format not ok
 */
inline double readDouble(std::istream& str) {
  std::string s;
  str >> s;
  return stringToDouble(s);
}

/**
 * Convert string to int.
 * @param s Input string
 * @return the int represented by s
 * @throw Exception if format not ok
 */
long stringToInt(const char* s);

inline long stringToInt(std::string s) {
  return stringToInt(s.c_str());
}

/**
 * Convert an integer into a string.
 */
std::string intToString(const int i);

/**
 * Convert a double into a string.
 */
std::string doubleToString(const double d, const unsigned int digits = 6,
                           const bool fixedPoint = false);

/**
 * Round a floating point value and convert to int.
 */
inline int roundInt(double d) {
  return int(round(d));
}

/**
 * Round a floating point value and convert to int.
 */
inline int roundInt(float d) {
  return int(roundf(d));
}

} // namespace

#endif // _NUMERICTOOLS_FBASICS_H
