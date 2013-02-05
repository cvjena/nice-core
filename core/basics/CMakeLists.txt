SET(core_basics_src Config.cpp BinStreamable.cpp  FastMath.cpp          gzstream.cpp      Observer.cpp            stringutils.cpp
bzstream.cpp       FileMgt.cpp           Log.cpp           ResourceStatistics.cpp  Timer.cpp
Config.cpp         FileName.cpp          numerictools.cpp  Streamable.cpp          tools.cpp
Exception.cpp      FrameRateCounter.cpp  Observable.cpp    StringTools.cpp
)

ADD_LIBRARY(core_basics SHARED ${core_basics_src})

INSTALL(TARGETS core_basics DESTINATION libs)
