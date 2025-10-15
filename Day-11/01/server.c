#include<stdio.h>
#include<unistd.h>
#include<sys/socket>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<>

int main(){
	struct sockaddr_in serv_addr,cli_addr; 
	socklen_t clisock_len = sizeof(cli_addr);

	int serv_fd = socket(AF_INET,SOCK_STREAM,0);
	if(serv_fd==-1){
		perror("-Server creation failed\n");
		_exit(-1);
	}
	else printf("-Server created successfully\n");
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(SERV_PORT);
	serv_addr.sin_addr.s_addr = inet_addr(SERV_IP);
	int ret = bind(serv_fd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
	if(ret==-1){
		perror("-Binding failed\n");
		_exit(-1);
	}
	else printf("-Binding successful\n");
	
	listen(serv_fd,4);

	int cli_fd =accept(cli_fd,(struct sockaddr*)&serv_addr,&clisock_len);
	if(cli_fd==-1){
		perror("-Accept failed\n");
		_exit(-1);
	}
	else printf("-Accept success\n");
	
	char f_name[10], ff_name[10];
	printf("client>");
	read(cli_fd,f_name,sizeof(f_name));
	read(cli_fd,ff_name,sizeof(ff_name));
	printf("file name : %s, fifo name : %s",f_name,ff_name);
	

return 0;}










