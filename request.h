#ifndef HTTP_REQUEST_HPP
#define HTTP_REQUEST_HPP

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

#endif
