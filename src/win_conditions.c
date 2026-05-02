#include "connect4.h"

int check_vertical(t_game game, int p, int x, int y) {
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

int check_horizontal(t_game game, int p, int x, int y) {
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

int check_diagonals(t_game game, int p, int x, int y) {
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

// loop1: i=-3 board[y-3][x-3] == board[y-2][x-2] == board[y-1][x-1] == board[y][x]
//             board[y-3][x+3] == board[y-2][x+2] == board[y-1][x+1] == board[y][x]
// loop2: i=-2 board[y-2][x-2] == board[y-1][x-1] == board[y][x] == board[y+1][x+1]
//             board[y-2][x+2] == board[y-1][x+1] == board[y][x] == board[y+1][x-1]
// loop3: i=-1 board[y-1][x-1] == board[y][x] == board[y+1][x+1] == board[y+2][x+2]
//             board[y-1][x+1] == board[y][x] == board[y+1][x-1] == board[y+2][x-2]
// loop4: i=0 board[y][x] == board[y+1][x+1] == board[y+2][x+2] == board[y+3][x+3]
//.           board[y][x] == board[y+1][x-1] == board[y+2][x-2] == board[y+3][x-3] 

int check_win(t_game game, int x, int y) {
    if (check_vertical(game, game.board, x, y) == 1)
        return 1;
    if (check_horizontal(game, game.board, x, y) == 1)
        return 1;
    if (check_diagonals(game, game.board, x, y) == 1)
        return 1;
    return 0;
}

// loop1: r=-3 c=-3 board[y-3][x-3] == board[y-3][x-2] == board[y-3][x-1] == board[y-3][x]
// loop2: r=-3 c=-2 board[y-3][x-2] == board[y-3][x-1] == board[y-3][x] == board[y-3][x+1]
// loop3: r=-3 c=-1 board[y-3][x-1] == board[y-3][x] == board[y-3][x+1] == board[y-3][x+2]
// loop4: r=-3 c=0 board[y-3][x] == board[y-3][x+1] == board[y-3][x+2] == board[y-3][x+3]
// loop5: r=-2 c=-3 board[y-2][x-3] == board[y-2][x-2] == board[y-2][x-1] == board[y-2][x]
// loop6: r=-2 c=-2 board[y-2][x-2] == board[y-2][x-1] == board[y-2][x] == board[y-2][x+1]
// loop7: r=-2 c=-1 board[y-2][x-1] == board[y-2][x] == board[y-2][x+1] == board[y-2][x+2]
// loop8: r=-2 c=0 board[y-2][x] == board[y-2][x+1] == board[y-2][x+2] == board[y-2][x+3]

// [ 
//   [ 0         , 0         , (x, y+3), 0         , 0         , (x+3, y+3)]
//   [ (x-2, y+2), 0         , (x, y+2), 0         , (x+2, y+2), 0         ]
//   [ 0         , (x-1, y+1), (x, y+1), (x+1, y+1), 0         , 0         ]
//   [ (x-2, y)  , (x-1, y)  , (x, y)  , (x+1, y)  , (x+2, y)  , (x+3, y)  ]
//   [ 0         , (x-1, y-1), (x, y-1), (x+1, y-1), 0         , 0         ]
//   [ (x-2, y-2), 0         , (x, y-2), 0         , (x+2, y-2), 0         ]
//   [ 0         , 0         , (x, y-3), 0         , 0         , (x+3, y-3)] 
//  ]

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
