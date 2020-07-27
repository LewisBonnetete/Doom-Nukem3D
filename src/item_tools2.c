/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   item_tools2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trabut <trabut@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 17:04:28 by lewis             #+#    #+#             */
/*   Updated: 2020/07/27 18:15:58 by trabut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void			draw_i_color(t_var *info, t_render *render,
			t_i_tool *tool, t_item *item)
{
	if (tool->color != 0)
	{
		if (item->name[0] == 's')
			i_color_set(info, render, tool, item);
		else if (item->name[0] == 'c')
		{
			if (render->x == WINDOW_W / 2 &&
				tool->y == WINDOW_H / 2 && item->pv > 0)
				info->player->no_scope = render->itab[tool->k].id;
			put_pixel(darken_wall(info, tool->color, render, tool->y),
				render->x, tool->y, info->image);
		}
		else if (item->name[0] == 'p')
			put_pixel(tool->color, render->x, tool->y, info->image);
		else if (item->name[0] == 'a')
			put_pixel(tool->color, render->x, tool->y, info->image);
		else
			put_pixel(darken_wall(info, tool->color, render, tool->y),
				render->x, tool->y, info->image);
	}
}

int				may_weapon(t_item *item)
{
	if (item && item->cap == 2 && item->name[0] == 'a')
		return (1);
	else if (item && item->next_item)
		return (may_weapon(item->next_item));
	return (0);
}

static	int		draw_i_iter(t_render *render, int k)
{
	int i;
	int tmp;

	tmp = k;
	i = -1;
	while (++i < render->nb_item_to_draw)
	{
		if (render->itab[k].dist < render->itab[i].dist
		&& render->itab[i].used == 0)
			tmp = i;
	}
	return (tmp);
}

static	void	draw_i_calc(t_render *render)
{
	int i;

	if (!render->itab)
		return ;
	if (render->nb_item_to_draw <= 0)
		return ;
	i = -1;
	while (++i < render->nb_item_to_draw + 1)
		if (render->itab[i].name == NULL)
		{
			render->itab[i].dist = -1;
			render->itab[i].used = 1;
		}
}

void			draw_item(t_render *render, t_var *info)
{
	int		j;
	int		k;

	draw_i_calc(render);
	j = -1;
	while (++j < render->nb_item_to_draw)
	{
		k = 0;
		while (render->itab[k].used != 0)
			++k;
		if (!render->itab[k].name)
			break ;
		k = draw_i_iter(render, k);
		if (render->itab[k].used != 1)
		{
			put_item(k, render->item_0, render, info);
			render->itab[k].used = 1;
			render->itab[k].dist = -1;
		}
	}
}
