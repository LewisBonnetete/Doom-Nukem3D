/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/07/10 13:36:20 by lbonnete         ###   ########.fr       */
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

void	init_norm1(t_norm1 *norm1, t_map *map)
{
	norm1->item = map->items;
	norm1->prop = map->props;
	norm1->enemy = map->enemys;
}

int		is_in_object(t_point new, t_map *map)
{
	t_norm1 norm1;

	init_norm1(&norm1, map);
	while (norm1.item || norm1.prop || norm1.enemy)
	{
		if (norm1.item)
		{
			if (norm1.item->x == new.x && norm1.item->y == new.y)
				return (0);
			norm1.item = norm1.item->next_item;
		}
		if (norm1.prop)
		{
			if (norm1.prop->x == new.x && norm1.prop->y == new.y)
				return (0);
			norm1.prop = norm1.prop->next_prop;
		}
		if (norm1.enemy)
		{
			if (norm1.enemy->x == new.x && norm1.enemy->y == new.y)
				return (0);
			norm1.enemy = norm1.enemy->next_enemy;
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
			new.x = x_coo(&event, map);
			new.y = y_coo(&event, map);
			ok = spawn_checks(new, map);
		}
		if (event.key.keysym.sym == SDLK_d && event.key.state == SDL_PRESSED)
		{
			ft_putendl("Back to creation");
			return (0);
		}
	}
	map->spawn.x = new.x;
	map->spawn.y = new.y;
	return (1);
}
