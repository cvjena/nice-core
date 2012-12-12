/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libfbasics - library of some basic tools
 * See file License for license information.
 */
#include "core/basics/stringutils.h"
#include <core/basics/types.h>

namespace NICE {
  
std::string itostr(int integer)
{
    std::string s;
    if(integer<0) {
        integer=-integer;
        s="-";
    }
    int k=integer;
    int div=1;
    while(k>9) {
        k/=10;
        div*=10;
    }
    while(div>0) {
        s += ((integer/div)%10+48);
        div/=10;
    }
    return s;
}

std::vector<std::string> splitString(const std::string &s, char separator) {
  std::vector<std::string> result;
  splitString(s, separator, result);
  return result;
}

void splitString(const std::string &s, char separator,
                 std::vector<std::string>& result)
{
  int lastpos=0;
  int pos=0;
  while(pos!=-1) {
    pos = s.find_first_of(separator,lastpos);
    result.push_back(s.substr(lastpos,pos-lastpos));
    lastpos=pos+1;
  }
}

std::vector<std::vector<std::string> > splitStringVector(
                                         const std::vector<std::string> &inlist,
                                         char separator)
{
  std::vector<std::vector<std::string> > outlist(inlist.size());
  for(uint i=0;i<inlist.size();i++) {
    splitString(inlist[i], separator, outlist[i]);
//    int lastpos=0;
//    int pos=0;
//    while(pos!=-1) {
//        pos = inlist[i].find_first_of(separator,lastpos);
//        outlist[i].push_back(inlist[i].substr(lastpos,pos-lastpos));
//        lastpos=pos+1;
//    }
  }
  return outlist;
}

std::string replaceChar(const std::string& s, char oldChar, char newChar) {
  std::string result(s);
  for (uint i = 0; i < s.size(); ++i) {
    if (result[i] == oldChar) {
      result[i] = newChar;
    }
  }
  return result;
}

} // namespace
