#include "request.h"
#include <string>
#include <vector>
using namespace std;

class reply
{
public:
	string to_buffers();
private:
	enum status_type
	{
		ok = 200,
		created = 201,
		accepted = 202,
		no_content = 204,
		moved_permanently = 301,
		moved_temporarily = 302,
		not_modified = 304,
		bad_request = 400,
		unauthorized = 401,
		forbidden = 403,
		not_found = 404,
		internal_server_error = 500,
		not_implemented = 501,
		bad_gateway = 502,
		service_unavailable = 503
	}status;
	std::vector<header> headers;
	std::string content;

private:
	string to_string(reply::status_type status);
	string to_reply_content(reply::status_type status);
};


