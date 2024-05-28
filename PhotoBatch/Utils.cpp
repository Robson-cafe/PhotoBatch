#include "Utils.h"

#include <string>
#include <algorithm>

string Utils::ToLower(
  string str
)
{
	/*for (char& c : str) {
		c = tolower(c);
	}*/

	transform(begin(str), end(str), begin(str), [](unsigned char c) {return tolower(c); });
	return str;
}

//----------------------------------------------------------------------------------------------

bool Utils::HasWhiteSpace(const string& flag)
{
	return flag.find(' ') != string::npos;
}
