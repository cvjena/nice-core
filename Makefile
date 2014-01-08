# --------------------------------
# - initialization in top makefile
#
# here all variables used later on will be defined and initialized. also the
# default target (i.e. the one made with a simple `make`) is redirected to do
# something useful.

#incomplete collection of warnings...
CFLAGS_WARN=-Wall -Wextra -Wno-unused-parameter -Wno-strict-aliasing # -Wchar-subscripts -Wundef -Wshadow -Wcast-align -Wwrite-strings -Wsign-compare -Wunused -Wuninitialized -Wpointer-arith -Wredundant-decls -Wmissing-declarations -Wlong-long -Wfloat-equal

#some that are not really helpful
# -Wpadded -Wunreachable-code
#some more, only valid for C
# -Wbad-function-cast -Wnested-externs -Wmissing-prototypes -Wstrict-prototypes

ifdef OPTIMIZE
CFLAGS=-fPIC -O3
else
CFLAGS=-fPIC -O0
endif

ifdef DEBUG
CFLAGS+= -g $(CFLAGS_WARN) -DDEBUG
else
CFLAGS+= -g $(CFLAGS_WARN)
endif

CFLAGS+=-DUSE_64_BIT_PTR_CAST -DDISABLE_IPP_MAXMIN

ifdef NOVISUAL
CFLAGS+=-DNOVISUAL
endif

CFLAGS_CUDA=-Xcompiler "-fpic -O3 -pthread" 

PLATFORM:=$(shell uname -m)

AR=ar
CC=gcc
CXX=g++
CXXCUDA=nvcc
SYMLINK=ln -sf
DOXYGEN=doxygen
PKGCONFIG=pkg-config
SED=sed
MOC=echo "QT MOC is required. Please define the variable MOC in Makefile.config. "
CPPUNIT_MAIN=templates/cppUnitTestRunner.cpp

#normal mode
VERBOSE := @\#
VERBOSE2 :=
#abstract mode
#VERBOSE := @
#VERBOSE2 := @

USE_STATIC_LIBRARIES=1

ifdef USE_STATIC_LIBRARIES
    LINK_FILE_EXTENSION=a
else
    LINK_FILE_EXTENSION=so
endif


# various rules to create directory names
PROJECTDIR:=$(shell pwd)/
BUILDDIR:=BUILD_$(PLATFORM)$(NICE_BUILD)/
OBJDIR=$(BUILDDIR)$(SUBDIR)
LIBDIR=$(BUILDDIR)$(SUBDIR)
BINDIR=$(BUILDDIR)$(SUBDIR)
PKGDIR=$(BUILDDIR)$(SUBDIR)
LIBSYMLINKDIR=$(BUILDDIR)lib/
BINSYMLINKDIR=$(BUILDDIR)bin/
PKGSYMLINKDIR=$(BUILDDIR)pkgconfig/
ifeq "$(PKG_CONFIG_PATH)" ""
export PKG_CONFIG_PATH:=$(PROJECTDIR)/$(PKGSYMLINKDIR)
else
export PKG_CONFIG_PATH:=$(PROJECTDIR)/$(PKGSYMLINKDIR):$(PKG_CONFIG_PATH)
endif

# "global" variables
ALL_OBJS:=
ALL_LIBRARIES:=
ALL_BINARIES:=
ALL_CHECKS:=
SUBDIR:=

# various rules to create file names
LIBNAME=lib$(subst /,_,$(patsubst %/,%,$(1)))

