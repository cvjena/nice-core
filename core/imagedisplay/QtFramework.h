/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libimagedisplay - A library for image and video display
 * See file License for license information.
 */
#ifndef _IMAGEDISPLAY_QTFRAMEWORK_H
#define _IMAGEDISPLAY_QTFRAMEWORK_H

#include <qapplication.h>
#include <core/basics/NonCopyable.h>
#include <memory>

namespace NICE {

/**
 * A simple framework for Qt applications.
 *
 * @author Ferid Bajramovic
 * 
 * @note
 * This class is experimental and might change in the future.
 */
class QtFramework : private NonCopyable {
private:
  /**
   * Constructor: also creates the QApplication object.
   * @note This constructor will pass dummy commandline options to Qt!!!
   */
  QtFramework();

  /**
   * Constructor: also creates the QApplication object.
   */
  QtFramework(int& argc, char** argv);
  
public:
  //! Destructor
  virtual ~QtFramework();

  static inline QtFramework& instance() {
    if (theInstance.get() == NULL) {
      theInstance.reset(new QtFramework());
    }
    return *theInstance;
  }

  static inline bool isInstanceInitialized() {
    return theInstance.get() != NULL;
  }
  
  static inline void init(int& argc, char** argv) {
    if (theInstance.get() != NULL) {
      return;
    }
    theInstance.reset(new QtFramework(argc, argv));
  }

  static inline int exec(bool showDefaultWindow = true) {
    return instance().nonstaticExec(showDefaultWindow);
  }

  /**
   * Start the framework (and thus Qt).
   * @param _mainWindow the main window (Ownership is taken!)
   * @param showMainWindow automatically show the main window?
   */
  static inline int exec(std::auto_ptr<QWidget> _mainWindow,
                         bool showMainWindow = true) {
    return instance().nonstaticExec(_mainWindow, showMainWindow);
  }

  /**
   * Start the framework (and thus Qt).
   * @param _mainWindow the main window (Ownership is taken!)
   * @param showMainWindow automatically show the main window?
   */
  static inline int exec(QWidget* _mainWindow, bool showMainWindow = true) {
    return instance().nonstaticExec(_mainWindow, showMainWindow);
  }
  
  /**
   * Access the main window.
   */
  inline QWidget* getMainWindow() const {
    return mainWindow;
  }

private:
  static std::auto_ptr<QtFramework> theInstance;

  int doExec(bool showMainWindow);

  /**
   * Start the framework (and thus Qt) with a default main window.
   * @param showDefaultWindow automatically show the main window?
   */
  int nonstaticExec(bool showDefaultWindow = true);

  /**
   * Start the framework (and thus Qt).
   * @param _mainWindow the main window (Ownership is taken!)
   * @param showMainWindow automatically show the main window?
   */
  int nonstaticExec(std::auto_ptr<QWidget> _mainWindow, 
                    bool showMainWindow = true);

  /**
   * Start the framework (and thus Qt).
   * @param _mainWindow the main window (Ownership is taken!)
   * @param showMainWindow automatically show the main window?
   */
  int nonstaticExec(QWidget* _mainWindow, bool showMainWindow = true);

  //std::auto_ptr<QApplication> application;
  QApplication* application;

  //std::auto_ptr<QWidget> mainWindow;
  QWidget* mainWindow;

  int fake_argc;
  char **fake_argv;
};

} // namespace
#endif /* _IMAGEDISPLAY_QTFRAMEWORK_H */
