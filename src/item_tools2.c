/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   item_tools2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 17:04:28 by lewis             #+#    #+#             */
/*   Updated: 2020/07/15 17:30:47 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void		draw_i_color(t_var *info, t_render *render,
			t_i_tool *tool, t_item *item)
{
	if (tool->color != 0)
	{
		if (item->name[0] == 's')
		{
			if (tool->color != (Uint32)-6815608)
			{
				// if (render->x == WINDOW_W / 2 && tool->y == WINDOW_H / 2 && item->pv > 0)
				// {
				// 	info->player->no_scopex = item->x;
				// 	info->player->no_scopey = item->y;
				// 	printf(" %i | %i\n", item->x, item->y);
				// }
				put_pixel(darken_wall(info, tool->color, render, tool->y),
				render->x, tool->y, info->image);
			}
		}
		else if (item->name[0] == 'c')
		{
			// if (render->x == WINDOW_W / 2 && item->pv > 0)
			// {
			// 	info->player->no_scopex = item->x;
			// 	info->player->no_scopey = item->y;
			// 	printf(" %i | %i\n", item->x, item->y);
			// }
			put_pixel(darken_wall(info, tool->color, render, tool->y),
				render->x, tool->y, info->image);
		}
		else if (item->name[0] == 'p')
			put_pixel(tool->color, render->x, tool->y, info->image);
		else
			put_pixel(darken_wall(info, tool->color, render, tool->y),
				render->x, tool->y, info->image);
	}
}

int			may_weapon(t_item *item)
{
	if (item && item->cap == 2 && item->name[0] == 'a')
		return (1);
	else if (item && item->next_item)
		return (may_weapon(item->next_item));
	return (0);
}

void		ft_put_weapon(t_var *info, t_render *render)
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
