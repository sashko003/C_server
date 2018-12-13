#include "header.h"

int main()
{
	// Initialize winsock
	WSADATA wsaData;
	WORD wVersion = MAKEWORD(2, 2);

	int wsOK = WSAStartup(wVersion, &wsaData);
	if (wsOK != 0) {
		printf("Can't initialize winsock. \n");
		return -1;
	}

	// Create a socket
	SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening == INVALID_SOCKET) {
		printf("Can't create a socket. \n");
		return -1;
	}

	// Bind the socket to an IP-address and port
	struct sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(9999);
	hint.sin_addr.S_un.S_addr = INADDR_ANY;  // inet_pton

	bind(listening, (struct sockaddr*)&hint, sizeof(hint));

	// Tell Winsock the socket is for listening
	listen(listening, SOMAXCONN);

	// Wait for a connection
	struct sockaddr_in client;
	int clientSize = sizeof(client);

	SOCKET clientSocket = accept(listening, (struct sockaddr*)&client, &clientSize);

	char host[NI_MAXHOST]; // client's remote name
	char service[NI_MAXHOST]; // service (port) the client is connect on

	ZeroMemory(host, NI_MAXHOST);
	ZeroMemory(service, NI_MAXHOST);

	if (getnameinfo((struct sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXHOST, 0) == 0) {
		printf("%s connected on port %s \n", host, service);
	}
	else {
		inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
		printf("%s connected on port %s \n", host, ntohs(client.sin_port));
	}

	// Close listening socket
	closesocket(listening);

	// While loop: accept and echo message back to client

	char buffer[4096];
	MouseActivities unMouseAct;
	while (1) {
		ZeroMemory(unMouseAct.chMessage, sizeof(unMouseAct.chMessage));

		// wait for client to send data
		int byteReceived = recv(clientSocket, unMouseAct.chMessage, sizeof(unMouseAct.chMessage), 0);
		if (byteReceived == SOCKET_ERROR) {
			printf( "Error in recv().\n");
			break;
		}
		if (byteReceived == 0) {
			printf("Client disconnected. \n");
			break;
		}
		printf("X: %d  Y: %d \n", unMouseAct.iCoords[0], unMouseAct.iCoords[1]);
		
		//// echo message back to client
		send(clientSocket, unMouseAct.chMessage, byteReceived + 1, 0);
	}
	// close a socket
	closesocket(clientSocket);

	// shutdown winsock
	WSACleanup();

	return 0;
}