#ifndef CA_GAME_H
#define CA_GAME_H

#include "begin.h"

#include <ca/server_logic.h>
#include <ca/player_logic.h>

CA_EXTERN_BEGIN
CA_API void init_player(server_t* server, player_ptr* player);
CA_EXTERN_END

#endif