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


macro(nice_build_library)
  ADD_LIBRARY("nice_${the_library}" ${NICE_BUILD_LIBS_STATIC_SHARED} ${nice_${the_library}_HDR} ${nice_${the_library}_SRC})
  TARGET_LINK_LIBRARIES("nice_${the_library}" ${nice_${the_library}_LINKING_DEPENDENCIES})
  #TARGET_LINK_LIBRARIES("nice_${the_library}" ${nice_${the_library}_LINKING_DEPENDENCIES} ${Boost_LIBRARIES} ${OPENGL_LIBRARY} ${GLUT_LIBRARY} ${QT_LIBRARIES})
  SET_PROPERTY(TARGET "nice_${the_library}" PROPERTY FOLDER "library")
  INSTALL(TARGETS "nice_${the_library}" DESTINATION lib)

  configure_file( ../cmake/niceConfig.cmake.in "${PROJECT_BINARY_DIR}/lib/nice_${the_library}Config.cmake" )
endmacro()


#using variables "the_library"
#and subvariables ${nice_${the_library}_PROGFILES_SRC}
macro(nice_add_progs)

  if(BUILD_PROGRAMS)
    message(STATUS "building progs:")
    
    foreach(__progcpp ${nice_${the_library}_PROGFILES_SRC})
      get_filename_component(__progname ${__progcpp} NAME_WE )
      message(STATUS "progname: ${__progname} ${__progcpp}")
    
      set(prog_target_name "${the_library}_${__progname}")
      ADD_EXECUTABLE( ${prog_target_name} ${__progcpp})
      TARGET_LINK_LIBRARIES(${prog_target_name} "nice_${the_library}")
      SET_TARGET_PROPERTIES(${prog_target_name} PROPERTIES OUTPUT_NAME "${__progname}")
      
      INSTALL(TARGETS ${prog_target_name} DESTINATION "bin/${the_library}")
      
      SET_PROPERTY(TARGET ${prog_target_name} PROPERTY FOLDER "programs/${the_library}")
    
    endforeach()
  endif()

endmacro()

#using variables "the_library"
#and subvariables ${nice_${the_library}_TESTFILES_SRC}
macro(nice_add_unittests)

  if(BUILD_UNITTESTS)
    INCLUDE_DIRECTORIES(${CPPUNIT_INCLUDE_DIR})
    message(STATUS "building tests:")
    foreach(__testcpp ${nice_${the_library}_TESTFILES_SRC})
      get_filename_component(__testname ${__testcpp} NAME_WE )
      nice_get_real_path(__testname_abspath ${__testcpp})
      get_filename_component(__testname_dir ${__testname_abspath} DIRECTORY)

      message(STATUS "unittest: ${__testname} ${__testcpp}")
      
      ADD_EXECUTABLE( ${__testname} ../templates/cppUnitTestRunner.cpp ${__testcpp})
      TARGET_LINK_LIBRARIES(${__testname} "nice_${the_library}" ${CPPUNIT_LIBRARIES} )

      INSTALL(TARGETS ${__testname} DESTINATION "tests/${the_library}")
      SET_PROPERTY(TARGET ${__testname} PROPERTY FOLDER "unittests/${the_library}")
      ADD_TEST(${__testname} ${__testname} WORKING_DIRECTORY ${__testname_dir})
    endforeach()

#     INCLUDE_DIRECTORIES(${CPPUNIT_INCLUDE_DIR})
#     message(STATUS "building tests:")
# 
#       ADD_EXECUTABLE( "cppunits_${the_library}" ../templates/cppUnitTestRunner.cpp ${nice_${the_library}_TESTFILES_SRC})
#       TARGET_LINK_LIBRARIES("cppunits_${the_library}" "nice_${the_library}" ${CPPUNIT_LIBRARIES} )
# 
#       INSTALL(TARGETS "cppunits_${the_library}" DESTINATION "tests/${the_library}")
#       SET_PROPERTY(TARGET "cppunits_${the_library}" PROPERTY FOLDER "unittests/${the_library}")
#       ADD_TEST("cppunits_${the_library}" "cppunits_${the_library}")

  endif()

endmacro()

