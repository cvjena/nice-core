/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libimagedisplay - A library for image and video display
 * See file License for license information.
 */
#ifndef _IMAGEDISPLAY_IMAGEDISPLAY_H
#define _IMAGEDISPLAY_IMAGEDISPLAY_H

#include <qgl.h>
#include <qevent.h>
#include <QMouseEvent>
#include <QContextMenuEvent>
#include <QGLWidget>
#include <QMenu>

#include <vector>

#include <core/image/ColorImageT.h>
#include <core/image/ImageT.h>
#include <core/image/ImageFileListWriter.h>
#include <core/basics/NonCopyable.h>
#include <core/basics/FrameRateCounter.h>
#include <core/imagedisplay/CaptureDialog.h>
#include <memory>

namespace NICE {

/**
 * ImageDisplay is a simple image display widget.
 * There is also support for selecting a rectangle in the image using the mouse,
 * which also allows handling single clicks (see \c rectSelect()).
 * Please not that you can use Qt widgets (and thus \c ImageDisplay)
 * as part of another window, but also as a window itself.
 *
 * @author Ferid Bajramovic (ferid [dot] bajramovic [at] informatik [dot] uni-jena [dot] de)
 *         (based on DispImgGL by ???)
 *
 * @note
 * This class is experimental and might change in the future.
 */
class ImageDisplay : public QGLWidget, private NICE::NonCopyable {
  Q_OBJECT;
public:

  class Text {
    public:

        Text(const int _x, const int _y, const std::string& _text,
             const bool _visible, const Color& _color)
            : x(_x), y(_y), text(_text), visible(_visible), color(_color) {
        }

        int x,y;
        std::string text;
        bool visible;
        Color color;
  };

  //! Default constructor
  ImageDisplay(QWidget* parent = NULL, const char* name = NULL,
               Qt::WFlags flags = 0);

  //! Destructor of ImageDisplay
  virtual ~ImageDisplay();

  /**
   * Set the image to be displayed in this window.
   * @param image The image to be displayed.
   * @param copy Create a copy of the image for the display?
   *        If copy == false, the image must have the memory layout
   *        \c AbstractImage::noAlignment. Otherwise the image will not
   *        be displayed correctly. (Note that more precisely the image
   *        must fullfill stepsize == width * 3 which is garanteed for
   *        \c AbstractImage::noAlignment, but may be fullfilled in other
   *        cases as well).
   */
  void setImage(const NICE::ColorImage* image, const bool copy = true);

  /**
   * Set the image to be displayed in this window.
   * @param image The image to be displayed.
   * @param copy Create a copy of the image for the display?
   *        If copy == false, the image must have the memory layout
   *        \c AbstractImage::noAlignment. Otherwise the image will not
   *        be displayed correctly. (Note that more precisely the image
   *        must fullfill stepsize == width which is garanteed for
   *        \c AbstractImage::noAlignment, but may be fullfilled in other
   *        cases as well).
   *
   */
  void setImage(const NICE::Image* image, const bool copy = true);

	inline unsigned int imageWidth ( void )
	{
		if ( image != NULL )
		{
			return image->width();
		}
		return 0;
	}
	
	inline unsigned int imageHeight ( void )
	{
		if ( image != NULL )
		{
			return image->height();
		}
		return 0;
	}
 
 /**
   * Set the overlay image to be displayed in this window.
   * @param image The overlay image to be displayed.
   */
  void setOverlayImage(const NICE::Image* overlayImage );
 
  /**
   * Draw the selection rectangle?
   * Typically this is turned on then connecting to the \c rectSelect signal.
   * @param draw The new setting
   */
  inline void setDrawSelectionRect(bool draw) {
    drawSelectionRect = draw;
  }
  
  NICE::ColorImage * getColorImageBuffer()
  {
    return this->colorImageBuffer;
  }
 
  /**
   * Draw the selection rectangle?
   * @return The current setting
   */
  inline bool isDrawSelectionRect() const {
    return drawSelectionRect;
  }

  virtual void setCaption(const QString& s);

  /**
   * Add a line of text to be display on the image.
   * @param x x-coordinate
   * @param y y-coordinate
   * @param text the text
   * @return id needed to change/remove the text
   */
  inline int addText(int x, int y, const std::string& text) {
    return addText(x, y, text, Color(255, 255, 255));
  }

