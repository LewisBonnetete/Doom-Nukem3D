/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   item_tools3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trabut <trabut@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/07/23 15:50:38 by trabut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int			check_sec(t_sector *sec, t_point a, t_point b,
		t_render *render)
{
	render->n = -1;
	while (++render->n < sec->nbr_walls)
	{
		render->wall = &sec->walls[render->n];
		if (render->wall->is_portal != 1
		&& intersect(render->ray, render->wall) == 1)
			if (calc_dist(a, b) > calc_dist(a, render->wall->a))
				return (1);
	}
	if (sec->next_sector)
		return (check_sec(sec->next_sector, a, b, render));
	return (0);
}

int			draw_i2_help(t_var *info, t_render *render,
					t_i_tool *tool, int k)
{
	t_point		a;
	t_point		b;

	a.x = info->player->posx;
	a.y = info->player->posy;
	b.x = render->itab[k].item_x;
	b.y = render->itab[k].item_y;
	tool->ty = 0;
	tool->y = WINDOW_H / 2 + WINDOW_H / 2 / render->distance;
	if (render->itab[k].name[0] == 'b')
		tool->y += WINDOW_H / 4 / render->distance;
	tool->i = -1;
	if (is_in_sector(a, render->s) == is_in_sector(b, render->s))
		return (0);
	update_ray(info, render);
	return (check_sec(render->sec_0, a, b, render));
}

void		i_color_set(t_var *info, t_render *render,
					t_i_tool *tool, t_item *item)
{
	if (tool->color != (Uint32) - 6815608)
	{
		if (render->x == WINDOW_W / 2 && tool->y ==
			WINDOW_H / 2 && item->pv > 0)
			info->player->no_scope = item->id;
		put_pixel(darken_wall(info, tool->color, render, tool->y),
		render->x, tool->y, info->image);
	}
}

void		you_win(t_var *info, t_render *render, t_i_tool *tool)
{
	if (render->itab[tool->k].text_id == 7)
	{
		ft_putendl("SUCCESS!");
		ft_exit(info, render);
	}
}
