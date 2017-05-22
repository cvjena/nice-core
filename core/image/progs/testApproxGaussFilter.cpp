#include <iostream>
#include "core/image/FilterT.h"
#include "core/basics/Timer.h"

using namespace NICE;
using namespace std;

#define DATATYPE double
//#define DATATYPE_UCHAR

int main ( int argc, char **argv )
{
  if ( argc != 2 ) {
    std::cerr << "usage: " << argv[0] << " <img>" << std::endl;
    exit ( -1 );
  }
  NICE::Image img_uchar ( argv[1] );
  NICE::ImageT<DATATYPE> img ( img_uchar.width(), img_uchar.height() );

  for ( int y = 0; y < img.height(); y++ )
    for ( int x = 0; x < img.width(); x++ )
      img.setPixel ( x, y, ( DATATYPE ) img_uchar.getPixel ( x, y ) );

  NICE::ImageT<DATATYPE> gaussResult ( img.width(), img.height() );
  NICE::ImageT<DATATYPE> gaussResultApprox ( img.width(), img.height() );
  gaussResult.set ( 0 );
  gaussResultApprox.set ( 0 );

  bool verbose = true;
  bool evaluate_mean_filter = false;
  bool write_last_result = true;

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
      {
#ifdef DATATYPE_UCHAR
        NICE::FilterT<unsigned char, int, int> filter;
        filter.filterMean ( img, filtersize, &gaussResult );
#else
        NICE::FilterT<DATATYPE, DATATYPE, DATATYPE> filter;
        filter.filterMean ( img, filtersize, &gaussResult );
#endif
      }
      else
      {
#ifdef DATATYPE_UCHAR
        NICE::FilterT<unsigned char, int, int> filter;
        filter.filterGaussSigmaApproximate ( img, sigma, &gaussResult );
#else
        NICE::FilterT<DATATYPE, DATATYPE, DATATYPE> filter;
        filter.filterGaussSigmaApproximate ( img, sigma, &gaussResult );
#endif
      }

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
      {
#ifdef DATATYPE_UCHAR
        NICE::FilterT<unsigned char, int, unsigned char> filter;
        filter.filterMeanLargeFS ( img, filtersize, &gaussResultApprox );
#else
        NICE::FilterT<DATATYPE, DATATYPE, DATATYPE> filter;
        filter.filterMeanLargeFS ( img, filtersize, &gaussResultApprox );
#endif
      }
      else
      {
#ifdef DATATYPE_UCHAR
        NICE::FilterT<unsigned char, int, int> filter;
        filter.filterGaussSigmaApproximate ( img, sigma, &gaussResult );
#else
        NICE::FilterT<DATATYPE, DATATYPE, DATATYPE> filter;
        filter.filterGaussSigmaApproximate ( img, sigma, &gaussResult );
#endif
      }

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
