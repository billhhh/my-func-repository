#include <string>

string wh_int2string(int n)
{
	std::stringstream ss;
	std::string str;
	ss<<n;
	ss>>str;

	return str;
}