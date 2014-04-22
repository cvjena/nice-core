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
#include <core/matlabAccess/MatFileIO.h>

/*
 * Entry point
 */
int main(int argc, char** argv) {
	// Check if enough parameters were supplied
	if (argc < 2) {
		std::cout << "USAGE: " << argv[0] << " <matlab file>\n";
		return -1;
	}

	// These are our file names
	std::string input_path(argv[1]);

	NICE::MatFileIO matlab_file(input_path, MAT_ACC_RDONLY);
	
	int vars_in_file = matlab_file.getNumberOfVariables();
	std::cout << vars_in_file << " Variables in " << input_path << "\n";

	return 0;
}
