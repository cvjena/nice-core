/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libfbasics - library of some basic tools
 * See file License for license information.
 */
#include "core/basics/Timer.h"
#include <core/basics/Exception.h>
#include <limits>

namespace NICE {

Timer::Timer() : printToLogWhenDestroyed ( false ), name ( "" ) {
  reset();
}

Timer::Timer ( const std::string _name, bool _printToLogWhenDestroyed )
    : printToLogWhenDestroyed ( _printToLogWhenDestroyed ), name ( _name ) {
  reset();
}

Timer::~Timer() {
  if ( printToLogWhenDestroyed ) {
    Log::timing() << std::fixed << "Timer " << name << ":"
    << " process_time=" << getSum()
    << ", mean=" << getMean()
    << "; absolute_time=" << getSumAbsolute()
    << ", mean=" << getMeanAbsolute() << std::endl;
  }
}

double Timer::getCurrentAbsoluteTime() const {
#ifdef LIMUN_AIBO_MODE
  struct SystemTime t;
  GetSystemTime ( &t );
  return double ( t.seconds ) + double ( t.useconds ) * 1e-6;
#else
  struct timezone tz;
  struct timeval tv;
  gettimeofday ( &tv, &tz );
  return convertTime ( tv );
#endif
}

void Timer::start() {
  startClock = clock();
  startTimeAbsolute = getCurrentAbsoluteTime();
}

void Timer::stop() {
  const clock_t endClock = clock();
  double passedClock = double ( endClock ) - double ( startClock );
  if ( endClock < startClock ) {
    passedClock += double ( std::numeric_limits<clock_t>::max() );
  }
  last = passedClock / double ( CLOCKS_PER_SEC );

  double endTimeAbsolute = getCurrentAbsoluteTime();
  lastAbsolute = endTimeAbsolute - startTimeAbsolute;

  counter++;
  sum += last;
  sumAbsolute += lastAbsolute;
}

double Timer::getStartTime() const
{
  return startTimeAbsolute;
}

double Timer::getNow()
{
#ifdef LIMUN_AIBO_MODE
  fthrow ( Exception, "Not supported on AIBO." );
#else
  struct timeval actTime;
  struct timezone tz;
  gettimeofday ( &actTime, &tz );
  return Timer::convertTime ( actTime );
#endif
}

std::string Timer::getNowString() {
  time_t nowTime = time ( 0 );
  tm* nowTm = localtime ( &nowTime );

  std::stringstream s;
  s << ( 1900 + nowTm->tm_year ) << "-" << ( nowTm->tm_mon + 1 )
  << "-" << nowTm->tm_mday << "-" << nowTm->tm_hour
  << "-" << nowTm->tm_min << "-" << nowTm->tm_sec;

  return s.str();
}

long int Timer::getMicroseconds() {
#ifdef LIMUN_AIBO_MODE
  fthrow ( Exception, "Not supported on AIBO." );
#else
  struct timeval actTime;
  struct timezone tz;
  gettimeofday ( &actTime, &tz );
  return actTime.tv_usec;
#endif
}


double Timer::getEstimatedEndTime ( double fac ) const
{
  double actTime = getCurrentAbsoluteTime();
  double expected = ( actTime - startTimeAbsolute
                      + sumAbsolute - lastAbsolute ) * ( fac - 1.0 );
  return actTime + expected;
}

std::string Timer::timeToString ( double sec )
{
  return Timer::timeToString ( static_cast<time_t> ( sec ) );
}

std::string Timer::timeToString ( time_t sec )
{
  std::string acttime = ctime ( &sec );
  acttime = acttime.substr ( 0, acttime.size() - 1 );
  return acttime;
}

void Timer::reset() {
  counter = 0;
  last = 0.0;
  sum = 0.0;
  lastAbsolute = 0.0;
  sumAbsolute = 0.0;
}

} // namespace

