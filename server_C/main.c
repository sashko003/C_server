#include "header.h"

int writeToFile(char *fName, const MouseActivities *unMouseAct);

int main()
{
	// Initialize winsock
	if (initializeSocket() != 0) {
		printf("Can't initialize winsock.\n");
		return -1;
	}

	// Create a socket
	SOCKET skListening = socket(AF_INET, SOCK_STREAM, 0);
	if (skListening == INVALID_SOCKET) {
		printf("Can't create a socket. \n");
		return -1;
	}

	// Bind the socket to an IP-address and port
	struct sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(PORT);
	//hint.sin_addr.S_un.S_addr = INADDR_ANY;  // inet_pton
	//inet_pton(AF_INET, "178.212.111.39", &hint.sin_addr);

	bind(skListening, (struct sockaddr*)&hint, sizeof(hint));

	// the socket is for listening
	listen(skListening, SOMAXCONN);

	// Wait for a connection
	struct sockaddr_in addrClient;
	int clientSize = sizeof(addrClient);

	SOCKET clientSocket = accept(skListening, (struct sockaddr*)&addrClient, &clientSize);

	char chHost[NI_MAXHOST]; // client's remote name
	char chService[NI_MAXHOST]; // service the client is connected on

	memset(chHost, 0, NI_MAXHOST);
	memset(chService, 0, NI_MAXHOST);

	if (getnameinfo((struct sockaddr*)&addrClient, sizeof(addrClient), chHost, NI_MAXHOST, chService, NI_MAXHOST, 0) == 0) {
		printf("%s connected on port %s \n", chHost, chService);
	}
	else {
		inet_ntop(AF_INET, &addrClient.sin_addr, chHost, NI_MAXHOST);
		printf("%s connected on port %d \n", chHost, ntohs(addrClient.sin_port));
	}

	// Close listening socket
	closeSocket(skListening);

	// accept and echo mouse activities back to client
	MouseActivities unMouseAct;
	while (1) {
		memset((void*)&unMouseAct, 0, sizeof(unMouseAct));

		// wait for client to send data
		int byteReceived = recv(clientSocket, unMouseAct.chMessage, sizeof(unMouseAct.chMessage), 0);
		if (byteReceived == SOCKET_ERROR) {
			printf( "Error in recv() function.\n");
			break;
		}
		if (byteReceived == 0) {
			printf("Client disconnected. \n");
			break;
		}

		//if (unMouseAct.chClickType == 0)
		//	printf("%s \n", unMouseAct.chClickType);
		//else
			printf("\n");

		//// echo message back to client
		if(byteReceived >= 8){
            if(writeToFile("//home//sashko999//task1//dev_server_CB//log.txt", &unMouseAct)<0){
                printf("Cannot write to file.\n");
            }
            send(clientSocket, unMouseAct.chMessage, sizeof(unMouseAct.chMessage), 0);
            printf("X: %d  Y: %d ", unMouseAct.iCoords[X_COORD], unMouseAct.iCoords[Y_COORD]);
        }
	}
	// close a socket
	closeSocket(clientSocket);

	return 0;
}

int writeToFile(char *fName, const MouseActivities *unMouseAct)
{
FILE *f = fopen(fName, "a+");
if (f == NULL)
{
    printf("Error opening file!\n");
    return -1;
}

fprintf(f, "X: %d Y: %d  %s\n", unMouseAct->iCoords[X_COORD], unMouseAct->iCoords[Y_COORD], unMouseAct->chClickType);

return fclose(f);
}
