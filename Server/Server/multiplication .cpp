#pragma once
#include "multiplication.h"
#include <sstream>
#include <string>
#include <iostream>




multiplication::multiplication(void) { message::setName("multiplication"); };

string multiplication::messageRequest(char* buf)
{

	string str(buf), str3;
	std::size_t pos;
	int num1, num2;
	pos = str.find(" ");
	if (pos == string::npos)
		return "few argument\r\n";
	str3 = str.substr(pos + 1);
	pos = str3.find(" ");
	if (pos == string::npos)
		return "few argument\r\n";
	string str1(str3.substr(0, pos));
	string str2(str3.substr(pos + 1));
	if (!validKelet(str1, str2))
		return "Illegal numbers!!!\r\n";
	num1 = stoi(str1);
	num2 = stoi(str2);
	if (num1)
		num1 *= num2;
	stringstream strs;
	strs << num1;
	string temp_str = strs.str();
	const int size = temp_str.length();
	char* char_type = (char*)temp_str.c_str();
	char_type[size] = '\r';
	char_type[size + 1] = '\n';
	char_type[size + 2] = 0x00;

	string s5(char_type);
	return s5;


}


bool multiplication::validKelet(string str1, string str2)
{
	return(IsValidNumber(str1) && IsValidNumber(str2));
}

bool multiplication::IsValidNumber(string string)
{
	for (unsigned i = 0; i <string.length(); i++)
	{
		//ASCII value of 0 = 48, 9 = 57. So if value is outside of numeric range then fail
		//Checking for negative sign "-" could be added: ASCII value 45.
		if (string[i] == 13)
			return true;
		if (string[i] < 48 || string[i] > 57)
		{
			return FALSE;
		}
	}

	return TRUE;
}