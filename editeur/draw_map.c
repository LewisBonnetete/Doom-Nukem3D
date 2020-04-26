/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lewis <lewis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/04/26 17:51:06 by lewis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem_edit.h"

void	quitter(t_var *info)
{
	ft_putendl(SDL_GetError());
	SDL_DestroyWindow(info->window);
	SDL_Quit();
}

int		draw_state(t_sector *sector)
{
	t_var *info;
	t_map *map;

	info = sector->info;
	map = sector->map;
	draw_grid(info, map);
	draw_map_edit(info, map);
	if (!(info->texture =
	SDL_CreateTextureFromSurface(info->renderer, info->image)))
	{
		ft_putstr("Erreur CreateTextureFromSurface :\n");
		quitter(info);
		return (0);
	}
	if (SDL_RenderCopy(info->renderer, info->texture, NULL, NULL))
	{
		ft_putstr("Erreur RenderCopy :\n");
		quitter(info);
		return (0);
	}
	SDL_RenderPresent(info->renderer);
	SDL_DestroyTexture(info->texture);
	return (1);
}

void	draw_grid(t_var *info, t_map *map)
{
	int x;
	int y;

	x = -1;
	while (++x < WINDOW_H)
	{
		y = -1;
		while (++y < WINDOW_H)
		{
			if (x > 0 && x < WINDOW_H && y > 0 && y < WINDOW_H)
				put_pixel_to_suface(BLACK, x, y, info->image);
		}
	}
	x = 0;
	while (x < WINDOW_H - 50)
	{
		y = 0;
		while (y < WINDOW_H - 50)
		{
			if (x > 0 && x < WINDOW_H - 50 && y > 0 && y < WINDOW_H - 50)
				put_pixel_to_suface(WHITE, x, y, info->image);
			y += (WINDOW_H - 50) / map->size;
		}
		x += (WINDOW_H - 50) / map->size;
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
		if (sector->walls[i].b.x >= 0)
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
		if (sector->walls[i].b.x >= 0)
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

void	draw_portal_edit(t_var *info, t_map *map, t_sector *sector, int wall_id)
{
	t_line line;
	t_wall wall;

	wall = sector->walls[wall_id];
	if (wall.is_portal == 1)
	{
		line.x1 = wall.a.x * ((WINDOW_H - 50) / map->size);
		line.x2 = wall.b.x * ((WINDOW_H - 50) / map->size);
		line.y1 = wall.a.y * ((WINDOW_H - 50) / map->size);
		line.y2 = wall.b.y * ((WINDOW_H - 50) / map->size);
		draw_line(info, &line, BLUE);
	}
}

void	draw_map_edit(t_var *info, t_map *map)
{
	draw_sectors_edit(info, map);
}
