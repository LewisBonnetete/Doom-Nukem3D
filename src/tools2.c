/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trabut <trabut@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 17:04:28 by lewis             #+#    #+#             */
/*   Updated: 2020/07/22 16:35:10 by trabut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void			u_r_b_helpdir(t_var *info, t_render *render, int dir)
{
	if (dir == 2)
	{
		render->ray->dx = -info->player->dy
		+ info->player->planex * render->ray->cam_x;
		render->ray->dy = info->player->dx
		+ info->player->planey * render->ray->cam_x;
	}
	if (dir == 3)
	{
		render->ray->dx = info->player->dy
		+ info->player->planex * render->ray->cam_x;
		render->ray->dy = -info->player->dx
		+ info->player->planey * render->ray->cam_x;
	}
}

void			u_r_b_help(t_var *info, t_render *render, int dir)
{
	if (dir == 0)
	{
		render->ray->dx = info->player->dx
		+ info->player->planex * render->ray->cam_x;
		render->ray->dy = info->player->dy
		+ info->player->planey * render->ray->cam_x;
	}
	if (dir == 1)
	{
		render->ray->dx = -info->player->dx
		+ info->player->planex * render->ray->cam_x;
		render->ray->dy = -info->player->dy
		+ info->player->planey * render->ray->cam_x;
	}
	u_r_b_helpdir(info, render, dir);
}

void			update_ray_box(t_var *info, t_render *render,
				int dir, t_point p)
{
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

int				hit_objet(t_var *info, t_render *render)
{
	if (render->item->name[0] == 'c' && render->item->pv > 0)
	{
		info->player->hp = 0;
		return (0);
	}
	if (render->item->name[0] == 's' && render->item->pv > 0)
	{
		info->player->hp -= 5;
		return (0);
	}
	if (render->item->name[0] == 'a' ||
		render->item->name[0] == 'm' || render->item->name[0] == 'h')
		return (1);
	if (render->item->name[0] == 'b')
		return (0);
	return (1);
}
