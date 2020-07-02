/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   item.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/07/02 16:03:14 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem_edit.h"

void	create_item(t_map *map)
{
	int			valid_coo;
	int			x;
	int			y;
	SDL_Event	event;

	ft_putendl("Place your item");
	valid_coo = 0;
	while (valid_coo == 0)
	{
		SDL_WaitEvent(&event);
		if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			x = x_coo(&event, map);
			y = y_coo(&event, map);
			if ((valid_coo = valid_new_item(map, x, y)))
			{
				if (!add_item(map, get_item_name(), x, y))
					exit_edit(map->sectors->info, map);
			}
			else
			{
				ft_putendl("You can't put an item here");
				break ;
			}
		}
		else if (event.key.keysym.sym == SDLK_d)
			break ;
	}
}

char	*get_item_name(void)
{
	char	*line;
	int		size;

	ft_putendl("What is your item?");
	size = 0;
	while (size < 3 || size > 10)
	{
		get_next_line(0, &line);
		size = ft_strlen(line);
		if (size < 3 || size > 10)
			ft_putendl("Invalid name");
	}
	return (line);
}

int		valid_new_item2(int x, int y, t_enemy *enemy, t_prop *prop)
{
	while (enemy)
	{
		if (enemy->x == x && enemy->y == y)
			return (0);
		enemy = enemy->next_enemy;
	}
	while (prop)
	{
		if (prop->x == x && prop->y == y)
			return (0);
		prop = prop->next_prop;
	}
	return (1);
}

int		valid_new_item(t_map *map, int x, int y)
{
	t_item		*item;
	t_prop		*prop;
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
	prop = map->props;
	if (valid_new_item2(x, y, enemy, prop) == 0)
		return (0);
	new.x = x;
	new.y = y;
	if (item_checks(new, map) )
		return (0);
	return (1);
}

int		item_checks(t_point new, t_map *map)
{
	if (is_in_sectors_spawn(new, map))
		return (0);
	if (!is_new_point_in_sectors(new, map))
		return (0);
	return (1);
}
