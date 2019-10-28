#include <ca/cadventure.h>
#include <ca/game_logic.h>
#include <ca/console.h>
#include <ca/networking.h>

#include <time.h>

int main() {
	WSACleanup();
	client_t* client;
	ca_client(&client, "127.0.0.1", 7777, "anus");

	console_t* console;
	init_console(&console,L"Consolas", "C Proto");

	const char* texts[3] = { "C PROTO","hello world","sent message"};
	clock_t start, end;
	double el = 0;
	int sending = 0;
	while (1) {
		start = clock();
		memset(console->console_buffer, 0,console->scr.cbSize);
		
		for (int i = 0; i < (strlen(texts[1]) + 2); i++) {
			draw_pixel(console, (int2_t) { WIDTH / 2 - ((strlen(texts[1]) / 2) + 1) + i, HEIGHT / 2 - 1 }, BG_DARK_GREY | FG_BLACK, PIXEL_QUARTER);
			if(i < 2) draw_text(console, (int2_t) { WIDTH / 2 - strlen(texts[i]) / 2, HEIGHT / 2 + i }, texts[i], BG_GREY | FG_BLACK);
			draw_pixel(console, (int2_t) { WIDTH / 2 - ((strlen(texts[1]) / 2) + 1) + i, HEIGHT / 2 + 2 }, BG_DARK_GREY | FG_BLACK, PIXEL_QUARTER);
		}
	
		if (GetAsyncKeyState(VK_F1) && !sending) {
			if (sendto(client->winsock.socket, "perse", strlen("perse"), 0, (struct sockaddr*) & client->winsock.this_address, sizeof(struct sockaddr_in)) == SOCKET_ERROR) {
				draw_text(console, (int2_t) {0, 0 }, TEXT("send failed %i", WSAGetLastError()), BG_WHITE | FG_BLACK);
			}
			else draw_text(console, (int2_t) { 0, 0}, texts[2], BG_WHITE | FG_BLACK);

			sending = 1;
		}
		else if (!GetAsyncKeyState(VK_F1) && sending) sending = 0;
		
		if (sending == 1)draw_console(console),Sleep(2000);
		else draw_console(console);

		end = clock();
	}
	closesocket(client->winsock.socket);

	WSACleanup();
	return 0;
}