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
		dongle.c \
		pairs.c \
		scheduler.c

OBJS = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

REMOVE = rm -rf

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

burnout: all
	./codexion 4 100 50 50 50 5 0 edf

done: all
	./codexion 4 1000 50 50 50 5 0 edf

tests: all
	@fails=0; \
		for i in $$(seq 100); do \
			out=$$(./codexion 5 200 20 20 10 5 10 edf); \
			if [ $$? -eq 0 ] && ! echo "$$out" | grep -q "burned out"; then \
				echo "SUCCESS $$i"; \
			else \
				echo "FAIL $$i"; fails=$$((fails + 1)); \
			fi \
		done; \
		[ $$fails -eq 0 ] && echo "all runs passed" || { echo "$$fails/100 failed"; exit 1; }


valgrind: all
	valgrind --leak-check=full --show-leak-kinds=all ./codexion 5 100 20 20 10 5 10 edf

helgrind: all
	valgrind --tool=helgrind ./codexion 5 100 20 20 10 5 10 edf

clean:
	$(REMOVE) $(OBJ_DIR)

fclean: clean
	$(REMOVE) $(NAME)

re: fclean all

.PHONY = all burnout done tests valgrind helgrind clean fclean re
