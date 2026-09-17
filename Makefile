CC = cc

CFLAGS = -Wall -Wextra -Werror

SRC =

OBJ = $(SRC:.c=.o)

NAME = codexion

REMOVE = rm -f

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

all: $(NAME)

clean:
	$(REMOVE) $(OBJ)

fclean: clean
	$(REMOVE) $(NAME)

re: fclean all