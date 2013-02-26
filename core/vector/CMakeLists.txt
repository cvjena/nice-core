ocv_add_module(vector)


ocv_clear_vars(ADDITIONAL_CORE_VECTOR_LIBS)

if(OPENMP_FOUND)#NICE_USELIB_OPENMP
  set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
  ADD_DEFINITIONS( "-DNICE_USELIB_OPENMP" )
  ocv_include_directories(${OpenMP_INCLUDE_DIR})
  #list(APPEND ADDITIONAL_CORE_VECTOR_LIBS ${PNG_LIBRARIES})
endif()

if(IPP_FOUND) #NICE_USELIB_IPP
endif()

if(LINAL_FOUND) #NICE_USELIB_LINAL
endif()

if(ZLIB_FOUND)#NICE_USELIB_ZLIB
endif()

if(BZLIB_FOUND)#NICE_USELIB_BZLIB //in test/TestSTreamable.cpp
endif()

if(CPPUNIT_FOUND)#NICE_USELIB_CPPUNIT
endif()

ocv_module_include_directories()
ocv_glob_module_sources()

#ocv_create_module(  ) 

ocv_create_module(${ADDITIONAL_CORE_VECTOR_LIBS})

if(MSVC)
  if(NOT ENABLE_NOISY_WARNINGS)
    ocv_warnings_disable(CMAKE_CXX_FLAGS /wd4996)
  endif()
endif()
#add_subdirectory(progs bin)





