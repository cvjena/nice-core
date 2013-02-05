
ADD_EXECUTABLE(testConfig testConfig.cpp)
ADD_EXECUTABLE(testMemoryUsage testMemoryUsage.cpp) 

TARGET_LINK_LIBRARIES(testConfig core_basics)
TARGET_LINK_LIBRARIES(testMemoryUsage core_basics)

INSTALL(TARGETS testConfig DESTINATION bin)
INSTALL(TARGETS testMemoryUsage DESTINATION bin)
