#
# Makefile for list test 
#
# 
LIBS-y += list/liblist.o
LIBS-y += main/list_main.o

include $(TOPDIR)/script/base.mk
list_test:$(LIBS)
	$(CC) -Wl,--start-group  $(LIBS) -Wl,--end-group $(LDLIB) -o $(obj)list_test
clean: libs_clean
	rm -f $(obj)list_test
