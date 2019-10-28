#include <ca/networking.h>

int main() {
	WSACleanup();
	server_t* server;
	ca_server(&server,7777);
	Sleep(1000);
	ca_server_loop(server);
	closesocket(&server->winsock.read_socket);
	closesocket(&server->winsock.write_socket);
	WSACleanup();
	return 0;
}