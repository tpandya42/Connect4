NAME = connect4

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC_DIR = src
INC_DIR = inc

SRCS = $(SRC_DIR)/main.c
OBJS = $(SRCS:.c=.o)

INCS = -I$(INC_DIR)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
