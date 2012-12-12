/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libimagedisplay - A library for image and video display
 * See file License for license information.
 */
#ifndef _IMAGEDISPLAY_IMAGEDISPLAYMANAGER_H
#define _IMAGEDISPLAY_IMAGEDISPLAYMANAGER_H

#include <list>
#include <core/imagedisplay/ImageDisplay.h>

namespace NICE {

/**
 * Keep track of all stand alone ImageDisplay widgets. Singleton pattern.
 * Note that only "stand alone" ImageDisplay widgets are managed.
 * This means that widgets contained in other widgets are completely ignored
 * by ImageDisplayManager.
 *
 * @author Ferid Bajramovic
 * 
 * @note
 * This class is experimental and might change in the future.
 */
class ImageDisplayManager {
public:
  //! Destructor
  virtual ~ImageDisplayManager();
  
  static inline ImageDisplayManager& instance() {
    if (s_instance.get() == NULL) {
      s_instance.reset(new ImageDisplayManager());
    }
    return *s_instance;
  }
  
  void registerWidget(ImageDisplay* widget);
  void unregisterWidget(ImageDisplay* widget);
  
  void hideAll();
  void showAll();
  void deleteAll();

private:
  /**
   * Constructor.
   */
  ImageDisplayManager();
  
  static std::auto_ptr<ImageDisplayManager> s_instance;
  
  std::list<ImageDisplay*> widgets;
};

} // namespace
#endif /* _IMAGEDISPLAY_IMAGEDISPLAYMANAGER_H */
