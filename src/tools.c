/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 17:04:28 by lewis             #+#    #+#             */
/*   Updated: 2020/07/16 18:11:34 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

double			calc_dist(t_point a, t_point b)
{
	double res;

	res = (b.x - a.x) * (b.x - a.x)
	+ (b.y - a.y) * (b.y - a.y);
	return (sqrt(res));
}

void			free_sector(t_sector *sector)
{
	if (sector->next_sector)
		free_sector(sector->next_sector);
	ft_memdel((void **)&sector);
}

void			free_ren_help(t_render *render)
{
	if (render->itab)
		free_itab(render->itab);
	if (render->ray)
		free_ray(render->ray);
	if (render->s)
		free_sector(render->s);
	if (render->wall)
		free_wall(render->wall);
	if (render->wall_item)
		free_wall(render->wall_item);
}

void			free_render(t_render *render)
{
	int i;

	i = -1;
	while (++i < NB_TEXT)
		if (render->tab_sdl[i])
			SDL_FreeSurface(render->tab_sdl[i]);
	i = -1;
	while (++i < NB_TEXT_I)
		if (render->tab_sdl_item[i])
			SDL_FreeSurface(render->tab_sdl_item[i]);
	free_ren_help(render);
	while (render->item_0)
	{
		free_item(render->item_0);
		render->item_0 = render->item_0->next_item;
	}
}