  /**
   * Add a line of text to be display on the image.
   * @param x x-coordinate
   * @param y y-coordinate
   * @param text the text
   * @param color the color of the text
   * @return id needed to change/remove the text
   */
  int addText(int x, int y, const std::string& text, const Color& color);

  /**
   * Hide a line of text.
   */
  inline void hideText(int id) {
    texts[id].visible = false;
  }

  /**
   * Show a line of text, which has been hidden before.
   */
  inline void showText(int id) {
    texts[id].visible = true;
  }

  /**
   * Remove a line of text.
   */
  inline Text& text(int id) {
    return texts[id];
  }

  inline void removeAllText() {
    texts.clear();
  }

  /**
   * The total number of text lines.
   */
  inline uint numberOfTextLines() const {
    return texts.size();
  }

signals:
  /**
   * A rectangle (\c left, \c top, \c right, \c bottom) has been drawn
   * by the user.
   * @note A single click results in a degenerate rectangle.
   *       Thus, single clicks can also be handled:
   *       use point (\c left, \c top).
   */
  void rectSelect(float left, float top, float right, float bottom);

public slots:
  /**
   * Repaint this widget.
   */
  void repaint();

  /**
   * Save menu item clicked.
   */
  void menuSave();

  /**
   * Start video capture menu item clicked.
   */
  void menuStartCapture();

  /**
   * Stop video capture menu item clicked.
   */
  void menuStopCapture();

  /**
   * Start button clicked in video capture dialog.
   */
  void dialogStartCapture();

  /**
   * Stop button clicked in video capture dialog.
   */
  void dialogStopCapture();

  /**
   * Aspect ratio menu item clicked.
   */
  void menuAspectRatio();

protected:
  /**
   * Implements QGLWidget::paintGL()
   */
  virtual void paintGL();
  
  /**
   * called by paintGL(), use this to change projection mode
   */
  virtual void setGLProjection(void);
  
  /**
   * called by paintGL(), use this to include additional openGL code
   */
  virtual void paintGLObjects(void);

  /** 
   * called by contextMenuEvent(), use this to include additional
   * menu items
   */
  virtual void addExtraMenuItems ( QMenu *popupMenu );

  //! receive mouse events
  virtual void mousePressEvent(QMouseEvent* event);

  //! receive mouse events
  virtual void mouseReleaseEvent(QMouseEvent* event);

  //! receive mouse events
  virtual void mouseMoveEvent(QMouseEvent* event);

private:
  //! capture control dialog
  std::auto_ptr<CaptureDialog> dialog;

protected:
  //! a pointer to the current image
  const NICE::GrayColorImageCommonImplementationT<Ipp8u>* image;

  //! color or gray?
  bool isColor;

  //! buffer for copied a \c ColorImage
  NICE::ColorImage* colorImageBuffer;

  //! buffer for copied a \c Image
  NICE::Image* grayImageBuffer;

  //! has the image been copied
  bool copied;

private:
  //! Draw the selection rectangle?
  bool drawSelectionRect;

  //! Qt event handler
  virtual void contextMenuEvent(QContextMenuEvent* event);

  // handling of mouse input (rect drawing)
  void startDrag(int x, int y);

  // handling of mouse input (rect drawing)
  void makeDrop(int x, int y);

  // handling of mouse input (rect drawing)
  void dragging(int x, int y);

  //! handling of mouse input (rect drawing)
  bool isDragging;

  //! handling of mouse input (rect drawing)
  float dragX;

  //! handling of mouse input (rect drawing)
  float dragY;

  //! handling of mouse input (rect drawing)
  float dropX;

  //! handling of mouse input (rect drawing)
  float dropY;

  //! video capture
  std::auto_ptr<ImageFileListWriter> sequenceWriter;

  //! FPS Counter
  FrameRateCounter frameRateCounter;

  QString captionBuffer;

  void doSetCaption();

  std::vector<Text> texts;

