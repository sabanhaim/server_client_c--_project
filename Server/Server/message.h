#pragma once
#include <iostream>
#include <WS2tcpip.h>
#include <string>
#include <sstream>
using namespace std;
//abstract class for message

class message
{
public:
	message();
	virtual string messageRequest(char*) = 0;
	int get_id(void);
	void sed_id(int id);
	string getNmae(void);
	void setName(string s);
protected:
	int id = -1;
	string nameMessage;
	bool processing = false;
};