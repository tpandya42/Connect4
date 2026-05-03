#include "connect4.h"
#include "libft.h"

void display_welcome(void)
{
	ft_printf("\n");
	ft_printf("========================================\n");
	ft_printf("          Welcome to Connect 4!         \n");
	ft_printf("========================================\n");
	ft_printf("\nPlayer (X) vs AI (O)\n");
	ft_printf("Drop your pawn by choosing a column!\n\n");
}

void display_board(t_game game)
{
	int row;
	int col;

	ft_printf("\n");

	if (game.cols > MAX_DISPLAY_COLS || game.rows > MAX_DISPLAY_ROWS)
	{
		ft_printf("Board is too large to display. Columns: %d, Rows: %d\n", game.cols, game.rows);
		ft_printf("Column numbers: ");
		for (col = 0; col < game.cols; col++)
			ft_printf("%d ", col % 10);
		ft_printf("\n");
		return ;
	}

	for (col = 0; col < game.cols; col++)
		ft_printf(" %d ", col);
	ft_printf("\n");

	for (col = 0; col < game.cols; col++)
		ft_printf("---");
	ft_printf("\n");

	for (row = 0; row < game.rows; row++)
	{
		for (col = 0; col < game.cols; col++)
		{
			if (game.board[row][col] == PLAYER)
				ft_printf("|X");
			else if (game.board[row][col] == AI)
				ft_printf("|O");
			else
				ft_printf("| ");
		}
		ft_printf("|\n");
	}

	for (col = 0; col < game.cols; col++)
		ft_printf("---");
	ft_printf("\n\n");
}

int get_player_input(t_game game)
{
	char buffer[256];
	int col;

	while (1)
	{
		ft_printf("Player's turn! Choose a column (0-%d): ", game.cols - 1);
		if (fgets(buffer, sizeof(buffer), stdin) == NULL)
			return (-1);

		col = ft_atoi(buffer);

		if (col < 0 || col >= game.cols)
		{
			ft_printf("Invalid column! Please choose between 0 and %d.\n", game.cols - 1);
			continue ;
		}

		if (can_drop_pawn(game, col) == -1)
		{
			ft_printf("Column %d is full! Choose another column.\n", col);
			continue ;
		}

		return (col);
	}
}

void display_game_end(t_game game, int winner)
{
	(void)game;

	ft_printf("\n========================================\n");
	if (winner == PLAYER)
		ft_printf("               You Won!                 \n");
	else if (winner == AI)
		ft_printf("         AI Won! Better luck next!      \n");
	else if (winner == 0)
		ft_printf("              It's a Draw!              \n");
	ft_printf("========================================\n\n");
}
