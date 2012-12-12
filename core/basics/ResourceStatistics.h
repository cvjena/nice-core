/** 
* @file ResourceStatistics.h
* @author Paul Bodesheim
* @date 03/02/2012 (dd/mm/yyyy)

*/
#ifndef _NICE_ResourceStatistics_INCLUDE
#define _NICE_ResourceStatistics_INCLUDE

#include <sys/time.h>
#include <sys/resource.h>
#include <core/basics/Exception.h>

namespace NICE {
  
/** @class ResourceStatistics
 * Interface that provides statistics for runtime and memory usage based on the function "getrusage" of <sys/resource.h>
 *
 * @author Paul Bodesheim
 */
class ResourceStatistics
{

    private:
      
      // both variables are necessary for the function "getrusage"
      int mode; 
      struct rusage memoryStatistics;

    public:

    /**
    * @brief simple constructor 
    * 
    * @param _mode mode for "getrusage", it is recommended to use the default value RUSAGE_SELF
    */
    ResourceStatistics(int _mode = RUSAGE_SELF);
      
    /**
    * @brief simple destructor 
    */
    ~ResourceStatistics();

    /**
     * @brief get maximum memory (maximum resident set size) measured in kilo-bytes 
     *
     * @param memory maximum memory measured in KB
     **/
    void getMaximumMemory(long & memory);
    
    /**
     * @brief get the user CPU time used (seconds)
     *
     * @param time user cpu time measured in seconds
     **/
    void getUserCpuTime(double & time);
    
    /**
     * @brief get the system CPU time used (seconds)
     *
     * @param time system cpu time measured in seconds
     **/
    void getSystemCpuTime(double & time); 
    
    /**
     * @brief get three measures of your program: maximum memory, user CPU time, system CPU time
     *
     * @param memory maximum memory measured in KB
     * @param userCpuTime user cpu time measured in seconds
     * @param systemCpuTime system cpu time measured in seconds
     **/
    void getStatistics(long & memory, double & userCpuTime, double & systemCpuTime);
};

}

#endif
