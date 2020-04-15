/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lewis <lewis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/04/15 18:33:28 by lewis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem_edit.h"

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

int		spawn_checks(t_point new, t_map *map)
{
	if (!is_in_sectors_spawn(new, map))
	{
		ft_putendl("Spawn must be in a sector or a bigger one");
		return (0);
	}
	if (!is_new_point_in_sectors(new, map))
	{
		ft_putendl("Spawn can't be inside a wall");
		return (0);
	}
	return (1);
}

int		set_spawn(t_map *map)
{
	int ok;
	t_point new;
	SDL_Event event;
	float	temp;

	ok = 0;
	ft_putendl("Set your Spawn");
	while(ok == 0)
	{
		SDL_WaitEvent(&event);
		if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			temp = (float)event.button.x / (float)(WINDOW_H - 50) * map->size;
			new.x = round(temp);
			temp = (float)event.button.y / (float)(WINDOW_H - 50) * map->size;
			new.y = round(temp);
			printf("spawn: %i | %i\n",new.x,new.y);
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
	printf("spawn: %i | %i | %i\n",map->spawn.x,map->spawn.y,map->spawn.z);
	return (1);
}