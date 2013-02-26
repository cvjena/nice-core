
ADD_EXECUTABLE(testApproxGaussFilter testApproxGaussFilter.cpp)
#ADD_EXECUTABLE(testGenericSobelFilter testGenericSobelFilter.cpp)

TARGET_LINK_LIBRARIES(testApproxGaussFilter nice_core nice_core_image ${Boost_LIBRARIES} ${ImageMagick_LIBRARIES} ${PNG_LIBRARIES} )#nice_core_algebra nice_core_basics ${Boost_LIBRARIES})
#TARGET_LINK_LIBRARIES(testGenericSobelFilter nice_core ${Boost_LIBRARIES})#nice_core_algebra nice_core_basics ${Boost_LIBRARIES})

INSTALL(TARGETS testApproxGaussFilter DESTINATION bin)
#INSTALL(TARGETS testGenericSobelFilter DESTINATION bin)
