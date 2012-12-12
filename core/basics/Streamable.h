/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libfbasics - library of some basic tools
 * See file License for license information.
 */
/*****************************************************************************/
#ifndef _STREAMABLE_FBASICS_H
#define _STREAMABLE_FBASICS_H

#include <iostream>
#include <string>


namespace NICE {

extern const char* GERMAN_LOCALE;
extern const char* US_ENGLISH_LOCALE;

/**
 * Abstract base class for streamable classes.
 */
class Streamable {
public:
  /**
   * Format (compression method)
   */
  enum Format {
    /**
     * Save in ascii format (uncompressed)
     */
    ASCII=0,
    /**
     * Compress the ascii format with bzip2
     * (only supported if compiled with bzlib, use \#ifdef NICE_USELIB_BZLIB)
     */
    ASCII_BZ=1,
    /**
     * Compress the ascii format with gzip
     * (only supported if compiled with zlib, use \#ifdef NICE_USELIB_ZLIB)
     */
    ASCII_GZ=2
  };

  virtual ~Streamable(){}

  /**
   * Read this object (class attributes) from \c ostream.
   * \param stream istream to read elements from
   */
  virtual void read(std::istream& stream) = 0;

  /**
   * Write class atttributes to ostream
   *  \param stream ostream to write elements to
   */
  virtual void write(std::ostream& stream) const = 0;

  /** Read class attributes from a file.
   * \param filename Name of the file
   * \param compression file format \see SaveMethod
   */
  virtual void readFromFile(const char* filename,
                            Format compression=ASCII);

  //! see readFromFile(const char *, Format)
  inline void readFromFile(const std::string& filename,
                           Format compression=ASCII) {
    readFromFile(filename.c_str(), compression);
  }

  /**
   * Write class attributes to a file.
   * \param filename Name of the file
   * \param compression file format \see SaveMethod
   */
  virtual void writeToFile(const char* filename,
                           Format compression=ASCII) const;

  //! see writeToFile(const char *, Format)
  inline void writeToFile(const std::string& filename,
                          Format compression=ASCII) const {
    writeToFile(filename.c_str(), compression);
  }

  /**
   * Return a string representing this object.
   * Default implementation streams the object to a string stream.
   */
  virtual std::string toString() const;
};

inline std::ostream& operator<<(std::ostream &strm, const Streamable &ex) {
  ex.write(strm);
  return strm;
}

inline std::istream& operator>>(std::istream &strm, Streamable &ex) {
  ex.read(strm);
  return strm;
}

inline void writeBool(std::ostream& output, bool b) {
  int i = (b ? 1 : 0);
  output << i;
}

inline bool readBool(std::istream& input) {
  int i;
  input >> i;
  return i != 0;
}

}; // namespace NICE

#endif /* _STREAMABLE_FBASICS_H */
