#include <ca/server_logic.h>

CA_API int init_server(server_ptr* server,int port) {
	printf("Initialising Winsock...\n");
	server_t* tmp = &server;
	tmp =  malloc(sizeof(server_t));
	tmp->player_count = 0;

	//wsa startup
	tmp->winsock.slen = sizeof(tmp->winsock.client_address);
	{
		int wsa = WSAStartup(MAKEWORD(2, 2), &tmp->winsock.wsa);
		if (wsa != 0)
		{
			printf("!\twsa startup failed. error Code : % d\n", wsa);
			return 0;
		}
		printf(".\twsa startup complete\n");
	}

	//create udp socket for client connection requests and answers
	{
		if ((tmp->winsock.udp_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET)
		{
			printf("!\tcould not create udp socket : %d\n", WSAGetLastError());
			WSACleanup();
			return 1;
		}
		printf(".\tudp socket created\n");
	}

	//prepare server address
	{
		ZeroMemory(&tmp->winsock.server_address, sizeof(tmp->winsock.server_address));
		tmp->winsock.server_address.sin_family = AF_INET;
		tmp->winsock.server_address.sin_addr.s_addr = INADDR_ANY;
		tmp->winsock.server_address.sin_port = htons(port);
	}

	//Bind tcp socket
	{
		if (bind(tmp->winsock.udp_socket, (struct sockaddr*) &tmp->winsock.server_address, sizeof(tmp->winsock.server_address)) == SOCKET_ERROR)
		{		
			printf("!\tudp bind failed with error code : %d\n", WSAGetLastError());
			closesocket(tmp->winsock.udp_socket);
			WSACleanup();
			return 1;
		}
		printf(".\tudp bind complete\n");
	}
	printf(".\twinsock init succesful\n");
	*server = tmp;
}



CA_API void	server_loop(server_t* server ) {

	char buffer[512];
	printf("\nreceiving... \n");
	while (1) {
			if (server->winsock.udp_socket != SOCKET_ERROR)
			{			
				memset(buffer, 0, 512);
				struct sockaddr_in connecting_client;
				int32_t address_length = (int32_t)sizeof(struct sockaddr_in);
				int valread = recvfrom((SOCKET)server->winsock.udp_socket, buffer, 512, 0, (struct sockaddr*) &connecting_client, &address_length);
			
				int found = 0;
				for (int i = 0; i < server->player_count; i++) {
					if (server->winsock.client_address[i].sin_addr.S_un.S_addr == connecting_client.sin_addr.S_un.S_addr) {
						printf(".\texisting player: %s\n\tmessage: %s\n", inet_ntoa(connecting_client.sin_addr),&buffer);			
						found = 1;
					}
				}
				if (!found) {
					server->winsock.client_address[server->player_count].sin_addr = connecting_client.sin_addr;
					printf(".\tnew player: %s\n\tmessage: '%s'\n", inet_ntoa(server->winsock.client_address[server->player_count].sin_addr),&buffer);	
					server->player_count++;
				}
			}
		}
}