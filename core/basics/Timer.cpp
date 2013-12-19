/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libfbasics - library of some basic tools
 * See file License for license information.
 */
#include "core/basics/Timer.h"
#include <core/basics/Exception.h>
#include <limits>

#ifdef WIN32
 #ifdef NICE_BOOST_FOUND
	#include "boost/date_time/posix_time/posix_time.hpp"
	#include "boost/date_time/gregorian/gregorian_types.hpp"
#endif
#endif

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
#ifdef WIN32
 #ifdef NICE_BOOST_FOUND
	return getNow();
 #else
	return -1.0;
	#pragma message NICE_WARNING("Timer::getCurrentAbsoluteTime() : not yet ported to WIN32 plattform, returning -1")
 #endif
#else
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
#ifdef WIN32
 #ifdef NICE_BOOST_FOUND
	boost::posix_time::ptime time_t_epoch( boost::gregorian::date(1970,1,1)); 
	boost::posix_time::ptime now = boost::posix_time::second_clock::local_time();
	boost::posix_time::time_duration diff = now - time_t_epoch;
	return  diff.total_seconds();
 #else
	return -1.0;
	#pragma message NICE_WARNING("Timer::getNow() : not yet ported to WIN32 plattform, returning -1")
 #endif
#else
#ifdef LIMUN_AIBO_MODE
  fthrow ( Exception, "Not supported on AIBO." );
#else
  struct timeval actTime;
  struct timezone tz;
  gettimeofday ( &actTime, &tz );
  return Timer::convertTime ( actTime );
#endif
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
#ifdef WIN32
 #ifdef NICE_BOOST_FOUND
	return getNow();
 #else
	return -1.0;
	#pragma message NICE_WARNING("Timer::getMicroseconds() : not yet ported to WIN32 plattform, returning -1")
 #endif
#else

#ifdef LIMUN_AIBO_MODE
  fthrow ( Exception, "Not supported on AIBO." );
#else
  struct timeval actTime;
  struct timezone tz;
  gettimeofday ( &actTime, &tz );
  return actTime.tv_usec;
#endif
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

double Timer::convertTime ( const struct timeval &time ) {
#ifndef WIN32
      return double ( time.tv_sec ) + double ( time.tv_usec ) * 1e-6;
#else
		return -1.0;
		#pragma message NICE_WARNING("Timer::convertTime() : not yet ported to WIN32 plattform, returning -1")
#endif
    }

} // namespace

