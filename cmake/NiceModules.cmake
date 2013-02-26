# clean flags for modules enabled on previous cmake run
# this is necessary to correctly handle modules removal
foreach(mod ${OPENCV_MODULES_BUILD} ${OPENCV_MODULES_DISABLED_USER} ${OPENCV_MODULES_DISABLED_AUTO} ${OPENCV_MODULES_DISABLED_FORCE})
  if(HAVE_${mod})
    unset(HAVE_${mod} CACHE)
  endif()
  unset(OPENCV_MODULE_${mod}_REQ_DEPS CACHE)
  unset(OPENCV_MODULE_${mod}_OPT_DEPS CACHE)
endforeach()

# clean modules info which needs to be recalculated
set(OPENCV_MODULES_PUBLIC         "" CACHE INTERNAL "List of OpenCV modules marked for export")
set(OPENCV_MODULES_BUILD          "" CACHE INTERNAL "List of OpenCV modules included into the build")
set(OPENCV_MODULES_DISABLED_USER  "" CACHE INTERNAL "List of OpenCV modules explicitly disabled by user")
set(OPENCV_MODULES_DISABLED_AUTO  "" CACHE INTERNAL "List of OpenCV modules implicitly disabled due to dependencies")
set(OPENCV_MODULES_DISABLED_FORCE "" CACHE INTERNAL "List of OpenCV modules which can not be build in current configuration")


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

