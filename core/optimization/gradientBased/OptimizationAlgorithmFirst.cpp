/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - liboptimization - An optimization/template for new NICE libraries
 * See file License for license information.
 */
/*****************************************************************************/
#include "core/optimization/gradientBased/OptimizationAlgorithmFirst.h"

namespace NICE {

OptimizationAlgorithmFirst::~OptimizationAlgorithmFirst() {
}

void OptimizationAlgorithmFirst::doOptimize(
                                   OptimizationProblemSecond& problem) {
  doOptimizeFirst(problem);
}

}; // namespace NICE 
