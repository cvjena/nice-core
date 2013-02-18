set(NICE_CURR_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "${NICE_CURR_DIR}")
get_filename_component(currDirName ${NICE_CURR_DIR} NAME )
message(status "CMAKE_CURRENT_LIST_DIR : ${currDirName}")
set(testvar "${testvar}core_")
message(STATUS "before: ${testvar}")

ocv_glob_modules(${NICE_CURR_DIR})
message(STATUS "after: ${testvar}")

####
ADD_EXECUTABLE(testConfig ./basics/progs/testConfig.cpp)
ADD_EXECUTABLE(testMemoryUsage ./basics/progs/testMemoryUsage.cpp) 

TARGET_LINK_LIBRARIES(testConfig libnice_core_basics libnice_core_vector)
TARGET_LINK_LIBRARIES(testMemoryUsage libnice_core_basics libnice_core_vector)

INSTALL(TARGETS testConfig DESTINATION bin)
INSTALL(TARGETS testMemoryUsage DESTINATION bin)


###

#CONFIGURE_FILE(
#  "CMakeDefinesConfig.h.in"
#  "${PROJECT_BINARY_DIR}/CMakeDefinesConfig.h"
#)
#include_directories("${PROJECT_BINARY_DIR}")

#INCLUDE_DIRECTORIES(basics)
#INCLUDE_DIRECTORIES(algebra)
#INCLUDE_DIRECTORIES(vector)
#INCLUDE_DIRECTORIES(optimization)
#INCLUDE_DIRECTORIES(image)

#INCLUDE_DIRECTORIES(iceconversion)
#INCLUDE_DIRECTORIES(imagedisplay)
#INCLUDE_DIRECTORIES(matlabAccess)
#INCLUDE_DIRECTORIES(progs)

#ADD_SUBDIRECTORY(basics)
#ADD_SUBDIRECTORY(algebra)
#ADD_SUBDIRECTORY(vector)
#ADD_SUBDIRECTORY(optimization)
#ADD_SUBDIRECTORY(image)

#SET(core_src 
#${core_basics_src} 
#${core_algebra_src}
#${core_vector_src}
#${core_optimization}
#${core_image}
#)

#MESSAGE(STATUS "${core_src}")

#ADD_LIBRARY(core ${NICE_BUILD_LIBS_STATIC_SHARED} ${core_src})
