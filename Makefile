LIBFT = ./libft/libft.a

SRC = monitoring.c init.c times.c parse.c utils.c monitoring_aux.c
HEADERS = ./includes/monitoring.h

OBJ_PATH = objects
OBJ_SRC = $(SRC:%.c=$(OBJ_PATH)/%.o)
OBJ_SRC = $(patsubst %.c,$(OBJ_PATH)/%.o, $(SRC))

NAME = monitoring

CC = gcc -g3
CFLAGS = -lcurl -lpthread
RM = rm -rf

$(OBJ_PATH)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all:	$(NAME)

$(NAME):	$(OBJ_PATH) $(LIBFT) $(OBJ_SRC) $(HEADERS)
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

.PHONY: all clean fclean re
