NAME = codexion
CC = cc
HEADER_DIR = headers
SRC_DIR = srcs
OBJ_DIR = objs

CFLAGS = -Wall -Wextra -Werror -pthread

SRC = 	\
		parsing.c \
		main.c \
		error.c \
		init.c \
		routine.c \
		threads.c \
		monitor.c \
		free.c \
		time.c \
		dongle.c

OBJS = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

REMOVE = rm -rf

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	$(REMOVE) $(OBJ_DIR)

fclean: clean
	$(REMOVE) $(NAME)

re: fclean all

.PHONY = all clean fclean re


# ./codexion 4 1000 50 50 50 5 0 edf -> all done
# ./codexion 4 100 50 50 50 5 0 edf -> one burnout
# ./codexion 1 200 500 50 50 5 0 edf -> one coder burnout mid routine
# ./codexion 7 1000 50 50 50 2 0 edf -> odd table, no deadlock
