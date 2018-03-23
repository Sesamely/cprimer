/************************************************************************
****	> File Name:    	read_U.c
****	> Author:       	yiwen liu
****	> Mail:         	newiyuil@163.com
****	> Created Time: 	2018年03月18日 星期日 22时25分16秒
************************************************************************/

#include <stdio.h>  
#include <stdlib.h>  
#include <stdio.h>   
#include <errno.h>   
#include <unistd.h>   
#include <sys/types.h>   
#include <sys/stat.h>   
#include <fcntl.h>   
#include <string.h>
  
#include <linux/fs.h>   
#include <sys/ioctl.h>  
void extend_file_name(char *src, char *des);
unsigned find_entry_with_short_filename(const char *filename, const char *buf);
  
  
#define ROOT_DIR_FIRST_CLUSTER 0x2
#define SECTORS_PER_CLUSTER 0x10
#define SECTOR_SIZE 0x200 /*字节大小*/
#define CLUSTER_BEGIN_LBA 0x1000000
#define FAT_BEGIN_LAB 0x190000
#define MAX_ENTRY_NUMBER 0x100
#define BYTE_PER_ENTRY 0x20

char buf[SECTOR_SIZE * SECTORS_PER_CLUSTER] = {}; // 8K 缓冲区

int main(int argc, char** argv)   
{  
    if (argc != 2) {
        printf("Usage: elf filename\n");
        return 0;
    }
    int filename_size = strlen(argv[1]);
    if (filename_size > 11) {
        printf("I can only do with short name file!(less than 11 bytes)\n");
        return 0;
    }
    char filename[12];
    extend_file_name(argv[1], filename);

    char device[] = "/dev/sdc1";
    int fd = 0;
    fd = open(device, O_RDONLY);  
    if (fd == -1) {
        printf("No device %s !\n", device);
        return 0;
    }
    if(fd !=-1)  
    {     
  
        unsigned long read_cluster_lba = 0;
        read_cluster_lba = (ROOT_DIR_FIRST_CLUSTER - 2) * SECTORS_PER_CLUSTER * SECTOR_SIZE
            + CLUSTER_BEGIN_LBA;
        lseek(fd, read_cluster_lba, SEEK_SET);  
          
        read(fd, buf, SECTOR_SIZE * SECTORS_PER_CLUSTER);  

        unsigned entry_number = find_entry_with_short_filename(filename, buf);

        if (entry_number == MAX_ENTRY_NUMBER + 1) {
            printf("Sorry, No file named %s occurs in root dir!\n", filename);
            return 2;
        }
        unsigned short cluster_high = (unsigned short)buf[entry_number*BYTE_PER_ENTRY + 0x14];
        unsigned short cluster_low = (unsigned short)buf[entry_number*BYTE_PER_ENTRY + 0x1A];
        unsigned cluster_number = (cluster_high << 16) + cluster_low;

        while (cluster_number != 0x0FFFFFFF) {
            printf("%u -> ", cluster_number);
            unsigned read_offset = cluster_number * 4;
            lseek(fd, FAT_BEGIN_LAB+read_offset, SEEK_SET);
            read(fd, &cluster_number, 4);
        }
        printf("end\n");
  
    }  
  
    return 0;  
}  

unsigned find_entry_with_short_filename(const char *filename, const char *buf) {
    unsigned entry_number = 0;
    for (; entry_number<MAX_ENTRY_NUMBER; ++entry_number) {
        unsigned offset = entry_number * BYTE_PER_ENTRY;
        int match = 1;
        /*
         *for (int i=0; i<11; ++i) {
         *    printf("%c ", filename[i]);
         *}
         *printf("\n");
         */
        for (int i=0; i<11; ++i) {
            /*printf("%c ", buf[i+offset]);*/
            if (filename[i] != buf[i+offset]) {
                match = 0;
            }
        }
        /*printf("\n\n");*/
        if (match == 1) return entry_number;
    }
    return MAX_ENTRY_NUMBER + 1;
}
void extend_file_name(char *src, char *des)
{ 
    int des_size = strlen(src);
    des[11] = '\0';
    int add_zero_number = 11 - des_size;
    int loc = 0;
    int argv1_loc = 0;
    for (; loc<11&&argv1_loc<des_size;) {
        if (src[argv1_loc] != '.') {
            if (src[argv1_loc] >= 'a' && src[argv1_loc] <= 'z')
                des[loc] = src[argv1_loc] - 'a' + 'A';
            else {
                des[loc] = src[argv1_loc];
            }
        } else {
            int k=0;
            for (; k<add_zero_number; ++k) {
                des[loc] = 0x20;
                ++loc;
            }
            des[loc] = 0x20;
        }
        ++loc;
        ++argv1_loc;
    }
    while (loc<11) {
        des[loc] = 0x20;
        ++loc;
    }
}
