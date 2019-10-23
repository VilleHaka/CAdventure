#include <ca/server_logic.h>

int init_server(server_ptr* server,int port) {
	server_t* tmp = malloc(sizeof(server_t));
	tmp->player_count = 0;

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
		if ((tmp->winsock.socket = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)
		{
			printf("Could not create socket : %d\n", WSAGetLastError());
		}
		printf("Socket created.\n");
	}
	
	//prepare socketaddr_in
	{
		tmp->winsock.server.sin_family = AF_INET;
		tmp->winsock.server.sin_addr.s_addr = INADDR_ANY;
		tmp->winsock.server.sin_port = htons(port);
	}

	//Bind socket
	{
		if (bind(tmp->winsock.socket, (struct sockaddr*) &tmp->winsock.server, sizeof(tmp->winsock.server)) == SOCKET_ERROR)
		{
			printf("Bind failed with error code : %d\n", WSAGetLastError());
			return 0;
		}
		printf("Bind done\n");
	}

	*server = tmp;
}