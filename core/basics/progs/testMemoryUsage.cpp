/** 
* @file testMemoryUsage.cpp
* @author Paul Bodesheim
* @date  03/02/2012 (dd/mm/yyyy)
* @brief test routine for examining memory usage
*/

// #include <sys/time.h>
// #include <sys/resource.h>
#include "core/basics/ResourceStatistics.h"
#include <stdio.h>
#include "core/vector/MatrixT.h"
#include "core/vector/VectorT.h"
#include <iostream>

using namespace std;
using namespace NICE;

int main(int argc, char* argv[])
{
  
  ResourceStatistics resources;
  long memory;
  double userCpuTime;
  double systemCpuTime;
  
  NICE::Matrix M1(2000,2000,0.15);
  NICE::Matrix M2(2000,2000,0.25);
  
  std::cerr << "M1 and M2" << std::endl;

  resources.getMaximumMemory(memory);
  std::cerr << "memory:" << memory << std::endl;

  resources.getUserCpuTime(userCpuTime);
  std::cerr << "user cpu time:" << userCpuTime << std::endl;

  resources.getSystemCpuTime(systemCpuTime);
  std::cerr << "system cpu time:" << systemCpuTime << std::endl;
  
  NICE::Matrix M3(2000,2000,0.35);
  NICE::Matrix M4(2000,2000,0.45); 
  
  std::cerr << "M3 and M4" << std::endl;

  resources.getStatistics(memory,userCpuTime,systemCpuTime);
  std::cerr << "memory:" << memory << std::endl;
  std::cerr << "user cpu time:" << userCpuTime << std::endl;
  std::cerr << "system cpu time:" << systemCpuTime << std::endl;
  
  return 0;
}

// worked 
//
// int main(int argc, char* argv[])
// {
//   struct rusage memoryStatistics;
//   
//   NICE::Matrix M1(2000,2000,0.75);
//   NICE::Matrix M2(2000,2000,0.85);
// 
//   int check = getrusage(RUSAGE_SELF,&memoryStatistics);
//   
//   if ( check == -1 ) 
//     std::cerr << "getrusage failed" << std::endl;
//   else if ( check == 0 ) 
//   {
//     std::cerr << "success:" << std::endl;
//     std::cerr << "user cpu time: " << memoryStatistics.ru_utime.tv_sec << " sec " << memoryStatistics.ru_utime.tv_usec << " micro-sec" << std::endl;
//     std::cerr << "system cpu time: " << memoryStatistics.ru_stime.tv_sec << " sec " << memoryStatistics.ru_stime.tv_usec << " micro-sec" << std::endl;
//     std::cerr << "maximum memory: " << memoryStatistics.ru_maxrss << " KB"<< std::endl;
//     std::cerr << "inputs: " << memoryStatistics.ru_inblock << std::endl;
//     std::cerr << "outputs: " << memoryStatistics.ru_oublock << std::endl;
//   
//   } else
//     std::cerr << "unknown flag returned" << std::endl;
//   
//   return 0;
// }
