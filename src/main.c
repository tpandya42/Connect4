#include "connect4.h"

int main(int argc, char **argv)
{
	t_game game;

	srand(time(NULL));
	if (init_game(&game, argc, argv) != 0)
		return 1;
	game.turn = (rand() % 2) + 1;
	while (game.is_running)
	{
		// print board
		//
		//
		// if game.turn is for player 1 then do the thingy
		//
		//
		//
		// if turn is for ai then let ai do its thingy
		//
		//
		// check for winning condition 
		//
		//
		// switch turn and repeat.......	
	}

	// cleanup 
	//
	//
	// free game and exit
    return (0);
}
