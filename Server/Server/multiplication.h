#pragma once
#include "message.h"
// client message for asking multiplication two numbers; 
class multiplication : public message
{

private:

public:
	multiplication();
	bool validKelet(string str1, string str2);
	bool multiplication::IsValidNumber(string string);
	string messageRequest(char*);
	int inProcess = 0;
	bool Firstnumber = false;
	int sum;
};

