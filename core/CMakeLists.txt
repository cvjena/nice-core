include( corefiles.cmake)
include( progfiles.cmake)
include( testfiles.cmake)

#message(STATUS "nice_core_hdr:${NICE_CORE_HDR}")

ADD_LIBRARY(nice_core ${NICE_BUILD_LIBS_STATIC_SHARED} ${NICE_CORE_HDR} ${NICE_CORE_SRC})
TARGET_LINK_LIBRARIES(nice_core ${Boost_LIBRARIES} ${OPENGL_LIBRARY} ${GLUT_LIBRARY} ${QT_LIBRARIES})
SET_PROPERTY(TARGET nice_core PROPERTY FOLDER "library")
INSTALL(TARGETS nice_core DESTINATION lib)


if(BUILD_CORE_PROGS)
  message(STATUS "building progs:")
  foreach(__progcpp ${NICE_PROGFILES_SRC})
    get_filename_component(__progname ${__progcpp} NAME_WE )
    message(STATUS "progname: ${__progname} ${__progcpp}")
    ADD_EXECUTABLE( ${__progname} ${__progcpp})
    TARGET_LINK_LIBRARIES(${__progname} nice_core)
    INSTALL(TARGETS ${__progname} DESTINATION bin)
	SET_PROPERTY(TARGET ${__progname} PROPERTY FOLDER "programs")
  endforeach()
endif()

if(BUILD_CORE_TESTS)
  INCLUDE_DIRECTORIES(${CPPUNIT_INCLUDE_DIR})
  message(STATUS "building tests:")
  foreach(__testcpp ${NICE_TESTFILES_SRC})
    get_filename_component(__testname ${__testcpp} NAME_WE )
    message(STATUS "unittest: ${__testname} ${__testcpp}")
    
    ADD_EXECUTABLE( ${__testname} ../templates/cppUnitTestRunner.cpp ${__testcpp})
    TARGET_LINK_LIBRARIES(${__testname} nice_core ${CPPUNIT_LIBRARIES} )

    INSTALL(TARGETS ${__testname} DESTINATION tests)
	SET_PROPERTY(TARGET ${__testname} PROPERTY FOLDER "unittests")
	if(BUILD_CORE_TESTS_PERFORM_AS_POSTBUILD_STEP)
		add_custom_command(TARGET ${__testname}
                   POST_BUILD
                   COMMAND "$<TARGET_FILE:${__testname}>"
                   COMMENT "Unit Tests...")
	else()
		ADD_TEST(${__testname} UnitTester ${__testname})
	endif()
  endforeach()
endif()

#####
 set(the_module "nice_core")
 if(ENABLE_SOLUTION_FOLDERS)
    set_target_properties(${the_module} PROPERTIES FOLDER "modules")
  endif()
	
  set_target_properties(${the_module} PROPERTIES
    OUTPUT_NAME "${the_module}${OPENCV_DLLVERSION}"
    DEBUG_POSTFIX "${OPENCV_DEBUG_POSTFIX}"
    ARCHIVE_OUTPUT_DIRECTORY ${LIBRARY_OUTPUT_PATH}
    RUNTIME_OUTPUT_DIRECTORY ${EXECUTABLE_OUTPUT_PATH}
    INSTALL_NAME_DIR lib
  )
  
  if(BUILD_SHARED_LIBS)
    if(MSVC)
      set_target_properties(${the_module} PROPERTIES DEFINE_SYMBOL CVAPI_EXPORTS)
    else()
      add_definitions(-DCVAPI_EXPORTS)
    endif()
  endif()

  if(MSVC)
    if(CMAKE_CROSSCOMPILING)
      set_target_properties(${the_module} PROPERTIES LINK_FLAGS "/NODEFAULTLIB:secchk")
    endif()
    set_target_properties(${the_module} PROPERTIES LINK_FLAGS "/NODEFAULTLIB:libc /DEBUG")
  endif()

  install(TARGETS ${the_module}
    RUNTIME DESTINATION bin COMPONENT main
    LIBRARY DESTINATION ${OPENCV_LIB_INSTALL_PATH} COMPONENT main
    ARCHIVE DESTINATION ${OPENCV_LIB_INSTALL_PATH} COMPONENT main
    )

#   # only "public" headers need to be installed
#   if(OPENCV_MODULE_${the_module}_HEADERS AND ";${OPENCV_MODULES_PUBLIC};" MATCHES ";${the_module};")
#     foreach(hdr ${OPENCV_MODULE_${the_module}_HEADERS})
#       string(REGEX REPLACE "^.*opencv2/" "opencv2/" hdr2 "${hdr}")
#       if(hdr2 MATCHES "^(opencv2/.*)/[^/]+.h(..)?$")
#         install(FILES ${hdr} DESTINATION "${OPENCV_INCLUDE_INSTALL_PATH}/${CMAKE_MATCH_1}" COMPONENT main)
#       endif()
#     endforeach()
#   endif()


#############################################################
# set(NICE_CURR_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
# ocv_glob_modules(${NICE_CURR_DIR})
#ocv_add_module(core)

#ocv_module_include_directories()
#ocv_glob_module_sources()
#ocv_create_module()


# set(NICE_CURR_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
# ocv_glob_modules(${NICE_CURR_DIR})

# ADD_EXECUTABLE(testConfig ./basics/progs/testConfig.cpp)
# ADD_EXECUTABLE(testMemoryUsage ./basics/progs/testMemoryUsage.cpp)

# TARGET_LINK_LIBRARIES(testConfig libnice_core_basics libnice_core_vector)
# TARGET_LINK_LIBRARIES(testMemoryUsage libnice_core_basics)

# INSTALL(TARGETS testConfig DESTINATION bin)
# INSTALL(TARGETS testMemoryUsage DESTINATION bin)


###

#CONFIGURE_FILE(
#  "CMakeDefinesConfig.h.in"
#  "${PROJECT_BINARY_DIR}/CMakeDefinesConfig.h"
#)
#include_directories("${PROJECT_BINARY_DIR}")
