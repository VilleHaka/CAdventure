#include <ca/server_logic.h>

int main() {
	server_t* server;
	init_server(&server,8080);
	int sending = 0;
	char buf[512];
	Sleep(2000);
	while (1) {
		system("cls");
		printf("Waiting for data... ");
	

		/*memset(buf, NULL, 512);*/
		
		if (server->winsock.recv_len = recvfrom(server->winsock.socket, buf, 512, 0, (struct sockaddr*) & server->winsock.si_other, &server->winsock.slen) == SOCKET_ERROR) {
			printf("receiving failed\n");
		}

		printf("Received packet from %s: %d\n", inet_ntoa(server->winsock.si_other.sin_addr), ntohs(server->winsock.si_other.sin_port));
		printf("Data: % s\n", buf);
		Sleep(2000);
		/*if (GetAsyncKeyState(VK_F1) && !sending) {
			
			printf("sent :)\n");
			sending = 1;
		}
		else if (!GetAsyncKeyState(VK_F1) && sending) sending = 0;*/

	}

	closesocket(server->winsock.socket);
	WSACleanup();
	return 0;
}