# these are commands for the libdepend.inc files
FILE_DEPEND_EXT=$(eval EXTLIBS_$(OBJDIR)$(1)+=$(2))
FILE_DEPEND_INT=$(eval INTLIBS_$(OBJDIR)$(1)+=$(2))
PKG_DEPEND_EXT=$(eval EXTLIBS_$(OBJDIR)+=$(1))
PKG_DEPEND_EXT_ESSENTIAL=$(if $($(1)_CFLAGS)$($(1)_LDFLAGS),$(eval EXTLIBS_$(OBJDIR)+=$(1)),$(eval SKIP_BUILD_$(OBJDIR)=1))
PKG_DEPEND_INT=$(eval INTLIBS_$(OBJDIR)+=$(1))
PKG_DESCRIPTION=$(eval PKGDESC_$(OBJDIR)=$(1))
PKG_VERSION=$(eval PKGVERS_$(OBJDIR)=$(1))

# these are internal variables used within the Makefile.inc files and the
# rules below
PRINT_EXTLIB_LIST=$(EXTLIBS_$(1)) $(EXTLIBS_$(dir $1))
PRINT_EXTLIB_PKGCONFIG=$(foreach l,$(call PRINT_EXTLIB_LIST,$(1)),$($(l)_PKGCONFIG))

#PRINT_EXTLIB_CFLAGS=$(foreach l,$(call PRINT_EXTLIB_LIST,$(1)),$($(l)_CFLAGS))
PRINT_EXTLIB_CFLAGS=$(foreach l,$(call PRINT_EXTLIB_LIST,$(1)),$(if $($(l)_PKGCONFIG),`pkg-config $($(l)_PKGCONFIG) --cflags` )$($(l)_CFLAGS))
PRINT_EXTLIB_CFLAGS_NOPKG=$(foreach l,$(call PRINT_EXTLIB_LIST,$(1)),$($(l)_CFLAGS))

PRINT_EXTLIB_LDFLAGS=$(foreach l,$(call PRINT_EXTLIB_LIST,$(1)),$(if $($(l)_PKGCONFIG),`pkg-config $($(l)_PKGCONFIG) --libs` )$($(l)_LDFLAGS))
PRINT_EXTLIB_LDFLAGS_NOPKG=$(foreach l,$(call PRINT_EXTLIB_LIST,$(1)),$($(l)_LDFLAGS))


PRINT_INTLIB_DEPS=$(foreach l,$(INTLIBS_$(1)) $(INTLIBS_$(dir $(1))),$(BUILDDIR)$(patsubst %/,%,$(l))/$(call LIBNAME,$(l))$(2))

PRINT_INTLIB_PKGCONFIG=$(foreach l,$(INTLIBS_$(1)) $(INTLIBS_$(dir $1)),$(call LIBNAME,$(l)))
#PRINT_PKGCONFIG_SAFE=$(if $(strip $(1)),`$(PKGCONFIG) $(1) $(2)`)
PRINT_PKGCONFIG_SAFE=$(foreach l,$(1),`$(PKGCONFIG) $(l) $(2)`)

PRINT_INTLIB_CFLAGS=$(call PRINT_PKGCONFIG_SAFE,$(call PRINT_INTLIB_PKGCONFIG,$(1)),--cflags)
PRINT_INTLIB_LDFLAGS=$(call PRINT_PKGCONFIG_SAFE,$(call PRINT_INTLIB_PKGCONFIG,$(1)),--libs)

#PROCESS_DEPFILE=$(SED) -e's@^[^ ].*:@&$(call PRINT_INTLIB_PCS,$@)@'

.PHONY:all alldep alllib allbin clean check doc

all:alldep alllib allbin

# -----------------------------
# - configuration for libraries
#
# This configuration is moved to a separate configuration file. There the
# necessary defines $($(x)_CFLAGS) and $($(x)_LDFLAGS) are set up. Within
# this Makefile, one can simply say a target needs library $(x), and includes
# as well as libraries will be found.
PKGCONFIG_3RDPARTY=$(if $(shell pkg-config $(2) --exists && echo "1"),\
    $(call CONFIGINFO,$(1),1)$(eval $(1)_PKGCOONFIG=$(2)) \
    $(eval $(1)_CFLAGS=-DUSELIB_$(1)) \
    $(call CONFIGINFO,$(1),0))

