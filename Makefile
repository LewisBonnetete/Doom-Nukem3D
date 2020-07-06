# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/18 15:34:09 by trabut            #+#    #+#              #
#    Updated: 2020/07/03 17:04:46 by lbonnete         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = doom-nukem

FLAGS       = -O2 -O3

SDL			= -lpthread -F ./frameworks/ -framework SDL2 -framework SDL2_image -framework SDL2_ttf
SDL_HEADER	= -I ./frameworks/SDL2.framework/Headers -I ./frameworks/SDL2_image.framework/Headers -I ./frameworks/SDL2_ttf.framework/Headers

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
		load_map.c\
		check_map.c\
		tools.c\
		textures.c\
		tools2.c\
		valid_wall.c\
		polygon_checks.c\
		editer_tools.c\
		points_comparator.c\
		polygon_checks_float.c\
		hud.c\
		hud2.c\
		draw_tools.c\
		algo_tools.c\
		math_tools.c\
		gameplay.c\
		dealers.c\
		dealers2.c\
		dealers3.c\
		dealers4.c\
		rain.c
		
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
