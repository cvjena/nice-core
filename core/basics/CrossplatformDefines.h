#ifndef CROSSPLATFORMDEFINES_H
#define CROSSPLATFORMDEFINES_H


/////////////////////////////////////////////////////////////////////
//define a consistent warning preprocessor for unix and win systems
// see http://stackoverflow.com/questions/471935/user-warnings-on-msvc-and-gcc

#define STRINGISE_IMPL(x) #x
#define STRINGISE(x) STRINGISE_IMPL(x)

// Use: #pragma message WARNING("My message")
#if _MSC_VER
#   define FILE_LINE_LINK __FILE__ "(" STRINGISE(__LINE__) ") : "
#   define WARNING(exp) (FILE_LINE_LINK "WARNING: " exp)
#else//__GNUC__ - may need other defines for different compilers
#   define WARNING(exp) ("WARNING: " exp)
#endif

//
/////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////
//
#include <math.h>
#ifdef WIN32
typedef unsigned int uint;


inline double round(double r) {
    return (r > 0.0) ? floor(r + 0.5) : ceil(r - 0.5);
}
inline float roundf(float r)
{
	return (float)round(r);
}
#endif


#endif //CROSSPLATFORMDEFINES_H