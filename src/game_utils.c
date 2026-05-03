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

static int num_width(int n)
{
	int width;

	width = 1;
	while (n >= 10)
	{
		n /= 10;
		width++;
	}
	return (width);
}

static void print_nchar(char ch, int count)
{
	while (count-- > 0)
		ft_printf("%c", ch);
}

static void print_padded_num(int n, int width)
{
	char buf[12];
	int i;
	int j;
	int len;
	char tmp;

	if (n == 0)
	{
		buf[0] = '0';
		buf[1] = '\0';
		len = 1;
	}
	else
	{
		i = 0;
		while (n > 0 && i < 11)
		{
			buf[i++] = (char)('0' + (n % 10));
			n /= 10;
		}
		len = i;
		j = 0;
		while (j < len / 2)
		{
			tmp = buf[j];
			buf[j] = buf[len - 1 - j];
			buf[len - 1 - j] = tmp;
			j++;
		}
		buf[len] = '\0';
	}
	print_nchar(' ', width - len);
	ft_printf("%s", buf);
}

static void print_header(int row_w, int col_w, int cols)
{
	int col;

	print_nchar(' ', row_w);
	ft_printf(" |" );
	for (col = 0; col < cols; col++)
	{
		print_nchar(' ', 1);
		print_padded_num(col, col_w);
		print_nchar(' ', 1);
		ft_printf("|");
	}
	ft_printf("\n");
}

static void print_border(int row_w, int col_w, int cols)
{
	int col;

	print_nchar(' ', row_w);
	ft_printf(" +");
	for (col = 0; col < cols; col++)
	{
		print_nchar('-', col_w + 2);
		ft_printf("+");
	}
	ft_printf("\n");
}

void display_board(t_game game)
{
	int row_w;
	int col_w;
	int row;
	int col;
	char token;

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

	row_w = num_width(game.rows - 1);
	col_w = num_width(game.cols - 1);

	print_header(row_w, col_w, game.cols);
	print_border(row_w, col_w, game.cols);

	for (row = 0; row < game.rows; row++)
	{
		print_padded_num(row, row_w);
		ft_printf(" |");
		for (col = 0; col < game.cols; col++)
		{
			if (game.board[row][col] == PLAYER)
				token = 'X';
			else if (game.board[row][col] == AI)
				token = 'O';
			else
				token = ' ';
			ft_printf(" %c", token);
			print_nchar(' ', col_w - 1);
			ft_printf(" |");
		}
		ft_printf("\n");
		print_border(row_w, col_w, game.cols);
	}
	ft_printf("\n");
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
