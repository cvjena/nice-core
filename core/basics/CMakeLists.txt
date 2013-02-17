SET(core_basics_src Config.cpp BinStreamable.cpp  FastMath.cpp          gzstream.cpp      Observer.cpp            stringutils.cpp
bzstream.cpp       FileMgt.cpp           Log.cpp           ResourceStatistics.cpp  Timer.cpp
Config.cpp         FileName.cpp          numerictools.cpp  Streamable.cpp          tools.cpp
Exception.cpp      FrameRateCounter.cpp  Observable.cpp    StringTools.cpp
)

message(STATUS "vector sources: ${core_vectors_src}")
ADD_LIBRARY(core_basics ${NICE_BUILD_LIBS_STATIC_SHARED} ${core_basics_src} ${core_vectors_src})
#TARGET_LINK_LIBRARIES(core_basics core_vector)

#add_dependencies(core_basics core_vectors)

ADD_SUBDIRECTORY(progs)

INSTALL(TARGETS core_basics DESTINATION libs)
