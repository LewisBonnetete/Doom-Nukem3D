/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 17:04:28 by lewis             #+#    #+#             */
/*   Updated: 2020/07/17 15:32:58 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static	void	c_i_tool(t_render *render, t_item *item)
{
	render->nb_item_to_draw++;
	render->itab[render->k].dist = render->wall_dist;
	render->itab[render->k].name = ft_strdup(item->name);
	render->itab[render->k].item_x = item->x;
	render->itab[render->k].item_y = item->y;
	render->itab[render->k].start = render->x;
	render->itab[render->k].h = item->h;
	render->itab[render->k].w = item->w;
	render->itab[render->k].text_id = item->text_id;
	render->itab[render->k].id = item->id;
	item->cap = 1;
	render->x++;
}

static	void	c_i_while(t_render *render, t_point p, t_point w, int *a)
{
	if (is_in_sector(w, render->s) != is_in_sector(p, render->s))
	{
		render->n = -1;
		while (++render->n < render->s->nbr_walls)
		{
			render->wall = &render->s->walls[render->n];
			if (intersect(render->ray, render->wall) == 1)
				if (!render->wall->is_portal)
					*a = 1;
		}
	}
}

static	void	c_i_test(t_var *info, t_render *render, t_item *item)
{
	c_i_tool(render, item);
	while (intersect(render->ray, &render->wall_item) == 1)
	{
		++render->x;
		update_ray(info, render);
	}
	render->itab[render->k].end = render->x;
	render->x = render->itab[render->k].start;
	update_ray(info, render);
	++render->k;
}

void			check_intersect(t_var *info, t_render *render, t_item *item)
{
	t_point		p;
	t_point		w;
	int			a;

	if (calc_item_wall(render, item, info) == 1)
	{
		if (intersect(render->ray, &render->wall_item) == 1
			&& item->cap == 0)
		{
			render->itab[render->k].pv = item->pv;
			a = 0;
			p.x = info->player->posx;
			p.y = info->player->posy;
			w.x = item->x;
			w.y = item->y;
			render->wall_dist = calc_dist(p, w);
			c_i_while(render, p, w, &a);
			if (a == 0)
			{
				c_i_test(info, render, item);
			}
		}
	}
	if (item->next_item)
		check_intersect(info, render, item->next_item);
}
