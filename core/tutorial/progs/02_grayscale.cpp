/*
 * Tutorial 02 - Grayscale Image Operations
 * Sample Implementation
 *
 * @file 02_grayscale.cpp
 * @brief Sample implementation for tutorial 02
 * @date 09.03.2014
 * @author Clemens-A. Brust
 */

#include <iostream>
#include <string>
#include <core/image/ImageT.h>
#include <core/image/ImageFile.h>
#include <core/image/Histogram.h>
#include <core/vector/VectorT.h>

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

	// Read image into memory
	NICE::ImageFile source_file(input_path);
	NICE::Image image;
	source_file.reader(&image);

	// Calculate cumulative histogram
	NICE::Histogram histogram(image, 0, 256);
	NICE::IntVector* cumulative_histogram = histogram.cumulative();

	// The largest value in the cumulative histogram is the total pixel count
	// of the source image. We need to scale this down to 255 to match the pixel
	// format of the image.
	double factor = 255.0/(double)(image.width()*image.height());

	// Transform using our pattern
	for(int x = 0; x < image.width(); x++) {
		for(int y=0; y < image.height(); y++) {
			// This is the old gray value
			Ipp8u pixel = image.getPixelQuick(x, y);

			// We use it as and index into the cumulative histogram to
			// computer the new one. This has to be scaled appropriately
			// using our precomputed factor.
			double new_pixel_f =
					((double)cumulative_histogram->get(pixel))*factor;

			// The pixel format is 8-bit integer, so we have to convert
			// the result
			Ipp8u new_pixel = static_cast<Ipp8u>(new_pixel_f + 0.5);

			// ..and save it
			image.setPixelQuick(x, y, new_pixel);

		}
	}


	// Write image to disk
	NICE::ImageFile dest_image(output_path);
	dest_image.writer(&image);
	return 0;
}
