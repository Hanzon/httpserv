#include "reply.h"
#include "request.h"
#include "request_handler.h"
#include <fstream>
#include <string>

using namespace std;

request_handler::request_handler(const string& docroot):m_docroot(docroot)
{}

void request_handler::produre_reply(const request& req, reply& rep)
{
	string request_path;
	//
	request_path = req;
	//Request path must be absolute and not contain ".."
	if(request_path.empty() || request_path[0]!='/' 
		|| request_path.find("..")!=string::npos)
	{
		rep = rep::stock_reply(reply::bad_request);
	}
}

bool request_handler::url_decode(const string& in, string& out)
{

}
