/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polygon_checks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/07/03 14:39:24 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem_edit.h"

int		is_in_sectors(t_point first, t_map *map)
{
	t_sector *current_sector;

	current_sector = map->sectors;
	while (current_sector->next_sector)
	{
		if (!is_in_sector(first, current_sector))
			return (0);
		current_sector = current_sector->next_sector;
	}
	return (1);
}

int		pnpoly_spawn(int nbr_walls, t_wall *walls, t_point first)
{
	int i;
	int j;
	int c;

	i = 0;
	j = nbr_walls - 1;
	c = 0;
	while (i < nbr_walls)
	{
		if (!is_new_point_in_sector(first, walls))
			return (0);
		if (((walls[i].a.y >= first.y) != (walls[j].a.y >= first.y))
		&& (first.x <= (walls[j].a.x - walls[i].a.x) * (first.y - walls[i].a.y)
		/ (walls[j].a.y - walls[i].a.y) + walls[i].a.x))
			c = !c;
		j = i++;
	}
	return (c);
}

int		is_in_sector_spawn(t_point first, t_sector *sector)
{
	if (pnpoly_spawn(sector->nbr_walls, sector->walls, first))
	{
		sector->map->spawn.z = sector->walls[0].d.z;
		sector->map->spawn_sector_id = sector->sector_id;
		return (1);
	}
	return (0);
}

int		is_in_sectors_spawn(t_point first, t_map *map)
{
	t_sector *current_sector;

	current_sector = map->sectors;
	while (current_sector)
	{
		if (is_in_sector_spawn(first, current_sector))
			return (1);
		current_sector = current_sector->next_sector;
	}
	return (0);
}
