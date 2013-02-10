/** 
* @file FileMgt.cpp
* @brief Misc file management utilities
* @author Erik Rodner
* @date 10/26/2007

i*/
#include <stdlib.h>

#ifdef WIN32
#include <process.h>
#else
#include <unistd.h>
#include <sys/file.h>
#endif

#include <sys/types.h>    // For stat()
#include <sys/stat.h>     // For stat()

#include <iostream>
#include <algorithm>

#include "FileMgt.h"

#include "ossettings.h"
#include "StringTools.h"

#include <errno.h>
#include <string.h>

using namespace NICE;

using namespace std;
using namespace NICE;


void FileMgt::DirectoryRecursive ( std::vector<string> & files, const std::string & dir )
{	
#ifndef WIN32
	std::string command = "find -L \"" + dir + "\" -type f";
	//cerr << "FileMgt::DirectoryRecursive: find command (" << command << ")" << endl;

	FILE *pipe = popen ( command.c_str(), "r" );
	//cerr << "FileMgt::DirectoryRecursive: popen issued !" << endl;
	if ( pipe == NULL ) {
    int errsv = errno; //just to be sure that the writing on std::cerr does not change the errno
		cerr << "FileMgt::DirectoryRecursive: find command failed (" << command << ")" << endl;
    std::cerr << "FileMgt::DirectoryRecursive: popen error message is " << strerror(errsv) << std::endl;
		return;
	}
	char line[MAXLINESIZE];

	while (! feof(pipe) )
	{
	    if ( fgets ( line, MAXLINESIZE, pipe ) == NULL )
                  break;

	    std::string line_stl ( line );
		
	    line_stl = StringTools::chomp (line_stl);  

	    files.push_back ( line_stl );
	}

	pclose ( pipe );

	std::sort ( files.begin(), files.end() );
#else
	#pragma message WARNING("FileMgt::DirectoryRecursive() : Function not yet ported for platform WIN")
	fthrow ( Exception, "FileMgt::DirectoryRecursive() : Function not yet ported for platform WIN");
#endif
}
	
std::string FileMgt::createTempFile ( const std::string & templatefn )
{
#ifndef WIN32
    int max_iterations = 1024;
    int iteration = 0;
    char fn[1024];
    char subst[1024];
	int pid = (int)getpid();
    struct stat statbuf;
    int statval = -1;
    int fd = -1;

    //srand(time(NULL));

    do {
		long id = rand() % 1000000000;
		snprintf( subst, 1023, "%04d_%010ld", pid, id );
		snprintf( fn, 1023, templatefn.c_str(), subst );
		statval = stat( fn, &statbuf );
		iteration++;

		if ( statval != 0 )
		{
			fd = creat (fn, 0600 );
			close(fd);
		}
		
	} while ( (fd < 0) && (iteration < max_iterations) );

	if ( fd < 0 ) 
	{
		string errormessage = "FileMgt::createTempFile: FATAL ERROR unable to create temporary filename with template "+templatefn+".\n";
		fprintf (stderr, errormessage.c_str());
		throw (errormessage.c_str());
	}

    return string(fn);
#else
	#pragma message WARNING("FileMgt::createTempFile() : Function not yet ported for platform WIN")
	fthrow ( Exception, "FileMgt::createTempFile() : Function not yet ported for platform WIN");
#endif
}
	
void FileMgt::deleteTempFile ( const std::string & tempfile )
{
#ifdef WIN32
    if ( _unlink(tempfile.c_str()) != 0 )
#else
	if ( unlink(tempfile.c_str()) != 0 )
#endif
    {
		string errormessage = "FileMgt::deleteTempFile: FATAL ERROR removing "+tempfile+".\n";
		fprintf (stderr, errormessage.c_str());
		throw (errormessage.c_str());
    }
}

bool FileMgt::fileExists ( const std::string & file )
{
    struct stat info;
    int result = stat ( file.c_str(), &info );

    return ( result == 0 );
}
