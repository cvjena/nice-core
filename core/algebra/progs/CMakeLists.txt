
ADD_EXECUTABLE(testILSConjugateGradients testILSConjugateGradients.cpp)
#ADD_EXECUTABLE(testMemoryUsage testMemoryUsage.cpp) 

message(STATUS "boost_Libraries: ${Boost_LIBRARIES}")
TARGET_LINK_LIBRARIES(testILSConjugateGradients libnice_core_algebra libnice_core_basics ${Boost_LIBRARIES})
#TARGET_LINK_LIBRARIES(testMemoryUsage libnice_core_basics libnice_core_vector)

INSTALL(TARGETS testILSConjugateGradients DESTINATION bin)
#INSTALL(TARGETS testMemoryUsage DESTINATION bin)
