/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/07/07 16:50:32 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem_edit.h"

int		is_new_point_in_sectors(t_point new, t_map *map)
{
	t_sector *sector;

	sector = map->sectors;
	while (sector->next_sector)
	{
		if (!is_new_point_in_sector(new, sector->walls))
			return (0);
		sector = sector->next_sector;
	}
	return (1);
}

int		is_in_object(t_point new, t_map *map)
{
	t_item	*item;
	t_prop	*prop;
	t_enemy *enemy;

	item = map->items;
	prop = map->props;
	enemy = map->enemys;
	while (item || prop || enemy)
	{
		if (item)
		{
			if (item->x == new.x && item->y == new.y)
				return (0);
			item = item->next_item;
		}
		if (prop)
		{
			if (prop->x == new.x && prop->y == new.x)
				return (0);
			prop = prop->next_prop;
		}
		if (enemy)
		{
			if (enemy->x == new.x && enemy->y == new.y)
				return (0);
			enemy = enemy->next_enemy;
		}
	}
	return (1);
}

int		spawn_checks(t_point new, t_map *map)
{
	if (!is_in_sectors_spawn(new, map))
	{
		ft_putendl("Spawn musts be in a sector");
		return (0);
	}
	if (!is_new_point_in_sectors(new, map))
	{
		ft_putendl("Spawn can't be inside a wall");
		return (0);
	}
	if (!is_in_object(new, map))
	{
		ft_putendl("Spawn can't be inside something");
		return (0);
	}
	if (new.x == map->end.x && new.y == map->end.y)
	{
		ft_putendl("Spawn can't be on the end");
		return (0);
	}
	return (1);
}

int		set_spawn(t_map *map)
{
	int			ok;
	t_point		new;
	SDL_Event	event;

	ok = 0;
	ft_putendl("Set your Spawn");
	while (ok == 0)
	{
		SDL_WaitEvent(&event);
		if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			new.x = round(((float)event.button.x
			/ (float)(WINDOW_H - 50) * map->size));
			new.y = round(((float)event.button.y
			/ (float)(WINDOW_H - 50) * map->size));
			ok = spawn_checks(new, map);
		}
		else if (event.key.keysym.sym == SDLK_d)
		{
			ft_putendl("Back to creation");
			return (0);
		}
	}
	map->spawn.x = new.x;
	map->spawn.y = new.y;
	printf("spawn: %i | %i | %i\n", map->spawn.x, map->spawn.y, map->spawn.z);
	return (1);
}
