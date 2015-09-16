# Tutorial 00 - Building and installing NICE-core

## Dependencies

### Linux
The following libraries and programs are required in order to build NICE-core.

 - Command line developer tools 
 - CMake 2.8.6 or later
 - Qt 4.x
 - OpenGL
 - GLUT 2.x

### Mac OS X
Newer version of Mac OS X ship with clang as the default compiler.
NICE depends on some libraries that are available from _homebrew_,
so you need to install it from [brew.sh](http://brew.sh) first.

You also need to install Qt 4.8.5 for Mac.
If you have Mac OS X 10.9, you also have to remove lines 330-332 from
_qtglobal.h_:

```c++
#  if (MAC_OS_X_VERSION_MAX_ALLOWED > MAC_OS_X_VERSION_10_8)
#    warning "This version of Mac OS X is unsupported"
#  endif
```

And finally FreeGLUT (using _homebrew_):

```bash
$ brew install freeglut
```

Sometimes you also need to specify an external framework path (like for MacPorts and Lion)

```
$ export DYLD_FRAMEWORK_PATH=/opt/local/Library/Frameworks/
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
