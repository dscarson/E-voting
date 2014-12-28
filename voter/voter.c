#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include "RSA.c"

int main()
	{
	int sockfd = 0,n = 0;
	char recvBuff[1024];
	struct sockaddr_in serv_addr;
	
	memset(recvBuff, '0' ,sizeof(recvBuff));
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(2001);
	serv_addr.sin_addr.s_addr = inet_addr("23.23.190.204");

	connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	return 0;
	}
