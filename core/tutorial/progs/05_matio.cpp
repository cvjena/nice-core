/*
 * Tutorials 05/06 - Matlab I/O and Linear Algebra
 * Sample Implementation
 *
 * @file 05_matio.cpp
 * @brief Sample implementation for tutorials 05/06
 * @date 09.03.2014
 * @author Clemens-A. Brust
 */

#include <iostream>
#include <string>
#include <exception>
#include <core/image/ImageT.h>
#include <core/vector/MatrixT.h>
#include <core/vector/VectorT.h>
#include <core/vector/Eigen.h>
#include <core/vector/SVD.h>
#include <core/image/FilterT.h>

#ifdef NICE_USELIB_MATIO
#include <core/matlabAccess/MatFileIO.h>

template<typename T> void printMatrix(NICE::MatrixT<T> matrix);

/*
 * Entry point
 */
int main(int argc, char** argv) {
	// Check if enough parameters were supplied
	if (argc < 3) {
		std::cout << "USAGE: " << argv[0] << " <matlab file> <matrix name>\n";
		return -1;
	}

	// These are our file names
	std::string input_path(argv[1]);
	std::string matrix_name(argv[2]);

	NICE::MatFileIO matlab_file(input_path, MAT_ACC_RDONLY);
	
	// Show the number of variables in the file
	int vars_in_file = matlab_file.getNumberOfVariables();
	std::cout << vars_in_file << " Variables in " << input_path << "\n";

	// Load the matrix
	std::cout << "Loading matrix \"" << matrix_name << "\"...\n";

	// Check if the variable is a matrix
	matvar_t* matrix_variable = matlab_file.getVariableViaName(matrix_name);
	if(matrix_variable->rank != 2) {
		std::cout << "Variable is not a matrix. Rank: " << matrix_variable->rank << ".\n";
		return -1;
	}

	// Read the dimensions
	int cols = matrix_variable->dims[1];
	int rows = matrix_variable->dims[0];
	std::cout << "Dimensions: " << cols << " x " << rows << "\n";

	// Read the matrix into a vector of vectors
	std::vector< std::vector<double> > matrix_vecvec(rows, std::vector<double>(cols));
	matlab_file.getFeatureMatrixViaName(matrix_vecvec, matrix_name);

	// Now, we want a NICE matrix
	NICE::MatrixT<double> matrix(rows, cols);
	for(int i = 0; i < rows; i++) {
		for(int j = 0; j < cols; j++) {
			matrix(i,j) = matrix_vecvec[i][j];
		}
	}

	// Print the NICE matrix
	printMatrix(matrix);

	// Check if eigenvalues exist
	if(rows != cols) {
		std::cout << "Matrix is not square, cannot calculate eigenvalues!\n";
		return -1;
	}

	// Calculate eigenvalues
	try {
		NICE::VectorT<double>* matrix_eigenvalues = NICE::eigenvalues(matrix);
	} catch (std::exception& e) {
		std::cout << "Exception occured during eigenvalue calculation, "
			<< "is IPP installed?\n";
	}

#ifdef NICE_USELIB_LINAL
	// Calculate singular value decomposition
	NICE::SVD<double> matrix_svd(matrix);

	std::cout << "Vt:\n";
	printMatrix(matrix_svd.getVt());

	std::cout << "U:\n";
	printMatrix(matrix_svd.getU());

	std::cout << "S:\n";
	printMatrix(matrix_svd.getS());
#else
	std::cout << "LinAL is not installed, SVD calculation is not possible!\n";
#endif
	return 0;

}

template<typename T> void printMatrix(NICE::MatrixT<T> matrix) {
	for(int i = 0; i < matrix.rows(); i++) {
		for(int j = 0; j < matrix.cols(); j++) {
			std::cout << matrix(i,j) << "\t";
		}
		std::cout << "\n";
	}
}
#else

/*
 * Replacement entry point
 */
int main(int argc, char** argv) {
	std::cout << "This sample needs MATIO to work!\n";
}
#endif
