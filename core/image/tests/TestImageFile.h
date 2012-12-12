/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libimage - An image/template for new NICE libraries
 * See file License for license information.
 */
#ifndef _TESTIMAGEFILE_IMAGE_H
#define _TESTIMAGEFILE_IMAGE_H

#include <cppunit/extensions/HelperMacros.h>
#include <core/image/ImageFile.h>

/**
 * CppUnit-Testcase. 
 * Test template...
 */
class TestImageFile : public CppUnit::TestFixture 
{
	CPPUNIT_TEST_SUITE( TestImageFile );
	CPPUNIT_TEST( testFloatPXM   );
	CPPUNIT_TEST( testFloatImage );
	CPPUNIT_TEST( testColorImage );
	CPPUNIT_TEST( testGrayImage  );
	CPPUNIT_TEST( testJPG_IO     );
	CPPUNIT_TEST_SUITE_END();

   private:
 
   public:
	void setUp();
	void tearDown();
	
	/**
	* Constructor / Destructor testing 
	*/  
	void testConstructor();
	
	/**
	* Operator testing 
	*/  
	void testOperators();

	/**
	* Test read and write 
	*/  
	void testFloatPXM();
	void testFloatImage();
	void testColorImage();
	void testGrayImage();

	/**
	* Test JPEG Input and Output
	*/
  	void testJPG_IO();
};

#endif // _TESTIMAGEFILE_IMAGE_H
