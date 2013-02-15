SET(core_vector_src Algorithms.cpp Algorithms.tcc
Distance.cpp
Distance.tcc
Eigen.tcc
ippwrapper.cpp
ippwrapper.tcc
MatrixT.tcc
RowMatrixT.tcc
SparseVectorT.tcc
VectorT.tcc
VVector.cpp
)

ADD_LIBRARY(core_vector ${NICE_BUILD_LIBS_STATIC_SHARED} ${core_vector_src})

INSTALL(TARGETS core_vector DESTINATION libs)
