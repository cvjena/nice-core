/**
 * @file StringTools.h
 * @brief some string handling routines
 * @author Erik Rodner
 * @date 19.09.2007

 */
#ifndef STRINGTOOLSINCLUDE
#define STRINGTOOLSINCLUDE

#include <vector>
#include <string>
#include <sstream>

#include <core/vector/VectorT.h>

namespace NICE
{

/** @brief some string handling routines */
class StringTools
{
public:
    /** normalize the std::string value, remove leading and
     finishing whitespaces, tabulars, a finishing semicolon
     @param s input std::string which will be modified
     */
    static void normalize_string(std::string & s);

    /** split a std::string
     @param s input string
     @param splitChar character which was used for seperation
     @param list resulting list of sub strings
     */
    static void split(const std::string & s, char splitChar, std::vector<
                      std::string> & list);

    /** split a std::string and convert the strings to double values
     @param input std::string value
     @param splitChar character which was used as a seperation
     @param x resulting std::vector of double values
     */
    static void splitVector(const std::string & s, char splitChar,
                            NICE::Vector & x);

    /** remove a leading and a finishing character
     @param value input std::string value
     @param trimChar e.g.
     */
    static void trimbounds(std::string & value, char trimChar);

    /** chomp off the end-of-line characters
     @param s input and output string
     */
    static std::string chomp(std::string s);

    /** whatever */
    static std::string trim(std::string s, const std::string& drop = " ");

    /** trims the filename to be without directories, similar to basename in linux
     @param str input string
     @param extension specifies if output is with extension or not
     */
    static std::string baseName(const std::string& str, bool extension = true);

    /** perform regular expression matching and return true if the string \c s
     *  matches the regular expression in \c regex (GNU regex style!).
     */
    static bool regexMatch(const std::string & s, const std::string & regex);

    /** perform regular expression matching and return true if the string \c s
     *  matches the regular expression in \c regex (GNU regex style!),
     *  sub-pattern matches are stored in submatches and denoted with (...) in
     *  the regular expression.
     *  @note submatches[0] is the whole match and submatches[i] is the i'th sub-pattern match
     */
    static bool regexMatch(const std::string & s, const std::string & regex,
                           std::vector<std::string> & submatches);

    /** substitute a regular expression match with \c subst */
    static bool regexSubstitute(std::string & s, const std::string & regex,
                                const std::string & subst);

    /** convert a string to another type using stringstream */
    template<class F>
    static F convert(const std::string & s);

    /** convert a string to another type using stringstream and returning true on success and
     * false if there is a parsing error */
    template<class F>
    static bool convert(const std::string & s, F & i);

    /** convert another type to a string using stringstream */
    template<class F>
    static std::string convertToString(const F & s);

    /** convert another type to a string using stringstream */
    template<class F>
    static std::string convertToString(const F & s, uint precision);

};

// template implementations

template<class F>
F StringTools::convert(const std::string & s)
{
    std::istringstream is(s);
    F i;
    is >> i;
    return i;
}

template<class F>
bool StringTools::convert(const std::string & s, F & i)
{
    std::istringstream is(s);
    is >> i;
    return (!is.fail());
}

template<class F>
std::string StringTools::convertToString(const F & s)
{
    std::ostringstream os;
    os << s;
    return os.str();
}

template<class F>
std::string StringTools::convertToString(const F & s, uint precision)
{
    std::ostringstream os;
    os.precision(precision);
    os.setf(std::ios::fixed,std::ios::floatfield);
    os << s;
    return os.str();
}

} // namespace

#endif
