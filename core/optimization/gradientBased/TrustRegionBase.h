/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - liboptimization - An optimization/template for new NICE libraries
 * See file License for license information.
 */
/*****************************************************************************/
#ifndef _TRUSTREGIONBASE_OPTIMIZATION_H
#define _TRUSTREGIONBASE_OPTIMIZATION_H

#include <iostream>

#include <core/basics/NonCopyable.h>
#include <core/optimization/gradientBased/OptimizationProblemFirst.h>

namespace NICE {

/**
 * Base class for trust region algorithms.
 * Mostly for common configuration parameters.
 * Notation as in Ferid Bajramovic: Kernel-basierte Objektverfolgung,
 *                Master's thesis (Diplomarbeit),
 *                Computer Science Department, University Passau
 *
 * \ingroup optimization_algorithms
 */
class TrustRegionBase {
public:
  TrustRegionBase(double typicalGradientNorm = 0.1)
      : eta1(0.05), eta2(0.9), alpha1(2.5), alpha2(0.25),
        deltaMin(1E-5), epsilonM(std::numeric_limits<double>::epsilon()),
        //epsilonR(0.05),
        epsilonR(1E-5),
        epsilonG(epsilonR * typicalGradientNorm),
        epsilonDelta(2.0 * epsilonM), epsilonRho(2.0 * epsilonM),
        maxIterations(10000000) {
  }

  virtual ~TrustRegionBase();

  /**
   * Specify a relative gradient threshold stopping condition by
   * setting \f$\epsilon_{g}\f$ via \f$\epsilon_{r}\f$.
   * @param _epsilonR Fraction of \c _typicalGradient to be used as threshold
   *                  \f$\epsilon_{g}\f$.
   * @param _typicalGradient A typical value for the gradient norm,
   *                         e.g. the current gradient norm.
   */
  inline void setEpsilonR(double _epsilonR, double _typicalGradient) {
    // make sure that the threshold is positive
    if (_typicalGradient < 1e-300) {
      _typicalGradient = 1e-300;
    }
    epsilonR = _epsilonR;
    setEpsilonG(_epsilonR * _typicalGradient);
  }

  /**
   * Specify an absolute gradient threshold stopping condition by
   * setting \f$\epsilon_{g}\f$.
   * @param _epsilonG Threshold
   */
  inline void setEpsilonG(double _epsilonG) {
    epsilonG = _epsilonG;
  }

  /**
   * Set the maximum number of iterations (stopping condition).
   * @param _maxIterations
   */
  inline void setMaxIterations(unsigned int _maxIterations) {
    maxIterations = _maxIterations;
  }

  /**
   * Set the minimum size of the trust region radius (stopping condition).
   * @param _deltaMin
   */
  inline void setDeltaMin(double _deltaMin) {
    deltaMin = _deltaMin;
  }

  /**
    * Set the parameter eta1.
    * @param _eta1
   */
   inline void setEta1(double _eta1 = 0.05) {
       eta1 = _eta1;
   }

  /**
    * Set the parameter eta2.
    * @param _eta2
   */
   inline void setEta2(double _eta2 = 0.9) {
       eta2 = _eta2;
   }

  /**
    * Set the parameter alpha1
    * @param _alpha1
   */
   inline void setAlpha1(double _alpha1 = 2.5) {
       alpha1 = _alpha1;
   }

  /**
    * Set the parameter alpha2
    * @param _alpha2
   */
   inline void setAlpha2(double _alpha2 = 2.5) {
       alpha2 = _alpha2;
   }

protected:
  //! \f$\eta_1\f$
  double eta1;

  //! \f$\eta_2\f$
  double eta2;

  //! \f$\mu_1\f$
  double alpha1;

  //! \f$\mu_2\f$
  double alpha2;

//  //! \f$\Delta\f$
//  double delta;

  //! \f$\Delta_{\min}\f$
  double deltaMin;

  //! \f$\epsilon_{M}\f$
  double epsilonM;

  //! \f$\epsilon_{r}\f$
  double epsilonR;

  //! \f$\epsilon_{g}\f$: threshold on gradient norm (stopping condition)
  double epsilonG;

  //! \f$\epsilon_{\Delta}\f$
  double epsilonDelta;

  //! \f$\epsilon_{\rho}\f$
  double epsilonRho;

  //! maximum number of iterations
  int maxIterations;

  /**
   * Check if the change by step \c step is numerically minimal
   * (relative to the current \c position in parameter space).
   */
  bool changeIsMinimal(const Vector& step,
                       const Vector& position);
};

}; // namespace NICE

#endif /* _TRUSTREGIONBASE_OPTIMIZATION_H */

