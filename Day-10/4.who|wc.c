#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/wait.h>

// using redirection

int main(){
	
	int pid1 = fork();
	if(pid1==0){ // child-1 : to run 'who'
		
		int open_fd = open("./o.txt",O_WRONLY|O_TRUNC|O_CREAT,0644);
		dup2(open_fd,1);
		close(open_fd);
		int exc = execl("/usr/bin/who","who",NULL);
		if(exc==-1){
			perror("C1 : execl() failed\n");
			_exit(-1);
		}
	}
	
	int pid2 = fork();	
	if(pid2==0){ // child-2 : to run 'wc'
		int fd = open("./o.txt",O_RDONLY);
	//	if(fd!=-1) printf("C2 : file opened\n");
		dup2(fd,0);
		close(fd);
		int exc = execl("/usr/bin/wc","wc",NULL);
		if(exc==-1){
			perror("C2 : execl() failed\n");
			_exit(-1);
		}	
	}
	int s;
	wait(&s);

return 0;}
