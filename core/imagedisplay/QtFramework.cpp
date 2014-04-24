/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libimagedisplay - An imagedisplay/template for new NICE libraries
 * See file License for license information.
 */
#include "core/imagedisplay/QtFramework.h"
#include "core/imagedisplay/DefaultMainWindow.h"

#ifdef NICE_USELIB_GLUT
#include <GL/glut.h>
#endif


namespace NICE {

std::auto_ptr<QtFramework> QtFramework::theInstance;

QtFramework::QtFramework()
    : application(NULL), mainWindow(NULL) {
  fake_argc = 0;
  fake_argv = new char * [1];
  fake_argv[0] = new char [2];
  fake_argv[0][0] = '.';
  fake_argv[0][1] = '\0';
  //application.reset(new QApplication(argc, argv));
  application = new QApplication(fake_argc, fake_argv);

#ifdef NICE_USELIB_GLUT
  glutInit(&fake_argc, fake_argv);
#endif

#ifndef WIN32
#ifndef __clang__
#ifndef __llvm__ 
    std::set_terminate(__gnu_cxx::__verbose_terminate_handler);
#endif
#endif
#endif
}

QtFramework::QtFramework(int& argc, char** argv)
    : application(new QApplication(argc, argv)), mainWindow(NULL) {
  fake_argv = NULL;
#ifdef NICE_USELIB_GLUT
  glutInit(&argc, argv);
#endif

#ifndef WIN32
#ifndef __clang__
#ifndef __llvm__ 
    std::set_terminate(__gnu_cxx::__verbose_terminate_handler);
#endif
#endif
#endif
}

QtFramework::~QtFramework() {

// NOTE Qt widgets don't seem to enjoy being deleted
//  if (mainWindow != NULL) {
//    delete mainWindow;
//    mainWindow = NULL;
//  }

// NOTE Qt's QApplication object doesn't seem to enjoy being deleted
//  if (application != NULL) {
//    delete application;
//    application = NULL;
//  }

  if ( fake_argv != NULL )
  {
    if ( fake_argv[0] != NULL )
      delete [] fake_argv[0];
    delete [] fake_argv;
  }
}

int QtFramework::nonstaticExec(bool showDefaultWindow) {
  //mainWindow.reset(new DefaultMainWindow("LImUn Qt Framework Application"));
  mainWindow = new DefaultMainWindow("LImUn Qt Framework Application");
  return doExec(showDefaultWindow);
}

int QtFramework::nonstaticExec(std::auto_ptr<QWidget> _mainWindow,
                               bool showMainWindow) {
  //mainWindow = _mainWindow;
  mainWindow = _mainWindow.release();
  return doExec(showMainWindow);
}

int QtFramework::nonstaticExec(QWidget* _mainWindow, bool showMainWindow) {
  //mainWindow.reset(_mainWindow);
  mainWindow = _mainWindow;
  return doExec(showMainWindow);
}

int QtFramework::doExec(bool showMainWindow) {
  //application->setMainWidget(mainWindow.get());
  application->setMainWidget(mainWindow);
  if (showMainWindow) {
    mainWindow->show();
  }
//  application->connect(application.get(), SIGNAL(lastWindowClosed()),
//                       application.get(), SLOT(quit()));
  return application->exec();
}

} // namespace
