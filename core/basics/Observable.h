#ifndef _OBSERVABLE_FBASICS_H
#define _OBSERVABLE_FBASICS_H

#include <vector>
#include <core/basics/Observer.h>

namespace NICE {
  
/**
 * Observable as in Observer-pattern.
 * 
 * @author Ferid Bajramovic (ferid [dot] bajramovic [at] informatik [dot] uni-jena [dot] de)
 */
class Observable {
public:
  //! notify all observers
  void notifyObservers();

  /**
   * Add an Observer (Ownership NOT taken.)
   */
  inline void addObserver(Observer* observer) {
    observers.push_back(observer);
    observer->setObserved(this);
  }

  /**
   * Remove an Observer.
   * @note If the Observer has been added multiple times,
   *       all entries will be removed.
   */
  void removeObserver(Observer* observer);
  
private:
  std::vector<Observer*> observers;
};

} // namespace
#endif // _OBSERVABLE_FBASICS_H
