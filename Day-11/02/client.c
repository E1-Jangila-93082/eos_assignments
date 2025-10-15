#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/un.h>
#include<stdlib.h>

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

	struct sockaddr_un serv_addr;
//	socklen_t servsock_len = sizeof(serv_addr);
	int cli_fd = socket(AF_UNIX,SOCK_STREAM,0);
	if(cli_fd==-1){
		perror("Client creation failed\n");
		_exit(-1);
	}
	else printf("Client creation success\n");
	serv_addr.sun_family = AF_UNIX;
	strcpy(serv_addr.sun_path,"/home/jangila/Git_data/eos_assignments/Day-11/02/my_socket"); 
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
	printf("operation : %.2f\n",res);
	close(cli_fd);
return 0;}
