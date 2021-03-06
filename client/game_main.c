#include <ca/cadventure.h>
#include <ca/game_logic.h>
#include <ca/console.h>
#include <ca/networking.h>

#include <time.h>


/* 
			uint8_t mem [1024] = {0};
			memcpy (mem, &header, 24);
			memcpy (mem + 24, &data, sizeof (fcs_data_t));

			uint32_t writen = 0;
			ruska_socket_send_to (socket, mem, sizeof (fcs_data_t) + 24, &writen, address, port);
*/

void Login(client_t* client)
{
    char ip[20];
    char name[20];
    char port[4];
    printf("Welcome to the game sir!\nGive us some info we need to get you connected!\n");
    printf("Ip address: ");
    gets(ip);
    printf("Port: ");
    gets(port);
    printf("Username: ");
    gets(name);
    printf("Connecting to ip %s:%s.", ip, port);
    printf("\nLogging in\n");
    ca_client(client, ip, atoi(port), name);
}

int main() {
 
	WSACleanup();
	client_t* client;
	ca_client(&client, "127.0.0.1", 8080, "anus");

   // Login(&client);

	 //77.223.41.27, 7777 // ville's IP addresso


	console_t* console;
	init_console(&console,L"Consolas", "C Proto");

	const char* texts[3] = { "C PROTO","hello world","sent message"};
	clock_t start, end;
	double el = 0;
	int sending = 0;
	double elapsed = 0;
	while (1) {
		memset(console->console_buffer, 0,console->scr.cbSize);
		client->mani.uptime = (double)(clock() - client->mani.start_time);

		
		for (int i = 0; i < (strlen(texts[1]) + 2); i++) {
			draw_pixel(console, (int2_t) { WIDTH / 2 - ((strlen(texts[1]) / 2) + 1) + i, HEIGHT / 2 - 1 }, BG_DARK_GREY | FG_BLACK, PIXEL_QUARTER);
			if(i < 2) draw_text(console, (int2_t) { WIDTH / 2 - strlen(texts[i]) / 2, HEIGHT / 2 + i }, texts[i], BG_GREY | FG_BLACK);
			draw_pixel(console, (int2_t) { WIDTH / 2 - ((strlen(texts[1]) / 2) + 1) + i, HEIGHT / 2 + 2 }, BG_DARK_GREY | FG_BLACK, PIXEL_QUARTER);
		}
	
		if (GetAsyncKeyState(VK_F1) && !sending) {
			strcpy(client->mani.command, "sups");			
			/*if (sendto(client->winsock.socket, "perse", strlen("perse"), 0, (struct sockaddr*) & client->winsock.this_address, sizeof(struct sockaddr_in)) == SOCKET_ERROR) {
				draw_text(console, (int2_t) {0, 0 }, TEXT("send failed %i", WSAGetLastError()), BG_WHITE | FG_BLACK);
			}
			else draw_text(console, (int2_t) { 0, 0}, texts[2], BG_WHITE | FG_BLACK);*/

			sending = 1;
		}
		else if (!GetAsyncKeyState(VK_F1) && sending) sending = 0;
		
		ca_client_loop(client);
		draw_console(console);
	}
	closesocket(client->winsock.socket);

	WSACleanup();
	return 0;
}