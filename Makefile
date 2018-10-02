CFLAGS		= -Wall -Wextra -Werror
NAME		= wolf3d
SRC_NAME 	= main.c list_work.c get_next_line.c data_work.c
LIBFT_DIR	= ./libft/
LIBFT		= ./libft/libft.a
SRC			=$(addprefix ./src/, $(SRC_NAME))
OBJ			= $(SRC:%.c=%.o)

.PHONY: norm all re clean fclean

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	gcc $(CFLAGS) $(OBJ) -I ./includes -I /usr/local/include -I -r $(LIBFT) -L /usr/local/lib -lmlx -framework OpenGL -framework AppKit -o $(NAME)

# macos gcc $(CFLAGS) $(OBJ) -I /usr/local/include -I -r $(LIBFT) -L /usr/local/lib -lmlx -framework OpenGL -framework AppKit -o $(NAME)
# linux gcc $(CFLAGS)  $(SCR) -I ././includes -I /usr/local/include -I -r ././libft/libft.a  -lmlx -lXext -lX11 -L ./minilibx/ -I ./minilibx/ -lm -o $(NAME)

%.o:%.c $(LIBFT) ./includes/wolf.h
	gcc $(CFLAGS) -c $< -o $@ -I ./includes

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all