#ifdef NICE_USELIB_SDL

#include <stdio.h>
#include <iostream>

#include <SDL/SDL.h>
#if defined(Q_WS_X11)
#include <X11/Xlib.h>
#endif

#include "core/imagedisplay/ImageDisplaySDL.h"

using namespace std;

namespace NICE {

bool ImageDisplaySDL::sdlDisplayActive = false;

ImageDisplaySDL::ImageDisplaySDL(QWidget *parent, const char *name)
    : QWidget(parent, name), screen(NULL), colorImage(NULL) {
  if (!sdlDisplayActive) {
    atexit(SDL_Quit);
  }
}

ImageDisplaySDL::~ImageDisplaySDL() {
  if (sdlDisplayActive) {
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
    sdlDisplayActive = false;
  }
}

void ImageDisplaySDL::resizeEvent(QResizeEvent *) {
  // is SDL display already usend by another ImageDisplaySDL?
  if (screen == NULL && sdlDisplayActive) {
    return;
  }

  // We could get a resize event at any time, so clean previous mode
  screen = NULL;
  SDL_QuitSubSystem(SDL_INIT_VIDEO);
  sdlDisplayActive = false;

  // init SDL, do a little hack to get SDL in this Qt widget
  char variable[64];
  sprintf(variable, "SDL_WINDOWID=0x%lx", winId());
  putenv(variable);
  if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0) {
    cerr << "Unable to init SDL: " << SDL_GetError() << endl;
    return;
  }

  // this holds some info about our display
  const SDL_VideoInfo* videoInfo = SDL_GetVideoInfo();

  // the flags to pass to SDL_SetVideoMode()
  int videoFlags = 0;
  int bitDepth = 0;
  if (videoInfo == NULL) {
    // FIXME throw an exception
    cerr << "Video query failed: " << SDL_GetError() << endl;
  } else {
    videoFlags = SDL_GL_DOUBLEBUFFER;

//#define _OPENGL_
    #ifdef _OPENGL_
      bitDepth = 32;
      // use OpenGL
      videoFlags |= SDL_OPENGL;
      //videoFlags |= SDL_OPENGLBLIT;

      // color depth
      SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, bitDepth);
      SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);//Use at least 5 bits of Red
      SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);//Use at least 5 bits of Green
      SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);//Use at least 5 bits of Blue
      SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);//Use at least 16 bits for the depth buffer

      SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);//Enable double buffering
    #else
      bitDepth = 24;
    #endif

    videoFlags |= SDL_HWPALETTE;    // Store the palette in hardware
    videoFlags |= SDL_RLEACCEL;     // use compression to speedup blit-transfer
    videoFlags |= SDL_ANYFORMAT;    // simply use whatever format the hardware can accomodate
    videoFlags |= SDL_ASYNCBLIT;
    //videoFlags |= SDL_RESIZABLE;    // Enable window resizing

    // This checks if hardware blits can be done
    if (videoInfo->blit_hw) {
      videoFlags |= SDL_HWACCEL;
      cerr << "SDL: blit_hw" << endl;
    }

    // This checks to see if surfaces can be stored in memory
    if (videoInfo->hw_available) {
      videoFlags |= SDL_HWSURFACE;
      cerr << "SDL: hw_available" << endl;
    } else {
      videoFlags |= SDL_SWSURFACE;
    }
  }

  // Set the new video mode with the new window size
  //screen = SDL_SetVideoMode(width(), height(), 0, 0);
  screen = SDL_SetVideoMode(width(), height(),
                            bitDepth, videoFlags);
  if (screen == NULL) {
    cerr << "Unable to set video mode: " << SDL_GetError() << endl;
    return;
  } else {
    sdlDisplayActive = true;
  }
  if (!SDL_WM_ToggleFullScreen(screen)) {
    cerr << "SDL: SDL_WM_ToggleFullScreen(screen) failed." << endl;
  }
}

void ImageDisplaySDL::paintEvent(QPaintEvent *) {
#if defined(Q_WS_X11)
  // Make sure we're not conflicting with drawing from the Qt library
  XSync(QPaintDevice::x11Display(), FALSE);
#endif
  if (screen != NULL && colorImage != NULL) {
    // Lock surface if needed
//    if (SDL_MUSTLOCK(screen)) {
//      if (SDL_LockSurface(screen) < 0) {
//        return;
//      }
//    }

    SDL_Surface* sdlImage
      = SDL_CreateRGBSurfaceFrom(colorImage->getPixelPointer(),
                                 colorImage->width(),
                                 colorImage->height(),
                                 24,
                                 colorImage->getStepsize(),
#if SDL_BYTEORDER == SDL_LIL_ENDIAN
                                 0x000000ff, 0x0000ff00, 0x00ff0000, 0);
#else
                                 0xff000000, 0x00ff0000, 0x0000ff00, 0);
#endif

    if (sdlImage) {
      SDL_Rect dst;
      dst.x = (screen->w - sdlImage->w) / 2;
      dst.y = (screen->h - sdlImage->h) / 2;
      dst.w = sdlImage->w;
      dst.h = sdlImage->h;
      SDL_BlitSurface(sdlImage, NULL, screen, &dst);
    }

    // Unlock if needed
//    if (SDL_MUSTLOCK(gScreen)) {
//      SDL_UnlockSurface(gScreen);
//    }

    // Tell SDL to update the whole gScreen
    //SDL_UpdateRect(screen, 0, 0, m_iWidth, m_iHeight);

    SDL_Flip(screen);
  }
}

void ImageDisplaySDL::setImage(image::ColorImage* _image,
                               const bool copy) {
  colorImage = _image;
  resize(colorImage->width(), colorImage->height());
  //updateGL();
  update();
}

} // namespace


#else // NICE_USELIB_SDL

#include "core/imagedisplay/ImageDisplaySDL.h"
namespace NICE {
bool ImageDisplaySDL::sdlDisplayActive = false;
ImageDisplaySDL::ImageDisplaySDL(QWidget */*parent*/, const char */*name*/) {}
ImageDisplaySDL::~ImageDisplaySDL() {}
void ImageDisplaySDL::resizeEvent(QResizeEvent *) {}
void ImageDisplaySDL::paintEvent(QPaintEvent *) {}
void ImageDisplaySDL::setImage(ColorImage* /*_image*/, const bool /*copy*/) {}
} // namespace

#endif // NICE_USELIB_SDL
