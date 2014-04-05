/*
 * Tutorial 04 - Filters
 * Sample Implementation
 *
 * @file 04_filter.cpp
 * @brief Sample implementation for tutorial 04
 * @date 09.03.2014
 * @author Clemens-A. Brust
 */

#include <iostream>
#include <string>
#include <core/image/ImageT.h>
#include <core/vector/MatrixT.h>
#include <core/image/FilterT.h>

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

		// Allocate memory for result image
		NICE::Image result(image.width(), image.height());

		// Put together a simple convolution kernel for our motion blur effect
		NICE::Matrix kernel(10,10);
		kernel.set(0);
		kernel.addIdentity(0.1);

		// Filter the image
		NICE::Filter::filter(image, kernel, result);

		// Write image to disk
		NICE::ImageFile dest_image(output_path);
		dest_image.writer(&result);
		return 0;
}
