/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_walls_sector.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/06/26 14:51:57 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem_edit.h"

// int			get_walls_sector4(t_map *map, t_sector *sector, int *height)
// {
	
// }

// int			get_walls_sector3(t_map *map, t_sector *sector, int *height)
// {

// }

// int			get_walls_sector2(t_map *map, t_sector *sector, int *height)
// {
	
// }

int			get_walls_sector(t_map *map, t_sector *sector, int *height)
{
	SDL_Event	event;
	int			i;

	i = 0;
	ft_putstr("Place you walls, you'll have to put two vertex ");
	ft_putendl("for your first wall");
	ft_putendl("Press 'd' to delete your sector :)");
	while (i < sector->nbr_walls)
	{
		SDL_WaitEvent(&event);
		if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			if (i == 0)
			{
				if (is_valid_first_wall(&event, map))
				{
					create_first_wall_edit(sector, height, i, event);
					i++;
				}
				else
					ft_putendl("Nope, try something else");
			}
			else if (i < sector->nbr_walls - 1 && i > 0)
			{
				if (is_valid_wall(&event, sector, i))
				{
					create_wall_edit(sector, height, i, event);
					draw_state(sector);
					i++;
				}
				else
					ft_putendl("Nope, try something else");
			}
			else if (i == sector->nbr_walls - 1)
			{
				if (is_valid_last_wall(&event, sector, i))
				{
					create_wall_edit(sector, height, i, event);
					draw_state(sector);
					i++;
				}
				else
					ft_putendl("Nope, try something else");
			}
		}
		else if (event.key.keysym.sym == SDLK_d
		&& event.key.state == SDL_PRESSED)
		{
			ft_putendl("Sector deleted");
			del_sector(sector->info, map);
			draw_state(sector);
			return (1);
		}
		if (i == sector->nbr_walls && !check_convexity(sector))
		{
			ft_putendl("Sorry but your sector is not convex :(");
			ft_putendl("Sector deleted");
			del_sector(sector->info, map);
			draw_state(sector);
			return (1);
		}
		if (i == sector->nbr_walls && !check_self_intersection(sector))
		{
			ft_putendl("Sorry but your sector crosses itself :(");
			ft_putendl("Sector deleted");
			del_sector(sector->info, map);
			draw_state(sector);
			return (1);
		}
		if (i == sector->nbr_walls && !check_surrounding(sector))
		{
			ft_putendl("Sorry but your sector surrounds another :(");
			ft_putendl("Sector deleted");
			del_sector(sector->info, map);
			draw_state(sector);
			return (1);
		}
		if (event.type == SDL_QUIT || (event.key.keysym.sym == SDLK_ESCAPE
		&& event.type == SDL_KEYDOWN))
		{
			exit_edit(sector->info, map);
			return (1);
		}
	}
	close_sector(sector, sector->nbr_walls - 1);
	return (1);
}
