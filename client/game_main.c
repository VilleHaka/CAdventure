#include <ca/cadventure.h>
#include <ca/game_logic.h>
#include <ca/console.h>
#include <ca/client_logic.h>

#include <time.h>

int main() {
	WSACleanup();
	console_t* console;
	init_console(&console,L"Consolas", "C Proto");

	client_t* client;
	init_client(&client, "127.0.0.1", 8080,"perse");
	
	const char* texts[2] = { "C PROTO","hello world"};
	clock_t start, end;
	double el = 0;
	int sending = 0;
	while (1) {
		start = clock();
		//memset(console->console_buffer, 0, WIDTH * HEIGHT*sizeof(CHAR_INFO));

		if (GetAsyncKeyState(VK_F1) && !sending) {
			if (sendto(client->winsock.udp_socket, "perse", strlen("perse"), 0, (struct sockaddr*)&client->winsock.ReceiverAddr, &client->winsock.slen) == SOCKET_ERROR) {
				printf("send failed %d\n",WSAGetLastError());
			}
			else printf("sent :)\n");
			
			sending = 1;		
		}
		else if (!GetAsyncKeyState(VK_F1) && sending) sending = 0;
	
		for (int i = 0; i < (strlen(texts[1]) + 2); i++) {
			draw_pixel(console, (int2_t) { WIDTH / 2 - ((strlen(texts[1]) / 2) + 1) + i, HEIGHT / 2 - 1 }, BG_DARK_GREY | FG_BLACK, PIXEL_QUARTER);
			if(i < 2) draw_text(console, (int2_t) { WIDTH / 2 - strlen(texts[i]) / 2, HEIGHT / 2 + i }, texts[i], BG_GREY | FG_BLACK);
			draw_pixel(console, (int2_t) { WIDTH / 2 - ((strlen(texts[1]) / 2) + 1) + i, HEIGHT / 2 + 2 }, BG_DARK_GREY | FG_BLACK, PIXEL_QUARTER);
		}
	
	//	draw_console(console);
		end = clock();
	}
	closesocket(client->winsock.udp_socket);
	WSACleanup();
	return 0;
}