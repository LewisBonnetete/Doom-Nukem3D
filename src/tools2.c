/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trabut <trabut@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 17:04:28 by lewis             #+#    #+#             */
/*   Updated: 2020/07/10 17:03:25 by trabut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int				do_trigo(t_var *info, t_wall *wall)
{
	double	i;
	double	x;
	double	y;
	int		a;

	x = info->player->posx;
	y = info->player->posy;
	i = 0.0;
	while (i <= 180.0)
	{
		x = info->player->posx + cos(i);
		y = info->player->posy + sin(i);
		if ((a = xy_in_ab(x, y, wall->a, wall->b)) != 0)
			return (1);
		i += 0.1;
	}
	return (0);
}

static	void	u_r_b_help(t_var *info, t_render *render, int dir)
{
	if (dir == 0)
	{
		render->ray->dx = info->player->dx;
		render->ray->dy = info->player->dy;
	}
	if (dir == 1)
	{
		render->ray->dx = -info->player->dx;
		render->ray->dy = -info->player->dy;
	}
	if (dir == 2)
	{
		render->ray->dx = -info->player->dy;
		render->ray->dy = info->player->dx;
	}
	if (dir == 3)
	{
		render->ray->dx = info->player->dy;
		render->ray->dy = -info->player->dx;
	}
}

void			update_ray_box(t_var *info, t_render *render,
				int dir, t_point p)
{
	render->x = WINDOW_W / 2;
	render->ray->x = p.x;
	render->ray->y = p.y;
	render->ray->cam_x = 2 * render->x / (double)(WINDOW_W) - 1;
	u_r_b_help(info, render, dir);
	if (render->ray->dx != 0.0)
	{
		render->ray->eq_slope = render->ray->dy
		/ render->ray->dx;
		render->ray->eq_cste = render->ray->y
		- render->ray->eq_slope * render->ray->x;
	}
	else
	{
		render->ray->eq_slope = 1111;
		render->ray->eq_cste = render->ray->x;
	}
}

int				hitbox(t_var *info, t_render *render, int dir)
{
	t_point	r;
	t_point	p;

	p.x = info->player->posx;
	p.y = info->player->posy;
	update_ray_box(info, render, dir, p);
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
	while (render->item)
	{
		calc_item_wall(render, render->item, info);
		if (intersect(render->ray, render->wall_item))
		{
			r.x = render->ray->x2;
			r.y = render->ray->y2;
			if (calc_dist(r, p) <= 0.5)
			{
				if (render->item->name[0] == 'c')
					info->player->hp = 0;
				return (0);
			}
		}
		render->item = render->item->next_item;
	}
	render->item = render->item_0;
	return (1);
}
