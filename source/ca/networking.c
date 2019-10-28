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
	if ((netw->write_socket = socket(AF_INET, socket_type,protocol)) == INVALID_SOCKET)
	{
		printf("!\tcould not create write_socket : %d\n", WSAGetLastError());
		WSACleanup();
		return 1;
	}
	if ((netw->read_socket = socket(AF_INET, socket_type, protocol)) == INVALID_SOCKET)
	{
		printf("!\tcould not create read_socket : %d\n", WSAGetLastError());
		WSACleanup();
		return 1;
	}
	printf(".\tsockets created\n");
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
	if (bind(netw->read_socket, (struct sockaddr*) & netw->this_address, (int32_t)sizeof(struct sockaddr_in)) == SOCKET_ERROR)
	{
		printf("!\tsocket bind failed with error code : %d\n", WSAGetLastError());
		closesocket(netw->write_socket);
		WSACleanup();
		return 1;
	}
	printf(".\tsocket bind complete\n");	
	Sleep(100);
	return 0;
}

CA_API int ca_network(network_t* network, long address, int port, int socket_type) {
	int is_server = address == ADDR_ANY ? 1 : 0;
	if (!ca_wsa(network) && !ca_socket(network, socket_type,socket_type == SOCK_DGRAM ? IPPROTO_UDP : IPPROTO_TCP) && !ca_address(network, address, port) && !ca_bind_socket(network)) {
		//if (is_server)!ca_bind_socket(network);
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
	printf("network ready\n");
	*server = tmp;
}

CA_API void	ca_server_loop(server_t* server ) {

	char buffer[512];
	printf("\nreceiving... \n");
	while (1) {
			if (server->winsock.write_socket != SOCKET_ERROR)
			{						
				memset(buffer, 0, 512);
				struct sockaddr_in connecting_client;
				int32_t address_length = (int32_t)sizeof(struct sockaddr_in);
				int valread = recvfrom((SOCKET)server->winsock.read_socket, buffer, 512, 0, (struct sockaddr*) &connecting_client, &address_length);
				int found = 0;
				for (int i = 0; i < server->player_count; i++) {
					if (server->clients[i].sin_addr.S_un.S_addr == connecting_client.sin_addr.S_un.S_addr) {
						printf(".\texisting player: %s\n\tmessage: '%s'\n", inet_ntoa(connecting_client.sin_addr),&buffer);			
						found = 1;
					}
				}
				if (!found) {
					server->clients[server->player_count].sin_addr = connecting_client.sin_addr;
					printf(".\tnew player: %s\n\tname: '%s'\n", inet_ntoa(server->clients[server->player_count].sin_addr),&buffer);
					sendto((SOCKET)server->winsock.write_socket, "homo", strlen("homo"), 0, (struct sockaddr*) & connecting_client.sin_addr, sizeof(connecting_client.sin_addr));
					printf(".\treplying back...\n");								
					
					server->player_count++;
				}
			}
		}
}

CA_API int ca_client(client_ptr* client, const char* address, int port, const char* player_name) {
	printf("CLIENT\ninitialising winsock...\n");
	client_t* tmp = &client;
	tmp = (client_t*)malloc(sizeof(client_t));
	tmp->player_id = player_name;
	ca_network(&tmp->winsock, address, port, SOCK_DGRAM);
	 
	int32_t address_length = (int32_t)sizeof(struct sockaddr_in);
	printf("handshaking server at %s:%i..\n", address, port);
	
	struct sockaddr_in rec;
	int nMode = 1; // 1: NON-BLOCKING
	if (ioctlsocket(tmp->winsock.write_socket, FIONBIO, &nMode) == SOCKET_ERROR)
	{
		printf("!\tnon-blocking failed with error %d\n",WSAGetLastError());
		closesocket(tmp->winsock.write_socket);
		WSACleanup();
		return nMode;
	}
	char buff[512];
		while (1) {
			memset(buff, NULL, 512);
			int siz = sendto((SOCKET)tmp->winsock.write_socket, tmp->player_id, strlen(tmp->player_id),0, (struct sockaddr*) & tmp->winsock.this_address, &address_length);
			printf("send.. %i\n", siz);
			int r = recvfrom((SOCKET)tmp->winsock.read_socket, buff, 512, 0, (struct sockaddr*) & rec, &address_length);
			printf("%s\n", &buff);
			if (buff != "homo") {
				printf("!\tfailed, error %d.. retrying\n", WSAGetLastError());
				Sleep(2000);
				continue;
			}
			printf(".\treceiving handshake ok\n");
			break;
		}
		
	
	printf("connection ok\n");
	Sleep(2000);
	*client = tmp;
}


