
#include <iostream>
#include <core/image/ImageT.h>

using namespace NICE;
using namespace std;

int main ( int argc, char **argv )
{
	cout << "converting and cropping (not resizing!) tool (c) Erik Rodner, 2011" << endl;
	if ( (argc != 3) && (argc != 5) ) {
		cerr << "usage: " << argv[0] << " <src> <dst> [width] [height]" << endl;
		exit(-1);
	} 

	ColorImage src ( argv[1] );

	if ( argc == 3 ) 
	{
		src.write(argv[2]);
	} else {
		int xsize = std::min( atoi(argv[3]), src.width() );
		int ysize = std::min( atoi(argv[4]), src.height() );

		src.createSubImage(Rect(0,0,xsize,ysize))->write ( argv[2] );
	}
}
