#pragma once
#include <iostream>
#include <stdio.h>
#include "UDPServer.h"
#include "UDPSocket.h"
using namespace std;

#include <stdio.h>
#ifndef _WIN32
using SOCKET = int;
#define WSAGetLastError() 1
#else
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib") //Winsock Library
#endif

#define SERVER "127.0.0.1"	//ip address of udp server
#define BUFLEN 	1024		//Max length of buffer
#define PORT 8888			//The port on which to listen for incoming data

bool signInServer(UDPServer server, struct sockaddr_in si_other, int slen);

bool signInClient(UDPSocket client_sock, struct sockaddr_in si_other, int slen);