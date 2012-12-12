/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - liboptimization - An optimization/template for new NICE libraries
 * See file License for license information.
 */
/*****************************************************************************/
#include "core/optimization/gradientBased/OptimizationProblemSecond.h"

namespace NICE {

OptimizationProblemSecond::~OptimizationProblemSecond() {
}

void OptimizationProblemSecond::computeGradient(Vector& newGradient) {
  m_hessianCache.resize(dimension(), dimension());
  computeGradientAndHessian(newGradient, m_hessianCache);
}

}; // namespace NICE 
