#include "server_logic.h"

void init_server(server_ptr* server) {
	server_t* tmp = malloc(sizeof(server_t));
	tmp->player_count = 0;
	*server = tmp;
}