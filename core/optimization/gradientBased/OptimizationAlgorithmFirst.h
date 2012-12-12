/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - liboptimization - An optimization/template for new NICE libraries
 * See file License for license information.
 */
/*****************************************************************************/
#ifndef _OPTIMIZATIONALGORITHMFIRST_OPTIMIZATION_H
#define _OPTIMIZATIONALGORITHMFIRST_OPTIMIZATION_H

#include <iostream>

#include <core/basics/NonCopyable.h>
#include <core/optimization/gradientBased/OptimizationAlgorithmSecond.h>
#include <core/optimization/gradientBased/OptimizationProblemFirst.h>

namespace NICE {

/**
 * Base class for first (and thus also second) order optimization algorithms
 * 
 * \ingroup optimization_algorithms 
 */
class OptimizationAlgorithmFirst : private OptimizationAlgorithmSecond {
public:
  virtual ~OptimizationAlgorithmFirst();
  
  inline void optimize(OptimizationProblemSecond& problem) {
    optimizeFirst(problem);
  }

  inline void optimizeFirst(OptimizationProblemFirst& problem) {
    problem.init();
    doOptimizeFirst(problem);
  }
    
protected:
  virtual void doOptimize(OptimizationProblemSecond& problem);

  virtual void doOptimizeFirst(OptimizationProblemFirst& problem) = 0;
};

}; // namespace NICE 

#endif /* _OPTIMIZATIONALGORITHMFIRST_OPTIMIZATION_H */

