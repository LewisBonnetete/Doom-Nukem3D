/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/07/27 14:02:39 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

float		ft_fabs(float a)
{
	if (a < 0)
		return (-1 * a);
	return (a);
}

int			draw_line_condition(t_line *line)
{
	return ((line->x1 != line->x2 || line->y1 != line->y2)
		&& line->x1 < WINDOW_W
		&& line->y1 < WINDOW_H && line->x1 >= 0 && line->y1 >= 0);
}

int			draw_line(t_var *info, t_line *line, Uint32 color)
{
	int		e2;

	line->dx = ft_fabs(line->x2 - line->x1);
	line->sx = line->x1 < line->x2 ? 1 : -1;
	line->dy = ft_fabs(line->y2 - line->y1);
	line->sy = line->y1 < line->y2 ? 1 : -1;
	line->err = (line->dx > line->dy ? line->dx : -line->dy) / 2;
	while (draw_line_condition(line))
	{
		put_pixel(color, line->x1, line->y1, info->image);
		e2 = line->err;
		if (e2 > -line->dx)
		{
			line->err -= line->dy;
			line->x1 += line->sx;
		}
		if (e2 < line->dy)
		{
			line->err += line->dx;
			line->y1 += line->sy;
		}
	}
	return (1);
}

void		draw_square(t_var *info, t_point a, t_point b, Uint32 color)
{
	int		x;
	t_line	line;

	x = a.x;
	while (x <= b.x)
	{
		line.x1 = x;
		line.x2 = x;
		line.y1 = a.y;
		line.y2 = b.y;
		draw_line(info, &line, color);
		x++;
	}
}

void		hud(t_var *info, t_player *player, t_map *map)
{
	SDL_Color	color;

	color.a = 255;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	if (info->font)
	{
		hp(info, player, color);
		name(info, map, color);
		inventory(info, color);
		weapon(info, player, color);
		munitions(info, color);
	}
}
