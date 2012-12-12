/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - liboptimization - An optimization/template for new NICE libraries
 * See file License for license information.
 */
/*****************************************************************************/
#ifndef _OPTIMIZATIONALGORITHMSECOND_OPTIMIZATION_H
#define _OPTIMIZATIONALGORITHMSECOND_OPTIMIZATION_H

#include <iostream>

#include <core/basics/NonCopyable.h>
#include <core/optimization/gradientBased/OptimizationProblemSecond.h>

namespace NICE {

/**
 * \defgroup optimization_algorithms Optimization Algorithms
 * 
 * This module contains the optimization algorithms that
 * can be used to solve a user defined 
 * \link optimization_problems optimization problem \endlink.
 * 
 * The actual optimization problem, i.e. the objective function and their
 * derivatives need to be specified by the user of this library
 * by implementing a subclass of \c NICE::OptimizationProblemSecond
 * or \c NICE::OptimizationProblemFirst, respectively.
 * "First" refers to "first order", meaning that only
 * the gradient of the objective function is used. Accordingly,
 * "Second" refers to "second order": gradient and Hessian.
 * 
 * Second order algorithms
 * (subclasses of \c NICE::OptimizationAlgorithmSecond)
 * are generally more efficient than first order algorithms
 * (subclasses of \c NICE::OptimizationAlgorithmFirst),
 * but require the Hessian matrix,
 * which can be more difficult to implement than the gradient,
 * and is sometimes very time consuming to compute.
 * 
 * \note There are some optimization algorithms which use only the gradient 
 * directly and compute an approximation of the Hessian themselves.
 * Currently, there is no such algorithm in this library.
 * If you want to implement one, make it a subclass of 
 * \c NICE::OptimizationAlgorithmFirst
 * as it only needs to be supplied with the gradient.
 * 
 * \note \c NICE::OptimizationAlgorithmFirst is a subclass of 
 * \c NICE::OptimizationAlgorithmSecond, as first order algorithms
 * also work with \c NICE::OptimizationProblemSecond, which provides
 * the required gradient.
 */

/**
 * Base class for second order optimization algorithms.
 * 
 * \ingroup optimization_algorithms 
 */
class OptimizationAlgorithmSecond : private NonCopyable {
public:
  virtual ~OptimizationAlgorithmSecond();
  
  inline void optimize(OptimizationProblemSecond& problem) {
    problem.init();
    doOptimize(problem);
  }
  
protected:
  virtual void doOptimize(OptimizationProblemSecond& problem) = 0;
};

}; // namespace NICE 

#endif /* _OPTIMIZATIONALGORITHM_OPTIMIZATION_H */

