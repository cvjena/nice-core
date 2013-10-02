/** demonstrations program for the image routines
 * in the nice/core library */

#include <iostream>
#include <core/image/ImageT.h>
#include <core/image/FilterT.h>

// QT Interface for image display
// We only use the simple function showImage in this example, but there is far more
// to explore in this area.
#ifdef NICE_USELIB_QT
#include <core/imagedisplay/ImageDisplay.h>
#endif

using namespace NICE;
using namespace std;

int main ( int argc, char **argv )
{
	if ( (argc != 2) ) {
		cerr << "usage: " << argv[0] << " <image>" << endl;
		exit(-1);
	} 

  // read a color image
	ColorImage srcColor ( argv[1] );

  // show the image and wait for the window being closed manually
#ifdef NICE_USELIB_GLUT
#ifdef NICE_USELIB_QT
  showImage ( srcColor );
#else
  cerr << "Visualization disabled: no QT library available" << endl;
#endif
#else 
  cerr << "Visualization disabled: no GLUT library available" << endl;
#endif

  // simple grayvalue image
  Image src;

  rgbToGray ( srcColor, &src ); 

  // convert the color image to a grayvalue image
  

  // first demonstration: some simple filters
  
  // using the FilterT interface
  FloatImage gradient;
  FilterT<unsigned char, float, float>::gradientStrength( src, gradient );
  ColorImage gradientColor;
  imageToPseudoColor ( gradient, gradientColor );

#ifdef NICE_USELIB_GLUT
#ifdef NICE_USELIB_QT
  showImage ( gradientColor );
#endif
#endif


}
