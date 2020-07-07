/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/07/07 16:34:55 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem_edit.h"

int		end_checks(t_point new, t_map *map)
{
	if (!is_in_sectors_spawn(new, map))
	{
		ft_putendl("end musts be in a sector");
		return (0);
	}
	if (!is_new_point_in_sectors(new, map))
	{
		ft_putendl("end can't be inside a wall");
		return (0);
	}
	if (!is_in_object(new, map))
	{
		ft_putendl("end can't be inside something");
		return (0);
	}
	 return (1);
}

int		set_end(t_map *map)
{
	int			ok;
	t_point		new;
	SDL_Event	event;

	ok = 0;
	ft_putendl("Set your end");
	while (ok == 0)
	{
		SDL_WaitEvent(&event);
		if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			new.x = round(((float)event.button.x
			/ (float)(WINDOW_H - 50) * map->size));
			new.y = round(((float)event.button.y
			/ (float)(WINDOW_H - 50) * map->size));
			ok = end_checks(new, map);
		}
		else if (event.key.keysym.sym == SDLK_d)
		{
			ft_putendl("Back to creation");
			return (0);
		}
	}
	map->end.x = new.x;
	map->end.y = new.y;
	printf("end: %i | %i | %i\n", map->end.x, map->end.y, map->end.z);
	return (1);
}