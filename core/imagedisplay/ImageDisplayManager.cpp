/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libimagedisplay - An imagedisplay/template for new NICE libraries
 * See file License for license information.
 */
#include "core/imagedisplay/ImageDisplayManager.h"

namespace NICE {

std::auto_ptr<ImageDisplayManager> ImageDisplayManager::s_instance;

ImageDisplayManager::ImageDisplayManager() {
}

ImageDisplayManager::~ImageDisplayManager() {
}

void ImageDisplayManager::registerWidget(ImageDisplay* widget) {
  widgets.push_back(widget);
}

void ImageDisplayManager::unregisterWidget(ImageDisplay* widget) {
  widgets.remove(widget);
}
  
void ImageDisplayManager::hideAll() {
  for (std::list<ImageDisplay*>::iterator iter = widgets.begin();
       iter != widgets.end(); ++iter) {
    (*iter)->hide();
  }
}

void ImageDisplayManager::showAll() {
  for (std::list<ImageDisplay*>::iterator iter = widgets.begin();
       iter != widgets.end(); ++iter) {
    (*iter)->show();
  }
}

void ImageDisplayManager::deleteAll() {
  for (std::list<ImageDisplay*>::iterator iter = widgets.begin();
       iter != widgets.end(); ++iter) {
    delete *iter;
    //widgets.remove(*iter);
  }
  widgets.clear();
}


} // namespace
