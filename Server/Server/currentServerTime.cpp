#pragma once
#include "currentServerTime.h"


currentServerTime::currentServerTime(void) { message::setName("currentServerTime"); };

string currentServerTime::messageRequest(char* buf)
{
	return "#0";
};
