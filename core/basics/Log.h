/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libfbasics - library of some basic tools
 * See file License for license information.
 */
#ifndef _LOG_H_
#define _LOG_H_

#include <iostream>
#include <sstream>

namespace NICE {

/**
 * A simple Logging mechanism.
 * \note Interface might change in future versions!
 */
class Log { //: public std::ostream<char> {
public:
	inline Log(std::ostream& _target = std::cerr)
         : target(&_target), quiet(false) {}
	virtual ~Log();

//  inline static Log& global() {
//    return globalLog;
//  }
//
//  inline static Log& error() {
//    return globalLog;
//  }

  //! for debug messages
  inline static std::ostream& debug() { return _debugLog(); }

  //! for errors
  inline static std::ostream& error() { return _errorLog(); }

  //! for timing data
  inline static std::ostream& timing() { return _timingLog(); }

  //! for detailed results
  inline static std::ostream& detail() { return _detailLog(); }

  //! for main results (defaults to std::cout, not std::cerr)
  inline static std::ostream& result() { return _resultLog(); }

  //! for debug messages
  inline static Log& debugLog() { return _debugLog; }

  //! for errors
  inline static Log& errorLog() { return _errorLog; }

  //! for timing data
  inline static Log& timingLog() { return _timingLog; }

  //! for detailed results
  inline static Log& detailLog() { return _detailLog; }

  //! for main results (defaults to std::cout, not std::cerr)
  inline static Log& resultLog() { return _resultLog; }

  inline std::ostream& operator() () {
    if (quiet) {
      return dummy;
    } else {
      return *target;
    }
  }

  inline void setQuiet(const bool _quiet = true) {
    quiet = _quiet;
  }

private:
  static Log _debugLog;
  static Log _errorLog;
  static Log _timingLog;
  static Log _detailLog;
  static Log _resultLog;
  static std::stringstream dummy;

  std::ostream* target;
  bool quiet;
};

} // namespace
#endif //_LOG_H_
