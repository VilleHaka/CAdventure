#include <ca/server_logic.h>

CA_API int init_server(server_ptr* server,int port) {
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
		if ((tmp->winsock.listen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
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
		if (bind(tmp->winsock.listen, (struct sockaddr*) &tmp->winsock.server, sizeof(tmp->winsock.server)) == SOCKET_ERROR)
		{		
			closesocket(tmp->winsock.listen);
			WSACleanup();
			printf("Bind failed with error code : %d\n", WSAGetLastError());
			return 0;
		}
		printf("Bind done\n");
	}

	printf("Init succesful\n");
	*server = tmp;
}

CA_API unsigned __stdcall  listen_thread(void* data) {
	server_t *server = (server_t*)data;
	listen_on_clients(&server);
}


CA_API void listen_on_clients(server_t* server) {
	printf("Waiting for connections... \n");
	if (listen(server->winsock.listen, 1) == SOCKET_ERROR) {
		printf("listen failed with error: %ld\n", WSAGetLastError());
		closesocket(server->winsock.listen);
		WSACleanup();
		Sleep(3000);
		return 0;
	}

	server->winsock.socket = accept(server->winsock.listen, NULL, NULL);
	{
		if (server->winsock.socket == INVALID_SOCKET) {
			printf("Accepted connection.. but failed :( error code: &ld\n", WSAGetLastError());
			closesocket(server->winsock.listen);
			WSACleanup();
		}
	}
	printf("Connection accepted! hozaah\n");
	server->threads.thread_handles[1] = CreateThread(NULL, 0, &client_thread, (void*)server->winsock.socket, 0, server);
	/*SOCKET client_sock = SOCKET_ERROR;
	if(client_sock = accept(server->winsock.socket, NULL, NULL) != SOCKET_ERROR) {
		unsigned thread_id;
		CreateThread(NULL, 0, &client_session, (void*)sclient_sock, 0, server);
	}*/
	listen_on_clients(&server);
}

CA_API unsigned __stdcall  client_thread(void* data) {
	server_t *client = (server_t*)data;
	printf("perse\n");
	
}