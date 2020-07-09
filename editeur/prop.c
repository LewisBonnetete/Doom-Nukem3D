/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/07/09 12:02:20 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem_edit.h"

t_prop	*go_to_last_prop(t_prop *props)
{
	t_prop *prop;

	prop = props;
	while (prop->next_prop)
	{
		prop = prop->next_prop;
	}
	return (prop);
}

int		add_prop(t_map *map, char *name, int x, int y)
{
	t_prop	*prop;

	if (map->props)
		prop = go_to_last_prop(map->props);
	else
	{
		if (!(map->props = (t_prop*)malloc(sizeof(t_prop))))
			return (0);
		map->props->next_prop = NULL;
		map->props->x = x;
		map->props->y = y;
		map->props->name = name;
		return (1);
	}
	if (!(prop->next_prop = (t_prop*)malloc(sizeof(t_prop))))
		return (0);
	prop->next_prop->next_prop = NULL;
	prop->next_prop->x = x;
	prop->next_prop->y = y;
	prop->next_prop->name = name;
	return (1);
}

int		del_prop2(int x, int y, t_prop *prop, t_prop *previous)
{
	while (prop)
	{
		if (prop->x == x && prop->y == y)
		{
			previous->next_prop = prop->next_prop;
			free(prop->name);
			free(prop);
			return (1);
		}
		prop = prop->next_prop;
		previous = previous->next_prop;
	}
	return (0);
}

int		del_prop(t_map *map, int x, int y)
{
	t_prop *prop;
	t_prop *previous;

	prop = map->props;
	previous = map->props;
	if (prop)
	{
		if (prop->x == x && prop->y == y)
		{
			map->props = map->props->next_prop;
			free(prop->name);
			free(prop);
			return (1);
		}
		prop = prop->next_prop;
		if (del_prop2(x, y, prop, previous) == 1)
			return (1);
	}
	return (0);
}
