#define SERV_PORT 8080
#define LISTENQ 10
#include "mime_types.h"
#include "request_parser.h"
#include "request_handler.h"
#include <iostream>
#include <netinet/in.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/select.h>
#include <sys/time.h>
#include <errno.h>
#include <syslog.h>

const unsigned int Max_packet_size = 2048;
const string doc_root = "/home/diange/Myproject/httpserv_git/httpserv/www";

ssize_t rio_readn(int fd, char *usrbuf, size_t n)
{
	size_t nleft = n;
	ssize_t nread;
	char *bufp = usrbuf;
	while (nleft > 0)
	{
		if( (nread=read(fd, bufp, nleft)) < 0)
		{
			if( errno == EINTR)
				nread = 0;
			else
				return -1;
		}
		else if (nread == 0)
				break;
		nleft -= nread;
		bufp += nread;
	}
	return (n-nleft);
}

ssize_t rio_writen(int fd, char *usrbuf, size_t n)
{
	size_t nleft =n;
	ssize_t nwritten;
	char *bufp = usrbuf;

	while( nleft>0)
	{
		if( (nwritten=write(fd, bufp, nleft) <=0) )
		{
			if(errno == EINTR)
				nwritten = 0;
			else 
				return -1;
			nleft -= nwritten;
			bufp += nwritten;
		}
		return n;
	}
}
