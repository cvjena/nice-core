#include "MultiChannelImageTTest.h"
#include <string>


#include <core/image/ippwrapper.h>

#include <core/image/MultiChannelImageT.h>

#include "core/basics/cppunitex.h"

using namespace std;
using namespace NICE;

CPPUNIT_TEST_SUITE_REGISTRATION ( MultiChannelImageTTest );

void MultiChannelImageTTest::setUp() {
}

void MultiChannelImageTTest::tearDown() {
}

void MultiChannelImageTTest::test() {
  int width = 5;
  int height = 10;
  MultiChannelImageT<double> img(width, height, 1);
  MultiChannelImageT<int> iImg(width, height, 2);
  for (int y = 0; y < height; y++)
  {
    for (int x = 0; x < width; x++)
    {
      iImg(x, y, 0) = x + y;
      iImg(x, y, 1) = x * y;
      img(x, y, 0) = (double)x / ((double)y + 1.0);
    }
  }

  for (int y = 0; y < height; y++)
  {
    for (int x = 0; x < width; x++)
    {
      CPPUNIT_ASSERT_EQUAL(img(x, y, 0), (double)x / ((double)y + 1.0));
      CPPUNIT_ASSERT_EQUAL(iImg(x, y, 0), x + y);
      CPPUNIT_ASSERT_EQUAL(iImg(x, y, 1), x*y);
    }
  }

  img.addChannel(iImg);

  CPPUNIT_ASSERT_EQUAL(img.channels(), 3);
  CPPUNIT_ASSERT_EQUAL(img.width(), width);
  CPPUNIT_ASSERT_EQUAL(img.height(), height);

  for (int y = 0; y < height; y++)
  {
    for (int x = 0; x < width; x++)
    {
      CPPUNIT_ASSERT_EQUAL(img(x, y, 0), (double)x / ((double)y + 1.0));
      CPPUNIT_ASSERT_EQUAL(img(x, y, 1), (double)(x + y));
      CPPUNIT_ASSERT_EQUAL(img(x, y, 2), (double)(x*y));
    }
  }

  MultiChannelImageT<double> imgCopy = img;

  CPPUNIT_ASSERT_EQUAL(img.channels(), imgCopy.channels());
  CPPUNIT_ASSERT_EQUAL(img.width(), imgCopy.width());
  CPPUNIT_ASSERT_EQUAL(img.height(), imgCopy.height());

  for (int c = 0; c < imgCopy.channels(); c++)
  {
    for (int y = 0; y < height; y++)
    {
      for (int x = 0; x < width; x++)
      {
        CPPUNIT_ASSERT_EQUAL(img(x, y, c), imgCopy(x, y, c));
      }
    }
  }

  MultiChannelImageT<double> imgInt(width,height,2);
  
  for (int y = 0; y < height; y++)
  {
    for (int x = 0; x < width; x++)
    {
      imgInt(x,y,0) = x;
      imgInt(x,y,1) = x;
    }
  }
  
  imgInt.calcIntegral(1);
  
  CPPUNIT_ASSERT_EQUAL(imgInt(0,0,0), imgInt.getIntegralValue(0,0,0,0,1));
  CPPUNIT_ASSERT_EQUAL(imgInt(2,2,0), imgInt.getIntegralValue(2,2,2,2,1));
  CPPUNIT_ASSERT_EQUAL(1.0, imgInt.getIntegralValue(0,0,2,2,1));
}
