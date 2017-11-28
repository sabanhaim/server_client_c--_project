#include "protocole.h"
#include <sstream>
#include <string>
#include <iostream>

protocole::protocole() {
};

void protocole::init()
{
	array_message = new message*[10];
}

message** protocole::get()
{
	return array_message;
}

void protocole::set(message** m)
{
	array_message = m;
}

int protocole::getCurrentMessage(void) { return currentMessage; };

void protocole::setCurrentMessage(int num) { this->currentMessage = num; };

string protocole::getStrOpen() { return this->strOpen; };

int protocole::getStrOpenLength() { return this->strOpenLength; };


void protocole::peotocoleMenu()
{

	strOpen.append("choose your next message from server\r\n");
	for (int i = 0; i < getCurrentMessage(); i++)
	{
		std::ostringstream oss;
		oss << i + 1;
		strOpen.append(oss.str());
		strOpen.append(") ");
		strOpen.append(array_message[i]->getNmae());
		strOpen.append("\r\n");

	}
	this->strOpenLength = strOpen.length();

}