/** 
* @file FastMath.h
* @brief lookup tables and more
* @author Erik Rodner
* @date 07/31/2008

*/
#ifndef FASTMATHINCLUDE
#define FASTMATHINCLUDE


namespace NICE {

/** @brief some lookup tables suitable for image gradients */
class FastMath
{
    public:
	/** maximum value of image gradients */
 	static const int gradientMaximum = 255;

	/** sqrt(.) 2*255^2 is the maximum value of the argument */
	static const int sqrtTableMaximum = 2*gradientMaximum*gradientMaximum+1;

	/** access to the sqrt table sqrtTable[y*gradientMaximum + x] */
	double *sqrtTable;

	/** lookup table for atan2 */
	static const int atan2TableMaximum = (2*gradientMaximum+1)*(2*gradientMaximum+1);

	/** access to the atan2 table atan2Table[y*gradientMaximum + x] */
	double *atan2Table;
 
	/** do not use this constructor directly */
	FastMath ();
	
	/** destructor: removes all lookup tables  */
	~FastMath ();

	/** get the singleton object instance */
	static FastMath & getSingleton () {
	    static FastMath fastMathSingleton;
	    return fastMathSingleton;
	}
     
};



} // namespace

#endif
