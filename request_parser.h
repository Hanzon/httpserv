#include "request.h"
#include <string>
using namespace std;

class request_parser
{
public:
	void reset();
	bool parse(string);
	request getreq();

private:
	request req;
	bool parse_reqline(string);
	bool parse_reqheader(string);
};
