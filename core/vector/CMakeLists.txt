message(STATUS "vector_location: ${OPENCV_MODULE_opencv_vector_LOCATION}")

ocv_add_module(vector)


set(testvar "${testvar}vector")
message(STATUS "before: ${testvar}")


message(STATUS "vector_location: ${OPENCV_MODULE_vector_LOCATION}")

ocv_module_include_directories()
ocv_glob_module_sources()
ocv_create_module()