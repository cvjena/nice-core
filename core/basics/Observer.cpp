#include "core/basics/Observer.h"

namespace NICE {

Observer::~Observer() {
  if (observed != NULL) {
    observed->removeObserver(this);
  }
}

} // namespace
