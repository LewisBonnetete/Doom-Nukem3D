/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hitbox.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trabut <trabut@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 17:04:28 by lewis             #+#    #+#             */
/*   Updated: 2020/07/23 15:39:41 by trabut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int				ray_hit(t_render *render, t_point p)
{
	t_point r;

	render->n = -1;
	while (++render->n < render->s->nbr_walls)
	{
		render->wall = &render->s->walls[render->n];
		if (intersect(render->ray, render->wall) == 1)
		{
			r.x = render->ray->x2;
			r.y = render->ray->y2;
			if (render->wall->is_portal == 1)
				return (1);
			if (calc_dist(r, p) <= 0.5)
				return (0);
		}
	}
	return (1);
}

int				hit_item(t_var *info, t_render *render, t_point p)
{
	t_point	r;

	while (render->item)
	{
		calc_item_wall(render, render->item, info);
		if (intersect(render->ray, &render->wall_item))
		{
			r.x = render->ray->x2;
			r.y = render->ray->y2;
			if (calc_dist(r, p) <= 0.5)
				return (hit_objet(info, render));
		}
		render->item = render->item->next_item;
	}
	return (1);
}

int				hitbox(t_var *info, t_render *render, int dir)
{
	t_point	p;

	render->x = 0;
	p.x = info->player->posx;
	p.y = info->player->posy;
	render->x = 0;
	while (render->x++ < WINDOW_W)
	{
		update_ray_box(info, render, dir, p);
		if (!ray_hit(render, p))
			return (0);
		if (!hit_item(info, render, p))
			return (0);
		render->item = render->item_0;
	}
	return (1);
}
