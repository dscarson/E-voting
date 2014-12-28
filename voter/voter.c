#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include "RSA.c"

void conv(char x[30])
	{
	int i;
	for(i=0;x[i]!=':';i++);
	x[i]=' ';
	return;	
	}
int main()
	{
	int sockfd = 0,n = 0;
	char recvBuff[1024];
	struct sockaddr_in serv_addr;
	FILE *ip=fopen("ip.config","r");
	char PKdist[30];
	char registrar[30];
	char auth[30];
	char counter[30];
	char ip_t[30];
	char _pub[16];
	char name[33]={0};
	char email[33]={0};
	char sendBuff[1024];
	int port_t;
	fgets(registrar,30,ip);
	fgets(PKdist,30,ip);
	fgets(auth,30,ip);
	fgets(counter,30,ip);
	fclose(ip);
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	serv_addr.sin_family = AF_INET;
	
	conv(registrar);
	sscanf(registrar,"%s %d",ip_t,&port_t);
	serv_addr.sin_port = htons(port_t);
	serv_addr.sin_addr.s_addr = inet_addr(ip_t);
	connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	
	keygen();
	printf("Enter name: ");
	gets(name);
	printf("Enter Email ID: ");
	gets(email);
	sendBuff[0]=0;
	memcpy(sendBuff+1,name,32);
	memcpy(sendBuff+33,email,32);
	
	FILE *pub=fopen("pub_key","rb");
	memcpy(sendBuff+32+32+1,_pub,16);
	fwrite(sendBuff,32+32+1+16,1,stdout);
	write(sockfd,sendBuff,32+32+16+1);
	return 0;
	}
