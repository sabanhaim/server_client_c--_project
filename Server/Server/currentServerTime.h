#pragma once
#include "message.h"
// client message for asking currentServerTime; 
class currentServerTime : public message
{

private:

public:
	currentServerTime();
	string messageRequest(char* buf);

};