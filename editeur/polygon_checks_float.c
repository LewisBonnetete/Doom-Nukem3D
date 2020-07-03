/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polygon_checks_float.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/07/03 14:39:27 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem_edit.h"

int		pnpoly_float(int nbr_walls, t_wall *walls,
float center_x, float center_y)
{
	int i;
	int j;
	int c;

	i = 0;
	j = nbr_walls - 1;
	c = 0;
	while (i < nbr_walls)
	{
		if ((((float)walls[i].a.y > center_y)
		!= ((float)walls[j].a.y > center_y))
		&& (center_x < ((float)walls[j].a.x - (float)walls[i].a.x)
		* (center_y - (float)walls[i].a.y)
		/ ((float)walls[j].a.y - (float)walls[i].a.y) + (float)walls[i].a.x))
			c++;
		j = i++;
	}
	return (c % 2);
}

int		is_in_sector_float(float center_x, float center_y, t_sector *sector)
{
	if (pnpoly_float(sector->nbr_walls, sector->walls, center_x, center_y))
	{
		return (0);
	}
	return (1);
}

int		is_in_sectors_float(float center_x, float center_y, t_map *map)
{
	t_sector *current_sector;

	current_sector = map->sectors;
	while (current_sector->next_sector)
	{
		if (!is_in_sector_float(center_x, center_y, current_sector))
			return (0);
		current_sector = current_sector->next_sector;
	}
	return (1);
}