  unsigned char *buf_overlayImage;
  int overlayImageWidth;
  int overlayImageHeight;
};

/**
 * Create an \c ImageDisplay and use it to display \c image.
 * @param image The image to be displayed
 * @param title The title of the display window
 * @param copy Copy the image?
 * @return the new \c ImageDisplay
 * @note This function creates a Qt widget. This means that Qt has to be
 *       initialized before creating the widget \b and that control has
 *       to be passed to Qt before exiting the program.
 *       If Qt has not been initialized, yet
 *       (i.e. no QApplication object has been created, yet),
 *       this function will create a \c NICE::QtFramework object,
 *       which will also initialize Qt (with empty commandline options).
 *       If you want to properly initialize Qt,
 *       use \c NICE::QtFramework::init(int&, char**).
 *       To pass control to Qt before exiting, do \c NICE::QtFramework::exec().
 *       Using \c NICE::QtFramework is opional - you can also directly use Qt.
 *       The example code shows the simplest way to use this function.
 *
 */
ImageDisplay* displayImage(const NICE::ColorImage* image,
                           const std::string& title = "ImageDisplay",
                           const bool copy = true);
/**
 * @example imageDisplayExample.cpp
 * The example code shows the simplest way to use the functions
 * \c displayImage.
 */

/**
 * Create an \c ImageDisplay and use it to display \c image.
 * @see displayImage(const NICE::ColorImage*,const std::string&,const bool)
 */
ImageDisplay* displayImage(const NICE::Image* image,
                           const std::string& title = "ImageDisplay",
                           const bool copy = true);

/**
 * Create an \c ImageDisplay and use it to display \c image with \c overlay as
 * overlay image.
 * @see displayImage(const NICE::ColorImage*,const std::string&,const bool)
 */
ImageDisplay* displayImageOverlay(const NICE::Image* image,
			   const NICE::Image *overlay,
                           const std::string& title = "ImageDisplay",
			   const bool copy = true);

/**
 * Create an \c ImageDisplay and use it to display \c image with \c overlay as
 * overlay image.
 * @see displayImage(const NICE::ColorImage*,const std::string&,const bool)
 */
ImageDisplay* displayImageOverlay(const NICE::ColorImage* image,
			   const NICE::Image *overlay,
                           const std::string& title = "ImageDisplay",
			   const bool copy = true);

/**
 * Display an image and five control to Qt
 * @see displayImage(const NICE::ColorImage*,const std::string&,const bool)
 */
void showImage(const NICE::ColorImage & image,
	       const std::string& title = "ImageDisplay",
	       const bool copy = true);

/**
 * Create an \c ImageDisplay and use it to display \c image and give control to Qt.
 * @see showImage(const NICE::ColorImage*,const std::string&,const bool)
 */
void showImage(const NICE::Image & image,
	       const std::string& title = "ImageDisplay",
	       const bool copy = true);

/**
 * Create an \c ImageDisplay and use it to display \c image with \c overlay 
 * as overlay image and finally give control to Qt.
 * @see showImage(const NICE::ColorImage*,const std::string&,const bool)
 */
void showImageOverlay(const NICE::Image & image,
		const NICE::Image & overlay,
		const std::string& title = "ImageDisplay",
		const bool copy = true);

/**
 * Create an \c ImageDisplay and use it to display \c image with \c overlay 
 * as overlay image and finally give control to Qt.
 * @see showImage(const NICE::ColorImage*,const std::string&,const bool)
 */
void showImageOverlay(const NICE::ColorImage & image,
		const NICE::Image & overlay,
		const std::string& title = "ImageDisplay",
		const bool copy = true);

/**
 * Create an \c ImageDisplay and use it to display \c image.
 * Difference to \c displayImage(const NICE::ColorImage*,const std::string&,const bool):
 * the image will always be copied.
 * @see displayImage(const NICE::ColorImage*,const std::string&,const bool)
 */
inline ImageDisplay* displayImage(const NICE::ColorImage& image,
                                  const std::string& title = "ImageDisplay") {
  return displayImage(&image, title, true);
}

/**
 * Create an \c ImageDisplay and use it to display \c image.
 * Difference to \c displayImage(const NICE::ColorImage*,const std::string&,const bool):
 * the image will always be copied.
 * @see displayImage(const NICE::ColorImage*,const std::string&,const bool)
 */
inline ImageDisplay* displayImage(const NICE::Image& image,
                                  const std::string& title = "ImageDisplay") {
  return displayImage(&image, title, true);
}

} // namespace
#endif /* _IMAGEDISPLAY_IMAGEDISPLAY_H */
