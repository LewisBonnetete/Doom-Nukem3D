/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   item.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/06/17 14:50:43 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem_edit.h"

void	create_item(t_map *map)
{
	int valid_coo = 0;
	int x;
	int y;
	float temp;
	SDL_Event	event;

	ft_putendl("Place your item");
	while(valid_coo == 0)
	{
		SDL_WaitEvent(&event);
		if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			temp = (float)event.button.x / (float)(WINDOW_H - 50) * map->size;
			x = round(temp);
			temp = (float)event.button.y / (float)(WINDOW_H - 50) * map->size;
			y = round(temp);
			if (valid_new_item(map, x, y))
			{
				valid_coo = 1;
				if (!add_item(map, get_item_name(), x, y))
					exit_edit(map->sectors->info, map);
			}
			else
			{
				ft_putendl("You can't put an item here");
			}
		}
	}
}

char 	*get_item_name()
{
	char *line;
	int size;

	ft_putendl("What is your item?");
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

int		valid_new_item(t_map *map, int x, int y)
{
	t_item		*item;
	t_prop		*prop;
	t_sector	*sector;
	t_point		new;
	t_enemy		*enemy;

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
	if (item_checks(new, map))
		return (0);
	return (1);
}

int		item_checks(t_point new, t_map *map)
{
	if (is_in_sectors_spawn(new, map))
	{
		ft_putendl("Items must be in a sector");
		return (0);
	}
	if (!is_new_point_in_sectors(new, map))
	{
		ft_putendl("Items can't be inside a wall");
		return (0);
	}
	return (1);
}

t_item	*go_to_last_item(t_item *items)
{
	t_item *item;

	item = items;
	while (item->next_item)
	{
		item = item->next_item;
	}
	return (item);
}

int		add_item(t_map *map, char *name, int x, int y)
{
	t_item	*item;

	if (map->items)
		item = go_to_last_item(map->items);
	else
	{
		if (!(map->items = (t_item*)malloc(sizeof(t_item))))
			return (0);
		map->items->next_item = NULL;
		map->items->x = x;
		map->items->y = y;
		map->items->name = name;
		return (1);
	}
	if (!(item->next_item = (t_item*)malloc(sizeof(t_item))))
		return (0);
	item->next_item->next_item = NULL;
	item->next_item->x = x;
	item->next_item->y = y;
	item->next_item->name = name;
	return (1);
}

void	del_item_or_prop(t_map *map)
{
	int			valid_coo;
	float		temp;
	int 		x;
	int 		y;
	SDL_Event	event;

	ft_putendl("Click on the item/prop you wanna remove");
	valid_coo = 0;
	while(valid_coo == 0)
	{
		SDL_WaitEvent(&event);
		if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			temp = (float)event.button.x / (float)(WINDOW_H - 50) * map->size;
			x = round(temp);
			temp = (float)event.button.y / (float)(WINDOW_H - 50) * map->size;
			y = round(temp);
			if (del_item(map, x, y) || del_prop(map, x, y) || del_enemy(map, x, y))
				ft_putendl(" removed");
			else
				ft_putendl("Nothing here...");
			valid_coo = 1;
		}
	}
	draw_grid(map->sectors->info, map);
}

int		del_item(t_map *map, int x, int y)
{
	t_item *item;
	t_item *previous;

	item = map->items;
	previous = map->items;
	if (item)
	{
		if (item->x == x && item->y == y)
		{
			map->items = map->items->next_item;
			ft_putstr(item->name);
			free(item->name);
			free(item);
			return (1);
		}
		item = item->next_item;
		while (item)
		{
			if (item->x == x && item->y == y)
			{
				previous->next_item = item->next_item;
				ft_putstr(item->name);
				free(item->name);
				free(item);
				return (1);
			}
			item = item->next_item;
			previous = previous->next_item;
		}
	}
	return (0);
}