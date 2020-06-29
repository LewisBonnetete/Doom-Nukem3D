/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/06/29 14:29:58 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem_edit.h"

void		create_enemy(t_map *map)
{
	int			valid_coo;
	int			x;
	int			y;
	SDL_Event	event;

	ft_putendl("Place your enemy");
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
			if ((valid_coo = valid_new_enemy(map, x, y)))
			{
				if (!add_enemy(map, get_enemy_name(), x, y))
					exit_edit(map->sectors->info, map);
			}
			else
				ft_putendl("You can't put an enemy here");
		}
		else if (event.key.keysym.sym == SDLK_d)
		{
			ft_putendl("Back to creation");
			break;
		}
	}
}

char		*get_enemy_name(void)
{
	char	*line;
	int		size;

	ft_putendl("What is your enemy?");
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

int			valid_new_enemy2(t_map *map, int x, int y)
{
	t_prop		*prop;
	t_enemy		*enemy;

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
	return (1);
}

int			valid_new_enemy(t_map *map, int x, int y)
{
	t_item		*item;
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
	if (valid_new_enemy2(map, x, y) == 0)
		return (0);
	new.x = x;
	new.y = y;
	if (enemy_checks(new, map))
		return (0);
	return (1);
}
