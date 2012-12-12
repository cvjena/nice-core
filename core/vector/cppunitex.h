/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libfbasics - library of some basic tools
 * See file License for license information.
 */
#ifndef _CPPUNITEX_BASICVECTOR_H
#define _CPPUNITEX_BASICVECTOR_H



#ifdef NICE_USELIB_CPPUNIT

#include <cppunit/extensions/HelperMacros.h>
#include <core/basics/numerictools.h>
#include <core/basics/cppunitex.h>

/**
 * CppUnit macro asserting equality of double vectors.
 */
#define CPPUNIT_ASSERT_DOUBLEVECTORS_EQUAL_NOT_NAN_STREAMABLE(a,b,c,s) \
  { \
    CPPUNIT_ASSERT_EQUAL((a).size(), (b).size()); \
    bool uaieuaieOK = true; \
    for (uint uiaeuiae = 0; uiaeuiae < (a).size(); ++uiaeuiae) { \
      if (!isZero((a)[uiaeuiae] - (b)[uiaeuiae], (c)) \
          || isNaN((b)[uiaeuiae])) { \
        uaieuaieOK = false; \
        break; \
      } \
    } \
    CPPUNIT_ASSERT_STREAMABLE(uaieuaieOK, \
      "vector equality assertion failed. " << s << std::endl \
      << "- Expected: " << (a) << std::endl \
      << "- Actual  : " << (b) << std::endl); \
  }

/**
 * CppUnit macro asserting equality of double vectors.
 */
#define CPPUNIT_ASSERT_DOUBLEVECTORS_EQUAL_NOT_NAN(a,b,c) \
  CPPUNIT_ASSERT_DOUBLEVECTORS_EQUAL_NOT_NAN_STREAMABLE(a,b,c,"")

/**
 * CppUnit macro asserting equality of double vectors.
 */
#define CPPUNIT_ASSERT_DOUBLEMATRICES_EQUAL_NOT_NAN_STREAMABLE(a,b,c,s) \
  { \
    CPPUNIT_ASSERT_EQUAL((a).rows(), (b).rows()); \
    CPPUNIT_ASSERT_EQUAL((a).cols(), (b).cols()); \
    bool uaieuaieOK = true; \
    for (uint uiaeuiae = 0; uiaeuiae < (a).cols(); ++uiaeuiae) { \
      for (uint uiaeuiae2 = 0; uiaeuiae2 < (a).rows(); ++uiaeuiae2) { \
        if (!isZero((a)(uiaeuiae,uiaeuiae2) - (b)(uiaeuiae, uiaeuiae2), (c)) \
            || isNaN((b)(uiaeuiae, uiaeuiae2))) {\
          uaieuaieOK = false; \
          break; \
        } \
      } \
    } \
    CPPUNIT_ASSERT_STREAMABLE(uaieuaieOK, \
      "matrix equality assertion failed. " << s << std::endl \
      << "- Expected: " << (a) \
      << "- Actual  : " << (b)); \
  }

#define CPPUNIT_ASSERT_DOUBLEMATRICES_EQUAL_NOT_NAN(a,b,c) \
  CPPUNIT_ASSERT_DOUBLEMATRICES_EQUAL_NOT_NAN_STREAMABLE(a,b,c,"")

#endif // NICE_USELIB_CPPUNIT

#endif // _CPPUNITEX_BASICVECTOR_H
