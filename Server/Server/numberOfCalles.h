#pragma once
#include "message.h"
// client message for asking numberOfCalles to server; 

class numberOfCalles : public message
{

private:

public:
	numberOfCalles();
	string messageRequest(char*);
};