# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/12 18:24:53 by lbonnete          #+#    #+#              #
#    Updated: 2020/02/06 15:11:08 by lbonnete         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = ft_lstnew.c\
	ft_sqrt.c\
	ft_strncpy.c\
	ft_memalloc.c\
	ft_strcat.c\
	ft_strnequ.c\
	ft_atoi.c\
	ft_memccpy.c\
	ft_strchr.c\
	ft_strnew.c\
	ft_bzero.c\
	ft_memchr.c\
	ft_strclr.c\
	ft_strnstr.c\
	ft_count_letters.c\
	ft_memcmp.c\
	ft_strcmp.c\
	ft_strrchr.c\
	ft_count_words.c\
	ft_memcpy.c\
	ft_strcpy.c\
	ft_strsplit.c\
	ft_intlen.c\
	ft_memdel.c\
	ft_strdel.c\
	ft_strstr.c\
	ft_isalnum.c\
	ft_memmove.c\
	ft_strdup.c\
	ft_strsub.c\
	ft_isalpha.c\
	ft_memset.c\
	ft_strequ.c\
	ft_strtrim.c\
	ft_isascii.c\
	ft_putchar.c\
	ft_striter.c\
	ft_swap.c\
	ft_isdigit.c\
	ft_putchar_fd.c\
	ft_striteri.c\
	ft_tolower.c\
	ft_isprint.c\
	ft_putendl.c\
	ft_strjoin.c\
	ft_toupper.c\
	ft_itoa.c\
	ft_putendl_fd.c\
	ft_strlcat.c\
	intmin.c\
	ft_lstadd.c\
	ft_putnbr.c\
	ft_strlen.c\
	ft_lstdel.c\
	ft_putnbr_fd.c\
	ft_strmap.c\
	ft_lstdelone.c\
	ft_putstr.c\
	ft_strmapi.c\
	ft_lstiter.c\
	ft_putstr_fd.c\
	ft_strncat.c\
	ft_lstmap.c\
	ft_recursive_factorial.c\
	ft_strncmp.c\
	ft_count_sep.c\
	get_next_line.c
		

OBJ = ft_lstnew.o\
	ft_sqrt.o\
	ft_strncpy.o\
	ft_memalloc.o\
	ft_strcat.o\
	ft_strnequ.o\
	ft_atoi.o\
	ft_memccpy.o\
	ft_strchr.o\
	ft_strnew.o\
	ft_bzero.o\
	ft_memchr.o\
	ft_strclr.o\
	ft_strnstr.o\
	ft_count_letters.o\
	ft_memcmp.o\
	ft_strcmp.o\
	ft_strrchr.o\
	ft_count_words.o\
	ft_memcpy.o\
	ft_strcpy.o\
	ft_strsplit.o\
	ft_intlen.o\
	ft_memdel.o\
	ft_strdel.o\
	ft_strstr.o\
	ft_isalnum.o\
	ft_memmove.o\
	ft_strdup.o\
	ft_strsub.o\
	ft_isalpha.o\
	ft_memset.o\
	ft_strequ.o\
	ft_strtrim.o\
	ft_isascii.o\
	ft_putchar.o\
	ft_striter.o\
	ft_swap.o\
	ft_isdigit.o\
	ft_putchar_fd.o\
	ft_striteri.o\
	ft_tolower.o\
	ft_isprint.o\
	ft_putendl.o\
	ft_strjoin.o\
	ft_toupper.o\
	ft_itoa.o\
	ft_putendl_fd.o\
	ft_strlcat.o\
	intmin.o\
	ft_lstadd.o\
	ft_putnbr.o\
	ft_strlen.o\
	ft_lstdel.o\
	ft_putnbr_fd.o\
	ft_strmap.o\
	ft_lstdelone.o\
	ft_putstr.o\
	ft_strmapi.o\
	ft_lstiter.o\
	ft_putstr_fd.o\
	ft_strncat.o\
	ft_lstmap.o\
	ft_recursive_factorial.o\
	ft_strncmp.o\
	ft_count_sep.o\
	get_next_line.o

all: $(NAME)

$(NAME): $(OBJ)
	@echo "\nBuilding libft...\n"
	@gcc -c -Wall -Wextra -Werror $(SRC)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo "Compilation Successful"
	@echo "libft Ready"

a: all clean

clean:
	@/bin/rm -f $(OBJ)

fclean:	clean
		@/bin/rm -f $(NAME)
		@echo "Library Destroyed"

re:	fclean all

norm:
	@norminette $(SRC) $(INC)

.PHONY:	all clean fclean re norm
