NAME = codexion
CC = cc
HEADER_DIR = headers
SRC_DIR = srcs

CFLAGS = -Wall -Wextra -Werror -pthread -I$(HEADER_DIR)

SRC = 	$(addprefix $(SRC_DIR)/,\
		parsing.c \
		main.c)

OBJ = $(SRC:.c=.o)

REMOVE = rm -f

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

all: $(NAME)

clean:
	$(REMOVE) $(OBJ)

fclean: clean
	$(REMOVE) $(NAME)

re: fclean all

.PHONY = all clean fclean re