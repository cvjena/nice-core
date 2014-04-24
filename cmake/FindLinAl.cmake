# Find the DBV library LinAl headers and library.
#
#  LINAL_INCLUDE_DIR - where to find Linal/linal.h, etc.
#  LINAL_LIBRARIES      - List of libraries.
#  LINAL_FOUND        - True if LinAl found.



# Look for the library.
#execute_process(COMMAND /home/dbv/3rdparty64-gcc43/LinAl/bin/linal-config --libs
#                OUTPUT_VARIABLE LINAL_LIBRARIES)

set(LINAL_LIBRARIES "/home/dbv/3rdparty64-gcc43/LinAl/lib/libLinAl.so;/home/dbv/3rdparty64-gcc43/LinAl/lib/libarpack++.a;/home/dbv/3rdparty64-gcc43/LinAl/lib/libsuperlu.a;/home/dbv/3rdparty64-gcc43/LinAl/lib/libarpack.a;/home/dbv/3rdparty64-gcc43/LinAl/lib/liblapack.a;/home/dbv/3rdparty64-gcc43/LinAl/lib/libblas.so")
IF(UNIX) #find gfortran
  # If the faster 'gold' linker is used, to avoid complaints about undefined symbol
  # '_gfortran_concat_string', '_gfortran_pow_i4_i4', ... , let's link against gfortran libraries.
  # These errors happen while linking against VTK static built with R support
  SET(CMAKE_FIND_LIBRARY_SUFFIXES_SAVED ${CMAKE_FIND_LIBRARY_SUFFIXES}) # Backup
  LIST(APPEND CMAKE_FIND_LIBRARY_SUFFIXES ".so.3")
  FIND_LIBRARY(GFortran_LIBRARY gfortran)
  SET(CMAKE_FIND_LIBRARY_SUFFIXES ${CMAKE_FIND_LIBRARY_SUFFIXES_SAVED}) # Restore
  LIST(APPEND LINAL_LIBRARIES ${GFortran_LIBRARY})
#  message(STATUS "GFortran_LIBRARY: ${GFortran_LIBRARY}")
ENDIF()
MARK_AS_ADVANCED(LINAL_LIBRARIES)

# Look for the header file.
#execute_process(COMMAND /home/dbv/3rdparty64-gcc43/LinAl/bin/linal-config --cxxflags
#                OUTPUT_VARIABLE LINAL_INCLUDE_DIR)
set(LINAL_INCLUDE_DIR "/home/dbv/3rdparty64-gcc43/LinAl/include/")
MARK_AS_ADVANCED(LINAL_INCLUDE_DIR)


# handle the QUIETLY and REQUIRED arguments and set LINAL_FOUND to TRUE if 
# all listed variables are TRUE
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(LINAL DEFAULT_MSG LINAL_LIBRARIES LINAL_INCLUDE_DIR)

#IF(MATIO_FOUND)
#  SET(MATIO_LIBRARIES ${MATIO_LIBRARY} ${HDF5_LIBRARIES})
#  SET(MATIO_INCLUDE_DIRS ${MATIO_INCLUDE_DIR} ${HDF5_INCLUDE_DIR})
#ELSE(MATIO_FOUND)
  #SET(MATIO_LIBRARIES)
  #SET(MATIO_INCLUDE_DIRS)
#ENDIF(MATIO_FOUND)