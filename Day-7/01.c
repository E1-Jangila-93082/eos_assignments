#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
int main(){
	int stat;
	printf("*****START*****\n");
	for(int i=1; i<=5; i++){
		pid_t ret = fork();
	
		if(ret == 0)
		{
			printf("child%d : pid = %d ppid = %d\n",i,getpid(),getppid());
			sleep(5);
			return 0;
		}
	}
	sleep(1);
	printf("Timer start :\n");
	for(int t=5; t>=1;t--){
		printf("%d\n",t);
		sleep(1);
	}
	while(wait(&stat)>0);
	printf("*****END*****\n");
return 0;}
