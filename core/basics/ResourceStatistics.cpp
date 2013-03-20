/** 
* @file ResourceStatistics.cpp
* @brief Iteratively solving linear equation systems with the symmetric LQ (SYMMLQ) method using Lanczos process
* @author Paul Bodesheim
* @date 03/02/2012 (dd/mm/yyyy)

*/

#include "ResourceStatistics.h"

using namespace NICE;
using namespace std;

#ifndef WIN32

ResourceStatistics::ResourceStatistics(int _mode)
{
  mode = _mode;
}
      
ResourceStatistics::~ResourceStatistics()
{
}

void ResourceStatistics::getMaximumMemory(long & memory)
{
  int check = getrusage(mode,&memoryStatistics);
  
  if ( check == -1 )
  {
    fthrow(Exception, "ResourceStatistics::getMaximumMemory:  getrusage failed");
    return;
  
  } else if ( check == 0 )
  {
    
    memory = memoryStatistics.ru_maxrss;
    return;
    
  } else
  {
    fthrow(Exception, "ResourceStatistics::getMaximumMemory:  unexpected flag");
    return;     
    
  }
}
    

void ResourceStatistics::getUserCpuTime(double & time)
{
  int check = getrusage(mode,&memoryStatistics);
  
  if ( check == -1 )
  {
    fthrow(Exception, "ResourceStatistics::getUserCpuTime:  getrusage failed");
    return;
  
  } else if ( check == 0 )
  {
    
    double sec = (double) memoryStatistics.ru_utime.tv_sec;
    double msec = (double) memoryStatistics.ru_utime.tv_usec;
    time = sec + (msec/1e6);
    return;
    
  } else
  {
    fthrow(Exception, "ResourceStatistics::getUserCpuTime:  unexpected flag");
    return;     
    
  }

}
    

void ResourceStatistics::getSystemCpuTime(double & time)
{
  int check = getrusage(mode,&memoryStatistics);
  
  if ( check == -1 )
  {
    fthrow(Exception, "ResourceStatistics::getSystemCpuTime:  getrusage failed");
    return;
  
  } else if ( check == 0 )
  {
    
    double sec = (double) memoryStatistics.ru_stime.tv_sec;
    double msec = (double) memoryStatistics.ru_stime.tv_usec;
    time = sec + (msec/1e6);
    return;
    
  } else
  {
    fthrow(Exception, "ResourceStatistics::getSystemCpuTime:  unexpected flag");
    return;     
    
  } 

}

void ResourceStatistics::getStatistics(long & memory, double & userCpuTime, double & systemCpuTime)
{
  int check = getrusage(mode,&memoryStatistics);
  
  if ( check == -1 )
  {
    fthrow(Exception, "ResourceStatistics::getStatistics:  getrusage failed");
    return;
  
  } else if ( check == 0 )
  {
    double sec, msec;
    
    memory = memoryStatistics.ru_maxrss;
    
    sec = (double) memoryStatistics.ru_utime.tv_sec;
    msec = (double) memoryStatistics.ru_utime.tv_usec;
    userCpuTime = sec + (msec/1e6);    
    
    sec = (double) memoryStatistics.ru_stime.tv_sec;
    msec = (double) memoryStatistics.ru_stime.tv_usec;
    systemCpuTime = sec + (msec/1e6);
    
    return;
    
  } else
  {
    fthrow(Exception, "ResourceStatistics::getStatistics:  unexpected flag");
    return;     
    
  }   
  
  
  
}

#else 
/// WIN32 PORT following here
#include "CrossplatformDefines.h"

#pragma message NICE_WARNING("ResourceStatistics class : not yet ported to WIN32 plattform")

ResourceStatistics::ResourceStatistics(int _mode)
{
  mode = _mode;
}
      
ResourceStatistics::~ResourceStatistics()
{
}

void ResourceStatistics::getMaximumMemory(long & memory)
{
	fthrow ( Exception, "ResourceStatistics class : not yet ported to WIN32 plattform");
}
    

void ResourceStatistics::getUserCpuTime(double & time)
{
	fthrow ( Exception, "ResourceStatistics class : not yet ported to WIN32 plattform");
}
    

void ResourceStatistics::getSystemCpuTime(double & time)
{
	fthrow ( Exception, "ResourceStatistics class : not yet ported to WIN32 plattform");
}

void ResourceStatistics::getStatistics(long & memory, double & userCpuTime, double & systemCpuTime)
{
	fthrow ( Exception, "ResourceStatistics class : not yet ported to WIN32 plattform");
}

#endif