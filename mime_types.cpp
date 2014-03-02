#include "mime_types.h"

mapping::mapping()
{
	this->maper["gif"]="image/gif";
	this->maper["htm"]="text/html";
	this->maper["html"]="text/html";
	this->maper["jpg"]="image/jpeg";
	this->maper["png"]="image/png";
}

string mapping::extension_to_type(const string& extension)
{
	map<string, string>::iterator iter;
	iter = this->maper.find(extension);
	if( iter == this->maper.end() )
		return "text/plain";
	return iter->second;
}
