#
# Makefile for Linux theread lib
#
# 
#ǰ������������Ȼ�Ѿ�ʵ�����Զ�����
#�Զ�����ļ����£��������������룬����
#ǰ���������ļ�Ŀ¼��һ����̫�ʺϴ�����Ŀ
#��Makefile��Ҫ�󣬶���һ��Ŀ¼�ṹһ���ӣ�
#���кܴ��ظ�����


#############################
##����Makefile����һЩ�������Ա㽫��ʹ��
##
####################################

###################
#������ʱ�ļ����Ŀ¼�����û�ж���
#�ñ��������Ŀ¼Ϊ��ǰĿ¼
ifdef O
ifeq ("$(origin O)", "command line")
BUILD_DIR := $(O)
endif
endif

ifneq ($(BUILD_DIR),)
saved-output := $(BUILD_DIR)

# Attempt to create a output directory.
$(shell [ -d ${BUILD_DIR} ] || mkdir -p ${BUILD_DIR})

# Verify if it was successful.
BUILD_DIR := $(shell cd $(BUILD_DIR) && /bin/pwd)
$(if $(BUILD_DIR),,$(error output directory "$(saved-output)" does not exist))
endif # ifneq ($(BUILD_DIR),)

#####�˴���������obj�ļ������Ŀ¼
OBJTREE		:= $(if $(BUILD_DIR),$(BUILD_DIR),$(CURDIR))
SRCTREE		:= $(CURDIR)
TOPDIR		:= $(SRCTREE)
LNDIR		  := $(OBJTREE)

#�������������Ա���makefile��������
export	TOPDIR SRCTREE OBJTREE 


all: print_test thread_test list_test stack_overflower emmc_command
	@echo compile all unit test application
	#$(MAKE) -f $(TOPDIR)/script/print.mk print_test
	
print_test:
	$(MAKE) -f $(TOPDIR)/script/print.mk print_test

thread_test:
	$(MAKE) -f $(TOPDIR)/script/thread.mk thread_test

list_test:
	$(MAKE) -f $(TOPDIR)/script/list.mk list_test

stack_overflower:
	$(MAKE) -f $(TOPDIR)/script/stack_overflower.mk stack_overflower
emmc_command:
	$(MAKE) -f $(TOPDIR)/script/emmc_command.mk emmc_command
print_test_clean:
	@echo clean print_test temp files
	$(MAKE) -f $(TOPDIR)/script/print.mk clean

stack_overflower_clean:
	@echo clean  stack_overflower temp files
	$(MAKE) -f $(TOPDIR)/script/stack_overflower.mk clean

thread_test_clean:
	@echo clean thread_test temp files
	$(MAKE) -f $(TOPDIR)/script/thread.mk clean

list_test_clean:
	@echo clean list_test temp files
	$(MAKE) -f $(TOPDIR)/script/list.mk clean

emmc_command_clean:
	$(MAKE) -f $(TOPDIR)/script/emmc_command.mk clean

clean: print_test_clean thread_test_clean list_test_clean stack_overflower_clean emmc_command_clean
	@echo clean the temp files
	#$(MAKE) -f $(TOPDIR)/script/print.mk clean

help:	
	@echo ""	
	@echo " unit-tests useful Makefile targets:"	
	@echo ""	
	@echo "    all       :  build all tests (default)"		
	@echo "    clean     :  remove object files"	
	@echo "    help      :  print this message"
	
PHONY = all clean
PHONY += print_test print_test_clean
PHONY += thread_test thread_test_clean
PHONY += list_test list_test_clean
PHONY += stack_overflower stack_overflower_clean
PHONY += emmc_command emmc_command_clean
  
.PHONY: $(PHONY)
