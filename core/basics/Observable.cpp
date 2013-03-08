#include "core/basics/Observable.h"

namespace NICE {

void Observable::notifyObservers() {
  for (unsigned int i = 0; i < observers.size(); i++) {
    observers[i]->notified();
  }
}

void Observable::removeObserver(Observer* observer) {
  for (std::vector<Observer*>::iterator iter = observers.begin();
       iter != observers.end();
       ++iter) {
    if (*iter == observer) {
      observers.erase(iter);
     // --iter; don't know, this line doesnt make sense... code crashes when not uncommenting this line
      break;
    }
  }
}

} // namespace
