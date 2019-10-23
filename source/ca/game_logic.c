#include <ca/game_logic.h>

CA_API void init_player(server_t* server, player_ptr* player) {
	player_t* tmp = malloc(sizeof(player_t));
	tmp->id = server->player_count;
	server->player_count++;
	*player = tmp;
}
