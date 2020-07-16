/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trabut <trabut@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 17:04:28 by lewis             #+#    #+#             */
/*   Updated: 2020/07/16 15:25:15 by trabut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static	void	draw_i_calc(t_render *render)
{
	int i;

	if (!render->itab)
		return ;
	if (render->nb_item_to_draw <= 0)
		return ;
	i = -1;
	while (++i < render->nb_item_to_draw + 1)
		if (render->itab[i].name == 0)
		{
			render->itab[i].dist = -1;
			render->itab[i].name = "-1";
		}
}

static	int		draw_i_iter(t_render *render, int k)
{
	int i;
	int tmp;

	tmp = k;
	i = -1;
	while (render->itab[++i].name && i < render->nb_item_to_draw + 1)
	{
		if (render->itab[k].dist < render->itab[i].dist
			&& render->itab[i].name[0] !=
			'-' && render->itab[i].name[1] != '1')
			tmp = i;
	}
	return (tmp);
}

void			draw_item(t_render *render, t_var *info)
{
	int		j;
	int		k;
	int		i;

	draw_i_calc(render);
	j = -1;
	while (++j < render->nb_item_to_draw)
	{
		k = 0;
		while (render->itab[k].name && render->itab[k].name[0] == '-'
				&& render->itab[k].name[1] == '1')
			++k;
		if (!render->itab[k].name)
			break ;
		k = draw_i_iter(render, k);
		if (render->itab[k].name[0] != '-' && render->itab[k].name[1] != '1')
		{
			put_item(k, render->item_0, render, info);
			render->itab[k].name = "-1";
			render->itab[k].dist = -1;
		}
	}
	i = -1;
	while (++i < render->nb_item_to_draw + 1)
		render->itab[i].name = 0;
}

static	int		ray_iter(t_render *render, t_var *info)
{
	int		*tab;

	if (!(tab = (int *)ft_memalloc((sizeof(int) * (render->nb_sec + 1)))))
		return (0);
	while (render->x < WINDOW_W)
	{
		go_to_sector(render->sec_0, info->player->sector_id, render);
		init_tab(tab, render->nb_sec);
		update_ray(info, render);
		draw_column(info, render, tab);
		render->x++;
	}
	draw_item(render, info);
	if (may_weapon(render->item_0) == 1)
		ft_put_weapon(info, render);
	hud(info, info->player, info->map);
	rain_gen(info);
	free(tab);
	if (render->itab)
		free(render->itab);
	return (1);
}

int				raycasting(t_var *info, t_render *render)
{
	t_ray	ray;
	int		i;

	init_cast(info, render, &ray);
	if (tex_floor_ciel(info, render) == 0)
		return (0);
	if (render->nbr_items > 100)
		return (0);
	if (render->nbr_items > 0)
	{
		if (!(render->itab = (t_itab *)ft_memalloc(sizeof(t_itab)
			* (render->nbr_items + 1))))
			return (0);
		i = -1;
		while (++i < render->nbr_items + 1)
		{
			render->itab[i].name = 0;
			render->itab[i].dist = 0;
		}
	}
	if (!(ray_iter(render, info)))
		return (0);
	return (1);
}
