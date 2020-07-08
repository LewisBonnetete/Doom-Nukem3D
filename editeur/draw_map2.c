/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/07/08 14:33:07 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem_edit.h"

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

void	draw_grid2(t_var *info, t_map *map)
{
	int x;
	int y;

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
	draw_grid2(info, map);
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
