# Tutorial 06 - Linear Algebra

## Singular value decomposition
_Note: Currently, calculating the SVD of a matrix requires LinAL_

Use the _SVD_ class for fast singular value decomposition.
The calculation is performed at initialization and the resulting
matrices are available from getter functions.

See this short example:

```c++
// Create a matrix
NICE::MatrixT<double> my_matrix(3,3,0);
my_matrix.addIdentity(1);
my_matrix(0,2) = 5;
my_matrix(1,0) = 3;

// Calculate the SVD
NICE::SVD svd(my_matrix);

// Store the results
NICE::MatrixT<double> result_vt = svd.getVt();
NICE::MatrixT<double> result_u = svd.getU();

// This returns the singular values in a diagonal matrix
// This diagonal matrix is allocated only if you call this function.
NICE::MatrixT<double> result_s_matrix = svd.getS();

// This returns the singular values as a vector. Use this function for
// increased efficiency
NICE::VectorT<double> result_s_vector = svd.getSingularValues();
```
