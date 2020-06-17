/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/06/17 14:42:36 by lbonnete         ###   ########.fr       */
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

int		enemy_checks(t_point new, t_map *map)
{
	if (is_in_sectors_spawn(new, map))
	{
		ft_putendl("enemys must be in a sector");
		return (0);
	}
	if (!is_new_point_in_sectors(new, map))
	{
		ft_putendl("enemys can't be inside a wall");
		return (0);
	}
	return (1);
}

t_enemy	*go_to_last_enemy(t_enemy *enemys)
{
	t_enemy *enemy;

	enemy = enemys;
	while (enemy->next_enemy)
	{
		enemy = enemy->next_enemy;
	}
	return (enemy);
}

int		add_enemy(t_map *map, char *name, int x, int y)
{
	t_enemy	*enemy;

	if (map->enemys)
		enemy = go_to_last_enemy(map->enemys);
	else
	{
		if (!(map->enemys = (t_enemy*)malloc(sizeof(t_enemy))))
			return (0);
		map->enemys->next_enemy = NULL;
		map->enemys->x = x;
		map->enemys->y = y;
		map->enemys->name = name;
		return (1);
	}
	if (!(enemy->next_enemy = (t_enemy*)malloc(sizeof(t_enemy))))
		return (0);
	enemy->next_enemy->next_enemy = NULL;
	enemy->next_enemy->x = x;
	enemy->next_enemy->y = y;
	enemy->next_enemy->name = name;
	return (1);
}

int		del_enemy(t_map *map, int x, int y)
{
	t_enemy *enemy;
	t_enemy *previous;

	enemy = map->enemys;
	previous = map->enemys;
	if (enemy)
	{
		if (enemy->x == x && enemy->y == y)
		{
			map->enemys = map->enemys->next_enemy;
			ft_putstr(enemy->name);
			free(enemy->name);
			free(enemy);
			return (1);
		}
		enemy = enemy->next_enemy;
		while (enemy)
		{
			if (enemy->x == x && enemy->y == y)
			{
				previous->next_enemy = enemy->next_enemy;
				ft_putstr(enemy->name);
				free(enemy->name);
				free(enemy);
				return (1);
			}
			enemy = enemy->next_enemy;
			previous = previous->next_enemy;
		}
	}
	return (0);
}