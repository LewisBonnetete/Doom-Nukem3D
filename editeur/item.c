/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   item.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lewis <lewis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/06/05 13:33:23 by lewis            ###   ########.fr       */
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
	(void)map;
	(void)x;
	(void)y;
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
			free(item->name);
			free(item);
			return (1);
		}
		item = item->next_item;
		while (item->next_item)
		{
			if (item->x == x && item->y == y)
			{
				previous->next_item = item->next_item;
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