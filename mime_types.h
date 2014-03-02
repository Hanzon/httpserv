#ifndef MIME_TYPES_H
#define MIME_TYPES_H

#include <map>
#include <string>
using namespace std;
	
class mapping
{
public:
	mapping();
	string extension_to_type(const string& extension);
private:
	map<string, string> maper;
};

#endif
