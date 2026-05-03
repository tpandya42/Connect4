#include "connect4.h"

static int check_vertical(t_game game, int p, int x, int y) {
    int **board = game.board;

    for (int r = y - 3; r <= y; r++) {
        if (r >= game.cols - 3)
            break;
        if (r < 0)
            continue;

        if (board[r][x] == p && board[r+1][x] == p && board[r+2][x] == p && board[r+3][x] == p)
            return 1;
    }

    return 0;
}

static int check_horizontal(t_game game, int p, int x, int y) {
    int **board = game.board;

    for (int c = x - 3; c <= x; c++) {
        if (c >= game.cols - 3)
            break;
        if (c < 0)
            continue;

        if (board[y][c] == p && board[y][c + 1] == p && board[y][c + 2] == p && board[y][c + 3] == p)
            return 1;
    }

    return 0;
}

static int check_diagonals(t_game game, int p, int x, int y) {
    int **board = game.board;

    for (int i = -3; i <= 0; i++) {
        if (x - i >= game.cols || y - i >= game.rows)
            continue;
        if (x + i < 0 || y + i < 0)
            continue;

        if (board[y+i][x+i] == p && board[y+i+1][x+i+1] == p && board[y+i+2][x+i+2] == p && board[y+i+3][x+i+3] == p)
            return 1;
        else if (board[y+i][x-i] == p && board[y+i+1][x-i-1] == p && board[y+i+2][x-i-2] == p && board[y+i+3][x-i-3] == p)
            return 1;
    }

    return 0;
}

int check_win(t_game game, int x, int y) {
    int position = game.board[y][x];
    if (check_vertical(game, position, x, y) == 1)
        return 1;
    if (check_horizontal(game, position, x, y) == 1)
        return 1;
    if (check_diagonals(game, position, x, y) == 1)
        return 1;
    return 0;
}

int full_board(t_game game) {
    for (int x = 0; x < game.rows; x++) {
        for (int y = 0; y < game.cols; y++) {
            if (game.board[x][y] == 0) {
                return 0;
            }
        }
    }

    return 1;
}
