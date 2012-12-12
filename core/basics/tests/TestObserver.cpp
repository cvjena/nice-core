#include "TestObserver.h"

using namespace std;
using namespace NICE;

CPPUNIT_TEST_SUITE_REGISTRATION( TestObserver );


void TestObserver::setUp() {
}

void TestObserver::tearDown() {
}

class Thing : public Observable {
public:
  Thing() : value(0) {}
  void setValue(int i) { value = i; notifyObservers(); }
  int getValue() { return value; }
private:
  int value;
};

class Display : public Observer {
public:
  Display(Thing* _thing) {
    duplicate = 0;
    _thing->addObserver(this);
  }
  
  void notified() {
    duplicate = static_cast<Thing*>(getObserved())->getValue();
  }
  
  int getDuplicate() { return duplicate; }

private:
  int duplicate;
};

void TestObserver::testObserver() {
  std::auto_ptr<Thing> thing(new Thing());
  thing->setValue(5);
  CPPUNIT_ASSERT_EQUAL(5, thing->getValue());
  std::auto_ptr<Display> display(new Display(thing.get()));
  thing->setValue(10);
  CPPUNIT_ASSERT_EQUAL(10, thing->getValue());
  CPPUNIT_ASSERT_EQUAL(10, display->getDuplicate());
  thing->removeObserver(display.get());
  thing->setValue(210);
  CPPUNIT_ASSERT_EQUAL(210, thing->getValue());
  CPPUNIT_ASSERT_EQUAL(10, display->getDuplicate());
}
