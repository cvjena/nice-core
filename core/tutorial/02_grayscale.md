# Tutorial 02 - Grayscale Image Operations

After reading your image from a file into memory, you may want to optimize its histogram using gray value transforms. This tutorial will tech you the basics.

## Pattern for gray value transforms
You can use the following pattern for your gray value transforms.

``` c++
template <class P> void MyTransform(NICE::ImageT<P>& image)
{
	for(int x = 0; x < image.width(); x++) {
		for(int y=0; y < image.height(); y++) {
			P pixel = image.getPixelQuick(x, y);
			// Insert transform here	
			image.setPixelQuick(x, y, pixel);
		}
	}
}
```

Note that the get/setPixelQuick Methods don't perform boundary checks!

### Optimization
If you have access to Intel IPP, you can use the overloaded operators provided in ImageOperators.h.

Another easy way to improve performance is adding a "parallel for" OpenMP compilation hint.

## Gamma transforms
Gamma transforms are a little more complicated, because gray values are not always in the [0,1] range.
For example, the _Image_ and _GrayImage16s_ use the full positive range of their data types while the _FloatImage_ class can handle arbitrary ranges.

You can use the __max()__ and __min()__ methods on your image to find its specific range. 

## Histogram
NICE provides a _Histogram_ class for 8-bit grayscale and color images (_Image_ and _ColorImage_).
To calculate an image's histogram, use the constructor:

``` c++
NICE::Histogram histogram(image, 0, 256);
```

### Equalization
The sample code uses the pattern from the beginning and the _Histogram_ class to
optimize the source image's contrast.

The transformation works by computing the cumulative histogram like this:

```c++
NICE::IntVector* cumulative_histogram = histogram.cumulative();
```

It is then scaled down to make it a homogenuos transform from [0,255] to [0,255].
The histogram of the resulting image *should* resemble a uniform distribution.