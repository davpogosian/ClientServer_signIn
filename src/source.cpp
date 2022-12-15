#include "source.h"


bool signInServer(UDPServer server, struct sockaddr_in si_other, int slen)
{
	char username[BUFLEN];
	char password[BUFLEN];
	char yes[BUFLEN] = "yes";
	char no[BUFLEN] = "no";
	char us[2][BUFLEN] = { {"vsergoyan"}, {"elhovhan"} };
	char ps[2][BUFLEN] = { {"12345678"}, {"12345678"} };
	int i, k = 0;
		memset(username, '\0', BUFLEN);
		memset(password, '\0', BUFLEN);

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
					return true;
				}
				else
				{
					printf("Password is not correct...   \n");
					server.SendDatagram(no, (int)strlen(no), (struct sockaddr*)&si_other, slen);
					k = 1;
					return false;
				}
			}
			i++;
		}
		if (k == 0)
		{
			server.SendDatagram(no, (int)strlen(no), (struct sockaddr*)&si_other, slen);
			printf("Username is not defined!!!\n");
			return false;
		}
	return false;
}

bool signInClient(UDPSocket client_sock, struct sockaddr_in si_other, int slen)
{
	char username[BUFLEN];
	char answ[BUFLEN];
	char password[BUFLEN];
		memset(answ, '\0', BUFLEN);
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
				return true;
			}
			else
			{
				printf("Password is false!!!");
				return false;
			}
		}
		else
		{
			printf("Username is not defined");
			return false;
		}
	return false;;
}