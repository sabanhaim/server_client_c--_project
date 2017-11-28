#include <iostream>
#include <string>
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#define port 54000

using namespace std;

void main()
{
	string ipAddress = "127.0.0.1";
	WSADATA data; 
	WORD ver = MAKEWORD(2, 2);
	int wsEresult = WSAStartup(ver, &data);
	if (wsEresult != 0)
	{
		cerr << "can't start Winsock, Err #" << wsEresult << endl;
		return;
	}

	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
	{
		cerr << "cant create socket, Err #" << WSAGetLastError() << endl;
		return;
	}
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

	int connResult = connect(sock, (sockaddr*)&hint, sizeof(hint));
	if (connResult == SOCKET_ERROR)
	{
		cerr << "Can't connect to server , sErr *" << WSAGetLastError() << endl;
		closesocket(sock);
		WSACleanup();
		return;
	}
	char buf[4096];
	string userInput;
	///for the first message
	int sendResulat = send(sock, userInput.c_str(), userInput.size() + 1, 0);
	if (sendResulat != SOCKET_ERROR)
	{
		ZeroMemory(buf, 4096);
		int bytesReceievd = recv(sock, buf, 4096, 0);
		if (bytesReceievd > 0)
		{
			cout << "<SERVER>" << string(buf, 0, bytesReceievd) << endl;

		}
	}

	do
	{
		cout << '>';
		getline(cin, userInput);

		if (userInput.size() > 0)
		{
			int sendResulat = send(sock, userInput.c_str(), userInput.size() + 1, 0);
			if (sendResulat != SOCKET_ERROR)
			{
				ZeroMemory(buf, 4096);
				int bytesReceievd = recv(sock, buf, 4096, 0);
				if (bytesReceievd > 0)
				{
					cout << "<SERVER>" << string(buf, 0, bytesReceievd)<< endl;

				}
			}
		}
	} while (userInput.size() > 0);

	closesocket(sock);
	WSACleanup();
	
}