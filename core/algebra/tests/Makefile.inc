# BINARY-DIRECTORY-MAKEFILE
# conventions:
# - there are no subdirectories, they are ignored!
# - all ".C", ".cpp" and ".c" files in the current directory are considered
#   independent binaries, and linked as such.
# - the binaries depend on the library of the parent directory
# - the binary names are created with $(BINNAME), i.e. it will be more or less
#   the name of the .o file
# - all binaries will be added to the default build list ALL_BINARIES

# --------------------------------
# - remember the last subdirectory
#
# set the variable $(SUBDIR) correctly to the current subdirectory. this
# variable can be used throughout the current makefile.inc. The many 
# SUBDIR_before, _add, and everything are only required so that we can recover
# the previous content of SUBDIR before exitting the makefile.inc

SUBDIR_add:=$(dir $(word $(words $(MAKEFILE_LIST)),$(MAKEFILE_LIST)))
SUBDIR_before:=$(SUBDIR)
SUBDIR:=$(strip $(SUBDIR_add))
SUBDIR_before_$(SUBDIR):=$(SUBDIR_before)

# ------------------------
# - include subdirectories
#
# note the variables $(SUBDIRS_OF_$(SUBDIR)) are required later on to recover
# the dependencies automatically. if you handle dependencies on your own, you
# can also dump the $(SUBDIRS_OF_$(SUBDIR)) variable, and include the
# makefile.inc of the subdirectories on your own...

#SUBDIRS_OF_$(SUBDIR):=$(patsubst %/Makefile.inc,%,$(wildcard $(SUBDIR)*/Makefile.inc))
#include $(SUBDIRS_OF_$(SUBDIR):%=%/Makefile.inc)

# ----------------------------
# - include local dependencies
#
# include the libdepend.inc file, which gives additional dependencies for the
# libraries and binaries. additionally, an automatic dependency from the library
# of the parent directory is added (commented out in the code below).

-include $(SUBDIR)libdepend.inc

PARENTDIR:=$(patsubst %/,%,$(dir $(patsubst %/,%,$(SUBDIR))))
$(call PKG_DEPEND_INT,$(PARENTDIR))
$(call PKG_DEPEND_EXT,CPPUNIT)

# ---------------------------
# - objects in this directory
#
# the use of the variable $(OBJS) is not mandatory. it is mandatory however
# to update $(ALL_OBJS) in a way that it contains the path and name of
# all objects. otherwise we can not include the appropriate .d files.

OBJS:=$(patsubst %.cpp,$(OBJDIR)%.o,$(notdir $(wildcard $(SUBDIR)*.cpp))) \
      $(patsubst %.C,$(OBJDIR)%.o,$(notdir $(wildcard $(SUBDIR)*.C))) \
      $(shell grep -ls Q_OBJECT $(SUBDIR)*.h | sed -e's@^@/@;s@.*/@$(OBJDIR)moc_@;s@\.h$$@.o@') \
      $(patsubst %.c,$(OBJDIR)%.o,$(notdir $(wildcard $(SUBDIR)*.c)))
ALL_OBJS += $(OBJS)

# ----------------------------
# - binaries in this directory
#
# output of binaries in this directory. none of the variables has to be used.
# but everything you add to $(ALL_LIBRARIES) and $(ALL_BINARIES) will be
# compiled with `make all`. be sure again to add the files with full path.

CHECKS:=$(BINDIR)$(call LIBNAME,$(SUBDIR))
ALL_CHECKS+=$(CHECKS)

# ---------------------
# - binary dependencies
#
# there is no way of determining the binary dependencies automatically, so we
# follow conventions. each binary depends on the corresponding .o file and
# on the libraries specified by the INTLIBS/EXTLIBS. these dependencies can be
# specified manually or they are automatically stored in a .bd file.

$(foreach head,$(wildcard $(SUBDIR)*.h),$(eval $(shell grep -q Q_OBJECT $(head) && echo $(head) | sed -e's@^@/@;s@.*/\(.*\)\.h$$@$(BINDIR)\1:$(OBJDIR)moc_\1.o@')))
$(eval $(foreach c,$(CHECKS),$(c):$(BUILDDIR)$(CPPUNIT_MAIN_OBJ) $(OBJS) $(call PRINT_INTLIB_DEPS,$(c),.a)))

# -------------------
# - subdir management
#
# as the last step, always add this line to correctly recover the subdirectory
# of the makefile including this one!

SUBDIR:=$(SUBDIR_before_$(SUBDIR))

