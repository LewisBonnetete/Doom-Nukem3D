/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lewis <lewis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/02/20 17:26:31 by lewis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem_edit.h"

void	draw_grid(t_var *info, t_map *map)
{
	int x;
	int y;

	x = 0;
	while(x < WINDOW_W)
	{
		y = 0;
		while (y < WINDOW_H)
		{
			if(x > 0 && x < WINDOW_W && y > 0 && y < WINDOW_H)
				put_pixel_to_suface(WHITE, x, y, info->image);
			y += WINDOW_H / map->size;
		}
		x += WINDOW_W / map->size;
	}
}

void	draw_sectors_edit(t_var *info, t_map *map)
{
	int x;
	int y;

	x = 0;
	while(x < WINDOW_W)
	{
		y = 0;
		while (y < WINDOW_H)
		{
			if(x > 0 && x < WINDOW_W && y > 0 && y < WINDOW_H)
				put_pixel_to_suface(WHITE, x, y, info->image);
			y += WINDOW_H / map->size;
		}
		x += WINDOW_W / map->size;
	}
}

void	draw_wall_edit(t_var *info, t_map *map, int sector_id, int wall_id)
{
	t_line line;
	t_wall wall;

	wall = map->sectors[sector_id].walls[wall_id];
	
	line.x1 = wall.a.x * (WINDOW_W / map->size);
	line.x2 = wall.b.x * (WINDOW_W / map->size);
	line.y1 = wall.a.y * (WINDOW_H / map->size);
	line.y2 = wall.b.y * (WINDOW_H / map->size);
	draw_line(info, &line);
	ft_putendl("1");
	line.x1 = wall.b.x * (WINDOW_W / map->size);
	line.x2 = wall.c.x * (WINDOW_W / map->size);
	line.y1 = wall.b.y * (WINDOW_H / map->size);
	line.y2 = wall.c.y * (WINDOW_H / map->size);
	draw_line(info, &line);
	ft_putendl("2");
	line.x1 = wall.c.x * (WINDOW_W / map->size);
	line.x2 = wall.d.x * (WINDOW_W / map->size);
	line.y1 = wall.c.y * (WINDOW_H / map->size);
	line.y2 = wall.d.y * (WINDOW_H / map->size);
	draw_line(info, &line);
	ft_putendl("3");
	line.x1 = wall.d.x * (WINDOW_W / map->size);
	line.x2 = wall.a.x * (WINDOW_W / map->size);
	line.y1 = wall.d.y * (WINDOW_H / map->size);
	line.y2 = wall.a.y * (WINDOW_H / map->size);
	draw_line(info, &line);	
	ft_putendl("4");
}

void	draw_map_edit(t_var *info, t_map *map)
{
	draw_grid(info, map);
	draw_sectors_edit(info, map);
	draw_wall_edit(info, map, 1, 0);
}