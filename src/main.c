#include "connect4.h"
#include "libft.h"

void free_board(t_game game) {
	int i = 0;
	while (i++ < game.rows) {
		free(game.board[i]);
	}

	free(game.board);
}

int can_drop_pawn(t_game game, int x) {
	int y = 0;

	for (int i = 0; i < game.rows; i++) {
		if (game.board[y][x] == 0) {
			return y;
		}
	}

	return -1;
}

int init_game(t_game *game, int argc, char** argv) {
	if (argc < 3 || argc > 4) {
		ft_printf("Number of argument is wrong.\n");
		return 1;
	}

	int rows = ft_atoi(argv[1]);
	int cols = ft_atoi(argv[2]);

	if (cols < 7 || rows < 6) {
		ft_printf("Minimum number is 6 for rows and 7 for columns.\n");
		return 1;
	}
	if (cols > 1000 || rows > 1000) { // max to be defined
		ft_printf("Maximum number is ? for rows and ? for columns.\n");
		return 1;
	}

	(*game).mode = MODE_TERMINAL;
	if (argc == 4) {
		int mode = ft_atoi(argv[3]);
		if (mode == 1)
			(*game).mode = MODE_GUI;
		else if (mode != 0) {
			ft_printf("Please enter 0 for terminal mode and 1 for GUI mode.\n");
			return 1;
		}
	}

	int **board = malloc(rows * sizeof(int*));
	if (board == NULL) {
		ft_printf("Malloc failed.\n");
		return 1;
	}

	int i = 0;
	while (i < rows) {
		board[i] = malloc(cols * sizeof(int));
		if (board[i] == NULL) {
			ft_printf("Malloc failed.\n");
			while (--i >= 0)
				free(board[i]);
			free(board);
			return 1;
		}
		int j = 0;
		while (j < cols) {
			board[i][j++] = 0;
		}
		i++;
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
	// 1 for player and 2 for bot ?
	while (game.is_running)
	{
		if (game.turn == 1) {
			// get player input
			int x = 0; // get real input
			int y = can_drop_pawn(game, x);
			while (y == -1) {
				// get player input again
				y = can_drop_pawn(game, x);
			}
			game.board[y][x] = game.turn;

			if (check_win(game, x, y)) {
				ft_printf("Congralutions, you won!\n");
				game.is_running = 0;
			}
			// player
		} else {
			// ai
		}
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
		if (full_board(game)) {
			ft_printf("It's a tie!\n");
			game.is_running = 0;
		}	
		game.turn = (game.turn % 2) + 1;
	}

	// cleanup 
	//
	//
	// free game and exit
	free_board(game);
    return (0);
}
