/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_sector.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/07/09 12:21:24 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem_edit.h"

void	del_enemys_if_in_sector(t_enemy *enemys, t_sector *sector)
{
	t_enemy *enemy;
	t_point new;

	enemy = enemys;
	while (enemy)
	{
		new.x = enemy->x;
		new.y = enemy->y;
		if (is_in_sector_spawn(new, sector))
			del_enemy(sector->map, enemy->x, enemy->y);
		enemy = enemy->next_enemy;
	}
}

void	del_props_if_in_sector(t_prop *props, t_sector *sector)
{
	t_prop	*prop;
	t_point	new;

	prop = props;
	while (prop)
	{
		new.x = prop->x;
		new.y = prop->y;
		if (is_in_sector_spawn(new, sector))
			del_prop(sector->map, prop->x, prop->y);
		prop = prop->next_prop;
	}
}

void	find_items_enemys_props(t_map *map, t_sector *sector)
{
	del_items_if_in_sector(map->items, sector);
	del_props_if_in_sector(map->props, sector);
	del_enemys_if_in_sector(map->enemys, sector);
}

void	del_sector2(t_map *map)
{
	int			sector_id;
	t_sector	*sector;
	t_sector	*previous_sector;

	sector_id = nbr_of_sectors(map);
	sector = get_to_last_sector(map->sectors);
	previous_sector = get_a_sector_by_id(map, sector_id - 1);
	find_items_enemys_props(map, sector);
	free(sector->walls);
	free(sector);
	previous_sector->next_sector = NULL;
	ft_putstr("Sector ");
	ft_putnbr(sector_id);
	ft_putendl(" Destroyed");
}

void	del_sector(t_var *info, t_map *map)
{
	int			sector_id;

	if (map->sectors)
	{
		sector_id = nbr_of_sectors(map);
		if (sector_id > 1)
			del_sector2(map);
		else if (sector_id == 1)
		{
			find_items_enemys_props(map, map->sectors);
			free(map->sectors->walls);
			free(map->sectors);
			map->sectors = NULL;
			ft_putendl("Sector 1 Destroyed");
		}
		draw_grid(info, map);
	}
}
