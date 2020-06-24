/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/06/24 15:07:53 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem_edit.h"

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
