// ============================================================================
// bzstream, C++ iostream classes wrapping the zlib compression library.
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
// File          : bzstream.h
// Revision      : $Revision: 1.2 $
// Revision_date : $Date: 2009/05/28 11:36:30 $
// Author(s)     : Deepak Bandyopadhyay, Lutz Kettner, Frank Mattern
// 
// Standard streambuf implementation following Nicolai Josuttis, "The 
// Standard C++ Library".
// ============================================================================


#ifndef BZSTREAM_H
#define BZSTREAM_H 1


#ifdef NICE_USELIB_BZLIB
// standard C++ with new header file names and std:: namespace
#include <iostream>
#include <fstream>
#include <bzlib.h>

namespace NICE{

// ----------------------------------------------------------------------------
// Internal classes to implement bzstream. See below for user classes.
// ----------------------------------------------------------------------------

class bzstreambuf : public std::streambuf {
private:
    static const int bufferSize = 47+256;    // size of data buff
    // totals 512 bytes under g++ for ibzstream at the end.

    BZFILE      *file;               // file handle for compressed file
    char             buffer[bufferSize]; // data buffer
    char             opened;             // open/close state of stream
    int              mode;               // I/O mode

    int flush_buffer();
public:
    bzstreambuf() : opened(0) {
        setp( buffer, buffer + (bufferSize-1));
        setg( buffer + 4,     // beginning of putback area
              buffer + 4,     // read position
              buffer + 4);    // end position      
        // ASSERT: both input & output capabilities will not be used together
    }
    int is_open() { return opened; }
    bzstreambuf* open( const char* name, int open_mode);
    bzstreambuf* close();
    ~bzstreambuf() { close(); }
    
    virtual int     overflow( int c = EOF);
    virtual int     underflow();
    virtual int     sync();
};

class bzstreambase : virtual public std::ios {
protected:
    bzstreambuf buf;
public:
    bzstreambase() { init(&buf); }
    bzstreambase( const char* name, int open_mode);
    ~bzstreambase();
    void open( const char* name, int open_mode);
    void close();
    bzstreambuf* rdbuf() { return &buf; }
};

// ----------------------------------------------------------------------------
// User classes. Use ibzstream and obzstream analogously to ifstream and
// ofstream respectively. They read and write files based on the bz* 
// function interface of the zlib. Files are compatible with bzip compression.
// ----------------------------------------------------------------------------

/**
 * Input bzip stream class. 
 * Supports reading of bzip files. 
 * 
 * @author Deepak Bandyopadhyay, Lutz Kettner, Frank Mattern 
 */
class ibzstream : public bzstreambase, public std::istream {
public:
    ibzstream() : std::istream( &buf) {} 
    ibzstream( const char* name, int open_mode = std::ios::in)
        : bzstreambase( name, open_mode), std::istream( &buf) {}  
    bzstreambuf* rdbuf() { return bzstreambase::rdbuf(); }
    void open( const char* name, int open_mode = std::ios::in) {
        bzstreambase::open( name, open_mode);
    }
};

/**
 * Output bzip stream class. 
 * Supports writing of bzip files. 
 * 
 * @author Deepak Bandyopadhyay, Lutz Kettner, Frank Mattern 
 */
class obzstream : public bzstreambase, public std::ostream {
public:
    obzstream() : std::ostream( &buf) {}
    obzstream( const char* name, int mode = std::ios::out)
        : bzstreambase( name, mode), std::ostream( &buf) {}  
    bzstreambuf* rdbuf() { return bzstreambase::rdbuf(); }
    void open( const char* name, int open_mode = std::ios::out) {
        bzstreambase::open( name, open_mode);
    }
};

} // namespace

#endif
#endif // BZSTREAM_H
// ============================================================================
// EOF //

