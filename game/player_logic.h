
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




//location functions
void Move(player_t* playa, int direction);
void PickUp(player_t* playa);
void Hide(player_t* playa);
void Harvest(player_t* playa, char* what);
void Talk(player_t* playa);
void Rest(player_t* playa);
void Taunt(player_t* playa);
void StartCampfire(player_t* playa);

//turn functions
void EndTurn(player_t* playa);
void ExtendTime(player_t* playa);

//free functions
void Inspect(player_t* playa, char* what);
void Help(player_t* playa);
void OpenInventory(player_t* playa);
void ShowStats(player_t* playa);

//stat changes
void ChangeHealth(player_t* playa, int amount);
void ChangeAp(player_t* playa, int amount);
void ChangeExhaustion(player_t* playa, int amount);

//inventory changes
void UseItem(player_t* playa, int id);
void EquipItem(player_t* playa, int id);
void GiveItem(player_t* playa, player_t* toPlaya, int id);
void DropItem(player_t* playa, int id);
void StoreInInventory(player_t* playa, int id);


//combat functions
void StartFight(player_t* playa);
void JoinFight(player_t* playa);
void TrySkipFight(player_t* playa);
void Escape(player_t* playa, int id);
void UseSkill(player_t* playa, int id);
void Attack(player_t* playa);
void UseSpell(player_t* playa, int id);

//crafting
void CraftItem(player_t* playa, int id);