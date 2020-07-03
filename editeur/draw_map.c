/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/07/03 14:32:32 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem_edit.h"

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
	draw_items(info, map);
	draw_props(info, map);
	draw_enemys(info, map);
}

void	draw_items(t_var *info, t_map *map)
{
	t_item		*item;
	SDL_Rect	pos;
	SDL_Surface	*texte;
	SDL_Color	color;

	color.r = 50;
	color.g = 205;
	color.b = 50;
	color.a = 255;
	item = map->items;
	while (item)
	{
		texte = TTF_RenderText_Blended(info->font, item->name, color);
		pos.x = item->x * ((WINDOW_H - 50) / map->size);
		pos.y = item->y * ((WINDOW_H - 50) / map->size);
		put_pixel_to_suface(GREEN, pos.x, pos.y, map->sectors->info->image);
		pos.x += NAME_DEC;
		pos.y += NAME_DEC;
		SDL_BlitSurface(texte, NULL, info->image, &pos);
		SDL_FreeSurface(texte);
		item = item->next_item;
	}
}

void	draw_props(t_var *info, t_map *map)
{
	t_prop		*prop;
	SDL_Rect	pos;
	SDL_Surface	*texte;
	SDL_Color	color;

	color.r = 255;
	color.g = 165;
	color.b = 0;
	color.a = 255;
	prop = map->props;
	while (prop)
	{
		texte = TTF_RenderText_Blended(info->font, prop->name, color);
		pos.x = prop->x * ((WINDOW_H - 50) / map->size);
		pos.y = prop->y * ((WINDOW_H - 50) / map->size);
		put_pixel_to_suface(ORANGE, pos.x, pos.y, map->sectors->info->image);
		pos.x += NAME_DEC;
		pos.y += NAME_DEC;
		SDL_BlitSurface(texte, NULL, info->image, &pos);
		SDL_FreeSurface(texte);
		prop = prop->next_prop;
	}
}

void	draw_enemys(t_var *info, t_map *map)
{
	t_enemy		*enemy;
	SDL_Rect	pos;
	SDL_Surface	*texte;
	SDL_Color	color;

	color.r = 255;
	color.g = 0;
	color.b = 0;
	color.a = 255;
	enemy = map->enemys;
	while (enemy)
	{
		texte = TTF_RenderText_Blended(info->font, enemy->name, color);
		pos.x = enemy->x * ((WINDOW_H - 50) / map->size);
		pos.y = enemy->y * ((WINDOW_H - 50) / map->size);
		put_pixel_to_suface(RED, pos.x, pos.y, map->sectors->info->image);
		pos.x += NAME_DEC;
		pos.y += NAME_DEC;
		SDL_BlitSurface(texte, NULL, info->image, &pos);
		SDL_FreeSurface(texte);
		enemy = enemy->next_enemy;
	}
}
