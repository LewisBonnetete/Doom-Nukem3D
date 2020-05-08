# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lewis <lewis@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/18 15:34:09 by trabut            #+#    #+#              #
#    Updated: 2020/05/08 18:01:48 by lewis            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = doom-nukem

FLAGS       = -O3 -Wextra -Wall -Werror

SDL			= -lpthread -F ./frameworks/ -framework SDL2 -framework SDL2_image
SDL_HEADER	= -I ./frameworks/SDL2.framework/Headers -I ./frameworks/SDL2_image.framework/Headers

LIBFT = libft/libft.a

CC = gcc

HEAD_DIR = inc
SRC_DIR	 = src
OBJ_DIR	 = obj

SRC =	main.c\
		sdl_init.c\
		game_init.c\
		algo_intersection.c\
		algo_draw.c\
		algo.c\
		map_init.c\
		move.c\
		load_map.c
		
INC = doom-nukem.h
OBJ	= $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC))

$(shell mkdir -p $(OBJ_DIR))

all: $(NAME)
	echo "doom-nukem ready"

$(NAME): $(OBJ) $(LIBFT)
	$(CC) -I $(HEAD_DIR) -o $@ $(OBJ) $(SDL) $(LIBFT) $(FLAGS)


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -I $(HEAD_DIR) -o $@ $(SDL_HEADER) -c $< $(FLAGS)

$(LIBFT):
	make -C libft/ libft.a

p: all clean

clean:
	make clean -C libft
	/bin/rm -f $(OBJ)
	echo "Objects Destroyed"

fclean:	clean
	make fclean -C libft
	/bin/rm -f $(NAME)
	echo "Project Destroyed"

re:	fclean all

.PHONY:	all clean fclean re norm p

.SILENT:
