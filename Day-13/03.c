#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>
#include<stdlib.h>

sem_t s;

void *sunbeam(void *param){
	char *ptr = (char *)param;
	
	for(int i=0; ptr[i]!= '\n'; i++){
		putchar(ptr[i]);
		fflush(stdout);
		usleep(200000);
	}
	printf("\n");
	sem_post(&s);
}
void *info(void *param){
	char *ptr = (char *)param;
	sem_wait(&s);
	for(int i=0; ptr[i]!= '\n'; i++){
		putchar(ptr[i]);
		fflush(stdout);
		usleep(200000);
	}
}

int main(){
	pthread_t t1,t2;

	sem_init(&s,0,0);
	
	char str1[] = {'S','U','N','B','E','A','M','\n'};
	char str2[] = {'I','N','F','O','T','E','C','H','\n'};
	
	int ret1 = pthread_create(&t1,NULL,sunbeam,&str1);
	if(ret1!=0){
		perror("Thread creation failed\n");
		exit(-1);
	}
	int ret2 = pthread_create(&t2,NULL,info,&str2);
	if(ret2!=0){
		perror("Thread creation failed\n");
		exit(-1);
	}

	pthread_join(t1,NULL);
	pthread_join(t2,NULL);

	printf("\n");
return 0;}




