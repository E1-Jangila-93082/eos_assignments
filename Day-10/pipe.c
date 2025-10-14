#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>

int main(){

	int p1_arr[2],p2_arr[2];
	int p1 = pipe(p1_arr); 
	int p2 = pipe(p2_arr); // arr[0] : read end ; arr[1] : write end

	int pid = fork();

	if(pid==0){	// child process
		close(p1_arr[0]); // writer
		int arr[10];
		printf("C : Enter num1 :");
		scanf("%d",&arr[0]);
		printf("C : Enter num2 :");
		scanf("%d",&arr[1]);
		int wr = write(p1_arr[1],arr,sizeof(arr));
		if(wr==-1){
			perror("C : Writing values on pipe1 - failed\n");
		}
		else printf("C : Writing values on pipe1 - successful\n");	// upto this values are sent to first pipe
		close(p1_arr[1]);
		
		// now we have to read 'result' from second pipe
		close(p2_arr[1]); // reader (for pipe2)
		int rd = read(p2_arr[0],arr,sizeof(arr));
		if(rd==-1){
			perror("C : Result not recieved from pipe2\n");
			_exit(-1);
		}
		else{
			printf("C : Result received from pipe2\n");
			printf("C : Sum : %d\n",arr[0]);
		}
		close(p2_arr[0]);

	}	
	else{	// parent process
		close(p1_arr[1]); // reader
		int arr[10];
		int rd = read(p1_arr[0],arr,sizeof(arr));
		if(rd==-1){
			perror("P : Values not recieved from pipe1\n");
			_exit(-1);
		}
		else{
			printf("P : Values recieved from pipe1\n");
			arr[0] += arr[1];	// upto this values are recieved from 1st pipe, calculated and result is stored in arr[0]
			printf("P : Calc.....\n");
		}	
		close(p1_arr[0]);	
		// now we need to send result through 2nd pipe
	
		close(p2_arr[0]); // writer (for pipe 2)
		int wr = write(p2_arr[1],arr,sizeof(arr));
		if(wr==-1){
			perror("P : Writing result on pipe2 - failed\n");
			_exit(-1);
		}
		else printf("P : Writing result on pipe2 - successful\n");
		close(p2_arr[1]);

		int s;
		wait(&s);
	}

return 0;}
