#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")

#define WIDTH (64)
#define HEIGHT (32)

#define FG_BLACK		(0x0000)
#define FG_DARK_BLUE	(0x0001)
#define FG_DARK_GREEN	(0x0002)
#define FG_DARK_CYAN	(0x0003)
#define FG_DARK_RED		(0x0004)
#define FG_DARK_MAGENTA	(0x0005)
#define FG_DARK_YELLOW	(0x0006)
#define FG_GREY			(0x0007)
#define FG_DARK_GREY	(0x0008)
#define FG_BLUE			(0x0009)
#define FG_GREEN		(0x000A)
#define FG_CYAN			(0x000B)
#define FG_RED			(0x000C)
#define FG_MAGENTA		(0x000D)
#define FG_YELLOW		(0x000E)
#define FG_WHITE		(0x000F)

#define BG_BLACK		(0x0000)
#define BG_DARK_BLUE	(0x0010)
#define BG_DARK_GREEN	(0x0020)
#define BG_DARK_CYAN	(0x0030)
#define BG_DARK_RED		(0x0040)
#define BG_DARK_MAGENTA	(0x0050)
#define BG_DARK_YELLOW	(0x0060)
#define BG_GREY			(0x0070)
#define BG_DARK_GREY	(0x0080)
#define BG_BLUE			(0x0090)
#define BG_GREEN		(0x00A0)
#define BG_CYAN			(0x00B0)
#define BG_RED			(0x00C0)
#define BG_MAGENTA		(0x00D0)
#define BG_YELLOW		(0x00E0)
#define BG_WHITE		(0x00F0)

typedef struct {
	union {
		struct {
			int x, y;
		};
		int v[2];
	};
}int2_t;

typedef struct {
	int r, g, b;
}rgb_t;

typedef struct {
	SHORT C_WIDTH;
	SHORT C_HEIGHT;
	SHORT W_WIDTH;
	SHORT W_HEIGHT;

	LPCTSTR title;

	HANDLE output;
	HANDLE temp;
	HANDLE read;
	COORD render_area;
	CHAR_INFO* console_buffer;
	COORD char_buffer_size;
	COORD char_position;
	SMALL_RECT write_area;

	CONSOLE_FONT_INFOEX font;
}console_t,*console_ptr;


void init_console(console_ptr *perkele) {
	console_t* console;

	console = (console_t*)malloc(sizeof(console_t));
	//console->console_buffer = malloc(size.x * size.y);
	//SetConsoleTitle(TEXT("CAdventure"));
	console->output = GetStdHandle(STD_OUTPUT_HANDLE);

	
	console->title = "CAdventure";


	console->W_WIDTH = WIDTH;
	console->W_HEIGHT = HEIGHT;
	console->render_area = (COORD){ WIDTH, HEIGHT };
	console->char_buffer_size = (COORD){ WIDTH, HEIGHT };
	console->char_position = (COORD){ 0, 0 };
	console->write_area = (SMALL_RECT){ 0, 0, WIDTH -1, HEIGHT - 1 };
	console->console_buffer = (CHAR_INFO*)calloc(WIDTH * HEIGHT, sizeof(CHAR_INFO));
	SetConsoleTitle(TEXT(console->title));
	CONSOLE_FONT_INFOEX font;

	SMALL_RECT window_size = { 0, 0, WIDTH, HEIGHT };
	SetConsoleWindowInfo(console->output, FALSE, &window_size);

	CONSOLE_CURSOR_INFO cursor_info;
	//GetConsoleCursorInfo(console->output, &cursor_info);

	font.cbSize = sizeof(font);
	font.nFont = 0;
	font.dwFontSize.X = 8;
	font.dwFontSize.Y = 16;
	font.FontFamily = FF_DONTCARE;
	font.FontWeight = FW_NORMAL;
	wcscpy(font.FaceName, L"Consolas");
	SetCurrentConsoleFontEx(console->output, TRUE, &font);

	cursor_info.bVisible = 0;
	SetConsoleCursorInfo(console->output, &cursor_info);
	SetConsoleActiveScreenBuffer(console->output);
	*perkele = console;
}


void draw_text(console_t* console, int2_t pos, const char* text, DWORD color) {
	for (int i = 0; i < strlen(text); i++) {
		console->console_buffer[(pos.x + i) + WIDTH * pos.y].Attributes = color;
		console->console_buffer[(pos.x + i) + WIDTH * pos.y].Char.UnicodeChar = text[i];
	}
}

void draw_pixel(console_t* console, int2_t pos, DWORD color) {
	console->console_buffer[pos.x + WIDTH * pos.y].Attributes = color;
	console->console_buffer[pos.x + WIDTH * pos.y].Char.UnicodeChar = 'å';
}

void draw_console(console_t* console) {
	
	WriteConsoleOutput(console->output, console->console_buffer, console->char_buffer_size, console->char_position, &console->write_area);
}


int game(console_t* console) {
	//memset(console->console_buffer, 0, sizeof(HANDLE));

	
	
	
	return 1;
}


typedef struct {
	int id;
	int my_turn; // bool

	struct {
		int speed;
	}stats;
}player_t,*player_ptr;

typedef struct {
	int player_count;
}server_t, *server_ptr;


void init_player(server_t* server,player_ptr* player) {
	player_t* tmp = malloc(sizeof(player_t));
	tmp->id = server->player_count;
	server->player_count++;
	*player = tmp;
}

void init_server(server_ptr* server) {
	server_t* tmp = malloc(sizeof(server_t));
	tmp->player_count = 0;
	*server = tmp;
}

int main() {
	console_t* console;
	init_console(&console, (int2_t) {WIDTH,HEIGHT});

	server_t* server;
	init_server(&server);
	
	player_t* player;
	init_player(server,&player);

	player_t* player2;
	init_player(server, &player2);

	// WINSUCK
	struct sockaddr_in si_other;
	int s, slen = sizeof(si_other);
	char buf[15];
	char message[15];
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2),&wsa);

	s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	memset((char*)&si_other, 0, sizeof(si_other));

	si_other.sin_family = AF_INET;
	si_other.sin_port = htons(7777);
	si_other.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");



	char* perse;
	itoa(server->player_count, &perse, 10);
	draw_text(console, (int2_t) { WIDTH / 2, HEIGHT / 2 - 1 },&perse, BG_WHITE | FG_BLACK);
	draw_pixel(console, (int2_t) { WIDTH/2, HEIGHT/2 }, BG_WHITE | FG_WHITE);
	while (1) {

		draw_console(console);
	}

	closesocket(s);
	WSACleanup();
	return 0;
}