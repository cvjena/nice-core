#ifndef GZBINSTREAM_H
#define GZBINSTREAM_H
// ============================================================================
// gzbinstream, C++ iostream classes for gzbinary in and output 
// Copyright (C) 2006  Frank Mattern 
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
// ============================================================================
//
// File          : gzbinstream.h
// Revision      : $Revision: 1.2 $
// Revision_date : $Date: 2009/05/28 11:36:30 $
// Author(s)     : Frank Mattern 
// 
// Standard streambuf implementation following Nicolai Josuttis, "The 
// Standard C++ Library".
// ============================================================================


#include "core/basics/binstream.h"
// standard C++ with new header file names and std:: namespace
#ifdef NICE_USELIB_ZLIB
#ifdef NICE_USELIB_LINAL
#include "LinAl/matrix.h"
#endif
#include "core/basics/gzstream.h"
#include "core/basics/binstream.h"
#include <iostream>
#include <fstream>
#include <zlib.h>


namespace NICE{


// ----------------------------------------------------------------------------
// User classes. Use igzbinstream and ogzbinstream analogously to ifstream and
// ofstream respectively. They read and write files based on the gz* 
// function interface of the zlib. Files are compatible with gzip compression.
// ----------------------------------------------------------------------------

/**
 * Input gzip binary stream class. 
 * Supports reading of gzip binary files. 
 * 
 * @author Frank Mattern, Ferid Bajramovic
 */
class igzbinstream : public NICE::ibinstream {
private:
  igzstream stream;
public:
  igzbinstream() {} 
  
  igzbinstream(const char* name,
               std::ios_base::openmode mode = std::ios::in)
      : stream(name, mode) {}
  
  //gzstreambuf* rdbuf() { return gzstreambase::rdbuf(); }
  
  virtual void read(char* data, unsigned int length) {
    stream.read(data, length);
  }
    
  inline void open(const char* name, 
            std::ios_base::openmode mode = std::ios::out) {
    stream.open(name, mode);
  }
  
  inline void close() {
    stream.close();
  }
  
  inline bool good() const {
    return stream.good();
  }

  inline bool fail() const {
    return stream.fail();
  }
};

/**
 * Output gzip binary stream class. 
 * Supports writing of binary gziped files. 
 * 
 * @note If the compiler cannot find the correct operator \c <<,
 *       try casting your object of this class to \c (NICE::obinstream&).
 *       However, this is NOT a good idea in combination with
 *       \c NICE::IOStreamable (which is deprecated)!
 * 
 * @author Frank Mattern, Ferid Bajramovic
 */
class ogzbinstream : public NICE::obinstream {
private:
  ogzstream stream;
  
public:
  ogzbinstream() {}
  
  ogzbinstream( const char* name, int mode = std::ios::out)
      : stream(name, mode) {}
  
  //gzstreambuf* rdbuf() { return gzstreambase::rdbuf(); }

  virtual void write(char* data, unsigned int length) {
    stream.write(data, length);
  }
    
  inline void open(const char* name, 
            std::ios_base::openmode open_mode = std::ios::out) {
    stream.open(name, open_mode);
  }
  
  inline void close() {
    stream.close();
  }
  
  inline bool good() const {
    return stream.good();
  }
  
  inline bool fail() const {
    return stream.fail();
  }
};

} // namespace

#else // NICE_USELIB_ZLIB
namespace NICE{
  typedef ifbinstream igzbinstream;
  typedef ofbinstream ogzbinstream;
} // namespace
#endif // NICE_USELIB_ZLIB
#endif // GZBINSTREAM_H
