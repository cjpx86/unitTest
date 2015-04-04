#
# Makefile for print
#
# 

include $(TOPDIR)/config.mk

LIB	:= $(obj)libprint.o

COBJS-y += print_hello.o
COBJS-y += print_love.o
COBJS-y += print_birthday.o

COBJS	:= $(COBJS-y)
SRCS	:= $(COBJS:.o=.c)

OBJS	:= $(addprefix $(obj),$(COBJS))
DEPENDS := $(OBJS:.o=.d)

all:	$(LIB) 



$(LIB): $(OBJS)
	@echo $(OBJS)
	@echo $(SRCS)
	@echo $@
	$(call cmd_link_o_target, $(OBJS))

#利用make的静态模式简化
#将所有的.o文件替换成.c文件

#$(OBJS):%.o:%.c 
#	$(CC) $(CCFLAGS) $(LDLIB) -c $< -o $@
$(obj)%.o:	%.c
	$(CC)  $(CCFLAGS) -o $@ $< -c

PHONY = all
PHONY += FORCE clean
FORCE:

##上面的头文件改动，没有被makefie检测到，主要是
##由于通过这种方式我们丢失了c文件对头文件的依赖
##因此我们必须将相关的依赖文件加上  



include $(SRCTREE)/rules.mk     
sinclude $(DEPENDS)


  
clean:
	rm -rf $(OBJS)
	rm -f $(obj)*.d
	rm -f $(LIB)
	
.PHONY: $(PHONY)
