/**
* @file FileMgt.h
* @brief Misc file management utilities
* @author Erik Rodner
* @date 10/26/2007
*/
#ifndef FILEMGTINCLUDE
#define FILEMGTINCLUDE

#include <vector>
#include <string>


namespace NICE {

/** @brief Misc file management utilities */
class FileMgt
{

  protected:

  public:

    /** collect all files in a directory (including all subdirectories
        @param files resulting list of files
        @param dir input directory
    */
    static void DirectoryRecursive ( std::vector<std::string> & files, const std::string & dir );

    /** create a temporary file using a template prefix
        @param templatefn template prefix of the temporary filename
        @return generated temporary filename
    */
    static std::string createTempFile ( const std::string & templatefn );

    /** delete a temporary filename
        @param tempfile name of the file which will be deleted
    */
    static void deleteTempFile ( const std::string & tempfile );

    /** returns true if a file exists
        @param file input filename
        @return true if the file exists
    */
    static bool fileExists ( const std::string & file );

};


} // namespace

#endif
