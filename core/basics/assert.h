/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libfbasics - library of some basic tools
 * See file License for license information.
 */
#ifndef _ASSERT_H_
#define _ASSERT_H_

#include <iostream>
#include <string>
#include <sstream>
#include <core/basics/types.h>

#include <core/basics/Exception.h>

namespace NICE {

//#define assert(t) if (!t) {cout << "Assertion failed." << endl;}

/**
 * Deprecated! A simple assertion function.
 * @deprecated Use fassert() or fassert2() instead
 */
inline void assert2(const bool t, const std::string& message = std::string()) {
  if (!t) {
    std::cerr << "Assertion failed. " << message << std::endl;
    //std::stringstream s;
    //s << "Assertion failed: " << message;
    //fthrow(Exception, s.str());
  }
}

/**
 * A simple assertion function. (Behavior might be changed in the future.)
 */
inline void __assert(const bool exp,
                     std::string message = std::string(),
                     std::string code = std::string(),
                     const char* file = "",
                     uint line = 0) {
  if (!exp) {
    //std::cerr << "Assertion failed. " << message << std::endl;
    std::stringstream s;
    s << "Assertion failed in file " << file << " at line " << line
      << ". Code: '" << code << "'";
    if (message.size() > 0) {
      s << " Message: '" << message << "'";
    }
    s << ".";
//     std::cerr << s.str() << std::endl;
//     fthrow(Exception, s.str());
    std::string* buffer = new std::string(s.str());
    fthrow(Exception, *buffer);
  }
}

#define fassert(exp) NICE::__assert((exp), "", #exp,__FILE__,__LINE__)
#define fassert2(exp, msg) \
{ \
  std::stringstream s; \
  s << msg; \
  NICE::__assert((exp), s.str(), #exp,__FILE__,__LINE__); \
}

} // namespace
#endif // _ASSERT_H_
