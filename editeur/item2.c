/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   item2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/07/09 12:02:32 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem_edit.h"

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
	int			x;
	int			y;
	SDL_Event	event;

	ft_putendl("Click on the item/prop you wanna remove");
	valid_coo = 0;
	while (valid_coo == 0)
	{
		SDL_WaitEvent(&event);
		if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			x = round(((float)event.button.x /
			(float)(WINDOW_H - 50) * map->size));
			y = round(((float)event.button.y /
			(float)(WINDOW_H - 50) * map->size));
			if (del_item(map, x, y) || del_prop(map, x, y)
			|| del_enemy(map, x, y))
				ft_putendl(" removed");
			else
				ft_putendl("Nothing here...");
			valid_coo = 1;
		}
	}
	draw_grid(map->sectors->info, map);
}

int		del_item2(int x, int y, t_item *item, t_item *previous)
{
	while (item)
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
	return (0);
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
		if (del_item2(x, y, item, previous) == 1)
			return (1);
	}
	return (0);
}
