cmake_minimum_required(VERSION 2.8.6) #version 2.8.6 at least required because of command set(CMAKE_AUTOMOC TRUE) for qt moc-ing (see below)
project (NICELibrary)

include(CheckSymbolExists)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

#include(cmake/OpenCVUtils.cmake REQUIRED)
#include(cmake/OpenCVDetectCXXCompiler.cmake REQUIRED)
include(cmake/NiceModules.cmake REQUIRED)
#include(cmake/OpenCVCompilerOptions.cmake REQUIRED)

# The version number.
set(NICELibrary_VERSION_MAJOR 1)
set(NICELibrary_VERSION_MINOR 0)

set(CMAKE_VERBOSE_MAKEFILE off) 

set(CMAKE_INSTALL_PREFIX ${PROJECT_BINARY_DIR})

set(NICE_BUILD_LIBS_STATIC_SHARED STATIC)

set(NICE_BUILD_PROGS 1)

set(Boost_USE_STATIC_LIBS ON)
FIND_PACKAGE(Boost COMPONENTS date_time filesystem)
IF (Boost_FOUND)
	message(STATUS "boost-incl-dir: ${Boost_INCLUDE_DIRS}")
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
    ADD_DEFINITIONS( "-DNICE_BOOST_FOUND" )
	ADD_DEFINITIONS( "-DNICE_USELIB_BOOST" )
ENDIF()

FIND_PACKAGE(CppUnit)
IF (CPPUNIT_FOUND)
	message(STATUS "CppUnit-dir: ${CPPUNIT_INCLUDE_DIR}")
    INCLUDE_DIRECTORIES(${CPPUNIT_INCLUDE_DIR})
    ADD_DEFINITIONS( "-DNICE_USELIB_CPPUNIT" )
else()
  #set(CPPUNIT_INCLUDE_DIR "/usr/include/") #can be found in  /usr/include/cppunit
 # ADD_DEFINITIONS( "-DNICE_USELIB_CPPUNIT" )
  message(STATUS "CppUnit not found")
ENDIF()

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    ADD_DEFINITIONS( "-DNICE_USELIB_OPENMP")
endif()

#find_package(PNG)
if (PNG_FOUND)
  INCLUDE_DIRECTORIES(${PNG_INCLUDE_DIRS})
  ADD_DEFINITIONS( "-DNICE_USELIB_PNG")
endif()


find_package(ImageMagick COMPONENTS Magick++)
if(ImageMagick_FOUND)
	message(STATUS "imagemagick found: ${ImageMagick_LIBRARIES}")
	else()
	message(STATUS "imagemagick not found")
endif()

FIND_PACKAGE(Qt4)# COMPONENTS Qt3Support QtOpenGl)
SET(QT_USE_QTOPENGL TRUE)
SET(QT_USE_QTXML TRUE)
SET(QT_USE_QT3SUPPORT TRUE)
if(QT_FOUND)
#  ADD_DEFINITIONS("-DQT3_SUPPORT")
  message(STATUS "QTfound ${QT_QT3SUPPORT_INCLUDE_DIR}")
  set(CMAKE_AUTOMOC TRUE) #see doc: http://blogs.kde.org/2011/11/01/cool-new-stuff-cmake-286-automoc
  INCLUDE(${QT_USE_FILE})
  #INCLUDE(${QT_QT3SUPPORT_INCLUDE_DIR})
  ADD_DEFINITIONS(${QT_DEFINITIONS})
  ADD_DEFINITIONS( "-DNICE_USELIB_QT")
endif()
find_package(OpenGL)
if(OPENGL_FOUND)
  message(STATUS "OPENGL found")
  include_directories( ${OPENGL_INCLUDE_DIRS} )
  ADD_DEFINITIONS( "-DNICE_USELIB_OPENGL")
endif()

if(WIN32)
	message(STATUS "find GLUT for win32")
	set(GLUT_INCLUDE_DIR "C:/Libraries/freeglut-MSVC-2.8.0-1.mp/freeglut/include/")# , where to find GL/glut.h, etc.
	set(GLUT_ROOT_PATH "C:/Libraries/freeglut-MSVC-2.8.0-1.mp/freeglut/") #  GLUT_LIBRARIES
	set(tmp_OPENGL_LIBRARY_DIR "${OPENGL_LIBRARY_DIR}") #temporarily store opengl_lib path
	set(OPENGL_LIBRARY_DIR "${GLUT_ROOT_PATH}lib")
	find_package(GLUT)
	if(GLUT_FOUND)
	  message(STATUS "GLUT found")
	  include_directories( ${GLUT_INCLUDE_DIR} )
	  ADD_DEFINITIONS( -DNICE_USELIB_GLUT)
	  #ADD_DEFINITIONS(-DBUILD_VTI -DFREEGLUT_STATIC) with static seems not to work
	endif()
	set(OPENGL_LIBRARY_DIR "${tmp_OPENGL_LIBRARY_DIR}") #reset opengl lib path
else()
	find_package(GLUT)
	if(GLUT_FOUND)
	  message(STATUS "GLUT found")
	  include_directories( ${GLUT_INCLUDE_DIR} )
	  ADD_DEFINITIONS(-DNICE_USELIB_GLUT)
	endif()
endif()

#find_package(ImageMagick COMPONENTS Magick++)
#if(ImageMagick_FOUND)
#  INCLUDE_DIRECTORIES(${ImageMagick_INCLUDE_DIRS})
#  ADD_DEFINITIONS( "-DNICE_USELIB_LIBMAGICK")
#endif()

if(MSVC)
  #enable solution folders
  SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)
  SET_PROPERTY(GLOBAL PROPERTY AUTOMOC_FOLDER automoc) #in future (>cmake1.8.11 this might separate the automoc projects into a separate solution folder)
  
  #in Visual Studio avoid overwriting of std::max with macro definition max() in WinDef.h (http://support.microsoft.com/kb/143208/de)
  ADD_DEFINITIONS("-DNOMINMAX")
endif()

set(BUILD_CORE_VECTOR ON)
set(BUILD_CORE_BASICS ON)
#set(BUILD_CORE_ALGEBRA ON)
#set(BUILD_CORE_OPTIMIZATION ON)
#set(BUILD_CORE_IMAGE ON)
#set(BUILD_CORE_MATLABACCESS ON)
if(CPPUNIT_FOUND)
	set(BUILD_CORE_TESTS ON)
else()
	set(BUILD_CORE_TESTS OFF)
endif()
	
set(BUILD_CORE_PROGS ON)

if( BUILD_CORE_TESTS)
	enable_testing()
	include(CTest)
endif()

set(OPENCV_LIB_INSTALL_PATH lib)

INCLUDE_DIRECTORIES(".")
INCLUDE_DIRECTORIES(core)

#set(the_module "libnice")
set(the_module "nice")

set(NICE_CURR_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
SUBDIRLIST(__listSubDirs "${NICE_CURR_DIR}")
foreach(_curSubdir ${__listSubDirs})
	nice_get_real_path(__modpath "${NICE_CURR_DIR}/${_curSubdir}/")
	if(EXISTS "${__modpath}/CMakeLists.txt")
		ADD_SUBDIRECTORY(${__modpath})
	endif()
endforeach()
#ADD_SUBDIRECTORY(core)
#ADD_SUBDIRECTORY(vislearning)
  

# doxygen support
#FIND_PROGRAM(DOXYGEN_EXECUTABLE "doxygen")


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
