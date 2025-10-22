#include<stdio.h>
#include<unistd.h>
#include<sys/sem.h>
#include<sys/ipc.h>
#include<sys/wait.h>
#include<stdlib.h>

#define SEM_KEY 0x1234
union semun {
       int              val;    /* Value for SETVAL */
       struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
       unsigned short  *array;  /* Array for GETALL, SETALL */
       struct seminfo  *__buf;  /* Buffer for IPC_INFO */
};

int main(){
	union semun su;
	struct sembuf ops[1];
	int semid = semget(SEM_KEY,1,IPC_CREAT|0600);
	if(semid==-1){
		perror("-Semaphore creation failed\n");
		exit(-1);
	}
	su.val = 0;
	semctl(semid,0,SETVAL,su);
	int pid = fork();
	if(pid==0){	 // child
		ops[0].sem_num = 0;
		ops[0].sem_op = -1;
		ops[0].sem_flg = 0;
		int ret = semop(semid,ops,1);
		if(ret!=0){
			perror("Operation infotech failed\n");
			exit(-1);
		}
		char str2[] = "INFOTECH\n"; 
		for(int i=0; i!='\n'; i++){
			putchar(str2[i]);
			fflush(stdout);
			sleep(1);
		}
	}
	else{	// parent
		char str1[] = "SUNBEAM\n"; 
		for(int i=0; i!='\n'; i++){
			putchar(str1[i]);
			fflush(stdout);
			sleep(1);
		}
		ops[0].sem_num = 0;
		ops[0].sem_op = 1;
		ops[0].sem_flg = 0;
		int ret = semop(semid,ops,1);
		if(ret!=0){
			perror("Operation sunbeam failed\n");
			exit(-1);
		}
	}
//	printf("\n");	
	int s;
	wait(&s);
	semctl(semid,0,IPC_RMID);
return 0;}
