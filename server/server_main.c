#include <ca/server_logic.h>

int main() {
	WSACleanup();
	server_t* server;
	init_server(&server,8080);
	Sleep(2000);
	server_loop(server);
	closesocket(&server->winsock.udp_socket);
	WSACleanup();
	return 0;
}