#
# Makefile for print test 
#
# 
LIBS-y += main/emmc_command.o

include $(TOPDIR)/script/base.mk
emmc_command:$(LIBS)
	$(CC) -Wl,--start-group  $(LIBS) -Wl,--end-group $(LDLIB) -o $(obj)emmc_command
clean: libs_clean
	rm -f $(obj)emmc_command