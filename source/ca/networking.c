#include <ca/networking.h>

CA_API int ca_wsa(network_t* netw){
	int wsa = WSAStartup(MAKEWORD(2, 2), &netw->wsa);
	if (wsa != 0) {
		printf("!\twsa startup failed. error Code : % d\n", wsa);
		return 1;
	}
	printf(".\twsa startup complete\n");
	Sleep(100);
	return 0;
}

CA_API int ca_socket(network_t* netw,int socket_type){
	if ((netw->socket = socket(AF_INET, socket_type,0)) == INVALID_SOCKET)
	{
		printf("!\tcould not create socket : %d\n", WSAGetLastError());
		WSACleanup();
		return 1;
	}
	printf(".\tsocket created\n");
	Sleep(100);
	return 0;
}

CA_API int ca_address(network_t* netw, const char* address, int port) {
	//prepare address
	ZeroMemory(&netw->this_address, (int32_t)sizeof(struct sockaddr_in));
	netw->this_address.sin_family = AF_INET;
	netw->this_address.sin_addr.s_addr = address == ADDR_ANY ? ADDR_ANY : inet_addr(address);
	netw->this_address.sin_port = htons(port);
	printf(".\tserver port set to %i\n", port);
	Sleep(100);
	return 0;
}

CA_API int	ca_bind_socket(network_t* netw) {
	if (bind(netw->socket, (struct sockaddr*) & netw->this_address, (int32_t)sizeof(struct sockaddr_in)) == SOCKET_ERROR)
	{
		printf("!\tsocket bind failed with error code : %d\n", WSAGetLastError());
		closesocket(netw->socket);
		WSACleanup();
		return 1;
	}
	printf(".\tsocket bind complete\n");	
	Sleep(100);
	return 0;
}

CA_API int ca_network(network_t* network, long address, int port, int socket_type) {
	int is_server = address == ADDR_ANY ? 1 : 0;
	if (!ca_wsa(network) && !ca_socket(network, socket_type) && !ca_address(network, address, port)) {
		if (is_server)!ca_bind_socket(network);
		printf(".\twinsock init succesful\n");
		return 0;
	}
	return 1;
}

CA_API int ca_server(server_ptr* server,int port) {
	printf("initialising winsock...\n");
	server_t* tmp = &server;
	tmp =  malloc(sizeof(server_t));
	tmp->player_count = 0;
	ca_network(&tmp->winsock,ADDR_ANY,port,SOCK_DGRAM);
	printf("network ready\n");
	*server = tmp;
}

CA_API void	ca_server_loop(server_t* server ) {

	char buffer[512];
	printf("\nreceiving... \n");
	while (1) {
			if (server->winsock.socket != SOCKET_ERROR)
			{			
				memset(buffer, 0, 512);
				struct sockaddr_in connecting_client;
				int32_t address_length = (int32_t)sizeof(struct sockaddr_in);
				int valread = recvfrom((SOCKET)server->winsock.socket, buffer, 512, 0, (struct sockaddr*) &connecting_client, &address_length);
			
				int found = 0;
				for (int i = 0; i < server->player_count; i++) {
					if (server->clients[i].sin_addr.S_un.S_addr == connecting_client.sin_addr.S_un.S_addr) {
						printf(".\texisting player: %s\n\tmessage: '%s'\n", inet_ntoa(connecting_client.sin_addr),&buffer);			
						found = 1;
					}
				}
				if (!found) {
					server->clients[server->player_count].sin_addr = connecting_client.sin_addr;
					printf(".\tnew player: %s\n\tmessage: '%s'\n", inet_ntoa(server->clients[server->player_count].sin_addr),&buffer);	
					server->player_count++;
				}
			}
		}
}

CA_API int ca_client(client_ptr* client, const char* address, int port, const char* player_name) {
	client_t* tmp = &client;
	tmp = (client_t*)malloc(sizeof(client_t));
	tmp->player_id = player_name;
	ca_network(&tmp->winsock, address, port, SOCK_DGRAM);

	Sleep(1000);
	*client = tmp;
}


