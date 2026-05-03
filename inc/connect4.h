#ifndef CONNECT4_H
# define CONNECT4_H

# include <stdlib.h>
# include <time.h>
# include <stdio.h>
# include <limits.h>

#define MIN_ROWS 6
#define MIN_COLS 7
#define MAX_ROWS 1000
#define MAX_COLS 1000

#define PLAYER 1
#define AI 2
#define EMPTY 0

#define MAX_DISPLAY_COLS 50
#define MAX_DISPLAY_ROWS 30

typedef enum e_mode {
	MODE_TERMINAL,
	MODE_GUI
} t_mode;

typedef struct s_game {
	int		**board;
	int		rows;
	int		cols;
	int		turn;
	t_mode	mode;
	int		is_running;
} t_game;

/* Initialization and cleanup */
int		init_game(t_game *game, int argc, char **argv);
void	free_board(t_game game);

/* Display and input */
void	display_board(t_game game);
int		get_player_input(t_game game);
void	display_welcome(void);
void	display_game_end(t_game game, int winner);

/* Game logic */
int		drop_pawn(t_game *game, int col, int player);
int		can_drop_pawn(t_game game, int col);
int		check_win(t_game game, int col, int row);
int		full_board(t_game game);

/* AI logic */
int		ai_play(t_game *game, int *col_out);
int		minimax(t_game *game, int depth, int is_maximizing, int *best_col, int alpha, int beta);
int		evaluate_board(t_game game);

#endif
