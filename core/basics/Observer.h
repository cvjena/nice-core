#ifndef _OBSERVER_FBASICS_H
#define _OBSERVER_FBASICS_H

#include <string>

namespace NICE {

class Observable;
  
/**
 * Base class for Observer as in Observer-pattern.
 * 
 * @author Ferid Bajramovic (ferid [dot] bajramovic [at] informatik [dot] uni-jena [dot] de)
 */
class Observer {
public:
  inline Observer() : observed(NULL) {}

  virtual ~Observer();

protected:
  inline Observable* getObserved() const { return observed; }

  /**
   * Called by Observable when its state has changed.
   */
  virtual void notified() = 0;
  
private:
  Observable* observed;
  
  inline void setObserved(Observable* _observed) {
    observed = _observed;
  }
  
  friend class Observable;
};

} // namespace

#include <core/basics/Observable.h>

#endif // _OBSERVER_FBASICS_H
