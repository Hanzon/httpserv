#define SERV_PORT 8080
#define LISTENQ 10

#include <netinet/in.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/select.h>
#include <sys/time.h>

int main()
{
	int listenfd, connfd, sockfd;
	listenfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	
	socklen_t clilen;
	struct sockaddr_in cliaddr, servaddr;
	memset(&servaddr, 0,sizeof(servaddr));	
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);
	
	bind(listenfd, (sockaddr*)&servaddr, sizeof(servaddr));
	listen(listenfd, LISTENQ);

	int nready, client[FD_SETSIZE];
	int i,j;
	for(i=0; i<FD_SETSIZE; ++i)
		client[i] = -1;

	fd_set rset, allset;
	FD_ZERO(&allset);
	FD_SET(listenfd, &allset);

	int maxi = -1;
	int maxfd = listenfd;

	pid_t pid;

	while(1)
	{
		rset = allset;
		nready = select(maxfd+1, &rset, NULL, NULL, NULL);
		
		/*-------------------------------------------------*/
		if(FD_ISSET(listenfd, &rset))
		{
			clilen = sizeof(cliaddr);
			connfd = accept(listenfd, (sockaddr*)&cliaddr, &clilen);
			for(i=0; i<FD_SETSIZE; ++i)
			{
				if(client[i]<0)
				{
					client[i] = connfd;
					break;
				}
			}
			if( i == FD_SETSIZE)
			{
				//too many clients
			}

			FD_SET(connfd, &allset);
			if(connfd > maxfd)
				maxfd = connfd;
			if(i > maxi)
				maxi = i;

			if(--nready <=0 )
				continue;
		}

		/*-------------------------------------------------*/
		for(i=0; i<=maxi; i++)
		{
			if( (sockfd = client[i]) < 0)
				continue;
			if(FD_ISSET(sockfd, &rset))
			{
				if( (pid==fork())==0)
				{
					//child process
					for(j=0; j<FD_SETSIZE; ++j)
					{
						if(j==sockfd)
							continue;
						close(j);
					}
					//do something!
					

					close(sockfd);
					return 0;
				}
				//parent process
				close(client[i]);
			}

			if(--nready <= 0)
				break;
		}
	}
	return 0;
}



















