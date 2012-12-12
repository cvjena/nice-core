// ============================================================================
// binstream, C++ iostream classes for binary in and output 
// Copyright (C) 2006 Frank Mattern 
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
// File          : binstream.h
// Revision      : $Revision: 1.3 $
// Revision_date : $Date: 2011/10/18 14:15:29 $
// Author(s)     : Frank Mattern 
// 
// ============================================================================


#ifndef BINSTREAM_H
#define BINSTREAM_H 1


// standard C++ with new header file names and std:: namespace
#include <iostream>
#include <fstream>
#include <vector>
#include <core/basics/types.h>
#include <string.h>
#ifdef NICE_USELIB_LINAL
#include <cstddef>
#include "LinAl/matrix.h"
#endif

namespace NICE {

// ----------------------------------------------------------------------------
// User classes. Use ibinstream and obinstream analogously to ifstream and
// ofstream respectively. They read and write files based in a binary fashion.
// ----------------------------------------------------------------------------

/**
 * Input binary stream class. 
 * 
 * @author Frank Mattern, Ferid Bajramovic
 */
class ibinstream {
public:
  virtual void read(char* data, unsigned int length) = 0;
  virtual ~ibinstream() {}
  
  ibinstream &operator>>(bool &n) { 
    read((char*) &n, sizeof(bool)); return *this;
  }
  ibinstream &operator>>(int &n) { 
    read((char*) &n, sizeof(int)); return *this; 
  }
  ibinstream &operator>>(unsigned int &n) {
    read((char*) &n, sizeof(unsigned int)); return *this;
  }
  ibinstream &operator>>(char &n) {
    read((char*) &n, sizeof(char)); return *this;
  }
  ibinstream &operator>>(signed char &n) {
    read((char*) &n, sizeof(signed char)); return *this; 
  }
  ibinstream &operator>>(unsigned char &n) {
    read((char*) &n, sizeof(unsigned char)); return *this; 
  }
  ibinstream &operator>>(short &n) {
    read((char*) &n, sizeof(short)); return *this;
  }
  ibinstream &operator>>(unsigned short &n) {
    read((char*) &n, sizeof(unsigned short)); return *this;
  }
  ibinstream &operator>>(long &n) { 
    read((char*) &n, sizeof(long)); return *this;
  }
  ibinstream &operator>>(unsigned long &n) {
    read((char*) &n, sizeof(unsigned long)); return *this;
  }
  ibinstream &operator>>(long long &n) {
    read((char*) &n, sizeof(long long)); return *this; 
  }
  ibinstream &operator>>(unsigned long long &n) { 
    read((char*) &n, sizeof(unsigned long long)); return *this; 
  }
  ibinstream &operator>>(float &n) {
    read((char*) &n, sizeof(float)); return *this; 
  }
  ibinstream &operator>>(double &n) {
    read((char*) &n, sizeof(double)); return *this; 
  }
  ibinstream &operator>>(long double &n) {
    read((char*) &n, sizeof(long double)); return *this; 
  }
  ibinstream &operator>>(char *n) {
    int l=0; read((char*) &l, sizeof(int));  read((char*) n, l); return *this; 
  }
  
  ibinstream &operator>>(std::string &n) {
    int l=0;
    read((char*) &l, sizeof(int));
    char buf[l];
    read((char*) buf, l);
    n.assign(buf,l);
    return *this;
  }
  
  template<class T>
  ibinstream &operator>>(std::vector<T> &n) { 
    int l=0;
    read((char*) &l, sizeof(int));
    n.resize(l); 
    for(uint i=0;i<n.size();i++)
      (*this) >> n[i];
    return *this; 
  }
};

/**
 * Output binary stream class. 
 * 
 * @author Frank Mattern, Ferid Bajramovic
 */
class obinstream {
public:
  virtual void write(char* data, unsigned int length) = 0;
  virtual ~obinstream() {}
  
