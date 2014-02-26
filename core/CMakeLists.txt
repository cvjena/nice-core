####################################################
## library individual settings

#library name (name is appended to "nice_" to form the target library name)
set(the_library "core")

#add linkage dependencies to other libraries here
set("nice_${the_library}_LINKING_DEPENDENCIES"  ${Boost_LIBRARIES} ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${QT_LIBRARIES} ${IPP_LIBRARIES} ${ImageMagick_LIBRARIES})
if(MATIO_FOUND)
  list(APPEND nice_${the_library}_LINKING_DEPENDENCIES ${MATIO_LIBRARIES})
endif(MATIO_FOUND)

#####################################################
message(STATUS "adding library ${the_library}")

nice_get_source_files()

nice_build_library()

nice_add_progs()

nice_add_unittests()

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