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

CA_API int ca_socket(network_t* netw,int socket_type,int protocol){
	if ((netw->socket = socket(AF_INET, socket_type,protocol)) == INVALID_SOCKET)
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
	if (!ca_wsa(network) && !ca_socket(network, socket_type,0) && !ca_address(network, address, port)) {
		if (is_server)!ca_bind_socket(network);
		printf(".\twinsock init succesful\n");
		return 0;
	}
	return 1;
}

CA_API int ca_server(server_ptr* server,int port) {
	printf("SERVER\ninitialising winsock...\n");
	server_t* tmp = &server;
	tmp =  malloc(sizeof(server_t));
	tmp->player_count = 0;
	ca_network(&tmp->winsock,ADDR_ANY,port,SOCK_DGRAM);

	*server = tmp;
}

CA_API void	ca_server_loop(server_t* server ) {

	char* buffer = malloc(MAN_SIZE);
	while (1) {
		system("cls");
		printf("\nreceiving... \n");
		

			memset(buffer, 0, MAN_SIZE);
			if (server->winsock.socket != SOCKET_ERROR)
			{								
				struct sockaddr_in connecting_client;
				int32_t address_length = (int32_t)sizeof(struct sockaddr_in);
				recvfrom((SOCKET)server->winsock.socket, buffer, MAN_SIZE, 0, (struct sockaddr*) &connecting_client, &address_length);
				//printf("%i\n", valread);
				int found = 0;
				for (int i = 0; i < server->player_count; i++) {
					if (server->clients[i].sin_addr.S_un.S_addr == connecting_client.sin_addr.S_un.S_addr) {				
						man_ptr manif = (man_ptr)buffer;			
						printf(".\texisting client: %s\n\tname: %s uptime: %f command: %s\n", inet_ntoa(connecting_client.sin_addr),manif->name,manif->uptime,manif->command);

						strcpy(&manif->command, "");
				
                        sendto((SOCKET)server->winsock.socket, manif, MAN_SIZE, 0, (struct sockaddr*) & connecting_client, &address_length);
						found = 1;
					}
				}
				if (!found) {				
					server->clients[server->player_count].sin_addr = connecting_client.sin_addr;
					printf(".\tnew client: %s\n\tdata: '%s'\n", inet_ntoa(server->clients[server->player_count].sin_addr),buffer);
					sendto((SOCKET)server->winsock.socket, &buffer, sizeof(buffer), 0, (struct sockaddr*) & connecting_client, &address_length);
					printf(".\treplying back...\n");								
					
					server->player_count++;
					Sleep(POLL_TIME*9);
				}
			}
			Sleep(POLL_TIME);
		}
}

CA_API int ca_client(client_ptr* client, const char* address, int port, char* player_name) {
	printf("CLIENT\ninitialising winsock...\n");
	client_t* tmp = &client;
	tmp = (client_t*)malloc(sizeof(client_t));
	strcpy(tmp->mani.name,player_name);

	ca_network(&tmp->winsock, address, port, SOCK_DGRAM); 
	int32_t address_length = (int32_t)sizeof(struct sockaddr_in);
	printf("handshake to server at %s:%i..\n", address, port);
	
	struct sockaddr_in rec;
	
	const char* greet = "wank";
	char* check = malloc(strlen(greet) * sizeof(char));
		while (1) {		
			memset(&check, NULL, 5);
			int siz = sendto((SOCKET)tmp->winsock.socket, greet, strlen(greet),0, (struct sockaddr*) & tmp->winsock.this_address, &address_length);
			int r = recvfrom((SOCKET)tmp->winsock.socket, check, strlen(greet), 0, (struct sockaddr*) & rec, &address_length);

			if (r == -1) {
				printf("!\tfailed, error %d.. retrying\n", WSAGetLastError());
				Sleep(4000);
				continue;
			}
			printf(".\treceived handshake\n");
			break;
		}
	tmp->mani.start_time = clock();
	printf("connection ok\n");
	Sleep(2000);
	*client = tmp;
}

CA_API void	ca_client_loop(client_t* client) {
	client->mani.uptime = (clock() - client->mani.start_time) / 1000;
	struct sockaddr* rec;
	char* buf = (char* )malloc(MAN_SIZE);
	memset(buf, 0, MAN_SIZE);
	while (1) {
		Sleep(POLL_TIME);
		int se = sendto((SOCKET)client->winsock.socket, (man_t*)&client->mani, MAN_SIZE, 0, (struct sockaddr*) & client->winsock.this_address, (int32_t)sizeof(struct sockaddr_in));
		int re = recvfrom((SOCKET)client->winsock.socket, buf, MAN_SIZE, 0, 0, 0);
		if (re != -1) break;
	}
	man_ptr yes = (man_ptr)buf;
	memcpy(&client->mani, &yes, 1024);
}