#include <iostream>
using namespace std;
#include "server.h"
#include "protocole.h"
#include "cynetProtocole.h"

int main()
{

	cynetProtocole *a = new cynetProtocole();
	a->init();
	a->setMessage();
	a->peotocoleMenu();
	server *S = new server();
	S->setProtocole(*a);
	S->update();
	return 0;
}

