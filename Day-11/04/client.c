#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netinet/ip.h> 
#include<arpa/inet.h>

// Run this code in System-2 (client)

#define SERV_PORT 2899
#define SERV_IP "172.18.6.112" // here, put the ip address of the system-1

int main(){
	struct sockaddr_in serv_addr;
	
	int cli_fd = socket(AF_INET,SOCK_STREAM,0);
	if(cli_fd==-1){
		perror("Client creation failed\n");
		_exit(-1);
	}
	else printf("Client creation successful\n");
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(SERV_PORT);
	serv_addr.sin_addr.s_addr = inet_addr(SERV_IP);////////////
	int b_ret = connect(cli_fd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
	if(b_ret==-1){
		perror("Connection failed\n");
		_exit(-1);
	}
	else printf("Connection successful\n");

	char buf[200];
	do{
		printf("server>");
		fgets(buf,sizeof(buf),stdin);
		write(cli_fd,buf,strlen(buf));
		printf("client>");
		read(cli_fd,buf,sizeof(buf));
		printf("%s",buf);
	}while(strcmp(buf,"bye\n"));

	
	close(cli_fd);

return 0;}






















