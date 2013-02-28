# find . -name "*.cpp" -ipath "*progs*" > progfiles.cmake.t
set(NICE_PROGFILES_SRC 
./image/progs/compareImages.cpp
./image/progs/convertImageNice.cpp
./image/progs/testApproxGaussFilter.cpp
./image/progs/testGenericSobelFilter.cpp
./matlabAccess/progs/testMatFileIO.cpp
./progs/imageDemo.cpp
./imagedisplay/progs/showImage.cpp
./basics/progs/testConfig.cpp
./basics/progs/testMemoryUsage.cpp
./algebra/progs/testILSMinResLanczos.cpp
./algebra/progs/testILSConjugateGradients.cpp
./algebra/progs/testILSmethods.cpp
./algebra/progs/testILSSymmLqLanczos.cpp
./algebra/progs/testILSConjugateGradientsLanczos.cpp
./vector/progs/testMatrixFunctions.cpp
./vector/progs/testCholeskySpeed.cpp
)

set(NICE_PROGFILES_HDR
)
