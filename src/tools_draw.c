/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_draw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trabut <trabut@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 17:04:28 by lewis             #+#    #+#             */
/*   Updated: 2020/07/23 17:04:17 by trabut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void			rgb_cap(t_rgb *rgb)
{
	if (rgb->r >= 255)
		rgb->r = 255;
	if (rgb->g >= 255)
		rgb->g = 255;
	if (rgb->b >= 255)
		rgb->b = 255;
}

void			put_pixel(Uint32 color, int x, int y, SDL_Surface *image)
{
	Uint32 *pixels;

	pixels = image->pixels;
	if (x >= 0 && y >= 0 && x < image->w && y < image->h)
		pixels[y * image->w + x] = color;
}

void			crosshair(t_var *info)
{
	t_line		line;
	Uint32		color;
	int			a;

	a = 8;
	color = WHITE;
	line.x1 = WINDOW_W / 2 + a - 1;
	line.x2 = WINDOW_W / 2 - a;
	line.y1 = WINDOW_H / 2;
	line.y2 = WINDOW_H / 2;
	draw_line(info, &line, color);
	line.x1 = WINDOW_W / 2;
	line.x2 = WINDOW_W / 2;
	line.y1 = WINDOW_H / 2 + a - 1;
	line.y2 = WINDOW_H / 2 - a;
	draw_line(info, &line, color);
}

void			hitmarker(t_var *info)
{
	t_line line;
	Uint32 color;

	color = WHITE;
	line.x1 = WINDOW_W / 2 + 5;
	line.x2 = WINDOW_W / 2 + 15;
	line.y1 = WINDOW_H / 2 + 5;
	line.y2 = WINDOW_H / 2 + 15;
	draw_line(info, &line, color);
	line.x1 = WINDOW_W / 2 - 5;
	line.x2 = WINDOW_W / 2 - 15;
	line.y1 = WINDOW_H / 2 - 5;
	line.y2 = WINDOW_H / 2 - 15;
	draw_line(info, &line, color);
	line.x1 = WINDOW_W / 2 + 5;
	line.x2 = WINDOW_W / 2 + 15;
	line.y1 = WINDOW_H / 2 - 5;
	line.y2 = WINDOW_H / 2 - 15;
	draw_line(info, &line, color);
	line.x1 = WINDOW_W / 2 - 5;
	line.x2 = WINDOW_W / 2 - 15;
	line.y1 = WINDOW_H / 2 + 5;
	line.y2 = WINDOW_H / 2 + 15;
	draw_line(info, &line, color);
}
