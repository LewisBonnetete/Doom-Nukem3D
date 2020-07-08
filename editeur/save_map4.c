/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_map4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/07/08 15:15:35 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem_edit.h"

int		do_x_wall(t_wall *wall, int fd, int g)
{
	char	c;
	int		x;

	c = 'x';
	if (write(fd, &c, 1) == -1)
		return (0);
	x = -1;
	while (++x < g)
		if (do_wall(wall[x], fd) == 0)
			return (0);
	return (1);
}

int		do_point(t_point point, int fd)
{
	char	c;

	c = 'p';
	if (write(fd, &c, 1) == -1)
		return (0);
	if (do_int(point.x, fd) == 0 || do_int(point.y, fd) == 0
	|| do_int(point.z, fd) == 0)
		return (0);
	return (1);
}

int		do_wall(t_wall wall, int fd)
{
	char	c;

	c = 'w';
	if (write(fd, &c, 1) == -1)
		return (0);
	if (do_point(wall.a, fd) == 0 || do_point(wall.b, fd) == 0
	|| do_point(wall.c, fd) == 0 || do_point(wall.d, fd) == 0)
		return (0);
	if (do_int(wall.text_id, fd) == 0 || do_int(wall.wall_id, fd) == 0
	|| do_int(wall.is_portal, fd) == 0 || do_int(wall.is_transparent, fd) == 0
	|| do_int(wall.is_textured, fd) == 0 || do_int(wall.fill_up, fd) == 0
	|| do_int(wall.fill_down, fd) == 0 || do_int(wall.sector_id, fd) == 0
	|| do_int(wall.sector_id_it_leads_to, fd) == 0)
		return (0);
	return (1);
}

int		do_double(double d, int fd)
{
	char	c;
	int		a;
	int		b;

	c = 'd';
	if (write(fd, &c, 1) == -1)
		return (0);
	a = (int)d;
	d = d - a;
	b = d * 10;
	if (do_int(b, fd) == 0 || do_int(a, fd) == 0)
		return (0);
	return (1);
}
