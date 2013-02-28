if(BUILD_CORE_IMAGE)
#message(STATUS "vector_location: ${OPENCV_MODULE_opencv_vector_LOCATION}")

ocv_add_module(image)# ${Boost_LIBRARIES})# INTERNAL libnice_core_vector)

ocv_clear_vars(ADDITIONAL_CORE_IMAGE_LIBS)
if(IMAGEMAGIC_FOUND) #NICE_USELIB_LIBMAGICK
endif()

if(WITH_PNG OR WITH_TIFF OR WITH_OPENEXR)
  #ocv_include_directories(${ZLIB_INCLUDE_DIR})
  #list(APPEND GRFMT_LIBS ${ZLIB_LIBRARIES})
endif()

if(WITH_JPEG)
  #add_definitions(-DHAVE_JPEG)
  #ocv_include_directories(${JPEG_INCLUDE_DIR})
  #list(APPEND GRFMT_LIBS ${JPEG_LIBRARIES})
endif()

if(WITH_PNG)
  #add_definitions(-DHAVE_PNG)
  #add_definitions(${PNG_DEFINITIONS})
  #ocv_include_directories(${PNG_INCLUDE_DIR})
  #list(APPEND GRFMT_LIBS ${PNG_LIBRARIES})
endif()

if(WITH_TIFF)
  #add_definitions(-DHAVE_TIFF)
  #ocv_include_directories(${TIFF_INCLUDE_DIR})
  #list(APPEND GRFMT_LIBS ${TIFF_LIBRARIES})
endif()

#message(STATUS "vector_location: ${OPENCV_MODULE_vector_LOCATION}")

ocv_module_include_directories()#${Boost_INCLUDE_DIR})
#message(STATUS "vec-sources: ${OPENCV_MODULE_libnice_core_vector_SOURCES}")
ocv_glob_module_sources()#(SOURCES ${OPENCV_MODULE_libnice_core_vector_SOURCES})
ocv_create_module()

#add_subdirectory(progs bin)
endif()