#include "connect4.h"
#include "libft.h"

static int count_align(int **board, int rows, int cols, int row, int col, int player, int dr, int dc)
{
	int count = 0;
	int r = row;
	int c = col;

	while (r >= 0 && r < rows && c >= 0 && c < cols && board[r][c] == player)
	{
		count++;
		r += dr;
		c += dc;
	}
	return (count - 1);
}

static int score_position(int **board, int rows, int cols, int row, int col, int player)
{
	int score = 0;
	int directions[4][2] = {{0, 1}, {1, 0}, {1, 1}, {1, -1}};
	int i;
	int align1;
	int align2;
	int total;

	for (i = 0; i < 4; i++)
	{
		align1 = count_align(board, rows, cols, row, col, player, directions[i][0], directions[i][1]);
		align2 = count_align(board, rows, cols, row, col, player, -directions[i][0], -directions[i][1]);
		total = align1 + align2 + 1;

		if (total >= 4)
			score += 50000;
		else if (total == 3)
			score += 50;
		else if (total == 2)
			score += 10;
	}
	return (score);
}

int evaluate_board(t_game game)
{
	int score = 0;
	int ai_score = 0;
	int player_score = 0;
	int row;
	int col;

	for (row = 0; row < game.rows; row++)
	{
		for (col = 0; col < game.cols; col++)
		{
			if (game.board[row][col] == AI)
				ai_score += score_position(game.board, game.rows, game.cols, row, col, AI);
			else if (game.board[row][col] == PLAYER)
				player_score += score_position(game.board, game.rows, game.cols, row, col, PLAYER);
		}
	}
	score = ai_score - player_score;
	return (score);
}

int minimax(t_game *game, int depth, int is_maximizing, int *best_col, int alpha, int beta)
{
	int col_valid[MAX_COLS];
	int valid_moves = 0;
	int col;
	int i;
	int row;
	int eval;
	int max_eval;
	int min_eval;

	for (col = 0; col < game->cols; col++)
	{
		if (can_drop_pawn(*game, col) != -1)
		{
			col_valid[valid_moves] = col;
			valid_moves++;
		}
	}

	if (depth == 0 || valid_moves == 0 || full_board(*game))
		return (evaluate_board(*game));

	if (is_maximizing)
	{
		max_eval = INT_MIN;
		for (i = 0; i < valid_moves; i++)
		{
			col = col_valid[i];
			row = drop_pawn(game, col, AI);
			eval = minimax(game, depth - 1, 0, NULL, alpha, beta);

			game->board[row][col] = EMPTY;
			if (eval > max_eval)
			{
				max_eval = eval;
				if (best_col != NULL)
					*best_col = col;
			}
			alpha = (alpha > eval) ? alpha : eval;
			if (beta <= alpha)
				return (max_eval);
		}
		return (max_eval);
	}
	else
	{
		min_eval = INT_MAX;
		for (i = 0; i < valid_moves; i++)
		{
			col = col_valid[i];
			row = drop_pawn(game, col, PLAYER);
			eval = minimax(game, depth - 1, 1, NULL, alpha, beta);

			game->board[row][col] = EMPTY;
			if (eval < min_eval)
				min_eval = eval;
			beta = (beta < eval) ? beta : eval;
			if (beta <= alpha)
				return (min_eval);
		}
		return (min_eval);
	}
}

int ai_play(t_game *game, int *col_out)
{
	int best_col = -1;
	int depth = 6;
	int col;
	int row;

	if (game->rows > 10 || game->cols > 10)
		depth = 4;
	if (game->rows > 20 || game->cols > 20)
		depth = 3;

	minimax(game, depth, 1, &best_col, INT_MIN, INT_MAX);

	if (best_col == -1)
	{
		for (col = 0; col < game->cols; col++)
		{
			if (can_drop_pawn(*game, col) != -1)
			{
				best_col = col;
				break;
			}
		}
	}

	if (best_col != -1)
	{
		row = drop_pawn(game, best_col, AI);
		if (row == -1)
			return (-1);
		if (col_out != NULL)
			*col_out = best_col;
		return (row);
	}
	return (-1);
}
