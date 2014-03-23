# Tutorial 02 - Grayscale Image Operations

## Pattern for gray value transforms

You can use the following pattern for your gray value transforms.

``` c++
template <class P> void MyTransform(ImageT<P>& image)
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
