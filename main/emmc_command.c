/**
* this file is implementation the test case for emmc command string
* author: Alex.Li
**/



#include<stdio.h>
#include<stdlib.h>
#include<string.h>


#define BUFFLEN 128
#define CONFIG_EMMC_TEST_START_ADDR (0x80000000)
#define CONFIG_EMMC_TEST_LEN (512*1024*1024)
#define CONFIG_EMMC_TEST_END_ADDR (0xc0000000)


static int do_emmc_test(int argc, char * const argv[])
{

    char cmdstr[BUFFLEN];    
    int i =0;
    int j=0; 
    char tmpstr[64]={'\0'}; 
    unsigned long addr = 0x82000000;
    
    char *endp;
    unsigned long start_addr;
    unsigned long len;
    int loop =1;
    unsigned long bytes=0;
    unsigned long offset;
    
    
    
    /*default emmc test */
    if(argc ==1) {
        start_addr = CONFIG_EMMC_TEST_START_ADDR;
        len = CONFIG_EMMC_TEST_LEN;
    }else if(argc < 3){
        printf(" arg vaild\n");
        return -1;
    }
    
     
    
    if(argc >=4){
        start_addr = strtoul(argv[1],&endp,0);
        len = strtoul(argv[2],&endp,0); 
        loop = strtoul(argv[3],&endp,0);
        printf("start_addr: 0x%lx len:0x%lx loop:%d\n",start_addr,len,loop); 
    }
    /*valid start_addr and len*/
    if(start_addr >= CONFIG_EMMC_TEST_START_ADDR && 
    start_addr <CONFIG_EMMC_TEST_END_ADDR && 
    (start_addr +len) < CONFIG_EMMC_TEST_END_ADDR){
    
        /*do emmc test*/
        
        for(i = 0;i <loop; ++i){
            /*emmc erase*/       
            memset(cmdstr,0,sizeof(cmdstr)); 
            strcat(cmdstr,"mmc erase ");
            sprintf(tmpstr,"0x%lx ", start_addr);
            strcat(cmdstr,tmpstr);
            memset(tmpstr,0,sizeof(tmpstr));
            sprintf(tmpstr,"0x%lx ",len);
            strcat(cmdstr,tmpstr);                       
            printf("%s\n",cmdstr);
            
            
            
            bytes= len;
            while(bytes != 0){
                memset(cmdstr,0,sizeof(cmdstr));
                memset(tmpstr,0,sizeof(tmpstr)); 
                strcat(cmdstr,"mmc write 0x82000000 ");
                offset = len -bytes; 
                printf("offset:0x%lx\n",offset);                  
                sprintf(tmpstr,"0x%lx ",(start_addr + offset));
                
                strcat(cmdstr,tmpstr);
                if(bytes >= (512*1024)){ 
                    strcat(cmdstr," 0x80000");
                    bytes -= (512*1024);
                }else{
                    memset(tmpstr,0,sizeof(tmpstr));
                    sprintf(tmpstr," 0x%lx ",bytes);
                    strcat(cmdstr,tmpstr);
                    bytes =0; 
                }
                printf("bytes : 0x%lx\n",bytes);       
                printf("%s\n",cmdstr);             
            }   
        
        
            /*read len bytes data form emmc*/
            
            bytes= len;
            while(bytes != 0){
                memset(cmdstr,0,sizeof(cmdstr));
                memset(tmpstr,0,sizeof(tmpstr)); 
                strcat(cmdstr,"mmc read 0x82000000 ");
                offset = len -bytes;                   
                sprintf(tmpstr,"0x%lx ",(start_addr + offset));
                
                strcat(cmdstr,tmpstr);
                if(bytes >= (512*1024)){ 
                    strcat(cmdstr," 0x80000");
                    bytes -= (512*1024);
                    
                }else{
                    memset(tmpstr,0,sizeof(tmpstr));
                    sprintf(tmpstr," 0x%lx ",bytes);
                    strcat(cmdstr,tmpstr);
                    bytes =0; 
                }
                
                printf("%s\n",cmdstr);
            
            }   
            
        }
    }
    else{
        printf("EMMC test addr from 0x%0x to 0x%0x\n",CONFIG_EMMC_TEST_START_ADDR,CONFIG_EMMC_TEST_END_ADDR);
        return -1;
    }

ret:          
    return 0;
}
int main(int argc,char *const argv[])
{
    do_emmc_test(argc,argv);
    
    return 0;
}
