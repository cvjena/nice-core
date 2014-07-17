#include "core/basics/FileName.h"
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>

#include <sys/param.h> //for MAXPATHLEN - the maximal path length


using namespace std;

namespace NICE {

FileName::FileName() {
}

FileName::FileName(const std::string& _fileName)
    : fileName(_fileName) {
}

FileName::FileName(const char* _fileName)
    : fileName(_fileName) {
}

FileName::FileName(const FileName& _fileName)
    : fileName(_fileName.str()) {
}

FileName& FileName::operator=(const FileName& _fileName) {
  fileName = _fileName.str();
  return *this;
}

FileName& FileName::operator=(const std::string& _fileName) {
  fileName = _fileName;
  return *this;
}

FileName& FileName::operator=(const char* _fileName) {
  fileName = _fileName;
  return *this;
}

FileName::~FileName() {
}

const string& FileName::str() const {
  return fileName;
}

FileName::operator const std::string&() const {
  return str();
}

FileName::operator const char*() const {
  return str().c_str();
}

FileName FileName::extractPath() const {
  int pos = (int)fileName.find_last_of('/');
  if (pos < 0) {
    return FileName("");
  } else {
    return FileName(fileName.substr(0, pos + 1));
  }
}

FileName FileName::extractFileName() const {
  int pos = (int)fileName.find_last_of('/');
  if (pos < 0) {
    return FileName(fileName);
  } else {
    return FileName(fileName.substr(pos + 1));
  }
}

FileName FileName::extractExtension() const {
  int pos = (int)fileName.find_last_of('.');
  if (pos < 0) {
    return FileName("");
  } else {
    return FileName(fileName.substr(pos));
  }
}

void FileName::removeExtension() {
  int pos = (int)fileName.find_last_of('.');
  if (pos > 0) {
    fileName.erase(pos);
  }
}

void FileName::addSlash() {
  if (fileName.length() == 0) {
    return;
  }
  
  if (fileName[fileName.length() - 1] != '/') {
    fileName += "/";
  }
}

void FileName::removeSlash() {
  if (fileName[fileName.length() - 1] == '/') {
    fileName.erase(fileName.end() - 1);
  }
}

void FileName::setExtension(const std::string& extension) {
  if (extractExtension().str() != extension) {
    fileName += extension;
  }
}

bool FileName::fileExists() const {
  struct stat my_stat;
  return (stat(fileName.c_str(), &my_stat) == 0);
}

bool FileName::isDirectory() const {
  struct stat my_stat;
  if (stat(fileName.c_str(), &my_stat) != 0) {
    return false;
  } else {
    return ((my_stat.st_mode & S_IFDIR) != 0);
  }
}

void FileName::createDirectory() const {
  if (fileName.length() == 0) {
    return;
  }

  string command = string("mkdir -p ") + fileName;
  system(command.c_str());
}

void FileName::deleteFile() const {
    remove(fileName.c_str());
}

bool FileName::isRelative() const {
    if(fileName.empty())
        return false;

    return  fileName.substr(0,1) != "/";
}

bool FileName::convertToRealPath()
{
    char actualpath [MAXPATHLEN];
    char *pRet = realpath( fileName.c_str(), actualpath);

    //TODO: how to treat the return value???
//    if( pRet == NULL)
//        return false;

    this->fileName = string( actualpath);
    return true;
}

} // namespace
