#include <core/basics/Exception.h>

#include "GMStandard.h"

using namespace NICE;
using namespace std;

void GMStandard::multiply ( const SetType & rowSet, const SetType & columnSet, NICE::Vector & y, const NICE::Vector & x) const
{
  if ( x.size() != columnSet.size() ) 
    fthrow(Exception, "Size of the column set is different from the size of the given input vector: " << columnSet.size() << " vs " << x.size());
  
  y.resize( rowSet.size() );

  // memory inefficient
  Matrix Asub ( rowSet.size(), columnSet.size() );

  int ii = 0;
  for ( SetType::const_iterator i = rowSet.begin(); i != rowSet.end(); i++,ii++ )
  {
    int jj = 0;
    for ( SetType::const_iterator j = columnSet.begin(); j != columnSet.end(); j++,jj++ )
      Asub ( ii, jj ) = A( *i, *j ); 
  }

  y.multiply ( Asub, x );
}
    
double GMStandard::getDiagonalElement ( uint i ) const
{
  if ( (i >= A.rows()) || (i >= A.cols()) )
    fthrow(Exception, "Invalid index to access diagonal element: " << i << " (" << A.rows() << " x " << A.cols() << ")" );

  return A(i,i);
}
