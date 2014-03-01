#include "reply.h"
#include <string>
using namespace std;


class request_handler
{
public:
	//avoid the parameter to be converted implicitly
	explicit request_handler(const string& docroot);
	void produre_reply(const request& req, reply& rep);

private:
	string m_docroot;
	static bool url_decode(const string& in, string& out);
};
