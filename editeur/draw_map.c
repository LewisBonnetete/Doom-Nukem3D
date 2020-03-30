/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lewis <lewis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/03/30 16:42:45 by lewis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem_edit.h"

int	draw_state(t_sector *sector)
{
	t_var *info;
	t_map *map;


	info = sector->info;
	map = sector->map;
	draw_map_edit(info, map);
	draw_sector_edit(info, map, sector);
	if (!(info->texture = SDL_CreateTextureFromSurface(info->renderer, info->image)))
	{
		ft_putstr("Erreur CreateTextureFromSurface :\n");
		ft_putendl(SDL_GetError());
		SDL_DestroyWindow(info->window);
		SDL_Quit();
		return (0);
	}
	if (SDL_RenderCopy(info->renderer, info->texture, NULL, NULL))
	{
		ft_putstr("Erreur RenderCopy :\n");
		ft_putendl(SDL_GetError());
		SDL_DestroyWindow(info->window);
		SDL_Quit();
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

	x = 0;
	while(x < WINDOW_H)
	{
		y = 0;
		while (y < WINDOW_H)
		{
			if(x > 0 && x < WINDOW_H && y > 0 && y < WINDOW_H)
				put_pixel_to_suface(BLACK, x, y, info->image);
			y += 1;
		}
		x += 1;
	}
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
	
	if (map->sectors)
	{
		sector = map->sectors;
		while(sector != NULL)
		{
			draw_sector_edit(info, map, sector);
			sector = sector->next_sector;
		}
	}
}

void	draw_sector_edit(t_var *info, t_map *map, t_sector *sector)
{
	int i;
	int max;

	i = 0;
	ft_putendl("");
	ft_putstr("euh...  (draw_map/draw_sector_edit)  ");
	max = sector->nbr_walls;
	ft_putendl("la c'est bon");
	while (i < max)
	{
		if (sector->walls[i].b.x >= 0)
		{
			draw_wall_edit(info, map, sector, i);
		}
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
	draw_sectors_edit(info, map);
}