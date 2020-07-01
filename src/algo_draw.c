/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trabut <trabut@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/07/01 17:45:50 by atyczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void			tex_floor_ciel(t_var *info, t_render *render)
{
	t_f_tool tool;

	tool.i = 0;
	tool.j = 0;
	tool.k = 0;
	while (tool.i++ < WINDOW_H)
	{
		init_floor(info, &tool);
		while (tool.j++ < WINDOW_W)
		{
			tool.tx = (int)(render->tab_sdl[render->s->celling.text_id]->w
			* (tool.floorx - (int)tool.floorx)) &
			(render->tab_sdl[render->s->celling.text_id]->w - 1);
			tool.ty = (int)(render->tab_sdl[render->s->celling.text_id]->h *
			(tool.floory - (int)tool.floory)) &
			(render->tab_sdl[render->s->celling.text_id]->h - 1);
			tool.floorx += tool.stepx;
			tool.floory += tool.stepy;
			put_pixel(darken_floor(&tool, render), tool.j, tool.i, info->image);
			put_pixel(darken_floor(&tool, render),
			tool.j, WINDOW_H - tool.i - 1, info->image);
		}
	}
}

void			put_pixel(Uint32 color, int x, int y, SDL_Surface *image)
{
	Uint32 *pixels;

	pixels = image->pixels;
	if (x >= 0 && y >= 0 && x < image->w && y < image->h)
		pixels[y * image->w + x] = color;
}

void			draw_textures(t_var *info, t_render *render)
{
	draw_texture_wall(info, render);
}

void			draw_texture_wall(t_var *info, t_render *render)
{
	t_w_draw draw;

	w_draw_calc(render, info, &draw);
	while (draw.i <= render->wall_y0)
	{
		if (draw.i == render->wall_y0 || draw.i == render->wall_y1)
		{
			put_pixel(BLACK, render->x, draw.i, info->image);
		}
		else
		{
			draw.texy += draw.step;
			draw.color = get_pixel(render->tab_sdl[render->wall->text_id],
			(int)draw.pos_relative, (int)draw.texy);
			put_pixel(darken_wall(info, draw.color, render, draw.i),
			render->x, draw.i, info->image);
		}
		draw.i++;
	}
}
