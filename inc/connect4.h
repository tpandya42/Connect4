#ifndef CONNECT4_H
# define CONNECT4_H

# include <stdlib.h>
# include <time.h>
# include <stdio.h>

#define MIN_ROWS 6
#define MIN_COLS 7

typedef enum e_mode {
	MODE_TERMINAL,
	MODE_GUI
} t_mode;

typedef struct s_game {
	int	**board;
	int		rows;
	int 	cols;
	int 	turn;
	t_mode 	mode;
	int		is_running;
} t_game;

int 	init_game(t_game *game, int argc, char **argv);

#endif
