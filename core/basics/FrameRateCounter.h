/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libfbasics - library of some basic tools
 * See file License for license information.
 */
#ifndef _FRAMERATECOUNTER_H_
#define _FRAMERATECOUNTER_H_


#include <string>
#include <core/basics/Timer.h>

namespace NICE {

/**
 * Frame rate counter: compute frames per second.
 */
class FrameRateCounter {
public:
  /**
   * 
   */
  FrameRateCounter(unsigned int lookBack = 30);

  ~FrameRateCounter();
  
  /**
   * Reset measurements.
   */
  void reset();
  
  /**
   * A new frame.
   */
  void newFrame();
  
  /**
   * Frame rate in seconds (FPS).
   */
  inline double getFrameRate() const {
    return m_frameRate;
  }
  
  /**
   * The number of calls to \c newFrame().
   */
  inline int getCounter() const {
    return m_counter;
  }

private:
  Timer m_timer;
  unsigned int m_lookBack;
  unsigned int m_counter;
  double m_frameRate;
};

} // namespace
#endif // _FRAMERATECOUNTER_H_
