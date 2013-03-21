notes on porting NICE to WIN using CMAKE:
-------

1. Never use GLOB_RECURSE. It's evil. E.g. if you add or remove source files, CMake has no way of knowing that it should be re-run. Just list all the files in your CMakeLists.txt (or, if you think the list is excessively long, create a file called e.g. files.cmake, put the list in there and INCLUDE it in the CMakeLists.txt file.
2. Never do in-source builds. CMake creates many, many files, and you don't want to delete them all individually for a clean build. And there's no way to implement a safe "make clean" (e.g. your build system might be running a custom utility which generates files CMake knows nothing about).

%%%% todos
- libmagic++ scheint sehr aufwendig in der benutzung unter Windows: How to build it with vs, anleitung:http://www.graphicsmagick.org/INSTALL-windows.html#windows-xp-vista-7-visual-c-6-0-through-9-0-compilation
unter windows doch einfacher: http://www.imagemagick.org/script/binary-releases.php#windows (sind nur die binaries, keine includes und libs)
http://www.imagemagick.org/Magick++/ sources runterladen (getan. TODO: entpacken c/libraries/ImageMagick-6.8.3-6-windows.zip)
braucht man überhaupt libmagick? warum nicht lieber opencv zum bilderlesen benutzen: momentan ist das lesen und schreiben eh mit throw exception not implemented verbunden:
void ImageFile::readerMagick ( GrayColorImageCommonImplementationT<P> *image )
{
  fthrow ( ImageException, "Format not yet implemented (only available for standard images)." );
}
weil magick momentan der default imagereader ist: void ImageFile::reader(...), wenn keine libPNG und LibJpeg gegeben ist.



- make compilable without Qt
- make compileable without opengl

- regex lib nutzen von boost (->config.h)
- substitue FileMgt::DirectoryRecursive by platform independend code using boost::filesystem

- Implement ResouceStatistics for windows
- 
- braucht man GLUT noch ? Alt??? enable build without glut atleast!!

- remove all warnings for function shadowing
- remove all warning unreachable code
%%%%%
needed libraries windows:
freeglut (download from: http://freeglut.sourceforge.net/index.php#download)
adjust pathes GLUT_ROOT_PATH in root-CMakeLists.txt

%%%%%%

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

--------------- CPPUNIT verwenden ---------------------
1) installation
1-a) linux
  if not already in path then:
    download source from http://sourceforge.net/projects/cppunit/files/cppunit/1.12.1/cppunit-1.12.1.tar.gz/download
    unzip
    create build_<pcname> dir
    cd build_<pcname>
    ../configure - -prefix=<path>/build_<pcname>/install
    make 
    make install
    put <path>/build_<pcname>/install/include into system path variable, example in .bashrc:
    PATH=/home/ruehle/libs/cppunit-1.12.1/build_sigma15/install/include/:$PATH

1-b) Windows:
  download http://www.comp.nus.edu.sg/~cs3215/tools/cppunitAll.html
  build with visual studio
  put path to generated lib in path variable (pointing to the */include path)
2) enabling building cpp unit tests
  NICE_BUILD_TESTS   
  running tests: <build ordner>: cmake
  make
3) run the unit tests
im <build ordner>: cmake --output-on-failure
--------------------------------------------------------------

NICE_BUILD_PROGS

/wd"4244" /wd"4100" /wd"4127" /wd"4091" 

#adding custom build step:
	if(BUILD_CORE_TESTS_PERFORM_AS_POSTBUILD_STEP)
		add_custom_command(TARGET ${__testname}
                   POST_BUILD
                   COMMAND "$<TARGET_FILE:${__testname}>"
                   COMMENT "Unit Tests...")
	else()
###
installing boost:
