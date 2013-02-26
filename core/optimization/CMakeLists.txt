if(BUILD_CORE_OPTIMIZATION)
#get_filename_component(currDirName ${CMAKE_CURRENT_SOURCE_DIR} NAME )
#set(the_module "${the_module}_${currDirName}")

#add_subdirectory(blackbox)
#add_subdirectory(gradientBased)

ocv_add_module(optimization)

ocv_module_include_directories()
ocv_glob_module_sources()
ocv_create_module()
endif()