  obinstream &operator<<(bool n) { 
    write((char*) &n, sizeof(bool)); return *this; 
  }
  obinstream &operator<<(int n) {
    write((char*) &n, sizeof(int)); return *this; 
  }
  obinstream &operator<<(unsigned int n) {
    write((char*) &n, sizeof(unsigned int)); return *this; 
  }
  obinstream &operator<<(char n) {
    write((char*) &n, sizeof(char)); return *this; 
  }
  obinstream &operator<<(signed char n) {
    write((char*) &n, sizeof(signed char)); return *this; 
  }
  obinstream &operator<<(unsigned char n) {
    write((char*) &n, sizeof(unsigned char)); return *this; 
  }
  obinstream &operator<<(short n) { 
    write((char*) &n, sizeof(short)); return *this; 
  }
  obinstream &operator<<(unsigned short n) {
    write((char*) &n, sizeof(unsigned short)); return *this; 
  }
  obinstream &operator<<(long n) {
    write((char*) &n, sizeof(long)); return *this; 
  }
  obinstream &operator<<(unsigned long n) {
    write((char*) &n, sizeof(unsigned long)); return *this; 
  }
  obinstream &operator<<(long long n) {
    write((char*) &n, sizeof(long long)); return *this; 
  }
  obinstream &operator<<(unsigned long long n) {
    write((char*) &n, sizeof(unsigned long long)); return *this; 
  }
  obinstream &operator<<(float n) {
    write((char*) &n, sizeof(float)); return *this; 
  }
  obinstream &operator<<(double n) {
    write((char*) &n, sizeof(double)); return *this; 
  }
  obinstream &operator<<(long double n) {
    write((char*) &n, sizeof(long double)); return *this;
  }
    
  obinstream &operator<<(const char *n) { 
    int l=(int)strlen(n)+1;
    write((char*) &l, sizeof(int));
    write((char*) n, l);
    return *this;
  }
  
  obinstream &operator<<(const std::string &n) {
    int l=(int)n.size();
    write((char*) &l, sizeof(int));
    write((char*) n.c_str(), l);
    return *this;
  }
  
  template<class T>
  obinstream &operator<<(const std::vector<T> &n) { 
    int l=n.size(); 
    write((char*) &l, sizeof(int)); 
    for(uint i=0;i<n.size();i++)
      *this << n[i];
    return *this; 
  }
};

/**
 * Input binary stream class, reading from binary files.
 * 
 * @author Frank Mattern, Ferid Bajramovic
 */
class ifbinstream : public ibinstream {
private:
  std::ifstream stream;
public:
  ifbinstream() {} 
  ifbinstream(const char* name, 
              std::ios_base::openmode open_mode = std::ios::in)
      : stream(name, open_mode) {}

  virtual void read(char* data, unsigned int length) {
    stream.read(data, length);
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

/**
 * Output binary stream class, writing to binary files.
 * 
 * @author Frank Mattern, Ferid Bajramovic
 */
class ofbinstream : public obinstream {
private:
  std::ofstream stream;
public:
  ofbinstream() {}
  ofbinstream( const char* name,
               std::ios_base::openmode mode = std::ios::out|std::ios::binary)
      : stream(name, mode) {}

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


#ifdef NICE_USELIB_LINAL

template <class Tp>
inline ibinstream& operator>>(ibinstream& s, LinAl::Ref<Tp> r) {
  Tp i;
  s>>i;
  r=i;
  return s;
}

template <class Tp>
inline obinstream& operator<<(obinstream& s, const LinAl::Ref<Tp>& r) {
  s<<(Tp)r;
  return s;
}

template <class Tp>
inline ibinstream& operator>>(ibinstream& s, LinAl::MatrixC<Tp> &A) {
  int nrows, ncols;
  s >> nrows >> ncols;
  A.resize(nrows, ncols);
  for(int r = 0; r < nrows; r++)
    for(int c = 0; c < ncols; c++) {
        s >> A(r,c);
    }
  return s;
}

template <class Tp>
inline obinstream& operator<<(obinstream &s, const LinAl::MatrixC<Tp> &A) {
    s << A.nr() << A.nc();
    for(int i = 0; i < A.nr(); i++) {
      for(int j = 0; j < A.nc(); j++) {
          s << A(i,j);
      }
    }
  return s;
}

#else
#ifndef LINAL_WARNING
#warning LinAl addons will not be compiled.
#define LINAL_WARNING
#endif
#endif

 
} // namespace

#endif // BINSTREAM_H
