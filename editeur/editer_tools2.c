/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editer_tools2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/07/03 14:32:53 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem_edit.h"

void		put_pixel_to_suface(Uint32 color, int x, int y, SDL_Surface *image)
{
	Uint32 *pixels;

	pixels = image->pixels;
	if (x >= 0 && y >= 0 && x < image->w && y < image->h)
		pixels[y * image->w + x] = color;
}

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
		put_pixel_to_suface(color, line->x1, line->y1, info->image);
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

t_sector	*get_to_last_sector(t_sector *sectors)
{
	t_sector *sector;

	sector = sectors;
	while (sector->next_sector)
	{
		sector = sector->next_sector;
	}
	return (sector);
}
