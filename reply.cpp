#include "reply.h"
#include <string>

string reply::to_string(reply::status_type status)
{
	switch(status)
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

string reply::to_reply_content(reply::status_type status)
{
	string shead = "<html><body><h1>";
	string stail = "</h1></body></html>";
	switch(status)
	{
	case ok:
		return "";
	case created:
		return shead+"201 Created"+stail;
	case bad_request:
		return shead+"400 Bad Request"+stail;
	case forbidden:
		return shead+"403 Forbidden"+stail;
	case not_found:
		return shead+"404 Not Found"+stail;
	default:
		return shead+"500 Internal Server Error"+stail;
	}
}

string reply::to_buffers()
{
	string re;
	re += to_string(this->status);
	for(std::size_t i=0; i< this->headers.size(); ++i)
		re += this->headers[i].name + ":" + this->headers[i].value + "\r\n";
	//如何构造各种响应包。
	re += this->content;
	return re;
}

