# Tutorial 05 - Linear Algebra
## Vectors
NICE provides the generic _VectorT<>_ class for vector data storage and
calculations.
It supports the same, large number of operations for all data types.

There are deep and shallow copy functions for LinAl interoperability.

### Construction
While _VectorT<>_ provides a default constructor, it is only if you want
to avoid pointers as member variables.

_VectorT<>_ needs to know the number of elements because resizing a vector is
extremely inefficient. You can also initialize the elements if you want to:

```c++
// This line creates an empty vector
VectorT<double> empty_vector();

// This line creates a three-dimensional vector
// The elements are not initialized
VectorT<double> threed_vector(3);

// This line creates a two-dimensional vector
// We initialize the elements to the value 25.3
VectorT<double> twod_vector(3, 25.3);
```


### Operators
For easy and expressive calculations, _VectorT<>_ defines the following
classes of operators:

* Unary operators:
    - Unchecked read or reference access to element ([])
    - Checked read or reference access to element (())

* Binary operators:
    - Vector addition and subtraction (+,-)
    - Scalar multiplication (\*)

* Combined assignment operators:
    - Vector addition and subtraction (+=,-=)
    - Vector multiplication and division (\*=,/=)
    - Scalar addition and subtraction (+=,-=)
    - Scalar multiplication and division (\*=,/=)

### Methods
In addition to basic algebra, _VectorT<>_ supports more complex operations.
These include:

* Calculating the scalar product of two _VectorT<>_: __scalarProduct__
* Determining various statistics: __Sum__, __Mean__, __Median__, __StdDev__,
  __Min__, __Max__
* Additional information on these statistics: __MaxIndex__, __MinIndex__
* Mean in non-euclidean vector spaces: __CircularMean__
* Several norms: __normInf__, __normL1__, __normL2__
* ...and normalization routines: __normalizeInf__, __normalizeL1__, __normalizeL2__
* Basic sorting functions: __sortAscend__, __sortDescend__

## Matrices
Just like vectors, matrices have a generic representation in NICE.
The class is called _MatrixT<>_ and is not related to _VectorT<>_ in that it
is not a construct like _VectorT<VectorT<>>_.

### Construction
_MatrixT<>_ has a large number of constructors for different use cases.
The default constructor creates a _MatrixT<>_ of dimensions 0x0 and should
only be used for RAII purposes because resizing a _MatrixT<>_ is a very
inefficient operation.

```c++
// Construction and expansion
NICE::MatrixT<double> empty_matrix();
empty_matrix.resize(5,4);
```

Instead, you can specifiy the dimensions and an optional default element.
When no default element is given to the constructor, the matrix will not
be initialized contains unpredictable data.

```c++
// 4x5 matrix - no initialization
NICE::MatrixT<double> undefined_matrix(4,5);

// 5x6 matrix - default element: 1
NICE::MatrixT<double> simple_matrix(5,6,1);
```

### Data access
_MatrixT<>_ provides different methods for read and write access to fit as
many applications as possible.
See the following snippet for important use cases:

```c++
// This is our matrix
NICE::MatrixT<double> matrix(3,3);

// At this point, the elements are unknown, so let's set them all to zero.
matrix.set(0);

// Now, create a vector
NICE::VectorT<double> vector(3);
vector[0]=1, vector[1]=2, vector[2]=3;

// We can use this vector with the setRow method
matrix.setRow(0, vector);

// Set the center element to 5
matrix(1,1)=5;

// How can we set a column using a VectorT?
matrix.getColumnRef(2)=vector;
```

### Operators
_MatrixT<>_ exports basic calculations and methods as operators:

* Unary operators:
    - Unchecked read or reference access to element (())

* Binary operators:
    - Matrix addition and subtraction (+,-)
    - Matrix-scalar multiplication (\*)
    - Matrix-vector multiplication (\*)
    - Matrix multiplication (\*)

* Combined assignment operators:
    - Matrix addition and subtraction (+=,-=)
    - Matrix multiplication and division - element-wise (\*=,/=)
    - Scalar addition and subtraction (+=,-=)
    - Scalar multiplication and division (\*=,/=)

### Methods
More advanced calculations are available as member functions:

* Set the matrix to a multiple of the identity matrix or
  add to the existing matrix: __setIdentity__, __addIdentity__
* Add a vector's elements as a diagonal matrix: __addDiagonal__
* Calculate the tensor product of two vectors and store it
  or add it to the matrix: __tensorProduct__, __addTensorProduct__
* Store the result of a matrix multiplication: __multiply__
* Check if a floating point matrix contains a NaN element: __containsNaN__