$(info $(shell if [ ! -f Makefile.config ];then echo "+++ creating default Makefile.config - please manually check the configuration"; cp templates/Makefile.config.template Makefile.config;fi))

include Makefile.config

# --------------------
# - cppunit test stuff

ALL_OBJS+=$(CPPUNIT_MAIN_OBJ)
CPPUNIT_MAIN_OBJ=$(CPPUNIT_MAIN:%.cpp=%.o)
$(call FILE_DEPEND_EXT,$(CPPUNIT_MAIN_OBJ),CPPUNIT)

# ------------------------
# - include subdirectories
#
# in fact a simple "include Makefile.inc" would suffice to reach the top level
# source directory, from where other directories can be included.

SUBDIRS:=./
include $(SUBDIRS:%=%/Makefile.inc)

# --------------------------------------
# - override the default list of targets

ifneq "$(TARGETS_FROM)" ""
ALL_OBJS:=$(filter $(BUILDDIR)$(TARGETS_FROM)%,$(ALL_OBJS))
ALL_LIBRARIES:=$(filter $(BUILDDIR)$(TARGETS_FROM)%,$(ALL_LIBRARIES))
ALL_BINARIES:=$(filter $(BUILDDIR)$(TARGETS_FROM)%,$(ALL_BINARIES))
ALL_CHECKS:=$(filter $(BUILDDIR)$(TARGETS_FROM)%,$(ALL_CHECKS))
endif

# -----------------------------
# - rules in top level makefile
#
# the rules are the heart of the makefile. all rules are defined implicitly
# which has many advantages. you should definitely know what you are doing
# if you add an implicit rule however.

allbin:$(ALL_BINARIES)
	

alllib:$(ALL_LIBRARIES)

alldep:allpkg $(ALL_OBJS:%.o=%.d)

allpkg:$(ALL_LIBRARIES:%.$(LINK_FILE_EXTENSION)=%.pc)

check:$(ALL_CHECKS)

clean:
	$(VERBOSE)echo "+++ removing all files"
	$(VERBOSE2)rm -f $(ALL_OBJS) $(ALL_OBJS:%.o=%.d)
	$(VERBOSE2)rm -f $(ALL_BINARIES) $(ALL_BINARIES:%=%.bd)
	$(VERBOSE2)rm -f $(ALL_LIBRARIES) $(ALL_CHECKS)
	$(VERBOSE2)find ./core/ -name moc*.cpp -delete

#TODO: does not remove moc_*.C (created with QT-moc from .h files)
#alternative solution is to just rm -rf BUILD

doc: Makefile.config
	$(VERBOSE)echo "+++ creating documentation"
	$(VERBOSE2)cp Doxyfile Doxyfile.tmp
	$(VERBOSE2)perl -e 'print "PREDEFINED =     "; while(<>){ if ( /(NICE_USELIB_\w+)/ ) { print "$$1 "; } }; print "\n"' Makefile.config >> Doxyfile.tmp
	$(VERBOSE2)$(DOXYGEN) Doxyfile.tmp
	$(VERBOSE2)rm Doxyfile.tmp

MKOUTPUTDIR=[ -d $(@D) ] || mkdir -p $(@D)
MKOUTPUTDIR2=[ -d $(dir $(1)) ] || mkdir -p $(dir $(1))

$(BUILDDIR)%.d:%.c $(ALL_LIBRARIES:%.$(LINK_FILE_EXTENSION)=%.pc)
	@$(MKOUTPUTDIR)
	$(VERBOSE)echo "+++ making dependencies $@"
	$(VERBOSE2)$(CC) -MT '$@ $(@:%.d=%.o)' -MM -I. $(call PRINT_INTLIB_CFLAGS,$@) $(call PRINT_EXTLIB_CFLAGS,$@) $< > $@

