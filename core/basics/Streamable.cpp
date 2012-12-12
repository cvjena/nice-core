/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libfbasics - library of some basic tools
 * See file License for license information.
 */
/*****************************************************************************/
#include "core/basics/Streamable.h"
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <core/basics/gzstream.h>
#include <core/basics/bzstream.h>

#include "core/basics/Exception.h"

namespace NICE {

const char* GERMAN_LOCALE = "de_DE.utf8";
const char* US_ENGLISH_LOCALE = "en_US.utf8";
// const char* US_ENGLISH_LOCALE = "en_US";

// set the global locale to US english at startup
class __SetLocale__ {
private:
  inline __SetLocale__() {
    std::locale::global(std::locale(US_ENGLISH_LOCALE));
  }
  static __SetLocale__ instance;
};

void Streamable::readFromFile(const char* filename, Format compression)
{
  switch(compression) {
    case ASCII: {
      std::ifstream file(filename);
      if (!file.good() || !file.is_open()) {
        fthrow(Exception, "readFromFile(): could not open file: " << filename);
      }
      read(file);
      file.close();
      break;
    }
#ifdef NICE_USELIB_ZLIB
    case ASCII_GZ: {
      igzstream file(filename);
      if (!file.good()) {
        fthrow(Exception, "readFromFile(): could not open file: " << filename);
      }
      read(file);
      file.close();
      break;
    }
#endif
#ifdef NICE_USELIB_BZLIB
    case ASCII_BZ: {
      ibzstream file(filename);
      if (!file.good()) {
        fthrow(Exception, "readFromFile(): could not open file: " << filename);
      }
      read(file);
      file.close();
      break;
    }
#endif
    default:
      fthrow(Exception,
             "File cannot be read! Compression method not supported.");
      break;
  }
}

void Streamable::writeToFile(const char* filename, Format compression) const
{
  switch(compression) {
    case ASCII: {
      std::ofstream file(filename);
      if (!file.good()) {
        fthrow(Exception, "writeToFile(): could not open file: " << filename);
      }
      write(file);
      file.close();
      break;
    }
#ifdef NICE_USELIB_ZLIB
    case ASCII_GZ: {
      ogzstream file(filename);
      if (!file.good()) {
        fthrow(Exception, "writeToFile(): could not open file: " << filename);
      }
      write(file);
      file.close();
      break;
    }
#endif
#ifdef NICE_USELIB_BZLIB
    case ASCII_BZ: {
      obzstream file(filename);
      if (!file.good()) {
        fthrow(Exception, "writeToFile(): could not open file: " << filename);
      }
      write(file);
      file.close();
      break;
    }
#endif
    default:
      fthrow(Exception,
             "File cannot be written! Compression method not supported.");
      break;
  }
}

std::string Streamable::toString() const {
  std::stringstream s;
  s << *this;
  return s.str();
}

}; // namespace NICE
