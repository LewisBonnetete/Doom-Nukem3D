/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   item_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trabut <trabut@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 15:51:41 by lbonnete          #+#    #+#             */
/*   Updated: 2020/07/28 14:57:22 by atyczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static	void	init_tools(t_render *render, t_var *info, int k, t_i_tool *tool)
{
	tool->p.x = info->player->posx;
	tool->p.y = info->player->posy;
	tool->w.x = render->itab[k].item_x;
	tool->w.y = render->itab[k].item_y;
	render->distance = calc_dist(tool->p, tool->w);
	tool->k = k;
	tool->pls = 0;
}

static	void	draw_item_if(t_var *info, t_render *render,
		t_i_tool *tool, t_item *item)
{
	if (render->itab[tool->k].text_id == 4)
	{
		item->cap = 3;
		info->player->hp += 25;
	}
	if (info->player->hp > 100)
		info->player->hp = 100;
	if (render->itab[tool->k].text_id == 0)
		item->cap = 2;
	if (render->itab[tool->k].text_id == 5)
	{
		if (may_weapon(render->item_0))
		{
			tool->weapon = go_to_item(render->item_0, 'a');
			while (tool->weapon && tool->weapon->hold != 1)
				tool->weapon = go_to_item(tool->weapon->next_item, 'a');
			if (!tool->weapon)
				tool->weapon = go_to_item(render->item_0, 'a');
			tool->weapon->mun += 25;
			item->cap = 3;
		}
		else
			item->cap = 0;
	}
	you_win(info, render, tool);
}

static	void	draw_i_help(t_render *render,
				t_i_tool *tool, t_item *item)
{
	if (render->distance <= 0.1)
		render->distance = 0.1;
	if (is_in_sector(tool->w, render->s) !=
		is_in_sector(tool->p, render->s) && item->name[0] == 'c')
		return ;
	if (is_in_sector(tool->w, render->s) !=
		is_in_sector(tool->p, render->s) && item->name[0] == 's')
		render->itab[tool->k].text_id = 6;
	render->height_item = render->itab[tool->k].h / render->distance;
	render->widht_item = render->itab[tool->k].w / render->distance;
	render->step_height = render->tab_sdl_item[render->itab[tool->k].text_id]->h
	/ render->height_item;
	render->step_width = render->tab_sdl_item[render->itab[tool->k].text_id]->w
	/ render->widht_item;
	render->tx = 0;
	render->itab[tool->k].end /= render->distance / 2;
}

static	void	item_checking(t_var *info,
				t_render *render, t_i_tool *tool, t_item *item)
{
	if (render->distance < 0.5 && (render->itab[tool->k].text_id == 0
	|| render->itab[tool->k].text_id == 4 || render->itab[tool->k].text_id == 5
	|| render->itab[tool->k].text_id == 7))
		draw_item_if(info, render, tool, item);
	else
		item->cap = 0;
	draw_i_help(render, tool, item);
	if (render->itab[tool->k].start == 0 &&
		render->widht_item > render->itab[tool->k].end)
	{
		render->tx = (render->widht_item - render->itab[tool->k].end)
		* render->step_width;
		render->widht_item -= (render->widht_item -
		render->itab[tool->k].end);
	}
	render->x = render->itab[tool->k].start - 1;
	render->p_0 = render->x + 2;
}

void			draw_item_2(t_render *render, t_var *info, int k, t_item *item)
{
	t_i_tool	tool;

	init_tools(render, info, k, &tool);
	item_checking(info, render, &tool, item);
	while (++render->x <= render->widht_item + render->p_0)
	{
		if (!draw_i2_help(info, render, &tool, k))
		{
			while (++tool.i <= render->height_item)
			{
				pls_ennemy(render, &tool, k);
				tool.ty += render->step_height;
				render->wall_dist = render->distance;
				draw_i_color(info, render, &tool, item);
				--tool.y;
			}
			render->tx += render->step_width;
		}
	}
}
