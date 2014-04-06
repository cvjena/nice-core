/*
 * Tutorial 03 - Color Image Operations
 * Sample Implementation
 *
 * @file 03_color.cpp
 * @brief Sample implementation for tutorial 03
 * @date 09.03.2014
 * @author Clemens-A. Brust
 */
 
 #include <iostream>
 #include <core/image/ImageT.h>
 #include <core/image/ColorImageT.h>
 #include <core/image/ImageFile.h>
 #include <core/image/Convert.h>

/*
 * Entry point
 */
int main(int argc, char** argv) {
	// Check if enough parameters were supplied
	if (argc < 3) {
		std::cout << "USAGE: " << argv[0] << " <input image> <output image>\n";
		return -1;
	}

	// These are our file names
	std::string input_path(argv[1]);
	std::string output_path(argv[2]);

	// Read file header and display header information
	NICE::ImageFile source_file(input_path);

	// Read image into memory
	NICE::Image image;
	source_file.reader(&image);

	NICE::ColorImage pseudo_image(image.width(), image.height());
	imageToPseudoColor(image, pseudo_image);

	// Write image to disk
	NICE::ImageFile dest_image(output_path);
	dest_image.writer(&pseudo_image);
	return 0;
}
