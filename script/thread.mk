#
# Makefile for thread test 
#
# 

LIBS-y += main/thread_main.o
LIBS-y += thread/libthread.o

include $(TOPDIR)/script/base.mk
thread_test:$(LIBS)
	$(CC) -Wl,--start-group  $(LIBS) -Wl,--end-group $(LDLIB) -o $(obj)thread_test
clean: libs_clean
	rm -f $(obj)thread_test
