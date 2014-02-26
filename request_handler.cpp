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
		rep.set_status(reply::bad_request);
		return;
	}

	if(request_path[request_path.size() -1] == '/')
	{
		request_path += "index.html";
	}

	std::size_t last_slash_pos = request_path.find_last_of("/");
	std::size_t last_dot_pos = request_path.find_last_of(".");
	string extension;
	if( last_dot_pos!=string::npos && last_dot_pos> last_slash_pos)
	{
		extension = request_path.substr(last_dot_pos+1);
	}

	std::string full_path = this->doc_root + request_path;
	ifstream in(full_path.c_str(), std::ios::in | std::ios::binary);
	if( !in)
	{
		rep.set_status(reply::not_found);
		return;
	}

	rep.status = reply::ok;
	vector<char> buf;
	buf.reserve(512);
	while(in.read( 
}

bool request_handler::url_decode(const string& in, string& out)
{

}
