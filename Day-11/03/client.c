#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netinet/ip.h>
#include<arpa/inet.h>
#include<stdlib.h>

#define SERV_IP "127.0.0.1"
#define SERV_PORT 2019

int main(int argc, char *argv[]){
	if(argc!=4){
		perror("Syntax error\n");
		_exit(-1);
	}

	float num1,num2,res;
	char op[4];
	num1 = atoi(argv[1]);
	strcpy(op,argv[2]);
	printf("operation : '%s'\n",op);
	num2 = atoi(argv[3]);

	struct sockaddr_in serv_addr;
	int cli_fd = socket(AF_INET,SOCK_STREAM,0);
	if(cli_fd==-1){
		perror("-Client creation failed\n");
		_exit(-1);
	}
	else printf("-Client creation success\n");
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(SERV_PORT);
	serv_addr.sin_addr.s_addr = inet_addr(SERV_IP); 
	int ret = connect(cli_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
	if(ret==-1){
		perror("-Connection failed\n");
		_exit(-1);
	}
	else printf("-Connection success\n");

	write(cli_fd,&num1,sizeof(float));
	write(cli_fd,&num2,sizeof(float));
	write(cli_fd,op,sizeof(op));
	printf("server>");
	read(cli_fd,&res,sizeof(float));
	printf("Result : %.2f\n",res);
	close(cli_fd);
return 0;}
