# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: trabut <trabut@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/18 15:34:09 by trabut            #+#    #+#              #
#    Updated: 2020/07/23 16:02:01 by trabut           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = doom-nukem

FLAGS       = -O2 -Wextra -Werror -W -Wall

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
		algo2.c\
		move.c\
		hitbox.c\
		item_tools2.c\
		item_tools3.c\
		algo3.c\
		algo4.c\
		item_tools.c\
		load_map.c\
		check_map.c\
		tools.c\
		tools2.c\
		load_map3.c\
		load_map4.c\
		valid_wall.c\
		polygon_checks.c\
		editer_tools.c\
		points_comparator.c\
		polygon_checks_float.c\
		hud.c\
		hud2.c\
		hud3.c\
		draw_tools.c\
		algo_tools.c\
		math_tools.c\
		dealers.c\
		dealers2.c\
		dealers3.c\
		rain.c\
		shoot.c\
		tools_draw.c\
		change_weapon.c\
		gameplay.c\
		item_tool.c\
		load_map1.c\
		load_map2.c\
		png_parser.c\
		tools3.c\
		tools4.c\
		valid_wall2.c\
		check_wall_intersections.c\
		comparator.c\

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
