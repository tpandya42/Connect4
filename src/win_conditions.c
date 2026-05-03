#include "connect4.h"

static int check_vertical(t_game game, int player, int col, int row)
{
	int **board = game.board;
	int r;

	for (r = row - 3; r <= row; r++)
	{
		if (r < 0 || r + 3 >= game.rows)
			continue ;

		if (board[r][col] == player && board[r + 1][col] == player
			&& board[r + 2][col] == player && board[r + 3][col] == player)
			return (1);
	}

	return (0);
}

static int check_horizontal(t_game game, int player, int col, int row)
{
	int **board = game.board;
	int c;

	for (c = col - 3; c <= col; c++)
	{
		if (c < 0 || c + 3 >= game.cols)
			continue ;

		if (board[row][c] == player && board[row][c + 1] == player
			&& board[row][c + 2] == player && board[row][c + 3] == player)
			return (1);
	}

	return (0);
}

static int check_diagonals(t_game game, int player, int col, int row)
{
	int **board = game.board;
	int i;

	for (i = -3; i <= 0; i++)
	{
		if (col + i >= 0 && row + i >= 0 && col + i + 3 < game.cols && row + i + 3 < game.rows)
		{
			if (board[row + i][col + i] == player && board[row + i + 1][col + i + 1] == player
				&& board[row + i + 2][col + i + 2] == player && board[row + i + 3][col + i + 3] == player)
				return (1);
		}

		if (col - i < game.cols && row + i >= 0 && col - i - 3 >= 0 && row + i + 3 < game.rows)
		{
			if (board[row + i][col - i] == player && board[row + i + 1][col - i - 1] == player
				&& board[row + i + 2][col - i - 2] == player && board[row + i + 3][col - i - 3] == player)
				return (1);
		}
	}

	return (0);
}

int check_win(t_game game, int col, int row)
{
	int player = game.board[row][col];

	if (check_vertical(game, player, col, row) == 1)
		return (1);
	if (check_horizontal(game, player, col, row) == 1)
		return (1);
	if (check_diagonals(game, player, col, row) == 1)
		return (1);
	return (0);
}

int full_board(t_game game)
{
	int row;
	int col;

	for (row = 0; row < game.rows; row++)
	{
		for (col = 0; col < game.cols; col++)
		{
			if (game.board[row][col] == EMPTY)
				return (0);
		}
	}

	return (1);
}

int can_drop_pawn(t_game game, int col)
{
	int row;

	if (col < 0 || col >= game.cols)
		return (-1);

	for (row = game.rows - 1; row >= 0; row--)
	{
		if (game.board[row][col] == EMPTY)
			return (row);
	}

	return (-1);
}

int drop_pawn(t_game *game, int col, int player)
{
	int row = can_drop_pawn(*game, col);

	if (row == -1)
		return (-1);

	game->board[row][col] = player;
	return (row);
}

