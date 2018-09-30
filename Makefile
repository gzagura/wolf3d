CFLAGS		= -Wall -Wextra -Werror
NAME		= wolf3d
SCR 		= src/main.c src/list_work.c src/get_next_line.c src/data_work.c
OBJ			= $(SRC:%.c=%.o)

.PHONY: norm all re clean fclean

all: $(NAME)

$(NAME): $(OBJ) ./libft/libft.a
	gcc $(CFLAGS)  $(SCR) -I ././includes -I /usr/local/include -I -r ././libft/libft.a  -lmlx -lXext -lX11 -L ./minilibx/ -I ./minilibx/ -lm -o $(NAME)

./libft/libft.a:
	@$(MAKE) -C ./libft

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all