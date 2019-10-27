#include <ca/server_logic.h>

CA_API int init_server(server_ptr* server,int port) {
	printf("Initialising Winsock...\n...\t");
	server_t* tmp = malloc(sizeof(server_t));
	tmp->player_count = 0;

	
	//init udp sockets
	for (int i = 0; i < 10; i++) tmp->winsock.udp_socket[i] = 0;

	//wsa init
	tmp->winsock.slen = sizeof(tmp->winsock.client_address);
	{
		if (WSAStartup(MAKEWORD(2, 2), &tmp->winsock.wsa) != 0)
		{
			printf("wsa startup failed. error Code : % d\n", WSAGetLastError());
			return 0;
		}
		printf("wsa startup complete\n...\t");
	}

	//create tcp socket for client connection requests and answers
	{
		if ((tmp->winsock.tcp_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
		{
			printf("could not create tcp socket : %d\n", WSAGetLastError());
			WSACleanup();
			return 1;
		}
		printf("tcp socket created\n...\t");
	}
	//{
	//	ZeroMemory(&tmp->winsock.hints, sizeof(tmp->winsock.hints));
	//	tmp->winsock.hints.ai_family = AF_INET;
	//	tmp->winsock.hints.ai_socktype = SOCK_STREAM;
	//	tmp->winsock.hints.ai_protocol = IPPROTO_TCP;
	//	tmp->winsock.hints.ai_flags = AI_PASSIVE;
	//}
	

	////create udp socket for data transfer
	//{
	//	if ((tmp->winsock.udp_socket = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)
	//	{
	//		printf("Could not create udp socket : %d\n", WSAGetLastError());
	//	}
	//	printf("udp socket created\n...\t");
	//}

	//prepare server address
	{
		tmp->winsock.server_address.sin_family = AF_INET;
		tmp->winsock.server_address.sin_addr.s_addr = INADDR_ANY;
		tmp->winsock.server_address.sin_port = htons(port);
	}


	//resolve server addresses

	//{
	//	//ZeroMemory(&tmp->winsock.result, sizeof(tmp->winsock.result));
	//	DWORD ress = getaddrinfo(NULL, port, &tmp->winsock.hints, &tmp->winsock.result);
	//	if (ress == SOCKET_ERROR) {
	//		printf("getaddrinfo failed with error: %d\n", WSAGetLastError());
	//		WSACleanup();
	//		return 1;
	//	}
	//}



	//Bind tcp socket
	{
		if (bind(tmp->winsock.tcp_socket, (struct sockaddr*) &tmp->winsock.server_address, sizeof(tmp->winsock.server_address)) == SOCKET_ERROR)
		{		
			printf("tcp bind failed with error code : %d\n", WSAGetLastError());
			closesocket(tmp->winsock.tcp_socket);
			WSACleanup();
			return 1;
		}
		printf("tcp bind complete\n...\t");
	}

	

	////prepare server address
	//{
	//	port += 1;
	//	tmp->winsock.server_address.sin_family = AF_INET;
	//	tmp->winsock.server_address.sin_addr.s_addr = INADDR_ANY;
	//	tmp->winsock.server_address.sin_port = htons(port);
	//}
	////Bind udp socket
	//{
	//	if (bind(tmp->winsock.udp_socket, (struct sockaddr*) & tmp->winsock.server_address, sizeof(tmp->winsock.server_address)) == SOCKET_ERROR)
	//	{
	//		closesocket(tmp->winsock.tcp_socket);
	//		WSACleanup();
	//		printf("udp bind failed with error code : %d\n", WSAGetLastError());
	//		return 0;
	//	}
	//	printf("udp bind complete\n...\t");
	//}

	printf("winsock init succesful\n");
	*server = tmp;
}

CA_API unsigned __stdcall  listen_thread(void* data) {
	server_t *server = (server_t*)data;
	listen_on_clients(server);
}


CA_API void listen_on_clients(server_t* server) {
	printf("Waiting for connections... \n");
	listen(server->winsock.tcp_socket, 1);
	//if (listen(server->winsock.tcp_socket, 1) == SOCKET_ERROR) {
	//	printf("listen failed with error: %ld\n", WSAGetLastError());
	//	closesocket(server->winsock.tcp_socket);
	//	WSACleanup();
	//	Sleep(3000);
	//	return 0;
	//}

	SOCKET accept_socket = accept(server->winsock.tcp_socket, &server->winsock.client_address, NULL);
	{
		if (accept_socket == INVALID_SOCKET) {
			printf("Accepted connection.. but failed :( error code: &ld\n", WSAGetLastError());
			closesocket(server->winsock.tcp_socket);
			WSACleanup();
		}
		else {
			sendto(accept_socket, server->winsock.udp_socket[server->player_count], sizeof(server->winsock.udp_socket[server->player_count]), NULL, &server->winsock.client_address, sizeof(server->winsock.udp_socket[server->player_count]));
		}
	}

	printf("Connection accepted! hozaah\n");
	server->player_count++;
	//server->threads.thread_handles[1] = CreateThread(NULL, 0, &client_thread, (void*)server->winsock.socket, 0, server);
	/*SOCKET client_sock = SOCKET_ERROR;
	if(client_sock = accept(server->winsock.socket, NULL, NULL) != SOCKET_ERROR) {
		unsigned thread_id;
		CreateThread(NULL, 0, &client_session, (void*)sclient_sock, 0, server);
	}*/
	listen_on_clients(server);


	//printf("Waiting for connections... \n");
	///*if (listen(server->winsock.listen, 1) == SOCKET_ERROR) {
	//	printf("listen failed with error: %ld\n", WSAGetLastError());
	//	closesocket(server->winsock.listen);
	//	WSACleanup();
	//	Sleep(3000);
	//	return 0;
	//}*/

	//char buf[512];

	////int ready_socket,max_sock;
	////fd_set set;
	////FD_ZERO(&set);
	////max_sock = max(server->winsock.tcp_socket, server->winsock.udp_socket) + 1;

	//SOCKET accept_socket;
	//while (1) {
	//	listen(server->winsock.tcp_socket, 3);
	///*	accept_socket = accept(server->winsock.tcp_socket, (struct sockaddr*) & server->winsock.server_address, NULL);*/
	//	if (accept(server->winsock.tcp_socket, (struct sockaddr*) & server->winsock.client_address, NULL) != SOCKET_ERROR)printf("connected\n");
	//}
	//while (1) {
	//	//
	//	//FD_SET(server->winsock.tcp_socket, &set);
	/////	FD_SET(server->winsock.udp_socket, &set);
	//	
	//
	//	//ready_socket = select(max_sock, &set, NULL, NULL, NULL);
	//	
	//	//if (FD_ISSET(server->winsock.tcp_socket, &set)) {		
	//	//	//SOCKET accept_socket = accept(server->winsock.tcp_socket, (SOCKADDR*)& server->winsock.server_address, &server->winsock.slen);
	//	//	

	//	//}
	//	//if (FD_ISSET(server->winsock.udp_socket, &set)) {
	//	//	
	//	//	//int accept_socket = accept(server->winsock.udp_socket, (SOCKADDR*)& server->winsock.client_address, &server->winsock.slen);
	//	//	int br = recvfrom(server->winsock.udp_socket, buf, 512, 0, (SOCKADDR*)& server->winsock.udp_socket, &server->winsock.slen);
	//	//	if (br > 0)printf("connected\n");

	//	//}
	//	/*int br = recvfrom(server->winsock.socket, buf,512, 0, (SOCKADDR*)& server->winsock.server, &server->winsock.slen);
	//	if (printf("%i\n",recvfrom(server->winsock.socket, buf, 512, 0, (SOCKADDR*)& server->winsock.server, &server->winsock.slen))) {*/
	//		
	//		////Get client information
	//		//{
	//		//	getsockname(server->winsock.socket, (SOCKADDR*)& server->winsock.server, (int*)sizeof(server->winsock.server));
	//		//	printf("Server: Receiving IP(s) used : % s\n", inet_ntoa(server->winsock.server.sin_addr));

	//		//	printf("Server: Receiving port used : % d\n", htons(server->winsock.server.sin_port));

	//		//	printf("Server: I\'m ready to receive a datagram...\n");
	//		//	break;
	//		//}
	//		
	//	//}

	//}
	////server->winsock.socket = accept(server->winsock.socket, NULL, NULL);
	//{
	//	if (server->winsock.socket == INVALID_SOCKET) {
	//		printf("Accepted connection.. but failed :( error code: &ld\n", WSAGetLastError());
	//		closesocket(server->winsock.socket);
	//		WSACleanup();
	//	}
	//}
	//printf("Connection accepted! hozaah\n");
	//server->threads.thread_handles[1] = CreateThread(NULL, 0, &client_thread, (void*)server->winsock.socket, 0, server);
	/*SOCKET client_sock = SOCKET_ERROR;
	if(client_sock = accept(server->winsock.socket, NULL, NULL) != SOCKET_ERROR) {
		unsigned thread_id;
		CreateThread(NULL, 0, &client_session, (void*)sclient_sock, 0, server);
	}*/
	
}

CA_API unsigned __stdcall  client_thread(void* data) {
	server_t *client = (server_t*)data;
	printf("perse\n");
	
}