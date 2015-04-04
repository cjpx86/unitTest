#
# Makefile for print test 
#
# 
LIBS-y += print/libprint.o
LIBS-y += main/print_main.o

include $(TOPDIR)/script/base.mk
print_test:$(LIBS)
	$(CC) -Wl,--start-group  $(LIBS) -Wl,--end-group $(LDLIB) -o $(obj)print_test
clean: libs_clean
	rm -f $(obj)print_test
