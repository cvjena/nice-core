SET(core_algebra_src CholeskyRobustAuto.cpp    EigValues.cpp       GenericMatrix.cpp         ILSConjugateGradients.cpp         ILSPlainGradient.cpp       LUDecomposition.cpp
CholeskyRobust.cpp        EigValuesTRLAN.cpp  GMSparseVectorMatrix.cpp  ILSConjugateGradientsLanczos.cpp  ILSSymmLqLanczos.cpp
DiagonalMatrixApprox.cpp  GBCDSolver.cpp      GMStandard.cpp            ILSMinResLanczos.cpp              IterativeLinearSolver.cpp
)

ADD_LIBRARY(core_algebra SHARED ${core_algebra_src}) 

INSTALL(TARGETS core_algebra DESTINATION libs)
