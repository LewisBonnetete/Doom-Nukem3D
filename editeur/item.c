/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   item.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lewis <lewis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/06/03 16:58:20 by lewis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem_edit.h"

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

int		add_item(t_map *map, char name, int x, int y)
{
	t_item	*item;

	item = go_to_last_item(map->items);
	if (item->next_item = (t_item*)malloc(sizeof(t_item)))
		return (0);
	item->next_item->next_item = NULL;
	item->next_item->x = x;
	item->next_item->y = y;
	item->next_item->name = ft_strdup(name);
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
			free(item->name)
			free(item);
			return (1);
		}
		item = item->next_item;
		while (item->next_item)
		{
			if (item->x == x && item->y == y)
			{
				previous->next_item = item->next_item;
				free(item->name)
				free(item);
				return (1);
			}
			item = item->next_item;
		}
	}
	return (0);
}