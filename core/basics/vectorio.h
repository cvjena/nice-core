/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libfbasics - library of some basic tools
 * See file License for license information.
 */
#ifndef _VECTORIO_H_
#define _VECTORIO_H_

#include <iostream>
#include <vector>

namespace NICE  {

/**
 * Output function.
 */
template<class T>
std::ostream& operator << ( std::ostream& output, const std::vector<T>& v );

/**
 * Output function.
 */
template<class T>
void writeVectorHumanReadable ( std::ostream& output, const std::vector<T>& v );

/**
 * Output function.
 */
template<class T>
void writeVectorOfPointers ( std::ostream& output, const std::vector<T*>& v );

/**
 * Output function.
 */
template<class T>
void writeVectorOfPointersHumanReadable ( std::ostream& output,
    const std::vector<T*>& v );

/**
 * Input function.
 * Format has to be as produced by
 * \c operator << (std::ostream& output, const std::vector<T>& v),
 * \c writeVectorHumanReadable(), \c writeVectorOfPointers()
 * or \c writeVectorOfPointersHumanReadable().
 * Note that no data element must begin with '>'.
 */
template<class T>
std::istream& operator >> ( std::istream& input, std::vector<T>& v );

/**
 * Input function. A new heap object will be created for each vector element
 * (Ownership given away.)
 * Format has to be as produced by
 * \c operator << (std::ostream& output, const std::vector<T>& v),
 * \c writeVectorHumanReadable(), \c writeVectorOfPointers()
 * or \c writeVectorOfPointersHumanReadable().
 */
template<class T>
void readVectorOfPointers ( std::istream& input, std::vector<T*>& v );

} // namespace

//#ifdef __GNUC__
#include "core/basics/vectorio.tcc"
//#endif

#endif //_VECTORIO_H_
