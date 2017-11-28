#include <iostream>
#include <WS2tcpip.h>
#include <string>
#include <sstream>
#include "server.h"

#pragma comment (lib, "ws2_32.lib")

using namespace std;

server::server(void)
{

};
void server::update(void)
{
	WSADATA wsData;
	WORD ver = MAKEWORD(2, 2);

	int wsOk = WSAStartup(ver, &wsData);
	if (wsOk != 0)
	{
		cerr << "Can't Initialize winsock! Quitting" << endl;
		return;
	}

	// Create a socket
	SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening == INVALID_SOCKET)
	{
		cerr << "Can't create a socket! Quitting" << endl;
		return;
	}

	// Bind the ip address and port to a socket
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	hint.sin_addr.S_un.S_addr = INADDR_ANY;

	bind(listening, (sockaddr*)&hint, sizeof(hint));

	// Tell Winsock the socket is for listening 
	listen(listening, SOMAXCONN);

	// Create the master file descriptor set and zero it
	fd_set master;
	FD_ZERO(&master);

	// Add our first socket that we're interested in interacting with; the listening socket! 
	FD_SET(listening, &master);

	// this will be changed by the \quit command (see below, bonus not in video!)
	bool running = true;

	//start the clock
	start = clock();
	while (running)
	{
		fd_set copy = master;
		// See who's talking to us
		int socketCount = select(0, &copy, nullptr, nullptr, nullptr);
		// Loop through all the current connections / potential connect
		for (int i = 0; i < socketCount; i++)
		{
			SOCKET sock = copy.fd_array[i];

			// Is it an inbound communication?
			if (sock == listening)
			{
				// Accept a new connection
				SOCKET client = accept(listening, nullptr, nullptr);

				// Add the new connection to the list of connected clients
				FD_SET(client, &master);

				// Send a welcome message to the connected client
				string s = this->serverProtocole.getStrOpen();
				// Send a protcole message to the connected client
				send(client, s.c_str(), this->serverProtocole.getStrOpenLength(), 0);
				log(client, "is connected to the server");
			}
			else // It's an inbound message
			{
				char buf[4096];
				ZeroMemory(buf, 4096);

				// Receive message
				int bytesIn = recv(sock, buf, 4096, 0);
				if (bytesIn <= 0)
				{
					// Drop the client
					log(sock, "left the server");
					closesocket(sock);
					FD_CLR(sock, &master);
				}
				else
				{
					server::messageHandle(sock, buf);
				}

			}
		}
	}



	// Remove the listening socket from the master file descriptor set and close it
	// to prevent anyone else trying to connect.
	FD_CLR(listening, &master);
	closesocket(listening);

	// Message to let users know what's happening.
	string msg = "Server is shutting down. Goodbye\r\n";

	while (master.fd_count > 0)
	{
		// Get the socket number
		SOCKET sock = master.fd_array[0];

		// Send the goodbye message
		send(sock, msg.c_str(), msg.size() + 1, 0);

		// Remove it from the master file list and close the socket
		FD_CLR(sock, &master);
		closesocket(sock);
	}

	// Cleanup winsock
	WSACleanup();

	//system("pause");
}

void server::incNumOfCallesToServer() { this->numOfCallesToServer += 1; };

string server::getNumOfCallesToServer() {
	int  num1 = this->numOfCallesToServer;
	return to_string(num1).append("\r\n").insert(0, "The number of calles to server is ");
};

void server::setProtocole(protocole p)

{
	this->serverProtocole = p;
}


string server::getCurrentTimeServer() {
	endTime = clock();
	clockTicksTaken = endTime - start;
	duration = clockTicksTaken / (double)CLOCKS_PER_SEC;
	return to_string(duration).append("\r\n").insert(0, "Current server time is ");
}

void server::messageHandle(SOCKET sock, char *buf)
{

	messageReq = std::atoi(buf);
	if (messageReq <= this->serverProtocole.getCurrentMessage() && messageReq > 0)
	{
		log(sock, "send a meesage");
		message **m = serverProtocole.get();

		string str = (m[messageReq - 1]->messageRequest(buf));

		if (str[0] != '#')
			send(sock, str.c_str(), str.size(), 0);
		else
		{
			funcServerMassage(sock, str);
		}
		this->incNumOfCallesToServer();

	}
	else
	{
		if (messageReq != 0)
		{
			log(sock, "send a meesage");
			send(sock, "try again!!!\r\n", 14, 0);
		}
	}
}

void server::funcServerMassage(SOCKET sock, string str)
{
	switch (str[1] - '0')
	{
	case 0://getCurrentTimeServer
	{
		string str2 = this->getCurrentTimeServer();
		send(sock, str2.c_str(), str2.size(), 0);
		break;
	}
	case 1://getNumOfCallesToServer
	{

		string str2 = this->getNumOfCallesToServer();
		send(sock, str2.c_str(), str2.size(), 0);
	}
	}
}

void server::log(SOCKET sock, string s)
{
	cout << "SOCKET #" << sock << ": " << s << "\r\n";
}
;