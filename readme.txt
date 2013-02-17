notes on porting NICE to WIN using CMAKE:


------------------------------------------
porting core/basics/timer.h/cpp
highly unix dependend
better use 3rd party time functionality for now()
better use
boost::timer ??

---------------------------
stringtools highly os dependented
->recursive dir scan with "ls -r" syntax!!
use 3rd party lib like boost oder qt
use boost regex for regex syntax in stringtools::regex bla


################################
defs to care about
NICE_USELIB_CUDACHOLESKY
NICE_USELIB_IPP