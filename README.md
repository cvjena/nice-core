## NICE Library
by Computer Vision Group Jena, 2004-2019

#### Dependencies

* Qt4 (mandatory)
* libPNG or ImageMagick (mandatory)
* OpenGL (mandatory)
* OpenMP (optional)
* MATIO (optional)
* Boost (optional)

#### Installation

For installation of the library the cross-platform compiling tool CMake is used.
After cloning the repository from GitHub, by e.g.

	git clone git@github.com:cvjena/nice-core.git

navigate to the repository directory using the terminal and run the following commands

	mkdir build
	cd build
	cmake ..
	make

Alternatively, you can use `ccmake ..` instead to modfiy the installation configuration.

Please note, there are additional library modules for *optimization*, *segmentation*, *semantic segmentation* and *visual learning* available.
If you are interested in using them, contact the authors.
