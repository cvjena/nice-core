/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libimagedisplay - A library for image and video display
 * See file License for license information.
 */
#ifndef _SIMPLESELECTOR_SIMPLESELECTOR_H
#define _SIMPLESELECTOR_SIMPLESELECTOR_H

#include <vector>
#include <memory>
#include <map>

#include <core/image/ColorImageT.h>
#include <core/image/ImageT.h>
#include <core/image/RectT.h>
#include <core/image/ColorT.h>

#include <core/imagedisplay/ImageDisplay.h>
#include <core/imagedisplay/QtFramework.h>

namespace NICE {

/**
 * SimpleSelector is a simple image display widget which
 * supports the selection (and display) of labeled rectangles
 * and points.
 *
 * @author Erik Rodner (Erik [dot] Rodner [at] uni-jena [dot] de)
 *
 * @note
 * This class is experimental and might change in the future.
 */
class SimpleSelector : public ImageDisplay {
  Q_OBJECT;
public:

  //! Default constructor
  SimpleSelector ( bool drawRectangle = false, 
		   bool drawCross = true,
		   int m_maxColors = 1,
		   QWidget* parent = NULL, 
		   const char* name = NULL,
		   Qt::WFlags flags = 0);

  //! Destructor of SimpleSelector
  virtual ~SimpleSelector();

  //! get selected rectangles
  const std::vector< NICE::RectT<double> > & getRectangles(void) const
  { return m_rectangles; }

  //! add a rectangle
  void addRectangle ( const NICE::RectT<double> & rectangle, int color );

  //! get colors of all selected rectangles
  const std::vector< int > & getColors(void) const
  { return m_rectanglesColor; }

protected:

  /** print markers and rectangle boundaries */
  virtual void paintGLObjects(void);

 /** 
   * called by contextMenuEvent(), use this to include additional
   * menu items
   */
  void addExtraMenuItems ( QMenu *popupMenu );

  //! set current marker color
  void setCurrentColor ( int color );

private slots:
 /**
   * A rectangle (\c left, \c top, \c right, \c bottom) has been drawn
   * by the user.
   * @note A single click results in a degenerate rectangle.
   *       Thus, single clicks can also be handled:
   *       use point (\c left, \c top).
   */
  void rectSelect(float left, float top, float right, float bottom);

  //! slot needed for the context menu
  void menuActivated ( QAction* action );

  //! dummy slot for menu item insertion
  void dummy(void);

private:

  //! current color
  int m_markColor;
  //! maximum number of colors
  int m_maxColors;

  //! draw selected rectangles
  bool m_drawRectangle;
  //! draw selected points (left, top)
  bool m_drawCross;
  //! size of crosses
  int  m_crossSize;

  //! selected rectangles
  std::vector< NICE::RectT<double> > m_rectangles;
  //! corresponding colors of selected rectangles
  std::vector<int> m_rectanglesColor;

  //! this map maps menu item ids to colors
  std::map<QAction*, int> colorMenuMap;

};

/**
 * Create a \c SimpleSelector window (which allows rectangle
 * and point selection), display the \c image 
 * and finally give control to Qt.
 * @param rectangles list of all selected rectangles
 * @param colors corresponding colors of all selected points
 * @param title window title
 * @param maximum number of colors
 */
template <class ImageType>
void selectColoredRectangles (  const ImageType & image,
                                std::vector<NICE::RectT<double> > & rectangles, 
                                std::vector<int> & colors,
                                const std::string & title,
                                const int maxColors) 
{
  if (qApp == NULL) {
    QtFramework::instance();
  }

  SimpleSelector* display = new SimpleSelector( true, false, maxColors );
  display->setCaption(title.c_str());
  display->setImage(&image, true);
  display->show();
 
  QtFramework::exec ( false );

  rectangles = display->getRectangles();
  colors = display->getColors();

  delete display;
}

/**
 * Create a \c SimpleSelector window (which allows rectangle
 * and point selection), display the \c image 
 * and finally give control to Qt.
 * @param rectangles list of all selected rectangles
 * @param title window title
 */
template <class ImageType>
void selectRectangles (  const ImageType & image, std::vector<NICE::RectT<double> > & rectangles, 
			 const std::string & title )
{
    std::vector<int> colors;
    selectColoredRectangles ( image, rectangles, colors, title, 1 );
}

/**
 * Create a \c SimpleSelector window (which allows rectangle
 * and point selection), display the \c image 
 * and finally give control to Qt.
 * @param points list of all selected points
 * @param colors corresponding colors of all selected points
 * @param title window title
 * @param maximum number of colors
 */
template <class ImageType>
void selectColoredPoints (  const ImageType & image,
                            std::vector<NICE::CoordT<double> > & points, 
                            std::vector<int> & colors,
                            const std::string & title,
                            const int maxColors) 
{
  if (qApp == NULL) {
    QtFramework::instance();
  }

  SimpleSelector* display = new SimpleSelector( false, true, maxColors );
  display->setCaption(title.c_str());
  display->setImage(&image, true);
  display->show();
 
  QtFramework::exec ( false );

  const std::vector<NICE::RectT<double> > & rectangles = display->getRectangles();
  colors = display->getColors();

  points.clear();
  for ( std::vector<NICE::RectT<double> >::const_iterator i = rectangles.begin(); i != rectangles.end(); i++ )
  {
      points.push_back ( NICE::CoordT<double> ( i->left, i->top ) ); 
  }

  //don't waste memory
  delete display;
}

/**
 * Create a \c SimpleSelector window (which allows rectangle
 * and point selection), display the \c image 
 * and finally give control to Qt.
 * @param points list of all selected points
 * @param title window title
 */
template <class ImageType>
void selectPoints (  const ImageType & image,
                     std::vector<NICE::CoordT<double> > & points,
                     const std::string & title)
{
    std::vector<int> colors;
    selectColoredPoints ( image, points, colors, title, 1 );
}


} // namespace
#endif /* _SIMPLESELECTOR_SIMPLESELECTOR_H */

