/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_map3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/07/16 16:49:48 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem_edit.h"

int		do_item(t_item *tem, int fd)
{
	char	c;

	c = 't';
	if (write(fd, &c, 1) == -1)
		return (0);
	if (tem->name)
		if (do_x_char(tem->name, fd) == 0)
			return (0);
	if (do_int(tem->x, fd) == 0)
		return (0);
	if (do_int(tem->y, fd) == 0)
		return (0);
	if (tem->next_item)
		do_item(tem->next_item, fd);
	return (1);
}

int		do_prop(t_prop *prop, int fd)
{
	char	c;

	c = 't';
	if (write(fd, &c, 1) == -1)
		return (0);
	if (prop->name)
		if (do_x_char(prop->name, fd) == 0)
			return (0);
	if (do_int(prop->x, fd) == 0)
		return (0);
	if (do_int(prop->y, fd) == 0)
		return (0);
	if (prop->next_prop)
		do_prop(prop->next_prop, fd);
	return (1);
}

int		do_box(t_box box, int fd)
{
	int		x;
	char	c;

	c = 'b';
	x = -1;
	if (write(fd, &c, 1) == -1)
		return (0);
	while (++x < 5)
		if (do_wall(box.walls[x], fd) == 0)
			return (0);
	if (do_int(box.nbr_walls, fd) == 0)
		return (0);
	if (do_int(box.size, fd) == 0)
		return (0);
	if (do_wall(box.floor, fd) == 0 || do_wall(box.celling, fd) == 0)
		return (0);
	return (1);
}

int		do_sectors(t_sector *sectors, int fd)
{
	char	c;

	c = 's';
	if (write(fd, &c, 1) == -1)
		return (0);
	if (do_int(sectors->nbr_walls, fd) == 0)
		return (0);
	if (do_x_wall(sectors->walls, fd, sectors->nbr_walls) == 0)
		return (0);
	if (do_wall(sectors->floor, fd) == 0 || do_wall(sectors->celling, fd) == 0)
		return (0);
	if (do_int(sectors->light, fd) == 0 || do_int(sectors->sector_id, fd) == 0)
		return (0);
	if (sectors->next_sector)
		if (do_sectors(sectors->next_sector, fd) == 0)
			return (0);
	return (1);
}
