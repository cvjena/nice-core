#ifndef STRINGUTILS_H
#define STRINGUTILS_H
/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libfbasics - library of some basic tools
 * See file License for license information.
 */

#include <vector>
#include <string>

namespace NICE  {

/** Convert the integer "integer" into a string.
 * @param integer integer to convert
 * @return string the integer string
 * @deprecated see numerictools.h
 **/
std::string itostr(int integer);

/** Split the string \c s into a vector of strings.
  * @param s input string
  * @param separator character to separate the string
  * @return vector of strings
 **/
std::vector<std::string> splitString(const std::string &s, char separator);

/** Split the string \c s into a vector of strings.
  * @param s input string
  * @param separator character to separate the string
  * @param result vector of strings
 **/
void splitString(const std::string &s, char separator,
                 std::vector<std::string>& result);

/** Split the vector of strings \c inlist to a vector of vector of strings.
  * @param inlist input list of strings
  * @param separator character to separate the strings
  * @return vector of vector of strings
 **/
std::vector<std::vector<std::string> > splitStringVector(
                                         const std::vector<std::string> &inlist,
                                         char separator);

/**
 * Replace a certain character in a string (all occurences).
 */
std::string replaceChar(const std::string& s, char oldChar, char newChar);
  
} // namespace

#endif // STRINGUTILS_H
