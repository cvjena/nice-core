# Tutorial 01 - Basic Image I/O Operations

In this first tutorial you will learn how to read and write image files and how images are represented in NICE.

## Prerequisites
If you need support for a specific image file format other than PGM/PPM, you have to compile nice-core yourself and add the necessary libraries and CMake flags.

The sample code for this tutorial does not have any dependencies other than nice-core. You can find it in the tutorial/progs subfolder.

## Images in memory
NICE provides a common generic interface for grayscale and multi-channel
images.
The corresponding classes are _ImageT_ and _ColorImageT_, both subclasses of
_GrayColorImageCommonImplementationT_ which contains the most basic image
access methods.
Those are used by many of the other modules.
You can find typical use cases in the next tutorials.

Note that NICE does not have generic implementations of every function.
We recommend using 8-bit images for most applications and also
provide a shorthand typedef called _Image_.

## Image files
In NICE, instances of _ImageT_ or _ColorImageT_ do not have to exist on disk. Files are different, completely independent objects. The _ImageFile_ class serves as a pointer to a file in the file system.

An instance of _ImageFile_ can be read from or written to, but it does not modify the file in any way unless you call those methods.

Constructing an _ImageFile_ is simple:

```c++
ImageFile file("path/to/file.pgm");
```

This does not touch the file at all and it doesn't need to exist. If it does exist, you can read the image file into memory like this:

```c++
Image image_in_memory;
file.reader(&image_in_memory);
```

After making our changes to the image (in memory), we can write them to the file:

```c++
file.writer(&image_in_memory);
```

## Header information
Sometimes it can be useful to access metadata without reading the whole image into memory. _ImageFile_ provides the __getHeader__ method for this. It reads the file and returns an instance of _Header_ with the fields __width__, __height__, __bitdepth__, __channel__.

## Formats
Note that _ImageFile_ attemtps to determine the file format by looking at the file name. You can override this behaviour by providing the __type__ parameter using the _Format_ enumeration.

Supported file formats include PGM/PPM out of the box and those provided by libpng, libjpeg and libimagemagick++.

The sample images do not need any additional libraries.

# Sample code
There is a complete sample program for every tutorial in this series.
These samples are built along with NICE and can be found in the
__core__ output directory.

The sample program for this tutorial reads a file from disk to memory,
displays metadata from the file header and writes the image to another
file.

You can find PXM sample images to use with the sample code
in the __tutorial__ folder.

## Includes
We start of the sample program by including the necessary header files.
The first few tutorials explain the usage of classes in the __image__
subdirectory.

Header files are usually named after the classes they declare.
We need the _ImageT_ and _ImageFile_ classes, so our sample code
starts like this:

```c++
#include <iostream>
#include <string>
#include <core/image/ImageT.h>
#include <core/image/ImageFile.h>
```

## File names
We then get the file names from the command line.
NICE will automatically determine the file type from its ending.
This works for reads and writes, so you can use this sample program
as a simple converter between image formats.

This next part simply checks if the user specified both source and
destination file.
If there are enough arguments, they are stored in a _string_.
 
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

## Image metadata
_ImageFile_ can read the header information without reading the whole image
into memory.
We use the __getHeader__ method to obtain a _Header_ instance.
The fields are written to the standard output.

```c++
// Read file header and display header information
NICE::ImageFile source_file(input_path);
NICE::ImageFile::Header source_header = source_file.getHeader();

std::cout << "Source image dimensions: " << source_header.width << " x " << source_header.height;
std::cout << " (" << source_header.channel << " channels, " << source_header.bitdepth << " bpp)\n";
```

## Reading and writing the image
To read the image, we create an empty instance of _ColorImage_ hand it over
to the file's __reader__ method.

Writing the image to disk is just as easy: contruct an _ImageFile_ with the
destination path and call the __writer__ method.

```c++
// Read image into memory
NICE::ColorImage source_image;
source_file.reader(&source_image);

// Write image to disk
NICE::ImageFile dest_image(output_path);
dest_image.writer(&source_image);
return 0;
```

Remember that _ImageFile_ objects are just containers for a file's location
and only open the file when you call methods that require reading or writing.

## Running the sample

_Command line:_

```bash
./01_imageio ../../nice-core/core/tutorial/samples/peppers_color.ppm /tmp/output.ppm
```

_Output:_

```
Source image dimensions: 512 x 512 (3 channels, 8 bpp)
```
