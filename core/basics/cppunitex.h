/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libfbasics - library of some basic tools
 * See file License for license information.
 */
#ifndef _CPPUNITEX_FBASICS_H
#define _CPPUNITEX_FBASICS_H



#ifdef NICE_USELIB_CPPUNIT

#include <cppunit/extensions/HelperMacros.h>
#include <core/basics/numerictools.h>

/**
 * This is similar to CppUnit's built in CPPUNIT_ASSERT_MESSAGE,
 * but \c _STREAMABLE_ can be anything streamable to a std::stringstream
 * (including expressions like the following:
 *  <code>"test failed with error " << error << "."</code>)
 */
#define CPPUNIT_ASSERT_STREAMABLE(_CONDITION_,_STREAMABLE_) \
      if(!(_CONDITION_)) { \
        std::stringstream _MSG_; \
        _MSG_<<_STREAMABLE_<<std::endl; \
        CPPUNIT_NS::Asserter::fail(_MSG_.str() , CPPUNIT_SOURCELINE() ); }

/**
 * CppUnit macro asserting that \c b is NOT NaN (Not a Number)
 */
#define CPPUNIT_ASSERT_NOT_NAN(b) \
        CPPUNIT_ASSERT_MESSAGE("Value is NaN", !isNaN(b));

/**
 * CppUnit macro asserting that \c b IS NaN (Not a Number)
 */
#define CPPUNIT_ASSERT_IS_NAN(b) \
        CPPUNIT_ASSERT_MESSAGE("Value is not NaN", isNaN(b));


/**
 * CppUnit macro asserting equality of doubles.
 */
#define CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN_STREAMABLE(a,b,c,s) \
  { \
    bool uaieuaieOK = true; \
    if (!isZero(double(a) - double(b), double(c)) || isNaN(b)) { \
      uaieuaieOK = false; \
    } \
    CPPUNIT_ASSERT_STREAMABLE(uaieuaieOK, \
      "equality assertion failed. " << s << std::endl \
      << "- Expected: " << (a) << std::endl \
      << "- Actual  : " << (b) << std::endl); \
  }

/**
 * CppUnit macro asserting equality of doubles.
 */
#define CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(a,b,c) \
  CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN_STREAMABLE(a,b,c,"")

/**
 * CppUnit macro asserting equality of double values.
 * This is like CppUnit's built in CPPUNIT_ASSERT_DOUBLES_EQUAL
 * extended by an explicit check that \c b is NOT NaN
 * (CPPUNIT_ASSERT_DOUBLES_EQUAL will NOT fail if \c b is NaN,
 *  but most of the time, this IS an error).
 */
/*
#define CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(a,b,c) \
        CPPUNIT_ASSERT_NOT_NAN((b)); \
        CPPUNIT_ASSERT_DOUBLES_EQUAL((a),(b),(c));
*/

/**
 * Like CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN, but here \c c is \b relative
 * to \c a.
 */
#define CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN_REL(a,b,c) \
        CPPUNIT_ASSERT_NOT_NAN((b)); \
        CPPUNIT_ASSERT_DOUBLES_EQUAL((a),(b),fabs(a*c));


/**
 * This is similar to CppUnit's built in CPPUNIT_ASSERT_EQUAL,
 * but streams the two parameters and compares the resulting strings.
 * Hence, any streamable objects can be compared.
 */
#define CPPUNIT_ASSERT_EQUAL_STREAMED(a,b) \
    { \
      std::ostringstream str_a, str_b; \
      str_a << a; \
      str_b << b; \
      CPPUNIT_ASSERT_EQUAL(str_a.str(), str_b.str()); \
    }

/**
 * This is similar to CppUnit's built in CPPUNIT_ASSERT_MESSAGE,
 * but \c _STREAMABLE_ can be anything streamable to a std::stringstream
 * (including expressions like the following:
 *  <code>"test failed with error " << error << "."</code>)
 * @deprecated Use CPPUNIT_ASSERT_STREAMABLE instead
 */
#define CPPUNIT_COND_STREAM(_COND_,_STREAM_) \
      CPPUNIT_ASSERT_STREAMABLE(_COND_,_STREAM_)

#endif // NICE_USELIB_CPPUNIT

#endif // _CPPUNITEX_FBASICS_H
