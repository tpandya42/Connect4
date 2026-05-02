#include "connect4.h"
#include "libft.h"

int init_game(t_game *game, int argc, char** argv) {
	if (argc < 3 || argc > 4) {
		// print
		return -1;
	}

	int rows = ft_atoi(argv[1]);
	int cols = ft_atoi(argv[2]);
	(*game).mode = MODE_TERMINAL;
	if (argc == 4) {
		int mode = ft_atoi(argv[3]);
		if (mode == 1)
			(*game).mode = MODE_GUI;
	}
	int **board = malloc(rows * sizeof(int*));
	int i = 0;
	while (i++ < rows) {
		board[i] = malloc(cols * sizeof(int));
		int j = 0;
		while (j++ < cols) {
			board[i][j] = 0;
		}
	}

	(*game).board = board;
	(*game).rows = rows;
	(*game).cols = cols;
	(*game).is_running = 1;
	return 0;
}

int main(int argc, char **argv)
{
	t_game game;

	srand(time(NULL));
	if (init_game(&game, argc, argv) != 0)
		return 1;
	game.turn = (rand() % 2) + 1;
	while (game.is_running)
	{
		break;
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
