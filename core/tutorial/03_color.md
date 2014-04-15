# Tutorial 03 - Color Image Operations

## Architecture
As mentioned in tutorial 01, color images in memory are represented by instances of
_ColorImageT<>_.

## File input/output
Because _ImageT<>_ and _ColorImageT<>_ are both subclasses of 
_GrayColorImageCommonImplementationT<>_, you can use the __reader__ and __writer__ methods
as explained in tutorial 01.

Note that using a file format that doesn't match the number of channels used by your image
results in undefined behavior.

## Read/write operations
For pixel access, the __setPixelQuick__ methods accepts either a matching instance of
_ColorT<>_ (_Color_ for 8-bit images) or three pixel values:

```c++
// Using Color
color_image.setPixelQuick(4, 3, NICE::Color(0, 255, 0));

// Using separate parameters
color_image.setPixelQuick(4, 3, 0, 255, 0);
```

To read a pixel, use __getPixelQuick__ with the additional _channel_ parameter:

```c++
r = color_image.getPixelQuick(4, 3, 0);
g = color_image.getPixelQuick(4, 3, 1);
b = color_image.getPixelQuick(4, 3, 2);
```

## Conversion between color spaces
NICE can convert between the three-channel color spaces YUV, HSV and RGB.
The following methods are available:

- __rgbToHSV__
- __hsvToRGB__
- __rgbToYUV__
- __yuvToRGB__

These methods allocate a new _ColorImageT<>_ (you can specify your own if you want to) and
return a pointer to it:

```c++
// Use the return value
NICE::ColorImage my_rgb_image = NICE::hsvToRGB(my_hsv_image);

// Specify your own!
NICE::ColorImage my_yuv_image(my_hsv_image.width(), my_hsv_image.height());
NICE::rgbToYUV(my_rgb_image, my_yuv_image);
```

### Pseudocolors
While not strictly a conversion, you can enhance a gray image with pseudocolors using the
built-in function _imageToPseudoColor_. This is a very helpful visualization technique
if your gray values represent something other than intensity (e.g depth or temperature):

```c++
// Allocate color image of appropriate dimensions
NICE::ColorImage color_image(image.width(), image.height());

// Convert to pseudocolor image
NICE::imageToPseudoColor(image, color_image);
```

# Sample code
The sample program for this chapter follows the input-transform-output pattern
of the previous examples. Because conversions between color spaces are
very easy to do with NICE-core, but also very hard to visualize, we will
show you how to work with _ColorImageT<>_ by coloring a grayscale input
using pseudocolors.

## Includes and file names
You can find the pseudocolor and conversion functions in __Convert.h_.
_ColorImageT<>_ has its own header file.

```c++
#include <iostream>
#include <string>
#include <core/image/ImageT.h>
#include <core/image/ColorImageT.h>
#include <core/image/ImageFile.h>
#include <core/image/Convert.h>
```

We also need to check the command line for arguments and store them
if there are enough:

```c++
// Check if enough parameters were supplied
if (argc < 3) {
	std::cout << "USAGE: " << argv[0] << " <input image> <output image>\n";
	return -1;
}

// These are our file names
std::string input_path(argv[1]);
std::string output_path(argv[2]);
```

## Pseudocolors
The next step is reading the file into an _Image_ and calling the
_imageToPseudoColor_ method to perform the colorization. This methods needs
a destination _ColorImage_ of similar dimensions.

```c++
// Read image into memory
NICE::ImageFile source_file(input_path);
NICE::Image image;
source_file.reader(&image);

// Calculate pseudocolors
NICE::ColorImage pseudo_image(image.width(), image.height());
NICE::imageToPseudoColor(image, pseudo_image);
```

After this is done, we write __pseudo_image__ to disk so we can look at it:

```c++
NICE::ImageFile dest_image(output_path);
dest_image.writer(&pseudo_image);
return 0;
```