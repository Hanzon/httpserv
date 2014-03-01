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
	request_path = req.url;
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

	std::string full_path = this->m_docroot + request_path;
	ifstream in(full_path.c_str(), std::ios::in | std::ios::binary);
	if( !in)
	{
		rep.set_status(reply::not_found);
		return;
	}

	rep.set_status(reply::ok);
	string content;
	char buf[512];
	while(in.read(buf, sizeof(buf)).gcount() > 0)
			content.append(buf, in.gcount());
	rep.set_content(content);
	
	vector<header> headers;
	headers.resize(2);
	headers[0].name = "Content-Length";
	char len[8] = {0};
	sprintf(len, "%d", static_cast<int>(rep.get_content().size()) );
	headers[0].value = len;
	headers[1].name = "Content-Type";
	headers[1].value = maper.extension_to_type(extension); //Check the extension! 	
	rep.set_headers(headers);
}

bool request_handler::url_decode(const string& in, string& out)
{
	
}

