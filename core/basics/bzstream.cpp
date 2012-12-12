// ============================================================================
// bzstream, C++ iostream classes wrapping the zlib compression library.
// Copyright (C) 2001  Deepak Bandyopadhyay, Lutz Kettner
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
// File          : bzstream.C
// Revision      : $Revision: 1.2 $
// Revision_date : $Date: 2009/05/28 11:36:30 $
// Author(s)     : Deepak Bandyopadhyay, Lutz Kettner
// 
// Standard streambuf implementation following Nicolai Josuttis, "The 
// Standard C++ Library".
// ============================================================================

#include <core/basics/bzstream.h>
#ifdef NICE_USELIB_BZLIB
#include <iostream>
#include <string.h>  // for memcpy

namespace NICE {

// ----------------------------------------------------------------------------
// Internal classes to implement bzstream. See header file for user classes.
// ----------------------------------------------------------------------------

// --------------------------------------
// class bzstreambuf:
// --------------------------------------

bzstreambuf* bzstreambuf::open( const char* name, int open_mode) {
    if ( is_open())
        return (bzstreambuf*)0;
    mode = open_mode;
    // no append nor read/write mode
    if ((mode & std::ios::ate) || (mode & std::ios::app)
        || ((mode & std::ios::in) && (mode & std::ios::out)))
        return (bzstreambuf*)0;
    char  fmode[10];
    char* fmodeptr = fmode;
    if ( mode & std::ios::in)
        *fmodeptr++ = 'r';
    else if ( mode & std::ios::out)
        *fmodeptr++ = 'w';
    *fmodeptr++ = 'b';
    *fmodeptr = '\0';
    file = 0; 
    file = BZ2_bzopen( name, fmode);
    if (file == 0)
        return (bzstreambuf*)0;
    opened = 1;
    return this;
}

bzstreambuf * bzstreambuf::close() {
    if ( is_open()) {
        sync();
        opened = 0;
        BZ2_bzclose(file);
        return this;
    }
    return (bzstreambuf*)0;
}

int bzstreambuf::underflow() { // used for input buffer only
    if ( gptr() && ( gptr() < egptr()))
        return * reinterpret_cast<unsigned char *>( gptr());

    if ( ! (mode & std::ios::in) || ! opened)
        return EOF;
    // Josuttis' implementation of inbuf
    int n_putback = gptr() - eback();
    if ( n_putback > 4)
        n_putback = 4;
    memcpy( buffer + (4 - n_putback), gptr() - n_putback, n_putback);

    int num = 0; 
    num = BZ2_bzread( file, buffer+4, bufferSize-4);
    if (num <= 0) // ERROR or EOF
        return EOF;

    // reset buffer pointers
    setg( buffer + (4 - n_putback),   // beginning of putback area
          buffer + 4,                 // read position
          buffer + 4 + num);          // end of buffer

    // return next character
    return * reinterpret_cast<unsigned char *>( gptr());    
}

int bzstreambuf::flush_buffer() {
    // Separate the writing of the buffer from overflow() and
    // sync() operation.
    int w = pptr() - pbase();
    if ( BZ2_bzwrite( file, pbase(), w) != w)
        return EOF;
    pbump( -w);
    return w;
}

int bzstreambuf::overflow( int c) { // used for output buffer only
    if ( ! ( mode & std::ios::out) || ! opened)
        return EOF;
    if (c != EOF) {
        *pptr() = c;
        pbump(1);
    }
    if ( flush_buffer() == EOF)
        return EOF;
    return c;
}

int bzstreambuf::sync() {
    // Changed to use flush_buffer() instead of overflow( EOF)
    // which caused improper behavior with std::endl and flush(),
    // bug reported by Vincent Ricard.
    if ( pptr() && pptr() > pbase()) {
        if ( flush_buffer() == EOF)
            return -1;
    }
    return 0;
}

// --------------------------------------
// class bzstreambase:
// --------------------------------------

bzstreambase::bzstreambase( const char* name, int mode) {
    init( &buf);
    open( name, mode);
}

bzstreambase::~bzstreambase() {
    buf.close();
}

void bzstreambase::open( const char* name, int open_mode) {
    if ( ! buf.open( name, open_mode))
        clear( rdstate() | std::ios::badbit);
}

void bzstreambase::close() {
    if ( buf.is_open())
        if ( ! buf.close())
            clear( rdstate() | std::ios::badbit);
}

} // namespace

#else
#warning "bzstream will not be compiled." 
#endif

// ============================================================================
// EOF //