# collect modules from specified directories
# NB: must be called only once!
macro(ocv_glob_modules modulepath)
  if(DEFINED OPENCV_INITIAL_PASS)
    message(FATAL_ERROR "OpenCV has already loaded its modules. Calling ocv_glob_modules second time is not allowed.")
  endif()
  set(__directories_observed "")

  #nice-----
  #get_filename_component(currDirName ${CMAKE_CURRENT_SOURCE_DIR} NAME )
  #get_filename_component(currDirName ${modulepath} NAME )
  #set(the_module "${the_module}_${currDirName}")
  #message(STATUS "currDirName=${currDirName}")
  #------
  
  # collect modules
  set(OPENCV_INITIAL_PASS ON)
  foreach(__path ${modulepath} ) #${ARGN})
    ocv_get_real_path(__path "${__path}")

    list(FIND __directories_observed "${__path}" __pathIdx)
    if(__pathIdx GREATER -1)
      message(FATAL_ERROR "The directory ${__path} is observed for OpenCV modules second time.")
    endif()
    list(APPEND __directories_observed "${__path}")

    file(GLOB __ocvmodules RELATIVE "${__path}" "${__path}/*")
    if(__ocvmodules)
      list(SORT __ocvmodules)
      foreach(mod ${__ocvmodules})
        ocv_get_real_path(__modpath "${__path}/${mod}")
        if(EXISTS "${__modpath}/CMakeLists.txt")
	      #message(STATUS "${__modpath} adding subdir")
          list(FIND __directories_observed "${__modpath}" __pathIdx)
          if(__pathIdx GREATER -1)
            message(FATAL_ERROR "The module from ${__modpath} is already loaded.")
          endif()
          list(APPEND __directories_observed "${__modpath}")

          if(OCV_MODULE_RELOCATE_ON_INITIAL_PASS)
            #file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/${mod}/.${mod}")
            file(COPY "${__modpath}/CMakeLists.txt" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/${mod}/.${mod}")
            add_subdirectory("${CMAKE_CURRENT_BINARY_DIR}/${mod}/.${mod}" "${CMAKE_CURRENT_BINARY_DIR}/${mod}/.${mod}")
            if("${OPENCV_MODULE_opencv_${mod}_LOCATION}" STREQUAL "${CMAKE_CURRENT_BINARY_DIR}/${mod}/.${mod}")
              set(OPENCV_MODULE_opencv_${mod}_LOCATION "${__modpath}" CACHE PATH "" FORCE)
            endif()
          else()
            #org: add_subdirectory("${__modpath}" "${CMAKE_CURRENT_BINARY_DIR}/${mod}/.${mod}")
			add_subdirectory("${__modpath}" "${CMAKE_CURRENT_BINARY_DIR}/${mod}")
          endif()
        endif()
      endforeach()
    endif()
  endforeach()
  ocv_clear_vars(__ocvmodules __directories_observed __path __modpath __pathIdx)

  # resolve dependencies
#  __ocv_flatten_module_dependencies()

  # create modules
  set(OPENCV_INITIAL_PASS OFF PARENT_SCOPE)
  set(OPENCV_INITIAL_PASS OFF)
  foreach(m ${OPENCV_MODULES_BUILD})
    message(STATUS "${OPENCV_MODULES_BUILD}")
    if(m MATCHES "^opencv_")
      string(REGEX REPLACE "^opencv_" "" __shortname "${m}")
      add_subdirectory("${OPENCV_MODULE_${m}_LOCATION}" "${CMAKE_CURRENT_BINARY_DIR}/${__shortname}")
    endif()
  endforeach()
  unset(__shortname)
endmacro()


# adds dependencies to OpenCV module
# Usage:
#   add_dependencies(opencv_<name> [REQUIRED] [<list of dependencies>] [OPTIONAL <list of modules>])
# Notes:
# * <list of dependencies> - can include full names of modules or full pathes to shared/static libraries or cmake targets
macro(ocv_add_dependencies full_modname)
  #we don't clean the dependencies here to allow this macro several times for every module
  foreach(d "REQUIRED" ${ARGN})
    if(d STREQUAL "REQUIRED")
      set(__depsvar OPENCV_MODULE_${full_modname}_REQ_DEPS)
    elseif(d STREQUAL "OPTIONAL")
      set(__depsvar OPENCV_MODULE_${full_modname}_OPT_DEPS)
    else()
      list(APPEND ${__depsvar} "${d}")
    endif()
  endforeach()
  unset(__depsvar)

  ocv_list_unique(OPENCV_MODULE_${full_modname}_REQ_DEPS)
  ocv_list_unique(OPENCV_MODULE_${full_modname}_OPT_DEPS)

  set(OPENCV_MODULE_${full_modname}_REQ_DEPS ${OPENCV_MODULE_${full_modname}_REQ_DEPS} CACHE INTERNAL "Required dependencies of ${full_modname} module")
  set(OPENCV_MODULE_${full_modname}_OPT_DEPS ${OPENCV_MODULE_${full_modname}_OPT_DEPS} CACHE INTERNAL "Optional dependencies of ${full_modname} module")
endmacro()


# declare new OpenCV module in current folder
# Usage:
#   ocv_add_module(<name> [INTERNAL|BINDINGS] [REQUIRED] [<list of dependencies>] [OPTIONAL <list of optional dependencies>])
# Example:
#   ocv_add_module(yaom INTERNAL opencv_core opencv_highgui opencv_flann OPTIONAL opencv_gpu)
macro(ocv_add_module _name)
  #string(TOLOWER "${_name}" name)
  #string(REGEX REPLACE "^opencv_" "" ${name} "${name}")
  #set(the_module opencv_${name})
  #-----
  get_filename_component(currDirName ${CMAKE_CURRENT_SOURCE_DIR} NAME )
  set(the_module "${the_module}_${currDirName}")
  #----
  
  # the first pass - collect modules info, the second pass - create targets
  if(OPENCV_INITIAL_PASS)
    #guard agains redefinition
    if(";${OPENCV_MODULES_BUILD};${OPENCV_MODULES_DISABLED_USER};" MATCHES ";${the_module};")
      message(FATAL_ERROR "Redefinition of the ${the_module} module.
  at:                    ${CMAKE_CURRENT_SOURCE_DIR}
  previously defined at: ${OPENCV_MODULE_${the_module}_LOCATION}
")
    endif()

    if(NOT DEFINED the_description)
      set(the_description "The ${name} OpenCV module")
    endif()

    if(NOT DEFINED BUILD_${the_module}_INIT)
      set(BUILD_${the_module}_INIT ON)
    endif()

    # create option to enable/disable this module
#    option(BUILD_${the_module} "Include ${the_module} module into the OpenCV build" ${BUILD_${the_module}_INIT})

    # remember the module details
    set(OPENCV_MODULE_${the_module}_DESCRIPTION "${the_description}" CACHE INTERNAL "Brief description of ${the_module} module")
    set(OPENCV_MODULE_${the_module}_LOCATION    "${CMAKE_CURRENT_SOURCE_DIR}" CACHE INTERNAL "Location of ${the_module} module sources")

    # parse list of dependencies
    if("${ARGV1}" STREQUAL "INTERNAL" OR "${ARGV1}" STREQUAL "BINDINGS")
      set(OPENCV_MODULE_${the_module}_CLASS "${ARGV1}" CACHE INTERNAL "The cathegory of the module")
      set(__ocv_argn__ ${ARGN})
      list(REMOVE_AT __ocv_argn__ 0)
      ocv_add_dependencies(${the_module} ${__ocv_argn__})
      unset(__ocv_argn__)
    else()
      set(OPENCV_MODULE_${the_module}_CLASS "PUBLIC" CACHE INTERNAL "The cathegory of the module")
      ocv_add_dependencies(${the_module} ${ARGN})
      if(BUILD_${the_module})
        set(OPENCV_MODULES_PUBLIC ${OPENCV_MODULES_PUBLIC} "${the_module}" CACHE INTERNAL "List of OpenCV modules marked for export")
      endif()
    endif()

    # add self to the world dependencies
    if(NOT DEFINED OPENCV_MODULE_IS_PART_OF_WORLD AND NOT OPENCV_MODULE_${the_module}_CLASS STREQUAL "BINDINGS" OR OPENCV_MODULE_IS_PART_OF_WORLD)
      ocv_add_dependencies(opencv_world OPTIONAL ${the_module})
    endif()

    if(BUILD_${the_module})
      set(OPENCV_MODULES_BUILD ${OPENCV_MODULES_BUILD} "${the_module}" CACHE INTERNAL "List of OpenCV modules included into the build")
    else()
      set(OPENCV_MODULES_DISABLED_USER ${OPENCV_MODULES_DISABLED_USER} "${the_module}" CACHE INTERNAL "List of OpenCV modules explicitly disabled by user")
    endif()

    # TODO: add submodules if any

    # stop processing of current file
#    return()
  else(OPENCV_INITIAL_PASS)
    if(NOT BUILD_${the_module})
      return() # extra protection from redefinition
    endif()
    project(${the_module})
  endif(OPENCV_INITIAL_PASS)
endmacro()


# setup include paths for the list of passed modules
macro(ocv_include_modules)
  foreach(d ${ARGN})
    if(d MATCHES "^opencv_" AND HAVE_${d})
#		message(STATUS "${OPENCV_MODULE_${d}_LOCATION}")
      if (EXISTS "${OPENCV_MODULE_${d}_LOCATION}/include")
        ocv_include_directories("${OPENCV_MODULE_${d}_LOCATION}/include")
      endif()
    elseif(EXISTS "${d}")
      ocv_include_directories("${d}")
    endif()
  endforeach()
endmacro()

# setup include path for OpenCV headers for specified module
# ocv_module_include_directories(<extra include directories/extra include modules>)
macro(ocv_module_include_directories)
#  ocv_include_directories("${OPENCV_MODULE_${the_module}_LOCATION}/include"
#                          "${OPENCV_MODULE_${the_module}_LOCATION}/src"
#                          "${CMAKE_CURRENT_BINARY_DIR}" # for precompiled headers
#                          )
  ocv_include_directories("${OPENCV_MODULE_${the_module}_LOCATION}/"
                          "${CMAKE_CURRENT_BINARY_DIR}" # for precompiled headers
                          )						  
  ocv_include_modules(${OPENCV_MODULE_${the_module}_DEPS} ${ARGN})
endmacro()


# sets header and source files for the current module
# NB: all files specified as headers will be installed
# Usage:
# ocv_set_module_sources([HEADERS] <list of files> [SOURCES] <list of files>)
macro(ocv_set_module_sources)
  #opencv: set(OPENCV_MODULE_${the_module}_HEADERS "" )
  #opencv: set(OPENCV_MODULE_${the_module}_SOURCES "" )
  set(OPENCV_MODULE_${the_module}_HEADERS "" PARENT_SCOPE)
  set(OPENCV_MODULE_${the_module}_SOURCES "" PARENT_SCOPE)

  foreach(f "HEADERS" ${ARGN})
    if(f STREQUAL "HEADERS" OR f STREQUAL "SOURCES")
      set(__filesvar "OPENCV_MODULE_${the_module}_${f}")
    else()
      list(APPEND ${__filesvar} "${f}")
    endif()
  endforeach()

  # the hacky way to embeed any files into the OpenCV without modification of its build system
  if(COMMAND ocv_get_module_external_sources)
    ocv_get_module_external_sources()
  endif()

  # use full paths for module to be independent from the module location
  ocv_convert_to_full_paths(OPENCV_MODULE_${the_module}_HEADERS)

  set(OPENCV_MODULE_${the_module}_HEADERS ${OPENCV_MODULE_${the_module}_HEADERS} CACHE INTERNAL "List of header files for ${the_module}")
  set(OPENCV_MODULE_${the_module}_SOURCES ${OPENCV_MODULE_${the_module}_SOURCES} CACHE INTERNAL "List of source files for ${the_module}")
endmacro()

# finds and sets headers and sources for the standard OpenCV module
# Usage:
# ocv_glob_module_sources(<extra sources&headers in the same format as used in ocv_set_module_sources>)
macro(ocv_glob_module_sources)
#  file(GLOB_RECURSE lib_srcs "src/*.cpp")
#  file(GLOB_RECURSE lib_int_hdrs "src/*.hpp" "src/*.h")
#  file(GLOB lib_hdrs "include/opencv2/${name}/*.hpp" "include/opencv2/${name}/*.h")
#  file(GLOB lib_hdrs_detail "include/opencv2/${name}/detail/*.hpp" "include/opencv2/${name}/detail/*.h")

#  source_group("Src" FILES ${lib_srcs} ${lib_int_hdrs})
#  source_group("Include" FILES ${lib_hdrs})
#  source_group("Include\\detail" FILES ${lib_hdrs_detail})

#  ocv_set_module_sources(${ARGN} HEADERS ${lib_hdrs} ${lib_hdrs_detail} SOURCES ${lib_srcs} ${lib_int_hdrs})

  file(GLOB lib_srcs "*.cpp")
  #file(GLOB_RECURSE lib_int_hdrs "./*.hpp" "./*.h")
  #file(GLOB_RECURSE lib_int_hdrs "./*.hpp" "./*.h")
  file(GLOB lib_hdrs "*.hpp" "*.h" "*.tcc")
  #message(status "lib_srcs: ${lib_srcs}")
  #message(status "lib_hdrs: ${lib_hdrs}")
  source_group("Src" FILES ${lib_srcs})
  source_group("Include" FILES ${lib_hdrs})
  ocv_set_module_sources(${ARGN} HEADERS ${lib_hdrs} SOURCES ${lib_srcs})
endmacro()

# creates OpenCV module in current folder
# creates new target, configures standard dependencies, compilers flags, install rules
# Usage:
#   ocv_create_module(<extra link dependencies>)
#   ocv_create_module(SKIP_LINK)
macro(ocv_create_module)
	##############################################
	### process all subdirs #####
	#get list subdirs
	# include subdirs if != progs && != test, handle these two separately
	set(__path "${CMAKE_CURRENT_SOURCE_DIR}")
	#file(GLOB __listSubdirs RELATIVE "${__path}" "${__path}/*")
    SUBDIRLIST(__listSubdirs "${__path}")
	if(__listSubdirs)
		list(SORT __listSubdirs)
		foreach(currSubDir ${__listSubdirs})
			ocv_get_real_path(__subdirpath "${__path}/${currSubDir}")
			#message(STATUS "${currSubDir}")
			#message(STATUS "subdir examining: ${__subdirpath}")
			if(EXISTS "${__subdirpath}/CMakeLists.txt")
				message(STATUS "${currSubDir} has CMakeLists.txt")
				if ( "${currSubDir}" STREQUAL "tests" )
					if( NICE_BUILD_TESTS )
						#add tests
						#add_subdirectory("${__subdirpath}")
					else()
						message(STATUS "by configuration: tests/ not added")
					endif()
				elseif( "${currSubDir}" STREQUAL "progs" )
					if( NICE_BUILD_PROGS )
						#add progs
						add_subdirectory("${__subdirpath}")
					else()
						message(STATUS "by configuration: progs/ not added")	
					endif()
				else()
					message(STATUS "adding subdir")
					add_subdirectory("${__subdirpath}")
					#add subdir sources to the accumulated source variable of this directory
					#message(STATUS "subdir-sources: ${OPENCV_MODULE_${the_module}_${currSubDir}_SOURCES}")
					set(OPENCV_MODULE_${the_module}_SOURCES "${OPENCV_MODULE_${the_module}_SOURCES}" "${OPENCV_MODULE_${the_module}_${currSubDir}_SOURCES}")
					set(OPENCV_MODULE_${the_module}_HEADERS "${OPENCV_MODULE_${the_module}_HEADERS}" "${OPENCV_MODULE_${the_module}_${currSubDir}_HEADERS}")
					#message(STATUS "accumulated sources of ${the_module}: ${OPENCV_MODULE_${the_module}_SOURCES}")
					#message(STATUS "accumulated headers of ${the_module}: ${OPENCV_MODULE_${the_module}_HEADERS}")
				endif()
			endif()
		endforeach()
	endif()

	##################################################

  #add_library(${the_module} ${OPENCV_MODULE_TYPE} ${OPENCV_MODULE_${the_module}_HEADERS} ${OPENCV_MODULE_${the_module}_SOURCES})
#  message(STATUS "linking source files of ${the_module}: ${OPENCV_MODULE_${the_module}_SOURCES}")
#  message(STATUS "linking header files of ${the_module}: ${OPENCV_MODULE_${the_module}_HEADERS}")
  add_library(${the_module} ${NICE_BUILD_LIBS_STATIC_SHARED} ${OPENCV_MODULE_${the_module}_HEADERS} ${OPENCV_MODULE_${the_module}_SOURCES})  

  if(NOT "${ARGN}" STREQUAL "SKIP_LINK")
    target_link_libraries(${the_module} ${OPENCV_MODULE_${the_module}_DEPS} ${OPENCV_MODULE_${the_module}_DEPS_EXT} ${OPENCV_LINKER_LIBS} ${IPP_LIBS} ${ARGN})
  endif()

#jojo  add_dependencies(opencv_modules ${the_module})

  if(ENABLE_SOLUTION_FOLDERS)
    set_target_properties(${the_module} PROPERTIES FOLDER "modules")
  endif()
	
#	message(STATUS "LIBRARY_OUTPUT_PATH: ${LIBRARY_OUTPUT_PATH}")
	#message(STATUS "EXECUTABLE_OUTPUT_PATH: ${EXECUTABLE_OUTPUT_PATH}")
  set_target_properties(${the_module} PROPERTIES
    OUTPUT_NAME "${the_module}${OPENCV_DLLVERSION}"
    DEBUG_POSTFIX "${OPENCV_DEBUG_POSTFIX}"
    ARCHIVE_OUTPUT_DIRECTORY ${LIBRARY_OUTPUT_PATH}
    RUNTIME_OUTPUT_DIRECTORY ${EXECUTABLE_OUTPUT_PATH}
    INSTALL_NAME_DIR lib
  )

  # For dynamic link numbering convenions
  if(NOT ANDROID)
    # Android SDK build scripts can include only .so files into final .apk
    # As result we should not set version properties for Android
    set_target_properties(${the_module} PROPERTIES
      VERSION ${OPENCV_VERSION}
      SOVERSION ${OPENCV_SOVERSION}
    )
  endif()

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

  # only "public" headers need to be installed
  if(OPENCV_MODULE_${the_module}_HEADERS AND ";${OPENCV_MODULES_PUBLIC};" MATCHES ";${the_module};")
    foreach(hdr ${OPENCV_MODULE_${the_module}_HEADERS})
      string(REGEX REPLACE "^.*opencv2/" "opencv2/" hdr2 "${hdr}")
      if(hdr2 MATCHES "^(opencv2/.*)/[^/]+.h(..)?$")
        install(FILES ${hdr} DESTINATION "${OPENCV_INCLUDE_INSTALL_PATH}/${CMAKE_MATCH_1}" COMPONENT main)
      endif()
    endforeach()
  endif()
endmacro()


# opencv precompiled headers macro (can add pch to modules and tests)
# this macro must be called after any "add_definitions" commands, otherwise precompiled headers will not work
# Usage:
# ocv_add_precompiled_headers(${the_module})
macro(ocv_add_precompiled_headers the_target)
    if("${the_target}" MATCHES "^opencv_test_.*$")
        SET(pch_path "test/test_")
    elseif("${the_target}" MATCHES "^opencv_perf_.*$")
        SET(pch_path "perf/perf_")
    else()
        SET(pch_path "src/")
    endif()
    set(pch_header "${CMAKE_CURRENT_SOURCE_DIR}/${pch_path}precomp.hpp")

    if(PCHSupport_FOUND AND ENABLE_PRECOMPILED_HEADERS AND EXISTS "${pch_header}")
        if(CMAKE_GENERATOR MATCHES Visual)
            set(${the_target}_pch "${CMAKE_CURRENT_SOURCE_DIR}/${pch_path}precomp.cpp")
            add_native_precompiled_header(${the_target} ${pch_header})
        elseif(CMAKE_GENERATOR MATCHES Xcode)
            add_native_precompiled_header(${the_target} ${pch_header})
        elseif(CMAKE_COMPILER_IS_GNUCXX AND CMAKE_GENERATOR MATCHES "Makefiles|Ninja")
            add_precompiled_header(${the_target} ${pch_header})
        endif()
    endif()
    unset(pch_header)
    unset(pch_path)
    unset(${the_target}_pch)
endmacro()