$(BUILDDIR)%.d:%.C $(ALL_LIBRARIES:%.$(LINK_FILE_EXTENSION)=%.pc)
	@$(MKOUTPUTDIR)
	$(VERBOSE)echo "+++ making dependencies $@"
	$(VERBOSE2)$(CC) -MT '$@ $(@:%.d=%.o)' -MM -I. $(call PRINT_INTLIB_CFLAGS,$@) $(call PRINT_EXTLIB_CFLAGS,$@) $< > $@

$(BUILDDIR)%.d:%.cpp $(ALL_LIBRARIES:%.$(LINK_FILE_EXTENSION)=%.pc)
	@$(MKOUTPUTDIR)
	$(VERBOSE)echo "+++ making dependencies $@"
	$(VERBOSE2)$(CXX) -MT '$@ $(@:%.d=%.o)' -MM -I. $(call PRINT_INTLIB_CFLAGS,$@) $(call PRINT_EXTLIB_CFLAGS,$@) $< > $@

$(BUILDDIR)%.d:%.cu $(ALL_LIBRARIES:%.$(LINK_FILE_EXTENSION)=%.pc)
	@$(MKOUTPUTDIR)
	$(VERBOSE)echo "+++ making dependencies $@"
	$(VERBOSE2)$(CXXCUDA) -M '$@ $(@:%.d=%.o)' -I. $(call PRINT_INTLIB_CFLAGS,$@) $(call PRINT_EXTLIB_CFLAGS,$@) $< > $@

$(BUILDDIR)%.bd:$(ALL_LIBRARIES:%.$(LINK_FILE_EXTENSION)=%.pc)
	@$(MKOUTPUTDIR)
	$(VERBOSE)echo "+++ making dependencies $@"
	$(VERBOSE2)echo '$@:$(patsubst $(BUILDDIR)%,%,$(dir $@))libdepend.inc' > $@
	$(VERBOSE2)echo '$(@:%.bd=%):$(@:%.bd=%.o) $(call PRINT_INTLIB_DEPS,$(@:%.bd=%),.$(LINK_FILE_EXTENSION))' >> $@

$(BUILDDIR)%.o:%.c
	@$(MKOUTPUTDIR)
	$(VERBOSE)echo "+++ compiling object $@"
	$(VERBOSE2)$(CC) -c $(CFLAGS) -I. $(call PRINT_INTLIB_CFLAGS,$@) $(call PRINT_EXTLIB_CFLAGS,$@) $< -o $@

$(BUILDDIR)%.o:%.C
	@$(MKOUTPUTDIR)
	$(VERBOSE)echo "+++ compiling object $@"
	$(VERBOSE2)$(CXX) -c $(CFLAGS) -I. $(call PRINT_INTLIB_CFLAGS,$@) $(call PRINT_EXTLIB_CFLAGS,$@) $< -o $@

$(BUILDDIR)%.o:%.cpp
	@$(MKOUTPUTDIR)
	$(VERBOSE)echo "+++ compiling object $@"
	$(VERBOSE2)$(CXX) -c $(CFLAGS) -I. $(call PRINT_INTLIB_CFLAGS,$@) $(call PRINT_EXTLIB_CFLAGS,$@) $< -o $@

$(BUILDDIR)%.o:%.cu
	@$(MKOUTPUTDIR)
	$(VERBOSE)echo "+++ compiling cuda object $@"
	$(VERBOSE2)$(CXXCUDA) -c $(CFLAGS_CUDA) -I. $(call PRINT_INTLIB_CFLAGS,$@) $(call PRINT_EXTLIB_CFLAGS,$@) $< -o $@

moc_%.cpp:%.h
	$(VERBOSE)echo "+++ creating moc $@"
	$(VERBOSE2)$(MOC) $< -o $@

