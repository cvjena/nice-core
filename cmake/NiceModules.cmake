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





# collect modules from specified directories
# NB: must be called only once!
macro(ocv_glob_modules)
  if(DEFINED OPENCV_INITIAL_PASS)
    message(FATAL_ERROR "OpenCV has already loaded its modules. Calling ocv_glob_modules second time is not allowed.")
  endif()
  set(__directories_observed "")

  # collect modules
  set(OPENCV_INITIAL_PASS ON)
  foreach(__path ${ARGN})
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
	message(STATUS "${__modpath}")
        if(EXISTS "${__modpath}/CMakeLists.txt")
	  message(STATUS "${__modpath} adding subdir")
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
            add_subdirectory("${__modpath}" "${CMAKE_CURRENT_BINARY_DIR}/${mod}/.${mod}")
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
  string(TOLOWER "${_name}" name)
  string(REGEX REPLACE "^opencv_" "" ${name} "${name}")
  set(the_module opencv_${name})

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
  ocv_include_directories("${OPENCV_MODULE_${the_module}_LOCATION}/include"
                          "${OPENCV_MODULE_${the_module}_LOCATION}/src"
                          "${CMAKE_CURRENT_BINARY_DIR}" # for precompiled headers
                          )
  ocv_include_modules(${OPENCV_MODULE_${the_module}_DEPS} ${ARGN})
endmacro()