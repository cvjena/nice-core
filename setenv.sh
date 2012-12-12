# This script sets some enviroment variables for the NICE framework,
# such as PATH and LD_LIBRARY_PATH
# usage: source setenv.sh [NICEDIR]

# DO NOT SUBMIT A CHANGED VERSION TO THIS FILE UNLESS YOU
# KNOW WHAT YOU ARE DOING !!

# current path
MYPATH=`pwd`
# list of possible nice directories
POSSIBLE_NICE_DIRECTORIES="$1 $MYPATH $NICEHOME $HOME/code/nice $HOME/dev/nice $HOME/workspace/nice $HOME/libs/nice/ $HOME/src/nice/"
for MYNICEDIR in $POSSIBLE_NICE_DIRECTORIES; do
	# check whether we have an absolute path
	echo checking $MYNICEDIR
	if [ `echo $MYNICEDIR | cut -c1` != "/" ]; then
		# this is not an absolute path
		continue
	fi
	# check whether this is a suitable NICE core directory
	if [ -d "$MYNICEDIR/core/" ]; then
		NICEHOME=$MYNICEDIR
		break
	fi
done
echo Configuring NICE framework in $NICEHOME

# Set the PKG_CONFIG_PATH to include the nice-core pc-files
export PKG_CONFIG_PATH=$PKG_CONFIG_PATH:/usr/lib64/pkgconfig/:/usr/lib/pkgconfig/:/usr/lib/pkgconfig/:/usr/local/lib/pkgconfig/:$NICEHOME/BUILD_`uname -m`$NICE_BUILD/pkgconfig/

# Determine the GCC version, we might need it ...
GCC_VERSION=`gcc --version | perl -e '$_=<>;/^gcc.+?([\d\.]+)/;print $1'`
GCC_VERSION_MAJOR=`echo $GCC_VERSION | perl -e '$_=<>;/^(\d+\.\d+)\.\d+/;print $1'`

# Use the slim-pkg-config program
# (1) set the link
ln -s $MYNICEDIR/slim-pkg-config/slim-pkg-config $MYNICEDIR/slim-pkg-config/pkg-config 2>/dev/null
# (2) modify the PATH variable, because we want to use slim-pkg-config instead of the standard (slow!) pkg-config
export PATH=$MYNICEDIR/slim-pkg-config/:$PATH
echo "Using slim-pkg-config instead of pkg-config: which pkg-config = `which pkg-config`"

PATH=$PATH:$NICEHOME/BUILD_`uname -m`$NICE_BUILD/bin
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$NICEHOME/BUILD_`uname -m`$NICE_BUILD/lib

echo "Configuring BUILDIR: $NICEHOME/BUILD_`uname -m`$NICE_BUILD"

LOCAL_SETENV="$NICEHOME/setenv_local.sh"
if [ -f "$LOCAL_SETENV" ]; then
	 echo "Using your local version: $LOCAL_SETENV"
	 source "$LOCAL_SETENV"
	 return
fi

if [ -e $HOME/DBVFAIL ]; then
  return
fi

if [ -d /home/dbv/ ]; then
	# The following commands are tuned for the enviroment
	# at the chair for computer vision, university of jena

	echo "Configuring to use /home/dbv/ ..."
	# check whether we have a 64bit machine 
	if test "`uname -m`" == "x86_64"
	then
		 # Do we really need this gcc stuff anymore?
		 #source /home/dbv/3rdparty64-gcc43/gcc/setenv.sh
		 source /home/dbv/3rdparty64-gcc43/ipp53/setenv.sh
		 source /home/dbv/3rdparty64-gcc43/FireCap/setenv.sh
		 #source /home/dbv/3rdparty64-gcc43/Coin3dQt4/setenv.sh
		 source /home/dbv/3rdparty64-gcc43/LinAl/setenv.sh
		 source /home/dbv/3rdparty64-gcc43/cppunit/setenv.sh
		 # source /home/dbv/3rdparty64-gcc43/qt4/setenv.sh
		 source /home/dbv/3rdparty64-gcc43/opencv/setenv.sh
		 source /home/dbv/3rdparty64/cudaSIFT/setenv.sh
		 source /home/dbv/3rdparty64/cuda/setenv_cuda.sh
		 # Do we really need this gcc stuff anymore?
		 PATH=$PATH:/home/dbv/3rdparty64-gcc43/bin
		 LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/dbv/3rdparty64-gcc43/libptu/lib:/home/dbv/3rdparty64-gcc43/Aria/lib
	else
		 #32 bit system 
		 #source /home/dbv/3rdparty32/gcc/setenv.sh
		 source /home/dbv/3rdparty32/ipp53/setenv.sh
		 source /home/dbv/3rdparty32/FireCap/setenv.sh
		 source /home/dbv/3rdparty32/Coin3d/setenv.sh
		 source /home/dbv/3rdparty32/LinAl/setenv.sh
		 #source /home/dbv/3rdparty64-gcc43/cppunit/setenv.sh
		 #source /home/dbv/3rdparty32/qt4/setenv.sh
		 source /home/dbv/3rdparty32-102/opencv/setenv.sh
		 PATH=$PATH:/home/dbv/3rdparty32/bin:$NICEHOME/BUILD_i686/bin
		 LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$NICEHOME/BUILD_i686/lib:/home/dbv/3rdparty32/qt4/lib:/home/dbv/3rdparty32/libptu/lib:/home/dbv/3rdparty32/Aria/lib
	fi
else	
	echo "The directory /home/dbv/ does not exist, therefore, I guess you have a local copy and take care of your env variables yourself."
    echo "Do not commit a local version of this script to the repository!"
fi

