/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   item_tools3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trabut <trabut@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/07/28 15:16:45 by atyczyns         ###   ########.fr       */
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
			if (xy_in_ab(render->ray->x2, render->ray->y2, a, b) == 1)
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
	tool->y = WINDOW_H / 2 + WINDOW_H / 2 /
	render->distance + info->y_dec + tool->pls;
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
	if (render->x == WINDOW_W / 2 && tool->y ==
		WINDOW_H / 2 && item->pv > 0)
		info->player->no_scope = render->itab[tool->k].id;
	if (tool->color != (Uint32) - 6815608)
	{
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

void		pls_ennemy(t_render *render, t_i_tool *tool, int k)
{
	if ((render->itab[k].name[0] == 'c' ||
	render->itab[k].name[0] == 's') && render->itab[k].pv <= 5)
	{
		tool->pls = 100 / render->itab[k].dist;
		tool->color = get_pixel(render->tab_sdl_item[render->itab[k].text_id],
		(int)render->tx,
		render->tab_sdl_item[render->itab[k].text_id]->h - (int)tool->ty);
	}
	else
		tool->color = get_pixel(render->tab_sdl_item[render->itab[k].text_id],
		render->tab_sdl_item[render->itab[k].text_id]->h -
		(int)tool->ty, (int)render->tx);
}
