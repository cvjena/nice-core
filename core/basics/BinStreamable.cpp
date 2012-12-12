/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libfbasics - library of some basic tools
 * See file License for license information.
 */
/*****************************************************************************/
#include "core/basics/BinStreamable.h"
#include <stdexcept>
#include <fstream>
#include <core/basics/gzbinstream.h>

#include "core/basics/Exception.h"

namespace NICE {

void BinStreamable::readFromBinFile(const char *filename, Format compression)
{
  switch(compression) {
    case BIN: {
      ifbinstream file(filename);
      if (!file.good()) {
        fthrow(Exception, "readFromBinFile(): could not open file.");
      }
      readBin(file);
      file.close();
      break;
    }
#ifdef NICE_USELIB_ZLIB
    case BIN_GZ: {
      igzbinstream file(filename);
      if (!file.good()) {
        fthrow(Exception, "readFromBinFile(): could not open file.");
      }
      readBin(file);
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

void BinStreamable::writeToBinFile(const char *filename, 
                                   Format compression) const
{
  switch(compression) {
    case BIN: {
      ofbinstream file(filename);
      if (!file.good()) {
        fthrow(Exception, "writeToBinFile(): could not open file.");
      }
      writeBin(file);
      file.close();
      break;
    }
#ifdef NICE_USELIB_ZLIB
    case BIN_GZ: {
      ogzbinstream file(filename);
      if (!file.good()) {
        fthrow(Exception, "writeToBinFile(): could not open file.");
      }
      writeBin(file);
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

}; // namespace NICE 
