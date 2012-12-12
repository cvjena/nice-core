/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libfbasics - library of some basic tools
 * See file License for license information.
 */
#include "core/basics/FrameRateCounter.h"

namespace NICE {

FrameRateCounter::FrameRateCounter(unsigned int lookBack)
    : m_lookBack(lookBack), m_counter(0), m_frameRate(0.0) {
  reset();
}

FrameRateCounter::~FrameRateCounter() {
}

void FrameRateCounter::newFrame() {
  m_counter++;
  if (m_counter == m_lookBack) {
    m_timer.stop();
    m_timer.start();
    m_frameRate = double(m_lookBack) / double(m_timer.getLastAbsolute());
    m_counter = 0;
  }
}

void FrameRateCounter::reset() {
  m_timer.start();
}

} // namespace

