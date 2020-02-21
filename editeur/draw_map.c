/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lewis <lewis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/02/21 15:48:56 by lewis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem_edit.h"

void	draw_grid(t_var *info, t_map *map)
{
	int x;
	int y;

	x = 0;
	while(x < WINDOW_H)
	{
		y = 0;
		while (y < WINDOW_H)
		{
			if(x > 0 && x < WINDOW_H && y > 0 && y < WINDOW_H)
				put_pixel_to_suface(WHITE, x, y, info->image);
			y += WINDOW_H / map->size;
		}
		x += WINDOW_H / map->size;
	}
	draw_cadre(info);
}

void	draw_cadre(t_var *info)
{
	t_line line;

	line.x1 = 0;
	line.x2 = WINDOW_H;
	line.y1 = 0;
	line.y2 = 0;
	draw_line(info, &line, WHITE);
	line.x1 = WINDOW_H;
	line.x2 = WINDOW_H;
	line.y1 = 0;
	line.y2 = WINDOW_H;
	draw_line(info, &line, WHITE);
	line.x1 = 0;
	line.x2 = WINDOW_H;
	line.y1 = WINDOW_H - 1;
	line.y2 = WINDOW_H - 1;
	draw_line(info, &line, WHITE);
	line.x1 = 0;
	line.x2 = 0;
	line.y1 = 0;
	line.y2 = WINDOW_H;
	draw_line(info, &line, WHITE);
}

void	draw_sectors_edit(t_var *info, t_map *map)
{
	t_sector *sector;

	sector = map->sectors;
	while(sector != NULL)
	{
		draw_sector_edit(info, map, sector);
		sector = sector->next_sector;
	}
}

void	draw_sector_edit(t_var *info, t_map *map, t_sector *sector)
{
	int i;

	i = 0;
	while (i < sector->nbr_walls)
	{
		draw_wall_edit(info, map, sector, i);
		i++;
	}	
}

void	draw_wall_edit(t_var *info, t_map *map, t_sector *sector, int wall_id)
{
	t_line line;
	t_wall wall;
	Uint32 color;

	color = WHITE;
	wall = sector->walls[wall_id];
	if(wall.is_portal)
		color = BLUE;
	line.x1 = wall.a.x * (WINDOW_H / map->size);
	line.x2 = wall.b.x * (WINDOW_H / map->size);
	line.y1 = wall.a.y * (WINDOW_H / map->size);
	line.y2 = wall.b.y * (WINDOW_H / map->size);
	draw_line(info, &line, color);
}

void	draw_map_edit(t_var *info, t_map *map)
{
	draw_grid(info, map);
	draw_sectors_edit(info, map);
}