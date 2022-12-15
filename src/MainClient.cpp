/*
	UDP Client routine
*/

#include "UDPSocket.h"
//#include "source.h"
#include <stdio.h>

int main(int argc, char* argv[])
{
	//	SOCKET s;
	struct sockaddr_in si_other;
	int slen = sizeof(si_other);

	//struct sockaddr_in si_other1;
	//int slen1 = sizeof(si_other1);

	char buf[BUFLEN];
	char message[BUFLEN];
	char username[BUFLEN];
	char answ[BUFLEN];
	char password[BUFLEN];

	unsigned short srv_port = 0;
	char srv_ip_addr[40];
	memset(srv_ip_addr, 0, 40);


	//create socket
	UDPSocket client_sock;

	//setup address structure
	memset((char*)&si_other, 0, sizeof(si_other));
	si_other.sin_family = AF_INET;

	if (1 == argc)
	{
		si_other.sin_port = htons(PORT);
		si_other.sin_addr.S_un.S_addr = inet_addr(SERVER);
		printf("1: Server - addr=%s , port=%d\n", SERVER, PORT);
	}
	else if (2 == argc)
	{
		si_other.sin_port = htons(atoi(argv[1]));
		si_other.sin_addr.S_un.S_addr = inet_addr(SERVER);
		printf("2: argv[0]: Server - addr=%s , port=%d\n", SERVER, atoi(argv[1]));
	}
	else
	{
		si_other.sin_port = htons(atoi(argv[2]));
		si_other.sin_addr.S_un.S_addr = inet_addr(argv[1]);
		printf("3: Server - addr=%s , port=%d\n", argv[1], atoi(argv[2]));
	}



	///////////////////////////////////////////////


	/*memset((char*)&si_other1, 0, sizeof(si_other1));
	si_other1.sin_family = AF_INET;

	if (1 == argc)
	{
		si_other1.sin_port = htons(PORT);
		si_other1.sin_addr.S_un.S_addr = inet_addr(SERVER);
		printf("1: Server - addr=%s , port=%d\n", SERVER, PORT);
	}
	else if (2 == argc)
	{
		si_other1.sin_port = htons(atoi(argv[1]));
		si_other1.sin_addr.S_un.S_addr = inet_addr(SERVER);
		printf("2: argv[0]: Server - addr=%s , port=%d\n", SERVER, atoi(argv[1]));
	}
	else
	{
		si_other1.sin_port = htons(atoi(argv[2]));
		si_other1.sin_addr.S_un.S_addr = inet_addr(argv[1]);
		printf("3: Server - addr=%s , port=%d\n", argv[1], atoi(argv[2]));
	}*/

	//start communication  lifecircle

	//if (signInClient(client_sock, si_other, slen))
	//{
	//	printf("OK!!!\n");
	//	while (1)
	//	{
	//		memset(buf, '\0', BUFLEN);
	//		memset(message, '\0', BUFLEN);
	//		printf("Enter message: ");
	//		gets_s(message, BUFLEN);
	//		client_sock.SendDatagram(message, (int)strlen(message), (struct sockaddr*)&si_other1, slen1);
	//		client_sock.RecvDatagram(buf, BUFLEN, (struct sockaddr*)&si_other1, &slen1);
	//		printf("Answer: %s\n", buf);
	//	}
	//}
	while (1)
	{
		memset(answ, '\0', BUFLEN);
		memset(buf, '\0', BUFLEN);
		memset(message, '\0', BUFLEN);
		memset(username, '\0', BUFLEN);
		printf("\nEnter username : ");
		gets_s(username, BUFLEN);

		client_sock.SendDatagram(username, (int)strlen(username), (struct sockaddr*)&si_other, slen);

		client_sock.RecvDatagram(answ, BUFLEN, (struct sockaddr*)&si_other, &slen);
		if (strcmp(answ, "yes") == 0)
		{
			printf("\nEnter password : ");
			gets_s(password, BUFLEN);
			client_sock.SendDatagram(password, (int)strlen(password), (struct sockaddr*)&si_other, slen);
			memset(answ, '\0', BUFLEN);
			client_sock.RecvDatagram(answ, BUFLEN, (struct sockaddr*)&si_other, &slen);
			if (strcmp(answ, "yes") == 0)
			{
				printf("OK!!!\n");
				while (1)
				{
					printf("Enter message: ");
					gets_s(message, BUFLEN);
					client_sock.SendDatagram(message, (int)strlen(message), (struct sockaddr*)&si_other, slen);
					client_sock.RecvDatagram(buf, BUFLEN, (struct sockaddr*)&si_other, &slen);
					printf("Answer: %s\n", buf);
				}
			}
			else
			{
				printf("Password is false!!!");
			}
		}
		else
		{
			printf("Username is not defined");
		}
	}
	return 0;
}