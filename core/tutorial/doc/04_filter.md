# Tutorial 04 - Filters
Linear filters play an important role in image processing.
They are used for dealing with noise and in many computer vision applications.
NICE provides generic implementations of several common filter types and
supports custom kernels.

## Data types
The class _FilterT<>_ contains static methods for every filter type supported
by NICE.
You can specify different data types for your source and destination images and
also
for the calculations used during convolution.

We recommend sticking to 8-bit-per-channel images (using the Image typedef as
recommended throughout this tutorial series) and using _double_ values for
the filter calculations.

In this case you can use the _Filter_ typedef.

## Source and destination image
Most filter methods expect a destination image to write their results to.
This image should have the same dimensions as the source image, otherwise
it will be resized or an exception will be thrown.

You should always construct a destination image like this:

```c++
// [...]
NICE::Image image;
// [...]
NICE::Image result(image.width(), image.height());
```

## Filter types
This section will give you an overview of the different kinds of filter NICE
supports.

### Mean filter
A very simple filter for noise reduction is the mean filter.
NICE implements this filter two times: for small and for large kernels.

For most applications, the small implementation will suffice:

```c++
const unsigned int size = 3;
NICE::Filter::filterMean(image, size, result);
```

The __size__ parameter describes the radius of the neighborhood
(not including the center)
used as a filter kernel. For size = 3, you get a 7x7 mean filter.

### Sobel filter
For some detection algorithms, you need gradient images.
To compute the first derivative of your image in X and Y directions,
use the following methods:

```c++
NICE::Filter::sobelX(image,gradientImageX);
NICE::Filter::sobelY(image,gradientImageY);
```


### Using your own filter kernel
Some applications require a specific filter kernel.
You can supply an instance of _MatrixT<>_ with your values.

The template argument should match the type used for calculations in
_FilterT_.
If you use the _Filter_ typedef, you can use the _Matrix_ typedef as well.

You can then apply the filter like this:

```c++
NICE::Filter::filter(image, kernel, result);
```

If your filter kernel is separable, you can get better performance by applying
two one-dimensional convolutions.
Instead of _MatrixT<>_, you supply two _VectorT<>_ instances.
As with _Matrix_, there's a typedef _Vector_ for _VectorT<double>_.

You need to call two methods in this case:

```c++
NICE::Filter::filterX(image, kernel, result);
NICE::Filter::filterY(image, kernel, result);
```

## Running the sample

_Command line:_

```bash
./04_filter ../../nice-core/core/tutorial/samples/peppers_color.ppm /tmp/output.pgm
```
