/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - liboptimization - An optimization/template for new NICE libraries
 * See file License for license information.
 */
/*****************************************************************************/
#include "core/optimization/gradientBased/FirstOrderTrustRegion.h"

#include <core/basics/Log.h>

namespace NICE {

FirstOrderTrustRegion::~FirstOrderTrustRegion() 
{
}

void FirstOrderTrustRegion::doOptimizeFirst(OptimizationProblemFirst& problem) {
  bool previousStepSuccessful = true;
  double previousError = problem.objective();
  problem.computeGradient();
  double delta = computeInitialDelta(problem.gradientNormCached());
  double normOldPosition = 0.0;

  if ( verbose )
     Log::debug() << "optimizeFirst(): "
         << " " << previousError
         << std::endl;

  // iterate
  for (int iteration = 0; iteration < maxIterations; iteration++) {
	if ( verbose )
    	Log::debug() << "iteration, objective: " << iteration << ", "
                     << problem.objective() << std::endl;

    if (previousStepSuccessful && iteration > 0) {
      problem.computeGradient();
    }

    // gradient-norm stopping condition
    if (problem.gradientNormCached() < epsilonG) {
	  if ( verbose )
	      Log::debug() << "first order: epsilonG" << std::endl;
      break;
    }

    // compute step
    Vector step(problem.gradientCached());
    step *= (-delta / problem.gradientNormCached());

    // minimal change stopping condition
    if (changeIsMinimal(step, problem.position())) {
	  if ( verbose )
	      Log::debug() << "first order: change is min" << std::endl;
      break;
    }

    if (previousStepSuccessful) {
      normOldPosition = problem.position().normL2();
    }

    // set new position (to be verified later)
    problem.applyStep(step);

    // compute reduction rate
    const double newError = problem.objective();

	if ( verbose )
      Log::debug() << iteration << " optimizeFirst(): "
         << " " << newError
         << ", " << previousError
//         << problem.position()
//         << ", " << problem.gradientCached()
//         << ", " << step
//         << " -- " << problem.gradientNormCached()
         << ", " << epsilonG
         << ", " << delta
         << std::endl;

//Log::debug() << "newError: " << newError << std::endl;
    const double errorReduction = newError - previousError;
    const double psi = problem.gradientCached().scalarProduct(step);
    double rho;
    if (std::fabs(psi) <= epsilonRho
        && std::fabs(errorReduction) <= epsilonRho) {
	  if ( verbose )
		  Log::debug() << iteration << " optimizeFirst(): rho set to 1.0" << std::endl;
      rho = 1.0;
    } else {
      rho = errorReduction / psi;
	  if ( verbose )
		  Log::debug() << iteration << " optimizeFirst(): rho set to " << rho << " error reduction = " << errorReduction << std::endl;
    }

    // NOTE psi check should not really be needed
    if (rho < eta1 || psi >= 0.0 ) {
	  if ( verbose )
		  Log::debug() << iteration << " optimizeFirst(): step failed" << std::endl;
      previousStepSuccessful = false;
      problem.unapplyStep(step);
      delta = alpha2 * step.normL2();
    } else {
	  if ( verbose )
		  Log::debug() << iteration << " optimizeFirst(): step accepted" << std::endl;
      previousStepSuccessful = true;
      previousError = newError;
      if (rho >= eta2) {
        const double newDelta = alpha1 * step.normL2();
        if (newDelta > delta) {
          delta = newDelta;
        }
      } // else: don't change delta
    }

    // delta stopping condition
    if (delta < epsilonDelta * normOldPosition) {
	  if ( verbose )
        Log::debug() << "fist order: stop delta small" << std::endl;
      break;
    }
  }
}

double FirstOrderTrustRegion::computeInitialDelta(const double gradientNorm) {
  double result;
  if (isZero(gradientNorm)) {
    result = 1.0;
  } else {
    result = gradientNorm / 10.0;
  }
  if (result < deltaMin) {
    result = deltaMin;
  }
  return result;
}

}; // namespace NICE
