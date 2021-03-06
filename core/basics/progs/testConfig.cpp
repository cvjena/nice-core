/** 
* @file testConfig.cpp
* @brief test configuration
* @author Erik Rodner
* @date 09/08/2008

*/
#include <core/basics/Config.h>

using namespace NICE;
using namespace std;


/** 
    test configuration 
*/
int main (int argc, char **argv)
{   

#ifndef WIN32
#ifndef __clang__
#ifndef __llvm__ 
    std::set_terminate(__gnu_cxx::__verbose_terminate_handler);
#endif
#endif
#endif

    Config conf ( argc, argv );
    conf.store(cout);    

    return 0;
}
