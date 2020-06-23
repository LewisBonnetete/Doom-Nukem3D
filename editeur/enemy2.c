/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/06/23 16:45:34 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem_edit.h"

void	create_enemy(t_map *map)
{
	int valid_coo = 0;
	int x;
	int y;
	float temp;
	SDL_Event	event;

	ft_putendl("Place your enemy");
	while(valid_coo == 0)
	{
		SDL_WaitEvent(&event);
		if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			temp = (float)event.button.x / (float)(WINDOW_H - 50) * map->size;
			x = round(temp);
			temp = (float)event.button.y / (float)(WINDOW_H - 50) * map->size;
			y = round(temp);
			if (valid_new_enemy(map, x, y))
			{
				valid_coo = 1;
				if (!add_enemy(map, get_enemy_name(), x, y))
					exit_edit(map->sectors->info, map);
			}
			else
			{
				ft_putendl("You can't put an enemy here");
			}
		}
	}
}

char 	*get_enemy_name()
{
	char *line;
	int size;

	ft_putendl("What is your enemy?");
	size = 0;
	while(size < 3 || size > 5)
	{
		get_next_line(0, &line);
		size = ft_strlen(line);
		if (size < 3 || size > 5)
			ft_putendl("Invalid name");
	}
	return (line);
}

int		valid_new_enemy(t_map *map, int x, int y)
{
	t_enemy		*enemy;
	t_item		*item;
	t_prop		*prop;
	t_sector	*sector;
	t_point		new;

	item = map->items;
	while (item)
	{
		if (item->x == x && item->y == y)
		{
			return (0);
		}
		item = item->next_item;
	}
	enemy = map->enemys;
	while (enemy)
	{
		if (enemy->x == x && enemy->y == y)
		{
			return (0);
		}
		enemy = enemy->next_enemy;
	}
	prop = map->props;
	while (prop)
	{
		if (prop->x == x && prop->y == y)
		{
			return (0);
		}
		prop = prop->next_prop;
	}
	sector = map->sectors;
	new.x = x;
	new.y = y;
	if (enemy_checks(new, map))
		return (0);
	return (1);
}