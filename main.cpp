#include "main.h"

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
	openlog("httpserv", LOG_PID|LOG_CONS, LOG_USER);

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
				syslog(LOG_ERR,"Too many clients!\n");
				return -1;	//how to deal with the problem?
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
				if( (pid=fork())==0)
				{
					//child process
					for(j=0; j<FD_SETSIZE; ++j)
					{
						if(j==sockfd)
							continue;
						close(j);
					}
					//read the request packet
					ssize_t nread;
					char recvbuf[Max_packet_size];	
					if( (nread=read(sockfd, recvbuf, Max_packet_size)) < 0)
					{
						close(sockfd);
						syslog(LOG_ERR, "%m\n");
						return -1;
					}
					syslog(LOG_INFO, "read the request successfully");
					//parse request
					request_parser reqer;
					reqer.parse(recvbuf);
					request req = reqer.getreq();

					reply rep;
					request_handler req_handler(doc_root);
					req_handler.produre_reply(req, rep);

					string t = rep.to_buffers();
					char* sendbuf = const_cast<char*>(t.c_str());

					nread = rio_writen(sockfd, sendbuf, t.size());	
					if( nread == -1)
					{
						close(sockfd);
						syslog(LOG_ERR, "%m\n");
						return -1;
					}
					syslog(LOG_INFO, "write the reply successfully, %d byte", static_cast<int>(nread));
					close(sockfd);
					return 0;
				}
				close(client[i]);
			}

			if(--nready <= 0)
				break;
		}
	}
	return 0;
}



















