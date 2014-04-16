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

### Operators
[...]
### Methods
[...]

# Sample code
[...]
