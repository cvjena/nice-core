/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libimagedisplay - An imagedisplay/template for new NICE libraries
 * See file License for license information.
 */
#include "core/imagedisplay/DefaultMainWindow.h"

#include <qapplication.h>
#include <qpushbutton.h>
#include <core/imagedisplay/ImageDisplayManager.h>
#include <core/imagedisplay/ImageDisplayManagerWidget.h>

namespace NICE {

DefaultMainWindow::DefaultMainWindow(const char* title) : QWidget(NULL, NULL) {
  setCaption(title);

  // create a timer waking us regularly
  timer.reset(new QTimer(this));
  timer->connect(timer.get(), SIGNAL(timeout()),
                 this, SLOT(timerSlot()));
  timerIntervalMS = 0;
  timer->start(timerIntervalMS, false);

  //ImageDisplayManagerWidget* manager =
      //new ImageDisplayManagerWidget(this, "image manager");
}


DefaultMainWindow::~DefaultMainWindow() {
  timer->stop();
}

//void DefaultMainWindow::closeEvent(QCloseEvent* e) {
//  e->accept();
//  qApp->quit();
//}

void DefaultMainWindow::timerSlot() {
  int nextSleepMS = timerIntervalMS;
  loop(nextSleepMS);
  if (nextSleepMS < 0) {
    timer->stop();
  } else if (nextSleepMS != timerIntervalMS) {
    timerIntervalMS = nextSleepMS;
    timer->start(timerIntervalMS, false);
  }
}

void DefaultMainWindow::loop(int& nextSleepMS) {
  nextSleepMS = -1;
}


} // namespace
