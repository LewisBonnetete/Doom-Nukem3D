/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/07/16 15:53:54 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem_edit.h"
#include <sys/stat.h>

int		do_x_char(char *str, int fd)
{
	int		x;
	char	c;

	c = 'e';
	if (write(fd, &c, 1) == -1)
		return (0);
	x = -1;
	while (str[++x])
		if (write(fd, &str[x], 1) == -1)
			return (0);
	return (1);
}

int		do_char(char c, int fd)
{
	char	a;

	a = 'c';
	if (write(fd, &a, 1) == -1)
		return (0);
	if (write(fd, &c, 1) == -1)
		return (0);
	return (1);
}

int		do_int(int i, int fd)
{
	char	*c;
	char	b;
	int		r;

	b = 'i';
	if (write(fd, &b, 1) == -1)
		return (0);
	if (i < 0)
	{
		if (write(fd, "0", 1) == -1)
			return (0);
	}
	else
	{
		c = ft_itoa(i);
		r = -1;
		while (c[++r])
			if (write(fd, &c[r], 1) == -1)
			{
				ft_strdel(&c);
				return (0);
			}
	}
	ft_strdel(&c);
	return (1);
}

int		creat_fichier(t_map *map, char *name)
{
	int		fd;

	if ((fd = open("../core", O_APPEND | O_RDWR)) == -1)
		return (0);
	ft_putstr_fd(name, fd);
	ft_putchar_fd(';', fd);
	if (do_map(map, fd) == 0)
		return (0);
	ft_putendl_fd("", fd);
	close(fd);
	return (1);
}
