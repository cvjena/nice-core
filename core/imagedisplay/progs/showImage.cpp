/**
* @file showImage.cpp
* @brief simple image viewer, a hello world program for NICE
* @author Erik Rodner
* @date 11/16/2011
*/
#include "core/basics/Exception.h"
using namespace NICE;
using namespace std;

#ifdef NICE_USELIB_QT
#ifdef NICE_USELIB_GLUT
#include "core/imagedisplay/ImageDisplay.h"


/**
    simple image viewer
*/
int main ( int argc, char **argv )
{
  std::set_terminate ( __gnu_cxx::__verbose_terminate_handler );

  for ( int i = 1 ; i < argc ; i++ )
  {
    ColorImage img ( argv[i] );
    showImage ( img );
  }

  return 0;
}
#else
#warning "showImage only works with GLUT"
int main ( void ) {
  fthrow ( Exception, "Please install the GLUT development files..." );
}
#endif
#else
#warning "showImage only works with Qt"
int main ( void ) {
  fthrow ( Exception, "Please install the Qt development files..." );
}
#endif
