/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libfbasics - library of some basic tools
 * See file License for license information.
 */
#ifndef _FBASICS_TIMER_H_
#define _FBASICS_TIMER_H_


#ifdef LIMUN_AIBO_MODE
#ifndef PLATFORM_APERIOS
#define PLATFORM_APERIOS
#endif
//#include <MCOOP.h>
#include <Shared/TimeET.h>
#else
#include <ctime>
 #ifdef WIN32
  #include <time.h>
  #include "CrossplatformDefines.h"
#else
  #include <sys/time.h>
 #endif
#endif
#include <string>
#include <core/basics/Log.h>

namespace NICE {

/**
 * A class to measure CPU time consumption. All times are measured in seconds.
 * There are currently two measurement techniques refered to as "process time"
 * and "absolute time". Process time only measures time while the process is
 * active. Absolute time is indepentent of scheduling, but offers much higher
 * precision and can measure longer times (see note).
 * \note On a typical GNU Linux system, process time measurement
 *       can only handle a maximum of approx 71.5 minutes
 *       between calls to start() and stop(). Otherwise overflows occur
 *       and the results are incorrect.
 */
class Timer {
  public:
    /**
     * @name Constructors and destructor
     * \{
     */

    /**
     * Create a unnamed timer which will not print results to timing log.
     */
    Timer();

    /**
     * Create a named timer which will (optionally) print results to timing log
     * Log::timing() when destroyed.
     */
    Timer ( const std::string _name, bool _printToLogWhenDestroyed = true );

    ~Timer();

    /**
     * \}
     * @name Measuring control.
     * \{
     */

    /**
     * Start time measurement.
     */
    void start();

    /**
     * Stop time measurement.
     */
    void stop();

    /**
     * Reset measurements.
     */
    void reset();

    /**
     * The number of calls to stop() since construction or last call of reset().
     */
    inline int getCounter() const {
      return counter;
    }

    /**
     * \}
     * @name Get measurement results - low resolution process time.
     * \{
     */

    /**
     * Value of the previous measurement in process time.
     * @return previous measurement
     */
    inline double getLast() const {
      return last;
    }

    /**
     * Sum of all measurement (since last \c reset()) in process time.
     * @return Sum of all measurements
     */
    inline double getSum() const {
      return sum;
    }

    /**
     * Mean of the all measurement (since last \c reset()) in process time.
     * @return Mean of all measurements
     */
    inline double getMean() const {
      return sum / ( double ) counter;
    }

    /**
     * \}
     * @name Get measurement results - high resolution absolute time.
     * \{
     */

    /**
     * Value of the previous measurement in absolute time.
     * @return previous measurement
     */
    inline double getLastAbsolute() const {
      return lastAbsolute;
    }

    /**
     * Sum of all measurement (since last \c reset()) in absolute time.
     * @return Sum of all measurements
     */
    inline double getSumAbsolute() const {
      return sumAbsolute;
    }

    /**
     * Mean of the all measurement (since last \c reset()) in absolute time.
     * @return Mean of all measurements
     */
    inline double getMeanAbsolute() const {
      return sumAbsolute / ( double ) counter;
    }

    /**
     * \}
     * @name Estimation of finishing time of some task.
     * \{
     */

    /**
     * double value of start time in seconds since Epoch
     * (00:00:00 UTC, January 1, 1970)
     * @return double value of start time in sec
     */
    double getStartTime() const;

    /**
     * double value of estimated end time by multiplying the elapsed absolute
     * sum with the factor \c fac.
     * @param fac factor to multiply the elapsed absolute time sum
     * @note use in a loop of i=0...max :  fac = max/(i+1.)
     * @return estimated end time in seconds since Epoch
     *         (00:00:00 UTC, January 1, 1970)
     */
    double getEstimatedEndTime ( double fac ) const;

    /**
     * \}
     * @name Time functions, NOT related to measuring periods of time.
     * \{
     */

    /**
     * Current time in seconds since Epoch (00:00:00 UTC, January 1, 1970).
     * Precision is up to one microsecond.
     */
    static double getNow();

    /**
     * Get current date and local time as a string of the following format:
     * yyyy-mm-dd-hh-mm-ss.
     */
    static std::string getNowString();

    /**
     * Get current microseconds - a pretty useless value, but nice for srand().
     */
    static long int getMicroseconds();

    /**
     * convert timeval format to double value of time in seconds since Epoch
     * (00:00:00 UTC, January 1, 1970)
     * @return double value of time in seconds
     */
    static double convertTime ( const struct timeval &time );

    /**
     * Date string from time since Epoch (00:00:00 UTC, January 1, 1970),
     * measured in seconds
     * @ sec seconds since 00:00:00 UTC, January 1, 1970
     * @return date string
     */
    static std::string timeToString ( time_t sec );

    /**
     * see \c timeToString(time_t)
     */
    static std::string timeToString ( double sec );

    /**
     * \}
     */

  private:
    //! Start time of current measurement
    clock_t startClock;

    //! Start time of current measurement
    double startTimeAbsolute;

    //! Previous measurement
    double last;

    //! Sum of all measurement (since last \c reset())
    double sum;

    //! Previous measurement
    double lastAbsolute;

    //! Sum of all measurement (since last \c reset())
    double sumAbsolute;

    //! Number of measurements (since last \c reset())
    int counter;

    //! Print results in destructor?
    bool printToLogWhenDestroyed;

    //! Name of the timer.
    std::string name;

    //! internal
    double getCurrentAbsoluteTime() const;
};

} // namespace
#endif // _FBASICS_TIMER_H_
