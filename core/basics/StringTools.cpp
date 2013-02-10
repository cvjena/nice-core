/** 
* @file StringTools.cpp
// refactor-nice.pl: check this substitution
// old: * @brief some string handling routines
* @brief some std::string handling routines
* @author Erik Rodner
* @date 19.09.2007

*/

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <assert.h>

#include "StringTools.h"

//#define USE_REGEX_LIB
#ifdef USE_REGEX_LIB
#include <regex.h>
#endif


#include "ossettings.h"

using namespace NICE;

using namespace std;

/** return base of a filename */
std::string StringTools::baseName(const std::string& str,bool extension)
{
     size_t begin = 0;
     size_t end = str.length() - 1;

     for (size_t i=0; i<str.length(); ++i) {
          if (str[i] == FILESEP) begin = i+1;
     }
     //leave extension iff true
     if (!extension)
     {
          for (size_t i=begin; i<str.length(); ++i) {
               if (str[i] == '.') end = i-1;
          }
     }
     return str.substr(begin,end - begin + 1);
}

void StringTools::normalize_string ( std::string & s )
{
    size_t j = 0;
    while ( (j < s.length()) &&
	    ((s[j] == ' ') || (s[j] == '\t') ) ) j++;
	
    int jj = s.length()-1;
    while ( (jj >= 0) &&
	    ((s[jj] == ' ') || (s[jj] == ';') ||
	     (s[jj] == '\t')) ) jj--;
   

    std::string news = "";

    for ( int k = j ; k <= jj ; k++ )
    {
	if ( s[k] != '\t' )
	    news.push_back (s[k]);
    }

    s = news;
}

void StringTools::split ( const std::string & s, char splitChar, vector<string> & list )
{
    size_t pos = 0;
    size_t oldpos = 0;

    while ( (pos = s.find(splitChar,oldpos)) != string::npos )
    {
	list.push_back ( s.substr(oldpos, pos-oldpos) );
	oldpos = pos+1;

	if ( oldpos >= s.length() ) break;
    }

    if ( oldpos < s.length() )
	list.push_back ( s.substr(oldpos) );

    for ( vector<string>::iterator i = list.begin(); i != list.end() ; i++ )
	normalize_string ( *i );
}
	
void StringTools::splitVector ( const std::string & s, char splitChar, NICE::Vector & x )
{
    size_t pos = 0;
    size_t oldpos = 0;
    vector<double> xdyn;

    double f;
    while ( (pos = s.find(splitChar,oldpos)) != string::npos )
    {
	stringstream sstr;
	sstr << s.substr(oldpos, pos-oldpos);
	sstr >> f;
	xdyn.push_back ( f );
	oldpos = pos+1;

	if ( oldpos >= s.length() ) break;
    }

    if ( oldpos < s.length() )
    {
	stringstream sstr;
	sstr << s.substr(oldpos);
	sstr >> f;
	xdyn.push_back(f);
    }

    x = NICE::Vector(xdyn);
}

void StringTools::trimbounds ( std::string & value, char trimChar )
{
    // remove "
    size_t pos1 = value.find(trimChar);
    size_t pos2 = value.rfind(trimChar);

    if ( (pos1 != pos2) && 
	 (pos1 != string::npos) &&
	 (pos2 != string::npos) )
    {
	value.erase( pos1, 1 );
	value.erase( pos2-1, 1 );
    }
}

/** @author Matti Bickel */
std::string StringTools::trim(string s, const std::string& drop)
{
    std::string r=s.erase(s.find_last_not_of(drop)+1);
    return r.erase(0,r.find_first_not_of(drop));
}

std::string StringTools::chomp(string s)
{
    return trim(trim(s, "\r"), "\n");
}

bool StringTools::regexSubstitute ( std::string & s, const std::string & regex, const std::string & subst )
{
#ifdef USE_REGEX_LIB
    vector<string> submatches;
    std::ostringstream os_regex;
    
    os_regex << "(.*)" << regex << "(.*)";
    bool ok = regexMatch ( s, os_regex.str(), submatches );

    if ( ! ok ) return false;

    assert ( submatches.size() >= 3 );

    std::string substc = subst;
    for ( uint k = 2 ; k < submatches.size()-1 ; k++ )
    {
		uint index = k - 1;
		std::ostringstream os;
		os << "\\" << index;
		size_t pos = subst.find(os.str());
		assert( pos != string::npos );
		substc.replace ( pos, 2, submatches[k] );
    }

    s = submatches[1] + substc + submatches[submatches.size()-1];

    return true;
#else
	fthrow ( Exception, "You have to install the regex lib to use this function!");
#endif
}

bool StringTools::regexMatch ( const string & s, const string & regex )
{
#ifdef USE_REGEX_LIB
    vector<string> submatches;
    return regexMatch ( s, regex, submatches );
#else
	fthrow ( Exception, "You have to install the regex lib to use this function!");
#endif
}

bool StringTools::regexMatch ( const string & s, const string & regex, 
			 vector<string> & submatches )
{
#ifdef USE_REGEX_LIB
	submatches.clear();

    int    status;
    regex_t    re;
    const int max_num_matches = 100;
    regmatch_t pmatch[max_num_matches];

    if (regcomp(&re, regex.c_str(), REG_EXTENDED) != 0) {
		fthrow ( Exception, "The regular expression <" << regex << "> is invalid.");
    }

    status = regexec(&re, s.c_str(), max_num_matches, pmatch, 0);

    if (status != 0) {
		regfree(&re);
        return false;
    }

    for (uint i = 0; !status && i <= re.re_nsub; i++)
    {
		char submatch[1024];
		strncpy (submatch, s.c_str() + pmatch[i].rm_so,
			pmatch[i].rm_eo - pmatch[i].rm_so);
	  	submatch[pmatch[i].rm_eo - pmatch[i].rm_so] = '\0';
		submatches.push_back(submatch);
    }
 
    regfree(&re);
    return true;
#else
	fthrow ( Exception, "You have to install the regex lib to use this function!");
#endif
}


