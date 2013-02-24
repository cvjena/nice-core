cmake_minimum_required(VERSION 2.8)
project (NICELibrary)

include(CheckSymbolExists)

# The version number.
set(NICELibrary_VERSION_MAJOR 1)
set(NICELibrary_VERSION_MINOR 0)

set(CMAKE_VERBOSE_MAKEFILE on) 

set(CMAKE_INSTALL_PREFIX ${PROJECT_BINARY_DIR})

set(NICE_BUILD_LIBS_STATIC_SHARED STATIC)

set(NICE_BUILD_PROGS 1)

FIND_PACKAGE(Boost COMPONENTS date_time filesystem)
IF (Boost_FOUND)
	message(STATUS "boost-incl-dir: ${Boost_INCLUDE_DIRS}")
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
    ADD_DEFINITIONS( "-DNICE_BOOST_FOUND" )
ENDIF()

#IF(WIN32)
 # MESSAGE(FATAL_ERROR "not yet ready")
#ENDIF(WIN32) 

# add the binary tree to the search path for include files
#include_directories ("${PROJECT_BINARY_DIR}")

#SET(CMAKE_USE_RELATIVE_PATHS ON)
#check_symbol_exists("__assert_fail" "assert.h" HAVE_ASSERT_FAIL)

include(cmake/OpenCVUtils.cmake REQUIRE)
include(cmake/NiceModules.cmake REQUIRE)

set(OPENCV_LIB_INSTALL_PATH lib)

INCLUDE_DIRECTORIES(".")
INCLUDE_DIRECTORIES(core)

set(the_module "libnice")

set(NICE_CURR_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
SUBDIRLIST(__listSubDirs "${NICE_CURR_DIR}")
ocv_glob_modules( ${NICE_CURR_DIR} )
# foreach(_curSubdir ${__listSubDirs})
	# ocv_get_real_path(__modpath "${NICE_CURR_DIR}/${_curSubdir}/")
	# if(EXISTS "${__modpath}/CMakeLists.txt")
		# message(STATUS "add module: ${__modpath}")
		set(__modpath "${__modpath}/")
		message(STATUS "add module: ${__modpath}")
		# ocv_glob_modules( ${__modpath} )
	# endif()
# endforeach()
#ADD_SUBDIRECTORY(core bin)
  
# doxygen support
FIND_PROGRAM(DOXYGEN_EXECUTABLE "doxygen")


#cmake code from: https://github.com/hmeyer/dcmtk/blob/master/CMakeLists.txt
# libxml support
# OPTION(WITH_LIBXML "Build with libxml support." OFF)
# FIND_PATH(WITH_LIBXMLINC "include/libxml/parser.h" "${dcmtk_SOURCE_DIR}/../libxml2-2.6.26")
# # libpng support
# OPTION(WITH_LIBPNG "Build with libpng support." ON)
# FIND_PATH(WITH_LIBPNGINC "include/png.h" "${dcmtk_SOURCE_DIR}/../libpng-1.2.8")
# # libtiff support
# OPTION(WITH_LIBTIFF "Build with libtiff support." ON)
# FIND_PATH(WITH_LIBTIFFINC "include/tiff.h" "${dcmtk_SOURCE_DIR}/../tiff-3.7.4")
# # openssl support
# OPTION(WITH_OPENSSL "Build with openssl support." OFF)
# FIND_PATH(WITH_OPENSSLINC "include/openssl/ssl.h" "${dcmtk_SOURCE_DIR}/../openssl-0.9.8a")
# # zlib support
# OPTION(WITH_ZLIB "Build with zlib support." ON)
# FIND_PATH(WITH_ZLIBINC "include/zlib.h" "${dcmtk_SOURCE_DIR}/../zlib-1.2.3")



# add the install targets
#install (TARGETS ImageLabeler DESTINATION bin)
#install (FILES "${PROJECT_BINARY_DIR}/TutorialConfig.h"        
#         DESTINATION include)
