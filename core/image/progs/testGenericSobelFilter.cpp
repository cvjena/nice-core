#include <iostream>
#include <core/image/FilterT.h>
#include <core/basics/Timer.h>

using namespace NICE;
using namespace std;

#define DATATYPE double
//#define DATATYPE_UCHAR

int main ( int argc, char **argv )
{
  if ( argc != 2 ) {
    cerr << "usage: " << argv[0] << " <img>" << endl;
    exit ( -1 );
  }

  Image img_uchar ( argv[1] );
  ImageT<DATATYPE> img ( img_uchar.width(), img_uchar.height() );

  for ( int y = 0; y < img.height(); y++ )
    for ( int x = 0; x < img.width(); x++ )
      img.setPixel ( x, y, ( DATATYPE ) img_uchar.getPixel ( x, y ) );

  ImageT<double> sobelResult ( img.width(), img.height() );
  sobelResult.set ( 0 );

  bool write_result = true;
  
  FilterT<DATATYPE,double,double>::gradientStrength(img, sobelResult);
  
  DATATYPE minval = numeric_limits<double>::max();
  DATATYPE maxval = -numeric_limits<double>::max();
  
  for ( int y = 0; y < img.height(); y++ )
    for ( int x = 0; x < img.width(); x++ )
    {
      img_uchar(x,y) = (uint)std::min(sobelResult(x,y),255.0);
      minval = min(minval, sobelResult(x,y));
      maxval = max(maxval, sobelResult(x,y));
    }
  
  cout << "maxval: " << maxval << " minval: " << minval << endl;
  
  if ( write_result )
  {
    img_uchar.write ( "sobel.pgm" );
  }

  return 0;
}
