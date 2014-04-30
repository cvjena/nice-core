####################################################################################
# Help function for building the NICE library and its sub-libraries.
# Inspired by the OpenCV cmake build system.
#
# Author: Johannes Ruehle
# Date: 2014-02-17
#
####################################################################################


# get a list of all sub directories in curdir
MACRO(SUBDIRLIST result curdir)
  FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
  SET(dirlist "")
  FOREACH(child ${children})
    IF(IS_DIRECTORY ${curdir}/${child})
        SET(dirlist ${dirlist} ${child})
    ENDIF()
  ENDFOREACH()
  SET(${result} ${dirlist})
ENDMACRO()

# get absolute path with symlinks resolved
macro(nice_get_real_path VAR PATHSTR)
  if(CMAKE_VERSION VERSION_LESS 2.8)
    get_filename_component(${VAR} "${PATHSTR}" ABSOLUTE)
  else()
    get_filename_component(${VAR} "${PATHSTR}" REALPATH)
  endif()
endmacro()

# get the source files and store them in the variables:
# ${nice_${the_library}_TESTFILES_SRC} (unit test cpps)
# ${nice_${the_library}_PROGFILES_SRC} (progs cpps)
# ${nice_${the_library}_SRC} (library cpp and tcc excluding progs and unit test cpps)
# ${nice_${the_library}_HDR} (all library header files)
#  
# Two methods for obtaining the source files:
# 1) recursively scan all subdirectories
# cmake variable NICE_SOURCEFILES_FIND_GLOBALLYRECURSIVE has to be set and to be true (1).
#   Notes:
#   - To exclude certain source files from appending in the source var, use the file black listing 
#   in a file "list_exclude_from_build.cmake" by adding it to the variable "list_exclude_from_build_SRC" 
#   in that file.
#   - All *moc_* files will be removed from the source file list variables
# 2) use the given *.cmake files that define variables containing the source and header files to be used for build:
#     corefiles.cmake (Source files for Library build)
#     progfiles.cmake (source files for progam builds)
#     testfiles.cmake (source files for unit test builds)
#
#
#Note: Variable ${the_library} contains the current (sub-)library name that called this function, 
# e.g. ${the_library} == 'core', ${the_library}=='vislearning'
#
# Author: Johannes Ruehle
# Date: 2014-02-17
#
macro(nice_get_source_files)
  if(NICE_SOURCEFILES_FIND_GLOBALLYRECURSIVE)
    message(STATUS "Recursively scanning for source files")


    #include local file containing a list of files to be excluded from compilation
    #list is in variable list_exclude_from_build_SRC
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/list_exclude_from_build.cmake")
      #message(STATUS "exclude list found")
      include(list_exclude_from_build.cmake)
      message(STATUS "exclude list:${list_exclude_from_build_SRC}")
    endif()


    ### Get all unit test cpp files recursively
    set(nice_${the_library}_TESTFILES_SRC "")
    set(nice_${the_library}_PROGFILES_SRC "")
    set(nice_${the_library}_SRC"")
    

    #message(STATUS "CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")
    file(GLOB_RECURSE list_tmp1 RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" *.cpp *.tcc *.c)
    #message(STATUS "list_tmp1: ${list_tmp1}")
    foreach( t_SrcFile ${list_tmp1})
      if( NOT t_SrcFile MATCHES "moc_" )
        if( t_SrcFile MATCHES "tests/" )
          #message(STATUS "test: ${t_SrcFile}")
          LIST(APPEND nice_${the_library}_TESTFILES_SRC ${t_SrcFile})
        elseif( t_SrcFile MATCHES "progs/" )
          #message(STATUS "prog: ${t_SrcFile}")
          LIST(APPEND nice_${the_library}_PROGFILES_SRC ${t_SrcFile})
        else()
          LIST(APPEND nice_${the_library}_SRC ${t_SrcFile})
        endif()
      endif()
    endforeach()


    ### Get all cpp and tcc files recursively but exclude progs and unit test files
    #file(GLOB_RECURSE nice_${the_library}_SRC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp *.tcc)
    #filter out source files listed on the blacklist to be excluded from build
    if(list_exclude_from_build_SRC)
      list( REMOVE_ITEM nice_${the_library}_SRC ${list_exclude_from_build_SRC} )  
      list( REMOVE_ITEM nice_${the_library}_TESTFILES_SRC ${list_exclude_from_build_SRC} )  
    endif()      

    #message(STATUS "globallyrecusive_tests: ${nice_${the_library}_TESTFILES_SRC}")
    #message(STATUS "globallyrecusive_progs: ${nice_${the_library}_PROGFILES_SRC}")

    ### Get all header files recursively
    file(GLOB_RECURSE nice_${the_library}_HDR RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.h)
    
  else()
    message(STATUS "Using source files from file lists (*.cmake)")
    #define variable nice_<libname>_HDR and nice_<libname>_SRC for library header and source files (don't include progs and test source files here)
    include( corefiles.cmake)

    #define variable nice_<libname>_PROGFILES_HDR and nice_<libname>_PROGFILES_SRC for program header and source files (don't include library and test source files here)
    include( progfiles.cmake)

    #define variable nice_<libname>_TESTFILES_HDR and nice_<libname>_TESTFILES_SRC for unit test header and source files (don't include library and progs source files here)
    include( testfiles.cmake) 
  endif()
endmacro()

macro(nice_build_library)
  ADD_LIBRARY("nice_${the_library}" ${nice_${the_library}_HDR} ${nice_${the_library}_SRC})
  TARGET_LINK_LIBRARIES("nice_${the_library}" ${nice_${the_library}_LINKING_DEPENDENCIES})
  #TARGET_LINK_LIBRARIES("nice_${the_library}" ${nice_${the_library}_LINKING_DEPENDENCIES} ${Boost_LIBRARIES} ${OPENGL_LIBRARY} ${GLUT_LIBRARY} ${QT_LIBRARIES})
  SET_PROPERTY(TARGET "nice_${the_library}" PROPERTY FOLDER "library")
  INSTALL(TARGETS "nice_${the_library}" DESTINATION lib EXPORT "nice_${the_library}-exports")
  INSTALL(EXPORT "nice_${the_library}-exports" DESTINATION lib/exports)

  install(DIRECTORY ./ DESTINATION "include/${the_library}"
          FILES_MATCHING 
          PATTERN "*.h"
          PATTERN "*.tcc"
	  PATTERN ".git" EXCLUDE)

  configure_file( ../cmake/niceConfig.cmake.in "${PROJECT_BINARY_DIR}/lib/nice_${the_library}Config.cmake" )
endmacro()


# Create builds for all programs that are in the subvariable ${nice_${the_library}_PROGFILES_SRC}
# and build them into "bin/${the_library}"
#
# Variable BUILD_PROGRAMS has to be set and true to invoke progam build. The Variable is controllable 
# via the main CMakeLists.txt file (or ccmake)
#
#Note: Variable ${the_library} contains the current (sub-)library name that called this function, 
# e.g. ${the_library} == 'core', ${the_library}=='vislearning'
# using subvariables ${nice_${the_library}_PROGFILES_SRC}
#
# Author: Johannes Ruehle
# Date: 2014-02-17
#
macro(nice_add_progs)

  if(BUILD_PROGRAMS)
    message(STATUS "building progs:")
    
    foreach(__progcpp ${nice_${the_library}_PROGFILES_SRC})
      get_filename_component(__progname ${__progcpp} NAME_WE )
      #message(STATUS "progname: ${__progname} ${__progcpp}")
    
      set(prog_target_name "${the_library}_${__progname}")
      ADD_EXECUTABLE( ${prog_target_name} ${__progcpp})
      TARGET_LINK_LIBRARIES(${prog_target_name} "nice_${the_library}")
      SET_TARGET_PROPERTIES(${prog_target_name} PROPERTIES OUTPUT_NAME "${__progname}")
      
      INSTALL(TARGETS ${prog_target_name} DESTINATION "bin/${the_library}")
      
      SET_PROPERTY(TARGET ${prog_target_name} PROPERTY FOLDER "programs/${the_library}")
    
    endforeach()
  endif()

endmacro()

# Create unit test (using library CppUnitTest) for all cpp files in the subvariable ${nice_${the_library}_TESTFILES_SRC}
# and build them into "bin/${the_library}"
#
# Variable BUILD_UNITTESTS has to be set and true to invoke unit test building. 
# The Variable is controllable via the main CMakeLists.txt file (or ccmake)
#
#Note: Variable ${the_library} contains the current (sub-)library name that called this function, 
# e.g. ${the_library} == 'core', ${the_library}=='vislearning'
#
# Author: Johannes Ruehle
# Date: 2014-02-17
#
macro(nice_add_unittests)

  if(BUILD_UNITTESTS)
    INCLUDE_DIRECTORIES(${CPPUNIT_INCLUDE_DIR})
    message(STATUS "building tests:")
    foreach(__testcpp ${nice_${the_library}_TESTFILES_SRC})
      get_filename_component(__testname ${__testcpp} NAME_WE )
      nice_get_real_path(__testname_abspath ${__testcpp})
      get_filename_component(__testname_dir ${__testname_abspath} PATH)

      message(STATUS "unittest: ${__testname} ${__testcpp}")
      
      ADD_EXECUTABLE( ${__testname} ../templates/cppUnitTestRunner.cpp ${__testcpp})
      TARGET_LINK_LIBRARIES(${__testname} "nice_${the_library}" ${CPPUNIT_LIBRARIES} )

      INSTALL(TARGETS ${__testname} DESTINATION "tests/${the_library}")
      SET_PROPERTY(TARGET ${__testname} PROPERTY FOLDER "unittests/${the_library}")
      ADD_TEST(NAME ${__testname} WORKING_DIRECTORY ${__testname_dir} COMMAND ${__testname})
    endforeach()
  endif()

endmacro()


# Provides an option that the user can optionally select.
# Can accept condition to control when option is available for user.
# Usage:
#   option(<option_variable> "help string describing the option" <initial value or boolean expression> [IF <condition>])
# 
# CopyRight: OpenCV
macro(NICE_OPTION variable description value)
  set(__value ${value})
  set(__condition "")
  set(__varname "__value")
  foreach(arg ${ARGN})
    if(arg STREQUAL "IF" OR arg STREQUAL "if")
      set(__varname "__condition")
    else()
      list(APPEND ${__varname} ${arg})
    endif()
  endforeach()
  unset(__varname)
  if("${__condition}" STREQUAL "")
    set(__condition 2 GREATER 1)
  endif()

  if(${__condition})
    if("${__value}" MATCHES ";")
      if(${__value})
        option(${variable} "${description}" ON)
      else()
        option(${variable} "${description}" OFF)
      endif()
    elseif(DEFINED ${__value})
      if(${__value})
        option(${variable} "${description}" ON)
      else()
        option(${variable} "${description}" OFF)
      endif()
    else()
      option(${variable} "${description}" ${__value})
    endif()
  else()
    unset(${variable} CACHE)
  endif()
  unset(__condition)
  unset(__value)
endmacro()

