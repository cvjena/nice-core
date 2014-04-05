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
