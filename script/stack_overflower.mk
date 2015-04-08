#
# Makefile for stack overflower test case 
#
# 

LIBS-y += main/stack_overflower.o
LIBS-y += thread/libthread.o

include $(TOPDIR)/script/base.mk
stack_overflower:$(LIBS)
	$(CC) -Wl,--start-group  $(LIBS) -Wl,--end-group $(LDLIB) -o $(obj)stack_overflower
clean: libs_clean
	rm -f $(obj)stack_overflower