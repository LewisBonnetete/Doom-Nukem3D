/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trabut <trabut@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/07/09 15:21:13 by trabut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int		is_valid_wall(SDL_Event *event, t_sector *sector, int i)
{
	t_point		new;
	t_point		old;

	new.x = round(((float)event->button.x
	/ (float)(WINDOW_H - 50) * sector->map->size));
	new.y = round(((float)event->button.y
	/ (float)(WINDOW_H - 50) * sector->map->size));
	old.x = sector->walls[i - 1].a.x;
	old.y = sector->walls[i - 1].a.y;
	if (event->button.x <= 0 || event->button.x >= WINDOW_H - 50 || new.x <= 0)
		return (0);
	if (event->button.y <= 0 || event->button.y >= WINDOW_H - 50 || new.y <= 0)
		return (0);
	if (!is_new_point_in_sector(new, sector->walls))
		return (0);
	if (!verify_crossing(new, old, sector))
		return (0);
	if (!center_in_poly(new, old, sector))
		return (0);
	return (1);
}

int		is_valid_last_wall2(t_point new, t_point old, t_sector *sector)
{
	if (!is_new_point_in_sector(new, sector->walls))
		return (0);
	if (!verify_crossing(new, old, sector))
		return (0);
	if (!center_in_poly(new, old, sector))
		return (0);
	return (1);
}

int		is_valid_last_wall(SDL_Event *event, t_sector *sector, int i)
{
	t_point		new;
	t_point		old;

	new.x = round(((float)event->button.x
	/ (float)(WINDOW_H - 50) * sector->map->size));
	new.y = round(((float)event->button.y
	/ (float)(WINDOW_H - 50) * sector->map->size));
	old.x = sector->walls[i - 1].a.x;
	old.y = sector->walls[i - 1].a.y;
	if (event->button.x <= 0 || event->button.x >= WINDOW_H - 50 || new.x <= 0)
		return (0);
	if (event->button.y <= 0 || event->button.y >= WINDOW_H - 50 || new.y <= 0)
		return (0);
	if (is_valid_last_wall2(new, old, sector) == 0)
		return (0);
	old.x = sector->walls[0].a.x;
	old.y = sector->walls[0].a.y;
	if (!verify_crossing(new, old, sector))
		return (0);
	if (!center_in_poly(new, old, sector))
		return (0);
	return (1);
}

int		is_valid_first_wall(SDL_Event *event, t_map *map)
{
	t_point first;
	float	temp;

	if (event->button.x <= 0 || event->button.x >= WINDOW_H - 50)
		return (0);
	if (event->button.y <= 0 || event->button.y >= WINDOW_H - 50)
		return (0);
	temp = (float)event->button.x / (float)(WINDOW_H - 50) * map->size;
	first.x = round(temp);
	temp = (float)event->button.y / (float)(WINDOW_H - 50) * map->size;
	first.y = round(temp);
	if (!is_in_sectors(first, map))
	{
		ft_putendl("Can't build a sector inside another");
		return (0);
	}
	return (1);
}
