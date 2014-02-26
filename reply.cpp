#include "reply.h"
#include <stdio.h>
#include <string>

void reply::set_status(const status_type status)
{
	this->status = status;
}

string reply::status_to_string()
{
	switch(this->status)
	{
	case ok:
		return "HTTP/1.0 200 OK\r\n";
	case created:
		return "HTTP/1.0 201 Created\r\n";
	case bad_request:
		return "HTTP/1.0 400 Bad Request\r\n";
	case forbidden:
		return "HTTP/1.0 403 Forbidden\r\n";
	case not_found:
		return "HTTP/1.0 404 Not Found\r\n";
	default:
		return "HTTP/1.0 500 Internal Server Error\r\n";
	}
}

void reply::to_reply_headers()
{
  this->headers.resize(2);
  this->headers[0].name = "Content-Length";
  char len[4] = {0};
  sprintf(len,"%d", static_cast<int>(this->content.size()) );
  this->headers[0].value = len; 
  this->headers[1].name = "Content-Type";
  this->headers[1].value = "test/html";
}

void reply::to_reply_content()
{
	string shead = "<html><body><h1>";
	string stail = "</h1></body></html>";
	switch(status)
	{
	case ok:
		this->content =  "";
		return;
	case created:
		this->content = shead+"201 Created"+stail;
		return;
	case bad_request:
		this->content = shead+"400 Bad Request"+stail;
		return;
	case forbidden:
		this->content = shead+"403 Forbidden"+stail;
		return;
	case not_found:
		this->content = shead+"404 Not Found"+stail;
		return;
	default:
		this->content = shead+"500 Internal Server Error"+stail;
		return;
	}
}

void reply::set_headers(const vector<header> headers)
{
	this->headers = headers;
}

void reply::set_content(const string content)
{
	this->content = content;
}

string reply::to_buffers()
{
	string re = status_to_string();
	if(this->status != ok)
	{
		to_reply_content();
		to_reply_headers();
	}
	for(std::size_t i=0; i< this->headers.size(); ++i)
		re += this->headers[i].name + ":" + this->headers[i].value + "\r\n";
	re += this->content;
	return re;
}

int main()
{
	return 0;
}

