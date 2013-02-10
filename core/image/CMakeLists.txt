set( core_image_src Algorithms.cpp
BlockImageAccessT.tcc
Buffer.tcc
CircleT.tcc
ColorImageAccess.cpp
ColorImageT.cpp
ColorImageT.tcc
ColorT.tcc
Convert.cpp
Convert.tcc
CrossT.tcc
DeprecatedConverter.cpp
DeprecatedConverter.tcc
EllipseT.tcc
Filter.cpp
Filter.tcc
FilterT.cpp
FilterT.tcc
Fourier.cpp
GaussPyramid.cpp
GHough.cpp
GrayColorImageCommonImplementation.cpp
GrayColorImageCommonImplementationT.tcc
Histogram.cpp
ImageAccess.cpp
ImageAccessT.tcc
ImageFile.cpp
ImageFileListReader.cpp
ImageFileListWriter.cpp
ImageFile.tcc
ImageInputStream.cpp
ImageOutputStream.cpp
ImageT.cpp
ImageTools.cpp
ImageTools.tcc
ImageT.tcc
ippwrapper.tcc
LineT.tcc
Morph.cpp
Morph.tcc
MultiChannelImageT.cpp
MultiChannelImageT.tcc
Pixel.tcc
PointT.tcc
RectangleT.tcc
RectT.tcc
Region.cpp
)

ADD_LIBRARY(core_image ${NICE_BUILD_LIBS_STATIC_SHARED} ${core_image_src})

INSTALL(TARGETS core_image DESTINATION libs)
