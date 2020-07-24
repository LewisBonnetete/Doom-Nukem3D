/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trabut <trabut@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 17:04:28 by lewis             #+#    #+#             */
/*   Updated: 2020/07/23 17:03:59 by trabut           ###   ########.fr       */
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
	int i;

	i = 0;
	if (sector->next_sector)
		free_sector(sector->next_sector);
	while (i < sector->nbr_walls)
	{
		free(&sector->walls[i]);
		i++;
	}
	ft_memdel((void **)&sector);
}

void			free_ren_help(t_render *render)
{
	if (render->ray)
		free_ray(render->ray);
}

void			free_text(SDL_Surface *text)
{
	free(text->pixels);
	free(text);
}

void			free_render(t_render *render)
{
	int		i;
	t_item	*item;

	i = -1;
	while (++i < NB_TEXT)
		if (render->tab_sdl[i])
			free_text(render->tab_sdl[i]);
	i = -1;
	while (++i < NB_TEXT_I)
		if (render->tab_sdl_item[i])
			free_text(render->tab_sdl_item[i]);
	free_ren_help(render);
	while (render->item_0)
	{
		item = render->item_0;
		render->item_0 = render->item_0->next_item;
		free_item(item);
	}
}
