#ifndef CA_CONSOLE_H
#define CA_CONSOLE_H

#include "begin.h"

#define WIDTH (64)
#define HEIGHT (32)

typedef enum COLOR_e {
FG_BLACK		= (0x0000),
FG_DARK_BLUE	= (0x0001),
FG_DARK_GREEN	= (0x0002),
FG_DARK_CYAN	= (0x0003),
FG_DARK_RED		= (0x0004),
FG_DARK_MAGENTA	= (0x0005),
FG_DARK_YELLOW	= (0x0006),
FG_GREY			= (0x0007),
FG_DARK_GREY	= (0x0008),
FG_BLUE			= (0x0009),
FG_GREEN		= (0x000A),
FG_CYAN			= (0x000B),
FG_RED			= (0x000C),
FG_MAGENTA		= (0x000D),
FG_YELLOW		= (0x000E),
FG_WHITE		= (0x000F),			
BG_BLACK		= (0x0000),
BG_DARK_BLUE	= (0x0010),
BG_DARK_GREEN	= (0x0020),
BG_DARK_CYAN	= (0x0030),
BG_DARK_RED		= (0x0040),
BG_DARK_MAGENTA	= (0x0050),
BG_DARK_YELLOW	= (0x0060),
BG_GREY			= (0x0070),
BG_DARK_GREY	= (0x0080),
BG_BLUE			= (0x0090),
BG_GREEN		= (0x00A0),
BG_CYAN			= (0x00B0),
BG_RED			= (0x00C0),
BG_MAGENTA		= (0x00D0),
BG_YELLOW		= (0x00E0),
BG_WHITE		= (0x00F0)
}COLOR_E;

enum PIXEL_TYPE
{
	PIXEL_SOLID = 0x2588,
	PIXEL_THREEQUARTERS = 0x2593,
	PIXEL_HALF = 0x2592,
	PIXEL_QUARTER = 0x2591,
};
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
	LPCTSTR title;

	HANDLE output;
	HANDLE input;

	CONSOLE_SCREEN_BUFFER_INFOEX scr;
	CHAR_INFO* console_buffer;
	CONSOLE_FONT_INFOEX font;
}console_t, * console_ptr;

CA_EXTERN_BEGIN
CA_API void init_console(console_ptr* console, const char* font, const char* title);
CA_API void draw_text(console_t* console, int2_t pos, const char* text, DWORD color);
CA_API void draw_pixel(console_t* console, int2_t pos, DWORD color,char sym);
CA_API void draw_console(console_t* console);
CA_EXTERN_END

#endif