/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trabut <trabut@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 15:51:41 by lbonnete          #+#    #+#             */
/*   Updated: 2020/07/09 12:30:55 by trabut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void			rec_sec_tool(char *the_map, t_map *map, t_sector *sectors)
{
	if (the_map[map->i] == 'w')
		sectors->floor = rec_wall(the_map, map);
	if (the_map[map->i] == 'w')
		sectors->celling = rec_wall(the_map, map);
	rec_sectors_int(the_map, sectors, map);
	if (the_map[map->i] == 's')
		sectors->next_sector = rec_sectors(the_map, map);
	else
		sectors->next_sector = NULL;
	if (the_map[map->i] == 'm')
		sectors->map = map;
}

t_sector		*rec_sectors(char *the_map, t_map *map)
{
	int			g;
	t_sector	*sectors;

	++map->i;
	if (!((sectors) = (t_sector *)ft_memalloc(sizeof(t_sector))))
		return (0);
	if (the_map[map->i] == 'i')
		sectors->nbr_walls = rec_int(the_map, map);
	if (!((sectors->walls) = (t_wall *)ft_memalloc(sizeof(t_wall)
	* sectors->nbr_walls)))
		return (0);
	g = -1;
	if (the_map[map->i] == 'x')
	{
		++map->i;
		while (++g < sectors->nbr_walls)
			if (the_map[map->i] == 'w')
				sectors->walls[g] = rec_wall(the_map, map);
	}
	rec_sec_tool(the_map, map, sectors);
	return (sectors);
}

t_point			rec_point(char *the_map, t_map *map)
{
	t_point	point;

	++map->i;
	if (the_map[map->i] == 'i')
		point.x = rec_int(the_map, map);
	if (the_map[map->i] == 'i')
		point.y = rec_int(the_map, map);
	if (the_map[map->i] == 'i')
		point.z = rec_int(the_map, map);
	return (point);
}
