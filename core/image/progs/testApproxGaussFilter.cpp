#include <iostream>
#include <core/image/Filter.h>
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

  ImageT<DATATYPE> gaussResult ( img.width(), img.height() );
  ImageT<DATATYPE> gaussResultApprox ( img.width(), img.height() );
  gaussResult.set ( 0 );
  gaussResultApprox.set ( 0 );

  bool verbose = false;
  bool evaluate_mean_filter = false;
  bool write_last_result = false;

  // ignore the following boundary when calculating the error
  const int boundary = 120;
  const int max_filtersize = 100;

  // TODO: derive a formula for the error of the approximate Gaussian filter
  // by using the Berry-Esseen Theorem
  int numRuns = 1;
  for ( int filtersize = 1 ; filtersize < max_filtersize ; filtersize++ )
  {
    // values used by Björn 3.2 .. 9.6
    double sigma = 3.2 + ( 9.6 - 3.2 ) * ( filtersize - 1 ) / max_filtersize;
    Timer t;
    if ( verbose )
      cerr << "Applying standard filter" << endl;
    t.start();
    for ( int i = 0 ; i < numRuns ; i++ )
      if ( evaluate_mean_filter )
#ifdef DATATYPE_UCHAR
        filterMean<unsigned char, int> ( img, filtersize, &gaussResult );
#else
        filterMean<DATATYPE, DATATYPE> ( img, filtersize, &gaussResult );
#endif
      else
#ifdef DATATYPE_UCHAR
        filterGaussSigma<unsigned char, int> ( img, sigma, &gaussResult );
#else
        filterGaussSigma<DATATYPE, DATATYPE> ( img, sigma, &gaussResult );
#endif
    t.stop();

    double timeStandard = t.getLast();
    if ( verbose )
      cerr << "Result: " << timeStandard << endl;

    if ( verbose )
      cerr << "Applying fast filter" << endl;
    t.reset();
    t.start();
    for ( int i = 0 ; i < numRuns ; i++ )
      if ( evaluate_mean_filter )
#ifdef DATATYPE_UCHAR
        filterMeanLargeFS<unsigned char, int, unsigned char> ( img, filtersize, &gaussResultApprox );
#else
        filterMeanLargeFS<DATATYPE, DATATYPE, DATATYPE> ( img, filtersize, &gaussResultApprox );
#endif
      else
#ifdef DATATYPE_UCHAR
        filterGaussSigmaApproximate<unsigned char, int, int> ( img, sigma, &gaussResultApprox );
#else
        filterGaussSigmaApproximate<DATATYPE, DATATYPE, DATATYPE> ( img, sigma, &gaussResultApprox );
#endif
    t.stop();

    double timeApprox = t.getLast();

    if ( verbose ) {
      cerr << "Result: " << timeApprox << endl;
      cerr << "Computing error" << endl;
    }

    double err = 0.0;
    for ( int y = boundary ; y < img.height() - boundary; y++ )
    {
      for ( int x = boundary ; x < img.width() - boundary; x++ )
      {
        err += fabs ( gaussResult.getPixel ( x, y ) - gaussResultApprox.getPixel ( x, y ) );
      }
    }

    err /= ( ( img.height() - 2 * boundary ) * ( img.width() - 2 * boundary ) );

    if ( verbose )
      cerr << "Error: " << err << endl;

    if ( evaluate_mean_filter )
      cerr << filtersize << " " << timeStandard << " " << timeApprox << " " << err << endl;
    else
      cerr << sigma << " " << timeStandard << " " << timeApprox << " " << err << endl;
  }

  if ( write_last_result )
  {
    img.write ( "input.png" );
    gaussResult.write ( "gauss.png" );
    gaussResultApprox.write ( "gauss_approx.png" );
  }

  return 0;
}
