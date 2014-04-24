# Tutorial 06 - Linear Algebra

## Singular value decomposition
_Note: Currently, calculating the SVD of a matrix requires LinAL_

Use the _SVD_ class for fast singular value decomposition.
The calculation is performed at initialization and the resulting
matrices are available from getter functions.

Calculating the SVD is a very straightforward task.
See this short example on how to use the SVD class:

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

## Eigenvalues
_Note: Currently, calculating the eigenvalues of a matrix requires IPP._

Calculating the eigenvalues of a matrix is as simple as single function call.
The __eigenvalues__ function takes a _MatrixT<>_ and returns a _VectorT<>_ 
that contains the eigenvalues. It allocates a _VectorT<>_ of matching dimensions
on the heap.
This behavior can be overridden be specifying a pointer as the second parameter.

```c++
// Create a matrix
NICE::MatrixT<double> matrix(3,3,0);
matrix.addIdentity(4);
matrix(0,1) = -2;

// Calculate the eigenvalues
NICE::VectorT<double> eigenvals = NICE::eigenvalues(matrix);

// ..or use your own vector
NICE::VectorT<double> my_own_vector(3);
NICE::eigenvalues(matrix, my_own_vector);
```
