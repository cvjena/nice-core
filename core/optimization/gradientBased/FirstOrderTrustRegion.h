/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - liboptimization - An optimization/template for new NICE libraries
 * See file License for license information.
 */
/*****************************************************************************/
#ifndef _FIRSTORDERTRUSTREGION_OPTIMIZATION_H
#define _FIRSTORDERTRUSTREGION_OPTIMIZATION_H

#include <iostream>

#include <core/basics/NonCopyable.h>
#include <core/optimization/gradientBased/OptimizationAlgorithmFirst.h>
#include <core/optimization/gradientBased/TrustRegionBase.h>

namespace NICE {

/**
 * A first order trust region algorithm.
 * Notation as in Ferid Bajramovic: Kernel-basierte Objektverfolgung,
 *                Master's thesis (Diplomarbeit), 
 *                Computer Science Department, University Passau
 * 
 * \ingroup optimization_algorithms 
 */
class FirstOrderTrustRegion : public OptimizationAlgorithmFirst,
                              public TrustRegionBase {
public:
  FirstOrderTrustRegion(double typicalGradient = 0.1, bool _verbose = false)
      : TrustRegionBase(typicalGradient), verbose(_verbose) {}
  
  virtual ~FirstOrderTrustRegion();
  
protected:
  virtual void doOptimizeFirst(OptimizationProblemFirst& problem);
  
private:
  bool verbose;

  /**
   * Compute the initial trust region radius.
   */
  double computeInitialDelta(const double gradientNorm);
};

}; // namespace NICE 

#endif /* _FIRSTORDERTRUSTREGION_OPTIMIZATION_H */

