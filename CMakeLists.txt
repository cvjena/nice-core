#cmake_minimum_required(VERSION 2.8.6) #version 2.8.6 at least required because of command set(CMAKE_AUTOMOC TRUE) for qt moc-ing (see below)
cmake_minimum_required(VERSION 2.8.6)
project (NICELibrary)

include(CheckSymbolExists)
include(CheckIncludeFiles)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

include(cmake/NiceModules.cmake REQUIRED)

# The version number.
set(NICELibrary_VERSION_MAJOR 1)
set(NICELibrary_VERSION_MINOR 2)
set(NICE_VERSION ${NICELibrary_VERSION_MAJOR}.${NICELibrary_VERSION_MINOR})

NICE_OPTION(NICE_BUILD_DEBUG "NICE Debug Build for debugging" OFF )
if(NICE_BUILD_DEBUG)
  message(STATUS "NICE debug build enabled")
  set (CMAKE_BUILD_TYPE Debug)
else()
  set (CMAKE_BUILD_TYPE Release)
endif()

NICE_OPTION(CMAKE_VERBOSE "Verbose mode" OFF )
if(CMAKE_VERBOSE)
  set(CMAKE_VERBOSE_MAKEFILE 1)
endif()

set(CMAKE_INSTALL_PREFIX ${PROJECT_BINARY_DIR})

set(NICE_SOURCEFILES_FIND_GLOBALLYRECURSIVE ON CACHE STRING "Scan a sublibraries directory for source files instead of using an explicit src file list")

NICE_OPTION(WITH_BOOST "Build with Boost support" OFF)
if(WITH_BOOST)
  set(Boost_USE_STATIC_LIBS ON)
  FIND_PACKAGE(Boost COMPONENTS date_time filesystem)
  IF (Boost_FOUND)
	  message(STATUS "boost-incl-dir: ${Boost_INCLUDE_DIRS}")
      INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
      ADD_DEFINITIONS( "-DNICE_BOOST_FOUND" )
	  ADD_DEFINITIONS( "-DNICE_USELIB_BOOST" )
  ENDIF()
endif()

FIND_PACKAGE(CppUnit)
IF (CPPUNIT_FOUND)
	message(STATUS "CppUnit-dir: ${CPPUNIT_INCLUDE_DIR}")
    INCLUDE_DIRECTORIES(${CPPUNIT_INCLUDE_DIR})
    ADD_DEFINITIONS( "-DNICE_USELIB_CPPUNIT" )
    ADD_DEFINITIONS( "-DCPPUNIT_USE_TYPEINFO_NAME") #converting test class name into test name
else()
  #set(CPPUNIT_INCLUDE_DIR "/usr/include/") #can be found in  /usr/include/cppunit
 # ADD_DEFINITIONS( "-DNICE_USELIB_CPPUNIT" )
  message(STATUS "CppUnit not found")
ENDIF()

NICE_OPTION(WITH_DBV_LIBRARIES "Build with DBV extern librares" OFF)
if(WITH_DBV_LIBRARIES)

  set(NICE_DBV_LIBRARIES_DIR "/home/dbv/3rdparty64-gcc43/")
  if(EXISTS "${NICE_DBV_LIBRARIES_DIR}")
    message(STATUS "using DBV extern librares in ${NICE_DBV_LIBRARIES_DIR}")

    NICE_OPTION(WITH_IPP "Build with Intel IPP support" ON)
    if(WITH_IPP)
      set(ENV{IPPROOT} "${NICE_DBV_LIBRARIES_DIR}ipp53/")

      include("cmake/NiceFindIPP.cmake")
      if(IPP_FOUND)
        #message(STATUS "ipp link dir: ${IPP_LIBRARY_DIRS}")
        #message(STATUS "ipp link libs: ${IPP_LIBRARIES}")
        ADD_DEFINITIONS( "-DNICE_USELIB_IPP=5" )
        INCLUDE_DIRECTORIES(${IPP_INCLUDE_DIRS})
        
      else()
        message(STATUS "IPP library not found")
      endif()
    endif()
  else()
    message( SEND_ERROR "trying to use DBV extern library dir, but couldn't be found ${NICE_DBV_LIBRARIES_DIR}. Switch off DBV Usage to continue.") #unsetting dbv libraries path
    unset(WITH_DBV_LIBRARIES) #unsetting, since dbv dir not found
  endif()
endif()

NICE_OPTION(WITH_OPENMP "Build with OpenMP support" ON)
if(WITH_OPENMP)
  find_package(OpenMP)
  if (OPENMP_FOUND)
      set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
      set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
      ADD_DEFINITIONS( "-DNICE_USELIB_OPENMP")
  endif()
endif()

NICE_OPTION(WITH_PNG "Build with libPNG support" OFF)
if(WITH_PNG)
    find_package(PNG)
    if (PNG_FOUND)
      INCLUDE_DIRECTORIES(${PNG_INCLUDE_DIRS})
      ADD_DEFINITIONS( "-DNICE_USELIB_PNG")
    endif()
endif()

