/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libfbasics - library of some basic tools
 * See file License for license information.
 */
#ifndef _FEXCEPTION_H_
#define _FEXCEPTION_H_

#include <exception>
#include <string>
#include <iostream>
#include <sstream>

namespace NICE {

/**
 * Throw an exception of type \c type with message \c m
 * and supply the exception's constructor with source code file and line.
 * The message will be composed using a stream.
 * Example: <code>fthrow(Exception, "ups. error: " << code)</code>
 */
#define fthrow(type, stream)                                  \
  {                                     \
   std::stringstream sneudfgiaenuiae;                         \
   sneudfgiaenuiae << stream;                                 \
   throw type((__FILE__), (__LINE__), sneudfgiaenuiae.str()); \
  };

/**
 * Throw an exception of type \c type
 * with message \c m and causing exception \c cause
 * and supply the exception's constructor with source code file and line.
 * Additionally specify the causing exception (when re-throwing).
 * The message will be composed using a stream.
 * Example: <code>fthrowc(Exception, "ups. error: " << code, cause)</code>
 */
#define fthrowc(type, stream, cause)                                   \
  {using namespace NICE;                                              \
   std::stringstream sneudfgiaenuiae;                                  \
   sneudfgiaenuiae << stream;                                          \
   throw type((__FILE__), (__LINE__), sneudfgiaenuiae.str(), (cause)); \
  };

/**
 * @deprecated Same as fthrow
 */
#define fthrowstream(type, m) \
  fthrow(type, m)
//   {using namespace NICE; throw type((__FILE__), (__LINE__), (m));};

/**
 * @deprecated Same as fthrowc
 */
#define fthrowstreamc(type, m, cause) \
  fthrowc(type, m, cause)
//   {using namespace NICE; throw type((__FILE__), (__LINE__), (m), (cause));};

/**
 * A general purpose exception class.
 * There are additional macros \c ::fthrow und \c ::fthrowc which simplify
 * the usage of some features of this class.
 */
class Exception : public std::exception {
public:
  /**
   * Create an exception with a message string.
   * @param _message The message text
   */
  inline Exception(const std::string& _message)
      : filename("unknown"), line(0), message(_message) {}

  /**
   * Create an exception with a message string and a causing exception
   * @param _message The message text
   * @param _cause The causing exception
   */
  Exception(const std::string& _message, const exception& _cause);

  /**
   * Create an exception with a message string and information about the
   * throwing position in the source code.
   * @param _filename Source code file
   * @param _line Source code line
   * @param _message The message text
   */
  inline Exception(const char* _filename, const int _line,
                    const std::string& _message)
      : filename(_filename), line(_line), message(_message) {}

  /**
   * Create an exception with a message string and a causing exception
   * as well as information about the throwing position in the source code.
   * @param _filename Source code file
   * @param _line Source code line
   * @param _message The message text
   * @param _cause The causing exception
   */
  Exception(const char* _filename, const int _line,
             const std::string& _message, const exception& _cause);

  inline Exception(const Exception& e) throw()
      : std::exception(e) {
    *this = e;
  }

  Exception& operator=(const Exception& e) throw() {
    filename = e.filename;
    line = e.line;
    message = e.message;
    cause = e.cause;
    return *this;
  }

  virtual ~Exception() throw();

  /**
   * The message text and additional information. Useful as output message.
   */
  virtual const char* what() const throw();

  /**
   * The name of the exception class. Should be re-implemented in subclasses.
   */
  virtual const char* name() const throw();

protected:
  //! Source code file
  std::string filename;

  //! Source code line
  int line;

  //! Message text
  std::string message;

  //! Causing exception
  std::string cause;
  
  //! a buffer for the string returned by what()
  mutable std::string whatBuffer;
};

} // namespace

/**
 * Define new exception classes.
 * Example: <code>DEFINE_NICE_EXCEPTION(ImageException)</code>.
 */
#define DEFINE_NICE_EXCEPTION(ename) \
class ename : public NICE::Exception { \
public: \
  inline ename(const std::string& _message) : Exception(_message) {} \
  inline ename(const std::string& _message, const exception& _cause) \
      : Exception(_message, _cause) {} \
  inline ename(const char* _filename, const int _line, \
               const std::string& _message) \
      : Exception(_filename, _line, _message) {} \
  inline ename(const char* _filename, const int _line, \
               const std::string& _message, const exception& _cause) \
      : Exception(_filename, _line, _message, _cause) {} \
  inline ename(const ename& orig) throw() : NICE::Exception(orig) {} \
  inline ename& operator=(const ename& orig) throw() { \
    *this = orig; \
    return *this; \
  } \
  virtual ~ename() throw() {} \
  const char* name() const throw() { return #ename; } \
};

#define DEFINE_LIMUN_EXCEPTION(ename) DEFINE_NICE_EXCEPTION(ename)

/*
#define LIMUN_EXCEPTION_IMPLEMENTATION(ename) \
ename::~ename()  throw() { \
} \
const char* ename::name() const throw() { \
  return #ename; \
}
*/

#endif //_FEXCEPTION_H_
