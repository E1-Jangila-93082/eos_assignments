#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netinet/ip.h> 
#include<arpa/inet.h>

// Run this code in System-1 (server) 

#define SERV_PORT 2009
#define SERV_IP "127.0.0.7" // here, put the ip address of the system-1

int main(){
	struct sockaddr_in serv_addr, cli_addr;
	socklen_t clisock_len = sizeof(cli_addr);
	int serv_fd = socket(AF_INET,SOCK_STREAM,0);
	if(serv_fd==-1){
		perror("Socket creation failed\n");
		_exit(-1);
	}
	else printf("Socket creation successful\n");
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(SERV_PORT);
	serv_addr.sin_addr.s_addr = inet_addr(SERV_IP);////////////
	int b_ret = bind(serv_fd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
	if(b_ret==-1){
		perror("Binding failed\n");
		_exit(-1);
	}
	else printf("Binding successful\n");
	
	listen(serv_fd,5);

	int cl_fd = accept(serv_fd,(struct sockaddr*)&cli_addr,&clisock_len);
	if(cl_fd==-1){
		perror("Accept failed\n");
		_exit(-1);
	}
	else printf("Accept successful\n");
	char buf[200];
	do{
		printf("client>");
		read(cl_fd,buf,sizeof(buf));
		printf("%s",buf);
		printf("server>");
		fgets(buf,sizeof(buf),stdin);
		write(cl_fd,buf,strlen(buf));
	}while(strcmp(buf,"Peace out\n")!=0);
	
	close(cl_fd);
	shutdown(serv_fd,SHUT_RDWR);

return 0;}






















