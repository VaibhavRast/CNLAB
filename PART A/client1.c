#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>
#define bufsize 1024

int clientSocket;
char buffer[bufsize];
char fname[255];
int fd,n;

struct sockaddr_in serverAddr;
socklen_t addrSize;


int main()
{
	clientSocket=socket(PF_INET, SOCK_STREAM, 0);

	//Configure address port ip Mmemset

	serverAddr.sin_family=AF_INET;
	serverAddr.sin_port=htons(7891);
	serverAddr.sin_addr.s_addr=inet_addr("127.0.0.1");

	memset(serverAddr.sin_zero,'\0',sizeof serverAddr.sin_zero);

	

	addrSize=sizeof serverAddr;
	connect(clientSocket, (struct sockaddr *) &serverAddr, addrSize);

	printf("Enter filename\n");
	scanf("%s",fname);


	send(clientSocket,fname,255,0);

	while(recv(clientSocket,buffer,bufsize,0)>0)
	{
		printf("%s\n",buffer);
	}
	printf("EOF\n");


	return close(clientSocket);



}