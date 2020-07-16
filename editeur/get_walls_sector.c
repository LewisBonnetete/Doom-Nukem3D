/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_walls_sector.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/07/16 15:04:00 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem_edit.h"

void		get_walls_sector2(t_gws *gws)
{
	if (gws->i == 0)
		if (is_valid_first_wall((gws->event), gws->map))
			create_first_wall_edit(gws->sector,
			gws->height, gws->i++, *(gws->event));
		else
			ft_putendl("Nope, try something else");
	else if (gws->i < gws->sector->nbr_walls - 1 && gws->i > 0)
		if (is_valid_wall((gws->event), gws->sector, gws->i))
		{
			create_wall_edit(gws->sector, gws->height, gws->i++, *(gws->event));
			draw_state(gws->sector);
		}
		else
			ft_putendl("Nope, try something else");
	else if (gws->i == gws->sector->nbr_walls - 1)
	{
		if (is_valid_last_wall((gws->event), gws->sector, gws->i))
		{
			create_wall_edit(gws->sector, gws->height, gws->i++, *(gws->event));
			draw_state(gws->sector);
		}
		else
			ft_putendl("Nope, try something else");
	}
}

int			get_walls_sector3(t_gws *gws)
{
	if (gws->i == gws->sector->nbr_walls && !check_convexity(gws->sector))
	{
		ft_putendl("Sorry but your sector is not convex :(");
		del_sector(gws->sector->info, gws->map);
		draw_state(gws->sector);
		return (1);
	}
	if (gws->i == gws->sector->nbr_walls
	&& !check_self_intersection(gws->sector))
	{
		ft_putendl("Sorry but your sector crosses itself :(");
		del_sector(gws->sector->info, gws->map);
		draw_state(gws->sector);
		return (1);
	}
	if (gws->i == gws->sector->nbr_walls && !check_surrounding(gws->sector))
	{
		ft_putendl("Sorry but your sector surrounds another :(");
		del_sector(gws->sector->info, gws->map);
		return (1);
	}
	return (0);
}

void		get_walls_sector4(t_gws *gws)
{
	if (gws->event->type == SDL_QUIT
	|| (gws->event->key.keysym.sym == SDLK_ESCAPE
	&& gws->event->type == SDL_KEYDOWN))
		exit_edit(gws->sector->info, gws->map);
}

int			get_walls_sector5(t_gws *gws)
{
	if (gws->event->key.keysym.sym == SDLK_d
	&& gws->event->key.state == SDL_PRESSED)
	{
		del_sector(gws->sector->info, gws->map);
		draw_state(gws->sector);
		return (1);
	}
	return (0);
}

int			get_walls_sector(t_map *map, t_sector *sector, int *height)
{
	t_gws		gws;
	SDL_Event	event;

	gws.map = map;
	gws.sector = sector;
	gws.event = &event;
	gws.i = 0;
	gws.height = height;
	ft_putstr("Place you walls, you'll have to put two vertex ");
	ft_putendl("for your first wall");
	while (gws.i < sector->nbr_walls)
	{
		SDL_WaitEvent(&event);
		if (event.type == SDL_MOUSEBUTTONDOWN)
			get_walls_sector2(&gws);
		else if (get_walls_sector5(&gws) == 1)
			return (1);
		if (get_walls_sector3(&gws) == 1)
			return (1);
		get_walls_sector4(&gws);
	}
	close_sector(sector, sector->nbr_walls - 1);
	return (1);
}
