#include <string>
#include <vector>
using namespace std;

struct header
{
	string name;
	string value;
};

struct request
{
	string method;
	string url;
	string version;
	vector<header> headers;
};
