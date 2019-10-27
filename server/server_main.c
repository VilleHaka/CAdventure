#include <ca/server_logic.h>

int main() {
	WSACleanup();
	server_t* server;
	init_server(&server,8080);
	int sending = 0;
	char buf[512];// = (char*)calloc(10, sizeof(char));
	Sleep(2000);
	int* log;
	SOCKET client_sock = SOCKET_ERROR;
	//server->threads.thread_handles[0] = CreateThread(NULL, 0, &listen_thread, (void*)server->winsock.tcp_socket, 0,&server);
	listen_on_clients(server);
	//WaitForSingleObject(server->threads.thread_handles, INFINITE);
	//WaitForMultipleObjects(3, &server->threads.thread_handles, 1, INFINITE);
	//printf("Waiting for connections... \n");
	
	//while(1) {
	/*if (listen(server->winsock.listen, 1) == SOCKET_ERROR) {
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
	printf("Connection accepted! hozaah\n");*/

	/*while (1) {
		memset(buf, NULL, 512);

		listen(server->winsock.socket, SOMAXCONN);
		if (recvfrom(server->winsock.socket, buf, 512, 0, &server->winsock.si_other, &server->winsock.slen) == SOCKET_ERROR) {
			printf("receiving failed\n");
		}
		 
		printf("\nReceived packet from %s:%d\n", inet_ntoa(server->winsock.si_other.sin_addr), ntohs(server->winsock.si_other.sin_port));
		printf("Data: %s\n", buf);
		Sleep(300);
	}*/
	closesocket(&server->winsock.tcp_socket);
	closesocket(&server->winsock.udp_socket);
	WSACleanup();
	return 0;
}