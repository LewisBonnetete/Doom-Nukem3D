/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lewis <lewis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/04/19 18:01:04 by lewis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem_edit.h"

void	hud(t_var *info)
{
	t_point a;
	t_point b;

	a.x = WINDOW_H + 1;
	a.y = 0;
	b.x = WINDOW_W;
	b.y = WINDOW_H;
	draw_square(info, a, b, DARK);
}