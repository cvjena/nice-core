SET(core_algebra_src CholeskyRobustAuto.cpp    EigValues.cpp       GenericMatrix.cpp         ILSConjugateGradients.cpp         ILSPlainGradient.cpp       LUDecomposition.cpp
CholeskyRobust.cpp        EigValuesTRLAN.cpp  GMSparseVectorMatrix.cpp  ILSConjugateGradientsLanczos.cpp  ILSSymmLqLanczos.cpp
DiagonalMatrixApprox.cpp  GBCDSolver.cpp      GMStandard.cpp            ILSMinResLanczos.cpp              IterativeLinearSolver.cpp
)

ADD_LIBRARY(libcore_algebra SHARED ${core_algebra_src}) 
