# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/18 15:34:09 by trabut            #+#    #+#              #
#    Updated: 2020/06/17 14:43:25 by lbonnete         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = editeur

FLAGS       = -Wall -Wextra -Werror -O3

SDL			= -lpthread -F ../frameworks/ -framework SDL2 -framework SDL2_image -framework SDL2_ttf 
SDL_HEADER	= -I ../frameworks/SDL2.framework/Headers -I ../frameworks/SDL2_image.framework/Headers -I ../frameworks/SDL2_ttf.framework/Headers

LIBFT = ../libft/libft.a

CC = gcc

HEAD_DIR = ./
SRC_DIR	 = ./
OBJ_DIR	 = ./

SRC =	main.c\
		init.c\
		sdl_init.c\
		editer.c\
		dealers_edit.c\
		map_creator.c\
		init_interact.c\
		draw_map.c\
		editer_tools.c\
		exit_edit.c\
		del_sector.c\
		valid_wall.c\
		polygon_checks.c\
		polygon_checks_float.c\
		points_comparator.c\
		validate.c\
		spawn.c\
		portals.c\
		hud.c\
		hud_tools.c\
		save_map.c\
		item.c\
		prop.c\
		enemy.c

INC = doom-nukem_edit.h
OBJ	= $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC))

$(shell mkdir -p $(OBJ_DIR))

all: $(NAME)
	echo "Editeur ready"

$(NAME): $(OBJ) $(LIBFT) 
	$(CC) -I $(HEAD_DIR) -o $@ $(OBJ) $(SDL) $(LIBFT) $(FLAGS) 


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -I $(HEAD_DIR) -o $@ $(SDL_HEADER) -c $< $(FLAGS)

$(LIBFT):
	make -C ../libft/ libft.a

p: all clean

clean:
	make clean -C ../libft
	/bin/rm -f $(OBJ)
	echo "Objects Destroyed"

fclean:	clean
	make fclean -C ../libft
	/bin/rm -f $(NAME)
	echo "Project Destroyed"

re:	fclean all

.PHONY:	all clean fclean re norm p

.SILENT:
