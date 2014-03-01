#include "reply.h"
#include "mime_types.h"
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
	mapping maper;
	static bool url_decode(const string& in, string& out);
};
