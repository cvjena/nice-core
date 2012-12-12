/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libfbasics - library of some basic tools
 * See file License for license information.
 */
#include "core/basics/Exception.h"
#include <sstream>
#include <iostream>

using namespace std;

namespace NICE {

Exception::Exception(const std::string& _message, const exception& _cause)
      : filename("unknown"), line(0), message(_message) {
  // NOTE for some (?) causing exceptions, the following code is
  // the ONLY working variant known -- DO NOT CHANGE!
  const std::string& temp = _cause.what();
  for (unsigned int i = 0; i < temp.size(); i++) {
    cause += temp[i];
  }
}

Exception::Exception(const char* _filename, const int _line,
                       const std::string& _message, const exception& _cause)
      : filename(_filename), line(_line), message(_message) {
  // NOTE for some (?) causing exceptions, the following code is
  // the ONLY working variant known -- DO NOT CHANGE!
  const std::string& temp = _cause.what();
  for (unsigned int i = 0; i < temp.size(); i++) {
    cause += temp[i];
  }
}

Exception::~Exception() throw() {
}

const char* Exception::what() const throw() {
  try {
    std::stringstream s;
    s << "Exception " << name()
      << " in file " << filename
      << " line " << line
      << " with message:" << std::endl << " " << message;
    if (cause.size() > 0) {
      s << std::endl << " caused by: " << cause;
    }
    whatBuffer = s.str();
    return whatBuffer.c_str();
  } catch(...) {
    return "Exception: exception while formating what()-string";
  }
}

const char* Exception::name() const throw() {
  return "Exception";
}

} // namespace
