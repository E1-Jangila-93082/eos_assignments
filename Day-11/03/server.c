#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netinet/ip.h>
#include<arpa/inet.h>
#include<stdlib.h>

#define SERV_IP "127.0.0.1"
#define SERV_PORT 2019

int main(){
	struct sockaddr_in serv_addr,cli_addr;
	socklen_t clisock_len = sizeof(cli_addr);
	
	unlink("/home/jangila/Git_data/eos_assignments/Day-11/03/my_socket");
	int serv_fd = socket(AF_INET,SOCK_STREAM,0);
	if(serv_fd==-1){
		perror("-Server creation failed\n");
		_exit(-1);
	}
	else printf("-Server creation successful\n");
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(SERV_PORT);
	serv_addr.sin_addr.s_addr = inet_addr(SERV_IP);
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
