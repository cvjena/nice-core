# LIBRARY-DIRECTORY-MAKEFILE
# conventions:
# - all subdirectories containing a "Makefile.inc" are considered sublibraries
#   exception: "progs/" and "tests/" subdirectories!
# - all ".C", ".cpp" and ".c" files in the current directory are linked to a
#   library
# - the library depends on all sublibraries 
# - the library name is created with $(LIBNAME), i.e. it will be somehow
#   related to the directory name and with the extension .a
#   (e.g. lib1/sublib -> lib1_sublib.a)
# - the library will be added to the default build list ALL_LIBRARIES

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
ifeq "$(SUBDIR)" "./"
SUBDIR:=
endif

# ------------------------
# - include subdirectories
#
# note the variables $(SUBDIRS_OF_$(SUBDIR)) are required later on to recover
# the dependencies automatically. if you handle dependencies on your own, you
# can also dump the $(SUBDIRS_OF_$(SUBDIR)) variable, and include the
# makefile.inc of the subdirectories on your own...

SUBDIRS_OF_$(SUBDIR):=$(patsubst %/Makefile.inc,%,$(wildcard $(SUBDIR)*/Makefile.inc))
include $(SUBDIRS_OF_$(SUBDIR):%=%/Makefile.inc)

# ----------------------------
# - include local dependencies
#
# you can specify libraries needed by the individual objects or by the whole
# directory. the object specific additional libraries are only considered
# when compiling the specific object files
# TODO: update documentation...

-include $(SUBDIR)libdepend.inc

$(foreach d,$(filter-out %progs %tests,$(SUBDIRS_OF_$(SUBDIR))),$(eval $(call PKG_DEPEND_INT,$(d))))

# ---------------------------
# - objects in this directory
#
# the use of the variable $(OBJS) is not mandatory. it is mandatory however
# to update $(ALL_OBJS) in a way that it contains the path and name of
# all objects. otherwise we can not include the appropriate .d files.

OBJS:=$(patsubst %.cpp,$(OBJDIR)%.o,$(notdir $(wildcard $(SUBDIR)*.cpp))) \
      $(patsubst %.C,$(OBJDIR)%.o,$(notdir $(wildcard $(SUBDIR)*.C))) \
      $(patsubst %.c,$(OBJDIR)%.o,$(notdir $(wildcard $(SUBDIR)*.c)))
ALL_OBJS += $(OBJS)

# ----------------------------
# - binaries in this directory
#
# output of binaries in this directory. none of the variables has to be used.
# but everything you add to $(ALL_LIBRARIES) and $(ALL_BINARIES) will be
# compiled with `make all`. be sure again to add the files with full path.

LIBRARY_BASENAME:=$(call LIBNAME,$(SUBDIR))
ifneq "$(SUBDIR)" ""
ALL_LIBRARIES+=$(LIBDIR)$(LIBRARY_BASENAME).$(LINK_FILE_EXTENSION)
endif

# ---------------------
# - binary dependencies
#
# there is no way of determining the binary dependencies automatically, so we
# follow conventions. the current library depends on all sublibraries.
# all other dependencies have to be added manually by specifying, that the
# current .pc file depends on some other .pc file. binaries depending on
# libraries should exclusivelly use the .pc files as well.

$(LIBDIR)$(LIBRARY_BASENAME).a:$(OBJS) \
	$(call PRINT_INTLIB_DEPS,$(PKGDIR)$(LIBRARY_BASENAME).a,.$(LINK_FILE_EXTENSION))
$(PKGDIR)$(LIBRARY_BASENAME).pc: \
	$(call PRINT_INTLIB_DEPS,$(PKGDIR)$(LIBRARY_BASENAME).pc,.pc)

# -------------------
# - subdir management
#
# as the last step, always add this line to correctly recover the subdirectory
# of the makefile including this one!

SUBDIR:=$(SUBDIR_before_$(SUBDIR))

