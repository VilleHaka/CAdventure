#include <ca/networking.h>

int main() {
	WSACleanup();
	server_t* server;
	ca_server(&server,8080);
	Sleep(1000);
	ca_server_loop(server);
	closesocket(&server->winsock.socket);
	WSACleanup();
	return 0;
}