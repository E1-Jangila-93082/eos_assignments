#include<stdio.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<sys/wait.h>


#define MSG_KEY 0x1234
	
int main(){
//	int n1,n2;
	struct msgp{
		long type;
		int data[10];
	};

	struct msgp m1;

	int msg_id = msgget(MSG_KEY,IPC_CREAT|0600); // msg queue created
	if(msg_id==-1){
		perror("msgget() failed\n");
		_exit(-1);
	}
	else printf("-Msg queue created\n");
	int pid = fork();
	if (pid==0){	// child process
			
		m1.type = 1;
		printf("C : Enter num1 :");
		scanf("%d",&m1.data[0]);		
		printf("C : Enter num2 :");
		scanf("%d",&m1.data[1]);
		
		int ret = msgsnd(msg_id,&m1,sizeof(m1.data),0);
		if(ret==-1){
			perror("C : Values send failed\n");
			_exit(-1);
		}
		else
			printf("C : Values sent successfully\n");
		int ret1 = msgrcv(msg_id,&m1,sizeof(m1.data),2,0);
		if(ret1==-1){
			perror("C : sum recieve unsuccessful\n");
			_exit(-1);
		}	
		else{ 
			printf("C : Sum received\n");
			printf("C : Sum : %d\n",m1.data[0]);
		}
	}
	else{ // parent process
		
		int rc = msgrcv(msg_id,&m1,sizeof(m1.data),1,0);
		if(rc==-1){
			perror("P : Values didn't recieved\n");
		}
		else printf("P : Values recieved\n");
		int a = m1.data[0];
		int b = m1.data[1];
		m1.data[0] = a+b;
		m1.type = 2;
		int ret = msgsnd(msg_id,&m1,sizeof(m1.data),0);
		if(ret==-1){
			perror("P : Sum send failed\n");
			_exit(-1);
		}
		else
			printf("P : Sum sent successfully\n");
		int s;
		wait(&s);
		msgctl(msg_id,IPC_RMID,NULL);
	}

return 0;}
