#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

// without 'for' loop

int main(){
	
	printf("\n***START***\n");
	pid_t A = fork();
	 	if(A==0){
		printf("Child-A: pid=%d ppid=%d\n",getpid(),getppid());
		pid_t B = fork();
		sleep(1);
			if(B==0){
			printf("Child-B: pid=%d ppid=%d\n",getpid(),getppid());
			pid_t C = fork();
			sleep(1);
				if(C==0){
				printf("Child-C: pid=%d ppid=%d\n",getpid(),getppid());
				pid_t D = fork();
				sleep(1);
					if(D==0){
					printf("Child-D: pid=%d ppid=%d\n",getpid(),getppid());
					sleep(5);
					return 0;
					}
				wait(NULL);
				return 0;
				}
			wait(NULL);
			return 0;
			}
		wait(NULL);
		return 0;
		}
	while(wait(NULL)>0);
	printf("***END***\n");
return 0;}
