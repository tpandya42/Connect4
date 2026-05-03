#include "connect4.h"
#include "libft.h"

void free_board(t_game game)
{
	int i;

	i = 0;
	while (i < game.rows)
	{
		free(game.board[i]);
		i++;
	}
	free(game.board);
}

static int validate_args(int rows, int cols)
{
	if (rows < MIN_ROWS || cols < MIN_COLS)
	{
		ft_printf("Error: Minimum size is %d rows and %d columns.\n", MIN_ROWS, MIN_COLS);
		return (1);
	}
	if (rows > MAX_ROWS || cols > MAX_COLS)
	{
		ft_printf("Error: Maximum size is %d rows and %d columns.\n", MAX_ROWS, MAX_COLS);
		return (1);
	}
	return (0);
}

int init_game(t_game *game, int argc, char **argv)
{
	int rows;
	int cols;
	int i;
	int j;
	int **board;

	if (argc < 3 || argc > 4)
	{
		ft_printf("Usage: ./connect4 <rows> <cols> [mode]\n");
		ft_printf("mode: 0 for terminal (default), 1 for GUI\n");
		return (1);
	}

	rows = ft_atoi(argv[1]);
	cols = ft_atoi(argv[2]);

	if (validate_args(rows, cols) != 0)
		return (1);

	game->mode = MODE_TERMINAL;
	if (argc == 4)
	{
		int mode = ft_atoi(argv[3]);
		if (mode == 1)
			game->mode = MODE_GUI;
		else if (mode != 0)
		{
			ft_printf("Error: Mode must be 0 (terminal) or 1 (GUI).\n");
			return (1);
		}
	}

	board = malloc(rows * sizeof(int *));
	if (board == NULL)
	{
		ft_printf("Error: Memory allocation failed.\n");
		return (1);
	}

	i = 0;
	while (i < rows)
	{
		board[i] = malloc(cols * sizeof(int));
		if (board[i] == NULL)
		{
			ft_printf("Error: Memory allocation failed.\n");
			while (--i >= 0)
				free(board[i]);
			free(board);
			return (1);
		}
		j = 0;
		while (j < cols)
		{
			board[i][j] = EMPTY;
			j++;
		}
		i++;
	}

	game->board = board;
	game->rows = rows;
	game->cols = cols;
	game->is_running = 1;
	return (0);
}

static void game_loop(t_game *game)
{
	int col;
	int row;

	display_welcome();

	while (game->is_running)
	{
		display_board(*game);

		if (game->turn == PLAYER)
		{
			col = get_player_input(*game);
			if (col == -1)
			{
				ft_printf("Error: Failed to read input.\n");
				game->is_running = 0;
				break ;
			}
			row = drop_pawn(game, col, PLAYER);
		}
		else
		{
			ft_printf("AI is thinking...\n");
			col = ai_play(game);
			if (col == -1)
			{
				ft_printf("Error: AI failed to play.\n");
				game->is_running = 0;
				break ;
			}
			row = can_drop_pawn(*game, col);
		}

		if (check_win(*game, col, row))
		{
			display_board(*game);
			display_game_end(*game, game->turn);
			game->is_running = 0;
		}
		else if (full_board(*game))
		{
			display_board(*game);
			display_game_end(*game, 0);
			game->is_running = 0;
		}
		else
		{
			game->turn = (game->turn == PLAYER) ? AI : PLAYER;
		}
	}
}

int main(int argc, char **argv)
{
	t_game game;

	srand(time(NULL));
	if (init_game(&game, argc, argv) != 0)
		return (1);

	game.turn = (rand() % 2) + 1;

	game_loop(&game);

	free_board(game);
	return (0);
}

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
