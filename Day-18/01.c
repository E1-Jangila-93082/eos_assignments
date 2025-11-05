#include<stdio.h>
#include<fcntl.h>
#include<sys/mman.h>
#include<sys/stat.h>
#include<unistd.h>
#include<string.h>

int main(int argc, char *argv[]){
    printf("File Copy using Memory Mapping\n");
    int src_fd,des_fd;
    struct stat sb;
    char *p1,*p2;
    if(argc != 3){
        printf("Usage: %s <source_file> <destination_file>\n", argv[0]);
        return -1;
    }
    printf("Starting file copy from %s to %s\n", argv[1], argv[2]);
    src_fd = open(argv[1], O_RDONLY);
    des_fd = open(argv[2], O_RDWR | O_CREAT | O_TRUNC,0644);
    if(des_fd == -1 || src_fd == -1){
        perror("File open error");
        return -1;
    }
    printf("Files opened successfully.\n");
    fstat(src_fd, &sb);
    ftruncate(des_fd,sb.st_size);
    p1 = (char *)mmap(NULL,sb.st_size,PROT_READ,MAP_PRIVATE,src_fd,0);
    p2 = (char *)mmap(NULL,sb.st_size,PROT_WRITE,MAP_SHARED,des_fd,0);
    memcpy(p2,p1,sb.st_size);
    munmap(p1,sb.st_size);
    munmap(p2,sb.st_size);
    close(des_fd);      
    close(src_fd);     
    printf("File copied successfully.\n"); 
    return 0;
}