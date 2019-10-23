#include <ca/cadventure.h>
#include <ca/game_logic.h>
#include <ca/console.h>

#include <time.h>

int main() {
	console_t* console;
	init_console(&console,L"Consolas", "C Proto");

	const char* texts[2] = { "C PROTO","hello world" };
	clock_t start, end;
	double el = 0;
	while (1) {
		start = clock();
		memset(console->console_buffer, NULL, WIDTH*HEIGHT*sizeof(CHAR_INFO));

		for (int i = 0; i < (strlen(texts[1]) + 2); i++) {
			draw_pixel(console, (int2_t) { WIDTH / 2 - ((strlen(texts[1]) / 2) + 1) + i, HEIGHT / 2 - 1 }, BG_DARK_GREY | FG_BLACK, PIXEL_QUARTER);
			if(i < 2) draw_text(console, (int2_t) { WIDTH / 2 - strlen(texts[i]) / 2, HEIGHT / 2 + i }, texts[i], BG_GREY | FG_BLACK);
			draw_pixel(console, (int2_t) { WIDTH / 2 - ((strlen(texts[1]) / 2) + 1) + i, HEIGHT / 2 + 2 }, BG_DARK_GREY | FG_BLACK, PIXEL_QUARTER);
		}
		
		draw_console(console);
		end = clock();
	}
	return 0;
}