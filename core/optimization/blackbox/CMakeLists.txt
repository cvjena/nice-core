SET(core_optimization_blackbox_src CostFunction.cpp
DimWrapperCostFunction.cpp
DownhillSimplexOptimizer.cpp
Optimizable.cpp
Optimizer.cpp
OptLogBase.cpp
SimpleOptimizer.cpp
SimpleOptProblem.cpp
)

ADD_LIBRARY(core_optimization_blackbox ${NICE_BUILD_LIBS_STATIC_SHARED} ${core_optimization_blackbox_src})

INSTALL(TARGETS core_optimization_blackbox DESTINATION libs)
