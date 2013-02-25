
ADD_EXECUTABLE(testILSConjugateGradients testILSConjugateGradients.cpp)
ADD_EXECUTABLE(testILSmethods testILSmethods.cpp)
#ADD_EXECUTABLE(testMemoryUsage testMemoryUsage.cpp) 

#message(STATUS "boost_Libraries: ${Boost_LIBRARIES}")
TARGET_LINK_LIBRARIES(testILSConjugateGradients nice_core )#nice_core_algebra nice_core_basics ${Boost_LIBRARIES})
TARGET_LINK_LIBRARIES(testILSmethods nice_core )#nice_core_algebra nice_core_basics ${Boost_LIBRARIES})
#TARGET_LINK_LIBRARIES(testMemoryUsage libnice_core_basics libnice_core_vector)

INSTALL(TARGETS testILSConjugateGradients DESTINATION bin)
INSTALL(TARGETS testILSmethods DESTINATION bin)
#INSTALL(TARGETS testMemoryUsage DESTINATION bin)
