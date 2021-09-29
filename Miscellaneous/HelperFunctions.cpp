#include <iostream>
#include <string>

std::string to_lower_case(std::string str) // Removes capitalization
{
	int length = str.length();
	for (int i = 0; i < length; ++i)
	{
		if ( (int) str[i] >= 'A' && (int) str[i] < 'a')
		{
			int num = str[i]+32;
			str[i] = num;
		}
	}
	return str;
}

std::string to_upper_case( std::string s )
{
	int length = s.length();
	for (int i = 0; i < length; ++i)
	{
		if ((int) s[i] >= 'a' && (int) s[i] <= 'z')
		{
			int num = s[i] - 32;
			s[i] = num;
		}
	}
	return s;
}