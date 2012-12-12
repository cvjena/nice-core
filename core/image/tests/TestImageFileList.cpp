#include "TestImageFileList.h"
#include "core/image/ImageFileListReader.h"
#include "core/image/ImageFileListWriter.h"
#include <iostream>
#include <string>

using namespace NICE;

CPPUNIT_TEST_SUITE_REGISTRATION( TestImageFileList );

void TestImageFileList::setUp() {
}

void TestImageFileList::tearDown() {
}

void TestImageFileList::testIO() {
  ColorImage image(1,2);
  
  std::string dataPath("ppmTestSequence");
  ImageFileListWriter writer(dataPath);
  writer.writeColorImage(image);
  writer.writeColorImage(image);
  writer.writeColorImage(image);
  writer.close();
  std::string sequenceFileName(writer.getSequenceFileName());

  {  
    ImageFileListReader sequence(sequenceFileName, false);
    CPPUNIT_ASSERT_EQUAL(3u, sequence.numberOfFrames());
    CPPUNIT_ASSERT_EQUAL(1, sequence.imageWidth());
    CPPUNIT_ASSERT_EQUAL(2, sequence.imageHeight());
    for (unsigned int i = 0; i < sequence.numberOfFrames(); i++) {
      CPPUNIT_ASSERT(!sequence.endOfStream());
      delete sequence.readColorImageNew();
    }
    CPPUNIT_ASSERT(sequence.endOfStream());
    CPPUNIT_ASSERT_THROW(sequence.readColorImageNew(), ImageException);
  }

  {
    ImageFileListReader sequence(sequenceFileName, true);
    CPPUNIT_ASSERT_EQUAL(3u, sequence.numberOfFrames());
    CPPUNIT_ASSERT_EQUAL(1, sequence.imageWidth());
    CPPUNIT_ASSERT_EQUAL(2, sequence.imageHeight());
    for (unsigned int i = 0; i < sequence.numberOfFrames(); i++) {
      CPPUNIT_ASSERT(!sequence.endOfStream());
      delete sequence.readColorImageNew();
    }
    CPPUNIT_ASSERT(sequence.endOfStream());
    CPPUNIT_ASSERT_THROW(sequence.readColorImageNew(), ImageException);
  }
  
  system((std::string("rm -rf ") + dataPath).c_str());
}
