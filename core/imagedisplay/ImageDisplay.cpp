/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libimagedisplay - A library for image and video display
 * See file License for license information.
 */
#include "core/imagedisplay/ImageDisplay.h"

#include <iostream>

#ifdef NICE_USELIB_GLUT
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#endif
#endif

#include <qcursor.h>
#include <QFileDialog>
#include <qapplication.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qcheckbox.h>
#include <QContextMenuEvent>
#include <QMouseEvent>
#include <QMenu>

#include <core/basics/Exception.h>
#include <core/basics/FileName.h>
#include <core/imagedisplay/QtFramework.h>
#include <core/imagedisplay/ImageDisplayManager.h>

#include <core/imagedisplay/OverlayColors.h>

// we need this function for overlays
#include <core/image/Convert.h>

namespace NICE {

ImageDisplay::ImageDisplay ( QWidget* parent, const char* name, Qt::WFlags flags )
    : QGLWidget ( parent, NULL, flags ),
    image ( NULL ),
    colorImageBuffer ( NULL ),
    grayImageBuffer ( NULL ),
    copied ( false ),
    isDragging ( false ),
    buf_overlayImage ( NULL )
{
  if ( parent == NULL ) {
    ImageDisplayManager::instance().registerWidget ( this );
  }
  updateGL();
}

ImageDisplay::~ImageDisplay() {
  //ImageDisplayManager::instance().unregisterWidget(this);
  if ( copied && colorImageBuffer != NULL ) {
    delete colorImageBuffer;
  }
  if ( copied && grayImageBuffer != NULL ) {
    delete grayImageBuffer;
  }
  if ( buf_overlayImage != NULL )
    delete [] buf_overlayImage;
}

void ImageDisplay::setImage ( const NICE::ColorImage* _image,
                              const bool copy ) {
  frameRateCounter.newFrame();
  if ( frameRateCounter.getCounter() == 0 ) {
    doSetCaption();
  }

  if ( sequenceWriter.get() != NULL ) {
    sequenceWriter->writeColorImage ( *_image );
  }

  int oldImageWidth = 0;
  int oldImageHeight = 0;
  if ( image != NULL ) {
    oldImageWidth = image->width();
    oldImageHeight = image->height();
  }

  if ( copied && grayImageBuffer != NULL ) {
    delete grayImageBuffer;
    grayImageBuffer = NULL;
  }

  isColor = true;

  if ( copy ) {
    if ( copied && colorImageBuffer != NULL ) {
      if ( _image->width() != colorImageBuffer->width()
           || _image->height() != colorImageBuffer->height() ) {
        delete colorImageBuffer;
        colorImageBuffer
        = new NICE::ColorImage ( *_image, NICE::GrayColorImageCommonImplementation::noAlignment );
      } else {
        colorImageBuffer->copyFrom ( *_image, NICE::GrayColorImageCommonImplementation::noAlignment );
      }
    } else {
      copied = true;
      colorImageBuffer
      = new NICE::ColorImage ( *_image, NICE::GrayColorImageCommonImplementation::noAlignment );
    }
    image = colorImageBuffer;
  } else {
    if ( copied && colorImageBuffer != NULL ) {
      delete colorImageBuffer;
      colorImageBuffer = NULL;
    }
    image = _image;
  }
  if ( oldImageWidth != image->width() || oldImageHeight != image->height() ) {
    resize ( image->width(), image->height() );
  }
  updateGL();
}

void ImageDisplay::setImage ( const NICE::Image* _image,
                              const bool copy ) {
  frameRateCounter.newFrame();
  if ( frameRateCounter.getCounter() == 0 ) {
    doSetCaption();
  }

  if ( sequenceWriter.get() != NULL ) {
    sequenceWriter->writeGrayImage ( *_image );
  }

  int oldImageWidth = 0;
  int oldImageHeight = 0;
  if ( image != NULL ) {
    oldImageWidth = image->width();
    oldImageHeight = image->height();
  }

  if ( copied && colorImageBuffer != NULL ) {
    delete colorImageBuffer;
    colorImageBuffer = NULL;
  }

  isColor = false;

  if ( copy ) {
    if ( copied && grayImageBuffer != NULL ) {
      if ( _image->width() != grayImageBuffer->width()
           || _image->height() != grayImageBuffer->height() ) {
        delete grayImageBuffer;
        grayImageBuffer
        = new NICE::Image ( *_image, NICE::GrayColorImageCommonImplementation::noAlignment );
      } else {
        grayImageBuffer->copyFrom ( *_image, NICE::GrayColorImageCommonImplementation::noAlignment );
      }
    } else {
      copied = true;
      grayImageBuffer
      = new NICE::Image ( *_image, NICE::GrayColorImageCommonImplementation::noAlignment );
    }
    image = grayImageBuffer;
  } else {
    if ( copied && grayImageBuffer != NULL ) {
      delete grayImageBuffer;
      grayImageBuffer = NULL;
    }
    image = _image;
  }
  if ( oldImageWidth != image->width() || oldImageHeight != image->height() ) {
    resize ( image->width(), image->height() );
  }
  updateGL();
}

void ImageDisplay::setOverlayImage ( const NICE::Image* overlayImage ) {
  bool alloc = false;

  if ( buf_overlayImage == NULL )
    alloc = true;
  else if ( ( overlayImageWidth != overlayImage->width() ) ||
            ( overlayImageHeight != overlayImage->height() ) )
    alloc = true;

  if ( alloc ) {
    if ( buf_overlayImage != NULL )
      delete [] buf_overlayImage;

    overlayImageWidth = overlayImage->width();
    overlayImageHeight = overlayImage->height();

    // RGBA image: 4 channels
    buf_overlayImage = new unsigned char[ overlayImageWidth *
                                          overlayImageHeight * 4 ];
  }
  long int k = 0;
  for ( int y = 0; y < overlayImage->height(); y++ ) {
    const unsigned char* end = overlayImage->getPixelPointerYEnd ( y );
    int colstep = overlayImage->columnStepsize();
    for ( const unsigned char* p = overlayImage->getPixelPointerY ( y ); p != end;
          p = ( const unsigned char * ) ( ( ( Ipp8u * ) p ) + colstep ) )
    {
      unsigned char overlayValue = *p;
      unsigned char r, g, b, alpha;
      if ( overlayValue <= 0 ) {
        r = 0;
        b = 0;
        g = 0;
        alpha = 0;
      } else {
        int colorValue = overlayValue % overlayColorTableNumEntries;

        r = overlayColorTable[colorValue][0];
        g = overlayColorTable[colorValue][1];
        b = overlayColorTable[colorValue][2];
        alpha = 255;
      }
      buf_overlayImage[k++] = r;
      buf_overlayImage[k++] = g;
      buf_overlayImage[k++] = b;
      buf_overlayImage[k++] = alpha;
    }
  }
  updateGL();
}

void ImageDisplay::repaint() {
  updateGL();
}

void ImageDisplay::paintGL() {
#ifdef NICE_USELIB_GLUT
  setGLProjection();
  if ( image != NULL ) {
    glPixelStorei ( GL_PACK_ALIGNMENT, 1 );
    glPixelStorei ( GL_UNPACK_ALIGNMENT, 1 );
    glPixelZoom ( ( GLfloat ) width() / ( ( GLfloat ) image->width() ),
                  ( ( GLfloat ) - height() ) / ( ( GLfloat ) image->height() ) );
    glRasterPos2f ( 0, height() - 0.5 );
    if ( isColor ) {
      glDrawPixels ( image->width(), image->height(),
                     GL_RGB, GL_UNSIGNED_BYTE,
                     image->getPixelPointer() );
    } else {
      glDrawPixels ( image->width(), image->height(),
                     GL_LUMINANCE, GL_UNSIGNED_BYTE,
                     image->getPixelPointer() );
    }
  } else {
    glClearColor ( 0.0, 0.0, 0.0, 0.0 );
    glClear ( GL_COLOR_BUFFER_BIT );
    glFlush();
  }

  if ( buf_overlayImage != NULL ) {
    if ( image == NULL ) {
      glPixelStorei ( GL_PACK_ALIGNMENT, 1 );
      glPixelStorei ( GL_UNPACK_ALIGNMENT, 1 );
      glPixelZoom ( ( GLfloat ) width() / ( ( GLfloat ) overlayImageWidth ),
                    ( ( GLfloat ) - height() ) / ( ( GLfloat ) overlayImageHeight ) );
      glRasterPos2f ( 0, height() - 0.5 );
    }

    glEnable ( GL_BLEND );
    glBlendFunc ( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    glDrawPixels ( overlayImageWidth, overlayImageHeight,
                   GL_RGBA, GL_UNSIGNED_BYTE, buf_overlayImage );
    glDisable ( GL_BLEND );
    glFlush();
  }

  if ( isDragging && drawSelectionRect ) {
    glLineWidth ( 1 );
    glEnable ( GL_LINE_STIPPLE );
    glLineStipple ( 1, 0x00FF );
    glColor4f ( 1, 1, 1, 1 );
//    // Antialiased Points
//    glEnable(GL_POINT_SMOOTH);
//    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
//    // Antialiased Lines
//    glEnable(GL_LINE_SMOOTH);
//    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glBegin ( GL_LINE_LOOP );
    glVertex2f ( dragX, height() - dragY );
    glVertex2f ( dragX, height() - dropY );
    glVertex2f ( dropX, height() - dropY );
    glVertex2f ( dropX, height() - dragY );
    glEnd();
    glDisable ( GL_LINE_STIPPLE );
    glFlush();
  }

  if ( texts.size() > 0 ) {
	  glEnable ( GL_BLEND );
    glBlendFunc ( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    for ( uint i = 0; i < texts.size(); ++i ) {

      Text& text = texts[i];

      glColor4ub ( text.color[0], text.color[1], text.color[2], 255 );

      float x = float ( text.x ) * float ( width() ) / float ( image->width() );
      float y = float ( text.y ) * float ( height() ) / float ( image->height() );

      glRasterPos2f ( x, height() - y - 0.5 );

      void* font = GLUT_BITMAP_HELVETICA_10;//(*i)->font;

      for ( uint j = 0; j < text.text.size(); ++j )
        glutBitmapCharacter ( font, text.text[j] );
    }

    glDisable ( GL_BLEND );
    glFlush();
  }
#else
     fthrow(Exception,"GLUT lib not availabe, recompile using GLUT!");
#endif

  paintGLObjects();
}

void ImageDisplay::setGLProjection ( void ) {
#ifdef NICE_USELIB_GLUT  
  glViewport ( 0, 0, width(), height() );
  glMatrixMode ( GL_PROJECTION );
  glLoadIdentity();
  gluOrtho2D ( 0.0, ( GLdouble ) width(), 0.0, ( GLdouble ) height() );
#else
	  fthrow(Exception,"GLUT lib not availabe, recompile using GLUT!");
#endif

}

void ImageDisplay::paintGLObjects ( void ) {
}

void ImageDisplay::mousePressEvent ( QMouseEvent* event ) {
  QGLWidget::mousePressEvent ( event );
  startDrag ( event->x(), event->y() );
}

void ImageDisplay::mouseMoveEvent ( QMouseEvent* event ) {
  QGLWidget::mouseMoveEvent ( event );
  dragging ( event->x(), event->y() );
}

void ImageDisplay::mouseReleaseEvent ( QMouseEvent* event ) {
  QGLWidget::mouseReleaseEvent ( event );
  makeDrop ( event->x(), event->y() );
  float left = dragX * ( image->width() / ( float ) width() );
  float right = dropX * ( image->width() / ( float ) width() );
  float top = dragY * ( image->height() / ( float ) height() );
  float bottom = dropY * ( image->height() / ( float ) height() );

  if ( left > right ) {
    std::swap ( left, right );
  }
  if ( top > bottom ) {
    std::swap ( top, bottom );
  }

  emit rectSelect ( left, top, right, bottom );
}

void ImageDisplay::startDrag ( int x, int y ) {
  isDragging = true;
  dragX = x;
  dragY = y;
  dropX = x;
  dropY = y;
  updateGL();
}

void ImageDisplay::dragging ( int x, int y ) {
  if ( isDragging ) {
    dropX = x;
    dropY = y;
    updateGL();
  }
}

void ImageDisplay::makeDrop ( int x, int y ) {
  if ( isDragging ) {
    isDragging = false;
    dropX = x;
    dropY = y;
    updateGL();
  }
}

void ImageDisplay::contextMenuEvent ( QContextMenuEvent* event ) {

  QMenu* popupMenu = new QMenu ( this );

  addExtraMenuItems ( popupMenu );

  popupMenu->addAction("&Save Image", this, SLOT ( menuSave() ), Qt::CTRL + Qt::Key_S);
  popupMenu->addAction("&Restore aspect ratio", this, SLOT ( menuAspectRatio ), Qt::CTRL + Qt::Key_A);

  popupMenu->addSeparator();

  popupMenu->addAction ( "Start &capturing image sequence", this, SLOT ( menuStartCapture() ) );
  popupMenu->addAction ( "Sto&p capturing", this, SLOT ( menuStopCapture() ) );

  popupMenu->exec ( QCursor::pos() );
  delete popupMenu;
}

void ImageDisplay::addExtraMenuItems ( QMenu *popupMenu )
{
}

void ImageDisplay::menuAspectRatio() {
  if ( image != NULL ) {
    resize ( size().width(), size().width() * image->height() / image->width() );
  }
}

void ImageDisplay::menuSave() {
  QString s = QFileDialog::getSaveFileName(this,
		"Save file dialog",
		"",
		"Images (*.ppm, *.pgm, *.png, *.jpg)");
  if ( s.isNull() ) {
    return;
  }

  NICE::FileName filename ( s.toLocal8Bit() );
  const std::string ext = filename.extractExtension().str();
  const bool extensionOk
  = ( ext == std::string ( ".ppm" ) || ext == std::string ( ".pgm" )
      || ext == std::string ( ".png" ) || ext == std::string ( ".jpg" ) );
  if ( !extensionOk ) {
    if ( isColor ) {
      filename.setExtension ( ".ppm" );
    } else {
      filename.setExtension ( ".pgm" );
    }
  }
  image->write ( filename.str() );
}

void ImageDisplay::menuStartCapture() {
  if ( dialog.get() == NULL ) {
    dialog.reset ( new CaptureDialog ( this, "Capture Dialog" ) );
    dialog->setWindowTitle ( "Capture: " + captionBuffer );
    connect ( ( QObject* ) dialog->capture(), SIGNAL ( started() ),
              this, SLOT ( dialogStartCapture() ) );
    connect ( ( QObject* ) dialog->capture(), SIGNAL ( stopped() ),
              this, SLOT ( dialogStopCapture() ) );
  }
  dialog->show();
}

void ImageDisplay::menuStopCapture() {
  if ( dialog.get() != NULL ) {
    dialog->capture()->buttonStopClicked();
  }
}

void ImageDisplay::dialogStartCapture() {
  sequenceWriter.reset (
    new ImageFileListWriter ( dialog->capture()->directoryName(),
                              dialog->capture()->extensionName(),
                              dialog->capture()->isBuffered() ) );
}

void ImageDisplay::dialogStopCapture() {
  sequenceWriter.reset ( NULL );
}

void ImageDisplay::setCaption ( const QString& s ) {
  captionBuffer = s;
  doSetCaption();
}

void ImageDisplay::doSetCaption() {
  std::stringstream s;
  s.precision ( 1 );
  s << std::fixed << captionBuffer.toAscii().constData()
  << " (FPS: " << frameRateCounter.getFrameRate() << ")";
  //std::cerr << "ImageDisplay::doSetCaption(): " << s.str() << std::endl;
  QWidget::setWindowTitle ( s.str().c_str() );
}


ImageDisplay* displayImage ( const NICE::ColorImage* image,
                             const std::string& title,
                             const bool copy ) {
  // make sure Qt is initialized
  if ( qApp == NULL ) {
    QtFramework::instance();
  }

//   QWidget* mainWindow = NULL;
//   if (QtFramework::isInstanceInitialized()) {
//     mainWindow = QtFramework::instance().getMainWindow();
//   }
//   ImageDisplay* display
//       = new ImageDisplay(mainWindow, title.c_str(),
//                          (unsigned int)Qt::WType_TopLevel);

  ImageDisplay* display = new ImageDisplay();
  display->setCaption ( title.c_str() );
  display->setImage ( image, copy );
  display->show();
  return display;
}

ImageDisplay* displayImage ( const NICE::Image* image,
                             const std::string& title,
                             const bool copy ) {
  // make sure Qt is initialized
  if ( qApp == NULL ) {
    QtFramework::instance();
  }

//   QWidget* mainWindow = NULL;
//   if (QtFramework::isInstanceInitialized()) {
//     mainWindow = QtFramework::instance().getMainWindow();
//   }
//   ImageDisplay* display
//       = new ImageDisplay(mainWindow, title.c_str(),
//                          (unsigned int)Qt::WType_TopLevel);

  ImageDisplay* display = new ImageDisplay();
  display->setCaption ( title.c_str() );
  display->setImage ( image, copy );
  display->show();
  return display;
}

ImageDisplay* displayImageOverlay ( const NICE::Image* image,
                                    const NICE::Image *overlay,
                                    const std::string& title,
                                    const bool copy )
{
  if ( ( image->width() != overlay->width() ) ||
       ( image->height() != overlay->height() ) )
  {
    fthrow ( Exception, "Image and overlay image must have the same dimensions." );
  }

  // make sure Qt is initialized
  if ( qApp == NULL ) {
    QtFramework::instance();
  }

  ImageDisplay *display = new ImageDisplay();
  display->setCaption ( title.c_str() );
  display->setImage ( image, copy );
  display->setOverlayImage ( overlay );
  display->show();

  return display;
}

ImageDisplay* displayImageOverlay ( const NICE::ColorImage* image,
                                    const NICE::Image *overlay,
                                    const std::string& title,
                                    const bool copy )
{
  if ( ( image->width() != overlay->width() ) ||
       ( image->height() != overlay->height() ) )
  {
    fthrow ( Exception, "Image and overlay image must have the same dimensions." );
  }

  // make sure Qt is initialized
  if ( qApp == NULL ) {
    QtFramework::instance();
  }

  ImageDisplay *display = new ImageDisplay();
  display->setCaption ( title.c_str() );
  display->setImage ( image, copy );
  display->setOverlayImage ( overlay );
  display->show();

  return display;
}

void showImage ( const NICE::Image& image,
                 const std::string& title,
                 const bool copy ) {
  // display image and wait for the user to close
  // the window
  displayImage ( &image, title, copy );
  QtFramework::exec ( false );
}

void showImage ( const NICE::ColorImage& image,
                 const std::string& title,
                 const bool copy ) {
  // display image and wait for the user to close
  // the window
  displayImage ( &image, title, copy );
  QtFramework::exec ( false );
}

void showImageOverlay ( const NICE::Image & image,
                        const NICE::Image & overlay,
                        const std::string& title,
                        const bool copy )
{
  displayImageOverlay ( &image, &overlay, title, copy );
  QtFramework::exec ( false );
}

void showImageOverlay ( const NICE::ColorImage & image,
                        const NICE::Image & overlay,
                        const std::string& title,
                        const bool copy )
{
  displayImageOverlay ( &image, &overlay, title, copy );
  QtFramework::exec ( false );
}

int ImageDisplay::addText ( int x, int y, const std::string& text,
                            const Color& color ) {

  Text t ( x, y, text, true, color );
  texts.push_back ( t );
  return texts.size() - 1;
}


} // namespace
