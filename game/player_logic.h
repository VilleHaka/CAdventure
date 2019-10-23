

typedef struct {
	int id;
	int my_turn; // bool

	struct {
		int speed;
	}stats;
}player_t, * player_ptr;