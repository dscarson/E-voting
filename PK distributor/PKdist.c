#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
 
int main(void)
{
  int listenfd = 0,connfd = 0;
  struct sockaddr_in serv_addr;
  char sendBuff[1025];  
  char readBuff[1024];
  char buff[16];
  int numrv;
  int n;
  int i;
  FILE* key;
  char filename[1024];
  listenfd = socket(AF_INET, SOCK_STREAM, 0);
  memset(&serv_addr, '0', sizeof(serv_addr));
  memset(sendBuff, '0', sizeof(sendBuff));
  serv_addr.sin_family = AF_INET;    
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); 
  serv_addr.sin_port = htons(5011);
   
  bind(listenfd, (struct sockaddr*)&serv_addr,sizeof(serv_addr));

  if(listen(listenfd, 1024) == -1 ){
      printf("Failed to listen\n");
      return -1;
  }
 printf("Distributor is up and running!\n");
  while(1)
    {
      connfd = accept(listenfd, (struct sockaddr*)NULL ,NULL); // accept awaiting request 
		
		printf("Reading");
		fflush(stdout);
		n=read(connfd,readBuff,4);
		if(n!=4)
			{
			sendBuff[0]=1;
			printf("Request rejected due to invalid format!\n");
			}
		else
			{
			readBuff[n]=0;
			unsigned int x=0;
			x=readBuff[3];
			x<<=8;
			x|=readBuff[2];
			x<<=8;
			x|=readBuff[1];
			x<<=8;
			x|=readBuff[0];
			sprintf(filename,"keys/%08X_pub",x);
			printf("%08X_pub",x);
			key=fopen(filename,"rb");
			if(key)
				{
				sendBuff[0]=0;
				fread(buff,1,16,key);
				for(i=0;i<16;i++)
					{
					sendBuff[i+1]=buff[i];	
					}
				}
			else
				{
				sendBuff[0]=2;
				printf("Requested key not found!\n");
				}
			}
			fflush(stdout);
		//strcpy(sendBuff, "Message from server1");
		fwrite(sendBuff,1,17,stdout);
      write(connfd, sendBuff, 17);
	close(connfd);
       sleep(1);
    }
 
 
  return 0;
}