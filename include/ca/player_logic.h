#ifndef CA_PLAYER_H
#define CA_PLAYER_H

#include "begin.h"
#define WAMWAMBAM 0
typedef enum {
    IDLE,
    AFK,
    DEAD,
    IN_COMBAT,
    CULTIVATING,
    TURN_OVER,
    TRAPPED,
}player_state;

typedef enum {
    HEALTHY,
    IMMOBILIZED,
    POISONED,
    FROZEN,
    ASLEEP,
    STUNNED,
}combat_status;

typedef struct {
	int id;
	int my_turn; // bool
    int in_combat;


    struct{
        int health, maxhealth;
        int spirit, maxspirit;//mana yms
        int status_duration;
        combat_status cur_status;
    }combat_stats;

	struct {
		int speed;
        int level;
        int ap, maxap;
        int experience;
        int exhaustion;
        int location_id;
        int crit_rate;
        int crit_dmg;

        player_state cur_state;
	}stats;

    struct {
        int size;
    }inventory;
}player_t, * player_ptr;

typedef struct {
    const char* name;
    int health;
}enemy_t;

CA_EXTERN_BEGIN
//location functions
CA_API void move(player_t* playa, int direction);
CA_API void pick_up(player_t* playa);
CA_API void hide(player_t* playa);
CA_API void harvest(player_t* playa, char* what);
CA_API void talk(player_t* playa);
CA_API void rest(player_t* playa);
CA_API void taunt(player_t* playa);
CA_API void start_campfire(player_t* playa);

//turn functions
CA_API void new_turn(player_t* playa);
CA_API void end_turn(player_t* playa);
CA_API void extend_time(player_t* playa);

//free functions
CA_API void inspect(player_t* playa, char* what);
CA_API void help(player_t* playa);
CA_API void open_inventory(player_t* playa);
CA_API void show_stats(player_t* playa);
CA_API void show_skills(player_t* playa);
CA_API void open_spellbook(player_t* playa);

//stat changes
CA_API void change_health(player_t* playa, int amount);
CA_API void change_ap(player_t* playa, int amount);
CA_API void change_exhaustion(player_t* playa, int amount);
CA_API void get_experience(player_t* playa, int amount);
CA_API void change_player_state(player_t* playa, player_state newstate);
CA_API void change_combat_status(player_t* playa, combat_status newstate);
CA_API void reduce_bad_status(player_t* playa);

//inventory changes
CA_API void use_consumable(player_t* playa, int id);
CA_API void equip_item(player_t* playa, int id);
CA_API void give_item(player_t* playa, player_t* toPlaya, int id);
CA_API void drop_item(player_t* playa, int id);
CA_API void add_to_inventory(player_t* playa, int id);

//combat functions
CA_API void start_fight(player_t* playa);
CA_API void join_fight(player_t* playa);
CA_API void try_skip_fight(player_t* playa);
CA_API void flee(player_t* playa);
CA_API void use_skill_self(player_t* playa, const char* skill);
CA_API void use_skill_enemy(player_t* playa, const char* skill, enemy_t target);
CA_API void attack(player_t* playa, enemy_t target);
CA_API void cast_spell_target(player_t* playa, const char* spell, enemy_t target);
CA_API void cast_spell_self(player_t* playa, const char* spell);

//crafting
CA_API void craft_item(player_t* playa, int id);
CA_EXTERN_END
#endif