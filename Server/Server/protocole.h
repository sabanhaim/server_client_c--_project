#pragma once
#define Max_Message 10;
#include <iostream>
using namespace std;
#include "message.h"

//abstract class for server protocole
class protocole

{
public:
	protocole(void);
	void init(void);
	message** get(void);
	void set(message**);
	int getCurrentMessage(void);
	void setCurrentMessage(int);
	void peotocoleMenu(void);
	string getStrOpen(void);
	int getStrOpenLength(void);


private:
	message **array_message;
	int currentMessage = 0;
	string strOpen = "";
	int strOpenLength;

};