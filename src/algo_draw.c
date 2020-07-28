/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/07/28 14:17:32 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void			floor_tool(t_f_tool *tool, t_var *info, t_render *render)
{
	tool->tx = (int)(render->tab_sdl[render->fid]->w
	* (tool->floorx - (int)tool->floorx)) &
	(render->tab_sdl[render->fid]->w - 1);
	tool->ty = (int)(render->tab_sdl[render->fid]->h *
	(tool->floory - (int)tool->floory)) &
	(render->tab_sdl[render->fid]->h - 1);
	tool->floorx += tool->stepx;
	tool->floory += tool->stepy;
	put_pixel(darken_floor(tool, render),
	tool->j, WINDOW_H - tool->i - 1, info->image);
}

void			cieling_tool(t_f_tool *tool, t_var *info, t_render *render)
{
	tool->tx = (int)(render->tab_sdl[render->cid]->w
	* (tool->floorx - (int)tool->floorx)) &
	(render->tab_sdl[render->cid]->w - 1);
	tool->ty = (int)(render->tab_sdl[render->cid]->h *
	(tool->floory - (int)tool->floory)) &
	(render->tab_sdl[render->cid]->h - 1);
	tool->floorx += tool->stepx;
	tool->floory += tool->stepy;
	put_pixel(darken_floor(tool, render), tool->j, tool->i, info->image);
}

int				tex_floor(t_var *info, t_render *render)
{
	t_f_tool tool;

	tool.i = WINDOW_H / 2 - 1 - info->y_dec;
	tool.j = -1;
	tool.k = -1;
	if (render->tab_sdl[render->fid])
	{
		while (tool.i++ <= WINDOW_H)
		{
			init_floor(info, &tool);
			while (tool.j++ <= WINDOW_W)
				floor_tool(&tool, info, render);
		}
	}
	else
		return (0);
	return (1);
}

int				tex_floor_ciel(t_var *info, t_render *render)
{
	t_f_tool tool;

	tool.i = WINDOW_H / 2 - 1 + info->y_dec;
	tool.j = -1;
	tool.k = -1;
	if (render->tab_sdl[render->cid])
	{
		while (tool.i++ <= WINDOW_H)
		{
			init_ceilling(info, &tool);
			while (tool.j++ <= WINDOW_W)
				cieling_tool(&tool, info, render);
		}
	}
	else
		return (0);
	return (tex_floor(info, render));
}

void			draw_texture_wall(t_var *info, t_render *render)
{
	t_w_draw draw;

	w_draw_calc(render, &draw);
	if (render->tab_sdl[render->wall->text_id]
		&& render->wall->text_id < NB_TEXT)
	{
		while (draw.i <= render->wall_y0)
		{
			if (draw.i == render->wall_y0 || draw.i == render->wall_y1)
				put_pixel(BLACK, render->x, draw.i, info->image);
			else
			{
				draw.texy += draw.step;
				draw.color = get_pixel(render->tab_sdl[render->wall->text_id],
				(int)draw.texy, (int)draw.pos_relative);
				put_pixel(darken_wall(info, draw.color, render, draw.i),
				render->x, draw.i, info->image);
			}
			draw.i++;
		}
	}
}
