/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prop2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/07/08 16:28:30 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem_edit.h"

void	create_prop(t_map *map)
{
	int			valid_coo;
	int			x;
	int			y;
	SDL_Event	event;

	ft_putendl("Place your prop");
	valid_coo = 0;
	while (valid_coo == 0)
	{
		SDL_WaitEvent(&event);
		if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			x = x_coo(&event, map);
			y = y_coo(&event, map);
			if ((valid_coo = valid_new_prop(map, x, y)))
			{
				if (!add_prop(map, get_prop_name(), x, y))
					exit_edit(map->sectors->info, map);
			}
			if (valid_coo == 0)
				ft_putendl("You can't put a prop here");
		}
		else if (event.key.keysym.sym == SDLK_d)
			break ;
	}
}

char	*get_prop_name(void)
{
	char	*line;
	int		size;

	ft_putendl("What is your prop?");
	size = 1;
	while (size)
	{
		get_next_line(0, &line);
		if (ft_strcmp("barrel", line) == 0)
			size = 0;
		else
		{
			ft_putendl("We only got barrel for now");
			free(line);
		}
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
	if (valid_new_prop2(x, y, enemy, item) == 0)
		return (0);
	new.x = x;
	new.y = y;
	if (prop_checks(new, map))
		return (0);
	return (1);
}

int		prop_checks(t_point new, t_map *map)
{
	if (is_in_sectors_spawn(new, map))
		return (0);
	if (!is_new_point_in_sectors(new, map))
		return (0);
	return (1);
}