NICE_OPTION(WITH_MATIO "Build with Matio and HDF5 support" OFF)
if(WITH_MATIO)
  find_package(HDF5)
  if(HDF5_FOUND)
    message(STATUS "HDF5-dir: ${HDF5_INCLUDE_DIR}")
  endif()
  find_package(MATIO)
  if(MATIO_FOUND)
    message(STATUS "Matio-dir: ${MATIO_INCLUDE_DIRS}")
    ADD_DEFINITIONS( "-DNICE_USELIB_MATIO")
    INCLUDE_DIRECTORIES(${MATIO_INCLUDE_DIRS})
  endif()
endif()

NICE_OPTION(WITH_IMAGEMAGICK "Build with ImageMagick++" OFF)
if(WITH_IMAGEMAGICK)
  find_package(ImageMagick COMPONENTS Magick++ MagickCore)
  if(ImageMagick_FOUND)
	  message(STATUS "imagemagick found: ${ImageMagick_LIBRARIES}")
    ADD_DEFINITIONS( "-DNICE_USELIB_LIBMAGICK")
    INCLUDE_DIRECTORIES(${ImageMagick_INCLUDE_DIRS})
	else()
	  message(STATUS "imagemagick not found")
  endif()
endif()

NICE_OPTION(WITH_QT "Build with Qt" ON)
if(WITH_QT)
  FIND_PACKAGE(Qt4 REQUIRED)# COMPONENTS QtOpenGl)
  SET(QT_USE_QTOPENGL TRUE)
  SET(QT_USE_QTXML TRUE)
  if(QT_FOUND)
    set(CMAKE_AUTOMOC TRUE) #see doc: http://blogs.kde.org/2011/11/01/cool-new-stuff-cmake-286-automoc
    INCLUDE(${QT_USE_FILE})
    ADD_DEFINITIONS(${QT_DEFINITIONS})
    ADD_DEFINITIONS( "-DNICE_USELIB_QT")
  endif()
endif()

NICE_OPTION(WITH_OPENGL "Build with OpenGL" ON)
if(WITH_OPENGL)
  find_package(OpenGL)
  if(OPENGL_FOUND)
    message(STATUS "OPENGL found")
    include_directories( ${OPENGL_INCLUDE_DIRS} )
    ADD_DEFINITIONS( "-DNICE_USELIB_OPENGL")
  endif()

  #try using GLUT
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

endif()

if(NOT WIN32)
  #check for available regex stuff
  CHECK_INCLUDE_FILES(regex.h HAVE_REGEX_H)
  if(HAVE_REGEX_H)
    ADD_DEFINITIONS(-DNICE_USELIB_REGEX)  #regular expressions are available per default under linux
    message(STATUS "Regex found")
  endif()
endif()

if(MSVC)
  #enable solution folders
  SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)
  SET_PROPERTY(GLOBAL PROPERTY AUTOMOC_FOLDER automoc) #in future (>cmake1.8.11 this might separate the automoc projects into a separate solution folder)
  
  #in Visual Studio avoid overwriting of std::max with macro definition max() in WinDef.h (http://support.microsoft.com/kb/143208/de)
  ADD_DEFINITIONS("-DNOMINMAX")
endif()

NICE_OPTION(BUILD_UNITTESTS "Build all unit tests" ON IF CPPUNIT_FOUND)
#if(CPPUNIT_FOUND)
#	set(BUILD_UNITTESTS ON)
#else()
#	set(BUILD_UNITTESTS OFF)
#endif()
if( BUILD_UNITTESTS)
	enable_testing()
	include(CTest)
endif()

NICE_OPTION(BUILD_PROGRAMS "Build all programs" ON)

set(OPENCV_LIB_INSTALL_PATH lib)

INCLUDE_DIRECTORIES(".")
INCLUDE_DIRECTORIES(core)

set(the_module "nice")

set(NICE_CURR_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
SUBDIRLIST(__listSubDirs "${NICE_CURR_DIR}")
set(__listSubLibs "")
foreach(_curSubdir ${__listSubDirs})
	nice_get_real_path(__modpath "${NICE_CURR_DIR}/${_curSubdir}/")
	if(EXISTS "${__modpath}/CMakeLists.txt")
		#ADD_SUBDIRECTORY(${__modpath})
	    LIST(APPEND __listSubLibs ${_curSubdir})
	  NICE_OPTION(BUILD_LIB_${_curSubdir} "Build library ${_curSubdir}" ON)
	endif()
endforeach()

foreach(_curSublib ${__listSubLibs})
  if(BUILD_LIB_${_curSublib})
    nice_get_real_path(__modpath "${NICE_CURR_DIR}/${_curSublib}/")
    ADD_SUBDIRECTORY(${__modpath})
  endif()
endforeach()

# doxygen support
#FIND_PROGRAM(DOXYGEN_EXECUTABLE "doxygen")


##############################################################################################
configure_file(cmake/templates/NICELibraryConfigVersion.cmake.in "${PROJECT_BINARY_DIR}/NICELibraryConfigVersion.cmake" @ONLY)

##############################################################################################

include (InstallRequiredSystemLibraries) # This module will include any runtime libraries that are needed by the project for the current platform
SET(CPACK_GENERATOR "RPM")
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "Johannes R.") #required
SET(CPACK_PACKAGE_NAME "NICE New Image Library")
SET(CPACK_PACKAGE_VENDOR "Computer Vision Group Jena, University of Jena")
INCLUDE(CPack)
