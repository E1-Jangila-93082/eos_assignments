#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/un.h>
#include<math.h>
#include<stdlib.h>

int main(){
	struct sockaddr_un serv_addr,cli_addr;
	socklen_t clisock_len = sizeof(cli_addr);
	
	unlink("/home/jangila/Git_data/eos_assignments/Day-11/02/my_socket");
	int serv_fd = socket(AF_UNIX,SOCK_STREAM,0);
	if(serv_fd==-1){
		perror("-Server creation failed\n");
		_exit(-1);
	}
	else printf("-Server creation successful\n");
	serv_addr.sun_family = AF_UNIX;
	strcpy(serv_addr.sun_path,"/home/jangila/Git_data/eos_assignments/Day-11/02/my_socket");
	int ret =bind(serv_fd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
	if(ret==-1){
		perror("-Binding failed\n");
		_exit(-1);
	}
	else printf("-Binding successful\n");
	
	listen(serv_fd,4);
	while(1){
		int cli_fd = accept(serv_fd,(struct sockaddr*)&cli_addr,&clisock_len);
		if(cli_fd==-1){
			perror("-Accept failed\n");
		}
		else printf("-Accept successful\n");

		float num1,num2,res;
		char op[4];
		printf("client>");
		read(cli_fd,&num1,sizeof(float));
		read(cli_fd,&num2,sizeof(float));
		read(cli_fd,op,sizeof(op));
		if(strcmp(op,"+")==0){
		res = num1 + num2;
		}
		if(strcmp(op,"-")==0){
			res = num1 - num2;
		}
		if(strcmp(op,"*")==0){
		res = num1 * num2;
			}
		if(strcmp(op,"/")==0){
			res = num1 / num2;
		}
		printf("%.2f %s %.2f",num1,op,num2);
		write(cli_fd,&res,sizeof(float));
		close(cli_fd);
	}
	shutdown(serv_fd,SHUT_RDWR);

return 0;}
