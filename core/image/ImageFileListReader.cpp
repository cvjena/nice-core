#include "core/image/ImageFileListReader.h"
#include "core/image/Convert.h"
#include "core/basics/Log.h"
#include <fstream>

namespace NICE {

ImageFileListReader::ImageFileListReader(const char* fileName, bool _preload) {
  init(std::string(fileName), _preload);
}

ImageFileListReader::ImageFileListReader(const std::string& fileName, bool _preload) {
  init(fileName, _preload);
}

void ImageFileListReader::init(const std::string& fileName, bool _preload) {
  preload = _preload;

  inputFileName = fileName;
  if (inputFileName.isDirectory()) {
    inputFileName.removeSlash();
    FileName lastPart = inputFileName.extractFileName();
    inputFileName.addSlash();
    inputFileName = FileName(inputFileName.str() + lastPart.str() + ".txt");
  }

  std::ifstream file( inputFileName.str().c_str() );
  if (!file.good()) {
    fthrow(ImageException,
           std::string("ImageFileListReader: Error opening filelist: ")
               + inputFileName.str());
  }

  FileName basePath = FileName(inputFileName).extractPath();

  while (!file.eof()) {
    char fileNameFrame[256];
    fileNameFrame[0] = 0;
    file >> fileNameFrame;
    if (strlen(fileNameFrame) > 0) {
      fileList.push_back(new std::string(basePath.str() + fileNameFrame));
    }
  }

  file.close();
  currentFrame = 0;

  // read width and height (of the first image)
  std::auto_ptr<ColorImage> image(doReadColorImage());
  currentFrame = 0;
  if (image.get() == NULL) {
    width = 0;
    height = 0;
  } else {
    width = image->width();
    height = image->height();
  }
  image.reset(NULL);

  if (preload) {
    for (unsigned int i = 0; i < numberOfFrames(); i++) {
      ColorImage* image = doReadColorImage();
      images.push_back(image);
    }
    reset();
  }
}

ImageFileListReader::~ImageFileListReader() {
  for (unsigned int i = 0; i < fileList.size(); i++) {
    delete fileList.at(i);
  }
  if (preload) {
    for (unsigned int i = 0; i < images.size(); i++) {
      delete images.at(i);
    }
  }
}

bool ImageFileListReader::endOfStream() {
  return currentFrame >= numberOfFrames();
}

void ImageFileListReader::readColorImage(ColorImage& buffer) {
  if (preload) {
    if (endOfStream()) {
      fthrow(ImageException, "End of stream reached.");
    }
    buffer = *images.at(currentFrame);
    currentFrame++;
  } else {
    doReadColorImage(&buffer);
  }
}

void ImageFileListReader::readGrayImage(Image& buffer) {
  if (preload) {
    if (endOfStream()) {
      fthrow(ImageException, "End of stream reached.");
    }
    rgbToGray(*images.at(currentFrame), &buffer);
    currentFrame++;
  } else {
    ColorImage image;
    doReadColorImage(&image);
    rgbToGray(image, &buffer);
  }
}

void ImageFileListReader::readColorImage(ColorImage& buffer, unsigned int index) {
  if (preload) {
    buffer = *images.at(index);
  } else {
    buffer.read(ImageFile(*fileList.at(index)));
  }
}

void ImageFileListReader::readGrayImage(Image& buffer, unsigned int index) {
  if (preload) {
    rgbToGray(*images.at(index), &buffer);
  } else {
    ColorImage image;
    image.read(ImageFile(*fileList.at(index)));
    rgbToGray(image, &buffer);
  }
}

ColorImage* ImageFileListReader::doReadColorImage(ColorImage* buffer) {
  if (endOfStream()) {
    //fthrow(ImageException, "End of stream reached.");
    return NULL;
  }
  ColorImage* image = buffer;
  if (buffer == NULL) {
    image = new ColorImage(*fileList.at(currentFrame));
  } else {
    buffer->read(ImageFile(*fileList.at(currentFrame)));
  }
  currentFrame++;
  return image;
}

int ImageFileListReader::imageHeight() {
  return height;
}

int ImageFileListReader::imageWidth(){
  return width;
}

unsigned int ImageFileListReader::numberOfFrames() const {
  return fileList.size();
}

void ImageFileListReader::reset() {
  currentFrame = 0;
}

void ImageFileListReader::ignoreFrames(int frames) {
  currentFrame += frames;
}

} // namespace
