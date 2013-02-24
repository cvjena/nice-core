#message(STATUS "vector_location: ${OPENCV_MODULE_opencv_vector_LOCATION}")

ocv_add_module(basics)# INTERNAL libnice_core_vector)

#message(STATUS "vector_location: ${OPENCV_MODULE_vector_LOCATION}")

ocv_module_include_directories()
#message(STATUS "vec-sources: ${OPENCV_MODULE_libnice_core_vector_SOURCES}")
ocv_glob_module_sources()#(SOURCES ${OPENCV_MODULE_libnice_core_vector_SOURCES})
ocv_create_module()

#add_subdirectory(progs bin)