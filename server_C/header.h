#ifndef C_SERVER_HEADER_H_
#define C_SERVER_HEADER_H_
#include "os.h"

#include <stdio.h>
#include <string.h>

#ifdef WINDOWS
#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment (lib, "ws2_32.lib")
#endif // WINDOWS

#ifdef LINUX
#include <sys/socket.h> //socket
#include <arpa/inet.h> // inet_addr
//#define <netdb.h>
#define NI_MAXHOST      1025
#define NI_MAXSERV      32

#define SOCKET int
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#endif // LINUX

#include "mouseActivities.h"

int initializeSocket(void);
int closeSocket(SOCKET sock);

#define PORT 9999
#define X_COORD 0
#define Y_COORD 1

#endif // !C_SERVER_HEADER_H_
