#
# Makefile for Linux theread lib
#
# 

include $(TOPDIR)/config.mk

LIBS := $(addprefix $(obj),$(sort $(LIBS-y)))
LIBS_CLEAN := $(patsubst %.o,%.clean,$(LIBS))


$(LIBS):	
		$(MAKE) -C $(dir $(subst $(obj),,$@))
		
$(LIBS_CLEAN):
	@echo $@
	$(MAKE) -C $(dir $(subst $(obj),,$@)) clean
	
libs_clean: $(LIBS_CLEAN) 
	
	
PHONY := $(LIBS) $(LIBS_CLEAN)  clean
.PHONY: $(PHONY)
