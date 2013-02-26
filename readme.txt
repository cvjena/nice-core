notes on porting NICE to WIN using CMAKE:
-------
fixing all these includes of template definitons:
//#ifdef __GNUC__
#include "core/vector/RowMatrixT.tcc"
//#endif
tcc are not cpps, they need to be included into the header file otherwise template usage will result in linking errors
See, Inclusion model of Template classes: http://stackoverflow.com/questions/3705740/c-lnk2019-error-unresolved-external-symbol-template-classs-constructor-and


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


-----------------------------------------------------------------------
macro add_all_subdirs()

set(_all_headers)
set(_all_sources)
set(_all_linkings)

#ge
foreach dir in subdirlist
{
  add_directories( dir )
  #add header, sources, linkings from subdir to _all_* variables

}  



endmacro

set(NICE_CURR_DIR "${CMAKE_CURRENT_SOURCE_DIR}")


#### geile funktionen der OpenCV:
---aus OpenCVUtils.cmake:
macro(ocv_convert_to_full_paths VAR) # convert list of paths to full paths
macro(ocv_get_real_path VAR PATHSTR) # get absolute path with symlinks resolved
macro(ocv_list_add_suffix LST SUFFIX) # add suffix to each item in the list
macro(ocv_list_add_prefix LST PREFIX) # add prefix to each item in the list
macro(ocv_list_unique __lst)# stable & safe duplicates removal macro



OpenCVModule.cmake
ocv_glob_modules(pathcurrdir) -->in modules
  in jedem untermodel, eg core
  ocv_add_module(modname)
    sets variable "the_module" => set(the_module opencv_${name})
    extra abhängikeitens über zweites argument in der funktion, eg. ocv_add_module(core ${ZLIB_Lbla})
  ocv_module_include_directories() ( auch mit zusatzincludes dann übergeben ${ZLib_include_Dir})
  ocv_glob_module_sources() holt cpps und hpp h aus unterordnern -- sources bilden
  ocv_create_module (binary build the module ->add_library,  set_target etc
  

#######
defs to care about
NICE_USELIB_CUDACHOLESKY
NICE_USELIB_IPP
NICE_USELIB_OPENMP
#ifdef NICE_USELIB_MATIO
NICE_USELIB_PNG
NICE_USELIB_JPG
NICE_USELIB_LIBMAGICK

#eigene definiton zum builden der sub-test-ordners
NICE_BUILD_TESTS	
NICE_BUILD_PROGS

/wd"4244" /wd"4100" /wd"4127" /wd"4091" 
