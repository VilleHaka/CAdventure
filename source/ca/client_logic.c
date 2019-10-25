#include <ca/client_logic.h>
#include <time.h>

CA_API int init_client(client_ptr* client, const char* address, int port, const char* player_name) {
	client_t* tmp = malloc(sizeof(client_t));
	tmp->player_id = player_name;
	
	//winsock init
	tmp->winsock.slen = sizeof(tmp->winsock.si_other);
	{
		printf("\nInitialising Winsock...\n");
		if (WSAStartup(MAKEWORD(2, 2), &tmp->winsock.wsa) != 0)
		{
			printf("Failed.Error Code : % d\n", WSAGetLastError());
			return 0;
		}
		printf("Initialised.\n");
	}

	//create socket
	{
		if ((tmp->winsock.socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
		{
			printf("Could not create socket : %d\n", WSAGetLastError());
		}
		printf("Socket created.\n");
	}
	
	//prepare si_other
	{
		memset((char*)& tmp->winsock.si_other, 0, sizeof(tmp->winsock.si_other));
		tmp->winsock.si_other.sin_family = AF_INET;
		tmp->winsock.si_other.sin_port = htons(port);
		tmp->winsock.si_other.sin_addr.S_un.S_addr = inet_addr(address);
	}
	time_t start;
	//connect to server
	{
		start = clock();
		printf("\nconnecting to: %s:%i...\n", address,port);

		int cres = 99;
		while(1)
		{
			cres = connect(tmp->winsock.socket, (SOCKADDR*)& tmp->winsock.si_other, sizeof(tmp->winsock.si_other));
			if (cres == 0) break;
			else {
				printf("... \tconnection failed with error: %ld\n", WSAGetLastError());
				Sleep(2000);
			}
			
			if ((clock() - start)/1000 > 25) { 
				closesocket(tmp->winsock.socket);
				WSACleanup();
				printf("... \ttimed out :(\n");
				return 0; 
			}
		}
	}
	printf("Connection successful.\n");
	Sleep(2000);
	*client = tmp;
}