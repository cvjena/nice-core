/*
 * Tutorial 01 - Basic Image I/O Operations
 * Sample Implementation
 *
 * @file 01_imageio.cpp
 * @brief Sample implementation for tutorial 01
 * @date 09.03.2014
 * @author Clemens-A. Brust
 */

#include <iostream>
#include <string>
#include <core/image/ImageT.h>

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
	NICE::ImageFile::Header source_header = source_file.getHeader();

	std::cout << "Source image dimensions: " << source_header.width << " x " << source_header.height;
	std::cout << " (" << source_header.channel << " channels, " << source_header.bitdepth << " bpp)\n";

	// Read image into memory
	NICE::ColorImage source_image;
	source_file.reader(&source_image);

	// Write image to disk
	NICE::ImageFile dest_image(output_path);
	dest_image.writer(&source_image);
	return 0;
}
