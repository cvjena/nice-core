/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - liboptimization - An optimization/template for new NICE libraries
 * See file License for license information.
 */
/*****************************************************************************/
#include "core/optimization/gradientBased/TrustRegionBase.h"

#include <core/basics/Log.h>

namespace NICE {

TrustRegionBase::~TrustRegionBase() {
}

bool TrustRegionBase::changeIsMinimal(
                                const Vector& step,
                                const Vector& position) {
  bool minimalChange = true;
  bool allZero = true;
  for (unsigned int i = 0; i < position.size(); i++) {
    const double param = position[i];
    const bool zero = isZero(param);
    allZero &= zero;
    if (zero) {
      minimalChange &= std::fabs(step[i]) < epsilonM;
    } else {
      minimalChange &= std::fabs(step[i]) < epsilonM * std::fabs(param);
    }
    //minimalChange &= (zero || std::fabs(step[i]) < epsilonM * std::fabs(param));
  }
  return minimalChange && !allZero;
}


}; // namespace NICE
