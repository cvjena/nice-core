#ifndef _IMAGEDISPLAY_SDLWIDGET_H
#define _IMAGEDISPLAY_SDLWIDGET_H

//#include <boost/utility.hpp>
#include <qwidget.h>

#include <core/image/ColorImageT.h>
#include <core/image/ImageT.h>
#include <core/basics/NonCopyable.h>
#include <memory>

struct SDL_Surface;

namespace NICE {

/**
 * High performance video display using SDL.
 * 
 * @note This class is experimental!
 * 
 * @note
 * There must not be more than one instance of ImageDisplaySDL.
 * Additional instances will not display anything.
 * 
 * @note
 * This class is currently NOT thread safe!
 *
 * @note
 * This class is HIGHLY experimental and might change in the future.
 * 
 * @author Ferid Bajramovic
 */
class ImageDisplaySDL : public QWidget, private NICE::NonCopyable {
  Q_OBJECT
public:
  ImageDisplaySDL(QWidget* parent = NULL, const char* name = NULL);
  
  virtual ~ImageDisplaySDL();

  void setImage(ColorImage* image, const bool copy = false);

protected:
  void resizeEvent(QResizeEvent *);
  void paintEvent(QPaintEvent *);

private:
  SDL_Surface* screen;
  
  NICE::ColorImage* colorImage;
  
  static bool sdlDisplayActive;
};

} // namespace
#endif // _IMAGEDISPLAY_SDLWIDGET_H
