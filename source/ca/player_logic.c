#include <ca/player_logic.h>

void change_health(player_t* playa, int amount)
{
    playa->combat_stats.health += amount;
    if (playa->combat_stats.health <= 0)
    {
        change_player_state(playa, DEAD);
    }
}
void change_ap(player_t* playa, int amount)
{
    playa->stats.ap += amount;
}
void change_exhaustion(player_t* playa, int amount)
{
    playa->stats.exhaustion += amount;
}
void get_experience(player_t* playa, int amount)
{
    playa->stats.experience += amount;
    int requiredexp = 100; //exp formula here
    //check if levelup
    if (playa->stats.experience >= requiredexp)
    {
        playa->stats.level++;
    }
    
}
void change_player_state(player_t* playa, player_state newstate)
{
    playa->stats.cur_state = newstate;
}
void change_combat_status(player_t* playa, combat_status newstatus)
{
    playa->combat_stats.cur_status = newstatus;
}
void reduce_bad_status(player_t* playa)
{
    if (playa->combat_stats.cur_status != HEALTHY)
    {
        playa->combat_stats.status_duration--;
        if (playa->combat_stats.status_duration <= 0)
        {
            change_combat_status(playa, HEALTHY);
        }
    }
}

void end_turn(player_t* playa)
{
    reduce_bad_status(playa);
}
void new_turn(player_t* playa)
{
    playa->stats.ap = playa->stats.maxap;
}