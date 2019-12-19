#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>
#define bufsize 1024

int serverSocket, newSocket;
char buffer[bufsize];
char fname[255];
int fd,n;

struct sockaddr_in serverAddr;
struct sockaddr_storage serverStorage;
socklen_t addrSize;


int main()
{
	serverSocket=socket(PF_INET, SOCK_STREAM, 0);

	//Configure address port ip Mmemset

	serverAddr.sin_family=AF_INET;
	serverAddr.sin_port=htons(7891);
	serverAddr.sin_addr.s_addr=inet_addr("127.0.0.1");

	memset(serverAddr.sin_zero,'\0',sizeof serverAddr.sin_zero);

	bind(serverSocket, (struct sockaddr *) &serverAddr, sizeof serverAddr);

	if(listen(serverSocket,5)==0)
		printf("Listening\n");
	else
		printf("Error\n");

	addrSize=sizeof serverStorage;
	newSocket=accept(serverSocket, (struct sockaddr *) &serverStorage, &addrSize);

	recv(newSocket,fname,255,0);

	fd=open(fname,O_RDONLY);
	if(fd==-1)
	{
		strcpy(buffer,"File Not Found");
		n=strlen(buffer);
	}
	else
	{
		n=read(fd,buffer,bufsize);
	}

	send(newSocket,buffer,n,0);

	close(newSocket);

	return close(serverSocket);



}