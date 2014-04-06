# Tutorial 03 - Color Image Operations

## Architecture
As mentioned in tutorial 01, color images in memory are represented by instances of
_ColorImageT<>_

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
``