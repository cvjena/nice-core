
# set(NICE_CURR_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
# ocv_glob_modules(${NICE_CURR_DIR})
ocv_add_module(core)

ocv_module_include_directories()
ocv_glob_module_sources()
ocv_create_module()


# set(NICE_CURR_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
# ocv_glob_modules(${NICE_CURR_DIR})

ADD_EXECUTABLE(testConfig ./basics/progs/testConfig.cpp)
ADD_EXECUTABLE(testMemoryUsage ./basics/progs/testMemoryUsage.cpp)

TARGET_LINK_LIBRARIES(testConfig libnice_core_basics libnice_core_vector)
TARGET_LINK_LIBRARIES(testMemoryUsage libnice_core_basics)

INSTALL(TARGETS testConfig DESTINATION bin)
INSTALL(TARGETS testMemoryUsage DESTINATION bin)


###

#CONFIGURE_FILE(
#  "CMakeDefinesConfig.h.in"
#  "${PROJECT_BINARY_DIR}/CMakeDefinesConfig.h"
#)
#include_directories("${PROJECT_BINARY_DIR}")
