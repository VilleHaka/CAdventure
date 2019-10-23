#include <ca/server_logic.h>

int main() {
	server_t* server;
	init_server(&server,7777);
	
	while (1) {
	}

	closesocket(server->winsock.socket);
	WSACleanup();
	return 0;
}