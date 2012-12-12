#include <iostream>
#include <core/image/ImageT.h>
#include <core/basics/Timer.h>

using namespace NICE;
using namespace std;

int main ( int argc, char **argv )
{
	if ( argc != 3 ) {
		cerr << "usage: " << argv[0] << " <src1> <src2>" << endl;
		exit(-1);
	}

	Image src1 ( argv[1] );
	Image src2 ( argv[2] );
	if ( (src1.width() != src2.width()) || (src1.height() != src2.height()) ) {
		cerr << "Images differ in size!" << endl;
		exit(-1);
	}

  Timer t;
  t.start();
	double l1error = 0.0;
	for ( int y = 0 ; y < src1.height(); y++ )
		for ( int x = 0 ; x < src1.width(); x++ )
			l1error += abs( src1(x,y) - src2(x,y) );

	l1error /= src1.height() * src1.width();
  t.stop();
	
	cerr << "Average pixel difference: " << l1error << endl;
  cerr << "Time used for comparision: " << t.getLast() << endl;

}
