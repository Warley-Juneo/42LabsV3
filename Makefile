LIBFT = ./libft/libft.a

SRC = monitoring.c init.c times.c parse.c utils.c monitoring_aux.c send_terminal.c


OBJ_PATH = objects
OBJ_SRC = $(SRC:%.c=$(OBJ_PATH)/%.o)
OBJ_SRC = $(patsubst %.c,$(OBJ_PATH)/%.o, $(SRC))

VPATH = ./src
NAME = monitoring

CC = gcc -g3
CFLAGS = -lcurl -lpthread
RM = rm -rf

$(OBJ_PATH)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all:	$(NAME)

$(NAME):	$(OBJ_PATH) $(LIBFT) $(OBJ_SRC)
			$(CC) $(OBJ_SRC) $(CFLAGS) $(LIBFT) -o $(NAME)

$(OBJ_PATH):
			mkdir -p $(OBJ_PATH)

$(LIBFT):
			make -C ./libft

clean:
			make -C ./libft clean
			$(RM) $(OBJ_PATH)

fclean:		clean
			make -C ./libft fclean
			$(RM) $(OBJ_PATH) $(NAME)

re:			clean fclean all

run:		$(NAME)
			./$(NAME)

runs:		$(NAME)
			./$(NAME) --simplify

.PHONY: all clean fclean re
