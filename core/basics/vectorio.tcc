/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libfbasics - library of some basic tools
 * See file License for license information.
 */
#include "core/basics/vectorio.h"
#include <sstream>
#include "core/basics/Exception.h"

namespace NICE {
  
template<class T>
std::ostream& operator << (std::ostream& output, const std::vector<T>& v) {
  output << "< ";
  for (unsigned int i = 0; i < v.size(); i++) {
    output << v[i] << " ";
  }
  output << ">";
  return output;
}

template<class T>
void writeVectorHumanReadable(std::ostream& output, const std::vector<T>& v) {
  output << "<" << std::endl;
  for (unsigned int i = 0; i < v.size(); i++) {
    output << v[i] << std::endl;
  }
  output << ">";
}

template<class T>
std::istream& operator >> (std::istream& input, std::vector<T>& v) {
  char c;
  input >> c;
  if (c != '<') {
    input.putback ( c );

    int dataSize;
    // try to read the size, and do not care about
    input >> dataSize;

    input >> c;
    
    bool AwA (true); // animals with attribues come along with features directly written into the file, without size or brackets
    if ( (c != '<' ) && AwA)
    { 
     input.putback(c);
//     input.putback(dataSize); // there is always a nasty white-space at the beginning
    }
    else if ( c != '<' )
    {
      fthrow(Exception, "syntax error reading vector");      
    }
  }
  while (true) {
    char c = '\0';
    input >> c;
    if (c == '>' || input.eof()) {
      break;
      // FIXME check if end of stream or followed by whitespace
    }
    input.putback(c);
//     std::string s;
//     input >> s;
//     if (s == ">") {
//       break;
//     }
//     std::stringstream st(s);
//     T x;
//     st >> x;
    T x;
    input >> x;
    v.push_back(x);
  }
  return input;
}

template<class T>
std::ostream& operator << (std::ostream& output, const std::vector<T*>& v) {
  output << "< ";
  for (unsigned int i = 0; i < v.size(); i++) {
    output << *(v[i]) << " ";
  }
  output << ">";
  return output;
}

template<class T>
void writeVectorHumanReadable(std::ostream& output, const std::vector<T*>& v) {
  output << "<" << std::endl;
  for (unsigned int i = 0; i < v.size(); i++) {
    output << *(v[i]) << std::endl;
  }
  output << ">";
}

template<class T>
std::istream& operator >> (std::istream& input, std::vector<T*>& v) {
  char c;
  input >> c;
  if (c != '<') {
    fthrow(Exception, "syntax error reading vector");
  }
  while (true) {
    std::string s;
    input >> s;
    if (s == ">") {
      break;
    }
    std::stringstream st(s);
    T* x = new T();
    st >> *x;
    v.push_back(x);
  }
  return input;
}


} // namespace
