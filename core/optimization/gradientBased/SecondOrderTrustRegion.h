/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - liboptimization - An optimization/template for new NICE libraries
 * See file License for license information.
 */
/*****************************************************************************/
#ifndef _SECONDORDERTRUSTREGION_OPTIMIZATION_H
#define _SECONDORDERTRUSTREGION_OPTIMIZATION_H

#include <iostream>

#include <core/basics/NonCopyable.h>
#include <core/optimization/gradientBased/OptimizationAlgorithmSecond.h>
#include <core/optimization/gradientBased/TrustRegionBase.h>

namespace NICE {

/**
 * A second order trust region algorithm.
 * Notation as in Ferid Bajramovic: Kernel-basierte Objektverfolgung,
 *                Master's thesis (Diplomarbeit), 
 *                Computer Science Department, University Passau
 * 
 * \ingroup optimization_algorithms 
 */
class SecondOrderTrustRegion : public OptimizationAlgorithmSecond,
                               public TrustRegionBase {
public:
  SecondOrderTrustRegion(double typicalGradient = 0.1)
      : TrustRegionBase(typicalGradient), kappa(0.1), 
        epsilonLambda(1E5 * epsilonM), maxSubIterations(150),
        tolerance(1E-14) {}
  
  virtual ~SecondOrderTrustRegion();
    
  /**
   * Set epsilonLambda relative to epsilonM
   */
  inline void setEpsilonLambdaRelative(double factor) {
    epsilonLambda = factor * epsilonM;
  }

  /**
   * Set epsilonLambda
   */
  inline void setEpsilonLambdaAbsolute(double newValue) {
    epsilonLambda = newValue;
  }
    
protected:
  virtual void doOptimize(OptimizationProblemSecond& problem);
  
private:
  //! \f$\kappa\f$
  double kappa;
  
  //! \f$\epsilon_{\lambda}\f$
  double epsilonLambda;
  
  unsigned int maxSubIterations;
  
  double tolerance;

  /**
   * Compute the initial trust region radius.
   */
  double computeInitialDelta(const Vector& gradient,
                             const Matrix& hessian);
};

}; // namespace NICE 

#endif /* _SECONDORDERTRUSTREGION_OPTIMIZATION_H */