$(BUILDDIR)%.a:
	@$(MKOUTPUTDIR)
	$(VERBOSE)echo "+++ linking library $@"
	$(VERBOSE2)test -n "$(filter %.o,$^)" && $(AR) -crs $@ $(filter %.o,$^); echo;
	$(VERBOSE2)test -f "$@" || (touch emptysource.cpp; gcc -c emptysource.cpp; $(AR) -crs $@ emptysource.o; rm emptysource.*); echo
	@touch $@
	@$(call MKOUTPUTDIR2,$(LIBSYMLINKDIR))
	$(VERBOSE2)cd $(LIBSYMLINKDIR);$(SYMLINK) ../$(@:$(BUILDDIR)%=%) $(@F)

$(BUILDDIR)%.so:$(BUILDDIR)%.a
	@$(MKOUTPUTDIR)
	$(VERBOSE)echo "+++ linking library $@"
	$(VERBOSE2)$(CXX) -shared -o $@ -Wl,-whole-archive $< -Wl,-no-whole-archive
	@$(call MKOUTPUTDIR2,$(LIBSYMLINKDIR))
	$(VERBOSE2)cd $(LIBSYMLINKDIR);$(SYMLINK) ../$(@:$(BUILDDIR)%=%) $(@F)

$(ALL_BINARIES):
	@$(MKOUTPUTDIR)
	$(VERBOSE)echo "+++ linking binary $@"
	$(VERBOSE2)$(CXX) -o $@ $(filter %.o,$^) $(call PRINT_INTLIB_LDFLAGS,$@) $(LDFLAGS) $(call PRINT_EXTLIB_LDFLAGS,$@)
	@$(call MKOUTPUTDIR2,$(BINSYMLINKDIR))
	$(VERBOSE2)cd $(BINSYMLINKDIR);$(SYMLINK) ../$(@:$(BUILDDIR)%=%) $(@F)

$(ALL_CHECKS):
	@$(MKOUTPUTDIR)
	$(VERBOSE)echo "+++ running test case $@"
	$(VERBOSE2)$(CXX) -o $@ $(filter %.o,$^) $(call PRINT_INTLIB_LDFLAGS,$@) $(LDFLAGS) $(call PRINT_EXTLIB_LDFLAGS,$@)
	$(VERBOSE2)cd $(patsubst $(BUILDDIR)%,%,$(dir $@)); $(PROJECTDIR)$@; mv $(PROJECTDIR)$@ $(PROJECTDIR)$@.bak

$(BUILDDIR)%.pc:
	@$(MKOUTPUTDIR)
	$(VERBOSE)echo "+++ creating package $@"
	$(VERBOSE2)echo "Name: $(notdir $@)" > $@
	$(VERBOSE2)echo "Description: $(if $(PKGDESC_$(dir $@)),$(PKGDESC_$(dir $@)),Just a sub-library)" >> $@
	$(VERBOSE2)echo "Version: $(if $(PKGVERS_$(dir $@)),$(PKGVERS_$(dir $@)),1.0.0)" >> $@
	$(VERBOSE2)echo "Requires: $(call PRINT_INTLIB_PKGCONFIG,$@) $(call PRINT_EXTLIB_PKGCONFIG,$@)" >> $@
	$(VERBOSE2)echo "Libs: -L$(PROJECTDIR)$(dir $@) -l$(patsubst lib%.pc,%,$(notdir $@)) $(call PRINT_EXTLIB_LDFLAGS_NOPKG,$@)" >> $@
	$(VERBOSE2)echo "Cflags: -I$(PROJECTDIR) $(call PRINT_EXTLIB_CFLAGS_NOPKG,$@)" >> $@
	@$(call MKOUTPUTDIR2,$(PKGSYMLINKDIR))
	$(VERBOSE2)cd $(PKGSYMLINKDIR);$(SYMLINK) ../$(@:$(BUILDDIR)%=%) $(@F)

# ----------------------
# - include dependencies
#
# finally, if we know how to make them, we can include all depedency .d files.
# personally i do not like this line, because you always always always have
# to make the dependencies then, even if you `make non_existing_target`.
# furthermore i do not like the idea of having one .d file for each source
# file, but it seems to be the only way...

-include $(ALL_OBJS:%.o=%.d)

