#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<signal.h>
#include<semaphore.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<sys/wait.h>
#include<stdlib.h>

typedef struct shared_data{
	pthread_mutex_t mutex;
	sem_t buf_full;
	sem_t buf_empty;
	int buf[10];
	int wr;
	int rd;	
}data_t;

data_t *shm_ptr;
int shmid;

void cleanup(int sig){
	pthread_mutex_destroy(&shm_ptr->mutex);
	sem_destroy(&shm_ptr->buf_full);
	sem_destroy(&shm_ptr->buf_empty);
	shmdt(shm_ptr);
	shmctl(shmid,IPC_RMID,NULL);
	if(sig!=0)
		exit(0);
}

int main(){
	
	signal(SIGINT,cleanup);
	
	shmid = shmget(IPC_PRIVATE,sizeof(data_t),IPC_CREAT|0644);
	if(shmid==-1){
		perror("shmget() failed\n");
		exit(-1);
	}

	shm_ptr = (data_t*)shmat(shmid,NULL,0);

	pthread_mutexattr_t mutex_attr;
	pthread_mutexattr_init(&mutex_attr);
	pthread_mutexattr_setpshared(&mutex_attr,PTHREAD_PROCESS_SHARED);
	pthread_mutex_init(&shm_ptr->mutex,&mutex_attr);

	sem_init(&shm_ptr->buf_full,1,0);// initially full slots = 0, bcoz there's nothing to read 
	sem_init(&shm_ptr->buf_empty,1,10);// initially whole buf is empty
	int pid = fork();
	if(pid==0){	// child : producer
		printf("CHILD (Producer) started\n");
		sem_wait(&shm_ptr->buf_empty);
		pthread_mutex_lock(&shm_ptr->mutex);
		for(int i=0; i<20; i++){
		shm_ptr->buf[shm_ptr->wr]=i;
		shm_ptr->wr = (shm_ptr->wr+1)%10;
		printf("Produced : %d\n",i);
		sem_post(&shm_ptr->buf_full);	
		usleep(100000);
		}
		pthread_mutex_unlock(&shm_ptr->mutex);
		printf("CHILD (Producer) finished\n");
		shmdt(shm_ptr);
	}
	else{	// parent : consumer		
		printf("PARENT (Consumer) started\n");
		sem_wait(&shm_ptr->buf_full);
		pthread_mutex_lock(&shm_ptr->mutex);
		for(int i=0; i<20; i++){
		int item = shm_ptr->buf[shm_ptr->rd];
		shm_ptr->rd = (shm_ptr->rd+1)%10;
		printf("Consumed : %d\n",i);
		sem_post(&shm_ptr->buf_empty);
		usleep(300000);
		}
		pthread_mutex_unlock(&shm_ptr->mutex);
		printf("PARENT (Consumer) finished\n");
		wait(NULL);
		cleanup(0);
	}
return 0;}
