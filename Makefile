# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gzagura <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/18 15:30:02 by gzagura           #+#    #+#              #
#    Updated: 2018/10/18 15:30:04 by gzagura          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS		= -Wall -Wextra -Werror
NAME		= wolf3d
SRC_NAME 	= main.c get_next_line.c data_work.c draw.c le_hook.c floor_ceiling.c help_draw.c
LIBFT_DIR	= ./libft/
LIBFT		= ./libft/libft.a
SRC			=$(addprefix ./src/, $(SRC_NAME))
OBJ			= $(SRC:%.c=%.o)

.PHONY: norm all re clean fclean

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	gcc $(CFLAGS) $(OBJ) -I ./includes -I /usr/local/include -I -r $(LIBFT) -L /usr/local/lib -lmlx -framework OpenGL -framework AppKit -o $(NAME) -lm 

%.o:%.c $(LIBFT) ./includes/wolf.h
	gcc $(CFLAGS) -c $< -o $@ -I ./includes

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
