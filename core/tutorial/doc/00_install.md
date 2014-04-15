# Tutorial 00 - Building and installing NICE-core

## Dependencies

### Linux
The following libraries and programs are required in order to build NICE-core.

 - GCC with C++ support (clang is _not_ supported)
 - CMake 2.8.6 or later
 - Qt 4.x
 - OpenGL
 - GLUT 2.x

### Mac OS X
Newer version of Mac OS X ship with clang as the default compiler.
NICE depends on some GCC-only features, so you need to install _homebrew_
from [brew.sh](http://brew.sh) first.

We recommend installing GCC 4.8 like this:

```bash
$ brew tap homebrew/versions
$ brew install gcc48
```

You also need to install Qt 4.8.5 for Mac.
If you have Mac OS X 10.9, you also have to remove lines 330-332 from
_qtglobal.h_:

```c++
#  if (MAC_OS_X_VERSION_MAX_ALLOWED > MAC_OS_X_VERSION_10_8)
#    warning "This version of Mac OS X is unsupported"
#  endif
```

And finally FreeGLUT:

```bash
$ brew install freeglut
```

## Preparing the file system
Make a new working directory and clone the repository from GitHub:

```bash
$ mkdir nice
$ cd nice
$ git clone https://github.com/cvjena/nice-core.git
```

NICE needs to be built out-of-tree (in a separate directory next
to __nice-core__):

```bash
$ cd nice
$ mkdir build
$ cd build
```

## Building NICE-core
Navigate to the __build__ directory and build NICE-core like this:

```bash
$ cmake ../nice-core
$ make
```

### Mac OS X
Because we installed a different toolchain, we need to tell CMake about it.
The STL headers in Mac OS X are also slightly different, so call CMake like
this:

```bash
$ cmake -DCMAKE_CXX_FLAGS:STRING="-include sys/types.h" -DCMAKE_CXX_COMPILER=g++-4.8 -DCMAKE_C_COMPILER=gcc ../nice-core/
$ make
```
