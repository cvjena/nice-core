/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - liboptimization - An optimization/template for new NICE libraries
 * See file License for license information.
 */
/*****************************************************************************/
#include "core/optimization/gradientBased/OptimizationProblemFirst.h"
#include <core/basics/tools.h>

namespace NICE {

OptimizationProblemFirst::~OptimizationProblemFirst() {
}

void OptimizationProblemFirst::computePosition(Vector& pos) {
  // default implementation is empty assuming \c parameters() is used.
  UNUSED_PARAMETER(pos);
}

void OptimizationProblemFirst::doApplyStep(const Vector& step) {
  m_previousPosition = m_positionCache;
  m_positionCache += step;
}

void OptimizationProblemFirst::doUnapplyStep(const Vector& step) {
//   m_positionCache -= step;

  UNUSED_PARAMETER(step);
  m_positionCache = m_previousPosition;
}

}; // namespace NICE
