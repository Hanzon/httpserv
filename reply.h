#include "request.h"
#include <string>
#include <vector>
using namespace std;

class reply
{
public:
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
	};

	void reset();
	string to_buffers();
	void set_status(const status_type);
	//functions used when the status equal 200
	void set_headers(const vector<header>& );
	void set_content(const string& );
	string get_content();

private:
	enum status_type status;
	vector<header> headers;
	string content;
	//functions used when the status unequal 200
	string status_to_string();
	void to_reply_headers();
	void to_reply_content();
};


