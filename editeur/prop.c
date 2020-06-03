/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lewis <lewis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/06/03 16:59:19 by lewis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem_edit.h"

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

int		add_prop(t_map *map, char name, int x, int y)
{
	t_prop	*prop;

	prop = go_to_last_prop(map->props);
	if (prop->next_prop = (t_prop*)malloc(sizeof(t_prop)))
		return (0);
	prop->next_prop->next_prop = NULL;
	prop->next_prop->x = x;
	prop->next_prop->y = y;
	prop->next_prop->name = ft_strdup(name);
	return (1);
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
			free(prop->name)
			free(prop);
			return (1);
		}
		prop = prop->next_prop;
		while (prop->next_prop)
		{
			if (prop->x == x && prop->y == y)
			{
				previous->next_prop = prop->next_prop;
				free(prop->name)
				free(prop);
				return (1);
			}
			prop = prop->next_prop;
		}
	}
	return (0);
}