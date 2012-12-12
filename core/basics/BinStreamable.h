/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libfbasics - library of some basic tools
 * See file License for license information.
 */
/*****************************************************************************/
#ifndef _BINSTREAMABLE_FBASICS_H
#define _BINSTREAMABLE_FBASICS_H

#include <iostream>

#include <core/basics/binstream.h>

namespace NICE {

/**
 * Abstract base class for binarily streamable classes.
 */
class BinStreamable {
public:
  /**
   * Format (compression method)
   */
  enum Format {
    /**
     * Save in binary format which is compressed with gzip
     * (only supported if compiled with zlib, use \#ifdef NICE_USELIB_ZLIB)
     */
    BIN_GZ=3,
    /**
     * Save in binary format (uncompressed)
     */
    BIN=4
  };

  virtual ~BinStreamable(){}

  /**
   * Read class attributes from ibinstream
   * \param stream ibinstream to read elements from
   */
  virtual void read(ibinstream& stream) = 0;

  /**
   * Write class attributes to obinstream.
   * \param stream obinstream to write elements to
   */
  virtual void write(obinstream& stream) const = 0;

  /**
   * Read class attributes from ibinstream
   * \param stream ibinstream to read elements from
     */
  inline void readBin(ibinstream& stream) {
    read(stream);
  }

  /**
   * Write class attributes to obinstream.
   * \param stream obinstream to write elements to
   */
  inline void writeBin(obinstream& stream) const {
    write(stream);
  }

  /** Read class attributes from a file.
   * \param filename Name of the file
   * \param compression file format \see SaveMethod
   */
  virtual void readFromBinFile(const char *filename,
                               Format compression=BIN);

  /**
   * Write class attributes to a file.
   * \param filename Name of the file
   * \param compression file format \see SaveMethod
   */
  virtual void writeToBinFile(const char *filename,
                              Format compression=BIN) const;
};

inline obinstream& operator<<(obinstream &strm, const BinStreamable &ex) {
  ex.writeBin(strm);
  return strm;
}

inline ibinstream& operator>>(ibinstream &strm, BinStreamable &ex) {
  ex.readBin(strm);
  return strm;
}

}; // namespace NICE

#endif /* _BINSTREAMABLE_FBASICS_H */
