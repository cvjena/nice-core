/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libimagedisplay - A library for image and video display
 * See file License for license information.
 */
#ifndef _IMAGEDISPLAY_DEFAULTMAINWINDOW_H
#define _IMAGEDISPLAY_DEFAULTMAINWINDOW_H

#include <qwidget.h>
#include <qtimer.h>
#include <memory>

namespace NICE {

/**
 * A simple Qt widget used by \c QtFramework as default main window
 * if no custom widget is specified.
 *
 * @author Ferid Bajramovic
 * 
 * @note
 * This class is experimental and might change in the future.
 */
class DefaultMainWindow : public QWidget {
  Q_OBJECT;
public:
  /**
   * Constructor.
   * @param title If not NULL, this will be used as the main window's caption.
   */
  DefaultMainWindow(const char* title = NULL);
  
  //! Destructor
  virtual ~DefaultMainWindow();

protected:
  /** 
   * Override this method to handle timer events.
   * @param nextSleepMS Change this value to change the delay until 
   *        the next call to \c loop(). Set to -1 to stop the timer, so
   *        \c loop will not be called any more.
   */
  virtual void loop(int& nextSleepMS);

private slots:
  //! receives timer signals
  void timerSlot();

private:
  //! A timer to call \c loop()
  std::auto_ptr<QTimer> timer;
  
  //! The current delay time of the timer.
  int timerIntervalMS;
};

} // namespace
#endif /* _IMAGEDISPLAY_DEFAULTMAINWINDOW_H */
