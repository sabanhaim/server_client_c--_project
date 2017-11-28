#pragma once
#include <iostream>
#include <WS2tcpip.h>
#include <string>
#include <sstream>
#include "server.h"
#include <cstdio>
#include <ctime>
#include "protocole.h"
#include <map>
#define currentServerTime 0  
#define numberOfCalles 1 
#define port 54000

//server which can handle for multiclient
#pragma comment (lib, "ws2_32.lib")
class server
{

public:

	server(void);
	void update(void);
	void messageHandle(SOCKET sock, char *buf);//buf is  the client request;
	void setProtocole(protocole p);
	void incNumOfCallesToServer(void);
	string  getNumOfCallesToServer(void);
	string getCurrentTimeServer(void);
	void funcServerMassage(SOCKET sock, string str);//message which need information from server
	void log(SOCKET sock, string s);// print what server is handle;


private:
	fd_set master;
	SOCKET listening;
	clock_t start;
	clock_t endTime;
	clock_t clockTicksTaken;
	double duration;
	protocole serverProtocole;
	int messageReq = 0;
	int numOfClient = 0;
	map<SOCKET, int> m;
	int numOfCallesToServer = 0;




};