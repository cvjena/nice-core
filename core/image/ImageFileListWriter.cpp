#include "core/image/ImageFileListWriter.h"
#include "core/image/Convert.h"
#include "core/basics/FileName.h"
#include <sstream>

namespace NICE {

ImageFileListWriter::ImageFileListWriter(const std::string& path,
                                         const std::string& extension,
                                         const bool _keepImagesInMemory)
    : nameExtension(extension), currentFrame(0),
      keepImagesInMemory(_keepImagesInMemory) {
  init(path);
}

ImageFileListWriter::~ImageFileListWriter() {
  close();
}

void ImageFileListWriter::writeColorImage(const ColorImage& image) {
  m_lastImageFileName = makeCurrentFileName();
  if (keepImagesInMemory) {
    ColorImage* imageCopy = new ColorImage(image);
    images.push_back(imageCopy);
    fileNames.push_back(new std::string(m_lastImageFileName));
  } else {
    //image.writePPM(fileName);
    image.write(ImageFile(m_lastImageFileName));
    addToFileList(m_lastImageFileName);
  }
  currentFrame++;
}

void ImageFileListWriter::writeGrayImage(const Image& image) {
  m_lastImageFileName = makeCurrentFileName();
  if (keepImagesInMemory) {
    ColorImage* imageCopy = grayToRGB(image);
    images.push_back(imageCopy);
    fileNames.push_back(new std::string(m_lastImageFileName));
  } else {
    //std::auto_ptr<ColorImage> imageCopy(grayToRGB(image));
    //imageCopy->writePPM(fileName);
    image.write(ImageFile(m_lastImageFileName));
    addToFileList(m_lastImageFileName);
  }
  currentFrame++;
}

void ImageFileListWriter::close() {
	flushMemoryBuffer();
  /*if (keepImagesInMemory) {
    for (unsigned int i = 0; i < images.size(); i++) {
      std::string* fileName = fileNames.at(i);
      ColorImage* image = images.at(i);

      //image->writePPM(*fileName);
      image->write(ImageFile(*fileName));
      addToFileList(*fileName);

      delete image;
      delete fileName;
    }
  }*/
  fileList.close();
}

void ImageFileListWriter::init(const std::string& path) {
  FileName thePath(path);
  thePath.removeSlash();
  FileName subdir = thePath.extractFileName();
  thePath.createDirectory();
  thePath.addSlash();
  namePrefix = thePath.str() + subdir.str();
  fileListFileName = namePrefix + ".txt";

  fileList.open(fileListFileName.c_str());
  if (!fileList.good()) {
    throw ImageException(
      std::string("ImageFileListWriter: Error creating filelist ")
      + fileListFileName);
  }
}

std::string ImageFileListWriter::makeCurrentFileName() {
  std::ostringstream counterStream;
  counterStream << currentFrame;
  std::string counter = counterStream.str();
  while (counter.length() < 5) {
    counter = "0" + counter;
  }
  return namePrefix + "_" + counter + nameExtension;//".ppm";
}

void ImageFileListWriter::addToFileList(const std::string& fileName) {
  FileName name(fileName);
  fileList << name.extractFileName() << std::endl;
}

void ImageFileListWriter::insertMissingFrames(int frames) {
  currentFrame += frames;
}

void ImageFileListWriter::flushMemoryBuffer() {
  if (keepImagesInMemory) {
    for (unsigned int i = 0; i < images.size(); i++) {
      std::string* fileName = fileNames.at(i);
      ColorImage* image = images.at(i);

      //image->writePPM(*fileName);
      image->write(ImageFile(*fileName));
      addToFileList(*fileName);

      delete image;
      delete fileName;
    }
    images.clear();
    fileNames.clear();
  }
}

} // namespace
