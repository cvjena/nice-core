/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libfbasics - library of some basic tools
 * See file License for license information.
 */
#ifndef _FBASICS_TOOLS_H
#define _FBASICS_TOOLS_H

#include <core/basics/numerictools.h>
#include <vector>
#include <string>
#include <ostream>

#define UNUSED_PARAMETER(parameter) {(void)parameter;};

namespace NICE {

/**
 * Delete elements in an STL container in the range [begin, end).
 */
template<class T>
void deleteElements(const T& begin, const T& end) {
  for (T iter = begin; iter != end; ++iter) {
    delete *iter;
  }
}

/**
 * Output a string matrix as latex tabular on an \c std::ostream.
 * @param out target stream
 * @param data data matrix, row major (a list of lines, each has columns)
 */
void writeLatexTabular(std::ostream& out,
                       std::vector<std::vector<std::string> >& data,
                       bool heading = false,
                       bool hlines = false,
                       bool vlines = false);

};

#endif // _FBASICS_TOOLS_H
