/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 17:04:28 by lewis             #+#    #+#             */
/*   Updated: 2020/07/27 14:04:55 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void			ft_put_weapon(t_var *info, t_render *render)
{
	double		x;
	double		y;
	Uint32		color;

	x = 0;
	while (x < render->tab_sdl[0]->w)
	{
		y = 0;
		while (y < render->tab_sdl[0]->h)
		{
			color = get_pixel(render->tab_sdl[0], y, x);
			if (color != 0)
				put_pixel(color, (int)x + WINDOW_W / 2 - 45,
				WINDOW_H + (int)y - 125 + info->d_gun, info->image);
			y++;
		}
		x++;
	}
}

static	int		ray_iter(t_render *render, t_var *info)
{
	while (render->x < WINDOW_W)
	{
		go_to_sector(render->sec_0, info->player->sector_id, render);
		init_tab(render->tab, render->nb_sec);
		update_ray(info, render);
		draw_column(info, render, render->tab);
		render->x++;
	}
	draw_item(render, info);
	if (may_weapon(render->item_0) == 1)
		ft_put_weapon(info, render);
	hud(info, info->player, info->map);
	rain_gen(info);
	return (1);
}

void			free_itab(t_itab *itab, t_render *render)
{
	int i;

	i = 0;
	while (i < render->nbr_items + 1)
	{
		free(itab[i].name);
		i++;
	}
	free(itab);
}

int				raycasting(t_var *info, t_render *render)
{
	t_ray	ray;
	int		i;

	init_cast(info, render, &ray);
	if (tex_floor_ciel(info, render) == 0 || render->nbr_items > 100)
		return (0);
	if (render->nbr_items > 0)
	{
		if (!(render->itab = (t_itab *)ft_memalloc(sizeof(t_itab)
			* (render->nbr_items + 1))))
			return (0);
		i = -1;
		while (++i < render->nbr_items + 1)
		{
			render->itab[i].name = NULL;
			render->itab[i].used = 0;
			render->itab[i].dist = 0;
		}
	}
	if (!(ray_iter(render, info)))
		return (0);
	if (render->nbr_items > 0)
		free_itab(render->itab, render);
	return (1);
}
