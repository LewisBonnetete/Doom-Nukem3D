/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/06/24 16:36:15 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem_edit.h"

void	create_prop(t_map *map)
{
	int			valid_coo;
	int			x;
	int			y;
	SDL_Event	event;

	ft_putendl("Place your prop");
	while (valid_coo == 0)
	{
		SDL_WaitEvent(&event);
		if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			x = round(((float)event.button.x
			/ (float)(WINDOW_H - 50) * map->size));
			y = round(((float)event.button.y
			/ (float)(WINDOW_H - 50) * map->size));
			if (valid_coo = valid_new_prop(map, x, y))
			{
				if (!add_prop(map, get_prop_name(), x, y))
					exit_edit(map->sectors->info, map);
			}
			else
				ft_putendl("You can't put a prop here");
		}
	}
}

char	*get_prop_name(void)
{
	char	*line;
	int		size;

	ft_putendl("What is your prop?");
	size = 0;
	while (size < 3 || size > 5)
	{
		get_next_line(0, &line);
		size = ft_strlen(line);
		if (size < 3 || size > 5)
			ft_putendl("Invalid name");
	}
	return (line);
}

int		valid_new_prop2(int x, int y, t_enemy *enemy, t_item *item)
{
	while (enemy)
	{
		if (enemy->x == x && enemy->y == y)
			return (0);
		enemy = enemy->next_enemy;
	}
	while (item)
	{
		if (item->x == x && item->y == y)
			return (0);
		item = item->next_item;
	}
	return (1);
}

int		valid_new_prop(t_map *map, int x, int y)
{
	t_item		*item;
	t_prop		*prop;
	t_sector	*sector;
	t_point		new;
	t_enemy		*enemy;

	enemy = map->enemys;
	prop = map->props;
	while (prop)
	{
		if (prop->x == x && prop->y == y)
		{
			return (0);
		}
		prop = prop->next_prop;
	}
	item = map->items;
	valid_new_prop2(x, y, enemy, item);
	new.x = x;
	new.y = y;
	if (prop_checks(new, map))
		return (0);
	return (1);
}

int		prop_checks(t_point new, t_map *map)
{
	if (is_in_sectors_spawn(new, map))
	{
		ft_putendl("props must be in a sector");
		return (0);
	}
	if (!is_new_point_in_sectors(new, map))
	{
		ft_putendl("props can't be inside a wall");
		return (0);
	}
	return (1);
}

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
			ft_putstr(prop->name);
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
			ft_putstr(prop->name);
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
