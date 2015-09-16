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

# get a list of all sub directories in curdir (recursive)
# this function lists only the directories that contain relevant files
MACRO(SUBDIRREC result curdir)
	FILE(GLOB_RECURSE children RELATIVE ${curdir} ${curdir}/*.c ${curdir}/*.cpp ${curdir}/*.h ${curdir}/*.tcc ${curdir}/Makefile)
	SET(dirlist "")
	FOREACH(child ${children})
		#message(STATUS ${child})
		GET_FILENAME_COMPONENT(to_add ${curdir}/${child} PATH)
		FILE(RELATIVE_PATH to_add_rel ${curdir} ${to_add})
		IF(IS_DIRECTORY ${curdir}/${to_add_rel})
			SET(dirlist ${dirlist} ${to_add_rel})
		ENDIF()
	ENDFOREACH()
	IF(NOT "${dirlist}" MATCHES "")
		LIST(REMOVE_DUPLICATES dirlist)
	ENDIF()
	SET(${result} ${dirlist})
ENDMACRO()


# update internal and external dependencies
#
# ${internal_deps} contains all the folders that are
# "allowed". files in folders that are not part of this list will
# _NOT_ be built.
# the relevant libdepend.inc files are parsed until no more changes
# are made
macro(UPDATE_NICE_DEPENDENCIES)
set(update_dependencies ON)
while(update_dependencies)
	message(STATUS "updating dependencies...")
	set(update_dependencies OFF)
	set(remove_these "")
	foreach(_curDep ${internal_deps})
		nice_get_real_path(_curDepPath ${NICE_CURR_DIR}/${_curDep})
		if(EXISTS ${_curDepPath}/libdepend.inc)
			#message(STATUS "Reading dependencies for ${_curDep}...")
			file(STRINGS ${_curDepPath}/libdepend.inc _dependencies REGEX "^[$][(]call( )+PKG_DEPEND_INT,")
			file(STRINGS ${_curDepPath}/libdepend.inc _extdependencies REGEX "^[$][(]call( )+PKG_DEPEND_EXT,")
			#message(STATUS "Deps: ${_dependencies}")
			#message(STATUS "Deps: ${_extdependencies}")

			list(LENGTH _dependencies _depCount)
			if(${_depCount} GREATER 0)
				foreach(_innerDep ${_dependencies})
					string(REGEX REPLACE "^[$][(]call( )+PKG_DEPEND_INT,(.*)[)].*$" "\\2" _innerDepName "${_innerDep}")
					string(REGEX REPLACE "(.*)/$" "\\1" _innerDepName ${_innerDepName})
					#message(STATUS "Inner dep: ${_innerDepName} (command: ${_innerDep})")
					list(FIND internal_deps "${_innerDepName}" _innerDepFound)
					if(${_innerDepFound} LESS 0)
						message(STATUS "Removing ${_curDep} from build because ${_innerDepName} is missing") 
						set(remove_these ${remove_these} ${_curDep})	
						set(update_dependencies ON)
					endif()
				endforeach()
			endif()

			list(LENGTH _extdependencies _extdepCount)
			if(${_extdepCount} GREATER 0)
				foreach(_extDep ${_extdependencies})
					string(REGEX REPLACE "^[$][(]call( )+PKG_DEPEND_EXT,(.*)[)].*$" "\\2" _extDepName "${_extDep}")
					string(REGEX REPLACE "(.*)/$" "\\1" _extDepName ${_extDepName})
					#message(STATUS "External dep: ${_extDepName} (command: ${_extDep})")
					list(FIND external_deps "${_extDepName}" _extDepFound)
					if(${_extDepFound} LESS 0)
						message(STATUS "Removing ${_curDep} from build because ${_extDepName} (external) is missing")
						set(remove_these ${remove_these} ${_curDep})
						set(update_dependencies ON)
					endif()
				endforeach()
			endif()

		endif()
	endforeach()
	foreach(_toRemove ${remove_these})
		message(STATUS "Checking subdirectories for ${_toRemove}")
		foreach(_checkDep ${internal_deps})
			if(${_checkDep} MATCHES "^${_toRemove}.*$")
				message(STATUS "Removing ${_checkDep}...")
				LIST(REMOVE_ITEM internal_deps ${_checkDep})
			endif()
		endforeach()
	endforeach()
endwhile()
message(STATUS "Done.")

endmacro()

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
    set(nice_${the_library}_MEXFILES_SRC "")
    set(nice_${the_library}_SRC"")
    

    #message(STATUS "CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")
    file(GLOB_RECURSE list_tmp1 RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" *.cpp *.tcc *.c *.C)
    #message(STATUS "list_tmp1: ${list_tmp1}")
    foreach( t_SrcFile ${list_tmp1})
      get_filename_component(t_SrcPath ${t_SrcFile} PATH)
      set(t_SrcPath ${the_library}/${t_SrcPath})
      string(REGEX REPLACE "(.*)/+$" "\\1" t_SrcPath ${t_SrcPath})
      list(FIND internal_deps ${t_SrcPath} dep_index)
      if(NOT ${dep_index} LESS 0)

	      if( NOT t_SrcFile MATCHES "moc_" )
		if( t_SrcFile MATCHES "tests/" )
		  #message(STATUS "test: ${t_SrcFile}")
		  LIST(APPEND nice_${the_library}_TESTFILES_SRC ${t_SrcFile})
		elseif( t_SrcFile MATCHES "progs/" )
		  #message(STATUS "prog: ${t_SrcFile}")
		  LIST(APPEND nice_${the_library}_PROGFILES_SRC ${t_SrcFile})
		elseif( t_SrcFile MATCHES "Mex[.]" )
		  message(STATUS "mex: ${t_SrcFile}")
		  LIST(APPEND nice_${the_library}_MEXFILES_SRC ${t_SrcFile})
		else()
		  LIST(APPEND nice_${the_library}_SRC ${t_SrcFile})
		endif()
	      endif()
      else()
	message(STATUS "Not building ${t_SrcFile} because ${t_SrcPath} is excluded (dependencies)")
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

    ### Get all header files recursively...
    # ... but filter the headers according to their "type", meaning whether they are part of a unit test, a prog, or a mex.
    # That means for example, that if you DO NOT WANT to build all progs in ./progs/ directories, all header files inside ./progs/ direcories 
    # should be excluded and not be consided in the build. The same example applies to unit tests (./tests/) and mex filex.
    # The reason is: The filter mechanism described above was also appied to source code files. So, we need to take care to have 
    # the source and header files synchronized, so that we avoid using only the header file of a class, but not its source code implementation file
    # which might lead to "undefined references" error. Especially in case of header file class definitions using Qt and an Q_OBJECT
    # definition, a header file is moc'ed but but will generate "undefined references" if the source code file is not available.
    file(GLOB_RECURSE list_tmp2 RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.h)
    set(nice_${the_library}_HDR "")
    foreach( t_HdrFile ${list_tmp2})
      get_filename_component(t_HdrPath ${t_HdrFile} PATH)
      set(t_HdrPath ${the_library}/${t_HdrPath})
      string(REGEX REPLACE "(.*)/+$" "\\1" t_HdrPath ${t_HdrPath})
      #list(FIND internal_deps ${t_HdrPath} dep_index)
      if( NOT t_HdrFile MATCHES "moc_" )
        if( t_HdrFile MATCHES "tests/" )
          if(BUILD_UNITTESTS)
            LIST(APPEND nice_${the_library}_HDR ${t_HdrFile})
          endif()
        elseif( t_HdrFile MATCHES "progs/" )
          if(BUILD_PROGRAMS)
            #message(STATUS "prog: ${t_HdrFile}")
            LIST(APPEND nice_${the_library}_HDR ${t_HdrFile})
          endif()
        elseif( t_HdrFile MATCHES "Mex[.]" )
          if(WITH_MEX)
            #message(STATUS "mex: ${t_HdrFile}")
            LIST(APPEND nice_${the_library}_HDR ${t_HdrFile})
          endif()
        else()
           LIST(APPEND nice_${the_library}_HDR ${t_HdrFile})
        endif()
      endif()
    endforeach()
    #message(STATUS "header files found: ${nice_${the_library}_HDR}")

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
  LIST(LENGTH nice_${the_library}_LINKING_DEPENDENCIES dependency_count)
  SET(tmp_dependencies "")
  IF(dependency_count GREATER 0)
	FOREACH(tmp_dependency ${nice_${the_library}_LINKING_DEPENDENCIES})
		IF("${tmp_dependency}" MATCHES "^nice_")
			STRING(REGEX REPLACE "^nice_(.*)" "\\1" tmp_dependency_nice ${tmp_dependency})
			LIST(FIND internal_deps ${tmp_dependency_nice} dep_found)
			IF(NOT ${dep_found} LESS 0)
				SET(tmp_dependencies ${tmp_dependencies} ${tmp_dependency})
			ELSE()
				MESSAGE(STATUS "${the_library} wants to link to NICE module: ${tmp_dependency_nice}, but it is not available.")
			ENDIF()
		ELSE()
			SET(tmp_dependencies ${tmp_dependencies} ${tmp_dependency})
		ENDIF()
	ENDFOREACH()
  ENDIF()
  SET(nice_${the_library}_LINKING_DEPENDENCIES ${tmp_dependencies})
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

# Add mex output
macro(nice_add_mexes)
  if(WITH_MEX)
    message(STATUS "building mexes:")
    
    foreach(__mexcpp ${nice_${the_library}_MEXFILES_SRC})
      get_filename_component(__mexname ${__mexcpp} NAME_WE )
      message(STATUS "mexname: ${__mexname} ${__mexcpp}")
    
      set(mex_target_name "${the_library}_${__mexname}")
      ADD_LIBRARY("${mex_target_name}" SHARED ${__mexcpp})
      TARGET_LINK_LIBRARIES(${mex_target_name} "nice_${the_library}")
      SET_TARGET_PROPERTIES(${mex_target_name} PROPERTIES OUTPUT_NAME "${__mexname}")
      SET_TARGET_PROPERTIES(${mex_target_name} PROPERTIES SUFFIX "${MEX_ENDING}")
      SET_TARGET_PROPERTIES(${mex_target_name} PROPERTIES PREFIX "")
      
      INSTALL(TARGETS ${mex_target_name} DESTINATION "bin/${the_library}")
      
      SET_PROPERTY(TARGET ${mex_target_name} PROPERTY FOLDER "programs/${the_library}")
    
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

