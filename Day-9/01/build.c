#include<stdio.h>
#include<stdlib.h>
#include"circle.h"
#include"sq.h"
#include"rect.h"
#include<unistd.h>
#include<sys/wait.h>
#include<signal.h>
#include<string.h>

int main(){

	printf("************START*************\n");

	signal(SIGINT,SIG_IGN);
	char *files_to_compile[]={ "circle.c","sq.c","rect.c","main.c"};
	int num_of_files = sizeof(files_to_compile)/sizeof(files_to_compile[0]);
	
	// create child for each files to be compiled - Child(1-4)
	for(int i=0; i<num_of_files; i++){
		pid_t pid = fork();
		
		if(pid==-1){
			perror("Process not created.\n");
			_exit(1);
		}
		else if(pid==0){ // child
			printf("%s (compiling...)\n",files_to_compile[i]);
			char *arg[]={"gcc","-c",(char*)files_to_compile[i],NULL};
			execvp("gcc",arg);
		}
	}

	// parent waits for all child process to finish
	int stat;
	for(int j=0; j<num_of_files; j++){
		pid_t ret = wait(&stat);
		if(ret==-1){
			printf("%s file is not compiled.\n",files_to_compile[j]);
		}
		else{
			printf("%s (Compilation DONE)\n",files_to_compile[j]);
		}
	}
	// upto this, all .c files are compiled and .o files are created
	// next we need to link all .o files, so create child(5)

	pid_t link_pid = fork();
	
	if(link_pid==0){ //child-5
		char *link_arg[] = {"gcc","-o","program.out","circle.o","sq.o","rect.o","main.o",NULL};
		int ret = execvp("gcc",link_arg);
		if(ret==-1){
			perror("Linking failed\n");
			_exit(5);
		}
		else
			printf("All files are linked and program is created.\n");		
		
	}
	waitpid(link_pid,&stat,0); //waiting for child-5 to end

	//execute the program, create child(6)
	pid_t exec_pid = fork();
	if(exec_pid==0){
		printf("\nRunning the program.............\n");
		execl("./program.out","program.out",NULL);
	}
	waitpid(exec_pid,&stat,0);//waiting for child-6 to end
	
	printf("\n************END*************\n");
	system("rm *.out *.o");
return 0;}
