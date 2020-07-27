/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trabut <trabut@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 17:04:28 by lewis             #+#    #+#             */
/*   Updated: 2020/07/27 18:02:32 by trabut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void		update_ray(t_var *info, t_render *render)
{
	render->ray->cam_x = 2 * render->x / (double)(WINDOW_W) - 1;
	render->ray->dx = info->player->dx
		+ info->player->planex * render->ray->cam_x;
	render->ray->dy = info->player->dy
		+ info->player->planey * render->ray->cam_x;
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

void		init_cast(t_var *info, t_render *render, t_ray *ray)
{
	info->player->no_scope = 0;
	render->sector_id = info->player->sector_id;
	render->n = -1;
	render->x = 0;
	render->k = 0;
	render->nb_item_to_draw = 0;
	render->ray = ray;
	if (render->item && !render->item->cap)
		render->item->cap = 0;
	else if (render->item && render->item->cap == 1)
		render->item->cap = 0;
	render->ray->x = info->player->posx;
	render->ray->y = info->player->posy;
	render->ray->z = info->player->posz;
	render->ray->cam_x = 2 * render->x / (double)(WINDOW_W) - 1;
	render->ray->dx = info->player->dx
	+ info->player->planex * render->ray->cam_x;
	render->ray->dy = info->player->dy
	+ info->player->planey * render->ray->cam_x;
	info->player->sector_id = player_sec(render->sec_0, info);
	if (info->player->sector_id)
		go_to_sector(render->sec_0, info->player->sector_id, render);
}

void		init_nb_sec(t_sector *sector, t_render *render)
{
	if (sector->next_sector)
	{
		render->nb_sec++;
		init_nb_sec(sector->next_sector, render);
	}
}

int			rgb_calc(int r, int g, int b)
{
	return (256 * 256 * (int)(r) + 256 * (int)(g) + (int)(b));
}

void		init_ceilling(t_var *info, t_f_tool *tool)
{
	tool->dirx0 = info->player->dx - info->player->planex;
	tool->diry0 = info->player->dy - info->player->planey;
	tool->dirx1 = info->player->dx + info->player->planex;
	tool->diry1 = info->player->dy + info->player->planey;
	tool->posz = 0.5 * (WINDOW_H + info->y_dec);
	tool->p = tool->i - (WINDOW_H / 2 + info->y_dec);
	tool->dist = tool->posz / tool->p;
	tool->stepx = tool->dist * (tool->dirx1 - tool->dirx0) / WINDOW_W;
	tool->stepy = tool->dist * (tool->diry1 - tool->diry0) / WINDOW_W;
	tool->floorx = info->player->posx + tool->dist * tool->dirx0;
	tool->floory = info->player->posy + tool->dist * tool->diry0;
	tool->j = -1;
}
