/*
	UDP Server
*/

#include <stdio.h>
#include "UDPServer.h"
//#include "source.h"

#ifndef _WIN32
using SOCKET = int
#define WSAGetLastError() 1
#else
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib") //Winsock Library
#endif

//#define SERVER "127.0.0.1"	//ip address of udp server
#define BUFLEN 	1024		    //Max length of buffer
#define PORT    8888			//The port on which to listen for incoming data

int main(int argc, char* argv[])
{
	struct sockaddr_in si_other;
	//struct sockaddr_in si_other1;
	unsigned short srvport;
	int slen, slen1;
	char buf[BUFLEN];
	char username[BUFLEN];
	char password[BUFLEN];
	char msg[BUFLEN];
	char yes[BUFLEN] = "yes";
	char no[BUFLEN] = "no";
	char us[2][BUFLEN] = { {"vsergoyan"}, {"elhovhan"} };
	char ps[2][BUFLEN] = { {"12345678"}, {"12345678"} };
	int i, k = 0;

	srvport = (1 == argc) ? PORT : atoi(argv[1]);

	UDPServer server(srvport);
	slen = sizeof(si_other);
	//slen1 = sizeof(si_other1);

	//keep listening for data

	//memset((char*)&si_other, 0, sizeof(si_other));

	//if (signInServer(server, si_other, slen))
	//{
	//	while (1)
	//	{
	//		memset(msg, '\0', BUFLEN);
	//		memset(buf, '\0', BUFLEN);
	//		//memset((char*)&si_other, 0, sizeof(si_other));
	//		printf("Waiting for data...   ");
	//		server.RecvDatagram(buf, BUFLEN, (struct sockaddr*)&si_other1, &slen1);
	//		printf("%s ", buf);
	//		printf("\nAnswer : ");
	//		gets_s(msg, BUFLEN);
	//		server.SendDatagram(msg, (int)strlen(msg), (struct sockaddr*)&si_other1, slen1);
	//	}
	//}
	while (1)
	{
		memset(username, '\0', BUFLEN);
		memset(password, '\0', BUFLEN);
		memset(msg, '\0', BUFLEN);
		memset(buf, '\0', BUFLEN);

		printf("Waiting for username...   ");
		fflush(stdout);
		server.RecvDatagram(username, BUFLEN, (struct sockaddr*)&si_other, &slen);

		printf("Received packet from %s:%d\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));
		i = 0;
		while (i < 2)
		{
			if (strcmp(username, us[i]) == 0)
			{
				printf("Username: %s\n", username);
				server.SendDatagram(yes, (int)strlen(yes), (struct sockaddr*)&si_other, slen);
				server.RecvDatagram(password, BUFLEN, (struct sockaddr*)&si_other, &slen);
				if (strcmp(password, ps[i]) == 0)
				{
					server.SendDatagram(yes, (int)strlen(yes), (struct sockaddr*)&si_other, slen);
					printf("Everything is OK.\n");
					while (1) 
					{
						printf("Waiting for data...   ");
						server.RecvDatagram(buf, BUFLEN, (struct sockaddr*)&si_other, &slen);
						printf("%s ", buf);
						printf("\nAnswer : ");
						gets_s(msg, BUFLEN);
						server.SendDatagram(msg, (int)strlen(msg), (struct sockaddr*)&si_other, slen);
					}
				}
				else
				{
					printf("Password is not correct...   \n");
					server.SendDatagram(no, (int)strlen(no), (struct sockaddr*)&si_other, slen);
					k = 1;
					break;
				}
			}
			i++;
		}
		if (k == 0)
		{
			server.SendDatagram(no, (int)strlen(no), (struct sockaddr*)&si_other, slen);
			printf("Username is not defined!!!\n");
		}
	}
	return 0;
}
