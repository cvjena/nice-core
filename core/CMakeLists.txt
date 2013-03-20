####################################################
## library individual settings

#library name (name is appended to "nice_" to form the target library name)
set(the_library "core")

#define variable nice_<libname>_HDR and nice_<libname>_SRC for library header and source files (don't include progs and test source files here)
include( corefiles.cmake)

#define variable nice_<libname>_PROGFILES_HDR and nice_<libname>_PROGFILES_SRC for program header and source files (don't include library and test source files here)
include( progfiles.cmake)

#define variable nice_<libname>_TESTFILES_HDR and nice_<libname>_TESTFILES_SRC for unit test header and source files (don't include library and progs source files here)
include( testfiles.cmake)	

#add linkage dependencies to other libraries here
set("nice_${the_library}_LINKING_DEPENDENCIES" "")

#####################################################
message(STATUS "adding library ${the_library}")

ADD_LIBRARY("nice_${the_library}" ${NICE_BUILD_LIBS_STATIC_SHARED} ${nice_${the_library}_HDR} ${nice_${the_library}_SRC})
TARGET_LINK_LIBRARIES("nice_${the_library}" "${nice_${the_library}_LINKING_DEPENDENCIES}" ${Boost_LIBRARIES} ${OPENGL_LIBRARY} ${GLUT_LIBRARY} ${QT_LIBRARIES})
SET_PROPERTY(TARGET "nice_${the_library}" PROPERTY FOLDER "library")
INSTALL(TARGETS "nice_${the_library}" DESTINATION lib)


if(BUILD_CORE_PROGS)
  message(STATUS "building progs:")
  foreach(__progcpp ${nice_${the_library}_PROGFILES_SRC})
    get_filename_component(__progname ${__progcpp} NAME_WE )
    message(STATUS "progname: ${__progname} ${__progcpp}")
    ADD_EXECUTABLE( ${__progname} ${__progcpp})
    TARGET_LINK_LIBRARIES(${__progname} "nice_${the_library}")
    INSTALL(TARGETS ${__progname} DESTINATION bin)
	SET_PROPERTY(TARGET ${__progname} PROPERTY FOLDER "programs")
  endforeach()
endif()

if(BUILD_CORE_TESTS)
  INCLUDE_DIRECTORIES(${CPPUNIT_INCLUDE_DIR})
  message(STATUS "building tests:")
  foreach(__testcpp ${nice_${the_library}_TESTFILES_SRC})
    get_filename_component(__testname ${__testcpp} NAME_WE )
    message(STATUS "unittest: ${__testname} ${__testcpp}")
    
    ADD_EXECUTABLE( ${__testname} ../templates/cppUnitTestRunner.cpp ${__testcpp})
    TARGET_LINK_LIBRARIES(${__testname} "nice_${the_library}" ${CPPUNIT_LIBRARIES} )

    INSTALL(TARGETS ${__testname} DESTINATION tests)
	SET_PROPERTY(TARGET ${__testname} PROPERTY FOLDER "unittests")
	ADD_TEST(${__testname} ${__testname})
  endforeach()
endif()

#####
 set(the_module "nice_${the_library}")
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