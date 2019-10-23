#ifndef CA_PLAYER_H
#define CA_PLAYER_H

#include "begin.h"

typedef struct {
	int id;
	int my_turn; // bool

	struct {
        int health;
		int speed;
        int exhaustion;
        int locationId;
	}stats;
    struct {
        int size;
    }inventory;
}player_t, * player_ptr;


CA_EXTERN_BEGIN
//location functions
CA_API void Move(player_t* playa, int direction);
CA_API void PickUp(player_t* playa);
CA_API void Hide(player_t* playa);
CA_API void Harvest(player_t* playa, char* what);
CA_API void Talk(player_t* playa);
CA_API void Rest(player_t* playa);
CA_API void Taunt(player_t* playa);
CA_API void StartCampfire(player_t* playa);

//turn functions
CA_API void EndTurn(player_t* playa);
CA_API void ExtendTime(player_t* playa);

//free functions
CA_API void Inspect(player_t* playa, char* what);
CA_API void Help(player_t* playa);
CA_API void OpenInventory(player_t* playa);
CA_API void ShowStats(player_t* playa);

//stat changes
CA_API void ChangeHealth(player_t* playa, int amount);
CA_API void ChangeAp(player_t* playa, int amount);
CA_API void ChangeExhaustion(player_t* playa, int amount);

//inventory changes
CA_API void UseItem(player_t* playa, int id);
CA_API void EquipItem(player_t* playa, int id);
CA_API void GiveItem(player_t* playa, player_t* toPlaya, int id);
CA_API void DropItem(player_t* playa, int id);
CA_API void StoreInInventory(player_t* playa, int id);

//combat functions
CA_API void StartFight(player_t* playa);
CA_API void JoinFight(player_t* playa);
CA_API void TrySkipFight(player_t* playa);
CA_API void Flee(player_t* playa, int id);
CA_API void UseSkill(player_t* playa, int id);
CA_API void Attack(player_t* playa);
CA_API void UseSpell(player_t* playa, int id);

//crafting
CA_API void CraftItem(player_t* playa, int id);
CA_EXTERN_END
#endif