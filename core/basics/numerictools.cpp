/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libfbasics - library of some basic tools
 * See file License for license information.
 */
#include "core/basics/numerictools.h"

#include <errno.h>
#include <sstream>
#include <clocale>
#include <core/basics/Log.h>
#include <core/basics/Timer.h>
#include <core/basics/Exception.h>
#include <core/basics/Streamable.h>

typedef unsigned int uint;

namespace NICE {

// check if endptr is empty string (except for whitespaces)
static bool isEndPtrOk(char* endptr) {
  std::stringstream s(endptr);
  // skip whitespaces
  ws(s);
  return s.eof();
}

// double stringToDouble(const char* s) {
//   errno = 0;
//   char* endptr;
//   const double v = strtod(s, &endptr);
//   if (errno != 0 || !isEndPtrOk(endptr)) {
//     fthrow(Exception, "Format error in floating point input");
//   }
//   return v;
// }

double stringToDouble(const char* s) {
  char* endptr;
  setlocale(LC_NUMERIC, US_ENGLISH_LOCALE);
  errno = 0;
  const double v = strtod(s, &endptr);
  if (errno != 0 || !isEndPtrOk(endptr)) {
    std::string st(s);
    if (st == "nan") {
      return doubleNaN();
    } else if (st == "inf") {
      return std::numeric_limits<double>::infinity();
    } else if (st == "-inf") {
      return -std::numeric_limits<double>::infinity();
    }
    fthrow(Exception, "Format error in floating point input: "
                       << s << " (" << errno << ")");
  }
  return v;
}

long stringToInt(const char* s) {
  errno = 0;
  char* endptr;
  const long v = strtol(s, &endptr, 10);
  if (errno != 0 || !isEndPtrOk(endptr)) {
    fthrow(Exception, "Format error in integer input");
  }
  return v;
}

void initRand( bool fixedSeed, unsigned int seed ) {
//  const double now = Timer::getNow();
//  const unsigned int seed = (unsigned int)(now * 1000.0);
//  Log::debug() << "now, seed: " << now << ", " << seed << std::endl;
//  srand(seed);
    if ( fixedSeed )
	  srand ( (uint)seed );
	else
	  srand((uint)Timer::getMicroseconds());
}

std::string intToString(const int i) {
  std::stringstream s;
  s << i;
  return s.str();
}

std::string doubleToString(const double d, const unsigned int digits,
                           const bool fixedPoint) {
  std::stringstream s;
  s.imbue(std::locale(US_ENGLISH_LOCALE));
  s.precision(digits);
  if (fixedPoint) {
    s << std::fixed;
  }
  s << d;
  return s.str();
}

} // namespace
