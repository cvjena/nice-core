/** 
* @file FastMath.cpp
* @brief lookup tables and more
* @author Erik Rodner
* @date 07/31/2008

*/
#include "FastMath.h"
#include <stdio.h>
#include <math.h>
#include <assert.h>

using namespace NICE;

using namespace std;

FastMath::~FastMath ()
{
    if ( sqrtTable != NULL )
	delete [] sqrtTable;
    if ( atan2Table != NULL )
	delete [] atan2Table;
}

FastMath::FastMath()
{
    sqrtTable = new double[sqrtTableMaximum];
    for ( int j = 0 ; j < sqrtTableMaximum; j++ )
	sqrtTable[j] = sqrt((double)j);

    atan2Table = new double[atan2TableMaximum];
    long k = 0 ;
    for ( int i = -gradientMaximum ; i <= gradientMaximum ; i++ )
	for ( int j = -gradientMaximum ; j <= gradientMaximum ; j++,k++ )
	    atan2Table[k] = atan2((double)i,(double)j);

    assert ( k == atan2TableMaximum );
}

