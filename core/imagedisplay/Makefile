#TARGETS_FROM:=$(notdir $(patsubst %/,%,$(shell pwd)))/$(TARGETS_FROM)
#$(info recursivly going up: $(TARGETS_FROM) ($(shell pwd)))

all:

%:
	$(MAKE) TARGETS_FROM=$(notdir $(patsubst %/,%,$(shell pwd)))/$(TARGETS_FROM) -C .. $@

