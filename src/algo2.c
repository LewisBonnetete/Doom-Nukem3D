/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 17:04:28 by lewis             #+#    #+#             */
/*   Updated: 2020/07/17 14:58:58 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void		update_render(t_var *info, t_render *render)
{
	render->scalar = scalar(info->player->dx, info->player->dy,
	render->ray->x2 - render->ray->x, render->ray->y2 - render->ray->y);
	render->y2 = render->scalar * info->player->dy;
	render->x2 = render->scalar * info->player->dx;
	render->wall_sqdist = norm2(render->x2, render->y2);
	render->wall_dist = sqrt(render->wall_sqdist);
	render->wall_height = WALL_H * (double)render->wall->height
	/ (double)render->wall_dist;
	render->wall_y0 = WINDOW_H / 2 - render->wall_height / 2 + info->y_dec;
	render->wall_y1 = WINDOW_H / 2 + render->wall_height / 2 + info->y_dec;
	if (info->player->posz != render->wall->a.z)
	{
		render->wall_y0 += DECALLAGE * (render->wall->a.z - info->player->posz)
		/ render->wall_dist;
		render->wall_y1 += DECALLAGE * (render->wall->a.z - info->player->posz)
		/ render->wall_dist;
	}
}

void		put_item(int k, t_item *src, t_render *render, t_var *info)
{
	if (render->itab[k].name[0] == src->name[0] && src->cap == 1)
	{
		if ((src->name[0] == 'c' && src->pv > 0)
			|| (src->name[0] == 's' && src->pv > 0))
			draw_item_2(render, info, k, src);
		else if (src->name[0] == 'c' || src->name[0] == 's')
			src->cap = 3;
		else
			draw_item_2(render, info, k, src);
	}
	else if (src->next_item)
		put_item(k, src->next_item, render, info);
}

int			little_check(t_render *render, t_var *info, int k)
{
	if (render->itab[k].name == 0)
		if (k >= render->nb_item_to_draw &&
			little_check(render, info, k + 1) == 0)
			return (0);
	return (1);
}

void		go_to_sector(t_sector *sec_0, int id, t_render *render)
{
	if (sec_0->sector_id < id)
		go_to_sector(sec_0->next_sector, id, render);
	else
		render->s = sec_0;
}

int			calc_item_wall(t_render *render, t_item *item, t_var *info)
{
	render->wall_item.a.x = 0.3 * info->player->planex + item->x;
	render->wall_item.a.y = 0.3 * info->player->planey + item->y;
	render->wall_item.b.x = item->x - 0.3 * info->player->planex;
	render->wall_item.b.y = item->y - 0.3 * info->player->planey;
	return (1);
}
