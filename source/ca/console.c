#include <ca/console.h>

CA_API void init_console(console_ptr* console,const char* font,const char* title) {
	console_t* tmp = &console;
	tmp = (console_t*)malloc(sizeof(console_t));

	tmp->output = (HANDLE)GetStdHandle(STD_OUTPUT_HANDLE);
	{
		tmp->title = title;
		SetConsoleTitle(TEXT(tmp->title));

		GetConsoleScreenBufferInfoEx(tmp->output, &tmp->scr);		
		tmp->scr.srWindow = (SMALL_RECT){ 0, 0, WIDTH, HEIGHT};	
		tmp->scr.bFullscreenSupported = 1;
		tmp->scr.cbSize = WIDTH*HEIGHT*sizeof(CHAR_INFO);
		tmp->scr.dwCursorPosition = (COORD){ 0, 0 };
		tmp->scr.dwMaximumWindowSize = (COORD){ WIDTH, HEIGHT };
		tmp->scr.dwSize = (COORD){ WIDTH, HEIGHT };	
		tmp->console_buffer = (CHAR_INFO*)malloc((int)tmp->scr.cbSize*sizeof(CHAR_INFO));
		memset(tmp->console_buffer, 0, tmp->scr.cbSize);
		SetConsoleActiveScreenBuffer(tmp->output);
		SetConsoleScreenBufferInfoEx(tmp->output, &tmp->scr);
		SetConsoleScreenBufferSize(tmp->output, tmp->scr.dwSize);
		SetConsoleWindowInfo(tmp->output, TRUE, &tmp->scr.srWindow);		
		
	}

	CONSOLE_CURSOR_INFO cursor_info;
	{	
		cursor_info.bVisible = 0;	
		SetConsoleCursorInfo(tmp->output, &cursor_info);
	}

	{
		tmp->font.cbSize = sizeof(tmp->font);
		tmp->font.nFont = 0;
		tmp->font.dwFontSize.X = 10;
		tmp->font.dwFontSize.Y = 18;
		tmp->font.FontFamily = FF_DONTCARE;
		tmp->font.FontWeight = FW_NORMAL;
		wcscpy(tmp->font.FaceName, font);

		SetCurrentConsoleFontEx(tmp->output, TRUE, &tmp->font);
	}

	*console = tmp;
}

CA_API void draw_text(console_t* console, int2_t pos, const char* text, DWORD color) {
	for (int i = 0; i < strlen(text); i++) {
		console->console_buffer[(pos.x + i) + WIDTH * pos.y].Attributes = color;
		console->console_buffer[(pos.x + i) + WIDTH * pos.y].Char.UnicodeChar = text[i];
	}
}

CA_API void draw_pixel(console_t* console, int2_t pos, DWORD color,char sym) {
	console->console_buffer[pos.x + WIDTH * pos.y].Attributes = color;
	console->console_buffer[pos.x + WIDTH * pos.y].Char.UnicodeChar = sym;
}

CA_API void draw_console(console_t* console) {
	WriteConsoleOutputA(console->output, console->console_buffer, console->scr.dwSize, console->scr.dwCursorPosition, &console->scr.srWindow);
}