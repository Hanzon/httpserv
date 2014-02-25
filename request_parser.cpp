#include <iostream>
#include "request_parser.h"

void request_parser::reset()
{
	this->req.method.clear();
	this->req.url.clear();
	this->req.version.clear();
	this->req.headers.clear();
}

request request_parser::getreq()
{
	return this->req;
}

bool request_parser::parse_reqline(string statu_line)
{
	string::size_type fpos, spos;

	fpos=0;
	spos=statu_line.find_first_of(" ");
	this->req.method = statu_line.substr(fpos, spos-fpos);
	
	fpos=spos+1;
	spos=statu_line.find_first_of(" ", fpos);
	this->req.url = statu_line.substr(fpos, spos-fpos);

	fpos=spos+1;
	spos=statu_line.find_first_of("\r\n", fpos);
	this->req.version = statu_line.substr(fpos, spos-fpos);

	return true;
}

bool request_parser::parse_reqheader(string header)
{

	string::size_type fpos=0, spos;
	int i=0;
	while( (spos=header.find_first_of("\r\n", fpos)) != string::npos )
	{
		string temp = header.substr(fpos, spos-fpos);
		string::size_type pos = temp.find_first_of(":");
		if(pos==string::npos)
			return false;
		
		struct header head;
		head.name = temp.substr(0,pos);
		head.value = temp.substr(pos+1, temp.size());
		req.headers.push_back(head);
		fpos=spos+2;
	}
	return true;
}

bool request_parser::parse(string packet)
{
	string::size_type pos = packet.find_first_of("\r\n");
	if(pos == string::npos)
		return false;
	string reqline, reqheader;
	reqline = packet.substr(0, pos);
	reqheader = packet.substr(pos+2, packet.size());
	return ( parse_reqline(reqline) && parse_reqheader(reqheader) );
}
/*
int main()
{
	string tem = "GET / HTTP/1.1\r\nHost:www.baidu.com\r\nnihao:hh\r\n";
	request_parser reqer;
	reqer.parse(tem);
	request t = reqer.getreq();
	cout<<t.method<<endl;
	cout<<t.url<<endl;
	cout<<t.version<<endl;
	cout<<t.headers[1].name;
	cout<<t.headers[1].value;
}
*/
