#
# 根据c文件生成对应的依赖文件
#
# 
   
$(obj)%.d: %.c
	@echo "create depend"
	@echo $*
	$(CC) -M $(CCFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,$(obj)\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm $@.$$$$    
	

