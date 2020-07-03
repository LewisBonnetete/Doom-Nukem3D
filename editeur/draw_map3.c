/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/07/03 14:32:38 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem_edit.h"

void	draw_sectors_edit(t_var *info, t_map *map)
{
	t_sector *sector;

	if (map->sectors)
	{
		sector = map->sectors;
		while (sector != NULL)
		{
			draw_sector_wall_edit(info, map, sector);
			sector = sector->next_sector;
		}
		sector = map->sectors;
		while (sector != NULL)
		{
			draw_sector_portal_edit(info, map, sector);
			sector = sector->next_sector;
		}
	}
}

void	draw_sector_wall_edit(t_var *info, t_map *map, t_sector *sector)
{
	int i;
	int max;

	i = 0;
	max = sector->nbr_walls;
	while (i < max)
	{
		if (sector->walls[i].b.x > 0)
		{
			draw_wall_edit(info, map, sector, i);
		}
		i++;
	}
}

void	draw_sector_portal_edit(t_var *info, t_map *map, t_sector *sector)
{
	int i;
	int max;

	i = 0;
	max = sector->nbr_walls;
	while (i < max)
	{
		if (sector->walls[i].b.x > 0)
		{
			draw_portal_edit(info, map, sector, i);
		}
		i++;
	}
}

void	draw_wall_edit(t_var *info, t_map *map, t_sector *sector, int wall_id)
{
	t_line line;
	t_wall wall;

	wall = sector->walls[wall_id];
	if (wall.is_portal == 0)
	{
		line.x1 = wall.a.x * ((WINDOW_H - 50) / map->size);
		line.x2 = wall.b.x * ((WINDOW_H - 50) / map->size);
		line.y1 = wall.a.y * ((WINDOW_H - 50) / map->size);
		line.y2 = wall.b.y * ((WINDOW_H - 50) / map->size);
		draw_line(info, &line, WHITE);
	}
}
